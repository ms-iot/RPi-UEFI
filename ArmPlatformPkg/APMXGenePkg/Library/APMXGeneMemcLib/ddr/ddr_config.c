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

/* Fixed values used in timing calculation */
#define MCU_FIXTIME_TCCD_VAL    4
/* NOTE: MUST +1 Mcu cycle: Phy Rank switch btwn fast to slow lane */
#define PHY_RANK_DIMM_DLY_VAL   2
#define PHY_FIXTIME_RTR_VAL     (6 + PHY_RANK_DIMM_DLY_VAL)
#define PHY_FIXTIME_WTW_VAL     (6 + PHY_RANK_DIMM_DLY_VAL)
#define PHY_FIXTIME_RTW_VAL     (6 + PHY_RANK_DIMM_DLY_VAL)
#define PHY_FIXTIME_WTR_VAL     (6 + PHY_RANK_DIMM_DLY_VAL)

int mcu_board_specific_settings(void *p)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int rank_mask;


	/* 
	 * Enable only populated ck, cke, cs, odt signals (noise - power)
	 * LRDIMM: needs CS0/CS1 even for 1-rank DIMMs 
	 */
	rank_mask = mcu->phy_tr_dly.rank_mask;
	if (mcu->mcu_params.dimm_type == LRDIMM) 
		rank_mask |= 0x3;

	mcu->phy_params.cfg_cs_en = rank_mask;

	switch (mcu->mcu_params.activeslots) {
	case 0x1:	
		/* Max 2 ck needed for 1 dimm (incl quad rank) */
		mcu->phy_params.cfg_ck_en = rank_mask & 0xF;
		mcu->phy_params.cfg_odt_en = rank_mask & 0xF;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
		break;
	case 0x3:
		/* Max 4 ck needed for 2 dimms (incl quad rank) */
		mcu->phy_params.cfg_ck_en = rank_mask & 0xF;
		mcu->phy_params.cfg_odt_en = rank_mask & 0xF;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
#if !defined(APM_SIM) && !defined(APM_VBIOS)
		/* For 2DPC configuration, support up to 1333 Mhz */
		if (mcu->mcu_ud.ud_speed > 1333)
			mcu->mcu_ud.ud_speed = 1333;
#endif
		break;
	case 0x7:
		/* Max 6 ck needed for 3 dimms (incl quad rank) - split CK */
		mcu->phy_params.cfg_ck_en = rank_mask & 0xF;
		mcu->phy_params.cfg_odt_en = rank_mask & 0x3F;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
		break;
	default:
		mcu->phy_params.cfg_ck_en = 0xF;
		mcu->phy_params.cfg_odt_en = 0x3F;
		mcu->phy_params.cfg_cke_en = 0x3F;
	}
	return 0;
}

