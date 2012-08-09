/** @file
*
*  Copyright (c) 2011, ARM Limited. All rights reserved.
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

#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <Ppi/ArmMpCoreInfo.h>

#include <Omap4430/Omap4430.h>
#include <PandaBoard.h>

ARM_CORE_INFO mVersatileExpressMpCoreInfoPandaBoard[] = {
  {
    // Cluster 0, Core 0
    0x0, 0x0,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (UINT64)0
  },
  {
    // Cluster 0, Core 1
    0x0, 0x1,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (EFI_PHYSICAL_ADDRESS)0x80000000,
    (UINT64)0
  }
};

VOID
PadConfiguration (
  PANDABOARD_REVISION Revision
  );

VOID
ClockInit (
  VOID
  );

/**
  Detect board revision

  @return Board revision
**/
PANDABOARD_REVISION
PandaBoardGetRevision (
  VOID
  )
{
#if 0
  UINT32 OldPinDir;
  UINT32 Revision;

  // Read GPIO 171, 172, 173
  OldPinDir = MmioRead32 (GPIO6_BASE + GPIO_OE);
  MmioWrite32(GPIO6_BASE + GPIO_OE, (OldPinDir | BIT11 | BIT12 | BIT13));
  Revision = MmioRead32 (GPIO6_BASE + GPIO_DATAIN);
  
  // Restore I/O settings
  MmioWrite32 (GPIO6_BASE + GPIO_OE, OldPinDir);
  
  return (PANDABOARD_REVISION)((Revision >> 11) & 0x7);
#endif

  return 0;
}

/**
  Remap the memory at 0x0

  Some platform requires or gives the ability to remap the memory at the address 0x0.
  This function can do nothing if this feature is not relevant to your platform.

**/
VOID
ArmPlatformBootRemapping (
  VOID
  )
{
  // Do nothing for the PandaBoard
}

/**
  Return the current Boot Mode

  This function returns the boot reason on the platform

**/
EFI_BOOT_MODE
ArmPlatformGetBootMode (
  VOID
  )
{
  return BOOT_WITH_FULL_CONFIGURATION;
}

/**
  Initialize controllers that must setup at the early stage

  Some peripherals must be initialized in Secure World.
  For example, some L2x0 requires to be initialized in Secure World

**/
VOID
ArmPlatformNormalInitialize (
  VOID
  )
{
#if 0
  PANDABOARD_REVISION Revision;

  Revision = PandaBoardGetRevision();

  // Set up Pin muxing.
  PadConfiguration (Revision);

  // Set up system clocking
  ClockInit ();

  // Turn off the functional clock for Timer 3
  MmioAnd32 (CM_FCLKEN_PER, 0xFFFFFFFF ^ CM_ICLKEN_PER_EN_GPT3_ENABLE );
  ArmDataSyncronizationBarrier ();

  // Clear IRQs
  MmioWrite32 (INTCPS_CONTROL, INTCPS_CONTROL_NEWIRQAGR);
  ArmDataSyncronizationBarrier ();
#endif

  // Make sure GPMC region region 0 is disabled
  // Not doing so makes gpmc_init hang early in kernel init
  MmioAnd32 (GPMC_CONFIG7_0, ~CSVALID);

}

/**
  Initialize the system (or sometimes called permanent) memory

  This memory is generally represented by the DRAM.

**/
VOID
ArmPlatformInitializeSystemMemory (
  VOID
  )
{
  // Nothing done here, handled by the ROM Configuration Header

}

EFI_STATUS
PrePeiCoreGetMpCoreInfo (
  OUT UINTN                   *CoreCount,
  OUT ARM_CORE_INFO           **ArmCoreTable
  )
{
  *CoreCount    = sizeof(mVersatileExpressMpCoreInfoPandaBoard) / sizeof(ARM_CORE_INFO);
  *ArmCoreTable = mVersatileExpressMpCoreInfoPandaBoard;

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
  }
};

VOID
ArmPlatformGetPlatformPpiList (
  OUT UINTN                   *PpiListSize,
  OUT EFI_PEI_PPI_DESCRIPTOR  **PpiList
  )
{
  *PpiListSize = sizeof(gPlatformPpiTable);
  *PpiList = gPlatformPpiTable;
}
