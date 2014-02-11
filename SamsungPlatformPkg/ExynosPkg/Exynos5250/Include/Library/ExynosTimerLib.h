/** @file
*
*  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.
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


#ifndef _EXYNOSTIMERLIB_H__
#define _EXYNOSTIMERLIB_H__

#define PWM_TCFG0_OFFSET		(0x0000)
#define PWM_TCFG1_OFFSET		(0x0004)
#define PWM_TCON_OFFSET			(0x0008)
#define PWM_TCNTB0_OFFSET		(0x000C)
#define PWM_TCMPB0_OFFSET		(0x0010)
#define PWM_TCNTO0_OFFSET		(0x0014)
#define PWM_TCNTB1_OFFSET		(0x0018)
#define PWM_TCMPB1_OFFSET		(0x001C)
#define PWM_TCNTO1_OFFSET		(0x0020)
#define PWM_TCNTB2_OFFSET		(0x0024)
#define PWM_TCMPB2_OFFSET		(0x0028)
#define PWM_TCNTO2_OFFSET		(0x002C)
#define PWM_TCNTB3_OFFSET		(0x0030)
#define PWM_TCMPB3_OFFSET		(0x0034)
#define PWM_TCNTO3_OFFSET		(0x0038)
#define PWM_TINT_CSTAT_OFFSET		(0x0044)

// Exynos4210 Timer constants
#define Exynos4210_TIMER_LOAD_REG          0x00
#define Exynos4210_TIMER_CURRENT_REG       0x04
#define Exynos4210_TIMER_CONTROL_REG       0x08
#define Exynos4210_TIMER_INT_CLR_REG       0x0C
#define Exynos4210_TIMER_RAW_INT_STS_REG   0x10
#define Exynos4210_TIMER_MSK_INT_STS_REG   0x14
#define Exynos4210_TIMER_BG_LOAD_REG       0x18

// Timer control register bit definitions
#define Exynos4210_TIMER_CTRL_ONESHOT        BIT0
#define Exynos4210_TIMER_CTRL_32BIT          BIT1
#define Exynos4210_TIMER_CTRL_PRESCALE_MASK  (BIT3|BIT2)
#define Exynos4210_PRESCALE_DIV_1            0
#define Exynos4210_PRESCALE_DIV_16           BIT2
#define Exynos4210_PRESCALE_DIV_256          BIT3
#define Exynos4210_TIMER_CTRL_INT_ENABLE     BIT5
#define Exynos4210_TIMER_CTRL_PERIODIC       BIT6
#define Exynos4210_TIMER_CTRL_ENABLE         BIT7

#endif
