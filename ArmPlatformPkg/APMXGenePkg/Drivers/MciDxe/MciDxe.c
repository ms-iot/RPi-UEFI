/**
 * SDIO Module
 *
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

#include <Include/APMXGeneAHBCCsr.h>
#include <MciDxe.h>


//#define MCI_DBG
//#define MCI_DBG_IO
//#define MCI_TRACE

#ifdef MCI_TRACE
#define TRACE(arg...) DEBUG((EFI_D_BLKIO,## arg))
#else
#define TRACE(arg...)
#endif

#define MCI_ERROR(arg...) DEBUG((EFI_D_ERROR,## arg))


#ifdef MCI_DBG
#define DBG(arg...) DEBUG((EFI_D_BLKIO,## arg))
#else
#define DBG(arg...)
#endif

#ifdef MCI_DBG_IO
#define DBG_IO(arg...) DEBUG((EFI_D_BLKIO,## arg))
#else
#define DBG_IO(arg...)
#endif

#define MMCI0_BLOCKLEN 512

#define AHBCCLKRSTOFFSET 0xC000


UINT64                     *gAHBCBaseAddress;
UINT64                     *gSDIO0BaseAddress;
UINT64                     *gSDIO1BaseAddress;
struct APM_SDHCI_HOST_T    gListMciHost[APM_SDHCI_HOST_SUPPORT];
UINTN                      gNumListMciHostActive;

UINT8                      gMaxDataTransferRate = 0;
UINT16                     gRca = 0;
BOOLEAN                    gBitModeSet = FALSE;

VOID AHBCWriteReg(IN UINT32 Reg, IN UINT32 Value)
{
  DBG_IO("AHBCWriteReg : write Reg 0x%llx value:0x%x\n",
      (UINT64)gAHBCBaseAddress + Reg, Value);
  *(volatile UINT32 *)((UINT64)gAHBCBaseAddress + Reg) = Value;
}

UINT32 AHBCReadReg(IN UINT32 Reg)
{
  UINT32 Val;
  Val = *(volatile UINT32 *)((UINT64)gAHBCBaseAddress + Reg);
  DBG_IO("AHBCReadReg : read Reg 0x%llx value:0x%x\n", (UINT64)gAHBCBaseAddress + Reg, Val);
  return Val;
}

UINT8 SDHCIReadReg8(IN UINT8 *Reg)
{
  UINT32 Val;
  UINT32 Val_Act;
  UINT32 *Base = (UINT32*)((UINT64)Reg & ~0x3);
  UINTN Shift = ((UINT64)Reg & 0x3) * 8;

  Val_Act = *(volatile UINT32 *)(Base);
  Val = ((Val_Act >> Shift) & 0xFF);
  DBG_IO("SDHCIReadReg8 : read Reg at 0x%llx value: 0x%x\n", (VOID *)Reg, Val);
  return (UINT8)Val;
}

UINT16 SDHCIReadReg16(IN UINT16 *Reg)
{
  UINT32 Val;
  UINT32 Val_Act;
  UINT32 *Base = (UINT32*)((UINT64)Reg & ~0x3);
  UINTN Shift = ((UINT64)Reg & 0x2) * 8;

  Val_Act = *(volatile UINT32 *)(Base);
  Val = ((Val_Act >> Shift) & 0xFFFF);
  DBG_IO("SDHCIReadReg16 : read Reg at 0x%llx value: 0x%x\n", (VOID *)Reg, Val);
  return (UINT16)Val;
}

UINT32 SDHCIReadReg32(IN UINT32 *Reg)
{
  UINT32 Val;
  Val = *(volatile UINT32 *)(Reg);
  DBG_IO("SDHCIReadReg32 : read Reg at 0x%llx value: 0x%x\n", (VOID *)Reg, Val);
  return Val;
}

VOID SDHCIWriteReg8(IN UINT8 *Reg, IN UINT8 Value)
{
  DBG_IO("SDHCIWriteReg8 : write Reg at 0x%llx value:0x%x\n", (VOID *)Reg, Value);
  UINT32 *Base = (UINT32 *)((UINT64)Reg & ~0x3);
  UINTN Shift = ((UINT64)Reg & 0x3) * 8;
  *(volatile UINT32 *)(Base) = ((SDHCIReadReg32(Base) & ~(((UINT32) 0xFF) << Shift)) | (((UINT32) Value) << Shift));
}

VOID
SDHCIWriteReg16(IN UINT16 *Reg, IN UINT16 Value)
{
  DBG_IO("SDHCIWriteReg16 : write Reg at 0x%llx value:0x%x\n", (VOID *)Reg, Value);
  UINT32 *Base = (UINT32 *)((UINT64)Reg & ~0x3);
  UINTN Shift = ((UINT64)Reg & 0x2) * 8;
  *(volatile UINT32 *)(Base) = ((SDHCIReadReg32(Base) & ~(((UINT32) 0xFFFF) << Shift)) | (((UINT32) Value) << Shift));
}

VOID
SDHCIWriteReg32(IN UINT32*Reg, IN UINT32 Value)
{
  DBG_IO("SDHCIWriteReg32 : write Reg at 0x%llx value:0x%x\n",
        (VOID *)Reg, Value);
  *(volatile UINT32 *)(Reg) = Value;
}

EFI_STATUS APMSDHCISetPowerCtrl(IN struct APM_SDHCI_HOST_T *Host)
{
  UINT32 Cap;
  UINT8 Ctrl;
  DBG("APMSDHCISetPowerCtrl called\n");

  /* Read capabilities register of host controller */
  Cap = SDHCIReadReg32(&Host->Reg->Capareg1);

  /* Select voltage level */
  Ctrl = SDHCIReadReg8(&Host->Reg->Pwrcon);

  if (Cap & (1 << 24)) {
    DBG("3.3v support\n");
    Ctrl |= 0x0E | 0x01; /* 3.3v support */
  } else if (Cap & (1 << 25)) {
    DBG("3.0v support\n");
    Ctrl |= 0x0C | 0x01; /* 3.0v support */
  } else if (Cap & (1 << 26)) {
    DBG("1.8v support\n");
    Ctrl |= 0x0A | 0x01; /* 1.8v support */
  } else {
    return EFI_INVALID_PARAMETER;
  }
  SDHCIWriteReg8(&Host->Reg->Pwrcon, Ctrl);
  Ctrl = SDHCIReadReg8(&Host->Reg->Pwrcon);

  MicroSecondDelay(1000);
  return EFI_SUCCESS;
}

