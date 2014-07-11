/*
 * Copyright (c) 1999, 2000
 * Intel Corporation.
 * All rights reserved.
 *  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgement:
 * 
 *    This product includes software developed by Intel Corporation and its
 *    contributors.
 * 
 * 4. Neither the name of Intel Corporation or its contributors may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL INTEL CORPORATION OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
 
#ifndef _FATFILESYSTEM_H_
#define _FATFILESYSTEM_H_

#pragma pack(1)
/* RAM disk device path structure.
 * Will use Vendor Messaging Device Path.
 */
typedef struct sRAM_DISK_DEVICE_PATH
{
	EFI_DEVICE_PATH Header;
	EFI_GUID        Guid;
	UINT8			DiskId[8];
	EFI_DEVICE_PATH EndDevicePath;
} RAM_DISK_DEVICE_PATH;

/* FAT16 boot sector definition */
typedef struct sBOOTSEC
{
	UINT8  BS_jmpBoot[3];
	UINT8  BS_OEMName[8];
	UINT16 BPB_BytsPerSec;
	UINT8  BPB_SecPerClus;
	UINT16 BPB_RsvdSecCnt;
	UINT8  BPB_NumFATs;
	UINT16 BPB_RootEntCnt;
	UINT16 BPB_TotSec16;
	UINT8  BPB_Media;
	UINT16 BPB_FATSz16;
	UINT16 BPB_SecPerTrk;
	UINT16 BPB_NumHeads;
	UINT32 BPB_HiddSec;
	UINT32 BPB_TotSec32;
	UINT8  BS_DrvNum;
	UINT8  BS_Reserved1;
	UINT8  BS_BootSig;
	UINT32 BS_VolID;
	UINT8  BS_VolLab[11];
	UINT8  BS_FilSysType[8];
	UINT8  BS_Code[448];
	UINT16 BS_Sig;
} BOOTSEC;

#pragma pack()

/* structure for total sectors to cluster size lookup */
typedef struct sFAT16TABLE
{
	UINTN size;
	UINT8  spc;
} FAT16TABLE;

#define PBLOCK_DEVICE_SIGNATURE SIGNATURE_32('r', 'd', 's', 'k')

/* Ramdisk device info structure */
typedef struct sRAM_DISKDEV
{
	UINTN                Signature;
	EFI_HANDLE           Handle;
	EFI_PHYSICAL_ADDRESS Start;
	EFI_BLOCK_IO         BlkIo;
	EFI_BLOCK_IO_MEDIA   Media;
	EFI_DEVICE_PATH      *DevicePath;
} RAM_DISK_DEV;

/* Macro finds the device info structure given a ramdisk BlkIo interface */
#define RAM_DISK_FROM_THIS(a) CR(a,RAM_DISK_DEV,BlkIo,PBLOCK_DEVICE_SIGNATURE)

/* Prototypes */
EFI_STATUS InitializeRamDiskDriver(
	IN EFI_HANDLE       ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable);

STATIC VOID FormatRamdisk(
	IN VOID*  pStart,
	IN UINT32 Size);

STATIC EFI_STATUS RamDiskReadBlocks(
	IN EFI_BLOCK_IO *This,
	IN UINT32       MediaId,
	IN EFI_LBA      LBA,
	IN UINTN        BufferSize,
	OUT VOID        *Buffer);

STATIC EFI_STATUS RamDiskWriteBlocks(
	IN EFI_BLOCK_IO *This,
	IN UINT32       MediaId,
	IN EFI_LBA      LBA,
	IN UINTN        BufferSize,
	IN VOID         *Buffer);

STATIC EFI_STATUS RamDiskFlushBlocks(
	IN EFI_BLOCK_IO *This);

#endif

