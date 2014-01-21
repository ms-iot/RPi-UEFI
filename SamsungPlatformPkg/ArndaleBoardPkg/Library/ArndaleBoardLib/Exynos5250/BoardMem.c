/** @file
*
*  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.
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

#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <ArmPlatform.h>

// Number of Virtual Memory Map Descriptors without a Logic Tile
#define MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS          9

// DDR attributes
#define DDR_ATTRIBUTES_CACHED           ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_WRITE_BACK
#define DDR_ATTRIBUTES_UNCACHED         ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_UNCACHED_UNBUFFERED
#define DDR_ATTRIBUTES_SECURE_CACHED    ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define DDR_ATTRIBUTES_SECURE_UNCACHED   ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED

// Logical Region 1
#define SOC_REGISTERS_IROM_PHYSICAL_BASE       0x00000000
#define SOC_REGISTERS_IROM_PHYSICAL_LENGTH     0x02010000
#define SOC_REGISTERS_IROM_ATTRIBUTES          ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE
#define SOC_REGISTERS_IROM_SECURE_ATTRIBUTES   ARM_MEMORY_REGION_ATTRIBUTE_DEVICE

// Logical Region 2
#define SOC_REGISTERS_SFR_PHYSICAL_BASE       0x10000000
#define SOC_REGISTERS_SFR_PHYSICAL_LENGTH     0x08FFFFFF
#define SOC_REGISTERS_SFR_ATTRIBUTES          ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE
#define SOC_REGISTERS_SFR_SECURE_ATTRIBUTES   ARM_MEMORY_REGION_ATTRIBUTE_DEVICE

/**
  Return the Virtual Memory Map of your platform

  This Virtual Memory Map is used by MemoryInitPei Module to initialize the MMU on your platform.

  @param[out]   VirtualMemoryMap    Array of ARM_MEMORY_REGION_DESCRIPTOR describing a Physical-to-
                                    Virtual Memory mapping. This array must be ended by a zero-filled
                                    entry

**/
VOID
ArmPlatformGetVirtualMemoryMap (
  IN ARM_MEMORY_REGION_DESCRIPTOR** VirtualMemoryMap
  )
{
  ARM_MEMORY_REGION_ATTRIBUTES  CacheAttributes;
  UINTN                         Index = 0;
  ARM_MEMORY_REGION_DESCRIPTOR  *VirtualMemoryTable;

  DEBUG ((EFI_D_ERROR, "++%a:%d\n", __FUNCTION__, __LINE__));

  UINTN  MemoryBase_Pcd = PcdGet64(PcdSystemMemoryBase);
  UINTN  MemorySize_Pcd = PcdGet64(PcdSystemMemorySize);
  UINTN  FrameBufferBase_Pcd = PcdGet32(PcdFrameBufferBase);
  UINTN  FrameBufferSize_Pcd = PcdGet32(PcdFrameBufferSize);
  UINTN  MpSharedArgsBase_Pcd = PcdGet32(PcdMpSharedArgsBase);
  UINTN  MpSharedArgsSize_Pcd = PcdGet32(PcdMpSharedArgsSize);
  UINTN  FdBaseAddress_Pcd = PcdGet32(PcdFdBaseAddress);
  UINTN  FdSize_Pcd = PcdGet32(PcdFdSize);
  UINTN  SmemBase_Pcd = PcdGet32(PcdSmemBaseAddress);
  UINTN  SmemSize_Pcd = PcdGet32(PcdSmemSize);
  UINTN  iRamBootBase_Pcd = PcdGet32(PcdiRamBootBase);
  UINTN  iRamBootSize_Pcd = PcdGet32(PcdiRamBootSize);
  BOOLEAN TrustzoneSupport_Pcd = PcdGetBool (PcdTrustzoneSupport);
  UINT32  Nsacr = ArmReadNsacr();
  UINTN  EmmcDMABufferBase_Pcd = PcdGet32(PcdEmmcDMABufferBase);

  // Checking Secure mode
  if(Nsacr == 0x0)  // Secure mode
  {
    TrustzoneSupport_Pcd = FALSE;
  }

  // Check if SMC TZASC is enabled. If Trustzone not enabled then all the entries remain in Secure World.
  // As this value can be changed in the Board Configuration file, the UEFI firmware needs to work for both case


  ASSERT(VirtualMemoryMap != NULL);

  VirtualMemoryTable = (ARM_MEMORY_REGION_DESCRIPTOR*)AllocatePages(EFI_SIZE_TO_PAGES (sizeof(ARM_MEMORY_REGION_DESCRIPTOR) * MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS));
  if (VirtualMemoryTable == NULL) {
      return;
  }

  if (FeaturePcdGet(PcdCacheEnable) == TRUE) {
      CacheAttributes = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_CACHED : DDR_ATTRIBUTES_SECURE_CACHED);
  } else {
      CacheAttributes = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_UNCACHED : DDR_ATTRIBUTES_SECURE_UNCACHED);
  }

  // FD region  : 0x40000000 - 0x40200000
  // Map in the FD region (includes SEC), the stack, and the exception vector region
  VirtualMemoryTable[Index].PhysicalBase = FdBaseAddress_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = FdBaseAddress_Pcd;
  VirtualMemoryTable[Index].Length         = FdSize_Pcd;  // need to check
  VirtualMemoryTable[Index].Attributes     = (ARM_MEMORY_REGION_ATTRIBUTES)CacheAttributes;
  DEBUG ((EFI_D_ERROR, "FD region  : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // SMEM       : 0x40200000 - 0x40300000
  // Shared memory 1MB (0x4000_0000 -- 0x4010_0000)
  VirtualMemoryTable[++Index].PhysicalBase = SmemBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = SmemBase_Pcd;
  VirtualMemoryTable[Index].Length         = SmemSize_Pcd;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_UNCACHED : DDR_ATTRIBUTES_SECURE_UNCACHED);
  DEBUG ((EFI_D_ERROR, "SMEM       : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // EMMC        : 0x40300000 - 0x40400000
  // EMMC (0x4030_0000 - 0x404_0000) (1MB)
  VirtualMemoryTable[++Index].PhysicalBase = EmmcDMABufferBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = EmmcDMABufferBase_Pcd;
  VirtualMemoryTable[Index].Length         = 0x00100000;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_UNCACHED : DDR_ATTRIBUTES_SECURE_UNCACHED);
  DEBUG ((EFI_D_ERROR, "EMMC       : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));


  // DDR        : 0x40400000 - 0x4E000000
  // DDR (0x4040_0000 - 0x4E00_0000) (511MB)
  VirtualMemoryTable[++Index].PhysicalBase = 0x40400000;
  VirtualMemoryTable[Index].VirtualBase    = 0x40400000;
  VirtualMemoryTable[Index].Length         = 0x0DC00000;
  VirtualMemoryTable[Index].Attributes     = (ARM_MEMORY_REGION_ATTRIBUTES)CacheAttributes;
  DEBUG ((EFI_D_ERROR, "DDR        : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // MpParkShared: 0x4D00_0000 - 0x4D10_0000
  // MpParkSahred (0x4D00_0000 - 0x4D10_0000)
  VirtualMemoryTable[++Index].PhysicalBase = MpSharedArgsBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = MpSharedArgsBase_Pcd;
  VirtualMemoryTable[Index].Length         = MpSharedArgsSize_Pcd;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_UNCACHED : DDR_ATTRIBUTES_SECURE_UNCACHED);
  DEBUG ((EFI_D_ERROR, "FrameBuffer: 0x%8X - 0x%8X\n", VirtualMemoryTable[Index].PhysicalBase,
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // FrameBuffer: 0x4E000000 - 0x50000000
  // Framebuffer (0x4E00_0000 - 0x5000_0000)
  VirtualMemoryTable[++Index].PhysicalBase = FrameBufferBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = FrameBufferBase_Pcd;
  VirtualMemoryTable[Index].Length         = FrameBufferSize_Pcd;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? DDR_ATTRIBUTES_UNCACHED : DDR_ATTRIBUTES_SECURE_UNCACHED);
  DEBUG ((EFI_D_ERROR, "FrameBuffer: 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // DDR        : 0x50000000 - 0xA0000000
  // DDR (0x5000_0000 - 0x8000_0000) (512MB)
  VirtualMemoryTable[++Index].PhysicalBase = MemoryBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = MemoryBase_Pcd;
  VirtualMemoryTable[Index].Length         = MemorySize_Pcd;
  VirtualMemoryTable[Index].Attributes     = (ARM_MEMORY_REGION_ATTRIBUTES)CacheAttributes;
  DEBUG ((EFI_D_ERROR, "DDR        : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // SFR        : 0x10000000 - 0x14000000
  // SFR
  VirtualMemoryTable[++Index].PhysicalBase = SOC_REGISTERS_SFR_PHYSICAL_BASE;
  VirtualMemoryTable[Index].VirtualBase    = SOC_REGISTERS_SFR_PHYSICAL_BASE;
  VirtualMemoryTable[Index].Length         = SOC_REGISTERS_SFR_PHYSICAL_LENGTH;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? SOC_REGISTERS_SFR_ATTRIBUTES : SOC_REGISTERS_SFR_SECURE_ATTRIBUTES);
  DEBUG ((EFI_D_ERROR, "SFR        : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // iRAM       : 0x02020000 - 0x02040000
  // iRAM
  VirtualMemoryTable[++Index].PhysicalBase = iRamBootBase_Pcd;
  VirtualMemoryTable[Index].VirtualBase    = iRamBootBase_Pcd;
  VirtualMemoryTable[Index].Length         = iRamBootSize_Pcd;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE : ARM_MEMORY_REGION_ATTRIBUTE_DEVICE);
  DEBUG ((EFI_D_ERROR, "iRAM       : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // iROM       : 0x00000000 - 0x02010000
  // iROM
  VirtualMemoryTable[++Index].PhysicalBase = SOC_REGISTERS_IROM_PHYSICAL_BASE;
  VirtualMemoryTable[Index].VirtualBase    = SOC_REGISTERS_IROM_PHYSICAL_BASE;
  VirtualMemoryTable[Index].Length         = SOC_REGISTERS_IROM_PHYSICAL_LENGTH;
  VirtualMemoryTable[Index].Attributes     = (TrustzoneSupport_Pcd ? SOC_REGISTERS_IROM_ATTRIBUTES : SOC_REGISTERS_IROM_SECURE_ATTRIBUTES);
  DEBUG ((EFI_D_ERROR, "iROM       : 0x%8X - 0x%8X\n", (UINT32)(VirtualMemoryTable[Index].PhysicalBase),
                     (UINT32)(VirtualMemoryTable[Index].PhysicalBase + VirtualMemoryTable[Index].Length)));

  // End of Table
  VirtualMemoryTable[++Index].PhysicalBase = 0;
  VirtualMemoryTable[Index].VirtualBase    = 0;
  VirtualMemoryTable[Index].Length         = 0;
  VirtualMemoryTable[Index].Attributes     = (ARM_MEMORY_REGION_ATTRIBUTES)0;

  *VirtualMemoryMap = VirtualMemoryTable;
  DEBUG ((EFI_D_ERROR, "--%a:%d\n", __FUNCTION__, __LINE__));
}

/**
  Return the EFI Memory Map provided by extension memory on your platform

  This EFI Memory Map of the System Memory is used by MemoryInitPei module to create the Resource
  Descriptor HOBs used by DXE core.
  TODO: CompleteMe .... say this is the memory not covered by the System Memory PCDs

  @param[out]   EfiMemoryMap        Array of ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR describing an
                                    EFI Memory region. This array must be ended by a zero-filled entry

**/
EFI_STATUS
ArmPlatformGetAdditionalSystemMemory (
  OUT ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR** EfiMemoryMap
  )
{
  return EFI_UNSUPPORTED;
}
