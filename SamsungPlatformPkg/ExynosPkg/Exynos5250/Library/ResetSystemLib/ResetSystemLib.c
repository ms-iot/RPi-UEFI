/** @file
  Template library implementation to support ResetSystem Runtime call.

  Fill in the templates with what ever makes you system reset.


  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <PiDxe.h>

#include <Library/UefiRuntimeLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/EfiResetSystemLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Platform/ArmPlatform.h>

#include <Guid/EventGroup.h>


/* Round off to 4KB pages */
#define ROUND_TO_PAGE(x) (x & 0xfffff000)


UINT32    gPmuBaseAddress   = 0;
EFI_EVENT VirtualAddressChangeEvent = NULL;

VOID DestroyExynosMemMap(VOID);
typedef VOID (EFIAPI *ptrImageStart)(VOID);

/**
  Virtual address change notification call back. It converts global pointer
  to virtual address.

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.
**/
VOID
EFIAPI
VirtualAddressChangeCallBack (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  gRT->ConvertPointer(0, (VOID**)&gPmuBaseAddress);
  gRT->ConvertPointer(0, (VOID**)&gRT);
}


VOID
DestroyExynosMemMap (
  VOID
  )
{
  EFI_STATUS              Status;
  UINTN                   MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR   *MemoryMap;
  UINTN                   MapKey;
  UINTN                   DescriptorSize;
  UINTN                   DescriptorVersion;
  UINTN                   Pages;

  MemoryMap = NULL;
  MemoryMapSize = 0;
  do {
    Status = gBS->GetMemoryMap (
                    &MemoryMapSize,
                    MemoryMap,
                    &MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );
    if (Status == EFI_BUFFER_TOO_SMALL) {

      Pages = EFI_SIZE_TO_PAGES (MemoryMapSize) + 1;
      MemoryMap = AllocatePages (Pages);

      //
      // Get System MemoryMap
      //
      Status = gBS->GetMemoryMap (
                      &MemoryMapSize,
                      MemoryMap,
                      &MapKey,
                      &DescriptorSize,
                      &DescriptorVersion
                      );
      // Don't do anything between the GetMemoryMap() and ExitBootServices()
      if (!EFI_ERROR (Status)) {
        Status = gBS->ExitBootServices (gImageHandle, MapKey);
        if (EFI_ERROR (Status)) {
          FreePages (MemoryMap, Pages);
          MemoryMap = NULL;
          MemoryMapSize = 0;
        }
      }
    }
  } while (EFI_ERROR (Status));

  //Clean and invalidate caches.
  WriteBackInvalidateDataCache();
  InvalidateInstructionCache();

  //Turning off Caches and MMU
  ArmDisableDataCache ();
  ArmDisableInstructionCache ();
  ArmDisableMmu ();
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
	volatile UINT32 count = 0;

  if (EfiAtRuntime())
	{
		while (count < 0x1000000)
		{
			count++;
		}
	}

	switch (ResetType) {
  case EfiResetShutdown:
  case EfiResetCold:
	case EfiResetWarm:
    //Perform warm reset of the system by jumping to the begining of the FV
	  //((ptrImageStart)PcdGet32(PcdFvBaseAddress))();
    //break;
  default:
		if(EfiAtRuntime () == 0)
		{
	    DestroyExynosMemMap();
		}

		/* Perform cold reset of the system - should not return */
    MmioWrite32 ((gPmuBaseAddress + SWRESET_OFFSET), 0x01);
    while ((MmioRead32(gPmuBaseAddress + SWRESET_OFFSET)) != 0x1);
    break;
  }

  // If the reset didn't work, return an error.
  ASSERT (FALSE);
  return EFI_SUCCESS;
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
  EFI_STATUS  Status;

  EFI_GCD_MEMORY_SPACE_DESCRIPTOR  PmuMemoryDescriptor;

	gPmuBaseAddress = PcdGet32(PcdPmuBase);

  /*
  * Get the GCD Memory Descriptor specified by WdtBaseAddress page boundary
  */
  Status = gDS->GetMemorySpaceDescriptor (ROUND_TO_PAGE(gPmuBaseAddress),
                                          &PmuMemoryDescriptor);
	ASSERT_EFI_ERROR (Status);

  /*
  * Mark the 4KB region as EFI_RUNTIME_MEMORY so the OS
  * will allocate a virtual address range.
  */
  Status = gDS->SetMemorySpaceAttributes (
                                          ROUND_TO_PAGE(gPmuBaseAddress),
                                          EFI_PAGE_SIZE,
                                          PmuMemoryDescriptor.Attributes | EFI_MEMORY_RUNTIME);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                               EVT_NOTIFY_SIGNAL,
                               TPL_NOTIFY,
                               VirtualAddressChangeCallBack,
                               NULL,
                               &gEfiEventVirtualAddressChangeGuid,
                               &VirtualAddressChangeEvent
                               );
  ASSERT_EFI_ERROR (Status);




  return EFI_SUCCESS;
}
