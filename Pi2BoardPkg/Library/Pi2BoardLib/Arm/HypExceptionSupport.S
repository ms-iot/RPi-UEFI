#include <Chipset/ArmV7.h>

#define F_BIT           0x40
#define I_BIT           0x80
#define A_BIT           0x100

.text
.align 5

GCC_ASM_EXPORT(HypExceptionVectorTable)
GCC_ASM_EXPORT(ArmSwitchFromHypToSvcMode)

ASM_PFX(HypExceptionVectorTable):

ASM_PFX(Reset):
  .word 0

ASM_PFX(UndefinedInstruction):
  .word 0

ASM_PFX(HypCall):
  b ASM_PFX(_HypCallEntry)

ASM_PFX(PrefetchAbort):
  .word 0

ASM_PFX(DataAbort):
  .word 0

ASM_PFX(HypTrap):
  .word 0

ASM_PFX(Irq):
  .word 0

ASM_PFX(Fiq):
  .word 0

ASM_PFX(_HypCallEntry):
  mov     r0, #(F_BIT | I_BIT | A_BIT)
  orr     r0, r0, #CPSR_MODE_SVC
  msr     spsr_c, r0                    // SVC mode switch on exception return
  isb
  .word   0xE160006E                    // Place ERET unconditional command encoding
                                        // ERET{c} = 1110|0001011000000000000001101110
                                        // ERET is a HYP specific exception return instruction
                                        // available only on ARM7VE
                                        // Current toolchain is ARM GCC4.8 which does not have ARMV7VE
                                        // TODO: Replace .word 0xE160006E with ERET once toolchain is
                                        // GCC4.9 or higher

ASM_PFX(ArmSwitchFromHypToSvcMode):
  mov     r2, lr                        // copy the link register into a non-banked register
  mov     r3, sp                        // copy the stack pointer into a non-banked register
                                        // since we are not interested in HYP mode, we will
                                        // just reuse its stack
  isb
  svc     #0                            // request supervisor mode switch

  mov     sp, r3                        // restore stack pointer to reuse HYP stack
  mov     lr, r2                        // restore link register, otherwise bx lr will branch
                                        // to undefined memory addresses since svc stack may
                                        // have never been initialized
  bx      lr

ASM_FUNCTION_REMOVE_IF_UNREFERENCED