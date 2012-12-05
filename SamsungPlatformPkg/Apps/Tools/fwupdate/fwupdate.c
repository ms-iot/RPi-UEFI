#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/EfiFileLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskIo.h>

#define FILE_COPY_CHUNK 0x280000
#define TZSW_PARTITION_SIZE 0x80000
#define BLOCK_SIZE    512
#ifndef MAX_PATH
#define MAX_PATH 128
#endif


/*
 * Enumerations for Source type and target device
 */
typedef enum _FW_SOURCE_TYPE {
  SOURCE_MEMORY = 1,
  SOURCE_FILE   = 2
} FW_SOURCE_TYPE;

typedef enum _FW_BOOT_DEVICE {
  BOOTDEV_MIN   = 0,
  BOOTDEV_EMMC  = 1,
  BOOTDEV_SDCARD= 2,
  BOOTDEV_MAX   = 3
} FW_BOOT_DEVICE;


/*
 * Default Settings for FW Update (Moved from PCD)
 */
#define DEFAULT_SOURCE_TYPE         SOURCE_MEMORY
#define DEFAULT_TARGET_DEVICE       BOOTDEV_EMMC
#define DEFAULT_BL1_SIZE						15
#define DEFAULT_BL1_SOURCE_ADDRESS  0x42000000
#define DEFAULT_UEFI_SOURCE_ADDRESS 0x44000000
#define DEFAULT_TZSW_SOURCE_ADDRESS 0x45000000
#define DEFAULT_BL1_SOURCE_FILE     L"fs1:\\fwbl1_5250.bin"
#define DEFAULT_UEFI_SOURCE_FILE    L"fs1:\\ARNDALE_EFI.fd"
#define DEFAULT_TZSW_SOURCE_FILE    L"fs1:\\TZSW.bin"

#define BL2_BLOCK_COUNT             32

typedef struct _FW_UPDATE_INFO {
  FW_SOURCE_TYPE  SourceType;
  UINT32                 BL1SourceAddr;
  UINT32                 UEFISourceAddr;
  UINT32                 TZSWSourceAddr;
  CHAR8 BL1FileName[MAX_PATH];
  CHAR8 UefiFileName[MAX_PATH];
  CHAR8 TZSWFileName[MAX_PATH];
  FW_BOOT_DEVICE TargetMediaID;

} FW_UPDATE_INFO;


/* Prototypes of local functions */
EFI_STATUS GetFirmwareUpdateInfoFromUser(
  OUT struct _FW_UPDATE_INFO* pFwUpdateInfo);
VOID SetDefaultFirmwareUpdateInfo(
  OUT struct _FW_UPDATE_INFO* pFwUpdateInfo);


