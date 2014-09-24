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

/*
  A driver using the EFI_FIRMWARE_VOLUME2_PROTOCOL to expose files in firmware
  volumes via the the EFI_SIMPLE_FILESYSTEM_PROTOCOL and EFI_FILE_PROTOCOL.

  Its primary intended use is to be able to start EFI applications embedded
  in FVs from the UEFI shell. For this reason, it is not fully compliant as a
  filesystem driver: it is entirely read-only, and does not support partially
  reading files.

  It will expose a single directory, containing one file for each file in the
  firmware volume. If a file has a UI section, its contents will be used as
  a filename. Otherwise, a string representation of the GUID will be used.
  Files of an executable type (That is PEIM, DRIVER, COMBINED_PEIM_DRIVER
  and APPLICATION) will have ".efi" added to their filename.

  The data returned by Read() depends on the type of the underlying FV file:
  - For executable types, the first section found that contains executable code
    is returned.
  - For files of type FREEFORM, the driver attempts to return the first section
    of type RAW. If none is found, the entire contents of the FV file are
    returned.
  - On all other files the entire contents of the FV file is returned, as by
    EFI_FIRMWARE_VOLUME2_PROTOCOL.ReadFile.

  See the EFI Firmware Volume specification (a separate document from the main
  UEFI specification) for more information about firmware volumes.
*/

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PathLib.h>

#include <Protocol/DriverBinding.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/UnicodeCollation.h>

#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>

#include "FvSimpleFilesystemInternal.h"

/*
  Find and call ReadSection on the first section found of an executable type.
*/
STATIC
EFI_STATUS
FvFsFindExecutableSection (
  IN  FV_FILESYSTEM_FILE *File,
  OUT UINTN              *BufferSize,
  OUT VOID              **Buffer
  )
{
  EFI_SECTION_TYPE               SectionType;
  UINT32                         AuthenticationStatus;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FvProtocol;
  EFI_STATUS                     Status;

  FvProtocol = File->Instance->FvProtocol;

  for (SectionType = EFI_SECTION_PE32; SectionType <= EFI_SECTION_TE; SectionType++) {
    Status = FvProtocol->ReadSection (
                           FvProtocol,
                           &File->NameGuid,
                           SectionType,
                           0,
                           Buffer,
                           BufferSize,
                           &AuthenticationStatus
                           );
    if (Status != EFI_NOT_FOUND) {
      return Status;
    }
  }
  return EFI_NOT_FOUND;
}

/*
  Get the size of the buffer that will be returned by FvFsReadFile.
*/
EFI_STATUS
FvFsGetFileSize (
  IN  FV_FILESYSTEM_FILE *File,
  OUT UINTN              *Size
  )
{
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FvProtocol;
  UINT32                         AuthenticationStatus;
  EFI_FV_FILETYPE                FoundType;
  EFI_FV_FILE_ATTRIBUTES         Attributes;
  EFI_STATUS                     Status;
  UINT8                          IgnoredByte;
  VOID                          *IgnoredPtr;

  FvProtocol = File->Instance->FvProtocol;

  // To get the size of a section, we pass 0 for BufferSize. But we can't pass
  // NULL for Buffer, as that will cause a return of INVALID_PARAMETER, and we
  // can't pass NULL for *Buffer, as that will cause the callee to allocate
  // a buffer of the sections size.
  IgnoredPtr = &IgnoredByte;
  *Size = 0;

  if (FV_FILETYPE_IS_EXECUTABLE (File->Type)) {
    // Get the size of the first executable section out of the file.
    Status = FvFsFindExecutableSection (File, Size, &IgnoredPtr);
    if (Status == EFI_WARN_BUFFER_TOO_SMALL) {
      return EFI_SUCCESS;
    }
  } else if (File->Type == EFI_FV_FILETYPE_FREEFORM) {
    // Try to get the size of a raw section out of the file
    Status = FvProtocol->ReadSection (
                           FvProtocol,
                           &File->NameGuid,
                           EFI_SECTION_RAW,
                           0,
                           &IgnoredPtr,
                           Size,
                           &AuthenticationStatus
                           );
    if (Status == EFI_WARN_BUFFER_TOO_SMALL) {
      return EFI_SUCCESS;
    }
    if (EFI_ERROR (Status)) {
      // Didn't find a raw section, just return the whole file's size.
      return FvProtocol->ReadFile (
                           FvProtocol,
                           &File->NameGuid,
                           NULL,
                           Size,
                           &FoundType,
                           &Attributes,
                           &AuthenticationStatus
                           );
    }
  } else {
    // Get the size of the entire file
    return FvProtocol->ReadFile (
                         FvProtocol,
                         &File->NameGuid,
                         NULL,
                         Size,
                         &FoundType,
                         &Attributes,
                         &AuthenticationStatus
                         );
  }

  return Status;
}

