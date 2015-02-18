/**
 * ResetSystem Runtime call.
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/EfiResetSystemLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>

#include <Guid/GlobalVariable.h>
#include <Guid/EventGroup.h>

#include <ArmPlatform.h>
#include <ipp_csr.h>
#include <ipp_interface.h>

#define SCU_BASE_ADDR         0x17000000
#define SCU_ADDRESS_MASK      0xfffff000
#define APM_MPA_REG_OFFSET    0x1000

UINT64  ResetAddr = (UINT64)(SCU_BASE_ADDR + 0x14);
UINT64  ResetAddrIpp = 0x10549010;
UINT64  IppInfoAddr = (UINT64)(SCU_BASE_ADDR + APM_MPA_REG_OFFSET + MPA_SCRATCH14_ADDR);

EFI_EVENT  mVirtualAddressChangeEvent = NULL;

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param  Event        Event whose notification function is being invoked.
  @param  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
VariableClassAddressChangeEvent (
  IN EFI_EVENT                            Event,
  IN VOID                                 *Context
  )
{
  EfiConvertPointer (0x0, (VOID **) &ResetAddr);
  EfiConvertPointer (0x0, (VOID **) &ResetAddrIpp);
  EfiConvertPointer (0x0, (VOID **) &IppInfoAddr);
}

EFI_STATUS
EFIAPI
IppReboot(VOID)
{
  ipp_info_t ipp_info;

  ipp_info.bd_pwr_info.data = MmioRead32((UINTN)IppInfoAddr);
  if (ipp_info.bd_pwr_info.inf.reset_cap){
    MmioWrite32((UINTN)ResetAddrIpp, 1);
    return EFI_SUCCESS;
  }

  return EFI_UNSUPPORTED;
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
  switch (ResetType) {
  case EfiResetWarm:
    // Map a warm reset into a cold reset
  case EfiResetCold:
  case EfiResetShutdown:
  case EfiResetPlatformSpecific:
    if (EFI_ERROR(IppReboot())) {
      MmioWrite32((UINTN)ResetAddr, 1);
    }
    // We should never be here
    while(1);
  }

  ASSERT(FALSE);
  return EFI_UNSUPPORTED;
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
  EFI_STATUS Status;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR Descriptor;

  Status = gDS->GetMemorySpaceDescriptor(ResetAddr & SCU_ADDRESS_MASK, &Descriptor);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gDS->SetMemorySpaceAttributes (
                  ResetAddr & SCU_ADDRESS_MASK,
                  0x1000, /* 4K align */
                  Descriptor.Attributes | EFI_MEMORY_RUNTIME
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gDS->GetMemorySpaceDescriptor(ResetAddrIpp & SCU_ADDRESS_MASK, &Descriptor);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gDS->SetMemorySpaceAttributes (
                  ResetAddrIpp & SCU_ADDRESS_MASK,
                  0x1000, /* 4K align */
                  Descriptor.Attributes | EFI_MEMORY_RUNTIME
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gDS->GetMemorySpaceDescriptor(IppInfoAddr & SCU_ADDRESS_MASK, &Descriptor);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gDS->SetMemorySpaceAttributes (
                  IppInfoAddr & SCU_ADDRESS_MASK,
                  0x1000, /* 4K align */
                  Descriptor.Attributes | EFI_MEMORY_RUNTIME
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  VariableClassAddressChangeEvent,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mVirtualAddressChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
