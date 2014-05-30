/** @file

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _MSHCDXE_H_
#define _MSHCDXE_H_

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
#include <Protocol/FirmwareVolumeBlock.h>

#include "eMMCDxe_5250.h"
#include "eMMCDxe_CMD.h"

/**
eMMC partition Gaia EVT1

boot partition-1        : 100M store BL1, BL2, UEFI, TZSW
boot partition-2        : 100M not used
RPMB                         : 16M  for secure team
General purpose-1   : not used
General purpose-2   : not used
General purpose-3   : not used
General purpose-4   : not used

boot partition-1 start offset
BL1: 0 
BL2: 16 
UEFI : 32 
TZSW : 2592~3104
NV data area : 3200
NV data for security team : 3200
NV data for general purpose : 3400
**/

#define MSHC_BOOT_SIZE  100
#define MSHC_RPMB_SIZE  0
#define MSHC_BOOT_SIZE_MULTI  (MSHC_BOOT_SIZE*2)
#define MSHC_BOOT_SECURE_OFFSET 3200
#define MSHC_BOOT_SECURE_SIZE 512 // 256k

#define MSHC_BOOT_PARTITION    0
#define MSHC_RPMB_PARTITION    1
#define MSHC_USER_PARTITION    2

#define BLEN_512BYTES	(0x200)
#define BLKSIZE_1	        (0x1)

#define OM_EMMC 0x8

#define MAX_RETRY_COUNT  (100000)
#define MMC_REFERENCE_CLK (96000000)
#define MSHC_CLK_400 (400)
#define MSHC_CLK_25M (25000)
#define MSHC_CLK_50M (50000)

#define OCR_BUSY	0x80000000
#define OCR_HCS		0x40000000

#define MMC_VDD_165_195	0x00000080	/* VDD voltage 1.65 - 1.95 */
#define MMC_VDD_20_21		0x00000100	/* VDD voltage 2.0 ~ 2.1 */
#define MMC_VDD_21_22		0x00000200	/* VDD voltage 2.1 ~ 2.2 */
#define MMC_VDD_22_23		0x00000400	/* VDD voltage 2.2 ~ 2.3 */
#define MMC_VDD_23_24		0x00000800	/* VDD voltage 2.3 ~ 2.4 */
#define MMC_VDD_24_25		0x00001000	/* VDD voltage 2.4 ~ 2.5 */
#define MMC_VDD_25_26		0x00002000	/* VDD voltage 2.5 ~ 2.6 */
#define MMC_VDD_26_27		0x00004000	/* VDD voltage 2.6 ~ 2.7 */
#define MMC_VDD_27_28		0x00008000	/* VDD voltage 2.7 ~ 2.8 */
#define MMC_VDD_28_29		0x00010000	/* VDD voltage 2.8 ~ 2.9 */
#define MMC_VDD_29_30		0x00020000	/* VDD voltage 2.9 ~ 3.0 */
#define MMC_VDD_30_31		0x00040000	/* VDD voltage 3.0 ~ 3.1 */
#define MMC_VDD_31_32		0x00080000	/* VDD voltage 3.1 ~ 3.2 */
#define MMC_VDD_32_33		0x00100000	/* VDD voltage 3.2 ~ 3.3 */
#define MMC_VDD_33_34		0x00200000	/* VDD voltage 3.3 ~ 3.4 */
#define MMC_VDD_34_35		0x00400000	/* VDD voltage 3.4 ~ 3.5 */
#define MMC_VDD_35_36		0x00800000	/* VDD voltage 3.5 ~ 3.6 */


#define MMC_SWITCH_MODE_CMD_SET		0x00 /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS	0x01 /* Set bits in EXT_CSD byte
						addressed by index which are
						1 in value field */
#define MMC_SWITCH_MODE_CLEAR_BITS	0x02 /* Clear bits in EXT_CSD byte
						addressed by index, which are
						1 in value field */
#define MMC_SWITCH_MODE_WRITE_BYTE	0x03 /* Set target byte to value */
/*
 * EXT_CSD fields
 */

#define EXT_CSD_BUS_WIDTH	183	/* R/W */
#define EXT_CSD_HS_TIMING	185	/* R/W */
#define EXT_CSD_CARD_TYPE	196	/* RO */
#define EXT_CSD_REV		192	/* RO */
#define EXT_CSD_SEC_CNT		212	/* RO, 4 bytes */
#define BOOT_SIZE_MULTI		226	/* RO */
#define PARTITIONING_SUPPORT	160	/* RO */

/*
 * EXT_CSD field definitions
 */

/* Card */
#define EXT_CSD_CMD_SET_NORMAL		(1<<0)
#define EXT_CSD_CMD_SET_SECURE		(1<<1)
#define EXT_CSD_CMD_SET_CPSECURE	(1<<2)

#define EXT_CSD_CARD_TYPE_26		(1<<0)	/* Card can run at 26MHz */
#define EXT_CSD_CARD_TYPE_52		(1<<1)	/* Card can run at 52MHz */
#define EXT_CSD_CARD_TYPE_52_DDR_18_30	(1<<2)	/* Card can run at 52MHz DDR 1.8V or 3V */
#define EXT_CSD_CARD_TYPE_52_DDR_12	(1<<3)	/* Card can run at 52MHz DDR 1.2V */

#define EXT_CSD_BUS_WIDTH_1	0	/* Card is in 1 bit mode */
#define EXT_CSD_BUS_WIDTH_4	1	/* Card is in 4 bit mode */
#define EXT_CSD_BUS_WIDTH_8	2	/* Card is in 8 bit mode */
#define EXT_CSD_BUS_WIDTH_4_DDR	5	/* Card is in 4 bit DDR mode */
#define EXT_CSD_BUS_WIDTH_8_DDR	6	/* Card is in 8 bit DDR mode */


typedef struct {
	UINT32 hs_max_dtr;
	UINT32 sectors;
	UINT32 boot_size_multi;     //226
        UINT32 Partitioning_Support; //160
}mmc_ext_csd;


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
  SD_CARD_2_HIGH,         //SD 2.0 or above high capacity card
  SD_CARD_MAX
} CARD_TYPE;



typedef enum {
    MSHC_IDMA,
    MSHC_FIFO
}MSHC_OPERATION_MODE;

typedef struct  {
  UINT16    RCA;
  UINTN     BlockSize;
  UINTN     NumBlocks;
  UINTN     TotalNumBlocks;
  UINTN     ClockFrequencySelect;
  CARD_TYPE CardType;
  OCR       OCRData;
  CID       CIDData;
  CSD       CSDData;
  mmc_ext_csd Extcsd;
} CARD_INFO;


EFI_STATUS
DetectCard (VOID);
void mshci_reset_fifo(void);

extern EFI_BLOCK_IO_PROTOCOL gBlockIo;
extern EFI_BLOCK_IO_MEDIA gSDMMCMedia;
extern CARD_INFO gCardInfo;
extern BOOLEAN gCardInit;
    
extern EFI_STATUS
SdReadWrite (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN  UINTN                   Lba,
  OUT VOID                    *Buffer,
  IN  UINTN                   BufferSize,
  IN  OPERATION_TYPE          OperationType
  );
EFI_STATUS
EraseBlockData (
  IN UINT32 Partition,
  IN UINTN StartBlock,
  IN  UINTN NumBlock
  );



#endif

