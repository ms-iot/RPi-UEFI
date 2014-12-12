/**
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

#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#include "DWUart.h"

UINTN GetSerialPortBase(VOID)
{
  return PcdGet64(PcdSerialRegisterBase);
}

UINTN GetSerialPortBaudRate(VOID)
{
  return PcdGet64(PcdUartDefaultBaudRate);
}

UINT8 GetSerialPortPolarity(VOID)
{
  return PcdGet8(PcdUartDefaultParity);
}

#if 0
static UINT8 GetSerialPortDataBits(VOID)
{
  return PcdGet8(PcdUartDefaultDataBits);
}
#endif

UINT8 GetSerialPortStopBits(VOID)
{
  return PcdGet8(PcdUartDefaultStopBits);
}

/*

  Programmed hardware of Serial port.

  @return    Always return RETURN_UNSUPPORTED.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
  return DWUartInitializePort( GetSerialPortBaudRate(),
                (EFI_PARITY_TYPE) GetSerialPortPolarity(),
                PcdGet8(PcdUartDefaultDataBits),
                (EFI_STOP_BITS_TYPE) GetSerialPortStopBits());
}

/**
  Write data to serial device.

  @param  Buffer           Point of data buffer which need to be written.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Write data failed.
  @retval !0               Actual number of bytes written to serial device.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
  )
{
  UINTN ByteCount = 0;
  ByteCount = DWUartWrite((UINTN) GetSerialPortBase(), Buffer, NumberOfBytes);
  return ((ByteCount < NumberOfBytes) ? EFI_ERROR(EFI_DEVICE_ERROR) : 
                                        ByteCount);
}

/**
  Read data from serial device and save the data in buffer.

  @param  Buffer           Point of data buffer which need to be written.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Read data failed.
  @retval !0               Actual number of bytes read from serial device.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
)
{
  return DWUartRead((UINTN) GetSerialPortBase(), Buffer, NumberOfBytes);
}

/**
  Check to see if any data is available to be read from the debug device.

  @retval TRUE       At least one byte of data is avaiable to be read
  @retval FALSE      No data is avaiable to be read

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  return DWUartPoll((UINTN) GetSerialPortBase(), DW_OPER_READ);
}
