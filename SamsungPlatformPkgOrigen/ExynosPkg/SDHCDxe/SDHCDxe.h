/** @file

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _SDHCDXE_H_
#define _SDHCDXE_H_

#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>


/* SDHC Register MAP */
#define BLKSIZE_OFFSET				(0x04)
#define BLKCNT_OFFSET				(0x04)	//only use [16:31]
#define BLEN_512BYTES				(0x200UL << 0)

#define ARGUMENT_OFFSET				(0x08)
#define TRNMOD_OFFSET				(0x0C)
#define CMDREG_OFFSET				(0x0C)		//only use [16:31]
#define ENDMA					BIT0
#define ENBLKCNT				BIT1
#define RD1WT0					BIT4
#define MUL1SIN0				BIT5
#define RSPTYP136				(0x1 << 16)
#define RSPTYP48				(0x2 << 16)
#define RSPTYP48B				(0x3 << 16)
#define ENCMDCRC				BIT19
#define ENCMDIDX				BIT20
#define DATAPRNT				BIT21
#define INDX(CMD_INDX)				((CMD_INDX & 0x3F) << 24)

#define RSPREG0_OFFSET				(0x10)
#define RSPREG1_OFFSET				(0x14)
#define RSPREG2_OFFSET				(0x18)
#define RSPREG3_OFFSET				(0x1C)
#define BDATA_OFFSET				(0x20)
#define PRNSTS_OFFSET				(0x24)
#define CMDINHCMD				BIT0
#define CMDINHDAT				BIT1
#define INSCARD					BIT16

#define HOSTCTL_OFFSET				(0x28)
#define PWRCON_OFFSET				(0x28)	//only use [8:15]
#define	WIDE4					BIT1
#define	SDBP					BIT8
#define SDBV18					(0x5 << 9)
#define SDBV30					(0x6 << 9)
#define SDBV33					(0x7 << 9)

#define CLKCON_OFFSET				(0x2C)
#define TIMEOUTCON_OFFSET			(0x2C)		//only use [16:23]
#define SDHC_SWRST_OFFSET			(0x2C)		//only use [24:31]
#define	ICE					BIT0
#define	ICS					BIT1
#define	CCE					BIT2
#define CCS					BIT3
#define SRA					BIT24
#define SRC				        BIT25
#define SRD					BIT26

#define INTSTS_OFFSET				(0x30)
#define INTEN_OFFSET				(0x34)
#define CMDCOMP					BIT0
#define	TRNSCOMP				BIT1
#define	RDYFORWT				BIT4
#define RDYFORRD				BIT5
#define CARDINSERT				BIT6
#define CARDREMOVE				BIT7
#define ERRINT					BIT15
#define CMDTOUTERR				BIT16
#define CMDCRCERR				BIT17
#define CMDEBITERR				BIT18
#define CMDIDXERR				BIT19
#define DATATOUTERR				BIT20
#define DATACRCERR				BIT21
#define DATAEBITERR				BIT22

#define HosttoCard				0x1
#define CardtoHost				0x0

/* Command Definitions */
#define CMD0              INDX(0)
#define CMD0_INT_EN       (CMDCOMP | CMDEBITERR)

#define CMD1              (INDX(1) | RSPTYP48)
#define CMD1_INT_EN       (CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD2              (INDX(2) | ENCMDCRC | RSPTYP136)
#define CMD2_INT_EN       (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD3              (INDX(3) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD3_INT_EN       (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD5              (INDX(5) | RSPTYP48)
#define CMD5_INT_EN       (CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD7              (INDX(7) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD7_INT_EN       (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD8              (INDX(8) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD8_INT_EN       (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)
//Reserved(0)[12:31], Supply voltage(1)[11:8], check pattern(0xCE)[7:0] = 0x1CE
#define CMD8_ARG          (0x0UL << 12 | BIT8 | 0xCEUL << 0)

#define CMD9              (INDX(9) | ENCMDCRC | RSPTYP136)
#define CMD9_INT_EN       (CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD16             (INDX(16) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD16_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD17             (INDX(17) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | RD1WT0)
#define CMD17_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORRD | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

#define CMD18             (INDX(18) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | MUL1SIN0 | RD1WT0 | ENBLKCNT | ENDMA)
#define CMD18_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORRD | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

