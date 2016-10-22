//------------------------------------------------------------------------------
//
// Copyright (c) 2013 - 2014, ARM Limited. All rights reserved.
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// This program and the accompanying materials
// are licensed and made available under the terms and conditions of the BSD License
// which accompanies this distribution.  The full text of the license may be found at
// http://opensource.org/licenses/bsd-license.php
//
// THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
// WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//------------------------------------------------------------------------------

#include <AsmMacroIoLib.h>

    INCLUDE AsmMacroIoLib.inc

    EXPORT ArmReadCpuExCr
    EXPORT ArmWriteCpuExCr

    AREA ArmCortexA5xHelper, CODE, READONLY

ArmReadCpuExCr
  mrrc    p15, 1, r0, r1, c15
  bx      lr

ArmWriteCpuExCr
  mcrr    p15, 1, r0, r1, c15
  dsb
  isb
  bx      lr


  END
