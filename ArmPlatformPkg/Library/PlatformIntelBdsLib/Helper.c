#include <Guid/GlobalVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/DiskIo.h>
#include <Protocol/UsbIo.h>
#include "Helper.h"

#define IS_DEVICE_PATH_NODE(node,type,subtype) (((node)->Type == (type)) && ((node)->SubType == (subtype)))

EFI_STATUS
GetGlobalEnvironmentVariable (
  IN     CONST CHAR16*   VariableName,
  IN     VOID*           DefaultValue,
  IN OUT UINTN*          Size,
  OUT    VOID**          Value
  )
{
  return GetEnvironmentVariable (VariableName, &gEfiGlobalVariableGuid,
           DefaultValue, Size, Value);
}

EFI_STATUS
GetEnvironmentVariable (
  IN     CONST CHAR16*   VariableName,
  IN     EFI_GUID*       VendorGuid,
  IN     VOID*           DefaultValue,
  IN OUT UINTN*          Size,
  OUT    VOID**          Value
  )
{
  EFI_STATUS  Status;
  UINTN       VariableSize;

  // Try to get the variable size.
  *Value = NULL;
  VariableSize = 0;
  Status = gRT->GetVariable ((CHAR16 *) VariableName, VendorGuid, NULL, &VariableSize, *Value);
  if (Status == EFI_NOT_FOUND) {
    if ((DefaultValue != NULL) && (Size != NULL) && (*Size != 0)) {
      // If the environment variable does not exist yet then set it with the default value
      Status = gRT->SetVariable (
                    (CHAR16*)VariableName,
                    VendorGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                    *Size,
                    DefaultValue
                    );
      *Value = AllocateCopyPool (*Size, DefaultValue);
    } else {
      return EFI_NOT_FOUND;
    }
  } else if (Status == EFI_BUFFER_TOO_SMALL) {
    // Get the environment variable value
    *Value = AllocatePool (VariableSize);
    if (*Value == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = gRT->GetVariable ((CHAR16 *)VariableName, VendorGuid, NULL, &VariableSize, *Value);
    if (EFI_ERROR (Status)) {
      FreePool(*Value);
      return EFI_INVALID_PARAMETER;
    }

    if (Size) {
      *Size = VariableSize;
    }
  } else {
    *Value = AllocateCopyPool (*Size, DefaultValue);
    return Status;
  }

  return EFI_SUCCESS;
}

BOOLEAN
BdsIsRemovableUsb (
  IN  EFI_DEVICE_PATH*  DevicePath
  )
{
  return ((DevicePathType (DevicePath) == MESSAGING_DEVICE_PATH) &&
          ((DevicePathSubType (DevicePath) == MSG_USB_CLASS_DP) ||
           (DevicePathSubType (DevicePath) == MSG_USB_WWID_DP)));
}

EFI_STATUS
BdsGetDeviceUsb (
  IN  EFI_DEVICE_PATH*  RemovableDevicePath,
  OUT EFI_HANDLE*       DeviceHandle,
  OUT EFI_DEVICE_PATH** NewDevicePath
  )
{
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         UsbIoHandleCount;
  EFI_HANDLE                    *UsbIoBuffer;
  EFI_DEVICE_PATH*              UsbIoDevicePath;
  EFI_DEVICE_PATH*              TmpDevicePath;
  USB_WWID_DEVICE_PATH*         WwidDevicePath1;
  USB_WWID_DEVICE_PATH*         WwidDevicePath2;
  USB_CLASS_DEVICE_PATH*        UsbClassDevicePath1;
  USB_CLASS_DEVICE_PATH*        UsbClassDevicePath2;

  // Get all the UsbIo handles
  UsbIoHandleCount = 0;
  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiUsbIoProtocolGuid, NULL, &UsbIoHandleCount, &UsbIoBuffer);
  if (EFI_ERROR (Status) || (UsbIoHandleCount == 0)) {
    return Status;
  }

  // Check if one of the handles matches the USB description
  for (Index = 0; Index < UsbIoHandleCount; Index++) {
    Status = gBS->HandleProtocol (UsbIoBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID **) &UsbIoDevicePath);
    if (!EFI_ERROR (Status)) {
      TmpDevicePath = UsbIoDevicePath;
      while (!IsDevicePathEnd (TmpDevicePath)) {
        // Check if the Device Path node is a USB Removable device Path node
        if (BdsIsRemovableUsb (TmpDevicePath)) {
          if (TmpDevicePath->SubType == MSG_USB_WWID_DP) {
            WwidDevicePath1 = (USB_WWID_DEVICE_PATH*)RemovableDevicePath;
            WwidDevicePath2 = (USB_WWID_DEVICE_PATH*)TmpDevicePath;
            if ((WwidDevicePath1->VendorId == WwidDevicePath2->VendorId) &&
                (WwidDevicePath1->ProductId == WwidDevicePath2->ProductId) &&
                (CompareMem (WwidDevicePath1+1, WwidDevicePath2+1, DevicePathNodeLength(WwidDevicePath1)-sizeof (USB_WWID_DEVICE_PATH)) == 0))
            {
              *DeviceHandle = UsbIoBuffer[Index];
              // Add the additional original Device Path Nodes (eg: FilePath Device Path Node) to the new Device Path
              *NewDevicePath = AppendDevicePath (UsbIoDevicePath, NextDevicePathNode (RemovableDevicePath));
              return EFI_SUCCESS;
            }
          } else {
            UsbClassDevicePath1 = (USB_CLASS_DEVICE_PATH*)RemovableDevicePath;
            UsbClassDevicePath2 = (USB_CLASS_DEVICE_PATH*)TmpDevicePath;
            if ((UsbClassDevicePath1->VendorId != 0xFFFF) && (UsbClassDevicePath1->VendorId == UsbClassDevicePath2->VendorId) &&
                (UsbClassDevicePath1->ProductId != 0xFFFF) && (UsbClassDevicePath1->ProductId == UsbClassDevicePath2->ProductId) &&
                (UsbClassDevicePath1->DeviceClass != 0xFF) && (UsbClassDevicePath1->DeviceClass == UsbClassDevicePath2->DeviceClass) &&
                (UsbClassDevicePath1->DeviceSubClass != 0xFF) && (UsbClassDevicePath1->DeviceSubClass == UsbClassDevicePath2->DeviceSubClass) &&
                (UsbClassDevicePath1->DeviceProtocol != 0xFF) && (UsbClassDevicePath1->DeviceProtocol == UsbClassDevicePath2->DeviceProtocol))
            {
              *DeviceHandle = UsbIoBuffer[Index];
              // Add the additional original Device Path Nodes (eg: FilePath Device Path Node) to the new Device Path
              *NewDevicePath = AppendDevicePath (UsbIoDevicePath, NextDevicePathNode (RemovableDevicePath));
              return EFI_SUCCESS;
            }
          }
        }
        TmpDevicePath = NextDevicePathNode (TmpDevicePath);
      }

    }
  }

  return EFI_NOT_FOUND;
}

