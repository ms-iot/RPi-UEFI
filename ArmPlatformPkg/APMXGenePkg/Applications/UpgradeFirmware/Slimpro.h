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

#ifndef _SLIMPRO_H_
#define _SLIMPRO_H_

#include "UpgradeFirmware.h"

EFI_STATUS
EFIAPI
EepromInit (VOID);

EFI_STATUS
EFIAPI
EepromRead (
  UINTN Offset,
  CHAR8 *Buffer,
  UINT32 Size
  );

EFI_STATUS
EFIAPI
EepromWrite (
  UINTN Offset,
  CHAR8 *Buffer,
  UINT32 Size
  );

#endif /* _SLIMPRO_H_ */
