/**
 * SPI Host library
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

#include <Library/DWSPI.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Guid/GlobalVariable.h>
#include <Guid/EventGroup.h>

#include <DWSPICsr.h>
#include <APMXGeneAHBCCsr.h>

#define TIMEOUT 0x200000
#define TIMEOUT_SLEEP 10

extern UINTN
EFIAPI
MicroSecondDelay (
  IN      UINTN                     MicroSeconds
  );

VOID
EFIAPI
ArmEnableInterrupts (
  VOID
  );

UINTN
EFIAPI
ArmDisableInterrupts (
  VOID
  );

//#define SPI_DBG

#define DWSPI_TX_FIFO_DEPTH    ((UINT32) PcdGet32(PcdDWSpiFifoDepth))
#define DWSPI_RX_FIFO_DEPTH    ((UINT32) PcdGet32(PcdDWSpiFifoDepth))
#define DWSPI_SYSCLK      ((UINT32) PcdGet32(PcdDWSpiSysClk))
#define DWSPI_MAXCS      ((UINT32) PcdGet32(PcdDWSpiMaxCS))
#define DWSPI_VERID      ((UINT32) PcdGet32(PcdDWSpiVerId))
#define DWSPI_BASE      ((UINT32) PcdGet64(PcdDWSpiBaseAddress))

#ifdef SPI_DBG
#define DBG(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define DBG(arg...)
#endif

struct DWSPI_XFER {
  UINTN Count;
  UINT8 *Tx_Ptr;
  UINT8 *Rx_Ptr;
};

struct DWSPI_CONTEXT {
  struct DWSPI_XFER Xfer[2];
  INTN Xfer_Count;
};

struct DWSPI_CONTEXT *Dwspi_Cntxt = NULL;
EFI_PHYSICAL_ADDRESS  SpiBase;
EFI_EVENT  mSpiVirtualAddressChangeEvent = NULL;

UINT32 DwSpiHostRead32(IN UINT64 Addr)
{
  //DBG(" Reg Addr = %x , Reg VAL = %x <--- \n",Addr, MmioRead32(Addr));
  return MmioRead32(Addr);
}

VOID DwSpiHostWrite32(IN UINT64 Addr, IN UINT32 Val)
{
  //DBG(" Reg Addr = %x , Before Write Reg VAL = %x, Value to be Written = %x ---> \n",Addr,MmioRead32(Addr), Val);
  MmioWrite32(Addr,Val);
  //DBG(" Reg Addr = %x , After Write Reg VAL = %x <--- \n",Addr, MmioRead32(Addr));
}

UINT32 DwSpiHostVersion(IN UINT64 Base)
{
  return DwSpiHostRead32(DWSPI_SSI_VER(Base));
} 

BOOLEAN DwSpiHostIsEnabled(IN UINT64 Base)
{
  UINT32 Dwspi_Stat;
  Dwspi_Stat = DwSpiHostRead32(DWSPI_SSIENR(Base));
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK) {
    return TRUE;
  }
  return FALSE;
}

VOID DwSpiHostEnable(IN UINT64 Base)
{
  UINT32 Dwspi_Stat;
  Dwspi_Stat = DwSpiHostRead32(DWSPI_SSIENR(Base));
  if (!(Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK))
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x1);
} 

VOID DwSpiHostDisable(IN UINT64 Base)
{
  UINT32 Dwspi_Stat;
  Dwspi_Stat = DwSpiHostRead32(DWSPI_SSIENR(Base));
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK)
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x0);
} 

VOID DwSpiHostEnableSlave(IN UINT64 Base, IN UINT32 Slave_Num)
{
  UINT32 Ser;
  if (DWSPI_MAXCS <= Slave_Num)
    return;
  Ser = DwSpiHostRead32(DWSPI_SER(Base));
  Ser = Ser | (0x1 << Slave_Num);
  DwSpiHostWrite32(DWSPI_SER(Base), Ser);
}

VOID DwSpiHostDisableSlave(IN UINT64 Base, IN UINT32 Slave_Num)
{
  UINT32 Ser;
  if (DWSPI_MAXCS <= Slave_Num)
    return;
  Ser = DwSpiHostRead32(DWSPI_SER(Base));
  Ser = Ser & ~(0x1 << Slave_Num);
  DwSpiHostWrite32(DWSPI_SER(Base), Ser);
} 

VOID DwSpiHostSetMode(IN UINT64 Base, IN UINT32 Mode)
{
  UINT32 Ctrlr0;
  UINT32 Dwspi_Stat;
  Dwspi_Stat = DwSpiHostRead32(DWSPI_SSIENR(Base));
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK)
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x0);
  Ctrlr0 = DwSpiHostRead32(DWSPI_CTRLR0(Base));
  Ctrlr0 &= ~DWSPI_CTRLR0_TMOD_MASK;
  Ctrlr0 |= (DWSPI_CTRLR0_TMOD_EEPROM << DWSPI_CTRLR0_TMOD_SHIFT);
  Ctrlr0 &= ~DWSPI_CTRLR0_DFS_MASK;
  Ctrlr0 |= DWSPI_CTRLR0_DFS_VAL;
  if (Mode & SPI_CPHA)
    Ctrlr0 |= DWSPI_CTRLR0_SCPH_MASK;
  else
    Ctrlr0 &= ~DWSPI_CTRLR0_SCPH_MASK;
  if (Mode & SPI_CPOL)
    Ctrlr0 |= DWSPI_CTRLR0_SCPOL_MASK;
  else
    Ctrlr0 &= ~DWSPI_CTRLR0_SCPOL_MASK;
  DwSpiHostWrite32(DWSPI_CTRLR0(Base), Ctrlr0);
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK)
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x1);
} 

VOID DwSpiHostBaudCfg(IN UINT64 Base, IN UINT32 Ssi_Clk, IN UINT32 Speed_Hz)
{
  UINT32 Div = (Speed_Hz) ? Ssi_Clk / Speed_Hz : 0xFFFE;
  UINT32 Dwspi_Stat;
  Dwspi_Stat = DwSpiHostRead32(DWSPI_SSIENR(Base));
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK)
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x0);
  if (Div % 2)
    Div = Div - Div % 2;
  if (Div == 0)
    Div = 2;
  DwSpiHostWrite32(DWSPI_BAUDR(Base), Div);
  if (Dwspi_Stat & DWSPI_SSIENR_SSI_EN_MASK)
    DwSpiHostWrite32(DWSPI_SSIENR(Base), 0x1);
} 

VOID DwSpiInitialize(IN UINT64 Base)
{  
  DwSpiHostDisable(Base);
  /* Disable all the INTNerrupts just in case */ 
  DwSpiHostWrite32(DWSPI_IMR(Base), DWSPI_IMR_VAL);

  /* Set TX full IRQ threshold */ 
  DwSpiHostWrite32(DWSPI_TXFTLR(Base), DWSPI_TXFTLR_VAL);
  /* Set RX empty IRQ threshold */ 
  DwSpiHostWrite32(DWSPI_RXFTLR(Base), DWSPI_RXFTLR_VAL);
  /* Set default Mode */ 
  
  DwSpiHostSetMode(Base, SPI_MODE_3);
  
  /* Disable chip select for all Slaves */ 
  DwSpiHostWrite32(DWSPI_SER(Base), 0x0);

  /* Allocate context memory */
  Dwspi_Cntxt = (struct DWSPI_CONTEXT *)AllocateRuntimeZeroPool(sizeof(struct DWSPI_CONTEXT));
  ASSERT(Dwspi_Cntxt);

} 