EFI_STATUS APMSDHCIResetPort(IN struct APM_SDHCI_HOST_T *Host, IN UINT32 Mask)
{
  INTN Timeout;
  UINT8 Reg;
  DBG(" APMSDHCIResetPort called\n");

  Reg = SDHCIReadReg8(&Host->Reg->Swrst);
  Reg |= Mask;
  SDHCIWriteReg8(&Host->Reg->Swrst, Reg);

  Host->Clock = 0;

  /* Wait max 100 ms */
  Timeout = 100;

  /* hw clears the bit when it's done */
  while (SDHCIReadReg8(&Host->Reg->Swrst) & Mask) {
    if (Timeout == 0) {
      DBG("%s: timeout error\n", __func__);
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(1000);
  }
  return EFI_SUCCESS;
}


EFI_STATUS APMSDHCICheckMemRdy(VOID)
{
  UINT32 Val;
  INTN Timeout = 5000;
  UINT64 Ahbc_Diag_Base = REGSPEC_AHBC_GLBL_DIAG_CSR_I_BASE_ADDR;

  DBG(" APMSDHCICheckMemRdy called\n");

  *(volatile UINT32 *)(Ahbc_Diag_Base + REGSPEC_CFG_MEM_RAM_SHUTDOWN_ADDR) = 0x00;
  MicroSecondDelay(1000);

  Val = *(volatile UINT32 *)(Ahbc_Diag_Base + REGSPEC_BLOCK_MEM_RDY_ADDR);

  while (Val != 0xFFFFFFFF) {
    Val = *(volatile UINT32 *)(Ahbc_Diag_Base + REGSPEC_BLOCK_MEM_RDY_ADDR);
    if(Timeout == 0) {
      DBG("%s: timeout error\n", __func__);
      DBG("AHBC_BLOCK_MEM_RDY[0x%llx] 0x%08X ! \n", Ahbc_Diag_Base + REGSPEC_BLOCK_MEM_RDY_ADDR, Val);
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(1000);
  }
  return EFI_SUCCESS;
}

EFI_STATUS APMSDHCIEnableClk(IN struct APM_SDHCI_HOST_T *Host)
{
  DBG(" APMSDHCIEnableClk called\n");
  UINT16 Reg;

  Reg = SDHCIReadReg16(&Host->Reg->Clkcon);
  DBG(" APMSDHCIEnableClk: Clkcon value:0x%x\n", Reg);
  Reg &= ~0x0004;
  SDHCIWriteReg16(&Host->Reg->Clkcon, Reg);
  MicroSecondDelay(200);

  /* Enable internal clock */
  Reg  = SDHCIReadReg16(&Host->Reg->Clkcon);
  Reg |= 0x0001;
  SDHCIWriteReg16(&Host->Reg->Clkcon, Reg);

  /* Wait until internal clock is stable before continue */
  do {
    MicroSecondDelay(200);
    Reg  = SDHCIReadReg16(&Host->Reg->Clkcon);
  } while (!(Reg & 0x02));

  /* Enable SD clock after internal clock is stable */
  Reg |= 0x0004;
  SDHCIWriteReg16(&Host->Reg->Clkcon, Reg);
  MicroSecondDelay(200);

  /* Check to make sure SD clock is enabled */
  Reg  = SDHCIReadReg16(&Host->Reg->Clkcon);
  if (!(Reg & 0x0004)) {
    return EFI_NOT_READY;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
APMSDHCIChangeBusWidth(IN struct APM_SDHCI_HOST_T *Host, IN UINTN BusWidth)
{
  UINT8 Reg;
  DBG(" APMSDHCIChangeBusWidth called\n");
  UINT32 Cap;
  /* Enable internal clock */
  Reg  = SDHCIReadReg8(&Host->Reg->Hostctl);
  DBG(" APMSDHCIChangeBusWidth Hostctl: 0x%x\n", Reg);
  if (BusWidth == 8) {
    Reg |= (1 << 5);
  } else if (BusWidth == 4) {
    Cap = SDHCIReadReg32(&Host->Reg->Capareg1);
    if (Cap & SDHCI_CAN_DO_HISPD) {
      Reg |= SDHCI_CTRL_HISPD;
    }
    Reg |= (1 << 1);
  } else {
    Reg &= ~(1 << 1);
  }
  Host->Bus_Width = BusWidth;
  SDHCIWriteReg8(&Host->Reg->Hostctl, Reg);
  MicroSecondDelay(100);
  DBG("Change bus width :%d\n", BusWidth);
  return EFI_SUCCESS;
}

UINT32
CalculateCardCLKD (VOID)
{
  UINTN    TransferRateValue = 0;
  UINTN    TimeValue = 0 ;
  UINT32    Frequency = 0;

  DBG("CalculateCardCLKD()\n");

  // For SD Cards  we would need to send CMD6 to set
  // speeds abouve 25MHz. High Speed mode 50 MHz and up

  // Calculate Transfer rate unit (Bits 2:0 of TRAN_SPEED)
  switch (gMaxDataTransferRate & 0x7) { // 2
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
      DEBUG ((DEBUG_BLKIO, "Invalid parameter.\n"));
      ASSERT(FALSE);
      return 0;
  }

  //Calculate Time value (Bits 6:3 of TRAN_SPEED)
  switch ((gMaxDataTransferRate >> 3) & 0xF) { // 6
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
      DBG ("Invalid parameter.\n");
      ASSERT(FALSE);
      return 0;
  }

  Frequency = TransferRateValue * TimeValue/10;

  DBG ("gMaxDataTransferRate: 0x%x, Frequency: %d KHz\n", gMaxDataTransferRate, Frequency/1000);
  return Frequency;
}

EFI_STATUS APMSDHCIChangeClk(IN struct APM_SDHCI_HOST_T *Host, IN UINT32 Clock)
{
  UINT32 Cap;
  INTN Div;
  UINT32 Sdio_Freq;
  UINT16 Clk;
  INTN Timeout;

  DBG(" APMSDHCIChangeClk called\n");

  if (Clock == 0) {
    Host->Clock = Clock;
    return EFI_INVALID_PARAMETER;
  }
  /* Read capabilities register of host controller */
  Cap = SDHCIReadReg32(&Host->Reg->Capareg1);

  Sdio_Freq = (Cap & 0x0000ff00) >> 8;
  Sdio_Freq *= 1000000;

  DBG(" Sdio_Freq: 0x%lld\n", Sdio_Freq);
  Div = Sdio_Freq / Clock;

  if (Div > 1) {
    Div--;
  } else {
    Div = 1;
  }
  if (Div > 0x2 && Div < 0x4) {
    Div = 0x2;
  } else if (Div > 0x4 && Div < 0x8) {
    Div = 0x4;
  } else if (Div > 0x8 && Div < 0x10) {
    Div = 0x8;
  } else if (Div > 0x10 && Div < 0x20) {
    Div = 0x10;
  } else if (Div > 0x20 && Div < 0x40) {
    Div = 0x20;
  } else if (Div > 0x40 && Div < 0x80) {
    Div = 0x40;
  } else if (Div > 0x80) {
    Div = 0x80;
  }
  SDHCIWriteReg16(&Host->Reg->Clkcon, 0);

  /*
   * CLKCON
   * SELFREQ[15:8]  : base clock divided by value
   * ENSDCLK[2]    : SD Clock Enable
   * STBLINTCLK[1]  : Internal Clock Stable
   * ENINTCLK[0]    : Internal Clock Enable
   */
  Clk = ((Div << APM_SDHCI_CLKCON_SDCLK_FREQ_SEL_SHIFT) |
         APM_SDHCI_CLKCON_INTERNAL_CLOCK_ENABLE);
  SDHCIWriteReg16(&Host->Reg->Clkcon, Clk);

  /* Wait max 10 ms */
  Timeout = 10;

  while (!(SDHCIReadReg16(&Host->Reg->Clkcon) &
     APM_SDHCI_CLKCON_INTERNAL_CLOCK_STABLE)) {
    if (Timeout == 0) {
      DBG("%s: timeout error\n", __func__);
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(1000);
  }

  Clk |= APM_SDHCI_CLKCON_SD_CLOCK_ENABLE;
  SDHCIWriteReg16(&Host->Reg->Clkcon, Clk);
  MicroSecondDelay(100);

  Host->Clock = Clock;

  DBG("APMSDHCIChangeClk: Clock = %08x\n", Clk);

  return EFI_SUCCESS;
}

BOOLEAN APMSDHCIDetectCard(IN struct APM_SDHCI_HOST_T *Host)
{
  UINT32 Reg;
  /* Check if card present */
  Reg = SDHCIReadReg32(&Host->Reg->Prnsts);
  return (Reg & 0x00010000) ? TRUE : FALSE;

}

EFI_STATUS APMSDHCISetIntMask(IN struct APM_SDHCI_HOST_T *Host)
{
  UINT32 Reg;

  /* Enable interrupt and clear interrupt */
  Reg = SDHCIReadReg32((UINT32 *)&Host->Reg->Norintstsen);
  Reg |= 0x00FF00FB;
  SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintstsen, Reg);
  MicroSecondDelay(200);

  SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsigen, Reg);
  MicroSecondDelay(200);

  SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, 0xFFFFFFFF);
  MicroSecondDelay(200);

  return EFI_SUCCESS;
}

EFI_STATUS APMSDHCISetLed(IN struct APM_SDHCI_HOST_T *Host, IN UINT8 Is_On)
{
  UINT8 Ret;

  Ret = SDHCIReadReg8(&Host->Reg->Hostctl);
  Ret |= (Is_On & 0x1);
  SDHCIWriteReg8(&Host->Reg->Hostctl, Ret);
  MicroSecondDelay(200);

  return EFI_SUCCESS;
}

EFI_STATUS APMSDHCISetTimeout(IN struct APM_SDHCI_HOST_T *Host)
{
  UINT8 Ret;

  Ret = 0x0E;
  SDHCIWriteReg8(&Host->Reg->Timeoutcon, Ret);
  MicroSecondDelay(200);

  return EFI_SUCCESS;
}

EFI_STATUS APMSDHCIPortInit(IN struct APM_SDHCI_HOST_T *Host)
{
  EFI_STATUS Ret;
  UINT8     Val;

  DBG("Port Init Entry\n");

  Ret = APMSDHCIResetPort(Host, APM_SDHCI_SWRST_SW_RESET_FOR_ALL);
  if (EFI_ERROR(Ret)) {
    MCI_ERROR("APM_SDHCI_Reset_port failed\n");
    goto LBL_FAIL;
  }

  Ret = APMSDHCISetPowerCtrl(Host);
  if (EFI_ERROR(Ret)) {
    MCI_ERROR("APMSDHCISetPowerCtrl failed\n");
    goto LBL_FAIL;
  }

  Val = SDHCIReadReg8(&Host->Reg->Hostctl);
  Val |= SDHCI_CTRL_CD_TEST_INS | SDHCI_CTRL_CD_TEST;
  SDHCIWriteReg8(&Host->Reg->Hostctl, Val);

  Ret = APMSDHCIEnableClk(Host);
  if (EFI_ERROR(Ret)) {
    MCI_ERROR("APMSDHCIEnableClk failed\n");
    goto LBL_FAIL;
  }

  APMSDHCISetIntMask(Host);

  if (!APMSDHCIDetectCard(Host)) {
    MCI_ERROR("No card on slot %d\n", Host->Index);
    goto LBL_FAIL;
  }

  Ret = APMSDHCISetLed(Host, 1);
  Ret |= APMSDHCISetTimeout(Host);

  goto LBL_SUCCESS;

LBL_FAIL:
  Ret = EFI_DEVICE_ERROR;

LBL_SUCCESS:
  return Ret;
}

EFI_STATUS
APMSDHCIProgMux(IN UINTN Slot)
{
  UINT32 Val;

  switch (Slot) {
  case 0:
  default:
    /* For PIN MUX and deep sleep PIN MUX, see documentation */

    /* Select SDIO_CLK_S1_OUT , SDIO_CMD, SDIO_DATA0, SDIO_DATA1_S1,
            SDIO_DATA2, SDIO_DATA3, SDIO_BUS_VOLT1, SDIO_CD_S1_N */

    Val = AHBCReadReg(CFG_PIN_MUX_SEL_1_ADDR);
    Val &= ~ 0x33F3F300;
    Val |=  0x00000000;   /* Select Alternate function 0 */
    AHBCWriteReg(CFG_PIN_MUX_SEL_1_ADDR, Val);

    /* Select SDIO_LED_ON_S1, SDIO_WP_S1, SDIO_MMC_RSTN1, SDIO_BPWR_EN1*/

    Val = AHBCReadReg(CFG_PIN_MUX_SEL_2_ADDR);
    Val &= ~ 0x00003333;
    Val |=  0x00000000;   /* Select Alternate fcuntion 0 */
    AHBCWriteReg(CFG_PIN_MUX_SEL_2_ADDR, Val);
    break;
  case 1:
    /* Select SDIO_CLK_S2_OUT , SDIO_CMD, SDIO_DATA0, SDIO_DATA1_S2,
      SDIO_DATA2, SDIO_DATA3, SDIO_BUS_VOLT2, SDIO_CD_S2_N */

    Val = AHBCReadReg(CFG_PIN_MUX_SEL_1_ADDR);
    Val &= ~ 0xCCFCFC00;
    Val |=  0x00000000; /* Select Alternate function 1 */
    AHBCWriteReg(CFG_PIN_MUX_SEL_1_ADDR, Val);

    /* Select SDIO_LED_ON_S2, SDIO_WP_S2, SDIO_MMC_RSTN2, SDIO_BPWR_EN2 */

    Val = AHBCReadReg(CFG_PIN_MUX_SEL_2_ADDR);
    Val &= ~0x0000CCCC;
    Val |=  0x00000000;  /* Select Alternate function 1 */
    AHBCWriteReg(CFG_PIN_MUX_SEL_2_ADDR, Val);
    break;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
APMSDHCISetHostCap(IN struct APM_SDHCI_HOST_T *Host)
{
  UINT32 Off_Cap_L;
  UINT32 Off_Cap_H;
  DBG("Set Host Cap\n");
  if (Host->Cap.Cap_Low == 0 && Host->Cap.Cap_High == 0) {
    DBG("We don't set cap right now\n");
    return EFI_SUCCESS;
  }

  switch (Host->Index) {
  case 0:
    Off_Cap_L = SDHC_CAP_REG_LOW_S1_ADDR;
    Off_Cap_H = SDHC_CAP_REG_HIGH_S1_ADDR;
    DBG("Set Host Cap for controller 0\n");
    break;
  case 1:
    Off_Cap_L = SDHC_CAP_REG_LOW_S2_ADDR;
    Off_Cap_H = SDHC_CAP_REG_HIGH_S2_ADDR;
    DBG("Set Host Cap for controller 1\n");
    break;
  default:
    return EFI_INVALID_PARAMETER;
  }
  AHBCWriteReg(Off_Cap_L, Host->Cap.Cap_Low);
  AHBCWriteReg(Off_Cap_H, Host->Cap.Cap_High);

  return EFI_SUCCESS;
}

EFI_STATUS
APMSDHCIInit(VOID)
{
  UINT32 Val;
  UINTN i;
  UINT32 Sd_Phy_Enable = (UINT32) FixedPcdGet32 (PcdSDIOHostPhyEnableMask);
  gAHBCBaseAddress = (UINT64 *) FixedPcdGet64 (PcdAHBCRegisterBase);

  gSDIO0BaseAddress = (UINT64 *) FixedPcdGet64 (PcdSDIORegisterBase);
  gSDIO1BaseAddress = gSDIO0BaseAddress + 0x100;

  if (Sd_Phy_Enable & 0x1) {
    APMSDHCIProgMux(0);
    gListMciHost[gNumListMciHostActive].Index = 0;
    gListMciHost[gNumListMciHostActive].Base = gSDIO0BaseAddress;
    gListMciHost[gNumListMciHostActive].Reg =
        (struct APM_SDHCI_REG_T *)gListMciHost[gNumListMciHostActive].Base;
    gListMciHost[gNumListMciHostActive].Cap.Cap_Low = (UINT32) FixedPcdGet32 (PcdSDIOCapLow);
    gListMciHost[gNumListMciHostActive].Cap.Cap_High = (UINT32) FixedPcdGet32 (PcdSDIOCapHigh);
    gNumListMciHostActive++;
  } else if (Sd_Phy_Enable & 0x2) {
    APMSDHCIProgMux(1);
    gListMciHost[gNumListMciHostActive].Index = 1;
    gListMciHost[gNumListMciHostActive].Base = gSDIO1BaseAddress;
    gListMciHost[gNumListMciHostActive].Reg =
        (struct APM_SDHCI_REG_T *)gListMciHost[gNumListMciHostActive].Base;
    gListMciHost[gNumListMciHostActive].Cap.Cap_Low = (UINT32) FixedPcdGet32 (PcdSDIOCapLow);
    gListMciHost[gNumListMciHostActive].Cap.Cap_High = (UINT32) FixedPcdGet32 (PcdSDIOCapHigh);
    gNumListMciHostActive++;
  } else {
    /* Maximum 2 hosts */
    return EFI_INVALID_PARAMETER;
  }
  DBG("Number of port actived: %d\n", gNumListMciHostActive);
  for (i = 0; i < gNumListMciHostActive; i++) {
    APMSDHCISetHostCap(&gListMciHost[i]);
  }

  Val = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR);
  Val &= ~CFG_CLKEN_SDIO_MASK;
  AHBCWriteReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR, Val);
  Val = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR);

  MicroSecondDelay(1000);

  Val = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR);
  Val |= CFG_CLKEN_SDIO_MASK;
  AHBCWriteReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR, Val);
  Val = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_CLKEN_ADDR);

  MicroSecondDelay(1000);

  Val  = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR);
  Val |= CFG_SDIO_RST_MASK;
  AHBCWriteReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR,Val);
  Val  = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR);

  MicroSecondDelay(1000);

  Val  = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR);
  Val &= ~CFG_SDIO_RST_MASK;
  AHBCWriteReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR,Val);
  Val  = AHBCReadReg(AHBCCLKRSTOFFSET + AHBC_SRST_ADDR);

  MicroSecondDelay(1000);

  return APMSDHCICheckMemRdy();

}

