/** @file
*
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
*  This variation of the Pre Pi Multi-Processor Core implements the
*  Multi-Processor Parking Protocol as required by Windows.
*
**/

#include "PrePi.h"

#include <Library/ArmGicLib.h>

#include <Ppi/ArmMpCoreInfo.h>

VOID
PrimaryMain (
  IN  UINTN                     UefiMemoryBase,
  IN  UINTN                     StacksBase,
  IN  UINTN                     GlobalVariableBase,
  IN  UINT64                    StartTimeStamp
  )
{
  DEBUG ((DEBUG_INIT, "(MPPP)PrimaryMain: Enter:\n"));

  // Enable the GIC Distributor
  ArmGicEnableDistributor(PcdGet32(PcdGicDistributorBase));

  // In some cases, the secondary cores are waiting for an SGI from the next stage boot loader to resume their initialization
  if (PcdGetBool(PcdSendSgiToBringUpSecondaryCores)) {
    // Sending SGI to all the Secondary CPU interfaces
    ArmGicSendSgiTo (PcdGet32(PcdGicDistributorBase), ARM_GIC_ICDSGIR_FILTER_EVERYONEELSE, 0x0E, PcdGet32 (PcdGicSgiIntId));
  }

  PrePiMain (UefiMemoryBase, StacksBase, GlobalVariableBase, StartTimeStamp);

  // We must never return
  ASSERT(FALSE);
}

VOID
SecondaryMain (
  IN  UINTN                     MpId
  )
{
  EFI_STATUS              Status;
  ARM_MP_CORE_INFO_PPI    *ArmMpCoreInfoPpi;
  UINTN                   Index;
  UINTN                   ArmCoreCount;
  ARM_CORE_INFO           *ArmCoreInfoTable;
  UINT32                  ClusterId;
  UINT32                  CoreId;
  VOID                    (*Jump)(VOID *MailboxAddr);

  UINT32                  *MailboxAddr;
  UINT32                  *ProcessorIdAddr;
  UINT64                  *JumpAddressAddr;

  UINTN                   AcknowledgeInterrupt;
  UINTN                   InterruptId;
  UINT32                  ProcessorId;
  UINTN                   JumpAddress;;

  // This must be set for MPPP because this stack MUST be permanent reserved memory usable
  // after UEFI has ExitBootServices.
  ASSERT(PcdGet64(PcdCPUCoresStackBase));

  ClusterId = GET_CLUSTER_ID(MpId);
  CoreId    = GET_CORE_ID(MpId);

  MailboxAddr = (UINT32 *) (PcdGet32(PcdCPUCoresMPPPMailboxBase) + (CoreId * PcdGet32(PcdCPUCoresMPPPMailboxSize)));

  ProcessorIdAddr = &MailboxAddr[0];
  // SecondaryMailboxAddr[1] is reserved
  JumpAddressAddr = (UINT64 *) (&MailboxAddr[2]);

  DEBUG ((DEBUG_INIT, "(MPPP)SecondaryMain: Enter: MpId=0x%8.8X, MailboxAddr=0x%8.8X\n",
          MpId,
          MailboxAddr));

  // On MP Core Platform we must implement the ARM MP Core Info PPI (gArmMpCoreInfoPpiGuid)
  Status = GetPlatformPpi (&gArmMpCoreInfoPpiGuid, (VOID**)&ArmMpCoreInfoPpi);
  ASSERT_EFI_ERROR (Status);

  ArmCoreCount = 0;
  Status = ArmMpCoreInfoPpi->GetMpCoreInfo (&ArmCoreCount, &ArmCoreInfoTable);
  ASSERT_EFI_ERROR (Status);

  // Find the core in the ArmCoreTable
  for (Index = 0; Index < ArmCoreCount; Index++) {
    if ((ArmCoreInfoTable[Index].ClusterId == ClusterId) && (ArmCoreInfoTable[Index].CoreId == CoreId)) {
      break;
    }
  }

  // The ARM Core Info Table must define every core
  ASSERT (Index != ArmCoreCount);

  // Clear Secondary cores MailBox
  if (ArmCoreInfoTable[Index].MailboxClearAddress != 0) {
    MmioWrite32 (ArmCoreInfoTable[Index].MailboxClearAddress, ArmCoreInfoTable[Index].MailboxClearValue);
  }

  // Clear the mailbox
  ZeroMem(MailboxAddr, PcdGet32(PcdCPUCoresMPPPMailboxSize));

  // MPPP requires the ProcessorId field to be set to all ones.
  *ProcessorIdAddr = 0xFFFFFFFF;

  // Some boot firmware already enables the data and instruction caches.
  // MPPP requires that all caches are disabled and the MMU is off.
  ArmDisableCachesAndMmu();

  // MPPP requires that all caches are invalidated
  ArmInvalidateDataCache();
  ArmInvalidateInstructionCache();

  // MPPP requires that interrupts are disabled.
  // The WFI will wake up the core on interrupt but not take it.
  ArmDisableInterrupts();

  do {
    ArmCallWFI ();

    // Non-GIC implementations need another means to receive an interrupt.
    // Therefore, we support both the mailbox and the ARM GIC as options.
    // When the ARM GIC is used the mailbox code does nothing.
    if (ArmCoreInfoTable[Index].MailboxClearAddress != 0) {
        // Read the mailbox
        MmioRead32 (ArmCoreInfoTable[Index].MailboxGetAddress);

        // Clear Secondary cores MailBox
        MmioWrite32 (ArmCoreInfoTable[Index].MailboxClearAddress, ArmCoreInfoTable[Index].MailboxClearValue);
    }

    // Get the values from the mailbox
    ProcessorId = *ProcessorIdAddr;

    // Note that we cast the 64-bit address to the native architecture here.
    JumpAddress = (UINTN) (*JumpAddressAddr);

    // Acknowledge the interrupt and send End of Interrupt signal.
    AcknowledgeInterrupt = ArmGicAcknowledgeInterrupt (PcdGet32(PcdGicInterruptInterfaceBase), &InterruptId);
    // Check if it is a valid interrupt ID
    if (InterruptId < ArmGicGetMaxNumInterrupts (FixedPcdGet32 (PcdGicDistributorBase))) {
        // Got a valid SGI number hence signal End of Interrupt
        ArmGicEndOfInterrupt (FixedPcdGet32 (PcdGicInterruptInterfaceBase), AcknowledgeInterrupt);
    }

    DEBUG ((DEBUG_INIT, "(MPPP)SecondaryMain: Wakeup: MpId=0x%8.8X, ProcId=0x%8.8X, JumpAddress=0x%8.8X\n",
            MpId,
            ProcessorId,
            (UINT32) JumpAddress));

  }
  while ( (ProcessorId != CoreId) ||
          (JumpAddress == 0) );

  DEBUG ((DEBUG_INIT, "(MPPP)SecondaryMain: Exit: MpId=0x%8.8X, JumpAddress=0x%8.8X\n",
          MpId,
          (UINT32) JumpAddress));

  // Acknowledge the jump address by clearing it
  *JumpAddressAddr = 0;

  // Jump to secondary core entry point.
  Jump = (VOID (*)()) (JumpAddress);

  Jump(MailboxAddr);

  // The secondaries shouldn't reach here
  ASSERT(FALSE);
}

