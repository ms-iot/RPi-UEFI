/** @file
*
*  Copyright (c) 2011-2014, ARM Limited. All rights reserved.
*  Copyright (c) Microsoft Corporation. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include "BdsInternal.h"

#include <Library/PcdLib.h>
#include <Library/PerformanceLib.h>
#include <Library/DxeServicesLib.h>
#include <Protocol/SimpleFileSystem.h>

#include <Protocol/Bds.h>

#include <Guid/EventGroup.h>
#include <Guid/WinSecureBoot.h>
#include <Guid/FileInfo.h>
#include <Library/ArmBdsHelperLib.h>

#define EFI_SET_TIMER_TO_SECOND   10000000

STATIC
EFI_STATUS
GetConsoleDevicePathFromVariable (
  IN  CHAR16*             ConsoleVarName,
  IN  CHAR16*             DefaultConsolePaths,
  OUT EFI_DEVICE_PATH**   DevicePaths
  )
{
  EFI_STATUS                Status;
  UINTN                     Size;
  EFI_DEVICE_PATH_PROTOCOL* DevicePathInstances;
  EFI_DEVICE_PATH_PROTOCOL* DevicePathInstance;
  CHAR16*                   DevicePathStr;
  CHAR16*                   NextDevicePathStr;
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *EfiDevicePathFromTextProtocol;

  Status = GetGlobalEnvironmentVariable (ConsoleVarName, NULL, NULL, (VOID**)&DevicePathInstances);
  if (EFI_ERROR(Status)) {
    // In case no default console device path has been defined we assume a driver handles the console (eg: SimpleTextInOutSerial)
    if ((DefaultConsolePaths == NULL) || (DefaultConsolePaths[0] == L'\0')) {
      *DevicePaths = NULL;
      return EFI_SUCCESS;
    }

    Status = gBS->LocateProtocol (&gEfiDevicePathFromTextProtocolGuid, NULL, (VOID **)&EfiDevicePathFromTextProtocol);
    ASSERT_EFI_ERROR(Status);

    DevicePathInstances = NULL;

    // Extract the Device Path instances from the multi-device path string
    while ((DefaultConsolePaths != NULL) && (DefaultConsolePaths[0] != L'\0')) {
      NextDevicePathStr = StrStr (DefaultConsolePaths, L";");
      if (NextDevicePathStr == NULL) {
        DevicePathStr = DefaultConsolePaths;
        DefaultConsolePaths = NULL;
      } else {
        DevicePathStr = (CHAR16*)AllocateCopyPool ((NextDevicePathStr - DefaultConsolePaths + 1) * sizeof(CHAR16), DefaultConsolePaths);
        *(DevicePathStr + (NextDevicePathStr - DefaultConsolePaths)) = L'\0';
        DefaultConsolePaths = NextDevicePathStr;
        if (DefaultConsolePaths[0] == L';') {
          DefaultConsolePaths++;
        }
      }

      DevicePathInstance = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath (DevicePathStr);
      ASSERT(DevicePathInstance != NULL);
      DevicePathInstances = AppendDevicePathInstance (DevicePathInstances, DevicePathInstance);

      if (NextDevicePathStr != NULL) {
        FreePool (DevicePathStr);
      }
      FreePool (DevicePathInstance);
    }

    // Set the environment variable with this device path multi-instances
    Size = GetDevicePathSize (DevicePathInstances);
    if (Size > 0) {
      gRT->SetVariable (
          ConsoleVarName,
          &gEfiGlobalVariableGuid,
          EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          Size,
          DevicePathInstances
          );
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }

  if (!EFI_ERROR(Status)) {
    *DevicePaths = DevicePathInstances;
  }
  return Status;
}

STATIC
EFI_STATUS
InitializeConsolePipe (
  IN EFI_DEVICE_PATH    *ConsoleDevicePaths,
  IN EFI_GUID           *Protocol,
  OUT EFI_HANDLE        *Handle,
  OUT VOID*             *Interface
  )
{
  EFI_STATUS                Status;
  UINTN                     Size;
  UINTN                     NoHandles;
  EFI_HANDLE                *Buffer;
  EFI_DEVICE_PATH_PROTOCOL* DevicePath;

  // Connect all the Device Path Consoles
  while (ConsoleDevicePaths != NULL) {
    DevicePath = GetNextDevicePathInstance (&ConsoleDevicePaths, &Size);

    Status = BdsConnectDevicePath (DevicePath, Handle, NULL);
    DEBUG_CODE_BEGIN();
      if (EFI_ERROR(Status)) {
        // We convert back to the text representation of the device Path
        EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextProtocol;
        CHAR16* DevicePathTxt;
        EFI_STATUS Status;

        Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID **)&DevicePathToTextProtocol);
        if (!EFI_ERROR(Status)) {
          DevicePathTxt = DevicePathToTextProtocol->ConvertDevicePathToText (DevicePath, TRUE, TRUE);

          DEBUG((EFI_D_ERROR,"Fail to start the console with the Device Path '%s'. (Error '%r')\n", DevicePathTxt, Status));

          FreePool (DevicePathTxt);
        }
      }
    DEBUG_CODE_END();

    // If the console splitter driver is not supported by the platform then use the first Device Path
    // instance for the console interface.
    if (!EFI_ERROR(Status) && (*Interface == NULL)) {
      Status = gBS->HandleProtocol (*Handle, Protocol, Interface);
    }
  }

  // No Device Path has been defined for this console interface. We take the first protocol implementation
  if (*Interface == NULL) {
    Status = gBS->LocateHandleBuffer (ByProtocol, Protocol, NULL, &NoHandles, &Buffer);
    if (EFI_ERROR (Status)) {
      BdsConnectAllDrivers();
      Status = gBS->LocateHandleBuffer (ByProtocol, Protocol, NULL, &NoHandles, &Buffer);
    }

    if (!EFI_ERROR(Status)) {
      *Handle = Buffer[0];
      Status = gBS->HandleProtocol (*Handle, Protocol, Interface);
      ASSERT_EFI_ERROR(Status);
    }
    FreePool (Buffer);
  } else {
    Status = EFI_SUCCESS;
  }

  return Status;
}

EFI_STATUS
InitializeConsole (
  VOID
  )
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH*          ConOutDevicePaths;
  EFI_DEVICE_PATH*          ConInDevicePaths;
  EFI_DEVICE_PATH*          ConErrDevicePaths;

  // By getting the Console Device Paths from the environment variables before initializing the console pipe, we
  // create the 3 environment variables (ConIn, ConOut, ConErr) that allows to initialize all the console interface
  // of newly installed console drivers
  Status = GetConsoleDevicePathFromVariable (L"ConOut", (CHAR16*)PcdGetPtr(PcdDefaultConOutPaths), &ConOutDevicePaths);
  ASSERT_EFI_ERROR (Status);
  Status = GetConsoleDevicePathFromVariable (L"ConIn", (CHAR16*)PcdGetPtr(PcdDefaultConInPaths), &ConInDevicePaths);
  ASSERT_EFI_ERROR (Status);
  Status = GetConsoleDevicePathFromVariable (L"ErrOut", (CHAR16*)PcdGetPtr(PcdDefaultConOutPaths), &ConErrDevicePaths);
  ASSERT_EFI_ERROR (Status);

  // Initialize the Consoles
  Status = InitializeConsolePipe (ConOutDevicePaths, &gEfiSimpleTextOutProtocolGuid, &gST->ConsoleOutHandle, (VOID **)&gST->ConOut);
  ASSERT_EFI_ERROR (Status);
  Status = InitializeConsolePipe (ConInDevicePaths, &gEfiSimpleTextInProtocolGuid, &gST->ConsoleInHandle, (VOID **)&gST->ConIn);
  ASSERT_EFI_ERROR (Status);
  Status = InitializeConsolePipe (ConErrDevicePaths, &gEfiSimpleTextOutProtocolGuid, &gST->StandardErrorHandle, (VOID **)&gST->StdErr);
  if (EFI_ERROR(Status)) {
    // In case of error, we reuse the console output for the error output
    gST->StandardErrorHandle = gST->ConsoleOutHandle;
    gST->StdErr = gST->ConOut;
  }

  // Free Memory allocated for reading the UEFI Variables
  if (ConOutDevicePaths) {
    FreePool (ConOutDevicePaths);
  }
  if (ConInDevicePaths) {
    FreePool (ConInDevicePaths);
  }
  if (ConErrDevicePaths) {
    FreePool (ConErrDevicePaths);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DefineDefaultBootEntries (
  VOID
  )
{
  BDS_LOAD_OPTION*                    BdsLoadOption;
  UINTN                               Size;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL* EfiDevicePathFromTextProtocol;
  EFI_DEVICE_PATH*                    BootDevicePath;
  UINT8*                              OptionalData;
  UINTN                               OptionalDataSize;
  ARM_BDS_LOADER_ARGUMENTS*           BootArguments;
  ARM_BDS_LOADER_TYPE                 BootType;
  EFI_DEVICE_PATH*                    InitrdPath;
  UINTN                               InitrdSize;
  UINTN                               CmdLineSize;
  UINTN                               CmdLineAsciiSize;
  CHAR16*                             DefaultBootArgument;
  CHAR8*                              AsciiDefaultBootArgument;

  //
  // If Boot Order does not exist then create a default entry
  //
  Size = 0;
  Status = gRT->GetVariable (L"BootOrder", &gEfiGlobalVariableGuid, NULL, &Size, NULL);
  if (Status == EFI_NOT_FOUND) {
    if ((PcdGetPtr(PcdDefaultBootDevicePath) == NULL) || (StrLen ((CHAR16*)PcdGetPtr(PcdDefaultBootDevicePath)) == 0)) {
      return EFI_UNSUPPORTED;
    }

    Status = gBS->LocateProtocol (&gEfiDevicePathFromTextProtocolGuid, NULL, (VOID **)&EfiDevicePathFromTextProtocol);
    if (EFI_ERROR(Status)) {
      // You must provide an implementation of DevicePathFromTextProtocol in your firmware (eg: DevicePathDxe)
      DEBUG((EFI_D_ERROR,"Error: Bds requires DevicePathFromTextProtocol\n"));
      return Status;
    }
    BootDevicePath = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath ((CHAR16*)PcdGetPtr(PcdDefaultBootDevicePath));

    DEBUG_CODE_BEGIN();
      // We convert back to the text representation of the device Path to see if the initial text is correct
      EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextProtocol;
      CHAR16* DevicePathTxt;

      Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID **)&DevicePathToTextProtocol);
      ASSERT_EFI_ERROR(Status);
      DevicePathTxt = DevicePathToTextProtocol->ConvertDevicePathToText (BootDevicePath, TRUE, TRUE);

      ASSERT (StrCmp ((CHAR16*)PcdGetPtr(PcdDefaultBootDevicePath), DevicePathTxt) == 0);

      FreePool (DevicePathTxt);
    DEBUG_CODE_END();

    // Create the entry is the Default values are correct
    if (BootDevicePath != NULL) {
      BootType = (ARM_BDS_LOADER_TYPE)PcdGet32 (PcdDefaultBootType);

      // We do not support NULL pointer
      ASSERT (PcdGetPtr (PcdDefaultBootArgument) != NULL);

      //
      // Logic to handle ASCII or Unicode default parameters
      //
      if (*(CHAR8*)PcdGetPtr (PcdDefaultBootArgument) == '\0') {
        CmdLineSize = 0;
        CmdLineAsciiSize = 0;
        DefaultBootArgument = NULL;
        AsciiDefaultBootArgument = NULL;
      } else if (IsUnicodeString ((CHAR16*)PcdGetPtr (PcdDefaultBootArgument))) {
        // The command line is a Unicode string
        DefaultBootArgument = (CHAR16*)PcdGetPtr (PcdDefaultBootArgument);
        CmdLineSize = StrSize (DefaultBootArgument);

        // Initialize ASCII variables
        CmdLineAsciiSize = CmdLineSize / 2;
        AsciiDefaultBootArgument = AllocatePool (CmdLineAsciiSize);
        if (AsciiDefaultBootArgument == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        UnicodeStrToAsciiStr ((CHAR16*)PcdGetPtr (PcdDefaultBootArgument), AsciiDefaultBootArgument);
      } else {
        // The command line is a ASCII string
        AsciiDefaultBootArgument = (CHAR8*)PcdGetPtr (PcdDefaultBootArgument);
        CmdLineAsciiSize = AsciiStrSize (AsciiDefaultBootArgument);

        // Initialize ASCII variables
        CmdLineSize = CmdLineAsciiSize * 2;
        DefaultBootArgument = AllocatePool (CmdLineSize);
        if (DefaultBootArgument == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        AsciiStrToUnicodeStr (AsciiDefaultBootArgument, DefaultBootArgument);
      }

      if ((BootType == BDS_LOADER_KERNEL_LINUX_ATAG) || (BootType == BDS_LOADER_KERNEL_LINUX_FDT)) {
        InitrdPath = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath ((CHAR16*)PcdGetPtr(PcdDefaultBootInitrdPath));
        InitrdSize = GetDevicePathSize (InitrdPath);

        OptionalDataSize = sizeof(ARM_BDS_LOADER_ARGUMENTS) + CmdLineAsciiSize + InitrdSize;
        BootArguments = (ARM_BDS_LOADER_ARGUMENTS*)AllocatePool (OptionalDataSize);
        if (BootArguments == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        BootArguments->LinuxArguments.CmdLineSize = CmdLineAsciiSize;
        BootArguments->LinuxArguments.InitrdSize = InitrdSize;

        CopyMem ((VOID*)(BootArguments + 1), AsciiDefaultBootArgument, CmdLineAsciiSize);
        CopyMem ((VOID*)((UINTN)(BootArguments + 1) + CmdLineAsciiSize), InitrdPath, InitrdSize);

        OptionalData = (UINT8*)BootArguments;
      } else {
        OptionalData = (UINT8*)DefaultBootArgument;
        OptionalDataSize = CmdLineSize;
      }

      BootOptionCreate (LOAD_OPTION_ACTIVE | LOAD_OPTION_CATEGORY_BOOT,
        (CHAR16*)PcdGetPtr(PcdDefaultBootDescription),
        BootDevicePath,
        BootType,
        OptionalData,
        OptionalDataSize,
        &BdsLoadOption
        );
      FreePool (BdsLoadOption);

      if (DefaultBootArgument == (CHAR16*)PcdGetPtr (PcdDefaultBootArgument)) {
        FreePool (AsciiDefaultBootArgument);
      } else if (DefaultBootArgument != NULL) {
        FreePool (DefaultBootArgument);
      }
    } else {
      Status = EFI_UNSUPPORTED;
    }
  }

  return Status;
}

EFI_STATUS
StartDefaultBootOnTimeout (
  VOID
  )
{
  UINTN               Size;
  UINT16              Timeout;
  UINT16              *TimeoutPtr;
  EFI_EVENT           WaitList[2];
  UINTN               WaitIndex;
  UINT16              *BootOrder;
  UINTN               BootOrderSize;
  UINTN               Index;
  CHAR16              BootVariableName[9];
  EFI_STATUS          Status;
  EFI_INPUT_KEY       Key;

  Size = sizeof(UINT16);
  Timeout = (UINT16)PcdGet16 (PcdPlatformBootTimeOut);
  Status = GetGlobalEnvironmentVariable (L"Timeout", &Timeout, &Size, (VOID**)&TimeoutPtr);
  if (!EFI_ERROR (Status)) {
    Timeout = *TimeoutPtr;
    FreePool (TimeoutPtr);
  }

  if (Timeout != 0xFFFF) {
    if (Timeout > 0) {
      // Create the waiting events (keystroke and 1sec timer)
      gBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &WaitList[0]);
      gBS->SetTimer (WaitList[0], TimerPeriodic, EFI_SET_TIMER_TO_SECOND);
      WaitList[1] = gST->ConIn->WaitForKey;

      // Start the timer
      WaitIndex = 0;
      Print(L"The default boot selection will start in ");
      while ((Timeout > 0) && (WaitIndex == 0)) {
        Print(L"%3d seconds",Timeout);
        gBS->WaitForEvent (2, WaitList, &WaitIndex);
        if (WaitIndex == 0) {
          Print(L"\b\b\b\b\b\b\b\b\b\b\b");
          Timeout--;
        }
      }
      // Discard key in the buffer
      do {
        Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
      } while(!EFI_ERROR(Status));
      gBS->CloseEvent (WaitList[0]);
      Print(L"\n\r");
    }

    // In case of Timeout we start the default boot selection
    if (Timeout == 0) {
      // Get the Boot Option Order from the environment variable (a default value should have been created)
      GetGlobalEnvironmentVariable (L"BootOrder", NULL, &BootOrderSize, (VOID**)&BootOrder);

      for (Index = 0; Index < BootOrderSize / sizeof (UINT16); Index++) {
        UnicodeSPrint (BootVariableName, 9 * sizeof(CHAR16), L"Boot%04X", BootOrder[Index]);
        Status = BdsStartBootOption (BootVariableName);
        if (!EFI_ERROR(Status)){
          // Boot option returned successfully, hence don't need to start next boot option
          break;
        }
        // In case of success, we should not return from this call.
      }
      FreePool (BootOrder);
    }
  }
  return EFI_SUCCESS;
}

EFI_STATUS
DefineSecureBootPolicy(
    VOID
    )
{
    EFI_STATUS  Status;
    VOID        *SecureBootData;
    UINTN       SecureBootDataSize;

    Status = GetSectionFromAnyFv(
        PcdGetPtr(PcdSecureBootPolicy),
        EFI_SECTION_RAW, 
        0,
        &SecureBootData, 
        &SecureBootDataSize
        );
    if (EFI_ERROR(Status)) {
        // Secure boot policy not found, this is not an error
        // as not all platform is required to provide one
        DEBUG((EFI_D_VERBOSE, "Secure boot policy is not initialize\n"));
        return EFI_SUCCESS;
    }

    DEBUG((DEBUG_INIT, "Secure boot policy found with size %d\n", SecureBootDataSize));

    Status = gRT->SetVariable(
        SECUREBOOT_CURRENT_POLICY_VARIABLE_NAME,
        &gEfiSecureBootPrivateVariableGuid,
        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        SecureBootDataSize,
        SecureBootData
        );
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "Fail to set SecureBootData"));
        goto Exit;
    }

    DEBUG((DEBUG_INIT, "Secure Boot Policy initialize succesfully\n"));
Exit:

    FreePool(SecureBootData);

    return EFI_SUCCESS;
}

/**
  An empty function to pass error checking of CreateEventEx ().

  @param  Event                 Event whose notification function is being invoked.
  @param  Context               Pointer to the notification function's context,
                                which is implementation-dependent.

**/
STATIC
VOID
EFIAPI
EmptyCallbackFunction (
  IN EFI_EVENT                Event,
  IN VOID                     *Context
  )
{
  return;
}

