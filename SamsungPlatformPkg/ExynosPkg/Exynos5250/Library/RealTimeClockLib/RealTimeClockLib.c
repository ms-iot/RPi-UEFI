/** @file
  Implement EFI RealTimeClock runtime services via RTC Lib.
  
  Currently this driver does not support runtime virtual calling.

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/RealTimeClockLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/RealTimeClock.h>
#include <Guid/GlobalVariable.h>


/*
 * Kimoon added on 2011.12.08
 */
#include <Library/PcdLib.h>
#include <Platform/ArmPlatform.h>

#define RTC_YEAR_DATUM 2000

unsigned bcd2bin(unsigned char val)
{
  return (val & 0x0f) + (val >> 4) * 10;
}

unsigned char bin2bcd(unsigned val)
{
  return ((val / 10) << 4) + val % 10;
}

/**
  Returns the current time and date information, and the time-keeping capabilities
  of the hardware platform.

  @param  Time                  A pointer to storage to receive a snapshot of the current time.
  @param  Capabilities          An optional pointer to a buffer to receive the real time clock
                                device's capabilities.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_INVALID_PARAMETER Time is NULL.
  @retval EFI_DEVICE_ERROR      The time could not be retrieved due to hardware error.

**/
EFI_STATUS
EFIAPI
LibGetTime (
  OUT EFI_TIME                *Time,
  OUT  EFI_TIME_CAPABILITIES  *Capabilities
  )
{
  /*
   * Kimoon added on 2011.12.08
   */
  UINT32 RtcBaseAddr;
  BOOLEAN Retried = FALSE;

  DEBUG((EFI_D_INFO, "++%a:%d\n", __func__, __LINE__));

  /*
   * Check set time
   */
  if (Time == NULL)
	goto cleanUp;

  /*
   * 1. Get RTC base address
   */
  RtcBaseAddr = PcdGet32(PcdRtcBase);

  /*
   * 2. Read registers
   */
RetryGetTime:
  Time->Minute = MmioRead32(RtcBaseAddr + EXYNOS_BCDMIN);
  Time->Hour = MmioRead32(RtcBaseAddr + EXYNOS_BCDHOUR);
  Time->Day = MmioRead32(RtcBaseAddr + EXYNOS_BCDDAY);
  Time->Month = MmioRead32(RtcBaseAddr + EXYNOS_BCDMON);
  Time->Year = MmioRead32(RtcBaseAddr + EXYNOS_BCDYEAR);
  Time->Second = MmioRead32(RtcBaseAddr + EXYNOS_BCDSEC);

  /*
   * 3. if second value is 0, try to read registers to escape errors.
   */
  if (Time->Second == 0 && !Retried) {
	Retried = TRUE;
	goto RetryGetTime;
  }

  /*
   * 4. Change BCD values to real values.
   */
  Time->Second = bcd2bin(Time->Second);
  Time->Minute = bcd2bin(Time->Minute);
  Time->Hour = bcd2bin(Time->Hour);
  Time->Day = bcd2bin(Time->Day);
  Time->Month = bcd2bin(Time->Month);
  Time->Year = bcd2bin(Time->Year) + RTC_YEAR_DATUM;

  // Update the Capabilities info
  if (Capabilities != NULL) {
    // PL031 runs at frequency 1Hz
    Capabilities->Resolution  = 1;
    // Accuracy in ppm multiplied by 1,000,000, e.g. for 50ppm set 50,000,000
    Capabilities->Accuracy    = 1000000;
    // FALSE: Setting the time does not clear the values below the resolution level
    Capabilities->SetsToZero  = FALSE;
  }


  DEBUG((EFI_D_INFO, "--%a:%d (%d/%d/%d %d:%d:%d)\n",
	                __func__, __LINE__,
	                Time->Year, Time->Month, Time->Day, Time->Hour, Time->Minute, Time->Second));
  return EFI_SUCCESS;

cleanUp:
  DEBUG((EFI_D_ERROR, "ERROR: %a:%d\n", __func__, __LINE__));
  return EFI_DEVICE_ERROR;

}


/**
  Sets the current local time and date information.

  @param  Time                  A pointer to the current time.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_INVALID_PARAMETER A time field is out of range.
  @retval EFI_DEVICE_ERROR      The time could not be set due due to hardware error.

**/
EFI_STATUS
EFIAPI
LibSetTime (
  IN EFI_TIME                *Time
  )
{
  /*
   * Kimoon added on 2011.12.08
   */
  UINT32 RtcBaseAddr;

  DEBUG((EFI_D_ERROR, "++%a:%d (%d/%d/%d %d:%d:%d)\n", 
	                __func__, __LINE__,
	                Time->Year, Time->Month, Time->Day, Time->Hour, Time->Minute, Time->Second));

  /*
   * Check set time
   */
  if (Time == NULL)
	goto cleanUp;

  /*
   * The RTC will only support a BCD year value of 0 - 99.  The year datum is
   * 2000, so any dates greater than 2099 will fail unless the datum is
   * adjusted.
   */
  if ((Time->Year < RTC_YEAR_DATUM) || (Time->Year - RTC_YEAR_DATUM > 99)) {
	DEBUG((EFI_D_ERROR, "RTC cannot support a year greater than %d or less than %d (value %d)\n",
		                (RTC_YEAR_DATUM + 99), RTC_YEAR_DATUM, Time->Year));
    goto cleanUp;
  }

  /*
   * 1. Get RTC base address
   */
  RtcBaseAddr = PcdGet32(PcdRtcBase);

  /*
   * 2. Set EXYNOS_RTCCON_RTCEN to Set BCD registers
   *    &= ~EXYNOS_RTCCON_RTCEN
   *    |= EXYNOS_RTCCON_RTCEN
   */
  MmioAndThenOr32(RtcBaseAddr + EXYNOS_RTCCON,	\
			~EXYNOS_RTCCON_RTCEN, EXYNOS_RTCCON_RTCEN);

  /*
   * 3. Set BCD registers
   */
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDSEC, bin2bcd(Time->Second));
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDMIN, bin2bcd(Time->Minute));
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDHOUR, bin2bcd(Time->Hour));
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDDAY, bin2bcd(Time->Day));
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDMON, bin2bcd(Time->Month));
  MmioWrite32(RtcBaseAddr + EXYNOS_BCDYEAR, bin2bcd(Time->Year - RTC_YEAR_DATUM));

  /*
   * 4. Clear EXYNOS_RTCCON_RTCEN to close setting BCD registers
   *    &= ~EXYNOS_RTCCON_RTCEN
   */
  MmioAndThenOr32(RtcBaseAddr + EXYNOS_RTCCON,	\
			~EXYNOS_RTCCON_RTCEN, (0<<0));

  DEBUG((EFI_D_ERROR, "--%a:%d\n", __func__, __LINE__));
  return EFI_SUCCESS;

