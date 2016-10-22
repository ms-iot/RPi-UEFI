//
//  Copyright (c) 2011-2014, ARM Limited. All rights reserved.
//  Copyright (c) Microsoft Corporation. All rights reserved.
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

#include <AsmMacroIoLib.h>
#include <Base.h>
#include <Library/PcdLib.h>
#include <AutoGen.h>

#include <Chipset/ArmV7.h>

.text
.align 3

GCC_ASM_IMPORT(CEntryPoint)
GCC_ASM_IMPORT(ArmPlatformIsPrimaryCore)
GCC_ASM_IMPORT(ArmReadMpidr)
GCC_ASM_IMPORT(ArmPlatformPeiBootAction)
GCC_ASM_IMPORT(ArmPlatformStackSet)
GCC_ASM_EXPORT(_ModuleEntryPoint)

StartupAddr: .word    CEntryPoint


ASM_PFX(_ModuleEntryPoint):
  // Do early platform specific actions
  bl    ASM_PFX(ArmPlatformPeiBootAction)

  // Get ID of this CPU in Multicore system
  bl    ASM_PFX(ArmReadMpidr)
  // Keep a copy of the MpId register value
  mov   r8, r0

_SetSVCMode:
  // Enter SVC mode, Disable FIQ and IRQ
  mov     r1, #(CPSR_MODE_SVC | CPSR_IRQ | CPSR_FIQ)
  msr     CPSR_c, r1

// Check if we can install the stack at the top of the System Memory or if we need
// to install the stacks at the bottom of the Firmware Device (case the FD is located
// at the top of the DRAM)
_SetupStackPosition:
  LoadConstantToReg (FixedPcdGet64 (PcdSystemMemoryBase), r1)

  // PcdSystemMemoryBase is declared as both Fixed and Dynamic in the Arm package dec file
  // The default is Fixed unless a UEFI package redeclare its dsc as Dynamic
  // If PcdSystemMemorySize is used in its default fixed form, then use that, otherwise
  // call a platform specific implementation which knows how to compute dynamic system
  // memory size. Most of the time it will be a platform specific dynamic PcdGet64
  // NOTE: ArmPlatformGetSystemMemorySize implementation should assume that no stack is 
  // setup and may need to work around this limitation.
.ifdef FixedPcdGet64 (PcdSystemMemorySize)
  LoadConstantToReg (FixedPcdGet64 (PcdSystemMemorySize), r2)
.else
  bl    ASM_PFX(ArmPlatformGetSystemMemorySize)
  mov   r2, r0
.endif
  sub   r2, r2, #1
  add   r1, r1, r2      // r1 = SystemMemoryTop = PcdSystemMemoryBase + PcdSystemMemorySize

  // Calculate Top of the Firmware Device
  LoadConstantToReg (FixedPcdGet32(PcdFdBaseAddress), r2)
  LoadConstantToReg (FixedPcdGet32(PcdFdSize), r3)
  sub   r3, r3, #1
  add   r3, r3, r2      // r3 = FdTop = PcdFdBaseAddress + PcdFdSize

  // UEFI Memory Size (stacks are allocated in this region)
  LoadConstantToReg (FixedPcdGet32(PcdSystemMemoryUefiRegionSize), r4)

  //
  // Reserve the memory for the UEFI region (contain stacks on its top)
  //

  // Calculate how much space there is between the top of the Firmware and the Top of the System Memory
  subs  r0, r1, r3      // r0 = SystemMemoryTop - FdTop
  bmi   _SetupStack     // Jump if negative (FdTop > SystemMemoryTop). Case when the PrePi is in XIP memory outside of the DRAM
  cmp   r0, r4
  bge   _SetupStack

  // Case the top of stacks is the FdBaseAddress
  mov   r1, r2

_SetupStack:
  // r1 contains the top of the stack (and the UEFI Memory)

  // Because the 'push' instruction is equivalent to 'stmdb' (decrement before), we need to increment
  // one to the top of the stack. We check if incrementing one does not overflow (case of DRAM at the
  // top of the memory space)
  adds  r9, r1, #1
  bcs   _SetupOverflowStack

_SetupAlignedStack:
  mov   r1, r9
  b     _GetBaseUefiMemory

_SetupOverflowStack:
  // Case memory at the top of the address space. Ensure the top of the stack is EFI_PAGE_SIZE
  // aligned (4KB)
  LoadConstantToReg (EFI_PAGE_MASK, r9)
  and   r9, r9, r1
  sub   r1, r1, r9

_GetBaseUefiMemory:
  // Calculate the Base of the UEFI Memory
  sub   r9, r1, r4

_GetStackBase:
  // r1 = The top of the Mpcore Stacks
  // Stack for the primary core = PrimaryCoreStack
  LoadConstantToReg (FixedPcdGet32(PcdCPUCorePrimaryStackSize), r2)
  sub   r10, r1, r2

  // Stack for the secondary core = Number of Cores - 1
  LoadConstantToReg (FixedPcdGet32(PcdCoreCount), r0)
  sub   r0, r0, #1
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoreSecondaryStackSize), r1)
  mul   r1, r1, r0
  sub   r10, r10, r1

// Check to see if a PcdCPUCoresStackBase value was provided (none-zero) and if so use that
// as the base for the CPU core stacks. This is *required* to be used for the Multi-Processor
// Parking Protocol as used by Windows because the secondary cores are started after
// ExitBootServices such that UEFI memory has already been released. Therefore, the memory
// represented by PcdCPUCoresStackBase *must* be outside of the System Memory declared to
// UEFI such that it's always available for use at any time.
//
// NOTE: This only applies to the secondary cores that will end up parked.
//
_CheckForExplictStack:
  // Is it the Primary Core ?
  mov   r0, r8
  bl    ASM_PFX(ArmPlatformIsPrimaryCore)
  cmp   r0, #1
  beq   _PlatformStackSet

  LoadConstantToReg (FixedPcdGet32 (PcdCPUCoresStackBase), r0)
  cmp   r0, #0
  beq   _PlatformStackSet

  // Use the explicit stack address instead.
  mov   r10, r0

_PlatformStackSet:
  // r10 = The base of the MpCore Stacks (primary stack & secondary stacks)
  mov   r0, r10
  mov   r1, r8
  //ArmPlatformStackSet(StackBase, MpId, PrimaryStackSize, SecondaryStackSize)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCorePrimaryStackSize), r2)
  LoadConstantToReg (FixedPcdGet32(PcdCPUCoreSecondaryStackSize), r3)
  bl    ASM_PFX(ArmPlatformStackSet)

  // Is it the Primary Core ?
  mov   r0, r8
  bl    ASM_PFX(ArmPlatformIsPrimaryCore)
  cmp   r0, #1
  bne   _PrepareArguments

_ReserveGlobalVariable:
  LoadConstantToReg (FixedPcdGet32(PcdPeiGlobalVariableSize), r0)
  // InitializePrimaryStack($GlobalVariableSize, $Tmp1)
  InitializePrimaryStack(r0, r1)

_PrepareArguments:
  mov   r0, r8
  mov   r1, r9
  mov   r2, r10
  mov   r3, sp

  // Move sec startup address into a data register
  // Ensure we're jumping to FV version of the code (not boot remapped alias)
  ldr   r4, StartupAddr

  // Jump to PrePiCore C code
  //    r0 = MpId
  //    r1 = UefiMemoryBase
  //    r2 = StacksBase
  //    r3 = GlobalVariableBase
  blx   r4

_NeverReturn:
  b _NeverReturn

