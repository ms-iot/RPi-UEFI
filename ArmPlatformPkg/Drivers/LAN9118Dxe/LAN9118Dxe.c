/** @file
*
*  Copyright (c) 2012-2013, ARM Limited. All rights reserved.
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

#include <Uefi.h>
#include <Uefi/UefiSpec.h>
#include <Base.h>

// Protocols used by this driver
#include <Protocol/SimpleNetwork.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/PxeBaseCode.h>
#include <Protocol/DevicePath.h>

// Libraries used by this driver
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/NetLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PrintLib.h>

#include "LAN9118DxeHw.h"

#define LAN9118_TPL   TPL_CALLBACK

// Most common CRC32 Polynomial for little endian machines
#define CRC_POLYNOMIAL               0xEDB88320

/* ------------------ Debug Functions ------------------ */

// Flags for printing register values
#define PRINT_REGISTERS_MAC               BIT0
#define PRINT_REGISTERS_PHY               BIT1
#define PRINT_REGISTERS_ALL               (BIT0 | BIT1)
#define PRINT_REGISTERS_SEL_MAC           BIT12
#define PRINT_REGISTERS_SEL_PHY           BIT13


/* ------------------ MAC CSR Access ------------------- */


// Flags for software reset
#define SOFT_RESET_CHECK_MAC_ADDR_LOAD                  BIT0
#define SOFT_RESET_CLEAR_INT                            BIT1
#define SOFT_RESET_SELF_TEST                            BIT2

// Flags for PHY reset
#define PHY_RESET_PMT                                   BIT0
#define PHY_RESET_BCR                                   BIT1
#define PHY_RESET_CHECK_LINK                            BIT2
#define PHY_SOFT_RESET_CLEAR_INT                        BIT3

// Flags for Hardware configuration
#define HW_CONF_USE_LEDS                                BIT0

// Stop transmitter flags
#define STOP_TX_MAC                       BIT0
#define STOP_TX_CFG                       BIT1
#define STOP_TX_CLEAR                     BIT2

// Stop receiver flags
#define STOP_RX_CLEAR                     BIT0

// Start transmitter flags
#define START_TX_MAC                      BIT0
#define START_TX_CFG                      BIT1
#define START_TX_CLEAR                    BIT2

// Stop receiver flags
#define START_RX_CLEAR                     BIT0

// Flags for FIFO allocation
#define ALLOC_USE_DEFAULT                 0x00000001
#define ALLOC_USE_FIFOS                   0x00000002
#define ALLOC_USE_DMA                     0x00000004

// FIFO min and max sizes
#define TX_FIFO_MIN_SIZE            0x00000600
#define TX_FIFO_MAX_SIZE            0x00003600
//#define RX_FIFO_MIN_SIZE
//#define RX_FIFO_MAX_SIZE
#define LAN9118_STALL     2

#define LAN9118_DEFAULT_MAC_ADDRL     0x00F70200
#define LAN9118_DEFAULT_MAC_ADDRH     0x00009040

/*---------------------------------------------------------------------------------------------------------------------

  LAN9118 Information Structure

---------------------------------------------------------------------------------------------------------------------*/

#define LAN9118_TX_CACHE_DEPTH  16

// TxCache management structure
typedef struct {
  VOID        *buffadr;
  UINTN        refcount;
} LAN9118_TX_CACHE;

typedef struct {
  // Driver signature
  UINT32            Signature;
  EFI_HANDLE        ControllerHandle;

  // EFI SNP protocol instances
  EFI_SIMPLE_NETWORK_PROTOCOL Snp;
  EFI_SIMPLE_NETWORK_MODE SnpMode;

  // EFI Snp statistics instance
  EFI_NETWORK_STATISTICS Stats;

  // Transmit Completion Cache
  VOID    *TxCache[LAN9118_TX_CACHE_DEPTH];
} LAN9118_DRIVER;

#define LAN9118_SIGNATURE                       SIGNATURE_32('l', 'a', 'n', '9')
#define INSTANCE_FROM_SNP_THIS(a)               CR(a, LAN9118_DRIVER, Snp, LAN9118_SIGNATURE)


typedef struct {
  MAC_ADDR_DEVICE_PATH      Lan9118;
  EFI_DEVICE_PATH_PROTOCOL  End;
} LAN9118_DEVICE_PATH;

LAN9118_DEVICE_PATH Lan9118PathTemplate =  {
  {
    {
      MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP,
      { (UINT8) (sizeof(MAC_ADDR_DEVICE_PATH)), (UINT8) ((sizeof(MAC_ADDR_DEVICE_PATH)) >> 8) }
    },
    { 0 },
    0
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    sizeof(EFI_DEVICE_PATH_PROTOCOL),
    0
  }
};

/**
  This internal function reverses bits for 32bit data.

  @param  Value                 The data to be reversed.

  @return                       Data reversed.

**/
UINT32
ReverseBits (
  UINT32  Value
  )
{
  UINTN   Index;
  UINT32  NewValue;

  NewValue = 0;
  for (Index = 0; Index < 32; Index++) {
    if ((Value & (1 << Index)) != 0) {
      NewValue = NewValue | (1 << (31 - Index));
    }
  }

  return NewValue;
}

/*
**  Create Ethernet CRC
**
**  INFO USED:
**    1: http://en.wikipedia.org/wiki/Cyclic_redundancy_check
**
**    2: http://www.erg.abdn.ac.uk/~gorry/eg3567/dl-pages/crc.html
**
**    3: http://en.wikipedia.org/wiki/Computation_of_CRC
*/
UINT32
GenEtherCrc32 (
  IN    EFI_MAC_ADDRESS *Mac,
  IN    UINT32 AddrLen
  )
{
  INT32 Iter;
  UINT32 Remainder;
  UINT8 *Ptr;

  Iter = 0;
  Remainder = 0xFFFFFFFF;    // 0xFFFFFFFF is standard seed for Ethernet

  // Convert Mac Address to array of bytes
  Ptr = (UINT8*)Mac;

  // Generate the Crc bit-by-bit (LSB first)
  while (AddrLen--) {
    Remainder ^= *Ptr++;
    for (Iter = 0;Iter < 8;Iter++) {
      // Check if exponent is set
      if (Remainder & 1) {
        Remainder = (Remainder >> 1) ^ CRC_POLYNOMIAL;
      } else {
        Remainder = (Remainder >> 1) ^ 0;
      }
    }
  }

  // Reverse the bits before returning (to Big Endian)
  return ReverseBits (Remainder);
}

#ifndef MDEPKG_NDEBUG
STATIC CONST CHAR16 *Mac2Str (EFI_MAC_ADDRESS *Mac)
{
  static CHAR16 MacStr[18];
  
  if (Mac == NULL) {
    return L"<null>";
  }

  UnicodeSPrintAsciiFormat (MacStr, sizeof(MacStr), 
      "%02x:%02x:%02x:%02x:%02x:%02x",
      Mac->Addr[0], Mac->Addr[1], Mac->Addr[2],
      Mac->Addr[3], Mac->Addr[4], Mac->Addr[5]);
  return MacStr;
}
#endif

// Function to read from MAC indirect registers
UINT32
IndirectMACRead32 (
  UINT32 Index
  )
{
  UINT32 MacCSR;

  // Check index is in the range
  ASSERT(Index <= 12);

  // Wait until CSR busy bit is cleared
  while ((MmioRead32 (LAN9118_MAC_CSR_CMD) & MAC_CSR_BUSY) == MAC_CSR_BUSY);

  // Set CSR busy bit to ensure read will occur
  // Set the R/W bit to indicate we are reading
  // Set the index of CSR Address to access desired register
  MacCSR = MAC_CSR_BUSY | MAC_CSR_READ | MAC_CSR_ADDR(Index);

  // Write to the register
  MmioWrite32 (LAN9118_MAC_CSR_CMD, MacCSR);

  // Wait until CSR busy bit is cleared
  while ((MmioRead32 (LAN9118_MAC_CSR_CMD) & MAC_CSR_BUSY) == MAC_CSR_BUSY);

  // Now read from data register to get read value
  return MmioRead32 (LAN9118_MAC_CSR_DATA);
}

// Function to write to MAC indirect registers
UINT32
IndirectMACWrite32 (
  UINT32 Index,
  UINT32 Value
  )
{
  UINT32 ValueWritten;
  UINT32 MacCSR;

  // Check index is in the range
  ASSERT(Index <= 12);

  // Wait until CSR busy bit is cleared
  while ((MmioRead32 (LAN9118_MAC_CSR_CMD) & MAC_CSR_BUSY) == MAC_CSR_BUSY);

  // Set CSR busy bit to ensure read will occur
  // Set the R/W bit to indicate we are writing
  // Set the index of CSR Address to access desired register
  MacCSR = MAC_CSR_BUSY | MAC_CSR_WRITE | MAC_CSR_ADDR(Index);

  // Now write the value to the register before issuing the write command
  ValueWritten = MmioWrite32 (LAN9118_MAC_CSR_DATA, Value);

  // Write the config to the register
  MmioWrite32 (LAN9118_MAC_CSR_CMD, MacCSR);

  // Wait until CSR busy bit is cleared
  while ((MmioRead32 (LAN9118_MAC_CSR_CMD) & MAC_CSR_BUSY) == MAC_CSR_BUSY);

  return ValueWritten;
}

// Function to read from MII register (PHY Access)
UINT32
IndirectPHYRead32 (
  UINT32 Index
  )
{
  UINT32 ValueRead;
  UINT32 MiiAcc;

  // Check it is a valid index
  ASSERT(Index < 31);

  // Wait for busy bit to clear
  while ((IndirectMACRead32 (INDIRECT_MAC_INDEX_MII_ACC) & MII_ACC_MII_BUSY) == MII_ACC_MII_BUSY);

  // Clear the R/W bit to indicate we are reading
  // Set the index of the MII register
  // Set the PHY Address
  // Set the MII busy bit to allow read
  MiiAcc = MII_ACC_MII_READ | MII_ACC_MII_REG_INDEX(Index) | MII_ACC_PHY_VALUE | MII_ACC_MII_BUSY;

  // Now write this config to register
  IndirectMACWrite32 (INDIRECT_MAC_INDEX_MII_ACC, MiiAcc & 0xFFFF);

  // Wait for busy bit to clear
  while ((IndirectMACRead32 (INDIRECT_MAC_INDEX_MII_ACC) & MII_ACC_MII_BUSY) == MII_ACC_MII_BUSY);

  // Now read the value of the register
  ValueRead = (IndirectMACRead32 (INDIRECT_MAC_INDEX_MII_DATA) & 0xFFFF); // only lower 16 bits are valid for any PHY register

  return ValueRead;
}


