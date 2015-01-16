/**
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

#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/ArmLib.h>
#include <Library/BaseMemoryLib.h>
#include <ArmPlatform.h>
#include <Ppi/ArmMpCoreInfo.h>
#include <Ppi/TemporaryRamSupport.h>
#include <Universal/SetupBrowserDxe/Setup.h>
#include <Library/SlimproLib.h>
#include "APMXGeneClock.h"
#include "APMXGenePMD.h"

#define FWSTRINGMAXLEN 32
#define MHZ_SCALE_FACTOR  1000000

#ifdef AARCH64_MP_PROTOCOL
ARM_CORE_INFO mArmPlatformNullMpCoreInfoTable[] = {
  {
    // Cluster 0, Core 0
    0x0, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0x8000,
    (EFI_PHYSICAL_ADDRESS)0x8000,
    (EFI_PHYSICAL_ADDRESS)0x8000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 1
    0x0, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0x9000,
    (EFI_PHYSICAL_ADDRESS)0x9000,
    (EFI_PHYSICAL_ADDRESS)0x9000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 2
    0x1, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xA000,
    (EFI_PHYSICAL_ADDRESS)0xA000,
    (EFI_PHYSICAL_ADDRESS)0xA000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 3
    0x1, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xB000,
    (EFI_PHYSICAL_ADDRESS)0xB000,
    (EFI_PHYSICAL_ADDRESS)0xB000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 4
    0x2, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xC000,
    (EFI_PHYSICAL_ADDRESS)0xC000,
    (EFI_PHYSICAL_ADDRESS)0xC000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 5
    0x2, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xD000,
    (EFI_PHYSICAL_ADDRESS)0xD000,
    (EFI_PHYSICAL_ADDRESS)0xD000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 6
    0x3, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xE000,
    (EFI_PHYSICAL_ADDRESS)0xE000,
    (EFI_PHYSICAL_ADDRESS)0xE000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 7
    0x3, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
};
#else
ARM_CORE_INFO mArmPlatformNullMpCoreInfoTable[] = {
  {
    // Cluster 0, Core 0
    0x0, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 1
    0x0, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 2
    0x1, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 3
    0x1, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 4
    0x2, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 5
    0x2, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 6
    0x3, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
  {
    // Cluster 0, Core 7
    0x3, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (EFI_PHYSICAL_ADDRESS)0xF000,
    (UINT64)0xFFFFFFFF
  },
};
#endif

/**
  Return the current Boot Mode

  This function returns the boot reason on the platform

  @return   Return the current Boot Mode of the platform

**/
EFI_BOOT_MODE
ArmPlatformGetBootMode (
  VOID
  )
{
	return BOOT_WITH_FULL_CONFIGURATION;
}

/**
  Initialize controllers that must setup in the normal world

  This function is called by the ArmPlatformPkg/PrePi or ArmPlatformPkg/PlatformPei
  in the PEI phase.

**/
RETURN_STATUS
ArmPlatformInitialize (
  IN  UINTN                     MpId
  )
{
	return RETURN_SUCCESS;
}

EFI_STATUS
PrePeiCoreGetMpCoreInfo (
  OUT UINTN                   *CoreCount,
  OUT ARM_CORE_INFO           **ArmCoreTable
  )
{
  INTN Count;

  *CoreCount    = sizeof(mArmPlatformNullMpCoreInfoTable) / sizeof(ARM_CORE_INFO);

  /* PcdTTBBaseAddr is no longer used so use it for storing arm core table*/
  *ArmCoreTable = (ARM_CORE_INFO *)(PcdGet64(PcdTTBBaseAddr));

  ASSERT(*ArmCoreTable);

  DEBUG ((EFI_D_VERBOSE, "*ArmCoreTable: %p\n", *ArmCoreTable));
  CopyMem((VOID *)*ArmCoreTable, (VOID *)mArmPlatformNullMpCoreInfoTable, sizeof(mArmPlatformNullMpCoreInfoTable));
  /* remove any cores that belong to PMU which is disabled */
  for (Count = 0; Count < *CoreCount; Count++) {
    if (apm88xxxx_is_pmd_available((*ArmCoreTable)[Count].ClusterId))
      continue;

    DEBUG ((EFI_D_VERBOSE, "Disabled core:%d cluster:%d\n",
            (*ArmCoreTable)[Count].CoreId,
            (*ArmCoreTable)[Count].ClusterId));
            (*ArmCoreTable)[Count].ClusterId = -1;
            (*ArmCoreTable)[Count].CoreId = -1;
  }

  for (Count = 0; Count < *CoreCount; Count++) {
    if ((*ArmCoreTable)[Count].ClusterId == -1 &&
        (*ArmCoreTable)[Count].CoreId == -1) {

      *CoreCount -= 1;
      if (*CoreCount == Count)
        break;

      CopyMem(&(*ArmCoreTable)[Count],
                &(*ArmCoreTable)[Count + 1], ((*CoreCount) - Count) * sizeof(ARM_CORE_INFO));
      /* prevent Count increase in next loop */
      Count--;
    }
  }

  for (Count = 0; Count < *CoreCount; Count++) {
    (*ArmCoreTable)[Count].MailboxClearAddress += (UINT64)PcdGet64 (PcdSystemMemoryBase);
    (*ArmCoreTable)[Count].MailboxSetAddress += (UINT64)PcdGet64 (PcdSystemMemoryBase);
    (*ArmCoreTable)[Count].MailboxGetAddress += (UINT64)PcdGet64 (PcdSystemMemoryBase);
  }

  return EFI_SUCCESS;
}

