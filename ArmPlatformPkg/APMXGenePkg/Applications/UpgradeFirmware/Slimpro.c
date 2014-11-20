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

#include "Slimpro.h"
#include <Library/SlimproLib.h>

#define EEPROM_PAGE_SIZE  (1 << PcdGet32(EepromPageWriteBits))
#define EEPROM_PAGE_OFFSET(x) ((x) & (EEPROM_PAGE_SIZE - 1))

EFI_STATUS
EFIAPI
EepromRead (
  UINTN Offset,
  CHAR8 *Buffer,
  UINT32 Size
  )
{
  UINTN DevAddr;
  UINTN End = Offset + Size;
  UINTN BlkOff;
  UINT32 aLen, Len, MaxLen;
  CHAR8 Addr[3];
  EFI_STATUS Ret;

  DevAddr = PcdGet32(EepromAddr);
  Ret = EFI_SUCCESS;

  while (Offset < End) {
    BlkOff = Offset & 0xFF;  /* block Offset */
    if (PcdGet32(EepromAddrLen) == 1) {
      Addr[0] = Offset >> 8;  /* block number */
      Addr[1] = BlkOff;  /* block Offset */
      aLen  = 2;
    } else {
      Addr[0] = Offset >> 16; /* block number */
      Addr[1] = Offset >>  8; /* upper Address octet */
      Addr[2] = BlkOff;  /* lower Address octet */
      aLen  = 3;
    }

    Addr[0] |= DevAddr;    /* insert device Address */

    Len = End - Offset;

    if (PcdGet32(EepromPageWriteBits) > 0)
      MaxLen = EEPROM_PAGE_SIZE - EEPROM_PAGE_OFFSET(BlkOff);
    else
      MaxLen = 0x100 - BlkOff;

    if (Len > MaxLen)
      Len = MaxLen;

    if (I2c_Read (Addr[0], Offset, aLen-1, (UINT8*) Buffer, Len) != 0)
      Ret = EFI_DEVICE_ERROR;

    Buffer += Len;
    Offset += Len;
  }

  return Ret;
}

EFI_STATUS
EFIAPI
EepromWrite (
  UINTN Offset,
  CHAR8 *Buffer,
  UINT32 Size
  )
{
  UINTN DevAddr;
  UINTN End = Offset + Size;
  UINTN BlkOff;
  UINT32 Crc_s,Crc_d;
  CHAR8 *CrcBuffer = NULL;
  CHAR8* BufferSrc = Buffer;
  UINTN OffsetSrc = Offset;
  UINT32 aLen, Len, MaxLen;
  CHAR8 Addr[3];
  EFI_STATUS Ret;
  EFI_TPL         OriginalTPL;

  DevAddr = PcdGet32(EepromAddr);

  // Raise TPL to TPL_HIGH to stop anyone from interrupting us.
  OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);

  Ret = EFI_SUCCESS;

  INFO("Slimpro updating.... ");

  XGeneBMCStart(FALSE);

  while (Offset < End) {

    BlkOff = Offset & 0xFF;  /* block Offset */
    if (PcdGet32(EepromAddrLen) == 1) {
      Addr[0] = Offset >> 8;  /* block number */
      Addr[1] = BlkOff;  /* block Offset */
      aLen  = 2;
    } else {
      Addr[0] = Offset >> 16; /* block number */
      Addr[1] = Offset >>  8; /* upper Address octet */
      Addr[2] = BlkOff;  /* lower Address octet */
      aLen  = 3;
    }

    Addr[0] |= DevAddr;    /* insert device Address */

    Len = End - Offset;

    if (PcdGet32(EepromPageWriteBits) > 0)
      MaxLen = EEPROM_PAGE_SIZE - EEPROM_PAGE_OFFSET(BlkOff);
    else
      MaxLen = 0x100 - BlkOff;

    if (Len > MaxLen)
      Len = MaxLen;

    Crc_s = Crc_d = 0;
    gBS->CalculateCrc32 ((VOID *)Buffer, Len, &Crc_s);
    if (I2c_Write (Addr[0], Offset, aLen-1, (UINT8*) Buffer, Len) != 0) {
        Ret = EFI_DEVICE_ERROR;
        goto EXIT;
    }
    Print(L"#");

    Buffer += Len;
    Offset += Len;
  }
  Print(L"\n");

  if (!EFI_ERROR(Ret)) {
    INFO("Slimpro Validating.... ");
    Crc_s = Crc_d;
    gBS->CalculateCrc32 ((VOID *)BufferSrc, Size, &Crc_s);
    DBG("Slimpro Source CRC32:0x%lx ", Crc_s);
    CrcBuffer = AllocateZeroPool (Size);
    if (!CrcBuffer) {
      ERROR("Out of resources\n");
      return EFI_INVALID_PARAMETER;
    }
    Ret = EepromRead(OffsetSrc, CrcBuffer, Size);
    if (EFI_ERROR(Ret)){
      DBG("Failed to read slimpro firmware\n");
      goto EXIT;
    }
    gBS->CalculateCrc32((VOID *)CrcBuffer, Size, &Crc_d);
    DBG("Destination CRC32:0x%lx\n", Crc_d);
    if (Crc_s == Crc_d) {
      INFO("Update slimpro firmware successful\n");
    }
    else {
      ERROR("Update slimpro firmware fail\n");
      Ret = EFI_DEVICE_ERROR;
    }
  }
EXIT:
  if (CrcBuffer)
    FreePool(CrcBuffer);

  // Interruptions can resume.
  gBS->RestoreTPL (OriginalTPL);

  return Ret;
}

EFI_STATUS
EFIAPI
EepromInit (VOID)
{
  return I2c_Probe(PcdGet32(EepromAddr));
}