/*
  Helper function to read a file. See comment at the top of this file for
  information on behaviour.
*/
EFI_STATUS
FvFsReadFile (
  FV_FILESYSTEM_FILE *File,
  UINTN              *BufferSize,
  VOID              **Buffer
  )
{
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FvProtocol;
  UINT32                         AuthenticationStatus;
  EFI_FV_FILETYPE                FoundType;
  EFI_FV_FILE_ATTRIBUTES         Attributes;
  EFI_STATUS                     Status;

  FvProtocol = File->Instance->FvProtocol;

  if (FV_FILETYPE_IS_EXECUTABLE (File->Type)) {
    // Read the first executable section out of the file.
    Status = FvFsFindExecutableSection (File, BufferSize, Buffer);
  } else if (File->Type == EFI_FV_FILETYPE_FREEFORM) {
    // Try to read a raw section out of the file
    Status = FvProtocol->ReadSection (
                           FvProtocol,
                           &File->NameGuid,
                           EFI_SECTION_RAW,
                           0,
                           Buffer,
                           BufferSize,
                           &AuthenticationStatus
                           );
    if (EFI_ERROR (Status)) {
      // Didn't find a raw section, just return the whole file.
      Status = FvProtocol->ReadFile (
                             FvProtocol,
                             &File->NameGuid,
                             Buffer,
                             BufferSize,
                             &FoundType,
                             &Attributes,
                             &AuthenticationStatus
                             );
    }
  } else {
    // Read the entire file
    Status = FvProtocol->ReadFile (
                           FvProtocol,
                           &File->NameGuid,
                           Buffer,
                           BufferSize,
                           &FoundType,
                           &Attributes,
                           &AuthenticationStatus
                           );
  }

  return Status;
}

