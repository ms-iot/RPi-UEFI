/** @file
  The file for AHCI mode of ATA host controller.

  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "AtaAtapiPassThru.h"

/**
  Read AHCI Operation register.

  @param  Base         Base address.
  @param  Offset       The operation register offset.

  @return The register content read.

**/
UINT32
EFIAPI
AhciReadReg (
  IN  VOID     *Base,
  IN  UINT32    Offset
  )
{
  ASSERT (Base != NULL);
  return *(volatile UINT32 *)(Base + Offset);
}

/**
  Write AHCI Operation register.

  @param  Base         Base address.
  @param  Offset       The operation register offset.
  @param  Data         The data used to write down.

**/
VOID
EFIAPI
AhciWriteReg (
  IN  VOID                *Base,
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
  ASSERT (Base != NULL);
  *(volatile UINT32 *)(Base + Offset) = Data;
}

VOID
EFIAPI
AhciWriteRegWithFlush (
  IN  VOID                *Base,
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
  AhciWriteReg(Base, Offset, Data);
  Data = AhciReadReg(Base, Offset);
}

/**
  Do AND operation with the value of AHCI Operation register.

  @param  Base         Base address.
  @param  Offset       The operation register offset.
  @param  AndData      The data used to do AND operation.

**/
VOID
EFIAPI
AhciAndReg (
  IN VOID                 *Base,
  IN UINT32               Offset,
  IN UINT32               AndData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Base, Offset);

  Data &= AndData;

  AhciWriteReg (Base, Offset, Data);
}

VOID
EFIAPI
AhciAndRegWithFlush (
  IN VOID                 *Base,
  IN UINT32               Offset,
  IN UINT32               AndData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Base, Offset);

  Data &= AndData;

  AhciWriteRegWithFlush (Base, Offset, Data);
}

/**
  Do OR operation with the value of AHCI Operation register.

  @param  Base         Base address.
  @param  Offset       The operation register offset.
  @param  OrData       The data used to do OR operation.

**/
VOID
EFIAPI
AhciOrReg (
  IN VOID                 *Base,
  IN UINT32               Offset,
  IN UINT32               OrData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Base, Offset);

  Data |= OrData;

  AhciWriteReg (Base, Offset, Data);
}

VOID
EFIAPI
AhciOrRegWithFlush (
  IN VOID                 *Base,
  IN UINT32               Offset,
  IN UINT32               OrData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Base, Offset);

  Data |= OrData;

  AhciWriteRegWithFlush (Base, Offset, Data);
}

