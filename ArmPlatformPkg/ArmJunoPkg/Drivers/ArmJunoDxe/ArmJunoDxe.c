/** @file
*
*  Copyright (c) 2013-2014, ARM Limited. All rights reserved.
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

#include "ArmJunoDxeInternal.h"

// This GUID must match the FILE_GUID in ArmPlatformPkg/ArmJunoPkg/AcpiTables/AcpiTables.inf
STATIC CONST EFI_GUID mJunoAcpiTableFile = { 0xa1dd808e, 0x1e95, 0x4399, { 0xab, 0xc0, 0x65, 0x3c, 0x82, 0xe8, 0x53, 0x0c } };

EFI_STATUS
EFIAPI
ArmJunoEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS Status;

  Status = PciEmulationEntryPoint ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Try to install the ACPI Tables
  Status = LocateAndInstallAcpiFromFv (&mJunoAcpiTableFile);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Try to install the Flat Device Tree (FDT). This function actually installs the
  // UEFI Driver Binding Protocol.
  Status = JunoFdtInstall (ImageHandle);

  return Status;
}