#define CMD23             (INDX(23) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD23_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD24             (INDX(24) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD24_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORWT | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

#define CMD25             (INDX(25) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | MUL1SIN0 | ENBLKCNT | ENDMA)
#define CMD25_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORWT | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

#define CMD55             (INDX(55) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD55_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define ACMD41            (INDX(41) | RSPTYP48)
#define ACMD41_INT_EN     (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define ACMD6             (INDX(6) | RSPTYP48)
#define ACMD6_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)


#define HCS               BIT30 //Host capacity support/1 = Supporting high capacity

#define MAX_RETRY_COUNT  (100000)
#define MMC_REFERENCE_CLK (96000000)

typedef struct {
  UINT32  Reserved0:   7; // 0
  UINT32  V170_V195:   1; // 1.70V - 1.95V
  UINT32  V200_V260:   7; // 2.00V - 2.60V
  UINT32  V270_V360:   9; // 2.70V - 3.60V
  UINT32  RESERVED_1:  5; // Reserved
  UINT32  AccessMode:  2; // 00b (byte mode), 10b (sector mode)
  UINT32  Busy:        1; // This bit is set to LOW if the card has not finished the power up routine
}OCR;

typedef struct {
  UINT32  NOT_USED;   // 1 [0:0]
  UINT32  CRC;        // CRC7 checksum [7:1]
  UINT32  MDT;        // Manufacturing date [19:8]
  UINT32  RESERVED_1; // Reserved [23:20]
  UINT32  PSN;        // Product serial number [55:24]
  UINT8   PRV;        // Product revision [63:56]
  UINT8   PNM[5];     // Product name [64:103]
  UINT16  OID;        // OEM/Application ID [119:104]
  UINT8   MID;        // Manufacturer ID [127:120]
}CID;

typedef struct {
  UINT8   NOT_USED:           1; // Not used, always 1 [0:0]
  UINT8   CRC:                7; // CRC [7:1]

  UINT8   RESERVED_1:         2; // Reserved [9:8]
  UINT8   FILE_FORMAT:        2; // File format [11:10]
  UINT8   TMP_WRITE_PROTECT:  1; // Temporary write protection [12:12]
  UINT8   PERM_WRITE_PROTECT: 1; // Permanent write protection [13:13]
  UINT8   COPY:               1; // Copy flag (OTP) [14:14]
  UINT8   FILE_FORMAT_GRP:    1; // File format group [15:15]

  UINT16  RESERVED_2:         5; // Reserved [20:16]
  UINT16  WRITE_BL_PARTIAL:   1; // Partial blocks for write allowed [21:21]
  UINT16  WRITE_BL_LEN:       4; // Max. write data block length [25:22]
  UINT16  R2W_FACTOR:         3; // Write speed factor [28:26]
  UINT16  RESERVED_3:         2; // Reserved [30:29]
  UINT16  WP_GRP_ENABLE:      1; // Write protect group enable [31:31]

  UINT32  WP_GRP_SIZE:        7; // Write protect group size [38:32]
  UINT32  SECTOR_SIZE:        7; // Erase sector size [45:39]
  UINT32  ERASE_BLK_EN:       1; // Erase single block enable [46:46]
  UINT32  C_SIZE_MULT:        3; // Device size multiplier [49:47]
  UINT32  VDD_W_CURR_MAX:     3; // Max. write current @ VDD max [52:50]
  UINT32  VDD_W_CURR_MIN:     3; // Max. write current @ VDD min [55:53]
  UINT32  VDD_R_CURR_MAX:     3; // Max. read current @ VDD max [58:56]
  UINT32  VDD_R_CURR_MIN:     3; // Max. read current @ VDD min [61:59]
  UINT32  C_SIZELow2:         2; // Device size [63:62]

  UINT32  C_SIZEHigh10:       10;// Device size [73:64]
  UINT32  RESERVED_4:         2; // Reserved [75:74]
  UINT32  DSR_IMP:            1; // DSR implemented [76:76]
  UINT32  READ_BLK_MISALIGN:  1; // Read block misalignment [77:77]
  UINT32  WRITE_BLK_MISALIGN: 1; // Write block misalignment [78:78]
  UINT32  READ_BL_PARTIAL:    1; // Partial blocks for read allowed [79:79]
  UINT32  READ_BL_LEN:        4; // Max. read data block length [83:80]
  UINT32  CCC:                12;// Card command classes [95:84]

  UINT8   TRAN_SPEED          ;  // Max. bus clock frequency [103:96]
  UINT8   NSAC                ;  // Data read access-time 2 in CLK cycles (NSAC*100) [111:104]
  UINT8   TAAC                ;  // Data read access-time 1 [119:112]

  UINT8   RESERVED_5:         6; // Reserved [125:120]
  UINT8   CSD_STRUCTURE:      2; // CSD structure [127:126]
}CSD;

