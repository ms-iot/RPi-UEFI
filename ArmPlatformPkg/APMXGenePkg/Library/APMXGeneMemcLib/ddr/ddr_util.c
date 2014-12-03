/**
 * APM X-Gene DDR3 controller code
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Feng Kan <fkan@apm.com>.
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

#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "kc_phy_util_reg_flds.h"

unsigned long long rb_page_translate(unsigned int page_addr,
		unsigned int offset)
{
	unsigned long sys_addr;

	sys_addr = page_addr << 16;
	sys_addr += (offset << 2);
	sys_addr += PCP_RB_BASE;
	return sys_addr;
}

void rb_write(unsigned int page_addr, unsigned int offset, unsigned int wr_data)
{
	unsigned long sys_addr;

	sys_addr = rb_page_translate(page_addr, offset);
	*(volatile unsigned int *)sys_addr = wr_data;
	DSB_SY_CALL;
}

unsigned int rb_read(unsigned int page_addr, unsigned int offset)
{
	unsigned long sys_addr;

	sys_addr = rb_page_translate(page_addr, offset);
	return *(volatile unsigned int *)sys_addr;
}

unsigned int csw_read_reg(void *p, unsigned int reg)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int data;

	data = *(volatile unsigned int *)(mcu->csw_base + reg);
	debug3("CSW %d: read reg 0x%lx  value ", mcu->id, mcu->csw_base + reg);
	debug3("0x%08X\n", data);
	DSB_SY_CALL;
	return data;
}

void csw_write_reg(void *p, unsigned int reg, unsigned int value)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	debug3("CSW %d: write reg 0x%lx ", mcu->id, mcu->csw_base + reg);
	debug3("value 0x%08X\n", value);
	*(volatile unsigned int *)(mcu->csw_base + reg) = value;
	DSB_SY_CALL;
}

unsigned int mcu_read_reg(void *p, unsigned int reg)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int data;

	data = *(volatile unsigned int *)(mcu->base + reg);
	DSB_SY_CALL;
	debug3("MCU %d: read reg 0x%lx  value ", mcu->id, mcu->base + reg);
	debug3("0x%08X\n", data);
	return data;
}

void mcu_write_reg(void *p, unsigned int reg, unsigned int value)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	debug3("MCU %d: write reg 0x%lx ", mcu->id, mcu->base + reg);
	debug3("value 0x%08X\n", value);
	*(volatile unsigned int *)(mcu->base + reg) = value;
	DSB_SY_CALL;
}

unsigned int phy_read_reg(void *p, unsigned int reg)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int data;

	DSB_SY_CALL_WDELAY;
	data = *(volatile unsigned int *)(mcu->base + MCU_PHY_OFFSET + reg);
	DSB_SY_CALL_WDELAY;
	debug3("MCU-PHY %d: read reg 0x%lx ", mcu->id,
	      mcu->base + MCU_PHY_OFFSET + reg);
	debug3(" value 0x%08X\n", data);
	return data;
}

void phy_write_reg(void *p, unsigned int reg, unsigned int value)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	debug3("MCU-PHY %d: write reg 0x%lx ", mcu->id,
			mcu->base + MCU_PHY_OFFSET + reg);
	debug3("value 0x%08X\n", value);
	DSB_SY_CALL_WDELAY;
	*(volatile unsigned int *)(mcu->base + MCU_PHY_OFFSET + reg) = value;
	DSB_SY_CALL_WDELAY;
}

int phy_poll_reg(void *p, unsigned int reg, unsigned int value,
		unsigned int mask)
{
	unsigned int rd_val;
	unsigned int polling_on;
	unsigned int err = 0;
	unsigned int timeout = 0x1000;

	polling_on = 1;
	while (polling_on) {
		rd_val = phy_read_reg(p, reg);
		if ((value & mask) == (rd_val & mask)) {
			polling_on = 0;
		}
		if (polling_on) {
			if (timeout) {
				timeout--;
				DELAY(10);
			} else {
				polling_on = 0;
				err++;
			}
		}
	}
	/* TDB timeout & error routine */
	return err;
}

