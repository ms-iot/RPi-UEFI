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

#ifndef __FVFS_INTERNAL_H__
#define __FVFS_INTERNAL_H__

#include <Library/BaseLib.h>

typedef struct _FV_FILESYSTEM_FILE FV_FILESYSTEM_FILE;

// Struct representing an instance of the "filesystem". There will be one of
// these structs per FV.
typedef struct _FV_FILESYSTEM_INSTANCE {
  UINT32                           Signature;
  LIST_ENTRY                       Link;
  LIST_ENTRY                       Files;
  EFI_DRIVER_BINDING_PROTOCOL     *DriverBinding;
  EFI_FIRMWARE_VOLUME2_PROTOCOL   *FvProtocol;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  SimpleFs;
  FV_FILESYSTEM_FILE              *Root;
  CHAR16                          *VolumeLabel;
} FV_FILESYSTEM_INSTANCE;

// Struct representing a file. There will be one of these for each file on each
// FV, plus one for each FV representing the "root directory".
struct _FV_FILESYSTEM_FILE {
  UINT32                           Signature;
  LIST_ENTRY                       Link;
  CHAR16                          *Name;
  FV_FILESYSTEM_FILE              *DirReadNext;
  EFI_GUID                         NameGuid;
  FV_FILESYSTEM_INSTANCE          *Instance;
  EFI_FILE_PROTOCOL                FileProtocol;
  UINTN                            Size;
  EFI_FV_FILETYPE                  Type;
};

#define FVFS_FILE_SIGNATURE      SIGNATURE_32 ('f', 'v', 'f', 'l')
#define FVFS_INSTANCE_SIGNATURE  SIGNATURE_32 ('f', 'v', 'f', 's')

#define FVFS_INSTANCE_FROM_BINDING_THIS(This) CR (    \
          This,                                       \
          FV_FILESYSTEM_INSTANCE,                     \
          DriverBinding,                              \
          FVFS_INSTANCE_SIGNATURE                     \
          )

#define FVFS_INSTANCE_FROM_SIMPLE_FS_THIS(This) CR (  \
          This,                                       \
          FV_FILESYSTEM_INSTANCE,                     \
          SimpleFs,                                   \
          FVFS_INSTANCE_SIGNATURE                     \
          )

#define FVFS_FILE_FROM_FILE_THIS(This) CR (           \
          This,                                       \
          FV_FILESYSTEM_FILE,                         \
          FileProtocol,                               \
          FVFS_FILE_SIGNATURE                         \
          )

#define FVFS_FILE_FROM_LINK(FileLink) CR (FileLink, FV_FILESYSTEM_FILE, Link, FVFS_FILE_SIGNATURE)

#define FVFS_GET_FIRST_FILE(Instance) FVFS_FILE_FROM_LINK (GetFirstNode (&Instance->Files))

#define FV_FILETYPE_IS_EXECUTABLE(Type) ((Type) == EFI_FV_FILETYPE_PEIM                  || \
                                         (Type) == EFI_FV_FILETYPE_DRIVER                || \
                                         (Type) == EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER  || \
                                         (Type) == EFI_FV_FILETYPE_APPLICATION)

EFI_STATUS
FvFsReadFile (
  FV_FILESYSTEM_FILE *File,
  UINTN              *BufferSize,
  VOID              **Buffer
  );

EFI_STATUS
FvFsGetFileSize (
  IN  FV_FILESYSTEM_FILE *File,
  OUT UINTN              *Size
  );

extern EFI_FILE_PROTOCOL mFilesystemTemplate;

extern EFI_UNICODE_COLLATION_PROTOCOL *mUnicodeCollation;

#endif
