/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "PciEmulation.h"
#include "Exynos5_USB2Phy.h"
#include "Exynos5_USB3Phy.h"
#include "Exynos5_USB3Drd.h"

#define HOST_CONTROLLER_OPERATION_REG_SIZE  0x44
#define USBDRD_CONTROLLER_OPERATION_REG_SIZE 0x400

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

#define EFI_PCI_IO_PRIVATE_DATA_SIGNATURE     SIGNATURE_32('p', 'c', 'i', 'o')
#define EFI_PCI_IO_PRIVATE_DATA_FROM_THIS(a)  CR(a, EFI_PCI_IO_PRIVATE_DATA, PciIoProtocol, EFI_PCI_IO_PRIVATE_DATA_SIGNATURE)

EFI_PCI_IO_DEVICE_PATH PciIoDevicePathTemplateUSB2 =
{
  {
    { ACPI_DEVICE_PATH, ACPI_DP, sizeof (ACPI_HID_DEVICE_PATH), 0},
    EISA_PNP_ID(0x0A03),  // HID
    0                     // UID
  },
  {
    { HARDWARE_DEVICE_PATH, HW_PCI_DP, sizeof (PCI_DEVICE_PATH), 0},
    0,
    0
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, sizeof (EFI_DEVICE_PATH_PROTOCOL), 0}
};

EFI_PCI_IO_DEVICE_PATH PciIoDevicePathTemplateUSB3 =
{
  {
    { ACPI_DEVICE_PATH, ACPI_DP, sizeof (ACPI_HID_DEVICE_PATH), 0},
    EISA_PNP_ID(0x0A03),  // HID
    1                     // UID
  },
  {
    { HARDWARE_DEVICE_PATH, HW_PCI_DP, sizeof (PCI_DEVICE_PATH), 0},
    0,
    1
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, sizeof (EFI_DEVICE_PATH_PROTOCOL), 0}
};

EFI_PCI_IO_DEVICE_PATH PciIoDevicePathTemplateUSB1 =
{
  {
    { ACPI_DEVICE_PATH, ACPI_DP, sizeof (ACPI_HID_DEVICE_PATH), 0},
    EISA_PNP_ID(0x0A03),  // HID
    2                     // UID
  },
  {
    { HARDWARE_DEVICE_PATH, HW_PCI_DP, sizeof (PCI_DEVICE_PATH), 0},
    0,
    2
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, sizeof (EFI_DEVICE_PATH_PROTOCOL), 0}
};