unsigned int mcb_read_reg(void *mcu, unsigned int reg)
{
	struct apm_mcu *ptr = (struct apm_mcu *)mcu;
	unsigned long offset = reg + ptr->mcb_base;
	unsigned int data;

	data = *(volatile unsigned int *)offset;
	debug3("MCB %d: read reg 0x%lx ", ptr->mcb_id, offset);
	debug3("value 0x%x\n", data);
	DSB_SY_CALL;
	return data;
}

void mcb_write_reg(void *mcu, unsigned int reg, unsigned int value)
{
	struct apm_mcu *ptr = (struct apm_mcu *)mcu;
	unsigned long offset = reg + ptr->mcb_base;

	debug3("MCB %d: write reg 0x%lx ", ptr->mcb_id, offset);
	debug3("value %x\n", value);
	*(volatile unsigned int *)offset = value;
	DSB_SY_CALL;
}

unsigned int mcu_regmod(void *ptr, unsigned int reg_offset, unsigned int data,
			unsigned int bh, unsigned int bl)
{
	unsigned int regval;
	unsigned int mask = 0xFFFFFFFF;
	unsigned int mask2 = 0xFFFFFFFF;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	debug3("mcu_regmod: reg offset 0x%x initial val :0x%x ", reg_offset, data);
	debug3("bl %x bh %x\n", bl, bh);
	if (bh < bl)
		return 0;
	if (bh < 31)
		mask = ~(mask << (bh - bl + 1));

	data &= mask;
	data = data << bl;

	if (bl > 0)
		mask2 = ~(mask << bl);
	mask |= mask2;

	regval = *(volatile unsigned int *)(mcu->base + reg_offset);
	regval &= mask;
	regval |= data;
	*(volatile unsigned int *)(mcu->base + reg_offset) = regval;
	debug3("MCU %d: regmod address 0x%lx ", mcu->id, mcu->base + reg_offset);
	debug3("value 0x%x\n", regval);
	DSB_SY_CALL;
	return 1;
}

int mcu_assert_mc_pwr_ok(void *p)
{
	volatile unsigned int *gpio_mode = (volatile unsigned int *)0x170012A0;
	volatile unsigned int *gpio_drive = (volatile unsigned int *)0x1700129C;
	unsigned int regval;

	debug("\n------- Assert DDR_MC_POWER_OK --------\n");
	/* Set to output mode */
	regval = *gpio_mode;
	*gpio_mode = regval | (1 << 23);

	/* Drive high */
	regval = *gpio_drive;
	*gpio_drive = regval | (1 << 23);

	return 0;
}

/*
 * Csw Address configuration
 * Setup CSW config register with value for address mode
 * interleave mode and dual MCB mode. Use lower three bits.
 * Bit 2 - full 42 bit address mode
 * Bit 1 - MCB interleaved mode
 * Bit 0 - two MCB active
 */
void CSWCR_setup(void *p, unsigned int mask)
{
	unsigned int cswcr;
	struct apm_memc *ddr = (struct apm_memc *)p;
	struct apm_mcu *mcu = &ddr->mcu[0];

	cswcr = mcu->csw_rd(mcu, RB_CSWCR);
	cswcr &= 0xFFFFFFF8;
	cswcr |= (mask & 0x7);
	mcu->csw_wr(mcu, RB_CSWCR, cswcr);
	return;
}