EFI_STATUS GetHIInputInteger (OUT UINTN   *Integer);
EFI_STATUS GetHIInputStr (IN OUT CHAR16  *CmdLine, IN UINTN MaxCmdLine);
EFI_STATUS GetHIInputHex (OUT UINTN   *Integer);

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_OPEN_FILE *Source = NULL;
  VOID *Buffer = NULL;
  EFI_HANDLE *HandleBuffer = NULL;
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN Size, NumHandles;
  EFI_BLOCK_IO_PROTOCOL *BlockIo;
  EFI_DISK_IO_PROTOCOL *DiskIo;
  UINT32 i;

  UINT32 TargetMediaId;

  /* Start block number for writing bootloader blocks - default value is for eMMC*/
  UINT32 BL1TargetBlock = 0;
  UINT32 BL2TargetBlock = 16;
  UINT32 UEFITargetBlock = 48;
  UINT32 TZSWTargetBlock = 5216; // 2608K

  struct _FW_UPDATE_INFO fwUpdateInfo;

  /* Get Firmware update information from User */
  GetFirmwareUpdateInfoFromUser(&fwUpdateInfo);

  /* Set Media ID as user's setting */
  switch (fwUpdateInfo.TargetMediaID) {
    case BOOTDEV_EMMC:
      TargetMediaId = SIGNATURE_32('e','m','m','c');
      break;
    case BOOTDEV_SDCARD:
      TargetMediaId = SIGNATURE_32('s','d','h','c');
      BL1TargetBlock += 1;
      break;
    default:
      DEBUG((EFI_D_ERROR, "Target Device is unknown device %d\n", fwUpdateInfo.TargetMediaID));
      return EFI_UNSUPPORTED;
  }

  /* Workaround: There's a code that increase MediaID of Block IO device when it found,
     Therefore, to match media ID of the device, target Media ID here should be incresed by 1
     This is temporary solution, eventually, Block IO device management code should be modified */
  TargetMediaId ++;

  DEBUG((EFI_D_INFO, "Target Device ID = 0x%x\n", TargetMediaId));

  /* Locating all handles in the system supporting EFI_BLOCK_IO_PROTOCOL */
  Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &NumHandles, &HandleBuffer);

  DEBUG((EFI_D_INFO, "Number of handles supporting Block IO = %d\n", NumHandles));

  /* Finding out the handle of the SDHC Block IO driver through its Media ID
  i.e. 0x63686473 (The Media ID can be found in the SDHC DXE driver code) */
  for(i=0;i<NumHandles;i++) {
    Status = gBS->HandleProtocol(HandleBuffer[i], &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
    ASSERT_EFI_ERROR(Status);

    DEBUG((EFI_D_ERROR, "Device %d Media ID=0x%x\n", i, BlockIo->Media->MediaId));

    if(BlockIo->Media->MediaId == TargetMediaId)
      break;
  }

  if(i == NumHandles) {
    DEBUG((EFI_D_ERROR, "Cannot find Block IO protocol handle! \n"));
    goto Exit;
  }

  /* Locating the Disk IO handle corresponding to the target device Block IO handle
     (Note: There is a Disk IO handle for every Block IO handle according to Disk IO driver implementation) */
  Status = gBS->HandleProtocol(HandleBuffer[i], &gEfiDiskIoProtocolGuid, (VOID **)&DiskIo);
  ASSERT_EFI_ERROR(Status);

  /* Allocating 2MB buffer for impending read operations */
  Buffer = AllocatePool(FILE_COPY_CHUNK);
  if (Buffer == NULL) {
    DEBUG((EFI_D_ERROR, "AllocatePool error.\n"));
    goto Exit;
  }


  /* for temporally */
  if (fwUpdateInfo.SourceType == SOURCE_FILE) {

    /* Reading BL1 binary from file system (for example in USB flask disk) into the allocated buffer */
    Source = EfiOpen(fwUpdateInfo.BL1FileName, EFI_FILE_MODE_READ, 0);
    if (Source == NULL) {
      /* TODO: Convert file name which is written in ASCII string to Unicode to print to console */
      DEBUG((EFI_D_ERROR, "Source file [%s] open error.\n", fwUpdateInfo.BL1FileName));
      return EFI_NOT_FOUND;
    }

    Size = EfiTell(Source, NULL);

    DEBUG((EFI_D_ERROR, "File size = %d\n", Size));

    Status = EfiRead(Source, Buffer, &Size);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "Read file error %r\n", Status));
      goto Exit;
    }

    Status = EfiClose(Source);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "Source file close error %r\n", Status));
    }
    Source = NULL;
  } else {
		if (*((UINT32 *)(fwUpdateInfo.BL1SourceAddr + 0x2000)) == 0xEA000038)
		{
			Size = 15 * 1024; // 16 KB
      DEBUG((EFI_D_ERROR, "Loading BL1 + BLMon (0x%X) (%d) \n", *((UINT32 *)(fwUpdateInfo.BL1SourceAddr + 0x2000)) ,Size));
		} else {
			Size = 8 * 1024;
      DEBUG((EFI_D_ERROR, "Loading BL1 without BLMon (0x%X) (%d) \n", *((UINT32 *)(fwUpdateInfo.BL1SourceAddr + 0x2000)) ,Size));
		}
    gBS->CopyMem(Buffer, (VOID *)fwUpdateInfo.BL1SourceAddr,  Size );
  }

  /* Writing BL1 into the SD card starting from block BL1TargetBlock (0 for eMMC, 1 for SD)
     i.e. offset -> block no. * block size -> 1 x 512 = 512 */
  Status = DiskIo->WriteDisk(DiskIo, BlockIo->Media->MediaId, (BL1TargetBlock*BLOCK_SIZE), Size, Buffer);
  ASSERT_EFI_ERROR(Status);


  /* BL2 target block should be vary with BL1 size */
  BL2TargetBlock = BL1TargetBlock + (UINT32)((Size-1) / BLOCK_SIZE) + 1;
  DEBUG((EFI_D_ERROR, "BL2 Target Block Number is %d\n", BL2TargetBlock));

  if (fwUpdateInfo.SourceType == SOURCE_FILE) {

    /* Reading the new UEFI F/W binary into the allocated buffer */
    Source = EfiOpen(fwUpdateInfo.UefiFileName, EFI_FILE_MODE_READ, 0);
    if (Source == NULL) {
      DEBUG((EFI_D_ERROR, "Source file [%s] open error.\n", fwUpdateInfo.UefiFileName));
      return EFI_NOT_FOUND;
    }

    Size = EfiTell(Source, NULL);

    DEBUG((EFI_D_ERROR, "File size = %d\n", Size));

    Status = EfiRead(Source, Buffer, &Size);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "Read file error %r\n", Status));
      goto Exit;
    }
  } else {
    Size = FILE_COPY_CHUNK;
    gBS->CopyMem( Buffer, (void *) fwUpdateInfo.UEFISourceAddr, Size);
  }


  /* Writing BL2 into  the Boot device from BL2 (16 for eMMC, 17 for SD) for upto 32 blocks */
  {
    UINT32 checksum, tmp, addr, i;

    addr = (UINT32)Buffer;

    /* Calculating and writing the checksum required for BL2 */
    for(i=0, checksum=0;i<((14*1024) -4);i++)
      checksum += *((UINT8 *)addr++);

    tmp = *((UINT32 *)addr);
    *((UINT32 *)addr) = checksum;

    Status = DiskIo->WriteDisk(DiskIo, BlockIo->Media->MediaId, (BL2TargetBlock*BLOCK_SIZE), (BL2_BLOCK_COUNT*BLOCK_SIZE), Buffer);
    ASSERT_EFI_ERROR(Status);

    *((UINT32 *)addr) = tmp;
  }


  /* UEFI target block should be vary with BL1 size */
  UEFITargetBlock = BL2TargetBlock + BL2_BLOCK_COUNT;
  DEBUG((EFI_D_ERROR, "UEFI Target Block Number is %d\n", UEFITargetBlock));

  /* Finally Writing the new UEFI F/W into the Boot device from UEFITargetBlock (48 for eMMC, 49 for SD) */
  Status = DiskIo->WriteDisk(DiskIo, BlockIo->Media->MediaId, (UEFITargetBlock*BLOCK_SIZE), Size, Buffer);
  ASSERT_EFI_ERROR(Status);


  if (fwUpdateInfo.SourceType == SOURCE_FILE) {

    /* Reading the new UEFI F/W binary into the allocated buffer */
    Source = EfiOpen(fwUpdateInfo.TZSWFileName, EFI_FILE_MODE_READ, 0);
    if (Source == NULL) {
      DEBUG((EFI_D_ERROR, "Source file [%s] open error.\n", fwUpdateInfo.TZSWFileName));
      return EFI_NOT_FOUND;
    }

    Size = EfiTell(Source, NULL);

    DEBUG((EFI_D_ERROR, "File size = %d\n", Size));

    Status = EfiRead(Source, Buffer, &Size);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "Read file error %r\n", Status));
      goto Exit;
    }
  } else {
    Size = TZSW_PARTITION_SIZE;
    gBS->CopyMem( Buffer, (void *) fwUpdateInfo.TZSWSourceAddr, Size);
  }


  TZSWTargetBlock = UEFITargetBlock + ((FILE_COPY_CHUNK-1) / BLOCK_SIZE) + 1;
  DEBUG((EFI_D_ERROR, "TZSW Target Block Number is %d\n", TZSWTargetBlock));

  Status = DiskIo->WriteDisk(DiskIo, BlockIo->Media->MediaId, (TZSWTargetBlock * BLOCK_SIZE), Size, Buffer);
  ASSERT_EFI_ERROR(Status);

