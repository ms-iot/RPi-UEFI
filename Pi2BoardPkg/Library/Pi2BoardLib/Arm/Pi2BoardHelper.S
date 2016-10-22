#
#  Copyright (c), Microsoft Corporation. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#

#include <AsmMacroIoLib.h>
#include <Library/ArmLib.h>
#include <AutoGen.h>

.text
.align 2

GCC_ASM_EXPORT(ArmPlatformPeiBootAction)
GCC_ASM_EXPORT(ArmPlatformIsPrimaryCore)
GCC_ASM_EXPORT(ArmPlatformGetPrimaryCoreMpId)
GCC_ASM_EXPORT(ArmPlatformGetCorePosition)
GCC_ASM_EXPORT(ArmReadCPSRMode)
GCC_ASM_EXPORT(ArmPlatformGetSystemMemorySize)
GCC_ASM_IMPORT(LibPcdGet64)
GCC_ASM_IMPORT(ArmPlatformStackSet)

GCC_ASM_IMPORT(_gPcd_FixedAtBuild_PcdArmPrimaryCore)
GCC_ASM_IMPORT(_gPcd_FixedAtBuild_PcdArmPrimaryCoreMask)

//UINTN
//ArmPlatformGetPrimaryCoreMpId (
//  VOID
//  );
ASM_PFX(ArmPlatformGetPrimaryCoreMpId):
  LoadConstantToReg (_gPcd_FixedAtBuild_PcdArmPrimaryCore, r0)
  ldr   r0, [r0]
  bx    lr

//UINTN
//ArmPlatformIsPrimaryCore (
//  IN UINTN MpId
//  );
ASM_PFX(ArmPlatformIsPrimaryCore):
  LoadConstantToReg (_gPcd_FixedAtBuild_PcdArmPrimaryCoreMask, r1)
  ldr   r1, [r1]
  and   r0, r0, r1
  LoadConstantToReg (_gPcd_FixedAtBuild_PcdArmPrimaryCore, r1)
  ldr   r1, [r1]
  cmp   r0, r1
  moveq r0, #1
  movne r0, #0
  bx    lr

//UINTN
//ArmPlatformGetCorePosition (
//  IN UINTN MpId
//  );
ASM_PFX(ArmPlatformGetCorePosition):
  and   r0, r0, #ARM_CORE_MASK
  bx    lr

ASM_PFX(ArmPlatformPeiBootAction):
  bx    lr
  
ASM_PFX(ArmReadCPSRMode):
  mrs     r0, cpsr
  ldr     r1, =CPSR_MODE_MASK
  and     r0, r0, r1
  bx      lr

_LibPcdGet64Addr: .word   LibPcdGet64

//
//UINT32
//EFIAPI
//ArmPlatformGetSystemMemorySize (
//  VOID
//  );
ASM_PFX(ArmPlatformGetSystemMemorySize):
  
  // The caller assumes this function is implemented in pure assembly
  // We can be called before UEFI stacks are properly setup or event existed
  // However, RPi memory assignemnt to GPU and System is specified by a Config
  // file which is consumed by the VideoCore (VC) firmware, and for UEFI to know
  // system memory assignment it will have to communicate with the GPU at least
  // once to get system memory size and cache it.
  // Facts:
  // - VC mailbox communication layer is very tedious to implement in pure assembly and
  //   is currently implemented in C code which assumes call stacks are there
  // - Pi2PcdLib!LibPcdGet64 will need to query system memory size form VC once and
  //   cache
  // To overcome the stacks limitation, we install a temp call stack at physical memory
  // location PcdCPUCoresSecStackBase for each core which in case of RPi is in UEFI boot
  // memory region, at the bottom of the memory.
  // It is safe to reuse the secure stack area since RPi does not have TrustedZone enabled
  // and that memory region is unused.

  mov   r9, lr
  mov   r10, sp

  bl    ASM_PFX(ArmReadMpidr)                     
  mov   r1, r0                                             // r1 = MpId

  LoadConstantToReg (
    FixedPcdGet32(PcdCPUCoresSecStackBase), r0)            // r0 = StackBase
  // Adjust SP if not 8-byte aligned
  tst   r0, #4
  subne r0, r0, #4                                                        
  LoadConstantToReg (
    FixedPcdGet32(PcdCPUCoreSecPrimaryStackSize), r2)      // r2 = PrimaryStackSize
  LoadConstantToReg (
    FixedPcdGet32(PcdCPUCoreSecSecondaryStackSize), r3)    // r3 = SecondaryStackSize
  
  //ArmPlatformStackSet(
  //  StackBase,
  //  MpId,
  //  PrimaryStackSize,
  //  SecondaryStackSize)
  bl    ASM_PFX(ArmPlatformStackSet)

  ldr   r0, =(PcdToken(PcdSystemMemorySize))               // Load the PCD token value for LibPcdGet64
  blx   ASM_PFX(LibPcdGet64)
  // On LibPcdGet64 return
  // r0 = Lower 32-bit
  // r1 = Higher 32-bit

  mov   sp, r10
  mov   lr, r9

  bx    lr

ASM_FUNCTION_REMOVE_IF_UNREFERENCED