EFI_GUID gMciDevicePathGuid[APM_SDHCI_HOST_SUPPORT] = {
  {0xb225ed30, 0x6dfd, 0x43a9,  { 0xbf, 0x6b, 0x57, 0x53, 0x35, 0x8f, 0x2f, 0x70} },
  {0x30b3030d, 0x3310, 0x4c8c,  { 0xa3, 0x11, 0x5f, 0xa0, 0xc9, 0xf3, 0xc0, 0x1b} }
};

EFI_STATUS
MciBuildDevicePath (
  IN EFI_MMC_HOST_PROTOCOL      *This,
  IN EFI_DEVICE_PATH_PROTOCOL   **DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *NewDevicePathNode;
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;

  NewDevicePathNode = CreateDeviceNode(HARDWARE_DEVICE_PATH,HW_VENDOR_DP,sizeof(VENDOR_DEVICE_PATH));
  CopyGuid(&((VENDOR_DEVICE_PATH*)NewDevicePathNode)->Guid,&gMciDevicePathGuid[Host->Index]);

  *DevicePath = NewDevicePathNode;
  return EFI_SUCCESS;
}


BOOLEAN
MciIsCardPresent (
  IN EFI_MMC_HOST_PROTOCOL     *This
  )
{
  return APMSDHCIDetectCard((struct APM_SDHCI_HOST_T *)This->InternalData);
}

