/** @file
*
*  Copyright (c) 2011-2014, ARM Limited. All rights reserved.
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

#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "Mmc.h"

#define USE_STREAM

#define MAX_RETRY_COUNT  1000
#define CMD_RETRY_COUNT  20
#define MAX_BLOCK_COUNT 4096

#define TPL_FIRMWARE_INTERRUPTS   ((EFI_TPL)((int) TPL_NOTIFY + 1))
#define TPL_FOR_MMC_BLOCK_IO      TPL_FIRMWARE_INTERRUPTS

EFI_TPL
CurrentTpl() {
  const EFI_TPL Current = gBS->RaiseTPL(TPL_HIGH_LEVEL) ;
  gBS->RestoreTPL(Current) ;
  return Current ;
}

EFI_TPL
RaiseTplIfLow() {
  EFI_TPL Current = CurrentTpl() ;
  /*
    UEFI Spec states:
    TPL_CALLBACK Interrupts code executing below TPL_CALLBACK level. Long
      term operations (such as file system operations and disk I/O) can occur
      at this level.
    TPL_NOTIFY Interrupts code executing below TPL_NOTIFY level. Blocking is
      not allowed at this level. Code executes to completion and returns. If
      code requires more processing, it needs to signal an event to wait to
      obtain control again at whatever level it requires. This level is
      typically used to process low level IO to or from a device.
    (Firmware Interrupts) This level is internal to the firmware . It is the
      level at which internal interrupts occur. Code running at this level
      interrupts code running at the TPL_NOTIFY level (or lower levels). If
      the interrupt requires extended time to complete, firmware signals
      another event (or events) to perform the longer term operations so that
      other interrupts can occur.
   */
  if (Current < TPL_FOR_MMC_BLOCK_IO) {
    Current = gBS->RaiseTPL(TPL_FOR_MMC_BLOCK_IO) ;
  }
  return Current ;
}

#include "Mmc.h"

EFI_STATUS
MmcNotifyState (
  IN MMC_HOST_INSTANCE *MmcHostInstance,
  IN MMC_STATE State
  )
{
  MmcHostInstance->State = State;
  return MmcHostInstance->MmcHost->NotifyState (MmcHostInstance->MmcHost, State);
}

EFI_STATUS
EFIAPI
MmcGetCardStatus (
  IN MMC_HOST_INSTANCE     *MmcHostInstance
  )
{
  EFI_STATUS              Status;
  UINT32                  Response[4];
  UINTN                   CmdArg;
  EFI_MMC_HOST_PROTOCOL   *MmcHost;

  Status = EFI_SUCCESS;
  MmcHost = MmcHostInstance->MmcHost;
  CmdArg = 0;

  if (MmcHost == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (MmcHostInstance->State != MmcHwInitializationState) {
    //Get the Status of the card.
    CmdArg = MmcHostInstance->CardInfo.RCA << 16;
    Status = MmcHost->SendCommand (MmcHost, MMC_CMD13, CmdArg, NULL);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "MmcGetCardStatus(MMC_CMD13): Error and Status = %r\n", Status));
      return Status;
    }

    //Read Response
    MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_R1, Response);
    PrintResponseR1 (Response[0]);
  }

  return Status;
}

EFI_STATUS
EFIAPI
MmcIdentificationMode (
  IN MMC_HOST_INSTANCE     *MmcHostInstance
  )
{
  EFI_STATUS              Status;
  UINT32                  Response[4];
  UINTN                   Timeout;
  UINTN                   CmdArg;
  BOOLEAN                 IsHCS;
  EFI_MMC_HOST_PROTOCOL   *MmcHost;

  MmcHost = MmcHostInstance->MmcHost;
  CmdArg = 0;
  IsHCS = FALSE;

  if (MmcHost == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // We can get into this function if we restart the identification mode
  if (MmcHostInstance->State == MmcHwInitializationState) {
    // Initialize the MMC Host HW
    Status = MmcNotifyState (MmcHostInstance, MmcHwInitializationState);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "MmcIdentificationMode() : Error MmcHwInitializationState\n"));
      return Status;
    }
  }

  Status = MmcHost->SendCommand (MmcHost, MMC_CMD0, 0, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode(MMC_CMD0): Error\n"));
    return Status;
  }

  Status = MmcNotifyState (MmcHostInstance, MmcIdleState);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode() : Error MmcIdleState\n"));
    return Status;
  }

  // Are we using SDIO ?
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD5, 0, NULL);

