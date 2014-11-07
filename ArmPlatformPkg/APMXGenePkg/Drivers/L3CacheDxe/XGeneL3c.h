/**
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * Author: Tuan Phan <tphan@apm.com>
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

#if !defined(__XGENEL3C_H__)
#define __XGENEL3C_H__

#define RB_MASTER_REG_BASE      0x7E000000
#define CSW_REG_BASE            0x7E200000
#define L3C_REG_BASE            0x7E600000

#define RB_RBASR                (0x004)

#define CSW_CSWSER              (0x008)
#define CSW_L3RCR               (0x300)
#define CSW_L3CCR               (0x308)

#define L3C_CR                  (0x00 * 4)
#define L3C_SIDR                (0x01 * 4)
#define L3C_SCRUB               (0x02 * 4)
#define L3C_DSTHR               (0x03 * 4)
#define L3C_OPCR                (0x04 * 4)
#define L3C_OPAR                (0x05 * 4)
#define L3C_OPTR0               (0x06 * 4)
#define L3C_OPTR1               (0x07 * 4)
#define L3C_OPDECCR0            (0x08 * 4)
#define L3C_OPDECCR1            (0x09 * 4)
#define L3C_ESR                 (0x0A * 4)
#define L3C_ECR                 (0x0B * 4)
#define L3C_ELR                 (0x0C * 4)
#define L3C_AELR                (0x0D * 4)
#define L3C_BELR                (0x0E * 4)
#define L3C_OPDR00              (0x10 * 4)
#define L3C_OPDR01              (0x11 * 4)
#define L3C_OPDR02              (0x12 * 4)
#define L3C_OPDR03              (0x13 * 4)
#define L3C_OPDR04              (0x14 * 4)
#define L3C_OPDR05              (0x15 * 4)
#define L3C_OPDR06              (0x16 * 4)
#define L3C_OPDR07              (0x17 * 4)
#define L3C_OPDR08              (0x18 * 4)
#define L3C_OPDR09              (0x19 * 4)
#define L3C_OPDR10              (0x1a * 4)
#define L3C_OPDR11              (0x1b * 4)
#define L3C_OPDR12              (0x1c * 4)
#define L3C_OPDR13              (0x1d * 4)
#define L3C_OPDR14              (0x1e * 4)
#define L3C_OPDR15              (0x1f * 4)
#define L3C_ID                  (0x20 * 4)
#define L3C_DBGCR               (0x21 * 4)
#define L3C_DBGAR               (0x22 * 4)
#define L3C_DBGDR               (0x23 * 4)
#define L3C_RMR                 (0x2A * 4)
#define L3C_TEMP                (0x2B * 4)
#define L3C_PER0                (0x30 * 4)
#define L3C_PER1                (0x30 * 4)
#define L3C_PER2                (0x30 * 4)
#define L3C_PER3                (0x30 * 4)
#define L3C_DBGBRKPS00          (0x40 * 4)
#define L3C_DBGBRKPS01          (0x41 * 4)
#define L3C_DBGBRKPS02          (0x42 * 4)
#define L3C_DBGBRKPS03          (0x43 * 4)
#define L3C_DBGBRKPS04          (0x44 * 4)
#define L3C_DBGBRKPS05          (0x45 * 4)
#define L3C_DBGBRKPS06          (0x46 * 4)
#define L3C_DBGBRKPS07          (0x47 * 4)
#define L3C_DBGBRKPS08          (0x48 * 4)
#define L3C_DBGBRKPS09          (0x49 * 4)
#define L3C_DBGBRKPS10          (0x4a * 4)
#define L3C_DBGBRKPS11          (0x4b * 4)
#define L3C_DBGBRKPS12          (0x4c * 4)
#define L3C_DBGBRKPS13          (0x4d * 4)
#define L3C_DBGBRKPS14          (0x4e * 4)
#define L3C_DBGBRKPS15          (0x4f * 4)

#endif