BOOLEAN
MciIsReadOnly (
  IN EFI_MMC_HOST_PROTOCOL     *This
  )
{
  UINT32 Reg;
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;
  /* Check if card present */
  Reg = SDHCIReadReg32(&Host->Reg->Prnsts);
  return (Reg & 0x00080000) ? FALSE : TRUE;
}


VOID MciPrepareData(IN struct APM_SDHCI_HOST_T *Host, IN UINT32 Blkcnt)
{
  /* FIXME: Use DMA */
  SDHCIWriteReg16(&Host->Reg->Blksize, MMCI0_BLOCKLEN & 0xFFF);
  SDHCIWriteReg16(&Host->Reg->Blkcnt, Blkcnt);
}

EFI_STATUS MciWaitInhibit(IN struct APM_SDHCI_HOST_T *Host,
                             IN MMC_CMD MmcCmd,
                             IN BOOLEAN DatWait,
                             IN UINTN Timeout)
{
  DBG(" MciWaitInhibit called\n");
  /*
   * PRNSTS
   * CMDINHDAT[1] : Command Inhibit (DAT)
   * CMDINHCMD[0] : Command Inhibit (CMD)
   */
  UINT32 Mask = APM_SDHCI_PRNSTS_CMD_INHIBIT_CMD;

  /*
   * We shouldn't wait for data inhibit for stop commands, even
   * though they might use busy signaling
   */
  if ((DatWait))
    Mask |= APM_SDHCI_PRNSTS_CMD_INHIBIT_DAT;

  while (SDHCIReadReg32(&Host->Reg->Prnsts) & Mask) {
    if (Timeout == 0) {
      DBG("%s: timeout error\n", __func__);
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(10);
  }

  return EFI_SUCCESS;
}

VOID MciSetTransferMode(IN struct APM_SDHCI_HOST_T *Host,
                                IN UINT16 Direction,
                                IN INTN Num_Block)
{
  UINT16 Mode;
  DBG(" MciSetTransferMode called with num_block:%d\n", Num_Block);
  /*
   * TRNMOD
   * MUL1SIN0[5]  : Multi/Single Block Select
   * RD1WT0[4]  : Data Transfer Direction Select
   *  1 = read
   *  0 = write
   * ENACMD12[2]  : Auto CMD12 Enable
   * ENBLKCNT[1]  : Block Count Enable
   * ENDMA[0]  : DMA Enable
   */
  /* FIXME: Use DMA */
  Mode = 0;
  Mode &= (~APM_SDHCI_TRNMOD_DMA_ENABLE);

  if (Num_Block > 1) {
    Mode |= APM_SDHCI_TRNMOD_MULTI_BLOCK_SELECT |
              APM_SDHCI_TRNMOD_BLOCK_COUNT_ENABLE;
  }
  Mode |= Direction;

  SDHCIWriteReg16(&Host->Reg->Trnmod, Mode);
  MicroSecondDelay(10);
}

EFI_STATUS
MciSendCommand (
  IN EFI_MMC_HOST_PROTOCOL     *This,
  IN MMC_CMD                    MmcCmd,
  IN  UINT32                    Argument,
  IN struct MMC_DATA            *Mmc_Data
  )
{
  DBG(" MciSendCommand called\n");

  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;
  UINTN Flags, i;
  EFI_STATUS Ret = EFI_SUCCESS;
  UINT32 Mask;
  BOOLEAN HaveData = FALSE;
  UINTN Retry = 0x100000;

  if (Mmc_Data)
    HaveData = TRUE;

  if ((MmcCmd == MMC_CMD17) || (MmcCmd == MMC_CMD18)) {
    Ret = MciWaitInhibit(Host, MmcCmd, HaveData, 10);
    MciPrepareData(Host, Mmc_Data->Blocks);
    MciSetTransferMode(Host, APM_SDHCI_TRNMOD_DATA_XFER_DIR_SEL_READ, Mmc_Data->Blocks);
  } else if ((MmcCmd == MMC_CMD24) || (MmcCmd == MMC_CMD25)) {
    Ret = MciWaitInhibit(Host, MmcCmd, HaveData, 10);
    MciPrepareData(Host, Mmc_Data->Blocks);
    MciSetTransferMode(Host, APM_SDHCI_TRNMOD_DATA_XFER_DIR_SEL_WRITE, Mmc_Data->Blocks);
  }

  if (EFI_ERROR(Ret)) {
    return Ret;
  }

  DBG("MmcCmd:%x cmd->arg: %08x\n", (UINT32)MmcCmd, Argument);
  SDHCIWriteReg32(&Host->Reg->Argument, Argument);

  /*
   * CMDREG
   * CMDIDX[13:8]  : Command index
   * DATAPRNT[5]  : Data Present Select
   * ENCMDIDX[4]  : Command Index Check Enable
   * ENCMDCRC[3]  : Command CRC Check Enable
   * RSPTYP[1:0]
   *  00 = No Response
   *  01 = Length 136
   *  10 = Length 48
   *  11 = Length 48 Check busy after response
   */
  if (!(MmcCmd & MMC_CMD_WAIT_RESPONSE)) {
    Flags = APM_SDHCI_CMDREG_RESP_TYPE_SELECT_NO_RESPONSE;
  } else if ((MmcCmd & MMC_CMD_LONG_RESPONSE)) {
    Flags = APM_SDHCI_CMDREG_RESP_TYPE_SELECT_LENGTH_136;
  } else {
    Flags = APM_SDHCI_CMDREG_RESP_TYPE_SELECT_LENGTH_48;
  }

  if (!(MmcCmd & MMC_CMD_NO_CRC_RESPONSE))
    Flags |= APM_SDHCI_TRNMOD_CMD_CRC_CHECK;

  if (HaveData) {
    Flags |= APM_SDHCI_TRNMOD_DATA_PRESENT_SELECT_DATA_TRANSFER;
  }

  SDHCIWriteReg16(&Host->Reg->Cmdreg, (MMC_GET_INDX(MmcCmd) << 8) | Flags);

  for (i = 0; i < Retry; i++) {
    Mask = SDHCIReadReg32((UINT32 *)&Host->Reg->Norintsts);
    /* Command Complete */
    if (Mask & APM_SDHCI_NORINTSTS_CMD_COMPLETE) {
      if (!HaveData) {
        SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Mask);
      }
      break;
    } else if (Mask & APM_SDHCI_NORINTSTS_CMD_TIMEOUT) {
      DBG("MciSendCommand: Command timeout\n");
      SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Mask);
      APMSDHCIResetPort(Host, APM_SDHCI_SWRST_SW_RESET_FOR_CMD_LINE);
      MicroSecondDelay(500);
      return EFI_TIMEOUT;
    } else if (Mask & APM_SDHCI_NORINTSTS_ERR_INTERRUPT) {
      /* Error Interrupt */
      DBG("error interrupt status: %04x cmd %d\n", Mask >> 16, MMC_GET_INDX(MmcCmd));
      SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Mask);
      return EFI_NOT_READY;
    }
  }

  if (i == Retry) {
    DBG("MciSendCommand: waiting for status update\n");
    SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Mask);
    return EFI_TIMEOUT;
  }

  MicroSecondDelay(100);

  return EFI_SUCCESS;
}