EFI_STATUS DwSpiHostClaimBus(IN struct SPI_SLAVE *Slave) 
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  if (DwSpiHostIsEnabled(Base))
    return EFI_NOT_READY ;
  DwSpiHostEnable(Base);
  return EFI_SUCCESS;
}


VOID DwSpiHostReleaseBus(IN struct SPI_SLAVE *Slave) 
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  DwSpiHostDisable(Base);
} 

VOID Reset_Spi_Ip(UINTN Bus)
{
  UINT32 Scu_Base = (UINT32 ) AHBC_CLKRST_REG_BASE_ADDR;
  UINT32 Srst_Offset = AHBC_SRST_ADDR;
  UINT32 Clken_Offset = AHBC_CLKEN_ADDR;
  UINT32 Reset_Mask = CFG_SPI0_RST_MASK;
  UINT32 Clken_Mask = CFG_CLKEN_SPI_0_MASK;
  UINT32 Val;

  ASSERT(EfiAtRuntime() == FALSE);

  if(Bus==1)
  {
     Reset_Mask = CFG_SPI1_RST_MASK;
     Clken_Mask = CFG_CLKEN_SPI_1_MASK;
  }
  //Assert reset
  Val = DwSpiHostRead32(Scu_Base + Srst_Offset);
  Val |= Reset_Mask;
  DwSpiHostWrite32(Scu_Base + Srst_Offset, Val);
  MicroSecondDelay(10);

  //disable the clock
  Val = DwSpiHostRead32(Scu_Base + Clken_Offset);
  Val &= ~Clken_Mask;
  DwSpiHostWrite32(Scu_Base + Clken_Offset, Val);
  MicroSecondDelay(10);

  //enable the clock
  Val = DwSpiHostRead32(Scu_Base + Clken_Offset);
  Val |= Clken_Mask;
  DwSpiHostWrite32(Scu_Base + Clken_Offset, Val);
  MicroSecondDelay(10);

  Val = DwSpiHostRead32(Scu_Base + Srst_Offset);
  Val &= ~Reset_Mask;
  DwSpiHostWrite32(Scu_Base + Srst_Offset, Val);
  MicroSecondDelay(500);

}

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param  Event        Event whose notification function is being invoked.
  @param  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
