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

#include "eMMCDxe.h"



#define DateInformation		"20120723_007"


MSHC_OPERATION_MODE MSHC_operation_mode=MSHC_FIFO;
//MSHC_OPERATION_MODE MSHC_operation_mode=MSHC_IDMA;


//#undef EFI_D_INFO
//#define EFI_D_INFO 1



CARD_INFO gCardInfo; 
BOOLEAN                    gMediaChange = TRUE;
BOOLEAN                    gCardInit = FALSE;


EFI_BLOCK_IO_MEDIA gSDMMCMedia = {
  SIGNATURE_32('e','m','m','c'),            // MediaId
  FALSE,                                     // RemovableMedia
  TRUE,                                    // MediaPresent
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
    0xb615f1f5, 0x5088, 0x43cd, 0x80, 0x9c, 0xa1, 0x6e, 0x52, 0x48, 0x7d, 0x00
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

  DEBUG ((EFI_D_INFO, "CMD = %d\n", (Cmd&0x3F)));

  timeout = MAX_RETRY_COUNT;
  SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);

    //1. Check if Data busy or not
    while(MmioRead32(SdMmcBaseAddr + MSHCI_STATUS) & (DATA_BUSY)) 
    {
        if (timeout == 0) 
        {
            DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd timeout : CMD = %d\n", Cmd));
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

    if((Cmd==CMD17)|(Cmd==CMD18)|(Cmd==CMD8))
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
    cmd_flags |= (CMD_STRT_BIT | CMD_USE_HOLD_REG | CMD_WAIT_PRV_DAT_BIT|CMD_SENT_AUTO_STOP_BIT);
    //cmd_flags |= (CMD_STRT_BIT | CMD_USE_HOLD_REG | CMD_WAIT_PRV_DAT_BIT);
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
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd timeout CMD:%d RINT:0x%x\n",(Cmd&0x3F) ,MmcStatus));
        return EFI_TIMEOUT;
    }

    if(MmcStatus & INTMSK_RTO)
    {
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Response timeout CMD:%d RINT:0x%x\n", (Cmd & 0x3F),MmcStatus));
         return EFI_TIMEOUT;
        
    }
    else if (MmcStatus & INTMSK_RE)
    {
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Response Error RINT:0x%x\n", MmcStatus));
        return EFI_TIMEOUT;
    }
    else if(MmcStatus & INTMSK_RCRC)
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Response CRC Err  RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_DCRC)
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd Data CRC Err RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_HLE)
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd HLE Err RINT:0x%x\n", MmcStatus));
    else if(MmcStatus & INTMSK_SBE)
        DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd SBE Err RINT:0x%x\n", MmcStatus));
  else if(MmcStatus & INTMSK_EBE)
      DEBUG ((EFI_D_ERROR, "MSHC::MSHC_SendCmd EBE Err RINT:0x%x\n", MmcStatus));

  return EFI_SUCCESS;
}

/**
Super block size : 4MB (16GB density)
Argument (Boot Size) =(Number of Super Block for boot partition) / 2

**/
EFI_STATUS MSHC_BOOT_Partition(UINT32 bootsize, UINT32 rpmbsize)
{
    UINTN CmdArgument;
    EFI_STATUS  Status = RETURN_SUCCESS;
    UINT32 BootSize, RPMBSize;

    /* Only use this command for raw eMMC moviNAND */
    /* Enter backdoor mode */
    CmdArgument = 0xefac62ec;
    Status = MSHC_SendCmd (CMD62, CMD62_INT_EN, CmdArgument);

    /* Boot partition changing mode */
    CmdArgument = 0xcbaea7;
    Status = MSHC_SendCmd (CMD62, CMD62_INT_EN, CmdArgument);

    //BootSize = ((bootsize*1024)/128);
    BootSize = (bootsize*2);
    
    /* Arg: boot partition size */
    CmdArgument = BootSize;
    Status = MSHC_SendCmd (CMD62, CMD62_INT_EN, CmdArgument);

    //RPMBSize = ((rpmbsize*1024)/128);
    RPMBSize = (rpmbsize*2);

    /* Arg: RPMB partition size */
    CmdArgument = RPMBSize;
    Status = MSHC_SendCmd (CMD62, CMD62_INT_EN, CmdArgument);

    return Status;

}

