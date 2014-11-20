/** @file
  This file initializes XGene USB controller and implements PCIE emulation for
  working with XHCI driver.

  Copyright (c) 2013, AMCC Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "UsbController.h"

extern INTN xgene_xhci_init(UINT64 serdes_base, UINT64 xhci_base,
		UINTN irq, UINTN cid, UINT32 clk2_sel, UINT32 ovrcur_en,
		UINT32 ovrcur_ivrt);

typedef struct {
  ACPI_HID_DEVICE_PATH      AcpiDevicePath;
  PCI_DEVICE_PATH           PciDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  EndDevicePath;
} EFI_PCI_IO_DEVICE_PATH;

typedef struct {
  UINT32                  Signature;
  EFI_PCI_IO_DEVICE_PATH  DevicePath;
  EFI_PCI_IO_PROTOCOL     PciIoProtocol;
  PCI_TYPE00              *ConfigSpace;
  PCI_ROOT_BRIDGE         RootBridge;
  UINTN                   Segment;
} EFI_PCI_IO_PRIVATE_DATA;

#define EFI_PCIUSB_PRIVATE_DATA_SIGNATURE     SIGNATURE_32('p', 'u', 's', 'b')
#define EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(a)  CR(a, EFI_PCI_IO_PRIVATE_DATA, PciIoProtocol, EFI_PCIUSB_PRIVATE_DATA_SIGNATURE)

EFI_PCI_IO_DEVICE_PATH PciIoDevicePathTemplate = 
{
  /* Port 0 */
  {
    { ACPI_DEVICE_PATH, ACPI_DP,  { sizeof (ACPI_HID_DEVICE_PATH), 0} },
    EISA_PNP_ID(0x0A03),  // HID
    0                     // UID
  },
  {
    { HARDWARE_DEVICE_PATH, HW_PCI_DP, { sizeof (PCI_DEVICE_PATH), 0} },
    0,
    0
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { sizeof (EFI_DEVICE_PATH_PROTOCOL), 0} }
};