STATIC
VOID
ConfigureUSBHost (
  VOID
  )
{
    DEBUG((EFI_D_INFO, "++%a:%d\n", __func__, __LINE__));

    exynos5_usb_phy20_init();
#if defined(XHCI_SUPPORT)
    exynos5_usb_phy30_init();
    exynos_xhci_change_mode();
    exynos_xhci_phy_set();
#endif

    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
}


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

    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
  return PciRootBridgeIoMemRead (&Private->RootBridge.Io,
                                (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH) Width,
                                Private->ConfigSpace->Device.Bar[BarIndex] + Offset,
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

    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
  return PciRootBridgeIoMemWrite (&Private->RootBridge.Io,
                                 (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH) Width,
                                 Private->ConfigSpace->Device.Bar[BarIndex] + Offset,
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

    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
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

    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
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

    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
  if (Operation == EfiPciIoOperationBusMasterRead) {
    DmaOperation = MapOperationBusMasterRead;
  } else if (Operation == EfiPciIoOperationBusMasterWrite) {
    DmaOperation = MapOperationBusMasterWrite;
  } else if (Operation == EfiPciIoOperationBusMasterCommonBuffer) {
    DmaOperation = MapOperationBusMasterCommonBuffer;
  } else {
    return EFI_INVALID_PARAMETER;
  }
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
  return DmaMap (DmaOperation, HostAddress, NumberOfBytes, DeviceAddress, Mapping);
}

EFI_STATUS
PciIoUnmap (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  VOID                         *Mapping
  )
{
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
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
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
  if (Attributes & EFI_PCI_ATTRIBUTE_INVALID_FOR_ALLOCATE_BUFFER) {
    // Check this
    return EFI_UNSUPPORTED;
  }

    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
  return DmaAllocateBuffer (MemoryType, Pages, HostAddress);
}


EFI_STATUS
PciIoFreeBuffer (
  IN EFI_PCI_IO_PROTOCOL           *This,
  IN  UINTN                        Pages,
  IN  VOID                         *HostAddress
  )
{
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
  return DmaFreeBuffer (Pages, HostAddress);
}


EFI_STATUS
PciIoFlush (
  IN EFI_PCI_IO_PROTOCOL  *This
  )
{
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
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
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
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

    DEBUG((EFI_D_INFO, "--%a:%d\n", __FUNCTION__, __LINE__));
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
    DEBUG((EFI_D_INFO, "++%a:%d\n", __FUNCTION__, __LINE__));
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
    DEBUG((EFI_D_INFO, "--%a(Set:1, Enable:2, Disable:3)(%d):%d\n", __FUNCTION__, Operation,__LINE__));
    return EFI_SUCCESS;

  default:
  ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  };
    DEBUG((EFI_D_INFO, "--%a(Get:0, Supported:4)(%d):%d\n", __FUNCTION__, Operation,__LINE__));
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
  PciIoMemRead,
  PciIoMemWrite,
  PciIoIoRead,
  PciIoIoWrite,
  PciIoPciRead,
  PciIoPciWrite,
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
PciEmulationEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              HandleUSB2;
  EFI_PCI_IO_PRIVATE_DATA *PrivateUSB2;
#if defined(OHCI_SUPPORT)
  EFI_HANDLE              HandleUSB1;
  EFI_PCI_IO_PRIVATE_DATA *PrivateUSB1;
#endif
#if defined(XHCI_SUPPORT)
  EFI_HANDLE              HandleUSB3;
  EFI_PCI_IO_PRIVATE_DATA *PrivateUSB3;
#endif
  UINT8                   CapabilityLength;
  UINT8                   PhysicalPorts;
#if defined(OHCI_SUPPORT)
#else
  UINTN                   Count;
#endif

  //Configure USB host for Exynos.
  ConfigureUSBHost();

  // Create a private structure for USB 2.0
  PrivateUSB2 = AllocatePool(sizeof(EFI_PCI_IO_PRIVATE_DATA));
  if (PrivateUSB2 == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    return Status;
  }
  PrivateUSB2->Signature              = EFI_PCI_IO_PRIVATE_DATA_SIGNATURE;  // Fill in signature
  PrivateUSB2->RootBridge.Signature   = PCI_ROOT_BRIDGE_SIGNATURE;          // Fake Root Bridge structure needs a signature too
  PrivateUSB2->RootBridge.MemoryStart = USB_EHCI_HCCAPBASE;                 // Get the USB capability register base
  PrivateUSB2->Segment                = 0;                                  // Default to segment zero


#if defined(XHCI_SUPPORT)
  // Create a private structure for USB 3.0
  PrivateUSB3 = AllocatePool(sizeof(EFI_PCI_IO_PRIVATE_DATA));
  if (PrivateUSB3 == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    return Status;
  }
  PrivateUSB3->Signature              = EFI_PCI_IO_PRIVATE_DATA_SIGNATURE;  // Fill in signature
  PrivateUSB3->RootBridge.Signature   = PCI_ROOT_BRIDGE_SIGNATURE;          // Fake Root Bridge structure needs a signature too
  PrivateUSB3->RootBridge.MemoryStart = USB_XHCI_HCCAPBASE;                 // Get the USB capability register base
  PrivateUSB3->Segment                = 0;                                  // Default to segment zero
#endif

#if defined(OHCI_SUPPORT)
  // Create a private structure for USB 1.0
  PrivateUSB1 = AllocatePool(sizeof(EFI_PCI_IO_PRIVATE_DATA));
  if (PrivateUSB1 == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    return Status;
  }
  PrivateUSB1->Signature              = EFI_PCI_IO_PRIVATE_DATA_SIGNATURE;  // Fill in signature
  PrivateUSB1->RootBridge.Signature   = PCI_ROOT_BRIDGE_SIGNATURE;          // Fake Root Bridge structure needs a signature too
  PrivateUSB1->RootBridge.MemoryStart = USB_OHCI_HCCAPBASE;                 // Get the USB capability register base
  PrivateUSB1->Segment                = 0;                                  // Default to segment zero
#endif

	// USB 2.0
  // Find out the capability register length and number of physical ports.
  CapabilityLength = MmioRead8(PrivateUSB2->RootBridge.MemoryStart);
  PhysicalPorts    = (MmioRead32 (PrivateUSB2->RootBridge.MemoryStart + 0x4)) & 0x0000000F;

  // Calculate the total size of the USB registers.
  PrivateUSB2->RootBridge.MemorySize = CapabilityLength + (HOST_CONTROLLER_OPERATION_REG_SIZE + ((4 * PhysicalPorts) - 1));

  // Enable Port Power bit in Port status and control registers in EHCI register space.
  // Port Power Control (PPC) bit in the HCSPARAMS register is already set which indicates
  // host controller implementation includes port power control.
  for (Count = 0; Count < PhysicalPorts; Count++) {
    MmioOr32 ((PrivateUSB2->RootBridge.MemoryStart + CapabilityLength + HOST_CONTROLLER_OPERATION_REG_SIZE + 4*Count), 0x00001000);
  }

#if defined(XHCI_SUPPORT)
	// USB 3.0
  // Find out the capability register length and number of physical ports.
  CapabilityLength = MmioRead8(PrivateUSB3->RootBridge.MemoryStart);
  PhysicalPorts    = ((MmioRead32 (PrivateUSB3->RootBridge.MemoryStart + 0x4)) & 0xFF000000) >> 24;

  // Calculate the total size of the USB registers.
	//                                      0x20                   0x400                            0x10
  //Private->RootBridge.MemorySize = CapabilityLength + (USBDRD_CONTROLLER_OPERATION_REG_SIZE + (0x10 * (PhysicalPorts - 1)));
  PrivateUSB3->RootBridge.MemorySize = 0x100000;

  for (Count = 0; Count < PhysicalPorts; Count++) {
    MmioOr32 (PrivateUSB3->RootBridge.MemoryStart + CapabilityLength + USBDRD_CONTROLLER_OPERATION_REG_SIZE + (0x10 * Count), 0x00000200);
  }
#endif

#if defined(OHCI_SUPPORT)
  CapabilityLength = 0;
  PhysicalPorts = 3;
  PrivateUSB1->RootBridge.MemorySize = 0x60;
#endif


	// USB 2.0
  // Create fake PCI config space.
  PrivateUSB2->ConfigSpace = AllocateZeroPool(sizeof(PCI_TYPE00));
  if (PrivateUSB2->ConfigSpace == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    FreePool(PrivateUSB2);
    return Status;
  }

  // Configure PCI config space
  PrivateUSB2->ConfigSpace->Hdr.VendorId = 0x3530;
  PrivateUSB2->ConfigSpace->Hdr.DeviceId = 0x3530;
  PrivateUSB2->ConfigSpace->Hdr.ClassCode[0] = 0x20;
  PrivateUSB2->ConfigSpace->Hdr.ClassCode[1] = 0x03;
  PrivateUSB2->ConfigSpace->Hdr.ClassCode[2] = 0x0C;
  PrivateUSB2->ConfigSpace->Device.Bar[0] = PrivateUSB2->RootBridge.MemoryStart;

#if defined(XHCI_SUPPORT)
	// USB 3.0
  // Create fake PCI config space.
  PrivateUSB3->ConfigSpace = AllocateZeroPool(sizeof(PCI_TYPE00));
  if (PrivateUSB3->ConfigSpace == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    FreePool(PrivateUSB3);
    return Status;
  }

  // Configure PCI config space
  PrivateUSB3->ConfigSpace->Hdr.VendorId = 0x3530;
  PrivateUSB3->ConfigSpace->Hdr.DeviceId = 0x3530;
  PrivateUSB3->ConfigSpace->Hdr.ClassCode[0] = 0x30;	/* 0x20 : EHIC, 0x30 : XHCI */
  PrivateUSB3->ConfigSpace->Hdr.ClassCode[1] = 0x03;
  PrivateUSB3->ConfigSpace->Hdr.ClassCode[2] = 0x0C;
  PrivateUSB3->ConfigSpace->Device.Bar[0] = PrivateUSB3->RootBridge.MemoryStart;
#endif

#if defined(OHCI_SUPPORT)
	// USB 1.0
  // Create fake PCI config space.
  PrivateUSB1->ConfigSpace = AllocateZeroPool(sizeof(PCI_TYPE00));
  if (PrivateUSB1->ConfigSpace == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    FreePool(PrivateUSB1);
    return Status;
  }

  // Configure PCI config space
  PrivateUSB1->ConfigSpace->Hdr.VendorId = 0x3530;
  PrivateUSB1->ConfigSpace->Hdr.DeviceId = 0x3530;
  PrivateUSB1->ConfigSpace->Hdr.ClassCode[0] = 0x10;
  PrivateUSB1->ConfigSpace->Hdr.ClassCode[1] = 0x03;
  PrivateUSB1->ConfigSpace->Hdr.ClassCode[2] = 0x0C;
  PrivateUSB1->ConfigSpace->Device.Bar[0] = PrivateUSB2->RootBridge.MemoryStart;
#endif


  HandleUSB2 = NULL;

	// USB 2.0
  // Unique device path.
  CopyMem(&PrivateUSB2->DevicePath, &PciIoDevicePathTemplateUSB2, sizeof(PciIoDevicePathTemplateUSB2));
  PrivateUSB2->DevicePath.AcpiDevicePath.UID = 0;
  // Copy protocol structure
  CopyMem(&PrivateUSB2->PciIoProtocol, &PciIoTemplate, sizeof(PciIoTemplate));

  Status = gBS->InstallMultipleProtocolInterfaces(&HandleUSB2,
                                                  &gEfiPciIoProtocolGuid,       &PrivateUSB2->PciIoProtocol,
                                                  &gEfiDevicePathProtocolGuid,  &PrivateUSB2->DevicePath,
                                                  NULL);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "PciEmulationEntryPoint InstallMultipleProtocolInterfaces() failed.\n"));
  }

