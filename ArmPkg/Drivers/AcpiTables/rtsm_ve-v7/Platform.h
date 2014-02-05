/** @file
  Platform specific defines for constructing ACPI tables

  Copyright (c) 2008, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials are
  licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*
 * Copyright (c) 2013 Linaro Limited
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the BSD License which accompanies
 * this distribution, and is available at
 * http://opensource.org/licenses/bsd-license.php
 *
 * Contributors:
 *     Yi Li - yi.li@linaro.org
*/

#ifndef _Platform_h_INCLUDED_
#define _Platform_h_INCLUDED_

#include <PiDxe.h>
#include <IndustryStandard/Acpi.h>

//
// ACPI table information used to initialize tables.RTSMVEV8
//
#define EFI_ACPI_OEM_ID           'L','I','N','A','R','O'   // OEMID 6 bytes long
#define EFI_ACPI_OEM_TABLE_ID     SIGNATURE_64('R','T','S','M','V','E','V','7' ) // OEM table id 8 bytes long
#define EFI_ACPI_OEM_REVISION     0x00000001
#define EFI_ACPI_CREATOR_ID       SIGNATURE_32('I','N','T','L')
#define EFI_ACPI_CREATOR_REVISION 0x20130517

#define INT_MODEL       0x01
#define SCI_INT_VECTOR  0x0
#define SMI_CMD_IO_PORT 0x0
#define ACPI_ENABLE     0x0
#define ACPI_DISABLE    0x0
#define S4BIOS_REQ      0x00
#define PM1a_EVT_BLK    0x00000001
#define PM1b_EVT_BLK    0x00000000
#define PM1a_CNT_BLK    0x00000001
#define PM1b_CNT_BLK    0x00000000
#define PM2_CNT_BLK     0x00000001
#define PM_TMR_BLK      0x00000001
#define GPE0_BLK        0x00000001
#define GPE1_BLK        0x00000000
#define PM1_EVT_LEN     0x04
#define PM1_CNT_LEN     0x02
#define PM2_CNT_LEN     0x01
#define PM_TM_LEN       0x04
#define GPE0_BLK_LEN    0x08
#define GPE1_BLK_LEN    0x00
#define GPE1_BASE       0x00
#define RESERVED        0x00
#define P_LVL2_LAT      0x0000
#define P_LVL3_LAT      0x0000
#define FLUSH_SIZE      0x0000
#define FLUSH_STRIDE    0x0000
#define DUTY_OFFSET     0x00
#define DUTY_WIDTH      0x00
#define DAY_ALRM        0x00
#define MON_ALRM        0x00
#define CENTURY         0x00
#define FLAG            0x00321033
#endif