int ddr_spd_init(void *p)
{
	unsigned int i, j, err;
	unsigned long long rank_size;
	unsigned int activeslots, common_dimm_type, 
			component_width, mcu_clk_min_ps;
	unsigned int rank_shift, total_n_ranks, total_n_slots_active;
	unsigned int pll_forced_speed;
	unsigned int enabled_rddeskew, enabled_rdlvl2nd, enabled_wrdeskew;
	unsigned int deskew_rank_no, dis_rank = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;

	if (!mcu->enabled)
		return 0;
	debug("\nMCU[%d]: SPD read & DIMM config param generation\n", mcu->id);

	err = 0;
	activeslots = 0;
	common_dimm_type = 0;
	total_n_slots_active = 0;
	/* MIMIC_SPD */
	if (mcu->mcu_ud.ud_mimicSPD) {
		activeslots = mcu->mcu_ud.ud_mimic_activeslots;
		/* using mimic SPD values based on "ddr_mimic_spd_array" */
		debug("* Using mimic SPD values based on 'ddr_mimic_spd_array'"
			" [active-slots:0x%X] *\n", activeslots);
	}
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (mcu->mcu_ud.ud_mimicSPD) {
			if (!((activeslots >> i) & 0x1)) 
				continue;

			debug("GetFixed SPD MCU[%d]-Slot[%d]\n", mcu->id, i);
			/* consider both slots have same 'part-number' DIMM */
			memcpy(&mcu->spd_info[i], 
					mcu->mcu_ud.p_ddr_mimic_spd_array, 
							sizeof(spd_eeprom_t));
		} else {
			debug("GetI2C SPD MCU[%d]-Slot[%d]\n", mcu->id, i);
			activeslots |= (memc->p_spd_get(mcu, i) & 0x1) << i;
		}
	}
	if (!activeslots) {
		mcu->enabled = 0;
		debug("MCU[%d] - No DIMMs detected, disabling MCU\n", mcu->id);
		return 0;
	}
	mcu->mcu_params.activeslots = activeslots;
	debug1("MCU[%d] Total Active Slots: 0x%X\n", mcu->id, activeslots);

	err += mcu->p_ud_fixup_config(mcu);

	if (mcu->mcu_ud.ud_en2tmode && mcu->mcu_params.activeslots > 1) {
		mcu->mcu_params.en2Tmode = 1;
		debug1("MCU[%d] Enabling 2T Mode\n", mcu->id);
	}

	/* Calculate DIMM timing params based of SPD data */
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) 
			continue;

		total_n_slots_active += 1;
		err += compute_dimm_parameters(mcu, i);
		/* check common dimm type */
		if (!common_dimm_type) 
			common_dimm_type = (mcu->spd_info[i].module_type) & 0xF;
		else if (((mcu->spd_info[i - 1].module_type) & 0xF) !=
				((mcu->spd_info[i].module_type) & 0xF)) 
			common_dimm_type = 0xF;
	
		/* Enable the Address Mirror if the DIMMs support */
		if (mcu->dimm_params[i].mirrored_dimm) {
			mcu->mcu_params.mirror_ctrl = DIMM_ADDR_MIRROR_CTRL;
			debug("MCU[%d]-Slot[%d] Address Mirrored DIMM\n",
					mcu->id, i);
		} else {
			mcu->mcu_params.mirror_ctrl = 0x0;
		}

		rank_shift = 0;

		debug("\tDIMM:%d ORG #RANKS:%d\n", 
				i, mcu->dimm_params[i].n_ranks);
		for (j = 0; j < (mcu->dimm_params[i].n_ranks); j++) {
			if (j > 1)
				rank_shift = 2;
			mcu->phy_tr_dly.rank_mask |=
				(0x1 << (j + i * 2 + rank_shift)) &
				~(mcu->mcu_params.ranksdisable[i]);
			debug("\tAvailable-rank:%d [i=%x j=%x rank_shift=%x],"
				" rank-disable=%x\n",
				(0x1 << (j + i * 2 + rank_shift)), i, j,
				rank_shift, mcu->mcu_params.ranksdisable[i]);
			if (!(~(mcu->mcu_params.ranksdisable[i]) &
					 (0x1 << (j + i * 2 + rank_shift)))) {
				dis_rank++;
				debug("MCU[%d] Disabling rank: #%d of slot:#%d\n",
					 mcu->id, j, i);
			}
		}
		mcu->dimm_params[i].n_ranks -= dis_rank;
		debug("\tDIMM:%d NEW #RANKS:%d\n", i,
				mcu->dimm_params[i].n_ranks);
	}

	total_n_ranks = 0;
	for (j = 0; j < 8; j++) {
		if (((mcu->phy_tr_dly.rank_mask) >> j) & 0x1) 
			total_n_ranks++;
	}

	mcu->mcu_params.activeranks = mcu->phy_tr_dly.rank_mask;
	debug("MCU[%d] Total-ranks: 0x%x [rank-mask=0x%x]\n", 
		mcu->id, total_n_ranks, mcu->phy_tr_dly.rank_mask);
	if (((total_n_ranks == 4) && (mcu->mcu_params.activeslots == 1))
	    || ((mcu->mcu_params.activeranks == 0xFF)
		&& (mcu->mcu_params.activeslots == 3)))
		mcu->mcu_params.all_DIMMs_quadrank = 1;

	/* Default */
	mcu->mcu_params.dimm_type = UNKNOWN;
	if (err) 
		debug("Error from SPD [ERROR=%d]\n", err);

	switch (common_dimm_type) {
	case 0x0:		/* Unknown */
	case 0xF:		/* Unknown */
		debug("Unsupported common DRAM type.... 0x%x\n",
						common_dimm_type);
		mcu->mcu_params.dimm_type = UNKNOWN;
		err |= 0x4;
		break;
	case 0x2:		/* UDIMM */
	case 0x6:		/* Mini-UDIMM */
		mcu->mcu_params.dimm_type = UDIMM;
		break;
	case 0x1:		/* RDIMM */
	case 0x5:		/* Mini-RDIMM */
		mcu->mcu_params.dimm_type = RDIMM;
		break;
	case 0x3:		/* SO-DIMM */
	case 0x4:		/* Micro-DIMM */
	case 0x8:		/* SO-DIMM */
		mcu->mcu_params.dimm_type = SODIMM;
		break;
	case 0xB:		/* LRDIMM */
		mcu->mcu_params.dimm_type = LRDIMM;
		break;
	default:
		mcu->mcu_params.dimm_type = UNKNOWN;
	}
	if (err) 
		debug("Error from DIMM-type [ERROR=%d]\n", err);

	mcu->phy_tr_dly.phy_wrcal_rank_mask = mcu->phy_tr_dly.rank_mask;
	err += mcu_board_specific_settings(p);

	debug2("MCU[%d] Setting wr-cal-rank-mask: 0x%x\n",
		mcu->id, mcu->phy_tr_dly.phy_wrcal_rank_mask);

	pll_forced_speed = mcu->mcu_ud.ud_speed;
	if (mcu->mcu_ud.ud_pllforce_div) {
		mcu->mcu_params.pllctl0_idiv = mcu->mcu_ud.ud_pllctl0_idiv;
		mcu->mcu_params.pllctl0_fbdiv = mcu->mcu_ud.ud_pllctl0_fbdiv;
		mcu->mcu_params.pllctl0_odiv = mcu->mcu_ud.ud_pllctl0_odiv;
	}
	if (mcu->mcu_ud.ud_pllforce)
		debug("Forcing PLL...\n");
	/* Calculate common max DIMM clock support */
	mcu->mcu_params.speed_supported = 3200;
	mcu_clk_min_ps =
		 rdiv((2 * 1000000ULL), (mcu->mcu_ud.ud_speed));
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) 
			continue;

		mcu->mcu_params.speed_supported =
		    min(mcu->mcu_params.speed_supported,
			rdiv((2 * 1000000ULL),
			     (mcu->dimm_params[i].tCKmin_X_ps)));
		if (mcu->mcu_ud.ud_pllforce) {
			mcu_clk_min_ps = rdiv((2 * 1000000ULL), 
						(pll_forced_speed));
			mcu->dimm_params[i].tCKmin_X_ps =
			    rdiv((2 * 1000000ULL), (pll_forced_speed));
		} else {
			mcu_clk_min_ps = max(mcu_clk_min_ps,
					mcu->dimm_params[i].tCKmin_X_ps);
			/* update with expected speed for calc */
			mcu->dimm_params[i].tCKmin_X_ps = mcu_clk_min_ps;
		}
	}
	if (!mcu_clk_min_ps) {
		debug("common max clock caluclaiton ERROR: tCKmin_X_ps=%dps\n",
								mcu_clk_min_ps);
		return 4;
	}

	if (mcu->mcu_ud.ud_pllforce) {
		/* PLL_FORCED_SPEED/2 - in rounded MHz */
		mcu->mcu_params.clk_mhz_max = rdiv(pll_forced_speed, 2);
		mcu->mcu_params.speed = pll_forced_speed;
	} else {
		mcu->mcu_params.clk_mhz_max = rdiv(1000000ULL, mcu_clk_min_ps);
		/* in Mbps (speed_.... = 2*clk_mhz) */
		mcu->mcu_params.speed = min((2 * mcu->mcu_params.clk_mhz_max), 
					mcu->mcu_ud.ud_speed);
	}
	mcu->mcu_params.clk_mhz_pll = rdiv(mcu->mcu_params.speed, 2);
	debug2
	    ("MCU[%d] Speed-desired: %dMbps  Speed-supported: %dMbps [%dMHz]\n",
				     mcu->id, mcu->mcu_ud.ud_speed,
				     mcu->mcu_params.speed_supported,
				     rdiv(mcu->mcu_params.speed_supported, 2));
	debug2
	    ("MCU[%d] Target ClkFreq: %dMHz  DDR-PLL should be set to: %dMHz\n",
	     mcu->id, mcu->mcu_params.clk_mhz_max, mcu->mcu_params.clk_mhz_pll);

	enabled_rddeskew = mcu->mcu_ud.ud_rddeskew_en;  
	enabled_rdlvl2nd = mcu->mcu_ud.ud_rdlvl2nd_en;
	enabled_wrdeskew = mcu->mcu_ud.ud_wrdeskew_en;
	deskew_rank_no = mcu->mcu_ud.ud_dskrank;

	/*
	 * deskew is done only on first rank and 
	 * 2nd-lvl is done except first rank
	 */

	/* Enable rd-deskew only for first rank */
	mcu->phy_tr_dly.rddeskew_rank_mask = 0;
	if (enabled_rddeskew) {
		if (((mcu->mcu_params.speed > 1400)
			&& (mcu->mcu_params.activeslots == 0x3))
		    || ((mcu->mcu_params.speed > 1700)
			&& (mcu->mcu_params.activeslots == 0x1))) 
			mcu->phy_tr_dly.rddeskew_rank_mask =
						mcu->phy_tr_dly.rank_mask & 
						(0x1U << deskew_rank_no);
		debug2("MCU[%d] Setting rd deskew-rank-mask: 0x%x\n",
				mcu->id, mcu->phy_tr_dly.rddeskew_rank_mask);
	}
	/* Enable 2nd level rd-leveling of non-first ranks */
	mcu->phy_tr_dly.rdlvl2nd_rank_mask = 0;
	if (enabled_rdlvl2nd) {
		if ((total_n_ranks > 1)
				&& (mcu->phy_tr_dly.rddeskew_rank_mask > 0)) {
			mcu->phy_tr_dly.rdlvl2nd_rank_mask =
					mcu->phy_tr_dly.rank_mask & 
					~(mcu->phy_tr_dly.rddeskew_rank_mask);
		}
	}
	debug2("MCU[%d] Setting 2nd level rd level rank-mask: 0x%x\n",
				mcu->id, mcu->phy_tr_dly.rdlvl2nd_rank_mask);

	/* Enable wr-deskew only for first rank */
	mcu->phy_tr_dly.wrdeskew_rank_mask = 0;
	if (enabled_wrdeskew) {
		if (mcu->mcu_params.speed > 1000) 
			mcu->phy_tr_dly.wrdeskew_rank_mask =
			    mcu->phy_tr_dly.rank_mask & (0x1U << deskew_rank_no);
		debug2("MCU[%d] Setting wr deskew-rank-mask: 0x%x\n",
				mcu->id, mcu->phy_tr_dly.wrdeskew_rank_mask);
	}
	if (!mcu->mcu_ud.ud_pllforce_div) 
	{
		/* Set PLL config parameters */
		mcu->mcu_params.pllctl0_idiv = 0x5;
		switch (mcu->mcu_params.speed) {
		case 401:
		case 400:
		case 399:
			mcu->mcu_params.pllctl0_fbdiv = 0x5F;	
			mcu->mcu_params.pllctl0_odiv = 3;
			break;
		case 667:
		case 666:
		case 665:
			mcu->mcu_params.pllctl0_fbdiv = 0x78;
			mcu->mcu_params.pllctl0_odiv = 2;
			break;
		case 801:
		case 800:
		case 799:
			mcu->mcu_params.pllctl0_fbdiv = 0xC0;
			mcu->mcu_params.pllctl0_odiv = 3;
			break;
		case 1067:
		case 1066:
		case 1065:
			mcu->mcu_params.pllctl0_fbdiv = 0x80;
			mcu->mcu_params.pllctl0_odiv = 1;
			break;
		case 1334:
		case 1333:
		case 1332:
			mcu->mcu_params.pllctl0_fbdiv = 0xA0;	
			mcu->mcu_params.pllctl0_odiv = 1;
			break;
		case 1601:
		case 1600:
		case 1599:
			mcu->mcu_params.pllctl0_fbdiv = 0x7F;
			mcu->mcu_params.pllctl0_odiv = 1;
			mcu->mcu_params.pllctl0_idiv = 3;
			break;
		case 1867:
		case 1866:
		case 1865:
			mcu->mcu_params.pllctl0_fbdiv = 0x70;
			mcu->mcu_params.pllctl0_odiv = 0x0;
			break;
		case 2134:
		case 2133:
		case 2132:
			mcu->mcu_params.pllctl0_fbdiv = 0x80;	
			mcu->mcu_params.pllctl0_odiv = 0x0;
			break;
		default:	
			mcu->mcu_params.pllctl0_fbdiv = 0xC0;	
			mcu->mcu_params.pllctl0_odiv = 0x1;
		}
	}

	if (mcu->mcu_params.speed > 2200) {
		mcu->phy_params.en_phy_dll_cal = 1;
		debug("MCU[%d] Enabling DLL cal\n", mcu->id);
	} else {
		mcu->phy_params.en_phy_dll_cal = 0;
	}
	if (mcu->mcu_params.speed < 1100)
		mcu->phy_params.dll_cal_lo_freq = 1;
	else
		mcu->phy_params.dll_cal_lo_freq = 0;

	/* Calculate MCU timing params common for all DIMMs */
	err |= compute_timing_params(mcu);
	/* Check ECC for the channel DIMMs */
	if (mcu->timing_params.all_DIMMs_ECC_capable) {
		mcu->phy_params.cfg_macro_en_val = KCPHY_CFG_MACRO_ENABLE_VAL;
		if (mcu->mcu_params.ECCenable) {
			debug("MCU[%d]: DIMM ECC capable - Enabling ECC\n",
								      mcu->id);
			mcu->mcu_params.glb_err_ctrl |= 0x10080;
		} else {
			debug("MCU[%d]: DIMM ECC capable - Not Enabling ECC\n",
								      mcu->id);
			mcu->mcu_params.glb_err_ctrl &= ~0x8F;
			mcu->mcu_params.ECCenable = 0;
		}
	} else {
		debug("MCU[%d]: DIMM ECC not supported\n", mcu->id);
		mcu->mcu_params.glb_err_ctrl &= ~0x8F;
		mcu->mcu_params.ECCenable = 0;
		mcu->mcu_ud.ud_ECCscheme = 0;
		mcu->phy_params.cfg_macro_en_val =
		    (KCPHY_CFG_MACRO_ENABLE_VAL & KCPHY_CFG_MACRO_NOECC_MASK);
	}
	/*
	 * Enable MCU illegal address checking interrupt
	 */
	mcu->mcu_params.glb_err_ctrl |= 0x200;

	component_width = 0;
	rank_size = 0;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) 
			continue;

		mcu->timing_params.ndimms_present++;
		mcu->mcu_params.ranksperslot[i] = mcu->dimm_params[i].n_ranks;
		if (!component_width) {
			component_width = mcu->dimm_params[i].component_width;
		} else if (component_width !=
				   mcu->dimm_params[i].component_width) {
			err |= 0x8;
			component_width = 0xF;
		}
		if (!rank_size) 
			rank_size = mcu->dimm_params[i].rank_density;
		else if (rank_size > mcu->dimm_params[i].rank_density) 
			rank_size = mcu->dimm_params[i].rank_density;
		debug2("MCU[%d]-Slot[%d]: n_ranks=%d rank-size=%dMB"
			" component-width=%d\n", mcu->id, i, 
			mcu->dimm_params[i].n_ranks,
			(unsigned int)((mcu->dimm_params[i].rank_density) /
							    (1024U * 1024U)),
			mcu->dimm_params[i].component_width);
		mcu->mcu_params.rca[i] = mcu->dimm_params[i].rca;
		mcu->mcu_params.rcb[i] = mcu->dimm_params[i].rcb;
	}
	if (mcu->timing_params.all_DIMMs_registered) {
		mcu->mcu_params.rc_en = 1;
		debug("MCU[%d] Enabling RC programming for RDIMM\n", mcu->id);
	}
	if (component_width == 4) {
		mcu->mcu_params.by4_mode = 1;
		mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_x4_MASK;
	} else if (component_width == 8) {
		mcu->mcu_params.by4_mode = 0;
		mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_x8_MASK;
	} else {
		err |= 0x10;
		debug("ERROR: Unsupported x4/x8 mode [bits/component = %d]\n",
							component_width);
	}
	if (rank_size) {
		mcu->mcu_params.minranksize = rank_size;
	} else {
		debug("ERROR: Null common minimum rank size\n");
		err |= 0x20;
	}

	if (mcu->timing_params.tCKmin_X_ps != mcu_clk_min_ps) {
		debug("ERROR: MCU common max-clock caluclaiton  "
			"[tCKmin_X_ps=%dps timing-calc-tCKmin_X_ps%dps]\n",
			mcu_clk_min_ps, mcu->timing_params.tCKmin_X_ps);
		err |= 0x40;
	}
	return err;
}

