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
#  APM Potenza ARMv8 64-bit processor start up code
##

#include <AsmMacroIoLibV8.h>
#include <Library/ArmGicLib.h>

#define APM88XXX_EFUSE_ADDR        0x1054a000
#ifdef AARCH64_MP_PROTOCOL
#define KERNEL_MAILBOX_ADDR        0x4000008000
#else
#define KERNEL_MAILBOX_ADDR        0x400000F000
#endif
#define SCU_SOCAHBDIV_ADDR         0x17000164
#define SCU_SOCGFCDIV_ADDR         0x17000170


ASM_GLOBAL ASM_PFX(CEntryPoint)
ASM_GLOBAL ASM_PFX(_ModuleEntryPoint)

.text
.align 3
ASM_PFX(_ModuleEntryPoint):
        mrs     x0, MPIDR_EL1     /* if need to access a core specific trickbox */
        msr     VMPIDR_EL2, x0    /* If user land code needs to access this */

        msr     VBAR_EL2, xzr     /* set VBAR_EL2 */
        movz    x5, 0x0800
        movk    x5, 0x00c5, LSL #16
        msr     SCTLR_EL1, x5     /* set writeable bits of SCTLR */
        msr     HCR_EL2, xzr      /* set writeable bits of HCR_EL2 */
        msr     VTTBR_EL2, xzr    /* set VTTBR_EL2 */
        msr     MAIR_EL2, xzr
        msr     MAIR_EL1, xzr
        msr     CNTFRQ_EL0, xzr
        msr     CNTVOFF_EL2, xzr
        mov     x30, xzr
	ldr     x4, =0x00300000
	msr     cpacr_el1, x4
        mov     x5, #3
        msr     CNTHCTL_EL2, x5   /* controls traps */
        msr     CPTR_EL2, xzr     /* controls traps */
reset_sctlr:
        movz    x5, 0x0870  	  /* reset value */
        movk    x5, 0x30c5, LSL #16
        msr     SCTLR_EL2,x5
reset_SPSRs:
        movz    x5, #0x00c0
        msr     SPSR_EL1,x5        /* same as SPSR_SVC */
        msr     SPSR_EL2,x5        /* same as SPSR_SVC */
        msr     SPSR_FIQ,x5        /* don't change x5, it is used way below */
        msr     SPSR_IRQ,x5
        msr     SPSR_UND,x5
        msr     SPSR_ABT,x5
reset_more_SPSRs:
        msr     ESR_EL1, xzr
        msr     ESR_EL2, xzr
        msr     FAR_EL1, xzr
        mov     x1, #4            /* number of counters for EL1/EL0 */
        msr     MDCR_EL2, x1      /* Disable monitor debug/trap */
        msr     FAR_EL2, xzr      /* not implemented in RTL yet */
        msr     PAR_EL1, xzr
        msr     HPFAR_EL2, xzr    /* likely not implemented in RTL yet */
        msr     ELR_EL1, xzr
        msr     FPEXC32_EL2, xzr  /* dci     0xd51c531f msr s3_4_c5_c3_0,x5 */

        msr     TCR_EL1, xzr      /* these may not be 'good' values but with paging off */
        msr     TCR_EL2, xzr      /* they shouldn't hurt */
        msr     TTBR0_EL1,xzr
        msr     TTBR1_EL1,xzr
        msr     TTBR0_EL2,xzr
        msr     VTCR_EL2, xzr
        mov     x0, 0x2000        /* as good as any, hopefully not used */
        msr     SP_EL0, x0
        msr     SP_EL1, x0
        mrs     x0, MIDR_EL1      /* Main ID reg, read */
        msr     VPIDR_EL2, x0     /* copy to Virt Processor IDR for EL1 use */
        msr     TPIDR_EL0, xzr    /* no reason for these either, they have no H/W significance */
        msr     TPIDR_EL1, xzr
        msr     TPIDR_EL2, xzr
        msr     TPIDRRO_EL0, xzr
        msr     PMCR_EL0, xzr
        msr     PMSELR_EL0, xzr
        msr     PMCCNTR_EL0, xzr
        msr     PMUSERENR_EL0, xzr
        msr	PMCNTENCLR_EL0, xzr
        msr     PMINTENCLR_EL1, xzr

        msr     CONTEXTIDR_EL1, xzr
        msr     CSSELR_EL1, xzr

check_for_el3:
        mrs     x0, CurrentEL
        cmp     w0, 0xc
        b.ne    in_el2
        /* bit 10-RW, 8-HCE, 7-SMC, 0-NS */