EFI_STATUS MSHC_EMMC_Boot_Open()
{
    UINTN CmdArgument;
    EFI_STATUS  Status = RETURN_SUCCESS;

    DEBUG ((EFI_D_INFO, "emmc open\n" ));
	/* Boot ack enable, boot partition enable , boot partition access */    
    CmdArgument = ((3<<24)|(179<<16)|(((1<<6)|(1<<3)|(1<<0))<<8));
    Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, CmdArgument);
    if (!EFI_ERROR(Status))
    {
        /* 4bit transfer mode at booting time. */
        CmdArgument = ((3<<24)|(177<<16)|((1<<0)<<8));
        Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, CmdArgument);
        if (EFI_ERROR(Status))
        {
            DEBUG ((EFI_D_ERROR, "emmc open fail 2nd CMD6\n" ));
        }
    }
    else
    {
        DEBUG ((EFI_D_ERROR, "emmc open fail first CMD6\n" ));
    }

    return Status;
}

EFI_STATUS MSHC_EMMC_Boot_Close()
{
    UINTN CmdArgument;
    EFI_STATUS  Status = RETURN_SUCCESS;

    DEBUG ((EFI_D_INFO, "emmc close\n" ));
    CmdArgument = ((3<<24)|(179<<16)|(((1<<6)|(1<<3)|(0<<0))<<8));
    Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, CmdArgument);
    if (EFI_ERROR(Status))
    {
        DEBUG ((EFI_D_ERROR, "emmc close fail \n" ));
    }
    return Status;
}


void PrintCardInfo()
{
    DEBUG ((EFI_D_INFO, "MSHC::READ_BL_LEN %d\n", gCardInfo.CSDData.READ_BL_LEN));     
    DEBUG ((EFI_D_INFO, "MSHC::CSize %d\n", gCardInfo.CSDData.C_SIZELow2 | (gCardInfo.CSDData.C_SIZEHigh10 << 2)));         
    DEBUG ((EFI_D_INFO, "MSHC::MULTI %d\n", gCardInfo.CSDData.C_SIZE_MULT));         

}


#define EXT_CSD_SIZE    128
UINT32 Ext_csd[EXT_CSD_SIZE];
VOID GetEXTCSD()
{
    gCardInfo.NumBlocks = 0;
    gCardInfo.TotalNumBlocks = 30801920;

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
        DEBUG ((EFI_D_INFO, "MSHC::EXT CSD \n"));
        //PrepareTransfer(&Ext_csd[0], 1, READ);
        //MSHC_ReadDMA(&Ext_csd[0], 1);
        MSHC_ReadFIFO(EXT_CSD_SIZE, &Ext_csd[0]);
        gCardInfo.NumBlocks = Ext_csd[EXT_CSD_SEC_CNT/4];
        gCardInfo.Extcsd.boot_size_multi = Ext_csd[BOOT_SIZE_MULTI/4];
        gCardInfo.Extcsd.boot_size_multi = (gCardInfo.Extcsd.boot_size_multi>>16)&0xff;
        //MicroSecondDelay(5000);
        
        DEBUG ((EFI_D_INFO, "MSHC::num blocks %d\n", gCardInfo.NumBlocks));         
        DEBUG ((1, "MSHC::eMMC Size:%dMB\n", (gCardInfo.NumBlocks/2048)));         
        DEBUG ((1, "MSHC::Boot partition Size:%dMB\n", ((gCardInfo.TotalNumBlocks-gCardInfo.NumBlocks)/2048)));         
        DEBUG ((EFI_D_INFO, "MSHC::Ext CSD boot block %d\n", (gCardInfo.Extcsd.boot_size_multi)));
       
    }
    else
    {
        gCardInfo.NumBlocks = 0x1D4C000;
        DEBUG ((EFI_D_ERROR, "MSHC:: default block number : 0x1D4C000"));         
    }

}


