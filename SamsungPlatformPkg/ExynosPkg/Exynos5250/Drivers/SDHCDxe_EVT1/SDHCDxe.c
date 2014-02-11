/** @file
  MMC/SD Card driver for Secure Digital Host Controller

  This driver always produces a BlockIo protocol but it starts off with no Media
  present. A TimerCallBack detects when media is inserted or removed and after
  a media change event a call to BlockIo ReadBlocks/WriteBlocks will cause the
  media to be detected (or removed) and the BlockIo Media structure will get
  updated. No MMC/SD Card harward registers are updated until the first BlockIo
  ReadBlocks/WriteBlocks after media has been insterted (booting with a card
  plugged in counts as an insertion event).

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>
#include <Platform/Exynos5250.h>
#include <Platform/Arndale5250.h>

#include "SDHCDxe.h"


#define DateInformation		"20120810_001"


MSHC_OPERATION_MODE MSHC_operation_mode=MSHC_FIFO;
//MSHC_OPERATION_MODE MSHC_operation_mode=MSHC_IDMA;


//#undef EFI_D_INFO
//#define EFI_D_INFO 1


CARD_INFO gCardInfo;
EFI_EVENT gTimerEvent;
BOOLEAN gMediaChange = FALSE;


EFI_BLOCK_IO_MEDIA gSDMMCMedia = {
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
} MSHC_DEVICE_PATH;

MSHC_DEVICE_PATH gMSHCDevicePath = {
  {
    HARDWARE_DEVICE_PATH,
    HW_VENDOR_DP,
    (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
    (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
    0x3a02e7fe, 0x649, 0x4fb4, 0xbe, 0x4f, 0xa8, 0x62, 0xca, 0x18, 0x72, 0xa9
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    sizeof (EFI_DEVICE_PATH_PROTOCOL),
    0
  }
};


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


EFI_STATUS
MSHC_SendCmd (
  UINTN Cmd,
  UINTN CmdInterruptEnableVal,
  UINTN CmdArgument
  )
{
  UINTN MmcStatus = 0;
  volatile UINTN RetryCount = 0;
  int cmd_flags = 0;
  int timeout=0;
  UINT32 SdMmcBaseAddr;
  //UINT32 MSHCRintStatus=0;

  DEBUG ((EFI_D_INFO, "CMD = %d Argument=0x%x\n", (Cmd&0x3F), CmdArgument));

  timeout = MAX_RETRY_COUNT;
  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

    //1. Check if Data busy or not
    while(MmioRead32(SdMmcBaseAddr + MSHCI_STATUS) & (DATA_BUSY)) 
    {
        if (timeout == 0) 
        {
            DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd timeout : CMD = %d\n", Cmd));
            return EFI_DEVICE_ERROR;
        }
    	timeout--;
    	MicroSecondDelay(1);
    }  

    // 2. Check if Raw interrupt is command done 
    /*MSHCRintStatus = MmioRead32(SdMmcBaseAddr + MSHCI_RINTSTS);
    if ((MSHCRintStatus & (INTMSK_CDONE|INTMSK_ACD)) == 0) 
    {
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd interrupt error : INT = %x\n", MmioRead32(SdMmcBaseAddr + MSHCI_RINTSTS)));
    }  */

    // 3. Clear Raw interrupt 
    MmioWrite32 ((SdMmcBaseAddr + MSHCI_RINTSTS), INTMSK_ALL);

    // 4. prepare data 
    //mshci_reset_fifo();
  
    //5. Set command argument register
    MmioWrite32 ((SdMmcBaseAddr + MSHCI_CMDARG), CmdArgument);

    // 6. transfer data

    //Enable interrupt enable events to occur
    // EVT1 do not need interrupt mask, use Raw interrupt 
    //MmioWrite32 ((SdMmcBaseAddr + MSHCI_INTMSK), CmdInterruptEnableVal);

    // 7. trasfer data
  
    //8. Send a command
    cmd_flags = (Cmd & 0x3F);
    if(Cmd & (RSPTYP48 | RSPTYP48B | RSPTYP136))
    {
        cmd_flags |= CMD_RESP_EXP_BIT;
        if(Cmd & RSPTYP136)
            cmd_flags |= CMD_RESP_LENGTH_BIT;
    }

    //if((Cmd==CMD17)|(Cmd==CMD18)|(Cmd==CMD8))
    if((Cmd==CMD17)|(Cmd==CMD18))
    {
        cmd_flags |= CMD_DATA_EXP_BIT;
        //DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Read\n"));
    }

    if((Cmd==CMD24)|(Cmd==CMD25))
    {
        cmd_flags |= CMD_DATA_EXP_BIT | CMD_RW_BIT;
        //DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Write\n"));

    }

    if (Cmd & ENCMDCRC)
    {   
        cmd_flags |= CMD_CHECK_CRC_BIT;
    }
    //cmd_flags |= (CMD_STRT_BIT | CMD_USE_HOLD_REG | CMD_WAIT_PRV_DAT_BIT|CMD_SENT_AUTO_STOP_BIT);
    cmd_flags |= (CMD_STRT_BIT | CMD_USE_HOLD_REG | CMD_WAIT_PRV_DAT_BIT);
    DEBUG ((EFI_D_INFO, "CMD flag = 0x%x\n", cmd_flags));
    MmioWrite32 ((SdMmcBaseAddr + MSHCI_CMD), cmd_flags);
    MicroSecondDelay(1);

  //9. Check for the Raw interrupt
  //wait for command complete by busy waiting. 
    for (RetryCount; RetryCount<MAX_RETRY_COUNT; RetryCount++) 
    {
        MmcStatus = MmioRead32(SdMmcBaseAddr + MSHCI_RINTSTS);
        if (MmcStatus & INTMSK_CDONE) 
        {
            break;
        }
    }

    if (RetryCount == MAX_RETRY_COUNT) 
    {
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd timeout CMD:%d RINT:0x%x\n",(Cmd&0x3F) ,MmcStatus));
        return EFI_TIMEOUT;
    }

    if(MmcStatus & INTMSK_RTO)
    {
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd Response timeout CMD:%d RINT:0x%x\n", (Cmd & 0x3F),MmcStatus));
         return EFI_TIMEOUT;
        
    }
    else if (MmcStatus & INTMSK_RE)
    {
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd Response Error RINT:0x%x\n", MmcStatus));
        return EFI_TIMEOUT;
    }
    else if(MmcStatus & INTMSK_RCRC)
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd Response CRC Err  RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_DCRC)
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd Data CRC Err RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_HLE)
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd HLE Err RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_SBE)
        DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd SBE Err RINT:0x%x\n", MmcStatus));
  else if(MmcStatus & INTMSK_EBE)
      DEBUG ((EFI_D_ERROR, "SDHC::MSHC_SendCmd EBE Err RINT:0x%x\n", MmcStatus));

  return EFI_SUCCESS;
}

