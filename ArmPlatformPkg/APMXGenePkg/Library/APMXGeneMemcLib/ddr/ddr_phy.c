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

#include "ddr_mcu.h"
#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

int phy_correct_wrdq_delays(void *ptr);
int phy_fix_wrdq_delays(void *ptr);
void phy_save_wrdq_dly_csrs(void *p);

void unrecovered_reset(struct apm_mcu *mcu)
{
	struct apm_memc *memc = mcu->parent;
	if (memc->mc_ud.ud_reset_on_err) {
		printf("Detected Unrecovered Error! Try resetting...\n");
		DELAY(50000);
		disable_interrupts();
		reset_cpu(0);
	} else {
		printf("\n*** FATAL-ERROR: (PHY leveling error) "
							"Need Reset ****\n");
	}
}

/*******************************************************************************
 *			PHY Training delay CSRs access
 ******************************************************************************/
/*
 * PHY Training delay CSRs restore 
 */
void phy_restore_train_dly_csrs(void *p, int unsigned rankmask,
				int unsigned setWr,
				int unsigned setGt, int unsigned setRd)
{
	int iia, jjb;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	int unsigned by4 = mcu->mcu_params.by4_mode;

	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!((rankmask >> iia) & 0x1)) 
			continue;
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
			if (setWr) {
				phy_write_reg(mcu,
					(PHY_CFG_REG_WRLVL_DELAY0_0 
					+ iia * PHY_REG_INCR_4_RANK_OFFSET
					+ jjb * PHY_REG_INCR_4_MACRO_OFFSET),
					mcu->phy_tr_dly.rank_dly[iia].
						wr_lvl[jjb * 2]);
				if (by4)
					phy_write_reg(mcu,
						(PHY_CFG_REG_WRLVL_DELAY0_0_1
						+ iia * PHY_REG_INCR_4_RANK_OFFSET
						+ jjb * PHY_REG_INCR_4_MACRO_OFFSET),
						mcu->phy_tr_dly.rank_dly[iia].
							wr_lvl[jjb * 2 + 1]);
			}
			if (setGt) {
				phy_write_reg(mcu,
					(PHY_CFG_REG_RDLVL_GATE_DELAY0_0
					 + iia * PHY_REG_INCR_4_RANK_OFFSET
					 + jjb * PHY_REG_INCR_4_MACRO_OFFSET),
					mcu->phy_tr_dly.rank_dly[iia].
						gt_lvl[jjb * 2]);
				if (by4)
					phy_write_reg(mcu,
						(PHY_CFG_REG_RDLVL_GATE_DELAY0_0_1
						 + iia * PHY_REG_INCR_4_RANK_OFFSET
						 + jjb * PHY_REG_INCR_4_MACRO_OFFSET),
						mcu->phy_tr_dly.rank_dly[iia].
							gt_lvl[jjb * 2 + 1]);
			}
			if (setRd) {
				phy_write_reg(mcu,
					(PHY_CFG_REG_RDLVL_DELAY0_0
					 + iia * PHY_REG_INCR_4_RANK_OFFSET
					 + jjb * PHY_REG_INCR_4_MACRO_OFFSET),
					mcu->phy_tr_dly.rank_dly[iia].
						rd_lvl[jjb * 2]);
				if (by4)
					phy_write_reg(mcu,
						(PHY_CFG_REG_RDLVL_DELAY0_0_1
						 + iia * PHY_REG_INCR_4_RANK_OFFSET
						 + jjb * PHY_REG_INCR_4_MACRO_OFFSET),
						mcu->phy_tr_dly.rank_dly[iia].
							rd_lvl[jjb * 2 + 1]);
			}
		}
	}

	/*
	 * Must reset statemachine to take in new changes
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_TRNLOAD(mcu);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
}			

/*
 * PHY Training delay CSRs store 
 */
void phy_save_train_dly_csrs(void *p)
{
	int iia, jjb;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	int unsigned by4 = mcu->mcu_params.by4_mode;

	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!(mcu->phy_tr_dly.rank_mask >> iia) & 0x1) 
			continue;
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
			/* Save PHY WR-LVL training delay */
			mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2] =
				phy_read_reg(mcu,
					(PHY_CFG_REG_WRLVL_DELAY0_0 +
					 iia * PHY_REG_INCR_4_RANK_OFFSET +
					 jjb * PHY_REG_INCR_4_MACRO_OFFSET));
			if (by4)
				mcu->phy_tr_dly.
					rank_dly[iia].wr_lvl[jjb * 2 + 1] =
					phy_read_reg(mcu,
						(PHY_CFG_REG_WRLVL_DELAY0_0_1 +
						 iia * PHY_REG_INCR_4_RANK_OFFSET +
						 jjb * PHY_REG_INCR_4_MACRO_OFFSET));

			/* Save PHY GT-LVL training delay */
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2] =
				phy_read_reg(mcu,
					(PHY_CFG_REG_RDLVL_GATE_DELAY0_0 +
					 iia * PHY_REG_INCR_4_RANK_OFFSET +
					 jjb * PHY_REG_INCR_4_MACRO_OFFSET));
			if (by4)
				mcu->phy_tr_dly.
					rank_dly[iia].gt_lvl[jjb * 2 + 1] =
					phy_read_reg(mcu,
						(PHY_CFG_REG_RDLVL_GATE_DELAY0_0_1
						 + iia * PHY_REG_INCR_4_RANK_OFFSET
						 + jjb * PHY_REG_INCR_4_MACRO_OFFSET));

			/* Save PHY RD-LVL training delay */
			mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2] =
				phy_read_reg(mcu,
					(PHY_CFG_REG_RDLVL_DELAY0_0 +
					 iia * PHY_REG_INCR_4_RANK_OFFSET +
					 jjb * PHY_REG_INCR_4_MACRO_OFFSET));
			if (by4)
				mcu->phy_tr_dly.
					rank_dly[iia].rd_lvl[jjb * 2 + 1] =
					phy_read_reg(mcu,
						(PHY_CFG_REG_RDLVL_DELAY0_0_1
						 + iia * PHY_REG_INCR_4_RANK_OFFSET
						 + jjb * PHY_REG_INCR_4_MACRO_OFFSET));
		}
	}
}		

/*
 * Print out PHY Training delay CSRs 
 */
