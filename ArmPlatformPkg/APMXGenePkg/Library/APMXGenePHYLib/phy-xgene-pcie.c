/*
 * APM X-Gene PCIE PHY driver
 *
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.	The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * This driver produces IDE_CONTROLLER_INIT protocol for APM X-Gene SATA
 * controllers.
 */

#define SDS0_CMU_STATUS0                0x2c
#define SDS1_CMU_STATUS0                0x64

#define PCIECORE_CTLANDSTATUS		0x50

#define SERDES_CONTROL3			0x108
#define SERDES_CONTROL4			0x10c
#define DFE_CONTROL0			0x134
#define DETECT_CONTROL			0x15c
#define USB_PCIE_CTRL			0x164
#define PIPECTLREG			0x1b0
#define  EQ_TX_PARAMS_VALID_SET(dst, src) \
		(((dst) & ~0x01000000) | (((u32) (src) << 24) & 0x01000000))
#define  PIPECTLREG_PHY_EQ_TX_FS_SET(dst, src) \
		(((dst) & ~0xfc0000) | (((u32) (src) << 0x12) & 0x00fc0000))
#define  PIPECTLREG_PHY_EQ_TX_LF_SET(dst, src) \
		(((dst) & ~0x3f000) | (((u32) (src) << 0xc) & 0x3f000))
#define  PIPECTLREG_PHY_EQ_TX_MAX_PRE_SET(dst, src) \
		(((dst) & ~0xfc0) | (((u32) (src) << 0x6) & 0xfc0))
#define  PIPECTLREG_PHY_EQ_TX_MAX_POST_SET(dst, src) \
		(((dst) & ~0x3f) | (((u32) (src)) & 0x3f))
#define  BYPASS_RECEIVER_DETECTION_SET(dst, src) \
		(((dst) & ~0x10000000) | (((u32) (src) << 0x1c) & 0x10000000))
#define ONE_CNT_TH_MASK			0x0000ffff
#define ONE_CNT_TH_SET(dst, src) \
		(((dst) & ~0x0000ffff) | ((u32)(src) & 0x0000ffff))
#define ONE_CNT_CMP_TH_MASK		0x0000ffff
#define ONE_CNT_CMP_TH_SET(dst, src) \
		(((dst) & ~0x0000ffff) | ((u32)(src) & 0x0000ffff))
#define SEL_CDR_OVR_LN_MASK		0x0000000f
#define SEL_CDR_OVR_LN_SET(dst, src) \
		(((dst) & ~0x0000000f) | ((u32)(src) & 0x0000000f))
#define TX_AMP_EN_LN0_MASK		0x00000040
#define TX_AMP_EN_LN0_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32)(src) << 0x6) & 0x00000040))
#define TX_AMP_LN0_MASK			0x00000780
#define TX_AMP_LN0_SET(dst, src) \
		(((dst) & ~0x00000780) | (((u32)(src) << 0x7) & 0x00000780))
#define TX_AMP_EN_LN1_MASK		0x00010000
#define TX_AMP_EN_LN1_SET(dst, src) \
		(((dst) & ~0x00010000) | (((u32)(src) << 0x10) & 0x00010000))
#define TX_AMP_LN1_MASK			0x001e0000
#define TX_AMP_LN1_SET(dst, src) \
		(((dst) & ~0x001e0000) | (((u32)(src) << 0x11) & 0x001e0000))

#define PIPE_REGS_LOS_PARAM		0x00a0
#define  CNTON_GEN12_SET(dst, src) \
		(((dst) & ~0xf0000000) | (((u32)(src) << 0x1c) & 0xf0000000))
#define  CNTOFF_GEN12_SET(dst, src) \
		(((dst) & ~0x0f000000) | (((u32)(src) << 0x18) & 0x0f000000))
#define  CNTON_GEN3_SET(dst, src) \
		(((dst) & ~0x00f00000) | (((u32)(src) << 0x14) & 0x00f00000))
#define  CNTOFF_GEN3_SET(dst, src) \
		(((dst) & ~0x000f0000) | (((u32)(src) << 0x10) & 0x000f0000))
#define PIPE_REGS_EFIFO_CONTROL0 	0x012c
#define  BUF_DEPTH_PCI_SET(dst, src) \
		(((dst) & ~0x00001f00) | (((u32)(src) << 0x8) & 0x00001f00))
#define PIPE_REGS_PIPE_CONTROL		0x0004
#define  WMSELECT_SET(dst, src) \
		(((dst) & ~0x0000001e) | (((u32)(src) << 0x1) & 0x0000001e))

#define PLL_RESETB_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))