EFI_STATUS
PerformCardIdenfication (
  VOID
  )
{
  EFI_STATUS Status;
  UINTN      CmdArgument = 0;
  //UINTN      Response = 0;
  //UINTN      RetryCount = 0;
  UINTN	   TempRes0,TempRes1,TempRes2,TempRes3;
  //BOOLEAN    SDCmd8Supported = FALSE;
  UINT32 SdMmcBaseAddr;
  int timeout = MAX_RETRY_COUNT;  

  SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);
  gCardInfo.CardType = MMC_CARD;
  
  //1. Send CMD0 command. go to IDLE
  Status = MSHC_SendCmd (CMD0, CMD0_INT_EN, CmdArgument);

    // 2. Send CMD1 while OCR is not busy and get OCR register
    do {
    	CmdArgument = OCR_HCS | MMC_VDD_32_33 | MMC_VDD_33_34;
      Status = MSHC_SendCmd (CMD1, CMD1_INT_EN, CmdArgument);

        if (EFI_ERROR(Status)) 
        {
            DEBUG ((EFI_D_ERROR, "MSHC::CMD1 fails.\n"));
        }

    	MicroSecondDelay(100);
    } while (!(MmioRead32 (SdMmcBaseAddr + MSHCI_RESP0)& OCR_BUSY) && timeout--);   

    if (timeout <= 0)
    {
        DEBUG ((EFI_D_ERROR, "MSHC::CMD1 OCR busy timeout.\n"));
        return EFI_DEVICE_ERROR;
    }
    DEBUG ((EFI_D_INFO, "MSHC::CMD1 OCR  0x%x\n", MmioRead32(SdMmcBaseAddr + MSHCI_RESP0)));

    ((UINT32 *) &(gCardInfo.OCRData))[0] = MmioRead32 ((SdMmcBaseAddr + MSHCI_RESP0));

  //3. send CMD2 to get CID register
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

    //4. send CMD3 to get RCA register  
  CmdArgument = 0;
  Status = MSHC_SendCmd (CMD3, CMD3_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD3 fails. Status: %x\n", Status));
    return Status;
  }

  //Set RCA for the detected card. RCA is CMD3 response.
  DEBUG ((EFI_D_INFO, "MSHC::CMD3 RCA  0x%x\n", MmioRead32(SdMmcBaseAddr + MSHCI_RESP0)));
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

  SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);

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
  UINT32 OMval;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);
  OMval = MmioRead32(0x10040000);
  DEBUG ((EFI_D_INFO, "MSHC::OM read 0x%x \n", OMval));

  //Send CMD7
  CmdArgument = gCardInfo.RCA << 16;
  Status = MSHC_SendCmd (CMD7, CMD7_INT_EN, CmdArgument);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "CMD7 fails. Status: %x\n", Status));
    return Status;
  } 

      //Send CMD16 to set the block length
      //CmdArgument = gCardInfo.BlockSize;
      CmdArgument = BLEN_512BYTES;
      Status = MSHC_SendCmd (CMD16, CMD16_INT_EN, CmdArgument);
      if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "CMD16 fails. Status: %x\n", Status));
        return Status;
      }

    if(OMval!=OM_EMMC)
    {
        GetEXTCSD();
        if(gCardInfo.Extcsd.boot_size_multi!= MSHC_BOOT_SIZE_MULTI)
        {
            MSHC_BOOT_Partition(MSHC_BOOT_SIZE, MSHC_RPMB_SIZE);
            DEBUG ((EFI_D_INFO, "MSHC::Doing Boot partition \n"));
        }
        else
        {
            DEBUG ((EFI_D_INFO, "MSHC::Alread boot partition \n", Status));
        }
    }
    else
    {
        DEBUG ((1, "MSHC::eMMC booting \n"));
        gCardInfo.TotalNumBlocks = 30801920;
        gCardInfo.NumBlocks = 30588928;
    }
    
        // set device into 4-bit data bus mode
        //Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, 0x2);
        // set device into 8-bit data bus mode
        CmdArgument = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
                            (EXT_CSD_BUS_WIDTH <<16) |
                             (EXT_CSD_BUS_WIDTH_8_DDR <<8);
        Status = MSHC_SendCmd (ACMD6, ACMD6_INT_EN, CmdArgument);
        if (!EFI_ERROR (Status)) {
          // Set host controler into 8-bit mode
          MmioOr32 ((SdMmcBaseAddr + MSHCI_CTYPE), CARD_WIDTH8);
          //MmioOr32 ((SdMmcBaseAddr + MSHCI_CTYPE), CARD_WIDTH14);
          DEBUG ((EFI_D_INFO, "8-bit mode\n"));
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

  DEBUG ((EFI_D_INFO, "MSHC::ReadBlockData start \n"));

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
EraseBlockData (
  IN UINT32 Partition,
  IN UINTN StartBlock,
  IN  UINTN NumBlock
  )
{
    UINTN cmdarg = 0;  
    EFI_STATUS status = EFI_SUCCESS;

    if(Partition!=MSHC_BOOT_PARTITION)
    {
        DEBUG ((EFI_D_ERROR, "EraseBlockData  failed  \n"));
        status = EFI_UNSUPPORTED;
        goto Exit;     
    }
    
    /* MMC High Capacity erase minimum size is 512KB */
    if (NumBlock < 1024) {
    	if (NumBlock < 512)
    		NumBlock = 1;
    	else
    		NumBlock = 2;
    } else {
    	if (0 == (NumBlock%1024)) {
    		NumBlock = (NumBlock / 1024);
    	} else {
    		NumBlock = (NumBlock / 1024) + 1;
    	}
    }
    DEBUG ((EFI_D_INFO, "EraseBlockData  start:%d, Numblock:%d\n", StartBlock, NumBlock));

    cmdarg = StartBlock;
    status = MSHC_SendCmd (CMD35, 0, cmdarg);
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((EFI_D_ERROR, "EraseBlockData  CMD35 failed \n"));
        status = EFI_DEVICE_ERROR;
        goto Exit;
    }

    cmdarg = StartBlock + NumBlock;
    status = MSHC_SendCmd (CMD36, 0, cmdarg);
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((EFI_D_ERROR, "EraseBlockData  CMD36 failed \n"));
        status = EFI_DEVICE_ERROR;
        goto Exit;
    }

    cmdarg = 0;
    status = MSHC_SendCmd (CMD38, 0, cmdarg);
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((EFI_D_ERROR, "EraseBlockData  CMD38 failed \n"));
        status = EFI_DEVICE_ERROR;
        goto Exit;
    }

    Exit:
        
    return status;
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
  DEBUG ((EFI_D_INFO, "===MSHC: Version %a ===\n", DateInformation));
  //DEBUG ((EFI_D_INFO, "===================================\n"));

  //SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);

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
  //gSDMMCMedia.BlockSize    = gCardInfo.BlockSize;
  gSDMMCMedia.BlockSize    = 512;
  gSDMMCMedia.ReadOnly     = 0;
  gSDMMCMedia.MediaPresent = TRUE;
  gSDMMCMedia.MediaId++;

  UpdateMSHCClkFrequency(MSHC_CLK_50M);
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
  //BOOLEAN    Update;
  UINT32     SdMmcBaseAddr;

  SdMmcBaseAddr = PcdGet32(PcdSdMmcCH0Base);

    if(gMediaChange==TRUE)
    {
      Status = DetectCard();
      gMediaChange = FALSE;
      gCardInit = TRUE;
    }
    if (EFI_ERROR(Status)) {
      DEBUG ((EFI_D_ERROR, "MSHC::Card initialization fail .\n"));
      gCardInit = FALSE;
      goto Done;
    }

