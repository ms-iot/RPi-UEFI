/** @file
  Serial I/O Port library functions with no library constructor/destructor


  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

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
#include <Library/DebugLib.h>

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
    UINT32 UARTConsoleBase;
    UINT32 Tmp;

    UARTConsoleBase=PcdGet32(PcdConsoleUartBase);

    // GPIO
    MmioWrite32(0x11400000, 0x00002222);
    MmioWrite32(0x11400020, 0x222222);
    MmioWrite32(0x11400160, 0x2222);

	// CMU
    Tmp = MmioRead32(0x10020250);
//    DEBUG ((EFI_D_ERROR, "%X \n", Tmp));

    Tmp &= ~((0xF << 16) + (0xF << 12) + (0xF << 8) + (0xF << 4) + (0xF << 0));
    Tmp |= ((0x6 << 16) + (0x6 << 12) + (0x6 << 8) + (0x6 << 4) + (0x6 << 0));
    MmioWrite32 (0x10020250, Tmp);

    Tmp = MmioRead32(0x10020558);
    Tmp &= ~((0xF << 16) + (0xF << 12) + (0xF << 8) + (0xF << 4) + (0xF << 0));
    Tmp |= ((0x7 << 16) + (0x7 << 12) + (0x7 << 8) + (0x7 << 4) + (0x7 << 0));
    MmioWrite32 (0x10020558, Tmp);

    // UART
	MmioWrite32(UARTConsoleBase, 0x3);
	MmioWrite32(UARTConsoleBase+0x4, 0x3C5);
	MmioWrite32(UARTConsoleBase+0x8, 0x111);
	MmioWrite32(UARTConsoleBase+0x28, 0x23);
	MmioWrite32(UARTConsoleBase+0x2C, 0x2);
/*
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
	MmioWrite32(UARTConsoleBase+0x20, 0x4F);
*/
	// For WindDebug Uart initialization
	UARTConsoleBase=PcdGet32(PcdWinDebugUartBase);
	MmioWrite32(UARTConsoleBase, 0x3);
	MmioWrite32(UARTConsoleBase+0x4, 0x3C5);
	MmioWrite32(UARTConsoleBase+0x8, 0x111);
	MmioWrite32(UARTConsoleBase+0x28, 0x35);
	MmioWrite32(UARTConsoleBase+0x2C, 0x4);

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
