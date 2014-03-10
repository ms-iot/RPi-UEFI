/** @file
*
*  Copyright (c) 2014, ARM Limited. All rights reserved.
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

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/DriverBinding.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/UnicodeCollation.h>

#include "FvSimpleFilesystemInternal.h"

EFI_UNICODE_COLLATION_PROTOCOL *mUnicodeCollation = NULL;

// A Guid string is 32 hex characters with 4 hyphens: 36 characters total
#define GUID_STRING_SIZE (36 * sizeof (CHAR16))

#define FVFS_VOLUME_LABEL_PREFIX    L"Firmware Volume: "
#define FVFS_VOLUME_LABEL_SIZE      (sizeof (FVFS_VOLUME_LABEL_PREFIX) + GUID_STRING_SIZE)
#define FVFS_FALLBACK_VOLUME_LABEL  L"Firmware Volume"

EFI_STATUS
EFIAPI
FvSimpleFilesystemOpenVolume (
  IN  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
  OUT EFI_FILE_PROTOCOL              **RootFile
  )
{
  EFI_STATUS                      Status;
  FV_FILESYSTEM_FILE             *Root;
  CHAR16                         *UiSection;
  EFI_GUID                        NameGuid;
  EFI_FV_FILE_ATTRIBUTES          Attributes;
  UINT32                          Authentication;
  VOID                           *Key;
  EFI_FV_FILETYPE                 FileType;
  UINTN                           Size;
  FV_FILESYSTEM_INSTANCE         *Instance;
  FV_FILESYSTEM_FILE             *File;
  EFI_FIRMWARE_VOLUME2_PROTOCOL  *FvProtocol;
  CHAR16                         *Name;

  Instance = FVFS_INSTANCE_FROM_SIMPLE_FS_THIS (This);
  Status = EFI_SUCCESS;

  if (Instance->Root == NULL) {
    //
    // Allocate file structure for root file
    //
    Root = AllocatePool (sizeof (FV_FILESYSTEM_FILE));
    if (Root == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Instance->Root = Root;

    Root->Instance = Instance;
    Root->Signature = FVFS_FILE_SIGNATURE;
    Root->Name = L"";
    Root->Size = 0;
    CopyMem (&Root->FileProtocol, &mFilesystemTemplate, sizeof (mFilesystemTemplate));

    //
    // Populate the instance's list of files. We consider anything a file that
    // has a UI_SECTION, which we consider to be its filename.
    //

    FvProtocol = Instance->FvProtocol;

    // Allocate Key
    Key = AllocatePool (FvProtocol->KeySize);
    ASSERT (Key != NULL);
    ZeroMem (Key, FvProtocol->KeySize);

    do {
      FileType = EFI_FV_FILETYPE_ALL;

      Status = FvProtocol->GetNextFile (
                             FvProtocol,
                             Key,
                             &FileType,
                             &NameGuid,
                             &Attributes,
                             &Size
                             );
      if (EFI_ERROR (Status)) {
        ASSERT (Status == EFI_NOT_FOUND);
        break;
      }

      //
      // Found a file.
      // Allocate a file structure and populate it.
      //
      File = AllocatePool (sizeof (FV_FILESYSTEM_FILE));
      if (File == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Get a file's name: If it has a UI section, use that, otherwise use
      // its NameGuid.
      //

      UiSection = NULL;
      Status = FvProtocol->ReadSection (
                                 FvProtocol,
                                 &NameGuid,
                                 EFI_SECTION_USER_INTERFACE,
                                 0,
                                 (VOID **)&UiSection,
                                 &Size,
                                 &Authentication
                                 );
      if (!EFI_ERROR (Status)) {
        Name = UiSection;
      } else {
        Name = AllocatePool (GUID_STRING_SIZE);
        if (Name == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        UnicodeSPrint (Name, GUID_STRING_SIZE, L"%g", &NameGuid);
      }

      // Add ".efi" to filenames of drivers and applications.
      if (FV_FILETYPE_IS_EXECUTABLE (FileType)) {
        File->Name = AllocateCopyPool (StrSize (Name) + 8, Name);
        StrCat (File->Name, L".efi");
        FreePool (Name);
      } else {
        File->Name = Name;
      }

      File->Type = FileType;
      File->Signature = FVFS_FILE_SIGNATURE;
      CopyGuid (&File->NameGuid, &NameGuid);
      File->Instance = Instance;
      CopyMem (&File->FileProtocol, &mFilesystemTemplate, sizeof (mFilesystemTemplate));
      InsertHeadList (&Instance->Files, &File->Link);

      // Call FvFsReadFile to get the file's size
      File->Size = 0;
      Status = FvFsGetFileSize (File, &File->Size);
      ASSERT_EFI_ERROR (Status);
    } while (TRUE);

    FreePool (Key);

    if (Status == EFI_NOT_FOUND) {
      Status = EFI_SUCCESS;
    }
  }

  Instance->Root->DirReadNext = FVFS_GET_FIRST_FILE (Instance);
  *RootFile = &Instance->Root->FileProtocol;
  return Status;
}

STATIC EFI_SIMPLE_FILE_SYSTEM_PROTOCOL mSimpleFsTemplate = {
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION,
  FvSimpleFilesystemOpenVolume
};

EFI_STATUS
EFIAPI
FvSimpleFilesystemDriverSupported (
  IN        EFI_DRIVER_BINDING_PROTOCOL *DriverBinding,
  IN        EFI_HANDLE                   ControllerHandle,
  IN        EFI_DEVICE_PATH_PROTOCOL    *DevicePath OPTIONAL
  )
{
  return gBS->OpenProtocol (
                ControllerHandle,
                &gEfiFirmwareVolume2ProtocolGuid,
                NULL,
                gImageHandle,
                ControllerHandle,
                EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                );
}

EFI_STATUS
EFIAPI
FvSimpleFilesystemDriverStart (
  IN        EFI_DRIVER_BINDING_PROTOCOL *DriverBinding,
  IN        EFI_HANDLE                   ControllerHandle,
  IN        EFI_DEVICE_PATH_PROTOCOL    *DevicePath OPTIONAL
  )
{
  EFI_STATUS                      Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL  *FvProtocol;
  FV_FILESYSTEM_INSTANCE         *Instance;
  EFI_DEVICE_PATH_PROTOCOL       *FvDevicePath;
  EFI_GUID                       *FvGuid;

  Status = gBS->LocateProtocol (
                  &gEfiUnicodeCollationProtocolGuid,
                  NULL,
                  (VOID **) &mUnicodeCollation
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open FV protocol
  //

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  (VOID **) &FvProtocol,
                  gImageHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Create an instance
  //
  Instance = AllocatePool (sizeof (FV_FILESYSTEM_INSTANCE));
  if (Instance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Instance->Root = NULL;
  Instance->FvProtocol = FvProtocol;
  Instance->Signature = FVFS_INSTANCE_SIGNATURE;
  InitializeListHead (&Instance->Files);
  CopyMem (&Instance->SimpleFs, &mSimpleFsTemplate, sizeof (mSimpleFsTemplate));

  Status = gBS->InstallProtocolInterface(
                  &ControllerHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &Instance->SimpleFs
                  );

  //
  // Decide on a filesystem volume label, which will include the FV's guid.
  //

  // Get the device path to find the FV's GUID
  Instance->VolumeLabel = NULL;
  Status =  gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &FvDevicePath,
                  gImageHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (!EFI_ERROR (Status)) {
    // Iterate over device path until we find a firmware volume node
    while (!IsDevicePathEndType (FvDevicePath)) {
      if (DevicePathType (FvDevicePath) == MEDIA_DEVICE_PATH &&
          DevicePathSubType (FvDevicePath) == MEDIA_PIWG_FW_VOL_DP) {
        // Allocate the volume label
        Instance->VolumeLabel = AllocatePool (FVFS_VOLUME_LABEL_SIZE);
        // Check the allocation was successful
        if (Instance->VolumeLabel != NULL) {
          // Extract the FV's guid
          FvGuid = &((MEDIA_FW_VOL_DEVICE_PATH *) FvDevicePath)->FvName;
          // Build the volume label string
          UnicodeSPrint (
                       Instance->VolumeLabel,
                       FVFS_VOLUME_LABEL_SIZE,
                       FVFS_VOLUME_LABEL_PREFIX L"%g",
                       FvGuid
            );
        }
        break;
      }
      FvDevicePath = NextDevicePathNode (FvDevicePath);
    }
  }
  // If we didn't decide on a volume label, set a fallback one
  if (Instance->VolumeLabel == NULL) {
    Instance->VolumeLabel = AllocateCopyPool (
                              sizeof (FVFS_FALLBACK_VOLUME_LABEL),
                              FVFS_FALLBACK_VOLUME_LABEL
                              );
  }

  return Status;
}

EFI_STATUS
EFIAPI
FvSimpleFilesystemDriverStop (
  IN        EFI_DRIVER_BINDING_PROTOCOL *DriverBinding,
  IN        EFI_HANDLE                   ControllerHandle,
  IN        UINTN                        NumberOfChildren,
  IN        EFI_HANDLE                  *ChildHandleBuffer OPTIONAL
  )
{
  EFI_STATUS              Status;
  FV_FILESYSTEM_INSTANCE *Instance;
  FV_FILESYSTEM_FILE     *File;
  LIST_ENTRY             *FileLink;

  Instance = FVFS_INSTANCE_FROM_BINDING_THIS (DriverBinding);

  //
  // Close and uninstall protocols.
  //

  Status = gBS->CloseProtocol (
                   ControllerHandle,
                   &gEfiFirmwareVolume2ProtocolGuid,
                   gImageHandle,
                   ControllerHandle
                   );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->UninstallProtocolInterface (
                  ControllerHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  &Instance->SimpleFs
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Free file structures
  //

  if (Instance->Root != NULL) {
    for (FileLink = GetFirstNode (&Instance->Files);
         !IsNull (&Instance->Files, FileLink);
         FileLink = GetNextNode (&Instance->Files, FileLink)) {
      File = FVFS_FILE_FROM_LINK (FileLink);

      FreePool (File->Name);
      FreePool (File);
    }
    // Root->Name is statically allocated, no need to free.
    FreePool (Instance->Root);
  }

  //
  // Free Instance
  //

  if (Instance->VolumeLabel != NULL) {
    FreePool (Instance->VolumeLabel);
  }
  FreePool (Instance);

  return EFI_SUCCESS;
}

EFI_DRIVER_BINDING_PROTOCOL mDriverBinding = {
  FvSimpleFilesystemDriverSupported,
  FvSimpleFilesystemDriverStart,
  FvSimpleFilesystemDriverStop,
  0,
  NULL,
  NULL
};

EFIAPI
EFI_STATUS
FvSimpleFilesystemEntryPoint (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS Status;

  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gEfiDriverBindingProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mDriverBinding
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
