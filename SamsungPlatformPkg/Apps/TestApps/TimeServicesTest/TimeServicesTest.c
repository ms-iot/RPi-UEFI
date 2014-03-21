/** @file TimeServicesTest.c

  Samsung S.LSI TimeServicesTest application

  Copyright (c) 2012-2013, Samsung Electronics Inc. All rights reserved.
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

  DateTime: 2012/01/31
  Author: Jang Young Gun : yg1004.jang@samsung.com

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/31/12   yg.jang Initial revision

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>


/** Various constant values defined for testing.
*/
UINT16 test_year = 2011;
UINT8 test_month = 5;
UINT8 test_day = 1;
UINT8 test_minute = 4;
UINT8 test_hour = 3;
UINT8 test_second = 6;
UINT32 test_nanosecond = 0;
UINT16 test_timezone = 7;
UINT8 test_daylight = 0;

/** We test via stalling a defined amount in the seconds.
*/
#define STALL_AMOUNT_SECONDS 4
#define LOWER_BOUND_SECONDS_TEST STALL_AMOUNT_SECONDS - 1
#define UPPER_BOUND_SECONDS_TEST STALL_AMOUNT_SECONDS + 1

/** Convert seconds into an amount the gBS->Stall function will
    accept.
*/
#define CONVERSION_FACTOR_GBS_STALL 1000000

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
RTCTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_TIME time;
  EFI_TIME_CAPABILITIES time_capabilities;

  BOOLEAN tests_passed = TRUE;

  time.Day = test_day;
  time.Daylight = test_daylight;
  time.Hour = test_hour;
  time.Minute = test_minute;
  time.Month = test_month;
  time.Nanosecond = test_nanosecond;
  time.Second = test_second;
  time.TimeZone = test_timezone;
  time.Year = test_year;


  AsciiPrint("Setting RTC time to a static value\n");
  Status = gRT->SetTime(&time);
  if (Status != EFI_SUCCESS) {
      tests_passed = FALSE;
      AsciiPrint("Fatal error during test\n");
      return Status;
  }
  AsciiPrint("Stalling for %d seconds to test incrementation\n", STALL_AMOUNT_SECONDS);
  Status = gBS->Stall( (STALL_AMOUNT_SECONDS * CONVERSION_FACTOR_GBS_STALL) );
  if (Status != EFI_SUCCESS) {
      tests_passed = FALSE;
	  AsciiPrint("Fatal error during test\n");
      return Status;
  }
  AsciiPrint("Getting RTC Time with capabilities\n");
  Status = gRT->GetTime(&time, &time_capabilities);
  if (Status != EFI_SUCCESS) {
      tests_passed = FALSE;
      AsciiPrint("Fatal error during test\n");
	  return Status;
  }
  AsciiPrint("Getting RTC Time without capabilities\n");
  Status = gRT->GetTime(&time, NULL);
  if (Status != EFI_SUCCESS) {
      tests_passed = FALSE;
      AsciiPrint("Failure during test\n");
      return Status;
  }

  AsciiPrint("Now displaying deviations\n");
  if ((time.Day - test_day != 0)) {
      AsciiPrint("Deviation in DAY of %d days\n", time.Day - test_day);
      tests_passed = FALSE;
  }
  if ((time.Hour - test_hour != 0)) {
      AsciiPrint("Deviation in HOUR of %d hours\n", time.Hour - test_hour);
      tests_passed = FALSE;
  }
  if ((time.Minute - test_minute != 0)) {
      AsciiPrint("Deviation in MINUTE of %d minutes\n", time.Minute - test_minute);
      tests_passed = FALSE;
  }

  if ((time.Second - test_second ) > UPPER_BOUND_SECONDS_TEST ||
      (time.Second - test_second ) < LOWER_BOUND_SECONDS_TEST) {
      AsciiPrint("Deviation in SECOND of %d seconds\n", time.Second - test_second);
      tests_passed = FALSE;
  }
  if ((time.Year - test_year != 0)) {
      AsciiPrint("Deviation in YEAR of %d years\n", time.Year - test_year);
      tests_passed = FALSE;
  }
  AsciiPrint("Finished displaying deviations\n");
  if (tests_passed) {
      AsciiPrint("All tests completed successfully\n");
  }
  else{
      AsciiPrint("Not all tests passed. Please see the deviations above.\n");
  }
  return Status;
}
