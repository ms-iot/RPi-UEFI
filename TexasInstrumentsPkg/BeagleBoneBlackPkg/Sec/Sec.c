/** @file
*  Main file supporting the SEC Phase on ARM Platforms
*
*  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
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

#include <Library/ArmTrustedMonitorLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SerialPortLib.h>
#include <Library/ArmGicLib.h>

#include "SecInternal.h"

#define SerialPrint(txt)  SerialPortWrite ((UINT8*)txt, AsciiStrLen(txt)+1);

VOID
CEntryPoint (
  IN UINTN MpId,
  IN UINTN SecBootMode
  )
{
  //CHAR8           Buffer[100];
  //UINTN           CharCount;
  UINTN           JumpAddress;

  // CPU specific settings
  ArmCpuSetup (MpId);

  // Enable Floating Point Coprocessor if supported by the platform
  if (FixedPcdGet32 (PcdVFPEnabled)) {
    ArmEnableVFP();
  }

  // With Trustzone support the transition from Sec to Normal world is done by return_from_exception().
  // If we want to keep this function call we need to ensure the SVC's SPSR point to the same Program
  // Status Register as the the current one (CPSR).
  copy_cpsr_into_spsr ();

  // Call the Platform specific function to execute additional actions if required
  JumpAddress = FixedPcdGet32 (PcdFvBaseAddress);

  //ArmPlatformSecExtraAction (MpId, &JumpAddress);
  NonTrustedWorldTransition (MpId, JumpAddress);

  ASSERT (0); // never return
}

/*
VOID
TrustedWorldInitialization (
  IN  UINTN                     MpId,
  IN  UINTN                     SecBootMode
  )
{
  //UINTN   JumpAddress;

  //-------------------- Monitor Mode ---------------------

  // Set up Monitor World (Vector Table, etc)
  ArmSecureMonitorWorldInitialize ();

  // Transfer the interrupt to Non-secure World
  ArmGicSetupNonSecure (MpId, PcdGet32(PcdGicDistributorBase), PcdGet32(PcdGicInterruptInterfaceBase));

  // Initialize platform specific security policy
  ArmPlatformSecTrustzoneInit (MpId);

  // Setup the Trustzone Chipsets
  if (SecBootMode == ARM_SEC_COLD_BOOT) {
    if (ArmPlatformIsPrimaryCore (MpId)) {
      if (ArmIsMpCore()) {
        // Signal the secondary core the Security settings is done (event: EVENT_SECURE_INIT)
        ArmCallSEV ();
      }
    } else {
      // The secondary cores need to wait until the Trustzone chipsets configuration is done
      // before switching to Non Secure World

      // Wait for the Primary Core to finish the initialization of the Secure World (event: EVENT_SECURE_INIT)
      ArmCallWFE ();
    }
  }

  // Call the Platform specific function to execute additional actions if required
  //JumpAddress = PcdGet32 (PcdFvBaseAddress);
  //ArmPlatformSecExtraAction (MpId, &JumpAddress);

  // Initialize architecture specific security policy
  ArmSecArchTrustzoneInit ();

  // CP15 Secure Configuration Register
  ArmWriteScr (PcdGet32 (PcdArmScr));

  //NonTrustedWorldTransition (MpId, JumpAddress);
}
*/
VOID
NonTrustedWorldTransition (
  IN  UINTN                     MpId,
  IN  UINTN                     JumpAddress
  )
{
  // If PcdArmNonSecModeTransition is defined then set this specific mode to CPSR before the transition
  // By not set, the mode for Non Secure World is SVC
  if (PcdGet32 (PcdArmNonSecModeTransition) != 0) {
    set_non_secure_mode ((ARM_PROCESSOR_MODE)PcdGet32 (PcdArmNonSecModeTransition));
  }

  return_from_exception (JumpAddress);
  //-------------------- Non Secure Mode ---------------------

  // PEI Core should always load and never return
  ASSERT (FALSE);
}