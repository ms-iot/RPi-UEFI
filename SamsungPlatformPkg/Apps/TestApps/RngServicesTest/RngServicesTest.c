/** @file  
  Application for Pseudorandom Number Generator Validation.

Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UncachedMemoryAllocationLib.h>

#include <Protocol/ExynosRng.h>

#define RANDOM_DATA_SIZE	32	/* Bytes */

/**
 * Validate UEFI pseudorandom number generator

**/
EFI_STATUS
EFIAPI
RngTestMain (
  IN EFI_HANDLE		ImageHandle,
  IN EFI_SYSTEM_TABLE	*SystemTable
  )
{
	BOOLEAN  Status = EFI_SUCCESS;
	UINT8 *RandomData;
	UINT32 count;
	EFI_RNG_PROTOCOL *RngProtocol;

	DEBUG((EFI_D_ERROR, "UEFI pseudorandom number generator.\n"));
	DEBUG((EFI_D_ERROR, "Random Generation...\n\n"));

	RandomData = (UINT8 *)UncachedAllocatePool(RANDOM_DATA_SIZE);

	Status = gBS->LocateProtocol(&gSamsungPlatformRngProtocolGuid, NULL, (VOID **)&RngProtocol);

	RngProtocol->RandomBytes(RngProtocol, RandomData, RANDOM_DATA_SIZE);

	for (count = 0; count < (RANDOM_DATA_SIZE >> 2); count++)
		DEBUG((EFI_D_ERROR, "RandomData[%d] : %x\n", count, *(UINT32 *)((UINT32)RandomData + (count << 2))));

	return Status;
}