void mcu_odt_config(struct apm_mcu *mcu)
{
	mcu->mcu_params.rank_mask_disable_rttnom = 0;
	/* Needed new RD-ODT table for multislot HW-WR-CAL workaround */
	if ((mcu->mcu_params.activeslots == 0x3) && 
			!mcu->mcu_params.all_DIMMs_quadrank) {	
		mcu->mcu_params.rank_rd_odt[0] = 0x4;	
		mcu->mcu_params.rank_rd_odt[1] = 0x8;
		mcu->mcu_params.rank_rd_odt[2] = 0x1;
		mcu->mcu_params.rank_rd_odt[3] = 0x2;
		mcu->mcu_params.rank_rd_odt[4] = 0x4;
		mcu->mcu_params.rank_rd_odt[5] = 0x8;
		mcu->mcu_params.rank_rd_odt[6] = 0x1;
		mcu->mcu_params.rank_rd_odt[7] = 0x2;
		debug("\tMCU[%d] 2S: Changing ODT table for 2R2S/4R2S "
				"[ActiveRanks:0x%x, ActiveSlots:0x%x]\n",
				mcu->id, mcu->mcu_params.activeranks,
				mcu->mcu_params.activeslots);
	} else if (mcu->mcu_params.all_DIMMs_quadrank == 1) {
		mcu->mcu_params.rank_wr_odt[0] = 0x05;
		mcu->mcu_params.rank_wr_odt[1] = 0x06;
		mcu->mcu_params.rank_wr_odt[2] = 0x05;
		mcu->mcu_params.rank_wr_odt[3] = 0x09;
		mcu->mcu_params.rank_wr_odt[4] = 0x05;
		mcu->mcu_params.rank_wr_odt[5] = 0x06;
		mcu->mcu_params.rank_wr_odt[6] = 0x05;
		mcu->mcu_params.rank_wr_odt[7] = 0x09;

		mcu->mcu_params.rank_rd_odt[0] = 0x04;	
		mcu->mcu_params.rank_rd_odt[1] = 0x08;
		mcu->mcu_params.rank_rd_odt[2] = 0x01;
		mcu->mcu_params.rank_rd_odt[3] = 0x02;
		mcu->mcu_params.rank_rd_odt[4] = 0x04;
		mcu->mcu_params.rank_rd_odt[5] = 0x08;
		mcu->mcu_params.rank_rd_odt[6] = 0x01;
		mcu->mcu_params.rank_rd_odt[7] = 0x02;

		mcu->mcu_ud.ud_bit_dq_stren = 4;

		/* Quad Rank disable rank 1,3 or rank 2,3 RttNom (depends on dimm) */
		mcu->mcu_params.rank_mask_disable_rttnom = 0xAA;
		debug("\tMCU[%d] 4R: Changing ODT table for 4R1S/4R2S"
				" [ActiveRanks:0x%x, ActiveSlots:0x%x]\n",
				mcu->id, mcu->mcu_params.activeranks,
				mcu->mcu_params.activeslots);
	} else {
		debug("\tMCU[%d]: Using Default ODT table for 1R1S/2R1S/2R2S"
				" \n\t\t[ActiveRanks:0x%x, ActiveSlots:0x%x]\n",
				mcu->id, mcu->mcu_params.activeranks,
				mcu->mcu_params.activeslots);
	}
}

