#define USB_PIPE_PCS_STATUS0           0x0004
#define  CFG_O_PIPE_CLOCK_VALID        0x10000000
#define USB_PIPE_PCS_CTL0              0x000c
#define USB_SDS_CTL0                   0x0018
#define  USB_SDS_CTL0_CFG_I_CUSTOMER_PIN_MODE_SET(dst, src) \
		(((dst) & ~0x0007FFFF) | (((u32)(src) << 0) & 0x0007FFFF))
#define USB_PIPE_PCS_PD_RDY_I          (1 << 31)
#define USB_SDS_CMU_STATUS0            0x0020
#define LOS_PARAM                      0xa0
#define  LOS_PARAM_TH_CNTOFF_GEN12_SET(dst, src) \
		(((dst) & ~0x0f000000) | (((u32)(src) << 24) & 0x0f000000))
#define LOS_PARAM_TH_CNTON_GEN12_SET(dst, src) \
		(((dst) & ~0xf0000000) | (((u32)(src) << 28) & 0xf0000000))
#define SERDES_CONTROL3                0x108
#define SERDES_CONTROL4                0x10c
#define EFIFO_CONTROL0                 0x12c
#define  EFIFO_CONTROL0_WM_SELECT_USB_SET(dst, src) \
		(((dst) & ~0x0000000f) | ((u32)(src) & 0x0000000f))
#define  EFIFO_CONTROL0_BUF_DEPTH_USB_SET(dst, src) \
		(((dst) & ~0x0003e000) | (((u32)(src) << 13) & 0x0003e000))
#define EFIFO_CONTROL1                 0x130
#define  EFIFO_CONTROL1_INIT_BUF_FILL_USB_SET(dst, src) \
		(((dst) & ~0x0000001f) | ((u32)(src) & 0x0000001f))
#define DFE_CONTROL0                   0x134
#define DETECT_CONTROL                 0x15c
#define USB_PCIE_CTRL                  0x164
#define  ONE_CNT_TH_SET(dst, src) \
		(((dst) & ~0x0000ffff) | ((u32)(src) & 0x0000ffff))
#define  ONE_CNT_CMP_TH_SET(dst, src) \
		(((dst) & ~0x0000ffff) | ((u32)(src) & 0x0000ffff))
#define  SEL_CDR_OVR_LN_SET(dst, src) \
		(((dst) & ~0x0000000f) | ((u32)(src) & 0x0000000f))

/*
 * Wait for register has specific value or timeout.
 * Time unit is us.
 */
u32 xgene_wait_register(void *reg, u32 mask, u32 val,
		int interval, unsigned long timeout)
{
	unsigned long deadline = 0;
	u32 dt;

	dt = readl(reg);
	while (((dt & mask) != val) && (deadline < timeout)) {
		usleep_range(interval, interval*2);
		dt = readl(reg);
		deadline += interval;
	}

	return dt;
}

static void xgene_xhci_cmu_cfg(struct xgene_phy_ctx *ctx,
		enum cmu_type_t cmu_type)
{
	u32 dt;

	/* TX ready delay */
	cmu_rd(ctx, cmu_type, CMU_REG12, &dt);
	dt = CMU_REG12_STATE_DELAY9_SET(dt, 0x5);
	cmu_wr(ctx, cmu_type, CMU_REG12, dt);

	cmu_rd(ctx, cmu_type, CMU_REG13, &dt);
	dt = CMU_REG13_STATE_DELAY1_SET(dt, 0xf);
	dt = CMU_REG13_STATE_DELAY2_SET(dt, 0xa);
	dt = CMU_REG13_STATE_DELAY3_SET(dt, 0x2);
	dt = CMU_REG13_STATE_DELAY4_SET(dt, 0x2);
	cmu_wr(ctx, cmu_type, CMU_REG13, dt);

	cmu_rd(ctx, cmu_type, CMU_REG14, &dt);
	dt = CMU_REG14_STATE_DELAY5_SET(dt, 0x2);
	dt = CMU_REG14_STATE_DELAY6_SET(dt, 0x2);
	dt = CMU_REG14_STATE_DELAY7_SET(dt, 0xa);
	dt = CMU_REG14_STATE_DELAY8_SET(dt, 0xf);
	cmu_wr(ctx, cmu_type, CMU_REG14, dt);

