/**
 *  SPI flash interface
 *  
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#include <Library/SPIFlash.h>
#include <Library/UefiLib.h>

//#define SPI_FLASH_DBG

#ifdef SPI_FLASH_DBG
#define DBG(arg...) DEBUG ((EFI_D_BLKIO,## arg))
#else
#define DBG(arg...)
#endif

EFI_STATUS Spi_Flash_Cmd(struct SPI_SLAVE *Spi, UINT8 Cmd, VOID *Response, UINT32 Len)
{
  UINT32 Flags = SPI_XFER_BEGIN;
  EFI_STATUS Ret;

  if (Len == 0)
    Flags |= SPI_XFER_END;

  Ret = Spi_Xfer(Spi, 8, &Cmd, NULL, Flags);
  if (EFI_ERROR(Ret)) {
    DBG("SF: Failed to send command %02x: %d\n", Cmd, Ret);
    return Ret;
  }

  if (Len) {
    Ret = Spi_Xfer(Spi, Len * 8, NULL, Response, SPI_XFER_END);
    if (EFI_ERROR(Ret))
      DBG("SF: Failed to read Response (%zu bytes): %d\n",
          Len, Ret);
  }

  return Ret;
}

EFI_STATUS Spi_Flash_Cmd_Read(struct SPI_SLAVE *Spi, const UINT8 *Cmd,
    UINT32 Cmd_Len, VOID *Data, UINT32 Data_Len)
{
  UINT32 Flags = SPI_XFER_BEGIN;
  EFI_STATUS Ret;

  if (Data_Len == 0)
    Flags |= SPI_XFER_END;

  Ret = Spi_Xfer(Spi, Cmd_Len * 8, Cmd, NULL, Flags);
  if (EFI_ERROR(Ret)) {
    DBG("SF: Failed to send read command (%zu bytes): %d\n",
        Cmd_Len, Ret);
  } else if (Data_Len != 0) {
    Ret = Spi_Xfer(Spi, Data_Len * 8, NULL, Data, SPI_XFER_END);
    if (EFI_ERROR(Ret))
      DBG("SF: Failed to read %zu bytes of Data: %d\n",
          Data_Len, Ret);
  }

  return Ret;
}

EFI_STATUS Spi_Flash_Cmd_Write(struct SPI_SLAVE *Spi, const UINT8 *Cmd, UINT32 Cmd_Len,
    const VOID *Data, UINT32 Data_Len)
{
  UINT32 Flags = SPI_XFER_BEGIN;
  EFI_STATUS Ret;

  if (Data_Len == 0)
    Flags |= SPI_XFER_END;

  Ret = Spi_Xfer(Spi, Cmd_Len * 8, Cmd, NULL, Flags);
  if (EFI_ERROR(Ret)) {
    DBG("SF: Failed to send read command (%zu bytes): %d\n",
        Cmd_Len, Ret);
  } else if (Data_Len != 0) {
    Ret = Spi_Xfer(Spi, Data_Len * 8, Data, NULL, SPI_XFER_END);
    if (EFI_ERROR(Ret))
      DBG("SF: Failed to read %zu bytes of Data: %d\n",
          Data_Len, Ret);
  }

  return Ret;
}


EFI_STATUS Spi_Flash_Read_Common(struct SPI_FLASH *Flash, const UINT8 *Cmd,
    UINT32 Cmd_Len, VOID *Data, UINT32 Data_Len)
{
  struct SPI_SLAVE *Spi = &(Flash->Spi);
  EFI_STATUS Ret;
  Spi_Claim_Bus(Spi);
  Ret = Spi_Flash_Cmd_Read(Spi, Cmd, Cmd_Len, Data, Data_Len);
  Spi_Release_Bus(Spi);

  return Ret;
}

struct SPI_FLASH *Spi_Flash_Probe(struct SPI_FLASH *Flash, UINTN Bus, UINTN Cs,
    UINTN Max_Hz, UINTN Spi_Mode)
{
  EFI_STATUS Ret;
  UINT8 Cmd[2];
  UINT8 Idcode[5];
  DBG("SF: Spi_Flash_Probe: Bus:%d CS:%d Max_Hz:%d Spi_Mode:%d\n",
        Bus, Cs, Max_Hz, Spi_Mode);
  if (!Spi_Setup_Slave(&Flash->Spi, Bus, Cs, Max_Hz, Spi_Mode)) {
    DBG("SF: Failed to set up Slave\n");
    return NULL;
  }
  Ret = Spi_Claim_Bus(&(Flash->Spi));
  if (EFI_ERROR(Ret)) {
    DBG("SF: Failed to claim SPI Bus: %d\n", Ret);
    goto ERR_CLAIM_BUS;
  }
  /* Attemp1: Read the ID codes */
  Ret = Spi_Flash_Cmd(&(Flash->Spi), CMD_READ_ID, &Idcode, sizeof(Idcode));
  if (EFI_ERROR(Ret))
    goto ERR_READ_ID;

  DBG("SF: Got Idcode %02x %02x %02x %02x %02x\n", Idcode[0],
      Idcode[1], Idcode[2], Idcode[3], Idcode[4]);
  
  Ret = EFI_SUCCESS;
  switch (Idcode[0]) {
#ifdef CONFIG_SPI_FLASH_STMICRO
  case 0x20:
    if (!Spi_Flash_Probe_Stmicro(Flash, Idcode))
      Ret = EFI_INVALID_PARAMETER;
    break;
#endif
  default:
    DBG("SF: Unsupported manufacturer %02X\n", Idcode[0]);
    Ret = EFI_INVALID_PARAMETER;
    break;
  }

  if (!EFI_ERROR(Ret))
    goto SPI_FLASH_PROBE_DONE;

  /* Attempt2: Read the ID codes */
  Cmd[0] = CMD_READ_ID;
  Cmd[1] = 0x0;
  Ret = Spi_Flash_Cmd_Read(&(Flash->Spi), Cmd, 2, &Idcode, sizeof(Idcode));
  if (EFI_ERROR(Ret))
    goto ERR_READ_ID;

  DBG("SF: Got Idcode %02x %02x %02x %02x %02x\n", Idcode[0],
      Idcode[1], Idcode[2], Idcode[3], Idcode[4]);

  switch (Idcode[0]) {
#ifdef CONFIG_SPI_FLASH_MICRON
  case 0x2C:
    Ret = Spi_Flash_Probe_Micron(Flash, Idcode);
    break;
#endif
  default:
    DBG("SF: Unsupported manufacturer %02X\n", Idcode[0]);
    Ret = EFI_INVALID_PARAMETER;
    break;
  }

  if (EFI_ERROR(Ret))
    goto ERR_MANUFACTURER_PROBE;

SPI_FLASH_PROBE_DONE:
  Spi_Release_Bus(&(Flash->Spi));

  return Flash;

ERR_MANUFACTURER_PROBE:
ERR_READ_ID:
  Spi_Release_Bus(&(Flash->Spi));
ERR_CLAIM_BUS:
  return NULL;
}