Exit:
  if (Source != NULL) {
    Status = EfiClose(Source);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "Source file close error %r\n", Status));
    }
  }

    if (Buffer != NULL) {
    FreePool(Buffer);
  }

  return Status;
}



/**
  Get required parameters such as firmware image file name and target device from the user

  @param[out] pFwUpdateInfo  Pointer to a structure that has firmware update information

  @retval EFI_SUCCESS       This function is executed successfully
  @retval other             Some error occurs while executing this function

**/

EFI_STATUS
GetFirmwareUpdateInfoFromUser(
  OUT struct _FW_UPDATE_INFO* pFwUpdateInfo
  )
{
  UINT32  TargetMediaId;
  UINT32  nInput;
  CHAR16  InputFileName[MAX_PATH];



  SetDefaultFirmwareUpdateInfo(pFwUpdateInfo);


  /* Derek - 2012. 7. 10 */
  // Ask to user about Update image source
  Print(L"Select your update image source location (1: Memory , 2: File) (%d):", pFwUpdateInfo->SourceType);
  GetHIInputInteger(&nInput);
	if( (nInput == 1) || (nInput == 2) )
    pFwUpdateInfo->SourceType = nInput;

  if (pFwUpdateInfo->SourceType == SOURCE_MEMORY) {
    Print(L"Enter BL1 Source Address (0x%08X) : 0x", pFwUpdateInfo->BL1SourceAddr);
    GetHIInputHex(&nInput);
    if (nInput)
        pFwUpdateInfo->BL1SourceAddr = nInput;

    Print(L"Enter UEFI Source address (0x%08X) : 0x", pFwUpdateInfo->UEFISourceAddr);
    GetHIInputHex(&nInput);
    if (nInput)
        pFwUpdateInfo->UEFISourceAddr = nInput;

    Print(L"Enter TZSW Source address (0x%08X) : 0x", pFwUpdateInfo->TZSWSourceAddr);
    GetHIInputHex(&nInput);
    if (nInput)
        pFwUpdateInfo->TZSWSourceAddr = nInput;

  } else { // Source type is File

    Print(L"Enter BL1 Image File Name (%a):",pFwUpdateInfo->BL1FileName);

    GetHIInputStr(InputFileName, MAX_PATH);
    if (StrLen (InputFileName) > 0)
      UnicodeStrToAsciiStr(InputFileName, pFwUpdateInfo->BL1FileName);


    Print (L"Enter UEFI File Name (%a): ", pFwUpdateInfo->UefiFileName);

    GetHIInputStr(InputFileName, MAX_PATH);
    if (StrLen (InputFileName) > 0)
      UnicodeStrToAsciiStr(InputFileName, pFwUpdateInfo->UefiFileName);


    Print (L"Enter TZSW File Name (%a): ", pFwUpdateInfo->TZSWFileName);

    GetHIInputStr(InputFileName, MAX_PATH);
    if (StrLen (InputFileName) > 0)
      UnicodeStrToAsciiStr(InputFileName, pFwUpdateInfo->TZSWFileName);
  }

  Print (L"Select Target Device (1: eMMC, 2: SDCard) (eMMC) :");
  GetHIInputInteger(&TargetMediaId);



  if (TargetMediaId > (UINT32)BOOTDEV_MIN && TargetMediaId < (UINT32)BOOTDEV_MAX)
    pFwUpdateInfo->TargetMediaID = (FW_BOOT_DEVICE)TargetMediaId;


  /* Print the final update information on the screen */

  if (pFwUpdateInfo->SourceType == SOURCE_MEMORY) {
    Print(L"BL1:0x%08X, UEFI:0x%08X and TXSW:0x%08X will be updated on %s\n",
      pFwUpdateInfo->BL1SourceAddr,
      pFwUpdateInfo->UEFISourceAddr,
      pFwUpdateInfo->TZSWSourceAddr,
      ((pFwUpdateInfo->TargetMediaID == 1)?L"eMMC":L"SD Card"));

  } else {
    Print(L"BL1:%a, UEFI:%a and TZSW:%a will be updated on %s\n",
      pFwUpdateInfo->BL1FileName,
      pFwUpdateInfo->UefiFileName,
      pFwUpdateInfo->TZSWFileName,
      ((pFwUpdateInfo->TargetMediaID == 1)?L"eMMC":L"SD Card"));
  }


  return EFI_SUCCESS;
}

