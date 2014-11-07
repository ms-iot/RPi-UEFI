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

#include "UpgradeFirmware.h"
#include "Slimpro.h"
#include "Md5.h"

#define BUFFER_MD5_STRING_LEN 32
#define BUFFER_READ_LEN 8192
#define MAX_PATH 512
#define MAX_SIZE_NUMBER_STR 5

#define TIANOCORE_FIRMWARE 0
#define SLIMPRO_FIRMWARE 1
#define MAX_FIRMWARE_LIST 2

STATIC MD5_CTX           gMd5Ctx;
STATIC UINTN             gNumFirmwares;
struct FirmwareCtx{
  UINTN Type;
  CHAR8 Md5[BUFFER_MD5_STRING_LEN + 1];
  CHAR16 Path[MAX_PATH]; /* Unicode path */
};

STATIC
EFI_STATUS
OpenFile(
  IN CHAR16             *FilePath,
  OUT SHELL_FILE_HANDLE *FileHandle
  )
{
  EFI_STATUS            Status;
  Status =  ShellOpenFileByName(FilePath, FileHandle,
                    EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
  if (EFI_ERROR(Status)) {
    ERROR("Can't open file:%s. Error code:%d\n", FilePath, Status);
    return Status;
  }
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
GetStringFromLine(
  IN CHAR16             *Buffer,
  IN OUT UINTN          *Size,
  OUT CHAR8             *AsciStr,
  IN UINTN              Len
  )
{
  BOOLEAN               HasChar = FALSE;
  INTN                  Count;
  UINTN                 Num = 0;

  for (Count = 0; Count < *Size && Num < Len - 1; Count++) {
    /* This doesn't work for big endian */
    if ((CHAR8)Buffer[Count] == ' ' || (CHAR8)Buffer[Count] == '\t'
        || (CHAR8)Buffer[Count] == '\r' || (CHAR8)Buffer[Count] == '\n') {
      if (!HasChar)
        continue;
      break;
    } else {
      if (!HasChar)
        HasChar = TRUE;
      AsciStr[Num++] = *(CHAR8*)(&Buffer[Count]);
    }
  }
  if (Count < *Size)
    *Size = Count + 1;
  if (HasChar) {
    AsciStr[Num] = '\0';
    return EFI_SUCCESS;
  }
  return EFI_INVALID_PARAMETER;
}

STATIC
EFI_STATUS
ParseFirmwareCtxFromFile (
  IN SHELL_FILE_HANDLE    FileHandle,
  OUT struct FirmwareCtx *ListCtx,
  IN UINTN                ListLen
  )
{
  EFI_STATUS              Status;
  CHAR16                  *BufferTemp;
  UINTN                   ReadLen = 0;
  UINTN                   Len;
#ifdef APPS_DEBUG
  INTN                    Count;
#endif
  BOOLEAN                 isAscii;
  CHAR8                   NumberStr[MAX_SIZE_NUMBER_STR];
  CHAR16                  *Pointer;
  CHAR8                   AsciiPath[MAX_PATH];

  BufferTemp = AllocateZeroPool(BUFFER_READ_LEN * sizeof(CHAR16));
  if (!BufferTemp) {
    ERROR("Out of Memory\n");
    Status = EFI_NOT_READY;
    goto EXIT;
  }
  gNumFirmwares = 0;
  ReadLen = BUFFER_READ_LEN * sizeof(CHAR16);
  Status = ShellFileHandleReadLine(FileHandle, BufferTemp,
                                      &ReadLen, FALSE, &isAscii);
  if (!isAscii) {
    /* don't support non Ascii file */
    Status = EFI_INVALID_PARAMETER;
    goto EXIT;
  }
  while (Status == EFI_SUCCESS && gNumFirmwares < ListLen && StrLen(BufferTemp) > 0) {
    Pointer = BufferTemp;
    Len = StrLen(Pointer);
    /* Parse type */
    Status = GetStringFromLine(Pointer, &Len, NumberStr, MAX_SIZE_NUMBER_STR);
    if (EFI_ERROR(Status)) {
      DBG("Can't parse type of image in the line:%s\n", BufferTemp);
      goto EXIT;
    }
    ListCtx[gNumFirmwares].Type = AsciiStrDecimalToUintn(NumberStr);
    DBG("Line:%s Parsed type:%d\n", BufferTemp, ListCtx[gNumFirmwares].Type);

    /* Parse MD5 */
    Pointer += Len;
    Len = StrLen(Pointer);
    Status = GetStringFromLine(Pointer, &Len, ListCtx[gNumFirmwares].Md5, BUFFER_MD5_STRING_LEN + 1);
    if (EFI_ERROR(Status)) {
      DBG("Can't parse md5 in the line:%s\n", BufferTemp);
      goto EXIT;
    }

    DBG("Line:%s Parsed md5:");
#ifdef APPS_DEBUG
    for (Count = 0; Count < BUFFER_MD5_STRING_LEN; Count++) {
      Print(L"%c", ListCtx[gNumFirmwares].Md5[Count]);
    }
    Print(L"\n");
#endif

    /* Parse File path */
    Pointer += Len;
    Len = StrLen(Pointer);
    Status = GetStringFromLine(Pointer, &Len, AsciiPath, MAX_PATH);
    if (EFI_ERROR(Status)) {
      DBG("Can't parse path in the line:%s\n", BufferTemp);
      goto EXIT;
    }
    AsciiStrToUnicodeStr(AsciiPath, ListCtx[gNumFirmwares].Path);
    DBG("Line:%s Parsed path:%s\n", BufferTemp, ListCtx[gNumFirmwares].Path);

    gNumFirmwares++;
    ReadLen = BUFFER_READ_LEN * sizeof(CHAR16);
    Status = ShellFileHandleReadLine(FileHandle, BufferTemp,
                                          &ReadLen, FALSE, &isAscii);
  }
  Status = EFI_SUCCESS;

EXIT:
  if (BufferTemp)
    FreePool(BufferTemp);
  return Status;
}
/***
  Print a usage.

  Print how to run the applcation
  .
  @param[in]  Argc    Number of argument tokens pointed to by Argv.
  @param[in]  Argv    Array of Argc pointers to command line tokens
***/
STATIC VOID PrintUsage(
  IN UINTN          Argc,
  IN CHAR16         **Argv
  )
{
  Print(L"Usage: %s <Upgrade description text file>\n", Argv[0]);
  Print(L"<Upgrade description text file> : A text file that contains information for how to upgrade\n");
}

STATIC
EFI_STATUS
CalculateMD5Firmware(
  IN OUT CHAR8                  *BufferMd5,
  IN SHELL_FILE_HANDLE          FileHandle
  )
{
  EFI_STATUS                    Status;
  CHAR8                         *BufferTemp;
  UINTN                         ReadLen = 0;
  INTN                          Count;

  BufferTemp = AllocateZeroPool(BUFFER_READ_LEN);
  if (!BufferTemp) {
    ERROR("Out of Memory\n");
    Status = EFI_NOT_READY;
    goto EXIT;
  }

  MD5Init (&gMd5Ctx);
  ReadLen = BUFFER_READ_LEN;
  Status = ShellReadFile(FileHandle, &ReadLen, BufferTemp);
  while (Status == EFI_SUCCESS && ReadLen > 0) {
    MD5Update(&gMd5Ctx, (VOID *)BufferTemp, ReadLen);
    if (ReadLen != BUFFER_READ_LEN) {
      /* We are in the end of file */
      break;
    }
    ReadLen = BUFFER_READ_LEN;
    Status = ShellReadFile(FileHandle, &ReadLen, BufferTemp);
  }

  MD5Final(&gMd5Ctx, (UINT8*) BufferMd5);

  /* Output of BufferMd5 is 128bit(16 bytes) so we need to convert it to 32 chars string */
  for (Count = 0; Count < 16; Count++) {
    AsciiSPrint(BufferTemp + Count * 2, 3, "%02x", (UINT8)BufferMd5[Count]);
  }

  CopyMem(BufferMd5, BufferTemp, BUFFER_MD5_STRING_LEN);
  BufferMd5[BUFFER_MD5_STRING_LEN] = '\0';

  Status = EFI_SUCCESS;

EXIT:
  if (BufferTemp)
    FreePool(BufferTemp);

  return Status;
}

STATIC
BOOLEAN
CompareMd5(
  IN CHAR8                            *BufferMd5Source,
  IN CHAR8                            *BufferMd5Dest
  )
{
  if (AsciiStriCmp(BufferMd5Source, BufferMd5Dest))
    return FALSE;
  return TRUE;
}

STATIC
EFI_STATUS
WriteFirmware(
  IN SHELL_FILE_HANDLE                FileHandle
  )
{
  EFI_STATUS Status;
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *EfiDevicePathFromTextProtocol;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePathInstance;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePathInstanceNext;
  EFI_BLOCK_IO_PROTOCOL               *BlockIo = NULL;
  EFI_BLOCK_IO_PROTOCOL               *BlockIoNext = NULL;
  EFI_BLOCK_IO_PROTOCOL               *PointerBlockIo;
  EFI_HANDLE                          BlockIoHandle = NULL;
  EFI_HANDLE                          BlockIoHandleNext = NULL;
  UINT8                               *Buffer;
  UINTN                               BufferSize;
  UINTN                               ReadLen;
  EFI_LBA                             Lba;
  UINT64                              FileSize;

  Status = gBS->LocateProtocol (&gEfiDevicePathFromTextProtocolGuid, NULL, (VOID **)&EfiDevicePathFromTextProtocol);
  if (EFI_ERROR(Status)) {
    DBG("Failed to locate EfiDevicePathFromTextProtocol\n");
    return Status;
  }

  DevicePathInstance = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath ((CHAR16 *) PcdGetPtr(FirmwareBlockDevicePath));
  if (!DevicePathInstance) {
    DBG("Failed to load device path:%s\n", (CHAR16 *) PcdGetPtr(FirmwareBlockDevicePath));
    return EFI_NOT_FOUND;
  }

  DevicePathInstanceNext = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath ((CHAR16 *) PcdGetPtr(FirmwareBlockDevicePathNext));
  if (!DevicePathInstanceNext) {
    DBG("Failed to load device path:%s\n", (CHAR16 *) PcdGetPtr(FirmwareBlockDevicePathNext));
    return EFI_NOT_FOUND;
  }

  if (gBS->LocateDevicePath(&gEfiBlockIoProtocolGuid, &DevicePathInstance, &BlockIoHandle) == EFI_NOT_FOUND) {
    DBG("Failed to locate block IO protocol Guid\n");
    DBG("Device path:%s\n", (CHAR16 *) PcdGetPtr(FirmwareBlockDevicePath));
    return EFI_NOT_FOUND;
  }

  Status = gBS->OpenProtocol(BlockIoHandle, &gEfiBlockIoProtocolGuid, (VOID**)&BlockIo, gImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
  if (EFI_ERROR(Status)) {
    DBG("Failed to open block io protocol\n");
    return Status;
  }

  ShellGetFileSize(FileHandle, &FileSize);
  DBG("File of firmware:%ll\n", FileSize);
  if ((UINT64)((BlockIo->Media->LastBlock + 1) * BlockIo->Media->BlockSize) < FileSize) {
    /* we need next block IO in case firmware span multi regions */
    DBG("Need next block IO\n");
    if (gBS->LocateDevicePath(&gEfiBlockIoProtocolGuid, &DevicePathInstanceNext, &BlockIoHandleNext) == EFI_NOT_FOUND) {
      DBG("Failed to locate block IO protocol Guid\n");
      DBG("Device path:%s\n", (CHAR16 *) PcdGetPtr(FirmwareBlockDevicePathNext));

      gBS->CloseProtocol(BlockIoHandle, &gEfiBlockIoProtocolGuid, gImageHandle, NULL);
      return EFI_NOT_FOUND;
    }

    Status = gBS->OpenProtocol(BlockIoHandleNext, &gEfiBlockIoProtocolGuid, (VOID**)&BlockIoNext, gImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
      DBG("Failed to open block io protocol\n");

      gBS->CloseProtocol(BlockIoHandle, &gEfiBlockIoProtocolGuid, gImageHandle, NULL);
      return Status;
    }
  }
  /* One block for each write */
  if (BlockIoNext && BlockIoNext->Media->BlockSize > BlockIo->Media->BlockSize)
    Buffer     = AllocateZeroPool(BlockIoNext->Media->BlockSize);
  else
    Buffer     = AllocateZeroPool(BlockIo->Media->BlockSize);

  /* reset file position to zero */
  ShellSetFilePosition(FileHandle, 0);

  Lba = 0;
  PointerBlockIo = BlockIo;
  BufferSize = BlockIo->Media->BlockSize;
  ReadLen = BufferSize;
  Status = ShellReadFile(FileHandle, &ReadLen, Buffer);

  INFO("Writing the firmware. Please wait\n");
  while (Status == EFI_SUCCESS && ReadLen > 0) {
    Status = PointerBlockIo->WriteBlocks(PointerBlockIo, PointerBlockIo->Media->MediaId, Lba, ReadLen, Buffer);
    if (EFI_ERROR(Status)) {
      DBG("Failed to write block: %d\n", Lba);
      goto EXIT;
    }
    Print(L"#");
    Lba++;
    if (ReadLen != BufferSize) {
      /* We are in the end of file */
      break;
    }
    if (Lba > PointerBlockIo->Media->LastBlock) {
      DBG("Switch to next block io\n");
      BufferSize = BlockIoNext->Media->BlockSize;
      PointerBlockIo = BlockIoNext;
      Lba = 0;
    }
    ReadLen = BufferSize;
    Status = ShellReadFile(FileHandle, &ReadLen, Buffer);
  }
  INFO("Upgraded firmware SUCCESSFULLY\n");

EXIT:
  if (Buffer != NULL) {
    FreePool(Buffer);
  }
  gBS->CloseProtocol(BlockIoHandle, &gEfiBlockIoProtocolGuid, gImageHandle, NULL);
  if (BlockIoHandleNext)
    gBS->CloseProtocol(BlockIoHandleNext, &gEfiBlockIoProtocolGuid, gImageHandle, NULL);

  return Status;
}

STATIC
EFI_STATUS
WriteSlimproFirmware(
  IN SHELL_FILE_HANDLE      FileHandle
  )
{
  EFI_STATUS                Status;
  UINT8                     *Buffer = NULL;
  VOID                      *Pointer;
  UINT64                    BufferSize;
  UINT64                    ReadLen;

  Status = ShellGetFileSize(FileHandle, &BufferSize);
  if (EFI_ERROR(Status)) {
    ERROR("Failed to read slimpro firmware\n");
    goto EXIT;
  }
  Buffer = AllocateZeroPool(BufferSize);
  if (!Buffer) {
    ERROR("Out of memory\n");
    goto EXIT;
  }
  /* reset file position to zero */
  ShellSetFilePosition(FileHandle, 0);

  ReadLen = BUFFER_READ_LEN;
  Pointer = Buffer;
  Status = ShellReadFile(FileHandle, &ReadLen, Pointer);
  while (Status == EFI_SUCCESS && ReadLen > 0) {
    Pointer += ReadLen;
    if (ReadLen < BUFFER_READ_LEN)
      break;
    ReadLen = BUFFER_READ_LEN;
    Status = ShellReadFile(FileHandle, &ReadLen, Pointer);
  }
  if (((UINT64)Pointer - (UINT64)Buffer) != BufferSize) {
    DBG("Can't read the whole of slimpro firmware\n");
    goto EXIT;
  }
  Status = EepromWrite (0, (CHAR8 *)Buffer, (UINT32) BufferSize);
  if (EFI_ERROR(Status)) {
    DBG("Write slimpro FAILED\n");
    goto EXIT;
  }

  INFO("Upgraded slimpro firmware SUCCESSFULLY\n");

EXIT:
  if (Buffer != NULL) {
    FreePool(Buffer);
  }
  return Status;
}

/***
  Print a welcoming message.

  Establishes the main structure of the application.
  @param[in]  Argc    Number of argument tokens pointed to by Argv.
  @param[in]  Argv    Array of Argc pointers to command line tokens

  @retval  0         The application exited normally.
  @retval  Other     An error occurred.
***/
INTN
EFIAPI
ShellAppMain (
  IN UINTN            Argc,
  IN CHAR16           **Argv
  )
{
  EFI_STATUS          Status;
  CHAR8               BufferMd5Calculated[BUFFER_MD5_STRING_LEN + 1];
  SHELL_FILE_HANDLE   FileHandle = 0;
  struct FirmwareCtx  *ListCtx = NULL;
  INTN                Count;
#ifdef APPS_DEBUG
  INTN                Count1;
#endif

  Status = EFI_SUCCESS;

  /* First argument must be FW tianocore_mustang.fd
   * Second argument must be text file contain checksum of the firmware
   */
  if (Argc != 2) {
    Status = OpenFile(L"apm_upgrade.cmd", &FileHandle);
    if (EFI_ERROR(Status)) {
      PrintUsage(Argc, Argv);
      goto EXIT;
    }
  } else {
    Status = OpenFile(Argv[1], &FileHandle);
    if (EFI_ERROR(Status)) {
      ERROR("Failed to open file:%s\n", Argv[1]);
      goto EXIT;
    }
  }

  ListCtx = AllocateZeroPool (sizeof(struct FirmwareCtx) * MAX_FIRMWARE_LIST);
  if (!ListCtx) {
    ERROR("Out of memory\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto EXIT;
  }

  Status = ParseFirmwareCtxFromFile(FileHandle, ListCtx, MAX_FIRMWARE_LIST);
  if (EFI_ERROR(Status)) {
    ERROR("Can't get content from file:%s\n", Argv[1]);
    goto EXIT;
  }

  for (Count = 0; Count < gNumFirmwares; Count++) {
    /* close previous opened file */
    ShellCloseFile (&FileHandle);
    FileHandle = 0;

    Status = OpenFile(ListCtx[Count].Path, &FileHandle);
    if (EFI_ERROR(Status)) {
      ERROR("Failed to open file:%s\n", ListCtx[Count].Path);
      goto EXIT;
    }
    Status = CalculateMD5Firmware(BufferMd5Calculated, FileHandle);
    if (EFI_ERROR(Status)) {
      ERROR("Failed to calculate MD5 for file:%s\n",
                  ListCtx[Count].Path);
      goto EXIT;
    }
#ifdef APPS_DEBUG
    DBG("MD5 calculated:");
    for (Count1 = 0; Count1 < BUFFER_MD5_STRING_LEN; Count1++) {
      AsciiPrint("%c", BufferMd5Calculated[Count1]);
    }
    Print(L"\n");
#endif
    if (CompareMd5(BufferMd5Calculated, ListCtx[Count].Md5)) {
      DBG("Md5checksum matched for file:%s\n", ListCtx[Count].Path);
    } else {
      ERROR("Checksum is not matched for file:%s\n", ListCtx[Count].Path);
      goto EXIT;
    }

    if (ListCtx[Count].Type == TIANOCORE_FIRMWARE) {
      INFO("Writing tianocore firmware from file:%s\n", ListCtx[Count].Path);
      Status = WriteFirmware(FileHandle);
      if (EFI_ERROR(Status)) {
        ERROR("Failed to write firmware from file:%s\n", ListCtx[Count].Path);
        goto EXIT;
      }
    }
    if (ListCtx[Count].Type == SLIMPRO_FIRMWARE) {
      INFO("Writing slimpro firmware from file:%s\n", ListCtx[Count].Path);
      Status = WriteSlimproFirmware(FileHandle);
      if (EFI_ERROR(Status)) {
        ERROR("Failed to write slimpro firmware from file:%s\n", ListCtx[Count].Path);
        goto EXIT;
      }
    }
  }

EXIT:
  if (FileHandle) {
    ShellCloseFile (&FileHandle);
  }

  return (INTN)Status;
}
