/** @file
  MMC/SD Card driver for Secure Digital Host Controller

  This driver always produces a BlockIo protocol but it starts off with no Media
  present. A TimerCallBack detects when media is inserted or removed and after
  a media change event a call to BlockIo ReadBlocks/WriteBlocks will cause the
  media to be detected (or removed) and the BlockIo Media structure will get
  updated. No MMC/SD Card harward registers are updated until the first BlockIo
  ReadBlocks/WriteBlocks after media has been insterted (booting with a card
  plugged in counts as an insertion event).

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>

#include "SDHCDxe.h"


EFI_BLOCK_IO_MEDIA gSDHCMedia = {
  SIGNATURE_32('s','d','h','c'),            // MediaId
  TRUE,                                     // RemovableMedia
  FALSE,                                    // MediaPresent
  FALSE,                                    // LogicalPartition
  FALSE,                                    // ReadOnly
  FALSE,                                    // WriteCaching
  512,                                      // BlockSize
  4,                                        // IoAlign
  0,                                        // Pad
  0                                         // LastBlock
};

typedef struct {
  VENDOR_DEVICE_PATH  Mmc;
  EFI_DEVICE_PATH     End;
} SDHC_DEVICE_PATH;

SDHC_DEVICE_PATH gSDHCDevicePath = {
  {
    HARDWARE_DEVICE_PATH,
    HW_VENDOR_DP,
    (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
    (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
    0xb615f1f5, 0x5088, 0x43cd, 0x80, 0x9c, 0xa1, 0x6e, 0x52, 0x48, 0x7d, 0x00
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    sizeof (EFI_DEVICE_PATH_PROTOCOL),
    0
  }
};

CARD_INFO                  gCardInfo;
EFI_EVENT                  gTimerEvent;
BOOLEAN                    gMediaChange = FALSE;

//
// Internal Functions
//


VOID
ParseCardCIDData (
  UINT32 Response0,
  UINT32 Response1,
  UINT32 Response2,
  UINT32 Response3
  )
{
  gCardInfo.CIDData.MDT = ((Response0 >> 8) & 0xFFF);
  gCardInfo.CIDData.PSN = (((Response0 >> 24) & 0xFF) | ((Response1 & 0xFFFFFF) << 8));
  gCardInfo.CIDData.PRV = ((Response1 >> 24) & 0xFF);
  gCardInfo.CIDData.PNM[4] = ((Response2) & 0xFF);
  gCardInfo.CIDData.PNM[3] = ((Response2 >> 8) & 0xFF);
  gCardInfo.CIDData.PNM[2] = ((Response2 >> 16) & 0xFF);
  gCardInfo.CIDData.PNM[1] = ((Response2 >> 24) & 0xFF);
  gCardInfo.CIDData.PNM[0] = ((Response3) & 0xFF);
  gCardInfo.CIDData.OID = ((Response3 >> 8) & 0xFFFF);
  gCardInfo.CIDData.MID = ((Response3 >> 24) & 0xFF);
}


VOID
UpdateSDHCClkFrequency (
  UINTN NewCLK
  )
{
  UINT32 CumBaseAddr;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
 // Disable all clocks to not provide the clock to the card
  MmioAnd32 ((SdMmcBaseAddr + CLKCON_OFFSET), ~(0xF));

  CumBaseAddr = PcdGet32(PcdCmuBase);
  //Set new clock frequency.
  if (NewCLK == 400)
		MmioAndThenOr32 ((CumBaseAddr + CLK_DIV_FSYS2_OFFSET), ~(0xFFFF), 0xE008);
  else if (NewCLK == 25000)
		MmioAndThenOr32 ((CumBaseAddr + CLK_DIV_FSYS2_OFFSET), ~(0xFFFF), 0x0307);

  MmioOr32 ((SdMmcBaseAddr + CLKCON_OFFSET), ICE);

  //Poll till Internal Clock Stable
  while ((MmioRead32 ((SdMmcBaseAddr + CLKCON_OFFSET)) & ICS) != ICS);

  //Set Clock enable to 0x1 to provide the clock to the card
  MmioOr32 ((SdMmcBaseAddr + CLKCON_OFFSET), CCE);
}

VOID
PrepareTransfer (
	UINTN	Direction, UINTN BlockCount
	)
{
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
  //Set Block Size and Block count.
  MmioWrite32 ((SdMmcBaseAddr + BLKSIZE_OFFSET), BLEN_512BYTES | (BlockCount << 16));

  //Setting Data timeout counter value to max value.
  MmioAndThenOr32 ((SdMmcBaseAddr + TIMEOUTCON_OFFSET), ~(0xFF << 16), 0xE << 16);
}

EFI_STATUS
SendCmd (
  UINTN Cmd,
  UINTN CmdInterruptEnableVal,
  UINTN CmdArgument
  )
{
  UINTN MmcStatus;
  UINTN RetryCount = 0;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  //Check if command line is in use or not. Poll till command line is available.
  while (MmioRead32 ((SdMmcBaseAddr + PRNSTS_OFFSET)) & (CMDINHCMD | CMDINHDAT));
 //Clear Status register.
  MmioWrite32 ((SdMmcBaseAddr + INTSTS_OFFSET), 0xFFFFFFFF);

  //Set command argument register
  MmioWrite32 ((SdMmcBaseAddr + ARGUMENT_OFFSET), CmdArgument);

  //Enable interrupt enable events to occur
  MmioWrite32 ((SdMmcBaseAddr + INTEN_OFFSET), CmdInterruptEnableVal);

	DEBUG ((EFI_D_INFO, "SDHC::SendCmd : CMD = %d\n", (Cmd >> 24) & 0x3F));

  MmioAndThenOr32 ((SdMmcBaseAddr + TIMEOUTCON_OFFSET), ~(0xFF << 16), 0xE << 16);
  MicroSecondDelay(1);
  //Send a command
  MmioWrite32 ((SdMmcBaseAddr + CMDREG_OFFSET), Cmd);
  MicroSecondDelay(1);

  //Check for the command status.
  while (RetryCount < MAX_RETRY_COUNT) {
    do {
      MmcStatus = MmioRead32 ((SdMmcBaseAddr + INTSTS_OFFSET));
    } while (MmcStatus == 0);

    //Read status of command response
    if ((MmcStatus & ERRINT) != 0) {

      //Perform soft-reset for cmd line.
      MmioOr32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRC);
      while ((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRC));

      DEBUG ((EFI_D_INFO, "MmcStatus: %x\n", MmcStatus));
      return EFI_DEVICE_ERROR;
    }

    //Check if command is completed.
    if ((MmcStatus & CMDCOMP) == CMDCOMP) {
      MmioWrite32 ((SdMmcBaseAddr + INTSTS_OFFSET), CMDCOMP);
      break;
    }

    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}


VOID
GetBlockInformation (
  UINTN *BlockSize,
  UINTN *NumBlocks
  )
{
  CSD_SDV2 *CsdSDV2Data;
  UINTN    CardSize;

  if (gCardInfo.CardType == SD_CARD_2_HIGH) {
    CsdSDV2Data = (CSD_SDV2 *)&gCardInfo.CSDData;

    //Populate BlockSize.
    *BlockSize = (0x1UL << CsdSDV2Data->READ_BL_LEN);

    //Calculate Total number of blocks.
    CardSize = CsdSDV2Data->C_SIZELow16 | (CsdSDV2Data->C_SIZEHigh6 << 2);
    *NumBlocks = ((CardSize + 1) * 1024);
  } else {
    //Populate BlockSize.
    *BlockSize = (0x1UL << gCardInfo.CSDData.READ_BL_LEN);

    //Calculate Total number of blocks.
    CardSize = gCardInfo.CSDData.C_SIZELow2 | (gCardInfo.CSDData.C_SIZEHigh10 << 2);
    *NumBlocks = (CardSize + 1) * (1 << (gCardInfo.CSDData.C_SIZE_MULT + 2));
  }

  //For >=2G card, BlockSize may be 1K, but the transfer size is 512 bytes.
  if (*BlockSize > 512) {
    *NumBlocks = MultU64x32(*NumBlocks, *BlockSize/2);
    *BlockSize = 512;
  }

  DEBUG ((EFI_D_ERROR, "Card type: 0x%x, BlockSize: 0x%x, NumBlocks: 0x%x\n", gCardInfo.CardType, *BlockSize, *NumBlocks));
}


VOID
CalculateCardCLKD (
  UINTN *ClockFrequencySelect
  )
{
  UINT8    MaxDataTransferRate;
  UINTN    TransferRateValue = 0;
  UINTN    TimeValue = 0 ;
  UINTN    Frequency = 0;

  MaxDataTransferRate = gCardInfo.CSDData.TRAN_SPEED;

	DEBUG((EFI_D_INFO, "SDHC::CalculateCardCLKD : 0x%x.\n", MaxDataTransferRate));

  // For SD Cards  we would need to send CMD6 to set
  // speeds abouve 25MHz. High Speed mode 50 MHz and up

  //Calculate Transfer rate unit (Bits 2:0 of TRAN_SPEED)
  switch (MaxDataTransferRate & 0x7) {
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
      DEBUG((EFI_D_ERROR, "Invalid parameter.\n"));
      ASSERT(FALSE);
  }

  //Calculate Time value (Bits 6:3 of TRAN_SPEED)
  switch ((MaxDataTransferRate >> 3) & 0xF) {
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
      DEBUG((EFI_D_ERROR, "Invalid parameter.\n"));
      ASSERT(FALSE);
  }

  Frequency = TransferRateValue * TimeValue/10;

  //Calculate Clock divider value to program in SDHC_SYSCTL[CLKD] field.
  *ClockFrequencySelect = ((MMC_REFERENCE_CLK/Frequency) + 1);

  DEBUG ((EFI_D_INFO, "MaxDataTransferRate: 0x%x, Frequency: %d KHz, ClockFrequencySelect: %x\n", MaxDataTransferRate, Frequency/1000, *ClockFrequencySelect));
}


VOID
GetCardConfigurationData (
  VOID
  )
{
  UINTN  BlockSize;
  UINTN  NumBlocks;
 // UINTN  ClockFrequencySelect;

  //Calculate BlockSize and Total number of blocks in the detected card.
  GetBlockInformation(&BlockSize, &NumBlocks);
  gCardInfo.BlockSize = BlockSize;
  gCardInfo.NumBlocks = NumBlocks;

  //Calculate Card clock divider value.
 // CalculateCardCLKD(&ClockFrequencySelect);
//  gCardInfo.ClockFrequencySelect = ClockFrequencySelect;
  gCardInfo.ClockFrequencySelect = 25000000;
}


EFI_STATUS
InitializeSDHC (
  VOID
  )
{

  EFI_STATUS    Status;
  EXYNOS_GPIO *Gpio;
  UINT32 CumBaseAddr;
  UINT32 SdMmcBaseAddr;

  Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
  ASSERT_EFI_ERROR(Status);

  CumBaseAddr = PcdGet32(PcdCmuBase);
  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
  // Reset Host Controller
  MmioWrite32((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRA);
  while ((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRA) != 0x0);

	// Set Clock Source for using MPLL
  MmioAndThenOr32 ((CumBaseAddr + CLK_SRC_FSYS_OFFSET), ~(0xF << 8), (0x6 << 8));

  // Set GPIO for using SDMMC2
  Gpio->Set(Gpio,SD_2_CLK,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_CMD,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_CDn,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_DATA0,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_DATA1,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_DATA2,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,SD_2_DATA3,GPIO_MODE_SPECIAL_FUNCTION_2);

  Gpio->SetPull(Gpio,SD_2_CLK,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,SD_2_CMD,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,SD_2_CDn,GPIO_PULL_UP);
  Gpio->SetPull(Gpio,SD_2_DATA0,GPIO_PULL_UP);
  Gpio->SetPull(Gpio,SD_2_DATA1,GPIO_PULL_UP);
  Gpio->SetPull(Gpio,SD_2_DATA2,GPIO_PULL_UP);
  Gpio->SetPull(Gpio,SD_2_DATA3,GPIO_PULL_UP);


  Gpio->SetStrength(Gpio,SD_2_CLK,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_CMD,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_CDn,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_DATA0,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_DATA1,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_DATA2,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,SD_2_DATA3,GPIO_DRV_4X);

  return EFI_SUCCESS;
}


EFI_STATUS
PerformCardIdenfication (
  VOID
  )
{
  EFI_STATUS Status;
  UINTN      CmdArgument = 0;
  UINTN      Response = 0;
  UINTN      RetryCount = 0;
  UINTN			 TempRes0,TempRes1,TempRes2,TempRes3;
  BOOLEAN    SDCmd8Supported = FALSE;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
  //Enable interrupts.
  MmioWrite32 ((SdMmcBaseAddr + INTEN_OFFSET), (CMDCOMP | TRNSCOMP | RDYFORRD | RDYFORWT | CARDINSERT | CARDREMOVE));

  //Change clock frequency to 400KHz to fit protocol
  UpdateSDHCClkFrequency(400);

  //Send CMD0 command.
  Status = SendCmd (CMD0, CMD0_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Cmd0 fails.\n"));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "CMD0 response: %x\n", MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET))));

  //Send CMD8 command. (New v2.00 command for Voltage check)
  //Only 2.7V - 3.6V is supported for SD2.0, only SD 2.0 card can pass.
  //MMC & SD1.1 card will fail this command.
  CmdArgument = CMD8_ARG;
  Status = SendCmd (CMD8, CMD8_INT_EN, CmdArgument);
  if (Status == EFI_SUCCESS) {
    Response = MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET));
    DEBUG ((EFI_D_INFO, "CMD8 success. CMD8 response: %x\n", Response));
    if (Response != CmdArgument) {
      return EFI_DEVICE_ERROR;
    }
    DEBUG ((EFI_D_INFO, "Card is SD2.0\n"));
    SDCmd8Supported = TRUE; //Supports high capacity.
  } else {
    DEBUG ((EFI_D_INFO, "CMD8 fails. Not an SD2.0 card.\n"));
  }

  MmioOr32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRC);
  while ((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRC));

  //Poll till card is busy
  while (RetryCount < MAX_RETRY_COUNT) {
    //Send CMD55 command.
    CmdArgument = 0;
    Status = SendCmd (CMD55, CMD55_INT_EN, CmdArgument);
    if (Status == EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO, "CMD55 success. CMD55 response: %x\n", MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET))));
      gCardInfo.CardType = SD_CARD;
    } else {
      DEBUG ((EFI_D_ERROR, "CMD55 fails.\n"));
      gCardInfo.CardType = MMC_CARD;
    }

    //Send appropriate command for the card type which got detected.
    if (gCardInfo.CardType == SD_CARD) {
      CmdArgument = ((UINTN *) &(gCardInfo.OCRData))[0];

      //Set HCS bit.
      if (SDCmd8Supported) {
        CmdArgument |= HCS;
      }

      Status = SendCmd (ACMD41, ACMD41_INT_EN, CmdArgument);
      if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "ACMD41 fails.\n"));
        return Status;
      }
      ((UINT32 *) &(gCardInfo.OCRData))[0] = MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET));
      DEBUG ((EFI_D_INFO, "SD card detected. ACMD41 OCR: %x\n", ((UINT32 *) &(gCardInfo.OCRData))[0]));
    } else if (gCardInfo.CardType == MMC_CARD) {
      CmdArgument = 0;
      Status = SendCmd (CMD1, CMD1_INT_EN, CmdArgument);
      if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "CMD1 fails.\n"));
        return Status;
      }
      Response = MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET));
      DEBUG ((EFI_D_INFO, "MMC card detected. CMD1 response: %x\n", Response));

      //NOTE: For now, I am skipping this since I only have an SD card.
      //Compare card OCR and host OCR (Section 22.6.1.3.2.4)
      return EFI_UNSUPPORTED; //For now, MMC is not supported.
    }

    //Poll the card until it is out of its power-up sequence.
    if (gCardInfo.OCRData.Busy == 1) {

      if (SDCmd8Supported) {
        gCardInfo.CardType = SD_CARD_2;
      }

      //Card is ready. Check CCS (Card capacity status) bit (bit#30).
      //SD 2.0 standard card will response with CCS 0, SD high capacity card will respond with CCS 1.
      if (gCardInfo.OCRData.AccessMode & BIT1) {
        gCardInfo.CardType = SD_CARD_2_HIGH;
        DEBUG ((EFI_D_INFO, "High capacity card.\n"));
      } else {
        DEBUG ((EFI_D_INFO, "Standard capacity card.\n"));
      }

      break;
    }

    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    DEBUG ((EFI_D_ERROR, "Timeout error. RetryCount: %d\n", RetryCount));
    return EFI_TIMEOUT;
  }

  //Read CID data.
  CmdArgument = 0;
  Status = SendCmd (CMD2, CMD2_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD2 fails. Status: %x\n", Status));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "CMD2 response: %x %x %x %x\n",	MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET)), \
							MmioRead32 ((SdMmcBaseAddr + RSPREG1_OFFSET)), \
							MmioRead32 ((SdMmcBaseAddr + RSPREG2_OFFSET)), \
							MmioRead32 ((SdMmcBaseAddr + RSPREG3_OFFSET))));

  TempRes0 = MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET));
  TempRes1 = MmioRead32 ((SdMmcBaseAddr + RSPREG1_OFFSET));
  TempRes2 = MmioRead32 ((SdMmcBaseAddr + RSPREG2_OFFSET));
  TempRes3 = MmioRead32 ((SdMmcBaseAddr + RSPREG3_OFFSET));

  //Parse CID register data.
	ParseCardCIDData(TempRes0 << 8, (TempRes1 << 8) | (TempRes0 >> 24),
			(TempRes2 << 8) | (TempRes1 >> 24), (TempRes3 << 8) | (TempRes2 >> 24));

    //Read RCA
  CmdArgument = 0;
  Status = SendCmd (CMD3, CMD3_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD3 fails. Status: %x\n", Status));
    return Status;
  }

  //Set RCA for the detected card. RCA is CMD3 response.
  gCardInfo.RCA = (MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET)) >> 16);
  DEBUG ((EFI_D_ERROR, "CMD3 response: RCA %x\n", gCardInfo.RCA));

  //MMC Bus setting change after card identification.
//	MmioAndThenOr32 (SDHC_PWRCON, ~(0x7<<9), SDBV30); //check if our controller voltage is 3.0v or 3.3v //wprkfgur
  UpdateSDHCClkFrequency(400); //Set the clock frequency to 400KHz.

  return EFI_SUCCESS;
}


EFI_STATUS
GetCardSpecificData (
  VOID
  )
{
  EFI_STATUS Status;
  UINTN      CmdArgument;
  UINTN			 TempRes[4],i;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  //Send CMD9 to retrieve CSD.
  CmdArgument = gCardInfo.RCA << 16;
  Status = SendCmd (CMD9, CMD9_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD9 fails. Status: %x\n", Status));
    return Status;
  }

  TempRes[0] = MmioRead32 ((SdMmcBaseAddr + RSPREG0_OFFSET));
  TempRes[1] = MmioRead32 ((SdMmcBaseAddr + RSPREG1_OFFSET));
  TempRes[2] = MmioRead32 ((SdMmcBaseAddr + RSPREG2_OFFSET));
  TempRes[3] = MmioRead32 ((SdMmcBaseAddr + RSPREG3_OFFSET));

  //Populate 128-bit CSD register data.
	for (i = 0 ; i < 4; i++) {
		((UINT32 *)&(gCardInfo.CSDData))[i] = TempRes[i] << 8;
		if (i != 0)
						((UINT32 *)&(gCardInfo.CSDData))[i] |= ((TempRes[i-1] >> 24) & 0xFF);
	}

  DEBUG ((EFI_D_INFO, "CMD9 response: %x %x %x %x\n", ((UINT32 *)&(gCardInfo.CSDData))[0], ((UINT32 *)&(gCardInfo.CSDData))[1], ((UINT32 *)&(gCardInfo.CSDData))[2], ((UINT32 *)&(gCardInfo.CSDData))[3]));

  //Calculate total number of blocks and max. data transfer rate supported by the detected card.
  GetCardConfigurationData();

  return Status;
}


EFI_STATUS
PerformCardConfiguration (
  VOID
  )
{
  UINTN      CmdArgument = 0;
  EFI_STATUS Status;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  //Send CMD7
  CmdArgument = gCardInfo.RCA << 16;
  Status = SendCmd (CMD7, CMD7_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD7 fails. Status: %x\n", Status));
    return Status;
  }

  if ((gCardInfo.CardType != UNKNOWN_CARD) && (gCardInfo.CardType != MMC_CARD)) {
    // We could read SCR register, but SD Card Phys spec stats any SD Card shall
    // set SCR.SD_BUS_WIDTHS to support 4-bit mode, so why bother?

    // Send ACMD6 (application specific commands must be prefixed with CMD55)
    Status = SendCmd (CMD55, CMD55_INT_EN, CmdArgument);
    if (!EFI_ERROR (Status)) {
      // set device into 4-bit data bus mode
      Status = SendCmd (ACMD6, ACMD6_INT_EN, 0x2);
      if (!EFI_ERROR (Status)) {
        // Set host controler into 4-bit mode
        MmioOr32 ((SdMmcBaseAddr + HOSTCTL_OFFSET), WIDE4);
        DEBUG ((EFI_D_INFO, "SD Memory Card set to 4-bit mode\n"));
      }
    }
  }

  //Send CMD16 to set the block length
  CmdArgument = gCardInfo.BlockSize;
  Status = SendCmd (CMD16, CMD16_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD16 fails. Status: %x\n", Status));
    return Status;
  }

  //Change SDHC clock frequency to what detected card can support.
  UpdateSDHCClkFrequency(250000);		//Fix the clock value temporary
	//UpdateSDHCClkFrequency(gCardInfo.ClockFrequencySelect);

  return EFI_SUCCESS;
}


EFI_STATUS
ReadBlockData (
  IN  EFI_BLOCK_IO_PROTOCOL       *This,
  OUT VOID                        *Buffer
  )
{
  UINTN MmcStatus;
  UINTN *DataBuffer = Buffer;
  UINTN DataSize = This->Media->BlockSize/4;
  UINTN Count;
  UINTN RetryCount = 0;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  //Check controller status to make sure there is no error.
  while (RetryCount < MAX_RETRY_COUNT) {
    do {
      //Read Status.
      MmcStatus = MmioRead32 ((SdMmcBaseAddr + INTSTS_OFFSET));
    } while(MmcStatus == 0);

    //Check if Buffer read ready (RDYFORRD) bit is set?
    if (MmcStatus & RDYFORRD) {

      //Clear RDYFORRD bit
      MmioOr32 ((SdMmcBaseAddr + INTSTS_OFFSET), RDYFORRD);

      //Read block worth of data.
      for (Count = 0; Count < DataSize; Count++) {
        *DataBuffer++ = MmioRead32 ((SdMmcBaseAddr + BDATA_OFFSET));
      }
      break;
    }
    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
WriteBlockData (
  IN  EFI_BLOCK_IO_PROTOCOL       *This,
  OUT VOID                        *Buffer
  )
{
  UINTN MmcStatus;
  UINTN *DataBuffer = Buffer;
  UINTN DataSize = This->Media->BlockSize/4;
  UINTN Count;
  UINTN RetryCount = 0;
  UINT32 SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
  //Check controller status to make sure there is no error.
  while (RetryCount < MAX_RETRY_COUNT) {
    do {
      //Read Status.
      MmcStatus = MmioRead32 ((SdMmcBaseAddr + INTSTS_OFFSET));
    } while(MmcStatus == 0);

    //Check if Buffer write ready (RDYFORWT) bit is set?
    if (MmcStatus & RDYFORWT) {

      //Clear RDYFORWT bit
      MmioOr32 ((SdMmcBaseAddr + INTSTS_OFFSET), RDYFORWT);

      //Write block worth of data.
      for (Count = 0; Count < DataSize; Count++) {
        MmioWrite32 ((SdMmcBaseAddr + BDATA_OFFSET), *DataBuffer++);
      }

      break;
    }
    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
TransferBlock (
  IN EFI_BLOCK_IO_PROTOCOL        *This,
  IN  UINTN                       Lba,
  IN OUT VOID                     *Buffer,
  IN  OPERATION_TYPE              OperationType
  )
{
  EFI_STATUS Status;
  UINTN      MmcStatus;
  UINTN      RetryCount = 0;
  UINTN      Cmd = 0;
  UINTN      CmdInterruptEnable = 0;
  UINTN      CmdArgument = 0;
  UINT32     SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  DEBUG ((EFI_D_INFO, "SDHC::TransferBlock : Lba = %d, Buffer = 0x%x, Type = %d\n", Lba, Buffer, OperationType));
  //Populate the command information based on the operation type.
  if (OperationType == READ) {
    Cmd = CMD17; //Single block read
    CmdInterruptEnable = CMD17_INT_EN;
		PrepareTransfer(CardtoHost, 1);
  } else if (OperationType == WRITE) {
    Cmd = CMD24; //Single block write
    CmdInterruptEnable = CMD24_INT_EN;
		PrepareTransfer(HosttoCard, 1);
  }

  //Set command argument based on the card access mode (Byte mode or Block mode)
  if (gCardInfo.OCRData.AccessMode & BIT1) {
    CmdArgument = Lba;
  } else {
    CmdArgument = Lba * This->Media->BlockSize;
  }

  //Send Command.
  Status = SendCmd (Cmd, CmdInterruptEnable, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD fails. Status: %x\n", Status));
    return Status;
  }

  //Read or Write data.
  if (OperationType == READ) {
    Status = ReadBlockData (This, Buffer);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "ReadBlockData fails.\n"));
      return Status;
    }
  } else if (OperationType == WRITE) {
    Status = WriteBlockData (This, Buffer);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "WriteBlockData fails.\n"));
      return Status;
    }
  }

  //Check for the Transfer completion.
  while (RetryCount < MAX_RETRY_COUNT) {
    //Read Status
    do {
      MmcStatus = MmioRead32 ((SdMmcBaseAddr + INTSTS_OFFSET));
    } while (MmcStatus == 0);

    //Check if Transfer complete (TRNSCOMP) bit is set?
    if (MmcStatus & TRNSCOMP) {
      break;
    } else {
      DEBUG ((EFI_D_INFO, "MmcStatus for TRNSCOMP: %x\n", MmcStatus));
      //Check if DATAEBITERR, DATACRCERR or DATATOUTERR interrupt occured.
      if ((MmcStatus & DATAEBITERR) | (MmcStatus & DATACRCERR) | (MmcStatus & DATATOUTERR)) {
        //There was an error during the data transfer.

        //Set SRD bit to 1 and wait until it return to 0x0.
        MmioOr32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRD);
        while((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRD) != 0x0);

        return EFI_DEVICE_ERROR;
      }
    }
    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    DEBUG ((EFI_D_ERROR, "TransferBlockData timed out.\n"));
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

BOOLEAN
CardPresent (
  VOID
  )
{
  UINT32     SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);
  if (MmioRead32((SdMmcBaseAddr + PRNSTS_OFFSET)) & INSCARD)
    return TRUE;
  else
    return FALSE;
}

EFI_STATUS
DetectCard (
  VOID
  )
{
  EFI_STATUS    Status;
  UINT32     SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  if (!CardPresent ()) {
    return EFI_NO_MEDIA;
  }

  //Initialize MMC host controller clocks.
  Status = InitializeSDHC ();
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Initialize MMC host controller fails. Status: %x\n", Status));
    return Status;
  }

  //Soft reset for all.
  MmioWrite32((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRA);
  while ((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRA) != 0x0);

  //Set the clock frequency to 400KHz.
  UpdateSDHCClkFrequency (400);

  //Card idenfication
  Status = PerformCardIdenfication ();
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "No MMC/SD card detected.\n"));
    return Status;
  }

  //Get CSD (Card specific data) for the detected card.
  Status = GetCardSpecificData();
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //Configure the card in data transfer mode.
  Status = PerformCardConfiguration();
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //Patch the Media structure.
  gSDHCMedia.LastBlock    = (gCardInfo.NumBlocks - 1);
  gSDHCMedia.BlockSize    = gCardInfo.BlockSize;
  gSDHCMedia.ReadOnly     = 0;
  gSDHCMedia.MediaPresent = TRUE;
  gSDHCMedia.MediaId++;

  DEBUG ((EFI_D_INFO, "SD Card Media Change on Handle 0x%08x\n", gImageHandle));

  return Status;
}

#define MAX_SDHC_TRANSFER_SIZE  0x4000

EFI_STATUS
SdReadWrite (
  IN EFI_BLOCK_IO_PROTOCOL    *This,
  IN  UINTN                   Lba,
  OUT VOID                    *Buffer,
  IN  UINTN                   BufferSize,
  IN  OPERATION_TYPE          OperationType
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN      RetryCount = 0;
  UINTN      BlockCount;
  UINTN      BytesToBeTranferedThisPass = 0;
  UINTN      BytesRemainingToBeTransfered;
  EFI_TPL    OldTpl;
  BOOLEAN    Update;
  UINT32     SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  Update               = FALSE;

  DEBUG ((EFI_D_INFO, "SDHC::SDHCInitialize is called \n"));
  if (gMediaChange) {
    Update = TRUE;
    Status = DetectCard();
    if (EFI_ERROR (Status)) {
		DEBUG ((EFI_D_ERROR, "SDHC::SDHCInitialize:Card Detect Fail\n"));
      gSDHCMedia.MediaPresent = FALSE;
      gSDHCMedia.LastBlock    = 0;
      gSDHCMedia.BlockSize    = 512;  // Should be zero but there is a bug in DiskIo
      gSDHCMedia.ReadOnly     = FALSE;
    }
    gMediaChange             = FALSE;
  } else if (!gSDHCMedia.MediaPresent) {
    Status = EFI_NO_MEDIA;
    goto Done;
  }

 if (Update) {
    DEBUG ((EFI_D_INFO, "SD Card ReinstallProtocolInterface ()\n"));
    gBS->ReinstallProtocolInterface (

          gImageHandle,

          &gEfiBlockIoProtocolGuid,

          &gBlockIo,

          &gBlockIo

          );
 }
DEBUG ((EFI_D_INFO, "SDHC::SDHCInitialize:CardInfo : LastBlock = %ld, BlockSize = %d\n", gSDHCMedia.LastBlock, gSDHCMedia.BlockSize));


  if (Buffer == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto Done;
  }

  if (Lba > This->Media->LastBlock) {
    Status = EFI_INVALID_PARAMETER;
    goto Done;
  }

  if ((BufferSize % This->Media->BlockSize) != 0) {
    Status = EFI_BAD_BUFFER_SIZE;
    goto Done;
  }

  //Check if the data lines are not in use.
  while ((RetryCount++ < MAX_RETRY_COUNT) && (MmioRead32 ((SdMmcBaseAddr + PRNSTS_OFFSET)) & CMDINHDAT));
  if (RetryCount == MAX_RETRY_COUNT) {
    Status = EFI_TIMEOUT;
    goto Done;
  }

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  BytesRemainingToBeTransfered = BufferSize;
  while (BytesRemainingToBeTransfered > 0) {
    // Turn OFF DMA path until it is debugged
    // BytesToBeTranferedThisPass = (BytesToBeTranferedThisPass >= MAX_SDHC_TRANSFER_SIZE) ? MAX_SDHC_TRANSFER_SIZE : BytesRemainingToBeTransfered;
    BytesToBeTranferedThisPass   = This->Media->BlockSize;

    BlockCount = BytesToBeTranferedThisPass/This->Media->BlockSize;

    if (BlockCount > 1) {
//      Status = DmaBlocks (This, Lba, Buffer, BlockCount, OperationType);
    } else {
      //Transfer a block worth of data.
      Status = TransferBlock (This, Lba, Buffer, OperationType);

    }

    if (EFI_ERROR(Status)) {
      DEBUG ((EFI_D_ERROR, "TransferBlockData fails. %x\n", Status));
      goto DoneRestoreTPL;
    }

    BytesRemainingToBeTransfered -= BytesToBeTranferedThisPass;
    Lba    += BlockCount;
    Buffer = (UINT8 *)Buffer + This->Media->BlockSize;
  }

DoneRestoreTPL:

  gBS->RestoreTPL (OldTpl);

Done:

  return Status;

}


/**

  Reset the Block Device.



  @param  This                 Indicates a pointer to the calling context.

  @param  ExtendedVerification Driver may perform diagnostics on reset.



  @retval EFI_SUCCESS          The device was reset.

  @retval EFI_DEVICE_ERROR     The device is not functioning properly and could

                               not be reset.



**/
EFI_STATUS
EFIAPI
SDHCReset (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN BOOLEAN                        ExtendedVerification
  )
{
  DEBUG ((EFI_D_INFO, " SDHC::SDHCReset is called\n"));
  return EFI_SUCCESS;
}