#define MIDR_EL1_REV_MASK	0x0000000F

static void xgene_phy_cfg_pipe(struct xgene_phy_ctx *ctx)
{
	u32 val;
	int i;

	/* Set receiver detection threshold */
	pipe_rd(ctx, DETECT_CONTROL, &val);
	val = ONE_CNT_TH_SET(val, 0xffff);
	pipe_wr(ctx, DETECT_CONTROL, val);

	pipe_rd(ctx, USB_PCIE_CTRL, &val);
	val = ONE_CNT_CMP_TH_SET(val, 0x50);
	pipe_wr(ctx, USB_PCIE_CTRL, val);

	/* Set speed for lanes - Gen3 */
	for (i = 0; i < ctx->lane; i++) {
		pipe_rd(ctx, DFE_CONTROL0 + i * 4, &val);
		val = SEL_CDR_OVR_LN_SET(val, 0x7);
		pipe_wr(ctx, DFE_CONTROL0 + i * 4, val);
	}

	/* Tx amp for lane 0 has different bit location than other lanes */
	pipe_rd(ctx, SERDES_CONTROL3, &val);
	val = TX_AMP_EN_LN0_SET(val, 0x1);
	val = TX_AMP_LN0_SET(val, 0xf);
	pipe_wr(ctx, SERDES_CONTROL3, val);

	for (i = 0; i < ctx->lane - 1; i++) {
		pipe_rd(ctx, SERDES_CONTROL4 + i * 4, &val);
		val = TX_AMP_EN_LN1_SET(val, 0x1);
		val = TX_AMP_LN1_SET(val, 0xf);
		pipe_wr(ctx, SERDES_CONTROL4 + i * 4, val);
	}

	/* Remove SD glitch */
	pipe_rd(ctx, PIPE_REGS_LOS_PARAM, &val);
	val = CNTON_GEN12_SET(val, 0xf);
	val = CNTOFF_GEN12_SET(val, 0x8);
	val = CNTON_GEN3_SET(val, 0xf);
	val = CNTOFF_GEN3_SET(val, 0x8);
	pipe_wr(ctx, PIPE_REGS_LOS_PARAM, val);

	pipe_wr(ctx, 0x0c, 0x2c0);

	pipe_rd(ctx, PIPE_REGS_EFIFO_CONTROL0, &val);
	if (ctx->lane > 1)
		if (xgene_is_preB0())
			val = BUF_DEPTH_PCI_SET(val, 0x1a);
		else
			val = BUF_DEPTH_PCI_SET(val, 0x10);
	else
		val = BUF_DEPTH_PCI_SET(val, 0xF);
	pipe_wr(ctx, PIPE_REGS_EFIFO_CONTROL0, val);

	pipe_rd(ctx, PIPE_REGS_PIPE_CONTROL, &val);
	val = WMSELECT_SET(val, 0x6);
	pipe_wr(ctx, PIPE_REGS_PIPE_CONTROL, val);
}

static void xgene_phy_pcie_cfg_cmu_core(struct xgene_phy_ctx *ctx,
					enum cmu_type_t cmu_type)
{
	u32 dt;

	cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
	dt = CMU_REG0_PCIEGEN3_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG0, dt);

	cmu_rd(ctx, cmu_type, CMU_REG1, &dt);
	dt = CMU_REG1_PLL_CP_SET(dt, 0xf);
	dt = CMU_REG1_PLL_CP_SEL_SET(dt, 0xc);
	cmu_wr(ctx, cmu_type, CMU_REG1, dt);

	cmu_rd(ctx, cmu_type, CMU_REG3, &dt);
	dt = CMU_REG3_VCOVARSEL_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG3, dt);

	cmu_rd(ctx, cmu_type, CMU_REG2, &dt);
	dt = CMU_REG2_PLL_LFRES_SET(dt, 0x2);
	dt = CMU_REG2_PLL_FBDIV_SET(dt, 0x31);
	cmu_wr(ctx, cmu_type, CMU_REG2, dt);

	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = CMU_REG5_PLL_LFCAP_SET(dt, 0);
	dt = CMU_REG5_PLL_LFSMCAP_SET(dt, 0);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG4, &dt);
	dt = CMU_REG4_VCOVARSEL_PCIE_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG4, dt);

	cmu_rd(ctx, cmu_type, CMU_REG32, &dt);
	dt = CMU_REG32_IREF_ADJ_SET(dt, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG32, dt);

	cmu_rd(ctx, cmu_type, CMU_REG1, &dt);
	dt = CMU_REG1_PLL_MANUALCAL_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG1, dt);

	cmu_rd(ctx, cmu_type, CMU_REG3, &dt);
	dt = CMU_REG3_VCO_MOMSEL_INIT_SET(dt, 0x10);
	cmu_wr(ctx, cmu_type, CMU_REG3, dt);

	cmu_rd(ctx, cmu_type, CMU_REG4, &dt);
	dt = CMU_REG4_MOMSEL_INIT_PCIE_SET(dt, 0x10);
	cmu_wr(ctx, cmu_type, CMU_REG4, dt);

	cmu_rd(ctx, cmu_type, CMU_REG34, &dt);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(dt, 0x2);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(dt, 0xa);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(dt, 0x2);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(dt, 0xa);
	cmu_wr(ctx, cmu_type, CMU_REG34, dt);

	cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
	dt = CMU_REG0_CAL_COUNT_RESOL_SET(dt, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, dt);

	cmu_rd(ctx, cmu_type, CMU_REG16, &dt);
	dt = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(dt, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG16, dt);

	cmu_rd(ctx, cmu_type, CMU_REG30, &dt);
	dt = CMU_REG30_REFDIV_GEN3_SET(dt, 0x1);
	dt = CMU_REG30_LOCK_COUNT_SET(dt, 0x3);
	dt = CMU_REG30_FBDIV_GEN3_SET(dt, 0x4f);
	cmu_wr(ctx, cmu_type, CMU_REG30, dt);

	cmu_rd(ctx, cmu_type, CMU_REG12, &dt);
	dt = CMU_REG12_STATE_DELAY9_SET(dt, 0x2);
	cmu_wr(ctx, cmu_type, CMU_REG12, dt);

	cmu_rd(ctx, cmu_type, CMU_REG13, &dt);
	dt = CMU_REG13_STATE_DELAY1_SET(dt, 0xf);
	dt = CMU_REG13_STATE_DELAY2_SET(dt, 0x2);
	dt = CMU_REG13_STATE_DELAY3_SET(dt, 0xd);
	dt = CMU_REG13_STATE_DELAY4_SET(dt, 0xb);
	cmu_wr(ctx, cmu_type, CMU_REG13, dt);

	cmu_rd(ctx, cmu_type, CMU_REG14, &dt);
	dt = CMU_REG14_STATE_DELAY5_SET(dt, 0x2);
	dt = CMU_REG14_STATE_DELAY6_SET(dt, 0x2);
	dt = CMU_REG14_STATE_DELAY7_SET(dt, 0x7);
	dt = CMU_REG14_STATE_DELAY8_SET(dt, 0xa);
	cmu_wr(ctx, cmu_type, CMU_REG14, dt);

	cmu_rd(ctx, cmu_type, CMU_REG32, &dt);
	dt = CMU_REG32_PVT_CAL_WAIT_SEL_SET(dt, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG32, dt);

	cmu_rd(ctx, cmu_type, CMU_REG31, &dt);
	dt = CMU_REG31_OVERRIDE_CH3_SET(dt, 0x1);
	dt = CMU_REG31_OVERRIDE_CH2_SET(dt, 0x1);
	dt = CMU_REG31_OVERRIDE_CH1_SET(dt, 0x1);
	dt = CMU_REG31_OVERRIDE_CH0_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG31, dt);

	cmu_rd(ctx, cmu_type, CMU_REG37, &dt);
	dt = CMU_REG37_CAL_DONE_OVR_SET(dt, 0xf);
	dt = CMU_REG37_SEARCH_DONE_OVR_SET(dt, 0xf);
	cmu_wr(ctx, cmu_type, CMU_REG37, dt);

	cmu_rd(ctx, cmu_type, CMU_REG27, &dt);
	dt = CMU_REG27_VOLT_SEL_CH0_SET(dt, 0x2);
	dt = CMU_REG27_VOLT_SEL_CH1_SET(dt, 0x2);
	dt = CMU_REG27_VOLT_SEL_CH2_SET(dt, 0x2);
	dt = CMU_REG27_VOLT_SEL_CH3_SET(dt, 0x2);
	cmu_wr(ctx, cmu_type, CMU_REG27, dt);
}

