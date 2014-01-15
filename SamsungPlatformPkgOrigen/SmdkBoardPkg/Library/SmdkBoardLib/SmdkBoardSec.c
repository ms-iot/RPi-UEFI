/** @file
*
*  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.
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

#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Drivers/PL310L2Cache.h>
#include <Drivers/PL341Dmc.h>


/**
  Initialize controllers that must setup at the early stage

  Some peripherals must be initialized in Secure World.
  For example, some L2x0 requires to be initialized in Secure World
 ============ added by girish to resolve compile error=================
**/

VOID
ArmPlatformSecInitialize (
  VOID
  ) {
  // The L2x0 controller must be intialize in Secure World
	L2x0CacheInit(PcdGet32(PcdL2x0ControllerBase),
      PL310_TAG_LATENCIES(L2x0_LATENCY_8_CYCLES,L2x0_LATENCY_8_CYCLES,L2x0_LATENCY_8_CYCLES),
      PL310_DATA_LATENCIES(L2x0_LATENCY_8_CYCLES,L2x0_LATENCY_8_CYCLES,L2x0_LATENCY_8_CYCLES),
      0,~0, // Use default setting for the Auxiliary Control Register
      FALSE);

}

/**
  Initialize the Secure peripherals and memory regions

  If Trustzone is supported by your platform then this function makes the required initialization
  of the secure peripherals and memory regions.

**/
VOID
ArmPlatformSecTrustzoneInit (
  IN  UINTN                     MpId
  )
{
return;
}
