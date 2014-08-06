/*******************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/


#ifndef __NANDDRIVER_H__
#define __NANDDRIVER_H__



//
// GUID for EFI HFFS Driver Protocol
//
#define EFI_NAND_DRIVER_PROTOCOL_GUID \
    {0xf355bcc3, 0x252d, 0x4dee, 0xad, 0x05, 0x94, 0xbb, 0x29, 0xc8, 0x4d, 0x46}


typedef struct _EFI_NAND_DRIVER_PROTOCOL  EFI_NAND_DRIVER_PROTOCOL;

#if 1
typedef struct NAND_CMD_INFO
{
    UINT32 ulPageSize;                            /* Page size                  */
    UINT32 ulBlockSize;                            /* Block size                  */
    UINT32 ulEndBlockNum;
}NAND_CMD_INFO_STRU;
#endif


typedef
UINT32 ( *EFI_NAND_DRIVER_INIT)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This
);

typedef
UINT32 ( *EFI_NAND_DRIVER_ERASE)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulBlockNum
);

typedef
UINT32 ( *EFI_NAND_DRIVER_WRITE)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulChunkNum,
    IN UINT32 ulOffsetInChunk,
    IN UINT32 ulLength,
    IN UINT8* pucData
);

typedef
UINT32 ( *EFI_NAND_DRIVER_READ)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulChunkNum,
    IN UINT32 ulOffsetInChunk,
    IN UINT32 ulLength,
    OUT UINT8* pucData
);

typedef
UINT32 ( *EFI_NAND_DRIVER_WRITEECC)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulChunkNum,
    IN UINT32 ulOffsetInChunk,
    IN UINT32 ulLength,
    IN UINT8* pucData
);

typedef
UINT32 ( *EFI_NAND_DRIVER_READECC)
(
IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulChunkNum,
    IN UINT32 ulOffsetInChunk,
    IN UINT32 ulLength,
    OUT UINT8* pucData,
    IN OUT UINT32* pulBitFlip
);

typedef
UINT32 ( *EFI_NAND_DRIVER_READSPARE)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This,
    IN UINT32 ulChunkNum,
    IN UINT32 ulOffsetInChunk,
    IN UINT32 ulLength,
    OUT UINT8* pucData
);

typedef
NAND_CMD_INFO_STRU ( *EFI_NAND_DRIVER_GETCMDINFO)
(
    IN EFI_NAND_DRIVER_PROTOCOL   *This
);




 
typedef struct _EFI_NAND_DRIVER_PROTOCOL {
    EFI_NAND_DRIVER_INIT        NandFlashInit;
    EFI_NAND_DRIVER_ERASE       NandFlashErase;
    EFI_NAND_DRIVER_WRITE       NandFlashWrite;
    EFI_NAND_DRIVER_READ        NandFlashRead;
    EFI_NAND_DRIVER_WRITEECC    NandFlashWriteEcc;
    EFI_NAND_DRIVER_READECC     NandFlashReadEcc;
    EFI_NAND_DRIVER_READSPARE   NandFlashReadSpare;
    EFI_NAND_DRIVER_GETCMDINFO    NandFlashGetCMDInfo;
} EFI_NAND_DRIVER_PROTOCOL;

extern EFI_GUID gNANDDriverProtocolGuid;

#endif
