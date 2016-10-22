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

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Bcm2836.h>

#include <LedLib.h>


VOID
LedInit (
  )
{
    static BOOLEAN g_bInitComplete = 0;

    if (g_bInitComplete)
    {
        return;
    }

    /* Setup GPIO47 ("ACT" LED) as Output */
    /* This uses r-m-w as other pins may have already been configured */
    {
        UINT32 u32GPSEL4 = MmioRead32(GPIO_GPFSEL4);

        /* Mask off to 0 the 3 function bits for this GPIO pin */
        u32GPSEL4 &= ~0x00E00000;

        /* OR in the setting to enable the pin as a GPIO output */
        u32GPSEL4 |=  0x00200000;

        MmioWrite32(GPIO_GPFSEL4, u32GPSEL4);
    }

    g_bInitComplete = TRUE;
}

VOID
LedSetOk (
  IN  BOOLEAN On
  )
{
    if (On)
    {
        MmioWrite32(GPIO_GPSET1, 0x00008000);
    }
    else
    {
        MmioWrite32(GPIO_GPCLR1, 0x00008000);
    }
}

VOID
LedFlashOk (
  IN  UINTN PeriodInMicroSec,
  IN  UINTN Count
  )
{
    ASSERT(FALSE);
}

