/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __OMAP4430USB_H__
#define __OMAP4430USB_H__

#define USB_BASE            (0x4A060000)

#define UHH_SYSCONFIG       (USB_BASE + 0x4010)
#define UHH_HOSTCONFIG      (USB_BASE + 0x4040)
#define UHH_SYSSTATUS       (USB_BASE + 0x4014)

#define USB_EHCI_HCCAPBASE  (USB_BASE + 0x4C00)

#define UHH_SYSCONFIG_STANDBYMODE_NO_STANDBY  BIT4
#define UHH_SYSCONFIG_IDLEMODE_NO_IDLE        BIT2
#define UHH_SYSCONFIG_SOFTRESET               BIT0

#define UHH_HOSTCONFIG_P2_CONNECT_STATUS_DISCONNECT (0UL <<  9)
#define UHH_HOSTCONFIG_P1_CONNECT_STATUS_DISCONNECT (0UL <<  8)
#define UHH_HOSTCONFIG_ENA_INCR_ALIGN_DISABLE       (0UL <<  5)
#define UHH_HOSTCONFIG_ENA_INCR16_ENABLE            BIT4
#define UHH_HOSTCONFIG_ENA_INCR8_ENABLE             BIT3
#define UHH_HOSTCONFIG_ENA_INCR4_ENABLE             BIT2
#define UHH_HOSTCONFIG_AUTOPPD_ON_OVERCUR_EN_ON     (0UL <<  1)
#define UHH_HOSTCONFIG_P1_ULPI_BYPASS_ULPI_MODE     (0UL <<  16)

#define UHH_SYSSTATUS_RESETDONE                (BIT1 | BIT2)

#endif // __OMAP4430USB_H__
