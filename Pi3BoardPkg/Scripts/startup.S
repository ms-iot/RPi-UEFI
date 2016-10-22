//
//  Copyright (c), Microsoft Corporation. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
// startup.bin simply jumps primary core to Pi2 or Pi2 UEFI image based on the CPU ARM cortex
// where Cortex-A7 means Pi2 and Cortex-A53 means Pi3.
// It also parks secondary cores until a valid jump address is written in each secondary
// core Mailbox3 read slot, and then jumps to that address.
//

.section .init
.globl _start

#define PI2_UEFI_BASE 0x8000
#define PI3_UEFI_BASE 0x108000
#define MIDR_PARTNUM_CORTEX_A7 0xC07
#define MIDR_PARTNUM_CORTEX_A53 0xD03

_start:
  mrc p15, 0, r0, c0, c0, 0         // Read MIDR
  ubfx r0, r0, #4, #12              // Extract bit [4:15] MIDR.PartNum

  ldr r1, =MIDR_PARTNUM_CORTEX_A7
  cmp r0, r1
  moveq r4, #PI2_UEFI_BASE          // Jump to Pi2 UEFI

  ldr r1, =MIDR_PARTNUM_CORTEX_A53
  cmp r0, r1
  moveq r4, #PI3_UEFI_BASE          // Jump to Pi3 UEFI

  cmp r0, #0
  beq park                          // Unrecognized Cortex, park indefinitely

  mrc p15, 0, r0, c0, c0, 5         // Read MPIDR
  ubfx r0, r0, #0, #2               // Extract bit [0:1] from MPIDR.Aff0
  cmp r0, #0                        // Primary core jump to UEFI directly
  beq uefiJump

  // Secondary cores wait for jump address to be written in their mailbox 3
  // which will happen later in UEFI when the primary core finishes necessary 
  // platform initializations

  ldr r5, =0x400000CC               // Core 0 Mailbox 3 read address

pollStart:
  ldr r4, [r5, r0, lsl #4]          // Current secondary core Mailbox 3 read address
  cmp r4, #0
  beq pollStart                     // Poll until non-zero jump address is read

  str r4, [r5, r0, lsl #4]          // Clear current secondary core Mailbox 3 read

uefiJump:
  bx r4

park:
  wfi
  b park
