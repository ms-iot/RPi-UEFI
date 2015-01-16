/** @file
 *  
 *  ST SPI flash STMicroFlash.c 
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

#include <Library/SPI.h>
#include <Library/SPIFlash.h>
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>

//#define SPI_STMICRO_DBG

#ifdef SPI_STMICRO_DBG
#define DBG(arg...) DEBUG ((EFI_D_BLKIO,## arg))
#else
#define DBG(arg...)
#endif

#define INFO(arg...) DEBUG ((EFI_D_INFO,## arg))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
#endif

#include <Library/PcdLib.h>

/* M25Pxx-specific commands */
#define CMD_M25PXX_WREN    0x06  /* Write Enable */
#define CMD_M25PXX_WRDI    0x04  /* Write Disable */
#define CMD_M25PXX_RDSR    0x05  /* Read Status Register */
#define CMD_M25PXX_WRSR    0x01  /* Write Status Register */
#define CMD_M25PXX_READ    0x03  /* Read Data Bytes */
#define CMD_M25PXX_FAST_READ  0x0b  /* Read Data Bytes at Higher Speed */
#define CMD_M25PXX_PP    0x02  /* Page Program */
#define CMD_M25PXX_SE    0xd8  /* Sector Erase */
#define CMD_M25PXX_BE    0xc7  /* Bulk Erase */
#define CMD_M25PXX_DP    0xb9  /* Deep Power-down */
#define CMD_M25PXX_RES    0xab  /* Release from DP, and Read Signature */
#define CMD_M25PXX_RFSR   0x70
#define CMD_M25PXX_4BYTE_ADDR_EN 0xB7 /* Enable 4-byte address mode */
#define STM_ID_M25P16    0x15
#define STM_ID_M25P20    0x12
#define STM_ID_M25P32    0x16
#define STM_ID_M25P40    0x13
#define STM_ID_M25P64    0x17
#define STM_ID_M25P80    0x14
#define STM_ID_M25P128    0x18
#define STM_ID_N25Q256    0x19
#define STM_ID_N25Q128          0x18
#define STMICRO_SR_WIP    (1 << 0)  /* Write-in-Progress */
#define STMICRO_RFSR_PE        (1<<7)

#define STMICRO_MAX_NAME_SIZE 10

struct STMICRO_SPI_FLASH_PARAMS {
  UINT8 Idcode1;
  UINT16 Page_Size;
  UINT16 Pages_Per_Sector;
  UINT16 Nr_Sectors;
  CHAR8 Name[STMICRO_MAX_NAME_SIZE];
};

struct STMICRO_SPI_FLASH_PARAMS Stmicro_Spi_Flash_Table[] = {
  {
    .Idcode1 = STM_ID_M25P16,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 32,
    .Name = "M25P16",
  },
  {
    .Idcode1 = STM_ID_M25P20,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 4,
    .Name = "M25P20",
  },
  {
    .Idcode1 = STM_ID_M25P32,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 64,
    .Name = "M25P32",
  },
  {
    .Idcode1 = STM_ID_M25P40,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 8,
    .Name = "M25P40",
  },
  {
    .Idcode1 = STM_ID_M25P64,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 128,
    .Name = "M25P64",
  },
  {
    .Idcode1 = STM_ID_M25P80,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 16,
    .Name = "M25P80",
  },
  {
    .Idcode1 = STM_ID_M25P128,
    .Page_Size = 256,
    .Pages_Per_Sector = 1024,
    .Nr_Sectors = 64,
    .Name = "M25P128",
  },
    {
    .Idcode1 = STM_ID_N25Q128,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors = 256 , 
    .Name="N25Q128" ,
  },
  {
    .Idcode1 = STM_ID_N25Q256,
    .Page_Size = 256,
    .Pages_Per_Sector = 256,
    .Nr_Sectors =512 ,
    .Name="N25Q256" ,
  },
};

EFI_STATUS Stmicro_Wait_Ready(struct SPI_FLASH *Flash, UINT32 Action, UINT32 Timeout)
{
  struct SPI_SLAVE *Spi = &(Flash->Spi);
  UINT32 Timebase =  0x200000;
  EFI_STATUS Ret;
  UINT8 Cmd;
  UINT8 Status;
  UINT8 Status_Mask;
  UINT8 Polling_Logic;
  if(Action ==0 ) // write
  {
    Polling_Logic= 0;
    Status_Mask= STMICRO_SR_WIP ;
    Cmd= CMD_M25PXX_RDSR;
  }
  else if (Action==1) //erase
  {
    Polling_Logic= STMICRO_RFSR_PE;
    Status_Mask= STMICRO_RFSR_PE;
    Cmd= CMD_M25PXX_RFSR;
  }
  else
  {
    Polling_Logic= 0;
    Status_Mask= STMICRO_SR_WIP ;
    Cmd= CMD_M25PXX_RDSR;
  }

  do {
    Ret = Spi_Flash_Cmd(Spi, Cmd, &Status, 1);
    if (EFI_ERROR(Ret))
      return EFI_DEVICE_ERROR;

    if ((Status & Status_Mask) == Polling_Logic)
      break;
    Timebase--;
    MicroSecondDelay(1000);
  } while (Timebase > 0);

  if ((Status & Status_Mask) == Polling_Logic)
    return EFI_SUCCESS;

  /* Timed out */
  return EFI_TIMEOUT;
}


