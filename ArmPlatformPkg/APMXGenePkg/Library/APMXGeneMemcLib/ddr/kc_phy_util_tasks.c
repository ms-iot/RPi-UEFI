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

#undef DEBUG 

#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "kc_phy_util_reg_flds.h"

/******************************************************************************
 *   KC PHY Tasks copied from KC Release and modified for RB
 *   /projects/svdc/vrelease/koolchip_phy/KC_T40G_D3_2G_R00_R16/
 *					verification/testbench/PHYReg_tasks.vh
 * - remove @(posedge regInfInst.clk);
 * - added input for x4
 * - seperated into two tasks
 *
 * - translated into C from SV from:
 *    potenza/MAIN/dv/lib/sv/seqs/rb/rb_mcu_kc_reg_tasks.svh#11
 *****************************************************************************/

/* 
 * kc_phy_timing_param_setup
 * Normalize to DFI clocks 
 */
void kc_phy_timing_param_setup(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned cmul = (mcu->mcu_params.single_clock_mode) ? 0 : 1;

	/* Act to Rd */
	mcu->phy_params.TRCD = 
		(((mcu->mcu_params.bank_actrd << cmul) & 0xFF) > 16)? 
		((mcu->mcu_params.bank_actrd << cmul) + 1) : 16;
	mcu->phy_params.TMOD = 16;
	mcu->phy_params.TMRD = 6;
	/* Rd to Pre */
	mcu->phy_params.TRP = 
		(((mcu->mcu_params.bank_rdpre << cmul) & 0xFF) > 14)?
		(mcu->mcu_params.bank_rdpre << cmul) : 14;
	/* Write Leveling DQS Delay. minimum time before first DQS */
	mcu->phy_params.TWLMRD = 4;
	/* Wr to Rd */
	mcu->phy_params.TWRD = 
		(((mcu->mcu_params.rank_wrrd << cmul) & 0xFF) > 16)?
		(mcu->mcu_params.rank_wrrd << cmul) : 16;
	return;
}

/*
 * kc_phy_cdr_lock
 * From TestChip CDR Lock
 */
void kc_phy_cdr_lock(void *ptr)
{			

	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int rddata, rddata2;

	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_CDR_LOCK_RESET, 0x1f);
	DELAYP(2);
	phy_write_reg(mcu, PHY_REG_CFG_CDR_ENABLE, 0x0);
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_CDR_LOCK_RESET, 0x0);	
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_CDR_RESETB, 0x1);
	DELAYP(1);
	phy_write_reg(mcu, PHY_REG_CFG_CDR_CONFIG, 0x3ec2);	
	DELAYP(2);

	/* All CDR LOCK */
	phy_write_reg(mcu, PHY_REG_CFG_CDR_ENABLE, 0x1F);	
	DELAYP(2);
	phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);

	/* From KC routine lock_check_apm() */
	DELAYP(2);
	phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);

	rddata = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE);	
	DELAYP(10);
	rddata2 = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE);
	if (rddata != rddata2) 
		debug("ERROR PI CODE change after CDR Lock 0x%x -> 0x%x\n",
						      rddata, rddata2);

	/* From KC routine deassert_phy_soft_reset_apm() */
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
	DELAYP(2);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);

	return;
}