/*
 * Function used to release MCB 0 reset. 
 * Based on Rev 0.09 of PCP Reset and Clock Guide:
 * 1) Wait for 64 CSW cycles (Streak divider minimum reset assertion time)
 * 2) Write MCB0CCR to clear McbClkEn (others unchanged)
 * 3) Write MCB0CCR to initialize clock macro settings:
 *   a. (Required) Clear McbClkMacRst
 *   b. (Optional) Clear CmINsCorrEn
 *   c. Others unchanged
 * 4) Wait for 10 ns (for CMOSCLK to stabilize)
 * 5) Write MCB0CCR to set McbClkEn (others unchanged)
 * 6) Wait for 64 CSW cycles (Streak divider minimum reset assertion time)
 * 7) Wait for 25 MCB cycles (minimum reset assertion time) [MCBDS]
 * 8) Write MCB0RCR to clear ResetMcb (others unchanged)
 * 9) Wait for 25 MCB cycles (maximum reset deassertion time) [MCBDS]
 */
void release_mcb_reset(struct apm_mcu *mcu)
{
	unsigned int reg;

	if (!mcu->enabled) 
		return;
#if !defined(APM_SIM)
	debug("release_mcb_reset: mcb-id:%d mcu-id:%d enabled:%d "
		"mcb-addr:0x%08x\n", mcu->mcb_id, mcu->id, mcu->enabled,
		(unsigned int)(PCP_RB_CSW_BASE + RB_MCB0CCR +
			    (mcu->mcb_id) * RB_MCB_REG_OFFSET));
#endif
	reg = mcu->csw_rd(mcu, RB_MCB0CCR + mcu->mcb_id * RB_MCB_REG_OFFSET);
	reg &= 0xFFFFF7FF;	
	mcu->csw_wr(mcu, RB_MCB0CCR + mcu->mcb_id * RB_MCB_REG_OFFSET, reg);
	reg &= 0xFFFF37DF;
	mcu->csw_wr(mcu, RB_MCB0CCR + mcu->mcb_id * RB_MCB_REG_OFFSET, reg);
	DELAY(1);
	reg |= 0x800;
	mcu->csw_wr(mcu, RB_MCB0CCR + mcu->mcb_id * RB_MCB_REG_OFFSET, reg);
	DELAY(1);
	reg = mcu->csw_rd(mcu, RB_MCB0RCR + mcu->mcb_id * RB_MCB_REG_OFFSET);
	reg &= 0xFFFFFFFE;
	mcu->csw_wr(mcu, RB_MCB0RCR + mcu->mcb_id * RB_MCB_REG_OFFSET, reg);
	/*
	   PCP_RB_CSW_MCB0CCR_MCBCLKMACRST_BIT      15
	   PCP_RB_CSW_MCB0CCR_MCBCLKMACRST_LEN      1
	   PCP_RB_CSW_MCB0CCR_MCBCLKMACPD_BIT       14
	   PCP_RB_CSW_MCB0CCR_MCBCLKMACPD_LEN       1
	   PCP_RB_CSW_MCB0CCR_MCBCLKEN_BIT          11
	   PCP_RB_CSW_MCB0CCR_MCBCLKEN_LEN          1
	   PCP_RB_CSW_MCB0CCR_CMLNSCORREN_BIT       5
	   PCP_RB_CSW_MCB0CCR_CMLNSCORREN_LEN       1

	   PCP_RB_CSW_MCB0RCR_RESETMCB_BIT          0
	   PCP_RB_CSW_MCB0RCR_RESETMCB_LEN          1
	 */
}

/*
 * Configure MCB modes
 */
void mcb_mode_setup(void *p, unsigned int mode, unsigned int spec_read)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int reg;

	if (!mcu->enabled) 
		return;
#if !defined(APM_SIM)
	debug("mcb_mode_setup: mcb-id:%d mcu-id:%d enabled:%d\n", 
				mcu->mcb_id, mcu->id, mcu->enabled);
#endif
	/* Non speculative read mode */
	reg = (0x1 & spec_read);
	mcu->mcb_wr(mcu, RB_MCB_SPECRMR, reg);

	/*
	 * Setup MCU address modes
	 * bit 3: mcu interleave mode
	 * bit 2: dual mcu mode
	 * bit 1: mcb interleave mode
	 * bit 0: 32 bit mode
	 */
	reg = mcu->mcb_rd(mcu, RB_MCB_ADDRRMR);
	reg &= 0xFFFFFFF0;
	reg |= (0xF & mode);
	mcu->mcb_wr(mcu, RB_MCB_ADDRRMR, reg);
}

