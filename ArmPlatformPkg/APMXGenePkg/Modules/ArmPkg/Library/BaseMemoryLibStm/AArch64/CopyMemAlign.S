/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 */

/**
  Copy Length bytes from Source to Destination. Overlap is OK.

  This implementation 

  @param  Destination Target of copy
  @param  Source      Place to copy from
  @param  Length      Number of bytes to copy

  @return Destination


VOID *
EFIAPI
InternalMemCopyMemAlign (
  OUT     VOID                      *DestinationBuffer,
  IN      CONST VOID                *SourceBuffer,
  IN      UINTN                     Length
  )
**/
.text
.align 3

ASM_GLOBAL ASM_PFX(InternalMemCopyMemAlign)
ASM_PFX(InternalMemCopyMemAlign):
    mov  x4, x0
    subs x2, x2, #8
    b.mi 2f
1:  ldr  x3, [x1], #8
    subs x2, x2, #8
    str  x3, [x4], #8
    b.pl 1b
2:  adds x2, x2, #4
    b.mi 3f
    ldr  w3, [x1], #4
    sub  x2, x2, #4
    str  w3, [x4], #4
3:  adds x2, x2, #2
    b.mi 4f
    ldrh w3, [x1], #2
    sub  x2, x2, #2
    strh w3, [x4], #2
4:  adds x2, x2, #1
    b.mi 5f
    ldrb w3, [x1]
    strb w3, [x4]
5:  ret