/**
    This utility function converts Ascii to Unicode. It would allocate the necassary buffer
    to hold the Unicode text and it is the caller responsibility to free it.

    @param  AsciiStr    Pointer to the Ascii string.
    @params UnicodeStr  Pointer to the allocated Unicode string upon success, caller is
                        responsible to free this.

    @return EFI_SUCCESS, EFI_INVALID_PARAMETER or  EFI_OUT_OF_RESOURCES.

**/
EFI_STATUS 
ConvertAllocAsciiStrToUnicodeStr (
    IN CHAR8        *AsciiStr,
    OUT CHAR16      **UnicodeStr
    )
{
    UINTN AsciiStrSize;
    if (AsciiStr == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    AsciiStrSize = StrLen ((CHAR16*)AsciiStr);
    if (AsciiStrSize == 0) {
        return EFI_INVALID_PARAMETER;
    }

    *UnicodeStr = AllocatePool ((AsciiStrSize + 1) * 2);
    if (*UnicodeStr == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    AsciiStrToUnicodeStr (AsciiStr, *UnicodeStr);

    return EFI_SUCCESS;
}

/**
    This utility function loops through all available file system to see if the
    requested application is available. If an application is found a device path
    is  allocated and return to the caller

    @param Index                Start file system index to begin to loop from
    @param AsciiAppPath         Pointer to the app file path in ascii format
    @param UnicodeAppPath       Pointer to the app file path in unicode format
    @param FullAppDevicePath    Pointer that is allocated and return to the caller
                                containing the full EFI device path to the requested
                                app. Caller is responsible to free this.

    @return EFI_NOT_FOUND or EFI_SUCCESS.

**/
EFI_STATUS
FindFileFullDevicePath (
    IN OUT UINTN            *Index,
    IN CHAR8                *AsciiAppPath,
    IN CHAR16               *UnicodeAppPath,
    EFI_DEVICE_PATH         **FullAppDevicePath
    )
{
    EFI_STATUS      Status;
    EFI_HANDLE      *FileSystemHandles;
    UINTN           NumberFileSystemHandles;
    BOOLEAN         FoundPath = FALSE;

    Status = BdsConnectAllDrivers ();
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "FindFileFullDevicePath: FAIL to connect all drivers\n"));
        return EFI_NOT_FOUND;
    }

    // Get all the handles to a recognize file system to see
    // if any of them contains the requested application
    Status = gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &NumberFileSystemHandles,
        &FileSystemHandles
        );
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "No recognize filesystem to parse\n"));
        return EFI_NOT_FOUND;
    }

    if (*Index >= NumberFileSystemHandles) {
        DEBUG ((EFI_D_ERROR, "Invalid file system index %d\n", *Index));
        return EFI_NOT_FOUND;
    }

    for (; (*Index) < NumberFileSystemHandles; (*Index)++) {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Volume = NULL;
        EFI_FILE_HANDLE                     Root = NULL;
        EFI_FILE_HANDLE                     ThisFile = NULL;
        EFI_HANDLE                          Handle;
        EFI_DEVICE_PATH                     *AppDevicePath;
        EFI_DEVICE_PATH                     *RemainingDevicePath;
        EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *EfiDevicePathFromTextProtocol;
        FILEPATH_DEVICE_PATH*               FilePathDevicePath;

        Status = gBS->LocateProtocol (
            &gEfiDevicePathFromTextProtocolGuid,
            NULL,
            (VOID **)&EfiDevicePathFromTextProtocol
            );
        if (EFI_ERROR (Status)) {
            DEBUG ((EFI_D_ERROR, "Error: DevicePathFromTextProtocol required\n"));
            goto NextFleSystemHandle;
        }

        AppDevicePath = EfiDevicePathFromTextProtocol->ConvertTextToDevicePath ((CHAR16*)AsciiAppPath);
        ASSERT (AppDevicePath != NULL);

        *FullAppDevicePath = AppendDevicePath (DevicePathFromHandle (
                FileSystemHandles[*Index]),
                AppDevicePath
                );
        if (*FullAppDevicePath == NULL) {
            DEBUG ((EFI_D_ERROR, "Error:Insufficient memory to allocate device path\n"));
            goto NextFleSystemHandle;
        }

        Status = BdsConnectAndUpdateDevicePath (
            FullAppDevicePath,
            &Handle,
            &RemainingDevicePath
            );
        if (EFI_ERROR (Status)) {
            DEBUG (
                (EFI_D_ERROR, 
                "Error: BdsConnectAndUpdateDevicePath failed (Status '0x%x')\n", 
                Status));
            goto NextFleSystemHandle;
        }

        FilePathDevicePath = (FILEPATH_DEVICE_PATH*)RemainingDevicePath;

        Status = gBS->HandleProtocol (
            Handle, 
            &gEfiSimpleFileSystemProtocolGuid, 
            (VOID **)&Volume
            );
        if (EFI_ERROR (Status)) {
            goto NextFleSystemHandle;
        }

        Status = Volume->OpenVolume (Volume, &Root);
        if (EFI_ERROR (Status)) {
            goto NextFleSystemHandle;
        }

        Status = Root->Open (
            Root, 
            &ThisFile, 
            FilePathDevicePath->PathName, 
            EFI_FILE_MODE_READ, 
            0
            );
        if (EFI_ERROR (Status)) {
            goto NextFleSystemHandle;
        }

        FoundPath = TRUE;

    NextFleSystemHandle:
        if (ThisFile) {
            ThisFile->Close (ThisFile);
        }
        if (Root) {
            Root->Close (Root);
        }
        if (FoundPath) {
            (*Index)++;
            return EFI_SUCCESS;
        }
        if (*FullAppDevicePath) {
            FreePool (*FullAppDevicePath);
            *FullAppDevicePath = NULL;
        }
    }

    return EFI_NOT_FOUND;
}
/**
    This function checks if there is a default boot app path (PcdDefaultBootAppPath)
    provided. If there is no default boot app provided it would just return immediately.
    If a boot app path is provided it would then look through all the available file
    system and check if it contains the specified boot app. If the boot application
    exist it would then create a device path of the boot app and subsequently add it
    as a boot option.

    Example :

    Booting Windows with EFI Boot manager
    (https://technet.microsoft.com/en-us/library/cc766223(v=ws.10).aspx)
        gArmPlatformTokenSpaceGuid.PcdDefaultBootAppPath|L"\\efi\\microsoft\\boot\\bootmgfw.efi"

    Booting Windows on ARM
        gArmPlatformTokenSpaceGuid.PcdDefaultBootAppPath|L"\\EFI\\BOOT\\BOOTARM.EFI"

    @param  None.

    @return None.

**/
EFI_STATUS
DefineDefaultBootAppBootEntries (
    VOID
    )
{
    EFI_STATUS          Status;
    UINTN               Index = 0;
    CHAR16              *UnicodeBootAppPath = NULL;
    CHAR8               *AsciiBootAppPath;
    EFI_DEVICE_PATH     *FullPath = NULL;
    BDS_LOAD_OPTION     *BdsLoadOption = NULL;

    AsciiBootAppPath = (CHAR8*)PcdGetPtr (PcdDefaultBootAppPath);
    if (AsciiBootAppPath == NULL) {
        return EFI_UNSUPPORTED;
    }

    Status = ConvertAllocAsciiStrToUnicodeStr (
        AsciiBootAppPath,
        &UnicodeBootAppPath);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "FAIL to cconvert boot app path to unicode format\n"));
        goto Exit;
    }

    // Attempt to create boot option if the boot app if found. Will add multiple
    // option if the boot app is found in multiple file system.
    do {
        Status = FindFileFullDevicePath (
            &Index,
            AsciiBootAppPath,
            UnicodeBootAppPath,
            &FullPath
            );
        if (Status == EFI_SUCCESS) {
            Status = BootOptionCreate (LOAD_OPTION_ACTIVE | LOAD_OPTION_CATEGORY_BOOT,
                                       L"Default EFI Boot Application",
                                       FullPath,
                                       BDS_LOADER_EFI_APPLICATION,
                                       NULL,
                                       0,
                                       &BdsLoadOption
                                       );
            if (EFI_ERROR (Status)) {
                DEBUG ((EFI_D_ERROR, "Fail to create boot option for %s\n", AsciiBootAppPath));
            } else {
                DEBUG ((DEBUG_INIT, "Created boot option for %s\n", AsciiBootAppPath));
            }
            if (BdsLoadOption) {
                FreePool (BdsLoadOption);
                BdsLoadOption = NULL;
            }
            if (FullPath) {
                FreePool (FullPath);
                FullPath = NULL;
            }
        }
    } while (Status != EFI_NOT_FOUND);

