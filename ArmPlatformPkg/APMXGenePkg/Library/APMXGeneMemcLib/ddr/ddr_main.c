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
 * This is the main init function file. The init is attached to the
 * apm_memc structure. These are the top level init function used
 * to initialize the system's ddr controllers. 
 *
 **/

#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

#if defined(APM_VBIOS)
#include <ddr_driver.h>
#endif

/*  Library User Defined parameters to known state  */
void ddr_sys_user_params_default(struct apm_memc *memc)
{
	struct apm_mcu *mcu;
	unsigned int iia;

	/* Initialize User Defined Data Structure to okay values */
	debug("DRAM: user_defined setup\n");
	memc->mc_ud.ud_mcu_mask = 0x1;
	memc->mc_ud.ud_mcb_intrlv = 1;
	memc->mcb[0].mcb_ud.ud_mcu_intrlv = 1;
	memc->mcb[1].mcb_ud.ud_mcu_intrlv = 1;

	memc->mc_ud.ud_skip_ecc_init = 0;
	memc->mc_ud.ud_ignore_init_cecc_err = 0;
	memc->mc_ud.ud_ignore_init_parity_err = 1;
	memc->mc_ud.ud_reset_on_err = 0;

	memc->p_spd_get = NULL;
	memc->mc_ud.ud_is_cache_on = 1;

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		mcu->mcu_ud.ud_speed = 1600;
		mcu->mcu_ud.ud_ECCscheme = 3U;
		mcu->mcu_ud.ud_en2tmode = MCU_ENABLE_2T_MODE;
		mcu->mcu_ud.ud_rank_intrlv = 1;
		mcu->mcu_ud.ud_rank_hash_en = 0;

		mcu->mcu_ud.ud_pllforce = 0;
		mcu->mcu_ud.ud_pllforce_div = 0;
		mcu->mcu_ud.ud_pllctl0_idiv = 0;
		mcu->mcu_ud.ud_pllctl0_fbdiv = 0;
		mcu->mcu_ud.ud_pllctl0_odiv = 0;

		mcu->mcu_ud.ud_zqcal_en = 0;
		mcu->mcu_ud.ud_zqcal_code = PHY_ZQCAL_CODE_VALUE;
		mcu->mcu_ud.ud_phy_zqcount = PHY_ZQCAL_COUNT;

		mcu->mcu_ud.ud_relax_time_en = 0x1;
		mcu->mcu_ud.ud_tmargin = 0x110000U;
		mcu->mcu_ud.ud_sysrd2rdmargin = 0;
		mcu->mcu_ud.ud_sysrd2wrmargin = 0;
		mcu->mcu_ud.ud_syswr2wrmargin = 0;
		mcu->mcu_ud.ud_syswr2rdmargin = 0;
		mcu->mcu_ud.ud_cl_margin = 0;
		mcu->mcu_ud.ud_tcrl = KCPHY_ADD_T_CRL_MARGIN;
		mcu->mcu_ud.ud_tcwl = KCPHY_SUB_T_CWL_MARGIN;
		mcu->mcu_ud.ud_wrlvl_min_smpl = KCPHY_PEVM_WRLVL_MIN_SMPLS;
		mcu->mcu_ud.ud_wrlvl_smpl_per_dly = KCPHY_PEVM_WRLVL_SMPL_PER_DLY;

		mcu->mcu_ud.ud_bit_dq_stren = KCPHY_BIT_DQ_STREN;
		mcu->mcu_ud.ud_bit_ad_stren = KCPHY_BIT_AD_STREN;
		mcu->mcu_ud.ud_bit_cmd_stren = KCPHY_BIT_CMD_STREN;
		mcu->mcu_ud.ud_bit_ctl_stren = KCPHY_BIT_CTL_STREN;
		mcu->mcu_ud.ud_bit_clk_stren = KCPHY_BIT_CLK_STREN;
		mcu->mcu_ud.ud_bit_odt_stren = KCPHY_BIT_ODT_STREN;

		mcu->mcu_ud.ud_bit_dq_slew = KCPHY_BIT_DQ_SLEW;
		mcu->mcu_ud.ud_bit_ad_slew = KCPHY_BIT_AD_SLEW;
		mcu->mcu_ud.ud_bit_cmd_slew = KCPHY_BIT_CMD_SLEW;
		mcu->mcu_ud.ud_bit_ctl_slew = KCPHY_BIT_CTL_SLEW;
		mcu->mcu_ud.ud_bit_clk_slew = KCPHY_BIT_CLK_SLEW;

		mcu->mcu_ud.ud_mimicSPD = 0;
		mcu->mcu_ud.ud_mimic_activeslots = 1;
		mcu->mcu_ud.p_ddr_mimic_spd_array = NULL;
		mcu->mcu_ud.ud_sw_wrcal = 0;
		mcu->mcu_ud.ud_rddeskew_en = EN_RDDESKEW;
		mcu->mcu_ud.ud_rdlvl2nd_en = EN_RDLVL2ND;
		mcu->mcu_ud.ud_wrdeskew_en = EN_WRDESKEW;
		mcu->mcu_ud.ud_dskrank = DESKEW_RANK_NO;

		mcu->mcu_ud.ud_sw_rdlvl = 0;
	}
}