// Function to write to the MII register (PHY Access)
UINT32
IndirectPHYWrite32 (
  UINT32 Index,
  UINT32 Value
  )
{
  UINT32 MiiAcc;
  UINT32 ValueWritten;

  // Check it is a valid index
  ASSERT(Index < 31);

  // Wait for busy bit to clear
  while ((IndirectMACRead32 (INDIRECT_MAC_INDEX_MII_ACC) & MII_ACC_MII_BUSY) == MII_ACC_MII_BUSY);

  // Clear the R/W bit to indicate we are reading
  // Set the index of the MII register
  // Set the PHY Address
  // Set the MII busy bit to allow read
  MiiAcc = MII_ACC_MII_WRITE | MII_ACC_MII_REG_INDEX(Index) | MII_ACC_PHY_VALUE | MII_ACC_MII_BUSY;

  // Write the desired value to the register first
  ValueWritten = IndirectMACWrite32 (INDIRECT_MAC_INDEX_MII_DATA, (Value & 0xFFFF));

  // Now write the config to register
  IndirectMACWrite32 (INDIRECT_MAC_INDEX_MII_ACC, MiiAcc & 0xFFFF);

  // Wait for operation to terminate
  while ((IndirectMACRead32 (INDIRECT_MAC_INDEX_MII_ACC) & MII_ACC_MII_BUSY) == MII_ACC_MII_BUSY);

  return ValueWritten;
}


// DEBUG: Print all register values
UINT32
PrintRegisters (
  IN  UINT32 Flags,
  IN  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 Count;
  UINT32 RegValue;

  // Select MAC register if defined (5 LSBs select register)
  if (Flags & PRINT_REGISTERS_SEL_MAC) {
    RegValue = IndirectMACRead32 (Flags & 0x1FF);
    DEBUG((EFI_D_ERROR, "MAC Register %02x:\thex: 0x%08x\n",Flags & 0x1FF, RegValue));
    return 0;
  }

  // Select PHY register if defined (5 LSBs select register)
  if (Flags & PRINT_REGISTERS_SEL_PHY) {
    RegValue = IndirectPHYRead32 (Flags & 0x1FF);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n",Flags & 0x1FF, RegValue));
    return 0;
  }

  // Loop through all MAC registers
  if (Flags & PRINT_REGISTERS_MAC) {
    for (Count = 1;Count <= 0xC;Count++) {
      RegValue = IndirectMACRead32 (Count);
      DEBUG((EFI_D_ERROR, "MAC Register %02x:\thex: 0x%08x\n", Count, RegValue));
    }
  }

  // Print PHY registers
  if (Flags & PRINT_REGISTERS_PHY) {
    for (Count = 0;Count <= 6;Count ++) {
      RegValue = IndirectPHYRead32 (Count);
      DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));
    }

    Count = 17;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));

    Count = 18;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));

    Count = 27;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));

    Count = 29;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));

    Count = 30;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));

    Count = 31;
    RegValue = IndirectPHYRead32 (Count);
    DEBUG((EFI_D_ERROR, "PHY Register %d:\thex: 0x%08x\n", Count, RegValue));
  }

  return 0;
}


/* ---------------- EEPROM Operations ------------------ */


// Function to read from EEPROM memory
UINT32
IndirectEEPROMRead32 (
  UINT32 Index
)
{
  // Eeprom command
  UINT32 EepromCmd = 0;//= MmioRead32 (LAN9118_E2P_CMD);

  // Set the busy bit to ensure read will occur
  EepromCmd |= ((UINT32)1 << 31);

  // Set the EEPROM command to read(0b000)
  EepromCmd &= ~(0x70000000); // Clear the command first
  EepromCmd |= (0 << 28);     // Not necessary, but here for clarity

  // Set the index to access desired EEPROM memory location
  EepromCmd |= (Index & 0xF);

  // Write to Eeprom command register
  MmioWrite32 (LAN9118_E2P_CMD, EepromCmd);
  gBS->Stall (LAN9118_STALL);

  // Wait until operation has completed
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  // Check that operation didn't time out
  if (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_TIMEOUT) {
    DEBUG((EFI_D_ERROR, "EEPROM Operation Timed out: Read command on index %x\n",Index));
    return 0;
  }

  // Wait until operation has completed
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  // Finally read the value
  return MmioRead32 (LAN9118_E2P_DATA);
}

// Function to write to EEPROM memory
UINT32
IndirectEEPROMWrite32 (
  UINT32 Index,
  UINT32 Value
  )
{
  UINT32 ValueWritten;
  UINT32 EepromCmd;

  ValueWritten = 0;

  // Read the EEPROM Command register
  EepromCmd = MmioRead32 (LAN9118_E2P_CMD);

  // Set the busy bit to ensure read will occur
  EepromCmd |= ((UINT32)1 << 31);

  // Set the EEPROM command to write(0b011)
  EepromCmd &= ~(0x70000000); // Clear the command first
  EepromCmd |= (3 << 28);     // Write 011

  // Set the index to access desired EEPROM memory location
  EepromCmd |= (Index & 0xF);

  // Write the value to the data register first
  ValueWritten = MmioWrite32 (LAN9118_E2P_DATA, Value);

  // Write to Eeprom command register
  MmioWrite32 (LAN9118_E2P_CMD, EepromCmd);
  gBS->Stall (LAN9118_STALL);

  // Wait until operation has completed
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  // Check that operation didn't time out
  if (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_TIMEOUT) {
    DEBUG((EFI_D_ERROR, "EEPROM Operation Timed out: Write command at memloc 0x%x, with value 0x%x\n",Index, Value));
    return 0;
  }

  // Wait until operation has completed
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  return ValueWritten;
}

/* ---------------- General Operations ----------------- */


// Stop the transmitter
EFI_STATUS
StopTx (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 MacCsr;
  UINT32 TxCfg;

  MacCsr = 0;
  TxCfg = 0;

  // Check if we want to clear tx
  if (Flags & STOP_TX_CLEAR) {
    TxCfg = MmioRead32 (LAN9118_TX_CFG);
    TxCfg |= TXCFG_TXS_DUMP | TXCFG_TXD_DUMP;
    MmioWrite32 (LAN9118_TX_CFG, TxCfg);
    gBS->Stall (LAN9118_STALL);
  }

  // Check if already stopped
  if (Flags & STOP_TX_MAC) {
    MacCsr = IndirectMACRead32 (INDIRECT_MAC_INDEX_CR);

    if (MacCsr & MACCR_TX_EN) {
      MacCsr &= ~MACCR_TX_EN;
      IndirectMACWrite32 (INDIRECT_MAC_INDEX_CR, MacCsr);
    }
  }

  if (Flags & STOP_TX_CFG) {
    TxCfg = MmioRead32 (LAN9118_TX_CFG);

    if (TxCfg & TXCFG_TX_ON) {
      TxCfg |= TXCFG_STOP_TX;
      MmioWrite32 (LAN9118_TX_CFG, TxCfg);
      gBS->Stall (LAN9118_STALL);

      // Wait for Tx to finish transmitting
      while (MmioRead32 (LAN9118_TX_CFG) & TXCFG_STOP_TX);
    }
  }

  return EFI_SUCCESS;
}

// Stop the receiver
EFI_STATUS
StopRx (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 MacCsr;
  UINT32 RxCfg;

  RxCfg = 0;

  // Check if already stopped
  MacCsr = IndirectMACRead32 (INDIRECT_MAC_INDEX_CR);

  if (MacCsr & MACCR_RX_EN) {
    MacCsr &= ~ MACCR_RX_EN;
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_CR, MacCsr);
  }

  // Check if we want to clear receiver FIFOs
  if (Flags & STOP_RX_CLEAR) {
    RxCfg = MmioRead32 (LAN9118_RX_CFG);
    RxCfg |= RXCFG_RX_DUMP;
    MmioWrite32 (LAN9118_RX_CFG, RxCfg);
    gBS->Stall (LAN9118_STALL);

    while (MmioRead32 (LAN9118_RX_CFG) & RXCFG_RX_DUMP);
  }

  return EFI_SUCCESS;
}

// Perform software reset on the LAN9118
// Return 0 on success, -1 on error
EFI_STATUS
SoftReset (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 HwConf;
  UINT32 ResetTime;

  // Stop Rx and Tx
  StopTx (STOP_TX_MAC | STOP_TX_CFG | STOP_TX_CLEAR, Snp);
  StopRx (STOP_RX_CLEAR, Snp); // Clear receiver FIFO

  // Issue the reset
  HwConf = MmioRead32 (LAN9118_HW_CFG);
  HwConf |= HWCFG_SRST | HWCFG_MBO;

  // Check that EEPROM isn't active
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  // Write the configuration
  MmioWrite32 (LAN9118_HW_CFG, HwConf);
  gBS->Stall (LAN9118_STALL);

  // Wait for reset to complete
  ResetTime = 1000;
  while (MmioRead32 (LAN9118_HW_CFG) & HWCFG_SRST) {

    gBS->Stall (LAN9118_STALL);

    // If time taken exceeds 1000us, then there was an error condition
    if (--ResetTime == 0) {
      Snp->Mode->State = EfiSimpleNetworkStopped;
      return EFI_TIMEOUT;
    }
  }

  // Check that MAC Address loaded successfully (if required)
  if (Flags & SOFT_RESET_CHECK_MAC_ADDR_LOAD) {
    if ((MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_MAC_ADDRESS_LOADED) == 0) {
      DEBUG((EFI_D_ERROR, "Warning: There was an error detecting EEPROM or loading the MAC Address:\n"
                          "         Using hard-coded MAC Address.\n"));

      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRL, LAN9118_DEFAULT_MAC_ADDRL);
      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRH, LAN9118_DEFAULT_MAC_ADDRH);
    }
  }

  // Check that EEPROM isn't active
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  // Clear and acknowledge all interrupts
  if (Flags & SOFT_RESET_CLEAR_INT) {
    MmioWrite32 (LAN9118_INT_EN, 0);
    MmioWrite32 (LAN9118_IRQ_CFG, 0);
    MmioWrite32 (LAN9118_INT_STS, 0xFFFFFFFF);
  }

  // Do self tests here?
  if (Flags & SOFT_RESET_SELF_TEST) {

  }

  return EFI_SUCCESS;
}