SpiVariableClassAddressChangeEvent (
  IN EFI_EVENT                            Event,
  IN VOID                                 *Context
  )
{
  EfiConvertPointer (0x0, (VOID **) &SpiBase);
  EfiConvertPointer (0x0, (VOID **) &Dwspi_Cntxt->Xfer[0].Tx_Ptr);
  EfiConvertPointer (0x0, (VOID **) &Dwspi_Cntxt->Xfer[0].Rx_Ptr);
  EfiConvertPointer (0x0, (VOID **) &Dwspi_Cntxt->Xfer[1].Tx_Ptr);
  EfiConvertPointer (0x0, (VOID **) &Dwspi_Cntxt->Xfer[1].Rx_Ptr);
  EfiConvertPointer (0x0, (VOID **) &Dwspi_Cntxt);
}

struct SPI_SLAVE *DwSpiHostSetupSlave(OUT struct SPI_SLAVE *Spi, 
                                  IN UINTN Bus, IN UINTN Cs,
                                  IN UINTN Max_Hz, IN UINTN Mode) 
{
  EFI_STATUS Status;

  UINT64 Base = DWSPI_BASE;
  UINT32 Sysclk = DWSPI_SYSCLK;

  SpiBase = Base;

  Base += 0x1000 * Bus;

  /* Check Version ID register for sanity */ 
/*  if (DwSpiHostVersion(Base) != DWSPI_VERID)
    return NULL; */

  Reset_Spi_Ip(Bus);

  /* Initialize controller */ 
  DwSpiInitialize(Base);


  Spi->Bus = Bus;
  Spi->Cs = Cs;
  
  /* Set Mode */
  DwSpiHostSetMode(Base, Mode);

  /* Set speed */ 
  DwSpiHostBaudCfg(Base, Sysclk, Max_Hz);
  
  /* Enable chip select */ 
  DwSpiHostEnableSlave(Base, Cs);

  Status = gBS->CreateEventEx (
                      EVT_NOTIFY_SIGNAL,
                      TPL_NOTIFY,
                      SpiVariableClassAddressChangeEvent,
                      NULL,
                      &gEfiEventVirtualAddressChangeGuid,
                      &mSpiVirtualAddressChangeEvent
                      );
  ASSERT_EFI_ERROR (Status);

  return Spi;
}


VOID DwSpiHostCsActivate(IN struct SPI_SLAVE *Slave) 
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  DwSpiHostEnableSlave(Base, Slave->Cs);
} 


VOID DwSpiHostCsDeactivate(IN struct SPI_SLAVE *Slave) 
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  DwSpiHostDisableSlave(Base, Slave->Cs);
} 

EFI_STATUS DwSpiHostRxDual(IN UINT64 Base, IN UINT8 * Rx1, IN UINT32 Rx1_Cnt, IN UINT8 * Rx2, IN UINT32 Rx2_Cnt)
{
  /* FIXME: Not required as of now */ 
  return EFI_SUCCESS;
}

