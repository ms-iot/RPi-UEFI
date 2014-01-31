
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/DxeServicesLib.h>

#include <Guid/FdtTable.h>

EFI_STATUS
EFIAPI
InitializeFdtTableDxe (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;
  VOID *FdtImageData;
  UINTN FdtImageSize;

  Status = GetSectionFromAnyFv(PcdGetPtr(PcdFdtImage), EFI_SECTION_RAW, 0,
    &FdtImageData, &FdtImageSize);
  if (EFI_ERROR(Status))
    return Status;

  DEBUG((EFI_D_ERROR, "InitializeFdtTableDxe: DTB @ 0x%08x\n", FdtImageData));

  return gBS->InstallConfigurationTable(&gEfiFdtTableGuid, FdtImageData);
}
