/** @file
*
*  Do a generic cold & warm reset.
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <PiDxe.h>
#include <Library/ArmLib.h>
#include <Library/IoLib.h>

#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>

#include <Guid/DxeServices.h>
#include <Guid/EventGroup.h>

#include <Bcm2836.h>


volatile UINT32 gPrcmBaseAddress = 0;
EFI_EVENT VirtualAddressChangeEvent = NULL;


typedef
VOID
(EFIAPI *CALL_STUB)(
  VOID
);


VOID
EFIAPI
VirtualAddressChangeCallBack (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  gRT->ConvertPointer(0, (VOID**)&gPrcmBaseAddress);
  gRT->ConvertPointer(0, (VOID**)&gRT);
}


/**
  Resets the entire platform.

  @param  ResetType             The type of reset to perform.
  @param  ResetStatus           The status code for the reset.
  @param  DataSize              The size, in bytes, of WatchdogData.
  @param  ResetData             For a ResetType of EfiResetCold, EfiResetWarm, or
                                EfiResetShutdown the data buffer starts with a Null-terminated
                                Unicode string, optionally followed by additional binary data.

**/
EFI_STATUS
EFIAPI
LibResetSystem (
  IN EFI_RESET_TYPE   ResetType,
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN CHAR16           *ResetData OPTIONAL
  )
{
  UINT32 Rstc;
  UINT32 Rsts = 0;

  switch(ResetType) 
  {
  case EfiResetShutdown:
      // For shut down we stup RSTS so bootcode is aware to halt the boot process.
      // There really isnt a way to shutdown beside stopping boot to continue after
      // reboot
      Rsts = MmioRead32(gPrcmBaseAddress + PRCM_RSTS_OFF);
      Rsts |= 0x0000003F;
      MmioWrite32(gPrcmBaseAddress + PRCM_RSTS_OFF, (PRCM_PASSWORD | Rsts));
  case EfiResetPlatformSpecific:
  case EfiResetWarm:
  case EfiResetCold:
  default: 
      // The platform has no external power/reset controls so the only thing
      // we can do is issue a hard reset triggered from the watchdog hardware.
      // There is no official public documentation on this block - this code is based
      // on snippets around the web.

      Rstc = MmioRead32(gPrcmBaseAddress + PRCM_RSTC_OFF);
      Rstc &= ~PRCM_RSTC_WRCFG_MASK;
      Rstc |= PRCM_RSTC_WRCFG_FULL_RESET;

      MmioWrite32(gPrcmBaseAddress + PRCM_WDOG_OFF, (PRCM_PASSWORD | 10));
      MmioWrite32(gPrcmBaseAddress + PRCM_RSTC_OFF, (PRCM_PASSWORD | Rstc));
      break;
      
  }
  
  // Spin to wait for the end.
  while(1);

  return EFI_DEVICE_ERROR;
}



/**
  Initialize any infrastructure required for LibResetSystem () to function.

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
LibInitializeResetSystem (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS      Status;
  gPrcmBaseAddress = PRCM_BASE_ADDRESS;

  Status = gDS->AddMemorySpace (
                  EfiGcdMemoryTypeMemoryMappedIo,
                  gPrcmBaseAddress, SIZE_4KB,
                  EFI_MEMORY_UC | EFI_MEMORY_RUNTIME
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "LibInitializeResetSystem AddMemorySpace error 0x%x \r\n",Status));
    return Status;
  }

  Status = gDS->SetMemorySpaceAttributes (gPrcmBaseAddress, SIZE_4KB, EFI_MEMORY_UC | EFI_MEMORY_RUNTIME);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "LibInitializeResetSystem SetMemorySpaceAttributes error 0x%x \r\n",Status));
    return Status;
  }

  Status = gBS->CreateEventEx (
                               EVT_NOTIFY_SIGNAL,
                               TPL_NOTIFY,
                               VirtualAddressChangeCallBack,
                               NULL,
                               &gEfiEventVirtualAddressChangeGuid,
                               &VirtualAddressChangeEvent
                               );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "LibInitializeResetSystem CreateEventEx error \r\n"));
    return Status;
  }

  return EFI_SUCCESS;
}


