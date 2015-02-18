#ifndef __ARMBDSHELPERLIB_H
#define __ARMBDSHELPERLIB_H

#include <Uefi/UefiBaseType.h>

/**
  Return the value of a global variable defined by its VariableName.
  The variable must be defined with the VendorGuid gEfiGlobalVariableGuid.

  @param  VariableName          A Null-terminated string that is the name of the vendor's
                                variable.
  @param  DefaultValue          Value returned by the function if the variable does not exist
  @param  DataSize              On input, the size in bytes of the return Data buffer.
                                On output the size of data returned in Data.
  @param  Value                 Value read from the UEFI Variable or copy of the default value
                                if the UEFI Variable does not exist

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         No handles match the search.
  @retval EFI_OUT_OF_RESOURCES  There is not resource pool memory to store the matching results.

**/
EFI_STATUS
GetGlobalEnvironmentVariable (
  IN     CONST CHAR16*   VariableName,
  IN     VOID*           DefaultValue,
  IN OUT UINTN*          Size,
  OUT    VOID**          Value
  );

/**
  Return the value of the variable defined by its VariableName and VendorGuid

  @param  VariableName          A Null-terminated string that is the name of the vendor's
                                variable.
  @param  VendorGuid            A unique identifier for the vendor.
  @param  DefaultValue          Value returned by the function if the variable does not exist
  @param  DataSize              On input, the size in bytes of the return Data buffer.
                                On output the size of data returned in Data.
  @param  Value                 Value read from the UEFI Variable or copy of the default value
                                if the UEFI Variable does not exist

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         No handles match the search.
  @retval EFI_OUT_OF_RESOURCES  There is not resource pool memory to store the matching results.

**/
EFI_STATUS
GetEnvironmentVariable (
  IN     CONST CHAR16*   VariableName,
  IN     EFI_GUID*       VendorGuid,
  IN     VOID*           DefaultValue,
  IN OUT UINTN*          Size,
  OUT    VOID**          Value
  );

EFI_STATUS
BdsConnectAndUpdateDevicePath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  OUT    EFI_HANDLE                *Handle,
  OUT    EFI_DEVICE_PATH_PROTOCOL  **RemainingDevicePath
  );

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
  );

/**
  Connect all DXE drivers

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         No handles match the search.
  @retval EFI_OUT_OF_RESOURCES  There is not resource pool memory to store the matching results.

**/
EFI_STATUS
BdsConnectAllDrivers (
  VOID
  );

#endif