void phy_display_post_train_csrs(void *p, unsigned int rankmask)
{
	int iia, jjb, kkc;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	int unsigned __attribute__ ((unused)) cfg_analog2, cfg_analog3, picode,
					cdrlock, commandcode, rttnom, dic,
					rttwr, trnerr, terrmacro;
	int unsigned __attribute__ ((unused)) zqcode, cfg_dly_from_rden;

	cfg_analog2 = mcu->phy_rd(mcu, PHY_REG_CFG_ANALOG_CONFIG_2);
	cfg_analog3 = mcu->phy_rd(mcu, PHY_REG_CFG_ANALOG_CONFIG_3);
	picode = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE);
	cdrlock = mcu->phy_rd(mcu, PHY_REG_CFG_CDR_LOCK);
	commandcode = mcu->phy_rd(mcu, PHY_REG_CFG_CMD_CODE);
	zqcode = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);

	cfg_dly_from_rden = phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);

	trnerr = mcu->phy_rd(mcu, KC_PHY_REG36);
	terrmacro = mcu->phy_rd(mcu, KC_PHY_REG49);

	/* WR-LVL */
	debug1("\n\nWrLvl \t");
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if ((rankmask >> iia) & 0x1) 
			debug1("\tR%01d", iia);
	}
	debug1("\n");
	for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
			continue;
		if ((jjb % 2) == 0)
			debug1("Ln %2d   ", jjb / 2);
		else
			debug1("Ln %2d x4", jjb / 2);
		for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
			if ((rankmask >> iia) & 0x1) 
				debug1("\t0x%03X",
					mcu->phy_tr_dly.
					rank_dly[iia].wr_lvl[jjb]);
		}
		if (jjb > 15) 
			debug1(" ecc");
		debug1("\n");
	}
	debug1("\n");

	/* GT-LVL */
	debug1("GtLvl \t");
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if ((rankmask >> iia) & 0x1) 
			debug1("\tR%01d", iia);
	}
	debug1("\n");
	for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
			continue;
		if ((jjb % 2) == 0)
			debug1("Ln %2d   ", jjb / 2);
		else
			debug1("Ln %2d x4", jjb / 2);
		for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
			if ((rankmask >> iia) & 0x1) 
				debug1("\t0x%03X",
					mcu->phy_tr_dly.
					rank_dly[iia].gt_lvl[jjb]);
		}
		if (jjb > 15) 
			debug1(" ecc");
		debug1("\n");
	}
	debug1("\n");

	/* RD-LVL */
	debug1("RdLvl \t");
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if ((rankmask >> iia) & 0x1) 
			debug1("\tR%01d", iia);
	}
	debug1("\n");
	for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
			continue;
		if ((jjb % 2) == 0)
			debug1("Ln %2d   ", jjb / 2);
		else
			debug1("Ln %2d x4", jjb / 2);
		for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
			if ((rankmask >> iia) & 0x1) 
				debug1("\t0x%03X",
					mcu->phy_tr_dly.
					rank_dly[iia].rd_lvl[jjb]);
		}
		if (jjb > 15) 
			debug1(" ecc");
		debug1("\n");
	}
	debug1("\n");

	/* RD-DESKEW-TRIM */
	debug1("RdDsk-Trim ");
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!((mcu->phy_tr_dly.rddeskew_rank_mask >> iia) & 0x1))
			continue;
		debug1("\tRankMask 0x%02X", iia);
		debug1("\n");
		debug1("\t\tBit\t0 1 2 3 4 5 6 7 \n");
		debug1("   \t\t\t| | | | | | | | \n");
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
			if (!((mcu->phy_params.
				cfg_macro_en_val >> jjb * 2) & 0x1))
				continue;
			debug1("Ln %2d   ", jjb);
			debug1("\t\t");
			for (kkc = 0; kkc < 8; kkc++)
				debug1("%d ", ((mcu->phy_tr_dly.
					rd_dsk[jjb]) >> (kkc * 3)) & 0x7);
			if (jjb > 15) 
				debug1(" ecc");
			debug1("\n");
		}
		/* Supported for only one rank */
		break;	
	}
	if (iia >= MCU_SUPPORTED_RANKS) 
		debug1("\tRankMask:0x%02X - [RD-DESKEW-DISABLED]",
		       mcu->phy_tr_dly.rddeskew_rank_mask);
	debug1("\n\n");

	/* WR-DESKEW-TRIM */
	debug1("WrDsk-Trim ");
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!((mcu->phy_tr_dly.wrdeskew_rank_mask >> iia) & 0x1)) 
			continue;
		debug1("\tRankMask 0x%02X", iia);
		debug1("\n");
		debug1("\tWRDQ-DQS    Bit\t0 1 2 3 4 5 6 7 \n");
		debug1("\t    |          \t| | | | | | | | \n");
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
			if (!((mcu->phy_params.
				cfg_macro_en_val >> jjb * 2) & 0x1))
				continue;
			debug1("Ln %2d  ", jjb);
			debug1("    0x%02X     \t",
					mcu->phy_tr_dly.wrdq_dly[jjb * 2]);
			for (kkc = 0; kkc < 8; kkc++)
				debug1("%d ", ((mcu->phy_tr_dly.
					wr_dsk[jjb]) >> (kkc * 3)) & 0x7);
			if (jjb == 8) 
				debug1(" ecc");
			debug1("\n");
		}
		/* Supported for only one rank */
		break;
	}

	if (mcu->mcu_ud.fix_wrdq_flg) {
		phy_save_wrdq_dly_csrs(p);
		debug1("\nMCU[%d]: Fixed WRDQ-DQS \n", mcu->id);
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
			if (!((mcu->phy_params.
                                cfg_macro_en_val >> jjb) & 0x1))
				continue;
			if ((jjb % 2) == 0)
				debug1("Ln %2d   ", jjb / 2);
			else
				debug1("Ln %2d x4", jjb / 2);

			debug1("\t0x%02X",
				       mcu->phy_tr_dly.wrdq_dly[jjb]);
			if ((jjb/2) == 8)
				debug1(" ecc");
			debug1("\n");
		}
	}

	if (iia >= MCU_SUPPORTED_RANKS) 
		debug1("\t\tRankMask: 0x%02X - [WR-DESKEW-DISABLED]",
		       mcu->phy_tr_dly.wrdeskew_rank_mask);
	debug1("\n");
	
	if (trnerr || terrmacro)
		debug("Phy Train Error Reg=0x%08x  Macro=0x%08x\n\n",
			trnerr, terrmacro);

	debug("DQ/DQS DriveStrength = %d  Slew = %d\n",
		((cfg_analog2 >> 5) & 0x7), ((cfg_analog2 >> 8) & 0x3));
	debug("ADDR   DriveStrength = %d  Slew = %d\n",
		((cfg_analog2 >> 13) & 0x7), ((cfg_analog2 >> 16) & 0x3));
	debug("CMD    DriveStrength = %d  Slew = %d\n",
		((cfg_analog2 >> 18) & 0x7), ((cfg_analog3 >> 0) & 0x3));
	debug("CLOCK  DriveStrength = %d  Slew = %d\n",
		((cfg_analog3 >> 7) & 0x7), ((cfg_analog3 >> 10) & 0x3));
	debug("CTL    DriveStrength = %d  Slew = %d\n",
		((cfg_analog3 >> 2) & 0x7), ((cfg_analog3 >> 5) & 0x3));
	debug("ODT    RcvrStrength  = %d  \n", ((cfg_analog3 >> 12) & 0x7));

	rttnom = ((mcu->mcu_params.mode_reg[1] >> 7) & 0x4) |
		((mcu->mcu_params.mode_reg[1] >> 5) & 0x2) |
		((mcu->mcu_params.mode_reg[1] >> 2) & 0x1);
	dic = ((mcu->mcu_params.mode_reg[1] >> 4) & 0x2) |
		((mcu->mcu_params.mode_reg[1] >> 1) & 0x1);
	rttwr = (mcu->mcu_params.mode_reg[2] >> 9) & 0x3;
	debug1("Dimm RttNom = 0x%x  DIC = 0x%x\n", rttnom, dic);
	debug1("Dimm RttWr  = 0x%x  \n", rttwr);
	debug1("PHY  ZQ Code {neg , pos} = {0x%02X , 0x%02X}\n",
			((zqcode >> 6) & 0x3F), (zqcode & 0x3F));
#if 0
	debug("     PI Code = 0x%X \n", picode);
	debug("    CDR Lock = 0x%X \n", cdrlock);
	debug("COMMAND Code = 0x%X (PI+180) \n", commandcode);
	debug
	    ("Dly from Rd En = R0 \tR1 \tR2 \tR3 \tR4 \tR5 \tR6 \tR7\n");
	for (iia = 0; iia < 8; iia++) 
	        debug("0x%02X\t", ((cfg_dly_from_rden >> (iia * 3)) & 0x7));
#endif
	debug("\n");
}

/*
 * PHY RD-DESKEW delay CSRs store 
 */
void phy_save_rddsk_dly_csrs(void *p)
{
	int jjb, rddata;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		rddata = phy_read_reg(mcu,
				PHY_CFG_RDLVL_TRIM_N +
				jjb * PHY_REG_INCR_4_MACRO_OFFSET);
		mcu->phy_tr_dly.rd_dsk[jjb] = rddata;
	}
}		

/*
 * PHY WR-DESKEW delay CSRs store 
 */
void phy_save_wrdsk_dly_csrs(void *p)
{
	int jjb, rddata;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		rddata = phy_read_reg(mcu,
				PHY_CFG_WRLVL_TRIM_N +
				jjb * PHY_REG_INCR_4_MACRO_OFFSET);
		mcu->phy_tr_dly.wr_dsk[jjb] = rddata;
	}
}	

/*
 * Clear PHY WR-DESKEW Trim 
 */
void phy_clear_wrdsk_trim(void *p)
{
	int jjb, rddata, addr;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		addr = PHY_CFG_WRLVL_TRIM_N + 
			jjb * PHY_REG_INCR_4_MACRO_OFFSET;
		rddata = phy_read_reg(mcu, addr);
		phy_write_reg(mcu, addr, 0x0);	
		debug("Clearing PHY[%d]-WRDESKEW-TRIM-MACRO[%d] @0x%x:0x%x\n",
				mcu->id, jjb, addr, rddata);
	}
	debug1("Cleared PHY-WR-TRIM for all macros\n");
}

/*
 * Clear PHY RD-DESKEW Trim 
 */
void phy_clear_rddsk_trim(void *p)
{
	int jjb, rddata, addr;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		addr = PHY_CFG_RDLVL_TRIM_N + 
			jjb * PHY_REG_INCR_4_MACRO_OFFSET;
		rddata = phy_read_reg(mcu, addr);
		phy_write_reg(mcu, addr, 0x0);
		debug("Clearing PHY[%d]-RDDESKEW-TRIM-MACRO[%d] @0x%x:0x%x\n",
				mcu->id, jjb, addr, rddata);
	}
	debug1("Cleared PHY-RD-TRIM for all macros\n");
}		

/*
 * PHY WRDQ delay CSRs store 
 */
void phy_save_wrdq_dly_csrs(void *p)
{
	int jjb, rddata;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		rddata = phy_read_reg(mcu,
			(PHY_CFG_WRDQ_DEL_N_0 +
			 jjb * PHY_REG_INCR_4_MACRO_OFFSET));
		mcu->phy_tr_dly.wrdq_dly[jjb * 2] = rddata & 0xFFF;
		mcu->phy_tr_dly.wrdq_dly[jjb * 2 + 1] =
			((rddata >> 12) & 0xFFF);
	}
}	

/*
 * Initialize PHY Training delay values 
 */
void init_phy_tr_dly_vals(void *p)
{
	int iia, jjb;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
			mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2] =
				PHY_CFG_REG_WRLVL_DELAY;
			mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2 + 1] =
				PHY_CFG_REG_WRLVL_DELAY;
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2] =
				PHY_CFG_REG_RDLVL_GATE_DELAY;
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2 + 1] =
				PHY_CFG_REG_RDLVL_GATE_DELAY;
			mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2] =
				PHY_CFG_REG_RDLVL_DELAY;
			mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2 + 1] =
				PHY_CFG_REG_RDLVL_DELAY;
		}
	}
	/* Init to Phy CSR reset value */
	for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
		mcu->phy_tr_dly.wrdq_dly[jjb * 2] = 0x40;
		mcu->phy_tr_dly.wrdq_dly[jjb * 2 + 1] = 0x40;
	}

	return;
}

