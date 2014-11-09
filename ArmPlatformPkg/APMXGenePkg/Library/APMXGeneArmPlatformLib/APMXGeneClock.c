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

#include <Library/IoLib.h>
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <APMXGeneSlimPROCSR.h>

#define CONFIG_SYS_CLK_FREQ	100000000
#define STORM_SLIMPRO_CSR_BASE	0x17000000
#define STORM_REGBUS_BASE	0x7C000000
#define readl(x)		MmioRead32((x))

unsigned long get_base_clk(void)
{
  return CONFIG_SYS_CLK_FREQ;
}

unsigned long get_PCP_CLK(void)
{
  /**
   * PLL VCO = Reference clock * NF
   * PCP PLL = PLL_VCO / 2
   *
   */
   unsigned int pcppll;
   unsigned long vco;

   pcppll = readl(STORM_SLIMPRO_CSR_BASE + SCU_PCPPLL_ADDR);
   vco = get_base_clk() * (N_DIV_RD(pcppll) + 4);
   return vco / 2;
}

unsigned int read_pmd_reg(unsigned int noncpu, int cpuid_group, int page, int offset)
{
  UINT64 addr = STORM_REGBUS_BASE;

  addr |= (32 * noncpu) << 20;		/* CPU/non-cpu pages at 0/32MB offset
						   from REGBUS_BASE*/
  addr |= (1 * cpuid_group) << 20;	/* each group of 1MB */
  addr |= (64 * page) << 10;		/* each page of 64KB */
  addr |= offset & ~0x3;			/* offset word aligned */
  return readl(addr);
}

unsigned long get_PMD_CLK(int pmd)
{
  unsigned int pxccr0 = read_pmd_reg(1, 2, 0, (0x200 | (pmd << 4)));
  unsigned int pmd_div = ((pxccr0 >> 12) & 0x3)+1;
  return get_PCP_CLK() / pmd_div;
}

unsigned long get_SOC_CLK(void)
{
  /**
    * Fref = Reference Clock / NREF;
    * Fvco = Fref * NFB;
    * Fout = Fvco / NOUT;
    */
  unsigned int socpll = readl(STORM_SLIMPRO_CSR_BASE + SCU_SOCPLL_ADDR);
  unsigned int nref = CLKR_RD_SOCPLL(socpll) + 1;
  unsigned int nout = CLKOD_RD(socpll) + 1;
  unsigned int nfb = CLKF_RD(socpll);
  unsigned long fref = get_base_clk() / nref;
  unsigned long fvco = fref * nfb;
  return fvco / nout;
}

unsigned long get_IOBAXI_CLK(void)
{
  unsigned long socclk = get_SOC_CLK();
  unsigned int sociobixa = readl(STORM_SLIMPRO_CSR_BASE + SCU_SOCIOBAXIDIV_ADDR);
  return socclk / IOB_AXI_FREQ_SEL_RD(sociobixa);
}

unsigned long get_AXI_CLK(void)
{
  unsigned long socclk = get_SOC_CLK();
  unsigned int socixa = readl(STORM_SLIMPRO_CSR_BASE + SCU_SOCAXIDIV_ADDR);
  return socclk / 2 / AXI_FREQ_SEL_RD(socixa);
}

unsigned long get_AHB_CLK(void)
{
  unsigned long socclk = get_SOC_CLK();
  unsigned int socahb = readl(STORM_SLIMPRO_CSR_BASE + SCU_SOCAHBDIV_ADDR);
  return socclk / 2 / AHB_FREQ_SEL_RD(socahb);
}

unsigned long get_SLIMPRO_CLK(void)
{
  unsigned long socclk = get_SOC_CLK();
  unsigned int socslimpro = readl(STORM_SLIMPRO_CSR_BASE + SCU_INTAHBDIV_ADDR);
  return socclk / 2 / AHB_FREQ_SEL_F1_RD(socslimpro);
}

unsigned long get_GFC_CLK(void)
{
  unsigned long socclk = get_SOC_CLK();
  unsigned int socgfc = readl(STORM_SLIMPRO_CSR_BASE + SCU_SOCGFCDIV_ADDR);
  return socclk / 2 / GFC_FREQ_SEL_RD(socgfc);
}