exit_to_el2:
        mrs     x0, SCR_EL3
        mov     x2, 0x581
        orr     x0, x0, x2              /* AEM only code to get out of EL3, set RW, HCE, and NS */
        msr     SCR_EL3, x0             /* in SCR */
        adr     x0, in_el2              /* in el3 switch to el2 */
        msr     elr_el3, x0             /* address of unified EL */
        mrs     x0, DAIF
        add     x0, x0, #9              /* EL2h, assuming lower bits are zero from DAIF */
        msr     spsr_el3, x0
        eret                            /* to the next instructions but in el2 a64 */
        /* set aw(5) and fw(4) NS(0)in scr? */

in_el2:
        mrs     x0, cnthctl_el2
        orr     x0, x0, #3              /* Enable kernel access to timers */
        msr     cnthctl_el2, x0
        mrs     x0, cntkctl_el1
        orr     x0, x0, #2              /* Enable kernel access to timers */
        msr     cntkctl_el1, x0
        ldr     x0, =50000000	        /* FIXME - assume 50MHz ref */
        msr     cntfrq_el0, x0

        /* Setup stack */
        ldr	x1,=0x1D0FF000
        ldr	x2,=0x1000
	add     x1, x1, x2

reset_registers:
        mov     sp, x1      /* set sp_el2 /* stack for EL2 */
        msr     sp_el1, x1  /* and future SP's */
        msr     sp_el0, x1
        mov     x17, x1     /* resetting these is a work around until the tests */
        mov     x19, x1     /* properly set their stack, problem in the inte */
        mov     x21, x1     /* tests assuming FIS set them a stack */
        mov     x23, x1

reset_other_regs:
        mov     x1, #-1
        msr     DACR32_EL2, x1
/* This puts every domain into manager, so domain and stage 1 access
 * permissions are ignored
 */
        msr     CPTR_EL2, xzr       /* No traps */
        msr     HSTR_EL2, xzr       /* No traps */
/* reset EL1 registers */
        msr     CONTEXTIDR_EL1, xzr // ASID = 0
        msr     MDSCR_EL1, xzr      // Disable monitor debug/trap
#if 0 /* current fpga release does not support these regs */
        msr	DBGBVR0_EL1, xzr
        msr	DBGBVR1_EL1, xzr
        msr	DBGBVR2_EL1, xzr
        msr	DBGBVR3_EL1, xzr
        msr	DBGWVR0_EL1, xzr
        msr	DBGWVR1_EL1, xzr
        msr	DBGWVR2_EL1, xzr
        msr	DBGWVR3_EL1, xzr
#endif
        /*msr	DBGDTR_EL0, xzr no support for now, maybe later toolchain */

        /* Set VBAR to the start of the exception vectors in Secure Mode */
        ldr     x0, =ExceptionVectorTable
        msr     VBAR_EL2, x0
        msr     VBAR_EL1, x0

        /* stay in EL2 */
        movz    x12, 0
        movk    x12, 0x8000, LSL #16 /* set rw to 64 bit */
        orr     x12, x12, 0x18 /* enable IRQ and FIQ */
        msr     HCR_EL2, x12
        movk    x12, 0xC9      /* C for fast, regular irq disabled, (M=9) 9 is for EL2h */
        msr     spsr_el2, x12

_InitMem:
        /* Initialize Init Boot Memory */
	bl	ASM_PFX(ArmPlatformSecBootMemoryInit)

	/* Initialize GIC per CPU */
	ldr x0, =0x78010000
	ldr x1, =0x78020000

	mov	w9, #~0		/* Config SGIs and PPIs as Grp1 */
	str	w9, [x0, ARM_GIC_ICDISR]    /* GICD_IGROUPR0 */
	mov	w9, #0x1	/* Enable SGI 0 */
	str	w9, [x0, ARM_GIC_ICDISER]

	/* Initialize Cpu Interface */
	mov	w9, #0x1e7	/* Disable IRQ/FIQ Bypass & */
				/* Enable Ack Group1 Interrupt & */
				/* EnableGrp0 & EnableGrp1 */
	str	w9, [x1, ARM_GIC_ICCICR]    /* Secure GICC_CTLR */
	mov	w9, #0x1 << 7	/* Non-Secure access to GICC_PMR */
	str	w9, [x1, ARM_GIC_ICCPMR]