Exit:
    if (UnicodeBootAppPath) {
        FreePool (UnicodeBootAppPath);
    }
    return Status;
}

/**
    This function runs pre-boot app before a the main boot loader is launch.
    Pre boot app path is specify with PcdPreBootAppPath variable.
    The pre-boot app would run any customization before the main OS loader
    allowing some modification without the need to reinstall the OS

    @param  None.

    @return None.

**/
EFI_STATUS
RunPrePreBootApp (
    VOID
    )
{
    EFI_STATUS      Status;
    UINTN           Index = 0;
    CHAR16          *UnicodePreBootAppPath = NULL;
    CHAR8           *AsciiPreBootAppPath;
    EFI_DEVICE_PATH *FullPath = NULL;

    AsciiPreBootAppPath = (CHAR8*)PcdGetPtr (PcdPreBootAppPath);
    if (AsciiPreBootAppPath == NULL) {
        return EFI_UNSUPPORTED;
    }

    Status = ConvertAllocAsciiStrToUnicodeStr (
        AsciiPreBootAppPath,
        &UnicodePreBootAppPath);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "FAIL to convert pre-boot app path to unicode format\n"));
        goto Exit;
    }

    // Launch the Pre Boot app if it exist and only expect one pre boot app
    do {
        Status = FindFileFullDevicePath (
            &Index,
            AsciiPreBootAppPath,
            UnicodePreBootAppPath,
            &FullPath
            );
        if (Status == EFI_SUCCESS) {
            Status = BdsStartEfiApplication (
                gImageHandle,
                FullPath,
                0,
                NULL
                );
            if (EFI_ERROR (Status)) {
                DEBUG ((EFI_D_ERROR, "Fail to launch pre boot app %s (Status '0x%x')\n", AsciiPreBootAppPath, Status));
            } else {
                DEBUG ((DEBUG_INIT, "Launcing pre boot app %s (Status '0x%x')\n", AsciiPreBootAppPath, Status));
            }
            if (FullPath) {
                FreePool (FullPath);
                FullPath = NULL;
            }
            goto Exit;
        }
        if (FullPath) {
            FreePool (FullPath);
            FullPath = NULL;
        }
    } while (Status != EFI_NOT_FOUND);