// Needs to be declared in the file. Otherwise gArmMpCoreInfoPpiGuid is undefined in the contect of PrePeiCore
EFI_GUID mArmMpCoreInfoPpiGuid = ARM_MP_CORE_INFO_PPI_GUID;
ARM_MP_CORE_INFO_PPI mMpCoreInfoPpi = { PrePeiCoreGetMpCoreInfo };

EFI_PEI_PPI_DESCRIPTOR      gPlatformPpiTable[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI,
    &mArmMpCoreInfoPpiGuid,
    &mMpCoreInfoPpi
  },
};

/**
  Return the Platform specific PPIs

  This function exposes the Platform Specific PPIs. They can be used by any PrePi modules or passed
  to the PeiCore by PrePeiCore.

  @param[out]   PpiListSize         Size in Bytes of the Platform PPI List
  @param[out]   PpiList             Platform PPI List

**/
VOID
ArmPlatformGetPlatformPpiList (
  OUT UINTN                   *PpiListSize,
  OUT EFI_PEI_PPI_DESCRIPTOR  **PpiList
  )
{
	if (ArmIsMpCore()) {
		*PpiListSize = sizeof(gPlatformPpiTable);
		*PpiList = gPlatformPpiTable;
	} else {
		*PpiListSize = 0;
		*PpiList = NULL;
	}
}

#define read_cpuid(reg) ({                                              \
        UINT64 __val;                                                   \
        asm("mrs        %0, " reg : "=r" (__val));                      \
        __val;                                                          \
})

/*
 * The CPU ID never changes at run time, so we might as well tell the
 * compiler that it's constant.  Use this function to read the CPU ID
 * rather than directly reading processor_id or read_cpuid() directly.
 */
UINTN read_cpuid_id(void)
{
        UINT64     val;
        unsigned int aff0;
	#define ID_MPIDR_EL1            "mpidr_el1"

        val = read_cpuid(ID_MPIDR_EL1);

        val &= 0xFFFF;
        aff0 = ((unsigned int)val & 0x1);
        val &= 0xFF00;
        val >>= 7;
        val |= aff0;

        return (unsigned int) val;
}

UINTN  read_pmdid(void)
{
        return read_cpuid_id() / 2;
}

/**
  Display the Platform banner

  This function display the Platform board banner.

**/
VOID
ArmPlatformShowBoardBanner (UINTN (*PrintFunc)(IN CONST CHAR16 *Format, ...)
  )
{
  CHAR16 FWRevision[FWSTRINGMAXLEN];

  PrintFunc(L"TianoCore %s UEFI %d.%d.%d %a %a\n\r",
            (CHAR16*) PcdGetPtr(PcdFirmwareVersionString), 
            EFI_IFR_SPECIFICATION_VERSION >> 8,
            (EFI_IFR_SPECIFICATION_VERSION >> 4) & 0xF,
            EFI_IFR_SPECIFICATION_VERSION & 0xF,
            __DATE__, __TIME__);
  PrintFunc(L"CPU: APM ARM 64-bit Potenza");
  PrintFunc(L" %dMHz", get_PMD_CLK(read_pmdid())/MHZ_SCALE_FACTOR);
  PrintFunc(L" PCP %dMHz\n", get_PCP_CLK()/MHZ_SCALE_FACTOR);
  PrintFunc(L"     32 KB ICACHE, 32 KB DCACHE\n");
  PrintFunc(L"     SOC %dMHz", get_SOC_CLK()/MHZ_SCALE_FACTOR);
  PrintFunc(L" IOBAXI %dMHz", get_IOBAXI_CLK()/MHZ_SCALE_FACTOR);
  PrintFunc(L" AXI %dMHz", get_AXI_CLK()/MHZ_SCALE_FACTOR);
  PrintFunc(L" AHB %dMHz", get_AHB_CLK()/MHZ_SCALE_FACTOR);
  PrintFunc(L" GFC %dMHz\n", get_GFC_CLK()/MHZ_SCALE_FACTOR);
  if (PcdGetPtr(PcdFirmwareVendor) != NULL)
    PrintFunc(L"Board: %a\n\r", PcdGetPtr(PcdFirmwareVendor));
  XGeneIppGetFWRevision(FWRevision, FWSTRINGMAXLEN);
  PrintFunc(L"SLIMpro FW : %s\n\r", FWRevision);
}