/* 
 * Initialize up to 2 Mcb and 4 Mcu
 */
int ddr_sys_setup(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia;

	debug("DRAM: memc setup - Storm revision %s\n", 
					is_storm_revA()? "Ax" : "B0");

	/* Initialize DDR structure */
	memc->p_mcb_reset = memc_dummy_fn;
	memc->p_mcu_reset = memc_dummy_fn;
	memc->p_mc_pwr_ok = mcu_assert_mc_pwr_ok;
	memc->p_memsys_unreset = memsys_unreset;
	memc->p_mem_test_init = memc_dummy_fn;
	memc->p_addressmap = memc_addr_cfg;
	memc->p_tlb_map = memc_dummy_fn;

	ddr_sys_user_params_default(memc); 
	/* Overload user defined DDR params and routines */
	if (!memc->p_usr_setup)
		memc->p_usr_setup = memc_dummy_fn;
	err = memc->p_usr_setup(memc); 

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		mcu->id = iia;
		mcu->parent = (void*)memc;
		mcu->enabled = (memc->mc_ud.ud_mcu_mask >> iia) & 1;
		memc->mcu_mask |= mcu->enabled << iia;

		/* Mcb0->mcu0/1 :: Mcb1->mcu2/3 */
		mcu->mcb_id = iia / 2;	
		mcu->base = PCP_RB_MCU_BASE + iia * PCP_RB_MCU_OFFSET;
		mcu->phy_addr = mcu->base;
		mcu->csw_base = PCP_RB_CSW_BASE;

		mcu->mcb_base = (iia < 2) ? PCP_RB_MCB_BASE :
			(PCP_RB_MCB_BASE + PCP_RB_MCB_OFFSET);

		mcu->mcu_rd = mcu_read_reg;
		mcu->mcu_wr = mcu_write_reg;
		mcu->mcu_rmw = mcu_regmod;
		mcu->phy_rd = phy_read_reg;
		mcu->phy_wr = phy_write_reg;
		mcu->mcb_rd = mcb_read_reg;
		mcu->mcb_wr = mcb_write_reg;
		mcu->csw_rd = csw_read_reg;
		mcu->csw_wr = csw_write_reg;

		mcu->prbs_test = 0;
		mcu->bist_test = 0;
		mcu->p_phy_pre_init = memc_dummy_fn;
		mcu->p_prbs_test = memc_dummy_fn;
		mcu->p_bist_test = memc_dummy_fn;
		mcu->p_phy_retrain = memc_dummy_fn;

		mcu->p_ud_fixup_config = memc_dummy_fn;
		mcu->p_spd_init = (SKIP_SPD_INIT)? memc_dummy_fn : ddr_spd_init;
		mcu->p_timing_config = (SKIP_SPD_INIT || SKIP_TIMING_CONFIG)?
					memc_dummy_fn : mcu_timing_config;
		mcu->p_csr_config = mcu_csr_config;
		mcu->p_pre_init = mcu_pre_init;
		mcu->p_phy_setup = mcu_kc_phy_setup_tc;
		mcu->p_post_init = mcu_post_init;
		mcu->p_phy_post_init = mcu_post_assert_mc_pwr_tc;
		mcu->p_dimm_post_init = dimm_mcu_fsm_init;
		mcu->p_phy_calib = calib_pevm_custom_steps;
		mcu->p_post_train_setup = mcu_post_train_setup;
		mcu->p_meminitdone = mcu_en_traffic_mem_init_done;
		mcu->p_sw_phy_retrain = mcu->mcu_ud.ud_sw_rdlvl? 
					sw_phy_retrain : memc_dummy_fn;

	}

	/* Setup apm_memc with generic values */
	populate_mc_default_parms(memc);

	return err;
}