BOOLEAN
BdsIsRemovableHd (
  IN  EFI_DEVICE_PATH*  DevicePath
  )
{
  return IS_DEVICE_PATH_NODE (DevicePath, MEDIA_DEVICE_PATH, MEDIA_HARDDRIVE_DP);
}

EFI_STATUS
BdsGetDeviceHd (
  IN  EFI_DEVICE_PATH*  RemovableDevicePath,
  OUT EFI_HANDLE*       DeviceHandle,
  OUT EFI_DEVICE_PATH** NewDevicePath
  )
{
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         PartitionHandleCount;
  EFI_HANDLE                    *PartitionBuffer;
  EFI_DEVICE_PATH*              PartitionDevicePath;
  EFI_DEVICE_PATH*              TmpDevicePath;
  HARDDRIVE_DEVICE_PATH*        HardDriveDevicePath1;
  HARDDRIVE_DEVICE_PATH*        HardDriveDevicePath2;

  // Get all the DiskIo handles
  PartitionHandleCount = 0;
  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiDiskIoProtocolGuid, NULL, &PartitionHandleCount, &PartitionBuffer);
  if (EFI_ERROR (Status) || (PartitionHandleCount == 0)) {
    return Status;
  }

  // Check if one of the handles matches the Hard Disk Description
  for (Index = 0; Index < PartitionHandleCount; Index++) {
    Status = gBS->HandleProtocol (PartitionBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID **) &PartitionDevicePath);
    if (!EFI_ERROR (Status)) {
      TmpDevicePath = PartitionDevicePath;
      while (!IsDevicePathEnd (TmpDevicePath)) {
        // Check if the Device Path node is a HD Removable device Path node
        if (BdsIsRemovableHd (TmpDevicePath)) {
          HardDriveDevicePath1 = (HARDDRIVE_DEVICE_PATH*)RemovableDevicePath;
          HardDriveDevicePath2 = (HARDDRIVE_DEVICE_PATH*)TmpDevicePath;
          if ((HardDriveDevicePath1->SignatureType == HardDriveDevicePath2->SignatureType) &&
              (CompareGuid ((EFI_GUID *)HardDriveDevicePath1->Signature, (EFI_GUID *)HardDriveDevicePath2->Signature) == TRUE) &&
              (HardDriveDevicePath1->PartitionNumber == HardDriveDevicePath2->PartitionNumber))
          {
            *DeviceHandle = PartitionBuffer[Index];
            // Add the additional original Device Path Nodes (eg: FilePath Device Path Node) to the new Device Path
            *NewDevicePath = AppendDevicePath (PartitionDevicePath, NextDevicePathNode (RemovableDevicePath));
            return EFI_SUCCESS;
          }
        }
        TmpDevicePath = NextDevicePathNode (TmpDevicePath);
      }

    }
  }

  return EFI_NOT_FOUND;
}

