/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __OMAP4430_H__
#define __OMAP4430_H__

#include "Omap4430Gpio.h"
#include "Omap4430Interrupt.h"
#include "Omap4430Prcm.h"
#include "Omap4430Timer.h"
#include "Omap4430Uart.h"
#include "Omap4430Usb.h"
#include "Omap4430MMCHS.h"
#include "Omap4430I2c.h"
#include "Omap4430PadConfiguration.h"
#include "Omap4430Gpmc.h"
#include "Omap4430Dma.h"


//CONTROL_PBIAS_LITE
#define CONTROL_PBIAS_LITE    0x4a100600
#define PBIASVMODE3V          BIT21
#define PBIASLITEPWRDNZ       BIT22
#define PBIASVMODEERR         BIT23
#define PBIASHIZ              BIT25
#define PBIASPWRDNZ           BIT26

#endif // __OMAP4430_H__