static void xgene_phy_pcie_cfg_rx(struct xgene_phy_ctx *ctx, u32 lane)
{
	u32 dt;
	u32 addr;
	u32 i;

	serdes_rd(ctx, lane, RXTX_REG147, &dt);
	dt = RXTX_REG147_STMC_OVERRIDE_SET(dt, 0x6);
	serdes_wr(ctx, lane, RXTX_REG147, dt);

	serdes_rd(ctx, lane, RXTX_REG27, &dt);
	dt = RXTX_REG27_RXPD_CONFIG_SET(dt, 0x1);
	serdes_wr(ctx, lane, RXTX_REG27, dt);

	serdes_rd(ctx, lane, RXTX_REG2, &dt);
	dt = RXTX_REG2_RESETB_TERM_SET(dt, 0x0);
	dt = RXTX_REG2_VTT_ENA_SET(dt, 0x1);
	dt = RXTX_REG2_VTT_SEL_SET(dt, 0x1);
	serdes_wr(ctx, lane, RXTX_REG2, dt);

	serdes_rd(ctx, lane, RXTX_REG1, &dt);
	dt = RXTX_REG1_RXACVCM_SET(dt, 0x7);
	serdes_wr(ctx, lane, RXTX_REG1, dt);

	serdes_rd(ctx, lane, RXTX_REG12, &dt);
	dt = RXTX_REG12_RX_DET_TERM_ENABLE_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG12, dt);

	addr = RXTX_REG148;
	for (i = 0; i < 4; i++) {
		serdes_rd(ctx, lane, addr, &dt);
		dt = 0xffff;
		serdes_wr(ctx, lane, addr, dt);
		addr += 2;
	}

	serdes_rd(ctx, lane, RXTX_REG1, &dt);
	if (xgene_is_preB0())
		dt = RXTX_REG1_CTLE_EQ_SET(dt, 0x1c);
	else
		dt = RXTX_REG1_CTLE_EQ_SET(dt, 0x10);
	serdes_wr(ctx, lane, RXTX_REG1, dt);

	serdes_rd(ctx, lane, RXTX_REG0, &dt);
	dt = RXTX_REG0_CTLE_EQ_FR_SET(dt, 0x1C);
	dt = RXTX_REG0_CTLE_EQ_QR_SET(dt, 0x1C);
	dt = RXTX_REG0_CTLE_EQ_HR_SET(dt, 0x1C);
	serdes_wr(ctx, lane, RXTX_REG0, dt);

	serdes_rd(ctx, lane, RXTX_REG12, &dt);
	dt = RXTX_REG12_LATCH_OFF_ENA_SET(dt, 0x1);
	serdes_wr(ctx, lane, RXTX_REG12, dt);

	serdes_rd(ctx, lane, RXTX_REG128, &dt);
	dt = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(dt, 0x3);
	serdes_wr(ctx, lane, RXTX_REG128, dt);

	serdes_rd(ctx, lane, RXTX_REG8, &dt);
	dt = RXTX_REG8_CDR_LOOP_ENA_SET(dt, 0x1);
	dt = RXTX_REG8_CDR_BYPASS_RXLOS_SET(dt, 0x0);
	dt = RXTX_REG8_SD_VREF_SET(dt, 0x4);
	serdes_wr(ctx, lane, RXTX_REG8, dt);

	serdes_rd(ctx, lane, RXTX_REG125, &dt);
	if (xgene_is_preB0())
		dt = RXTX_REG125_PQ_REG_SET(dt, 0xA);
	else
		dt = RXTX_REG125_PQ_REG_SET(dt, 0x11);
	dt = RXTX_REG125_PHZ_MANUAL_SET(dt, 0x1);
	serdes_wr(ctx, lane, RXTX_REG125, dt);

	serdes_rd(ctx, lane, RXTX_REG11, &dt);
	dt = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG11, dt);

	serdes_rd(ctx, lane, RXTX_REG61, &dt);
	dt = RXTX_REG61_LOADFREQ_SHIFT_SET(dt, ctx->ssc ? 0x0 : 0x1);
	serdes_wr(ctx, lane, RXTX_REG61, dt);

	serdes_rd(ctx, lane, RXTX_REG102, &dt);
	dt = RXTX_REG102_FREQLOOP_LIMIT_SET(dt, ctx->ssc ? 0x0 : 0x3);
	serdes_wr(ctx, lane, RXTX_REG102, dt);

	serdes_rd(ctx, lane, RXTX_REG8, &dt);
	dt = RXTX_REG8_SSC_ENABLE_SET(dt, ctx->ssc ? 0x1 : 0x0);
	serdes_wr(ctx, lane, RXTX_REG8, dt);

	addr = RXTX_REG96;
	for (i = 0; i < 3; i++) {
		serdes_rd(ctx, lane, addr, &dt);
		dt = RXTX_REG96_MU_FREQ1_SET(dt, 0x10);
		dt = RXTX_REG96_MU_FREQ2_SET(dt, 0x10);
		dt = RXTX_REG96_MU_FREQ3_SET(dt, 0x10);
		serdes_wr(ctx, lane, addr, dt);
		addr += 2;
	}

	addr = RXTX_REG99;
	serdes_rd(ctx, lane, addr, &dt);
	dt = RXTX_REG99_MU_PHASE1_SET(dt, 0x6);
	dt = RXTX_REG99_MU_PHASE2_SET(dt, 0x6);
	dt = RXTX_REG99_MU_PHASE3_SET(dt, 0x6);
	serdes_wr(ctx, lane, addr, dt);

	addr = RXTX_REG100;
	serdes_rd(ctx, lane, addr, &dt);
	dt = RXTX_REG100_MU_PHASE4_SET(dt, 0x6);
	dt = RXTX_REG100_MU_PHASE5_SET(dt, 0x6);
	dt = RXTX_REG100_MU_PHASE6_SET(dt, 0x6);
	serdes_wr(ctx, lane, addr, dt);

	addr = RXTX_REG101;
	serdes_rd(ctx, lane, addr, &dt);
	dt = RXTX_REG101_MU_PHASE7_SET(dt, 0x6);
	dt = RXTX_REG101_MU_PHASE8_SET(dt, 0x6);
	dt = RXTX_REG101_MU_PHASE9_SET(dt, 0x6);
	serdes_wr(ctx, lane, addr, dt);

	serdes_rd(ctx, lane, RXTX_REG8, &dt);
	dt = RXTX_REG8_SD_DISABLE_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG8, dt);

	serdes_rd(ctx, lane, RXTX_REG26, &dt);
	dt = RXTX_REG26_BLWC_ENA_SET(dt, 0x1);
	serdes_wr(ctx, lane, RXTX_REG26, dt);

	addr = RXTX_REG81;
	for (i = 0; i < 9; i++) {
		serdes_rd(ctx, lane, addr, &dt);
		dt = RXTX_REG81_MU_DFE1_SET(dt, 0xe);
		dt = RXTX_REG81_MU_DFE2_SET(dt, 0xe);
		dt = RXTX_REG81_MU_DFE3_SET(dt, 0xe);
		serdes_wr(ctx, lane, addr, dt);
		addr += 2;
	}

	serdes_rd(ctx, lane, RXTX_REG145, &dt);
	dt = RXTX_REG145_RXDFE_CONFIG_SET(dt, 0x3);
	serdes_wr(ctx, lane, RXTX_REG145, dt);
	if (xgene_is_preB0())
		serdes_wr(ctx, lane, RXTX_REG28, 0x3);
	else {
		serdes_rd(ctx, lane, RXTX_REG92, &dt);
		dt = RXTX_REG92_MU_BCA9_SET(dt, 0xa);
		serdes_wr(ctx, lane, RXTX_REG92, dt);
		serdes_wr(ctx, lane, RXTX_REG28, 0x7);
	}

	serdes_rd(ctx, lane, RXTX_REG7, &dt);
	dt = RXTX_REG7_RESETB_RXD_SET(dt, 0x1);
	dt = RXTX_REG7_LP_ENA_CTLE_SET(dt, 0x0);
	dt = RXTX_REG7_BIST_ENA_RX_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG7, dt);

	serdes_rd(ctx, lane, RXTX_REG12, &dt);
	dt = RXTX_REG12_RX_INV_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG12, dt);
}