/*BOOLEAN
BdsIsRemovableCdrom (
  IN  EFI_DEVICE_PATH*  DevicePath
  )
{
  return IS_DEVICE_PATH_NODE (DevicePath, MEDIA_DEVICE_PATH, MEDIA_CDROM_DP);
}

EFI_STATUS
BdsGetDeviceCdrom (
  IN  EFI_DEVICE_PATH*  RemovableDevicePath,
  OUT EFI_HANDLE*       DeviceHandle,
  OUT EFI_DEVICE_PATH** DevicePath
  )
{
  ASSERT(0);
  return EFI_UNSUPPORTED;
}*/

typedef BOOLEAN
(*BDS_IS_REMOVABLE) (
  IN  EFI_DEVICE_PATH*  DevicePath
  );

typedef EFI_STATUS
(*BDS_GET_DEVICE) (
  IN  EFI_DEVICE_PATH*  RemovableDevicePath,
  OUT EFI_HANDLE*       DeviceHandle,
  OUT EFI_DEVICE_PATH** DevicePath
  );

typedef struct {
  BDS_IS_REMOVABLE    IsRemovable;
  BDS_GET_DEVICE      GetDevice;
} BDS_REMOVABLE_DEVICE_SUPPORT;

BDS_REMOVABLE_DEVICE_SUPPORT  RemovableDeviceSupport[] = {
  { BdsIsRemovableUsb, BdsGetDeviceUsb },
  { BdsIsRemovableHd, BdsGetDeviceHd },
  //{ BdsIsRemovableCdrom, BdsGetDeviceCdrom }
};

