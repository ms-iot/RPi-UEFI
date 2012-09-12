/** @file

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>

#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Platform/ArmPlatform.h>
#include <Library/ExynosTimerLib.h>


// Setup SP810's Timer2 for managing delay functions. And Timer3 for Performance counter
// Note: ArmVE's Timer0 and Timer1 are used by TimerDxe.
RETURN_STATUS
EFIAPI
TimerConstructor (
  VOID
  )
{
  UINT32	PWMTimerBase;
  UINT32	rwVal;

  PWMTimerBase = PcdGet32(PcdPWMTimerBase);

/**
  This function is for initializing for PWM Timer
  Timer 2 = > Delay Counter
  Timer 3 = > Performance Counter
**/
// PWM Input Clock(ACLK_100) is 100 Mhz so We need to prescale about 1Mhz to make udelay function
	rwVal = MmioRead32 (PWMTimerBase + PWM_TCFG0_OFFSET);
	rwVal &= ~(0xFF << PRESCALE_GRP1_START_POS);
	rwVal |= (PRESCALE_TIMER_GRP1 << PRESCALE_GRP1_START_POS);
	MmioWrite32 ((PWMTimerBase + PWM_TCFG0_OFFSET), rwVal);
	MmioWrite32 ((PWMTimerBase + PWM_TCFG1_OFFSET), 0x0);

// PWM Timer INT disable
	rwVal = MmioRead32 (PWMTimerBase + PWM_TINT_CSTAT_OFFSET);
	MmioWrite32 ((PWMTimerBase + PWM_TINT_CSTAT_OFFSET), rwVal & ~(TIMER_INTR_MASK(TIMER_2) | TIMER_INTR_MASK(TIMER_3)));

// PWM Timer 2,3 make to stop
	rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
	MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & (STOP_TIMER_VAL(TIMER_2) | STOP_TIMER_VAL(TIMER_3)));

// PWM Timer 3 used by Free running counter with Auto re-load mode
	MmioWrite32 ((PWMTimerBase + PWM_TCNTB3_OFFSET), MAX_COUNT_VAL);
// Set and Clear PWM Manually update for Timer 3
	rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
	MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | UPDATE_COUNT_BUF_MASK(TIMER_3));
	MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & ~UPDATE_COUNT_BUF_MASK(TIMER_3));
// Set Auto re-load and start Timer
	MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | RELOAD_AND_START(TIMER_3));

	DEBUG ((EFI_D_ERROR, "Timer 2,3 Enabled\n"));

    return RETURN_SUCCESS;
}

/**
  Stalls the CPU for at least the given number of microseconds.

  Stalls the CPU for the number of microseconds specified by MicroSeconds.

  @param  MicroSeconds  The minimum number of microseconds to delay.

  @return The value of MicroSeconds inputted.

**/
UINTN
EFIAPI
MicroSecondDelay (
  IN  UINTN MicroSeconds
  )
{
  UINT32 rwVal;
  UINT32	PWMTimerBase;

  PWMTimerBase=PcdGet32(PcdPWMTimerBase);
  // load the timer count register
  MmioWrite32 ((PWMTimerBase + PWM_TCNTB2_OFFSET), MicroSeconds);


// PWM Timer 2 stop
  rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & STOP_TIMER_VAL(TIMER_2));

// Set and Clear PWM Manually update for Timer 2
  rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | UPDATE_COUNT_BUF_MASK(TIMER_2));
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & ~UPDATE_COUNT_BUF_MASK(TIMER_2));
  //Start Timer 2
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | START_TIMER(TIMER_2));
  //Wait for requested delay time
  while (MmioRead32 (PWMTimerBase + PWM_TCNTO2_OFFSET) > 0) {
    ;
  }

  return MicroSeconds;
}

/**
  Stalls the CPU for at least the given number of nanoseconds.

  Stalls the CPU for the number of nanoseconds specified by NanoSeconds.

  @param  NanoSeconds The minimum number of nanoseconds to delay.

  @return The value of NanoSeconds inputted.

**/
UINTN
EFIAPI
NanoSecondDelay (
  IN  UINTN NanoSeconds
  )
{
  UINT32 MicroSeconds;
  UINT32 rwVal;
  UINT32	PWMTimerBase;

  PWMTimerBase=PcdGet32(PcdPWMTimerBase);

  // Round up to 1us Tick Number
  MicroSeconds =   (UINT32)NanoSeconds / 1000;
  MicroSeconds += ((UINT32)NanoSeconds % 1000) == 0 ? 0 : 1;
  // load the timer count register
  MmioWrite32 ((PWMTimerBase + PWM_TCNTB2_OFFSET), MicroSeconds);

// PWM Timer 2 stop
  rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & STOP_TIMER_VAL(TIMER_2));
// Set and Clear PWM Manually update for Timer 2
  rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | UPDATE_COUNT_BUF_MASK(TIMER_2));
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal & ~UPDATE_COUNT_BUF_MASK(TIMER_2));
  //Start Timer 2
  rwVal = MmioRead32 (PWMTimerBase + PWM_TCON_OFFSET);
  MmioWrite32 ((PWMTimerBase + PWM_TCON_OFFSET), rwVal | START_TIMER(TIMER_2));

  //Wait for requested delay time
  while (MmioRead32 (PWMTimerBase + PWM_TCNTO0_OFFSET) > 0) {
    ;
  }

  return NanoSeconds;
}

/**
  Retrieves the current value of a 64-bit free running performance counter.

  The counter can either count up by 1 or count down by 1. If the physical
  performance counter counts by a larger increment, then the counter values
  must be translated. The properties of the counter can be retrieved from
  GetPerformanceCounterProperties().

  @return The current value of the free running performance counter.

**/
UINT64
EFIAPI
GetPerformanceCounter (
  VOID
  )
{
  UINT32	PWMTimerBase;

  PWMTimerBase=PcdGet32(PcdPWMTimerBase);
  // Free running 64-bit/32-bit counter is needed here.
  // Don't think we need this to boot, just to do performance profile
  // ASSERT (FALSE);
  UINT32 val = MmioRead32 (PWMTimerBase + PWM_TCNTO3_OFFSET);

  ASSERT(val > 0);

  return (UINT64)val;
}


/**
  Retrieves the 64-bit frequency in Hz and the range of performance counter
  values.

  If StartValue is not NULL, then the value that the performance counter starts
  with immediately after is it rolls over is returned in StartValue. If
  EndValue is not NULL, then the value that the performance counter end with
  immediately before it rolls over is returned in EndValue. The 64-bit
  frequency of the performance counter in Hz is always returned. If StartValue
  is less than EndValue, then the performance counter counts up. If StartValue
  is greater than EndValue, then the performance counter counts down. For
  example, a 64-bit free running counter that counts up would have a StartValue
  of 0 and an EndValue of 0xFFFFFFFFFFFFFFFF. A 24-bit free running counter
  that counts down would have a StartValue of 0xFFFFFF and an EndValue of 0.

  @param  StartValue  The value the performance counter starts with when it
                      rolls over.
  @param  EndValue    The value that the performance counter ends with before
                      it rolls over.

  @return The frequency in Hz.

**/
UINT64
EFIAPI
GetPerformanceCounterProperties (
  OUT UINT64  *StartValue,  OPTIONAL
  OUT UINT64  *EndValue     OPTIONAL
  )
{
  if (StartValue != NULL) {
    // Timer starts with the reload value
    *StartValue = (UINT64)0ULL;
  }

  if (EndValue != NULL) {
    // Timer counts up to 0xFFFFFFFF
    *EndValue = 0xFFFFFFFF;
  }

  return 1000000;
}
