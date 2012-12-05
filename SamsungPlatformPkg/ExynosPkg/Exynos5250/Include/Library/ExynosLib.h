/** @file

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __EXYNOSLIB_H__
#define __EXYNOSLIB_H__

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/**
  gExynosPkgTokenSpaceGuid GUID definition.
*/
#define EXYNOSPKG_TOKEN_SPACE_GUID \
         { 0x70b6655a, 0x7a03, 0x11e0, { 0xbe, 0x19, 0x00, 0x26, 0xb9, 0x73, 0x3e, 0x2c } }

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the gExynosPkgTokenSpaceGuid GUID.
*/
extern EFI_GUID gExynosPkgTokenSpaceGuid;


UINT32
EFIAPI
GpioBase (
  IN  UINTN Port
  );

#endif // __EXYNOSLIB_H__
