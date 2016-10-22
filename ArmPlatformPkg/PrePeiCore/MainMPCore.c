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

#include <Library/ArmGicLib.h>

#include <Ppi/ArmMpCoreInfo.h>

#include "PrePeiCore.h"

/*
 * This is the main function for secondary cores. They loop around until a non Null value is written to
 * SYS_FLAGS register.The SYS_FLAGS register is platform specific.
 * Note:The secondary cores, while executing secondary_main, assumes that:
 *      : SGI 0 is configured as Non-secure interrupt
 *      : Priority Mask is configured to allow SGI 0
 *      : Interrupt Distributor and CPU interfaces are enabled
 *
 */
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>

#include <Platform/ArmPlatform.h>

/// Assembler function to jump to the second parameter
/// which allows us to preserve the mailbox address in R0/X0.
VOID
WOASecondaryStart (
    IN UINTN    MailboxBase,
    IN UINTN    JumpAddr
    );

VOID
WOAMPParkingProto (
    IN  UINTN   MpId,
    OUT UINTN   *SecondaryEntryAddr
    )
{
  UINTN   WOAMailboxBase;
  UINTN   FwMailboxBase;
  UINT32  CoreId;
  UINT32  ClusterId;
  UINT32  GicId;
  UINT32  CharCount;
  CHAR8   MPLogBuffer[128];
  UINTN   AcknowledgeInterrupt;
  UINTN   InterruptId;

  CoreId = GET_CORE_ID (MpId);
  ClusterId = GET_CLUSTER_ID (MpId & FixedPcdGet32 (PcdArmPrimaryCoreMask));
  GicId = ArmPlatformGetGicId ();
  WOAMailboxBase = ((UINTN) FixedPcdGet64 (PcdCpuParkedAddress)) + (ClusterId * MAX_CORES_PERCLUSTER + CoreId) * PARKEDCPU_MAILBOX_SIZE;

  DEBUG ((EFI_D_INFO,"MpId = 0x%x, GicId = 0x%x, WOAMailboxBase = 0x%p\n", MpId, GicId, WOAMailboxBase));
  // Firmware Mailbox Initialization
  FwMailboxBase = WOAMailboxBase + (PARKEDCPU_MAILBOX_SIZE >> 1);
  MmioWrite64 (FwMailboxBase, MpId);            // MpId
  ArmDataSyncronizationBarrier ();
  MmioWrite32 ((FwMailboxBase + 0x8), GicId);   // GicId
  ArmDataSyncronizationBarrier ();

  // OS Mailbox Initialization
  MmioWrite64 ((WOAMailboxBase + 0x8), 0);      // jump address
  ArmDataSyncronizationBarrier ();
  MmioWrite32 (WOAMailboxBase, 0xFFFFFFFFU);    // processor ID
  ArmDataSyncronizationBarrier ();

  while (*SecondaryEntryAddr == 0) {
    ArmCallWFI ();
    ArmDataSyncronizationBarrier ();

    if (MmioRead32 (WOAMailboxBase) == GicId) {
      *SecondaryEntryAddr = MmioRead64 (WOAMailboxBase + 0x8);

#ifdef ARM_CPU_AARCH64
      CharCount = AsciiSPrint (MPLogBuffer, sizeof (MPLogBuffer),
                               "\r\n--- GIC_ID #0x%x start SUCCESS, jump to #0x%08x_%08x ---\r\n",
                               GicId, ((*SecondaryEntryAddr)>>32), ((UINT32)(*SecondaryEntryAddr)));
#else
      CharCount = AsciiSPrint (MPLogBuffer, sizeof (MPLogBuffer),
                               "\r\n--- GIC_ID #0x%x start SUCCESS, jump to #0x%08x ---\r\n",
                               GicId, ((UINT32)(*SecondaryEntryAddr)));
#endif
      SerialPortWrite ((UINT8*) MPLogBuffer, CharCount);
    }
#ifdef DEBUG_CORE_PARKING
    else {
      CharCount = AsciiSPrint (MPLogBuffer, sizeof (MPLogBuffer),
                               "\r\n!!! GIC_ID #0x%x start FAIL, wakeup ID #0x%016lx !!!\r\n",
                               GicId, MmioRead64 (WOAMailboxBase));
      SerialPortWrite ((UINT8*) MPLogBuffer, CharCount);
    }
#endif
    // Acknowledge the interrupt and send End of Interrupt signal.
    AcknowledgeInterrupt = ArmGicAcknowledgeInterrupt (FixedPcdGet32 (PcdGicInterruptInterfaceBase), &InterruptId);
    // Check if it is a valid interrupt ID
    if (InterruptId < ArmGicGetMaxNumInterrupts (FixedPcdGet32 (PcdGicDistributorBase))) {
      // Got a valid SGI number hence signal End of Interrupt
      ArmGicEndOfInterrupt (FixedPcdGet32 (PcdGicInterruptInterfaceBase), AcknowledgeInterrupt);
    }

    ArmDataSyncronizationBarrier ();
  }

  // Write 0 to jump-addr to ack
  MmioWrite64 ((WOAMailboxBase + 0x8), 0);
  ArmDataSyncronizationBarrier ();
}

