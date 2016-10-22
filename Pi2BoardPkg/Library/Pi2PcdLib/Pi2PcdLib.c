#/** @file
#
#  Copyright (c), Microsoft Corporation. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#**/

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>

#include <Pi2Board.h>
#include <BcmMailbox.h>

typedef struct
{
    UINT64 TokenNumber;
    UINT64 Value;
    UINT64 DefaultValue;
}PCD_DYNAMIC_VALUE;

PCD_DYNAMIC_VALUE DynamicPCDValue[] =
{
    { PcdToken(PcdSystemMemorySize), 0, 0 },
    { PcdToken(PcdGpuMemorySize), 0, 0 },
};

extern MAILBOX_GET_MEMORY MbGetMemory;

PCD_DYNAMIC_VALUE* GetDynamicPCD (
    IN UINTN             TokenNumber
    )
{
    UINTN i;

    for (i = 0; i < (sizeof(DynamicPCDValue) / sizeof(PCD_DYNAMIC_VALUE)); ++i) {
        if (DynamicPCDValue[i].TokenNumber == TokenNumber) {
            return &DynamicPCDValue[i];
        }
    }

    return NULL;
}

/**
  This function retrieves a value for a dynamic token.

  @param[in]  TokenNumber The PCD token number to retrieve a current value for.

  @return Returns the 64-bit value for the token specified by TokenNumber.

**/
UINT64
EFIAPI
LibPcdGet64 (
    IN UINTN             TokenNumber
    )
{
    PCD_DYNAMIC_VALUE* Pcd;

    Pcd = GetDynamicPCD(TokenNumber);
    ASSERT(Pcd != NULL);

    // Use lazy initialization to assign dynamic PCD values
    if (Pcd->Value == Pcd->DefaultValue) {
        switch (Pcd->TokenNumber) {
        // Query ARM System Memory Size
        case PcdToken(PcdSystemMemorySize):
            {
                EFI_STATUS Status;
                ZeroMem((void*)&MbGetMemory, sizeof(MbGetMemory));
                MbGetMemory.Header.BufferSize = sizeof(MbGetMemory);
                MbGetMemory.Header.TagID = TAG_GET_ARM_MEMORY;
                MbGetMemory.Header.TagLength = 8;

                Status = MailboxProperty(MAILBOX_CHANNEL_PROPERTY_ARM_VC, (MAILBOX_HEADER*)&MbGetMemory);
                if (Status == EFI_SUCCESS) {
                    PcdSet64(PcdSystemMemorySize, (MbGetMemory.Size - FixedPcdGet64(PcdSystemMemoryBase)));
                } else {
                    // Assert immediately because this means VC firmware has failed
                    ASSERT(FALSE);
                }
                DEBUG((DEBUG_VERBOSE, "LibPcdGet64: PcdSystemMemorySize=0x%8.8X\n", PcdGet64(PcdSystemMemorySize)));
            }
            break;
        // Query VC GPU Memory Size
        case PcdToken(PcdGpuMemorySize):
            {
                EFI_STATUS Status;
                ZeroMem((void*)&MbGetMemory, sizeof(MbGetMemory));
                MbGetMemory.Header.BufferSize = sizeof(MbGetMemory);
                MbGetMemory.Header.TagID = TAG_GET_VC_MEMORY;
                MbGetMemory.Header.TagLength = 8;

                Status = MailboxProperty(MAILBOX_CHANNEL_PROPERTY_ARM_VC, (MAILBOX_HEADER*)&MbGetMemory);
                if (Status == EFI_SUCCESS) {
                    PcdSet64(PcdGpuMemorySize, MbGetMemory.Size);
                } else {
                    // Assert immediately because this means VC firmware has failed
                    ASSERT(FALSE);
                }
                DEBUG((DEBUG_VERBOSE, "LibPcdGet64: PcdGpuMemorySize=0x%8.8X\n", PcdGet64(PcdGpuMemorySize)));
            }
            break;
        default:
            DEBUG((DEBUG_ERROR, "LibPcdGet64: PcdToken=0x%8.8X for DynamicPcd is not supported\n", Pcd->TokenNumber));
            ASSERT(FALSE);
        }
    }

    // DynamicPcd value should have been computed by this line
    ASSERT(Pcd->Value != Pcd->DefaultValue);
    return Pcd->Value;
}

/**
  This function sets a value for a dynamic token.

  Sets the 64-bit value for the token specified by TokenNumber
  to the value specified by Value.  Value is returned.

  If the set operation was not correctly performed, then ASSERT().

  @param[in]  TokenNumber   The PCD token number to set a current value for.
  @param[in]  Value         The 64-bit value to set.

  @return Return the value that was set.

**/
UINT64
EFIAPI
LibPcdSet64 (
    IN UINTN             TokenNumber,
    IN UINT64            Value
    )
{
    PCD_DYNAMIC_VALUE* Pcd;

    Pcd = GetDynamicPCD(TokenNumber);
    ASSERT(Pcd != NULL);

    DEBUG((DEBUG_VERBOSE, "LibPcdSet64 (%d) = 0x%8.8X\n", Pcd->TokenNumber, Pcd->Value));

    Pcd->Value = Value;

    return Value;
}