#if 1 // Added for Panda Board
  /* It seems few SD cards need some time to recover from this command? */
  MicroSecondDelay(1000);
#endif
  
  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode(MMC_CMD5): Error - SDIO not supported.\n"));
    return EFI_UNSUPPORTED;
  }

  // Check which kind of card we are using. Ver2.00 or later SD Memory Card (PL180 is SD v1.1)
  CmdArg = (0x0UL << 12 | BIT8 | 0xCEUL << 0);
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD8, CmdArg, NULL);
  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Card is SD2.0 => Supports high capacity\n"));
    IsHCS = TRUE;
    MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_R7, Response);
    PrintResponseR1 (Response[0]);
    //check if it is valid response
    if ((Response[0] & 0xFF) != (CmdArg & 0xFF)){
      DEBUG ((EFI_D_ERROR, "The Card is not usable\n"));
      return EFI_UNSUPPORTED;
    }
  } else {
    DEBUG ((EFI_D_ERROR, "Not a SD2.0 Card\n"));
  }

  // We need to wait for the MMC or SD card is ready => (gCardInfo.OCRData.PowerUp == 1)
  Timeout = MAX_RETRY_COUNT;
  while (Timeout > 0) {
    // SD Card or MMC Card ? CMD55 indicates to the card that the next command is an application specific command
    Status = MmcHost->SendCommand (MmcHost, MMC_CMD55, 0, NULL);
    if (Status == EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO, "Card should be SD\n"));
      if (IsHCS) {
        MmcHostInstance->CardInfo.CardType = SD_CARD_2;
      } else {
        MmcHostInstance->CardInfo.CardType = SD_CARD;
      }

      // Note: The first time CmdArg will be zero
      CmdArg = ((UINTN *) &(MmcHostInstance->CardInfo.OCRData))[0];
      if (IsHCS) {
        CmdArg |= BIT30;
      }
      Status = MmcHost->SendCommand (MmcHost, MMC_ACMD41, CmdArg, NULL);
      if (!EFI_ERROR (Status)) {
        MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_OCR, Response);
        ((UINT32 *) &(MmcHostInstance->CardInfo.OCRData))[0] = Response[0];
      }
    } else {
      DEBUG ((EFI_D_INFO, "Card should be MMC\n"));
      MmcHostInstance->CardInfo.CardType = MMC_CARD;

      Status = MmcHost->SendCommand (MmcHost, MMC_CMD1, 0x800000, NULL);

      if (!EFI_ERROR (Status)) {
        MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_OCR, Response);
        ((UINT32 *) &(MmcHostInstance->CardInfo.OCRData))[0] = Response[0];
      }
    }

    if (!EFI_ERROR (Status)) {
      if (!MmcHostInstance->CardInfo.OCRData.PowerUp) {
        MicroSecondDelay (1);
        Timeout--;
      } else {
        if ((MmcHostInstance->CardInfo.CardType == SD_CARD_2) && (MmcHostInstance->CardInfo.OCRData.AccessMode & BIT1)) {
          MmcHostInstance->CardInfo.CardType = SD_CARD_2_HIGH;
          DEBUG ((EFI_D_ERROR, "High capacity card.\n"));
        }
        break;  // The MMC/SD card is ready. Continue the Identification Mode
      }
    } else {
      MicroSecondDelay (1);
      Timeout--;
    }
  }

  if (Timeout == 0) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode(): No Card\n"));
    return EFI_NO_MEDIA;
  } else {
    PrintOCR (Response[0]);
  }

  Status = MmcNotifyState (MmcHostInstance, MmcReadyState);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode() : Error MmcReadyState\n"));
    return Status;
  }

  Status = MmcHost->SendCommand (MmcHost, MMC_CMD2, 0, NULL);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode(MMC_CMD2): Error\n"));
    return Status;
  }
  MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_CID, Response);
  PrintCID (Response);

  Status = MmcNotifyState (MmcHostInstance, MmcIdentificationState);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode() : Error MmcIdentificationState\n"));
    return Status;
  }

  //
  // Note, SD specifications say that "if the command execution causes a state change, it
  // will be visible to the host in the response to the next command"
  // The status returned for this CMD3 will be 2 - identification
  //
  CmdArg = 1;
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD3, CmdArg, NULL);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "MmcIdentificationMode(MMC_CMD3): Error\n"));
    return Status;
  }

  MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_RCA, Response);
  PrintRCA (Response[0]);

  // For MMC card, RCA is assigned by CMD3 while CMD3 dumps the RCA for SD card
  if (MmcHostInstance->CardInfo.CardType != MMC_CARD) {
    MmcHostInstance->CardInfo.RCA = Response[0] >> 16 & 0xffff;
  } else {
    MmcHostInstance->CardInfo.RCA = CmdArg;
  }

  return EFI_SUCCESS;
}