int ddr_sys_spd_calc(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, ecc_en;

	debug("DRAM: SPD discovery and timing calc\n");
	ecc_en = 0;
	/*
	 * SPD init & setup for bringup
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		/* SPD read & timing parameter generation */
		err |= mcu->p_spd_init(mcu);
		/* DDRlib struct fillup & crosscheck spd vs test-requirements */
		err |= mcu->p_timing_config(mcu);
		if (mcu->enabled)
			ecc_en |= ((mcu->mcu_ud.ud_ECCscheme != 0)
					&& mcu->mcu_params.ECCenable) ? 1 : 0;
	}

	if (ecc_en && !memc->mc_ud.ud_skip_ecc_init) 
		memc->p_mem_test_init = memc_ecc_init_en;

	return err;
}

int ddr_sys_init(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	int iia;

	debug("DRAM: system initialization this time\n");
	/* Top Level MCU/PHY-PLL turn on and Unreset memory sub-system */
	err += memc->p_memsys_unreset(memc);
	if (err) {
		debug("\nMemory sub-system Unreset ERROR [%d]\n", err);
		return err;
	}
	/* Memory controller pre setup/initialization */ 
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		if (!mcu->enabled)
			continue;

		/* MCU CSR setup */
		err += mcu->p_csr_config(mcu);
		/* MCU pre power ok initialization */
		err += mcu->p_pre_init(mcu);
		if (err) {
			debug("\nPre-Init ERROR [%d]\n", err);
			return err;
		}
	}

	err += memc->p_addressmap(memc);
	if (err) {
		debug("\nAddress Map ERROR [%d]\n", err);
		return err;
	}
	err += memc->p_tlb_map(memc);
	if (err) {
		debug("\nTLB Map ERROR [%d]\n", err);
		return err;
	}
	/* Assert DDR_MC_POWER_OK since  MCU have common pin. */  
	err += memc->p_mc_pwr_ok(mcu);

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!mcu->enabled)
			continue;
	 	/* MCU post power of initialization */
		err += mcu->p_post_init(mcu);
		if (err) {
			debug("\nPost-Init ERROR [%d]\n", err);
			return err;
		}
	 	/* MCU-BIST */
		if (mcu->bist_test)
			err += mcu->p_bist_test(mcu);
		if (err) {
			debug("\nBIST ERROR [%d]\n", err);
			return err;
		}
	}

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!mcu->enabled)
			continue;
	 	/* MCU- Poll InitDone */
		err += mcu->p_post_train_setup(mcu);
		err += mcu->p_meminitdone(mcu);
		if (err) {
			debug("\nPost-Train / Init-Done ERROR [%d]\n", err);
			return err;
		}
	}

	/* Do sw PHY retraining */
	if (!mcu->mcu_ud.ud_sw_rdlvl)
		goto skip_sw_rdlvl; 
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!mcu->enabled)
			continue;

		err += mcu->p_sw_phy_retrain(mcu);
		if (err) 
			debug("\nSW PHY retraining ERROR [%d]\n", err);
	}
skip_sw_rdlvl:

	/* MEMC - test memory or initialize with ECC syndrome and enable ECC */
	err += memc->p_mem_test_init(memc);
	if (err) {
		debug("ECCinit ERROR [%d]\n", err);
		return err;
	}

	debug("DRAM: memc setup DONE!\n");
	return err;
}