_IdentifyPrimary:
	/* SMP - Find primary core - Read PMD disable efuse */
	ldr	x0, =APM88XXX_EFUSE_ADDR
	ldr	w0, [x0, #0x0]
	movz	x1, #0x0			/* Assume PMD0 core 0 */
	tst	w0, #1
	b.eq	done_find_primary_core
	movz	x1, #0x100			/* Assume PMD1 core 0 */
	tst	w0, #2
	b.eq	done_find_primary_core
	movz	x1, #0x200			/* Assume PMD2 core 0 */
	tst	w0, #4
	b.eq	done_find_primary_core
	mov	x1, #0x300			/* Assume PMD3 core 0 */
	b secondary_core_wait
done_find_primary_core:

	/* Primary core jump to kernel in EL1 */
	mrs	x0, mpidr_el1
	/* We don't support multi core tianocore for now */
	and     x0, x0, #0xFFFF
	cmp     x0, x1
	b.eq	primary_core_boot

secondary_core_wait:
#ifdef AARCH64_MP_PROTOCOL
	ldr x0,	=0x78020000
	movz w1, #0xFF /* Non-Secure access to GICC_PMR */
	str  w1, [x0, ARM_GIC_ICCPMR]

	/* To wake up secondary CPU using wfi, these commented code need
to be called 
	ldr	x0, =0x78010000
	mov	w9, #0x8000
	movk	w9, #0x100, lsl #16
	str	w9, [x0, ARM_GIC_ICDSGIR]
	*/

	/* Secondary wait for signal */
	mrs     x0, mpidr_el1
	and     x0, x0, #0xffff
	mov     x1, x0
	and     x1, x1, #0x1
	and     x0, x0, #0xff00
	ror     x0, x0, #7
	orr     x0, x0, x1 /* CPU ID */

	ldr	    x1, =KERNEL_MAILBOX_ADDR /* start from 0x4000008000 */
	movz    x2, 0x1000 /* 4K */
	madd    x1, x2, x0, x1

	ldr w3, =0xFFFFFFFF
	str	w3, [x1]
	movz	x4, #0
	str	x4, [x1, #8]

	mrs     x0, mpidr_el1
	and     x0, x0, #0xffff

/* For backward compatibility reasons with systems using DTBs, we're not
 * fully and implementing parking protocol.
 */
1:
#ifdef TRUE_AARCH64_MP_PROTOCOL
	wfi
	ldr	 w2, [x1]
	cmp	 w2, w0 /* Check processor ID */
 	b.ne	1b
#else
	wfe
#endif

	ldr     x3, [x1, #8]
	cbz	    x3, 1b
	movz    x4, #0
    str     x4, [x1, #8]
    mov     x0, x1 /* copy mailbox address to x0 */
	br	    x3	/* branch to the given address */
	b	    secondary_core_wait
#else

    /* Secondary wait for signal */
       ldr         x1, =KERNEL_MAILBOX_ADDR
    movz    x3, #0
    str     x3, [x1]

1:	wfe
	ldr     x3, [x1]
	cbz	    x3, 1b
	br	    x3	/* branch to the given address */
	b	    secondary_core_wait
#endif

primary_core_boot:
	/* GIC Distributer configuration */
	ldr	x0, =0x78010000
	mov	w9, #0x3		/* EnableGrp0 | EnableGrp1 */
	str	w9, [x0, ARM_GIC_ICDDCR]	/* Secure GICD_CTLR */
	ldr	w9, [x0, ARM_GIC_ICDICTR]
	and	w10, w9, #0x1f		/* ITLinesNumber */
	cbz	w10, 1f			/* No SPIs */
	add	x11, x0, (ARM_GIC_ICDISR + 4)
	mov	w9, #~0			/* Config SPIs as Grp1 */
0:	str	w9, [x11], #0x4
	sub	w10, w10, #0x1
	cbnz	w10, 0b
1:

	/* Make sure AHB divider is 5 to get 200MHz with SOC 2000MHz */
	mov w4, #0x5
	ldr x5, =SCU_SOCAHBDIV_ADDR
	str w4, [x5]

	/* Make sure GFC divider is 8 to get 125MHz with SOC 2000MHz */
	mov w4, #0x8
	ldr x5, =SCU_SOCGFCDIV_ADDR
	str w4, [x5]

	/* Identify CPU ID */
	mrs	 x5, mpidr_el1
	and	 x5, x5, #0xF
	mov	 x10, #0x1		/* Booting mode is unused as of now */

_PrepareArguments:
	/* Move sec startup address into a data register
	 * Ensure we're jumping to FV version of the code
	 * (not boot remapped alias)
	 * Jump to SEC C code
	x0 = mp_id
	x1 = Boot Mode
	 */
	mov	x0, x5
	mov	x1, x10
	b	ASM_PFX(CEntryPoint)

_NeverReturn:
	b _NeverReturn