EFI_STATUS
PciIoPollMem (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN  UINT8                        BarIndex,
  IN  UINT64                       Offset,
  IN  UINT64                       Mask,
  IN  UINT64                       Value,
  IN  UINT64                       Delay,
  OUT UINT64                       *Result
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoPollIo (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN  UINT8                        BarIndex,
  IN  UINT64                       Offset,
  IN  UINT64                       Mask,
  IN  UINT64                       Value,
  IN  UINT64                       Delay,
  OUT UINT64                       *Result
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoMemRead (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT8                        BarIndex,
  IN     UINT64                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  EFI_PCI_IO_PRIVATE_DATA *Private = EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(This);

  return PciRootBridgeIoMemRead (&Private->RootBridge.Io, 
                                (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH) Width,
                                Private->ConfigSpace->Device.Bar[0] + Offset,
                                Count,
                                Buffer
                                );
}

EFI_STATUS
PciIoMemWrite (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT8                        BarIndex,
  IN     UINT64                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  EFI_PCI_IO_PRIVATE_DATA *Private = EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(This);

  return PciRootBridgeIoMemWrite (&Private->RootBridge.Io, 
                                 (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH) Width,
                                 Private->ConfigSpace->Device.Bar[0] + Offset,
                                 Count,
                                 Buffer
                                 );
}

EFI_STATUS
PciIoIoRead (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT8                        BarIndex,
  IN     UINT64                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoIoWrite (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT8                        BarIndex,
  IN     UINT64                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoPciRead (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT32                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  EFI_PCI_IO_PRIVATE_DATA *Private = EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(This);

  return PciRootBridgeIoMemRW ((EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)Width, 
                               Count, 
                               TRUE, 
                               (PTR)(UINTN)Buffer, 
                               TRUE, 
                               (PTR)(UINTN)(((UINT8 *)Private->ConfigSpace) + Offset)
                              );
}

EFI_STATUS
PciIoPciWrite (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT32                       Offset,
  IN     UINTN                        Count,
  IN OUT VOID                         *Buffer
  )
{
  EFI_PCI_IO_PRIVATE_DATA *Private = EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(This);

  return PciRootBridgeIoMemRW ((EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH) Width, 
                               Count, 
                               TRUE, 
                               (PTR)(UINTN)(((UINT8 *)Private->ConfigSpace) + Offset), 
                               TRUE, 
                               (PTR)(UINTN)Buffer
                               );
}

EFI_STATUS
PciIoCopyMem (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN     UINT8                        DestBarIndex,
  IN     UINT64                       DestOffset,
  IN     UINT8                        SrcBarIndex,
  IN     UINT64                       SrcOffset,
  IN     UINTN                        Count
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoMap (
  IN EFI_PCI_IO_PROTOCOL                *This,
  IN     EFI_PCI_IO_PROTOCOL_OPERATION  Operation,
  IN     VOID                           *HostAddress,
  IN OUT UINTN                          *NumberOfBytes,
  OUT    EFI_PHYSICAL_ADDRESS           *DeviceAddress,
  OUT    VOID                           **Mapping
  )
{
  DMA_MAP_OPERATION   DmaOperation;

  if (Operation == EfiPciIoOperationBusMasterRead) {
    DmaOperation = MapOperationBusMasterRead;
  } else if (Operation == EfiPciIoOperationBusMasterWrite) {
    DmaOperation = MapOperationBusMasterWrite;
  } else if (Operation == EfiPciIoOperationBusMasterCommonBuffer) {
    DmaOperation = MapOperationBusMasterCommonBuffer;
  } else {
    return EFI_INVALID_PARAMETER;
  }
  return DmaMap (DmaOperation, HostAddress, NumberOfBytes, DeviceAddress, Mapping);
}

EFI_STATUS
PciIoUnmap (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  VOID                         *Mapping
  )
{
  return DmaUnmap (Mapping);
}

EFI_STATUS
PciIoAllocateBuffer (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  EFI_ALLOCATE_TYPE            Type,
  IN  EFI_MEMORY_TYPE              MemoryType,
  IN  UINTN                        Pages,
  OUT VOID                         **HostAddress,
  IN  UINT64                       Attributes
  )
{
  if (Attributes & EFI_PCI_ATTRIBUTE_INVALID_FOR_ALLOCATE_BUFFER) {
    // Check this
    return EFI_UNSUPPORTED;
  }

  return DmaAllocateBuffer (MemoryType, Pages, HostAddress);
}


EFI_STATUS
PciIoFreeBuffer (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  UINTN                        Pages,
  IN  VOID                         *HostAddress
  )
{
  return DmaFreeBuffer (Pages, HostAddress);
}


EFI_STATUS
PciIoFlush (
  IN EFI_PCI_IO_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
PciIoGetLocation (
  IN EFI_PCI_IO_PROTOCOL          *This,
  OUT UINTN                       *SegmentNumber,
  OUT UINTN                       *BusNumber,
  OUT UINTN                       *DeviceNumber,
  OUT UINTN                       *FunctionNumber
  )
{
  EFI_PCI_IO_PRIVATE_DATA *Private = EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(This);

  if (SegmentNumber != NULL) {
    *SegmentNumber = Private->Segment;
  }

  if (BusNumber != NULL) {
    *BusNumber = 0xff;
  }

  if (DeviceNumber != NULL) {
    *DeviceNumber = 0;
  }

  if (FunctionNumber != NULL) {
    *FunctionNumber = 0;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
PciIoAttributes (
  IN EFI_PCI_IO_PROTOCOL                       *This,
  IN  EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION  Operation,
  IN  UINT64                                   Attributes,
  OUT UINT64                                   *Result OPTIONAL
  )
{
  switch (Operation) {
  case EfiPciIoAttributeOperationGet:
  case EfiPciIoAttributeOperationSupported:
    if (Result == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    // We are not a real PCI device so just say things we kind of do
    *Result = EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER | EFI_PCI_DEVICE_ENABLE;
    break;

  case EfiPciIoAttributeOperationSet:
  case EfiPciIoAttributeOperationEnable:
  case EfiPciIoAttributeOperationDisable:
    // Since we are not a real PCI device no enable/set or disable operations exist.
    return EFI_SUCCESS;
    
  default:
  ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  };
  return EFI_SUCCESS;
}

EFI_STATUS
PciIoGetBarAttributes (
  IN EFI_PCI_IO_PROTOCOL             *This,
  IN  UINT8                          BarIndex,
  OUT UINT64                         *Supports, OPTIONAL
  OUT VOID                           **Resources OPTIONAL
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_STATUS
PciIoSetBarAttributes (
  IN EFI_PCI_IO_PROTOCOL              *This,
  IN     UINT64                       Attributes,
  IN     UINT8                        BarIndex,
  IN OUT UINT64                       *Offset,
  IN OUT UINT64                       *Length
  )
{
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

EFI_PCI_IO_PROTOCOL PciIoTemplate = 
{
  PciIoPollMem,
  PciIoPollIo,
  { PciIoMemRead, PciIoMemWrite},
  { PciIoIoRead, PciIoIoWrite},
  { PciIoPciRead, PciIoPciWrite},
  PciIoCopyMem,
  PciIoMap,
  PciIoUnmap,
  PciIoAllocateBuffer,
  PciIoFreeBuffer,
  PciIoFlush,
  PciIoGetLocation,
  PciIoAttributes,
  PciIoGetBarAttributes,
  PciIoSetBarAttributes,
  0,
  0
};


EFI_STATUS
EFIAPI
PciUsbEmulationEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS              Status = 0;
  EFI_HANDLE              Handle;
  EFI_PCI_IO_PRIVATE_DATA *Private;
  INTN    Cid;
  UINT64  csr_base;
  UINT64  xhci_base;
  INTN    irq;
  INTN    clk_sel;
  INTN    ovrcur_en;
  INTN    ovrcur_ivrt;

  for (Cid = 0; Cid < 2; Cid++) {
	if (!((PcdGet32(PcdUsbControllerMask) >> Cid) & 0x1))
		continue;

    // Get parameters
    switch (Cid) {
    case 0:
      if (PcdGet64(PcdXHCI1RegisterBase) == 0)
        continue;
      csr_base    = PcdGet64(PcdUsb1CsrRegisterBase);
      xhci_base   = PcdGet64(PcdXHCI1RegisterBase);
      irq         = PcdGet32(PcdUsb1Irq);
      clk_sel     = 0;
      ovrcur_en   = PcdGet32(PcdUsb1OvrcurEn);
      ovrcur_ivrt = PcdGet32(PcdUsb1OvrcurIvrt);
      break;
    case 1:
      if (PcdGet64(PcdXHCI2RegisterBase) == 0)
        continue;
      csr_base    = PcdGet64(PcdUsb2CsrRegisterBase);
      xhci_base   = PcdGet64(PcdXHCI2RegisterBase);
      irq         = PcdGet32(PcdUsb2Irq);
      clk_sel     = 0xB;
      ovrcur_en   = PcdGet32(PcdUsb2OvrcurEn);
      ovrcur_ivrt = PcdGet32(PcdUsb2OvrcurIvrt);
      break;
    default:
      continue;
    }

    DEBUG((EFI_D_BLKIO, "PciUsbEmulationEntryPoint started.\n"));
    /* Configure USB host */
	if (xgene_xhci_init(csr_base, xhci_base, irq, Cid, clk_sel, ovrcur_en,
			ovrcur_ivrt)) {
		DEBUG((EFI_D_ERROR, "USB%d Initialization failed\n", Cid));
		Status = EFI_DEVICE_ERROR;
		return Status;
	}

    // Create a private structure
    Private = AllocatePool(sizeof(EFI_PCI_IO_PRIVATE_DATA));
    if (Private == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      return Status;
    }
    Private->Signature              = EFI_PCIUSB_PRIVATE_DATA_SIGNATURE;  // Fill in signature
    Private->RootBridge.Signature   = PCI_ROOT_BRIDGE_SIGNATURE;          // Fake Root Bridge structure needs a signature too
    Private->RootBridge.MemoryStart = xhci_base;                          // Get the USB capability register base
    Private->Segment                = 0;                                  // Default to segment zero

    // Calculate the total size of the USB registers.
    Private->RootBridge.MemorySize = 0x10000;

    // Create fake PCI config space.
    Private->ConfigSpace = AllocateZeroPool(sizeof(PCI_TYPE00));
    if (Private->ConfigSpace == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      FreePool(Private);
      return Status;
    }

    // Configure PCI config space
    Private->ConfigSpace->Hdr.VendorId = 0x10E8;   // AMCC
    Private->ConfigSpace->Hdr.DeviceId = 0x3530;
    Private->ConfigSpace->Hdr.ClassCode[0] = 0x30; // XHCI
    Private->ConfigSpace->Hdr.ClassCode[1] = 0x03; // USB controller
    Private->ConfigSpace->Hdr.ClassCode[2] = 0x0C; // Serial Bus Controller
    Private->ConfigSpace->Device.Bar[0] = Private->RootBridge.MemoryStart;

    Handle = NULL;

    // Unique device path.
    CopyMem(&Private->DevicePath, &PciIoDevicePathTemplate, sizeof(PciIoDevicePathTemplate));
    Private->DevicePath.AcpiDevicePath.UID = 8 + Cid;
  
    // Copy protocol structure
    CopyMem(&Private->PciIoProtocol, &PciIoTemplate, sizeof(PciIoTemplate));

    Status = gBS->InstallMultipleProtocolInterfaces(&Handle,
                                                    &gEfiPciIoProtocolGuid,       &Private->PciIoProtocol,
                                                    &gEfiDevicePathProtocolGuid,  &Private->DevicePath,
                                                    NULL);

    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "PciUsbEmulationEntryPoint InstallMultipleProtocolInterfaces() failed.\n"));
    } else {
      DEBUG((EFI_D_BLKIO, "PciUsbEmulationEntryPoint InstallMultipleProtocolInterfaces() successful.\n"));
    }

    if (EFI_ERROR (Status)) {
      if(Private != NULL) {
        if(Private->ConfigSpace != NULL)
          FreePool(Private->ConfigSpace);
        FreePool(Private);
      }
    }
  }

  return Status;
}