	cmu_rd(ctx, cmu_type, CMU_REG0, &dt);
	dt =  CMU_REG0_CAL_COUNT_RESOL_SET(dt, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, dt);

	cmu_rd(ctx, cmu_type, CMU_REG1, &dt);
	dt = CMU_REG1_PLL_CP_SET(dt, 0x1);
	dt = CMU_REG1_PLL_CP_SEL_SET(dt, 0x2);
	dt = CMU_REG1_PLL_MANUALCAL_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG1, dt);
	cmu_rd(ctx, cmu_type, CMU_REG1, &dt);

	cmu_rd(ctx, cmu_type, CMU_REG2, &dt);
	dt = CMU_REG2_PLL_LFRES_SET(dt, 0x2);
	dt = CMU_REG2_PLL_FBDIV_SET(dt, 0x31);
	cmu_wr(ctx, cmu_type, CMU_REG2, dt);

	cmu_rd(ctx, cmu_type, CMU_REG3, &dt);
	dt = CMU_REG3_VCOVARSEL_SET(dt, 0xf);
	dt = CMU_REG3_VCO_MOMSEL_INIT_SET(dt, 0x10);
	cmu_wr(ctx, cmu_type, CMU_REG3, dt);

	cmu_rd(ctx, cmu_type, CMU_REG5, &dt);
	dt = CMU_REG5_PLL_LFCAP_SET(dt, 0);
	dt = CMU_REG5_PLL_LFSMCAP_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG5, dt);

	cmu_rd(ctx, cmu_type, CMU_REG6, &dt);
	dt = CMU_REG6_PLL_VREGTRIM_SET(dt, 0x0);
	dt = CMU_REG6_MAN_PVT_CAL_SET(dt, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG6, dt);

	cmu_rd(ctx, cmu_type, CMU_REG16, &dt);
	dt = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(dt, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG16, dt);

	cmu_rd(ctx, cmu_type, CMU_REG30, &dt);
	dt = CMU_REG30_LOCK_COUNT_SET(dt, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG30, dt);

	cmu_wr(ctx, cmu_type, CMU_REG31, 0xF);

	cmu_rd(ctx, cmu_type, CMU_REG32, &dt);
	dt = CMU_REG32_IREF_ADJ_SET(dt, 0x3);
	dt = CMU_REG32_PVT_CAL_WAIT_SEL_SET(dt, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG32, dt);

	cmu_rd(ctx, cmu_type, CMU_REG34, &dt);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(dt, 0x2);
	dt = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(dt, 0xa);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(dt, 0x2);
	dt = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(dt, 0xa);
	cmu_wr(ctx, cmu_type, CMU_REG34, dt);

	cmu_rd(ctx, cmu_type, CMU_REG37, &dt);
	dt = CMU_REG37_CAL_DONE_OVR_SET(dt, 0xf);
	dt = CMU_REG37_SEARCH_DONE_OVR_SET(dt, 0xf);
	cmu_wr(ctx, cmu_type, CMU_REG37, dt);
}