/*******************************************************************************
 *			Utility functions
 ******************************************************************************/

/*
 * Clear MCU & PHY read datapath 
 */
void mcu_phy_rdfifo_reset(void *ptr)
{
	int unsigned dat;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	dat = mcu->mcu_rd(mcu, MCU_REG_RDLVLCTL);
	dat |= 0x100U;
	/* Toggle Rd FIFO reset 
	    MCU_RDLVLCTL_SAMPLE_DELAY_RNG       21:16
	    MCU_RDLVLCTL_RDFIFO_RESET_RNG       8
	    MCU_RDLVLCTL_RDLVL_EN_RNG           3 << only this asserted
	    MCU_RDLVLCTL_RDLVLALLDONE_RNG       2
	    MCU_RDLVLCTL_DORDLVL_RNG            1
	    MCU_RDLVLCTL_RDLVLENDRANK_RNG       0
	 */
	mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, dat);
	dat &= (~0x100U);
	mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, dat);
}

/*
 * Detect PHY training errors 
 *	   bit[0] = error
 *	   bit[1] = timeout error
 *	   bit[2] = IRQ for PHY error
 *	   bit[3] = Phy error
 */
int mcu_check_phy_trainerr(void *ptr, int unsigned expphyerr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned rddata;
	int unsigned iia;
	int bout = 0;

	/* 
	 * Mcu_Reset FSM timeout error 
	 * (Phy did no converge and send back done for a training step) 
	 */
	rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
	if ((expphyerr & 0x1) !=
	    ((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1)) {
		debug("PHY[%d] ERROR Mcu PEVM (Phy) TimeoutErr not match:"
			" act(%01d) vs exp(%01d)\n", mcu->id,
			((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1),
			(expphyerr & 0x1));
		debug("PHY[%d] INFO MCU PEVM (Phy) WrLvl,GtLvl,RdLvl ="
			" {%01X} steps done.\n", mcu->id,
			((rddata >> MCU_DDR_INIT_STATUS_RDLVLDONE_RNG) & 0x7));
		bout |= 0x3;
	} else {
		debug("PHY[%d] INFO MCU PEVM (Phy) TimeoutErr matches:"
			" act(%01d) vs exp(%01d)\n", mcu->id,
			 ((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1),
			 (expphyerr & 0x1));
	}

	/* Check MCU_REG_MCUGESR for IRQ */ 
	rddata = mcu->mcu_rd(mcu, MCU_REG_MCUGESR);
	if ((expphyerr & 0x1) !=
		((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1)) {
		debug("PHY[%d]  ERROR  MCUGESR IRQ: PhyTrainingErr not match:"
			" act(%01d) vs exp(%01d)\n", mcu->id,
			 ((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1),
			 (expphyerr & 0x1));
		bout |= 0x5;
	} else {
		debug("PHY[%d] INFO MCUGESR IRQ: PhyTrainingErr match:"
			" act(%01d) vs exp(%01d)\n", mcu->id,
			((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1),
			(expphyerr & 0x1));
	}

	/* Read PHY error CSRs */
	rddata = phy_read_reg(mcu, KC_PHY_REG36);
	if (!(expphyerr & 0x1)) {
		if (rddata & 0x1F) {
			debug("PHY[%d] ERROR Phy unexpected training_error :"
				"{WrLvl,WrCal,GtLvl,RdLvl,TrainErr}={%02X}\n",
				 mcu->id, (rddata & 0x1F));
			bout |= 0x9;
		} else {
			debug("PHY[%d] INFO  Phy no training_error.\n",
				 mcu->id);
		}
	}

	/* Read per lane error info */
	rddata = phy_read_reg(mcu, KC_PHY_REG49);
	debug("PHY[%d] PHYCSR CFG_MACRO_TR_ERROR lane [", mcu->id);
	for (iia = 0; iia < 9; iia++) 
		debug("(%01d  e=%01d)", iia, ((rddata >> (iia * 2)) & 0x1));

	if (mcu->mcu_params.by4_mode) {
		debug("] x4 nibble 0\n");
		debug("PHY[%d] PHYCSR CFG_MACRO_TR_ERROR lane [", mcu->id);
		for (iia = 0; iia < 9; iia++) 
			debug(" (%01d  e=%01d) ", iia,
				((rddata >> ((iia * 2) + 1)) & 0x1));
		debug("] x4 nibble 1\n");
	} else {
		debug("] x8\n");
	}

	return bout;
}

int kc_phy_wrcal(void *ptr, int unsigned rank, int unsigned checktrainerr)
{
	int err0 = 0;
	int unsigned cs_n;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	cs_n = (~(1U << rank)) & 0xFF;

	mcu_phy_rdfifo_reset(ptr);
	/* Turn on  dfi_rdlvl_cs_n */
	mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, cs_n);
#ifdef PEVM2DPC_MCU_OTD_DRIVE
	if (mcu->mcu_params.activeslots == 0x3) {
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 1, 0);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0000, 1, 0);
	} else {
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);
	}
#else
	mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);
#endif
	/* WR-CAL */
	if ((mcu->phy_tr_dly.phy_wrcal_rank_mask >> rank) & 0x1) {
		debug("PHY[%d] ::Starting WrCal  rank=%01d\n", mcu->id, rank);
		phy_rf_write_cfg_wrcal_en(ptr, 0x1);	
		/* 500ns */
		err0 += phy_poll_reg(ptr, 0x18U, 0x1U, 0x1U);

		/* Clear RD-ODT */
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 0, 0);
		mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0, 0, 0);

		if (checktrainerr)
			err0 += mcu_check_phy_trainerr(ptr, 0);

		phy_rf_write_cfg_wrcal_en(ptr, 0x0);
		debug("MCU%d: eval_mode_wrcal::Finished WrCal rank=%01d\n",
			mcu->id, rank);
	}
	/* Turn off dfi_rdlvl_cs_n */
	mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, 0xFF);
	mcu_set_SWISS_TRNCTL(ptr, 0, 0, 0, 0, 0xFF, 0xFF);

	mcu_phy_rdfifo_reset(ptr);
	return err0;
} /* kc_phy_wrcal */

int kc_phy_deskew_per_rank(void *ptr, int unsigned rank, 
				int unsigned checktrainerr)
{
	int slice, olddelay;
	int err0 = 0;
	int unsigned cs_n;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	cs_n = (~(1U << rank)) & 0xFF;

	mcu_phy_rdfifo_reset(ptr);
	/* Turn on  dfi_rdlvl_cs_n */
	mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, cs_n);

#ifdef PEVM2DPC_MCU_OTD_DRIVE
	if (mcu->mcu_params.activeslots == 0x3) {
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 1, 0);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0000, 1, 0);
	} else {
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);
	}
#else
	mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);
#endif
	/* Deskew */
	if ((mcu->phy_tr_dly.rddeskew_rank_mask >> rank) & 0x1) {
		debug("MCU%d: eval_mode_wrcal: Starting Rd Deskew rank=%01d\n",
			mcu->id, rank);

#ifdef FIX_DEFAULT_RDE_BFRDSK
		/* Set default/start value as 0x20 and then backoff by 0x10 */
		if ((mcu->phy_tr_dly.rddeskew_rank_mask >> rank) & 0x1) {
			/* RD-DESKEW supported only for Rank-0 */
			if (rank == 0) {
				debug("\n\nMCU[%d]: Fixing default RDE Leveling"
					" values for all macros"
					" (Before PEVM-RD-DESKEW)\n", mcu->id);
				for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
				     slice++) {
					if (!((mcu->phy_params
					    .cfg_macro_en_val >> slice) & 0x1))
						continue;
					mcu->phy_tr_dly.
					    rank_dly[rank].rd_lvl[slice] =
					    DEFAULT_RDEYE_VALUE;
				}
				debug("Restoring the FIX delays...\n");
				phy_restore_train_dly_csrs(mcu, (0x1U << rank),
							   0, 0, 1);
			}
		}
#endif
		/* deskew rd */
		phy_rf_write_cfg_rd_deskew_en(ptr, 0x1);
		DELAY(50);
		/* 5000ns */
		err0 += phy_poll_reg(ptr, 0x24, 0x1, 0x1);
		if (checktrainerr)
			err0 += mcu_check_phy_trainerr(ptr, 0);
		phy_rf_write_cfg_rd_deskew_en(ptr, 0x0);
		debug("PHY[%d]: Finished Rd Deskew rank=%01d\n", mcu->id, rank);
		phy_save_train_dly_csrs(ptr);
