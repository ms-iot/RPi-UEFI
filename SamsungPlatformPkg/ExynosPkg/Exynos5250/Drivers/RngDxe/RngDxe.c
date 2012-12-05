/** @file
  Implement EFI Random Number Generator runtime services via Rng Lib.
  
  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/ArmGicLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/ExynosRng.h>

#include "RngDxe.h"

#define CLKDIV		512
#define RNGSEL		5

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
EFI_STATUS
EFIAPI
RngDxeRandomBytes (
  IN CONST EFI_RNG_PROTOCOL	*This,
  OUT UINT8			*Output,
  IN UINTN			Size
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32	TRNGBase;
  UINT32	value, count, fifo_addr;

  TRNGBase = PcdGet32(PcdCryptoBase);

  /* Set Clock Divider */
  MmioWrite32(TRNGBase + TRNG_CLKDIV, CLKDIV);

  /* Select RNG Engine */
  value = TRNG_ENABLE | TRNG_MANUAL_ENABLE | RNGSEL;
  MmioWrite32(TRNGBase + TRNG_CTRL, value);

  /* Select and Enable Post Processor */
  value = TRNG_POST_ENABLE | TRNG_POST_SEL_LFSR;
  MmioWrite32(TRNGBase + TRNG_POST_CTRL, value);

  /* Disable Online Tester */
  MmioWrite32(TRNGBase + TRNG_ONLINE_CTRL, 0);

  /* Set FIFO pointer as number of random bits */
  MmioWrite32(TRNGBase + TRNG_FIFO_CTRL, Size << 3);

  /* Poll FIFO pointer until TRNG_FIFO_CTRL.FIFOPTR == 0 */
  while (MmioRead32(TRNGBase + TRNG_FIFO_CTRL));

  /* Read TRNG FIFO */
  for (count = 0; count < (Size >> 2); count++) {
	  fifo_addr = TRNG_FIFO_0 + (count << 2);
	  value = MmioRead32(TRNGBase + fifo_addr);
	  CopyMem((UINT8 *)((UINT32)Output + (count << 2)), &value, sizeof(value));
  }

  return Status;
}

EFI_RNG_PROTOCOL gRng = {
	RngDxeRandomBytes
};

/**
  Initialize the state information for the RngDxe

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
RngDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = gBS->InstallMultipleProtocolInterfaces(
			&ImageHandle,
			&gSamsungPlatformRngProtocolGuid,
			&gRng,
			NULL
			);

	return Status;
}
