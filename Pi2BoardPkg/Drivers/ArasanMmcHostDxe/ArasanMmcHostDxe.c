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
*  Edited by Jason Lin (Jason.Lin@microsoft.com), 7/18/2014
*
**/

#include "ArasanMmcHostDxe.h"
#include <BcmMailbox.h>

UINT8 mMaxDataTransferRate = 0;
UINT32 mRca = 0;
BOOLEAN PreviousIsCardPresent = FALSE;

// Related to the MBR+GPT Workaround
BOOLEAN MBRGPTWorkaroundEnabled;
UINT32 MBRGPTWorkaroundOffsetLba;
BOOLEAN MBRGPTWorkaroundReceivedCmdSendCSD;

// Ensure 16 byte alignment
volatile MAILBOX_GET_CLOCK_RATE MbGcr __attribute__((aligned(16)));

typedef struct
{
    VENDOR_DEVICE_PATH  Mmc;
    EFI_DEVICE_PATH     End;
} MMCHS_DEVICE_PATH;

MMCHS_DEVICE_PATH gMMCDevicePath =
{
    {
        {
            HARDWARE_DEVICE_PATH,
            HW_VENDOR_DP,
            {
                (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
                (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
            }
        },
        {
            0xb615f1f5, 0x5088, 0x43cd, { 0x80, 0x9c, 0xa1, 0x6e, 0x52, 0x48, 0x7d, 0x00 }
        }
    },
    {
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        {
            sizeof(EFI_DEVICE_PATH_PROTOCOL),
            0
        }
    }
};

/**
  These SD commands are optional, according to the SD Spec
**/
BOOLEAN
IgnoreCommand(
    UINT32 Command
    )
{
    switch (Command) {
    case MMC_CMD20:
        return TRUE;
    default:
        return FALSE;
    }
}

/**
  Translates a generic SD command into the format used by the Arasan SD Host Controller
**/
UINT32
TranslateCommand(
    UINT32 Command
    )
{
    UINT32 Translation;

    switch (Command) {
    case MMC_CMD0:
        Translation = CMD0;
        break;
    case MMC_CMD1:
        Translation = CMD1;
        break;
    case MMC_CMD2:
        Translation = CMD2;
        break;
    case MMC_CMD3:
        Translation = CMD3;
        break;
    case MMC_CMD5:
        Translation = CMD5;
        break;
    case MMC_CMD7:
        Translation = CMD7;
        break;
    case MMC_CMD8:
        Translation = CMD8;
        break;
    case MMC_CMD9:
        Translation = CMD9;
        break;
    case MMC_CMD11:
        Translation = CMD11;
        break;
    case MMC_CMD12:
        Translation = CMD12;
        break;
    case MMC_CMD13:
        Translation = CMD13;
        break;
    case MMC_CMD16:
        Translation = CMD16;
        break;
    case MMC_CMD17:
        Translation = CMD17;
        break;
    case MMC_CMD18:
        Translation = CMD18;
        break;
    case MMC_CMD23:
        Translation = CMD23;
        break;
    case MMC_CMD24:
        Translation = CMD24;
        break;
    case MMC_CMD55:
        Translation = CMD55;
        break;
    case MMC_ACMD41:
        Translation = ACMD41;
        break;
    case CMD55:
        Translation = CMD55;
        break;
    case ACMD6:
        Translation = ACMD6;
        break;
    default:
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: TranslateCommand(): Unrecognized Command: %d\n", Command));
        Translation = Command;
    }

    return Translation;
}

/**
  Repeatedly polls a register until its value becomes correct, or until MAX_RETRY_COUNT polls is reached
**/
EFI_STATUS
PollRegisterWithMask(
    IN UINTN Register,
    IN UINTN Mask,
    IN UINTN ExpectedValue
    )
{
    UINTN RetryCount = 0;

    while (RetryCount < MAX_RETRY_COUNT) {
        if ((MmioRead32(Register) & Mask) != ExpectedValue) {
            RetryCount++;
            gBS->Stall(STALL_AFTER_RETRY_US);
        } else {
            break;
        }
    }

    if (RetryCount == MAX_RETRY_COUNT) {
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

/**
  Calculate the clock divisor
**/
EFI_STATUS
CalculateClockFrequencyDivisor(
    IN UINTN TargetFrequency,
    OUT UINT32 *DivisorValue,
    OUT UINTN *ActualFrequency
    )
{
    EFI_STATUS Status;
    UINT32 Divisor;
    UINTN BaseFrequency;

    // First figure out the current base clock, this can be configure through config.txt
    ZeroMem((void*)&MbGcr, sizeof(MbGcr));
    MbGcr.Header.BufferSize = sizeof(MbGcr);
    MbGcr.Header.TagID = TAG_GET_CLOCK_RATE;
    MbGcr.Header.TagLength = 8;
    MbGcr.ClockId = CLOCK_ID_EMMC;

    Status = MailboxProperty(
        MAILBOX_CHANNEL_PROPERTY_ARM_VC,
        (MAILBOX_HEADER*)&MbGcr
        );
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: CalculateClockFrequencyDivisor fail to query base clock\n"));
        return Status;
    }

    BaseFrequency = MbGcr.Rate;

    Divisor = BaseFrequency / TargetFrequency;

    // Arasan controller is based on 3.0 spec so the div is multiple of 2 
    // Actual Frequency = BaseFequency/(Div*2)
    Divisor /= 2;

    if ((TargetFrequency < BaseFrequency) &&
        (TargetFrequency * 2 * Divisor != BaseFrequency)) {
        Divisor += 1;
    }

    if (Divisor > MAX_DIVISOR_VALUE) {
        Divisor = MAX_DIVISOR_VALUE;
    }

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: BaseFrequency 0x%x Divisor 0x%x\n", BaseFrequency, Divisor));

    *DivisorValue = (Divisor & 0xFF) << 8;
    Divisor >>= 8;
    *DivisorValue |= (Divisor & 0x03) << 6;

    if (ActualFrequency) {
        if (Divisor == 0) {
            *ActualFrequency = BaseFrequency;
        } else {
            *ActualFrequency = BaseFrequency / Divisor;
            *ActualFrequency >>= 1;
        }
        DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: *ActualFrequency 0x%x\n", *ActualFrequency));
    }

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: *DivisorValue 0x%x\n", *DivisorValue));

    return EFI_SUCCESS;
}

/**
  Calculate clock speed based on Card Specific Data
**/
EFI_STATUS
CalculateCardClock(
    UINTN *ClockFrequency
    )
{
    UINTN    TransferRateValue = 0;
    UINTN    TimeValue = 0;

    // Calculate Transfer rate unit (Bits 2:0 of TRAN_SPEED)
    switch (mMaxDataTransferRate & 0x7) // 2
    {
    case 0:
        TransferRateValue = 100 * 1000;
        break;

    case 1:
        TransferRateValue = 1 * 1000 * 1000;
        break;

    case 2:
        TransferRateValue = 10 * 1000 * 1000;
        break;

    case 3:
        TransferRateValue = 100 * 1000 * 1000;
        break;

    default:
        DEBUG((DEBUG_ERROR, "Invalid parameter.\n"));
        return EFI_INVALID_PARAMETER;
    }

    //Calculate Time value (Bits 6:3 of TRAN_SPEED)
    switch ((mMaxDataTransferRate >> 3) & 0xF) // 6
    {
    case 1:
        TimeValue = 10;
        break;

    case 2:
        TimeValue = 12;
        break;

    case 3:
        TimeValue = 13;
        break;

    case 4:
        TimeValue = 15;
        break;

    case 5:
        TimeValue = 20;
        break;

    case 6:
        TimeValue = 25;
        break;

    case 7:
        TimeValue = 30;
        break;

    case 8:
        TimeValue = 35;
        break;

    case 9:
        TimeValue = 40;
        break;

    case 10:
        TimeValue = 45;
        break;

    case 11:
        TimeValue = 50;
        break;

    case 12:
        TimeValue = 55;
        break;

    case 13:
        TimeValue = 60;
        break;

    case 14:
        TimeValue = 70;
        break;

    case 15:
        TimeValue = 80;
        break;

    default:
        DEBUG((DEBUG_ERROR, "Invalid parameter.\n"));
        return EFI_INVALID_PARAMETER;
    }

    *ClockFrequency = TransferRateValue * TimeValue / 10;

    DEBUG((DEBUG_MMCHOST_SD, "mMaxDataTransferRate: 0x%x, *ClockFrequency: %d Hz\n", mMaxDataTransferRate, *ClockFrequency));
    DEBUG((DEBUG_ERROR, "mMaxDataTransferRate: 0x%x, *ClockFrequency: %d Hz TransferRateValue 0x%x TimeValue 0x%x\n", mMaxDataTransferRate, *ClockFrequency, TransferRateValue, TimeValue));

    return EFI_SUCCESS;
}

BOOLEAN
MMCIsCardPresent(
    IN EFI_MMC_HOST_PROTOCOL *This
    )
{
    BOOLEAN IsCardPresent;

    // Enable all Interrupts ('Interrupts' is badly named, these are not ARM IRQ/FIQ Interrupts, but simply a register
    // that is repeatedly polled)
    MmioWrite32(MMCHS_IE, ALL_EN);
    IsCardPresent = (MmioRead32(MMCHS_INT_STAT) & CARD_INS) == CARD_INS;

    // This function is called multiple times per second. To reduce the number of DebugPrints, only print if the card
    // is NOT present, OR if the CardPresent state changes.
    if (IsCardPresent == FALSE || IsCardPresent != PreviousIsCardPresent) {
        DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCIsCardPresent(): %d\n", IsCardPresent));
    }
    PreviousIsCardPresent = IsCardPresent;
    return IsCardPresent;
}

BOOLEAN
MMCIsReadOnly(
    IN EFI_MMC_HOST_PROTOCOL *This
    )
{
    BOOLEAN IsReadOnly = !((MmioRead32(MMCHS_PRES_STATE) & WRITE_PROTECT_OFF) == WRITE_PROTECT_OFF);
    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCIsReadOnly(): %d\n", IsReadOnly));
    return IsReadOnly;
}

EFI_STATUS
MMCBuildDevicePath(
    IN EFI_MMC_HOST_PROTOCOL       *This,
    IN EFI_DEVICE_PATH_PROTOCOL    **DevicePath
    )
{
    EFI_DEVICE_PATH_PROTOCOL *NewDevicePathNode;
    EFI_GUID DevicePathGuid = EFI_CALLER_ID_GUID;

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCBuildDevicePath()\n"));

    NewDevicePathNode = CreateDeviceNode(HARDWARE_DEVICE_PATH, HW_VENDOR_DP, sizeof(VENDOR_DEVICE_PATH));
    CopyGuid(&((VENDOR_DEVICE_PATH*)NewDevicePathNode)->Guid, &DevicePathGuid);
    *DevicePath = NewDevicePathNode;

    return EFI_SUCCESS;
}

EFI_STATUS
MMCSendCommand(
    IN EFI_MMC_HOST_PROTOCOL    *This,
    IN MMC_CMD                  MmcCmd,
    IN UINT32                   Argument
    )
{
    UINTN MmcStatus;
    UINTN RetryCount = 0;
    UINTN CmdSendOKMask;

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCSendCommand(MmcCmd: %08x, Argument: %08x)\n", MmcCmd, Argument));

    if (IgnoreCommand(MmcCmd)) {
        return EFI_SUCCESS;
    }

    MmcCmd = TranslateCommand(MmcCmd);

    // Check if command and data lines are in use or not. Poll till both lines are available
    // However, for CMD12 (Stop Transmission), no need to wait for data line to be available
    if (MmcCmd == CMD_STOP_TRANSMISSION) {
        CmdSendOKMask = CMDI_MASK;
    } else {
        CmdSendOKMask = CMDI_MASK | DATI_MASK;
    }

    if (PollRegisterWithMask(MMCHS_PRES_STATE, CmdSendOKMask, 0) == EFI_TIMEOUT) {
        // CMD13 COULD time out (especially if following a WRITE). The Port Driver will automatically call CMD13
        // again many times. If THAT also fails, then the Port Driver will also print out an error message.
        // So sporadic printouts of the message below for CMD13 shoud be fine.
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCSendCommand(): TIMEOUT: Wait for CMD/DATA line, CMD: %x ", MmcCmd));
        if (MmcCmd == CMD13) {
            DEBUG((DEBUG_ERROR, "**This is CMD13 (GET_STATUS) timing out, should be OK if no other errors seen.**",
                   MmcCmd));
        }
        DEBUG((DEBUG_ERROR, "\n"));
        return EFI_TIMEOUT;
    }

    // Provide (Block Count << 16 | Block Size)
    // CMD23 (SET_BLOCK_COUNT) is sent before CMD18 (READ_MULTIPLE_BLOCK),
    // and sets the number of blocks to read in CMD18
    if (MmcCmd == CMD_SET_BLOCK_COUNT) {
        MmioWrite32(MMCHS_BLK, Argument << BLOCK_COUNT_SHIFT | BLEN_512BYTES);
    }
    // For CMD17 and CMD24 (read and write single block), Block Count is 0
    else if (MmcCmd == CMD_READ_SINGLE_BLOCK || MmcCmd == CMD_WRITE_SINGLE_BLOCK) {
        MmioWrite32(MMCHS_BLK, BLEN_512BYTES);
    }

    // Set Data timeout counter value to max value.
    MmioAndThenOr32(MMCHS_SYSCTL, ~DTO_MASK, DTO_VAL);

    // Clear Interrupt Status Register, but not the Card Inserted bit, because the SD port driver polls
    // the Card Inserted bit periodically and assumes card is removed if Card Inserted bit is cleared
    MmioWrite32(MMCHS_INT_STAT, ALL_EN & (~CARD_INS));

    // Set command argument register
    // Workaround for MBR+GPT on SD Card. Offset all IO accesses to card so that the GPT Header
    // looks like LBA 0 on the card.
    if ((MBRGPTWorkaroundEnabled == TRUE) &&
        (MmcCmd == CMD_READ_SINGLE_BLOCK || MmcCmd == CMD_READ_MULTIPLE_BLOCK ||
         MmcCmd == CMD_WRITE_SINGLE_BLOCK || MmcCmd == CMD_WRITE_MULTIPLE_BLOCK)) {
        // 'Argument' is the requested LBA from the SD Port Driver
        MmioWrite32(MMCHS_ARG, Argument + MBRGPTWorkaroundOffsetLba);
    } else {
        MmioWrite32(MMCHS_ARG, Argument);
    }

    // Workaround for MBR+GPT on SD Card. The SD Card size reported to the SD Port Driver needs
    // to be decreased, since we are carving out a portion of the entire Card for the GPT portion.
    // The CSD (Card-Specific Data) data structure contains the size of the card. When CMD_SEND_CSD
    // is received, keep track, so that the next call to MMCReceiveResponse() will return
    // the modified smaller card size.
    if ((MmcCmd == CMD_SEND_CSD) && (MBRGPTWorkaroundEnabled == TRUE)) {
        MBRGPTWorkaroundReceivedCmdSendCSD = TRUE;
    } else {
        MBRGPTWorkaroundReceivedCmdSendCSD = FALSE;
    }

    // Send the command
    MmioWrite32(MMCHS_CMD, MmcCmd);

    // Check for the command status.
    while (RetryCount < MAX_RETRY_COUNT) {
        MmcStatus = MmioRead32(MMCHS_INT_STAT);

        // Read status of command response
        if ((MmcStatus & ERRI) != 0) {
            // Perform soft-reset for mmci_cmd line.
            MmioOr32(MMCHS_SYSCTL, SRC);
            while ((MmioRead32(MMCHS_SYSCTL) & SRC));

            // CMD5 (CMD_IO_SEND_OP_COND) is only valid for SDIO cards and thus expected to fail
            if (MmcCmd != CMD_IO_SEND_OP_COND) {
                DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCSendCommand(): ERROR in Pres Status Reg: %08x\n", MmcStatus));
            }

            return EFI_DEVICE_ERROR;
        }

        // Check if command is completed.
        if ((MmcStatus & CC) == CC) {
            MmioWrite32(MMCHS_INT_STAT, CC);
            break;
        }

        RetryCount++;
        gBS->Stall(STALL_AFTER_RETRY_US);
    }

    gBS->Stall(STALL_AFTER_SEND_CMD_US);

    if (RetryCount == MAX_RETRY_COUNT) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCSendCommand(): TIMEOUT: No response for Send Command\n"));
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
MMCNotifyState(
    IN EFI_MMC_HOST_PROTOCOL    *This,
    IN MMC_STATE                State
    )
{
    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCNotifyState(State: %d)\n", State));

    switch (State) {
    case MmcHwInitializationState:
    {
        EFI_STATUS Status;
        UINT32 Divisor;
        // Soft reset for all
        MmioOr32(MMCHS_SYSCTL, SRC);
        if (PollRegisterWithMask(MMCHS_SYSCTL, SRA, 0) == EFI_TIMEOUT) {
            DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCNotifyState(): TIMEOUT: Soft reset for all\n"));
            return EFI_TIMEOUT;
        }

        // Attempt to set the clock to 400Khz which is the expected initialization speed
        Status = CalculateClockFrequencyDivisor(400000, &Divisor, NULL);
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCNotifyState(): Fail to initialize SD clock\n"));
            return Status;
        }

        // Set Data Timeout Counter value, set clock frequency, enable internal clock
        MmioOr32(MMCHS_SYSCTL, DTO_VAL | Divisor | CEN | ICS | ICE);

        // Enable interrupts
        MmioWrite32(MMCHS_IE, ALL_EN);
    }
    break;
    case MmcIdleState:
        break;
    case MmcReadyState:
        break;
    case MmcIdentificationState:
        break;
    case MmcStandByState:
    {
        EFI_STATUS Status;
        UINTN ClockFrequency = 25000000;
        UINT32 Divisor;

        // Standby state is set right after card specific data is acquired.
        // This would be a good time to set the clock frequency based on card

        // First turn off the clock
        MmioAnd32(MMCHS_SYSCTL, ~CEN);

        // 
        // Commenting out calculating card speed as there is a bug in the way the driver
        // captures the SDCard CSD TRAN_SPEED in MMCReceiveResponse, see comment there
        // Instead, use 25Mhz which is the mandotory maximum normal speed 12.5MB/s
        //
        /*
        Status = CalculateCardClock(&ClockFrequency);
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MmcStandByState(): ClockFrequency 0x%x\n", ClockFrequency));
        if(EFI_ERROR(Status))
        {
            DEBUG((DEBUG_ERROR, "ArasanMMCHost: MmcStandByState(): Fail to initialize SD clock\n"));
            return Status;
        }
        */

        Status = CalculateClockFrequencyDivisor(ClockFrequency, &Divisor, NULL);
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR, "ArasanMMCHost: MmcStandByState(): Fail to initialize SD clock\n"));
            return Status;
        }

        // Setup new divisor
        MmioAndThenOr32(MMCHS_SYSCTL, ~CLKD_MASK, Divisor);

        // Wait for the clock to stabilise
        while ((MmioRead32(MMCHS_SYSCTL) & ICS_MASK) != ICS);

        // Set Data Timeout Counter value, set clock frequency, enable internal clock
        MmioOr32(MMCHS_SYSCTL, CEN);
    }
    break;
    case MmcTransferState:
        break;
    case MmcSendingDataState:
        break;
    case MmcReceiveDataState:
        break;
    case MmcProgrammingState:
        break;
    case MmcDisconnectState:
    case MmcInvalidState:
    default:
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCNotifyState(): Invalid State: %d\n", State));
        ASSERT(0);
    }

    return EFI_SUCCESS;
}