#ifdef FIX_DEFAULT_RDE
		/* 
		 * AUTOFIX: Back-Off RDE based on default value 
		 * [new-lvl -= (default-reg-value)/2]
		 */
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
				continue;
			olddelay = mcu->phy_tr_dly.rank_dly[rank].rd_lvl[slice];
			if (olddelay > (DEFAULT_RDEYE_VALUE / 2)) {
				mcu->phy_tr_dly.rank_dly[rank].rd_lvl[slice] -=
					(DEFAULT_RDEYE_VALUE / 2);
				debug("\t\tCorrecting RDE-LVL RANK[%d]-Macro[%d]"
					": 0x%x [old:0x%x] after DESKEW\n",
					rank, slice, mcu->phy_tr_dly.
					rank_dly[rank].rd_lvl[slice], olddelay);
			}

		}
		debug("Restoring the Auto Fixed delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << rank), 0, 0, 1);
		mcu_phy_rdfifo_reset(ptr);

#endif
	}
	/* Check/Fix broken RDE based on FIX_BROKEN_RDEYE_PERMACRO */
	if (is_storm_revA())
		err0 += phy_correct_rdeye_delays(ptr, rank);

	if ((mcu->phy_tr_dly.wrdeskew_rank_mask >> rank) & 0x1) {
		debug("PHY[%d] ::Start Wr Deskew  rank=%01d\n", mcu->id, rank);
		/* wr deskew */
		phy_rf_write_cfg_wr_deskew_en(ptr, 0x1);
		/* 20000n */
		err0 += phy_poll_reg(ptr, 0x24, 0x2, 0x2);
		if (checktrainerr)
			err0 += mcu_check_phy_trainerr(ptr, 0);
		phy_rf_write_cfg_wr_deskew_en(ptr, 0x0);
		debug("PHY[%d]: Finished Wr Deskew rank=%01d\n",
			mcu->id, rank);
		/* Check/Fix broken WR-DQ-DQS based on FIX_BROKEN_WRDQ_PERMACRO */
		err0 += phy_correct_wrdq_delays(mcu);
	}
	/* Clear RD-ODT */
	mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 0, 0);
	mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0, 0, 0);

	/* Turn off dfi_rdlvl_cs_n */
	mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, 0xFF);
	mcu_set_SWISS_TRNCTL(ptr, 0, 0, 0, 0, 0xFF, 0xFF);

	mcu_phy_rdfifo_reset(ptr);
	return err0;
}	/* kc_phy_deskew_per_rank */

int kc_phy_deskew(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int iia;
	unsigned int err = 0, err_deskew = 0;
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!((mcu->phy_tr_dly.rank_mask >> iia) & 0x1)) 
			continue;

		if (((mcu->phy_tr_dly.rddeskew_rank_mask >> iia) & 0x1)
			|| ((mcu->phy_tr_dly.wrdeskew_rank_mask >> iia) & 0x1)){
#ifdef DUMMY_BIST_FOR_2S_LVL_BEFORE_DESKEW
			/* Doing DummyBIST on non-populated ranks */
			if (mcu->mcu_params.activeslots == 0x3) {
				mcu_dummy_bist_2s_calib(mcu, iia + 4, 1);
				mcu_phy_rdfifo_reset(mcu);
				mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 1, 0);
			}
#endif
			debug1("\n- - - - - - - - - - - - - - - - - - - - - -\n");
			debug1("MCU[%d] Starting Deskew - Rank-CS[%d]...\n",
				 mcu->id, iia);
			debug("NON-DFI-TRAINING: "
				"rddeskew[0x%02X], wrdeskew [0x%02X] (rank:%d)\n",
				 mcu->phy_tr_dly.rddeskew_rank_mask,
				 mcu->phy_tr_dly.wrdeskew_rank_mask, iia);
			err = kc_phy_deskew_per_rank(ptr, iia, 1);

			/* Clear RD-ODT */
			mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 0, 0);
			mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0, 0, 0);

		}
		if (err)
			err_deskew |= (0x1 << iia);
		phy_save_train_dly_csrs(mcu);
		mcu_phy_rdfifo_reset(mcu);
	}
	return err_deskew;

}

/*
 * phy_correct_rdeye_delays
 * If RD-lvl (EYE) values are less then 0x20, fix it to 0x40
 */