/**
  Wait for the value of the specified MMIO register set to the test value.

  @param  Base              Base address.
  @param  Offset            The MMIO address to test.
  @param  MaskValue         The mask value of memory.
  @param  TestValue         The test value of memory.
  @param  Timeout           The time out value for wait memory set, uses 100ns as a unit.

  @retval EFI_TIMEOUT       The MMIO setting is time out.
  @retval EFI_SUCCESS       The MMIO is correct set.

**/
EFI_STATUS
EFIAPI
AhciWaitMmioSet (
  IN  VOID                      *Base,
  IN  UINTN                     Offset,
  IN  UINT32                    MaskValue,
  IN  UINT32                    TestValue,
  IN  UINT64                    Timeout
  )
{
  UINT32     Value;
  UINT32     Delay;

  Delay = (UINT32) (DivU64x32 (Timeout, 1000) + 1);

  do {
    //
    // Access PCI MMIO space to see if the value is the tested one.
    //
    Value = AhciReadReg (Base, (UINT32) Offset) & MaskValue;

    if (Value == TestValue) {
      return EFI_SUCCESS;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay (100);

    Delay--;

  } while (Delay > 0);

  return EFI_TIMEOUT;
}

/**
  Wait for the value of the specified system memory set to the test value.

  @param  Address           The system memory address to test.
  @param  MaskValue         The mask value of memory.
  @param  TestValue         The test value of memory.
  @param  Timeout           The time out value for wait memory set, uses 100ns as a unit.

  @retval EFI_TIMEOUT       The system memory setting is time out.
  @retval EFI_SUCCESS       The system memory is correct set.

**/
EFI_STATUS
EFIAPI
AhciWaitMemSet (
  IN  EFI_PHYSICAL_ADDRESS      Address,
  IN  UINT32                    MaskValue,
  IN  UINT32                    TestValue,
  IN  UINT64                    Timeout
  )
{
  UINT32     Value;
  UINT32     Delay;

  Delay = (UINT32) (DivU64x32 (Timeout, 1000) + 1);

  do {
    //
    // Access sytem memory to see if the value is the tested one.
    //
    // The system memory pointed by Address will be updated by the
    // SATA Host Controller, "volatile" is introduced to prevent
    // compiler from optimizing the access to the memory address
    // to only read once.
    //
    Value  = *(volatile UINT32 *) Address;
    Value &= MaskValue;

    if (Value == TestValue) {
      return EFI_SUCCESS;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay (100);

    Delay--;

  } while (Delay > 0);

  return EFI_TIMEOUT;
}

/**
  Check the memory status to the test value.

  @param[in]       Address           The memory address to test.
  @param[in]       MaskValue         The mask value of memory.
  @param[in]       TestValue         The test value of memory.
  @param[in, out]  RetryTimes        The retry times value for waitting memory set. If 0, then just try once.

  @retval EFI_NOTREADY      The memory is not set.
  @retval EFI_TIMEOUT       The memory setting retry times out.
  @retval EFI_SUCCESS       The memory is correct set.

**/
EFI_STATUS
EFIAPI
AhciCheckMemSet (
  IN     EFI_PHYSICAL_ADDRESS      Address,
  IN     UINT32                    MaskValue,
  IN     UINT32                    TestValue,
  IN OUT UINTN                     *RetryTimes OPTIONAL
  )
{
  UINT32     Value;

  if (RetryTimes != NULL) {
    (*RetryTimes)--;
  }

  Value  = *(volatile UINT32 *) Address;
  Value &= MaskValue;

  if (Value == TestValue) {
    return EFI_SUCCESS;
  }

  if ((RetryTimes != NULL) && (*RetryTimes == 0)) {
    return EFI_TIMEOUT;
  } else {
    return EFI_NOT_READY;
  }
}

/**
  Check if the device is still on port. It also checks if the AHCI controller
  supports the address and data count will be transferred.

  @param  Base             Base address.
  @param  Port             The number of port.

  @retval EFI_SUCCESS      The device is attached to port and the transfer data is
                           supported by AHCI controller.
  @retval EFI_UNSUPPORTED  The transfer address and count is not supported by AHCI
                           controller.
  @retval EFI_NOT_READY    The physical communication between AHCI controller and device
                           is not ready.

**/
EFI_STATUS
EFIAPI
AhciCheckDeviceStatus (
  IN VOID                    *Base,
  IN  UINT8                  Port
  )
{
  UINT32      Data;
  UINT32      Offset;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;

  Data   = AhciReadReg (Base, Offset) & EFI_AHCI_PORT_SSTS_DET_MASK;

  if (Data == EFI_AHCI_PORT_SSTS_DET_PCE) {
    return EFI_SUCCESS;
  }

  return EFI_NOT_READY;
}

/**

  Clear the port interrupt and error status. It will also clear
  HBA interrupt status.

  @param      Base           Base address.
  @param      Port           The number of port.

**/
VOID
EFIAPI
AhciClearPortStatus (
  IN VOID                    *Base,
  IN  UINT8                  Port
  )
{
  UINT32 Offset;

  //
  // Clear any error status
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
  AhciWriteRegWithFlush (Base, Offset, AhciReadReg (Base, Offset));

  //
  // Clear any port interrupt status
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_IS;
  AhciWriteRegWithFlush (Base, Offset, AhciReadReg (Base, Offset));

  //
  // Clear any HBA interrupt status
  //
  AhciWriteRegWithFlush (Base, EFI_AHCI_IS_OFFSET, AhciReadReg (Base, EFI_AHCI_IS_OFFSET));
}

/**
  This function is used to dump the Status Registers and if there is ERR bit set
  in the Status Register, the Error Register's value is also be dumped.

  @param  Base             Base address.
  @param  Port             The number of port.
  @param  AtaStatusBlock   A pointer to EFI_ATA_STATUS_BLOCK data structure.

**/
VOID
EFIAPI
AhciDumpPortStatus (
  IN     VOID                       *Base,
  IN     UINT8                      Port,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock
  )
{
  UINT32               Offset;
  UINT32               Data;

  ASSERT (Base != NULL);

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  Data   = AhciReadReg (Base, Offset);

  if (AtaStatusBlock != NULL) {
    ZeroMem (AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

    AtaStatusBlock->AtaStatus  = (UINT8)Data;
    if ((AtaStatusBlock->AtaStatus & BIT0) != 0) {
      AtaStatusBlock->AtaError = (UINT8)(Data >> 8);
    }
  }
}


/**
  Enable the FIS running for giving port.

  @param      Base           Base address.
  @param      Port           The number of port.
  @param      Timeout        The timeout value of enabling FIS, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The FIS enable setting fails.
  @retval EFI_TIMEOUT        The FIS enable setting is time out.
  @retval EFI_SUCCESS        The FIS enable successfully.

**/
EFI_STATUS
EFIAPI
AhciEnableFisReceive (
  IN  VOID                      *Base,
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  AhciOrRegWithFlush (Base, Offset, EFI_AHCI_PORT_CMD_FRE);

//  return AhciWaitMmioSet (
//           Base,
//           Offset,
//           EFI_AHCI_PORT_CMD_FR,
//           EFI_AHCI_PORT_CMD_FR,
//           Timeout
//           );
  return EFI_SUCCESS;
}

/**
  Disable the FIS running for giving port.

  @param      Base           Base address.
  @param      Port           The number of port.
  @param      Timeout        The timeout value of disabling FIS, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The FIS disable setting fails.
  @retval EFI_TIMEOUT        The FIS disable setting is time out.
  @retval EFI_UNSUPPORTED    The port is in running state.
  @retval EFI_SUCCESS        The FIS disable successfully.

**/
EFI_STATUS
EFIAPI
AhciDisableFisReceive (
  IN  VOID                      *Base,
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;
  UINT32 Data;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  Data   = AhciReadReg (Base, Offset);

  //
  // Before disabling Fis receive, the DMA engine of the port should NOT be in running status.
  //
  if ((Data & (EFI_AHCI_PORT_CMD_ST | EFI_AHCI_PORT_CMD_CR)) != 0) {
    return EFI_UNSUPPORTED;
  }

  //
  // Check if the Fis receive DMA engine for the port is running.
  //
  if ((Data & EFI_AHCI_PORT_CMD_FR) != EFI_AHCI_PORT_CMD_FR) {
    return EFI_SUCCESS;
  }

  AhciAndRegWithFlush (Base, Offset, (UINT32)~(EFI_AHCI_PORT_CMD_FRE));

  return EFI_SUCCESS;
//  return AhciWaitMmioSet (
//           Base,
//           Offset,
//           EFI_AHCI_PORT_CMD_FR,
//           0,
//           Timeout
//           );
}



/**
  Build the command list, command table and prepare the fis receiver.

  @param    Base                  Base address.
  @param    AhciRegisters         The pointer to the EFI_AHCI_REGISTERS.
  @param    Port                  The number of port.
  @param    PortMultiplier        The timeout value of stop.
  @param    CommandFis            The control fis will be used for the transfer.
  @param    CommandList           The command list will be used for the transfer.
  @param    AtapiCommand          The atapi command will be used for the transfer.
  @param    AtapiCommandLength    The length of the atapi command.
  @param    CommandSlotNumber     The command slot will be used for the transfer.
  @param    DataPhysicalAddr      The pointer to the data buffer pci bus master address.
  @param    DataLength            The data count to be transferred.

**/
VOID
EFIAPI
AhciBuildCommand (
  IN     VOID                      *Base,
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_COMMAND_FIS       *CommandFis,
  IN     EFI_AHCI_COMMAND_LIST      *CommandList,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     UINT8                      CommandSlotNumber,
  IN OUT VOID                       *DataPhysicalAddr,
  IN     UINT32                     DataLength
  )
{
  UINT64     BaseAddr;
  UINT32     PrdtNumber;
  UINT32     PrdtIndex;
  UINTN      RemainedData;
  UINT64     MemAddr;
  DATA_64    Data64;
  UINT32     Offset;

  //
  // Filling the PRDT
  //
  PrdtNumber = (DataLength + EFI_AHCI_MAX_DATA_PER_PRDT - 1) / EFI_AHCI_MAX_DATA_PER_PRDT;

  //
  // According to AHCI 1.3 spec, a PRDT entry can point to a maximum 4MB data block.
  // It also limits that the maximum amount of the PRDT entry in the command table
  // is 65535.
  //
  ASSERT (PrdtNumber <= 65535);

  Data64.Uint64 = (UINT64) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;

  BaseAddr = Data64.Uint64;
  ZeroMem ((VOID *)((UINT64) BaseAddr), sizeof (EFI_AHCI_RECEIVED_FIS));

  ZeroMem (AhciRegisters->AhciCommandTable, sizeof (EFI_AHCI_COMMAND_TABLE));
  CommandFis->AhciCFisPmNum = PortMultiplier;

  CopyMem (&AhciRegisters->AhciCommandTable->CommandFis, CommandFis, sizeof (EFI_AHCI_COMMAND_FIS));
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  if (AtapiCommand != NULL) {
    CopyMem (
      &AhciRegisters->AhciCommandTable->AtapiCmd,
      AtapiCommand,
      AtapiCommandLength
      );

    CommandList->AhciCmdA = 1;
    CommandList->AhciCmdP = 1;
    CommandList->AhciCmdC = (DataLength == 0) ? 1 : 0;

    AhciOrReg (Base, Offset, (EFI_AHCI_PORT_CMD_DLAE | EFI_AHCI_PORT_CMD_ATAPI));
  } else {
    AhciAndReg (Base, Offset, (UINT32)~(EFI_AHCI_PORT_CMD_DLAE | EFI_AHCI_PORT_CMD_ATAPI));
  }

  RemainedData = DataLength;
  MemAddr      = (UINT64) DataPhysicalAddr;
  CommandList->AhciCmdPrdtl = PrdtNumber;
  for (PrdtIndex = 0; PrdtIndex < PrdtNumber; PrdtIndex++) {
    if (RemainedData < EFI_AHCI_MAX_DATA_PER_PRDT) {
      AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbc = (UINT32)RemainedData - 1;
    } else {
      AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbc = EFI_AHCI_MAX_DATA_PER_PRDT - 1;
    }

    Data64.Uint64 = (UINT64)MemAddr;
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDba  = Data64.Uint32.Lower32;
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbau = Data64.Uint32.Upper32;
    RemainedData -= EFI_AHCI_MAX_DATA_PER_PRDT;
    MemAddr      += EFI_AHCI_MAX_DATA_PER_PRDT;
  }

  //
  // Set the last PRDT to Interrupt On Complete
  //
  if (PrdtNumber > 0) {
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtNumber - 1].AhciPrdtIoc = 1;
  }
  CopyMem (
    (VOID *) ((UINT64) AhciRegisters->AhciCmdList + (UINT64) CommandSlotNumber * sizeof (EFI_AHCI_COMMAND_LIST)),
    CommandList,
    sizeof (EFI_AHCI_COMMAND_LIST)
    );

  Data64.Uint64 = (UINT64) AhciRegisters->AhciCommandTable;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdCtba  = Data64.Uint32.Lower32;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdCtbau = Data64.Uint32.Upper32;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdPmp   = PortMultiplier;
}

/**
  Buid a command FIS.

  @param  CmdFis            A pointer to the EFI_AHCI_COMMAND_FIS data structure.
  @param  AtaCommandBlock   A pointer to the AhciBuildCommandFis data structure.

**/
VOID
EFIAPI
AhciBuildCommandFis (
  IN OUT EFI_AHCI_COMMAND_FIS    *CmdFis,
  IN     EFI_ATA_COMMAND_BLOCK   *AtaCommandBlock
  )
{
  ZeroMem (CmdFis, sizeof (EFI_AHCI_COMMAND_FIS));

  CmdFis->AhciCFisType = EFI_AHCI_FIS_REGISTER_H2D;
  //
  // Indicator it's a command
  //
  CmdFis->AhciCFisCmdInd      = 0x1;
  CmdFis->AhciCFisCmd         = AtaCommandBlock->AtaCommand;

  CmdFis->AhciCFisFeature     = AtaCommandBlock->AtaFeatures;
  CmdFis->AhciCFisFeatureExp  = AtaCommandBlock->AtaFeaturesExp;

  CmdFis->AhciCFisSecNum      = AtaCommandBlock->AtaSectorNumber;
  CmdFis->AhciCFisSecNumExp   = AtaCommandBlock->AtaSectorNumberExp;

  CmdFis->AhciCFisClyLow      = AtaCommandBlock->AtaCylinderLow;
  CmdFis->AhciCFisClyLowExp   = AtaCommandBlock->AtaCylinderLowExp;

  CmdFis->AhciCFisClyHigh     = AtaCommandBlock->AtaCylinderHigh;
  CmdFis->AhciCFisClyHighExp  = AtaCommandBlock->AtaCylinderHighExp;

  CmdFis->AhciCFisSecCount    = AtaCommandBlock->AtaSectorCount;
  CmdFis->AhciCFisSecCountExp = AtaCommandBlock->AtaSectorCountExp;

  CmdFis->AhciCFisDevHead     = (UINT8) (AtaCommandBlock->AtaDeviceHead | 0xE0);
}

/**
  Start a PIO data transfer on specific port.

  @param[in]       Base                Base address.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The PIO data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The PIO data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciPioTransfer (
  IN     VOID                       *Base,
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     BOOLEAN                    Read,
  IN     EFI_ATA_COMMAND_BLOCK      *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock,
  IN OUT VOID                       *MemoryAddr,
  IN     UINT32                     DataCount,
  IN     UINT64                     Timeout,
  IN     ATA_NONBLOCK_TASK          *Task
  )
{
  EFI_STATUS                    Status;
  EFI_PHYSICAL_ADDRESS          FisBaseAddr;
  UINTN                         Offset;
  UINT32                        Delay;
  EFI_AHCI_COMMAND_FIS          CFis;
  EFI_AHCI_COMMAND_LIST         CmdList;
  UINT32                        PortTfd;
  UINT32                        PrdCount;

  Timeout *= 10;
  //
  // Package read needed
  //
  AhciBuildCommandFis (&CFis, AtaCommandBlock);

  ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

  CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;
  CmdList.AhciCmdW   = Read ? 0 : 1;

  AhciBuildCommand (
    Base,
    AhciRegisters,
    Port,
    PortMultiplier,
    &CFis,
    &CmdList,
    AtapiCommand,
    AtapiCommandLength,
    0,
    (VOID *)MemoryAddr,
    DataCount
    );

  Status = AhciStartCommand (
             Base,
             Port,
             0,
             Timeout
             );
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  //
  // Check the status and wait the driver sending data
  //
  FisBaseAddr = (UINT64)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);

  if (Read && (AtapiCommand == 0)) {
    //
    // Wait device sends the PIO setup fis before data transfer
    //
    Status = EFI_TIMEOUT;
    Delay  = (UINT32) (DivU64x32 (Timeout, 1000) + 1);
    do {
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
      PortTfd = AhciReadReg (Base, (UINT32) Offset);

      if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
        Status = EFI_DEVICE_ERROR;
        break;
      }
      Offset = FisBaseAddr + EFI_AHCI_PIO_FIS_OFFSET;


      Status = AhciCheckMemSet (Offset, EFI_AHCI_FIS_TYPE_MASK, EFI_AHCI_FIS_PIO_SETUP, 0);
      if (!EFI_ERROR (Status)) {
        PrdCount = *(volatile UINT32 *) (&(AhciRegisters->AhciCmdList[0].AhciCmdPrdbc));
        if (PrdCount == DataCount) {
          break;
        }
      }

      Offset = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
      Status = AhciCheckMemSet (Offset, EFI_AHCI_FIS_TYPE_MASK, EFI_AHCI_FIS_REGISTER_D2H, 0);
      if (!EFI_ERROR (Status)) {
        Status = EFI_DEVICE_ERROR;
        break;
      }

      //
      // Stall for 100 microseconds.
      //
      MicroSecondDelay(100);

      Delay--;
    } while (Delay > 0);
  } else {
    //
    // Wait for D2H Fis is received
    //
    Offset = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
    Status = AhciWaitMemSet (
               Offset,
               EFI_AHCI_FIS_TYPE_MASK,
               EFI_AHCI_FIS_REGISTER_D2H,
               Timeout
               );

    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
    PortTfd = AhciReadReg (Base, (UINT32) Offset);
    if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
      Status = EFI_DEVICE_ERROR;
    }
  }


Exit:
  AhciStopCommand (
    Base,
    Port,
    Timeout
    );

  AhciDisableFisReceive (
    Base,
    Port,
    Timeout
    );

  AhciDumpPortStatus (Base, Port, AtaStatusBlock);
  return Status;
}

/**
  Start a DMA data transfer on specific port

  @param[in]       Instance            The ATA_ATAPI_PASS_THRU_INSTANCE protocol instance.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The DMA data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The DMA data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciDmaTransfer (
  IN     ATA_ATAPI_PASS_THRU_INSTANCE *Instance,
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     BOOLEAN                    Read,
  IN     EFI_ATA_COMMAND_BLOCK      *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock,
  IN OUT VOID                       *MemoryAddr,
  IN     UINT32                     DataCount,
  IN     UINT64                     Timeout,
  IN     ATA_NONBLOCK_TASK          *Task
  )
{
  EFI_STATUS                    Status;
  UINTN                         Offset;
  EFI_AHCI_COMMAND_FIS          CFis;
  EFI_AHCI_COMMAND_LIST         CmdList;
  UINT64                        FisBaseAddr;
  UINT32                        PortTfd;
  VOID                          *Base;

  EFI_TPL                       OldTpl;

  if (Instance->Mode != EfiAtaAhciMode) {
    return EFI_INVALID_PARAMETER;
  }

  Base = Instance->AhciRegisters.MapBaseAddress;

  if (!Base) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Before starting the Blocking BlockIO operation, push to finish all non-blocking
  // BlockIO tasks.
  // Delay 100us to simulate the blocking time out checking.
  //
  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  while ((Task == NULL) && (!IsListEmpty (&Instance->NonBlockingTaskList))) {
    AsyncNonBlockingTransferRoutine (NULL, Instance);
    //
    // Stall for 100us.
    //
    MicroSecondDelay (100);
  }
  gBS->RestoreTPL (OldTpl);

  if ((Task == NULL) || ((Task != NULL) && (!Task->IsStart))) {
    //
    // Mark the Task to indicate that it has been started.
    //
    if (Task != NULL) {
      Task->IsStart      = TRUE;
      Task->RetryTimes   = (UINT32) (DivU64x32(Timeout, 1000) + 1);
    }

    if (Task != NULL) {
      Task->Map = NULL;
    }
    //
    // Package read needed
    //
    AhciBuildCommandFis (&CFis, AtaCommandBlock);

    ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

    CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;
    CmdList.AhciCmdW   = Read ? 0 : 1;

    AhciBuildCommand (
      Base,
      AhciRegisters,
      Port,
      PortMultiplier,
      &CFis,
      &CmdList,
      AtapiCommand,
      AtapiCommandLength,
      0,
      (VOID *)MemoryAddr,
      DataCount
      );

    Status = AhciStartCommand (
               Base,
               Port,
               0,
               Timeout
               );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }
  }

  //
  // Wait for command compelte
  //
  FisBaseAddr = (UINT64)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);
  Offset      = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
  if (Task != NULL) {
    //
    // For Non-blocking
    //
    Status = AhciCheckMemSet (
               Offset,
               EFI_AHCI_FIS_TYPE_MASK,
               EFI_AHCI_FIS_REGISTER_D2H,
               (UINTN *) (&Task->RetryTimes)
               );
  } else {
    Status = AhciWaitMemSet (
               Offset,
               EFI_AHCI_FIS_TYPE_MASK,
               EFI_AHCI_FIS_REGISTER_D2H,
               Timeout
               );
  }

  if (EFI_ERROR (Status)) {
    Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
    goto Exit;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg (Base, (UINT32) Offset);
  if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  //
  // For Blocking mode, the command should be stopped, the Fis should be disabled
  // and the PciIo should be unmapped.
  // For non-blocking mode, only when a error is happened (if the return status is
  // EFI_NOT_READY that means the command doesn't finished, try again.), first do the
  // context cleanup, then set the packet's Asb status.
  //
  if (Task == NULL ||
      ((Task != NULL) && (Status != EFI_NOT_READY))
     ) {
    AhciStopCommand (
      Base,
      Port,
      Timeout
      );

    AhciDisableFisReceive (
      Base,
      Port,
      Timeout
      );

    if (Task != NULL) {
      Task->Packet->Asb->AtaStatus = 0x01;
    }
  }

  AhciDumpPortStatus (Base, Port, AtaStatusBlock);
  return Status;
}

/**
  Start a non data transfer on specific port.

  @param[in]       Base                Base address.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The non data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The non data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciNonDataTransfer (
  IN     VOID                         *Base,
  IN     EFI_AHCI_REGISTERS            *AhciRegisters,
  IN     UINT8                         Port,
  IN     UINT8                         PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND        *AtapiCommand OPTIONAL,
  IN     UINT8                         AtapiCommandLength,
  IN     EFI_ATA_COMMAND_BLOCK         *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK          *AtaStatusBlock,
  IN     UINT64                        Timeout,
  IN     ATA_NONBLOCK_TASK             *Task
  )
{
  EFI_STATUS                   Status;
  UINT64                       FisBaseAddr;
  UINTN                        Offset;
  UINT32                       PortTfd;
  EFI_AHCI_COMMAND_FIS         CFis;
  EFI_AHCI_COMMAND_LIST        CmdList;

  //
  // Package read needed
  //
  AhciBuildCommandFis (&CFis, AtaCommandBlock);

  ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

  CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;

  AhciBuildCommand (
    Base,
    AhciRegisters,
    Port,
    PortMultiplier,
    &CFis,
    &CmdList,
    AtapiCommand,
    AtapiCommandLength,
    0,
    NULL,
    0
    );

  Status = AhciStartCommand (
             Base,
             Port,
             0,
             Timeout
             );
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  //
  // Wait device sends the Response Fis
  //
  FisBaseAddr = (UINT64)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);
  Offset      = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
  Status      = AhciWaitMemSet (
                  Offset,
                  EFI_AHCI_FIS_TYPE_MASK,
                  EFI_AHCI_FIS_REGISTER_D2H,
                  Timeout
                  );

  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg (Base, (UINT32) Offset);
  if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  AhciStopCommand (
    Base,
    Port,
    Timeout
    );

  AhciDisableFisReceive (
    Base,
    Port,
    Timeout
    );

  AhciDumpPortStatus (Base, Port, AtaStatusBlock);

  return Status;
}

/**
  Stop command running for giving port

  @param  Base               Base address.
  @param  Port               The number of port.
  @param  Timeout            The timeout value of stop, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The command stop unsuccessfully.
  @retval EFI_TIMEOUT        The operation is time out.
  @retval EFI_SUCCESS        The command stop successfully.

**/
EFI_STATUS
EFIAPI
AhciStopCommand (
  IN  VOID                     *Base,
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;
  UINT32 Data;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  Data   = AhciReadReg (Base, Offset);

  if ((Data & (EFI_AHCI_PORT_CMD_ST |  EFI_AHCI_PORT_CMD_CR)) == 0) {
    return EFI_SUCCESS;
  }

  if ((Data & EFI_AHCI_PORT_CMD_ST) != 0) {
    AhciAndRegWithFlush (Base, Offset, (UINT32)~(EFI_AHCI_PORT_CMD_ST));
  }

  return AhciWaitMmioSet (
           Base,
           Offset,
           EFI_AHCI_PORT_CMD_CR,
           0,
           Timeout
           );
}

/**
  Start command for give slot on specific port.

  @param  Base               Base address.
  @param  Port               The number of port.
  @param  CommandSlot        The number of Command Slot.
  @param  Timeout            The timeout value of start, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The command start unsuccessfully.
  @retval EFI_TIMEOUT        The operation is time out.
  @retval EFI_SUCCESS        The command start successfully.

**/
EFI_STATUS
EFIAPI
AhciStartCommand (
  IN  VOID                     *Base,
  IN  UINT8                     Port,
  IN  UINT8                     CommandSlot,
  IN  UINT64                    Timeout
  )
{
  UINT32     CmdSlotBit;
  EFI_STATUS Status;
  UINT32     PortStatus;
  UINT32     StartCmd;
  UINT32     PortTfd;
  UINT32     Offset;
  UINT32     Capability;

  //
  // Collect AHCI controller information
  //
  Capability = AhciReadReg(Base, EFI_AHCI_CAPABILITY_OFFSET);

  CmdSlotBit = (UINT32) (1 << CommandSlot);

  AhciClearPortStatus (
    Base,
    Port
    );

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;

  Status = AhciEnableFisReceive (
             Base,
             Port,
             Timeout
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  PortStatus = AhciReadReg (Base, Offset);

  StartCmd = 0;
  if ((PortStatus & EFI_AHCI_PORT_CMD_ALPE) != 0) {
    StartCmd = AhciReadReg (Base, Offset);
    StartCmd &= ~EFI_AHCI_PORT_CMD_ICC_MASK;
    StartCmd |= EFI_AHCI_PORT_CMD_ACTIVE;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg (Base, Offset);

  if ((PortTfd & (EFI_AHCI_PORT_TFD_BSY | EFI_AHCI_PORT_TFD_DRQ)) != 0) {
    if ((Capability & BIT24) != 0) {
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      AhciOrRegWithFlush (Base, Offset, EFI_AHCI_PORT_CMD_CLO);

      AhciWaitMmioSet (
        Base,
        Offset,
        EFI_AHCI_PORT_CMD_CLO,
        0,
        Timeout
        );
    }
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  AhciOrRegWithFlush (Base, Offset, EFI_AHCI_PORT_CMD_ST | StartCmd);

  //
  // Setting the command
  //
  /* We don't use NCQ so don't need to set SACT */
  /*
   * Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SACT;
   * AhciAndRegWithFlush (Base, Offset, 0);
   * AhciOrRegWithFlush (Base, Offset, CmdSlotBit);
   */

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CI;
  AhciAndRegWithFlush (Base, Offset, 0);
  AhciOrRegWithFlush (Base, Offset, CmdSlotBit);

  return EFI_SUCCESS;
}

/**
  Do AHCI port reset.

  @param  Base               Base address.
  @param  Port               The number of port.
  @param  Timeout            The timeout value of reset, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The port reset unsuccessfully
  @retval EFI_TIMEOUT        The reset operation is time out.
  @retval EFI_SUCCESS        The port reset successfully.

**/
EFI_STATUS
EFIAPI
AhciPortReset (
  IN  VOID                      *Base,
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  EFI_STATUS      Status;
  UINT32          Offset;

  AhciClearPortStatus (Base, Port);

  AhciStopCommand (Base, Port, Timeout);

  AhciDisableFisReceive (Base, Port, Timeout);

  AhciEnableFisReceive (Base, Port, Timeout);

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SCTL;

  AhciOrRegWithFlush (Base, Offset, EFI_AHCI_PORT_SCTL_DET_INIT);

  //
  // wait 5 millisecond before de-assert DET
  //
  MicroSecondDelay (5000);

  AhciAndRegWithFlush (Base, Offset, (UINT32)EFI_AHCI_PORT_SCTL_MASK);

  //
  // wait 5 millisecond before de-assert DET
  //
  MicroSecondDelay (5000);

  //
  // Wait for communication to be re-established
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;
  Status = AhciWaitMmioSet (
             Base,
             Offset,
             EFI_AHCI_PORT_SSTS_DET_MASK,
             EFI_AHCI_PORT_SSTS_DET_PCE,
             Timeout
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
  AhciOrRegWithFlush (Base, Offset, EFI_AHCI_PORT_ERR_CLEAR);

  return EFI_SUCCESS;
}

/**
  Do AHCI HBA reset.

  @param  Base               Base address.
  @param  Timeout            The timeout value of reset, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   AHCI controller is failed to complete hardware reset.
  @retval EFI_TIMEOUT        The reset operation is time out.
  @retval EFI_SUCCESS        AHCI controller is reset successfully.

**/
EFI_STATUS
EFIAPI
AhciReset (
  IN  VOID                      *Base,
  IN  UINT64                    Timeout
  )
{
  UINT32                 Delay;
  UINT32                 Value;

  AhciOrRegWithFlush (Base, EFI_AHCI_GHC_OFFSET, EFI_AHCI_GHC_RESET);

  Delay = (UINT32) (DivU64x32(Timeout, 1000) + 1);

  do {
    Value = AhciReadReg(Base, EFI_AHCI_GHC_OFFSET);

    if ((Value & EFI_AHCI_GHC_RESET) == 0) {
      break;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay(100);

    Delay--;
  } while (Delay > 0);

  if (Delay == 0) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

/**
  Send SMART Return Status command to check if the execution of SMART cmd is successful or not.

  @param  Base                Base address.
  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The timeout value of stop.
  @param  AtaStatusBlock      A pointer to EFI_ATA_STATUS_BLOCK data structure.

  @retval EFI_SUCCESS     Successfully get the return status of S.M.A.R.T command execution.
  @retval Others          Fail to get return status data.

**/
EFI_STATUS
EFIAPI
AhciAtaSmartReturnStatusCheck (
  IN VOID                        *Base,
  IN EFI_AHCI_REGISTERS          *AhciRegisters,
  IN UINT8                       Port,
  IN UINT8                       PortMultiplier,
  IN OUT EFI_ATA_STATUS_BLOCK    *AtaStatusBlock
  )
{
  EFI_STATUS              Status;
  EFI_ATA_COMMAND_BLOCK   AtaCommandBlock;
  UINT8                   LBAMid;
  UINT8                   LBAHigh;
  UINT64                   FisBaseAddr;
  UINT32                  Value;

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));

  AtaCommandBlock.AtaCommand      = ATA_CMD_SMART;
  AtaCommandBlock.AtaFeatures     = ATA_SMART_RETURN_STATUS;
  AtaCommandBlock.AtaCylinderLow  = ATA_CONSTANT_4F;
  AtaCommandBlock.AtaCylinderHigh = ATA_CONSTANT_C2;

  //
  // Send S.M.A.R.T Read Return Status command to device
  //
  Status = AhciNonDataTransfer (
             Base,
             AhciRegisters,
             (UINT8)Port,
             (UINT8)PortMultiplier,
             NULL,
             0,
             &AtaCommandBlock,
             AtaStatusBlock,
             ATA_ATAPI_TIMEOUT,
             NULL
             );

  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  FisBaseAddr = (UINT64)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);

  Value = *(UINT32 *) (FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET);

  if ((Value & EFI_AHCI_FIS_TYPE_MASK) == EFI_AHCI_FIS_REGISTER_D2H) {
    LBAMid  = ((UINT8 *)(UINT64)(FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET))[5];
    LBAHigh = ((UINT8 *)(UINT64)(FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET))[6];

    if ((LBAMid == 0x4f) && (LBAHigh == 0xc2)) {
      //
      // The threshold exceeded condition is not detected by the device
      //
      DEBUG ((EFI_D_INFO, "The S.M.A.R.T threshold exceeded condition is not detected\n"));

    } else if ((LBAMid == 0xf4) && (LBAHigh == 0x2c)) {
      //
      // The threshold exceeded condition is detected by the device
      //
      DEBUG ((EFI_D_INFO, "The S.M.A.R.T threshold exceeded condition is detected\n"));
    }
  }

  return EFI_SUCCESS;
}

/**
  Enable SMART command of the disk if supported.

  @param  Base                Base address.
  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The timeout value of stop.
  @param  IdentifyData        A pointer to data buffer which is used to contain IDENTIFY data.
  @param  AtaStatusBlock      A pointer to EFI_ATA_STATUS_BLOCK data structure.

**/
VOID
EFIAPI
AhciAtaSmartSupport (
  IN VOID                          *Base,
  IN EFI_AHCI_REGISTERS            *AhciRegisters,
  IN UINT8                         Port,
  IN UINT8                         PortMultiplier,
  IN EFI_IDENTIFY_DATA             *IdentifyData,
  IN OUT EFI_ATA_STATUS_BLOCK      *AtaStatusBlock
  )
{
  EFI_STATUS               Status;
  EFI_ATA_COMMAND_BLOCK    AtaCommandBlock;

  //
  // Detect if the device supports S.M.A.R.T.
  //
  if ((IdentifyData->AtaData.command_set_supported_82 & 0x0001) != 0x0001) {
    //
    // S.M.A.R.T is not supported by the device
    //
    DEBUG ((EFI_D_INFO, "S.M.A.R.T feature is not supported at port [%d] PortMultiplier [%d]!\n",
            Port, PortMultiplier));
  } else {
    //
    // Check if the feature is enabled. If not, then enable S.M.A.R.T.
    //
    if ((IdentifyData->AtaData.command_set_feature_enb_85 & 0x0001) != 0x0001) {
      ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));

      AtaCommandBlock.AtaCommand      = ATA_CMD_SMART;
      AtaCommandBlock.AtaFeatures     = ATA_SMART_ENABLE_OPERATION;
      AtaCommandBlock.AtaCylinderLow  = ATA_CONSTANT_4F;
      AtaCommandBlock.AtaCylinderHigh = ATA_CONSTANT_C2;

      //
      // Send S.M.A.R.T Enable command to device
      //
      Status = AhciNonDataTransfer (
                 Base,
                 AhciRegisters,
                 (UINT8)Port,
                 (UINT8)PortMultiplier,
                 NULL,
                 0,
                 &AtaCommandBlock,
                 AtaStatusBlock,
                 ATA_ATAPI_TIMEOUT,
                 NULL
                 );


      if (!EFI_ERROR (Status)) {
        //
        // Send S.M.A.R.T AutoSave command to device
        //
        ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));

        AtaCommandBlock.AtaCommand      = ATA_CMD_SMART;
        AtaCommandBlock.AtaFeatures     = 0xD2;
        AtaCommandBlock.AtaSectorCount  = 0xF1;
        AtaCommandBlock.AtaCylinderLow  = ATA_CONSTANT_4F;
        AtaCommandBlock.AtaCylinderHigh = ATA_CONSTANT_C2;

        Status = AhciNonDataTransfer (
                   Base,
                   AhciRegisters,
                   (UINT8)Port,
                   (UINT8)PortMultiplier,
                   NULL,
                   0,
                   &AtaCommandBlock,
                   AtaStatusBlock,
                   ATA_ATAPI_TIMEOUT,
                   NULL
                   );

        if (!EFI_ERROR (Status)) {
          Status = AhciAtaSmartReturnStatusCheck (
                     Base,
                     AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplier,
                     AtaStatusBlock
                     );
        }
      }
    }
    DEBUG ((EFI_D_INFO, "Enabled S.M.A.R.T feature at port [%d] PortMultiplier [%d]!\n",
            Port, PortMultiplier));
  }

  return ;
}

/**
  Send Buffer cmd to specific device.

  @param  Base                Base address.
  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The timeout value of stop.
  @param  Buffer              The data buffer to store IDENTIFY PACKET data.

  @retval EFI_DEVICE_ERROR    The cmd abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for executing.
  @retval EFI_SUCCESS         The cmd executes successfully.

**/
EFI_STATUS
EFIAPI
AhciIdentify (
  IN VOID                     *Base,
  IN EFI_AHCI_REGISTERS       *AhciRegisters,
  IN UINT8                    Port,
  IN UINT8                    PortMultiplier,
  IN OUT EFI_IDENTIFY_DATA    *Buffer
  )
{
  EFI_STATUS                   Status;
  EFI_ATA_COMMAND_BLOCK        AtaCommandBlock;
  EFI_ATA_STATUS_BLOCK         AtaStatusBlock;

  if (Base == NULL || AhciRegisters == NULL || Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

  AtaCommandBlock.AtaCommand     = ATA_CMD_IDENTIFY_DRIVE;
  AtaCommandBlock.AtaSectorCount = 1;

  Status = AhciPioTransfer (
             Base,
             AhciRegisters,
             Port,
             PortMultiplier,
             NULL,
             0,
             TRUE,
             &AtaCommandBlock,
             &AtaStatusBlock,
             Buffer,
             sizeof (EFI_IDENTIFY_DATA),
             ATA_ATAPI_TIMEOUT,
             NULL
             );

  return Status;
}

/**
  Send Buffer cmd to specific device.

  @param  Base                Base address.
  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The timeout value of stop.
  @param  Buffer              The data buffer to store IDENTIFY PACKET data.

  @retval EFI_DEVICE_ERROR    The cmd abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for executing.
  @retval EFI_SUCCESS         The cmd executes successfully.

**/
EFI_STATUS
EFIAPI
AhciIdentifyPacket (
  IN VOID                     *Base,
  IN EFI_AHCI_REGISTERS       *AhciRegisters,
  IN UINT8                    Port,
  IN UINT8                    PortMultiplier,
  IN OUT EFI_IDENTIFY_DATA    *Buffer
  )
{
  EFI_STATUS                   Status;
  EFI_ATA_COMMAND_BLOCK        AtaCommandBlock;
  EFI_ATA_STATUS_BLOCK         AtaStatusBlock;

  if (Base == NULL || AhciRegisters == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

  AtaCommandBlock.AtaCommand     = ATA_CMD_IDENTIFY_DEVICE;
  AtaCommandBlock.AtaSectorCount = 1;

  Status = AhciPioTransfer (
             Base,
             AhciRegisters,
             Port,
             PortMultiplier,
             NULL,
             0,
             TRUE,
             &AtaCommandBlock,
             &AtaStatusBlock,
             Buffer,
             sizeof (EFI_IDENTIFY_DATA),
             ATA_ATAPI_TIMEOUT,
             NULL
             );

  return Status;
}

/**
  Send SET FEATURE cmd on specific device.

  @param  Base                Base address.
  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The timeout value of stop.
  @param  Feature             The data to send Feature register.
  @param  FeatureSpecificData The specific data for SET FEATURE cmd.

  @retval EFI_DEVICE_ERROR    The cmd abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for executing.
  @retval EFI_SUCCESS         The cmd executes successfully.

**/
EFI_STATUS
EFIAPI
AhciDeviceSetFeature (
  IN VOID                   *Base,
  IN EFI_AHCI_REGISTERS     *AhciRegisters,
  IN UINT8                  Port,
  IN UINT8                  PortMultiplier,
  IN UINT16                 Feature,
  IN UINT32                 FeatureSpecificData
  )
{
  EFI_STATUS               Status;
  EFI_ATA_COMMAND_BLOCK    AtaCommandBlock;
  EFI_ATA_STATUS_BLOCK     AtaStatusBlock;

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

  AtaCommandBlock.AtaCommand      = ATA_CMD_SET_FEATURES;
  AtaCommandBlock.AtaFeatures     = (UINT8) Feature;
  AtaCommandBlock.AtaFeaturesExp  = (UINT8) (Feature >> 8);
  AtaCommandBlock.AtaSectorCount  = (UINT8) FeatureSpecificData;
  AtaCommandBlock.AtaSectorNumber = (UINT8) (FeatureSpecificData >> 8);
  AtaCommandBlock.AtaCylinderLow  = (UINT8) (FeatureSpecificData >> 16);
  AtaCommandBlock.AtaCylinderHigh = (UINT8) (FeatureSpecificData >> 24);

  Status = AhciNonDataTransfer (
             Base,
             AhciRegisters,
             (UINT8)Port,
             (UINT8)PortMultiplier,
             NULL,
             0,
             &AtaCommandBlock,
             &AtaStatusBlock,
             ATA_ATAPI_TIMEOUT,
             NULL
             );

  return Status;
}

/**
  This function is used to send out ATAPI commands conforms to the Packet Command
  with PIO Protocol.

  @param Base               Base address.
  @param AhciRegisters      The pointer to the EFI_AHCI_REGISTERS.
  @param Port               The number of port.
  @param PortMultiplier     The number of port multiplier.
  @param Packet             A pointer to EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET structure.

  @retval EFI_SUCCESS       send out the ATAPI packet command successfully
                            and device sends data successfully.
  @retval EFI_DEVICE_ERROR  the device failed to send data.

**/
EFI_STATUS
EFIAPI
AhciPacketCommandExecute (
  IN  VOID                                          *Base,
  IN  EFI_AHCI_REGISTERS                            *AhciRegisters,
  IN  UINT8                                         Port,
  IN  UINT8                                         PortMultiplier,
  IN  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET    *Packet
  )
{
  EFI_STATUS                   Status;
  VOID                         *Buffer;
  UINT32                       Length;
  EFI_ATA_COMMAND_BLOCK        AtaCommandBlock;
  EFI_ATA_STATUS_BLOCK         AtaStatusBlock;
  BOOLEAN                      Read;

  if (Packet == NULL || Packet->Cdb == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));
  AtaCommandBlock.AtaCommand      = ATA_CMD_PACKET;
  //
  // No OVL; No DMA
  //
  AtaCommandBlock.AtaFeatures     = 0x00;
  //
  // set the transfersize to ATAPI_MAX_BYTE_COUNT to let the device
  // determine how many data should be transferred.
  //
  AtaCommandBlock.AtaCylinderLow  = (UINT8) (ATAPI_MAX_BYTE_COUNT & 0x00ff);
  AtaCommandBlock.AtaCylinderHigh = (UINT8) (ATAPI_MAX_BYTE_COUNT >> 8);

  if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
    Buffer = Packet->InDataBuffer;
    Length = Packet->InTransferLength;
    Read = TRUE;
  } else {
    Buffer = Packet->OutDataBuffer;
    Length = Packet->OutTransferLength;
    Read = FALSE;
  }

  if (Length == 0) {
    Status = AhciNonDataTransfer (
               Base,
               AhciRegisters,
               Port,
               PortMultiplier,
               Packet->Cdb,
               Packet->CdbLength,
               &AtaCommandBlock,
               &AtaStatusBlock,
               Packet->Timeout,
               NULL
               );
  } else {
    Status = AhciPioTransfer (
               Base,
               AhciRegisters,
               Port,
               PortMultiplier,
               Packet->Cdb,
               Packet->CdbLength,
               Read,
               &AtaCommandBlock,
               &AtaStatusBlock,
               Buffer,
               Length,
               Packet->Timeout,
               NULL
               );
  }
  return Status;
}

/**
  Allocate transfer-related data struct which is used at AHCI mode.

  @param  Base                  Base address.
  @param  AhciRegisters         The pointer to the EFI_AHCI_REGISTERS.

**/
EFI_STATUS
EFIAPI
AhciCreateTransferDescriptor (
  IN     VOID                   *Base,
  IN OUT EFI_AHCI_REGISTERS     *AhciRegisters
  )
{
  EFI_STATUS            Status;
  VOID                  *Buffer;
  UINT32                Capability;
  UINT8                 MaxPortNumber;
  UINT8                 MaxCommandSlotNumber;
  UINT64                MaxReceiveFisSize;
  UINT64                MaxCommandListSize;
  UINT64                MaxCommandTableSize;
  //
  // Collect AHCI controller information
  //
  Capability           = AhciReadReg(Base, EFI_AHCI_CAPABILITY_OFFSET);
  MaxPortNumber        = (UINT8) ((Capability & 0x1F) + 1);
  //
  // Get the number of command slots per port supported by this HBA.
  //
  MaxCommandSlotNumber = (UINT8) (((Capability & 0x1F00) >> 8) + 1);

  MaxReceiveFisSize    = MaxPortNumber * sizeof (EFI_AHCI_RECEIVED_FIS);
  Buffer = AllocateZeroPool((UINTN) MaxReceiveFisSize + 256);

  if (!Buffer) {
    return EFI_OUT_OF_RESOURCES;
  }

  AhciRegisters->AhciRFis          = Buffer;
  AhciRegisters->MaxReceiveFisSize = MaxReceiveFisSize;


  //
  // Allocate memory for command list
  // Note that the implemenation is a single task model which only use a command list for all ports.
  //
  MaxCommandListSize = MaxCommandSlotNumber * sizeof (EFI_AHCI_COMMAND_LIST);
  Buffer = AllocateZeroPool((UINTN) MaxCommandListSize + 2048);

  if (!Buffer) {
    return EFI_OUT_OF_RESOURCES;
    goto Error2;
  }

  AhciRegisters->AhciCmdList        = Buffer;
  AhciRegisters->MaxCommandListSize = MaxCommandListSize;

  //
  // Allocate memory for command table
  // According to AHCI 1.3 spec, a PRD table can contain maximum 65535 entries.
  //
  MaxCommandTableSize = sizeof (EFI_AHCI_COMMAND_TABLE);


  Buffer = AllocateZeroPool((UINTN) MaxCommandTableSize + 256);

  if (!Buffer) {
    //
    // Free mapped resource.
    //
    Status = EFI_OUT_OF_RESOURCES;
    goto Error1;
  }

  AhciRegisters->AhciCommandTable    = Buffer;
  AhciRegisters->MaxCommandTableSize = MaxCommandTableSize;

  AhciRegisters->AhciCmdList = (VOID *) (((UINT64)AhciRegisters->AhciCmdList + 2048) & (~(2048 - 1)));
  AhciRegisters->AhciRFis = (VOID *) (((UINT64)AhciRegisters->AhciRFis + 256) & (~(256 - 1)));
  AhciRegisters->AhciCommandTable = (VOID *) (((UINT64)AhciRegisters->AhciCommandTable + 256) & (~(256 - 1)));

  return EFI_SUCCESS;
  //
  // Map error or unable to map the whole CmdList buffer into a contiguous region.
  //
Error1:
  FreePool (AhciRegisters->AhciCmdList);
Error2:
  FreePool (AhciRegisters->AhciRFis);

  return Status;
}

/**
  Initialize ATA host controller at AHCI mode.

  The function is designed to initialize ATA host controller.

  @param[in]  Instance          A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.

**/
EFI_STATUS
EFIAPI
AhciModeInitialization (
  IN  ATA_ATAPI_PASS_THRU_INSTANCE    *Instance
  )
{
  EFI_STATUS                       Status;
  EFI_IDE_CONTROLLER_INIT_PROTOCOL *IdeInit;
  UINT32                           Capability;
  UINT8                            MaxPortNumber;
  UINT32                           PortImplementBitMap;
  UINT64                           BaseAddress;
  EFI_AHCI_REGISTERS               *AhciRegisters;

  UINT8                            Port;
  DATA_64                          Data64;
  UINT32                           Offset;
  UINT32                           Data;
  EFI_IDENTIFY_DATA                Buffer;
  EFI_ATA_DEVICE_TYPE              DeviceType;
  EFI_ATA_COLLECTIVE_MODE          *SupportedModes;
  EFI_ATA_TRANSFER_MODE            TransferMode;
  UINT32                           PhyDetectDelay;

  if (Instance == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  IdeInit = Instance->IdeControllerInit;

  if (Instance->Mode != EfiAtaAhciMode) {
    return EFI_INVALID_PARAMETER;
  }

  /* Support memory-mapped base address */
  IdeInit->GetMappedBaseAddress(IdeInit, &BaseAddress);
  Instance->AhciRegisters.MapBaseAddress = (VOID *) BaseAddress;

  if (!Instance->AhciRegisters.MapBaseAddress) {
    return EFI_INVALID_PARAMETER;
  }

  Status = AhciReset (Instance->AhciRegisters.MapBaseAddress, EFI_AHCI_BUS_RESET_TIMEOUT);

  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Enable AE before accessing any AHCI registers
  //
  AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, EFI_AHCI_GHC_OFFSET, EFI_AHCI_GHC_ENABLE);

  //
  // Collect AHCI controller information
  //
  Capability           = AhciReadReg(Instance->AhciRegisters.MapBaseAddress, EFI_AHCI_CAPABILITY_OFFSET);

  //
  // Get the number of command slots per port supported by this HBA.
  //
  MaxPortNumber        = (UINT8) ((Capability & 0x1F) + 1);

  //
  // Get the bit map of those ports exposed by this HBA.
  // It indicates which ports that the HBA supports are available for software to use.
  //
  PortImplementBitMap  = AhciReadReg(Instance->AhciRegisters.MapBaseAddress, EFI_AHCI_PI_OFFSET);

  DEBUG ((EFI_D_INFO, "PortImplementBitMap:%x\n", PortImplementBitMap));

  AhciRegisters = &Instance->AhciRegisters;
  Status = AhciCreateTransferDescriptor (Instance->AhciRegisters.MapBaseAddress, AhciRegisters);

  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  for (Port = 0; Port < MaxPortNumber; Port ++) {
    if ((PortImplementBitMap & (BIT0 << Port)) != 0) {
      IdeInit->NotifyPhase (IdeInit, EfiIdeBeforeChannelEnumeration, Port);

      //
      // Initialize FIS Base Address Register and Command List Base Address Register for use.
      //
      Data64.Uint64 = (UINT64) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
      AhciWriteRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, Data64.Uint32.Lower32);

      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
      AhciWriteRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, Data64.Uint32.Upper32);

      Data64.Uint64 = (UINT64) (AhciRegisters->AhciCmdList);
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
      AhciWriteRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, Data64.Uint32.Lower32);

      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
      AhciWriteRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, Data64.Uint32.Upper32);


      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      Data = AhciReadReg (Instance->AhciRegisters.MapBaseAddress, Offset);
      if ((Data & EFI_AHCI_PORT_CMD_CPD) != 0) {
        AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, EFI_AHCI_PORT_CMD_POD);
      }

      if ((Capability & EFI_AHCI_CAP_SSS) != 0) {
        DEBUG ((EFI_D_INFO, "Port :%d spinned up\n", Port));
        AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, EFI_AHCI_PORT_CMD_SUD);
      }

      //
      // Disable aggressive power management.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SCTL;
      AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, EFI_AHCI_PORT_SCTL_IPM_INIT);

      //
      // Disable the reporting of the corresponding interrupt to system software.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_IE;
      AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, 0);

      //
      // Now inform the IDE Controller Init Module.
      //
      IdeInit->NotifyPhase (IdeInit, EfiIdeBusBeforeDevicePresenceDetection, Port);

      //
      // Enable FIS Receive DMA engine for the first D2H FIS and spin up.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      AhciOrRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset, EFI_AHCI_PORT_CMD_FRE);


      //
      // Wait no longer than 10 ms to wait the Phy to detect the presence of a device.
      // It's the requirment from SATA1.0a spec section 5.2.
      //
      PhyDetectDelay = EFI_AHCI_BUS_PHY_DETECT_TIMEOUT;
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;
      do {
        Data = AhciReadReg (Instance->AhciRegisters.MapBaseAddress, Offset) & EFI_AHCI_PORT_SSTS_DET_MASK;
        if ((Data == EFI_AHCI_PORT_SSTS_DET_PCE) || (Data == EFI_AHCI_PORT_SSTS_DET)) {
          break;
        }

        MicroSecondDelay (1000);
        PhyDetectDelay--;
      } while (PhyDetectDelay > 0);

      if (PhyDetectDelay == 0) {
        //
        // No device detected at this port.
        //
        DEBUG ((EFI_D_INFO, "No device detected at this port:%p\n", Port));
        continue;
      }

      //
      // According to SATA1.0a spec section 5.2, we need to wait for PxTFD.BSY and PxTFD.DRQ
      // and PxTFD.ERR to be zero. The maximum wait time is 16s which is defined at ATA spec.
      //
      PhyDetectDelay = 16 * 1000;
      do {
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
        if (AhciReadReg(Instance->AhciRegisters.MapBaseAddress, Offset) != 0) {
          AhciWriteRegWithFlush (Instance->AhciRegisters.MapBaseAddress, Offset,
                        AhciReadReg(Instance->AhciRegisters.MapBaseAddress, Offset));
        }
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;

        Data = AhciReadReg (Instance->AhciRegisters.MapBaseAddress, Offset) & EFI_AHCI_PORT_TFD_MASK;
        if (Data == 0) {
          break;
        }

        MicroSecondDelay (1000);
        PhyDetectDelay--;
      } while (PhyDetectDelay > 0);

      if (PhyDetectDelay == 0) {
        DEBUG ((EFI_D_INFO, "No device detected at this port:%p\n", Port));
        continue;
      }

      Data = AhciReadReg (Instance->AhciRegisters.MapBaseAddress, Offset);

      //
      // When the first D2H register FIS is received, the content of PxSIG register is updated.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SIG;
      Status = AhciWaitMmioSet (
                 Instance->AhciRegisters.MapBaseAddress,
                 Offset,
                 0x0000FFFF,
                 0x00000101,
                 EFI_TIMER_PERIOD_SECONDS(16)
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_INFO, "Wait PORT_SIG timeout\n"));
        continue;
      }

      Data = AhciReadReg (Instance->AhciRegisters.MapBaseAddress, Offset);

      if ((Data & EFI_AHCI_ATAPI_SIG_MASK) == EFI_AHCI_ATAPI_DEVICE_SIG) {
        Status = AhciIdentifyPacket (Instance->AhciRegisters.MapBaseAddress, AhciRegisters, Port, 0, &Buffer);

        if (EFI_ERROR (Status)) {
          continue;
        }

        DeviceType = EfiIdeCdrom;
      } else if ((Data & EFI_AHCI_ATAPI_SIG_MASK) == EFI_AHCI_ATA_DEVICE_SIG) {
        Status = AhciIdentify (Instance->AhciRegisters.MapBaseAddress, AhciRegisters, Port, 0, &Buffer);

        if (EFI_ERROR (Status)) {
          REPORT_STATUS_CODE (EFI_PROGRESS_CODE, (EFI_PERIPHERAL_FIXED_MEDIA | EFI_P_EC_NOT_DETECTED));
          continue;
        }

        DeviceType = EfiIdeHarddisk;
      } else {
        continue;
      }
      DEBUG ((EFI_D_INFO, "port [%d] port mulitplier [%d] has a [%a]\n",
              Port, 0, DeviceType == EfiIdeCdrom ? "cdrom" : "harddisk"));

      //
      // If the device is a hard disk, then try to enable S.M.A.R.T feature
      //
      if (DeviceType == EfiIdeHarddisk) {
        AhciAtaSmartSupport (
          Instance->AhciRegisters.MapBaseAddress,
          AhciRegisters,
          Port,
          0,
          &Buffer,
          NULL
          );
      }

      //
      // Submit identify data to IDE controller init driver
      //
      IdeInit->SubmitData (IdeInit, Port, 0, &Buffer);

      //
      // Now start to config ide device parameter and transfer mode.
      //
      Status = IdeInit->CalculateMode (
                          IdeInit,
                          Port,
                          0,
                          &SupportedModes
                          );
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Calculate Mode Fail, Status = %r\n", Status));
        continue;
      }

      //
      // Set best supported PIO mode on this IDE device
      //
      if (SupportedModes->PioMode.Mode <= EfiAtaPioMode2) {
        TransferMode.ModeCategory = EFI_ATA_MODE_DEFAULT_PIO;
      } else {
        TransferMode.ModeCategory = EFI_ATA_MODE_FLOW_PIO;
      }

      TransferMode.ModeNumber = (UINT8) (SupportedModes->PioMode.Mode);