static const UINT32 FreqUnit[4]={10, 100, 1000, 10000};
static const UINT8 MultiFactor[16]={0, 10, 12, 13, 15, 20, 26, 30, 35, 40, 45, 52, 55, 60, 70, 80};

void PrintCardInfo()
{
#if !defined(MDEPKG_NDEBUG)
    UINT8 TransSpeed = gCardInfo.CSDData.TRAN_SPEED;
    
    DEBUG ((EFI_D_INFO, "SDHC::READ_BL_LEN %d\n", gCardInfo.CSDData.READ_BL_LEN));     
    DEBUG ((EFI_D_INFO, "SDHC::CSize %d\n", gCardInfo.CSDData.C_SIZELow2 | (gCardInfo.CSDData.C_SIZEHigh10 << 2)));         
    DEBUG ((EFI_D_INFO, "SDHC::MULTI %d\n", gCardInfo.CSDData.C_SIZE_MULT));         
    DEBUG ((EFI_D_INFO, "SDHC::Speed %d\n", (FreqUnit[TransSpeed&0x7]*MultiFactor[TransSpeed>>3])));         
#endif
}


#define EXT_CSD_SIZE    128
UINT32 Ext_csd[EXT_CSD_SIZE];
VOID GetEXTCSD()
{
    gCardInfo.NumBlocks = 0x1D4C000;
    DEBUG ((EFI_D_INFO, "SDHC:: default block number : 0x1D4C000"));         

    UINTN cmdarg = 0;  
    EFI_STATUS Status = EFI_SUCCESS;

    cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
            (EXT_CSD_HS_TIMING << 16) |
            (0 << 8);
    Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, cmdarg);

    cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
          (EXT_CSD_BUS_WIDTH << 16) |
          (EXT_CSD_BUS_WIDTH_1 << 8);
    Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, cmdarg);    

    cmdarg = 0;
    Status = MSHC_SendCmd (CMD8, CMD8_INT_EN, cmdarg);

    gCardInfo.BlockSize = BLEN_512BYTES;
    
    if (!EFI_ERROR(Status)) 
    {
        DEBUG ((EFI_D_INFO, "SDHC::EXT CSD \n"));
        PrepareTransfer(&Ext_csd[0], 1, READ);
        //MSHC_ReadDMA(&Ext_csd[0], 1);
        MSHC_ReadFIFO(EXT_CSD_SIZE, &Ext_csd[0]);
        gCardInfo.NumBlocks = Ext_csd[EXT_CSD_SEC_CNT/4];
        MicroSecondDelay(1000);
        DEBUG ((1, "SDHC::Size:%dMB\n", (gCardInfo.NumBlocks/2048)));         
    }
    
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
  } 
  else if(gCardInfo.CardType == MMC_CARD)
    {
    //Populate BlockSize.
    *BlockSize = (0x1UL << gCardInfo.CSDData.READ_BL_LEN);

    //Calculate Total number of blocks.
    CardSize = gCardInfo.CSDData.C_SIZELow2 | (gCardInfo.CSDData.C_SIZEHigh10 << 2);
    *NumBlocks = (CardSize + 1) * (1 << (gCardInfo.CSDData.C_SIZE_MULT + 2));
    *NumBlocks *= (*BlockSize);
  }

  //For >=2G card, BlockSize may be 1K, but the transfer size is 512 bytes.
  if (*BlockSize > 512) {
    DEBUG ((EFI_D_INFO, "SDHC::BlockSize:%d\n", *BlockSize));
    *NumBlocks = MultU64x32(*NumBlocks, *BlockSize/2);
    *BlockSize = 512;
  }

  DEBUG ((EFI_D_INFO, "Card type: 0x%x, BlockSize: 0x%x, NumBlocks: 0x%x\n", gCardInfo.CardType, *BlockSize, *NumBlocks));
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

  //Send CMD0 command.
  Status = MSHC_SendCmd (CMD0, CMD0_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Cmd0 fails.\n"));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "CMD0 response: %x\n", MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0))));

  //Send CMD8 command. (New v2.00 command for Voltage check)
  //Only 2.7V - 3.6V is supported for SD2.0, only SD 2.0 card can pass.
  //MMC & SD1.1 card will fail this command.
  CmdArgument = CMD8_ARG;
  Status = MSHC_SendCmd (CMD8, CMD8_INT_EN, CmdArgument);
  if (Status == EFI_SUCCESS) {
    Response = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));
    DEBUG ((EFI_D_INFO, "CMD8 success. CMD8 response: %x\n", Response));
    if (Response != CmdArgument) {
      return EFI_DEVICE_ERROR;
    }
    DEBUG ((EFI_D_INFO, "Card is SD2.0\n"));
    SDCmd8Supported = TRUE; //Supports high capacity.
  } else {
    DEBUG ((EFI_D_INFO, "CMD8 fails. Not an SD2.0 card.\n"));
  }

  //Poll till card is busy
  while (RetryCount < MAX_RETRY_COUNT) {
    //Send CMD55 command.
    CmdArgument = 0;
    Status = MSHC_SendCmd (CMD55, CMD55_INT_EN, CmdArgument);
    if (Status == EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO, "CMD55 success. CMD55 response: %x\n", MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0))));
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

      Status = MSHC_SendCmd (ACMD41, ACMD41_INT_EN, CmdArgument);
      if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "ACMD41 fails.\n"));
        return Status;
      }
      ((UINT32 *) &(gCardInfo.OCRData))[0] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));
      DEBUG ((EFI_D_INFO, "SD card detected. ACMD41 OCR: %x\n", ((UINT32 *) &(gCardInfo.OCRData))[0]));
    } else if (gCardInfo.CardType == MMC_CARD) {
      CmdArgument = 0;
      Status = MSHC_SendCmd (CMD1, CMD1_INT_EN, CmdArgument);
      if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "CMD1 fails.\n"));
        return Status;
      }
      Response = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));
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

    gBS->Stall(1000);
    RetryCount++;
  }

  if (RetryCount == MAX_RETRY_COUNT) {
    DEBUG ((EFI_D_ERROR, "Timeout error. RetryCount: %d\n", RetryCount));
    return EFI_TIMEOUT;
  }

  //Read CID data.
  CmdArgument = 0;
  Status = MSHC_SendCmd (CMD2, CMD2_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD2 fails. Status: %x\n", Status));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "CMD2 response: %x %x %x %x\n",	MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0)), \
							MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP1)), \
							MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP2)), \
							MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP3))));

  TempRes0 = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));
  TempRes1 = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP1));
  TempRes2 = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP2));
  TempRes3 = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP3));

  //Parse CID register data.
	ParseCardCIDData(TempRes0 << 8, (TempRes1 << 8) | (TempRes0 >> 24),
			(TempRes2 << 8) | (TempRes1 >> 24), (TempRes3 << 8) | (TempRes2 >> 24));

    //Read RCA
  CmdArgument = 0;
  Status = MSHC_SendCmd (CMD3, CMD3_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD3 fails. Status: %x\n", Status));
    return Status;
  }

  //Set RCA for the detected card. RCA is CMD3 response.
  gCardInfo.RCA = (MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0)) >> 16);
  DEBUG ((EFI_D_INFO, "CMD3 response: RCA %x\n", gCardInfo.RCA));

  gBS->Stall(1000);		//Need Debug by wprkfgur

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
  Status = MSHC_SendCmd (CMD9, CMD9_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD9 fails. Status: %x\n", Status));
    return Status;
  }

  TempRes[0] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));
  TempRes[1] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP1));
  TempRes[2] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP2));
  TempRes[3] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP3));

  //Populate 128-bit CSD register data.
  
	for (i = 0 ; i < 4; i++) {
		((UINT32 *)&(gCardInfo.CSDData))[i] = TempRes[i];
	}

    DEBUG ((EFI_D_INFO, "CMD9 response: %x %x %x %x\n", ((UINT32 *)&(gCardInfo.CSDData))[0], ((UINT32 *)&(gCardInfo.CSDData))[1], ((UINT32 *)&(gCardInfo.CSDData))[2], ((UINT32 *)&(gCardInfo.CSDData))[3]));
    PrintCardInfo();
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
  //UINTN FifoCount = 0;
  //UINTN Count=0;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  //Send CMD7
  CmdArgument = gCardInfo.RCA << 16;
  Status = MSHC_SendCmd (CMD7, CMD7_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD7 fails. Status: %x\n", Status));
    return Status;
  } 

  if ((gCardInfo.CardType != UNKNOWN_CARD) && (gCardInfo.CardType != MMC_CARD)) {
    // We could read SCR register, but SD Card Phys spec stats any SD Card shall
    // set SCR.SD_BUS_WIDTHS to support 4-bit mode, so why bother?

    // Send ACMD6 (application specific commands must be prefixed with CMD55)
    Status = MSHC_SendCmd (CMD55, CMD55_INT_EN, CmdArgument);
    if (!EFI_ERROR (Status)) {
      // set device into 4-bit data bus mode
      Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, 0x2);
      if (!EFI_ERROR (Status)) {
        // Set host controler into 4-bit mode
        MmioOr32 ((SdMmcBaseAddr + MSHCI_CTYPE), CARD_WIDTH14);
        DEBUG ((EFI_D_INFO, "SD Memory Card set to 4-bit mode\n"));
      }
    }
  }

  //Send CMD16 to set the block length
  CmdArgument = gCardInfo.BlockSize;
  Status = MSHC_SendCmd (CMD16, CMD16_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD16 fails. Status: %x\n", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ReadBlockData (
  IN  EFI_BLOCK_IO_PROTOCOL       *This,
  OUT VOID                        *Buffer, 
  IN  UINTN                         BlockCount
  )
{
  EFI_STATUS Status = EFI_INVALID_PARAMETER;
  UINTN DataSize = This->Media->BlockSize/4;

  DEBUG ((EFI_D_INFO, "SDHC::ReadBlockData start \n"));

    if(MSHC_operation_mode == MSHC_FIFO)
    {
        Status = MSHC_ReadFIFO(DataSize, Buffer);
    }
    
    else if(MSHC_operation_mode == MSHC_IDMA)
    {
        Status = MSHC_ReadDMA(Buffer, BlockCount);
    }

  return Status;
}