int phy_correct_rdeye_delays(void *ptr, unsigned int rank)
{
	unsigned int n, err;
	unsigned int readData, offset, wdata = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	if (!mcu->enabled) 
		return 1;

	err = 0;
	/* This value might change based on DIMM/SPEED/LOAD/RD-DESKEW */
	if (mcu->mcu_params.activeslots == 0x3)
		wdata = FIX_BROKEN_RDEYE_VALUE_2S;
	else
		wdata = FIX_BROKEN_RDEYE_VALUE_1S;
	for (n = 0; n < 9; n++) {
		/* byte/x4[0] of the macro */
		offset = PHY_CFG_REG_RDLVL_DELAY0_0 +
			(unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET) +
					(rank * PHY_REG_INCR_4_RANK_OFFSET));
		/* Check if macro enabled */
		if (!((mcu->phy_params.cfg_macro_en_val >> (n * 2)) & 0x1))
			continue;
		readData = phy_read_reg(mcu, offset) & 0xFFF;
		if (readData < CMP_BROKEN_RDEYE_VALUE_LO) {
#ifdef FIX_BROKEN_RDEYE_PERMACRO
			phy_write_reg(mcu, offset, wdata);
			debug("PHY[%d]: FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);

#else
			debug("PHY[%d]: Need FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
			err++;
#endif
		} else if (readData > CMP_BROKEN_RDEYE_VALUE_HI) {
#ifdef FIX_BROKEN_RDEYE_PERMACRO
			phy_write_reg(mcu, offset, wdata);
			debug("PHY[%d]: FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
#else
			debug("PHY[%d]: Need FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
			err++;
#endif
		}
		/* x4[1] of same macro */
		offset += 4;
		if (!((mcu->phy_params.cfg_macro_en_val >> ((n * 2) + 1)) & 0x1))
			continue;
		readData = phy_read_reg(mcu, offset) & 0xFFF;
		if (readData < CMP_BROKEN_RDEYE_VALUE_LO) {
#ifdef FIX_BROKEN_RDEYE_PERMACRO
			phy_write_reg(mcu, offset, wdata);
			debug("PHY[%d]: FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
#else
			debug("PHY[%d]: Need FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
			err++;
#endif
		} else if (readData > CMP_BROKEN_RDEYE_VALUE_HI) {
#ifdef FIX_BROKEN_RDEYE_PERMACRO
			phy_write_reg(mcu, offset, wdata);
			debug("PHY[%d]: FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
#else
			debug("PHY[%d]: Need FIX_BROKEN_RDEYE macro:%d "
                                "[PEVM-RDlvl-read: 0x%03X]\n",
                                mcu->id, n * 2, readData);
			err++;
#endif
		}
	}
	/*
	 * Must reset statemachine to take in new changes
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_TRNLOAD(mcu);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	return err;
}

int phy_fix_wrdq_delays(void *ptr)
{
	unsigned int n;
	unsigned int readData, offset, wdata = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	if (!mcu->enabled) 
		return 1;

	for (n = 0; n < 9; n++) {
		/* byte/x4[0] of the macro */
		offset = PHY_CFG_WRDQ_DEL_N_0 +
			(unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET));
		/* Check if macro enabled */
		if (!((mcu->phy_params.cfg_macro_en_val >> (2 * n)) & 0x1))
			continue;
		wdata = mcu->mcu_ud.fix_wrdq_dly[2 * n] & 0xFFF;
		phy_write_reg(mcu, offset, wdata);

		/* x4[1] of same macro */
		if (!((mcu->phy_params.cfg_macro_en_val >> (2 * n + 1)) & 0x1))
			continue;
		readData = phy_read_reg(mcu, offset);
		wdata = mcu->mcu_ud.fix_wrdq_dly[2 * n + 1] & 0xFFF;
		phy_write_reg(mcu, offset,
			      ((wdata << 12) | (readData & 0xFFF)));
	}
	/*
	 * Must reset statemachine to take in new changes
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_TRNLOAD(mcu);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	return 0;
}

/*
 * phy_correct_wrdq_delays 
 * If RD-lvl (EYE) values are less then 0x20, fix it to 0x40
 */
int phy_correct_wrdq_delays(void *ptr)
{
	unsigned int n, err;
	unsigned int readData, offset, wdata = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	if (!mcu->enabled) {
		return 1;
	}
	err = 0;
	/* This value might change based on DIMM/SPEED */
	if (((mcu->id == 1) || (mcu->id == 3)) && (mcu->mcu_params.speed > 1700)) 
		wdata = FIX_BROKEN_WRDQ_VALUE_1866;
	else 
		wdata = FIX_BROKEN_WRDQ_VALUE;

	for (n = 0; n < 9; n++) {
		/* byte/x4[0] of the macro */
		offset = PHY_CFG_WRDQ_DEL_N_0 +
			(unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET));
		/* Check if macro enabled */
		if (!((mcu->phy_params.cfg_macro_en_val >> (n * 2)) & 0x1))
			continue;
		readData = phy_read_reg(mcu, offset);
		if (((readData & 0xFFF) < CMP_BROKEN_WRDQ_VALUE_LO) ||
		    ((readData & 0xFFF) > CMP_BROKEN_WRDQ_VALUE_HI)) {
#ifdef FIX_BROKEN_WRDQ_PERMACRO
			phy_write_reg(mcu, offset,
				      ((readData & 0xFFF000) | wdata));
			debug("PHY[%d]: FIX_BROKEN_WRDQ macro:%d "
				"[After PEVM-WR-deskew: 0x%03X]\n",
				mcu->id, n * 2, readData & 0xFFF);
#else
			debug("PHY[%d]: Need FIX_BROKEN_WRDQ macro:%d "
				"[After PEVM-WR-deskew: 0x%03X]\n",
				mcu->id, n * 2, readData & 0xFFF);
			err++;
#endif
		}
		/* x4[1] of same macro */
		if (!((mcu->phy_params.cfg_macro_en_val >> ((n * 2) + 1)) & 0x1))
			continue;
		readData = phy_read_reg(mcu, offset);
		if ((((readData >> 12) & 0xFFF) < CMP_BROKEN_WRDQ_VALUE_LO) ||
		    (((readData >> 12) & 0xFFF) > CMP_BROKEN_WRDQ_VALUE_HI)) {
#ifdef FIX_BROKEN_WRDQ_PERMACRO
			phy_write_reg(mcu, offset,
				      ((wdata << 12) | (readData & 0xFFF)));
			debug("PHY[%d]: FIX_BROKEN_WRDQ macro:%d "
				"[After PEVM-WR-deskew: 0x%03X]\n",
				mcu->id, n * 2, readData & 0xFFF);
#else
			debug("PHY[%d]: Need FIX_BROKEN_WRDQ macro:%d "
				"[After PEVM-WR-deskew: 0x%03X]\n",
				mcu->id, n * 2, readData & 0xFFF);
			err++;
#endif
		}
	}
	/*
	 * Must reset statemachine to take in new changes
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_TRNLOAD(mcu);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	return err;
}

unsigned int rttnom_inohm(unsigned int mr1val)
{
	unsigned int rttnom = 0;

	rttnom = (mr1val >> 2) & 0x1;	/* A2 */
	rttnom |= (mr1val >> 5) & 0x2;	/* A6 */
	rttnom |= (mr1val >> 7) & 0x4;	/* A9 */
	switch (rttnom) {
	case 0:
		return 0;
	case 1:
		return 60;
	case 2:
		return 120;
	case 3:
		return 40;
	case 4:
		return 20;
	case 5:
		return 30;
	default:
		return 0;
	}
}

/* Using FSM to program MR regs for functioning mode */
void fsm_set_working_mr(void *ptr, unsigned int rank)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int mr1 = 0, mr2 = 0;
	unsigned int fsm_init_seq = 0;
	unsigned int fsm_init_ctl = 0;

	if ((mcu->mcu_params.activeslots == 1) &&
                mcu->mcu_params.all_DIMMs_quadrank) {
		if (rank != 5)
			return;	
		mr1 = 0x42;
		mr2 = 0x418;
        } else if ((mcu->mcu_params.activeslots == 3) &&
		mcu->mcu_params.all_DIMMs_quadrank) {
		if (rank != 7)
			return;	
		mr1 = 0x6;
		mr2 = 0x418;
	}
	mcu->mcu_wr(mcu, MCU_REG_MRS_1_VALUE, mr1);
	mcu->mcu_wr(mcu, MCU_REG_MRS_2_VALUE, mr2);
	debug("\tWR-LVL MCU%d FSM program working mode MR1 RTTnom ="
			" 0x%x (%dohm) - MR2 RTTWr = 0x%x\n",
			mcu->id, mr1, rttnom_inohm(mr1), mr2);
        fsm_init_ctl = (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
                        ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
                        ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_MRENAB_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	/* Kick off FSM */
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
	/* FSM runs ~15-30us */
	DELAY(30);
	mr_prog_done_poll(mcu);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
			POLL_EQUAL);
}

void set_working_mr_per_rank(void *ptr)
{
	int unsigned iir = 0;
	int unsigned mr2val, mr1val;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	if (!mcu->enabled)
		return;

	debug("\nMCU[%d] Setting default MR-RTT values for functional mode\n",
		mcu->id);
	for (iir = 0; iir < MCU_SUPPORTED_RANKS; iir++) {
		if ((mcu->phy_tr_dly.rank_mask >> iir) & 0x1) {
			debug("MCU[%d] Setting RTTNOM Rank-CS[%d]...\n",
				mcu->id, iir);
			mr1val = mcu->mcu_params.rank_mr1[iir];
			mr2val = mcu->mcu_params.rank_mr2[iir];
			debug("PHY[%d] Per rank MR prog: ", mcu->id);
			if (mcu->mcu_params.all_DIMMs_quadrank == 1) {
			/* 4 rank */
				if ((mcu->mcu_params
					.rank_mask_disable_rttnom >> iir) & 0x1) {
				/* ODD Rank of QuadRank DIMM -> RTTnom is OFF */
					debug("ODD rank[%d]: \n\tMR1-RTTnom=OFF",
						iir);
					mcu_rank_mr_update(mcu, iir, 1,
							   mr1val & 0xFDBBU);
				} else {
					debug("EVEN rank[%d]: \n\tUsing MR1-RTTnom="
						"0x%x (%dohm)", mcu->id, mr1val,
						rttnom_inohm(mr1val));
					mcu_rank_mr_update(mcu, iir, 1, mr1val);
				}
			} else if (mcu->mcu_params.activeslots == 0x3) {
			/* 2DPC - 2 dual rank DIMM per channel */
				if ((0x1 << iir) & 0xCC) {	
				/* Changing ODT for second slot ranks */
					mr1val &= 0xFDBBU;
					mr1val |= mcu->mcu_params.rttnom_s1;
					debug("2'S-rank[%d]: \n\tMR1-RTTnom="
						"0x%x (%dohm) 2DPC", iir, 
						mcu->mcu_params.rttnom_s1,
						rttnom_inohm(mr1val));
				} else {
					debug("1'S-rank[%d]: \n\tMR1-RTTnom="
						"0x%x (%dohm) 2DPC", iir, 
						mcu->mcu_params.rttnom_s0,
						rttnom_inohm(mr1val));
				}
				mcu_rank_mr_update(mcu, iir, 1, mr1val);
			} else {
			/* 1DPC 1/2 rank DIMM */
				debug("1'S-rank[%d]: \n\tMR1-RTTnom=0x%x"
					" (%dohm) 1DPC", iir, 
					mcu->mcu_params.rttnom_s0,
					rttnom_inohm(mr1val));
				mcu_rank_mr_update(mcu, iir, 1, mr1val);
			}
			mcu_rank_mr_update(mcu, iir, 2, mr2val);
			debug(" MR2-RTTwr=0x%x\n", mr2val);
		}
	}
}

/* PHY training read eye leveling */
int phy_train_rde_lvl_per_rank(struct apm_mcu *mcu, unsigned int rank)
{	
	unsigned int iia = rank;
	unsigned int slice;
	unsigned int olddelay;
	int unsigned __attribute__ ((unused)) rddata;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int err = 0;

	fsm_init_ctl = (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
                	((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
                	((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	/* 
	 *  FIX: RDG Read-Enable delay
	 */
	rddata = phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);
	rddata &= ~(0x7);
	rddata |= KCPHY_FIXED_READEN_DELAY;
	if (mcu->mcu_ud.fix_gtlvl_flg)
		rddata = 0x6db6ff;
	debug("PHY[%d] Setting FIXED RDEN: 0x%x\n", mcu->id, rddata);
	phy_write_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN, rddata);

	/* 
	 *  FIX: RDE leveling 
	 */
	if (mcu->mcu_ud.fix_rdlvl_flg) {
		debug("\n\nMCU[%d] - FIXING RDE Leveling values "
				"for all macros:\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >>
							slice) & 0x1))
				continue;
			mcu->phy_tr_dly.
				rank_dly[iia].rd_lvl[slice] =
				mcu->mcu_ud.fix_rd_lvl[iia][slice];
		}
		debug("Restoring the FIX delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 0, 1);
		mcu_phy_rdfifo_reset(mcu);
	} else {
		/* 
		 *  PEVM: RDE leveling
		 */
		if (!is_storm_revA())
			goto skip_fix_default_rde_1;
#ifdef FIX_DEFAULT_RDE
		/* Set default/start value as 0x20 then back-off by 0x10 */
		debug("MCU[%d] - FIXING DEFAULT RDE Leveling values "
				"for all macros (Before PEVM-RDEYE):\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
				slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >>
							slice) & 0x1))
				continue;
			mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice] =
				DEFAULT_RDEYE_VALUE;
		}
		debug("Restoring the FIX delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 0, 1);
#endif
skip_fix_default_rde_1:
		if (MCU_PHY_EARLY_RDGATELVL_ENAB) 
			mcu_set_SWISS_TRNCTL(mcu, 1, 0, 0, 1, 0xFF,
					((~(0x1U << iia)) & 0xFF));

		fsm_init_seq = (0U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
			(0U << MCU_DDR_INIT_SEQ_GATEENAB_RNG) |
			(1U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
		mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);	
		debug("MCU[%d]: ### start PEVM train RdLvl only for rank=%01d\n",
				mcu->id, iia);
		/* Kick off FSM */
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
		if (MCU_PHY_EARLY_RDGATELVL_ENAB) 
			mcu_set_SWISS_TRNCTL(mcu, 0, 0, 0, 0, 0xFF, 0xFF);
		/* FSM runs ~15-30us */
		DELAY(30);	
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		/* Look for training errors */
		err = mcu_check_phy_trainerr(mcu, 0);
		/* Copy delay values before WrCal & deskew */
		phy_save_train_dly_csrs(mcu);

		if (err) 
			debug("\nPHY[%d] *** PEVM-RDE leveling ERROR: %d ***\n",
					mcu->id, err);

#ifdef FIX_DEFAULT_RDE
		/* 
		 * AUTOFIX: Back-Off RDE based on default value 
		 * [new-lvl -= (default-reg-value)/2]
		 */
		debug("\nMCU[%d] - AUTO-FIXING RDE Leveling values "
				"for all macros:\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
				slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val
							>> slice) & 0x1))
				continue;
			olddelay = mcu->phy_tr_dly.
				rank_dly[iia].rd_lvl[slice];

			if (!is_storm_revA())
				goto skip_fix_default_rde_3;

			if (olddelay > (DEFAULT_RDEYE_VALUE / 2)) {
				mcu->phy_tr_dly.
					rank_dly[iia].rd_lvl[slice] -=
					(DEFAULT_RDEYE_VALUE / 2);
skip_fix_default_rde_3:
#ifdef FIX_RDLVL_BACKOFF
				/* 
				 * DQS might be too close 
				 * to the right edge of the DQ eye. 
				 */
				if (!is_storm_revA())
                                        mcu->phy_tr_dly.
                                        rank_dly[iia].rd_lvl[slice] -= 12;
                                else
                                        mcu->phy_tr_dly.
                                        rank_dly[iia].rd_lvl[slice] -= 8;
#endif
				debug("\t\t Correcting RDE-LVL RANK[%d]"
						"-Macro[%d]: 0x%x [old:0x%x]\n",
						iia, slice,mcu->phy_tr_dly.rank_dly
						[iia].rd_lvl[slice], olddelay);
			}

		}
		debug(" Restoring the Auto Fixed delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 0, 1);
		mcu_phy_rdfifo_reset(mcu);
#endif /* FIX_DEFAULT_RDE */

		/* Check/Fix broken RDE based on FIX_BROKEN_RDEYE_PERMACRO */
		if (is_storm_revA())
			err += phy_correct_rdeye_delays(mcu, iia);
	}

	return err;
}

