/** @file MiscellaneousTest.c

  Samsung S.LSI MiscellaneousServices application

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

EFI_EVENT HelloTimerEvent;

VOID
EFIAPI print_hello( void )
{
  UINT32 Index;

  Index = 0;

  //
  // Three PCD type (FeatureFlag, UINT32 and String) are used as the sample.
  //
  if (FeaturePcdGet (PcdHelloWorldPrintEnable)) {
	for (Index = 0; Index < PcdGet32 (PcdHelloWorldPrintTimes); Index ++) {
	  //
	  // Use UefiLib Print API to print string to UEFI console
	  //
	Print ((CHAR16*)PcdGetPtr (PcdHelloWorldPrintString));
    }
  }
}

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
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN EventIndex;
  EFI_STATUS  Status;
  UINT64 BSCounter;
  UINT64 BSCounterNext;
  UINT32 RTCounter;
  UINT32 RTCounterNext;

  do{
    print_hello();

    //
    // Create the timer event to implement a timer
    //
    Status = gBS->CreateEvent (
                    EVT_TIMER,
                    TPL_NOTIFY,
                    NULL,
                    NULL,
                    &HelloTimerEvent
                    );
    if(EFI_ERROR (Status)) {
      break;
    }

    // Set timer for 1 second
    AsciiPrint("Registering Timer Event: 1 second relative timer\n");
    gBS->SetTimer(HelloTimerEvent, TimerRelative, 10000000);
    AsciiPrint("Waiting for 1 second\n");
    gBS->WaitForEvent(1, &HelloTimerEvent, &EventIndex);
    AsciiPrint("1 second timer event signaled\n");

    // Test Stall
    AsciiPrint("Stalling for 2 seconds\n");
    gBS->Stall(2000000);
    AsciiPrint("2 second stall complete\n");

    // Testing GetNextMonotonicCount
    gBS->GetNextMonotonicCount(&BSCounter);
    AsciiPrint("Current Monotonic Counter Value: 0x%llx\n", BSCounter);
    gBS->GetNextMonotonicCount(&BSCounterNext);
    AsciiPrint("Next Monotonic Counter Value: 0x%llx\n", BSCounterNext);
    if (BSCounter != (BSCounterNext-1))
    {
      Status = EFI_UNSUPPORTED;
      break;
    }
    else
    {
      AsciiPrint("Monotonic Counter Test Case Passed\n");
    }

    // Testing GetNextHighMonotonicCount
    gRT->GetNextHighMonotonicCount(&RTCounter);
    AsciiPrint("Current High Monotonic Counter Value: 0x%x\n", RTCounter);
    gRT->GetNextHighMonotonicCount(&RTCounterNext);
    AsciiPrint("Next High Monotonic Counter Value: 0x%x\n", RTCounterNext);
    if (RTCounter != (RTCounterNext-1))
    {
      Status = EFI_UNSUPPORTED;
      break;
    }
    else
    {
      AsciiPrint("High Monotonic Counter Test Case Passed\n");
    }
  }while (0);

  return Status;
}