EFI_STATUS
WriteBlockData (
  IN  EFI_BLOCK_IO_PROTOCOL       *This,
  OUT VOID                        *Buffer,
  IN  UINTN                         BlockCount  
  )
{
    EFI_STATUS Status = EFI_INVALID_PARAMETER;
    UINTN DataSize = This->Media->BlockSize/4;

    if(MSHC_operation_mode == MSHC_FIFO)
    {
        Status = MSHC_WriteFIFO(DataSize, Buffer);
    }
    else if(MSHC_operation_mode == MSHC_IDMA)
    {
        Status = MSHC_WriteDMA(Buffer, BlockCount);
    }

    return Status;
}


EFI_STATUS
TransferBlock (
  IN EFI_BLOCK_IO_PROTOCOL        *This,
  IN  UINTN                          Lba,
  IN OUT VOID                     *Buffer,
  IN  UINTN                         BlockCount,  
  IN  OPERATION_TYPE          OperationType
  )
{
  EFI_STATUS Status;
  UINTN      Cmd = 0;
  UINTN      CmdInterruptEnable = 0;
  UINTN      CmdArgument = 0;

  // 1. FIFO reset
  // MSHC_SendCmd do the fifo reset

  // 2. prepare transfer
  
  DEBUG ((EFI_D_INFO, "SDHC::TransferBlock : Lba = %d, Buffer = 0x%x, Type = %d\n", Lba, Buffer, OperationType));
  //Populate the command information based on the operation type.
  if (OperationType == READ) 
  {
    if(BlockCount>1)
    {
        Cmd = CMD18; //multi block read
        CmdInterruptEnable = CMD18_INT_EN;
    }
    else
    {
        Cmd = CMD17; //Single block read
        CmdInterruptEnable = CMD17_INT_EN;
    }

  } 
  else if (OperationType == WRITE) 
  {
    if(BlockCount>1)
    {
        Cmd = CMD25; //multi block write
        CmdInterruptEnable = CMD25_INT_EN;       
    }
    else
    {
        Cmd = CMD24; //Single block write
        CmdInterruptEnable = CMD24_INT_EN;     
    }
   }
  PrepareTransfer(Buffer, BlockCount, OperationType);

  //Set command argument based on the card access mode (Byte mode or Block mode)
  if (gCardInfo.OCRData.AccessMode & BIT1) {
    CmdArgument = Lba;
  } else {
    CmdArgument = Lba * This->Media->BlockSize;
  }

  //Send Command.
  Status = MSHC_SendCmd (Cmd, CmdInterruptEnable, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD%d fails. Status: %x\n", (Cmd&0x3F), Status));
    return Status;
  }
  
  DEBUG ((EFI_D_INFO, "CMD%d succeed! \n", (Cmd&0x3F)));

  //Read or Write data.
  if (OperationType == READ) {
    Status = ReadBlockData (This, Buffer, BlockCount);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "ReadBlockData fails.\n"));
      return Status;
    }
  } else if (OperationType == WRITE) {
    Status = WriteBlockData (This, Buffer, BlockCount);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "WriteBlockData fails.\n"));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