/* 
 *  AUTOFIX: RDG leveling (pull/push rdg-lvl based on rdg+rde)
 */
void phy_fix_rdg_broken_window(struct apm_mcu *mcu, unsigned int rank)
{
	unsigned int iia = rank;
	unsigned int slice;
	unsigned int sumdelay, olddelay;

	debug("\nMCU[%d] - AUTO-FIXING RDG Leveling values for all macros:\n",
			mcu->id);
	for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
			continue;

		olddelay = mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice];
		sumdelay = (mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] & 0xFF) +
			mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice];
		if ((sumdelay > 0x50) && (sumdelay <= 0x60)) {
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] -= 0x10;
			debug("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay:"
					" 0x%x [0x%x(fr)+0x%x=0x%x 0x50-0x60]\n",
					iia, slice,
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice],
					olddelay,
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice],
					sumdelay);
		} else if ((sumdelay > 0x60) && (sumdelay <= 0x70)) {
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] -= 0x20;
			debug("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay:"
					" 0x%x [0x%x(fr)+0x%x=0x%x 0x60-0x70]\n",
					iia, slice, 
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice], 
					olddelay, 
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice], 
					sumdelay);
		} else if ((sumdelay > 0x70) && (sumdelay <= 0x80)) {
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] -= 0x30;
			debug("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay:"
					" 0x%x [0x%x(fr)+0x%x=0x%x 0x70-0x80]\n",
					iia, slice,
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice], 
					olddelay,
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice], 
					sumdelay);
		} else if ((sumdelay > 0x80) && (sumdelay <= 0x90)) {
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] -= 0x40;
			debug("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay:"
					" 0x%x [0x%x(fr)+0x%x=0x%x 0x80-0x90]\n",
					iia, slice,
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice], 
					olddelay,
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice], 
					sumdelay);
		} else if ((sumdelay > 0x90) && (sumdelay <= 0xa0)) {
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] -= 0x50;
			debug("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay:"
					" 0x%x [0x%x(fr)+0x%x=0x%x 0x90-0x98]\n",
					iia, slice,
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice], 
					olddelay,
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice], 
					sumdelay);
		} else {
			debug("\t\tRANK[%d]-MACRO[%d] HW-RDG-delay: 0x%x"
					"    [+0x%x=0x%x]\n",
					iia, slice,
					mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice], 
					mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice], 
					sumdelay);
		}
	}
	debug("Restoring the Auto Fixed delays...\n");
	phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 1, 0);
	mcu_phy_rdfifo_reset(mcu);
}

/* PHY training read gate leveling */
int phy_train_rdg_lvl_per_rank(struct apm_mcu *mcu, unsigned int rank)
{
	unsigned int iia = rank;
	unsigned int slice;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int err = 0;

	fsm_init_ctl = (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
                	((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
                	((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

#ifdef FIX_DEFAULT_RDG_PERMACRO_2S
	/* 
	 *  FIX-DEFAULT: RDG leveling
	 */
	debug1("\nMCU[%d] - FIXING DEFAULT RDG Leveling values"
			" for all macros [ActiveSlots:0x%x]\n",
			mcu->id, mcu->mcu_params.activeslots);
	/* LRDIMM */
	if (mcu->mcu_params.dimm_type == LRDIMM) 
		goto lrdimm_fix_dflt_rdg_2s;

	if (mcu->mcu_params.activeslots != 0x3) 
		goto skip_fix_dflt_rdg_permacro_2s;

	for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
			continue;

		if (mcu->mcu_params.speed > 1400) {
			if (mcu->timing_params.all_DIMMs_registered){
				if ((slice < 5) || ((slice > 11)
							&& (slice < 15)))
					mcu->phy_tr_dly.rank_dly[iia]
						.gt_lvl[slice] =
						FIX_DEFAULT_RDG_PERMACRO_VALUE_1600R_H;
				else
					mcu->phy_tr_dly.rank_dly[iia]
						.gt_lvl[slice] =
						FIX_DEFAULT_RDG_PERMACRO_VALUE_1600R_L;
			} else {
				mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] =
					FIX_DEFAULT_RDG_PERMACRO_VALUE_1600U;
			}
		} else {
			mcu->phy_tr_dly.rank_dly[iia].
				gt_lvl[slice] =
				FIX_DEFAULT_RDG_PERMACRO_VALUE_1333;
		}
		debug("\tRank[%d] Macro[%d] Starting RDG = 0x%X\n", iia, slice, 
				mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice]);
	}
	goto finish_fix_dflt_rdg_2s;

lrdimm_fix_dflt_rdg_2s:
	for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
		if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
			continue;
		if (mcu->mcu_params.speed > 1400) 
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice]
				= FIX_DEFAULT_RDG_PERMACRO_VALUE_1600_LRDIMM;
		else if (mcu->mcu_params.speed > 1200)
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice]
				= FIX_DEFAULT_RDG_PERMACRO_VALUE_1333_LRDIMM;
		else
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice]
				= FIX_DEFAULT_RDG_PERMACRO_VALUE_1066_LRDIMM;
	
		debug("\tLRDIMM: Rank[%d] Macro[%d] Starting RDG = 0x%X\n", iia,
			slice, mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice]);
	}

finish_fix_dflt_rdg_2s:
	debug(" Restoring the Auto Fixed delays...\n");
	phy_restore_train_dly_csrs(mcu, (0x1U << iia),0, 1, 0);
	mcu_phy_rdfifo_reset(mcu);
skip_fix_dflt_rdg_permacro_2s:
#endif /* FIX_DEFAULT_RDG_PERMACRO_2S */

	/* 
	 *  FIX: RDG leveling 
	 */
	if (mcu->mcu_ud.fix_gtlvl_flg) {
		debug("\n\nMCU[%d] - FIXING RDG Leveling values for "
				"all macros:\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >>
							slice) & 0x1))
				continue;
			mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice] =
				mcu->mcu_ud.fix_gt_lvl[iia][slice];
		}
		debug(" Restoring the FIX delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 1, 0);
		mcu_phy_rdfifo_reset(mcu);
	} else {
		/* 
		 *  PEVM: RDG leveling
		 */
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		if (MCU_PHY_EARLY_RDGATELVL_ENAB) 
			mcu_set_SWISS_TRNCTL(mcu, 1, 0, 1, 0, 0xFF, 
					((~(0x1U << iia)) & 0xFF));

		fsm_init_seq = (0U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
				(1U << MCU_DDR_INIT_SEQ_GATEENAB_RNG) |
				(0U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
		mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);
		debug("MCU[%d]: ### start PEVM train GtLvl only for"
				" rank=%01d\n", mcu->id, iia);
		/* Kick off FSM */
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
		if (MCU_PHY_EARLY_RDGATELVL_ENAB) 
			mcu_set_SWISS_TRNCTL(mcu, 0, 0, 0, 0, 0xFF, 0xFF); 
		/* FSM runs ~15-30us */
		DELAY(30);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		/* Look for training errors */
		err = mcu_check_phy_trainerr(mcu, 0);
		/* Copy delay values before WrCal & deskew */
		phy_save_train_dly_csrs(mcu);
		mcu_phy_rdfifo_reset(mcu);

		/* XXX: Review */
#ifdef CHECK_BROKEN_RDG2S
		/* 
		 *  AUTOFIX: RDG2S leveling
		 */
		if (!(mcu->mcu_params.activeslots == 0x3))
			goto skip_check_brken_rdg_2s;
		debug1("\nMCU[%d] - CHECKING RDG2S Leveling values for"
				" all macros:\n", mcu->id);

		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++){
			if (!((mcu->phy_params.cfg_macro_en_val >> slice)& 0x1))
				continue;
			if (mcu->phy_tr_dly.rank_dly[iia]
					.gt_lvl[slice] < 0x2c0){
				debug1("\t*WARNING: 2S RDG delay "
						"too small: Rank[%d]-Slice"
						"[%d]=0x%0x\n", iia, slice, 
						mcu->phy_tr_dly
						.rank_dly[iia].gt_lvl[slice]);
				/* err += 1; */
			}
		}
skip_check_brken_rdg_2s:
		if (err) 
			debug("\nPHY[%d] *** PEVM-RDG leveling ERROR: "
					"%d ***\n", mcu->id, err);
#endif
	}

	return err;
}