/*
 * Perform proper clock and reset initialization sequence
 * for an MCU.
 */
int mcb_mcu_init_clock_deassert_reset(void *p)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int reg;
	unsigned int mcu1_off = 0;

	debug(" ENTRY: %s > \n", __FUNCTION__);
	if (!mcu->enabled) 
		return 0;

	if (mcu->id % 2) 
		mcu1_off = RB_MCB_MCU_OFFSET;
#if !defined(APM_SIM)
	debug3("mcb_mcu_init_clock_deassert_reset: mcb-id:%d  mcu-id:%d "
			"enabled:%d: mcu1_off:0x%08x\n",
	     		mcu->mcb_id, mcu->id, mcu->enabled, mcu1_off);
#endif
	/*
	 * PLL reset - assert PLL/divider resets 
	 */
	/* Set PLLRR to reset post PLL divider */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_PLLRST + mcu1_off));
	reg &= 0xFFFFFFFE;
	reg |= 0x2;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLRST + mcu1_off), reg);
	DELAYP(1);
	/*
	 * Clock Control - DivRst=1 Clken=0
	 */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_CLKCTL + mcu1_off));
	reg &= 0xFFFFFFF8;
	reg |= 0x2;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_CLKCTL + mcu1_off), reg);
	DELAYP(1);
	/*
	 * Reset Control - assert Mcu Reset
	 */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_RSTCTL + mcu1_off));
	reg |= 0x1;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_RSTCTL + mcu1_off), reg);

	/*
	 * Phy PLL control values
	 */
	/* Upper bit normally zero 0xFFFFC000 */
	reg = 0;
	reg |= (mcu->mcu_params.pllctl0_idiv & 0x7U);	/* IDIV [2:0] */
	reg |= ((mcu->mcu_params.pllctl0_odiv & 0x3U) << 12);	/* ODIV [13:12] */
	reg |= ((mcu->mcu_params.pllctl0_fbdiv & 0x1FFU) << 3);	/* FBDIV [11:3] */

	debug3("MCU %1d: Using Mcu params PLLCTL0 = 0x%08X  ", mcu->id, reg);
	debug3("idiv=%1d odiv=%1d ", (mcu->mcu_params.pllctl0_idiv),
					(mcu->mcu_params.pllctl0_odiv));
	debug3("fbdiv=0x%03x\n", (mcu->mcu_params.pllctl0_fbdiv));

	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLCTL0 + mcu1_off), reg);

	debug3("MCU %1d: PLLCTL0 = 0x%08X  ", mcu->id, reg);
	debug3("idiv=%1d odiv=%1d ", (reg & 0x7U), ((reg >> 12) & 0x3));
	debug3("fbdiv=0x%03x\n", ((reg >> 3) & 0x1FF));

	reg = 0;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLCTL1 + mcu1_off), reg);

	debug3("MCU %1d: PLLCTL1 = 0x%08X \n", mcu->id, reg);
	DELAYP(1);

	/*
	 * PLL reset assert
	 */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_PLLRST + mcu1_off));
	reg |= 0x1;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLRST + mcu1_off), reg);
	DELAYP(2);
	reg &= 0xFFFFFFFEU;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLRST + mcu1_off), reg);
	DELAYP(15);
	/*
	 * Wait for PLL to lock
	 */
	reg = 0;
	while (!(reg & 0x1)) {
		reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_PLLSTS + mcu1_off));
		debug3("MCU[%d] poll PLL lock:  0x%08X\n", mcu->id, reg);
		DELAY(5);
	}
	/*
	 * Turn off phy reset 
	 */
	DELAYP(3);
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_PLLRST + mcu1_off));
	reg &= 0xFFFFFFFC;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_PLLRST + mcu1_off), reg);
	DELAYP(3);

	/*
	 * Turn off MCU divider reset
	 */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_CLKCTL + mcu1_off));
	reg &= 0xFFFFFFFD;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_CLKCTL + mcu1_off), reg);
	DELAYP(3);

	/*
	 * Enable MCU Clocks
	 */
	reg |= 0x1;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_CLKCTL + mcu1_off), reg);
	DELAYP(1);

	/*
	 * Clear MCU reset
	 */
	reg = mcu->mcb_rd(mcu, (RB_MCB_MCU_RSTCTL + mcu1_off));
	reg &= 0xFFFFFFFE;
	mcu->mcb_wr(mcu, (RB_MCB_MCU_RSTCTL + mcu1_off), reg);

	return 0;
}