EFI_STATUS
MMCReceiveResponse(
    IN EFI_MMC_HOST_PROTOCOL    *This,
    IN MMC_RESPONSE_TYPE        Type,
    IN UINT32*                  Buffer
    )
{
    UINTN OriginalCardSize;
    UINTN WorkaroundCardSize;

    if (Buffer == NULL) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCReceiveResponse(): Input Buffer is NULL\n"));
        return EFI_INVALID_PARAMETER;
    }

    if (Type == MMC_RESPONSE_TYPE_R2) // 16-byte response
    {
        Buffer[0] = MmioRead32(MMCHS_RSP10);
        Buffer[1] = MmioRead32(MMCHS_RSP32);
        Buffer[2] = MmioRead32(MMCHS_RSP54);
        Buffer[3] = MmioRead32(MMCHS_RSP76);

        DEBUG((
            DEBUG_MMCHOST_SD,
            "ArasanMMCHost: MMCReceiveResponse(Type: %x), Buffer[0-3]: %08x, %08x, %08x, %08x\n",
            Type, Buffer[0], Buffer[1], Buffer[2], Buffer[3]));
    } else  // 4-byte response
    {
        Buffer[0] = MmioRead32(MMCHS_RSP10);
        DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCReceiveResponse(Type: %08x), Buffer[0]: %08x\n", Type, Buffer[0]));
    }

    //
    // BUG: Drive has to keep track of all executed commands and ONLY
    // capture TRAN_SPEED from CSD if the last executed command is CMD9
    // if (Type == MMC_RESPONSE_TYPE_CSD && LastExecutedCommand == MMC_CMD9)
    // The same goes for RCA, but this driver is lucky because the sequence
    // MmcDxe execute commands happen to hide this bug.
    // if (Type == MMC_RESPONSE_TYPE_RCA && LastExecutedCommand == MMC_CMD3)
    //
    if (Type == MMC_RESPONSE_TYPE_CSD) {
        mMaxDataTransferRate = Buffer[3] & 0xFF;
    } else if (Type == MMC_RESPONSE_TYPE_RCA) {
        mRca = Buffer[0] >> RCA_SHIFT;
    }

    // Workaround for MBR+GPT on SD Card.
    // Return a smaller card size in the CSD, since we carved out a
    // portion of the entire Card for the GPT portion.
    if ((MBRGPTWorkaroundReceivedCmdSendCSD == TRUE) && (MBRGPTWorkaroundEnabled == TRUE)) {
        // The SD Spec's 'CardSize' terminology is confusing. To determine 'Real Card Size' (in bytes):
        // 'CardSize' = HC_MMC_CSD_GET_DEVICESIZE(Buffer);
        // NumBlocks = (('CardSize' + 1) * 1024);
        // 'RealCardSize' = NumBlocks * BLOCK_SIZE_IN_BYTES; (BLOCK_SIZE_IN_BYTES is 512)
        //
        // So to decrease NumBlocks by MBRGPTWorkaroundOffsetLba, we can decrease
        // 'CardSize' by (MBRGPTWorkaroundOffsetLba / 1024).
        //
        // ***** This card size calculation method only works for High Capacity SD Cards.
        // ***** For non-HC Cards the calculation is completely different.
        // ***** But detecting the card type in the miniport driver is very complicated.
        // ***** Since we are all using HC-Cards, this should be fine!

        OriginalCardSize = HC_MMC_CSD_GET_DEVICESIZE(Buffer);
        WorkaroundCardSize = OriginalCardSize - MBRGPTWorkaroundOffsetLba / 1024;

        Buffer[1] &= 0x0000FFFF;
        Buffer[1] |= (WorkaroundCardSize & 0x0000FFFF) << 16;

        Buffer[2] &= ~0x0000003F;
        Buffer[2] |= (WorkaroundCardSize >> 16) & 0x0000003F;

        MBRGPTWorkaroundReceivedCmdSendCSD = FALSE;
    }

    gBS->Stall(STALL_AFTER_REC_RESP_US);
    return EFI_SUCCESS;
}

