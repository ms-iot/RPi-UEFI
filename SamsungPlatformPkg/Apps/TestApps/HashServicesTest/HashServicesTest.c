#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UncachedMemoryAllocationLib.h>

#include <Protocol/Hash.h>
#include <Protocol/PciIo.h>

#define NOT_EXTEND	0
#define EXTEND		1

#define TEST_HASH	0x12345678

EFI_STATUS
EFIAPI
HashTestMain (
  IN EFI_HANDLE		ImageHandle,
  IN EFI_SYSTEM_TABLE	*SystemTable
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HASH_PROTOCOL *HashProtocol;
  UINTN HashSize;
  UINT8 *Message;
  UINT32 Count, Test[5];
  EFI_HASH_OUTPUT *Hash;

  DEBUG((EFI_D_ERROR, "[HashTestApps] : HashTestApps\n"));

  for (Count = 0 ; Count < 5; Count++)
	  Test[Count] = TEST_HASH;

  Status = gBS->LocateProtocol(&gEfiHashProtocolGuid, NULL, (VOID **)&HashProtocol);
  ASSERT_EFI_ERROR(Status);

  HashProtocol->GetHashSize(HashProtocol, &gEfiHashAlgorithmSha1Guid, &HashSize);

  Message = (UINT8 *)UncachedAllocatePool(HashSize);
  Hash = (EFI_HASH_OUTPUT *)UncachedAllocatePool(sizeof(EFI_HASH_OUTPUT));
  
  gBS->CopyMem(Hash, Test, sizeof(EFI_SHA1_HASH));
  gBS->CopyMem(Message, "abc", sizeof("abc"));

  HashProtocol->Hash(HashProtocol, &gEfiHashAlgorithmSha1Guid, EXTEND, Message, (UINT64)sizeof("abc"), Hash);

  DEBUG((EFI_D_ERROR, "[HashResult] : Result = %x\n", (EFI_SHA1_HASH *)Hash->Sha1Hash));

  return Status;
}

