#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/ArmGicLib.h>
#include <Library/UncachedMemoryAllocationLib.h>

#include <Protocol/Hash.h>

#include <Platform/ArmPlatform.h>
#include <Platform/Exynos5250.h>

#include "HashDxe.h"

#define CLOCK_ON	1
#define CLOCK_OFF	0

EFI_STATUS
EFIAPI
CryptoClockGating (
  IN UINT32	clock_status
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 CmuBase;
	UINT32 value;

	CmuBase = PcdGet32(PcdCmuBase);
	value = MmioRead32(CmuBase + SSS_CMU_OFFSET);

	if (clock_status == CLOCK_ON)
		MmioWrite32(CmuBase + SSS_CMU_OFFSET, value | CLK_SSS);
	else if (clock_status == CLOCK_OFF)
		MmioWrite32(CmuBase + SSS_CMU_OFFSET, value & ~CLK_SSS);
	else {
		DEBUG((EFI_D_ERROR, "[HashDxe] : Unsupported SSS clock status\n"));
		Status = EFI_INVALID_PARAMETER;
	}

	return Status;
}

/**
  Returns the size of the hash which results from a specific algorithm.

  @param[in]  This                  Points to this instance of EFI_HASH_PROTOCOL.
  @param[in]  HashAlgorithm         Points to the EFI_GUID which identifies the algorithm to use.
  @param[out] HashSize              Holds the returned size of the algorithm's hash.

  @retval EFI_SUCCESS           Hash size returned successfully.
  @retval EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported 
                                by this driver.

**/
EFI_STATUS
EFIAPI
HashDxeGetHashSize (
  IN  CONST EFI_HASH_PROTOCOL     *This,
  IN  CONST EFI_GUID              *HashAlgorithm,
  OUT UINTN                       *HashSize
  )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha1Guid))
		*HashSize = sizeof(EFI_SHA1_HASH);
	else if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha256Guid))
		*HashSize = sizeof(EFI_SHA256_HASH);
	else {
		DEBUG((EFI_D_ERROR, "[HashDxe] : Unsupported Hash Algorithm\n"));
		Status = EFI_UNSUPPORTED;
	}

	return Status;
}