Exit:
    if (UnicodePreBootAppPath) {
        FreePool (UnicodePreBootAppPath);
    }
    return Status;
}
/**
  This function uses policy data from the platform to determine what operating
  system or system utility should be loaded and invoked.  This function call
  also optionally make the use of user input to determine the operating system
  or system utility to be loaded and invoked.  When the DXE Core has dispatched
  all the drivers on the dispatch queue, this function is called.  This
  function will attempt to connect the boot devices required to load and invoke
  the selected operating system or system utility.  During this process,
  additional firmware volumes may be discovered that may contain addition DXE
  drivers that can be dispatched by the DXE Core.   If a boot device cannot be
  fully connected, this function calls the DXE Service Dispatch() to allow the
  DXE drivers from any newly discovered firmware volumes to be dispatched.
  Then the boot device connection can be attempted again.  If the same boot
  device connection operation fails twice in a row, then that boot device has
  failed, and should be skipped.  This function should never return.

  @param  This             The EFI_BDS_ARCH_PROTOCOL instance.

  @return None.

**/
VOID
EFIAPI
BdsEntry (
  IN EFI_BDS_ARCH_PROTOCOL  *This
  )
{
  UINTN               Size;
  EFI_STATUS          Status;
  UINT16             *BootNext;
  UINTN               BootNextSize;
  CHAR16              BootVariableName[9];
  EFI_EVENT           EndOfDxeEvent;

  //
  // Signal EndOfDxe PI Event
  //
  Status = gBS->CreateEventEx (
      EVT_NOTIFY_SIGNAL,
      TPL_NOTIFY,
      EmptyCallbackFunction,
      NULL,
      &gEfiEndOfDxeEventGroupGuid,
      &EndOfDxeEvent
      );
  if (!EFI_ERROR (Status)) {
    gBS->SignalEvent (EndOfDxeEvent);
  }

  PERF_END   (NULL, "DXE", NULL, 0);

  //
  // Declare the Firmware Vendor
  //
  if (FixedPcdGetPtr(PcdFirmwareVendor) != NULL) {
    Size = 0x100;
    gST->FirmwareVendor = AllocateRuntimePool (Size);
    ASSERT (gST->FirmwareVendor != NULL);
    UnicodeSPrint (gST->FirmwareVendor, Size, L"%a EFI %a %a", PcdGetPtr(PcdFirmwareVendor), __DATE__, __TIME__);
  }

  //
  // Fixup Table CRC after we updated Firmware Vendor
  //
  gST->Hdr.CRC32 = 0;
  Status = gBS->CalculateCrc32 ((VOID*)gST, gST->Hdr.HeaderSize, &gST->Hdr.CRC32);
  ASSERT_EFI_ERROR (Status);

  // If BootNext environment variable is defined then we just load it !
  BootNextSize = sizeof(UINT16);
  Status = GetGlobalEnvironmentVariable (L"BootNext", NULL, &BootNextSize, (VOID**)&BootNext);
  if (!EFI_ERROR(Status)) {
    ASSERT(BootNextSize == sizeof(UINT16));

    // Generate the requested Boot Entry variable name
    UnicodeSPrint (BootVariableName, 9 * sizeof(CHAR16), L"Boot%04X", *BootNext);

    // Set BootCurrent variable
    gRT->SetVariable (L"BootCurrent", &gEfiGlobalVariableGuid,
              EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
              BootNextSize, BootNext);

    FreePool (BootNext);

    // Start the requested Boot Entry
    Status = BdsStartBootOption (BootVariableName);
    if (Status != EFI_NOT_FOUND) {
      // BootNext has not been succeeded launched
      if (EFI_ERROR(Status)) {
        Print(L"Fail to start BootNext.\n");
      }

      // Delete the BootNext environment variable
      gRT->SetVariable (L"BootNext", &gEfiGlobalVariableGuid,
          EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          0, NULL);
    }

    // Clear BootCurrent variable
    gRT->SetVariable (L"BootCurrent", &gEfiGlobalVariableGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
        0, NULL);
  }

  // If Boot Order does not exist then create a default entry
  DefineDefaultBootEntries ();

  // If available add boot app into the boot entries
  DefineDefaultBootAppBootEntries ();

  // Apply secure boot policy if available
  DefineSecureBootPolicy ();

  // Run any pre boot app as needed
  RunPrePreBootApp();

  // Now we need to setup the EFI System Table with information about the console devices.
  InitializeConsole ();

  //
  // Update the CRC32 in the EFI System Table header
  //
  gST->Hdr.CRC32 = 0;
  Status = gBS->CalculateCrc32 ((VOID*)gST, gST->Hdr.HeaderSize, &gST->Hdr.CRC32);
  ASSERT_EFI_ERROR (Status);

  //
  // Signal the EVT_SIGNAL_READY_TO_BOOT event
  //
  EfiSignalEventReadyToBoot ();
  
  // Timer before initiating the default boot selection
  StartDefaultBootOnTimeout ();

  // Start the Boot Menu
  Status = BootMenuMain ();
  ASSERT_EFI_ERROR (Status);

}

EFI_BDS_ARCH_PROTOCOL  gBdsProtocol = {
  BdsEntry,
};

EFI_STATUS
EFIAPI
BdsInitialize (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiBdsArchProtocolGuid, &gBdsProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