typedef struct {
  UINT8   NOT_USED:           1; // Not used, always 1 [0:0]
  UINT8   CRC:                7; // CRC [7:1]
  UINT8   RESERVED_1:         2; // Reserved [9:8]
  UINT8   FILE_FORMAT:        2; // File format [11:10]
  UINT8   TMP_WRITE_PROTECT:  1; // Temporary write protection [12:12]
  UINT8   PERM_WRITE_PROTECT: 1; // Permanent write protection [13:13]
  UINT8   COPY:               1; // Copy flag (OTP) [14:14]
  UINT8   FILE_FORMAT_GRP:    1; // File format group [15:15]
  UINT16  RESERVED_2:         5; // Reserved [20:16]
  UINT16  WRITE_BL_PARTIAL:   1; // Partial blocks for write allowed [21:21]
  UINT16  WRITE_BL_LEN:       4; // Max. write data block length [25:22]
  UINT16  R2W_FACTOR:         3; // Write speed factor [28:26]
  UINT16  RESERVED_3:         2; // Reserved [30:29]
  UINT16  WP_GRP_ENABLE:      1; // Write protect group enable [31:31]
  UINT16  WP_GRP_SIZE:        7; // Write protect group size [38:32]
  UINT16  SECTOR_SIZE:        7; // Erase sector size [45:39]
  UINT16  ERASE_BLK_EN:       1; // Erase single block enable [46:46]
  UINT16  RESERVED_4:         1; // Reserved [47:47]
  UINT32  C_SIZELow16:        16;// Device size [69:48]
  UINT32  C_SIZEHigh6:        6; // Device size [69:48]
  UINT32  RESERVED_5:         6; // Reserved [75:70]
  UINT32  DSR_IMP:            1; // DSR implemented [76:76]
  UINT32  READ_BLK_MISALIGN:  1; // Read block misalignment [77:77]
  UINT32  WRITE_BLK_MISALIGN: 1; // Write block misalignment [78:78]
  UINT32  READ_BL_PARTIAL:    1; // Partial blocks for read allowed [79:79]
  UINT16  READ_BL_LEN:        4; // Max. read data block length [83:80]
  UINT16  CCC:                12;// Card command classes [95:84]
  UINT8   TRAN_SPEED          ;  // Max. bus clock frequency [103:96]
  UINT8   NSAC                ;  // Data read access-time 2 in CLK cycles (NSAC*100) [111:104]
  UINT8   TAAC                ;  // Data read access-time 1 [119:112]
  UINT8   RESERVED_6:         6; // 0 [125:120]
  UINT8   CSD_STRUCTURE:      2; // CSD structure [127:126]
}CSD_SDV2;

typedef enum {
  UNKNOWN_CARD,
  MMC_CARD,              //MMC card
  SD_CARD,               //SD 1.1 card
  SD_CARD_2,             //SD 2.0 or above standard card
  SD_CARD_2_HIGH         //SD 2.0 or above high capacity card
} CARD_TYPE;

typedef enum {
  READ,
  WRITE
} OPERATION_TYPE;

typedef struct  {
  UINT16    RCA;
  UINTN     BlockSize;
  UINTN     NumBlocks;
  UINTN     ClockFrequencySelect;
  CARD_TYPE CardType;
  OCR       OCRData;
  CID       CIDData;
  CSD       CSDData;
} CARD_INFO;

EFI_STATUS
DetectCard (
  VOID
  );

extern EFI_BLOCK_IO_PROTOCOL gBlockIo;

#endif
