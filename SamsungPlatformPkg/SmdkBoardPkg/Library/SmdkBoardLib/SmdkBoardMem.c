/** @file
*
*  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.
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
#include <Library/MemoryAllocationLib.h>

// DDR attributes
#define DDR_ATTRIBUTES_CACHED           ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define DDR_ATTRIBUTES_UNCACHED         ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED
#define DDR_ATTRIBUTES_SECURE_CACHED    ARM_MEMORY_REGION_ATTRIBUTE_SECURE_WRITE_BACK
#define DDR_ATTRIBUTES_SECURE_UNCACHED  ARM_MEMORY_REGION_ATTRIBUTE_SECURE_UNCACHED_UNBUFFERED

#if 0
/**
  Return the information about the memory region in permanent memory used by PEI

  One of the PEI Module must install the permament memory used by PEI. This function returns the
  information about this region for your platform to this PEIM module.

  @param[out]   PeiMemoryBase       Base of the memory region used by PEI core and modules
  @param[out]   PeiMemorySize       Size of the memory region used by PEI core and modules

**/
VOID ArmPlatformGetPeiMemory (
    OUT UINTN*                                   PeiMemoryBase,
    OUT UINTN*                                   PeiMemorySize
    ) {
    ASSERT((PeiMemoryBase != NULL) && (PeiMemorySize != NULL));

   // *PeiMemoryBase = ARM_EB_DRAM_BASE + ARM_EB_EFI_FIX_ADDRESS_REGION_SZ;
   // *PeiMemorySize = ARM_EB_EFI_MEMORY_REGION_SZ;
    *PeiMemoryBase = PcdGet32(PcdSystemMemoryBase) + PcdGet32(PcdSystemMemoryFixRegionSize);
    *PeiMemorySize = PcdGet32(PcdSystemMemoryUefiRegionSize);
}
#endif
/**
  Return the Virtual Memory Map of your platform

  This Virtual Memory Map is used by MemoryInitPei Module to initialize the MMU on your platform.

  @param[out]   VirtualMemoryMap    Array of ARM_MEMORY_REGION_DESCRIPTOR describing a Physical-to-
                                    Virtual Memory mapping. This array must be ended by a zero-filled
                                    entry

**/
VOID ArmPlatformGetVirtualMemoryMap(ARM_MEMORY_REGION_DESCRIPTOR** VirtualMemoryMap) {
//    UINT32                        val32;
    UINT32                        CacheAttributes;
    ARM_MEMORY_REGION_DESCRIPTOR  *VirtualMemoryTable;

    ASSERT(VirtualMemoryMap != NULL);

    VirtualMemoryTable = (ARM_MEMORY_REGION_DESCRIPTOR*)AllocatePages(sizeof(ARM_MEMORY_REGION_DESCRIPTOR) * 5);
    if (VirtualMemoryTable == NULL) {
        return;
    }

    if (FeaturePcdGet(PcdCacheEnable) == TRUE) {
        CacheAttributes = DDR_ATTRIBUTES_CACHED;
    } else {
        CacheAttributes = DDR_ATTRIBUTES_UNCACHED;
    }

    // SFR
    VirtualMemoryTable[0].PhysicalBase = 0x00000000;
    VirtualMemoryTable[0].VirtualBase  = 0x00000000;
    VirtualMemoryTable[0].Length       = 0x20000000;
    VirtualMemoryTable[0].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

    // DDR
    VirtualMemoryTable[1].PhysicalBase = 0x40000000;
    VirtualMemoryTable[1].VirtualBase  = 0x40000000;
    VirtualMemoryTable[1].Length       = 0x0e000000;
    VirtualMemoryTable[1].Attributes   = (ARM_MEMORY_REGION_ATTRIBUTES)CacheAttributes;

		// framebuffer
    VirtualMemoryTable[2].PhysicalBase = 0x4e000000;
    VirtualMemoryTable[2].VirtualBase  = 0x4e000000;
    VirtualMemoryTable[2].Length       = 0x02000000;
    VirtualMemoryTable[2].Attributes   = DDR_ATTRIBUTES_UNCACHED;

    VirtualMemoryTable[3].PhysicalBase = 0x50000000;
    VirtualMemoryTable[3].VirtualBase  = 0x50000000;
    VirtualMemoryTable[3].Length       = 0xb0000000;
    VirtualMemoryTable[3].Attributes   = (ARM_MEMORY_REGION_ATTRIBUTES)CacheAttributes;

    // End of Table
    VirtualMemoryTable[4].PhysicalBase = 0;
    VirtualMemoryTable[4].VirtualBase  = 0;
    VirtualMemoryTable[4].Length       = 0;
    VirtualMemoryTable[4].Attributes   = (ARM_MEMORY_REGION_ATTRIBUTES)0;

    *VirtualMemoryMap = VirtualMemoryTable;
}