// Check the Link Status and take appropriate action
BOOLEAN
CheckLinkStatus (
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 PhyBStatus;
  
  // Get the PHY Status
  PhyBStatus = IndirectPHYRead32 (PHY_INDEX_BASIC_STATUS);

  return (PhyBStatus & PHYSTS_LINK_STS) != 0;
}

// Perform PHY software reset
INT32
PhySoftReset (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 PmtCtrl = 0;
  UINT32 LinkTo = 0;

  // PMT PHY reset takes precedence over BCR
  if (Flags & PHY_RESET_PMT) {
    PmtCtrl = MmioRead32 (LAN9118_PMT_CTRL);
    PmtCtrl |= MPTCTRL_PHY_RST;
    MmioWrite32 (LAN9118_PMT_CTRL,PmtCtrl);

    // Wait for completion
    while (MmioRead32 (LAN9118_PMT_CTRL) & MPTCTRL_PHY_RST) {
      gBS->Stall (LAN9118_STALL);
    }
  // PHY Basic Control Register reset
  } else if (Flags & PHY_RESET_PMT) {
    IndirectPHYWrite32 (PHY_INDEX_BASIC_CTRL, PHYCR_RESET);

    // Wait for completion
    while (IndirectPHYRead32 (PHY_INDEX_BASIC_CTRL) & PHYCR_RESET) {
      gBS->Stall (LAN9118_STALL);
    }
  }

  // Check the link status
  if (Flags & PHY_RESET_CHECK_LINK) {
    LinkTo = 100000; // 2 second (could be 50% more)
    while (!CheckLinkStatus(Snp) && (LinkTo > 0)) {
      gBS->Stall (LAN9118_STALL);
      LinkTo--;
    }

    // Timed out
    if (LinkTo <= 0) {
      return -1;
    }
  }

  // Clear and acknowledge all interrupts
  if (Flags & PHY_SOFT_RESET_CLEAR_INT) {
    MmioWrite32 (LAN9118_INT_EN, 0);
    MmioWrite32 (LAN9118_IRQ_CFG, 0);
    MmioWrite32 (LAN9118_INT_STS, 0xFFFFFFFF);
  }

  return 0;
}


// Configure hardware for LAN9118
EFI_STATUS
ConfigureHardware (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 GpioConf;

  // Check if we want to use LEDs on GPIO
  if (Flags & HW_CONF_USE_LEDS) {
    GpioConf = MmioRead32 (LAN9118_GPIO_CFG);

    // Enable GPIO as LEDs and Config as Push-Pull driver
    GpioConf |= GPIO_GPIO0_PUSH_PULL | GPIO_GPIO1_PUSH_PULL | GPIO_GPIO2_PUSH_PULL |
                GPIO_LED1_ENABLE | GPIO_LED2_ENABLE | GPIO_LED3_ENABLE;

    // Write the configuration
    MmioWrite32 (LAN9118_GPIO_CFG, GpioConf);
    gBS->Stall (LAN9118_STALL);
  }

  return EFI_SUCCESS;
}

// Configure flow control
EFI_STATUS
ConfigureFlow (
  UINT32 Flags,
  UINT32 HighTrig,
  UINT32 LowTrig,
  UINT32 BPDuration,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  return EFI_SUCCESS;
}

// Do auto-negotiation
EFI_STATUS
AutoNegotiate (
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINTN  Retries;
  UINT32 PhyControl;
  UINT32 PhyStatus;
  UINT32 PhyAdvert;

  // First check that auto-negotiation is supported
  PhyStatus = IndirectPHYRead32 (PHY_INDEX_BASIC_STATUS);
  if ((PhyStatus & PHYSTS_AUTO_CAP) == 0) {
    return EFI_SUCCESS;
  }

  // Translate capabilities to advertise
  PhyAdvert = PHYANA_CSMA;

  if ((PhyStatus & PHYSTS_10BASET_HDPLX) != 0) {
    PhyAdvert |= PHYANA_10BASET;
  }
  if ((PhyStatus & PHYSTS_10BASET_FDPLX) != 0) {
    PhyAdvert |= PHYANA_10BASETFD;
  }
  if ((PhyStatus & PHYSTS_100BASETX_HDPLX) != 0) {
    PhyAdvert |= PHYANA_100BASETX;
  }
  if ((PhyStatus & PHYSTS_100BASETX_FDPLX) != 0) {
    PhyAdvert |= PHYANA_100BASETXFD;
  }
  if ((PhyStatus & PHYSTS_100BASE_T4) != 0) {
    PhyAdvert |= PHYANA_100BASET4;
  }

  // Write the features
  IndirectPHYWrite32 (PHY_INDEX_AUTO_NEG_ADVERT, PhyAdvert);

  // Restart Auto-Negotiation
  PhyControl = IndirectPHYRead32 (PHY_INDEX_BASIC_CTRL);
  PhyControl &= ~(PHYCR_SPEED_SEL | PHYCR_DUPLEX_MODE);
  PhyControl |= PHYCR_AUTO_EN | PHYCR_RST_AUTO;
  IndirectPHYWrite32 (PHY_INDEX_BASIC_CTRL, PhyControl);

  // Wait up to 2 seconds for the process to complete
  Retries = 2000000;
  while ((IndirectPHYRead32 (PHY_INDEX_BASIC_STATUS) & PHYSTS_AUTO_COMP) == 0) {
    if (--Retries == 0) {
      DEBUG((EFI_D_ERROR, "LAN9118: PHY auto-negotiation timed-out\n"));
      return EFI_TIMEOUT;
    }
    gBS->Stall (100);
  }

  return EFI_SUCCESS;
}

// Start the transmitter
EFI_STATUS
StartTx (
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  LAN9118_DRIVER *LanDriver;
  UINT32 MacCsr;
  UINT32 TxCfg;

  // Clear the transmitter
  TxCfg = MmioRead32 (LAN9118_TX_CFG);
  TxCfg |= TXCFG_TXS_DUMP | TXCFG_TXD_DUMP;
  MmioWrite32 (LAN9118_TX_CFG, TxCfg);
  gBS->Stall (LAN9118_STALL);

  // Clear the TxCache
  LanDriver = INSTANCE_FROM_SNP_THIS(Snp);
  ZeroMem (LanDriver->TxCache, sizeof(LanDriver->TxCache));

  // Start the MAC
  MacCsr = IndirectMACRead32 (INDIRECT_MAC_INDEX_CR);
  gBS->Stall (LAN9118_STALL);
  if ((MacCsr & MACCR_TX_EN) == 0) {
    MacCsr |= MACCR_TX_EN;
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_CR, MacCsr);
    gBS->Stall (LAN9118_STALL);
  }

  // Enable the transmitter
  TxCfg = MmioRead32 (LAN9118_TX_CFG);
  gBS->Stall (LAN9118_STALL);
  if ((TxCfg & TXCFG_TX_ON) == 0) {
    TxCfg |= TXCFG_TX_ON;
    MmioWrite32 (LAN9118_TX_CFG, TxCfg);
    gBS->Stall (LAN9118_STALL);
  }

  // Set the tx data trigger level

  return EFI_SUCCESS;
}


// Start the receiver
EFI_STATUS
StartRx (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 MacCsr;
  UINT32 RxCfg;

  RxCfg = 0;

  // Check if already started
  MacCsr = IndirectMACRead32 (INDIRECT_MAC_INDEX_CR);

  if ((MacCsr & MACCR_RX_EN) == 0) {
    // Check if we want to clear receiver FIFOs before starting
    if (Flags & START_RX_CLEAR) {
      RxCfg = MmioRead32 (LAN9118_RX_CFG);
      RxCfg |= RXCFG_RX_DUMP;
      MmioWrite32 (LAN9118_RX_CFG, RxCfg);
      gBS->Stall (LAN9118_STALL);

      while (MmioRead32 (LAN9118_RX_CFG) & RXCFG_RX_DUMP);
    }

    MacCsr |= MACCR_RX_EN;
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_CR, MacCsr);
    gBS->Stall (LAN9118_STALL);
  }

  return EFI_SUCCESS;
}

// Check Tx Data available space
UINT32
TxDataFreeSpace (
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 TxInf;
  UINT32 FreeSpace;

  // Get the amount of free space from information register
  TxInf = MmioRead32 (LAN9118_TX_FIFO_INF);
  FreeSpace = (TxInf & TXFIFOINF_TDFREE_MASK);

  return FreeSpace; // Value in bytes
}

// Check Tx Status used space
UINT32
TxStatusUsedSpace (
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 TxInf;
  UINT32 UsedSpace;

  // Get the amount of used space from information register
  TxInf = MmioRead32 (LAN9118_TX_FIFO_INF);
  UsedSpace = (TxInf & TXFIFOINF_TXSUSED_MASK) >> 16;

  return UsedSpace;
}

// Check Rx Data used space
UINT32
RxDataUsedSpace (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 RxInf;
  UINT32 UsedSpace;

  // Get the amount of used space from information register
  RxInf = MmioRead32 (LAN9118_RX_FIFO_INF);
  UsedSpace = (RxInf & RXFIFOINF_RXDUSED_MASK);

  return UsedSpace; // Value in bytes (rounded up to nearest DWORD)
}

// Check Rx Status used space
UINT32
RxStatusUsedSpace (
  UINT32 Flags,
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 RxInf;
  UINT32 UsedSpace;

  // Get the amount of used space from information register
  RxInf = MmioRead32 (LAN9118_RX_FIFO_INF);
  UsedSpace = (RxInf & RXFIFOINF_RXSUSED_MASK) >> 16;

  return UsedSpace << 2; // Value in bytes
}


