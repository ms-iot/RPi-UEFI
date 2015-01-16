/** @file

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/* Interrupt Controller */
#define INTERRUPT_BASE (0x48200000)

#define INT_NROF_VECTORS      (96)
#define MAX_VECTOR            (INT_NROF_VECTORS - 1)
#define INTCPS_SYSCONFIG      (INTERRUPT_BASE + 0x0010)
#define INTCPS_SYSSTATUS      (INTERRUPT_BASE + 0x0014)
#define INTCPS_SIR_IRQ        (INTERRUPT_BASE + 0x0040)
#define INTCPS_SIR_IFQ        (INTERRUPT_BASE + 0x0044)
#define INTCPS_CONTROL        (INTERRUPT_BASE + 0x0048)
#define INTCPS_PROTECTION     (INTERRUPT_BASE + 0x004C)
#define INTCPS_IDLE           (INTERRUPT_BASE + 0x0050)
#define INTCPS_IRQ_PRIORITY   (INTERRUPT_BASE + 0x0060)
#define INTCPS_FIQ_PRIORITY   (INTERRUPT_BASE + 0x0064)
#define INTCPS_THRESHOLD      (INTERRUPT_BASE + 0x0068)
#define INTCPS_ITR(n)         (INTERRUPT_BASE + 0x0080 + (0x20 * (n)))
#define INTCPS_MIR(n)         (INTERRUPT_BASE + 0x0084 + (0x20 * (n)))
#define INTCPS_MIR_CLEAR(n)   (INTERRUPT_BASE + 0x0088 + (0x20 * (n)))
#define INTCPS_MIR_SET(n)     (INTERRUPT_BASE + 0x008C + (0x20 * (n)))
#define INTCPS_ISR_SET(n)     (INTERRUPT_BASE + 0x0090 + (0x20 * (n)))
#define INTCPS_ISR_CLEAR(n)   (INTERRUPT_BASE + 0x0094 + (0x20 * (n)))
#define INTCPS_PENDING_IRQ(n) (INTERRUPT_BASE + 0x0098 + (0x20 * (n)))
#define INTCPS_PENDING_FIQ(n) (INTERRUPT_BASE + 0x009C + (0x20 * (n)))
#define INTCPS_ILR(m)         (INTERRUPT_BASE + 0x0100 + (0x04 * (m)))

#define INTCPS_ILR_FIQ            BIT0
#define INTCPS_SIR_IRQ_MASK       (0x7F)
#define INTCPS_CONTROL_NEWIRQAGR  BIT0
#define INTCPS_CONTROL_NEWFIQAGR  BIT1

/* Timer */
#define DMTIMER0_BASE    (0x44E05000)
#define DMTIMER1_1MS_BASE   (0x44E31000)
#define DMTIMER2_BASE   (0x48040000)
#define DMTIMER3_BASE   (0x48042000)
#define DMTIMER4_BASE   (0x48044000)
#define DMTIMER5_BASE   (0x48046000)
#define DMTIMER6_BASE   (0x48048000)
#define DMTIMER7_BASE   (0x4804A000)

#define WDTIMER2_BASE   (0x44E35000)

#define DMTIMER_TIOCP_CFG (0x0010)
#define DMTIMER_IRQENABLE_SET (0x002C)
#define DMTIMER_TISR      (0x0028)  // IRQSTATUS
#define DMTIMER_TIER      (0x001C)
#define DMTIMER_TWER      (0x0020)
#define DMTIMER_TCLR      (0x0038)
#define DMTIMER_TCRR      (0x003C)
#define DMTIMER_TLDR      (0x0040)
#define DMTIMER_TTGR      (0x0044)
#define DMTIMER_TWPS      (0x0048)
#define DMTIMER_TMAR      (0x004C)
#define DMTIMER_TCAR1     (0x0050)
#define DMTIMER_TSICR     (0x0054)
#define DMTIMER_TCAR2     (0x0058)

#define TISR_TCAR_IT_FLAG_MASK  BIT2
#define TISR_OVF_IT_FLAG_MASK   BIT1
#define TISR_MAT_IT_FLAG_MASK   BIT0
#define TISR_ALL_INTERRUPT_MASK (TISR_TCAR_IT_FLAG_MASK | TISR_OVF_IT_FLAG_MASK | TISR_MAT_IT_FLAG_MASK)

#define TISR_TCAR_IT_FLAG_NOT_PENDING   (0UL << 2)
#define TISR_OVF_IT_FLAG_NOT_PENDING    (0UL << 1)
#define TISR_MAT_IT_FLAG_NOT_PENDING    (0UL << 0)
#define TISR_NO_INTERRUPTS_PENDING      (TISR_TCAR_IT_FLAG_NOT_PENDING | TISR_OVF_IT_FLAG_NOT_PENDING | TISR_MAT_IT_FLAG_NOT_PENDING)

#define TISR_TCAR_IT_FLAG_CLEAR BIT2
#define TISR_OVF_IT_FLAG_CLEAR  BIT1
#define TISR_MAT_IT_FLAG_CLEAR  BIT0
#define TISR_CLEAR_ALL          (TISR_TCAR_IT_FLAG_CLEAR | TISR_OVF_IT_FLAG_CLEAR | TISR_MAT_IT_FLAG_CLEAR)

#define TCLR_AR_AUTORELOAD      BIT1
#define TCLR_AR_ONESHOT         (0UL << 1)
#define TCLR_ST_ON              BIT0
#define TCLR_ST_OFF             (0UL << 0)

#define TIER_TCAR_IT_ENABLE     (BIT2
#define TIER_TCAR_IT_DISABLE    (0UL << 2)
#define TIER_OVF_IT_ENABLE      BIT1
#define TIER_OVF_IT_DISABLE     (0UL << 1)
#define TIER_MAT_IT_ENABLE      BIT0
#define TIER_MAT_IT_DISABLE     (0UL << 0)