INTN Stmicro_Read_Fast(struct SPI_FLASH *Flash,
           UINT32 Offset, UINT32 Len, VOID *Buf)
{
  UINT8 Cmd[5];
  EFI_STATUS Ret;
  UINT32 Actual;
  UINT32 Chunk_Len;
  UINT32 From;
  struct STMICRO_SPI_FLASH_PARAMS *Params = (struct STMICRO_SPI_FLASH_PARAMS *)(Flash->Params);
  UINT32 Read_Limit = Params->Page_Size * Params->Pages_Per_Sector;

  DBG("SF: Read flash offset: 0x%x Len:0x%x\n", Offset, Len);

  From = Offset;
  /* Assume Offset is align to Page_Size */
  for (Actual = 0; Actual < Len; Actual += Chunk_Len) {
    Chunk_Len = MIN(Len - Actual, Read_Limit);

    Cmd[0] = CMD_READ_ARRAY_SLOW;
    Cmd[1] = From >> 24;
    Cmd[2] = From >> 16;
    Cmd[3] = From >> 8;
    Cmd[4] = From;

    DBG("SF: Spi_Flash_Read_Common: Chuck_Len:0x%x \n", Chunk_Len);
    Ret = Spi_Flash_Read_Common(Flash, Cmd, sizeof(Cmd), Buf + Actual, Chunk_Len);
    if (EFI_ERROR(Ret)) {
      DBG("SF: Read flash failed\n");
      return Ret;
    }

    From += Chunk_Len;
  }
  if (!EFI_ERROR(Ret)) {
    DBG("Read Successuflly %d @ offset %d \n", Len, Offset);
  }

  return EFI_SUCCESS;
}

INTN Stmicro_Write(struct SPI_FLASH *Flash,
       UINT32 Offset, UINT32 Len, const void *Buf)
{
  UINT32 Page_Size;
  UINT32 Chunk_Len;
  UINT32 Actual;
  UINT32 From;
  EFI_STATUS Ret;
  UINT8 Cmd[5];

  Page_Size = ((struct STMICRO_SPI_FLASH_PARAMS *)(Flash->Params))->Page_Size;

  Ret = Spi_Claim_Bus(&(Flash->Spi));
  if (EFI_ERROR(Ret)) {
    DBG("SF: Unable to claim SPI bus\n");
    return Ret;
  }

  Ret = EFI_SUCCESS;
  From = Offset;
  /* Assume Offset is align to Page_Size */
  for (Actual = 0; Actual < Len; Actual += Chunk_Len) {
    Chunk_Len = MIN(Len - Actual, Page_Size);
    Cmd[0] = CMD_M25PXX_PP;
    Cmd[1] = From >> 24;
    Cmd[2] = From >> 16;
    Cmd[3] = From >> 8;
    Cmd[4] = From;

    DBG("PP: 0x%p => Cmd = { 0x%02x 0x%02x%02x%02x%02x } Chunk_Len = %d\n",
         Buf + Actual, Cmd[0], Cmd[1], Cmd[2], Cmd[3], Cmd[4], Chunk_Len);

    Ret = Spi_Flash_Cmd(&(Flash->Spi), CMD_M25PXX_WREN, NULL, 0);
    if (EFI_ERROR(Ret)) {
      DBG("SF: Enabling Write failed\n");
      break;
    }

    Ret = Spi_Flash_Cmd_Write(&(Flash->Spi), Cmd, sizeof(Cmd),
            Buf + Actual, Chunk_Len);
    if (EFI_ERROR(Ret)) {
      DBG("SF: STMicro Page Program failed\n");
      break;
    }

    Ret = Stmicro_Wait_Ready(Flash, 0, SPI_FLASH_PROG_TIMEOUT);
    if (EFI_ERROR(Ret)) {
      DBG("SF: STMicro page programming timed out\n");
      break;
    }

    From += Chunk_Len;
  }

  if (!EFI_ERROR(Ret))
    DBG("SF: STMicro: Successfully programmed %lu bytes @ 0x%x\n",
        Len, Offset);

  Spi_Release_Bus(&(Flash->Spi));
  return Ret;
}