EFI_STATUS
MMCReadBlockData(
    IN EFI_MMC_HOST_PROTOCOL    *This,
    IN EFI_LBA                  Lba,
    IN UINTN                    Length,
    IN UINT32*                  Buffer
    )
{
    UINTN MmcStatus;
    UINTN Count;
    UINTN RetryCount = 0;

    // Make DebugPrints more manageable
    if (Lba % 2000 == 0) {
        DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCReadBlockData(LBA: 0x%x, Length: 0x%x, Buffer: 0x%x)\n",
               Lba, Length, Buffer));
    }

    if (Buffer == NULL) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCReadBlockData(): Input Buffer is NULL\n"));
        return EFI_INVALID_PARAMETER;
    }

    if (Length % BLEN_512BYTES != 0) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCReadBlockData(): Length (%d B) is not a multiple of 512\n", Length));
        return EFI_INVALID_PARAMETER;
    }

    LedSetOk(TRUE);
    {
        while (RetryCount < MAX_RETRY_COUNT) {
            // Read Status
            MmcStatus = MmioRead32(MMCHS_INT_STAT);

            // Check if Buffer Read Ready (BRR) bit is set
            if (MmcStatus & BRR) {
                // Clear BRR bit
                MmioWrite32(MMCHS_INT_STAT, BRR);

                for (Count = 0; Count < Length / 4; Count++) {
                    UINT32 data = MmioRead32(MMCHS_DATA);
                    Buffer[Count] = data;
                }

                break;
            }

            gBS->Stall(STALL_AFTER_RETRY_US);
            RetryCount++;
        }

        gBS->Stall(STALL_AFTER_READ_US);
    }
    LedSetOk(FALSE);

    if (RetryCount == MAX_RETRY_COUNT) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCReadBlockData(): TIMEOUT waiting for BRR, MMCHS_INT_STAT: %08x\n",
               MmcStatus));
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
MMCWriteBlockData(
    IN EFI_MMC_HOST_PROTOCOL    *This,
    IN EFI_LBA                  Lba,
    IN UINTN                    Length,
    IN UINT32*                  Buffer
    )
{
    UINTN MmcStatus;
    UINTN Count;
    UINTN RetryCount = 0;

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCWriteBlockData(LBA: 0x%x, Length: 0x%x, Buffer: 0x%x)\n",
           Lba, Length, Buffer));

    if (Buffer == NULL) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCWriteBlockData(): Input Buffer is NULL\n"));
        return EFI_INVALID_PARAMETER;
    }

    if (Length % BLEN_512BYTES != 0) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCWriteBlockData(): Length (%d B) is not a multiple of 512\n", Length));
        return EFI_INVALID_PARAMETER;
    }

    LedSetOk(TRUE);
    {
        while (RetryCount < MAX_RETRY_COUNT) {
            // Read Status
            MmcStatus = MmioRead32(MMCHS_INT_STAT);

            // Check if Buffer Write Ready (BWR) bit is set
            if (MmcStatus & BWR) {
                // Clear BWR bit
                MmioWrite32(MMCHS_INT_STAT, BWR);

                for (Count = 0; Count < Length / 4; Count++) {
                    MmioWrite32(MMCHS_DATA, Buffer[Count]);
                }

                break;
            }

            gBS->Stall(STALL_AFTER_RETRY_US);
            RetryCount++;
        }

        gBS->Stall(STALL_AFTER_WRITE_US);
    }
    LedSetOk(FALSE);

    if (RetryCount == MAX_RETRY_COUNT) {
        DEBUG((DEBUG_ERROR, "ArasanMMCHost: MMCWriteBlockData(): TIMEOUT waiting for BWR, MMCHS_INT_STAT: %08x\n",
               MmcStatus));
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

EFI_MMC_HOST_PROTOCOL gMMCHost =
{
    MMC_HOST_PROTOCOL_REVISION,
    MMCIsCardPresent,
    MMCIsReadOnly,
    MMCBuildDevicePath,
    MMCNotifyState,
    MMCSendCommand,
    MMCReceiveResponse,
    MMCReadBlockData,
    MMCWriteBlockData
};

EFI_STATUS
MMCInitialize(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
    )
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = NULL;

    DEBUG((DEBUG_MMCHOST_SD, "ArasanMMCHost: MMCInitialize()\n"));

    Status = gBS->InstallMultipleProtocolInterfaces(
        &Handle,
        &gEfiMmcHostProtocolGuid, &gMMCHost,
        NULL
        );
    ASSERT_EFI_ERROR(Status);

    MBRGPTWorkaroundReceivedCmdSendCSD = FALSE;
    MBRGPTWorkaroundEnabled = FixedPcdGetBool(PcdArasanSDCardMBRGPTWorkaroundEnabled);
    MBRGPTWorkaroundOffsetLba = FixedPcdGet32(PcdArasanSDCardMBRGPTWorkaroundGPTOffsetLba);
    if ((MBRGPTWorkaroundEnabled == TRUE) && ((MBRGPTWorkaroundOffsetLba % 1024) != 0)) {
        DEBUG((DEBUG_ERROR,
               "ArasanMMCHost: PcdArasanSDCardMBRGPTWorkaroundGPTOffsetLba must be a multiple of 1024 (0x400)!\n"));
        ASSERT(0);
    }

    // Init the LED to use as a disk access indicator
    LedInit();

    return Status;
}
