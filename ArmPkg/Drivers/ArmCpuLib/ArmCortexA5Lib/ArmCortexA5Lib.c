/** @file

  Copyright (c) 2011-2012, ARM Limited. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/ArmLib.h>
#include <Library/ArmCpuLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>

#include <Chipset/ArmCortexA5.h>

VOID
ArmCpuSetup (
  IN  UINTN         MpId
  )
{
  // Enable SWP instructions
  ArmEnableSWPInstruction ();

  // Enable program flow prediction, if supported.
  ArmEnableBranchPrediction ();

  // If MPCore then Enable the SCU
  if (ArmIsMpCore()) {
    // Turn on SMP coherency
    ArmSetAuxCrBit (A5_FEATURE_SMP);
  }

}


VOID
ArmCpuSetupSmpNonSecure (
  IN  UINTN         MpId
  )
{
}
