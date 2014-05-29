/** @file
  UART Serial Port library functions

  Copyright (c) 2006 - 2009, Intel Corporation
  All rights reserved. 
  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/SerialPortLib.h>
#include "SerialPortLib.h"
#include <Uefi/UefiBaseType.h>
#include <Protocol/SerialIo.h>

VOID SerialInit(VOID)
{
    UINT32 ulUartClkFreq;

    *(volatile UINT32 *)(UART_LCR_REG) = UART_LCR_DLS8;

    *(volatile UINT32 *)(UART_FCR_REG) = UART_FCR_EN | UART_FCR_RXCLR | UART_FCR_TXCLR;

    *(volatile UINT32 *)(UART_LCR_REG) = UART_LCR_DLAB | UART_LCR_DLS8;

    ulUartClkFreq = TCXO_CLK_FREQ;

    *(volatile UINT32 *)(UART_DLL_REG) = (ulUartClkFreq / (16 * BAUDRATE) ) & 0xff;
    *(volatile UINT32 *)(UART_DLH_REG) = ((ulUartClkFreq/ (16 * BAUDRATE) ) >> 8 ) & 0xff;

    *(volatile UINT32 *)(UART_LCR_REG) = UART_LCR_DLS8;

    *(volatile UINT32 *)(UART_IEL_REG) = 0x00;

    *(volatile UINT32 *)(UART_THR_REG) = 0x53;

    return ;

}


/**
  Initialize the serial device hardware.
  
  If no initialization is required, then return RETURN_SUCCESS.
  If the serial device was successfuly initialized, then return RETURN_SUCCESS.
  If the serial device could not be initialized, then return RETURN_DEVICE_ERROR.
  
  @retval RETURN_SUCCESS        The serial device was initialized.
  @retval RETURN_DEVICE_ERROR   The serail device could not be initialized.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
    return RETURN_SUCCESS;
}


UINT8 UART_ChkSndEnd(VOID)
{
    if(!(*(UINT8 *)UART_LSR_REG & UART_LSR_THRE))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
  Write data from buffer to serial device. 
 
  Writes NumberOfBytes data bytes from Buffer to the serial device.  
  The number of bytes actually written to the serial device is returned.
  If the return value is less than NumberOfBytes, then the write operation failed.

  If Buffer is NULL, then ASSERT(). 

  If NumberOfBytes is zero, then return 0.

  @param  Buffer           Pointer to the data buffer to be written.
  @param  NumberOfBytes    Number of bytes to written to the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes written to the serial device.  
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
)
{
  UINTN  Result;

  if (Buffer == NULL) {
    return 0;
  }

  Result = NumberOfBytes;

  while (NumberOfBytes--) {

    SerialPortWriteChar(*Buffer);
    Buffer++;
  }

  return Result;
}


/**
  Reads data from a serial device into a buffer.

  @param  Buffer           Pointer to the data buffer to store the data read from the serial device.
  @param  NumberOfBytes    Number of bytes to read from the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes read from the serial device.  
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
)
{
  UINTN  Result;

  if (NULL == Buffer) {
    return 0;
  }

  Result = NumberOfBytes;

  while (NumberOfBytes--) {
    //
    // Wait for the serail port to be ready.
    //
    *Buffer=SerialPortReadChar();
    Buffer++ ;
  }

  return Result;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls aserial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  return (BOOLEAN) ((*(volatile UINT8 *)(UART_LSR_REG) & UART_LSR_DR) == UART_LSR_DR);

}

VOID SerialPortWriteChar(UINT8 scShowChar)
{
    UINT32 ulLoop = 0;
      
    while(ulLoop < UART_SEND_DELAY)
    {
        if ((*(volatile UINT8 *)(UART_USR_REG) & UART_FCR_RXCLR) == UART_FCR_RXCLR)
        {
            break;
        }
        
        ulLoop++;
    }
    *(volatile UINT8 *)(UART_THR_REG) = (UINT8)scShowChar;

    ulLoop = 0;
    while(ulLoop < UART_SEND_DELAY)
    {
        if ((*(volatile UINT8 *)(UART_USR_REG) & UART_FCR_TXCLR) == UART_FCR_TXCLR)
        {
            break;
        }
        ulLoop++;
    }
           
    return;
}


UINT8 SerialPortReadChar(VOID)
{
    UINT8 recvchar = 0;

    do
    {
        if ((*(volatile UINT8 *)(UART_LSR_REG) & UART_LSR_DR) == UART_LSR_DR)
        {
            break;
        }
    }while(1);

    recvchar = (*(volatile UINT8 *)(UART_RBR_REG)); 
    
    return recvchar;
}

/**
  Set new attributes to PL011.

  @param  BaudRate                The baud rate of the serial device. If the baud rate is not supported,
                                  the speed will be reduced down to the nearest supported one and the
                                  variable's value will be updated accordingly.
  @param  ReceiveFifoDepth        The number of characters the device will buffer on input. If the specified
                                  value is not supported, the variable's value will be reduced down to the
                                  nearest supported one.
  @param  Timeout                 If applicable, the number of microseconds the device will wait
                                  before timing out a Read or a Write operation.
  @param  Parity                  If applicable, this is the EFI_PARITY_TYPE that is computer or checked
                                  as each character is transmitted or received. If the device does not
                                  support parity, the value is the default parity value.
  @param  DataBits                The number of data bits in each character
  @param  StopBits                If applicable, the EFI_STOP_BITS_TYPE number of stop bits per character.
                                  If the device does not support stop bits, the value is the default stop
                                  bit value.

  @retval EFI_SUCCESS             All attributes were set correctly on the serial device.
  @retval EFI_INVALID_PARAMETERS  One or more of the attributes has an unsupported value.

**/
RETURN_STATUS
EFIAPI
SerialPortSetAttributes (
  IN UINT64              BaudRate,
  IN UINT32              ReceiveFifoDepth,
  IN UINT32              Timeout,
  IN EFI_PARITY_TYPE     Parity,
  IN UINT8               DataBits,
  IN EFI_STOP_BITS_TYPE  StopBits
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Set the serial device control bits.

  @param  Control                 Control bits which are to be set on the serial device.

  @retval EFI_SUCCESS             The new control bits were set on the serial device.
  @retval EFI_UNSUPPORTED         The serial device does not support this operation.
  @retval EFI_DEVICE_ERROR        The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortSetControl (
  IN UINT32                  Control
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get the serial device control bits.

  @param  Control                 Control signals read from the serial device.

  @retval EFI_SUCCESS             The control bits were read from the serial device.
  @retval EFI_DEVICE_ERROR        The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortGetControl (
  OUT UINT32                  *Control
  )
{
    
    if (SerialPortPoll ()) {
        // If a character is pending don't set EFI_SERIAL_INPUT_BUFFER_EMPTY
        *Control = EFI_SERIAL_OUTPUT_BUFFER_EMPTY;
    } else {
        *Control = EFI_SERIAL_INPUT_BUFFER_EMPTY | EFI_SERIAL_OUTPUT_BUFFER_EMPTY;
    }
    return EFI_SUCCESS;
  //return EFI_UNSUPPORTED;
}