/**

  Read BufferSize bytes from Lba into Buffer.



  @param  This       Indicates a pointer to the calling context.

  @param  MediaId    Id of the media, changes every time the media is replaced.

  @param  Lba        The starting Logical Block Address to read from

  @param  BufferSize Size of Buffer, must be a multiple of device block size.

  @param  Buffer     A pointer to the destination buffer for the data. The caller is

                     responsible for either having implicit or explicit ownership of the buffer.



  @retval EFI_SUCCESS           The data was read correctly from the device.

  @retval EFI_DEVICE_ERROR      The device reported an error while performing the read.

  @retval EFI_NO_MEDIA          There is no media in the device.

  @retval EFI_MEDIA_CHANGED     The MediaId does not matched the current device.

  @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.

  @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not valid,

                                or the buffer is not on proper alignment.

EFI_STATUS

**/
EFI_STATUS
EFIAPI
SDHCReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN UINT32                         MediaId,
  IN EFI_LBA                        Lba,
  IN UINTN                          BufferSize,
  OUT VOID                          *Buffer
  )
{
  EFI_STATUS Status;

  DEBUG ((EFI_D_INFO, "SDHC::SDHCWriteBlocks : MediaId = %d, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
					MediaId, (UINTN)Lba, BufferSize, Buffer));
  //Perform Read operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, READ);

  return Status;

}


