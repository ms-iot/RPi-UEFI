/** @file
  APM X-Gene ACPI Platform Driver

  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/AcpiAml.h>
#include "XGeneEthMAC.h"
#include "XGeneCPU.h"

/**
  Notify function for event group EVT_SIGNAL_EXIT_BOOT_SERVICES. This is used
  to configure the system clock and PHY accordingly.

  @param[in]  Event   The Event that is being processed.
  @param[in]  Context The Event Context.

**/
VOID
EFIAPI
OnAcpiExitBootServices(
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  /* install APIC table */
  XGeneInstallApicTable();

  // Configure Ethernet MAC accordingly
  XGeneEthMACInit();
}

/**
  Entrypoint of Acpi Platform driver.

  @param  ImageHandle
  @param  SystemTable

  @return EFI_SUCCESS
  @return EFI_LOAD_ERROR
  @return EFI_OUT_OF_RESOURCES

**/
EFI_STATUS
EFIAPI
AcpiPlatformEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS Status;
  EFI_EVENT  ExitBootServicesEvent;

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  OnAcpiExitBootServices,
                  NULL,
                  &ExitBootServicesEvent);
  ASSERT_EFI_ERROR(Status);

  return EFI_SUCCESS;
}