static void xgene_phy_pcie_cfg_tx(struct xgene_phy_ctx *ctx, u32 lane)
{
	u32 dt;

	serdes_rd(ctx, lane, RXTX_REG2, &dt);
	dt = RXTX_REG2_TX_FIFO_ENA_SET(dt, 0x1);
	dt = RXTX_REG2_RESETB_TXD_SET(dt, 0x1);
	dt = RXTX_REG2_BIST_ENA_TX_SET(dt, 0x0);
	dt = RXTX_REG2_TX_INV_SET(dt, 0x0);
	dt = RXTX_REG2_TX_RCVDET_SEL_SET(dt, 3);
	serdes_wr(ctx, lane, RXTX_REG2, dt);

	serdes_rd(ctx, lane, RXTX_REG6, &dt);
	dt = RXTX_REG6_TXAMP_ENA_SET(dt, 0x1);
	dt = RXTX_REG6_TXAMP_CNTL_SET(dt, 0xf);
	dt = RXTX_REG6_TX_IDLE_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG6, dt);

	serdes_rd(ctx, lane, RXTX_REG5, &dt);
	dt = RXTX_REG5_TX_CN2_SET(dt, 0x2);
	dt = RXTX_REG5_TX_CP1_SET(dt, 0xf);
	dt = RXTX_REG5_TX_CN1_SET(dt, 0x2);
	serdes_wr(ctx, lane, RXTX_REG5, dt);

	serdes_rd(ctx, lane, RXTX_REG4, &dt);
	dt = RXTX_REG4_TX_LOOPBACK_BUF_EN_SET(dt, 0x0);
	dt = RXTX_REG4_COUNTER_TIME_SEL_CP_SET(dt, 0x7);
	dt = RXTX_REG4_COUNTER_TIME_SEL_CN_SET(dt, 0x7);
	serdes_wr(ctx, lane, RXTX_REG4, dt);

	serdes_rd(ctx, lane, RXTX_REG145, &dt);
	dt = RXTX_REG145_TX_IDLE_SATA_SET(dt, 0x0);
	serdes_wr(ctx, lane, RXTX_REG145, dt);
}