BOOLEAN
CardPresent (
  VOID
  )
{
    EXYNOS_GPIO *Gpio;
    EFI_STATUS    Status;
    UINT32 Val;

    Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
    ASSERT_EFI_ERROR(Status);

    Gpio->Get(Gpio,SD_2_EVT1_CDn,&Val);
    
    if(Val)
    {
        //DEBUG((EFI_D_INFO, "SDHC::CardPresent %d\n", Val));
        return FALSE;
    }
    else
        return TRUE;

}

EFI_STATUS
DetectCard (
  VOID
  )
{
  EFI_STATUS    Status;
  //UINT32     SdMmcBaseAddr;

  //DEBUG ((EFI_D_INFO, "===================================\n"));
  DEBUG ((EFI_D_INFO, "===SDHC: Version %a ===\n", DateInformation));
  //DEBUG ((EFI_D_INFO, "===================================\n"));

  //SdMmcBaseAddr = PcdGet32(PcdSdMmcBase);

  if (!CardPresent ()) {
    return EFI_NO_MEDIA;
  }

  //Initialize MMC host controller clocks.
  Status = InitializeMSHC ();
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "Initialize MMC host controller fails. Status: %x\n", Status));
    return Status;
  }

    // EVT1 InitializeSDHC do the SW Reset
    //Soft reset for all.
    //MmioWrite32((SdMmcBaseAddr + SDHC_SWRST_OFFSET), SRA);
    //gBS->Stall(1000);
    //while ((MmioRead32 ((SdMmcBaseAddr + SDHC_SWRST_OFFSET)) & SRA) != 0x0);

  //Set the clock frequency to 400KHz.
  UpdateMSHCClkFrequency (MSHC_CLK_400);

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
  gSDMMCMedia.LastBlock    = (gCardInfo.NumBlocks - 1);
 gSDMMCMedia.BlockSize    = gCardInfo.BlockSize;
 // gSDMMCMedia.BlockSize    = 512;
  gSDMMCMedia.ReadOnly     = 0;
  gSDMMCMedia.MediaPresent = TRUE;
  gSDMMCMedia.MediaId++;

  UpdateMSHCClkFrequency(MSHC_CLK_25M);
  DEBUG ((EFI_D_INFO, "SD Card Media Change on Handle 0x%08x\n", gImageHandle));

  return Status;
}


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
  UINTN      BytesRemainingToBeTransfered=0;
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
      gSDMMCMedia.MediaPresent = FALSE;
      gSDMMCMedia.LastBlock    = 0;
      gSDMMCMedia.BlockSize    = 512;  // Should be zero but there is a bug in DiskIo
      gSDMMCMedia.ReadOnly     = FALSE;
    }
    gMediaChange             = FALSE;
  } else if (!gSDMMCMedia.MediaPresent) {
    Status = EFI_NO_MEDIA;
    goto Done;
  }
  
 if (Update) {
    DEBUG ((EFI_D_INFO, "SD Card ReinstallProtocolInterface ()\n"));
    gBS->ReinstallProtocolInterface (
          gImageHandle,
          &gEfiBlockIoProtocolGuid,
          &gBlockIo,
          &gBlockIo);
 }