STATIC
BOOLEAN
IsRemovableDevice (
  IN  EFI_DEVICE_PATH*  DevicePath
  )
{
  UINTN             Index;
  EFI_DEVICE_PATH*  TmpDevicePath;

  TmpDevicePath = DevicePath;
  while (!IsDevicePathEnd (TmpDevicePath)) {
    for (Index = 0; Index < sizeof (RemovableDeviceSupport) / sizeof (BDS_REMOVABLE_DEVICE_SUPPORT); Index++) {
      if (RemovableDeviceSupport[Index].IsRemovable (TmpDevicePath)) {
        return TRUE;
      }
    }
    TmpDevicePath = NextDevicePathNode (TmpDevicePath);
  }

  return FALSE;
}

STATIC
EFI_STATUS
TryRemovableDevice (
  IN  EFI_DEVICE_PATH*  DevicePath,
  OUT EFI_HANDLE*       DeviceHandle,
  OUT EFI_DEVICE_PATH** NewDevicePath
  )
{
  EFI_STATUS        Status;
  UINTN             Index;
  EFI_DEVICE_PATH*  TmpDevicePath;
  BDS_REMOVABLE_DEVICE_SUPPORT* RemovableDevice;
  EFI_DEVICE_PATH* RemovableDevicePath;
  BOOLEAN         RemovableFound;

  RemovableDevice     = NULL;
  RemovableDevicePath = NULL;
  RemovableFound      = FALSE;
  TmpDevicePath       = DevicePath;

  while (!IsDevicePathEnd (TmpDevicePath) && !RemovableFound) {
    for (Index = 0; Index < sizeof (RemovableDeviceSupport) / sizeof (BDS_REMOVABLE_DEVICE_SUPPORT); Index++) {
      RemovableDevice = &RemovableDeviceSupport[Index];
      if (RemovableDevice->IsRemovable (TmpDevicePath)) {
        RemovableDevicePath = TmpDevicePath;
        RemovableFound = TRUE;
        break;
      }
    }
    TmpDevicePath = NextDevicePathNode (TmpDevicePath);
  }

  if (!RemovableFound) {
    return EFI_NOT_FOUND;
  }

  // Search into the current started drivers
  Status = RemovableDevice->GetDevice (RemovableDevicePath, DeviceHandle, NewDevicePath);
  if (Status == EFI_NOT_FOUND) {
    // Connect all the drivers
    BdsConnectAllDrivers ();

    // Search again into all the drivers
    Status = RemovableDevice->GetDevice (RemovableDevicePath, DeviceHandle, NewDevicePath);
  }

  return Status;
}