EFI_STATUS
MciReceiveResponse (
  IN EFI_MMC_HOST_PROTOCOL     *This,
  IN MMC_RESPONSE_TYPE          Type,
  IN UINT32*                    Buffer
  )
{
  DBG("MciReceiveResponse called\n");
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if ((Type == MMC_RESPONSE_TYPE_R1) || (Type == MMC_RESPONSE_TYPE_R1b) ||
      (Type == MMC_RESPONSE_TYPE_R3) || (Type == MMC_RESPONSE_TYPE_R6) ||
      (Type == MMC_RESPONSE_TYPE_R7))
  {
    Buffer[0] = SDHCIReadReg32(&Host->Reg->Rspreg0);
  } else if (Type == MMC_RESPONSE_TYPE_R2) {
    Buffer[3] = (SDHCIReadReg32(&Host->Reg->Rspreg3) << 8) |
                    ((SDHCIReadReg32(&Host->Reg->Rspreg2) & 0xFF000000) >> 24);
    Buffer[2] = SDHCIReadReg32(&Host->Reg->Rspreg2) << 8 |
                    ((SDHCIReadReg32(&Host->Reg->Rspreg1) & 0xFF000000) >> 24);
    Buffer[1] = SDHCIReadReg32(&Host->Reg->Rspreg1) << 8 |
                  ((SDHCIReadReg32(&Host->Reg->Rspreg0) & 0xFF000000) >> 24);
    Buffer[0] = SDHCIReadReg32(&Host->Reg->Rspreg0) << 8;
  }
  if (Type == MMC_RESPONSE_TYPE_CSD) {
    DBG("Set gMaxDataTransferRate to %d\n", Buffer[3] & 0xFF);
    gMaxDataTransferRate = Buffer[3] & 0xFF;
  } else if (Type == MMC_RESPONSE_TYPE_RCA) {
    DBG("Set gRca to %d\n", Buffer[0] >> 16);
    gRca = Buffer[0] >> 16 & 0xFFFF;
  }
  DBG("Respond type:%d\n", Type);
  DBG("Respond0:0x%x\n", Buffer[0]);
  DBG("Respond1:0x%x\n", Buffer[1]);
  DBG("Respond2:0x%x\n", Buffer[2]);
  DBG("Respond3:0x%x\n", Buffer[3]);
  return EFI_SUCCESS;
}