static void xgene_phy_pcie_cfg(struct xgene_phy_ctx *ctx)
{
	u32 i;
	u32 j;
	int lane;
	int loop = ctx->lane <= 4 ? 1 : ctx->lane / 4;

	for (i = 0; i < loop; i++) {
		xgene_phy_pcie_cfg_cmu_core(ctx, PHY_CMU + i);
		lane = ctx->lane <= 4 ? ctx->lane : 4;
		for (j = 0; j < lane; j++) {
			xgene_phy_pcie_cfg_rx(ctx, i * 4 + j);
			xgene_phy_pcie_cfg_tx(ctx, i * 4 + j);
		}
	}
}

static int xgene_phy_pcie_wait_pll_lock(struct xgene_phy_ctx *ctx)
{
	void __iomem *base = ctx->sds_base;
	u32 dt1 = 0, dt2 = 0x7;

	/* wait for at least 10 ms per CMU */
	int try = 10000;
	do {
		dt1 = readl(base + SDS0_CMU_STATUS0);
		if (ctx->lane > 4) {
			dt2 = readl(base + SDS1_CMU_STATUS0);
		}
		if (((dt1 & 0x7) == 0x7) && ((dt2 & 0x7) == 0x7)) {
			dev_dbg(ctx->dev, "PHY PLL calibration successful\n");
			return 0;
		}
		usleep_range(1, 10);
	} while (try--);
	dev_err(ctx->dev, "PHY PLL calibration failed - error Status: 0x%X 0x%X\n",
			(dt1 & 0x7), (dt2 & 0x7));
	return -ENODEV;
}
static int xgene_phy_pcie_vco_cal(struct xgene_phy_ctx *ctx,
		enum cmu_type_t cmu_type)
{
	u32 dt;
	int try = 10000;

	do {
		cmu_rd(ctx, cmu_type, CMU_REG32, &dt);
		dt = CMU_REG32_VCOCAL_START_SET(dt, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG32, dt);

		cmu_rd(ctx, cmu_type, CMU_REG32, &dt);
		dt = CMU_REG32_VCOCAL_START_SET(dt, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG32, dt);

			cmu_rd(ctx, cmu_type, CMU_REG7, &dt);
			if (CMU_REG7_PLL_CALIB_DONE_RD(dt))
				break;
		usleep_range(1, 10);
		if (try == 5000) {
			/*
		 * If calibration failed, power down and reset PLL.
		 * Do calibration again
		 */
		cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
		dt = CMU_REG0_PDOWN_SET(dt, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG0, dt);

		cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
		dt = PLL_RESETB_SET(dt, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG5, dt);

		cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
		dt = PLL_RESETB_SET(dt, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG5, dt);

			cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
			dt = CMU_REG0_PDOWN_SET(dt, 0x0);
			cmu_wr(ctx, cmu_type, CMU_REG0, dt);
		}
	} while (try--);

	if (!CMU_REG7_PLL_CALIB_DONE_RD(dt)) {
		dev_err(ctx->dev, "PHY PLL calibration failed\n");
		return -ENODEV;
	}
	return 0;
}