VOID SetDefaultFirmwareUpdateInfo(
  OUT struct _FW_UPDATE_INFO* pFwUpdateInfo
  )
{
  if (pFwUpdateInfo == NULL)
    return;

  pFwUpdateInfo->SourceType = DEFAULT_SOURCE_TYPE;

  pFwUpdateInfo->BL1SourceAddr = DEFAULT_BL1_SOURCE_ADDRESS;
  pFwUpdateInfo->UEFISourceAddr = DEFAULT_UEFI_SOURCE_ADDRESS;
  pFwUpdateInfo->TZSWSourceAddr = DEFAULT_TZSW_SOURCE_ADDRESS;

  pFwUpdateInfo->TargetMediaID = DEFAULT_TARGET_DEVICE;

  UnicodeStrToAsciiStr(DEFAULT_BL1_SOURCE_FILE, pFwUpdateInfo->BL1FileName);
  UnicodeStrToAsciiStr(DEFAULT_UEFI_SOURCE_FILE, pFwUpdateInfo->UefiFileName);
  UnicodeStrToAsciiStr(DEFAULT_TZSW_SOURCE_FILE, pFwUpdateInfo->TZSWFileName);

}



EFI_STATUS
EditHIInputStr (
  IN OUT CHAR16  *CmdLine,
  IN     UINTN   MaxCmdLine
  )
{
  UINTN           CmdLineIndex;
  UINTN           WaitIndex;
  CHAR8           Char;
  EFI_INPUT_KEY   Key;
  EFI_STATUS      Status;

  Print (CmdLine);

  for (CmdLineIndex = StrLen (CmdLine); CmdLineIndex < MaxCmdLine; ) {
    Status = gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, &WaitIndex);
    ASSERT_EFI_ERROR (Status);

    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    ASSERT_EFI_ERROR (Status);

    // Unicode character is valid when Scancode is NUll
    if (Key.ScanCode == SCAN_NULL) {
      // Scan code is NUll, hence read Unicode character
      Char = (CHAR8)Key.UnicodeChar;
    } else {
      Char = CHAR_NULL;
    }

    if ((Char == CHAR_LINEFEED) || (Char == CHAR_CARRIAGE_RETURN) || (Char == 0x7f)) {
      CmdLine[CmdLineIndex] = '\0';
      Print (L"\n\r");

      return EFI_SUCCESS;
    } else if ((Key.UnicodeChar == L'\b') || (Key.ScanCode == SCAN_LEFT) || (Key.ScanCode == SCAN_DELETE)){
      if (CmdLineIndex != 0) {
        CmdLineIndex--;
        Print (L"\b \b");
      }
    } else if ((Key.ScanCode == SCAN_ESC) || (Char == 0x1B) || (Char == 0x0)) {
      return EFI_INVALID_PARAMETER;
    } else {
      CmdLine[CmdLineIndex++] = Key.UnicodeChar;
      Print (L"%c", Key.UnicodeChar);
    }
  }

  return EFI_SUCCESS;
}


EFI_STATUS
GetHIInputStr (
  IN OUT CHAR16  *CmdLine,
  IN     UINTN   MaxCmdLine
  )
{
  EFI_STATUS  Status;

  // For a new input just passed an empty string
  CmdLine[0] = L'\0';

  Status = EditHIInputStr (CmdLine, MaxCmdLine);

  return Status;
}

EFI_STATUS
GetHIInputInteger (
  OUT UINTN   *Integer
  )
{
  CHAR16      CmdLine[255];
  EFI_STATUS  Status;

  CmdLine[0] = '\0';
  Status = EditHIInputStr (CmdLine, 255);
  if (!EFI_ERROR(Status)) {
    *Integer = StrDecimalToUintn (CmdLine);
  }

  return Status;
}

EFI_STATUS
GetHIInputHex (
  OUT UINTN   *Integer
  )
{
  CHAR16      CmdLine[255];
  EFI_STATUS  Status;

  CmdLine[0] = '\0';
  Status = EditHIInputStr (CmdLine, 255);
  if (!EFI_ERROR(Status)) {
    *Integer = StrHexToUintn (CmdLine);
  }

  return Status;
}