EFI_STATUS
MciReadBlockData (
  IN EFI_MMC_HOST_PROTOCOL     *This,
  IN EFI_LBA                    Lba,
  IN UINTN                      Length,
  IN UINT32*                    Buffer
  )
{
  DBG(" MciReadBlockData called\n");
  UINTN Loop;
  UINTN Count;
  UINTN Finish;
  UINT32 Status;
  EFI_STATUS RetVal =EFI_SUCCESS;
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;

  // Read data from the RX FIFO
  Loop = 0;
  Finish = Length / 4;
  do {
    // Read the Status flags
    Status = SDHCIReadReg32((UINT32 *)&Host->Reg->Norintsts);
    // Do eight reads if possible else a single read
    if (Status & APM_SDHCI_NORINTSTS_DATA_READ_READY) {
      SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);
      for (Count = 0 ; Count < MMCI0_BLOCKLEN/4; Count++) {
        Buffer[Loop] = SDHCIReadReg32(&Host->Reg->Bdata);
        Loop++;
      }
    } else {
      //Check for error conditions and timeouts
      if (Status & APM_SDHCI_NORINTSTS_ERR_INTERRUPT) {
        MCI_ERROR("MciReadBlockData(): Error interrup Status:0x%x\n",
                                 Status);
        SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);
        RetVal = EFI_DEVICE_ERROR;
        if(Status & APM_SDHCI_NORINTSTS_DATA_TIMEOUT) {
          DBG("MciReadBlockData(): TIMEOUT! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_TIMEOUT;
        } else if (Status & APM_SDHCI_NORINTSTS_DATA_CRC_ERROR) {
          DBG("MciReadBlockData(): CRC Error! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_CRC_ERROR;
        } else if (Status & APM_SDHCI_NORINTSTS_DATA_END_BIT_ERROR) {
          DBG("MciReadBlockData(): End-bit Error! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_NO_RESPONSE;
        }
        goto Exit;
      }
    }
  } while (!(Status & APM_SDHCI_NORINTSTS_XFER_COMPLETE));

  if (Loop < Finish) {
    MCI_ERROR("MciReadBlockData(): Complete transfer before read enough %d Error! Status:0x%x\n",
                            Length, Status);
    RetVal = EFI_DEVICE_ERROR;
  }

  SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);

Exit:
  return RetVal;
}