/**

  Write BufferSize bytes from Lba into Buffer.



  @param  This       Indicates a pointer to the calling context.

  @param  MediaId    The media ID that the write request is for.

  @param  Lba        The starting logical block address to be written. The caller is

                     responsible for writing to only legitimate locations.

  @param  BufferSize Size of Buffer, must be a multiple of device block size.

  @param  Buffer     A pointer to the source buffer for the data.



  @retval EFI_SUCCESS           The data was written correctly to the device.

  @retval EFI_WRITE_PROTECTED   The device can not be written to.

  @retval EFI_DEVICE_ERROR      The device reported an error while performing the write.

  @retval EFI_NO_MEDIA          There is no media in the device.

  @retval EFI_MEDIA_CHNAGED     The MediaId does not matched the current device.

  @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.

  @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not valid,

                                or the buffer is not on proper alignment.



**/
EFI_STATUS
EFIAPI
SDHCWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN UINT32                         MediaId,
  IN EFI_LBA                        Lba,
  IN UINTN                          BufferSize,
  IN VOID                           *Buffer
  )
{
  EFI_STATUS  Status;

  DEBUG ((EFI_D_INFO, "SDHC::SDHCWriteBlocks : MediaId = %d, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
					MediaId, (UINTN)Lba, BufferSize, Buffer));
  //Perform write operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, WRITE);


  return Status;

}


