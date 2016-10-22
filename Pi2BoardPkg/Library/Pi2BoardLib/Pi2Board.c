/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#include <Library/BaseMemoryLib.h>
#include <Ppi/ArmMpCoreInfo.h>

#include <Bcm2836.h>
#include <Pi2Board.h>
#include <BcmMailbox.h>

//
// We'll use Mailbox 3 for this since the Pi2 boot firmware already uses it
// for the initial parking of the secondary cores so we can use the definition
// both for the initial release and for the subsequent trigger for the MP
// Parking Protocol.
//
// NOTE: Windows uses the mailbox to be able to trigger the MP mailbox read
//       (substituting for the GIC feature supporting cross-core targetted
//       interrupts).

ARM_CORE_INFO mPi2InfoTable[] = {
    {
        // Core 0
        FixedPcdGet32(PcdCoresClusterId), 0x0,

        // MP Core MailBox Set/Get/Clear Addresses and Clear Value
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_WRITE_SET(0, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_READ(0, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_CLEAR(0, 3),
        (UINT64)CORE_MAILBOX_CLEAR_VALUE
    },
    {
        // Core 1
        FixedPcdGet32(PcdCoresClusterId), 0x1,

        // MP Core MailBox Set/Get/Clear Addresses and Clear Value
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_WRITE_SET(1, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_READ(1, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_CLEAR(1, 3),
        (UINT64)CORE_MAILBOX_CLEAR_VALUE
    },
    {
        // Core 2
        FixedPcdGet32(PcdCoresClusterId), 0x2,

        // MP Core MailBox Set/Get/Clear Addresses and Clear Value
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_WRITE_SET(2, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_READ(2, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_CLEAR(2, 3),
        (UINT64)CORE_MAILBOX_CLEAR_VALUE
    },
    {
        // Core 3
        FixedPcdGet32(PcdCoresClusterId), 0x3,

        // MP Core MailBox Set/Get/Clear Addresses and Clear Value
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_WRITE_SET(3, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_READ(3, 3),
        (EFI_PHYSICAL_ADDRESS)CORE_MAILBOX_CLEAR(3, 3),
        (UINT64)CORE_MAILBOX_CLEAR_VALUE
    }
};

VOID
HypExceptionVectorTable(
    VOID
    );

UINT32
ArmReadCPSRMode(
    VOID
    );

VOID
ArmSwitchFromHypToSvcMode(
    VOID
    );

volatile MAILBOX_GET_CLOCK_RATE MbGetMaxCR __attribute__((aligned(16)));
volatile MAILBOX_SET_CLOCK_RATE MbSetMaxCR __attribute__((aligned(16)));

/**
  Return the current Boot Mode

  This function returns the boot reason on the platform

**/
EFI_BOOT_MODE
ArmPlatformGetBootMode(
    VOID
    )
{
    return BOOT_WITH_FULL_CONFIGURATION;
}

BOOLEAN
SwitchToSvcMode(
    IN  UINTN                     MpId
    )
{
    ArmSwitchFromHypToSvcMode();

    UINT32 mode = ArmReadCPSRMode();
    if (mode == ARM_PROCESSOR_MODE_SUPERVISOR) {
        DEBUG((
            EFI_D_INIT,
            "Core%d running in SVC mode, switch succeeded\n",
            GET_CORE_ID(MpId)));
        return TRUE;
    } else {
        DEBUG((
            DEBUG_ERROR,
            "Core%d running in unexpected mode 0x%x, switch failed\n",
            GET_CORE_ID(MpId), mode));
        return FALSE;
    }
}

/**
  Initialize controllers that must setup at the early stage
**/
RETURN_STATUS
ArmPlatformInitialize(
    IN  UINTN                     MpId
    )
{
    SerialPortInitialize();

    // Output some information on what's being initilized.
    DEBUG((EFI_D_INIT, "Core%d MpId=0x%8.8X PriCore=%d StackPtr=0x%8.8p\n\r",
           GET_CORE_ID(MpId), MpId, ArmPlatformIsPrimaryCore(MpId), &MpId));

    // Virtualization is not currently supported by the OS
    // Switch to supervisor mode if booting in hypervisor mode
    {
        if (ArmReadCPSRMode() == ARM_PROCESSOR_MODE_HYP) {
            DEBUG((
                EFI_D_INIT,
                "Core%d running in HYP mode!! switching to SVC mode ...\n",
                GET_CORE_ID(MpId)));

            if (((UINT32)HypExceptionVectorTable & ARM_VECTOR_TABLE_ALIGNMENT) != 0) {
                ASSERT(0);
                return EFI_INVALID_PARAMETER;
            }

            ArmWriteHVBar((UINT32)HypExceptionVectorTable);

            if (!SwitchToSvcMode(MpId))
                return EFI_NOT_READY;
        }
    }

    // For multiprocessor support we need to ensure that the mailbox interrupt
    // hardware is enabled so that the secondary cores can exit out of WFI state
    // when the mailbox is set. The ARM core interrupt itself can be masked.
    // We're using Mailbox 3 for this purpose.
    {
        UINT32 CoreId;
        UINT32 Value;

        CoreId = GET_CORE_ID(MpId);

        Value = MmioRead32(INT_CORE_MAILBOX_CONTROL(CoreId));
        Value &= ~0x88; // Disable mailbox 3 IRQ and FIQ.
        Value |= 0x08; // Enable IRQ only.
        MmioWrite32(INT_CORE_MAILBOX_CONTROL(CoreId), Value);
    }

    if (ArmPlatformIsPrimaryCore(MpId)) {

        // Power on the USB Host Controller
        UINT32 MBData = POWER_USB << 4;

        DEBUG((EFI_D_INIT, "ArmPlatformInitialize writing 0x%8.8X to Mailbox to turn on USB controller\n", MBData));

        // Only USB controller is required to be turn on as other peripheral are by default
        // on. The open source SD card has remove code that access the mailbox
        if (!BcmMailboxWrite(MAILBOX_CHANNEL_POWER_MGMT, MBData)) {
            DEBUG((DEBUG_ERROR, "Failed to intialize USB Controller"));
        }

        DEBUG((DEBUG_VERBOSE, "ArmPlatformInitialize wrote 0x%8.8X to Mailbox\n", MBData));

        // Determine and set the max possible CPU clock speed and continue
        // to boot anyway in case any failure since this is not critical
        {
            EFI_STATUS Status;

            ZeroMem((void*)&MbGetMaxCR, sizeof(MbGetMaxCR));
            MbGetMaxCR.Header.BufferSize = sizeof(MbGetMaxCR);
            MbGetMaxCR.Header.TagID = TAG_GET_MAX_CLOCK_RATE;
            MbGetMaxCR.Header.TagLength = 8;
            MbGetMaxCR.ClockId = CLOCK_ID_ARM;

            Status = MailboxProperty(
                MAILBOX_CHANNEL_PROPERTY_ARM_VC,
                (MAILBOX_HEADER*)&MbGetMaxCR
                );
            if (EFI_ERROR(Status)) {
                DEBUG((DEBUG_ERROR, "Fail to query max ARM CPU clock rate\n"));
            } else {
                ZeroMem((void*)&MbSetMaxCR, sizeof(MbSetMaxCR));
                MbSetMaxCR.Header.BufferSize = sizeof(MbSetMaxCR);
                MbSetMaxCR.Header.TagID = TAG_SET_CLOCK_RATE;
                MbSetMaxCR.Header.TagLength = 8;
                MbSetMaxCR.ClockId = CLOCK_ID_ARM;
                MbSetMaxCR.Rate = MbGetMaxCR.Rate;
                MbSetMaxCR.SkipSettingTurbo = 1; 

                Status = MailboxProperty(
                    MAILBOX_CHANNEL_PROPERTY_ARM_VC,
                    (MAILBOX_HEADER*)&MbSetMaxCR
                    );
                if (EFI_ERROR(Status)) {
                    DEBUG((DEBUG_ERROR, "Fail to set max ARM CPU clock rate\n"));
                } else {
                    DEBUG((
                        EFI_D_INIT, 
                        "Setting ARM CPU to %d Hz\n", 
                        MbGetMaxCR.Rate));
                }
            }
        }
    }

    return RETURN_SUCCESS;
}

/**
  Initialize the system (or sometimes called permanent) memory

  This memory is generally represented by the DRAM.

**/
VOID
ArmPlatformInitializeSystemMemory(
    VOID
    )
{
    // We do not need to initialize the System Memory on Pi2.
}

EFI_STATUS
PrePeiCoreGetMpCoreInfo(
    OUT UINTN                   *CoreCount,
    OUT ARM_CORE_INFO           **ArmCoreTable
    )
{
    // Only support one cluster
    *CoreCount = sizeof(mPi2InfoTable) / sizeof(ARM_CORE_INFO);
    *ArmCoreTable = mPi2InfoTable;
    return EFI_SUCCESS;
}

// Needs to be declared in the file. Otherwise gArmMpCoreInfoPpiGuid is undefined in the contect of PrePeiCore
EFI_GUID mArmMpCoreInfoPpiGuid = ARM_MP_CORE_INFO_PPI_GUID;
ARM_MP_CORE_INFO_PPI mMpCoreInfoPpi = { PrePeiCoreGetMpCoreInfo };

EFI_PEI_PPI_DESCRIPTOR gPlatformPpiTable[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI,
    &mArmMpCoreInfoPpiGuid,
    &mMpCoreInfoPpi
  }
};

VOID
ArmPlatformGetPlatformPpiList(
    OUT UINTN                   *PpiListSize,
    OUT EFI_PEI_PPI_DESCRIPTOR  **PpiList
    )
{
    *PpiListSize = sizeof(gPlatformPpiTable);
    *PpiList = gPlatformPpiTable;
}