/*
  Helper function for populating an EFI_FILE_INFO for a file.
*/
STATIC
EFI_STATUS
FvFsGetFileInfo (
  IN     FV_FILESYSTEM_FILE *File,
  IN OUT UINTN              *BufferSize,
     OUT EFI_FILE_INFO      *FileInfo
  )
{
  UINTN                          InfoSize;

  InfoSize = sizeof (EFI_FILE_INFO) + StrSize (File->Name) - sizeof (CHAR16);
  if (*BufferSize < InfoSize) {
    *BufferSize = InfoSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  // Initialize FileInfo
  ZeroMem (FileInfo, InfoSize);
  FileInfo->Size = InfoSize;
  FileInfo->Attribute = EFI_FILE_READ_ONLY;

  // File is a directory if it is root.
  if (File == File->Instance->Root) {
    FileInfo->Attribute |= EFI_FILE_DIRECTORY;
  }

  FileInfo->FileSize = File->Size;
  FileInfo->PhysicalSize = File->Size;

  StrCpy (FileInfo->FileName, File->Name);

  *BufferSize = InfoSize;
  return EFI_SUCCESS;
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemOpen (
  IN EFI_FILE_PROTOCOL  *This,
  OUT EFI_FILE_PROTOCOL **NewHandle,
  IN CHAR16             *FileName,
  IN UINT64             OpenMode,
  IN UINT64             Attributes
  )
{
  FV_FILESYSTEM_INSTANCE      *Instance;
  FV_FILESYSTEM_FILE          *File;
  LIST_ENTRY                  *FileLink;

  File = FVFS_FILE_FROM_FILE_THIS (This);
  Instance = File->Instance;

  FileName = PathCleanUpDirectories (FileName);

  if (FileName[0] == L'\\') {
    FileName++;
  }

  // Check for opening root
  if (StrCmp (FileName, L".") == 0 || StrCmp (FileName, L"") == 0) {
    *NewHandle = &Instance->Root->FileProtocol;
    return EFI_SUCCESS;
  }

  //
  // Do a linear search for a file in the FV with a matching filename
  //
  for (FileLink = GetFirstNode (&Instance->Files);
       !IsNull (&Instance->Files, FileLink);
       FileLink = GetNextNode (&Instance->Files, FileLink)) {

    File = FVFS_FILE_FROM_LINK (FileLink);
    if (mUnicodeCollation->StriColl (mUnicodeCollation, File->Name, FileName) == 0) {
      *NewHandle = &File->FileProtocol;
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemClose (
  IN EFI_FILE_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}

/*
  Implementation of EFI_FILE_PROTOCOL.Read.

  This implementation is not compliant with the UEFI specification. As this
  driver's only intended use case is for loading and executing EFI images,
  it does not support partial reads. If *BufferSize is less than the size of the
  image being read, it will return EFI_UNSUPPORTED.
*/
EFIAPI
EFI_STATUS
FvSimpleFilesystemRead (
  IN EFI_FILE_PROTOCOL  *This,
  IN OUT UINTN          *BufferSize,
  OUT VOID              *Buffer
  )
{
  FV_FILESYSTEM_INSTANCE        *Instance;
  FV_FILESYSTEM_FILE            *File;
  EFI_STATUS                     Status;
  LIST_ENTRY                    *FileLink;

  File = FVFS_FILE_FROM_FILE_THIS (This);
  Instance = File->Instance;

  if (File == Instance->Root) {
    if (File->DirReadNext) {
      //
      // Directory read: populate Buffer with an EFI_FILE_INFO
      //
      Status = FvFsGetFileInfo (File->DirReadNext, BufferSize, Buffer);
      if (!EFI_ERROR (Status)) {
        //
        // Successfully read a directory entry, now update the pointer to the
        // next file, which will be read on the next call to this function
        //

        FileLink = GetNextNode (&Instance->Files, &File->DirReadNext->Link);
        if (IsNull (&Instance->Files, FileLink)) {
          // No more files left
          File->DirReadNext = NULL;
        } else {
          File->DirReadNext = FVFS_FILE_FROM_LINK (FileLink);
        }
      }
      return Status;
    } else {
      //
      // Directory read. All entries have been read, so return a zero-size
      // buffer.
      //
      *BufferSize = 0;
      return EFI_SUCCESS;
    }
  } else {
    if (*BufferSize < File->Size) {
      DEBUG ((EFI_D_ERROR, "FV Filesystem does not support partial file reads\n", *BufferSize, File->Size));
      return EFI_UNSUPPORTED;
    }
    return FvFsReadFile (File, BufferSize, &Buffer);
  }
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemWrite (
  IN EFI_FILE_PROTOCOL  *This,
  IN OUT UINTN          *BufferSize,
  IN VOID               *Buffer
  )
{
  return EFI_UNSUPPORTED;
}


EFIAPI
EFI_STATUS
FvSimpleFilesystemGetPosition (
  IN EFI_FILE_PROTOCOL  *This,
  OUT UINT64            *Position
  )
{
  return EFI_UNSUPPORTED;
}

/*
  This implementation of EFI_FILE_PROTOCOL.SetPosition is not compliant with
  the UEFI specification. We do not support partial file reads (see comment on
  FvSimpleFilesystemRead), therefore we only support seeking to position 0
*/
EFIAPI
EFI_STATUS
FvSimpleFilesystemSetPosition (
  IN EFI_FILE_PROTOCOL  *This,
  IN UINT64             Position
  )
{
  FV_FILESYSTEM_INSTANCE      *Instance;
  FV_FILESYSTEM_FILE          *File;

  File = FVFS_FILE_FROM_FILE_THIS (This);
  Instance = File->Instance;

  if (File == Instance->Root) {
    if (Position != 0) {
      return EFI_INVALID_PARAMETER;
    }
    // Reset directory position to first entry
    File->DirReadNext = FVFS_GET_FIRST_FILE (Instance);
  } else if (Position != 0) {
    // We don't support partial file reads, so we don't support seeking either.
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemFlush (
  IN EFI_FILE_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemDelete (
  IN EFI_FILE_PROTOCOL *This
  )
{
  return EFI_UNSUPPORTED;
}

STATIC EFI_FILE_SYSTEM_INFO mFsInfoTemplate = {
  0,    // Populate at runtime
  TRUE, // Read-only
  0,    // Don't know volume size
  0,    // No free space
  0,    // Don't know block size
  L""   // Populate at runtime
};

EFIAPI
EFI_STATUS
FvSimpleFilesystemGetInfo (
  IN EFI_FILE_PROTOCOL  *This,
  IN EFI_GUID           *InformationType,
  IN OUT UINTN          *BufferSize,
  OUT VOID              *Buffer
  )
{
  FV_FILESYSTEM_FILE          *File;
  EFI_FILE_SYSTEM_INFO        *FsInfoOut;
  FV_FILESYSTEM_INSTANCE      *Instance;
  UINTN                        InfoSize;

  File = FVFS_FILE_FROM_FILE_THIS (This);

  if (CompareGuid (InformationType, &gEfiFileSystemInfoGuid)) {
    //
    // Return filesystem info
    //
    Instance = File->Instance;

    InfoSize = sizeof (EFI_FILE_SYSTEM_INFO) + StrSize (Instance->VolumeLabel)
               - sizeof (CHAR16);

    if (*BufferSize < InfoSize) {
      *BufferSize = InfoSize;
      return EFI_BUFFER_TOO_SMALL;
    }

    // Cast output buffer for convenience
    FsInfoOut = (EFI_FILE_SYSTEM_INFO *) Buffer;

    CopyMem (FsInfoOut, &mFsInfoTemplate, mFsInfoTemplate.Size);
    StrCpy (FsInfoOut->VolumeLabel, Instance->VolumeLabel);
    return EFI_SUCCESS;
  } else if (CompareGuid (InformationType, &gEfiFileInfoGuid)) {
    //
    // Return file info
    //

    return FvFsGetFileInfo (File, BufferSize, (EFI_FILE_INFO *) Buffer);
  } else {
    return EFI_UNSUPPORTED;
  }
}

EFIAPI
EFI_STATUS
FvSimpleFilesystemSetInfo (
  IN EFI_FILE_PROTOCOL *This,
  IN EFI_GUID *InformationType,
  IN UINTN BufferSize,
  IN VOID *Buffer
  )
{
  return EFI_UNSUPPORTED;
}

EFI_FILE_PROTOCOL mFilesystemTemplate = {
  EFI_FILE_PROTOCOL_REVISION,
  FvSimpleFilesystemOpen,
  FvSimpleFilesystemClose,
  FvSimpleFilesystemDelete,
  FvSimpleFilesystemRead,
  FvSimpleFilesystemWrite,
  FvSimpleFilesystemGetPosition,
  FvSimpleFilesystemSetPosition,
  FvSimpleFilesystemGetInfo,
  FvSimpleFilesystemSetInfo,
  FvSimpleFilesystemFlush
};