/**
  Returns the size of the hash which results from a specific algorithm.

  @param[in]  This          Points to this instance of EFI_HASH_PROTOCOL.
  @param[in]  HashAlgorithm Points to the EFI_GUID which identifies the algorithm to use.
  @param[in]  Extend        Specifies whether to create a new hash (FALSE) or extend the specified
                            existing hash (TRUE).
  @param[in]  Message       Points to the start of the message.
  @param[in]  MessageSize   The size of Message, in bytes.
  @param[in,out]  Hash      On input, if Extend is TRUE, then this holds the hash to extend. On
                            output, holds the resulting hash computed from the message.

  @retval EFI_SUCCESS           Hash returned successfully.
  @retval EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this
                                 driver. Or, Extend is TRUE, and the algorithm doesn't support extending the hash.

**/
EFI_STATUS
EFIAPI
HashDxeRunHash (
  IN CONST EFI_HASH_PROTOCOL	*This,
  IN CONST EFI_GUID		*HashAlgorithm,
  IN BOOLEAN			Extend,
  IN CONST UINT8		*Message,
  IN UINT64			MessageSize,
  IN OUT EFI_HASH_OUTPUT	*Hash
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 value;
	UINT32 CryptoBase;
	UINT32 TotalMessageSize;
	UINT32 HashResult[8];
	UINT8 *TempMessage;

	CryptoBase = PcdGet32(PcdCryptoBase);

	CryptoClockGating(CLOCK_ON);

	/* Flush HRDMA */
	MmioWrite32(CryptoBase + SSS_FC_HRDMAC, SSS_FC_HRDMACFLUSH_ON);
	MmioWrite32(CryptoBase + SSS_FC_HRDMAC, SSS_FC_HRDMACFLUSH_OFF);

	/* Set byte swap of in/out data and iv */
	MmioWrite32(CryptoBase + SSS_HASH_BYTESWAP,
			SSS_HASH_SWAPDI_ON | SSS_HASH_SWAPDO_ON | SSS_HASH_SWAPIV_ON);

	/* Select HASH input mux as external source */
	value = MmioRead32(CryptoBase + SSS_FC_FIFOCTRL);
	value = (value & ~SSS_FC_SELHASH_MASK) | SSS_FC_SELHASH_EXOUT;
	MmioWrite32(CryptoBase + SSS_FC_FIFOCTRL, value);

	/* Set HASH algorithm and start hash engine */
	if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha1Guid))
		value = SSS_HASH_ENGSEL_SHA1HASH | SSS_HASH_STARTBIT_ON;
	else if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha256Guid))
		value = SSS_HASH_ENGSEL_SHA256HASH | SSS_HASH_STARTBIT_ON;
	else {
		DEBUG((EFI_D_ERROR, "[HashDxe] : Unsupported Hash Algorithm\n"));
		Status = EFI_UNSUPPORTED;
		return Status;
	}
	MmioWrite32(CryptoBase + SSS_HASH_CONTROL, value);

	/* Enable FIFO mode */
	MmioWrite32(CryptoBase + SSS_HASH_FIFO_MODE, SSS_HASH_FIFO_ON);

	if (Extend == 0)
		TotalMessageSize = MessageSize;
	else if (Extend == 1) {
		if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha1Guid)) {
			TempMessage = (UINT8 *)UncachedAllocatePool(sizeof(EFI_SHA1_HASH) + MessageSize);
			CopyMem(TempMessage, Hash, sizeof(EFI_SHA1_HASH));
			CopyMem(TempMessage + sizeof(EFI_SHA1_HASH), Message, MessageSize);
			TotalMessageSize = sizeof(EFI_SHA1_HASH) + MessageSize;
		 } else if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha256Guid)) {
			TempMessage = (UINT8 *)UncachedAllocatePool(sizeof(EFI_SHA256_HASH) + MessageSize);
			CopyMem(TempMessage, Hash, sizeof(EFI_SHA256_HASH));
			CopyMem(TempMessage + sizeof(EFI_SHA256_HASH), Message, MessageSize);
			TotalMessageSize = sizeof(EFI_SHA256_HASH) + MessageSize;
		}
	}

	MmioWrite32(CryptoBase + SSS_HASH_MSGSIZE_LOW, TotalMessageSize);
	MmioWrite32(CryptoBase + SSS_HASH_MSGSIZE_HIGH, 0);

	/* Set HRDMA */
	/*
	 * Message must be a physical address. Check it.
	 */
	if (Extend == 0)
		MmioWrite32(CryptoBase + SSS_FC_HRDMAS, (UINT32)Message);
	else if (Extend == 1)
		MmioWrite32(CryptoBase + SSS_FC_HRDMAS, (UINT32)TempMessage);

	MmioWrite32(CryptoBase + SSS_FC_HRDMAL, TotalMessageSize);

	/* Check the HASH status */
	while ((MmioRead32(CryptoBase + SSS_HASH_STATUS) & SSS_HASH_MSGDONE_MASK)
			== SSS_HASH_MSGDONE_OFF);

	/* Clear MSG_DONE bit */
	MmioWrite32(CryptoBase + SSS_HASH_STATUS, SSS_HASH_MSGDONE_ON);

	/* Read hash result */
	HashResult[0] = MmioRead32(CryptoBase + SSS_HASH_RESULT1);
	HashResult[1] = MmioRead32(CryptoBase + SSS_HASH_RESULT2);
	HashResult[2] = MmioRead32(CryptoBase + SSS_HASH_RESULT3);
	HashResult[3] = MmioRead32(CryptoBase + SSS_HASH_RESULT4);
	HashResult[4] = MmioRead32(CryptoBase + SSS_HASH_RESULT5);

	if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha256Guid)) {
		HashResult[5] = MmioRead32(CryptoBase + SSS_HASH_RESULT6);
		HashResult[6] = MmioRead32(CryptoBase + SSS_HASH_RESULT7);
		HashResult[7] = MmioRead32(CryptoBase + SSS_HASH_RESULT8);
	}

	if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha1Guid))
		CopyMem(Hash, HashResult, sizeof(EFI_SHA1_HASH));
	else if (CompareGuid(HashAlgorithm, &gEfiHashAlgorithmSha256Guid))
		CopyMem(Hash, HashResult, sizeof(EFI_SHA256_HASH));
	else {
		DEBUG((EFI_D_ERROR, "[HashDxe] : Unsupported Hash Algorithm\n"));
		Status = EFI_UNSUPPORTED;
		return Status;
	}

	MmioWrite32(CryptoBase + SSS_FC_INTPEND, SSS_FC_HRDMA);

	return Status;
}

EFI_HASH_PROTOCOL gHash = {
	HashDxeGetHashSize,
	HashDxeRunHash
};

/**
  Initialize the state information for the HashDxe

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
HashDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = gBS->InstallMultipleProtocolInterfaces(
			&ImageHandle,
			&gEfiHashProtocolGuid,
			&gHash,
			NULL
			);

	return Status;
}
