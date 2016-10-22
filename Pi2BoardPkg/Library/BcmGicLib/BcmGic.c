/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <Library/ArmLib.h>
#include <Library/DebugLib.h>
#include <Library/ArmGicLib.h>
#include <Library/ArmPlatformLib.h>

#include <Ppi/ArmMpCoreInfo.h>

VOID
EFIAPI
ArmGicEnableInterruptInterface (
  IN  INTN          GicInterruptInterfaceBase
  )
{
}

VOID
EFIAPI
ArmGicEnableDistributor (
  IN  INTN          GicDistributorBase
  )
{
    DEBUG ((DEBUG_INIT, "(BCM)ArmGicEnableDistributor\n"));
}

UINTN
EFIAPI
ArmGicGetMaxNumInterrupts (
  IN  INTN          GicDistributorBase
  )
{
  return 32;
}

VOID
EFIAPI
ArmGicSendSgiTo (
  IN  INTN          GicDistributorBase,
  IN  INTN          TargetListFilter,
  IN  INTN          CPUTargetList,
  IN  INTN          SgiId
  )
{
  // In this interface we ONLY support this API to release the secondary cores and that
  // has nothing to do with interrupts however we maintain the GIC interface for compatibilty
  // with real ARM GIC implementations.
  ASSERT(TargetListFilter == ARM_GIC_ICDSGIR_FILTER_EVERYONEELSE);
  ASSERT(CPUTargetList = 0x0E);
  ASSERT(SgiId == 0);

  {
      EFI_STATUS              Status;
      UINTN                   Index;
      UINTN                   ArmCoreCount;
      ARM_CORE_INFO           *ArmCoreInfoTable;
      UINTN                   MpId;
      UINT32                  ClusterId;
      UINT32                  CoreId;
      UINT32                  SecondaryEntryAddr;

      MpId      = ArmReadMpidr();
      ClusterId = GET_CLUSTER_ID(MpId);
      CoreId    = GET_CORE_ID(MpId);

      SecondaryEntryAddr = PcdGet32(PcdCpuResetAddress);

      DEBUG ((DEBUG_INIT, "(BCM)ArmGicSendSgiTo: Enter: MpId=0x%8.8X, SecondaryEntryAddr=0x%8.8X\n",
              MpId,
              SecondaryEntryAddr));

      {
        UINTN                   PpiListSize;
        EFI_PEI_PPI_DESCRIPTOR  *PpiList;
        ARM_MP_CORE_INFO_PPI    *MpCoreInfoPpi;

        ArmPlatformGetPlatformPpiList(&PpiListSize, &PpiList);

        // We expect a single entry as defined in the Pi2 Board Pkg containing only the
        // GetMpCoreInfo funciton.
        ASSERT(PpiListSize == sizeof(EFI_PEI_PPI_DESCRIPTOR));

        MpCoreInfoPpi = (ARM_MP_CORE_INFO_PPI *) PpiList[0].Ppi;

        ArmCoreCount = 0;
        Status = MpCoreInfoPpi->GetMpCoreInfo(&ArmCoreCount, &ArmCoreInfoTable);
        ASSERT_EFI_ERROR (Status);
      }

      // Loop to send the secondary cores their effective address to run from
      for (Index = 0; Index < ArmCoreCount; Index++)
      {
        // Skip ourselves (the primary core)
        if ((ArmCoreInfoTable[Index].ClusterId == ClusterId) && (ArmCoreInfoTable[Index].CoreId == CoreId))
        {
          continue;
        }

        DEBUG ((DEBUG_INIT, "(BCM)ArmGicSendSgiTo: ClusterId=0x%X, CoreId=0x%X, MBox=0x%8.8X\n",
                ArmCoreInfoTable[Index].ClusterId,
                ArmCoreInfoTable[Index].CoreId,
                ArmCoreInfoTable[Index].MailboxSetAddress));

        // Release the hounds
        MmioWrite32(ArmCoreInfoTable[Index].MailboxSetAddress, SecondaryEntryAddr);

        // Pause 200ms to let the secondary cores start, use the serial port for debug
        // (otherwise the serial output will be illegible) and fall into UEFI parking.
        MicroSecondDelay(200 * 1000);
      }

      // This is a built in self test for the MPPP that sets up the mailbox and triggers
      // an unpark. The test simply has the cores restart Pre Pi init to return back
      // to being parked.
      DEBUG ((DEBUG_INIT, "**** Multi-Processor Parking Protocol Self Test ****\n"));
      MicroSecondDelay(200 * 1000);

      // Loop to send the secondary cores their effective address to run from
      for (Index = 0; Index < ArmCoreCount; Index++)
      {
        UINT32   *MailboxAddr;

        // Skip ourselves (the primary core)
        if ((ArmCoreInfoTable[Index].ClusterId == ClusterId) && (ArmCoreInfoTable[Index].CoreId == CoreId))
        {
          continue;
        }

        // Note that this requires the mailboxes to reside somewhere within the first 4Gb of memory on
        // 64-bit systems in this release of the firmware.
        MailboxAddr = (UINT32 *) (PcdGet32(PcdCPUCoresMPPPMailboxBase) + (Index * PcdGet32(PcdCPUCoresMPPPMailboxSize)));

        MailboxAddr[2] = (UINT32) PcdGet64(PcdFvBaseAddress);
        MailboxAddr[0] = ArmCoreInfoTable[Index].CoreId;

        DEBUG ((DEBUG_INIT, "**** (%d)Trigger...\n", Index));

        // Trigger
        MmioWrite32(ArmCoreInfoTable[Index].MailboxSetAddress, 1);

        // Pause 200ms to let the secondary core start, use the serial port for debug
        // and fall into UEFI parking.
        MicroSecondDelay(200 * 1000);

        // The MPPP code should have acknowledged the trigger by:
        // 1) Resetting the mailbox.
        // 2) Clearing the JumpAddress field.
        {
          UINT32 Mailbox;

          Mailbox = MmioRead32(ArmCoreInfoTable[Index].MailboxGetAddress);

          DEBUG ((DEBUG_INIT, "**** (%d)Ack: Mailbox=0x%d, JumpAddress=0x%8.8X\n",
                 Index,
                 Mailbox,
                 MailboxAddr[2]));

          ASSERT((Mailbox == 0) && (MailboxAddr[2] == 0));
        }
      }
  }

  DEBUG ((DEBUG_INIT, "(BCM)ArmGicSendSgiTo: Exit:\n"));

}


RETURN_STATUS
EFIAPI
ArmGicAcknowledgeInterrupt (
  IN  UINTN          GicInterruptInterfaceBase,
  OUT UINTN          *InterruptId
  )
{
  return RETURN_SUCCESS;
}


VOID
EFIAPI
ArmGicEndOfInterrupt (
  IN UINTN           GicInterruptInterfaceBase,
  IN UINTN           Source
  )
{
  return;
}