int mcu_timing_config(void *p)
{
	unsigned int i, iir, temp;
	unsigned int mr0, mr1, mr2, mr3, ranks;
	unsigned int calc0, calc1, cycls;
	unsigned int cl, al, crl, cwl, blby2;
	unsigned int actpre1, rdpre, rdpre1, wrpre, wrrec, wrpre1, preact;
	unsigned int __attribute__ ((unused)) trfcmin;
	unsigned int tck_ps;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int relax_time_en, relax_margin_0, relax_margin_1, margin;
	unsigned int relax_rd2rd_margin, relax_rd2wr_margin, relax_wr2wr_margin,
		     relax_wr2rd_margin;
	unsigned int mr1_rttnom, mr1_rttnom_s1, mr2_rttwr;
	mcu_param_t *mp = &mcu->mcu_params;
	timing_params_t *tp = &mcu->timing_params;

	if (!(mcu->enabled)) 
		return 0;
	debug("\nMCU[%d]: Timing parameter calculation\n", mcu->id);

	/* Generate MCU CSR valis for timiing parameters */
	debug("* Generate MCU CSR values for timiing parameters *\n");
	cl = tp->lowest_common_SPD_caslat;
	crl = tp->cas_read_latency;
	/* XXX: Temp fix for dual slot */
	if (mcu->mcu_params.activeslots == 0x3) 
		/* Make WL close to RL to avoid ReadODT issue */
		cwl = tp->cas_read_latency + 1;
	else 
		cwl = tp->cas_write_latency;

	mp->cl = cl;
	debug("MCU[%d] cl=%d, tcrl=%d, tcwl=%d [original]\n", 
							mcu->id, cl, crl, cwl);
	
	/* LRDIMM */	
	if (mcu->mcu_params.dimm_type == LRDIMM) {
                const unsigned int mclk_ps = get_memory_clk_period_ps(p);
                unsigned int cmd_delay = 0;
                unsigned int dqs_delay = 0;
                unsigned int rd_min_delay_cycles = 0;
                unsigned int wr_min_delay_cycles = 0;

                cmd_delay = LRDIMM_CMDCK_DELAY_BASE + (mclk_ps / 2);
                dqs_delay = LRDIMM_DQS_DELAY_BASE + (mclk_ps / 4);
                rd_min_delay_cycles = (cmd_delay + dqs_delay)/mclk_ps + 2;
                wr_min_delay_cycles = (cmd_delay - dqs_delay)/mclk_ps;

                crl += rd_min_delay_cycles;
                cwl += wr_min_delay_cycles;

                debug("MCU[%d] cmd_delay = %dps, dqs_delay = %dps, tCK = %dps,"
			"min_delay_cycles: rd = %d, wr = %d, crl=%d, cwl=%d "
			"[After update for LRDIMM]\n",
                        mcu->id, cmd_delay, dqs_delay, mclk_ps,
			rd_min_delay_cycles, wr_min_delay_cycles, crl, cwl);
        }

	if (mcu->timing_params.all_DIMMs_registered &&
			(mcu->mcu_params.dimm_type != LRDIMM)) {
		mp->t_crl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? crl + 1 : crl;
		mp->t_cwl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? cwl + 1 : cwl;
	} else {
		mp->t_crl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? crl : crl - 1;
		mp->t_cwl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? cwl : cwl - 1;
	}
	debug("MCU[%d] tcrl=%d, tcwl=%d [After update for All-RDIMM=%d, "
		"PHY-EN-2T-adj=%d]\n", mcu->id, mp->t_crl, mp->t_cwl,
				mcu->timing_params.all_DIMMs_registered,
				mcu->phy_params.en_2T_adj_incr_latency);

	/* Setting custom t-crl */
	if (mcu->mcu_params.speed > 1700)
		mp->t_crl += 1;

	if (mcu->mcu_ud.ud_tcrl > 0) {
		mp->t_crl += mcu->mcu_ud.ud_tcrl;	
		debug("\nMCU[%d] Setting Custom t_crl: %d\n\n", mcu->id,
								mp->t_crl);
	}
	if (mcu->mcu_ud.ud_tcwl > 0) {
		mp->t_cwl -= mcu->mcu_ud.ud_tcwl;
		debug("\nMCU[%d] Setting Custom t_cwl: %d\n\n", mcu->id,
								mp->t_cwl);
	}
	debug("MCU[%d] tcrl=%d, tcwl=%d [After update for Margin]\n", 
					mcu->id, mp->t_crl, mp->t_cwl);

	mcu->phy_params.RL = (mcu->mcu_params.t_crl) + 1;
	mcu->phy_params.WL = (mcu->mcu_params.t_cwl) + 1;
	debug("PHY[%d] tcrl=%d, tcwl=%d\n", 
			mcu->id, mcu->phy_params.RL, mcu->phy_params.WL);

	if (mcu->mcu_params.en2Tmode) {
		mp->t_crl += 1;
		mp->t_cwl += 1;
	}
	debug("MCU[%d] tcrl=%d, tcwl=%d [After update for MCU-2T-EN=%d]\n",
		mcu->id, mp->t_crl, mp->t_cwl, mcu->mcu_params.en2Tmode);

	/* Check valid rd/wr latency */
	if (mp->t_crl < MCU_T_CRL_MIN) {
		debug("ERROR *** t_crl=%d < %d not supported.\n", 
						mp->t_crl, MCU_T_CRL_MIN);
		return 1;
	}
	if (mp->t_cwl < MCU_T_CWL_MIN) {
		debug("ERROR *** t_cwl=%d < %d not supported.\n", 
						mp->t_cwl, MCU_T_CWL_MIN);
		return 1;
	}
	if (mp->t_crl > MCU_T_CRL_MAX) {
		debug("ERROR *** t_crl=%d > %d not supported.\n", 
						mp->t_crl, MCU_T_CRL_MAX);
		return 1;
	}
	if (mp->t_cwl > MCU_T_CWL_MAX) {
		debug("ERROR *** t_cwl=%d > %d not supported.\n", 
						mp->t_cwl, MCU_T_CWL_MAX);
		return 1;
	}

	blby2 = (mp->burst_len) / 2;
	al = tp->additive_latency;
	tck_ps = tp->tCKmin_X_ps;

	relax_time_en = mcu->mcu_ud.ud_relax_time_en;
	relax_margin_0 = (mcu->mcu_ud.ud_tmargin >> 12) & 0xF;
	relax_margin_1 = (mcu->mcu_ud.ud_tmargin >> 8) & 0xF;
	relax_rd2rd_margin = (mcu->mcu_ud.ud_tmargin >> 4) & 0xF;
	relax_rd2wr_margin = (mcu->mcu_ud.ud_tmargin >> 20) & 0xF;
	relax_wr2wr_margin = mcu->mcu_ud.ud_tmargin & 0xF;
	relax_wr2rd_margin = (mcu->mcu_ud.ud_tmargin >> 16) & 0xF;

	if (mcu->mcu_params.dimm_type == LRDIMM){ 
		if (relax_wr2rd_margin < 1) 
			relax_wr2rd_margin = 1;
		if (mcu->mcu_params.speed > 1334) {
			debug("LRDIMM - DDRMARGIN re-adjusted to at least "
				"min values 0x410000 required for LRDIMM\n");
			if (relax_rd2wr_margin < 4) 
				relax_rd2wr_margin = 4;
		} else {
			debug("LRDIMM - DDRMARGIN re-adjusted to at least "
				"min values 0x310000 required for LRDIMM\n");
			if (relax_rd2wr_margin < 3) 
				relax_rd2wr_margin = 3;
		}
	}
	debug("\tMargin 0: %x - Margin 1: %x\n\t"
		"RD2RD Margin: %x - RD2WR Margin: %x - "
		"WR2WR Margin: %x - WR2RD Margin: %x\n",
		relax_margin_0, relax_margin_1, relax_rd2rd_margin,
		relax_rd2wr_margin, relax_wr2wr_margin, relax_wr2rd_margin);

	/* Note: APM_SIM printf fails with 3+ args */
	debug("\t[latency: cl=%d cwl=%d ", cl, cwl);
	debug("crl=%d bl=%d, ", crl, blby2 * 2);
	debug("al=%d, tck=%d]\n", al, tck_ps);
	if (relax_time_en)
		debug("\t[Timing relaxation by: %d, %d]\n\n", 
				relax_margin_0, relax_margin_1);

	/* BANK-ACTPRE: val = trasmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRAS_ps, tck_ps);
	calc1 = calc0;
	actpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1 * 2);
	mp->bank_actpre = cycls + margin - 1;
	debug2("\tMCU[%d] BANK-ACTPRE=0x%0X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actpre, calc0, calc1, cycls, margin);

	/* BANK-RDPRE: val = trtpmin*mtb / tck_ps + al [csr = (val/2)-1] */
	calc0 = max(4, rdiv(tp->tRTP_ps, tck_ps));
	rdpre = calc0;
	calc1 = calc0 + al;
	rdpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_rdpre = cycls + margin - 1;
	debug2("\tMCU[%d] BANK-RDPRE=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_rdpre, calc0, calc1, cycls, margin);

	/* BANK-WRPRE: val = twrmin*mtb / tck_ps + al + cwl + blby2 [csr = (val/2)-1] */
	calc0 = rdiv(tp->tWR_ps, tck_ps);
	wrpre = calc0;
	calc1 = calc0 + al + cwl + blby2;
	wrpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_wrpre = cycls + margin - 1;
	debug2("\tMCU[%d] BANK-WRPRE=0x%X [%d->%d>%d(+%d)]\n", 
			mcu->id, mp->bank_wrpre, calc0, calc1, cycls, margin);

	/* BANK-PREACT: val = trpmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRP_ps, tck_ps);
	preact = calc0;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0);
	mp->bank_preact = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-PREACT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_preact, calc0, calc1, cycls, margin);

	/* BANK-ACTACT: val = trcmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRC_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1 * 2);
	mp->bank_actact = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-ACTACT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actact, calc0, calc1, cycls, margin);

	/* BANK-RDAACT: val = rdpre+preact + al [csr = (val/2)-1] */
	calc0 = rdpre + preact;
	calc1 = calc0 + al;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1);
	mp->bank_rdaact = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-RDAACT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_rdaact, calc0, calc1, cycls, margin);

	/* BANK-WRAACT: val = wrpre+preact + al + cwl + blby2 [csr = (val/2)-1] */
	calc0 = wrpre + preact;
	calc1 = calc0 + al + cwl + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1);
	mp->bank_wraact = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-WRAACT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_wraact, calc0, calc1, cycls, margin);

	/* BANK-ACTRD: val = trcdmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRCD_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actrd = cycls + margin - 1;
	debug2("\tMCU[%d] BANK-ACTRD=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actrd, calc0, calc1, cycls, margin);

	/* BANK-ACTWR: val = trcdmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRCD_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actwr = cycls + margin - 1;
	debug2("\tMCU[%d] BANK-ACTWR=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actwr, calc0, calc1, cycls, margin);

	/* BANK-ACTRDA: val = actpre1 - rdpre1 [csr = (val/2)-1] */
	calc0 = actpre1 < rdpre1 ? 0 : (actpre1 - rdpre1);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actrda = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-ACTRDA=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actrda, calc0, calc1, cycls, margin);

	/* BANK-ACTWRA: val = actpre1 - wrpre1  [csr = (val/2)-1] */
	calc0 = actpre1 < wrpre1 ? 0 : (actpre1 - wrpre1);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actwra = cycls - 1 + margin;
	debug2("\tMCU[%d] BANK-ACTWRA=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->bank_actwra, calc0, calc1, cycls, margin);

	/* RANK-ACTACT: val = trrdmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRRD_ps, tck_ps);
	calc1 = max(4, calc0);
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0);
	mp->rank_actact = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-ACTACT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_actact, calc0, calc1, cycls, margin);

	/* RANK-RDRD: val = (tCCD = 4)  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_rd2rd_margin;
	mp->rank_rdrd = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-RDRD=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_rdrd, calc0, calc1, cycls, margin);

	/* RANK-WRWR: val = (tCCD = 4)  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_wr2wr_margin;
	mp->rank_wrwr = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-WRWR=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_wrwr, calc0, calc1, cycls, margin);

	/* RANK-RDWR: val = (tCCD = 4) + cl + 2 - cwl  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0 + cl + 2 - cwl;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_rd2wr_margin;
	mp->rank_rdwr = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-RDWR=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_rdwr, calc0, calc1, cycls, margin);

	/* RANK-WRRD: val = twtrmin*mtb / tck_ps + cwl + blby2  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tWTR_ps, tck_ps);
	calc1 = max(4, calc0) + cwl + blby2;	// + 1 Phy delay min lane to max
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_wr2rd_margin;
	mp->rank_wrrd = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-WRRD=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_wrrd, calc0, calc1, cycls, margin);

	/* RANK-ACTFAW: val = tfawmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tFAW_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 2 + relax_time_en * (relax_margin_0 * 4);
	mp->rank_actfaw = cycls - 1 + margin;
	debug2("\tMCU[%d] RANK-ACTFAW=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_actfaw, calc0, calc1, cycls, margin);

	/* SYS-RDRD: val = phy_rtr + blby2  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_RTR_VAL;
	calc1 = calc0 + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = mcu->mcu_ud.ud_sysrd2rdmargin;
	mp->sys_rdrd = cycls - 1 + margin;
	debug2("\tMCU[%d] SYS-RDRD=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->sys_rdrd, calc0, calc1, cycls, margin);

	/* SYS-WRWR: val = phy_wtw + blby2  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_WTW_VAL;
	calc1 = calc0 + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = mcu->mcu_ud.ud_syswr2wrmargin;
	mp->sys_wrwr = cycls - 1 + margin;
	debug2("\tMCU[%d] SYS-WRWR=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->sys_wrwr, calc0, calc1, cycls, margin);

	/* SYS-RDWR: val = phy_rtw + cl + blby2 - cwl  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_RTW_VAL;
	calc1 = calc0 + cl + blby2 - cwl;
	cycls = max(2, rdiv(calc1, 2));
	if (mp->activeslots > 1)
		margin = 2;
	margin += mcu->mcu_ud.ud_sysrd2wrmargin;
	mp->sys_rdwr = cycls - 1 + margin;
	debug2("\tMCU[%d] SYS-RDWR=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->sys_rdwr, calc0, calc1, cycls, margin);

	/* SYS-WRRD: val = phy_wtr + cwl + blby2 - cl  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_WTR_VAL;
	calc1 = calc0 + cwl + blby2 - cl;
	cycls = max(2, rdiv(calc1, 2));
	if (mp->activeslots > 1)
		margin = 2;
	margin += mcu->mcu_ud.ud_syswr2rdmargin;
	mp->sys_wrrd = cycls - 1 + margin;
	debug2("\tMCU[%d] SYS-WRRD=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->sys_wrrd, calc0, calc1, cycls, margin);

	/* RANK-REFACTREF: val = trfcmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRFC_ps, tck_ps);
	trfcmin = calc0;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		// + relax_time_en*(relax_margin+1);
	mp->rank_refactref = cycls - 1 + margin;
	debug2("\tMCU[%d] SYS-REFACTREF=0x%X [%d->%d->%d(+%d)]\n", 
		mcu->id, mp->rank_refactref, calc0, calc1, cycls, margin);

	/* REFINT: val = refrrate*8*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->refresh_rate_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		// + relax_time_en*(relax_margin+1);
	mp->rank_refint = cycls - 1 + margin;
	debug2("\tMCU[%d] REFINT=0x%X [%d->%d->%d(+%d)]\n", 
			mcu->id, mp->rank_refint, calc0, calc1, cycls, margin);

	/* REF-BURST-CNT: val = refint*4  [csr = (val/2)-1] */
	mp->rank_ref_burst_cnt = 4;
	debug("\tMCU[%d] REF-BURST-CNT=0x%X \n", mcu->id,
	      mp->rank_ref_burst_cnt);

	debug("\n");
	ranks = 0;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((mp->activeslots >> i) & 0x1)) {
			continue;
		}
		ranks += (mcu->dimm_params[i].n_ranks);
	}

	/* ODT Table update */
	mcu_odt_config(mcu);

	/* Mode Register Programming */
	switch (wrpre) {
	case 5:
			wrrec = 0x1;
			break;
	case 6:
			wrrec = 0x2;
			break;
	case 7:
			wrrec = 0x3;
			break;
	case 8:
			wrrec = 0x4;
			break;
	case 9:
	case 10:
			wrrec = 0x5;
			break;
	case 11:
	case 12:
			wrrec = 0x6;
			break;
	case 13:
	case 14:
			wrrec = 0x7;
			break;
	default:
			wrrec = 0;
	}

	if (cl >= 12) 
		mr0 = 0x100 | ((wrrec & 0x7) << 9) | 
					(0x70 & (0x10 * (cl - 12))) | 0x4;
	else
		mr0 = 0x100 | ((wrrec & 0x7) << 9) | (0x70 & ((cl - 4) << 4));