EFI_STATUS DwSpiHostTxDual(IN UINT64 Base, IN UINT8 * Tx1, IN UINT32 Tx1_Cnt, IN UINT8 * Tx2, IN UINT32 Tx2_Cnt)
{
  UINT32 Tx_Pos;
  UINT32 Sr, Old_Ser, Old_Ctrlr0;
  UINT32 Timeout = TIMEOUT;
  /* Wait for previous transfer to complete */ 

  while (DwSpiHostRead32(DWSPI_SR(Base)) & DWSPI_SR_BUSY_MASK) {
    Timeout--;
    if (!Timeout)
      return EFI_DEVICE_ERROR;
    MicroSecondDelay(TIMEOUT_SLEEP);
  }

  /* Save chip select and disable all Slaves */ 
  Old_Ser = DwSpiHostRead32(DWSPI_SER(Base));
  DwSpiHostWrite32(DWSPI_SER(Base), 0x0);
  
  /* Save control registers */
  Old_Ctrlr0 = DwSpiHostRead32(DWSPI_CTRLR0(Base));

  /* Overwrite control registers */ 
  DwSpiHostDisable(Base);
  DwSpiHostWrite32(DWSPI_CTRLR0(Base), 
      (Old_Ctrlr0 & ~DWSPI_CTRLR0_TMOD_MASK) | 
      (DWSPI_CTRLR0_TMOD_TXRX << DWSPI_CTRLR0_TMOD_SHIFT));
  DwSpiHostEnable(Base);
  
  /* Fill the TX FIFO */ 
  Tx_Pos = 0;
  while (Tx_Pos < (Tx1_Cnt + Tx2_Cnt)) {
    Sr = DwSpiHostRead32(DWSPI_SR(Base));
    if (Sr & DWSPI_SR_TFNF_MASK) {
      if (Tx_Pos < Tx1_Cnt) {
        DwSpiHostWrite32(DWSPI_DR(Base), Tx1[Tx_Pos]);
      } else {
        DwSpiHostWrite32(DWSPI_DR(Base),
            Tx2[Tx_Pos - Tx1_Cnt]);
      } 
      Tx_Pos++;
    } else {
      break;
    }
  }
  
  /* Enable Slaves to start transfer */ 
  DwSpiHostWrite32(DWSPI_SER(Base), Old_Ser);
  
  Timeout = TIMEOUT;
  /* Write remaing data to TX FIFO */ 
  while (Tx_Pos < (Tx1_Cnt + Tx2_Cnt)) {
    Sr = DwSpiHostRead32(DWSPI_SR(Base));
    if (Sr & DWSPI_SR_TFNF_MASK) {
      if (Tx_Pos < Tx1_Cnt) {
        DwSpiHostWrite32(DWSPI_DR(Base), Tx1[Tx_Pos]);
      } else {
        DwSpiHostWrite32(DWSPI_DR(Base),
            Tx2[Tx_Pos - Tx1_Cnt]);
      }
      Tx_Pos++;
    } else {
      Timeout--;
      if (!Timeout)
        return EFI_DEVICE_ERROR;
      MicroSecondDelay(TIMEOUT_SLEEP);
    }
  } 

  Timeout = TIMEOUT;
  /* Wait till TX FIFO is not empty */ 
  while (!(DwSpiHostRead32(DWSPI_SR(Base)) & DWSPI_SR_TFE_MASK)) {
    Timeout--;
    if (!Timeout)
      return EFI_DEVICE_ERROR;
    MicroSecondDelay(TIMEOUT_SLEEP);
  }
  
  Timeout = TIMEOUT;
  /* Wait for TX to complete */ 
  while (DwSpiHostRead32(DWSPI_SR(Base)) & DWSPI_SR_BUSY_MASK) {
    Timeout--;
    if (!Timeout)
      return EFI_DEVICE_ERROR;
    MicroSecondDelay(TIMEOUT_SLEEP);
  }
  
  /* Restore control registers */ 
  DwSpiHostDisable(Base);
  DwSpiHostWrite32(DWSPI_CTRLR0(Base), Old_Ctrlr0);
  DwSpiHostEnable(Base);

  return EFI_SUCCESS;
}

