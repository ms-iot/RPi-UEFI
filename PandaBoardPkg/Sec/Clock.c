/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Omap4430/Omap4430.h>
#include <Omap4430/Omap4430Rom.h>

VOID
ClockInit (
  VOID
  )
{
  // TODO: clocks configuration code clean up

  // CORE, PER DPLLs are configured part of Configuration header which OMAP4 ROM parses.

  // Turn on functional & interface clocks to MMC1 and I2C1 modules.
  MmioOr32(0x4a009328, 0x03070002);

  //Enable DMTIMER3 with SYS_CLK source
  MmioOr32(0x4A009440, 0x2);

  //Enable DMTIMER4 with SYS_CLK source
  MmioOr32(0x4A009448, 0x2);

  // Enable UART3 clocks
  RomEnableClocks (2, 2);

  // Enable watchdog interface clocks
  RomEnableClocks (6, 1);

}
