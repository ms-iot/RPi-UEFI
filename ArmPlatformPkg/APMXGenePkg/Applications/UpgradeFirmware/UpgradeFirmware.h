/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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

#ifndef _UPGRADEFIRMWARE_H_
#define _UPGRADEFIRMWARE_H_

#include <Uefi.h>
#include <Base.h>

#include <Guid/FileInfo.h>
#include <Guid/GlobalVariable.h>


#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/PathLib.h>
#include <Library/BaseLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/FileHandleLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/ShellLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>

#include <Protocol/SimpleFileSystem.h>
#include <Protocol/UnicodeCollation.h>
#include <Protocol/BlockIo.h>

#include <Library/I2C.h>

//#define APPS_DEBUG 1
#define APPS_INFO 1

#ifdef APPS_DEBUG
#define DBG(arg...) Print (L"DEBUG: " arg)
#else
#define DBG(arg...)
#endif

#ifdef APPS_INFO
#define INFO(arg...) Print (L"INFO: " arg)
#else
#define INFO(arg...)
#endif

#define ERROR(arg...) Print (L"ERROR: " arg)

#endif