#ifdef APM_XGENE
      SupportedModes->UdmaMode.Valid = FALSE;
#endif

      //
      // Set supported DMA mode on this IDE device. Note that UDMA & MDMA cann't
      // be set together. Only one DMA mode can be set to a device. If setting
      // DMA mode operation fails, we can continue moving on because we only use
      // PIO mode at boot time. DMA modes are used by certain kind of OS booting
      //
      if (SupportedModes->UdmaMode.Valid) {
        TransferMode.ModeCategory = EFI_ATA_MODE_UDMA;
        TransferMode.ModeNumber = (UINT8) (SupportedModes->UdmaMode.Mode);
      } else if (SupportedModes->MultiWordDmaMode.Valid) {
        TransferMode.ModeCategory = EFI_ATA_MODE_MDMA;
        TransferMode.ModeNumber = (UINT8) SupportedModes->MultiWordDmaMode.Mode;
      }

      Status = AhciDeviceSetFeature (Instance->AhciRegisters.MapBaseAddress, AhciRegisters,
                                    Port, 0, 0x03, (UINT32)(*(UINT8 *)&TransferMode));
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Set transfer Mode Fail, Status = %r\n", Status));
        continue;
      }

      //
      // Found a ATA or ATAPI device, add it into the device list.
      //
      CreateNewDeviceInfo (Instance, Port, 0, DeviceType, &Buffer);
      if (DeviceType == EfiIdeHarddisk) {
        REPORT_STATUS_CODE (EFI_PROGRESS_CODE, (EFI_PERIPHERAL_FIXED_MEDIA | EFI_P_PC_ENABLE));
      }
    }
  }

  return EFI_SUCCESS;
}

