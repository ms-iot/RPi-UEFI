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
**/

#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>

#include <BcmMailbox.h>

volatile MAILBOX_GET_GPIO_VIRT_ADDR MbGetGpiovirtAddr __attribute__((aligned(16)));

VOID
LedInit (
  )
{
    EFI_STATUS Status;

    ZeroMem((void*)&MbGetGpiovirtAddr, sizeof(MbGetGpiovirtAddr));
    MbGetGpiovirtAddr.Header.BufferSize = sizeof(MbGetGpiovirtAddr);
    MbGetGpiovirtAddr.Header.TagID = TAG_GET_GPIOVIRTBUF;
    MbGetGpiovirtAddr.Header.TagLength = 4;

    // Retrieve memory region that hold the GPIO state. 4 byte would represent
    // 1 pin. It looks like there is 2 GPIO pin expose by virtual GPIO.
    Status = MailboxProperty(
        MAILBOX_CHANNEL_PROPERTY_ARM_VC,
        (MAILBOX_HEADER*)&MbGetGpiovirtAddr
        );
    if (EFI_ERROR(Status)) 
    {
        DEBUG((DEBUG_ERROR, "Fail to query GPIO virtual buffer\n"));
        return;
    }

    // Convert to CPU alias
    MbGetGpiovirtAddr.GpioVirtAddr -= 0xC0000000;

    DEBUG((DEBUG_INIT, "GPIO virt address 0x%08x\n", MbGetGpiovirtAddr.GpioVirtAddr));
}

VOID
LedSetOk (
  IN  BOOLEAN On
  )
{
    UINT32 GpioCurrentState = MmioRead32(MbGetGpiovirtAddr.GpioVirtAddr);
    UINT16 EnableCount = GpioCurrentState >> 16;
    UINT16 DisableCount = (UINT16)(GpioCurrentState & 0xFFFF);

    // GPIO host track state by checking an enable and disable counter. It looks
    // like host might be polling since maintaining a counter allows it retrieve
    // any state change that is might have missed.
    if (On)
    {
        // Enable count is already higher nothing to do here.
        if (EnableCount > DisableCount)
        {
            return;
        }
        EnableCount++;

        MmioWrite32(MbGetGpiovirtAddr.GpioVirtAddr, ((EnableCount << 16) | DisableCount));
    }
    else
    {
        // Enable and disable count is already the same nothing to do here.
        if (EnableCount == DisableCount)
        {
            return;
        }
        DisableCount++;

        MmioWrite32(MbGetGpiovirtAddr.GpioVirtAddr, ((EnableCount << 16) | DisableCount));
    }

    ASSERT((EnableCount == DisableCount) || ((EnableCount - DisableCount) == 1));
}

VOID
LedFlashOk (
  IN  UINTN PeriodInMicroSec,
  IN  UINTN Count
  )
{
    ASSERT(FALSE);
}

