/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __TWL6030_H__
#define __TWL6030_H__

#define EXTERNAL_DEVICE_REGISTER_TO_SLAVE_ADDRESS(x)     (((x) >> 8) & 0xFF)
#define EXTERNAL_DEVICE_REGISTER_TO_REGISTER(x)          ((x) & 0xFF)
#define EXTERNAL_DEVICE_REGISTER(SlaveAddress, Register) (((SlaveAddress) & 0xFF) << 8 | ((Register) & 0xFF))

// I2C Address group
#define I2C_ADDR_GRP_ID1      0x48
#define I2C_ADDR_GRP_ID2      0x49
#define I2C_ADDR_GRP_ID3      0x4A
#define I2C_ADDR_GRP_ID4      0x4B
#define I2C_ADDR_GRP_ID5      0x12

// MMC definitions.
#define VMMC_CFG_GRP          0x98
#define DEV_GRP_APP           BIT0

#define VMMC_CFG_STATE        0x9A
#define VMMC_CFG_STATE_OFF    0xE0
#define VMMC_CFG_STATE_ON     0xE1

#define VMMC_CFG_VOLTAGE      0x9B
#define VSEL_3_00V            0x15

#define MMCCTRL               0xEE
#define CARD_DET_STS_MMC      BIT0
#define CARD_DET_CFG          BIT3

// LEDEN register
#define LEDEN                 0xEE
#define LEDAON                BIT0
#define LEDBON                BIT1
#define LEDAPWM               BIT4
#define LEDBPWM               BIT5

// RTC registers
#define SECONDS_REG           0x1C
#define MINUTES_REG           0x1D
#define HOURS_REG             0x1E
#define DAYS_REG              0x1F
#define MONTHS_REG            0x20
#define YEARS_REG             0x21
#define WEEKS_REG             0x22
#define RTC_CTRL_REG          0x29

// USB PHY power
#define VAUX2_DEDICATED       0x79
#define VAUX2_DEV_GRP         0x76

#define VAUX_DEV_GRP_NONE     0x00
#define VAUX_DEV_GRP_P1       0x20
#define VAUX_DEV_GRP_P2       0x40
#define VAUX_DEV_GRP_P3       0x80
#define VAUX_DEDICATED_18V    0x05

// Display subsystem
#define VPLL2_DEDICATED       0x91
#define VPLL2_DEV_GRP         0x8E

#define GPIODATADIR1          0x9B
#define SETGPIODATAOUT1       0xA4

#endif //__TWL6030_H__