/* PHY training write leveling */
int phy_train_wr_lvl_per_rank(struct apm_mcu *mcu, unsigned int rank)
{
	unsigned int iia = rank;
	unsigned int slice;
	int unsigned mr2val, mr1val, wdata, olddelay;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int err = 0;

	fsm_init_ctl = (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
                	((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
                	((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	/* 
	 *  FIX: WR leveling 
	 */
	if (mcu->mcu_ud.fix_wrlvl_flg) {
		debug("\n\nMCU[%d] - FIXING WR Leveling values "
					"for all macros:\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
				continue;
			mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] =
					mcu->mcu_ud.fix_wr_lvl[iia][slice];
		}
		debug("Restoring the FIX delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 1, 0, 0);
		mcu_phy_rdfifo_reset(mcu);

		debug("\nDisabling WR-CAL...\n");
		mcu->phy_tr_dly.phy_wrcal_rank_mask &= ~(0x1 << iia);
	} else {
		/* 
		 * PEVM: WR leveling
		 * Must turn off MR2 dynamic odt before WrLvl
		 * And only allow MR1 RttNom { RZQ/2 or RZQ/4 or RZQ/6 }
		 */
		if (rank > 0)
			goto skip_mr_lvl;
		debug("\nMCU[%d] Setting custom MR-RTT values "
				"for WR-LVL mode\n", mcu->id);
		mr1val = mcu->mcu_rd(mcu, MCU_REG_MRS_1_VALUE);
#ifdef FIX_RTTNOM_WRLVL
		/* Custom RTTNOM during wrlvl */
		wdata = putRttNomintoMR1(mr1val, FIX_RTTNOM_WRLVL_VAL);
#else
		/* RTTNOM during wrlvl default 40 Ohm RZQ/6 */
		wdata = putRttNomintoMR1(mr1val, 
					mcu->mcu_params.rttnom_wrlvl);	
#endif
		mcu->mcu_wr(mcu, MCU_REG_MRS_1_VALUE, wdata);
		debug("\tWR-LVL Rank[%d]: MCU FSM Setting MR1-RTTnom ="
				" 0x%x (%dohm)\n", 
				iia, wdata, rttnom_inohm(wdata));
		mr2val = mcu->mcu_rd(mcu, MCU_REG_MRS_2_VALUE);
		wdata = mr2val & 0xFFFFF9FF;
		mcu->mcu_wr(mcu, MCU_REG_MRS_2_VALUE, wdata);
		debug("\tWR-LVL Rank[%d]: MCU FSM Setting MR2-RTTwr ="
				" 0x%x\n", iia, wdata);

		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
				POLL_EQUAL);
		fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_MRENAB_RNG);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
		/* Kick off FSM */
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
		/* FSM runs ~15-30us */
		DELAY(30);
		mr_prog_done_poll(mcu);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
				POLL_EQUAL);

skip_mr_lvl:
		/* 
		 * Change WR_CAL pattern 
		 * Default pattern does not toggle bit3 & bit 7
		 */
		phy_write_reg(mcu, PHY_CFG_REG_WRCAL_PAT1, CHANGE_WRCAL_PAT1);
		phy_write_reg(mcu, PHY_CFG_REG_WRCAL_PAT2, CHANGE_WRCAL_PAT2);

		/* LRDIMM */
		if (mcu->mcu_params.dimm_type == LRDIMM) {
			debug("\nLRDIMM: Enable Pattern in MB for" 
							" Write Leveling\n");
			lrdimm_mb_WRleveling(mcu, 0);
		}
			
		fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
			(0U << MCU_DDR_INIT_SEQ_GATEENAB_RNG)
			| (0U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
		mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);
		debug("MCU[%d]: ### start PEVM train WrLvl only for "
				"rank=%01d\n", mcu->id, iia);
		/* Kick off FSM */
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);
		/* FSM runs ~15-30us */
		DELAY(30);
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
		/* Look for training errors */
		err += mcu_check_phy_trainerr(mcu, 0);
		/* Copy delay values before WrCal & deskew */
		phy_save_train_dly_csrs(mcu);
		mcu_phy_rdfifo_reset(mcu);

		/* LRDIMM */
		if (mcu->mcu_params.dimm_type == LRDIMM) {
			debug("\nLRDIMM: Disable Pattern in MB for WrLvl -"
					" Restore Normal Operations in MB\n");
			lrdimm_mb_normal_op(mcu, 0);
		}

		if ((mcu->mcu_params.activeslots == 1) &&
				mcu->mcu_params.all_DIMMs_quadrank)
			fsm_set_working_mr(mcu, rank);
		else
			set_working_mr_per_rank(mcu);

#ifdef FIX_WRLVL_BACKOFF
		/* 
		 * AUTOFIX: WR leveling (lvl -= min_samples)
		 */
		debug("\nMCU[%d] - AUTO-FIXING WR Leveling values for "
				"all macros:\n", mcu->id);
		for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
			if (!((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
				continue;
			olddelay = mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice];
			if (olddelay > mcu->phy_tr_dly.wrlvl_min_smpl) {
#ifdef FIX_WRLVL_BACKOFF_NOTFULL
				/*
				 * Full backoff might put WR-LVL in uncertain
				 * window. 2/3'rd backoff is prefered at the cost
				 * of loss of margin
				 */
				mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] -=
					((mcu->phy_tr_dly.wrlvl_min_smpl)
					 * FIX_WRLVL_BACKOFF_MVALUE) /
					FIX_WRLVL_BACKOFF_DVALUE;
#else
				mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] -=
						mcu->phy_tr_dly.wrlvl_min_smpl;

				if (!is_storm_revA()) 
					goto skip_wrlvl_fixup;

				/* Shift away broken wrlvl holes */
				if (mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] > 0x88 &&
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] <= 0x98) {
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] -= 0x30;
				} else if (mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] > 0xE0 &&
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] <= 0xFF) {
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] += 0x30;
				} else if (mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] > 0x98 &&
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] <= 0xE0) {
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] = 0xBC;
				}

				if (mcu->mcu_params.all_DIMMs_quadrank) {
					if (mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] > 0x30 &&
					mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] <= 0x50){ 
						 mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] += 0x20;
					} else if  (mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] > 0x1 &&
                                        mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] <= 0x30){
                                                 mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice] += 0x30;
					}
				} 
skip_wrlvl_fixup:
#endif
#ifdef FIX_WRLVL_BIT8_BEFOREWRCAL
				/* 
				 * Set all WR-LVL as 0x1XX to avoid WR-CAL 
				 * problem. WR-CAL migh be off by 1clk between
				 * two ranks, when CLK & DQS are aligned
				 */
				if (mcu->mcu_params.dimm_type != LRDIMM) {   
					mcu->phy_tr_dly.rank_dly[iia]
						.wr_lvl[slice] |= 0x100;
				} else if ((slice > 0) &&
						((mcu->phy_tr_dly.rank_dly[iia]
						  .wr_lvl[slice] + 0x80) <
						 mcu->phy_tr_dly.rank_dly[iia]
						 .wr_lvl[slice-1])) {
					mcu->phy_tr_dly.rank_dly[iia]
						.wr_lvl[slice] += 0x100;
				}
#endif
				debug("\t\tCorrecting WR-LVL RANK[%d]-"
						"Macro[%d]: 0x%x [old:0x%x]\n",
						iia, slice,
						mcu->phy_tr_dly.rank_dly[iia]
						.wr_lvl[slice], olddelay);
			}

		}
		debug("Restoring the Auto Fixed delays...\n");
		phy_restore_train_dly_csrs(mcu, (0x1U << iia), 1, 0, 0);
#endif /* FIX_WRLVL_BACKOFF */
	}
	return err;
}

/*
 * calib_pevm_custom_steps
 * PHY PEVM training for all lanes and ranks
 */
