/** @file
*
*  Copyright (c) 2013-2014, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <PiDxe.h>

#include <Library/DebugLib.h>
#include <Library/EfiResetSystemLib.h>
#include <Library/ArmSmcLib.h>
#include <ArmJunoSmc.h>

/**
  Resets the entire platform.

  @param  ResetType             The type of reset to perform.
  @param  ResetStatus           The status code for the reset.
  @param  DataSize              The size, in bytes, of WatchdogData.
  @param  ResetData             For a ResetType of EfiResetCold, EfiResetWarm, or
                                EfiResetShutdown the data buffer starts with a Null-terminated
                                Unicode string, optionally followed by additional binary data.

**/
EFI_STATUS
EFIAPI
LibResetSystem (
  IN EFI_RESET_TYPE   ResetType,
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN CHAR16           *ResetData OPTIONAL
  )
{
  ARM_SMC_ARGS SmcArgs;

  switch (ResetType) {
  case EfiResetWarm:
  case EfiResetCold:
    // Map a warm reset into a cold reset
    SmcArgs.Arg0 = ARM_JUNO_ARM_FAST_SMC_SET_SYSTEM_POWER_STATE;
    SmcArgs.Arg1 = ARM_JUNO_ARM_FAST_SMC_SYSTEM_POWER_STATE_REBOOT;
    break;
  case EfiResetShutdown:
    SmcArgs.Arg0 = ARM_JUNO_ARM_FAST_SMC_SET_SYSTEM_POWER_STATE;
    SmcArgs.Arg1 = ARM_JUNO_ARM_FAST_SMC_SYSTEM_POWER_STATE_SHUTDOWN;
    break;
  default:
    SmcArgs.Arg0 = 0;
    ASSERT(FALSE);
  }

  if (SmcArgs.Arg0 != 0) {
    ArmCallSmc (&SmcArgs);
    // We should never be here
    while(1);
  }

  return EFI_UNSUPPORTED;
}

/**
  Initialize any infrastructure required for LibResetSystem () to function.

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
LibInitializeResetSystem (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return EFI_SUCCESS;
}
