##
#  Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##

.text

ASM_GLOBAL ASM_PFX(ExceptionVectorTable)
ASM_GLOBAL ASM_PFX(SecVectorTable)

.macro	ExceptionVector	offset, label
.align	7
mov  x0, #\offset
b	\label
.endm


.macro saveExceptionRegs x1, x2, level
mrs \x1, esr_el\level
mrs \x2, elr_el\level
.endm

.macro handleException ex
.align 7
\ex:
mrs  x3, CurrentEL                        // EL that we are in now
and x3, x3, #0xC
cmp x3, #0xC
b.ne 2f
saveExceptionRegs x1, x2, 3
2:
cmp x3, #0x8
b.ne 1f
saveExceptionRegs x1, x2, 2
1:
cmp x3, #0x4
b.ne 0f
saveExceptionRegs x1, x2, 1
0:
bl   ASM_PFX(SecCommonExceptionEntry)
.endm


.align 11
ASM_PFX(ExceptionVectorTable):
ASM_PFX(SecVectorTable):
ExceptionVector 0x000, _Synchronous_CurrentELWithSP0
ExceptionVector 0x080, _IRQ_CurrentELWithSP0
ExceptionVector 0x100, _FIQ_CurrentELWithSP0
ExceptionVector 0x180, _SError_CurrentELWithSP0
ExceptionVector 0x200, _Synchronous_CurrentELWithSPx
ExceptionVector 0x280, _IRQ_CurrentELWithSPx
ExceptionVector 0x300, _FIQ_CurrentELWithSPx
ExceptionVector 0x380, _SError_CurrentELWithSPx
ExceptionVector 0x400, _Synchronous_LowerELWithAArch64
ExceptionVector 0x480, _IRQ_LowerELWithAArch64
ExceptionVector 0x580, _FIQ_LowerELWithAArch64
ExceptionVector 0x500, _SError_LowerELWithAArch64
ExceptionVector 0x600, _Synchronous_LowerELWithAArch32
ExceptionVector 0x680, _IRQ_LowerELWithAArch32
ExceptionVector 0x700, _FIQ_LowerELWithAArch32
ExceptionVector 0x780, _SError_LowerELWithAArch32


handleException _Synchronous_CurrentELWithSP0
handleException _IRQ_CurrentELWithSP0
handleException _FIQ_CurrentELWithSP0
handleException _SError_CurrentELWithSP0
handleException _Synchronous_CurrentELWithSPx
handleException _IRQ_CurrentELWithSPx
handleException _FIQ_CurrentELWithSPx
handleException _SError_CurrentELWithSPx
handleException _Synchronous_LowerELWithAArch64
handleException _IRQ_LowerELWithAArch64
handleException _FIQ_LowerELWithAArch64
handleException _SError_LowerELWithAArch64
handleException _Synchronous_LowerELWithAArch32
handleException _IRQ_LowerELWithAArch32
handleException _FIQ_LowerELWithAArch32
handleException _SError_LowerELWithAArch32