INTN Stmicro_Erase(struct SPI_FLASH *Flash, UINT32 Offset, UINT32 Len)
{
  UINT32 Sector_Size;
  UINT32 Actual;
  EFI_STATUS Ret;
  UINT8 Cmd[5];
  UINT32 From;

  struct STMICRO_SPI_FLASH_PARAMS *Params = (struct STMICRO_SPI_FLASH_PARAMS *)(Flash->Params);
  /*
   * This function currently uses sector erase only.
   * probably speed things up by using bulk erase
   * when possible.
   */

  Sector_Size = Params->Page_Size * Params->Pages_Per_Sector;

  if(Offset %Sector_Size)
  {
    INFO("erase offset not multiple of sector_size \n");
    Offset=(Offset/Sector_Size) * Sector_Size;
  }
  if(Len %Sector_Size)
  {
    INFO("erase length not a multiple of sector size \n");
    Len+=Sector_Size;
  }

  Len /= Sector_Size;
  Len = (Len == 0) ? 1 : Len;
  Cmd[0] = CMD_M25PXX_SE;
  Cmd[2] = 0x00;
  Cmd[3] = 0x00;

  Ret = Spi_Claim_Bus(&(Flash->Spi));
  if (EFI_ERROR(Ret)) {
    DBG("SF: Unable to claim SPI bus\n");
    return Ret;
  }

  Ret = EFI_SUCCESS;
  for (Actual = 0; Actual < Len; Actual++) {
    From = Offset + Sector_Size * Actual;
    Cmd[0] = CMD_M25PXX_SE;
    Cmd[1] = From >> 24;
    Cmd[2] = From >> 16;
    Cmd[3] = From >> 8;
    Cmd[4] = From;

    Ret = Spi_Flash_Cmd(&(Flash->Spi), CMD_M25PXX_WREN, NULL, 0);
    if (EFI_ERROR(Ret)) {
      INFO("SF: Enabling Write failed\n");
      break;
    }

    Ret = Spi_Flash_Cmd_Write(&(Flash->Spi), Cmd, sizeof(Cmd), NULL, 0);
    if (EFI_ERROR(Ret)) {
      INFO("SF: STMicro page erase failed\n");
      break;
    }

    Ret = Stmicro_Wait_Ready(Flash, 1, SPI_FLASH_PAGE_ERASE_TIMEOUT);
    if (EFI_ERROR(Ret)) {
      INFO("SF: STMicro page erase timed out\n");
      break;
    }
  }

  if (!EFI_ERROR(Ret))
    DBG("SF: STMicro: Successfully erased %u bytes @ 0x%x\n",
        Len * Sector_Size, Offset);

  Spi_Release_Bus(&(Flash->Spi));
  return Ret;
}

struct SPI_FLASH *
Spi_Flash_Probe_Stmicro(struct SPI_FLASH *Flash, UINT8 * Idcode)
{
  struct STMICRO_SPI_FLASH_PARAMS *Params;
  UINTN i;

  Params = (struct STMICRO_SPI_FLASH_PARAMS *)AllocateRuntimeZeroPool(sizeof(Stmicro_Spi_Flash_Table[0]));
  ASSERT(Params);

  for (i = 0; i < ARRAY_SIZE(Stmicro_Spi_Flash_Table); i++) {
    CopyMem((VOID *)Params, (VOID *)&Stmicro_Spi_Flash_Table[i], sizeof(Stmicro_Spi_Flash_Table[i]));
    if (Params->Idcode1 == Idcode[2]) {
      break;
    }
  }

  if (i == ARRAY_SIZE(Stmicro_Spi_Flash_Table)) {
    DBG("SF: Unsupported STMicro ID %02x\n", Idcode[1]);
    return NULL;
  }

  Flash->Name = Params->Name;

  Flash->Write = Stmicro_Write;
  Flash->Erase = Stmicro_Erase;
  Flash->Read = Stmicro_Read_Fast;
  Flash->Size = Params->Page_Size * Params->Pages_Per_Sector
      * Params->Nr_Sectors;
  Flash->Params = (VOID*)Params;
  if (Flash->Size < 32 * 1024 * 1024) {
    INFO("SF: Need 32 MB Flash for UEFI\n");
    return NULL;
  }
  /* Enable 4-byte address mode */
  Spi_Flash_Cmd(&(Flash->Spi), CMD_M25PXX_WREN, NULL, 0);
  Spi_Flash_Cmd(&(Flash->Spi), CMD_M25PXX_4BYTE_ADDR_EN, NULL, 0);

  DBG("SF: Detected %s with page size %u, total %u bytes\n",
        Params->Name, Params->Page_Size, Flash->Size);

  return Flash;
}