VOID
EFIAPI
SecondaryMain (
  IN UINTN MpId
  )
{
  UINT32  CoreId;
  UINT32  ClusterId;
  UINTN   SecondaryEntryAddr;

  UINTN   AcknowledgeInterrupt;
  UINTN   InterruptId;
  SecondaryEntryAddr = 0;
  // Enable the GIC CPU Interface
  ArmGicEnableInterruptInterface (FixedPcdGet32 (PcdGicInterruptInterfaceBase));
  // Enable NS-SGI0 - This needs to be done per CPU
  MmioOr32 (FixedPcdGet32 (PcdGicDistributorBase) + ARM_GIC_ICDISER, 0x1);

  CoreId = GET_CORE_ID (MpId);
  ClusterId = GET_CLUSTER_ID (MpId & FixedPcdGet32 (PcdArmPrimaryCoreMask));

  // WFI - Wait for Primary core to clear Fw Mailbox
  ArmDataSyncronizationBarrier ();
  ArmCallWFI ();

  // Acknowledge the interrupt and send End of Interrupt signal.
  AcknowledgeInterrupt = ArmGicAcknowledgeInterrupt (FixedPcdGet32 (PcdGicInterruptInterfaceBase), &InterruptId);
  // Check if it is a valid interrupt ID
  if (InterruptId < ArmGicGetMaxNumInterrupts (FixedPcdGet32 (PcdGicDistributorBase))) {
    // Got a valid SGI number hence signal End of Interrupt
    ArmGicEndOfInterrupt (FixedPcdGet32 (PcdGicInterruptInterfaceBase), AcknowledgeInterrupt);
  }

  //DEBUG ((EFI_D_WARN,"SecondaryMain: ClusterId = %d CoreId = %d\n", ClusterId, CoreId));

  WOAMPParkingProto (MpId, &SecondaryEntryAddr);
  WOASecondaryStart (
    (((UINTN)FixedPcdGet64 (PcdCpuParkedAddress)) + (ClusterId * MAX_CORES_PERCLUSTER + CoreId) * PARKEDCPU_MAILBOX_SIZE),
    SecondaryEntryAddr
  );

  // The secondaries shouldn't reach here
  ASSERT(FALSE);
}