static int xgene_phy_pcie_get_momsel(struct xgene_phy_ctx *ctx,
				     enum cmu_type_t cmu_type, u32 *momsel,
				     u32 *momsel_pcie)
{
	u32 dt;

	/* Reset PLL to clear any previous status flag */
	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = PLL_RESETB_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = PLL_RESETB_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG33, &dt);
	dt = CMU_REG33_CUST_MODE_INV_SET(dt, 0xffff);
	cmu_wr(ctx, cmu_type, CMU_REG33, dt);

	cmu_rd(ctx, cmu_type, CMU_REG30, &dt);
	dt = CMU_REG30_PCIE_MODE_SET(dt, 0x0);
	cmu_wr(ctx,  cmu_type, CMU_REG30, dt);

	cmu_rd(ctx, cmu_type, CMU_REG1, &dt);
	dt = CMU_REG1_PLL_MANUALCAL_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG1, dt);

	cmu_rd(ctx, cmu_type, CMU_REG2, &dt);
	dt = CMU_REG2_PLL_REFDIV_SET(dt, 0x1);
	dt = CMU_REG2_PLL_LFRES_SET(dt, 0x2);
	dt = CMU_REG2_PLL_FBDIV_SET(dt, 0x4f);
	cmu_wr(ctx, cmu_type, CMU_REG2, dt);

	cmu_rd(ctx, cmu_type, CMU_REG9, &dt);
	dt = CMU_REG9_PLL_POST_DIVBY2_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG9, dt);

	cmu_rd(ctx, cmu_type, CMU_REG34, &dt);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(dt, 0x8);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(dt, 0x8);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(dt, 0x5);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(dt, 0x5);
	cmu_wr(ctx, cmu_type, CMU_REG34, dt);

	cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
	dt = CMU_REG0_CAL_COUNT_RESOL_SET(dt, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, dt);

	if (xgene_phy_pcie_vco_cal(ctx, cmu_type) < 0) {
		return -ENODEV;
	}

	cmu_rd(ctx, cmu_type, CMU_REG19, &dt);
	*momsel_pcie = CMU_REG19_PLL_VCOMOMSEL_RD(dt);

	/* The delay is required for Serdes Calibration
	 * to complete successfully.
	 */
	usleep_range(20000, 20000);

	/* reset PLL to clear any previous status flag */
	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = PLL_RESETB_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = PLL_RESETB_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG2, &dt);
	dt = CMU_REG2_PLL_REFDIV_SET(dt, 0x0);
	dt = CMU_REG2_PLL_FBDIV_SET(dt, 0x31);
	cmu_wr(ctx, cmu_type, CMU_REG2, dt);

	cmu_rd(ctx, cmu_type, CMU_REG9, &dt);
	dt = CMU_REG9_PLL_POST_DIVBY2_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG9, dt);

	if (xgene_phy_pcie_vco_cal(ctx, cmu_type) < 0) {
		return -ENODEV;
	}

	/* check for 10ms */
	cmu_rd(ctx, cmu_type, CMU_REG19, &dt);
	*momsel = CMU_REG19_PLL_VCOMOMSEL_RD(dt);

	cmu_rd(ctx, cmu_type, CMU_REG2, &dt);
	dt = CMU_REG2_PLL_FBDIV_SET(dt, 0x31);
	cmu_wr(ctx, cmu_type, CMU_REG2, dt);

	cmu_rd(ctx, cmu_type, CMU_REG9, &dt);
	dt = CMU_REG9_PLL_POST_DIVBY2_SET(dt, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG9, dt);

	cmu_rd(ctx, cmu_type, CMU_REG33, &dt);
	dt = CMU_REG33_CUST_MODE_INV_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG33, dt);

	return 0;
}

static void xgene_phy_pcie_pll_cal(struct xgene_phy_ctx *ctx)
{
	int loop = ctx->lane <= 4 ? 1 : ctx->lane / 4;
	u32 momsel_pcie = 0;
	u32 momsel = 0;
	u32 dt;
	u32 j;

	for (j = 0; j < loop; j++) {
		xgene_phy_pcie_get_momsel(ctx, PHY_CMU + j, &momsel,
					  &momsel_pcie);
		cmu_rd(ctx, PHY_CMU + j, CMU_REG4, &dt);
		dt = CMU_REG4_MANMOMSEL_PCIE_SET(dt, momsel_pcie);
		cmu_wr(ctx, PHY_CMU + j, CMU_REG4, dt);

		cmu_rd(ctx, PHY_CMU + j, CMU_REG3, &dt);
		dt = CMU_REG3_VCO_MANMOMSEL_SET(dt, momsel);
		cmu_wr(ctx, PHY_CMU + j, CMU_REG3, dt);

		cmu_rd(ctx, PHY_CMU + j, CMU_REG1, &dt);
		dt = CMU_REG1_PLL_MANUALCAL_SET(dt, 0x1);
		cmu_wr(ctx, PHY_CMU + j, CMU_REG1, dt);
	}
	if (!preA3Chip)
		return;
	/* Only required for pre-A3 silicon */
	for (j = 0; j < loop; j++) {
		cmu_rd(ctx, PHY_CMU + j, CMU_REG6, &dt);
		dt = CMU_REG6_PLL_VREGTRIM_SET(dt, 0x0);
		dt = CMU_REG6_MAN_PVT_CAL_SET(dt, 0x1);
		cmu_wr(ctx, PHY_CMU + j, CMU_REG6, dt);
	}
}