void kc_phy_quick_setup(void *ptr)
{
	int unsigned wdata = 0;
	unsigned int auto_zqcal_count;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	phy_param_t *p_phy = &mcu->phy_params;

	/* setup Analog */
	/* AM/DM Stength/Slew Rates */
	phy_write_reg(mcu, PHY_REG_CFG_RECEIVER_BIAS, 0x7ffff);	

	if (mcu->mcu_ud.ud_zqcal_en) 
		phy_sw_adj_ctrlupdate(ptr);
	else 
		phy_write_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE, 
					mcu->mcu_ud.ud_zqcal_code);

	if (mcu->mcu_params.all_DIMMs_quadrank)
		phy_write_reg(mcu, PHY_REG_CFG_RANK_SHARE, 0xF5A0F5A0);
	else
		phy_write_reg(mcu, PHY_REG_CFG_RANK_SHARE, 0xE4E4E4E4);

	/*
	 * setup I/Os 
	 * Mode Register 
	 *	BIT_CFG_READ_W_FIXED_DELAY_12_1 = 0x1
	 *	BIT_CFG_RDLVL_MODE_6_2_ = 0x2
	 *	BIT_CFG_WRLVL_MODE_4_2 = 0x2
	 *	BIT_CFG_RDLVL_GATE_MODE_2_2 = 0x2
	 *	BIT_CFG_CMD_OE_0_1 = 0x1
	 *	BIT_CFG_RESET_OE_1_1 = 0x1
	 *	BIT_CFG_X4_EN_14_1 = 0x0
	 *	BIT_CFG_PARITY_OE_15_1 = 0x0
	 */
	wdata = (KCPHY_USE_READ_W_FIXED_DELAY << 12) | 
		((p_phy->cfg_parity_oe & 0x1) << 15) | 
		((mcu->mcu_params.by4_mode & 0x1) << 14) | 
		((p_phy->phy_train_mode & 0x3) << 6) | 
		((p_phy->phy_train_mode & 0x3) << 4) | 
		((p_phy->phy_train_mode & 0x3) << 2) | 0x3;	
	phy_write_reg(mcu, PHY_REG_CFG_PHY_CONFIG, wdata);

	/* Disable DLL Calibration */
	phy_write_reg(mcu, PHY_REG_CFG_DISABLE_DLL_CAL, 0x2);	

	/* Configure Training Registers */
	wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_1);
	wdata = ((mcu->phy_tr_dly.wrlvl_min_smpl & 0xFF) << 24) |
		((mcu->phy_tr_dly.wrlvl_dly_stsize & 0xFF) << 16) |
		((mcu->phy_tr_dly.wrlvl_smpl_per_dly & 0xF) << 12) |
		((mcu->phy_tr_dly.wrlvl_max_delay_limit & 0xFFF));
	phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_1, wdata);

	wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_2);
	wdata = ((mcu->phy_tr_dly.rdlvl_dly_stsize & 0xFF) << 16) |
		((mcu->phy_tr_dly.rdlvl_smpl_per_dly & 0xF) << 12) |
		((mcu->phy_tr_dly.rdlvl_max_delay_limit & 0xFFF));
	phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_2, wdata);

	wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_3);
	wdata = ((mcu->phy_tr_dly.gtlvl_min_smpl & 0xFF) << 24) |
		((mcu->phy_tr_dly.gtlvl_dly_stsize & 0xFF) << 16) |
		((mcu->phy_tr_dly.gtlvl_smpl_per_dly & 0xF) << 12) |
		((mcu->phy_tr_dly.gtlvl_max_delay_limit & 0xFFF));
	phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_3, wdata);

	wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_4);
	wdata = ((mcu->phy_tr_dly.cfg_gate_retrain_val & 0xFF) << 16) |
		((mcu->phy_tr_dly.wrcal_max_delay_limit & 0xFFF));
	phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_4, wdata);

	/* Enable Only CK0,2,4,6 */
	wdata =	((mcu->phy_params.cfg_cs_en & 0xFF) << 24) |
		((mcu->phy_params.cfg_ck_en & 0xFF) << 16) |
		((mcu->phy_params.cfg_odt_en & 0xFF) << 8) |
		((mcu->phy_params.cfg_cke_en & 0xFF));
	phy_write_reg(mcu, PHY_REG_CFG_MEM_OE, wdata);	

	if (!(mcu->mcu_params.ECCenable))
		mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_NOECC_MASK;
	if (mcu->mcu_params.by4_mode) 
		phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, 
				(mcu->phy_params.cfg_macro_en_val & 
				KCPHY_CFG_MACRO_x4_MASK));
	else 
		phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, 
				(mcu->phy_params.cfg_macro_en_val & 
				KCPHY_CFG_MACRO_x8_MASK));

	/* any valid dimm address */	
	phy_write_reg(mcu, PHY_REG_CFG_WRCAL_ADDR, 0x00001200);	

	/* DIMM related setup */
	auto_zqcal_count = mcu->mcu_ud.ud_phy_zqcount;
	phy_write_reg(mcu, PHY_REG_CFG_ZQ_COUNTER, auto_zqcal_count);	

	return;
}	/*  kc_phy_quick_setup */

void kc_phy_drv_strength_slew_setup(void *ptr)
{
	int unsigned wdata = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	wdata =	((mcu->mcu_ud.ud_bit_cmd_stren & 0x7) << 18) |
		((mcu->mcu_ud.ud_bit_ad_slew & 0x3) << 16) |
		((mcu->mcu_ud.ud_bit_ad_stren & 0x7) << 13) |
		((mcu->mcu_ud.ud_bit_dq_slew & 0x3) << 8) |
		((mcu->mcu_ud.ud_bit_dq_stren & 0x7) << 5) |
		((mcu->mcu_ud.ud_bit_dq_slew & 0x3) << 3) |
		(mcu->mcu_ud.ud_bit_dq_stren & 0x7);
	phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_2, wdata);	

	wdata =	((mcu->mcu_ud.ud_bit_odt_stren & 0x7) << 12) |
		((mcu->mcu_ud.ud_bit_clk_slew & 0x3) << 10) |
		((mcu->mcu_ud.ud_bit_clk_stren & 0x7) << 7) |
		((mcu->mcu_ud.ud_bit_ctl_slew & 0x3) << 5) |
		((mcu->mcu_ud.ud_bit_ctl_stren & 0x7) << 2) |
		(mcu->mcu_ud.ud_bit_cmd_slew & 0x3);
	phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_3, wdata);	

	return;
}

/*
 *  main Driver for PHY setup
 */