if(gCardInit)
{
  DEBUG ((EFI_D_INFO, "MSHC::SdReadWrite is called Buffersize:%d \n", BufferSize));

  if (Buffer == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto Done;
  }

  if (Lba > This->Media->LastBlock) {
    Status = EFI_INVALID_PARAMETER;
    DEBUG ((EFI_D_ERROR, "MSHC::SdReadWrite EFI_INVALID_PARAMETER\n"));
    goto Done;
  }

  if ((BufferSize % This->Media->BlockSize) != 0) {
    Status = EFI_BAD_BUFFER_SIZE;
    DEBUG ((EFI_D_ERROR, "MSHC::SdReadWrite EFI_BAD_BUFFER_SIZE\n"));    
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
else
    return EFI_TIMEOUT;
    

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
#define EMMC_TEST_SIZE  (MAX_MSHC_TRANSFER_SIZE+1024)
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
   for(Count=100; Count<102; Count++)
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
           DEBUG ((1, "MSHC::Read Write OK!!\n"));
       else
           DEBUG ((1, "MSHC::Read Write Failed  bWrite[%d]=0x%x : bRead[%d]=0x%x\n", ret, bWrite[ret], ret, bRead[ret]));
           
           
   }
       

}
#endif 


#define FVB_TEST    0

