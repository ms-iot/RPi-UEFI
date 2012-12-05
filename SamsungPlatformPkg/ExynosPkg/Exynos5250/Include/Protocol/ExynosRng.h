/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __EXYNOS_RNG_H__
#define __EXYNOS_RNG_H__

//
// Protocol interface structure
//
typedef struct _EFI_RNG_PROTOCOL EFI_RNG_PROTOCOL;

/**
 * Generates a pseudorandom byte stream of the specified size.
 *
 * If Output is NULL, then return FALSE.
 *
 * @param[out]  Output		Pointer to buffer to receive random value
 * @param[in]	Size		Size of random bytes to generate
 *
 * @retval  TRUE	Pseudorandom byte stream generated successfully.
 * @retval  FALSE	Pseudorandom number generator fails to generate due to lack of entropy.
 *
 **/
typedef
EFI_STATUS
(EFIAPI *EFI_RANDOM_BYTES) (
  IN CONST EFI_RNG_PROTOCOL	*This,
  OUT UINT8			*Output,
  IN UINTN			Size
  );

///
/// This protocol allows creating peudorandom random number using HW RNG engine.
///
struct _EFI_RNG_PROTOCOL {
  EFI_RANDOM_BYTES		RandomBytes;
};

extern EFI_GUID gSamsungPlatformRngProtocolGuid;

#endif
