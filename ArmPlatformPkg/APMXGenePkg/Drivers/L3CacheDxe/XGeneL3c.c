/**
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * Author: Tuan Phan <tphan@apm.com>
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

#include <Guid/EventGroup.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/PrintLib.h>
#include <Library/TimerLib.h>
#include <Library/ArmLib.h>
#include <Library/SerialPortLib.h>
#include <Library/DebugLib.h>

#include "XGeneL3c.h"

#define EFUSE0_BIT_L3C_DISABLE0   0x8
#define EFUSE0_SHADOW_ADDR_ABS    0x1054a000
#define L3C_SIZE_CONFIG PcdGet32(PcdL3cSize)

 UINT32 RbBase  = RB_MASTER_REG_BASE;
 UINT32 CswBase = CSW_REG_BASE;
 UINT32 L3cBase = L3C_REG_BASE;

/* Return efuse l3c size in MBs (Valid Values: 0,2,4,8) */
UINT32 XgeneGetL3cSize(VOID)
{
  UINT32 Val;
  UINT32 Size = 0;
  UINT32 i;

  Val = MmioRead32(EFUSE0_SHADOW_ADDR_ABS);

  for (i=0; i<4; i++) {
    if (Val & (1 << (EFUSE0_BIT_L3C_DISABLE0 + i)))
      continue;

    Size += 2;
  }

  DEBUG ((EFI_D_VERBOSE, "EfuseL3csize: %d\n", Size));
  return Size;
}

VOID XGeneL3cInit(VOID)
{
  UINT32 Val;
  UINT32 L3cSizeConfig, L3cSizeHW;
  UINTN CharCount;
  CHAR8 Buffer[100];

  L3cSizeConfig = L3C_SIZE_CONFIG > XgeneGetL3cSize() ? XgeneGetL3cSize(): L3C_SIZE_CONFIG;
  if (L3cSizeConfig == 0)
    return;

  DEBUG ((EFI_D_VERBOSE, "L3cSizeConfig: %d\n", L3cSizeConfig));

  Val = MmioRead32(RbBase + RB_RBASR);

  if (!(Val & (1 << 16))) {
    /* disable l3c clk */
    Val = MmioRead32(CswBase + CSW_L3CCR);
    Val &= ~(1 << 11);      /* L3CCR.L3cClkEn */
    MmioWrite32(CswBase + CSW_L3CCR, Val);

    Val = MmioRead32(CswBase + CSW_L3CCR);
    Val &= ~(1 << 15);      /* L3CCR.L3cClkMacRst */
    MmioWrite32(CswBase + CSW_L3CCR, Val);

    MicroSecondDelay(1);

    /* enable l3c clk */
    Val = MmioRead32(CswBase + CSW_L3CCR);
    Val |= (1 << 11);       /* L3CCR.L3cClkEn */
    MmioWrite32(CswBase + CSW_L3CCR, Val);

    MicroSecondDelay(1);

    /* clear l3c reset */
    Val = MmioRead32(CswBase + CSW_L3RCR);
    Val &= ~(1 << 0);       /* L3RCR.ResetL3c */
    MmioWrite32(CswBase + CSW_L3RCR, Val);

    MicroSecondDelay(1);

    /* set L3cAvail in RB Agent status register */
    Val = MmioRead32(RbBase + RB_RBASR);
    Val |= (1 << 16);       /* RBASR.L3cAvail */
    MmioWrite32(RbBase + RB_RBASR, Val);
  }

  /* read l3c Size from h/w */
  Val = MmioRead32(L3cBase + L3C_CR);
  L3cSizeHW = (Val >> 24) & 0x3F;

  DEBUG ((EFI_D_VERBOSE, "L3cSizeHW: %d\n", L3cSizeHW));

  if (L3cSizeHW > L3cSizeConfig)
    L3cSizeHW = L3cSizeConfig;

  /* Enable l3c array, set l3c Size, hash mode */
  Val = ((1 << 31) | (L3cSizeHW << 18));
  MmioWrite32(L3cBase + L3C_CR, Val);

  /* Clear l3c tags */
  MmioWrite32(L3cBase + L3C_OPTR0, 0);
  MmioWrite32(L3cBase + L3C_OPTR1, 0);

  Val = ((1 << 28) | (1 << 25) | ((L3cSizeHW * 4 - 1) << 8));
  MmioWrite32(L3cBase + L3C_OPCR, Val);

  /* wait till oper is complete */
  while (1) {
          Val = MmioRead32(L3cBase + L3C_OPCR);
          if (!(Val & (1 << 31)))
                  break;
  }

  /* enable l3c scrube */
  MmioWrite32(L3cBase + L3C_SCRUB, 0x0000ffff);
  Val = MmioRead32(L3cBase + L3C_CR);
  Val |= 0x00010000;       /* L3C SCRUB */
  MmioWrite32(L3cBase + L3C_CR, Val);

  /* enable l3c snoop & alloc */
  Val = MmioRead32(CswBase + CSW_CSWSER);
  Val |= ((1 << 18) | (1 << 16));
  MmioWrite32(CswBase + CSW_CSWSER, Val);

  CharCount = AsciiSPrint (Buffer,sizeof (Buffer),"L3c Cache: %dMB\n", L3cSizeHW);
  SerialPortWrite ((UINT8 *) Buffer, CharCount);
}

/**
  Notify function for event group EFI_EVENT_GROUP_READY_TO_BOOT. This is used
  to configure the system clock and PHY accordingly.

  @param[in]  Event   The Event that is being processed.
  @param[in]  Context The Event Context.

**/
VOID
EFIAPI
OnExitBootService(
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  ArmDisableInterrupts();
  // Clean before Disable else the Stack gets corrupted with old data.
  ArmCleanDataCache ();
  ArmDisableDataCache ();
  // Invalidate all the entries that might have snuck in.
  ArmInvalidateDataCache ();

  // Disable and invalidate the instruction cache
  ArmDisableInstructionCache ();
  ArmInvalidateInstructionCache ();

  // Turn off MMU
  ArmDisableMmu();

  XGeneL3cInit();
}

EFI_STATUS
L3CacheInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_EVENT  ExitBootEvent;

  //
  // Register notify function to configure system on ReadyToBoot Event
  Status = gBS->CreateEventEx (
        EVT_NOTIFY_SIGNAL,
        TPL_NOTIFY,
        OnExitBootService,
        NULL,
        &gEfiEventExitBootServicesGuid,
        &ExitBootEvent
        );
  ASSERT_EFI_ERROR(Status);

  return EFI_SUCCESS;
}
