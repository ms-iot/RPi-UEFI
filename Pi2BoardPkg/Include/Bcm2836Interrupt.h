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

#ifndef __BCM2836INTERRUPT_H__
#define __BCM2836INTERRUPT_H__

/*
   Note that the INT_CORE_* reflects the BCM2836 ARM interrupt controller that
   aggregates in the new sources such as the mailboxes & ARM timers (GIT) along with
   an interrupt line from the existing BCM2835 peripherals.
*/

/* The base address is above the 1Gb max SDRAM supported */
#define INT_CORE_BASE_ADDRESS       (0x40000000)

/* Note that the 4 cores have separate addresses: 0x0040, 0x0044, 0x0048, 0x004C */
#define INT_CORE_TIMERS_CONTROL(n)  (INT_CORE_BASE_ADDRESS + 0x0040 + ((n) * 4))

/* Note that the 4 cores have separate addresses: 0x0050, 0x0054, 0x0058, 0x005C */
#define INT_CORE_MAILBOX_CONTROL(n) (INT_CORE_BASE_ADDRESS + 0x0050 + ((n) * 4))

/* Note that the 4 cores have separate addresses: 0x0060, 0x0064, 0x0068, 0x006C */
#define INT_CORE_IRQ_SOURCE(n)      (INT_CORE_BASE_ADDRESS + 0x0060 + ((n) * 4))

/* This is the number of vectors. */
/* Since the register is 32 bits wide with 1 bit per source there are 32 vectors maximum */
#define INT_CORE_MAX_NUM_VECTORS  (32)
#define INT_CORE_MAX_VECTOR       (INT_CORE_MAX_NUM_VECTORS - 1)

#endif // __BCM2836INTERRUPT_H__

