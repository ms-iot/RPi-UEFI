/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Omap4430/Omap4430.h>
#include <Omap4430/Omap4430Rom.h>

VOID
PadConfiguration (
  VOID
  )
{
  // TODO: pad configuration

  // Configure UART3 pads
  RomCtrlConfigurePads (2, 2);

}
