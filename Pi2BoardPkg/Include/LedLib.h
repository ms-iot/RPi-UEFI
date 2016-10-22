/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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

#ifndef __LEDLIB_H__
#define __LEDLIB_H__

VOID
EFIAPI
LedInit (
  );

VOID
EFIAPI
LedSetOk (
  IN  BOOLEAN On
  );

VOID
EFIAPI
LedFlashOk (
  IN  UINTN PeriodInMicroSec,
  IN  UINTN Count
  );


#endif // __LEDLIB_H__

