/** @file

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _MSHCDXE_CMD_H_
#define _MSHCDXE_CMD_H_



#define HosttoCard				0x1
#define CardtoHost				0x0

#define ENDMA					BIT0
#define ENBLKCNT				BIT1
#define RD1WT0					BIT4
#define MUL1SIN0				BIT5
#define RSPTYP136				(0x1 << 16)
#define RSPTYP48				    (0x2 << 16)
#define RSPTYP48B				(0x3 << 16)
#define ENCMDCRC				BIT19
#define ENCMDIDX				BIT20
#define DATAPRNT				BIT21


#define CMDCOMP				BIT0
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

#define HCS               BIT30 //Host capacity support/1 = Supporting high capacity



/* Command Definitions */
#define INDX(CMD_INDX)			(CMD_INDX & 0x3F)

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

//#define CMD8              (INDX(8) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD8              (INDX(8) | ENCMDIDX | RSPTYP48)
#define CMD8_INT_EN       (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)
//Reserved(0)[12:31], Supply voltage(1)[11:8], check pattern(0xCE)[7:0] = 0x1CE
//#define CMD8_ARG          (0x0UL << 12 | BIT8 | 0xCEUL << 0)
#define CMD8_ARG          (0x0UL << 12 | BIT8 | 0xAAUL << 0)

#define CMD9              (INDX(9) | ENCMDCRC | RSPTYP136)
#define CMD9_INT_EN       (CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD13              (INDX(13) | RSPTYP48)
#define CMD13_INT_EN       (CMDCOMP | CMDEBITERR | CMDTOUTERR)


//#define CMD16             (INDX(16) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD16             (INDX(16) | ENCMDIDX | RSPTYP48)
#define CMD16_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD17             (INDX(17) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | RD1WT0)
#define CMD17_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORRD | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

//#define CMD18             (INDX(18) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | MUL1SIN0 | RD1WT0 | ENBLKCNT | ENDMA)
#define CMD18             (INDX(18) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 )
#define CMD18_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORRD | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

#define CMD23             (INDX(23) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD23_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD24             (INDX(24) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD24_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORWT | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

//#define CMD25             (INDX(25) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48 | MUL1SIN0 | ENBLKCNT | ENDMA)
#define CMD25             (INDX(25) | DATAPRNT | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD25_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | TRNSCOMP | RDYFORWT | CMDTOUTERR | DATATOUTERR | DATACRCERR | DATAEBITERR | CMDEBITERR)

//#define CMD55             (INDX(55) | ENCMDIDX | ENCMDCRC | RSPTYP48)
#define CMD55             (INDX(55) | ENCMDIDX | RSPTYP48)
#define CMD55_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define ACMD41            (INDX(41) | RSPTYP48)
#define ACMD41_INT_EN     (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define ACMD6             (INDX(6) | RSPTYP48)
#define ACMD6_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)

#define CMD62             (INDX(62) | RSPTYP48)
#define CMD62_INT_EN      (CMDIDXERR | CMDCRCERR | CMDCOMP | CMDEBITERR | CMDTOUTERR)



/*
EFI_STATUS
EFI_SUCCESS         0

EFI_LOAD_ERROR      1
EFI_INVALID_PARAMETER   2
EFI_UNSUPPORTED             3
EFI_BAD_BUFFER_SIZE         4
EFI_BUFFER_TOO_SMALL        5
EFI_NOT_READY                   6
EFI_DEVICE_ERROR            7
EFI_WRITE_PROTECTED     8
EFI_OUT_OF_RESOURCES    9
EFI_VOLUME_CORRUPTED    10
EFI_VOLUME_FULL                 11
EFI_NO_MEDIA                        12
EFI_MEDIA_CHANGED           13
EFI_NOT_FOUND                   14
EFI_ACCESS_DENIED           15
EFI_NO_RESPONSE             16
EFI_NO_MAPPING                  17
EFI_TIMEOUT                     18
EFI_NOT_STARTED             19
EFI_ALREADY_STARTED     20
EFI_ABORTED                     21
EFI_ICMO_ERROR              22
EFI_TFTP_ERROR                  23
EFI_PROTOCOL_ERROR          24
EFI_INCOMPATIBLE_VERSION    25
EFI_SECURITY_VIOLATION          26
EFI_CRC_ERROR                   27
EFI_END_OF_MEDIA                28
EFI_END_OF_FILE                 31
EFI_INVALID_LANGUAGE        32
EFI_COMPROMISED_DATA        33


*/

#endif