static void xgene_phy_pcie_manual_cal(struct xgene_phy_ctx *ctx)
{
	u32 dt;
	u32 i, j;
	int loop;

	loop = ctx->lane <= 4 ? 1 : ctx->lane / 4;

	xgene_phy_pcie_pll_cal(ctx);

	if (!preA3Chip)
		return;
	/* Only required for pre-A3 chip */
	for (j = 0; j < loop; j++) {
		for (i = 0; i < 4; i++) {
			/* Termination calibration */
			cmu_rd(ctx, PHY_CMU + j, CMU_REG17, &dt);
			dt = CMU_REG17_RESERVED_7_SET(dt, i);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG17, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG17, &dt);
			dt = CMU_REG17_PVT_CODE_R2A_SET(dt, 0x12);
			dt = CMU_REG17_TERM_MAN_ENA_SET(dt, 0x1);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG17, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG17, &dt);
			dt = CMU_REG17_TERM_MAN_ENA_SET(dt, 0x0);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG17, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG17, &dt);
			dt = CMU_REG17_RESERVED_7_SET(dt, i);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG17, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG17, &dt);
			dt = CMU_REG17_PVT_CODE_R2A_SET(dt, 0x29);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG17, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG16, &dt);
			dt = CMU_REG16_DN_MAN_ENA_SET(dt, 0x1);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG16, dt);

			cmu_rd(ctx, PHY_CMU + j, CMU_REG16, &dt);
			dt = CMU_REG16_DN_MAN_ENA_SET(dt, 0x0);
			cmu_wr(ctx, PHY_CMU + j, CMU_REG16, dt);
		}
	}
}

static int xgene_phy_pcie_wait_phy_rdy(struct xgene_phy_ctx *ctx)
{
	int try = 10000;
	u32 val;

	if (!ctx->core_base)
		return 0;

	/* Check for 10 ms */
	do {
		val = readl(ctx->core_base + PCIECORE_CTLANDSTATUS);
		if ((val & 0xff) == 0)
			return 0;
		usleep_range(1, 10);
	} while (try--);
	return -1;
};

int xgene_phy_hw_init_pcie(struct xgene_phy_ctx *ctx, enum clk_type_t clk_type,
		int ssc_enable)
{
	void *csr_base = ctx->sds_base;
	u32 val;
	int rc;

	val = readl(csr_base + SATA_ENET_SDS_CTL0);
	val &= ~0x1000;
	writel(val, csr_base + SATA_ENET_SDS_CTL0);
	if (ctx->lane == 8 && clk_type == CLK_EXT_DIFF) {
		/* Configure the second PHY clock macro for external clock */
		cmu_rd(ctx, PHY2_CMU, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x1);
		cmu_wr(ctx, PHY2_CMU, CMU_REG0, val);
	}

	val = readl(csr_base + PIPECTLREG);
	val = EQ_TX_PARAMS_VALID_SET(val, 0);
	writel(val, csr_base + PIPECTLREG);

	val = readl(csr_base + PIPECTLREG);
	val = PIPECTLREG_PHY_EQ_TX_FS_SET(val, 0x36);
	val = PIPECTLREG_PHY_EQ_TX_LF_SET(val, 0x10);
	val = PIPECTLREG_PHY_EQ_TX_MAX_PRE_SET(val, 0x6);
	val = PIPECTLREG_PHY_EQ_TX_MAX_POST_SET(val, 0xf);
	val = EQ_TX_PARAMS_VALID_SET(val, 1);
	writel(val, csr_base + PIPECTLREG);

	dev_dbg(ctx->dev, "Set the customer pin mode to PCIe\n");
	val = readl(csr_base + SATA_ENET_SDS_CTL0);
	val = REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_SET(val, 0x0d25);
	writel(val, csr_base + SATA_ENET_SDS_CTL0);

	xgene_phy_cfg_pipe(ctx);
	xgene_phy_pcie_cfg(ctx);

	val = readl(ctx->clk_base);
	writel(val & ~0x100, ctx->clk_base);

	rc = xgene_phy_pcie_wait_pll_lock(ctx);
	if (rc)
		return rc;

	rc = xgene_phy_pcie_wait_phy_rdy(ctx);
	if (rc)
		return rc;

	xgene_phy_pcie_manual_cal(ctx);

	return 0;
}