EFI_STATUS
MciWriteBlockData (
  IN EFI_MMC_HOST_PROTOCOL     *This,
  IN EFI_LBA                   Lba,
  IN UINTN                     Length,
  IN UINT32*                   Buffer
  )
{
  DBG(" MciWriteBlockData called\n");
  UINTN Loop;
  UINTN Count;
  UINTN Finish;
  UINT32 Status;
  EFI_STATUS RetVal = EFI_SUCCESS;
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;

  // Write the data to the TX FIFO
  Loop   = 0;
  Finish = Length / 4;
  do {
     // Read the Status flags
    Status = SDHCIReadReg32((UINT32 *)&Host->Reg->Norintsts);
    // Do eight writes if possible else a single write
    if (Status & APM_SDHCI_NORINTSTS_DATA_WRITE_READY) {
      //Clear sts
      SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);
      for (Count = 0 ; Count < MMCI0_BLOCKLEN/4; Count++) {
        SDHCIWriteReg32(&Host->Reg->Bdata, Buffer[Loop]);
        Loop++;
      }
    } else {
      if (Status & APM_SDHCI_NORINTSTS_ERR_INTERRUPT) {
        MCI_ERROR("MciWriteBlockData(): Error interrup Status:0x%x\n",
                                   Status);
        //Clear sts
        SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);
        RetVal = EFI_DEVICE_ERROR;
        //Check for error conditions and timeouts
        if (Status & APM_SDHCI_NORINTSTS_DATA_TIMEOUT) {
          DBG("MciWriteBlockData(): TIMEOUT! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_TIMEOUT;
        } else if (Status & APM_SDHCI_NORINTSTS_DATA_CRC_ERROR) {
          DBG("MciWriteBlockData(): CRC Error! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_CRC_ERROR;
        } else if (Status & APM_SDHCI_NORINTSTS_DATA_END_BIT_ERROR) {
          DBG("MciWriteBlockData(): End-bit Error! Response:0x%X Status:0x%x\n",
                                  SDHCIReadReg32(&Host->Reg->Rspreg3),Status);
          RetVal = EFI_NO_RESPONSE;
        }
        goto Exit;
      }
    }
  } while (!(Status & APM_SDHCI_NORINTSTS_XFER_COMPLETE));

  if (Loop < Finish) {
    MCI_ERROR("MciWriteBlockData(): Complete transfer before read enough %d Error! Status:0x%x\n",
                            Length, Status);
    RetVal = EFI_DEVICE_ERROR;
  }

  SDHCIWriteReg32((UINT32 *)&Host->Reg->Norintsts, Status);

Exit:
  return RetVal;
}

