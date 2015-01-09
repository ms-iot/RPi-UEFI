/**
 * Copyright (c) 2014, AppliedMicro  Corp. All rights reserved.
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
#ifndef APMXGENEPMD_H_
#define APMXGENEPMD_H_

#include <Uefi/UefiBaseType.h>

#define EFUSE0_SHADOW_ADDR_ABS                  0x1054a000UL
#define EFUSE1_SHADOW_ADDR_ABS                  0x1054a004UL


#define PMD0_DISABLE_MASK       0x00000001
#define PMD1_DISABLE_MASK       0x00000002
#define PMD2_DISABLE_MASK       0x00000004
#define PMD3_DISABLE_MASK       0x00000008
#define ALL_CPU_RESET_MASK      0x00800000
#define MAX_NUM_PMD   4
#define PCP_RB_CSW_PxRCR_ADDR                   0x7e200100UL
#define PCP_RB_CSW_PxRSR_ADDR                   0x7e200104UL
#define PCP_RB_CSW_PxRCR_STARTC0_MASK           0x1
#define PCP_RB_CSW_PxRCR_STARTC1_MASK           0x2
#define PCP_RB_CSW_PxRCR_STARTC0_STARTC1_MASK   0x3

#define u32 UINT32

/* return 1 if pmd available else return 0 */
inline int apm88xxxx_is_pmd_available(u32 pmd)
{
  u32 val;
  volatile void *reg;
  if (pmd >= MAX_NUM_PMD)
    return 0;

  reg = (void *)EFUSE0_SHADOW_ADDR_ABS;
  val = *((u32 *)reg);

  if (!(val & (1 << pmd)))
    return 1;
  else
    return 0;
}

/* return 1 if all cpus are out of reset else return 0 */
inline int apm88xxxx_is_all_cpu_reset(void)
{
  u32 val;
  volatile void *reg;

  reg = (void *)EFUSE1_SHADOW_ADDR_ABS;
  val = *((u32 *)reg);

  if (val & ALL_CPU_RESET_MASK)
    return 1;
  else
    return 0;
}

inline int apm88xxxx_get_num_available_pmds(void)
{
  int cnt = 0;
  u32   pmd;

  for (pmd = 0; pmd < MAX_NUM_PMD; pmd++) {
    if (apm88xxxx_is_pmd_available(pmd))
      cnt ++;
  }

  return cnt;
}

inline int apm88xxxx_get_num_available_cores(void)
{
  return (2 * apm88xxxx_get_num_available_pmds());
}

inline int apm88xxxx_get_first_valid_cpuid(void)
{
  u32   pmd;

  for (pmd = 0; pmd < MAX_NUM_PMD; pmd++) {
    if (apm88xxxx_is_pmd_available(pmd)) {
      return (2 * pmd);
    }
  }
  return -1;
}

inline int apm88xxxx_is_core_inreset(int pmd, int core)
{
  u32 val;
  volatile void *reg;

  reg = (void *)(PCP_RB_CSW_PxRSR_ADDR + (pmd << 4));
  val = *((u32 *)reg);

  return val & (1 << core);
}

#endif /* APMXGENEPMD_H_ */
