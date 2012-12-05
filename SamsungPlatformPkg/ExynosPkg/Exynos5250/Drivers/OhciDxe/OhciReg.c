/** @file

  The OHCI register operation routines.

Copyright (c) 2007, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "Ohci.h"


/**
  Read a OHCI register.

  @param  PciIo        The EFI_PCI_IO_PROTOCOL to use.
  @param  Offset       Register offset to USB_BAR_INDEX.

  @return Content of register.

**/
UINT32
OhciReadReg (
  IN USB_HC_DEV              *Ohc,
  IN UINT32                  Offset
  )
{
  UINT32                  Data;
  EFI_STATUS              Status;

  Status = Ohc->PciIo->Mem.Read (
                             Ohc->PciIo,
                             EfiPciIoWidthUint32,
                             OHC_BAR_INDEX,
                             (UINT64) (Offset),
                             1,
                             &Data
                             );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "OhcReadOpReg: Pci Io Read error - %r at %d\n", Status, Offset));
    Data = 0xFFFF;
  }

  return Data;
}


/**
  Write data to OHCI register.

  @param  PciIo        The EFI_PCI_IO_PROTOCOL to use.
  @param  Offset       Register offset to USB_BAR_INDEX.
  @param  Data         Data to write.

**/
VOID
OhciWriteReg (
  IN USB_HC_DEV              *Ohc,
  IN UINT32                  Offset,
  IN UINT32                  Data
  )
{
  EFI_STATUS              Status;

  Status = Ohc->PciIo->Mem.Write (
                             Ohc->PciIo,
                             EfiPciIoWidthUint32,
                             OHC_BAR_INDEX,
                             (UINT64) (Offset),
                             1,
                             &Data
                             );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "OhcWriteOpReg: Pci Io Write error: %r at %d\n", Status, Offset));
  }
}


/**
  Set a bit of the OHCI Register.

  @param  PciIo        The EFI_PCI_IO_PROTOCOL to use.
  @param  Offset       Register offset to USB_BAR_INDEX.
  @param  Bit          The bit to set.

**/
VOID
OhciSetRegBit (
  IN USB_HC_DEV              *Ohc,
  IN UINT32                  Offset,
  IN UINT16                  Bit
  )
{
  UINT16  Data;

  Data = OhciReadReg (Ohc, Offset);
  Data = (UINT16) (Data |Bit);
  OhciWriteReg (Ohc, Offset, Data);
}


/**
  Clear a bit of the OHCI Register.

  @param  PciIo        The PCI_IO protocol to access the PCI.
  @param  Offset       Register offset to USB_BAR_INDEX.
  @param  Bit          The bit to clear.

**/
VOID
OhciClearRegBit (
  IN USB_HC_DEV              *Ohc,
  IN UINT32                  Offset,
  IN UINT16                  Bit
  )
{
  UINT16  Data;

  Data = OhciReadReg (Ohc, Offset);
  Data = (UINT16) (Data & ~Bit);
  OhciWriteReg (Ohc, Offset, Data);
}


/**
  Clear all the interrutp status bits, these bits
  are Write-Clean.

  @param  Ohc          The OHCI device.

**/
VOID
OhciAckAllInterrupt (
  IN  USB_HC_DEV          *Ohc
  )
{
  //OhciWriteReg (Ohc, USBSTS_OFFSET, 0x3F);

  //
  // If current HC is halted, re-enable it. Host Controller Process Error
  // is a temporary error status.
  //
  if (!OhciIsHcWorking (Ohc)) {
    DEBUG ((EFI_D_ERROR, "OhciAckAllInterrupt: re-enable the OHCI from system error\n"));
    Ohc->Usb2Hc.SetState (&Ohc->Usb2Hc, EfiUsbHcStateOperational);
  }
}


/**
  Stop the host controller.

  @param  Ohc          The OHCI device.
  @param  Timeout      Max time allowed.

  @retval EFI_SUCCESS  The host controller is stopped.
  @retval EFI_TIMEOUT  Failed to stop the host controller.

**/
EFI_STATUS
OhciStopHc (
  IN USB_HC_DEV        *Ohc,
  IN UINTN             Timeout
  )
{
#if 1
/*
	UINT32                UsbCtr;
	UsbCtr = OhciReadReg(Ohc, HC_CONTROL_OFFSET);
	UsbCtr &= (1<<9); //all except of RWC is clear
	OhciWriteReg(Ohc, HC_CONTROL_OFFSET, UsbCtr);
*/
	return EFI_SUCCESS;
#else
	UINT16                UsbSts;
  UINTN                 Index;
  OhciClearRegBit (Ohc, USBCMD_OFFSET, USBCMD_RS);

  //
  // ensure the HC is in halt status after send the stop command
  // Timeout is in us unit.
  //
  for (Index = 0; Index < (Timeout / 50) + 1; Index++) {
    UsbSts = OhciReadReg (Ohc, USBSTS_OFFSET);

    if ((UsbSts & USBSTS_HCH) == USBSTS_HCH) {
      return EFI_SUCCESS;
    }

    gBS->Stall (50);
  }

  return EFI_TIMEOUT;
#endif
}


/**
  Check whether the host controller operates well.

  @param  PciIo        The PCI_IO protocol to use.

  @retval TRUE         Host controller is working.
  @retval FALSE        Host controller is halted or system error.

**/
BOOLEAN
OhciIsHcWorking (
  IN USB_HC_DEV        *Ohc
  )
{
  UINT16                UsbSts;
	/*
  UsbSts = OhciReadReg (Ohc, USBSTS_OFFSET);

  if ((UsbSts & (USBSTS_HCPE | USBSTS_HSE | USBSTS_HCH)) != 0) {
    DEBUG ((EFI_D_ERROR, "OhciIsHcWorking: current USB state is %x\n", UsbSts));
    return FALSE;
  }
	*/
  return TRUE;
}


/**
  Set the OHCI frame list base address. It can't use
  OhciWriteReg which access memory in UINT16.

  @param  PciIo        The EFI_PCI_IO_PROTOCOL to use.
  @param  Addr         Address to set.

**/
/*
VOID
OhciSetFrameListBaseAddr (
  IN USB_HC_DEV              *Ohc,
  IN VOID                    *Addr
  )
{
  EFI_STATUS              Status;
  UINT32                  Data;

  Data = (UINT32) ((UINTN) Addr & 0xFFFFF000);

  Status = PciIo->Io.Write (
                       PciIo,
                       EfiPciIoWidthUint32,
                       USB_BAR_INDEX,
                       (UINT64) USB_FRAME_BASE_OFFSET,
                       1,
                       &Data
                       );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "OhciSetFrameListBaseAddr: PciIo Io.Write error: %r\n", Status));
  }
}
*/

/**
  Disable USB Emulation.

  @param  PciIo        The EFI_PCI_IO_PROTOCOL protocol to use.

**/

/*
VOID
OhciTurnOffUsbEmulation (
  IN EFI_PCI_IO_PROTOCOL     *PciIo
  )
{
  UINT16            Command;

  Command = 0;

  PciIo->Pci.Write (
               PciIo,
               EfiPciIoWidthUint16,
               USB_EMULATION_OFFSET,
               1,
               &Command
               );
}*/
