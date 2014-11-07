/**
 * Applied Micro APM88xxxx Clock/PLL
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * Author: Loc Ho <lho@apm.com>
 *
 *  This program and the accompanying materials
 *  are licensed and made available under the terms and conditions of the BSD License
 *  which accompanies this distribution.  The full text of the license may be found at
 *  http://opensource.org/licenses/bsd-license.php
 *
 *  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#if !defined(__APMXGENECLOCK_H__)
#define __APMXGENECLOCK_H__

unsigned long get_base_clk(void);
unsigned long get_PCP_CLK(void);
unsigned int  read_pmd_reg(unsigned int noncpu, int cpuid_group, int page, int offset);
unsigned long get_PMD_CLK(int pmd);
unsigned long get_SOC_CLK(void);
unsigned long get_IOBAXI_CLK(void);
unsigned long get_AXI_CLK(void);
unsigned long get_AHB_CLK(void);
unsigned long get_SLIMPRO_CLK(void);
unsigned long get_GFC_CLK(void);

#endif