static void xgene_xhci_rxtx_cfg(struct xgene_phy_ctx *ctx)
{
	u32 dt;
	int i;

	serdes_rd(ctx, 0, RXTX_REG147, &dt);
	dt = RXTX_REG147_STMC_OVERRIDE_SET(dt, 0x6);
	serdes_wr(ctx, 0, RXTX_REG147, dt);

	/* Workaround to prevent serdes power down to p1 */
	serdes_rd(ctx, 0, RXTX_REG27, &dt);
	dt = RXTX_REG27_RXPD_CONFIG_SET(dt, 0x1);
	serdes_wr(ctx, 0, RXTX_REG27, dt);

	serdes_rd(ctx, 0, RXTX_REG0, &dt);
	dt = RXTX_REG0_CTLE_EQ_HR_SET(dt, 0x10);
	dt = RXTX_REG0_CTLE_EQ_QR_SET(dt, 0x10);
	dt = RXTX_REG0_CTLE_EQ_FR_SET(dt, 0x10);
	serdes_wr(ctx, 0, RXTX_REG0, dt);

	serdes_rd(ctx, 0, RXTX_REG1, &dt);
	dt = RXTX_REG1_RXACVCM_SET(dt, 0x7);
	dt = RXTX_REG1_CTLE_EQ_SET(dt, 0x1c);
	dt = RXTX_REG1_RXVREG1_SET(dt, 0x3);
	serdes_wr(ctx, 0, RXTX_REG1, dt);

	serdes_rd(ctx, 0, RXTX_REG2, &dt);
	dt = RXTX_REG2_TX_FIFO_ENA_SET(dt, 0x1);
	dt = RXTX_REG2_RESETB_TXD_SET(dt, 0x1);
	dt = RXTX_REG2_BIST_ENA_TX_SET(dt, 0x0);
	dt = RXTX_REG2_TX_INV_SET(dt, 0x0);
	dt = RXTX_REG2_VTT_ENA_SET(dt, 0x1);
	dt = RXTX_REG2_VTT_SEL_SET(dt, 0x1);
	dt = RXTX_REG2_RESETB_TERM_SET(dt, 0x0);
	dt = RXTX_REG2_TX_RCVDET_SEL_SET(dt , 3);
	serdes_wr(ctx, 0, RXTX_REG2, dt);

	serdes_rd(ctx, 0, RXTX_REG4, &dt);
	dt = RXTX_REG4_TX_LOOPBACK_BUF_EN_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG4, dt);

	serdes_rd(ctx, 0, RXTX_REG5, &dt);
	dt = RXTX_REG5_TX_CN2_SET(dt, 0x0);
	dt = RXTX_REG5_TX_CP1_SET(dt, 0xf);
	dt = RXTX_REG5_TX_CN1_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG5, dt);

	serdes_rd(ctx, 0, RXTX_REG6, &dt);
	dt = RXTX_REG6_TXAMP_ENA_SET(dt, 0x1);
	dt = RXTX_REG6_TXAMP_CNTL_SET(dt, 0xf);
	dt = RXTX_REG6_TX_IDLE_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG6, dt);

	serdes_rd(ctx, 0, RXTX_REG7, &dt);
	dt = RXTX_REG7_RESETB_RXD_SET(dt, 0x1);
	dt = RXTX_REG7_LP_ENA_CTLE_SET(dt, 0x0);
	dt = RXTX_REG7_BIST_ENA_RX_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG7, dt);

	serdes_rd(ctx, 0, RXTX_REG8, &dt);
	dt = RXTX_REG8_CDR_LOOP_ENA_SET(dt, 0x1);
	dt = RXTX_REG8_CDR_BYPASS_RXLOS_SET(dt, 0x0);
	dt = RXTX_REG8_SSC_ENABLE_SET(dt, 0x1);
	dt = RXTX_REG8_SD_DISABLE_SET(dt, 0);
	dt = RXTX_REG8_SD_VREF_SET(dt, 0x4);
	serdes_wr(ctx, 0, RXTX_REG8, dt);

	serdes_rd(ctx, 0, RXTX_REG11, &dt);
	dt = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG11, dt);

	serdes_rd(ctx, 0, RXTX_REG12, &dt);
	dt = RXTX_REG12_RX_DET_TERM_ENABLE_SET(dt, 0x0);
	dt = RXTX_REG12_LATCH_OFF_ENA_SET(dt, 0x1);
	dt = RXTX_REG12_RX_INV_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG12, dt);

	serdes_rd(ctx, 0, RXTX_REG26, &dt);
	dt = RXTX_REG26_BLWC_ENA_SET(dt, 0x1);
	serdes_wr(ctx, 0, RXTX_REG26, dt);

	serdes_wr(ctx, 0, RXTX_REG31, 0x0);

	serdes_rd(ctx, 0, RXTX_REG61, &dt);
	dt = RXTX_REG61_LOADFREQ_SHIFT_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG61, dt);

	for (i = 0; i < 9; i++) {
		serdes_rd(ctx, 0, RXTX_REG81 + i*2, &dt);
		dt = RXTX_REG81_MU_DFE1_SET(dt, 0xe);
		dt = RXTX_REG81_MU_DFE2_SET(dt, 0xe);
		dt = RXTX_REG81_MU_DFE3_SET(dt, 0xe);
		serdes_wr(ctx, 0, RXTX_REG81 + i*2, dt);
	}

	for (i = 0; i < 3; i++) {
		serdes_rd(ctx, 0, RXTX_REG96 + i*2, &dt);
		dt = RXTX_REG96_MU_FREQ1_SET(dt, 0x10);
		dt = RXTX_REG96_MU_FREQ2_SET(dt, 0x10);
		dt = RXTX_REG96_MU_FREQ3_SET(dt, 0x10);
		serdes_wr(ctx, 0, RXTX_REG96 + i*2, dt);
	}

	for (i = 0; i < 3; i++) {
		serdes_rd(ctx, 0, RXTX_REG99 + i*2, &dt);
		dt = RXTX_REG99_MU_PHASE1_SET(dt, 0x7);
		dt = RXTX_REG99_MU_PHASE2_SET(dt, 0x7);
		dt = RXTX_REG99_MU_PHASE3_SET(dt, 0x7);
		serdes_wr(ctx, 0, RXTX_REG99 + i*2, dt);
	}

	serdes_rd(ctx, 0, RXTX_REG102, &dt);
	dt = RXTX_REG102_FREQLOOP_LIMIT_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG102, dt);

	serdes_rd(ctx, 0, RXTX_REG125, &dt);
	dt = RXTX_REG125_PQ_REG_SET(dt, 0x8);
	dt = RXTX_REG125_PHZ_MANUAL_SET(dt, 0x1);
	serdes_wr(ctx, 0, RXTX_REG125, dt);

	serdes_rd(ctx, 0, RXTX_REG127, &dt);
	dt = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG127, dt);

	serdes_rd(ctx, 0, RXTX_REG128, &dt);
	dt = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(dt, 0x3);
	serdes_wr(ctx, 0, RXTX_REG128, dt);

	serdes_rd(ctx, 0, RXTX_REG145, &dt);
	dt = RXTX_REG145_RXDFE_CONFIG_SET(dt, 0x3);
	dt = RXTX_REG145_TX_IDLE_SATA_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG145, dt);

	serdes_wr(ctx, 0, RXTX_REG28, 0x7);

	for (i = 0; i < 4; i++)
		serdes_wr(ctx, 0, RXTX_REG148 + i*2, 0xffff);

	serdes_rd(ctx, 0, RXTX_REG144, &dt);
	dt = RXTX_REG144_USE_RAWSD_SET(dt, 0x0);
	serdes_wr(ctx, 0, RXTX_REG144, dt);
}