int unisolate_mcu(void *p)
{
	unsigned int i, reg;
	struct apm_memc *ddr = (struct apm_memc *)p;

	/* Assert isolate */
	reg = DDR_SCU_READ32(SCU_SOC_PWR_CTL);
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		if (ddr->mcu[i].enabled)
			reg |= (0x1 << (i + 1));
	}
	DDR_SCU_WRITE32(SCU_SOC_PWR_CTL, reg);
	DELAY(5);
	/* Deassert isolate */
	reg = DDR_SCU_READ32(SCU_SOC_PWR_CTL);
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		if (ddr->mcu[i].enabled)
			reg &= ~(0x1 << (i + 1));
	}
	DDR_SCU_WRITE32(SCU_SOC_PWR_CTL, reg);
	return 0;
}

int memsys_unreset(void *p)
{
	struct apm_memc *ddr = (struct apm_memc *)p;

	/*
	 * We need to add something here to detect DIMM
	 * presence, otherwise no way to tell how many
	 * mcu needs to be enabled. For now enable all four.
	 */
	debug(" ENTRY: %s > \n", __FUNCTION__);
	debug("\nTop Level MCU/PHY-PLL turn on and "
			"Unreset memory sub-system\n");
	/* Unisolate MCU from SCU */
	unisolate_mcu(ddr);

	/*
	 * MCB deassert reset, Mcu PLL & de-assert reset
	 */
	release_mcb_reset(&ddr->mcu[0]);
	release_mcb_reset(&ddr->mcu[2]);

	mcb_mcu_init_clock_deassert_reset(&ddr->mcu[0]);
	mcb_mcu_init_clock_deassert_reset(&ddr->mcu[1]);

	mcb_mcu_init_clock_deassert_reset(&ddr->mcu[2]);
	mcb_mcu_init_clock_deassert_reset(&ddr->mcu[3]);

	debug(" EXIT: %s < \n", __FUNCTION__);

	return 0;
}

int memc_dummy_fn(void *d)
{
	return (0);
}

/* Detect chip revision */
int is_storm_revA(void)
{
#define MIDR_EL1_REV_MASK	0x0000000f
	u32 val;
	asm volatile("mrs %0, midr_el1" : "=r" (val));
	val &= MIDR_EL1_REV_MASK;
	if (val == 0)
		return 1;
	else 
		return 0;
}

#if defined(APM_TIANOCORE)
void print_size (unsigned long long size, const char *s)
{
        unsigned long m = 0, n;
        unsigned long long d = 1 << 30;                /* 1 GB */
        char  c = 'G';

        if (size < d) {                 /* try MB */
                c = 'M';
                d = 1 << 20;
                if (size < d) {         /* print in kB */
                        c = 'k';
                        d = 1 << 10;
                }
        }

        n = size / d;

        /* If there's a remainder, deal with it */
        if(size % d) {
                m = (10 * (size - (n * d)) + (d / 2) ) / d;

                if (m >= 10) {
                        m -= 10;
                        n += 1;
                }
        }

        info ("%2ld", n);
        if (m) {
                info (".%ld", m);
        }
        info (" %cB%s", c, s);
}

#endif

