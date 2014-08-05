//
//  Copyright (c) 2011-2013, ARM Limited. All rights reserved.
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
#include "SecInternal.h"

.text
.align 3

GCC_ASM_IMPORT(CEntryPoint)
GCC_ASM_IMPORT(ArmReadMpidr)
GCC_ASM_EXPORT(_ModuleEntryPoint)

//StartupAddr:        .word       ASM_PFX(CEntryPoint)

ASM_PFX(_ModuleEntryPoint):

  // Doing a second stage boot from SPL
  mov   r10, #ARM_SEC_SECONDARY_COLD_BOOT

_IdentifyCpu:
  // Identify CPU ID
  bl    ASM_PFX(ArmReadMpidr)
  // Keep a copy of the MpId register value
  mov   r9, r0

_CallCEntryPoint:
  mov   r0, r9
  mov   r1, r10
  blx ASM_PFX(CEntryPoint)

_NeverReturn:
  b _NeverReturn