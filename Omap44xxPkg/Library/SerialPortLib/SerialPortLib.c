/** @file
  Serial I/O Port library functions with no library constructor/destructor


  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/SerialPortLib.h>
#include <Library/SerialPortExtLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/OmapLib.h>
#include <Omap4430/Omap4430.h>

/*

  Programmed hardware of Serial port.

  @return    Always return EFI_UNSUPPORTED.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
  UINTN   Uart            = PcdGet32(PcdOmap44xxConsoleUart);
  UINT32  UartBaseAddress = UartBase(Uart);

  // Configure UART3 pads
  MmioAnd32(0x4A100144, ~0x70007);

  // Enable UART3 clocks
  MmioOr32(0x4A009550, 0x2);
  
  // Set MODE_SELECT=DISABLE before trying to initialize or modify DLL, DLH registers.
  MmioWrite32 (UartBaseAddress + UART_MDR1_REG, UART_MDR1_MODE_SELECT_DISABLE);

  // Put device in configuration mode.
  MmioWrite32 (UartBaseAddress + UART_LCR_REG, UART_LCR_DIV_EN_ENABLE);

  // Programmable divisor N = 48Mhz/16/115200 = 26
  MmioWrite32 (UartBaseAddress + UART_DLL_REG, 3000000 / PcdGet64 (PcdUartDefaultBaudRate)); // low divisor
  MmioWrite32 (UartBaseAddress + UART_DLH_REG,  0); // high divisor

  // Enter into UART operational mode.
  MmioWrite32 (UartBaseAddress + UART_LCR_REG, UART_LCR_DIV_EN_DISABLE | UART_LCR_CHAR_LENGTH_8);

  // Force DTR and RTS output to active
  MmioWrite32 (UartBaseAddress + UART_MCR_REG, UART_MCR_RTS_FORCE_ACTIVE | UART_MCR_DTR_FORCE_ACTIVE);

  // Clear & enable fifos
  MmioWrite32 (UartBaseAddress + UART_FCR_REG, UART_FCR_TX_FIFO_CLEAR | UART_FCR_RX_FIFO_CLEAR | UART_FCR_FIFO_ENABLE);  

  // Restore MODE_SELECT 
  MmioWrite32 (UartBaseAddress + UART_MDR1_REG, UART_MDR1_MODE_SELECT_UART_16X);

  return RETURN_SUCCESS;
}

/**
  Write data to serial device.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Write data failed.
  @retval !0               Actual number of bytes writed to serial device.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
)
{
  UINT32  LSR = UartBase(PcdGet32(PcdOmap44xxConsoleUart)) + UART_LSR_REG;
  UINT32  THR = UartBase(PcdGet32(PcdOmap44xxConsoleUart)) + UART_THR_REG;
  UINTN   Count;
    
  for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
    while ((MmioRead8(LSR) & UART_LSR_TX_FIFO_E_MASK) == UART_LSR_TX_FIFO_E_NOT_EMPTY);
    MmioWrite8(THR, *Buffer);
  }

  return NumberOfBytes;
}


/**
  Read data from serial device and save the datas in buffer.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Read data failed.
  @retval !0               Aactual number of bytes read from serial device.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
)
{
  UINT32  LSR = UartBase(PcdGet32(PcdOmap44xxConsoleUart)) + UART_LSR_REG;
  UINT32  RBR = UartBase(PcdGet32(PcdOmap44xxConsoleUart)) + UART_RBR_REG;
  UINTN   Count;
    
  for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
    while ((MmioRead8(LSR) & UART_LSR_RX_FIFO_E_MASK) == UART_LSR_RX_FIFO_E_EMPTY);
    *Buffer = MmioRead8(RBR);
  }

  return NumberOfBytes;
}


/**
  Check to see if any data is avaiable to be read from the debug device.

  @retval EFI_SUCCESS       At least one byte of data is avaiable to be read
  @retval EFI_NOT_READY     No data is avaiable to be read
  @retval EFI_DEVICE_ERROR  The serial device is not functioning properly

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  UINT32 LSR = UartBase(PcdGet32(PcdOmap44xxConsoleUart)) + UART_LSR_REG;

  if ((MmioRead8(LSR) & UART_LSR_RX_FIFO_E_MASK) == UART_LSR_RX_FIFO_E_NOT_EMPTY) {
    return TRUE;
  } else {
    return FALSE;
  }
}

