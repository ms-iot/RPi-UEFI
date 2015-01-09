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
#  Based on ARM version.
##

#
#start of the code section
.text
.align 3

/* FIXME - Move some of this init stuff to better location later? */

ASM_GLOBAL ASM_PFX(StartExceptionLevel3)
ASM_GLOBAL ASM_PFX(SwitchToExceptionLevel1)
ASM_GLOBAL ASM_PFX(return_from_exception)
ASM_GLOBAL ASM_PFX(copy_cpsr_into_spsr)
ASM_GLOBAL ASM_PFX(set_non_secure_mode)

.set CNTFREQ,        0x01800000
.set GIC_DIST_BASE,  0x2c001000 // On RTSM Model
.set GIC_CPU_BASE,   0x2c002000 // On RTSM Model

ASM_PFX(StartExceptionLevel3):
  /* Which EL have we started at? We could be started on a Bare system
     or under the hypervisor. */
  mrs    x0, CurrentEL
  cmp    x0, #0xc               // 0xC = EL3t (SP0) , 0x5 = EL1h (SPx)
  b.ne   skip_el3

  mrs    x0, scr_el3            // Read EL3 Secure Configuration Register
  orr    x0, x0, #1             // EL0 an EL1 cannot access secure memory

  // Send all interrupts to their respective Exception levels for EL3
  bic    x0, x0, #(1 << 1)      // IRQ
  bic    x0, x0, #(1 << 2)      // FIQ
  bic    x0, x0, #(1 << 3)      // Serror and Abort

  orr    x0, x0, #(1 << 10)     // Make next level down 64Bit. This is EL2 in the case of the Model.
                                // We need a nice way to detect this.
  msr    scr_el3, x0            // Write back our settings

  /* Now setup our EL1. Controlled by EL2 config on Model */
  mrs    x0, hcr_el2            // Read EL2 Hypervisor configuration Register
  orr    x0, x0, #(1 << 31)     // Set EL1 to be 64bit

  // Send all interrupts to their respective Exception levels for EL2
  bic    x0, x0, #(1 << 3)      // Disable virtual FIQ
  bic    x0, x0, #(1 << 4)      // Disable virtual IRQ
  bic    x0, x0, #(1 << 5)      // Disable virtual SError and Abort
  msr    hcr_el2, x0            // Write back our settings

  /*
   * Enable architected timer access
   */
  mrs     x0, cnthctl_el2
  orr     x0, x0, #3                      // Enable EL1 access to timers
  msr     cnthctl_el2, x0

  mrs     x0, cntkctl_el1
  orr     x0, x0, #3                      // EL0 access to counters
  msr     cntkctl_el1, x0


  // TODO: Set Timer freq register cntfrq_el0 based on freq in board decription file.
  // The actual rate at which time passes on the model will vary based on the power
  // of the machine running it. 24Mhz seems to be a good guess for a good workstation.
  // In real life this will be set by the CPU manufacturer.
  ldr     x0, =CNTFREQ                    // Set this to 24Mhz.
  msr     cntfrq_el0, x0

  /*
   * Check for the primary CPU to avoid a race on the distributor
   * registers.
   */
   mrs     x0, mpidr_el1
   tst     x0, #15
   b.ne    1f                              // secondary CPU

   // Read GIC id
   ldr     x1, =GIC_DIST_BASE + 0x8        // GICD_IIDR
   ldr     w0, [x1]
   // Read GIC id values
   ldr     x1, =GIC_DIST_BASE + 0xFE0      // ICPIDR0
   ldr     w0, [x1]
   ldr     x1, =GIC_DIST_BASE + 0xFE4      // ICPIDR1
   ldr     w0, [x1]
   ldr     x1, =GIC_DIST_BASE + 0xFE8      // ICPIDR2
   ldr     w0, [x1]

   ldr     x1, =GIC_DIST_BASE              // GICD_CTLR
   mov     w0, #3                          // EnableGrp0 | EnableGrp1
   str     w0, [x1]

1: ldr     x1, =GIC_DIST_BASE + 0x80       // GICD_IGROUPR
   mov     w0, #~0                         // Grp1 interrupts
   str     w0, [x1], #4
   b.ne    2f                              // Only local interrupts for secondary CPUs
   str     w0, [x1], #4
   str     w0, [x1], #4

2: ldr     x1, =GIC_CPU_BASE               // GICC_CTLR
   ldr     w0, [x1]
   mov     w0, #3                          // EnableGrp0 | EnableGrp1
   str     w0, [x1]

   mov     w0, #1 << 7                     // allow NS access to GICC_PMR
   str     w0, [x1, #4]                    // GICC_PMR

skip_el3:
  ret

ASM_PFX(SwitchToExceptionLevel1):
  // Preferred Jump point provided in x0
  msr     elr_el3, x0           // Where we want to jump to in EL1
  mov     x1, #0x3C5            // We want to return to 64bit EL1 with SP1.
                                // Serror, Debug, IRQ and FIQ enabled.
  msr     spsr_el3, x1          // Set saved state so we switch to EL1
  eret


/* TODO for AArch64. The ARMv7 code below.
# r0: Monitor World EntryPoint
# r1: MpId
# r2: Secure Monitor mode stack
ASM_PFX(enter_monitor_mode):
    mrs     r4, cpsr                    // Save current mode (SVC) in r1
    bic     r3, r4, #0x1f               // Clear all mode bits
    orr     r3, r3, #0x16               // Set bits for Monitor mode
    msr     cpsr_cxsf, r3               // We are now in Monitor Mode

    cmp     r2, #0                      // If a Secure Monitor stack base has been passed, used it
    movne   sp, r2                      // Use the passed sp

    mov     lr, r0                      // Use the pass entrypoint as lr

    msr     spsr_cxsf, r4               // Use saved mode for the MOVS jump to the kernel

    mov     r4, r0                      // Swap EntryPoint and MpId registers
    mov     r0, r1

    bx      r4
*/

/* Put the address in ELR_EL1 and do a eret. */
ASM_PFX(return_from_exception):
/* Get current mode spsr? */
    msr     elr_el1, x0
    eret

// For AArch64 we need to construct the spsr we want from individual bits and pieces.
ASM_PFX(copy_cpsr_into_spsr):
    mrs     x0, CurrentEl  // Get te h current exception level we  are running at.
    mrs     x1, SPSel      // Which Stack are we using
    orr     x0, x0, x1
    mrs     x1, daif       // Which interrupts are enabled
    orr     x0, x0, x1
    msr     spsr_el1, x0   // Write to spsr
    ret

// Set the Non Secure Mode -> Stay at EL1 with SP1 All interrupts enabled.
// TODO: Get this from build file later or use specific policy.
ASM_PFX(set_non_secure_mode):
    mov     x0, #0x3c5
    msr     spsr_el1, x0
    ret

dead:
    b       dead

ASM_FUNCTION_REMOVE_IF_UNREFERENCED
