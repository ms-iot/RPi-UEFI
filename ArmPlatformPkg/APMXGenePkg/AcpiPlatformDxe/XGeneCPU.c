/** @file

  APM X-Gene insert APIC table

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
#include <Base.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Ppi/ArmMpCoreInfo.h>

#include <Protocol/AcpiTable.h>
#include <Guid/Acpi.h>
#include <IndustryStandard/Acpi51.h>

#ifdef AARCH64_MP_PROTOCOL
#define CPU_OFFSET	8
#else
#define CPU_OFFSET	0
#endif

EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE APICGicDistributerTemplate = {
  EFI_ACPI_5_1_GICD,
  sizeof(EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE),
  0,
  0,
  FixedPcdGet32(PcdGicDistributorBase),
  0,
  0
};

EFI_ACPI_5_1_GIC_STRUCTURE APICProcessorRecordTemplate = {
  EFI_ACPI_5_1_GIC,
  sizeof(EFI_ACPI_5_1_GIC_STRUCTURE),
  0,
  0,
  0, /* need fill in */
  EFI_ACPI_5_1_GIC_ENABLED,
  1,
  0,
  0, /* need fill in */
  FixedPcdGet32(PcdGicInterruptInterfaceBase),
  FixedPcdGet32(PcdGicInterruptInterfaceBase) + 0x40000, /* VGIC */
  FixedPcdGet32(PcdGicInterruptInterfaceBase) + 0x20000, /* Hyp GIC */
  0x9,
  FixedPcdGet32(PcdGicDistributorBase),
  0, /* need fill in */
};

EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER APICProcessorTableHeaderTemplate = {
  {
    EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_SIGNATURE,
    0, /* need fill in */
    EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_REVISION,    // Revision
    0x00, // Checksum will be updated at runtime
    //
    // It is expected that these values will be updated at EntryPoint.
    //
    {0},     // OEM ID is a 6 bytes long field
    0,       // OEM Table ID(8 bytes long)
    0,       // OEM Revision
    0,       // Creator ID
    0,       // Creator Revision
  },
  0,
  EFI_ACPI_5_1_PCAT_COMPAT
};

/**
  This function calculates and updates an UINT8 checksum.

  @param[in]  Buffer          Pointer to buffer to checksum
  @param[in]  Size            Number of bytes to checksum

**/
VOID
ApicAcpiTableChecksum (
  IN UINT8      *Buffer,
  IN UINTN      Size
  )
{
  UINTN ChecksumOffset;

  ChecksumOffset = OFFSET_OF (EFI_ACPI_DESCRIPTION_HEADER, Checksum);

  //
  // Set checksum to 0 first.
  //
  Buffer[ChecksumOffset] = 0;

  //
  // Update checksum value.
  //
  Buffer[ChecksumOffset] = CalculateCheckSum8 (Buffer, Size);
}

EFI_STATUS
XGeneInstallApicTable(VOID)
{
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTableProtocol;
  ARM_PROCESSOR_TABLE           *ArmProcessorTable;
  ARM_CORE_INFO                 *ArmCoreInfoTable;
  INTN                          Count, Count1;
  UINTN                         Size;
  EFI_STATUS                    Status;
  UINTN                         ApicTableKey  = 0;
  EFI_ACPI_5_1_GIC_STRUCTURE    *EntryPointer = NULL;
  EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE    *GicDistributePointer = NULL;
  EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER *ApicTablePointer = NULL;
  //
  // Get AcpiTable Protocol.
  //

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTableProtocol);
  if (EFI_ERROR (Status))
    return Status;

  for (Count = 0; Count < gST->NumberOfTableEntries; Count++) {
    if (CompareGuid (&gArmMpCoreInfoGuid, &(gST->ConfigurationTable[Count].VendorGuid))) {
      ArmProcessorTable = (ARM_PROCESSOR_TABLE *)gST->ConfigurationTable[Count].VendorTable;
      ArmCoreInfoTable = ArmProcessorTable->ArmCpus;

      Size = sizeof(EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER) +
              ArmProcessorTable->NumberOfEntries * sizeof(EFI_ACPI_5_1_GIC_STRUCTURE) +
              sizeof(EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE);

      ApicTablePointer = (EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER *)AllocateZeroPool(Size);
      if (!ApicTablePointer)
        return EFI_OUT_OF_RESOURCES;

      EntryPointer = (EFI_ACPI_5_1_GIC_STRUCTURE *) ((UINT64)ApicTablePointer +
          sizeof(EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER));

      GicDistributePointer = (EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE *) ((UINT64)EntryPointer +
          ArmProcessorTable->NumberOfEntries * sizeof(EFI_ACPI_5_1_GIC_STRUCTURE));

      for (Count1 = 0; Count1 < ArmProcessorTable->NumberOfEntries; Count1++ ) {
        CopyMem(&EntryPointer[Count1], &APICProcessorRecordTemplate, sizeof(EFI_ACPI_5_1_GIC_STRUCTURE));
        EntryPointer[Count1].AcpiProcessorUid = (ArmCoreInfoTable[Count1].ClusterId) << 8 |
                                  ArmCoreInfoTable[Count1].CoreId;
        EntryPointer[Count1].CPUInterfaceNumber = Count1;
        EntryPointer[Count1].MPIDR = EntryPointer[Count1].AcpiProcessorUid;
        /* FixMe: Work around for non Redhat kernel */
        if (PcdGet32 (PcdBootingLinuxUEFI) == 1)
          EntryPointer[Count1].ParkedAddress = ArmCoreInfoTable[Count1].MailboxSetAddress + CPU_OFFSET;
        else
          EntryPointer[Count1].ParkedAddress = ArmCoreInfoTable[Count1].MailboxSetAddress;
      }

      CopyMem(ApicTablePointer, &APICProcessorTableHeaderTemplate,
                          sizeof(EFI_ACPI_5_1_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER));

      ApicTablePointer->Header.Length = Size;
      CopyMem(ApicTablePointer->Header.OemId, "APM   ",
                    sizeof(ApicTablePointer->Header.OemId));
      ApicTablePointer->Header.OemTableId = SIGNATURE_64('X', 'G', 'E', 'N', 'E', ' ', ' ', ' ');
      ApicTablePointer->Header.OemRevision = 3;
      ApicTablePointer->Header.CreatorId = PcdGet32 (PcdAcpiDefaultCreatorId);
      ApicTablePointer->Header.CreatorRevision = PcdGet32 (PcdAcpiDefaultCreatorRevision);

      CopyMem(GicDistributePointer, &APICGicDistributerTemplate,
                                sizeof(EFI_ACPI_5_1_GIC_DISTRIBUTOR_STRUCTURE));

      ApicAcpiTableChecksum((UINT8 *)ApicTablePointer, ApicTablePointer->Header.Length);

      Status = AcpiTableProtocol->InstallAcpiTable (
                                    AcpiTableProtocol,
                                    (VOID *)ApicTablePointer,
                                    ApicTablePointer->Header.Length,
                                    &ApicTableKey
                                    );
      if (EFI_ERROR (Status)) {
        FreePool ((VOID *)ApicTablePointer);
        return Status;
      }
      break;
    }
  }

  if (Count == gST->NumberOfTableEntries)
    return EFI_INVALID_PARAMETER;

  return EFI_SUCCESS;
}
