//
//  Copyright (c), Microsoft Corporation. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//

#include <Base.h>
#include <AutoGen.h>
#include <Bcm2836.h>
#include <Bcm2836Gpio.h>
#include <AsmMacroIoLib.h>
#include <Chipset/ArmV7.h>

// Required for compilation with smc instruction
.arch_extension sec
                 
.text
.align 5

GCC_ASM_EXPORT(ArmPlatformSecBootAction)
GCC_ASM_EXPORT(ArmPlatformSecBootMemoryInit)

ASM_PFX(SecureMonitorExceptionVectorTable):
ASM_PFX(Reset):
  .word 0
ASM_PFX(UndefinedInstruction):
  .word 0
ASM_PFX(MonCall):
  b ASM_PFX(_MonCallExceptionHandler)
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

/**
  The main reason for entering the Monitor mode is to reset CNTVOFF
  and return back to SVC mode
**/
ASM_PFX(_MonCallExceptionHandler):
  mov r0, #(CPSR_FIQ | CPSR_IRQ | CPSR_ASYNC_ABORT)
  orr r0, r0, #CPSR_MODE_SVC
  msr spsr_cxfs, r0                       // Slot in SVC mode on this exception return

  mrc p15, 0, r1, c1, c1, 0               // Read SCR, Secure Configuration
  orr r1, r1, #0x1                        // Enable NS, Non-Secure
  mcr p15, 0, r1, c1, c1, 0               // Write SCR (with NS bit set)

  isb                                     // Synchronize with the new Non-Secure mode

  mov r0, #0
  mcrr p15, 4, r0, r0, c14                // Reset CNTVOFF (Counter Virtual Offset) to zero
                                          // If CNTVOFF is not reset to zero, the OS does not
                                          // boot successfully

  bic r1, r1, #0x1                        // Disable NS
  mcr p15, 0, r1, c1, c1, 0               // Write SCR (with NS bit unset)

  movs pc, lr                             // Return from exception to secure SVC

/**
  Current core enters a dead-loop in which only a JTAG
  debugger will be able to break it by simple changing
  the PC to LR
**/
ASM_PFX(_DeadLoop):
loop:
  b loop
  bx lr

/**
  Enable JTAG debugging by performing board specific JTAG pin muxing

  JTAG GPIO Pins:
  GPIO22 ALT4 TRST  - FSEL22
  GPIO23 ALT4 RTCK  - FSEL23
  GPIO24 ALT4 TDO   - FSEL24
  GPIO25 ALT4 TCK   - FSEL25
  GPIO26 ALT4 TDI   - FSEL26
  GPIO27 ALT4 TMS   - FSEL27
  
  GPFSEL2[20..29]      29 |28 |27 |26 |25 |24 |23 |22 |21 |20
  JTAG FSEL bit mask   000 000 111 111 111 111 111 111 000 000 = 0x00FFFFC0
  JTAG FSEL ALT Func   000 000 011 011 011 011 011 011 000 000 = 0x006DB6C0
**/
ASM_PFX(_ConfigureJtag):

#define JTAG_PINS_BIT_MASK          0x00FFFFC0
#define JTAG_PINS_FSEL_OUTPUT_SET   0x006DB6C0

  ldr r1, =GPIO_GPFSEL2
  ldr r0, [r1]                      // Read GPFSEL2
  ldr r2, =JTAG_PINS_BIT_MASK
  ldr r3, =JTAG_PINS_FSEL_OUTPUT_SET
  bic r0, r0, r2                    // Mask all JTAG pins FSEL bits
  orr r0, r0, r3                    // Set JTAG pins FSEL bits 000 000 011 011 011 011 011 011 000 000
  str r0, [r1]                      // Write GPFSEL2 with JTAG ALT functions

  // Blink green LED at GPIO47 to indicate JTAG enabled if needed

  LoadConstantToReg (FixedPcdGetBool(PcdJtagLedBlinkOnConfig), r3)
  cmp r3, #0
  beq blinkEnd

#define GPIO47_FSEL_MASK            0x00E00000
#define GPIO47_FSEL_OUTPUT_SET      0x00200000
#define GPIO47_GPSET_GPCLR_SET      0x00008000

  ldr r1, =GPIO_GPFSEL4
  ldr r0, [r1]                      // Read GPFSEL4
  ldr r2, =GPIO47_FSEL_MASK
  ldr r3, =GPIO47_FSEL_OUTPUT_SET
  bic r0, r0, r2                    // Mask GPIO47 GPFSEL4 bits
  orr r0, r0, r3                    // Set GPIO47 to output
  str r0, [r1]

  ldr r1, =GPIO_GPSET1
  ldr r2, =GPIO_GPCLR1
  ldr r7, =GPIO47_GPSET_GPCLR_SET
  ldr r8, =500000                   // loopDelay count
  mov r3, #0                        // Set/Clear flag

  mov r4, #0                        // Init loopSpin counter
loopSpin:
  mov r5, #0                        // Init loopDelay counter
loopDelay:
  mov r0, r0                        // Dummy op
  add r5, r5, #1                    // Increment loopDelay counter
  cmp r5, r8
  blt loopDelay
  cmp r3, #0
  beq gpset
  ldr r6, [r2]                      // Read GPIO_GPCLR1
  orr r6, r6, r7                    // Set pin Low
  str r6, [r2]
  b endsetclr
gpset:
  ldr r6, [r1]                      // Read GPIO_GPSET1
  orr r6, r6, r7                    // Set pin High
  str r6, [r1]
endsetclr:
  mvn r3, r3                        // Flip Set/Clear flag
  add r4, r4, #1                    // Increment loopSpin counter
  cmp r4, #6
  blt loopSpin
blinkEnd:

  bx lr

/**
  Call at the beginning of the platform boot up

  This function allows the firmware platform to do extra actions at the early
  stage of the platform power up.

  Note: This function must be implemented in assembler as there is no stack set up yet
**/
ASM_PFX(ArmPlatformSecBootAction):
  mov r9, lr                                // Save a copy of lr since stack has not been set yet
                                            // which implies that all functions called here should 
                                            // not call other functions, i.e not to use stack as well

  LoadConstantToReg (FixedPcdGetBool(PcdJtagEnabled), r0)
  cmp r0, #0
  beq jtagEnd                               // Config board for JTAG if Pcd flag enabled 
  
jtagStart:
  bl ASM_PFX(ArmReadMpidr)
  bl ASM_PFX(ArmPlatformIsPrimaryCore)
  cmp r0, #0
  beq jtagEnd                               // Only primary core configure JTAG

  bl ASM_PFX(_ConfigureJtag)

  LoadConstantToReg (FixedPcdGetBool(PcdJtagPrimaryCoreDeadLoopPostConfig), r0)
  cmp r0, #0
  beq jtagEnd
  bl ASM_PFX(_DeadLoop)                      // Primary core enters a dead-loop
jtagEnd:
  
  adr r1, SecureMonitorExceptionVectorTable
  mcr p15, 0, r1, c12, c0, 1                // Set MVBAR to secure exception vectors

  smc #0                                    // Call into MONITOR mode to reset counter virtual 
                                            // offset and switch back to secure-SVC mode

  mov lr, r9                                // Restore lr after being possibly overriden by
                                            // other bl calls up
  bx lr

/**
  Initialize the memory where the initial stacks will reside

  This memory can contain the initial stacks (Secure and Secure Monitor stacks).
  In some platform, this region is already initialized and the implementation of this function can
  do nothing. This memory can also represent the Secure RAM.
  This function is called before the satck has been set up. Its implementation must ensure the stack
  pointer is not used (probably required to use assembly language)

**/
ASM_PFX(ArmPlatformSecBootMemoryInit):
  // The SDRAM does not need to be initialized for Pi - already done.

  bx    lr