#if defined(XHCI_SUPPORT)
  HandleUSB3 = NULL;

	// USB 3.0
  // Unique device path.
  CopyMem(&PrivateUSB3->DevicePath, &PciIoDevicePathTemplateUSB3, sizeof(PciIoDevicePathTemplateUSB3));
  PrivateUSB3->DevicePath.AcpiDevicePath.UID = 1;
  // Copy protocol structure
  CopyMem(&PrivateUSB3->PciIoProtocol, &PciIoTemplate, sizeof(PciIoTemplate));


  Status = gBS->InstallMultipleProtocolInterfaces(&HandleUSB3,
                                                  &gEfiPciIoProtocolGuid,       &PrivateUSB3->PciIoProtocol,
                                                  &gEfiDevicePathProtocolGuid,  &PrivateUSB3->DevicePath,
                                                  NULL);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "PciEmulationEntryPoint InstallMultipleProtocolInterfaces() failed.\n"));
  }
#endif

#if defined(OHCI_SUPPORT)
  HandleUSB1 = NULL;

	// USB 1.0
  // Unique device path.
  CopyMem(&PrivateUSB1->DevicePath, &PciIoDevicePathTemplateUSB1, sizeof(PciIoDevicePathTemplateUSB1));
  PrivateUSB1->DevicePath.AcpiDevicePath.UID = 2;
  // Copy protocol structure
  CopyMem(&PrivateUSB1->PciIoProtocol, &PciIoTemplate, sizeof(PciIoTemplate));

  Status = gBS->InstallMultipleProtocolInterfaces(&HandleUSB1,
                                                  &gEfiPciIoProtocolGuid,       &PrivateUSB1->PciIoProtocol,
                                                  &gEfiDevicePathProtocolGuid,  &PrivateUSB1->DevicePath,
                                                  NULL);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "PciEmulationEntryPoint InstallMultipleProtocolInterfaces() failed.\n"));
  }
#endif


  return Status;
}