#if FVB_TEST
#define FVB_TEST_SIZE  1336//(64)
#define FVB_Offset  64 //0
UINT32 FVB_Read[512*3];
UINT32 FVB_Write[512*3];
UINT32 Temp[512*3];
void FVB_Test(IN EFI_BLOCK_IO_PROTOCOL *This)
{
    EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *Fvbhandle;
    EFI_STATUS status = EFI_SUCCESS;
    EFI_LBA Lba = 10;
    UINTN NumBytes=FVB_TEST_SIZE;
    UINT32 i;
    INTN ret;    
    UINTN Offset=FVB_Offset;
    //EFI_FVB_ATTRIBUTES_2 *Attribute=NULL;
    UINTN blocksize=0, numofblocks=0;
   UINTN EraseStartBlock=10, EraseNumBlocks=5;  
   EFI_PHYSICAL_ADDRESS *Address=NULL;
    

    Fvbhandle = (EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *)This;
    DEBUG ((1, "FVB_Test Start \n"));

    status = SdReadWrite (This, 0, &Temp[0], 512, READ);
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((1, "FVB_Test Card Init Failed !!\n"));
        goto Exit;
    }    

    for(i=0; i<512; i++)
    {
        FVB_Write[i]=i;
    }
    ZeroMem (&FVB_Read[0], 512);

    //DEBUG ((1, "FVB_Test FvbGetAttributes \n"));
   //FvbGetAttributes(Fvbhandle, Attribute);
   FvbGetPhysicalAddress(Fvbhandle, Address);
   FvbGetBlockSize(Fvbhandle, 0, &blocksize,  &numofblocks);
   DEBUG ((1, "FVB_Test erase\n"));    
   FvbEraseBlocks(Fvbhandle, EraseStartBlock, EraseNumBlocks, EFI_LBA_LIST_TERMINATOR);

    DEBUG ((1, "FVB_Test Offset : %d  Num : %d\n", Offset, NumBytes));    
    status = FvbWrite(Fvbhandle, Lba, Offset, &NumBytes, (UINT8 *)&FVB_Write[Offset]);
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((1, "FVB_Test write fail !!\n"));
        goto Exit;
    }
    
    status = FvbRead(Fvbhandle, Lba, Offset, &NumBytes, (UINT8 *)&FVB_Read[0]);    
    if(status!=EFI_SUCCESS)
    {
        DEBUG ((1, "FVB_Test read fail !!\n"));
        goto Exit;
    }

   DEBUG ((1, "FVB W: 0x%x, 0x%x, 0x%x, 0x%x    ",
           FVB_Write[Offset], FVB_Write[Offset+1], FVB_Write[Offset+2], FVB_Write[Offset+3]));
   DEBUG ((1, "FVB R : 0x%x, 0x%x, 0x%x, 0x%x\n",
           FVB_Read[0], FVB_Read[1], FVB_Read[2], FVB_Read[3]));
   
   ret = CompareMem(&FVB_Write[Offset], &FVB_Read[0], FVB_TEST_SIZE);
   
   if(ret==0)
       DEBUG ((1, "MSHC::FVB_Test OK!!\n"));
   else
       DEBUG ((1, "MSHC::ERROR !!! FVB_Test Failed   bWrite[%d]=0x%x : bRead[%d]=0x%x\n", ret, FVB_Write[ret], ret, FVB_Read[ret]));

    Exit:
        if(status!=EFI_SUCCESS)
            DEBUG ((1, "FVB_Test fail !!\n"));        

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
    DEBUG ((EFI_D_INFO, "MSHC::MSHCReadBlocks : MediaId = %x, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
    			MediaId, (UINTN)Lba, BufferSize, Buffer));

  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, READ);

#if 0
#if FVB_TEST
    FVB_Test(This);
#else
#if EMMC_TEST
    MSHC_Test(This);
#else    
  //Perform Read operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, READ);
#endif   
#endif //#if FVB_TEST
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

  DEBUG ((EFI_D_INFO, "MSHC::MSHCWriteBlocks : MediaId = 0x%x, Lba = %d, BufferSize = %d, Buffer = 0x%x\n",
  					MediaId, (UINTN)Lba, BufferSize, Buffer));

  //Perform write operation.
  Status = SdReadWrite (This, (UINTN)Lba, Buffer, BufferSize, WRITE);


#if 0
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
       DEBUG ((1, "MSHC::Read Write Test OK!!\n"));
    else
       DEBUG ((1, "MSHC::Read Write Test Failed -.-   bRead[%d]=0x%x  bWrite[%d]=0x%x \n", ret, bRead[ret], ret, bWrite[ret]));
             
#endif 
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
  DEBUG ((EFI_D_INFO, "MSHC::MSHCFlushBlocks is called\n"));
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


EFI_STATUS
EFIAPI
MSHCInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;
  
  ZeroMem (&gCardInfo, sizeof (CARD_INFO));

//Publish BlockIO. 
  Status = gBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiBlockIoProtocolGuid,    &gBlockIo,
                &gEfiDevicePathProtocolGuid, &gMSHCDevicePath,
                NULL
                );

  DEBUG ((EFI_D_INFO, "MSHC::MSHCInitialize:0x%x\n", Status));
  return Status;
}
