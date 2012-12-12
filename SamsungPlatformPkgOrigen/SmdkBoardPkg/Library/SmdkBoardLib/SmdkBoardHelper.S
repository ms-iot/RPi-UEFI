/*
 * Copyright (c) 2011, Samsung Electronics Co. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */

#include <AsmMacroIoLib.h>
#include <Base.h>
#include <Library/PcdLib.h>
#include <Platform/ArmPlatform.h>
#include <AutoGen.h>

/* Start of Code section */
.text
.align 3

GCC_ASM_IMPORT(_SetupPrimaryCoreStack)
GCC_ASM_EXPORT(ArmPlatformTZPCInitialized)
GCC_ASM_EXPORT(ArmPlatformUARTInitialized)
GCC_ASM_EXPORT(ArmPlatformIsClockInitialized)
GCC_ASM_EXPORT(ArmPlatformIsMemoryInitialized)
GCC_ASM_EXPORT(ArmPlatformInitializeBootMemory)
GCC_ASM_EXPORT(ArmPlatformSecBootAction)
GCC_ASM_EXPORT(ArmPlatformSecBootMemoryInit)

ASM_PFX(ArmPlatformTZPCInitialized):
        ldr     r0, =Exynos4210_TZPC0_BASE
        mov     r1, #0x0
        str     r1, [r0]
        mov     r1, #0xff
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        ldr     r0, =Exynos4210_TZPC1_BASE
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        ldr     r0, =Exynos4210_TZPC2_BASE
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        ldr     r0, =Exynos4210_TZPC3_BASE
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        ldr     r0, =Exynos4210_TZPC4_BASE
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        ldr     r0, =Exynos4210_TZPC5_BASE
        str     r1, [r0, #TZPC_DECPROT0SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT1SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT2SET_OFFSET]
        str     r1, [r0, #TZPC_DECPROT3SET_OFFSET]

        bx              lr

ASM_PFX(ArmPlatformUARTInitialized):
        ldr     r0, =0x11400000
        ldr     r1, =0x22222222
        str     r1, [r0]
        ldr     r0, =0x11400020
        ldr     r1, =0x222222
        str     r1, [r0]

        ldr     r0, =Exynos4210_CMU_BASE
        ldr     r1, =CLK_SRC_PERIL0_VAL
        ldr     r2, =CLK_SRC_PERIL0_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =CLK_DIV_PERIL0_VAL
        ldr     r2, =CLK_DIV_PERIL0_OFFSET
        str     r1, [r0, r2]

        ldr     r0, =Exynos4210_UART_BASE
        ldr     r1, =0x111
        str     r1, [r0, #UFCON_OFFSET]

        mov     r1, #0x3
        str     r1, [r0, #ULCON_OFFSET]

        ldr     r1, =0x3c5
        str     r1, [r0, #UCON_OFFSET]

        ldr     r1, =UART_UBRDIV_VAL
        str     r1, [r0, #UBRDIV_OFFSET]

        ldr     r1, =UART_UDIVSLOT_VAL
        str     r1, [r0, #UDIVSLOT_OFFSET]

        ldr     r1, =0x4c4c4c4c
        str     r1, [r0, #UTXH_OFFSET]          // 'L'

        ldr     r1, =0x4a4a4a4a
        str     r1, [r0, #UTXH_OFFSET]          // 'J'

        ldr     r1, =0x50505050
        str     r1, [r0, #UTXH_OFFSET]          // 'P'

        bx              lr


ASM_PFX(ArmPlatformIsClockInitialized):
        ldr     r0, =Exynos4210_CMU_BASE

        ldr     r1, =0x0
        ldr     r2, =CLK_SRC_CPU_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_1:
        subs    r1, r1, #1
        bne     cmu_1

        ldr     r1, =CLK_DIV_CPU0_VAL
        ldr     r2, =CLK_DIV_CPU0_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =CLK_DIV_CPU1_VAL
        ldr     r2, =CLK_DIV_CPU1_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =0x10000
        ldr     r2, =CLK_SRC_DMC_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_2:
        subs    r1, r1, #1
        bne     cmu_2

        ldr     r1, =CLK_DIV_DMC0_VAL
        ldr     r2, =CLK_DIV_DMC0_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =CLK_DIV_DMC1_VAL
        ldr     r2, =CLK_DIV_DMC1_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =CLK_SRC_TOP0_VAL
        ldr     r2, =CLK_SRC_TOP0_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =CLK_SRC_TOP1_VAL
        ldr     r2, =CLK_SRC_TOP1_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY

cmu_3:
        subs    r1, r1, #1
        bne     cmu_3

        ldr     r1, =CLK_DIV_TOP_VAL
        ldr     r2, =CLK_DIV_TOP_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =CLK_SRC_LEFTBUS_VAL
        ldr     r2, =CLK_SRC_LEFTBUS_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_4:
        subs    r1, r1, #1
        bne     cmu_4

        ldr     r1, =CLK_DIV_LEFRBUS_VAL
        ldr     r2, =CLK_DIV_LEFTBUS_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =CLK_SRC_RIGHTBUS_VAL
        ldr     r2, =CLK_SRC_RIGHTBUS_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_5:
        subs    r1, r1, #1
        bne     cmu_5

        ldr     r1, =CLK_DIV_RIGHTBUS_VAL
        ldr     r2, =CLK_DIV_RIGHTBUS_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =APLL_LOCK_VAL
        ldr     r2, =APLL_LOCK_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =MPLL_LOCK_VAL
        ldr     r2, =MPLL_LOCK_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =EPLL_LOCK_VAL
        ldr     r2, =EPLL_LOCK_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =VPLL_LOCK_VAL
        ldr     r2, =VPLL_LOCK_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =APLL_CON1_VAL
        ldr     r2, =APLL_CON1_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =APLL_CON0_VAL
        ldr     r2, =APLL_CON0_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =MPLL_CON1_VAL
        ldr     r2, =MPLL_CON1_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =MPLL_CON0_VAL
        ldr     r2, =MPLL_CON0_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =EPLL_CON1_VAL
        ldr     r2, =EPLL_CON1_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =EPLL_CON0_VAL
        ldr     r2, =EPLL_CON0_OFFSET
        str     r1, [r0, r2]

        ldr     r1, =VPLL_CON1_VAL
        ldr     r2, =VPLL_CON1_OFFSET
        str     r1, [r0, r2]
        ldr     r1, =VPLL_CON0_VAL
        ldr     r2, =VPLL_CON0_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_6:
        subs    r1, r1, #1
        bne     cmu_6

        ldr     r1, =CLK_SRC_CPU_VAL_MOUTMPLLFOUT
        ldr     r2, =CLK_SRC_CPU_OFFSET
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_7:
        subs    r1, r1, #1
        bne     cmu_7

        ldr     r0, =Exynos4210_DMC_0_BASE

        ldr     r1, =0x6910100A
        ldr     r2, =DMC_PHYCONTROL0
        str     r1, [r0, r2]
        ldr     r1, =0x00000084
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]

        ldr     r1, =0x6910100B

        ldr     r2, =DMC_PHYCONTROL0
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_8:
        subs    r1, r1, #1
        bne     cmu_8

        ldr     r1, =0x0000008C
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]
        ldr     r1, =0x00000084
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_9:
        subs    r1, r1, #1
        bne     cmu_9

        ldr     r0, =Exynos4210_DMC_1_BASE

        ldr     r1, =0xe910100A

        ldr     r2, =DMC_PHYCONTROL0
        str     r1, [r0, r2]
        ldr     r1, =0x00000084
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]

        ldr     r1, =0xe910100B

        ldr     r2, =DMC_PHYCONTROL0
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_10:
        subs    r1, r1, #1
        bne     cmu_10

        ldr     r1, =0x0000008C
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]
        ldr     r1, =0x00000084
        ldr     r2, =DMC_PHYCONTROL1
        str     r1, [r0, r2]

        mov     r1, #Exynos4210_CMU_DELAY
cmu_11:
        subs    r1, r1, #1
        bne     cmu_11

        ldr     r0, =Exynos4210_DMC_0_BASE
        ldr     r1, =0x0FFF30fa
        ldr     r2, =DMC_CONCONTROL
        str     r1, [r0, r2]
        ldr     r0, =Exynos4210_DMC_1_BASE
        ldr     r1, =0x0FFF30fa
        ldr     r2, =DMC_CONCONTROL
        str     r1, [r0, r2]

        ldr     r0, =Exynos4210_DMC_0_BASE
        ldr     r1, =0x00202537
        ldr     r2, =DMC_MEMCONTROL
        str     r1, [r0, r2]
        ldr     r0, =Exynos4210_DMC_1_BASE
        ldr     r1, =0x00202537
        ldr     r2, =DMC_MEMCONTROL
        str     r1, [r0, r2]

        bx              lr

/*
 * Call at the beginning of the platform boot up
 *
 * This function allows the firmware platform to do extra actions at the early
 * stage of the platform power up.
 *
 * Note: This function must be implemented in assembler
 *	 as there is no stack set up yet
 */
ASM_PFX(ArmPlatformSecBootAction):
	 bx    lr


ASM_PFX(ArmPlatformSecBootMemoryInit):
	 bx    lr

/*
 * Called at the early stage of the Boot phase to know if the memory has
 * already been initialized. Running the code from the reset vector does
 * not mean we start from cold boot. In some case, we can go through this
 * code with the memory already initialized.
 * Because this function is called at the early stage, the implementation
 * must not use the stack. Its implementation must probably done in
 * assembly to ensure this requirement.
 *
 * @return   Return the condition value into the 'Z' flag
 */
ASM_PFX(ArmPlatformIsMemoryInitialized):
 /*
  * Check if the memory has been already mapped,
  * if so skipped the memory initialization
  */
	LoadConstantToReg (Exynos4210_DMC_0_BASE, r0)
	ldr   r0, [r0, #0]
        and   r0, r0, #0x20
        cmp   r0, #0x00
	bx	lr

/*
 * Initialize the memory where the initial stacks will reside
 *
 * This memory can contain the initial stacks (Secure and Secure Monitor
 * stacks). In some platform, this region is already initialized and the
 * implementation of this function can do nothing. This memory can also
 * represent the Secure RAM.
 * This function is called before the satck has been set up. Its
 * implementation must ensure the stack pointer is not used (probably
 * required to use assembly language)
 */
ASM_PFX(ArmPlatformInitializeBootMemory):
/*
 * Check if the Memory is already Initialized.
 * If Initialized goto Stack setup
 */
	mov r10, lr
	bl   ASM_PFX(ArmPlatformIsMemoryInitialized)
	bne  skip_initmem

	ldr r0, =0x10010350
        mov r1, #1
        str r1, [r0]

/* CLK_DIV_DMC0 on iROM DMC=50MHz for Init DMC */
        ldr     r0, =Exynos4210_CMU_BASE
        ldr     r1, =0x13113113
        ldr     r2, =Exynos4210_CMU_DIV_DMC0
        str     r1, [r0, r2]

/* MIU Setting */
        ldr     r0, =Exynos4210_MIU_BASE

        ldr     r1, =0x20001507
        str     r1, [r0, #0x400]
        ldr     r1, =0x00000001
        str     r1, [r0, #0xc00]

/*****************************************************************/
/*DREX0***********************************************************/
/*****************************************************************/

        ldr     r0, =Exynos4210_DMC_0_BASE

        ldr     r1, =0xE3855503
        str     r1, [r0, #DMC_PHYZQCONTROL]

        ldr     r1, =0x71101008
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x7110100A
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x71101008
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x0000008C
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x0000008C
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x00000000
         str     r1, [r0, #DMC_PHYCONTROL2]

        ldr     r1, =0x0FFF30da
        str     r1, [r0, #DMC_CONCONTROL]

        ldr     r1, =0x00202500
        str     r1, [r0, #DMC_MEMCONTROL]

        ldr     r1, =0x20f01223
        str     r1, [r0, #DMC_MEMCONFIG0]

        ldr     r1, =0xff000000
        str     r1, [r0, #DMC_PRECHCONFIG]

        ldr     r1, =0x0000005D
        str     r1, [r0, #DMC_TIMINGAREF]

        ldr     r1, =0x34498691
        str     r1, [r0, #DMC_TIMINGROW]

        ldr     r1, =0x36330306
        str     r1, [r0, #DMC_TIMINGDATA]

        ldr     r1, =0x50380365
        str     r1, [r0, #DMC_TIMINGPOWER]

        mov     r2, #Exynos4210_DMC_DELAY

loop_2:
        subs    r2, r2, #1
        bne     loop_2
        ldr     r1, =0x07000000
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_3:
        subs    r2, r2, #1
        bne     loop_3
        ldr     r1, =0x00071C00
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_4:
        subs    r2, r2, #1
        bne     loop_4

        ldr     r1, =0x00010BFC
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_5:
        subs    r2, r2, #1
        bne     loop_5
        ldr     r1, =0x00000488
        str     r1, [r0, #DMC_DIRECTCMD]
        ldr     r1, =0x00000810
        str     r1, [r0, #DMC_DIRECTCMD]
        ldr     r1, =0x00000C08
        str     r1, [r0, #DMC_DIRECTCMD]

/* get DMC density information */
        ldr r1, =0x09010000
        mov r3, #10
loop_6:
        str r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_7:
        subs r2, r2, #1
        bne     loop_7
        ldr r6, [r0, #DMC_MRSTATUS]
        subs r3, r3, #1
        bne     loop_6
        and r6, r6, #0x3c
        lsr r6, r6, #2
        cmp r6, #6
        ldreq r1, =0x20e01323
        ldrne r1, =0x20f01223
        str     r1, [r0, #DMC_MEMCONFIG0]

/*****************************************************************/
/*DREX1***********************************************************/
/*****************************************************************/
        ldr     r0, =Exynos4210_DMC_1_BASE
        ldr     r1, =0xE3855503
        str     r1, [r0, #DMC_PHYZQCONTROL]

        ldr     r1, =0x71101008
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x7110100A
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x71101008
        str     r1, [r0, #DMC_PHYCONTROL0]

        ldr     r1, =0x0000008C
        str     r1, [r0, #DMC_PHYCONTROL1]
        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x0000008C
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x00000084
        str     r1, [r0, #DMC_PHYCONTROL1]

        ldr     r1, =0x00000000
        str     r1, [r0, #DMC_PHYCONTROL2]

        ldr     r1, =0x0FFF30da
        str     r1, [r0, #DMC_CONCONTROL]

        ldr     r1, =0x00202500
        str     r1, [r0, #DMC_MEMCONTROL]

        ldr     r1, =0x40f01223
        str     r1, [r0, #DMC_MEMCONFIG0]

        ldr     r1, =0x20f01223
        str     r1, [r0, #DMC_MEMCONFIG0]

        ldr     r1, =0xff000000
        str     r1, [r0, #DMC_PRECHCONFIG]

        ldr     r1, =0x0000005D
        str     r1, [r0, #DMC_TIMINGAREF]

        ldr     r1, =0x34498691
        str     r1, [r0, #DMC_TIMINGROW]

        ldr     r1, =0x36330306
        str     r1, [r0, #DMC_TIMINGDATA]

        ldr     r1, =0x50380365
        str     r1, [r0, #DMC_TIMINGPOWER]

        mov     r2, #Exynos4210_DMC_DELAY
loop_8:
        subs    r2, r2, #1
        bne     loop_8
        ldr     r1, =0x07000000
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_9:
        subs    r2, r2, #1
        bne     loop_9
        ldr     r1, =0x00071C00
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_10:
        subs    r2, r2, #1
        bne     loop_10

        ldr     r1, =0x00010BFC
        str     r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_11:
        subs    r2, r2, #1
        bne     loop_11
        ldr     r1, =0x00000488
        str     r1, [r0, #DMC_DIRECTCMD]

        ldr     r1, =0x00000810
        str     r1, [r0, #DMC_DIRECTCMD]

        ldr     r1, =0x00000C08
        str     r1, [r0, #DMC_DIRECTCMD]

/* get DMC density information */
        ldr r1, =0x09010000
        mov r3, #10
loop_12:
        str r1, [r0, #DMC_DIRECTCMD]
        mov     r2, #Exynos4210_DMC_DELAY
loop_13:
        subs r2, r2, #1
        bne     loop_13
        ldr r7, [r0, #DMC_MRSTATUS]
        subs r3, r3, #1
        bne     loop_12
        and r7, r7, #0x3c
        lsr r7, r7, #2
        cmp r7, #6
        ldreq r1, =0x20e01323
        ldrne r1, =0x20f01223
        str     r1, [r0, #DMC_MEMCONFIG0]
skip_initmem:
	mov lr, r10
	bx    lr

.end
