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

#include <AutoGen.h>
#include <AsmMacroIoLib.h>

#define APM88XXX_EFUSE_ADDR                     0x1054a000

GCC_ASM_EXPORT(ArmPlatformIsPrimaryCore)
GCC_ASM_EXPORT(ArmPlatformPeiBootAction)
GCC_ASM_EXPORT( ArmPlatformGetCorePosition)

.text
.align 3

ASM_PFX(ArmPlatformPeiBootAction):
  ret

ASM_PFX(ArmPlatformIsPrimaryCore):
  and   x0, x0, 0xFFFF
  ldr	x1, =APM88XXX_EFUSE_ADDR
  ldr	w1, [x1, #0x0]
  tst	w1, #1
  b.eq	done_find_primary_core0
  tst	w1, #2
  b.eq	done_find_primary_core2
  tst	w1, #4
  b.eq	done_find_primary_core4
  b.eq	done_find_primary_core6
done_find_primary_core0:
  cmp   x0, 0x0
  b.eq  done_yes
done_find_primary_core2:
  cmp   x0, 0x100
  b.eq  done_yes
done_find_primary_core4:
  cmp   x0, 0x200
  b.eq  done_yes
done_find_primary_core6:
  cmp   x0, 0x300
  b.eq  done_yes
done_no:
  mov   x0, xzr
  ret
done_yes:
  ldr   x0, =0x1
  ret

//UINTN
//ArmPlatformGetCorePosition (
//  IN UINTN MpId
//  );
ASM_PFX(ArmPlatformGetCorePosition):
  ret