// Change the allocation of FIFOs
EFI_STATUS
ChangeFifoAllocation (
  IN      UINT32 Flags,
  IN  OUT UINTN  *TxDataSize    OPTIONAL,
  IN  OUT UINTN  *RxDataSize    OPTIONAL,
  IN  OUT UINT32 *TxStatusSize  OPTIONAL,
  IN  OUT UINT32 *RxStatusSize  OPTIONAL,
  IN  OUT EFI_SIMPLE_NETWORK_PROTOCOL *Snp
  )
{
  UINT32 HwConf;
  UINT32 TxFifoOption;

  // Check that desired sizes don't exceed limits
  if (*TxDataSize > TX_FIFO_MAX_SIZE)
    return EFI_INVALID_PARAMETER;

#if defined(RX_FIFO_MIN_SIZE) && defined(RX_FIFO_MAX_SIZE)
  if (*RxDataSize > RX_FIFO_MAX_SIZE) {
    return EFI_INVALID_PARAMETER;
  }
#endif

  if (Flags & ALLOC_USE_DEFAULT) {
    return EFI_SUCCESS;
  }

  // If we use the FIFOs (always use this first)
  if (Flags & ALLOC_USE_FIFOS) {
    // Read the current value of allocation
    HwConf = MmioRead32 (LAN9118_HW_CFG);
    TxFifoOption = (HwConf >> 16) & 0xF;

    // Choose the correct size (always use larger than requested if possible)
    if (*TxDataSize < TX_FIFO_MIN_SIZE) {
      *TxDataSize = TX_FIFO_MIN_SIZE;
      *RxDataSize = 13440;
      *RxStatusSize = 896;
      TxFifoOption = 2;
    } else if ((*TxDataSize > TX_FIFO_MIN_SIZE) && (*TxDataSize <= 2560)) {
      *TxDataSize = 2560;
      *RxDataSize = 12480;
      *RxStatusSize = 832;
      TxFifoOption = 3;
    } else if ((*TxDataSize > 2560) && (*TxDataSize <= 3584)) {
      *TxDataSize = 3584;
      *RxDataSize = 11520;
      *RxStatusSize = 768;
      TxFifoOption = 4;
    } else if ((*TxDataSize > 3584) && (*TxDataSize <= 4608)) { // default option
      *TxDataSize = 4608;
      *RxDataSize = 10560;
      *RxStatusSize = 704;
      TxFifoOption = 5;
    } else if ((*TxDataSize > 4608) && (*TxDataSize <= 5632)) {
      *TxDataSize = 5632;
      *RxDataSize = 9600;
      *RxStatusSize = 640;
      TxFifoOption = 6;
    } else if ((*TxDataSize > 5632) && (*TxDataSize <= 6656)) {
      *TxDataSize = 6656;
      *RxDataSize = 8640;
      *RxStatusSize = 576;
      TxFifoOption = 7;
    } else if ((*TxDataSize > 6656) && (*TxDataSize <= 7680)) {
      *TxDataSize = 7680;
      *RxDataSize = 7680;
      *RxStatusSize = 512;
      TxFifoOption = 8;
    } else if ((*TxDataSize > 7680) && (*TxDataSize <= 8704)) {
      *TxDataSize = 8704;
      *RxDataSize = 6720;
      *RxStatusSize = 448;
      TxFifoOption = 9;
    } else if ((*TxDataSize > 8704) && (*TxDataSize <= 9728)) {
      *TxDataSize = 9728;
      *RxDataSize = 5760;
      *RxStatusSize = 384;
      TxFifoOption = 10;
    } else if ((*TxDataSize > 9728) && (*TxDataSize <= 10752)) {
      *TxDataSize = 10752;
      *RxDataSize = 4800;
      *RxStatusSize = 320;
      TxFifoOption = 11;
    } else if ((*TxDataSize > 10752) && (*TxDataSize <= 11776)) {
      *TxDataSize = 11776;
      *RxDataSize = 3840;
      *RxStatusSize = 256;
      TxFifoOption = 12;
    } else if ((*TxDataSize > 11776) && (*TxDataSize <= 12800)) {
      *TxDataSize = 12800;
      *RxDataSize = 2880;
      *RxStatusSize = 192;
      TxFifoOption = 13;
    } else if ((*TxDataSize > 12800) && (*TxDataSize <= 13824)) {
      *TxDataSize = 13824;
      *RxDataSize = 1920;
      *RxStatusSize = 128;
      TxFifoOption = 14;
    }
  } else {
    ASSERT(0); // Untested code path
    HwConf = 0;
    TxFifoOption = 0;
  }

  // Do we need DMA?
  if (Flags & ALLOC_USE_DMA) {
    return EFI_UNSUPPORTED; // Unsupported as of now
  }
  // Clear and assign the new size option
  HwConf &= ~(0xF0000);
  HwConf |= ((TxFifoOption & 0xF) << 16);
  MmioWrite32 (LAN9118_HW_CFG, HwConf);
  gBS->Stall (LAN9118_STALL);

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------------------------------------

    Utility functions

---------------------------------------------------------------------------------------------------------------------*/

EFI_MAC_ADDRESS
GetCurrentMacAddress (
  VOID
  )
{
  UINT32          MacAddrHighValue;
  UINT32          MacAddrLowValue;
  EFI_MAC_ADDRESS MacAddress;

  // Read the Mac Addr high register
  MacAddrHighValue = (IndirectMACRead32 (INDIRECT_MAC_INDEX_ADDRH) & 0xFFFF);
  // Read the Mac Addr low register
  MacAddrLowValue = IndirectMACRead32 (INDIRECT_MAC_INDEX_ADDRL);

  SetMem (&MacAddress, sizeof(MacAddress), 0);
  MacAddress.Addr[0] = (MacAddrLowValue & 0xFF);
  MacAddress.Addr[1] = (MacAddrLowValue & 0xFF00) >> 8;
  MacAddress.Addr[2] = (MacAddrLowValue & 0xFF0000) >> 16;
  MacAddress.Addr[3] = (MacAddrLowValue & 0xFF000000) >> 24;
  MacAddress.Addr[4] = (MacAddrHighValue & 0xFF);
  MacAddress.Addr[5] = (MacAddrHighValue & 0xFF00) >> 8;

  DEBUG((DEBUG_NET, "GetCurrentMacAddress() = %s\n", Mac2Str (&MacAddress)));
  return MacAddress;
}

#define ReturnUnlock(s) do { Status = (s); goto exit_unlock; } while(0)

/*
**  UEFI Start() function
**
**  Parameters:
**
**  @param pobj:  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
**
**  Description:
**
**    This function starts a network interface. If the network interface successfully starts, then
**    EFI_SUCCESS will be returned.
*/
EFI_STATUS
EFIAPI
SnpStart (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp
 )
{
  EFI_MAC_ADDRESS *Mac;
  EFI_TPL          SavedTpl;
  EFI_STATUS       Status;

  // Check Snp instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // Check state
  if ((Snp->Mode->State == EfiSimpleNetworkStarted) || (Snp->Mode->State == EfiSimpleNetworkInitialized)) {
    ReturnUnlock (EFI_ALREADY_STARTED);
  } else if (Snp->Mode->State == EfiSimpleNetworkMaxState) {
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Attempt to wake-up the device if it is in a lower power state
  if (((MmioRead32 (LAN9118_PMT_CTRL) & MPTCTRL_PM_MODE_MASK) >> 12) != 0) {
    DEBUG((DEBUG_NET, "Waking from reduced power state.\n"));
    MmioWrite32 (LAN9118_BYTE_TEST, 0xFFFFFFFF);
    gBS->Stall (LAN9118_STALL);
  }

  // Check that device is active
  while ((MmioRead32 (LAN9118_PMT_CTRL) & MPTCTRL_READY) == 0);

  // Check that EEPROM isn't active
  while (MmioRead32 (LAN9118_E2P_CMD) & E2P_EPC_BUSY);

  Mac = &Snp->Mode->CurrentAddress;
  DEBUG((DEBUG_NET, "Using current address %s\n", Mac2Str(Mac)));
  IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRL,
                      (Mac->Addr[3] << 24) |
                      (Mac->Addr[2] << 16) |
                      (Mac->Addr[1] << 8)  |
                       Mac->Addr[0]
                    );

  IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRH,
                      (Mac->Addr[5] << 8) |
                       Mac->Addr[4]
                    );

  // Clear and acknowledge interrupts
  MmioWrite32 (LAN9118_INT_EN, 0);
  MmioWrite32 (LAN9118_IRQ_CFG, 0);
  MmioWrite32 (LAN9118_INT_STS, 0xFFFFFFFF);

  // Change state
  Snp->Mode->State = EfiSimpleNetworkStarted;
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI Stop() function
**
*/
EFI_STATUS
EFIAPI
SnpStop (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp
  )
{
  EFI_TPL          SavedTpl;
  EFI_STATUS       Status;

  // Check Snp Instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // Check state of the driver
  if ((Snp->Mode->State == EfiSimpleNetworkStopped) || (Snp->Mode->State == EfiSimpleNetworkMaxState)) {
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Stop the Tx and Rx
  StopTx (STOP_TX_CFG | STOP_TX_MAC, Snp);
  StopRx (0, Snp);

  // Change the state
  switch (Snp->Mode->State) {
    case EfiSimpleNetworkStarted:
    case EfiSimpleNetworkInitialized:
      Snp->Mode->State = EfiSimpleNetworkStopped;
      break;
    default:
      ReturnUnlock (EFI_DEVICE_ERROR);
  }
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}


// Allocated receive and transmit buffers
STATIC UINT32 gTxBuffer = 0;

// Buffer sizes
STATIC UINT32 gTxDataSize = 0;
STATIC UINT32 gTxStatusSize = 0;
STATIC UINT32 gRxDataSize = 0;
STATIC UINT32 gRxStatusSize = 0;

/*
**  UEFI Initialize() function
**
*/
EFI_STATUS
EFIAPI
SnpInitialize (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        UINTN                        RxBufferSize    OPTIONAL,
  IN        UINTN                        TxBufferSize    OPTIONAL
  )
{
  EFI_TPL    SavedTpl;
  EFI_STATUS Status;
  UINT32     PmConf;
  INT32      AllocResult;

  // Initialize variables
  // Global variables to hold tx and rx FIFO allocation
  gTxBuffer = 0;

  // Check Snp Instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // First check that driver has not already been initialized
  if (Snp->Mode->State == EfiSimpleNetworkInitialized) {
    DEBUG((EFI_D_WARN, "LAN9118 Driver already initialized\n"));
    ReturnUnlock (EFI_SUCCESS);
  } else
  if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "LAN9118 Driver not started\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Initiate a PHY reset
  if (PhySoftReset (PHY_RESET_PMT | PHY_RESET_CHECK_LINK, Snp) < 0) {
    Snp->Mode->State = EfiSimpleNetworkStopped;
    DEBUG((EFI_D_WARN, "Warning: Link not ready after TimeOut. Check ethernet cable\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Initiate a software reset
  Status = SoftReset (0, Snp);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Soft Reset Failed: Hardware Error\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Read the PM register
  PmConf = MmioRead32 (LAN9118_PMT_CTRL);

  // MPTCTRL_WOL_EN: Allow Wake-On-Lan to detect wake up frames or magic packets
  // MPTCTRL_ED_EN:  Allow energy detection to allow lowest power consumption mode
  // MPTCTRL_PME_EN: Allow Power Management Events
  PmConf = 0;
  PmConf |= (MPTCTRL_WOL_EN | MPTCTRL_ED_EN | MPTCTRL_PME_EN);

  // Write the current configuration to the register
  MmioWrite32 (LAN9118_PMT_CTRL, PmConf);
  gBS->Stall (LAN9118_STALL);
  gBS->Stall (LAN9118_STALL);

  // Configure GPIO and HW
  Status = ConfigureHardware (HW_CONF_USE_LEDS, Snp);
  if (EFI_ERROR(Status)) {
    ReturnUnlock (Status);
  }

  // Assign the transmitter buffer size (default values)
  gTxDataSize = 4608;
  gTxStatusSize = 512;    // this never changes
  gRxDataSize = 10560;
  gRxStatusSize = 704;

  // Check that a buff size was specified
  if (TxBufferSize) {
    AllocResult = ChangeFifoAllocation (
                          ALLOC_USE_FIFOS,
                          &TxBufferSize,
                          &RxBufferSize,
                          &gTxStatusSize,
                          &gRxStatusSize,
                          Snp
                          );

    if (AllocResult < 0) {
      return EFI_OUT_OF_RESOURCES;
    }

    gTxDataSize = gTxDataSize;
    gTxStatusSize = gTxStatusSize;
    gTxDataSize = TxBufferSize;
    gRxDataSize = RxBufferSize;
  }

  // Set the current MAC Address
  Snp->Mode->CurrentAddress = GetCurrentMacAddress ();

  // Set the permanent MAC Address
  Snp->Mode->PermanentAddress = Snp->Mode->CurrentAddress;

  // Do auto-negotiation if supported
  Status = AutoNegotiate (Snp);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Lan9118: Auto Negotiation not supported.\n"));
  }

  // Configure flow control depending on speed capabilities
  Status = ConfigureFlow (0, 0, 0, 0, Snp);
  if (EFI_ERROR(Status)) {
    ReturnUnlock (Status);
  }

  // Enable the receiver and transmitter
  Status = StartRx (0, Snp);
  if (EFI_ERROR(Status)) {
    ReturnUnlock (Status);
  }

  Status = StartTx (Snp);
  if (EFI_ERROR(Status)) {
    ReturnUnlock (Status);
  }

  // Now acknowledge all interrupts
  MmioWrite32 (LAN9118_INT_STS, 0xFFFFFFFF);

  // Declare the driver as initialized
  Snp->Mode->State = EfiSimpleNetworkInitialized;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI Reset () function
**
*/
EFI_STATUS
EFIAPI
SnpReset (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        BOOLEAN Verification
  )
{
  EFI_TPL     SavedTpl;
  EFI_STATUS  Status;
  UINT32 PmConf;
  UINT32 HwConf;
  UINT32 ResetFlags;

  PmConf = 0;
  HwConf = 0;
  ResetFlags = 0;

  // Check Snp Instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // First check that driver has not already been initialized
  if (Snp->Mode->State == EfiSimpleNetworkStarted) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not yet initialized\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  } else if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not started\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Initiate a PHY reset
  if (PhySoftReset (PHY_RESET_PMT | PHY_RESET_CHECK_LINK, Snp) < 0) {
    Snp->Mode->State = EfiSimpleNetworkStopped;
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Initiate a software reset
  ResetFlags |= SOFT_RESET_CHECK_MAC_ADDR_LOAD | SOFT_RESET_CLEAR_INT;

  if (Verification) {
    ResetFlags |= SOFT_RESET_SELF_TEST;
  }

  if (SoftReset (ResetFlags, Snp) < 0) {
    DEBUG((EFI_D_WARN, "Warning: Soft Reset Failed: Hardware Error\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Read the PM register
  PmConf = MmioRead32 (LAN9118_PMT_CTRL);

  // MPTCTRL_WOL_EN: Allow Wake-On-Lan to detect wake up frames or magic packets
  // MPTCTRL_ED_EN:  Allow energy detection to allow lowest power consumption mode
  // MPTCTRL_PME_EN: Allow Power Management Events
  PmConf |= (MPTCTRL_WOL_EN | MPTCTRL_ED_EN | MPTCTRL_PME_EN);

  // Write the current configuration to the register
  MmioWrite32 (LAN9118_PMT_CTRL, PmConf);
  gBS->Stall (LAN9118_STALL);

  // Check that a buffer size was specified in SnpInitialize
  if (gTxBuffer != 0) {
    HwConf = MmioRead32 (LAN9118_HW_CFG);        // Read the HW register
    HwConf &= ~((UINT32)0xF0000);               // Clear buffer bits first
    HwConf |= (gTxBuffer << 16);                // assign size chosen in SnpInitialize

    MmioWrite32 (LAN9118_HW_CFG, HwConf);         // Write the conf
    gBS->Stall (LAN9118_STALL);
  }

  // Enable the receiver and transmitter and clear their contents
  StartRx (START_RX_CLEAR, Snp);
  StartTx (Snp);

  // Now acknowledge all interrupts
  MmioWrite32 (LAN9118_INT_STS, 0xFFFFFFFF);
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI Shutdown () function
**
*/
EFI_STATUS
EFIAPI
SnpShutdown (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp
  )
{
  EFI_TPL        SavedTpl;
  EFI_STATUS     Status;

  // Check Snp Instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // First check that driver has not already been initialized
  if (Snp->Mode->State == EfiSimpleNetworkStarted) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not yet initialized\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  } else if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver in stopped state\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Initiate a PHY reset
  PhySoftReset (PHY_RESET_PMT, Snp);

  // Initiate a software reset
  if (SoftReset (0, Snp) < 0) {
    DEBUG((EFI_D_WARN, "Warning: Soft Reset Failed: Hardware Error\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  }
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}


/*
**  UEFI ReceiveFilters() function
**
*/
EFI_STATUS
EFIAPI
SnpReceiveFilters (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        UINT32 Enable,
  IN        UINT32 Disable,
  IN        BOOLEAN Reset,
  IN        UINTN NumMfilter          OPTIONAL,
  IN        EFI_MAC_ADDRESS *Mfilter  OPTIONAL
  )
{
  EFI_TPL        SavedTpl;
  EFI_STATUS     Status;
  UINT32 MacCSRValue;
  UINT32 MultHashTableHigh;
  UINT32 MultHashTableLow;
  UINT32 Crc;
  UINT8 BitToSelect;
  UINT32 Count;

  MacCSRValue = 0;
  MultHashTableHigh = 0;
  MultHashTableLow = 0;
  Crc = 0xFFFFFFFF;
  BitToSelect = 0;
  Count = 0;

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // Check that driver was started and initialised
  if (Snp->Mode->State == EfiSimpleNetworkStarted) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not initialized\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  } else if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver in stopped state\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // If reset then clear the filter registers
  if (Reset) {
    Enable |= EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST;
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_HASHL, 0x00000000);
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_HASHH, 0x00000000);
  }

  // Set the hash tables
  if ((NumMfilter > 0) && (!Reset)) {

    // Read the Multicast High Hash Table
    MultHashTableHigh = IndirectMACRead32 (INDIRECT_MAC_INDEX_HASHH);

    // Read the Multicast Low Hash Table
    MultHashTableLow = IndirectMACRead32 (INDIRECT_MAC_INDEX_HASHL);

    // Go through each filter address and set appropriate bits on hash table
    for (Count = 0; Count < NumMfilter; Count++) {

      // Generate a 32-bit CRC for Ethernet
      Crc = GenEtherCrc32 (&Mfilter[Count],6);
      //gBS->CalculateCrc32 ((VOID*)&Mfilter[Count],6,&Crc); <-- doesn't work as desired

      // Get the most significant 6 bits to index hash registers
      BitToSelect = (Crc >> 26) & 0x3F;

      // Select hashlow register if MSB is not set
      if ((BitToSelect & 0x20) == 0) {
        MultHashTableLow |= (1 << BitToSelect);
      } else {
        MultHashTableHigh |= (1 << (BitToSelect & 0x1F));
      }
    }

    // Write the desired hash
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_HASHL, MultHashTableLow);
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_HASHH, MultHashTableHigh);
  }

  // Read MAC controller
  MacCSRValue = IndirectMACRead32 (INDIRECT_MAC_INDEX_CR);

  // Set the options for the MAC_CSR
  if (Enable & EFI_SIMPLE_NETWORK_RECEIVE_UNICAST) {
    StartRx (0, Snp);
    DEBUG((DEBUG_NET, "Allowing Unicast Frame Reception\n"));
  }

  if (Disable & EFI_SIMPLE_NETWORK_RECEIVE_UNICAST) {
    StopRx (0, Snp);
    DEBUG((DEBUG_NET, "Disabling Unicast Frame Reception\n"));
  }

  if (Enable & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) {
    MacCSRValue |= MACCR_HPFILT;
    DEBUG((DEBUG_NET, "Allowing Multicast Frame Reception\n"));
  }

  if (Disable & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) {
    MacCSRValue &= ~MACCR_HPFILT;
    DEBUG((DEBUG_NET, "Disabling Multicast Frame Reception\n"));
  }

  if (Enable & EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST) {
    MacCSRValue &= ~(MACCR_BCAST);
    DEBUG((DEBUG_NET, "Allowing Broadcast Frame Reception\n"));
  }

  if (Disable & EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST) {
    MacCSRValue |= MACCR_BCAST;
    DEBUG((DEBUG_NET, "Disabling Broadcast Frame Reception\n"));
  }

  if (Enable & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) {
    MacCSRValue |= MACCR_PRMS;
    DEBUG((DEBUG_NET, "Enabling Promiscuous Mode\n"));
  }

  if (Disable & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) {
    MacCSRValue &= ~MACCR_PRMS;
    DEBUG((DEBUG_NET, "Disabling Promiscuous Mode\n"));
  }

  if (Enable & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST) {
    MacCSRValue |= (MACCR_HPFILT | MACCR_PRMS);
    DEBUG((DEBUG_NET, "Enabling Promiscuous Multicast Mode\n"));
  }

  if (Disable & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST) {
    MacCSRValue &= ~(MACCR_HPFILT | MACCR_PRMS);
    DEBUG((DEBUG_NET, "Disabling Promiscuous Multicast Mode\n"));
  }

  // Write the options to the MAC_CSR
  IndirectMACWrite32 (INDIRECT_MAC_INDEX_CR, MacCSRValue);
  gBS->Stall (LAN9118_STALL);
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI StationAddress() function
**
*/
EFI_STATUS
EFIAPI
SnpStationAddress (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL *Snp,
  IN        BOOLEAN Reset,
  IN        EFI_MAC_ADDRESS *NewMac
)
{
  DEBUG((DEBUG_NET, "SnpStationAddress(%d, %s)\n", Reset, Mac2Str(NewMac)));

  EFI_TPL        SavedTpl;
  EFI_STATUS     Status;
  UINT32 Count;
  UINT8 PermAddr[6];

  Count = 0;

  // Check Snp instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // Check that driver was started and initialised
  if (Snp->Mode->State == EfiSimpleNetworkStarted) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not initialized\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  } else if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver in stopped state\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Get the Permanent MAC address if need reset
  if (Reset) {
    // Try using EEPROM first
    if ((IndirectEEPROMRead32 (0) & 0xFF) == 0xA5) {
      for (Count = 1; Count < 7; Count++) {
        PermAddr[Count - 1] = IndirectEEPROMRead32 (Count);
      }

      // Write address
      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRL, (UINT32)((UINT32)PermAddr[0]) | ((UINT32)PermAddr[1] << 8) | ((UINT32)PermAddr[2] << 16) | ((UINT32)PermAddr[3] << 24));
      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRH, (UINT32)((((UINT32)PermAddr[4]) | ((UINT32)PermAddr[5] << 8)) & 0xFFFF));
    } else {
      // Otherwise make our own
      DEBUG((EFI_D_WARN, "Warning: No valid EEPROM detected. Using a hard coded address.\n"));

      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRL, LAN9118_DEFAULT_MAC_ADDRL);
      IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRH, LAN9118_DEFAULT_MAC_ADDRH);
    }

  // Otherwise use the specified new MAC address
  } else {
    if (NewMac == NULL) {
      ReturnUnlock (EFI_INVALID_PARAMETER);
    }

    // Write address
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRL, (UINT32)((UINT32)NewMac->Addr[0]) | ((UINT32)NewMac->Addr[1] << 8) | ((UINT32)NewMac->Addr[2] << 16) | ((UINT32)NewMac->Addr[3] << 24));
    IndirectMACWrite32 (INDIRECT_MAC_INDEX_ADDRH, (UINT32)((((UINT32)NewMac->Addr[4]) | ((UINT32)NewMac->Addr[5] << 8)) & 0xFFFF));
  }
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI Statistics() function
**
*/
EFI_STATUS
EFIAPI
SnpStatistics (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        BOOLEAN Reset,
  IN  OUT   UINTN *StatSize,
      OUT   EFI_NETWORK_STATISTICS *Statistics
  )
{
  LAN9118_DRIVER *LanDriver;
  EFI_TPL         SavedTpl;
  EFI_STATUS      Status;

  DEBUG((DEBUG_NET, "SnpStatistics()\n"));

  // Check Snp instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Check pointless condition
  if ((!Reset) && (StatSize == NULL) && (Statistics == NULL)) {
    return EFI_SUCCESS;
  }

  // Check the parameters
  if ((StatSize == NULL) && (Statistics != NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);
  LanDriver = INSTANCE_FROM_SNP_THIS(Snp);

  // Check that driver was started and initialised
  if (Snp->Mode->State == EfiSimpleNetworkStarted) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver not initialized\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  } else if (Snp->Mode->State == EfiSimpleNetworkStopped) {
    DEBUG((EFI_D_WARN, "Warning: LAN9118 Driver in stopped state\n"));
    ReturnUnlock (EFI_NOT_STARTED);
  }

  // Do a reset if required
  if (Reset) {
    ZeroMem (&LanDriver->Stats, sizeof(EFI_NETWORK_STATISTICS));
  }

  // Check buffer size
  if (*StatSize < sizeof(EFI_NETWORK_STATISTICS)) {
    *StatSize = sizeof(EFI_NETWORK_STATISTICS);
    ReturnUnlock (EFI_BUFFER_TOO_SMALL);
  }

  // Fill in the statistics
  CopyMem(&Statistics, &LanDriver->Stats, sizeof(EFI_NETWORK_STATISTICS));
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}

/*
**  UEFI MCastIPtoMAC() function
**
*/
EFI_STATUS
EFIAPI
SnpMcastIptoMac (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        BOOLEAN IsIpv6,
  IN        EFI_IP_ADDRESS *Ip,
      OUT   EFI_MAC_ADDRESS *McastMac
  )
{
  DEBUG((DEBUG_NET, "SnpMcastIptoMac()\n"));

  // Check Snp instance
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Check parameters
  if ((McastMac == NULL) || (Ip == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  // Make sure MAC address is empty
  ZeroMem (McastMac, sizeof(EFI_MAC_ADDRESS));

  // If we need ipv4 address
  if (!IsIpv6) {
    // Most significant 25 bits of a multicast HW address are set
    McastMac->Addr[0] = 0x01;
    McastMac->Addr[1] = 0x00;
    McastMac->Addr[2] = 0x5E;

    // Lower 23 bits from ipv4 address
    McastMac->Addr[3] = (Ip->v4.Addr[1] & 0x7F); // Clear the ms bit (25th bit of MAC must be 0)
    McastMac->Addr[4] = Ip->v4.Addr[2];
    McastMac->Addr[5] = Ip->v4.Addr[3];
  } else {
    // Most significant 16 bits of multicast v6 HW address are set
    McastMac->Addr[0] = 0x33;
    McastMac->Addr[1] = 0x33;

    // lower four octets are taken from ipv6 address
    McastMac->Addr[2] = Ip->v6.Addr[8];
    McastMac->Addr[3] = Ip->v6.Addr[9];
    McastMac->Addr[4] = Ip->v6.Addr[10];
    McastMac->Addr[5] = Ip->v6.Addr[11];
  }

  return EFI_SUCCESS;
}

/*
**  UEFI NvData() function
**
*/
EFI_STATUS
EFIAPI
SnpNvData (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* pobj,
  IN        BOOLEAN read_write,
  IN        UINTN offset,
  IN        UINTN buff_size,
  IN  OUT   VOID *data
  )
{
  DEBUG((DEBUG_NET, "SnpNvData()\n"));

  return EFI_UNSUPPORTED;
}


/*
**  UEFI GetStatus () function
**
*/
EFI_STATUS
EFIAPI
SnpGetStatus (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
      OUT   UINT32 *IrqStat  OPTIONAL,
      OUT   VOID **TxBuff    OPTIONAL
  )
{
  LAN9118_DRIVER *LanDriver;
  EFI_STATUS Status;
  EFI_TPL SavedTpl;
  UINT32  FifoInt;
  UINT32  IntStatus;
  BOOLEAN MediaPresent;
  UINT32 TxStatus;
  INTN TxCacheIndex;

  // Check preliminaries
  if (Snp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  if (Snp->Mode->State != EfiSimpleNetworkInitialized) {
     ReturnUnlock (EFI_NOT_STARTED);
  }

  LanDriver = INSTANCE_FROM_SNP_THIS(Snp);

  // Set the transmit status available level
  FifoInt = MmioRead32 (LAN9118_FIFO_INT);

  if ((FifoInt & 0x00FF0000) == 0) {
    FifoInt |= (1 << 16);
    MmioWrite32 (LAN9118_FIFO_INT, FifoInt);
  }

  IntStatus = MmioRead32 (LAN9118_INT_STS);
  if ((IntStatus & (INSTS_TXSTOP_INT | INSTS_RXSTOP_INT | INSTS_TXSO | INSTS_RWT |
                    INSTS_RXE | INSTS_TXE | INSTS_TDFO | INSTS_TDFA | INSTS_TSFF |
                    INSTS_TSFL | INSTS_RXDF_INT | INSTS_RSFF)) != 0) {
    DEBUG((EFI_D_WARN, "IntStatus: %08x\n", IntStatus));
  }

  // Report interrupt status if IrqStat is not NULL
  if (IrqStat != NULL) {
    *IrqStat = 0;

    // Check for receive interrupt
    if (IntStatus & INSTS_RSFL) { // Data moved from rx FIFO
      *IrqStat |= EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT;
      MmioWrite32 (LAN9118_INT_STS,INSTS_RSFL);
    }

    // Check for transmit interrupt
    if (IntStatus & INSTS_TSFL) {
      *IrqStat |= EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT;
      MmioWrite32 (LAN9118_INT_STS,INSTS_TSFL);
    }

    // Check for software interrupt
    if (IntStatus & INSTS_SW_INT) {
      *IrqStat |= EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT;
      MmioWrite32 (LAN9118_INT_STS,INSTS_SW_INT);
    }
  }

  // Return the recycled transmit address
  if ((TxBuff != NULL) && (TxStatusUsedSpace (Snp) > 0)) {
    TxStatus = MmioRead32 (LAN9118_TX_STATUS);

    TxCacheIndex = ((INTN)(TxStatus >> 16) & 0xffff) - 1;
    if ((0 <= TxCacheIndex) && (TxCacheIndex < LAN9118_TX_CACHE_DEPTH)) {
      if (LanDriver->TxCache[TxCacheIndex] != NULL) {
        *TxBuff = LanDriver->TxCache[TxCacheIndex];
        LanDriver->TxCache[TxCacheIndex] = NULL;
      } else {
        *TxBuff = NULL;
      }
    } else {
      *TxBuff = NULL;
    }

    // Check Tx Status (we ignore TXSTATUS_NO_CA has it might happen in Full Duplex)
    if (((TxStatus & TXSTATUS_ES) != 0) && ((TxStatus & TXSTATUS_NO_CA) == 0)) {
      DEBUG((EFI_D_WARN, "Warning: There was an error transmitting TxStatus=0x%X:\n", TxStatus));
      if (TxStatus & TXSTATUS_DEF) {
        DEBUG((EFI_D_WARN, "- Packet tx was deferred\n"));
      }
      if (TxStatus & TXSTATUS_EDEF) {
        DEBUG((EFI_D_WARN, "- Tx ended because of excessive deferral\n"));
      }
      if (TxStatus & TXSTATUS_ECOLL) {
        DEBUG((EFI_D_WARN, "- Tx ended because of Excessive Collisions\n"));
      }
      if (TxStatus & TXSTATUS_LCOLL) {
        DEBUG((EFI_D_WARN, "- Packet Tx aborted after coll window of 64 bytes\n"));
      }
      if (TxStatus & TXSTATUS_LOST_CA) {
        DEBUG((EFI_D_WARN, "- Lost carrier during Tx\n"));
      }
    }
  }

  // Update the media status
  MediaPresent = CheckLinkStatus (Snp);
  if (MediaPresent != Snp->Mode->MediaPresent) {
    DEBUG((EFI_D_WARN, "LAN9118: Link %s\n", MediaPresent ? L"up" : L"down"));
  }
  Snp->Mode->MediaPresent = MediaPresent;
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}


/*
**  UEFI Transmit() function
**
*/
EFI_STATUS
EFIAPI
SnpTransmit (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN        UINTN HdrSize,
  IN        UINTN BuffSize,
  IN        VOID *Data,
  IN        EFI_MAC_ADDRESS *SrcAddr   OPTIONAL,
  IN        EFI_MAC_ADDRESS *DstAddr  OPTIONAL,
  IN        UINT16 *Protocol            OPTIONAL
  )
{
  LAN9118_DRIVER *LanDriver;
  EFI_TPL         SavedTpl;
  EFI_STATUS      Status;
  UINT32 TxFreeSpace;
  UINT32 TxStatusSpace;
  INT32 Count;
  UINT32 CommandA;
  UINT32 CommandB;
  UINT16 LocalProtocol;
  UINT32 *LocalData;
  INTN TxCacheIndex;

  // Check preliminaries
  if ((Snp == NULL) || (Data == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);
  LanDriver = INSTANCE_FROM_SNP_THIS(Snp);
  TxCacheIndex = (-1);

  if (Snp->Mode->State != EfiSimpleNetworkInitialized) {
     ReturnUnlock (EFI_NOT_STARTED);
  }

  // Ensure header is correct size if non-zero
  if (HdrSize) {
    if (HdrSize != Snp->Mode->MediaHeaderSize) {
       ReturnUnlock (EFI_INVALID_PARAMETER);
    }

    if ((DstAddr == NULL) || (Protocol == NULL)) {
       ReturnUnlock (EFI_INVALID_PARAMETER);
    }
  }

  // Before transmitting check the link status
  if (!Snp->Mode->MediaPresent) {
     ReturnUnlock (EFI_NOT_READY);
  }

  // Find a free entry in the TxCache array
  for (TxCacheIndex = LAN9118_TX_CACHE_DEPTH - 1; TxCacheIndex >= 0; --TxCacheIndex) {
    if (LanDriver->TxCache[TxCacheIndex] == NULL) {
      break;
    }
  }
  if (TxCacheIndex < 0) {
    ReturnUnlock (EFI_NOT_READY);
  }
  LanDriver->TxCache[TxCacheIndex] = Data;

  // Get DATA FIFO free space in bytes
  TxFreeSpace = TxDataFreeSpace (Snp);
  if (TxFreeSpace < BuffSize) {
    ReturnUnlock (EFI_NOT_READY);
  }

  // Get STATUS FIFO used space in DWORDS
  TxStatusSpace = TxStatusUsedSpace (Snp);
  if (TxStatusSpace > 125) {
    ReturnUnlock (EFI_NOT_READY);
  }

  // Check for the nature of the frame
  if ((DstAddr->Addr[0] & 0x1) == 1) {
    LanDriver->Stats.TxMulticastFrames += 1;
  } else {
    LanDriver->Stats.TxUnicastFrames += 1;
  }

  // Check if broadcast
  if (DstAddr->Addr[0] == 0xFF) {
    LanDriver->Stats.TxBroadcastFrames += 1;
  }

  if (HdrSize) {
    // Format pointer
    LocalData = (UINT32*) Data;
    LocalProtocol = *Protocol;

    // Create first buffer to pass to controller (for the header)
    CommandA = TX_CMD_A_FIRST_SEGMENT | TX_CMD_A_BUFF_SIZE(HdrSize);
    CommandB = TX_CMD_B_PACKET_TAG(TxCacheIndex + 1) | TX_CMD_B_PACKET_LENGTH(BuffSize);

    // Write the commands first
    MmioWrite32 (LAN9118_TX_DATA, CommandA);
    MmioWrite32 (LAN9118_TX_DATA, CommandB);

    // Write the destination address
    MmioWrite32 (LAN9118_TX_DATA,
               (DstAddr->Addr[0]) |
               (DstAddr->Addr[1] << 8) |
               (DstAddr->Addr[2] << 16) |
               (DstAddr->Addr[3] << 24)
               );

    MmioWrite32 (LAN9118_TX_DATA,
               (DstAddr->Addr[4]) |
               (DstAddr->Addr[5] << 8) |

    // Write the Source Address
               (SrcAddr->Addr[0] << 16) |
               (SrcAddr->Addr[1] << 24)
               );

    MmioWrite32 (LAN9118_TX_DATA,
               (SrcAddr->Addr[2]) |
               (SrcAddr->Addr[3] << 8) |
               (SrcAddr->Addr[4] << 16) |
               (SrcAddr->Addr[5] << 24)
               );

    // Write the Protocol
    MmioWrite32 (LAN9118_TX_DATA, (UINT32)(HTONS(LocalProtocol)));

    // Next buffer is the payload
    CommandA = TX_CMD_A_COMPLETION_INT | TX_CMD_A_START_OFFSET(2) |
               TX_CMD_A_LAST_SEGMENT | TX_CMD_A_BUFF_SIZE(BuffSize - HdrSize);

    // Write the commands
    MmioWrite32 (LAN9118_TX_DATA, CommandA);
    MmioWrite32 (LAN9118_TX_DATA, CommandB);

    // Write the payload
    for (Count = 0; Count < ((BuffSize + 3) >> 2) - 3; Count++) {
      MmioWrite32 (LAN9118_TX_DATA,LocalData[Count + 3]);
    }

    // Get STATUS FIFO used space in bytes
    /*TxStatusSpace = TxStatusUsedSpace (0, Snp);
    DEBUG((EFI_D_ERROR, "Status FIFO Size after write: %d\n",TxStatusSpace));

    // Data written debug
    DEBUG((EFI_D_ERROR, "Payload written: %d bytes",BuffSize - HdrSize));
    for (Count = 0; Count < ((BuffSize + 3) >> 2) - 3; Count++) {
      if ((Count % 6) == 0)
        DEBUG((EFI_D_ERROR, "\n"));
      DEBUG((DEBUG_NET, "0x%08X", NTOHL(LocalData[Count + 3])));
    }
    DEBUG((EFI_D_ERROR, "\n"));
    */

  } else {

    // Format pointer
    LocalData = (UINT32*) Data;

    // Create a buffer to pass to controller
    CommandA = TX_CMD_A_COMPLETION_INT | TX_CMD_A_FIRST_SEGMENT |
               TX_CMD_A_LAST_SEGMENT | TX_CMD_A_BUFF_SIZE(BuffSize);
    CommandB = TX_CMD_B_PACKET_TAG(TxCacheIndex + 1) | TX_CMD_B_PACKET_LENGTH(BuffSize);

    // Write the commands first
    MmioWrite32 (LAN9118_TX_DATA, CommandA);
    MmioWrite32 (LAN9118_TX_DATA, CommandB);

    // Write all the data
    for (Count = 0; Count < ((BuffSize + 3) >> 2); Count++) {
      MmioWrite32 (LAN9118_TX_DATA,LocalData[Count]);
    }

    // Data written debug
    /*DEBUG((EFI_D_ERROR, "Packet written:"));
    for (Count = 0; Count < ((BuffSize + 3) >> 2); Count++) {
      if ((Count % 6) == 0)
        DEBUG((EFI_D_ERROR, "\n"));
      DEBUG((DEBUG_NET, "0x%08X",LocalData[Count]));
    }*/
  }

  LanDriver->Stats.TxTotalFrames += 1;
  LanDriver->Stats.TxGoodFrames += 1;
  TxCacheIndex = (-1);
  Status = EFI_SUCCESS;

  // Restore TPL and return
exit_unlock:
  if (TxCacheIndex >= 0) {
    LanDriver->TxCache[TxCacheIndex] = NULL;
  }
  gBS->RestoreTPL (SavedTpl);
  return Status;
}


/*
**  UEFI Receive() function
**
*/
EFI_STATUS
EFIAPI
SnpReceive (
  IN        EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
      OUT   UINTN *HdrSize                OPTIONAL,
  IN  OUT   UINTN *BuffSize,
      OUT   VOID *Data,
      OUT   EFI_MAC_ADDRESS *SrcAddr      OPTIONAL,
      OUT   EFI_MAC_ADDRESS *DstAddr      OPTIONAL,
      OUT   UINT16 *Protocol              OPTIONAL
  )
{
  EFI_TPL         SavedTpl;
  EFI_STATUS      Status;
  LAN9118_DRIVER *LanDriver;
  UINT32 RxFifoStatus;
  UINT32 NumPackets;
  UINT32 RxDataUsed;
  UINT32 RxStatusUsed;
  UINT32 RxCfgValue;
  UINT32 PLength; // Packet length
  UINT32 ReadLimit;
  UINT32 Count;
  UINT32 Padding;
  UINT32 *RawData;
  EFI_MAC_ADDRESS Dst;
  EFI_MAC_ADDRESS Src;

  // Check preliminaries
  if ((Snp == NULL) || (Data == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  // Serialize access to data and registers
  SavedTpl = gBS->RaiseTPL (LAN9118_TPL);

  // Check state
  if (Snp->Mode->State != EfiSimpleNetworkInitialized) {
    ReturnUnlock (EFI_NOT_STARTED);
  }

  LanDriver = INSTANCE_FROM_SNP_THIS(Snp);

  // Before receiving check the link status
  /*if (CheckLinkStatus (Snp) < 0) {
    ReturnUnlock (EFI_NOT_READY);
  }*/

  // Get the used space in rx fifo
  RxDataUsed = RxDataUsedSpace (0, Snp);
  if (RxDataUsed > gRxDataSize - 4) {
    LanDriver->Stats.RxDroppedFrames += 1;
    ReturnUnlock (EFI_NOT_READY);
  }

  // Get the used status space
  RxStatusUsed = RxStatusUsedSpace (0, Snp);
  if (RxStatusUsed > gRxStatusSize - 4) {
    LanDriver->Stats.RxDroppedFrames += 1;
    ReturnUnlock (EFI_NOT_READY);
  }

  // Get the number of packets to read
  NumPackets = RxStatusUsed >> 2;
  if (!NumPackets) {
    ReturnUnlock (EFI_NOT_READY);
  }

  // Read Rx Status (only if not empty)
  RxFifoStatus = MmioRead32 (LAN9118_RX_STATUS);
  LanDriver->Stats.RxTotalFrames += 1;

  // First check for errors
  if ((RxFifoStatus & RXSTATUS_MII_ERROR) ||
      (RxFifoStatus & RXSTATUS_RXW_TO) ||
      (RxFifoStatus & RXSTATUS_FTL) ||
      (RxFifoStatus & RXSTATUS_LCOLL) ||
      (RxFifoStatus & RXSTATUS_LE) ||
      (RxFifoStatus & RXSTATUS_DB))
  {
    DEBUG((EFI_D_WARN, "Warning: There was an error on frame reception.\n"));
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Check if we got a CRC error
  if (RxFifoStatus & RXSTATUS_CRC_ERROR) {
    DEBUG((EFI_D_WARN, "Warning: Crc Error\n"));
    LanDriver->Stats.RxCrcErrorFrames += 1;
    LanDriver->Stats.RxDroppedFrames += 1;
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Check if we got a runt frame
  if (RxFifoStatus & RXSTATUS_RUNT) {
    DEBUG((EFI_D_WARN, "Warning: Runt Frame\n"));
    LanDriver->Stats.RxUndersizeFrames += 1;
    LanDriver->Stats.RxDroppedFrames += 1;
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Check filtering status for this packet
  if (RxFifoStatus & RXSTATUS_FILT_FAIL) {
    DEBUG((EFI_D_WARN, "Warning: Frame Failed Filtering\n"));
    // fast forward?
  }

  // Check if we got a broadcast frame
  if (RxFifoStatus & RXSTATUS_BCF) {
    LanDriver->Stats.RxBroadcastFrames += 1;
  }

  // Check if we got a multicast frame
  if (RxFifoStatus & RXSTATUS_MCF) {
    LanDriver->Stats.RxMulticastFrames += 1;
  }

  // Check if we got a unicast frame
  if ((RxFifoStatus & RXSTATUS_BCF) && ((RxFifoStatus & RXSTATUS_MCF) == 0)) {
    LanDriver->Stats.RxUnicastFrames += 1;
  }

  // Get the received packet length
  PLength = (RxFifoStatus & RXSTATUS_PL_MASK) >> 16;
  LanDriver->Stats.RxTotalBytes += (PLength - 4);

  // Check buffer size
  if (*BuffSize < PLength) {
    *BuffSize = PLength;
    ReturnUnlock (EFI_BUFFER_TOO_SMALL);
  }

  // If padding is applied, read more DWORDs
  if (PLength % 4) {
    Padding = 4 - (PLength % 4);
    ReadLimit = (PLength + Padding)/4;
  } else {
    ReadLimit = PLength/4;
    Padding = 0;
  }

  // Set the amount of data to be transfered out of FIFO for THIS packet
  // This can be used to trigger an interrupt, and status can be checked
  RxCfgValue = MmioRead32 (LAN9118_RX_CFG);
  RxCfgValue &= ~(RXCFG_RX_DMA_CNT_MASK);
  RxCfgValue |= (ReadLimit & 0xFFFF) << 16;

  // Set end alignment to 4-bytes
  RxCfgValue &= ~(RXCFG_RX_END_ALIGN_MASK);
  MmioWrite32 (LAN9118_RX_CFG, RxCfgValue);

  // Update buffer size
  *BuffSize = PLength; // -4 bytes may be needed: Received in buffer as
                       // 4 bytes longer than packet actually is, unless
                       // packet is < 64 bytes

  if (HdrSize != NULL)
    *HdrSize = Snp->Mode->MediaHeaderSize;

  // Format the pointer
  RawData = (UINT32*)Data;

  // Read Rx Packet
  for (Count = 0; Count < ReadLimit; Count++) {
    RawData[Count] = MmioRead32 (LAN9118_RX_DATA);
  }

  // Check for Rx errors (worst possible error)
  if (MmioRead32 (LAN9118_INT_STS) & INSTS_RXE) {
    DEBUG((EFI_D_WARN, "Warning: Receiver Error. Restarting...\n"));

    // Initiate a software reset
    if (SoftReset (0, Snp) < 0) {
      DEBUG((EFI_D_ERROR, "Error: Soft Reset Failed: Hardware Error.\n"));
      ReturnUnlock (EFI_DEVICE_ERROR);
    }

    // Acknowledge the RXE
    MmioWrite32 (LAN9118_INT_STS, INSTS_RXE);
    gBS->Stall (LAN9118_STALL);

    // Restart the rx (and do not clear FIFO)
    StartRx (0, Snp);

    // Say that command could not be sent
    ReturnUnlock (EFI_DEVICE_ERROR);
  }

  // Get the destination address
  if (DstAddr != NULL) {
    Dst.Addr[0] = (RawData[0] & 0xFF);
    Dst.Addr[1] = (RawData[0] & 0xFF00) >> 8;
    Dst.Addr[2] = (RawData[0] & 0xFF0000) >> 16;
    Dst.Addr[3] = (RawData[0] & 0xFF000000) >> 24;
    Dst.Addr[4] = (RawData[1] & 0xFF);
    Dst.Addr[5] = (RawData[1] & 0xFF00) >> 8;
    CopyMem (DstAddr, &Dst, NET_ETHER_ADDR_LEN);
  }

  // Get the source address
  if (SrcAddr != NULL) {
    Src.Addr[0] = (RawData[1] & 0xFF0000) >> 16;
    Src.Addr[1] = (RawData[1] & 0xFF000000) >> 24;
    Src.Addr[2] = (RawData[2] & 0xFF);
    Src.Addr[3] = (RawData[2] & 0xFF00) >> 8;
    Src.Addr[4] = (RawData[2] & 0xFF0000) >> 16;
    Src.Addr[5] = (RawData[2] & 0xFF000000) >> 24;
    CopyMem (SrcAddr,&Src, NET_ETHER_ADDR_LEN);
  }

  // Get the protocol
  if (Protocol != NULL) {
    *Protocol = NTOHS (RawData[3] & 0xFFFF);
  }

  LanDriver->Stats.RxGoodFrames += 1;
  Status = EFI_SUCCESS;

exit_unlock:
  gBS->RestoreTPL (SavedTpl);
  return Status;
}



/*
**  Entry point for the LAN9118 driver
**
*/
EFI_STATUS
Lan9118DxeEntry (
  IN EFI_HANDLE Handle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;
  LAN9118_DRIVER *LanDriver;
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp;
  EFI_SIMPLE_NETWORK_MODE *SnpMode;
  LAN9118_DEVICE_PATH *Lan9118Path;
  EFI_HANDLE ControllerHandle;

  // The PcdLan9118DxeBaseAddress PCD must be defined
  ASSERT(PcdGet32 (PcdLan9118DxeBaseAddress) != 0);

  // Allocate Resources
  LanDriver = AllocateZeroPool (sizeof(LAN9118_DRIVER));
  Lan9118Path = (LAN9118_DEVICE_PATH*)AllocateCopyPool(sizeof(LAN9118_DEVICE_PATH), &Lan9118PathTemplate);

  // Initialize pointers
  Snp = &(LanDriver->Snp);
  SnpMode = &(LanDriver->SnpMode);
  Snp->Mode = SnpMode;

  // Set the signature of the LAN Driver structure
  LanDriver->Signature = LAN9118_SIGNATURE;

  // Assign fields and func pointers
  Snp->Revision = EFI_SIMPLE_NETWORK_PROTOCOL_REVISION;
  Snp->WaitForPacket = NULL;
  Snp->Initialize = SnpInitialize;
  Snp->Start = SnpStart;
  Snp->Stop = SnpStop;
  Snp->Reset = SnpReset;
  Snp->Shutdown = SnpShutdown;
  Snp->ReceiveFilters = SnpReceiveFilters;
  Snp->StationAddress = SnpStationAddress;
  Snp->Statistics = SnpStatistics;
  Snp->MCastIpToMac = SnpMcastIptoMac;
  Snp->NvData = SnpNvData;
  Snp->GetStatus = SnpGetStatus;
  Snp->Transmit = SnpTransmit;
  Snp->Receive = SnpReceive;

  // Start completing simple network mode structure
  SnpMode->State = EfiSimpleNetworkStopped;
  SnpMode->HwAddressSize = NET_ETHER_ADDR_LEN; // HW address is 6 bytes
  SnpMode->MediaHeaderSize = sizeof(ETHER_HEAD); // Not sure of this
  SnpMode->MaxPacketSize = EFI_PAGE_SIZE; // Preamble + SOF + Ether Frame (with VLAN tag +4bytes)
  SnpMode->NvRamSize = 0;           // No NVRAM with this device
  SnpMode->NvRamAccessSize = 0; // No NVRAM with this device

  // Update network mode information
  SnpMode->ReceiveFilterMask = EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST |
                                 EFI_SIMPLE_NETWORK_RECEIVE_UNICAST |
                                 EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST |
                                 EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS;/* |
                                 EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST;*/
  // Current allowed settings
  SnpMode->ReceiveFilterSetting = EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST |
                                    EFI_SIMPLE_NETWORK_RECEIVE_UNICAST |
                                    EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST;

  // LAN9118 has 64bit multicast hash table
  SnpMode->MaxMCastFilterCount = MAX_MCAST_FILTER_CNT;
  SnpMode->MCastFilterCount = 0;
  ZeroMem (&SnpMode->MCastFilter, MAX_MCAST_FILTER_CNT * sizeof(EFI_MAC_ADDRESS));

  // Set the interface type (1: Ethernet or 6: IEEE 802 Networks)
  SnpMode->IfType = NET_IFTYPE_ETHERNET;

  // Mac address is changeable as it is loaded from erasable memory
  SnpMode->MacAddressChangeable = TRUE;

  // Can only transmit one packet at a time
  SnpMode->MultipleTxSupported = FALSE;

  // MediaPresent checks for cable connection and partner link
  SnpMode->MediaPresentSupported = TRUE;
  SnpMode->MediaPresent = FALSE;

  //  Set broadcast address
  SetMem (&SnpMode->BroadcastAddress, sizeof (EFI_MAC_ADDRESS), 0xFF);

  // Assign fields for device path
  Lan9118Path->Lan9118.MacAddress = GetCurrentMacAddress ();
  Lan9118Path->Lan9118.IfType = Snp->Mode->IfType;

  // Initialise the protocol
  ControllerHandle = 0;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ControllerHandle,
                  &gEfiSimpleNetworkProtocolGuid, Snp,
                  &gEfiDevicePathProtocolGuid, Lan9118Path,
                  NULL
                  );
  // Say what the status of loading the protocol structure is
  if (EFI_ERROR(Status)) {
    FreePool (LanDriver);
  } else {
    LanDriver->ControllerHandle = ControllerHandle;
  }

  return Status;
}