DEBUG ((EFI_D_INFO, "SDHC::SDHCInitialize:CardInfo : LastBlock = %ld, BlockSize = %d\n", gSDMMCMedia.LastBlock, gSDMMCMedia.BlockSize));


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
  while ((RetryCount++ < MAX_RETRY_COUNT) && (MmioRead32 ((SdMmcBaseAddr + MSHCI_STATUS)) & DATA_BUSY));
  if (RetryCount == MAX_RETRY_COUNT) {
    Status = EFI_TIMEOUT;
    DEBUG ((EFI_D_ERROR, "MSHC::SdReadWrite EFI_TIMEOUT\n"));        
    goto Done;
  }

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  BytesRemainingToBeTransfered = BufferSize;

    if(MSHC_operation_mode == MSHC_IDMA)
    { 
        while (BytesRemainingToBeTransfered > 0) {
          // Turn OFF DMA path until it is debugged
           BytesToBeTranferedThisPass = (BytesRemainingToBeTransfered >= MAX_MSHC_TRANSFER_SIZE) ? MAX_MSHC_TRANSFER_SIZE : BytesRemainingToBeTransfered;
          //BytesToBeTranferedThisPass   = This->Media->BlockSize;
      
          BlockCount = BytesToBeTranferedThisPass/This->Media->BlockSize;
          Status = TransferBlock (This, Lba, Buffer,BlockCount, OperationType);
      
          if (EFI_ERROR(Status)) {
            DEBUG ((EFI_D_ERROR, "TransferBlockData fails. %x\n", Status));
            goto DoneRestoreTPL;
          }
      
          BytesRemainingToBeTransfered -= BytesToBeTranferedThisPass;
          Lba    += BlockCount;
          Buffer = (UINT8 *)Buffer + (This->Media->BlockSize*BlockCount);
          DEBUG ((EFI_D_INFO, "SdReadWrite::Buf:0x%x, ToBe:0x%x Rema:0x%x \n", BufferSize, BytesToBeTranferedThisPass, BytesRemainingToBeTransfered));          
        }
    }
    else
    {      
          while (BytesRemainingToBeTransfered > 0) {
            // Turn OFF DMA path until it is debugged
            // BytesToBeTranferedThisPass = (BytesToBeTranferedThisPass >= MAX_SDHC_TRANSFER_SIZE) ? MAX_SDHC_TRANSFER_SIZE : BytesRemainingToBeTransfered;
            BytesToBeTranferedThisPass   = This->Media->BlockSize;
        
            BlockCount = BytesToBeTranferedThisPass/This->Media->BlockSize;
        
            if (BlockCount > 1) {
        //      Status = DmaBlocks (This, Lba, Buffer, BlockCount, OperationType);
            } else {
              //Transfer a block worth of data.
              Status = TransferBlock (This, Lba, Buffer, BlockCount,OperationType);
        
            }
        
            if (EFI_ERROR(Status)) {
              DEBUG ((EFI_D_ERROR, "TransferBlockData fails. %x\n", Status));
              goto DoneRestoreTPL;
            }
        
            BytesRemainingToBeTransfered -= BytesToBeTranferedThisPass;
            Lba    += BlockCount;
            Buffer = (UINT8 *)Buffer + This->Media->BlockSize;
          }      

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
MSHCReset (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN BOOLEAN                        ExtendedVerification
  )
{
  DEBUG ((EFI_D_INFO, " MSHC::MSHCReset is called\n"));
  MSHC_reset_all();
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


#define EMMC_TEST 0
#if EMMC_TEST
#define EMMC_TEST_SIZE  (512*2)//(MAX_MSHC_TRANSFER_SIZE+1024)
UINT32 bWrite[EMMC_TEST_SIZE];
UINT32 bRead[EMMC_TEST_SIZE];
//INTN EFIAPI  CompareMem (IN CONST VOID *DestinationBuffer, IN CONST VOID *SourceBuffer, IN UINTN Length) 
//two buffers are identical, then 0 is returned. Otherwise, the value returned is the first mismatched byte 

void MSHC_Test(  IN EFI_BLOCK_IO_PROTOCOL          *This)
{
    UINTN i=0;
    UINTN Count;  
    INTN ret;
    EFI_STATUS Status;    
    DEBUG ((EFI_D_INFO, "MSHC::Read Write test %dB\n", EMMC_TEST_SIZE));

    for(i=0; i<EMMC_TEST_SIZE; i++)
    {
        bWrite[i]=i;
    }

//multi 
   for(Count=100000; Count<100002; Count++)
   {
       //Lba=n;
       //DEBUG ((EFI_D_INFO, "MSHC::Read Write test : %d\n", Count));
       ZeroMem (&bRead[0], sizeof(bRead));
       DEBUG ((EFI_D_INFO, "ZR : 0x%x, 0x%x, 0x%x, 0x%x\n",
               bRead[0], bRead[1], bRead[2], bRead[3]));       

       Status = SdReadWrite (This, (UINTN)Count, &bWrite[0], EMMC_TEST_SIZE, WRITE);   
       Status = SdReadWrite (This, (UINTN)Count, &bRead[0], EMMC_TEST_SIZE, READ);
       
       DEBUG ((EFI_D_INFO, "W: 0x%x, 0x%x, 0x%x, 0x%x    ",
               bWrite[0], bWrite[1], bWrite[2], bWrite[3]));
       DEBUG ((EFI_D_INFO, "R : 0x%x, 0x%x, 0x%x, 0x%x\n",
               bRead[0], bRead[1], bRead[2], bRead[3]));
       
       ret = CompareMem(&bRead[0],&bWrite[0],EMMC_TEST_SIZE);
       
       if(ret==0)
           DEBUG ((1, "SDHC::Read Write OK!!\n\n"));
       else
           DEBUG ((1, "SDHC::Read Write Failed  bWrite[%d]=0x%x : bRead[%d]=0x%x\n", ret, bWrite[ret], ret, bRead[ret]));
           
           
   }
       

}
#endif 

EFI_STATUS
EFIAPI
MSHCReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN UINT32                         MediaId,
  IN EFI_LBA                        Lba,
  IN UINTN                          BufferSize,
  OUT VOID                          *Buffer
  )
{
  EFI_STATUS Status=EFI_SUCCESS;
    DEBUG ((EFI_D_INFO, "SDHC::MSHCReadBlocks : MediaId = %x, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
    			MediaId, (UINTN)Lba, BufferSize, Buffer));

#if EMMC_TEST
    MSHC_Test(This);
#else    
  //Perform Read operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, READ);
#endif   
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
MSHCWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL          *This,
  IN UINT32                         MediaId,
  IN EFI_LBA                        Lba,
  IN UINTN                          BufferSize,
  IN VOID                           *Buffer
  )
{
  EFI_STATUS  Status;
#if EMMC_TEST
    UINT32 Count=0;
    UINT32 ret;
#endif 

  DEBUG ((EFI_D_INFO, "SDHC::MSHCWriteBlocks : MediaId = 0x%x, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
  					MediaId, (UINTN)Lba, BufferSize, Buffer));

  //Perform write operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, WRITE);

#if EMMC_TEST
    Count = (BufferSize >= MAX_MSHC_TRANSFER_SIZE) ? MAX_MSHC_TRANSFER_SIZE : BufferSize;    
    DEBUG ((1, "\nMSHC::Read Write Test [0x%x] Start \n", Count));
    ZeroMem (&bRead[0], sizeof(bRead));
    CopyMem(&bWrite[0], (VOID *)Buffer, Count);
    Status = SdReadWrite (This, (UINTN)Lba, &bRead[0], Count, READ);
    DEBUG ((1, "W : 0x%x, 0x%x, 0x%x, 0x%x\n",
           bWrite[7], bWrite[8], bWrite[9], bWrite[10]));

    DEBUG ((1, "R : 0x%x, 0x%x, 0x%x, 0x%x\n",
           bRead[7], bRead[8], bRead[9], bRead[10]));

    ret = CompareMem(&bRead[0],&bWrite[0],Count);

    if(ret==0)
       DEBUG ((1, "SDHC::Read Write Test OK!!\n"));
    else
       DEBUG ((1, "SDHC::Read Write Test Failed -.-   bRead[%d]=0x%x  bWrite[%d]=0x%x \n", ret, bRead[ret], ret, bWrite[ret]));
             
#endif 

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
MSHCFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  )
{
  DEBUG ((EFI_D_INFO, "SDHC::MSHCFlushBlocks is called\n"));
  return EFI_SUCCESS;
}


EFI_BLOCK_IO_PROTOCOL gBlockIo = {
  EFI_BLOCK_IO_INTERFACE_REVISION,   // Revision
  &gSDMMCMedia,                      // *Media
  MSHCReset,                        // Reset
  MSHCReadBlocks,                   // ReadBlocks
  MSHCWriteBlocks,                  // WriteBlocks
  MSHCFlushBlocks                   // FlushBlocks
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

  //DEBUG ((EFI_D_ERROR, "SDHC::TimerCallBack is called\n"));
  Present = CardPresent ();
  if (gSDMMCMedia.MediaPresent) {
    if (!Present && !gMediaChange) {
      gMediaChange = TRUE;
    }
  } else {
    if (Present && !gMediaChange) {
      gMediaChange = TRUE;
    }
  }
}

EFI_HANDLE mHandle  = NULL;
EFI_EVENT mCommandProtocolRegistration=NULL;

VOID
EFIAPI
CommandProtocolNotificationEvent (
  IN  EFI_EVENT                           Event,
  IN  VOID                                *Context
  )
{
  EFI_STATUS  Status;

  if(mHandle!=NULL){
      return;
   }
  
  Status = gBS->InstallMultipleProtocolInterfaces (
              &mHandle,
              &gEfiBlockIoProtocolGuid,    &gBlockIo,
              &gEfiDevicePathProtocolGuid, &gMSHCDevicePath,
              NULL
              );
  DEBUG((EFI_D_INFO, "SDHC::install protocol  \n" ));
    if(Status!=EFI_SUCCESS)
    {
        DEBUG((EFI_D_ERROR, "SDHC::install protocol fail %r\n", Status));
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

  EfiCreateProtocolNotifyEvent (
    &gEfiEblAddCommandProtocolGuid,
    TPL_CALLBACK,
    CommandProtocolNotificationEvent,
    (VOID *)SystemTable,
    &mCommandProtocolRegistration
    );
  
#if 0
  //Publish BlockIO.
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiBlockIoProtocolGuid,    &gBlockIo,
                  &gEfiDevicePathProtocolGuid, &gMSHCDevicePath,
                  NULL
                  );
#endif 
  return Status;
}
