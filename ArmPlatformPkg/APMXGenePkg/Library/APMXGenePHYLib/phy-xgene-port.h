/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#ifndef __PHY_XGENE_PORT_H__
#define __PHY_XGENE_PORT_H__

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>

/* Porting wrapper */
typedef UINT32 u32;
typedef UINT64 u64;
typedef UINT16 u16;
typedef UINT8  u8;
#define uint32_t u32

#define readl(x)		*((volatile u32 *) (x))
#define writel(v, x)		*((volatile u32 *) (x)) = (v)
#define __iomem
#define __weak
#define ENODEV			19
#define dev_err(d, arg...)	DEBUG((EFI_D_ERROR,## arg))
#define dev_dbg(d, arg...)	DEBUG((EFI_D_BLKIO,## arg))
#define printf(arg...)		DEBUG((EFI_D_BLKIO,## arg))
#define dev_warn(d, arg...)	DEBUG((EFI_D_INFO,## arg))
#define pr_err(arg...)		DEBUG((EFI_D_ERROR,## arg))
#define pr_debug(arg...)	DEBUG((EFI_D_BLKIO,## arg))
#define usleep_range(x, y)	MicroSecondDelay((x))
#define mdelay(x)		MicroSecondDelay((x*1000))
#define udelay(x)		MicroSecondDelay((x))
#define preB0Chip		xgene_is_preB0()
#define preA3Chip		xgene_is_preA3()
#define jiffies			0
#define HZ			0
#define ARRAY_SIZE(x)		sizeof(x)/sizeof(x[0])
#define strcmp			AsciiStrCmp

static inline int time_before(unsigned long t1, unsigned long t2)
{
	return t1 <= t2 ? 1 : 0;
}

int xgene_is_preA3(void);
int xgene_is_preB0(void);

#endif
