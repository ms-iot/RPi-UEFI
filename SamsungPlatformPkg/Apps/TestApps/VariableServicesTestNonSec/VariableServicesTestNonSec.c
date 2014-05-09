/** @file VariableServicesTestNonSec.c

  If the Variable services have PcdVariableCollectStatistics set to TRUE then
  the EFI system table will contain statistical information about variable usage
  an this utility will print out the information. You can use console redirection
  to capture the data.

  Copyright (c) 2012 - 2013, Samsung Electronics Inc. All rights reserved.<BR>
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
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Guid/VariableFormat.h>


/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the image goes into a library that calls this
  function.


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
  EFI_STATUS            Status;
  VARIABLE_INFO_ENTRY   *VariableInfo;
  VARIABLE_INFO_ENTRY   *Entry;

  /* For GetNextVariableName */
  UINTN			VariableNameBufferSize;
  UINTN			VariableNameSize;
  CHAR16		*VariableName;
  UINTN			VariableDataBufferSize;
  UINTN			VariableDataSize;
  VOID			*VariableData;
  EFI_GUID		VendorGuid;
  UINT32		VariableAttributes;
  VOID			*NewBuffer;

  VariableNameBufferSize = sizeof (CHAR16);
  VariableNameSize = VariableNameBufferSize;
  VariableName = AllocateZeroPool (VariableNameSize);
  VariableDataBufferSize = 0;
  VariableDataSize = 0;
  VariableData = NULL;
  VariableAttributes = 0;

  Status = EfiGetSystemConfigurationTable (&gEfiVariableGuid, (VOID **)&Entry);
  if (!EFI_ERROR (Status) && (Entry != NULL)) {
    Print (L"Non-Volatile EFI Variables:\n");
    VariableInfo = Entry;
    do {
      if (!VariableInfo->Volatile) {
        Print (
          L"%g R%03d(%03d) W%03d D%03d:%s\n",
          &VariableInfo->VendorGuid,
          VariableInfo->ReadCount,
          VariableInfo->CacheCount,
          VariableInfo->WriteCount,
          VariableInfo->DeleteCount,
          VariableInfo->Name
          );
      }

      VariableInfo = VariableInfo->Next;
    } while (VariableInfo != NULL);

    Print (L"Volatile EFI Variables:\n");
    VariableInfo = Entry;
    do {
      if (VariableInfo->Volatile) {
        Print (
          L"%g R%03d(%03d) W%03d D%03d:%s\n",
          &VariableInfo->VendorGuid,
          VariableInfo->ReadCount,
          VariableInfo->CacheCount,
          VariableInfo->WriteCount,
          VariableInfo->DeleteCount,
          VariableInfo->Name
          );
      }
      VariableInfo = VariableInfo->Next;
    } while (VariableInfo != NULL);

  } else {
    Print (L"Warning: Variable Dxe driver doesn't enable the feature of statistical information!\n");
    Print (L"If you want to see this info, please:\n");
    Print (L"  1. Set PcdVariableCollectStatistics as TRUE\n");
    Print (L"  2. Rebuild Variable Dxe driver\n");
    Print (L"  3. Run \"VariableInfo\" cmd again\n");

  }

  Print (L"GetNextVariableName EFI Variables:\n");
  /* Check GetNextVariableName */
  do {
	VariableNameSize = VariableNameBufferSize;
	Status = gRT->GetNextVariableName(
				&VariableNameSize,
				VariableName,
				&VendorGuid
				);

	if(Status == EFI_BUFFER_TOO_SMALL) {
		NewBuffer = AllocatePool (VariableNameSize);
		CopyMem (NewBuffer, VariableName, VariableNameBufferSize);
		if(VariableName != NULL) {
			FreePool (VariableName);
		}
		VariableName = NewBuffer;
		VariableNameBufferSize = VariableNameSize;

		Status = gRT->GetNextVariableName(
				&VariableNameSize,
				VariableName,
				&VendorGuid
				);
	}

	if(Status == EFI_NOT_FOUND) {
		Status = EFI_SUCCESS;
		break;
	}

	VariableDataSize = VariableDataBufferSize;
	Status = gRT->GetVariable(
			VariableName,
			&VendorGuid,
			&VariableAttributes,
			&VariableDataSize,
			VariableData
			);
	if(Status == EFI_BUFFER_TOO_SMALL) {
		if(VariableDataBufferSize != 0) {
			FreePool (VariableData);
			VariableData = NULL;
			VariableDataBufferSize = 0;
		}

		VariableData = AllocatePool (VariableDataSize);

		VariableDataBufferSize = VariableDataSize;

		Status = gRT->GetVariable(
			VariableName,
			&VendorGuid,
			&VariableAttributes,
			&VariableDataSize,
			VariableData
			);
	}

	Print (L"%.-35g %.-20s : %X\n", &VendorGuid, VariableName, VariableData);

  } while (Status == EFI_SUCCESS);

  return Status;
}
