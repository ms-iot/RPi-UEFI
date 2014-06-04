//
//  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
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

#include <AutoGen.h>
#include <AsmMacroIoLib.h>
#include <Library/ArmPlatformLib.h>
#include <ArmPlatform.h>
#include "SecInternal.h"

.text
.align 3

GCC_ASM_IMPORT(CEntryPoint)
GCC_ASM_IMPORT(ArmPlatformIsPrimaryCore)
GCC_ASM_IMPORT(CopyFirmwareFromEMMC)
GCC_ASM_IMPORT(CopyFirmwareFromSDMMC)
GCC_ASM_IMPORT(ArmPlatformClockInitialize)
GCC_ASM_IMPORT(ArmPlatformSecBootAction)
GCC_ASM_IMPORT(ArmPlatformSecBootMemoryInit)
GCC_ASM_IMPORT(ArmDisableInterrupts)
GCC_ASM_IMPORT(ArmDisableCachesAndMmu)
GCC_ASM_IMPORT(ArmEnableBranchPrediction)
GCC_ASM_IMPORT(ArmReadMpidr)
GCC_ASM_IMPORT(ArmCallWFE)
GCC_ASM_IMPORT(_SecEntryFromTzsw)
GCC_ASM_EXPORT(_ModuleEntryPoint)

SecStartupAddr:	    .word       ASM_PFX(_SecEntryFromTzsw)
StartupAddr:        .word       ASM_PFX(CEntryPoint)

// Convert the (ClusterId,CoreId) into a Core Position
// 0x0F03 is the magic value for ARM_CORE_MASK | ARM_CLUSTER_MASK
//Core is 0-1 bits and cluster is 8-11 bits
#define GetCorePositionFromMpId(Pos, MpId, Tmp)    \
	ldr   Tmp, =0x0F03 ;                             \
	and   MpId, Tmp ;                                \
	lsr   Pos, MpId, #6 ;                            \
	and   Tmp, MpId, #3 ;                            \
	add   Pos, Pos, Tmp

// Reserve a region at the top of the IRAM Core stack
// for Global variables for the XIP phase
#define SetiRamStack(StackTop, GlobalSize, Tmp)  \
  and     Tmp, GlobalSize, #7         ;             \
  rsbne   Tmp, Tmp, #8                ;             \
  add     GlobalSize, GlobalSize, Tmp ;             \
  sub     sp, StackTop, GlobalSize    ;             \
                                      ;             \
  mov     Tmp, sp                     ;             \
  mov     GlobalSize, #0x0            ;             \
_SetiRamStackInitGlobals:             ;             \
  cmp     Tmp, StackTop               ;             \
  beq     _SetiRamStackEnd            ;             \
  str     GlobalSize, [Tmp], #4       ;             \
  b       _SetiRamStackInitGlobals    ;             \
_SetiRamStackEnd:


ASM_PFX(_ModuleEntryPoint):
  // First ensure all interrupts are disabled
  bl    ASM_PFX(ArmDisableInterrupts)

  // Ensure that the MMU and caches are off
  bl    ASM_PFX(ArmDisableCachesAndMmu)

  // Jump to Platform Specific Boot Action function
  blx   ASM_PFX(ArmPlatformSecBootAction)

  # Enable branch prediction
  bl  ASM_PFX(ArmEnableBranchPrediction)

  # TZPC1_DECPROT1Set (work-around for connecting T32 in SD booting mode)
//  ldr  r0, =0x10110810
//  mov  r1, #0xF
//  str  r1, [r0]
//  dsb
//  isb
//  sev

//  ldr  r0, =0x1
//  ldr  r1, =0x2
//infloop:
//  cmp  r0, r1
// bme  infloop


_IdentifyCpu:
  // Identify CPU ID
  bl   ASM_PFX(ArmReadMpidr)
 // Keep a copy of the MpId register value
  mov   r5, r0

  // Is it the Primary Core ?
  bl   ASM_PFX(ArmPlatformIsPrimaryCore)
  cmp   r0, #1

  // Only the primary core initialize the memory (SMC)
  beq  _InitMem

_WaitInitMem:
  // Wait for the primary core to initialize the initial memory (event: BOOT_MEM_INIT)
  bl   ASM_PFX(ArmCallWFE)
  // Now the Init Mem is initialized, we setup the secondary core stacks
  b    _SetupSecondaryCoreStack

_InitMem:
  // Initialize Init Boot Memory
  mov  r0, pc
  ldr  r1, =0x40000000
  cmp  r0, r1
  bgt  _SetupPrimaryCoreStack

  bl  ASM_PFX(ArmPlatformClockInitialize)

  LoadConstantToReg (FixedPcdGet32(PcdiRamStackBase), r1)
  LoadConstantToReg (FixedPcdGet32(PcdiRamStackSize), r2)

	// The reserved space for global variable must be 8-bytes aligned for pushing
  // 64-bit variable on the stack
  SetiRamStack (r1, r2, r3)

  bl  ASM_PFX(ArmPlatformSecBootMemoryInit)