static void xgene_xhci_phy_tuning(struct xgene_phy_ctx *ctx)
{
	u32 dt;

	pipe_rd(ctx, DFE_CONTROL0, &dt);
	dt = SEL_CDR_OVR_LN_SET(dt, 0x4);
	pipe_wr(ctx, DFE_CONTROL0, dt);

	pipe_rd(ctx, DETECT_CONTROL, &dt);
	dt = ONE_CNT_TH_SET(dt, 0xffff);
	pipe_wr(ctx, DETECT_CONTROL, dt);

	pipe_rd(ctx, USB_PCIE_CTRL, &dt);
	dt = ONE_CNT_CMP_TH_SET(dt, 0x50);
	pipe_wr(ctx, USB_PCIE_CTRL, dt);

	pipe_rd(ctx, EFIFO_CONTROL0, &dt);
	dt = EFIFO_CONTROL0_WM_SELECT_USB_SET(dt, 0xb);
	dt = EFIFO_CONTROL0_BUF_DEPTH_USB_SET(dt, 0x1f);
	pipe_wr(ctx, EFIFO_CONTROL0, dt);

	pipe_rd(ctx, EFIFO_CONTROL1, &dt);
	dt = EFIFO_CONTROL1_INIT_BUF_FILL_USB_SET(dt, 0x4);
	pipe_wr(ctx, EFIFO_CONTROL1, dt);

	pipe_rd(ctx, SERDES_CONTROL3, &dt);
	dt = dt & 0xf7ffffff;
	pipe_wr(ctx, SERDES_CONTROL3, dt);

	pipe_rd(ctx, LOS_PARAM, &dt);
	dt = LOS_PARAM_TH_CNTON_GEN12_SET(dt, 0xf);
	dt = LOS_PARAM_TH_CNTOFF_GEN12_SET(dt, 0x8);
	pipe_wr(ctx, LOS_PARAM, dt);
}