cleanUp:
  DEBUG((EFI_D_ERROR, "ERROR: %a:%d\n", __func__, __LINE__));
  return EFI_DEVICE_ERROR;

}


/**
  Returns the current wakeup alarm clock setting.

  @param  Enabled               Indicates if the alarm is currently enabled or disabled.
  @param  Pending               Indicates if the alarm signal is pending and requires acknowledgement.
  @param  Time                  The current alarm setting.

  @retval EFI_SUCCESS           The alarm settings were returned.
  @retval EFI_INVALID_PARAMETER Any parameter is NULL.
  @retval EFI_DEVICE_ERROR      The wakeup time could not be retrieved due to a hardware error.

**/
EFI_STATUS
EFIAPI
LibGetWakeupTime (
  OUT BOOLEAN     *Enabled,
  OUT BOOLEAN     *Pending,
  OUT EFI_TIME    *Time
  )
{
  // Not a required feature
  return EFI_UNSUPPORTED;
}


/**
  Sets the system wakeup alarm clock time.

  @param  Enabled               Enable or disable the wakeup alarm.
  @param  Time                  If Enable is TRUE, the time to set the wakeup alarm for.

  @retval EFI_SUCCESS           If Enable is TRUE, then the wakeup alarm was enabled. If
                                Enable is FALSE, then the wakeup alarm was disabled.
  @retval EFI_INVALID_PARAMETER A time field is out of range.
  @retval EFI_DEVICE_ERROR      The wakeup time could not be set due to a hardware error.
  @retval EFI_UNSUPPORTED       A wakeup timer is not supported on this platform.

**/
EFI_STATUS
EFIAPI
LibSetWakeupTime (
  IN BOOLEAN      Enabled,
  OUT EFI_TIME    *Time
  )
{
  // Not a required feature
  return EFI_UNSUPPORTED;
}



/**
  This is the declaration of an EFI image entry point. This can be the entry point to an application
  written to this specification, an EFI boot service driver, or an EFI runtime driver.

  @param  ImageHandle           Handle that identifies the loaded image.
  @param  SystemTable           System Table for this image.

  @retval EFI_SUCCESS           The operation completed successfully.

**/
EFI_STATUS
EFIAPI
LibRtcInitialize (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_HANDLE    Handle;
  EFI_TIME      Time;

  /*
   * Kimoon added on 2011.12.08
   */
  DEBUG((EFI_D_INFO, "++%a:%d\n", __func__, __LINE__));

  /*
   * Mask RTC gating (bit clear)
   */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_PERIR),	\
			~CLK_RTC_OFFSET, CLK_RTC_MASK);

  /*
   * Unmask RTC gating (bit set)
   */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_PERIR),	\
			~CLK_RTC_OFFSET, CLK_RTC_UNMASK);


  // Setup the setters and getters
  gRT->GetTime       = LibGetTime;
  gRT->SetTime       = LibSetTime;
  gRT->GetWakeupTime = LibGetWakeupTime;
  gRT->SetWakeupTime = LibSetWakeupTime;

  Time.Second = 0;
  Time.Minute = 0;
  Time.Hour   = 9;
  Time.Day    = 15;
  Time.Month  = 3;
  Time.Year   = 2012;

  LibSetTime(&Time);

  // Install the protocol
  Handle = NULL;
  gBS->InstallMultipleProtocolInterfaces (
                 &Handle,
                 &gEfiRealTimeClockArchProtocolGuid,  NULL,
                 NULL
                );

  DEBUG((EFI_D_INFO, "--%a:%d\n", __func__, __LINE__));
  return EFI_SUCCESS;
}


/**
  Fixup internal data so that EFI can be call in virtual mode.
  Call the passed in Child Notify event and convert any pointers in
  lib to virtual mode.

  @param[in]    Event   The Event that is being processed
  @param[in]    Context Event Context
**/
VOID
EFIAPI
LibRtcVirtualNotifyEvent (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  //
  // Only needed if you are going to support the OS calling RTC functions in virtual mode.
  // You will need to call EfiConvertPointer (). To convert any stored physical addresses 
  // to virtual address. After the OS transistions to calling in virtual mode, all future
  // runtime calls will be made in virtual mode.
  //
  return;
}