_SetupPrimaryCoreStack:
  // Get the top of the primary stacks (and the base of the secondary stacks)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoresSecStackBase), r1)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoreSecPrimaryStackSize), r2)
  add  r1, r1, r2

  LoadConstantToReg (FixedPcdGet32(PcdSecGlobalVariableSize), r2)

  // The reserved space for global variable must be 8-bytes aligned for pushing
  // 64-bit variable on the stack
  SetPrimaryStack (r1, r2, r3)

  mov  r0, pc
  ldr  r1, =0x40000000
  cmp  r0, r1
  bgt  _PrepareArguments_NonTZ

  b    _CopyFirmware

_SetupSecondaryCoreStack:
  // Get the top of the primary stacks (and the base of the secondary stacks)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoresSecStackBase), r1)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoreSecPrimaryStackSize), r2)
  add  r1, r1, r2

  // Get the Core Position (ClusterId * 4) + CoreId
  GetCorePositionFromMpId(r0, r5, r2)
  // The stack starts at the top of the stack region. Add '1' to the Core Position to get the top of the stack
  add  r0, r0, #1

  // StackOffset = CorePos * StackSize
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoreSecSecondaryStackSize), r2)
  mul  r0, r0, r2
  // SP = StackBase + StackOffset
  add  sp, r1, r0

  b _PrepareArguments_NonTZ

_PrepareArguments:
  // Move sec startup address into a data register
  // Ensure we're jumping to FV version of the code (not boot remapped alias)
	LoadConstantToReg (FixedPcdGet32(PcdTrustzoneSupport), r2)
	cmp  r2, #0x1				/* TrustZone Enable */
  beq  _PrepareArguments_TZ

_PrepareArguments_NonTZ:
  ldr  r3, StartupAddr
  // Jump to SEC C code
  //   r0 = mp_id
  mov  r0, r5
  blx  r3

_PrepareArguments_TZ:
  /* Load IRAM_NS on IRAM_NS_BASE */
  /* TZSW will call IRAM_NS code */
  bl      relocate_code

  /* Jump to Coldboot in TZSW */
  ldr  r0, SecStartupAddr
  b    _ColdBootTzsw

_CopyFirmware:
  ldr  r0, =Exynos5250_CMU_BASE
  ldr  r2, =CLK_DIV_FSYS2_OFFSET
  ldr  r1, [r0, r2]
  bic  r1, r1, #(0xFF << 8)
  bic  r1, r1, #(0xF)
  orr  r1, r1, #(0x9<< 8)
  orr  r1, r1, #0x3
  str  r1, [r0, r2]

  /* Read booting information */
  ldr r0, =0x10040000
  ldr r1, [r0,#0x0]
  bic r2, r1, #0xffffffc1

  cmp r2, #0x8
  beq _CopyFirmwareEMMC

  /* SD/MMC BOOT */
  cmp r2, #0x4
  beq _CopyFirmwareSDMMC


_CopyFirmwareSDMMC:
  bl  ASM_PFX(CopyFirmwareFromSDMMC)
  b   _PrepareArguments

_CopyFirmwareEMMC:
  bl  ASM_PFX(CopyFirmwareFromEMMC)
  b   _PrepareArguments

_ColdBootTzsw:
  bl  ASM_PFX(ColdBootForTzsw)
_NeverReturn:
  b _NeverReturn


/*
 * relocate_code: load NonSecure code(cpu1_wait)
 */
relocate_code:
  adr     r0, nscode_base                 @ r0: source address (start)
  adr     r1, nscode_end                  @ r1: source address (end)
  ldr     r2, =CONFIG_PHY_IRAM_NS_BASE    @ r2: target address

1:
  ldmia   r0!, {r3-r6}
  stmia   r2!, {r3-r6}
  cmp     r0, r1
  blt     1b

  .word   0xF57FF04F                      @dsb    sy
  .word   0xF57FF06F                      @isb    sy

  mov     pc, lr

/*
 * CPU1 waits here until CPU0 wake it up.
 * - below code is copied to CONFIG_PHY_IRAM_NS_BASE, which is non-secure memory.
 */
nscode_base:
  adr     r0, _ns_reg5
  b       1f

  .word   0x0                     @ REG0: RESUME_ADDR
  .word   0x0                     @ REG1: RESUME_FLAG
  .word   0x0                     @ REG2
  .word   0x0                     @ REG3
  .word   0x0                     @ REG4
_ns_reg5:
  .word   0x0                     @ REG5: CPU1_BOOT_REG
  .word   0x0                     @ REG6: REG_DIRECTGO_FLAG
  .word   0x0                     @ REG7: REG_DIRECTGO_ADDR
  .word   0x0                     @ REG8
  .word   0x0                     @ REG9

  nop
  nop

1:
#if 0   /* Exynos5250 do not require this code */
  mrc     p15, 0, r1, c0, c0, 5           @ MPIDR
  and     r1, r1, #0x3
  add     r0, r0, r1, lsl #0x2
#endif
cpu1_wait:
  .word   0xE320F002                      @ wfe instruction
  ldr     r1, [r0]
  cmp     r1, #0x0
  bxne    r1
  b       cpu1_wait
  nop
nscode_end:
