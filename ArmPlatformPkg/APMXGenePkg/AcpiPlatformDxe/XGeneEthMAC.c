/** @file
  APM X-Gene Ethernet Firmware Initialization Driver

  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

  This driver is called to initialize the FW part of the PHY in preparation
  for the OS.

**/

#include <Guid/ShellVariableGuid.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <APMXGeneSocCsr.h>

#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/AcpiAml.h>

#ifdef ACPI_DEBUG
#define DBG(arg...) DEBUG((EFI_D_ERROR,## arg))
#else
#define DBG(arg...)
#endif

#define EFI_ACPI_MAX_NUM_TABLES         20
#define DSDT_SIGNATURE                  0x54445344
/* For APM Ethernet driver */
#define APM_ACPI_ETH_ID                 "APMC0D19"
#define APM_ACPI_ETH_MAC_KEY            "local-mac-address"

/* For Open Source */
#define ACPI_ETH_ID                     "APMC0D05"
#define ACPI_ETH_MAC_KEY                "mac-address"

#define PREFIX_VARIABLE_NAME            L"MAC"
#define PREFIX_VARIABLE_NAME_COMPAT     L"RGMII_MAC"
#define MAC_MAX_LEN                     30

STATIC INTN FoundAPMEthernet = 0; //Set when first found APM Ethernet driver. Not open source driver

EFI_STATUS GetEnvMAC(
  IN UINTN    MacNextID,
  IN OUT      CHAR16 *MACBuffer)
{
  EFI_STATUS    Status;
  CHAR16        MACEnv[MAC_MAX_LEN + 2];
  UINTN         Size;

  //
  // Get the MAC from PCD ENV
  //
  UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME, MacNextID);

  Size = MAC_MAX_LEN * sizeof(CHAR16);
  Status = gRT->GetVariable(MACEnv, &gShellVariableGuid,
                            0, &Size, (VOID *) MACBuffer);
  if (EFI_ERROR(Status)) {
    DBG("No MAC set for %S: %d\n", MACEnv, Status);
    UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME_COMPAT, MacNextID);
    Size = MAC_MAX_LEN * sizeof(CHAR16);
    Status = gRT->GetVariable(MACEnv, &gShellVariableGuid,
                              0, &Size, (VOID *) MACBuffer);
    if (EFI_ERROR(Status)) {
      DBG("No MAC set for %S: %d\n", MACEnv, Status);
      return Status;
    }
  }

  DBG("%s %s\n", MACEnv, MACBuffer);
  return EFI_SUCCESS;
}

EFI_STATUS _SearchReplacePackageMACAddress(
  IN EFI_ACPI_SDT_PROTOCOL  *AcpiTableProtocol,
  IN EFI_ACPI_HANDLE        ChildHandle,
  IN UINTN                  Level,
  IN OUT BOOLEAN            *Found,
  IN UINTN                  *MacNextID)
{
/*
 *   Name (_DSD, Package () {
 *   ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *   Package () {
 *     Package (2) {"mac-address", Package (6) { 00, 11, 22, 33, 44, 55 }}
 *     Package (2) {"phy-channel", 0},
 *     Package (2) {"phy-mode", "rgmii"},
 *     Package (2) {"max-transfer-unit", 0x5dc},   // MTU of 1500
 *     Package (2) {"max-speed", 0x3e8},            // 1000 Mbps
 *   }
 * })
 */
  EFI_STATUS          Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CONST UINT8         *Data;
  CONST VOID          *Buffer;
  UINTN               DataSize;
  UINTN               Count;
  EFI_ACPI_HANDLE     CurrentHandle;
  EFI_ACPI_HANDLE     NextHandle;
  CHAR16              MACBuffer[MAC_MAX_LEN];
  CHAR16              StringByte[3];

  DBG("In Level:%d\n", Level);
  Status = EFI_SUCCESS;
  for (CurrentHandle = NULL; ;) {
    Status = AcpiTableProtocol->GetChild(ChildHandle, &CurrentHandle);
    if (Level != 3 && (EFI_ERROR(Status) || CurrentHandle == NULL))
       break;

    Status = AcpiTableProtocol->GetOption(CurrentHandle, 0, &DataType, &Buffer, &DataSize);
    Data = Buffer;
    DBG("_DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X\n",
        DataSize, Data[0], DataSize > 1 ? Data[1] : 0);

    if (Level < 2 && Data[0] != AML_PACKAGE_OP)
      continue;

    if (Level == 2 && Data[0] == AML_STRING_PREFIX) {
      Status = AcpiTableProtocol->GetOption(CurrentHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      DBG("  _DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X\n",
              DataSize, Data[0], DataSize > 1 ? Data[1] : 0);

      Data = Buffer;
      if (DataType != EFI_ACPI_DATA_TYPE_STRING
              || AsciiStrCmp((CHAR8 *) Data, ACPI_ETH_MAC_KEY) != 0)
        continue;

      DBG("_DSD Key Type %d. Found MAC address key\n", DataType);

      //
      // We found the node.
      //
      *Found = TRUE;
      continue;
    }

    if (Level == 3 && *Found) {
      UINTN ColonCount = 0;
      UINTN Value;

      //Update the MAC
      Status = GetEnvMAC((*MacNextID)++, MACBuffer);
      if (EFI_ERROR(Status))
        break;

      for (Count = 0; Count < 6; Count++) {
        StrnCpy(StringByte, MACBuffer + Count * 2 + ColonCount, 2);
        StringByte[2] = '\0';
        Value = StrHexToUintn(StringByte);

        Status = AcpiTableProtocol->GetOption(CurrentHandle, 1, &DataType, &Buffer, &DataSize);
        if (EFI_ERROR(Status))
          break;

        Data = Buffer;
        DBG("    _DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X\n",
            DataSize, Data[0], DataSize > 1 ? Data[1] : 0);

        if (DataType != EFI_ACPI_DATA_TYPE_UINT)
          break;

        // only need one byte.
        // FIXME: Assume the CPU is little endian
        Status = AcpiTableProtocol->SetOption(CurrentHandle, 1, (VOID *)&Value, sizeof(UINT8));
        if (EFI_ERROR(Status))
          break;

        Status = AcpiTableProtocol->GetChild(ChildHandle, &CurrentHandle);
        if (EFI_ERROR(Status) || CurrentHandle == NULL)
          break;

        ColonCount++;
      }

      break;
    }

    if (Level > 3)
      break;

    //Search next package
    AcpiTableProtocol->Open((VOID *) Buffer, &NextHandle);
    Status = _SearchReplacePackageMACAddress(AcpiTableProtocol, NextHandle, Level + 1, Found, MacNextID);
    AcpiTableProtocol->Close(NextHandle);
    if (!EFI_ERROR(Status))
      break;
  }

  return Status;
}

EFI_STATUS SearchReplacePackageMACAddress(
  IN EFI_ACPI_SDT_PROTOCOL  *AcpiTableProtocol,
  IN EFI_ACPI_HANDLE        ChildHandle,
  IN UINTN                  *MacNextID)
{
  BOOLEAN Found = FALSE;
  UINTN Level = 0;

  return _SearchReplacePackageMACAddress(AcpiTableProtocol, ChildHandle, Level, &Found, MacNextID);
}

EFI_STATUS XGeneProcessDSDTChild(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE ChildHandle, UINTN *MacNextID)
{
  EFI_STATUS          Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CONST UINT8         *Data;
  CONST VOID          *Buffer;
  UINTN               DataSize;
  EFI_ACPI_HANDLE     DevHandle;
  INTN                Found = 0;

  Status = AcpiTableProtocol->GetOption(ChildHandle, 0, &DataType, &Buffer, &DataSize);
  if (EFI_ERROR(Status))
    return EFI_SUCCESS;

  Data = Buffer;
  //
  // Skip all non-device type
  //
  if (DataSize != 2 || Data[0] != AML_EXT_OP || Data[1] != AML_EXT_DEVICE_OP)
    return EFI_SUCCESS;

  //
  // Walk the device type node
  //
  for (DevHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(ChildHandle, &DevHandle);
    if (EFI_ERROR(Status) || DevHandle == NULL)
      break;

    //
    // Search for _HID with Ethernet ID
    //
    Status = AcpiTableProtocol->GetOption(DevHandle, 0, &DataType, &Buffer, &DataSize);
    if (EFI_ERROR(Status))
      break;

    Data = Buffer;
    DBG("Data Type 0x%02X %02X\n", Data[0], DataSize > 1 ? Data[1] : 0);
    if (DataSize == 1 && Data[0] == AML_NAME_OP) {
      Status = AcpiTableProtocol->GetOption(DevHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      Data = Buffer;
      if (DataType == EFI_ACPI_DATA_TYPE_NAME_STRING) {
        if (AsciiStrnCmp((CHAR8 *) Data, "_HID", 4) == 0) {
          EFI_ACPI_HANDLE ValueHandle;

          Status = AcpiTableProtocol->GetOption(DevHandle, 2, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;

          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          AcpiTableProtocol->Open((VOID *) Buffer, &ValueHandle);
          Status = AcpiTableProtocol->GetOption(ValueHandle, 1, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          if (EFI_ERROR(Status) ||
              DataType != EFI_ACPI_DATA_TYPE_STRING ||
              (AsciiStrCmp((CHAR8 *) Data, APM_ACPI_ETH_ID) != 0 &&
                AsciiStrCmp((CHAR8 *) Data, ACPI_ETH_ID) != 0)) {
            AcpiTableProtocol->Close(ValueHandle);
            Found = 0;
            continue;
          }

          DBG("Found Ethernet device\n");
          AcpiTableProtocol->Close(ValueHandle);
          Found = 1;
        } else if (Found == 1 && AsciiStrnCmp((CHAR8 *) Data, "_DSD", 4) == 0) {
          //
          // Patch MAC address for open source kernel
          //
          EFI_ACPI_HANDLE    PkgHandle;
          Status = AcpiTableProtocol->GetOption(DevHandle, 2, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;

          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          //
          // Open package data
          //
          AcpiTableProtocol->Open((VOID *) Buffer, &PkgHandle);
          Status = AcpiTableProtocol->GetOption(PkgHandle, 0, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          DBG("_DSD Subnode Store Op Code 0x%02X %02X\n",
                Data[0], DataSize > 1 ? Data[1] : 0);

          //
          // Walk the _DSD node
          //
          if (DataSize == 1 && Data[0] == AML_PACKAGE_OP)
            Status = SearchReplacePackageMACAddress(AcpiTableProtocol, PkgHandle, MacNextID);

          AcpiTableProtocol->Close(PkgHandle);
        }
      }
    } else if (DataSize == 1 && Data[0] == AML_METHOD_OP && Found) {
      Status = AcpiTableProtocol->GetOption(DevHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      if (DataType != EFI_ACPI_DATA_TYPE_NAME_STRING)
        continue;

      Data = Buffer;
      if (AsciiStrnCmp((CHAR8 *) Data, "_DSM", 4) == 0) {
        //
        // Walk the _DSM node
        //
        EFI_ACPI_HANDLE    DSMHandle;
        EFI_ACPI_HANDLE    PkgHandle;
        EFI_ACPI_HANDLE    KeyValueHandle;
        for (DSMHandle = NULL; ; ) {
          Status = AcpiTableProtocol->GetChild(DevHandle, &DSMHandle);
          if (EFI_ERROR(Status) || DSMHandle == NULL)
            break;

          //
          // Search for AML_STORE_OP type
          //
          Status = AcpiTableProtocol->GetOption(DSMHandle, 0, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            continue;

          Data = Buffer;
          if (DataSize != 1 || Data[0] != AML_STORE_OP)
            continue;

          Status = AcpiTableProtocol->GetOption(DSMHandle, 1, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;
          DBG("_DSM Subnode Store Type %d\n", DataType);
          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          //
          // Open package data
          //
          AcpiTableProtocol->Open((VOID *) Buffer, &PkgHandle);
          Status = AcpiTableProtocol->GetOption(PkgHandle, 0, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          DBG("_DSM Subnode Store Op Code 0x%02X %02X\n",
                Data[0], DataSize > 1 ? Data[1] : 0);
          if (DataSize != 1 || Data[0] != AML_PACKAGE_OP) {
            AcpiTableProtocol->Close(PkgHandle);
            continue;
          }

          //
          // Walk the package items
          //
          for (KeyValueHandle = NULL; ; ) {
            CHAR16 MACValue16[30];
            CHAR8 MACBuffer[30];

            Status = AcpiTableProtocol->GetChild(PkgHandle, &KeyValueHandle);
            if (EFI_ERROR(Status) || KeyValueHandle == NULL)
              break;

            Status = AcpiTableProtocol->GetOption(KeyValueHandle, 0, &DataType, &Buffer, &DataSize);
            if (EFI_ERROR(Status))
              break;

            Data = Buffer;
            DBG("_DSM Key Value Op Code %d 0x%02X %02X\n",
                DataType, Data[0], DataSize > 1 ? Data[1] : 0);
            if (DataSize != 1 && Data[0] != AML_STRING_PREFIX)
              continue;

            Status = AcpiTableProtocol->GetOption(KeyValueHandle, 1, &DataType, &Buffer, &DataSize);
            if (EFI_ERROR(Status))
              break;

            Data = Buffer;
            if (DataType != EFI_ACPI_DATA_TYPE_STRING
                    || AsciiStrCmp((CHAR8 *) Data, APM_ACPI_ETH_MAC_KEY) != 0)
              continue;
            DBG("_DSM Key Type %d. Found Mac address key\n", DataType);

            if (!FoundAPMEthernet) {
              FoundAPMEthernet = 1;
              //Reset MacNextID
              *MacNextID = 0;
            }

            //
            // Get the MAC from PCD ENV
            //
            Status = GetEnvMAC((*MacNextID)++, MACValue16);
            if (EFI_ERROR(Status)) {
              continue;
            }

            UnicodeStrToAsciiStr(MACValue16, MACBuffer);

            //
            // We found the node. Update the MAC
            //
            Status = AcpiTableProtocol->GetChild(PkgHandle, &KeyValueHandle);
            if (EFI_ERROR(Status) || KeyValueHandle == NULL)
              break;

            Status = AcpiTableProtocol->SetOption(KeyValueHandle, 1, MACBuffer, AsciiStrSize(MACBuffer));
            break;
          }
          AcpiTableProtocol->Close(PkgHandle);
        }
      }
    }
  }

  return EFI_SUCCESS;
}

static EFI_STATUS XGeneProcessDSDT(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE TableHandle)
{
  EFI_STATUS              Status;
  EFI_ACPI_HANDLE         ChildHandle;
  UINTN                   MacEntryID;
  //
  // Parse table for device type
  MacEntryID = 0;
  for (ChildHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(TableHandle, &ChildHandle);
    if (EFI_ERROR(Status))
      break;
    if (ChildHandle == NULL)
      break;

    XGeneProcessDSDTChild(AcpiTableProtocol, ChildHandle, &MacEntryID);
  }

  return EFI_SUCCESS;
}

EFI_STATUS XGeneEthMACInit(void)
{
  EFI_STATUS              Status;
  EFI_ACPI_SDT_PROTOCOL   *AcpiTableProtocol;
  EFI_ACPI_SDT_HEADER     *Table;
  EFI_ACPI_TABLE_VERSION  TableVersion;
  UINTN                   TableKey;
  EFI_ACPI_HANDLE         TableHandle;
  UINTN                   i;

  DBG("Configure Ethernet MAC...\n");

  //
  // Find the AcpiTable protocol
  Status = gBS->LocateProtocol(&gEfiAcpiSdtProtocolGuid, NULL, (VOID**) &AcpiTableProtocol);
  if (EFI_ERROR(Status)) {
	  DBG("Unable to locate ACPI table protocol\n");
    return EFI_SUCCESS;
  }

  //
  // Search for DSDT Table
  for (i = 0; i < EFI_ACPI_MAX_NUM_TABLES; i++) {
    Status = AcpiTableProtocol->GetAcpiTable(i, &Table, &TableVersion, &TableKey);
    if (EFI_ERROR(Status))
      break;
    if (Table->Signature != DSDT_SIGNATURE)
      continue;

    Status = AcpiTableProtocol->OpenSdt(TableKey, &TableHandle);
    if (EFI_ERROR(Status))
      break;

    XGeneProcessDSDT(AcpiTableProtocol, TableHandle);

    AcpiTableProtocol->Close(TableHandle);
  }

  return EFI_SUCCESS;
}