#if defined(LRDIMM_INPHI_MR_CONFIG)
	if (mcu->mcu_params.dimm_type == LRDIMM) 
		mr0 |= LRDIMM_MR0_MBCONFIG;
#endif
	mp->mode_reg[0] = mr0;
	debug2("\tMCU[%d] MR0: 0x%04X [wrore:%d, wrrecovery:%d]\n", 
						mcu->id, mr0, wrpre, wrrec);
	if ((mcu->mcu_params.activeslots == 0x3) && 
			(mcu->mcu_params.dimm_type == UDIMM)) {
		mr1_rttnom = DIMM_MR1_RTTNOM_U2R2S0_DIC;
		mr1_rttnom_s1 = DIMM_MR1_RTTNOM_U2R2S1_DIC;
#if defined(LRDIMM_INPHI_MR_CONFIG)
	} else if (mcu->mcu_params.dimm_type == LRDIMM) {
		/* Rtt_Nom = 001(RZQ/4), ODIC = 01 (RZQ/7) */
		mr1_rttnom = LRDIMM_MR1_MBCONFIG;       
                mr1_rttnom_s1 = mr1_rttnom;

#endif
	} else if (mcu->mcu_params.all_DIMMs_quadrank == 1) {
		mr1_rttnom = DIMM_MR1_RTTNOM_R4R_DIC;
		mr1_rttnom_s1 = mr1_rttnom;
	} else if (ranks == 1) {
		mr1_rttnom = DIMM_MR1_RTTNOM_U1R_DIC;
		mr1_rttnom_s1 = mr1_rttnom;
	} else {
		mr1_rttnom = DIMM_MR1_RTTNOM_U2R_DIC;
		mr1_rttnom_s1 = mr1_rttnom;
	}
	mcu->mcu_params.rttnom_s0 = mr1_rttnom;
	mcu->mcu_params.rttnom_s1 = mr1_rttnom_s1;

	mr1 = mr1_rttnom;
	if (al == (cl - 2))
		mr1 |= (2 << 3);
	else if (al == (cl - 1))
		mr1 |= (1 << 3);
	mp->mode_reg[1] = mr1;
	for (iir = 0; iir < 8; iir++)
		mp->rank_mr1[iir] = mr1;
	debug("\tMCU[%d] MR1: 0x%04X\n", mcu->id, mr1);

	mr2 = (cwl - 5) << 3;
	if ((mcu->mcu_params.activeslots == 0x3) &&
			(mcu->mcu_params.dimm_type == UDIMM)) 
		mr2_rttwr = DIMM_MR2_RTTWR_U2R2S;