EFI_STATUS InitializeMmcDevice (
  IN  MMC_HOST_INSTANCE   *MmcHostInstance
  )
{
  UINT32                  Response[4];
  EFI_STATUS              Status;
  UINTN                   CardSize, NumBlocks, BlockSize, CmdArg;
  EFI_MMC_HOST_PROTOCOL   *MmcHost;
  UINTN                   BlockCount;

  BlockCount = 1;
  MmcHost = MmcHostInstance->MmcHost;

  MmcIdentificationMode (MmcHostInstance);

  //Send a command to get Card specific data
  CmdArg = MmcHostInstance->CardInfo.RCA << 16;
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD9, CmdArg, NULL);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "InitializeMmcDevice(MMC_CMD9): Error, Status=%r\n", Status));
    return Status;
  }
  //Read Response
  MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_CSD, Response);
  PrintCSD (Response);

  Status = MmcNotifyState (MmcHostInstance, MmcStandByState);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "InitializeMmcDevice() : Error MmcStandByState\n"));
    return Status;
  }

  if (MmcHostInstance->CardInfo.CardType == SD_CARD_2_HIGH) {
    CardSize = HC_MMC_CSD_GET_DEVICESIZE (Response);
    NumBlocks = ((CardSize + 1) * 1024);
    BlockSize = 1 << MMC_CSD_GET_READBLLEN (Response);
  } else {
    CardSize = MMC_CSD_GET_DEVICESIZE (Response);
    NumBlocks = (CardSize + 1) * (1 << (MMC_CSD_GET_DEVICESIZEMULT (Response) + 2));
    BlockSize = 1 << MMC_CSD_GET_READBLLEN (Response);
  }

  //For >=2G card, BlockSize may be 1K, but the transfer size is 512 bytes.
  if (BlockSize > 512) {
    NumBlocks = MultU64x32 (NumBlocks, BlockSize/512);
    BlockSize = 512;
  }

  MmcHostInstance->BlockIo.Media->LastBlock    = (NumBlocks - 1);
  MmcHostInstance->BlockIo.Media->BlockSize    = BlockSize;
  MmcHostInstance->BlockIo.Media->ReadOnly     = MmcHost->IsReadOnly (MmcHost);
  MmcHostInstance->BlockIo.Media->MediaPresent = TRUE;
  MmcHostInstance->BlockIo.Media->MediaId++;
  DEBUG((EFI_D_BLKIO, "InitializeMmcDevice: Numblock:%d BLocksize:%d\n", NumBlocks, BlockSize));

  CmdArg = MmcHostInstance->CardInfo.RCA << 16;
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD7, CmdArg, NULL);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "InitializeMmcDevice(MMC_CMD7): Error and Status = %r\n", Status));
    return Status;
  }

  Status = MmcNotifyState (MmcHostInstance, MmcTransferState);
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "InitializeMmcDevice(): Error MmcTransferState\n"));
    return Status;
  }

  // Set Block Length
  Status = MmcHost->SendCommand (MmcHost, MMC_CMD16, MmcHostInstance->BlockIo.Media->BlockSize, NULL);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "InitializeMmcDevice(MMC_CMD16): Error MmcHostInstance->BlockIo.Media->BlockSize: %d and Error = %r\n",
                        MmcHostInstance->BlockIo.Media->BlockSize, Status));
    return Status;
  }

  // Block Count (not used). Could return an error for SD card
  if (MmcHostInstance->CardInfo.CardType == MMC_CARD) {
    MmcHost->SendCommand (MmcHost, MMC_CMD23, BlockCount, NULL);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MmcReset (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN BOOLEAN                  ExtendedVerification
  )
{
  MMC_HOST_INSTANCE       *MmcHostInstance;

  MmcHostInstance = MMC_HOST_INSTANCE_FROM_BLOCK_IO_THIS (This);

  if (MmcHostInstance->MmcHost == NULL) {
    // Nothing to do
    return EFI_SUCCESS;
  }

  // If a card is not present then clear all media settings
  if (!MmcHostInstance->MmcHost->IsCardPresent (MmcHostInstance->MmcHost)) {
    MmcHostInstance->BlockIo.Media->MediaPresent = FALSE;
    MmcHostInstance->BlockIo.Media->LastBlock    = 0;
    MmcHostInstance->BlockIo.Media->BlockSize    = 512;  // Should be zero but there is a bug in DiskIo
    MmcHostInstance->BlockIo.Media->ReadOnly     = FALSE;

    // Indicate that the driver requires initialization
    MmcHostInstance->State = MmcHwInitializationState;

    return EFI_SUCCESS;
  }

  // Implement me. Either send a CMD0 (could not work for some MMC host) or just turn off/turn
  //      on power and restart Identification mode
  return EFI_SUCCESS;
}

EFI_STATUS
MmcDetectCard (
  EFI_MMC_HOST_PROTOCOL     *MmcHost
  )
{
  if (!MmcHost->IsCardPresent (MmcHost)) {
    return EFI_NO_MEDIA;
  } else {
    return EFI_SUCCESS;
  }
}

#define MMCI0_BLOCKLEN 512
#define MMCI0_TIMEOUT  10000

EFI_STATUS
MmcIoBlocks (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN UINTN                    Transfer,
  IN UINT32                   MediaId,
  IN EFI_LBA                  Lba,
  IN UINTN                    BufferSize,
  OUT VOID                    *Buffer
  )
{
  UINT32                  Response[4];
  EFI_STATUS              Status;
  UINTN                   CmdArg;
  INTN                    Timeout;
  UINTN                   Cmd;
  MMC_HOST_INSTANCE       *MmcHostInstance;
  EFI_MMC_HOST_PROTOCOL   *MmcHost;
  struct MMC_DATA         Mmc_Data;
  UINTN                   BytesRemainingToBeTransfered;
  UINTN                   BlockCount;
  EFI_TPL                 Tpl;

  BlockCount = 1;
  MmcHostInstance = MMC_HOST_INSTANCE_FROM_BLOCK_IO_THIS (This);
  ASSERT (MmcHostInstance != NULL);
  MmcHost = MmcHostInstance->MmcHost;
  ASSERT (MmcHost);

  if (This->Media->MediaId != MediaId) {
    return EFI_MEDIA_CHANGED;
  }

  if ((MmcHost == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  // Check if a Card is Present
  if (!MmcHostInstance->BlockIo.Media->MediaPresent) {
    return EFI_NO_MEDIA;
  }

  // All blocks must be within the device
  if ((Lba + (BufferSize / This->Media->BlockSize)) > (This->Media->LastBlock + 1)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((Transfer == MMC_IOBLOCKS_WRITE) && (This->Media->ReadOnly == TRUE)) {
    return EFI_WRITE_PROTECTED;
  }

  // Reading 0 Byte is valid
  if (BufferSize == 0) {
    return EFI_SUCCESS;
  }

  // The buffer size must be an exact multiple of the block size
  if ((BufferSize % This->Media->BlockSize) != 0) {
    return EFI_BAD_BUFFER_SIZE;
  }

  // Check the alignment
  if ((This->Media->IoAlign > 2) && (((UINTN)Buffer & (This->Media->IoAlign - 1)) != 0)) {
    return EFI_INVALID_PARAMETER;
  }

  BytesRemainingToBeTransfered = BufferSize;
  Mmc_Data.BlockSize =  This->Media->BlockSize;

  while (BytesRemainingToBeTransfered > 0) {
    BlockCount = (BytesRemainingToBeTransfered/This->Media->BlockSize) > MAX_BLOCK_COUNT ?
                  MAX_BLOCK_COUNT : (BytesRemainingToBeTransfered/This->Media->BlockSize);

    // Check if the Card is in Ready status
    CmdArg = MmcHostInstance->CardInfo.RCA << 16;
    Response[0] = 0;
    Timeout = MMCI0_TIMEOUT;

    while(   (!(Response[0] & MMC_R0_READY_FOR_DATA))
          && (MMC_R0_CURRENTSTATE (Response) != MMC_R0_STATE_TRAN)
          && Timeout--) {
      Status = MmcHost->SendCommand (MmcHost, MMC_CMD13, CmdArg, NULL);
      if (!EFI_ERROR (Status)) {
        MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_R1, Response);
      }
      NanoSecondDelay(100);
    }

    if (0 == Timeout) {
      DEBUG ((EFI_D_ERROR, "The Card is busy\n"));
      return EFI_NOT_READY;
    }

    //Set command argument based on the card access mode (Byte mode or Block mode)
    if (MmcHostInstance->CardInfo.OCRData.AccessMode & BIT1) {
      CmdArg = Lba;
    } else {
      CmdArg = Lba * This->Media->BlockSize;
    }

    if (Transfer == MMC_IOBLOCKS_READ) {
#ifndef USE_STREAM
      // Read a single block
      Cmd = MMC_CMD17;
#else
      if (BlockCount > 1)
        Cmd = MMC_CMD18;
      else
        Cmd = MMC_CMD17;
#endif
    } else {
#ifndef USE_STREAM
      // Write a single block
      Cmd = MMC_CMD24;
#else
      if (BlockCount > 1)
        Cmd = MMC_CMD24;
      else
        Cmd = MMC_CMD25;
#endif
    }
    // Raise Tpl to protect against Timer events between command and block IO
    Tpl = RaiseTplIfLow() ;
    Mmc_Data.Blocks = BlockCount;
    Status = MmcHost->SendCommand (MmcHost, Cmd, CmdArg, &Mmc_Data);

    if (EFI_ERROR (Status)) {
      gBS->RestoreTPL(Tpl);
      DEBUG ((EFI_D_ERROR, "MmcIoBlocks(MMC_CMD%d): Error %r\n", Cmd, Status));
      return Status;
    }

    if (Transfer == MMC_IOBLOCKS_READ) {
#ifndef USE_STREAM
      // Read one block of Data
      Status = MmcHost->ReadBlockData (MmcHost, Lba, This->Media->BlockSize, Buffer);
      gBS->RestoreTPL(Tpl) ;
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_BLKIO, "MmcIoBlocks(): Error Read Block Data and Status = %r\n", Status));
        return Status;
      }
#else
      Status = MmcHost->ReadBlockData (MmcHost, Lba, BlockCount * This->Media->BlockSize,Buffer);
      gBS->RestoreTPL(Tpl) ;
      if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_BLKIO, "MmcIoBlocks(): Error Read Block Data and Status = %r\n", Status));
        return Status;
      }
