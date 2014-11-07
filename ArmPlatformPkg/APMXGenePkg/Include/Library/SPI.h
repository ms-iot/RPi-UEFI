/**
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
 
#ifndef _SPI_H_
#define _SPI_H_

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>

/* SPI mode flags */
#define	SPI_CPHA	0x01			/* clock phase */
#define	SPI_CPOL	0x02			/* clock polarity */
#define	SPI_MODE_0	(0|0)			/* (original MicroWire) */
#define	SPI_MODE_1	(0|SPI_CPHA)
#define	SPI_MODE_2	(SPI_CPOL|0)
#define	SPI_MODE_3	(SPI_CPOL|SPI_CPHA)
#define	SPI_CS_HIGH	0x04			/* CS active high */
#define	SPI_LSB_FIRST	0x08			/* per-word bits-on-wire */
#define	SPI_3WIRE	0x10			/* SI/SO signals shared */
#define	SPI_LOOP	0x20			/* loopback mode */

/* SPI transfer flags */
#define SPI_XFER_BEGIN	0x01			/* Assert CS before transfer */
#define SPI_XFER_END	0x02			/* Deassert CS after transfer */
 
struct SPI_SLAVE {
  UINTN	Bus;
  UINTN	Cs;
};

EFI_STATUS Spi_Claim_Bus(struct SPI_SLAVE *);

VOID Spi_Release_Bus(struct SPI_SLAVE *Slave);

EFI_STATUS Spi_Xfer(struct SPI_SLAVE *, UINTN, const VOID *,
       VOID *, UINT32);

struct SPI_SLAVE *Spi_Setup_Slave(OUT struct SPI_SLAVE *, 
                                  IN UINTN , IN UINTN ,
                                  IN UINTN , IN UINTN );
#endif /* _SPI_H_ */
