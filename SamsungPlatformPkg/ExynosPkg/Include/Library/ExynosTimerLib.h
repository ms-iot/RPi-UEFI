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


#ifndef _EXYNOSTIMERLIB_H__
#define _EXYNOSTIMERLIB_H__

typedef enum{
  TIMER_0,
  TIMER_1,
  TIMER_2,
  TIMER_3,
  TIMER_4,
}PWM_TIMERS;

#define NUM_OF_TIMERS			(0x05)
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
#define PWM_TCNTB4_OFFSET		(0x003C)
#define PWM_TCNTO4_OFFSET		(0x0040)
#define PWM_TINT_CSTAT_OFFSET		(0x0044)

#define TIMER_STATUS_MASK(timer_no)		(1 << (NUM_OF_TIMERS + timer_no))
#define TIMER_INTR_MASK(timer_no)		(1 << (timer_no))
#define STOP_TIMER_VAL(timer_no)		 ~(0x0f << (((timer_no + 1)*(!!timer_no)) << 2))
#define UPDATE_COUNT_BUF_MASK(timer_no)	(2 << (((timer_no + 1)*(!!timer_no)) << 2))
#define RELOAD_AND_START(timer_no)		((AUTO_RELOAD | START_TIMERPOS) << (((timer_no + 1)*(!!timer_no)) << 2))
#define START_TIMER(timer_no)			(START_TIMERPOS << (((timer_no + 1)*(!!timer_no)) << 2))


#define PRESCALE_GRP0_START_POS		(0x00)
#define PRESCALE_TIMER_GRP0			(0x63)
#define PRESCALE_GRP1_START_POS		(0x08)
#define PRESCALE_TIMER_GRP1			(0x63)
#define MAX_COUNT_VAL				(0xFFFFFFFF)
#define AUTO_RELOAD					(0x8)
#define START_TIMERPOS				(0x1)



#endif