int mcu_kc_phy_setup_tc(void *ptr)
{
	unsigned int wdata, readData, dat;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	phy_param_t *p_phy = &mcu->phy_params;
	int unsigned __attribute__ ((unused)) en_dll_cal =
					p_phy->en_phy_dll_cal;
	int unsigned __attribute__ ((unused)) lo_freq = p_phy->dll_cal_lo_freq;

	/* KC PHY setup timing paramters from Mcu/SPD settings */
	debug2("Mcu PHY%1d param setup ...x4=%1d dllcal=%1d lofreq=%1d \n",
			mcu->id, mcu->mcu_params.by4_mode, en_dll_cal, lo_freq);
	debug("MCU-PHY %d: INFO: Finish KC PLL Lock stuff \n", mcu->id);
	mcu->phy_wr(mcu, PHY_REG_CFG_CDR_RESETB, 0x0);
	DELAY(120);
	mcu->phy_wr(mcu, PHY_REG_CFG_PRBS_RESETB, 0x0);
	DELAY(120);
	mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
	DELAY(120);

	/* setup Dimm timings */
	/* KC PHY Timing Init */
	kc_phy_timing_param_setup(ptr);

	debug("MCU-PHY %d: INFO: drive strengthn-slew setup \n", mcu->id);
	kc_phy_drv_strength_slew_setup(ptr);

	debug("MCU-PHY %d: INFO: CSR Setup \n", mcu->id);
	kc_phy_quick_setup(ptr);

	wdata = (((mcu->phy_params.TWLMRD) & 0xFF) << 24) | 
		(((mcu->phy_params.TMOD) & 0xFF) << 16) | 
		(((mcu->phy_params.twrlvl_ww) & 0xFF) << 8) |
		((mcu->phy_params.TRP) & 0xFF);
	phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_1, wdata);

	wdata = (((mcu->phy_params.TRCD) & 0xFF) << 24) | 
		(((mcu->phy_params.TWRD) & 0xFF) << 16) | 
		(((mcu->phy_params.WL) & 0xFF) << 8) |
		((mcu->phy_params.RL) & 0xFF);
	phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_2, wdata);

	debug("PHY[%d] WL=%2d RL=%2d \n", mcu->id, mcu->phy_params.WL,
							mcu->phy_params.RL);

	/* CDR reset & lock & deassert_phy_soft_reset */
	debug("PHY[%d[: CDR LOCK start\n", mcu->id);
	kc_phy_cdr_lock(ptr);	

	debug("MCU-PHY %d: INFO: DLL Cal not enabled\n", mcu->id);
	/* KC recommends not using DLL Calibration */

	debug("MCU-PHY %d: INFO: 180 enabled\n", mcu->id);
	/* NOTE: Address calibration - 180 deg */
	phy_write_reg(mcu, PHY_REG_CFG_ADDR_CAL_EN, 0x25);
	DELAY(20);
	readData = 0;
	while (readData == 0) 
		readData = phy_read_reg(mcu, PHY_REG_CFG_ADDR_CAL_DONE);	

	/* PostTC rtl settings */
	dat = phy_rf_read_dqs_weak_pull_down_disable(ptr);
	/* value 0x0 by default - weak pull down on */
	if (mcu->phy_params.phy_disable_pullup) {
		dat = (dat & 0xFFFFFFFE) | (0x1 & 
				mcu->phy_params.phy_disable_pullup);
		phy_rf_write_dqs_weak_pull_down_disable(ptr, dat);
	}
	phy_rf_write_cfg_timeout_counter(ptr, (0x3FFFFF << 10));

	/* set WrLvl OR gate */
	dat = phy_rf_read_spare_register_1_0(ptr);
	dat = (dat & 0xFFFFFFFC) | (PHY_WRLVL_USE_OR_GATE << 1);
	/*
	 * bit 0 must be 0 in 1:1 mode !!!DUHHHHHHHHHH!!
	 * bit 1 = 1 for WrLvl OR gate ( = 0 for AND gate)
	 */
	phy_rf_write_spare_register_1_0(ptr, dat);

	/* 
	 * For Storm B0, turn on if you intent to use RevA RDE algorithm  
	 * PHY_REG_SPARE_REGISTER_1_0[31]: disable_cumulative_fail
	 * PHY_REG_SPARE_REGISTER_1_0[23]: disable_consecutive_match
	 */
	if (0) {
		debug("MCU-PHY %d: Use Storm RevA RDE algorithm\n", mcu->id);
		readData = phy_read_reg(mcu, 0xF2C);
		wdata = readData | (1 << 31) | (1 << 23); 
		phy_write_reg(mcu, 0xF2C, wdata);
	}

	DELAY(20);
	readData = phy_read_reg(mcu, PHY_REG_CFG_CMD_CODE);	
	debug("PHY[%d] PI+180 Code: 0x%0x\n", mcu->id, readData);

	if (p_phy->phy_short_gt_preamble_en != 0) {
		dat = mcu->phy_params.phy_short_gt_preamble_val;
		mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_3, dat);
		dat = ((dat & 0xFF) << 24) | ((dat & 0xFF) << 16) | 
			((dat & 0xFF) << 8) | ((dat & 0xFF));
		mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_1, dat);
		mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_2, dat);
	}

	debug("PHY[%d] init config done. "
			"Ready for dfi_init_start...\n", mcu->id);
	return 0;
}	/* mcu_kc_phy_setup_tc */

