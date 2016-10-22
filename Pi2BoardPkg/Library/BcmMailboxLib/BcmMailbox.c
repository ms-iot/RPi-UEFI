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
#include <Bcm2836Mailbox.h>
#include <Library/CacheMaintenanceLib.h>

BOOLEAN BcmMailboxRead(
    IN UINT32 Channel,
    OUT UINT32* Value
    )
{
    UINT32 count = 0;
    UINT32 MBStatus = MAILBOX_STATUS_EMPTY;

    if (Value == NULL)
    {
        return FALSE;
    }
    
    DEBUG((EFI_D_VERBOSE, "BcmMailboxRead waiting for Mailbox\n"));

    MBStatus = MmioRead32(MAILBOX_STATUS_REG);
    while (MBStatus & MAILBOX_STATUS_EMPTY)
    {
        MBStatus = MmioRead32(MAILBOX_STATUS_REG);
        count++;
        if (count > MAILBOX_MAX_POLL)
        {
            return FALSE;
        }
    }

    count = 0;
    do
    {
        *Value = MmioRead32(MAILBOX_READ_REG);
        DEBUG((DEBUG_INFO, "BcmMailboxRead *Value = 0x%8.8X\n", *Value));
        if (count > MAILBOX_MAX_POLL)
        {
            return FALSE;
        }
    } while ((*Value & MAILBOX_CHANNEL_MASK) != Channel);

    *Value &= ~MAILBOX_CHANNEL_MASK;
    DEBUG((EFI_D_VERBOSE, "BcmMailboxRead read Value : %x\n", *Value));

    return TRUE;
}

BOOLEAN BcmMailboxWrite(
    IN UINT32 Channel,
    IN UINT32 Value
    )
{
    UINT32 count = 0;
    UINT32 MBStatus = MAILBOX_STATUS_FULL;

    DEBUG((EFI_D_VERBOSE, "BcmMailboxWrite waiting for Mailbox\n"));

    // Wait until there is available free buffer for use
    while (MBStatus & MAILBOX_STATUS_FULL)
    {
        MBStatus = MmioRead32(MAILBOX_STATUS_REG);
        count++;
        if (count > MAILBOX_MAX_POLL)
        {
            return FALSE;
        }
    }

    DEBUG((EFI_D_VERBOSE, "BcmMailboxWrite writing value : %x to Channel : %x\n", Value, Channel));

    MmioWrite32(MAILBOX_WRITE_REG, (Value & ~MAILBOX_CHANNEL_MASK) | Channel);

    return TRUE;
}

EFI_STATUS
MailboxProperty(
    IN UINT32 Channel,
    volatile MAILBOX_HEADER *pMbProperty
    )
{
    UINT32 MBStatus = 0;
    UINT32 MBData = ((UINT32)pMbProperty) | UNCACHED_ADDRESS_MASK;

    WriteBackInvalidateDataCacheRange((void*)pMbProperty, pMbProperty->BufferSize);
    if(!BcmMailboxWrite(Channel, MBData))
    {
        DEBUG((DEBUG_ERROR, "Failed to write MailboxProperty MBStatus 0x%x\n", MBStatus));
        return EFI_DEVICE_ERROR;
    }

    // Wait for the completion on the ARM to GPU channel
    if(!BcmMailboxRead(Channel, &MBStatus))
    {
        DEBUG((DEBUG_ERROR, "FB info update fail to complete MBStatus 0x%x\n", MBStatus));
        return EFI_DEVICE_ERROR;
    }
    WriteBackInvalidateDataCacheRange((void*)pMbProperty, pMbProperty->BufferSize);

    return EFI_SUCCESS;
}