int calib_pevm_custom_steps(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned iia;
	int unsigned wdata;
	int unsigned __attribute__ ((unused)) rddata;
	int err = 0, err0 = 0;
	int unsigned err_wrlvl = 0, err_rde = 0, err_rdg = 0, 
			err_wrcal = 0, err_deskew = 0, err_2ndlvl = 0;

	/* 
	 * Setup MCU Training FSM CSRs
	 */
	debug1("PHY[%d]: Setting WW:0x%x, RR:0x%x\n", mcu->id,
	       mcu->mcu_params.tWRLVL_WW, mcu->mcu_params.tRDLVL_RR);
	mcu->mcu_wr(mcu, MCU_REG_WRLVLMRD, (0x14U));	
	mcu->mcu_wr(mcu, MCU_REG_WRLVLTMRS, (0x0000FFFFU | 
			((mcu->mcu_params.tWRLVL_WW & 0xFF) << 24)));	
	mcu->mcu_wr(mcu, MCU_REG_RDLVLTMRS, (0x0010FFFFU | 
			((mcu->mcu_params.tRDLVL_RR & 0xFF) << 24)));	
	if (is_storm_revA()) {
		mcu->mcu_wr(mcu, MCU_REG_WRLVLDLY, (0x0A090F0FU));
		mcu->mcu_wr(mcu, MCU_REG_RDLVLDLY, (0x100A0C0AU));
	} else {
		mcu->mcu_wr(mcu, MCU_REG_WRLVLDLY, (0x0));
		mcu->mcu_wr(mcu, MCU_REG_RDLVLDLY, (0x1FU));
	}
	mcu->mcu_wr(mcu, MCU_REG_WRLVLCTL, (0x00000008U));
	mcu->mcu_wr(mcu, MCU_REG_RDGATECTL, (0x00000008U));
	mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, (0x00000008U));	
	mcu_phy_rdfifo_reset(mcu);

	if (mcu->mcu_params.all_DIMMs_quadrank == 1) 
		debug("4R: Calibration for 4R1S/4R2S DIMM "
			"[ActiveRanks:0x%x, ActiveSlots:0x%x]\n",
		     	mcu->mcu_params.activeranks, 
			mcu->mcu_params.activeslots);
	else 
		debug
		    ("Calibration for 2R2S/1R1S/1R2S/2R1S DIMM "
			"[ActiveRanks:0x%x, ActiveSlots:0x%x]\n",
		     	mcu->mcu_params.activeranks, 
			mcu->mcu_params.activeslots);

	/* Disable DLL-Reset */
	wdata = mcu->mcu_rd(mcu, MCU_REG_MRS_0_VALUE) & 0xFEFF;
	mcu->mcu_wr(mcu, MCU_REG_MRS_0_VALUE, wdata);

	/* Per rank calibration */
	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
		if (!((mcu->phy_tr_dly.rank_mask >> iia) & 0x1)) 
			continue;
		debug1("\n- - - - - - - - - - - - - - - - - - - - - - - -\n");
		debug1("\nMCU[%d] Starting Leveling Rank-CS[%d]...\n", 
								mcu->id, iia);
		/*** WR-LVL ***/
		err0 = phy_train_wr_lvl_per_rank(mcu, iia); 
		if (err0) {
			err += err0;
			err_wrlvl |= (0x1 << iia);
			unrecovered_reset(mcu);
		}

		/* Enable Weak Pull up/down for RDG/RDE leveling */
		phy_rf_write_dqs_weak_pull_down_disable(mcu, 
						KCPHY_DISABLE_PULLUP);
#ifdef DUMMY_BIST_FOR_2S_LVL
		/* Doing DummyBIST on non-populated ranks */
		if (mcu->mcu_params.activeslots == 0x3) {
			mcu_dummy_bist_2s_calib(mcu, iia + 4, 1);
			mcu_phy_rdfifo_reset(mcu);
			mcu_set_SWISS_ODTADDR(mcu, 1, 0, 0, 1, 0);
		}
#endif
		/*** RDG-LVL ***/
		err0 = phy_train_rdg_lvl_per_rank(mcu, iia); 
		if (err0) {
			err += err0;
			err_rdg |= (0x1 << iia);	
			unrecovered_reset(mcu);
		}

		/*** RDE-LVL ***/
		err0 = phy_train_rde_lvl_per_rank(mcu, iia);
		if (err0) {
			err += err0;
			err_rde |= (0x1 << iia);
			unrecovered_reset(mcu);
		}
		phy_save_train_dly_csrs(ptr);
		mcu_phy_rdfifo_reset(ptr);

#ifdef FIX_RDG_BROKEN_WINDOW
		if (is_storm_revA())
			phy_fix_rdg_broken_window(mcu, iia);
#endif 

		/* Fixing custom WRDQ-DQS CSRs */
		if (mcu->mcu_ud.fix_wrdq_flg) {
			mcu->phy_tr_dly.wrdeskew_rank_mask &= ~(0x1 << iia);
			debug(" Fixing WRDQ-DQS for all macros\n");
			err0 = phy_fix_wrdq_delays(mcu);
		}
		/* Disable Weak Pull up/dpwn for RDG/RDE leveling */
		phy_rf_write_dqs_weak_pull_down_disable(mcu, 1);

#ifdef OFF_DUMMY_BIST_FOR_2S_LVL
		if (mcu->mcu_params.activeslots == 0x3) {
			/* Clear RD-ODT */
			mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 0, 0);
			mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0, 0, 0);
		}
#endif
		/* 
		 * PEVM: WR-CAL, WR-Deskew, RD-Deskew & 2nd RD lvl
		 * PHY Write Calibration required
		 * (optional) PHY Deskew and 2nd Rd lvl
		 * check with KC on recommendations 
		 *   (only do middle rank for now - long ~50 us total)
		 */
		if ((mcu->phy_tr_dly.phy_wrcal_rank_mask >> iia) & 0x1) {
			debug("\n\n WR-CAL phy[0x%02X] (rank %d)\n\n",
				 mcu->phy_tr_dly.phy_wrcal_rank_mask, iia);
			if (mcu->mcu_ud.ud_sw_wrcal) {
				/* Currently, works only on BB2B@1600Mbps UDIMM */
				debug("Using SW-WR-CAL...\n");
				/* err0 += kc_phy_sw_fix_wrcal_deskew(ptr, iia, 1);*/
			} else {
				err0 += kc_phy_wrcal(ptr, iia, 1);
			}
		}
		if (err0) {
			err += err0;
			err_wrcal |= (0x1 << iia);
			unrecovered_reset(mcu);
		}


		if (err0) {
			if ((mcu->phy_tr_dly.rddeskew_rank_mask >> iia) & 0x1)
				debug(" ** WARNING: Disabling RD-DESKEW "
					"[Error detected in previous leveling: %d]\n",
					 err0);
			if ((mcu->phy_tr_dly.wrdeskew_rank_mask >> iia) & 0x1)
				debug(" ** WARNING: Disabling WR-DESKEW "
					"[Error detected in previous leveling: %d]\n",
					 err0);
			mcu->phy_tr_dly.rddeskew_rank_mask &= ~(0x1 << iia);
			mcu->phy_tr_dly.wrdeskew_rank_mask &= ~(0x1 << iia);
		}
		/* Clear RD-ODT */
		mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0, 0, 0);
		mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0, 0, 0);
	}	

	/*
	 * NON-DFI TRAINING: RD/WR DESKEW
	 */
	if (mcu->mcu_ud.ud_rddeskew_en || mcu->mcu_ud.ud_wrdeskew_en) {
		err_deskew = kc_phy_deskew(mcu); 
		if (err_deskew)
			err ++;
	}

	/*
	 * NON-DFI TRAINING: 2nd-lvl RDE
	 */
	if (mcu->mcu_ud.ud_rdlvl2nd_en) {
		/* err_2ndlvl = kc_phy_2ndlvl(mcu); */
		if (err_2ndlvl)
			err ++;
	}

	/* 
	 * Toggle lvl_load signals : MCU TRAIN Wr Rd Load
	 *   enables PHY to use restored Tr Delay CSRs 
	 */
	phy_rf_write_cfg_read_w_fixed_delay(mcu, KCPHY_USE_READ_W_FIXED_DELAY);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu_set_SWISS_TRNLOAD(mcu);
	mcu_phy_rdfifo_reset(mcu);

	/*
	 * Save off training delays (optional for driver)
	 */
	phy_save_train_dly_csrs(mcu);
	phy_save_wrdq_dly_csrs(mcu);
	phy_save_rddsk_dly_csrs(mcu);
	phy_save_wrdsk_dly_csrs(mcu);
	if (!mcu->mcu_ud.ud_sw_rdlvl || err)
		phy_display_post_train_csrs(mcu, mcu->phy_tr_dly.rank_mask);

#ifdef CLEAR_WRDESKEW_TRIM
	/*
	 * Clear WR-DESKEW trim values 
	 * (WR-DESKEW use used only to adjust DQ-DQS delay)
	 */
	if (mcu->phy_tr_dly.wrdeskew_rank_mask)
		phy_clear_wrdsk_trim(mcu);
#endif
#ifdef CLEAR_RDDESKEW_TRIM
	/*
	 * Clear RD-DESKEW trim values 
	 * (RD-DESKEW use used only to adjust RDE delay)
	 */
	if (mcu->phy_tr_dly.rddeskew_rank_mask)
		phy_clear_rddsk_trim(mcu);
#endif
	if (err) {
		debug1("\n***ERROR: PHY[%d] Calibration errors:0x%x\n", 
			mcu->id, err);
		debug1("\t[WR-LVL:[0x%x], RDG:[0x%x], RDE:[0x%x]]\n",
		       err_wrlvl, err_rdg, err_rde);
		debug1("\t[WR-CAL:[0x%x], DESKEW:[0x%x], 2ndlvl:[0x%x]]\n",
		       err_wrcal, err_deskew, err_2ndlvl);
	}
	return err;
}	/* calib_pevm_custom_steps */