/**

  Flush the Block Device.



  @param  This              Indicates a pointer to the calling context.



  @retval EFI_SUCCESS       All outstanding data was written to the device

  @retval EFI_DEVICE_ERROR  The device reported an error while writting back the data

  @retval EFI_NO_MEDIA      There is no media in the device.



**/
EFI_STATUS
EFIAPI
SDHCFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  )
{
  DEBUG ((EFI_D_INFO, "SDHC::SDHCFlushBlocks is called\n"));
  return EFI_SUCCESS;
}


EFI_BLOCK_IO_PROTOCOL gBlockIo = {
  EFI_BLOCK_IO_INTERFACE_REVISION,   // Revision
  &gSDHCMedia,                      // *Media
  SDHCReset,                        // Reset
  SDHCReadBlocks,                   // ReadBlocks
  SDHCWriteBlocks,                  // WriteBlocks
  SDHCFlushBlocks                   // FlushBlocks
};


/**

  Timer callback to convert card present hardware into a boolean that indicates

  a media change event has happened. If you just check the GPIO you could see

  card 1 and then check again after card 1 was removed and card 2 was inserted

  and you would still see media present. Thus you need the timer tick to catch

  the toggle event.



  @param  Event                 Event whose notification function is being invoked.

  @param  Context               The pointer to the notification function's context,

                                which is implementation-dependent. Not used.



**/
VOID
EFIAPI
TimerCallback (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  BOOLEAN Present;

  DEBUG ((EFI_D_INFO, "SDHC::TimerCallBack is called\n"));
  Present = CardPresent ();
  if (gSDHCMedia.MediaPresent) {
    if (!Present && !gMediaChange) {
      gMediaChange = TRUE;
    }
  } else {
    if (Present && !gMediaChange) {
      gMediaChange = TRUE;
    }
  }
}


EFI_STATUS
EFIAPI
SDHCInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;

  ZeroMem (&gCardInfo, sizeof (CARD_INFO));

  Status = gBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, TimerCallback, NULL, &gTimerEvent);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->SetTimer (gTimerEvent, TimerPeriodic, 1000000);
  ASSERT_EFI_ERROR (Status);

  //Publish BlockIO.
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiBlockIoProtocolGuid,    &gBlockIo,
                  &gEfiDevicePathProtocolGuid, &gSDHCDevicePath,
                  NULL
                  );
  return Status;
}