EFI_STATUS DwSpiHostEepromRead(IN UINT64 Base, IN UINT8 * Tx, IN UINT32 Tx_Cnt, IN UINT8 * Rx, IN UINT32 Rx_Cnt)
{
  UINT32 Tx_Pos, Rx_Pos;
  UINT32 Sr, Old_Ser, Old_Ctrlr0, Old_Ctrlr1;
  UINT32 Timeout;
  
  if ((DWSPI_TX_FIFO_DEPTH < Tx_Cnt) || 
        ((DWSPI_CTRLR1_MASK + 1) < Rx_Cnt))
    return EFI_NOT_READY ;
  
  /* Wait for previous transfer to complete */ 
  DBG("Wait previous transfer to complete\n");
  Timeout = TIMEOUT;
  while (DwSpiHostRead32(DWSPI_SR(Base)) & DWSPI_SR_BUSY_MASK) {
    Timeout--;
    if (!Timeout)
      return EFI_DEVICE_ERROR;
    MicroSecondDelay(TIMEOUT_SLEEP);
  }
  
  /* Save chip select and disable all Slaves */ 
  Old_Ser = DwSpiHostRead32(DWSPI_SER(Base));
  DwSpiHostWrite32(DWSPI_SER(Base), 0x0);
  
  /* Save control registers */ 
  Old_Ctrlr0 = DwSpiHostRead32(DWSPI_CTRLR0(Base));
  Old_Ctrlr1 = DwSpiHostRead32(DWSPI_CTRLR1(Base));
  
  /* Overwrite control registers */ 
  DwSpiHostDisable(Base);
  DwSpiHostWrite32(DWSPI_CTRLR0(Base), 
      (Old_Ctrlr0 & ~DWSPI_CTRLR0_TMOD_MASK) | 
      (DWSPI_CTRLR0_TMOD_EEPROM << DWSPI_CTRLR0_TMOD_SHIFT));
  DwSpiHostWrite32(DWSPI_CTRLR1(Base), (Rx_Cnt) ? (Rx_Cnt - 1) : 0);
  DwSpiHostEnable(Base);
  
  DBG("Write to TX FIFO\n");
  /* Write to TX FIFO */ 
  Tx_Pos = 0;
  Timeout = TIMEOUT;
  while (Tx_Pos < Tx_Cnt) {
    Sr = DwSpiHostRead32(DWSPI_SR(Base));
    if (Sr & DWSPI_SR_TFNF_MASK) {
      DwSpiHostWrite32(DWSPI_DR(Base), Tx[Tx_Pos]);
      Tx_Pos++;
    } else {
      Timeout--;
      if (!Timeout)
        return EFI_DEVICE_ERROR;
      MicroSecondDelay(TIMEOUT_SLEEP);
    }
  }

  DBG("Read to RX FIFO\n");

  /* Enable Slaves to start transfer */ 
  DwSpiHostWrite32(DWSPI_SER(Base), Old_Ser);

  /* Read from RX FIFO */ 
  Rx_Pos = 0;
  while (Rx_Pos < Rx_Cnt) {
    Sr = DwSpiHostRead32(DWSPI_SR(Base));
    while (Sr & DWSPI_SR_RFNE_MASK) {
      Rx[Rx_Pos] = (UINT8) (DwSpiHostRead32(DWSPI_DR(Base)));
      Rx_Pos++;
      Sr = DwSpiHostRead32(DWSPI_SR(Base));
    } 
  } 

  DBG("Wait for transfer complete\n");
  /* Wait for transfer complete */
  Timeout = TIMEOUT;
  while (DwSpiHostRead32(DWSPI_SR(Base)) & DWSPI_SR_BUSY_MASK) {
    Timeout--;
    if (!Timeout)
      return EFI_DEVICE_ERROR;
    MicroSecondDelay(TIMEOUT_SLEEP);
  }
  DBG("DwSpiHostEepromRead exit\n");
  /* Restore control registers */ 
  DwSpiHostDisable(Base);
  DwSpiHostWrite32(DWSPI_CTRLR0(Base), Old_Ctrlr0);
  DwSpiHostWrite32(DWSPI_CTRLR1(Base), Old_Ctrlr1);
  DwSpiHostEnable(Base);

  return EFI_SUCCESS;
}

