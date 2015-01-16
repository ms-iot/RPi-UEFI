/**
 *  Main file supporting the SEC Phase on ARM PLatforms
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#ifndef __SEC_H__
#define __SEC_H__

#include <Library/ArmLib.h>

#define IS_ALIGNED(Address, Align) (((UINTN)Address & (Align-1)) == 0)

VOID
TrustedWorldInitialization (
  IN  UINTN                     MpId,
  IN  UINTN                     SecBootMode
  );

VOID
NonTrustedWorldTransition (
  IN  UINTN                     MpId,
  IN  UINTN                     JumpAddress
  );

VOID
ArmSetupGicNonSecure (
  IN  INTN                  GicDistributorBase,
  IN  INTN                  GicInterruptInterfaceBase
);

// Vector Table for Sec Phase
VOID
SecVectorTable (
  VOID
  );

VOID
enter_monitor_mode (
  IN UINTN                  MonitorEntryPoint,
  IN UINTN                  MpId,
  IN UINTN                  SecBootMode,
  IN VOID*                  MonitorStackBase
  );

VOID
return_from_exception (
  IN UINTN                  NonSecureBase
  );

VOID
copy_cpsr_into_spsr (
  VOID
  );

VOID
set_non_secure_mode (
  IN ARM_PROCESSOR_MODE     Mode
  );

VOID
SecCommonExceptionEntry (
  IN UINT64  Type,
  IN UINT64  ESR,
  IN UINT64  ELR
  );

#endif