#endif
      Status = MmcNotifyState (MmcHostInstance, MmcProgrammingState);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "MmcIoBlocks() : Error MmcProgrammingState\n"));
        return Status;
      }
    } else {
#ifndef USE_STREAM
      // Write one block of Data
      Status = MmcHost->WriteBlockData (MmcHost, Lba, This->Media->BlockSize, Buffer);
      gBS->RestoreTPL(Tpl) ;
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_BLKIO, "MmcIoBlocks(): Error Write Block Data and Status = %r\n", Status));
        return Status;
      }
#else
      Status = MmcHost->WriteBlockData (MmcHost, Lba, BlockCount * This->Media->BlockSize, Buffer);
      gBS->RestoreTPL(Tpl) ;
      if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_BLKIO, "MmcIoBlocks(): Error Write Block Data and Status = %r\n", Status));
        return Status;
    }

#endif
    }

    if (BlockCount > 1) {
      // Command 12 - Stop transmission (ends read or write)
      Status = MmcHost->SendCommand (MmcHost, MMC_CMD12, 0, NULL);
      if (!EFI_ERROR (Status)) {
        MmcHost->ReceiveResponse (MmcHost, MMC_RESPONSE_TYPE_R1b, Response);
      }
    }

    Status = MmcNotifyState (MmcHostInstance, MmcTransferState);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "MmcIoBlocks() : Error MmcTransferState\n"));
      return Status;
    }

    BytesRemainingToBeTransfered -= BlockCount * This->Media->BlockSize;
    Lba    += BlockCount;
    Buffer = (UINT8 *)Buffer + BlockCount * This->Media->BlockSize;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MmcReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN UINT32                   MediaId,
  IN EFI_LBA                  Lba,
  IN UINTN                    BufferSize,
  OUT VOID                    *Buffer
  )
{
  return MmcIoBlocks (This, MMC_IOBLOCKS_READ, MediaId, Lba, BufferSize, Buffer);
}

EFI_STATUS
EFIAPI
MmcWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN UINT32                   MediaId,
  IN EFI_LBA                  Lba,
  IN UINTN                    BufferSize,
  IN VOID                     *Buffer
  )
{
  return MmcIoBlocks (This, MMC_IOBLOCKS_WRITE, MediaId, Lba, BufferSize, Buffer);
}

EFI_STATUS
EFIAPI
MmcFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}
