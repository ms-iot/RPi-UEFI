//
//  Copyright (c) 2011, ARM Limited. All rights reserved.
//  
//  This program and the accompanying materials                          
//  are licensed and made available under the terms and conditions of the BSD License         
//  which accompanies this distribution.  The full text of the license may be found at        
//  http://opensource.org/licenses/bsd-license.php                                            
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
//
//

#include <AsmMacroIoLib.h>
#include <Base.h>
#include <Library/PcdLib.h>
#include <PandaBoard.h>
#include <AutoGen.h>

.text
.align 3

GCC_ASM_EXPORT(ArmPlatformPrePiBootAction)
GCC_ASM_EXPORT(ArmPlatformGetCorePosition)

GCC_ASM_EXPORT(ArmPlatformIsPrimaryCore)
GCC_ASM_EXPORT(ArmPlatformPeiBootAction)
GCC_ASM_EXPORT(ArmPlatformGetPrimaryCoreMpId)

/**
  ArmPlatformPrePiBootAction

**/
ASM_PFX(ArmPlatformPrePiBootAction):
  //relocate the relocator
  sub r12,r12
  orr r12,r12,#0x80000000
  mov r3,r12                 // relocator target address (0x80000000)
  ldr r0, =relocator_start   // relocator code start addr
  ldr r1, =relocator_end     // relocator end addr
  sub r1,r1,r0               // compute relocator code size
  lsr r1,r1,#0x2             // size in words
reloc_loop_reloc:            // copy relocator
  ldm r0!,{r2}
  stm r3!,{r2}
  subs r1,r1,#0x1
  bne reloc_loop_reloc

  // get chip id code
  ldr r2,=0x4a002206         // control module id code address
  ldrh r2,[r2]               // get higher order 16b
  lsl r2,r2,#0x14
  ldr r1,=0xb9400000         // compare with 4460 id
  cmp r1,r2                  // Z bit set if 4460

  // update dmm conf
  mov r0,#0x4e
  lsl r0,r0,#0x18            // load DMM LISA base address
  ldr r2,=0x482af000         // load MA LISA base address
  ldr r1,[r0,#0x40]          // get DMM LISA section 0
  str r1,[r0,#0x4c]          // update DMM LISA section 3
  streq r1,[r2,#0x4c]        // update MA LISA section 3 (when Z=1: 4460 only)
  ldr r1,=0xff020100         // prepare LISA section 0
  str r1,[r0,#0x40]          // update DMM LISA section 0
  streq r1,[r2,#0x40]        // update MA LISA section 0 (when Z set: 4460 only)
  bx r12                     // jump to relocator

relocator_start:
  // update emif conf.
  sub r2,r0,#0x1000000
  sub r1,r2,#0x1000000
  mov r0,#0x10
  str r0,[r1,#0xc]
  str r0,[r2,#0xc]
  ldr r0,[r1,#0x8]
  orr r0,r0,#0x8
  str r0,[r1,#0x8]
  str r0,[r2,#0x8]

  // copy
  add r1,r12,#0x8000
  add r0,r1,#0x8000
  mov r10,#0x1
  lsl r11,r10,#0x5
reloc_loop_1M:
  lsl r10,r10,#0xA
reloc_loop_4K:
  ldm r0!,{r2-r9}
  stm r1!,{r2-r9}
  subs r10,r10,#1
  bne reloc_loop_4K
  add r0,r0,#0x8000
  subs r11,r11,#1
  add r10,r10,#0x1
  bne reloc_loop_1M
  bx lr
relocator_end:

//UINTN
//ArmPlatformGetCorePosition (
//  IN UINTN MpId
//  );
ASM_PFX(ArmPlatformGetCorePosition):
  bx    lr

ASM_PFX(ArmPlatformIsPrimaryCore):
  #Bits 8 through 11 are CPU ID
  ldr   r1, =0xf00
  and   r0, r0, r1
  #id for core0 should be 0
  ldr   r1, =0x0
  cmp   r0, r1
  moveq r0, #1
  movne r0, #0
  mov   pc, lr

ASM_PFX(ArmPlatformPeiBootAction):
  mov pc, lr

ASM_FUNCTION_REMOVE_IF_UNREFERENCED

//UINTN
//ArmPlatformGetPrimaryCoreMpId (
//  VOID
//  );
ASM_PFX(ArmPlatformGetPrimaryCoreMpId):
  LoadConstantToReg (_gPcd_FixedAtBuild_PcdArmPrimaryCore, r0)
  ldr   r0, [r0]
  bx    lr