#if defined(LRDIMM_INPHI_MR_CONFIG)
	else if (mcu->mcu_params.dimm_type == LRDIMM) 
		/* Rtt_WR = 10 (RZQ/2) */	
		mr2_rttwr = (LRDIMM_MR2_MBCONFIG & 0x3) >> 9;
#endif
	else if (mcu->mcu_params.all_DIMMs_quadrank == 1)
		mr2_rttwr = DIMM_MR2_RTTWR_R4R;
	else if (ranks == 1)
		mr2_rttwr = DIMM_MR2_RTTWR_U1R;
	else
		mr2_rttwr = DIMM_MR2_RTTWR_U2R1S;
	if (mr2_rttwr)
		mr2 |= (mr2_rttwr & 0x3) << 9;
#if defined(LRDIMM_INPHI_MR_CONFIG)
	if (mcu->mcu_params.dimm_type == LRDIMM) 
		/* Rtt_WR = 10 (RZQ/2) */
		mr2 |= LRDIMM_MR2_MBCONFIG;
#endif

	mp->mode_reg[2] = mr2;
	for (iir = 0; iir < 8; iir++)
		mp->rank_mr2[iir] = mr2;
	debug("\tMCU[%d] MR2: 0x%04X\n", mcu->id, mr2);

	mr3 = 0x0;
	mp->mode_reg[3] = mr3;
	debug("\tMCU[%d] MR3: 0x%04X\n", mcu->id, mr3);

	/* Wr Lvl RttNom setting (/2 /4 /6 only!) */
	temp = getRttNomfromMR1(mp->mode_reg[1]);
	switch (temp) {
	case 1:
		mcu->mcu_params.rttnom_wrlvl = temp;
		break;
	case 2:
		mcu->mcu_params.rttnom_wrlvl = temp;
		break;
	case 3:
		mcu->mcu_params.rttnom_wrlvl = temp;
		break;
	case 4:
		mcu->mcu_params.rttnom_wrlvl = 3;
		break;
	case 5:
		mcu->mcu_params.rttnom_wrlvl = 3;
		break;
	default:
		mcu->mcu_params.rttnom_wrlvl = 2;
		break;
	}
	/* For QRDIMM single slot, using RTTnom 40Ohm for wrlvl training */	
	if ((mcu->mcu_params.activeslots == 0x1) &&
			mcu->mcu_params.all_DIMMs_quadrank)
		mcu->mcu_params.rttnom_wrlvl = 3;
	
	/* clk200us calc */
	debug("\n");
	mp->clks200us = rdiv((200 + 4) * 1000000U / 2, (tck_ps));
	debug("\tMCU[%d] clks200us: 0x%06X\n", mcu->id, mp->clks200us);
	mp->clks500us = rdiv((500 + 10) * 1000000U / 2, (tck_ps));
	debug("\tMCU[%d] clks500us: 0x%06X\n", mcu->id, mp->clks500us);
	mp->clks6us = rdiv((((6) * 1000000U / 2) + 200000U), (tck_ps));
	debug("\tMCU[%d] clks6us: 0x%06X\n", mcu->id, mp->clks6us);
	mp->clkstxpr = 0x1FF;
	debug2("\tMCU[%d] clkstxpr: 0x%06X [trfcmin:%d]\n", 
					mcu->id, mp->clkstxpr, trfcmin);
	return 0;
}

unsigned int getRttNomfromMR1(unsigned int mr1val)
{
	unsigned int bout = 0;

	bout = ((mr1val >> 7) & 0x4) |	/* A9 */
		((mr1val >> 5) & 0x2) |	/* A6 */
		((mr1val >> 2) & 0x1);	/* A2 */
	return bout;
}

unsigned int putRttNomintoMR1(unsigned int mr1val, unsigned int rttnom)
{
	unsigned int bout = 0;

	bout = (mr1val & 0xFDBB) | ((rttnom & 0x4) << 7) |	/* A9 */
		((rttnom & 0x2) << 5) |				/* A6 */
		((rttnom & 0x1) << 2);				/* A2 */
	return bout;
}

