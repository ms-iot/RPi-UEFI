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

/*
 * Mcu_RESET FSM tasks
 *  Same as SV code: rb_mcu_request_seq_base.svh
 *  task mcu_CSR_reset_status_poll
 *  POLL MCU Reset status (RO) csr for FSM state , errors mem_init_done etc
 */
int mcu_reset_status_poll(void *p, unsigned int status, unsigned int mask,
		unsigned int flag)
{
	unsigned int done, rddata;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	done = 0;
	do {
		rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
		if (flag == POLL_EQUAL) {
			if ((rddata & mask) == (status & mask))
				done = 1;
			else
				DELAY(1);
		} else if (flag == POLL_LESS) {
			if ((rddata & mask) <= (status & mask))
				done = 1;
			else
				DELAY(1);
		} else if (flag == POLL_GREATER) {
			if ((rddata & mask) >= (status & mask))
				done = 1;
			else
				DELAY(1);
		}
	} while (done == 0);
	return rddata;
}

int mcu_init_done_poll(void *p)
{
	unsigned int status, mask;

	status = mask = 1;
	return (mcu_reset_status_poll(p, status, mask, POLL_EQUAL));
}

int mr_prog_done_poll(void *p)
{
	unsigned int status, mask;

	status = mask = 0x80;
	return (mcu_reset_status_poll(p, status, mask, POLL_EQUAL));
}

void mcu_reset_FSM_poll(void *p, unsigned int status, unsigned int flag)
{
	unsigned int mask;
	struct apm_mcu __attribute__ ((unused)) * mcu = (struct apm_mcu *)p;

	status = (status & 0x7F) << 24;
	mask = 0x7F000000;
	mcu_reset_status_poll(p, status, mask, flag);
}

/*
 * Mcu - Dimm Initialization Sub Tasks
 */
int mcu_pre_assert_mc_pwr(void *ptr)
{
	unsigned int reg;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	/*
	 * DFI reset
	 */
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	reg &= 0xFFFFFFFB;
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/*
	 * PHY PBRS & TR reset
	 */
	phy_rf_write_cfg_prbs_srst(mcu, 0x0);
	phy_rf_write_cfg_tr_srst(mcu, 0x0);

	return 0;
}

int mcu_post_assert_mc_pwr_tc(void *ptr)
{
	unsigned int reg;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	/* 
	 * Note: 
	 * TestChip does: MC_POWER_OK -> dfi_init_start -> dfi_reset (deassert)
	 */

	DELAYP(2);
	/*
	 * DFI reset
	 */
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	reg &= 0xFFFFFFFB;	
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/* 
	 * Start DFI initialization
	 */
	DELAYP(1);
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	if (1 == ((reg >> MCU_DFI_INIT_CTL_DFI_RESET_RNG) & 0x1)) {
		/* DFI RESET still asserted - turn off */
		mcu_pre_assert_mc_pwr(mcu);
	}
	/* Toggle signal dfi_init_start to PHY */
	reg |= 0x00000001;	
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);
	reg &= 0xFFFFFFFE;
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/* Wait for Signal dfi_init_complete from PHY */
	do {
		reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_STS);
	} while ((reg & 0x1) == 0);

	return 0;
}

int mcu_pre_init(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	if (!mcu->enabled)
		return 0;
	debug("\n------- MCU[%d] - Pre-Init --------\n", mcu->id);

	/*
	 * Reset CKE
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	mcu->p_phy_setup(ptr);

	/*
	 * Pre DDR_MC_POWER_OK phy init
	 */
	mcu->p_phy_pre_init(ptr);
	return 0;
}

int mcu_post_init(void *ptr)
{
	int err = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	if (!mcu->enabled)
		return 0;
	debug("\n------- MCU[%d] - Post-Init --------\n", mcu->id);
	/*
	 * Post assert MC power ok
	 */
	err += mcu->p_phy_post_init(ptr);
	err += mcu->p_prbs_test(ptr);
	err += mcu->p_dimm_post_init(ptr);
	err += mcu->p_phy_calib(ptr);
	return err;
}

