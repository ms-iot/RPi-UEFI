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

// Mailbox interface should remain consistent but register definition may change.
// So include SOC speficic register definition here.
#include <Bcm2836Mailbox.h>

#ifndef __BCMMAILBOXLIB_H__
#define __BCMMAILBOXLIB_H__

BOOLEAN BcmMailboxRead(
    IN UINT32 Channel,
    OUT UINT32* Value
    );

BOOLEAN BcmMailboxWrite(
    IN UINT32 Channel,
    IN UINT32 Value
    );

EFI_STATUS MailboxProperty(
    IN UINT32 Channel,
    volatile MAILBOX_HEADER *pMbProperty
    );

#endif // __BCMMAILBOXLIB_H__

