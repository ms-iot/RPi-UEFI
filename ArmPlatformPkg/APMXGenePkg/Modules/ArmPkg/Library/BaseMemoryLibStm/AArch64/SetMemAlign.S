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
  Set Buffer to Value for Size bytes.

  @param  Buffer   Memory to set.
  @param  Length   Number of bytes to set
  @param  Value    Value of the set operation.

  @return Buffer

VOID *
EFIAPI
InternalMemSetMemAlign (
  OUT     VOID                      *Buffer,
  IN      UINTN                     Length,
  IN      UINT8                     Value
  )
**/
.text
.align 3

ASM_GLOBAL ASM_PFX(InternalMemSetMemAlign)

ASM_PFX(InternalMemSetMemAlign):
    mov	x4, x0
    and	w2, w2, #0xff
    orr	w2, w2, w2, lsl #8
    orr	w2, w2, w2, lsl #16
    orr	x2, x2, x2, lsl #32
    subs    x1, x1, #8
	b.mi    2f
1:	str	x2, [x4], #8
    subs    x1, x1, #8
    b.pl    1b
2:	adds    x1, x1, #4
    b.mi    3f
    sub	x1, x1, #4
    str	w2, [x4], #4
3:	adds    x1, x1, #2
    b.mi    4f
    sub	x1, x1, #2
    strh    w2, [x4], #2
4:	adds    x1, x1, #1
    b.mi    5f
    strb    w2, [x4]
5:	ret