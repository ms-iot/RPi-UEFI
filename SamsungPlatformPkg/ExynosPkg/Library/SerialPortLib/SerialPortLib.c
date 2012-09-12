/** @file
  Serial I/O Port library functions with no library constructor/destructor


  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Include/Uefi.h>
#include <Library/SerialPortLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Platform/ArmPlatform.h>

/*

  Programmed hardware of Serial port.
 Irrespective of the previous settings Initialize it to current requirement
**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
#if 0
	UINT32 UARTConsoleBase;
	UINT32 SmdkCmuBase;

	UARTConsoleBase=PcdGet32(PcdConsoleUartBase);
	SmdkCmuBase=PcdGet32(PcdCmuBase);

	MmioWrite32 (SmdkCmuBase + CLK_SRC_PERIL0_OFFSET, CLK_SRC_PERIL0_VAL);
	MmioWrite32 (SmdkCmuBase + CLK_DIV_PERIL0_OFFSET, CLK_DIV_PERIL0_VAL);

	if (PL011_CONSOLE_UART_SPEED == 115200) {
		// Initialize baud rate generator
		MmioWrite32 (UARTConsoleBase + UARTIBRD, UART_115200_IDIV);
		MmioWrite32 (UARTConsoleBase + UARTFBRD, UART_115200_FDIV);
	} else if (PL011_CONSOLE_UART_SPEED == 38400) {
		// Initialize baud rate generator
		MmioWrite32 (UARTConsoleBase + UARTIBRD, UART_38400_IDIV);
		MmioWrite32 (UARTConsoleBase + UARTFBRD, UART_38400_FDIV);
	} else if (PL011_CONSOLE_UART_SPEED == 19200) {
		// Initialize baud rate generator
		MmioWrite32 (UARTConsoleBase + UARTIBRD, UART_19200_IDIV);
		MmioWrite32 (UARTConsoleBase + UARTFBRD, UART_19200_FDIV);
	} else {
		return EFI_INVALID_PARAMETER;
	}

	  // No parity, 1 stop, no fifo, 8 data bits
	  MmioWrite32 (UARTConsoleBase + UARTLCR_H, UART_LCON_VAL);

	  // configure FIFO contrl regs
	  MmioWrite32 (UARTConsoleBase + UARTECR, UART_ECR_VAL);

	  // enable tx, rx, and uart overall
	  MmioWrite32 (UARTConsoleBase + UARTCR, UART_CR_VAL);
#endif
	return EFI_SUCCESS;
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
	UINTN  Count;
        UINT32 UARTConsoleBase;

	UARTConsoleBase=PcdGet32(PcdConsoleUartBase);
	for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
		while ((MmioRead32 (UARTConsoleBase + UTRSTAT_OFFSET) & UART_TX_EMPTY_FLAG_MASK) == 0);
		MmioWrite8 (UARTConsoleBase + UTXH_OFFSET, *Buffer);
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
	 UINTN   Count;
	 UINT32 UARTConsoleBase;

        UARTConsoleBase=PcdGet32(PcdConsoleUartBase);
	for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
		while ((MmioRead32 (UARTConsoleBase + UTRSTAT_OFFSET) & UART_RX_EMPTY_FLAG_MASK) == 0);
		*Buffer = MmioRead8 (UARTConsoleBase + URXH_OFFSET);
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
        UINT32 UARTConsoleBase;
        UARTConsoleBase=PcdGet32(PcdConsoleUartBase);

	return ((MmioRead32 (UARTConsoleBase + UTRSTAT_OFFSET) & UART_RX_EMPTY_FLAG_MASK) != 0);
}
