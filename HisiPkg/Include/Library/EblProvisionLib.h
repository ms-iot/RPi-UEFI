/**********************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/
#ifndef _PROVISION_PATH_H
#define _PROVISION_PATH_H

#include <Protocol/DevicePath.h>
#include <Protocol/DevicePathToText.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/SimpleNetwork.h>

typedef struct {
  CHAR16  *Str;
  UINTN   Length;
  UINTN   Capacity;
} POOL_PRINT;

EFI_FILE_HANDLE
LibOpenRoot (
  IN EFI_HANDLE                   DeviceHandle
  );

EFI_STATUS
EditHIInputStr (
  IN OUT CHAR16  *CmdLine,
  IN     UINTN   MaxCmdLine
  );

EFI_STATUS
EditHIInputAscii (
  IN OUT CHAR8   *CmdLine,
  IN     UINTN   MaxCmdLine
  );

EFI_STATUS
GetHIInputAscii (
  IN OUT CHAR8   *CmdLine,
  IN     UINTN   MaxCmdLine
  );

EFI_STATUS
GetHIInputInteger (
  OUT UINTN   *Integer
  );

#endif
