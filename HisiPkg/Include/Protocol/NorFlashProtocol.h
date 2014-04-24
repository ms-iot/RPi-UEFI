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


#ifndef _NOR_FLASH_PROTOCOL_H_
#define _NOR_FLASH_PROTOCOL_H_
#include <Uefi/UefiBaseType.h>

#define UNI_NOR_FLASH_PROTOCOL_GUID   \
    {0x86F305EA, 0xDFAC, 0x4A6B, {0x92, 0x77, 0x47, 0x31, 0x2E, 0xCE, 0x42, 0xA}} 

typedef struct _UNI_NOR_FLASH_PROTOCOL UNI_NOR_FLASH_PROTOCOL;

typedef struct {
    UINT32 ManufacturerID; 
    UINT32 DeviceID; 
    UINT32 FlashSize; 
    UINT32 BlockSize;
    UINT8 ParallelNum; 
    UINT8 SeriesNum;
    UINT32 Base; 
}NOR_FLASH_INFO_TABLE;


typedef 
EFI_STATUS
(EFIAPI *UNI_FLASH_ERASE_INTERFACE) (
    IN UNI_NOR_FLASH_PROTOCOL   *This,
    IN UINT32                  Offset,
    IN UINT32                  Length
    );
typedef 
EFI_STATUS
(EFIAPI *UNI_FLASH_WRITE_INTERFACE) (
    IN UNI_NOR_FLASH_PROTOCOL   *This,
    IN  UINT32                 Offset,
    IN  UINT8                 *Buffer,
    UINT32                   ulLength
    );

typedef 
EFI_STATUS
(EFIAPI *UNI_FLASH_READ_INTERFACE) (
    IN UNI_NOR_FLASH_PROTOCOL   *This,
    IN UINT32                  Offset,
    IN OUT UINT8              *Buffer,
    IN UINT32                   ulLen
    );

typedef
EFI_STATUS 
(EFIAPI *UNI_FLASH_GetFlashInfo_INTERFACE) (
    IN  UNI_NOR_FLASH_PROTOCOL *This,
    OUT  NOR_FLASH_INFO_TABLE     *FlashInfo
  );

typedef 
EFI_STATUS
(EFIAPI *UNI_FLASH_DIRECT_WRITE_INTERFACE) (
    IN UNI_NOR_FLASH_PROTOCOL   *This,
    IN  UINT32                 Offset,
    IN  UINT8                 *Buffer,
    UINT32                   ulLength
    );
typedef 
EFI_STATUS
(EFIAPI *UNI_FLASH_GET_MANUID_INTERFACE) (
    IN UNI_NOR_FLASH_PROTOCOL   *This,
    IN  UINT32                 *ManuID
    );

typedef 
VOID
(EFIAPI *UNI_FLASH_CHECK_PROTECT_INTERFACE) (
    IN  UNI_NOR_FLASH_PROTOCOL *This
);

struct _UNI_NOR_FLASH_PROTOCOL {
    UNI_FLASH_ERASE_INTERFACE             Erase;
    UNI_FLASH_WRITE_INTERFACE             Write;
    UNI_FLASH_READ_INTERFACE              Read;
    UNI_FLASH_GetFlashInfo_INTERFACE      GetFlashInfo;
    UNI_FLASH_CHECK_PROTECT_INTERFACE     CheckFlashProtectFlag;
    UNI_FLASH_DIRECT_WRITE_INTERFACE      DirectWrite;
    UNI_FLASH_GET_MANUID_INTERFACE        GetManuID;
};

extern EFI_GUID gUniNorFlashProtocolGuid;

#endif
