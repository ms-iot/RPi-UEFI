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
 **/

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include "APMXGeneMemc.h"
#include "APMXGenePMD.h"

#define readl(x)    *((volatile u32 *) (x))
#define writel(v, x)    *((volatile u32 *) (x)) = (v)

void apm88xxxx_print_valid_pmd(void)
{
  int pmd;

  DEBUG ((EFI_D_VERBOSE, "CPUs:  "));
  for (pmd = MAX_NUM_PMD - 1; pmd >= 0; pmd--) {
    if (!apm88xxxx_is_pmd_available(pmd)) {
      DEBUG ((EFI_D_VERBOSE, "XX"));
      continue;
    }
    DEBUG ((EFI_D_VERBOSE, "%c%c",
      apm88xxxx_is_core_inreset(pmd, 1) ? '0' : '1',
      apm88xxxx_is_core_inreset(pmd, 0) ? '0' : '1'));
  }
  DEBUG ((EFI_D_VERBOSE, "\n"));
}

void apm88xxxx_start_core(u32 pmd, u32 start_mask)
{
  u32 val;
  volatile void *reg;

  reg = (void *)(PCP_RB_CSW_PxRCR_ADDR + (pmd << 4));

  val = *((u32 *)reg);
  val |= start_mask;
  *((u32 *)reg) = val;
  val = *((u32 *)reg);
}

int apm88xxxx_start_secondary_cores(void)
{
  int first_valid_cpuid;
  u32 start_mask;
  u32 pmd;

  int num_cores;
  int cnt = 1;

  if (apm88xxxx_is_all_cpu_reset())
    return 0;

  first_valid_cpuid = apm88xxxx_get_first_valid_cpuid();

  /* We enable all CPUs for now */
  num_cores = MAX_NUM_PMD * 2;
  for (pmd = 0; pmd < MAX_NUM_PMD && cnt < num_cores; pmd++) {
    if (!apm88xxxx_is_pmd_available(pmd))
      continue;
    if ((2 * pmd) == first_valid_cpuid) {
      start_mask = PCP_RB_CSW_PxRCR_STARTC1_MASK;
      cnt++;
    } else if (cnt + 2 <= num_cores) {
      start_mask = PCP_RB_CSW_PxRCR_STARTC0_STARTC1_MASK;
                        cnt += 2;
    } else {
      start_mask = PCP_RB_CSW_PxRCR_STARTC0_MASK;
      cnt++;
    }
    if (apm88xxxx_is_core_inreset(pmd, 0) ||
        apm88xxxx_is_core_inreset(pmd, 1)) {
      apm88xxxx_start_core(pmd, start_mask);
    }
  }
  /* FIXME: Need to wait all CPUs initialize done here */
  MicroSecondDelay(1000000);
  apm88xxxx_print_valid_pmd();

  return 0;
}

#define MIDR_EL1_REV_MASK   0x0000000f
#define REVIDR_EL1_MINOR_REV_MASK 0x00000007
#define EFUSE0_SHADOW_VERSION_SHIFT 28
#define EFUSE0_SHADOW_VERSION_MASK  0xF

int xgene_is_preB0(void)
{
  u32 val;
  asm volatile("mrs %0, midr_el1" : "=r" (val));
        val &= MIDR_EL1_REV_MASK;
  return val == 0 ? 1 : 0;
}

int apm88xxxx_CPU_setup(void)
{
  int num_cores;
  int i;

  num_cores = MAX_NUM_PMD * 2;
  for (i = 0; i < num_cores; i++) {
    unsigned long cccr_addr = 0x7c0c0000 + (0x100000 * i);
    unsigned long cccr_val = 0;

    if (!apm88xxxx_is_pmd_available(i/2))
      continue;

    cccr_val = readl(cccr_addr);
    if (xgene_is_preB0()) {
      /*
       * Bug 37385 FxBypDis = 0b01, skip disabled PMDs
       * Disable Fx result bypass, inhibit 5 cycle feedback
       */
      cccr_val |= 0x4000;
    }

    /* Bug 44899, Disable L1 data prefetch */
    cccr_val |= 0x200;
    writel(cccr_val, cccr_addr);
  }

  /*
   * L2 Cache modification
   */
  for(i=0; i<num_cores; i++) {
    unsigned long l2rtocr_addr = 0x7c0d0010 + (0x100000 * i);
    unsigned long val = 0;

    if (!apm88xxxx_is_pmd_available(i/2))
      continue;

    val = readl(l2rtocr_addr);

    /* Bug 44141, reduce request time out value */
    val &= 0xffffffc0;
    val |= 0x10;
    writel(val, l2rtocr_addr);
  }

  /* Disable CGC for FSU */
  if (xgene_is_preB0()){
    writel(0x911, (unsigned long)0x7e200200);
    writel(0x911, (unsigned long)0x7e200210);
    writel(0x911, (unsigned long)0x7e200220);
    writel(0x911, (unsigned long)0x7e200230);
  }

  return 0;
}
/**
  Initialize the Secure peripherals and memory regions

  If Trustzone is supported by your platform then this function makes the required initialization
  of the secure peripherals and memory regions.

**/
VOID
ArmPlatformSecTrustzoneInit (
  IN  UINTN                     MpId
  )
{
  /* Do nothing */
}

/**
  Initialize controllers that must setup at the early stage

  Some peripherals must be initialized in Secure World.
  For example, some L2x0 requires to be initialized in Secure World

**/
RETURN_STATUS
ArmPlatformSecInitialize (
  IN  UINTN                     MpId
  )
{

  RETURN_STATUS Status;

  /* Initialize DDR */
  Status = APMXGeneMemcInit();

  apm88xxxx_start_secondary_cores();

  apm88xxxx_CPU_setup();

  return Status;
}

/**
  Call before jumping to Normal World

  This function allows the firmware platform to do extra actions before
  jumping to the Normal World

**/
VOID
ArmPlatformSecExtraAction (
  IN  UINTN         MpId,
  OUT EFI_PHYSICAL_ADDRESS*        JumpAddress
  )
{
  *JumpAddress = PcdGet64(PcdFvBaseAddress);
}

/**
  Call to initalize early Sec boot memory for stack space
 
 **/
VOID 
ArmPlatformSecBootMemoryInit (
  VOID
  )
{
  /* Do nothing as stack is located on OCM and its is already initalized */
}

VOID
ArmCpuSetup (
  IN  UINTN         MpId
  )
{
  /* Do nothing */
}