STATIC
EFI_STATUS
BdsConnectAndUpdateDevicePath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  OUT    EFI_HANDLE                *Handle,
  OUT    EFI_DEVICE_PATH_PROTOCOL  **RemainingDevicePath
  )
{
  EFI_DEVICE_PATH*            Remaining;
  EFI_DEVICE_PATH*            NewDevicePath;
  EFI_STATUS                  Status;
  EFI_HANDLE                  PreviousHandle;

  if ((DevicePath == NULL) || (*DevicePath == NULL) || (Handle == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  PreviousHandle = NULL;
  do {
    Remaining = *DevicePath;

    // The LocateDevicePath() function locates all devices on DevicePath that support Protocol and returns
    // the handle to the device that is closest to DevicePath. On output, the device path pointer is modified
    // to point to the remaining part of the device path
    Status = gBS->LocateDevicePath (&gEfiDevicePathProtocolGuid, &Remaining, Handle);

    if (!EFI_ERROR (Status)) {
      if (*Handle == PreviousHandle) {
        //
        // If no forward progress is made try invoking the Dispatcher.
        // A new FV may have been added to the system and new drivers
        // may now be found.
        // Status == EFI_SUCCESS means a driver was dispatched
        // Status == EFI_NOT_FOUND means no new drivers were dispatched
        //
        Status = gDS->Dispatch ();
      }

      if (!EFI_ERROR (Status)) {
        PreviousHandle = *Handle;

        // Recursive = FALSE: We do not want to start the whole device tree
        Status = gBS->ConnectController (*Handle, NULL, Remaining, FALSE);
      }
    }
  } while (!EFI_ERROR (Status) && !IsDevicePathEnd (Remaining));

  if (!EFI_ERROR (Status)) {
    // Now, we have got the whole Device Path connected, call again ConnectController to ensure all the supported Driver
    // Binding Protocol are connected (such as DiskIo and SimpleFileSystem)
    Remaining = *DevicePath;
    Status = gBS->LocateDevicePath (&gEfiDevicePathProtocolGuid, &Remaining, Handle);
    if (!EFI_ERROR (Status)) {
      Status = gBS->ConnectController (*Handle, NULL, Remaining, FALSE);
      if (EFI_ERROR (Status)) {
        // If the last node is a Memory Map Device Path just return EFI_SUCCESS.
        if ((Remaining->Type == HARDWARE_DEVICE_PATH) && (Remaining->SubType == HW_MEMMAP_DP)) {
            Status = EFI_SUCCESS;
        }
      }
    }
  } else if (!IsDevicePathEnd (Remaining) && !IsRemovableDevice (Remaining)) {

    /*// If the remaining Device Path is a FilePath or MemoryMap then we consider the Device Path has been loaded correctly
    if ((Remaining->Type == MEDIA_DEVICE_PATH) && (Remaining->SubType == MEDIA_FILEPATH_DP)) {
      Status = EFI_SUCCESS;
    } else if ((Remaining->Type == HARDWARE_DEVICE_PATH) && (Remaining->SubType == HW_MEMMAP_DP)) {
      Status = EFI_SUCCESS;
    }*/

    //TODO: Should we just return success and leave the caller decide if it is the expected RemainingPath
    Status = EFI_SUCCESS;
  } else {
    Status = TryRemovableDevice (*DevicePath, Handle, &NewDevicePath);
    if (!EFI_ERROR (Status)) {
      Status = BdsConnectAndUpdateDevicePath (&NewDevicePath, Handle, RemainingDevicePath);
      *DevicePath = NewDevicePath;
      return Status;
    }
  }

  if (RemainingDevicePath) {
    *RemainingDevicePath = Remaining;
  }

  return Status;
}

/**
  Connect a Device Path and return the handle of the driver that support this DevicePath

  @param  DevicePath            Device Path of the File to connect
  @param  Handle                Handle of the driver that support this DevicePath
  @param  RemainingDevicePath   Remaining DevicePath nodes that do not match the driver DevicePath

  @retval EFI_SUCCESS           A driver that matches the Device Path has been found
  @retval EFI_NOT_FOUND         No handles match the search.
  @retval EFI_INVALID_PARAMETER DevicePath or Handle is NULL

**/
EFI_STATUS
BdsConnectDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL* DevicePath,
  OUT EFI_HANDLE                *Handle,
  OUT EFI_DEVICE_PATH_PROTOCOL  **RemainingDevicePath
  )
{
  return BdsConnectAndUpdateDevicePath (&DevicePath, Handle, RemainingDevicePath);
}

/**
  Connect all DXE drivers

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         No handles match the search.
  @retval EFI_OUT_OF_RESOURCES  There is not resource pool memory to store the matching results.

**/
EFI_STATUS
BdsConnectAllDrivers (
  VOID
  )
{
  UINTN                     HandleCount, Index;
  EFI_HANDLE                *HandleBuffer;
  EFI_STATUS                Status;

  do {
    // Locate all the driver handles
    Status = gBS->LocateHandleBuffer (
                AllHandles,
                NULL,
                NULL,
                &HandleCount,
                &HandleBuffer
                );
    if (EFI_ERROR (Status)) {
      break;
    }

    // Connect every handles
    for (Index = 0; Index < HandleCount; Index++) {
      gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
    }

    if (HandleBuffer != NULL) {
      FreePool (HandleBuffer);
    }

    // Check if new handles have been created after the start of the previous handles
    Status = gDS->Dispatch ();
  } while (!EFI_ERROR(Status));

  return EFI_SUCCESS;
}

