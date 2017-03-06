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
#include <Library/BaseMemoryLib.h>

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
        if (count > MAILBOX_MAX_POLL)
        {
            return FALSE;
        }
    } while ((*Value & MAILBOX_CHANNEL_MASK) != Channel);

    *Value &= ~MAILBOX_CHANNEL_MASK;

    return TRUE;
}

BOOLEAN BcmMailboxWrite(
    IN UINT32 Channel,
    IN UINT32 Value
    )
{
    UINT32 count = 0;
    UINT32 MBStatus = MAILBOX_STATUS_FULL;

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

    MmioWrite32(MAILBOX_WRITE_REG, (Value & ~MAILBOX_CHANNEL_MASK) | Channel);

    return TRUE;
}

EFI_STATUS
MailboxProperty(
    IN UINT32 Channel,
    MAILBOX_HEADER *pMbProperty
    )
{
    UINT32 MBStatus = 0;
    UINT32 MBData;
    UINT32 BufferSize;

    //
    // Cannot allocate memory from the heap because memory allocation
    // services may not be available yet, for example when this is
    // called by SerialPortInitialize() early in SEC phase.
    // This memory must be cache-size aligned, which on Pi is 64 bytes.
    // This is static because stack size is limited and the mailbox
    // is non-reentrant.
    //
    static UINT8 SharedMem[2048] __attribute__((aligned(64)));

    BufferSize = pMbProperty->BufferSize;
    if (BufferSize > sizeof(SharedMem))
    {
        //
        // Cannot debug print here as serial port may not be initialized yet
        //
        return EFI_OUT_OF_RESOURCES;
    }

    CopyMem(SharedMem, pMbProperty, BufferSize);
    WriteBackInvalidateDataCacheRange(SharedMem, BufferSize);
    MBData = ((UINT32)SharedMem) | UNCACHED_ADDRESS_MASK;

    if(!BcmMailboxWrite(Channel, MBData))
    {
        return EFI_DEVICE_ERROR;
    }

    // Wait for the completion on the ARM to GPU channel
    if(!BcmMailboxRead(Channel, &MBStatus))
    {
        return EFI_DEVICE_ERROR;
    }

    InvalidateDataCacheRange(SharedMem, BufferSize);
    CopyMem(pMbProperty, SharedMem, BufferSize);

    return EFI_SUCCESS;
}