static void xgene_xhci_phy_ssc_enable(struct xgene_phy_ctx *ctx,
		enum cmu_type_t cmu_type)
{
	u32 dt;

	cmu_rd(ctx, cmu_type, CMU_REG35, &dt);
	dt = CMU_REG35_PLL_SSC_MOD_SET(dt, 0x5F);
	cmu_wr(ctx, cmu_type, CMU_REG35, dt);

	/* Enable SSC, set vertical step and DSM value */
	cmu_rd(ctx, cmu_type, CMU_REG36, &dt);
	dt = CMU_REG36_PLL_SSC_VSTEP_SET(dt, 33);
	dt = CMU_REG36_PLL_SSC_EN_SET(dt, 1);
	dt = CMU_REG36_PLL_SSC_DSMSEL_SET(dt, 1);
	cmu_wr(ctx, cmu_type, CMU_REG36, dt);

	/* Reset the PLL */
	cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
	cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Force VCO calibration to restart */
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		CMU_REG32_FORCE_VCOCAL_START_MASK);
}

static int xgene_xhci_power_sequence_enable(struct xgene_phy_ctx *ctx)
{
	void *csr_base = ctx->sds_base;
	u32 val;

	/* Enable PIPE power sequence */
	dev_dbg(ctx->dev, "Enable power sequence:\n");
	val = readl(csr_base + USB_PIPE_PCS_CTL0);
	val |= USB_PIPE_PCS_PD_RDY_I;
	writel(val, csr_base + USB_PIPE_PCS_CTL0);

	/* Polling PCS_STATUS0 until PIPE clock valid status, maximum 1000ms */
	val = xgene_wait_register(csr_base + USB_PIPE_PCS_STATUS0,
		CFG_O_PIPE_CLOCK_VALID, CFG_O_PIPE_CLOCK_VALID, 100, 1000000);
	if (val & CFG_O_PIPE_CLOCK_VALID)
		dev_dbg(ctx->dev, "PIPE clock ready\n");
	else {
		dev_err(ctx->dev, "Timeout waiting for PIPE clock ready\n");
		return -1;
	}
	return 0;
}

static int apm_usb_superspeed_supported(void)
{
#ifdef APM_CONFIG_USB3_ENABLE
	return 1;
#else
	return 0;
#endif
}

static int xgene_phy_hw_init_usb(struct xgene_phy_ctx *ctx,
		enum clk_type_t clk_type, int ssc_enable)
{
	u32 dt;
	enum cmu_type_t cmu_type = PHY_CMU;
	void *sds_base = ctx->sds_base;
	int rc = 0;

	if (!apm_usb_superspeed_supported())
		return -ENODEV;

	dev_dbg(ctx->dev, "Initialize USB PHY\n");

	dev_dbg(ctx->dev, "Set the customer pin mode to USB\n");
	dt = readl(sds_base + USB_SDS_CTL0);
	dt = USB_SDS_CTL0_CFG_I_CUSTOMER_PIN_MODE_SET(dt, 0x0D21);
	writel(dt, sds_base + USB_SDS_CTL0);

	rc = xgene_xhci_power_sequence_enable(ctx);
	xgene_xhci_phy_tuning(ctx);
	xgene_xhci_rxtx_cfg(ctx);
	xgene_phy_cfg_cmu_clk_type(ctx, cmu_type, clk_type);
	xgene_xhci_cmu_cfg(ctx, cmu_type);
	if (ssc_enable)
		xgene_xhci_phy_ssc_enable(ctx, cmu_type);

	return rc;
}