EFI_STATUS DwSpiHostXfer(IN struct SPI_SLAVE *Slave, IN UINTN Bitlen, IN const VOID *Dout,
       IN VOID *Din, IN UINT32 Flags) 
{
  EFI_STATUS Rc = 0;
  EFI_PHYSICAL_ADDRESS Base = SpiBase;

  DBG("Bus:%d Xfer_Count:%d Flag:%d\n", Slave->Bus, Dwspi_Cntxt->Xfer_Count, Flags);
  Base += 0x1000 * Slave->Bus;
 
  /* Clear saved transfers */ 
  if (Flags & SPI_XFER_BEGIN) {
    Dwspi_Cntxt->Xfer_Count = 0;
  }

  /* Save transfer requests */ 
  if (Dwspi_Cntxt->Xfer_Count < 2 && (Dout != NULL || Din != NULL)) {
    Dwspi_Cntxt->Xfer[Dwspi_Cntxt->Xfer_Count].Tx_Ptr = (UINT8 *) Dout;
    Dwspi_Cntxt->Xfer[Dwspi_Cntxt->Xfer_Count].Rx_Ptr = (UINT8 *) Din;
    Dwspi_Cntxt->Xfer[Dwspi_Cntxt->Xfer_Count].Count = Bitlen / 8;
    Dwspi_Cntxt->Xfer_Count++;
  }
  DBG("Xfer_Count:%d\n", Dwspi_Cntxt->Xfer_Count);
  /* Execute saved transfer requests */ 
  if (Flags & SPI_XFER_END) {
    /* Disable INTNerrupts to ensure atomicity */ 
    ArmDisableInterrupts();
    /* Actual transfer */ 
    if (Dwspi_Cntxt->Xfer_Count == 1) {
      if (Dwspi_Cntxt->Xfer[0].Tx_Ptr) {
        Rc =  DwSpiHostTxDual(Base,
              Dwspi_Cntxt->Xfer[0].Tx_Ptr,
              Dwspi_Cntxt->Xfer[0].Count,
              NULL, 0);
        Dwspi_Cntxt->Xfer_Count -= 1;
      } else if (Dwspi_Cntxt->Xfer[0].Rx_Ptr) {
        Rc =  DwSpiHostRxDual(Base,
              Dwspi_Cntxt->Xfer[0].Rx_Ptr,
              Dwspi_Cntxt->Xfer[0].Count,
              NULL, 0);
        Dwspi_Cntxt->Xfer_Count -= 1;
      }
    } else if (Dwspi_Cntxt->Xfer_Count == 2) {
      if (Dwspi_Cntxt->Xfer[0].Tx_Ptr &&
          Dwspi_Cntxt->Xfer[1].Tx_Ptr) {
        DBG("Tx Dual\n");
        Rc = DwSpiHostTxDual(Base,
               Dwspi_Cntxt->Xfer[0].Tx_Ptr,
               Dwspi_Cntxt->Xfer[0].Count,
               Dwspi_Cntxt->Xfer[1].Tx_Ptr,
               Dwspi_Cntxt->Xfer[1].Count);
        Dwspi_Cntxt->Xfer_Count -= 2;
      } else if (Dwspi_Cntxt->Xfer[0].Tx_Ptr &&
          Dwspi_Cntxt->Xfer[0].Count <= DWSPI_TX_FIFO_DEPTH &&
          Dwspi_Cntxt->Xfer[1].Rx_Ptr &&
          Dwspi_Cntxt->Xfer[1].Count <= (DWSPI_CTRLR1_MASK + 1)) {
        DBG("DwSpiHostEepromRead\n");
        Rc = DwSpiHostEepromRead(Base,
            Dwspi_Cntxt->Xfer[0].Tx_Ptr,
            Dwspi_Cntxt->Xfer[0].Count,
            Dwspi_Cntxt->Xfer[1].Rx_Ptr,
            Dwspi_Cntxt->Xfer[1].Count);
        Dwspi_Cntxt->Xfer_Count -= 2;
      }
    }
    /* Enable INTNerrupts */ 
    ArmEnableInterrupts();
  }
  return Rc;
}

EFI_STATUS Spi_Claim_Bus(struct SPI_SLAVE *Slave)
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  if (DwSpiHostIsEnabled(Base)) {
    return EFI_NOT_READY ;
  }
  DwSpiHostEnable(Base);
  return EFI_SUCCESS;
}

VOID Spi_Release_Bus(struct SPI_SLAVE *Slave)
{
  EFI_PHYSICAL_ADDRESS Base = SpiBase;
  Base += 0x1000 * Slave->Bus;
  DwSpiHostDisable(Base);
}

struct SPI_SLAVE *Spi_Setup_Slave(OUT struct SPI_SLAVE *Spi_Slave, 
                                  IN UINTN Bus, IN UINTN Cs,
                                  IN UINTN Max_Hz, IN UINTN Mode)
{
  return DwSpiHostSetupSlave(Spi_Slave, Bus, Cs, Max_Hz, Mode);
}

EFI_STATUS Spi_Xfer(struct SPI_SLAVE *Slave, UINTN BitLen, const VOID *Dout,
       VOID *Din, UINT32 Flags)
{
  return DwSpiHostXfer(Slave, BitLen, Dout, Din, Flags);
}
