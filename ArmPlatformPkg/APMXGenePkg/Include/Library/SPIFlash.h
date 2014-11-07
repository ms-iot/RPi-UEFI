/**
 * SPI Flash INTNernal definitions
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#ifndef _SPIFLASH_H_
#define _SPIFLASH_H_

#include <Library/SPI.h>
#include <Library/DebugLib.h>

#define SPI_FLASH_PROG_TIMEOUT		(2)
#define SPI_FLASH_PAGE_ERASE_TIMEOUT	(5)
#define SPI_FLASH_SECTOR_ERASE_TIMEOUT	(10)

/* Common commands */
#define CMD_READ_ID			0x9f

#define CMD_READ_ARRAY_SLOW		0x03
#define CMD_READ_ARRAY_FAST		0x0b
#define CMD_READ_ARRAY_LEGACY		0xe8

#define CONFIG_SPI_FLASH_STMICRO 1

struct SPI_FLASH {
	struct SPI_SLAVE Spi;
	const CHAR8	*Name;
        VOID            *Params;
	UINT32		Size;
	INTN		(*Read)(struct SPI_FLASH *Flash, UINT32 Offset,
				UINT32 Len, VOID *Buf);
	INTN		(*Write)(struct SPI_FLASH *Flash, UINT32 Offset,
				UINT32 Len, const VOID *Buf);
	INTN		(*Erase)(struct SPI_FLASH *Flash, UINT32 Offset,
				UINT32 Len);
};

/* Send a single-byte command to the device and read the response */
EFI_STATUS Spi_Flash_Cmd(struct SPI_SLAVE *, UINT8 , VOID *, UINT32);

/*
 * Send a multi-byte command to the device and read the response. Used
 * for Flash array reads, etc.
 */
EFI_STATUS Spi_Flash_Cmd_Read(struct SPI_SLAVE *, const UINT8 *,
		UINT32 , VOID *, UINT32 );

/*
 * Send a multi-byte command to the device followed by (optional)
 * data. Used for programming the Flash array, etc.
 */
EFI_STATUS Spi_Flash_Cmd_Write(struct SPI_SLAVE *, const UINT8 *, UINT32 ,
		const VOID *, UINT32 );

/*
 * Same as Spi_Flash_cmd_read() except it also claims/releases the SPI
 * bus. Used as common part of the ->read() operation.
 */
EFI_STATUS Spi_Flash_Read_Common(struct SPI_FLASH *, const UINT8 *,
		UINT32 , VOID *, UINT32);

                
struct SPI_FLASH *
Spi_Flash_Probe(struct SPI_FLASH *, UINTN , UINTN ,
    UINTN , UINTN );
                
/* Manufacturer-specific probe functions */

struct SPI_FLASH *
Spi_Flash_Probe_Stmicro(struct SPI_FLASH *, UINT8 *);

#endif /*_SPIFLASH_H_ */