VOID
EFIAPI
PrimaryMain (
  IN  EFI_PEI_CORE_ENTRY_POINT  PeiCoreEntryPoint
  )
{
  EFI_SEC_PEI_HAND_OFF        SecCoreData;
  UINTN                       PpiListSize;
  EFI_PEI_PPI_DESCRIPTOR      *PpiList;
  UINTN                       TemporaryRamBase;
  UINTN                       TemporaryRamSize;
  UINTN                       FwMailboxBase;
  UINT32                      ClusterId;
  UINT32                      CoreId;
  UINT32                      GicId;
  UINTN                       MpId;

  // Use the ID to make processor-specific choices.
  MpId = ArmReadMpidr();

  CreatePpiList (&PpiListSize, &PpiList);

  // Enable the GIC Distributor
  ArmGicEnableDistributor (FixedPcdGet32 (PcdGicDistributorBase));
  // Enable NS-SGI0 - This needs to be done per CPU
  MmioOr32 (FixedPcdGet32 (PcdGicDistributorBase) + ARM_GIC_ICDISER, 0x1);

  // Clear Fw Mailbox
  for (ClusterId = 0; ClusterId < MAX_CLUSTERS; ++ClusterId) {
    for (CoreId = 0; CoreId < MAX_CORES_PERCLUSTER; ++CoreId) {
      FwMailboxBase = ((UINTN) FixedPcdGet64 (PcdCpuParkedAddress)) + ((ClusterId * MAX_CORES_PERCLUSTER + CoreId) * PARKEDCPU_MAILBOX_SIZE) + (PARKEDCPU_MAILBOX_SIZE >> 1);
      // Initialize the MpID and GicID to uninitialized value
      MmioWrite64 (FwMailboxBase, 0xFFFFFFFFFFFFFFFFULL);     // MpId
      MmioWrite32 ((FwMailboxBase + 0x8), 0xFFFFFFFFU);       // GicId
      ArmDataSyncronizationBarrier ();
    }
  }

  // Update the Mailbox for the Primary core
  CoreId = GET_CORE_ID (MpId);
  ClusterId = GET_CLUSTER_ID (MpId & FixedPcdGet32 (PcdArmPrimaryCoreMask));
  GicId = ArmPlatformGetGicId ();

  FwMailboxBase = ((UINTN)FixedPcdGet64 (PcdCpuParkedAddress)) + ((ClusterId * MAX_CORES_PERCLUSTER + CoreId) * PARKEDCPU_MAILBOX_SIZE) + (PARKEDCPU_MAILBOX_SIZE >> 1);
  MmioWrite32 ((FwMailboxBase + 0x8), GicId); // GicId
  ArmDataSyncronizationBarrier ();
  MmioWrite64 (FwMailboxBase, MpId);          // MpId
  ArmDataSyncronizationBarrier ();

  if (ArmPlatformGetCpuCount () > 1) {
    // Sending SGI to all the Secondary CPU interfaces
    DEBUG ((EFI_D_WARN,"PrimaryMain : Sending SGI 0x%x to wake up secondary cores\n", FixedPcdGet32 (PcdGicSgiIntId)));
    ArmGicSendSgiTo (FixedPcdGet32 (PcdGicDistributorBase), ARM_GIC_ICDSGIR_FILTER_EVERYONEELSE, 0xFE, FixedPcdGet32 (PcdGicSgiIntId));
  }

#ifdef ARM_CPU_AARCH64
  DEBUG ((EFI_D_WARN,"PrimaryMain [EL%d]: ClusterId = %d CoreId = %d GicID = %d\n", (ArmReadCurrentEL () == AARCH64_EL2 ? 2 : 1), ClusterId, CoreId, GicId));
#else
  DEBUG ((EFI_D_WARN,"PrimaryMain : ClusterId = %d CoreId = %d GicID = %d\n", ClusterId, CoreId, GicId));
#endif

  // Adjust the Temporary Ram as the new Ppi List (Common + Platform Ppi Lists) is created at
  // the base of the primary core stack
  PpiListSize = ALIGN_VALUE(PpiListSize, 0x4);
  TemporaryRamBase = (UINTN)PcdGet64 (PcdCPUCoresStackBase) + PpiListSize;
  TemporaryRamSize = (UINTN)PcdGet32 (PcdCPUCorePrimaryStackSize) - PpiListSize;

  // Make sure the size is 8-byte aligned. Once divided by 2, the size should be 4-byte aligned
  // to ensure the stack pointer is 4-byte aligned.
  TemporaryRamSize = TemporaryRamSize - (TemporaryRamSize & (0x8-1));

  //
  // Bind this information into the SEC hand-off state
  // Note: this must be in sync with the stuff in the asm file
  // Note also:  HOBs (pei temp ram) MUST be above stack
  //
  SecCoreData.DataSize               = sizeof(EFI_SEC_PEI_HAND_OFF);
  SecCoreData.BootFirmwareVolumeBase = (VOID *)(UINTN)PcdGet64 (PcdFvBaseAddress);
  SecCoreData.BootFirmwareVolumeSize = PcdGet32 (PcdFvSize);
  SecCoreData.TemporaryRamBase       = (VOID *)TemporaryRamBase; // We run on the primary core (and so we use the first stack)
  SecCoreData.TemporaryRamSize       = TemporaryRamSize;
  SecCoreData.PeiTemporaryRamBase    = SecCoreData.TemporaryRamBase;
  SecCoreData.PeiTemporaryRamSize    = SecCoreData.TemporaryRamSize / 2;
  SecCoreData.StackBase              = (VOID *)ALIGN_VALUE((UINTN)(SecCoreData.TemporaryRamBase) + SecCoreData.PeiTemporaryRamSize, 0x4);
  SecCoreData.StackSize              = (TemporaryRamBase + TemporaryRamSize) - (UINTN)SecCoreData.StackBase;

  // Jump to PEI core entry point
  PeiCoreEntryPoint (&SecCoreData, PpiList);
}