EFI_STATUS
MciNotifyState (
  IN  EFI_MMC_HOST_PROTOCOL     *This,
  IN MMC_STATE                  State
  )
{
  EFI_STATUS Status;
  struct APM_SDHCI_HOST_T *Host = (struct APM_SDHCI_HOST_T *)This->InternalData;
  UINT32 Freq;

  switch(State) {
  case MmcInvalidState:
    ASSERT(0);
    break;
  case MmcHwInitializationState:
    // If device already turn on then restart it
    TRACE("MciNotifyState(MmcHwInitializationState): Reset MCI\n");
    APMSDHCIPortInit(Host);
    APMSDHCIChangeBusWidth(Host, 1);
    APMSDHCIChangeClk(Host, 200000);
    break;
  case MmcIdleState:
    TRACE("MciNotifyState(MmcIdleState)\n");
    break;
  case MmcReadyState:
    TRACE("MciNotifyState(MmcReadyState)\n");
    break;
  case MmcIdentificationState:
    TRACE("MciNotifyState(MmcIdentificationState)\n");
    break;
  case MmcStandByState:{
    TRACE("MciNotifyState(MmcStandByState)\n");
    break;
  }
  case MmcTransferState:
    TRACE("MciNotifyState(MmcTransferState)\n");
    if (!gBitModeSet) {
      gBitModeSet = TRUE;
      Status = MciSendCommand (This, MMC_CMD55, gRca << 16, NULL);
      if (!EFI_ERROR (Status)) {
        // Set device into 4-bit data bus mode
        Status = MciSendCommand (This, MMC_ACMD6, 0x2, NULL);
        if (!EFI_ERROR (Status)) {
          // Set host controler into 4-bit mode
          APMSDHCIChangeBusWidth(Host, 4);
          DBG("SD Memory Card set to 4-bit mode\n");

        }
      }
      Freq = CalculateCardCLKD();
      APMSDHCIChangeClk(Host, Freq);
    }
    break;
  case MmcSendingDataState:
    TRACE("MciNotifyState(MmcSendingDataState)\n");
    break;
  case MmcReceiveDataState:
    TRACE("MciNotifyState(MmcReceiveDataState)\n");
    break;
  case MmcProgrammingState:
    TRACE("MciNotifyState(MmcProgrammingState)\n");
    break;
  case MmcDisconnectState:
    TRACE("MciNotifyState(MmcDisconnectState)\n");
    break;
  default:
    ASSERT(0);
  }
  return EFI_SUCCESS;
}

EFI_MMC_HOST_PROTOCOL gMciHost[APM_SDHCI_HOST_SUPPORT] = {
  {
    MMC_HOST_PROTOCOL_REVISION,
    MciIsCardPresent,
    MciIsReadOnly,
    MciBuildDevicePath,
    MciNotifyState,
    MciSendCommand,
    MciReceiveResponse,
    MciReadBlockData,
    MciWriteBlockData,
    NULL
  },
  {
    MMC_HOST_PROTOCOL_REVISION,
    MciIsCardPresent,
    MciIsReadOnly,
    MciBuildDevicePath,
    MciNotifyState,
    MciSendCommand,
    MciReceiveResponse,
    MciReadBlockData,
    MciWriteBlockData,
    NULL
  }
};

EFI_STATUS
MciDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_HANDLE    Handle = NULL;
  INTN i;

  TRACE("MciDxeInitialize()\n");
  gNumListMciHostActive = 0;
  APMSDHCIInit();

  //Publish Component Name, BlockIO protocol interfaces
  for (i = 0; i < gNumListMciHostActive; i++) {
    TRACE("Register MMC/SDIO host controller:%d\n", i);
    gMciHost[i].InternalData = &gListMciHost[i];
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &gEfiMmcHostProtocolGuid,  &gMciHost[i],
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