int phy_sw_adj_ctrlupdate(void *ptr)
{
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int rddata = 0;
	unsigned int poszq, txpren;
	unsigned int negzq;
	unsigned int err = 0;
	unsigned int posgood, neggood;

	if (!mcu->enabled) 
		return 0;

	/* Read PHY ZQ cal code after first Phy Ctrl Update */
	rddata = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("PHY[%d] Original ZQ Cal Code: 0x%0x\n", mcu->id, rddata);

	/*
	 * Setup initialization control
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	/* Write FSM delay values - should be done is csr config */
	rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
	txpren = (rddata >> MCU_RSTSTS_TXPROVER_RNG) & 0x1U;
	txpren = (~txpren) & 0x1U;
	rddata = (rddata >> MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG) & 0x1U;
	/* 
	 * if traffic, then use REF to clear Ops b4 CtrlUp 
	 * Preserve mem_init_done (traffic)
	 */
	fsm_init_seq = (rddata << MCU_DDR_INIT_SEQ_PREREFRESHENAB_RNG) |
			(txpren << MCU_DDR_INIT_SEQ_TXPRENAB_RNG) | 
			(1U << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | 
			(rddata << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);	

	fsm_init_ctl = (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
			((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
			((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	
	DELAY(10);
	rddata = (txpren << MCU_RSTSTS_TXPROVER_RNG) |
			(1U << MCU_RSTSTS_CTLUPDTOVER_RNG);
	mcu_reset_status_poll(mcu, rddata, rddata, POLL_EQUAL);
	DELAY(10);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	/* Read PHY ZQ cal code after first Phy Ctrl Update */
	rddata = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug1("PHY[%d] New ZQ Cal Code: 0x%0x\n", mcu->id, rddata);
	poszq = rddata & 0x3FU;
	negzq = (rddata >> 6) & 0x3FU;
	posgood = ((poszq > 0x8) && (poszq < 0x3F)) ? 1 : 0;
	neggood = ((negzq > 0x8) && (negzq < 0x3F)) ? 1 : 0;

	/* Check if ZQ value is good */
	if (posgood && neggood) {
		debug1("PHY[%d] ZQ Calibration GOOD [pu:0x%x pd:0x%x]\n",
				mcu->id, poszq, negzq);
#ifdef PHY_FIX_BROKEN_ZQCAL
	} else if (posgood) {
		debug1("PHY[%d] ZQ Calibration PD-BROKEN [pu:0x%x]\n", 
							mcu->id, poszq);
		/* PHY ZQ broken - copy positive into negative */
		rddata = poszq | (poszq << 6);
	} else if (neggood) {
		debug1("PHY[%d] ZQ Calibration PU-BROKEN [pd:0x%x]\n", 
							mcu->id, negzq);
		rddata = negzq | (negzq << 6);
	} else {
		debug1("PHY[%d] ZQ Calibration BROKEN [FIXING:0x%x]\n", 
				mcu->id, mcu->mcu_ud.ud_zqcal_code);
		rddata = mcu->mcu_ud.ud_zqcal_code;
#else
	} else {
		pr_err("PHY[%d] ZQ Calibration BROKEN [pu:0x%x pd:0x%x]\n",
						mcu->id, poszq, negzq);
		/* Hang on error */
		while(1);	
#endif
	}
	if (!err) {
		mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE, rddata);
		debug("PHY[%d]  ZQ Cal Code: wrote back 0x%0x\n", 
							mcu->id, rddata);
		rddata = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	}
	debug("PHY[%d]  ZQ Cal Code: 0x%0x\n", mcu->id, rddata);
	return err;
}	/*  phy_sw_adj_ctrlupdate */

int lrdimm_mcu_fsm_init(void *ptr)
{
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int err = 0;

	/* Setup initialization control */
        fsm_init_ctl =
            (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
            ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
            ((0x3U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_CLK200ENAB_RNG) |
		(1 << MCU_DDR_INIT_SEQ_CLK500ENAB_RNG) |
		(1 << MCU_DDR_INIT_SEQ_TXPRENAB_RNG) |
		((mcu->mcu_params.rc_en & 0x1) << MCU_DDR_INIT_SEQ_RCENAB_RNG) |
		(1 << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		((DO_INIT_SEQ_CTLUPDATE & mcu->mcu_ud.ud_zqcal_en) <<
		 				MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);   
	DELAY(600);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	/* Memory Buffer Pre-Init */
	lrdimm_mb_init_from_spd_preinit(mcu, 0);

	/* MCK Backup Clock Setup and Training - 800Mbps for HP NVDIMM */
	debug("\nLRDIMM: Init MB Registers Over SMBus For MCK Backup Clock\n");
	lrdimm_mb_init_from_spd_mck(mcu, 0);

	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		(DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);   
	DELAY(600);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	if (mcu->mcu_ud.ud_zqcal_en)
                err = phy_sw_adj_ctrlupdate(ptr);
        else
                mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE,
                                        mcu->mcu_ud.ud_zqcal_code);
	debug("\nLRDIMM Detected: Start MCK Training For Backup Mode\n");
	lrdimm_mb_mck_training(mcu, 0);
	/* CK Standard Clock Setup and Training - Frequency Set By Storm */
	debug("\nLRDIMM Detected: Init MB Registers Over SMBus For CK"
							" Standard Clock\n");
	lrdimm_mb_init_from_spd_ck(mcu, 0);

	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_MRENAB_RNG) |
		/* MR programming comes now in LRDIMM */
		(DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);   
	DELAY(600);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		(DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);  
	DELAY(600);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	if (mcu->mcu_ud.ud_zqcal_en)
                err = phy_sw_adj_ctrlupdate(ptr);
        else
                mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE,
                                        mcu->mcu_ud.ud_zqcal_code);

	debug("\nLRDIMM Detected: Start MB to DRAM Training For Normal"
							" Operations\n");
	lrdimm_mb_ck_training(mcu,0);
	debug("\n");

	lrdimm_mb_normal_op(mcu,0);

	return err;
}

int dimm_mcu_fsm_init(void *ptr)
{
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int __attribute__ ((unused)) rddata = 0;
	unsigned int err = 0;

	if (!mcu->enabled) 
		return 0;

	if (mcu->mcu_params.dimm_type == LRDIMM)
		return lrdimm_mcu_fsm_init(mcu);	
	
	/*
	 * Setup initialization control
	 */
	fsm_init_ctl = (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
			((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
			((0x3U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	/* Write FSM delay values - should be done is csr config */

	/* Read PHY ZQ cal code after first Phy Ctrl Update */
	rddata = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("PHY[%d]  ZQ Cal Code: 0x%0x\n", mcu->id, rddata);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_CLK200ENAB_RNG) | 
			(1 << MCU_DDR_INIT_SEQ_CLK500ENAB_RNG) | 
			(1 << MCU_DDR_INIT_SEQ_TXPRENAB_RNG) | 
			((mcu->mcu_params.rc_en & 0x1) << 
				MCU_DDR_INIT_SEQ_RCENAB_RNG) |
			(1 << MCU_DDR_INIT_SEQ_MRENAB_RNG) |
			(1 << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
			((DO_INIT_SEQ_CTLUPDATE & mcu->mcu_ud.ud_zqcal_en) <<
				MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM - initializing */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);

	DELAY(600);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	if (mcu->mcu_ud.ud_zqcal_en) 
		err = phy_sw_adj_ctrlupdate(ptr);
	else 
		mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE,
					mcu->mcu_ud.ud_zqcal_code);

	return err;
}	/* dimm_mcu_fsm_init */

/*
 * mcu_en_traffic_mem_init_done 
 * After all config, init, training, bist, etc 
 * Enable traffic to flow to Dimms
 */
int mcu_en_traffic_mem_init_done(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;

	debug(" ENTRY: %s > \n", __FUNCTION__);
	if (!mcu->enabled) 
		return 0;

	debug("\n------- MCU[%d] - Poll for Done --------\n", mcu->id);
	debug("MCU[%d] - mcu_en_traffic_mem_init_done\n", mcu->id);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq =
		(1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		((DO_INIT_SEQ_CTLUPDATE & mcu->mcu_ud.ud_zqcal_en) <<
		 MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (1U <<
			 MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
		(0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | 
		((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
		((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
	/* FSM runs ~15-30us */
	DELAY(30);

	/* Wait for traffic to flow */
	mcu_init_done_poll(mcu);

	return 0;
}

/*
 * mcu_dummy_bist_2s_calib
 * After all config, init, training, etc
 * Prevents traffic from CSW to dimms
 * Sets up Mcu BIST engine 
 *    no checking done here. must be done by user.
 * turnon - enables bist and exit 
 - otherwise user can enable after init
 */
int mcu_dummy_bist_2s_calib(void *ptr, unsigned int rank0, unsigned int turnon)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned ia, bctrl;
	unsigned int __attribute__ ((unused)) foo;

	if (!mcu->enabled) 
		return 0;

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("MCU-PHY[%d]  CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	for (ia = 0; ia < 5; ia++) 
		mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * ia)),
					    (0xF5A97C0 | (ia + 3)));

	bctrl = ((mcu->mcu_params.rank_rdwr & 0x1F) << 27) |
		((mcu->mcu_params.rank_wrrd & 0x1F) << 22) |
		((mcu->mcu_params.rank_wrwr & 0xF) << 18) |
		((mcu->mcu_params.rank_rdrd & 0xF) << 14) |
		((rank0 & 0x7) << 11) |	((rank0 & 0x7) << 8) |
		((rank0 & 0x7) << 5) | ((rank0 & 0x7) << 2) | 0x1;
	mcu->mcu_wr(mcu, MCU_REG_BISTROWCOL, 0x012301F0);
	mcu->mcu_wr(mcu, MCU_REG_BISTCTLSTS, bctrl);

	fsm_init_seq =
		(1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		(1U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
		((DO_INIT_SEQ_CTLUPDATE & mcu->mcu_ud.ud_zqcal_en) <<
		 MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
			 MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
		((turnon & 0x1U) << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
		((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
		((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
	DELAY(100);
	fsm_init_seq =
		(0U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		(1U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
		((DO_INIT_SEQ_CTLUPDATE & mcu->mcu_ud.ud_zqcal_en) <<
		 MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
			 MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	bctrl &= ~(0x3);
	mcu->mcu_wr(mcu, MCU_REG_BISTCTLSTS, bctrl);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	return 0;
}	/* mcu_dummy_bist_2s_calib */

/*
 * MCU Error check
 */
int mcu_error_status(void *ptr)
{
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int mcu_id = 0;
	unsigned int rddata = 0;
	int err = 0;

	debug("MCU error checking...\n");
	for (mcu_id = 0; mcu_id < CONFIG_SYS_NUM_DDR_CTLRS; mcu_id++) {
		mcu = (struct apm_mcu *)&memc->mcu[mcu_id];
		if (!(mcu->enabled))
			continue;
		rddata = mcu->mcu_rd(mcu, MCU_CPU_REG0_MCUGECR);
		debug("MCU[%d] Read MCUGECR = 0x%X\t", mcu_id, rddata);

		rddata = mcu->mcu_rd(mcu, MCU_CPU_REG0_MCUGESR);
		debug("Read MCUGESR = 0x%X\n", rddata);
		/* DDR_PHY_PARITY_ERR: Ignoring for Board-issue */
		if (memc->mc_ud.ud_ignore_init_parity_err)
			rddata &= ~(0x8U);
		/* SW Uboot: Ignore Init CECC Error */
		if (memc->mc_ud.ud_ignore_init_cecc_err)
			rddata &= ~(0x4U);
		if (rddata == 0)
			continue;
		err++;
		if (err)
			pr_err("ERROR! Init Failure ...\n");

		if (0x1 & (rddata >> 11))
			pr_err("MCU[%d]: PHY_TRAINING_ERR\n", mcu_id);
		if (0x1 & (rddata >> 10))
			pr_err("MCU[%d]: PHY_WRITE_LEVELING_TIMEOUT_ERR\n",
			       mcu_id);
		if (0x1 & (rddata >> 9))
			pr_err("MCU[%d]: PHY_READ_GATE_TRAINING_TIMEOUT_ERR\n",
			       mcu_id);
		if (0x1 & (rddata >> 8))
			pr_err("MCU[%d]: PHY_READ_LEVELING_TIMEOUT_ERR\n",
			       mcu_id);
		if (0x1 & (rddata >> 7))
			pr_err("MCU[%d]: MCU_ILLEGAL_ADRS_ERR\n", mcu_id);
		if (0x1 & (rddata >> 6))
			pr_err
			    ("MCU[%d]: MCU_CONTROL_REGISTER_CONSISTENCY_ERR\n",
			     mcu_id);
		if (0x1 & (rddata >> 3))
			pr_err("MCU[%d]: DDR_PHY_PARITY_ERR\n", mcu_id);
		if (0x1 & (rddata >> 2))
			pr_err("MCU[%d]: CORRECTABLE_ERR\n", mcu_id);
		if (0x1 & (rddata >> 1))
			pr_err("MCU[%d]: BACKGROUND_SCRUB_UNCORRECTABLE_ERR\n",
			       mcu_id);
		if (0x1 & (rddata >> 0))
			pr_err("MCU[%d]: DEMAND_OPERATION_UNCORRECTABLE_ERR\n",
			       mcu_id);
	}
	return err;
}				/* mcu_error_status() */

/*
 * Setup Memory for turning on ECC
 */
/* XXX: Need to clean this up */
int memc_ecc_init_en(void *ptr)
{
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, mcugecr[CONFIG_SYS_NUM_DDR_CTLRS],
		     scrubctl[CONFIG_SYS_NUM_DDR_CTLRS];
	unsigned int errcnt = 0;
	unsigned long long *addr_ptr;
	unsigned long long data2;

	debug("\n------- Start DDR ECCinit --------\n");
	debug("INFO: ECC initialization of ddr space starting...\n");
	memset((void *)&mcugecr, 0, sizeof(mcugecr));
	memset((void *)&scrubctl, 0, sizeof(scrubctl));

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!(mcu->enabled))
			continue;
		if (!mcu->mcu_params.ECCenable)	
			continue;

		/* Turn off ECC IRQ & counting */
		mcugecr[iia] = mcu->mcu_rd(mcu, MCU_REG_MCUGECR);
		if ((((mcugecr[iia] >> 7) & 0x1) == 1) ||
		    (((mcugecr[iia] >> 2) & 0x1) == 1) ||
		    (((mcugecr[iia]) & 0x1) == 1)) 
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
				    (mcugecr[iia] & 0xFFFFFF7AU));

		/* XXX: Disable Demand Scrub - ?? needed */
		scrubctl[iia] = mcu->mcu_rd(mcu, MCU_REG_SCRUB_CTL);
		if (((scrubctl[iia] >> 1) & 0x1) == 1) 
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
				    (scrubctl[iia] & 0xFFFFFFFDU));
	}

	/* Initialize ECC syndrom by partial write into each 64B location */
#if !defined(APM_SIM)
	printf(" ECC init ................");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
#endif
	data2 = 0;
	for (iia = 0; iia < memc->memspace.num_mem_regions; iia++) {
		addr_ptr = (unsigned long long *)(memc->memspace.str_addr[iia]);
		debug3("ECC-init region %d @ 0x%lx ...", iia,
		      (unsigned long long)addr_ptr);
		for (;addr_ptr <
		     ((unsigned long long *)(memc->memspace.end_addr[iia]));
		     						addr_ptr += 8) {
			/* Wr 8B of each 64B chunk for all memory */
			*addr_ptr = 0x0ULL;
#if defined(APM_SIM)
			if (((unsigned long long)addr_ptr % 0x10000000) == 0)
				debug(".");
#else
			if (!((unsigned long)addr_ptr & 0x7FFFFFF)) {
#if !defined(APM_SIM)
				printf("*");
#endif
				data2++;
			}
			if (data2 == 16) {
				data2 = 0;
#if !defined(APM_SIM)
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				printf("................");
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
#endif
			}
#endif
		}
		debug3("\n");
	}
#ifdef APM_VBIOS
	data_cache_flush_all();
#endif
#if !defined(APM_SIM)
	printf("                ");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	printf("\b\b\b\b\b");
#endif
	debug("INFO: ECC init delay before enable...memc_ecc_init_en()\n");
	DELAY(40000);
	/* Turn on Final ECC algo */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!(mcu->enabled))
			continue;
		if (!mcu->mcu_params.ECCenable)
			continue;
		if (mcu->mcu_ud.ud_zqcal_en) {
			debug1("\nPHY[%d] ZQ Calibration after ECCinit.....\n",
								mcu->id);
			errcnt = phy_sw_adj_ctrlupdate(mcu);
		} else {
			mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE,
					mcu->mcu_ud.ud_zqcal_code);
		}
		switch (mcu->mcu_ud.ud_ECCscheme) {
		case 0:	/* Disable all ECC */
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					mcugecr[iia] & 0xFFFFFF7AU);
			/* Disable Scrub */
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, 0);
			break;
		case 1:
			/* Enable correctable error intrrupt */
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR, 
					mcugecr[iia] | 0x10084);
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, 
					scrubctl[iia]);
			break;
		case 2:
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR, 
					mcugecr[iia] | 0x10084);	
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					scrubctl[iia] | 0x2);
			break;
		case 3:
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR, 
					mcugecr[iia] | 0x10085);	
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					scrubctl[iia] | 0x2);
			break;
		default: /* Leave configured value alone */
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR, mcugecr[iia]);
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, 
					scrubctl[iia]);
		}
	}
	DELAY(40000);
	debug("INFO: ECC init delay after enable...memc_ecc_init_en()\n");
	/* Spot check for ECC errors */
	for (iia = 0; iia < memc->memspace.num_mem_regions; iia++) {
		addr_ptr = (unsigned long long *)memc->memspace.str_addr[iia];
		for (;addr_ptr <
		     ((unsigned long long *)(memc->memspace.end_addr[iia] -
				2 * 8 * 0x40008)); addr_ptr += 0x40008) {
			data2 = *addr_ptr;
			if (data2 != 0x0) {
				debug("ERROR read after ecc init "
					"sa=0x%p (act=0x%llx vs exp=0)\n",
					addr_ptr, data2);
				errcnt++;
			}
		}
	}
#ifdef APM_VBIOS
	data_cache_flush_all();
#endif

#if !defined(APM_SIM) && !defined(APM_VBIOS)
	/* 
	 * SW Uboot: Short memtest on Uboot reallocate region 
	 * to catch ECC debug if init fail 
	 */
	addr_ptr =
		(unsigned long long *)(memc->memspace.end_addr[0] - 0x100000U + 1);
	for (;addr_ptr < 
		(unsigned long long *)(memc->memspace.end_addr[0] - 2 * 0x8); 
							addr_ptr += 0x1) {
		*addr_ptr = 0x0;
		data2 = *addr_ptr;
		if (data2 != 0x0)
			debug("\nERROR: ECC init failure!\n");
	}
#endif
	errcnt += mcu_error_status(ptr);

	if (errcnt)
		debug("INFO: ECC init ERRORS=%d \n", errcnt);
	return (errcnt);
}	/* memc_ecc_init_en */

/******************************************************************************
 *     Mcu_RESET SW Issue (SWISS) CSR operations
 *        Common tasks from Mcu_Reset FSM
 *****************************************************************************/

/*
 * mcu_set_SWISS_TRNLOAD
 * Pulse dfi_wrlvl_load dfi_rdlvl_load from Mcu to PHY
 * Tells phy its Delay CSRs are changed and ready to use
 */
void mcu_set_SWISS_TRNLOAD(void *p)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	/* Once is enought */
	unsigned int dat = 0x80000000 | mcu->phy_params.cfg_macro_en_val;

	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNWRLOAD, dat);
	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNRDLOAD, dat);
}

void mcu_set_SWISS_ODTADDR(void *ptr, int unsigned enab, int unsigned bnk,
		int unsigned addr, int unsigned odtRd, int unsigned odtWr)
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	data = ((enab & 0x1) << 31) | ((odtRd & 0x1) << 21) |
		((odtWr & 0x1) << 20) | ((bnk & 0x7) << 16) | (addr & 0xFFFF);
	/* 
	   MCU_SWISS_ODTADDR_ENABLE_RNG        31
	   MCU_SWISS_ODTADDR_ODTRD_RNG         21
	   MCU_SWISS_ODTADDR_ODTWR_RNG         20
	   MCU_SWISS_ODTADDR_BANK_RNG          18:16
	   MCU_SWISS_ODTADDR_ADDRESS_RNG       15:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_ODTADDR, data);
	debug2("MCU_REG_SWISS_ODTADDR set: "
			"en=%1d odtRd=%1d odtWr=%1d bnk=%01x a=0x%04x\n",
			enab, odtRd, odtWr, bnk, addr);
}

void mcu_set_SWISS_TRNCTL(void *ptr, int unsigned enab, int unsigned wrlvl_en, 
			int unsigned rdlvl_gate_en, int unsigned rdlvl_en, 
			int unsigned wrlvl_cs_n	, int unsigned rdlvl_cs_n)
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	data = ((enab & 0x1) << 31) | ((wrlvl_en & 0x1) << 18) |
		((rdlvl_gate_en & 0x1) << 17) | ((rdlvl_en & 0x1) << 16) |
		((wrlvl_cs_n & 0xFF) << 8) | (rdlvl_cs_n & 0xFF);
	/*
	   MCU_SWISS_TRNCTL_ENABLE_RNG         		31
	   MCU_SWISS_TRNCTL_DFI_WRLVL_EN_RNG           	18
	   MCU_SWISS_TRNCTL_DFI_RDLVL_GATE_EN_RNG       17
	   MCU_SWISS_TRNCTL_DFI_RDLVL_EN_RNG           	16
	   MCU_SWISS_TRNCTL_DFI_WRLVL_CS_N_RNG         	15:8
	   MCU_SWISS_TRNCTL_DFI_RDLVL_CS_N_RNG         	7:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNCTL, data);
	debug2("MCU_REG_SWISS_TRNCTL set: en=%1d wrlvl_en=%1d "
		"rdlvl_gate_en=%1d rdlvl_en=%1d wrlvl_cs_n=0x%02x "
		"rdlvl_cs_n=0x%02x\n",enab, wrlvl_en, rdlvl_gate_en, 
		rdlvl_en, wrlvl_cs_n, rdlvl_cs_n);
}

void mcu_set_SWISS_OPCTL(void *ptr, int unsigned sendOp, int unsigned rddata_en,
			 int unsigned cmd_n, int unsigned cs_n)	
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	data = ((sendOp & 0x1) << 31) | ((rddata_en & 0x1) << 12) | 
		((cmd_n & 0x7) << 8) |	(cs_n & 0xFF);
	/*
	   MCU_SWISS_OPCTL_SENDOP_RNG          		31
	   MCU_SWISS_OPCTL_DFI_INIT_RDDATA_EN_RNG       12
	   MCU_SWISS_OPCTL_DFI_INIT_CMD_N_RNG           10:8
	   MCU_SWISS_OPCTL_DFI_INIT_CS_N_RNG            7:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_OPCTL, data);
	debug2("MCU_REG_SWISS_OPCTL set: sndOp=%1d rddata_en=%1d "
		"cmd_n=%1d cs_n=0x%02x\n",
	     	sendOp, rddata_en, cmd_n, cs_n);
}

unsigned int mr_addmirror_add(unsigned int in)
{
	unsigned int out = 0;

	out |= in & 0x7;
	out |= (in & 0x100) >> 1;	//8 -> 7
	out |= (in & 0x800) << 1;	//7 -> 8
	out |= (in & 0x40) >> 1;	//6 -> 5
	out |= (in & 0x20) << 1;	//5 -> 6
	out |= (in & 0x10) >> 1;	//4 -> 3
	out |= (in & 0x8) << 1;		//3 -> 4
	out |= in & 0xFE00;
	return (out);
}		

unsigned int mr_addmirror_bnk(unsigned int in)
{
	unsigned int out = 0;

	out |= in & 0xC;
	out |= (in & 0x2) >> 1;		//1 -> 0
	out |= (in & 0x1) << 1;		//0 -> 1
	return (out);
}

void mcu_rank_mr_update(void *ptr, unsigned int rank, unsigned int mr,
						unsigned int value)
{
	int unsigned csn = 0xFF;
	int unsigned dat, bnk;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	bnk = mr;
	dat = value;
	if (mcu->mcu_params.mirror_ctrl & (0x1 << rank)) {
		bnk = mr_addmirror_bnk(mr);
		dat = mr_addmirror_add(value);
		debug("\tMirrored Rank\n");
	} else {
		debug("\tNon-Mirrored Rank\n");
	}
	mcu_set_SWISS_ODTADDR(mcu, 1, bnk, dat, 0, 0);
	DELAY(1);

	if (((mcu->mcu_params.activeslots == 1) && 
		(mcu->mcu_params.activeranks == 0xF)) || 
	   ((mcu->mcu_params.activeslots == 3) && 
		(mcu->mcu_params.activeranks == 0xFF)))	
		/* 4R1S/4R2S */
		switch (rank) {
		case 0:
			csn = 0xFE;
			break;
		case 1:
			csn = 0xFD;
			break;
		case 2:
			csn = 0xEF;
			break;
		case 3:
			csn = 0xDF;
			break;
		case 4:
			csn = 0xFB;
			break;
		case 5:
			csn = 0xF7;
			break;
		case 6:
			csn = 0xB7;
			break;
		case 7:
			csn = 0x7F;
			break;
		default:
			csn = 0xFF;
	} else {		
		/*  2R2S */
		csn &= ~(0x1 << rank);
	}
	mcu_set_SWISS_OPCTL(mcu, 1, 0, 6, csn);
	DELAY(1);
	debug("\tRank[%d] MR:%d [bnk:%d], Value:0x%04x [data:0x%04x] "
		"CSn:0x%2x\n", rank, mr, bnk, value, dat, csn);
}	/* mcu_rank_mr_update */