#if 0
/**
  Return the EFI Memory Map of your platform

  This EFI Memory Map of the System Memory is used by MemoryInitPei module to create the Resource
  Descriptor HOBs used by DXE core.

  @param[out]   EfiMemoryMap        Array of ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR describing an
                                    EFI Memory region. This array must be ended by a zero-filled entry

**/
VOID ArmPlatformGetEfiMemoryMap (
    OUT ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR** EfiMemoryMap
) {
    EFI_RESOURCE_ATTRIBUTE_TYPE     Attributes;
    UINT64                          MemoryBase;
    UINTN                           Index = 0;
    ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR  *EfiMemoryTable;

    ASSERT(EfiMemoryMap != NULL);

    EfiMemoryTable = (ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR*)AllocatePages(sizeof(ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR) * 6);

    Attributes =
    (
      EFI_RESOURCE_ATTRIBUTE_PRESENT |
      EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
      EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
      EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
      EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
      EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
      EFI_RESOURCE_ATTRIBUTE_TESTED
    );
    MemoryBase = PcdGet32(PcdSystemMemoryBase);//ARM_EB_DRAM_BASE;

    // Memory Reserved for fixed address allocations (such as Exception Vector Table)
    EfiMemoryTable[Index].ResourceAttribute = Attributes;
    EfiMemoryTable[Index].PhysicalStart = MemoryBase;
    EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdSystemMemoryFixRegionSize);//ARM_EB_EFI_FIX_ADDRESS_REGION_SZ;

    MemoryBase += PcdGet32(PcdSystemMemoryFixRegionSize);//ARM_EB_EFI_FIX_ADDRESS_REGION_SZ;

    // Memory declared to PEI as permanent memory for PEI and DXE
    EfiMemoryTable[++Index].ResourceAttribute = Attributes;
    EfiMemoryTable[Index].PhysicalStart = MemoryBase;
    EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdSystemMemoryUefiRegionSize);//ARM_EB_EFI_MEMORY_REGION_SZ;

    MemoryBase += PcdGet32(PcdSystemMemoryUefiRegionSize);//ARM_EB_EFI_MEMORY_REGION_SZ;

    // We must reserve the memory used by the Firmware Volume copied in DRAM at 0x80000000
    if (!PcdGet32(PcdStandalone)) {
        // Chunk between the EFI Memory region and the firmware
        EfiMemoryTable[++Index].ResourceAttribute = Attributes;
        EfiMemoryTable[Index].PhysicalStart = MemoryBase;
        //EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdEmbeddedFdBaseAddress) - MemoryBase;
        EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdNormalFdBaseAddress) - MemoryBase;

        // Chunk reserved by the firmware in DRAM
        EfiMemoryTable[++Index].ResourceAttribute = Attributes & (~EFI_RESOURCE_ATTRIBUTE_PRESENT);
        //EfiMemoryTable[Index].PhysicalStart = PcdGet32(PcdEmbeddedFdBaseAddress);
        EfiMemoryTable[Index].PhysicalStart = PcdGet32(PcdNormalFdBaseAddress);
        //EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdEmbeddedFdSize);
        EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdNormalFdSize);

       //MemoryBase = PcdGet32(PcdEmbeddedFdBaseAddress) + PcdGet32(PcdEmbeddedFdSize);
        MemoryBase = PcdGet32(PcdNormalFdBaseAddress) + PcdGet32(PcdNormalFdSize);
    }

    // We allocate all the remain memory as untested system memory
    EfiMemoryTable[++Index].ResourceAttribute = Attributes & (~EFI_RESOURCE_ATTRIBUTE_TESTED);
    EfiMemoryTable[Index].PhysicalStart = MemoryBase;
    EfiMemoryTable[Index].NumberOfBytes = PcdGet32(PcdSystemMemorySize) - (MemoryBase-PcdGet32(PcdSystemMemoryBase));

    EfiMemoryTable[++Index].ResourceAttribute = 0;
    EfiMemoryTable[Index].PhysicalStart = 0;
    EfiMemoryTable[Index].NumberOfBytes = 0;

    *EfiMemoryMap = EfiMemoryTable;
}
#endif

/**
  Return the EFI Memory Map of your platform

  This EFI Memory Map of the System Memory is used by MemoryInitPei module to create the Resource
  Descriptor HOBs used by DXE core.

  @param[out]   EfiMemoryMap        Array of ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR describing an
                                    EFI Memory region. This array must be ended by a zero-filled entry

**/
EFI_STATUS
ArmPlatformGetAdditionalSystemMemory (
    OUT ARM_SYSTEM_MEMORY_REGION_DESCRIPTOR** EfiMemoryMap
) {

//  ArmPlatformGetEfiMemoryMap(EfiMemoryMap);
  //return EFI_SUCCESS;
  return EFI_UNSUPPORTED;
}
