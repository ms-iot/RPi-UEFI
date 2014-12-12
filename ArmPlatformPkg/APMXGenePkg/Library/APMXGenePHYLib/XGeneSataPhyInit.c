/*
 * APM X-Gene SATA host controller driver
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
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include "phy-xgene.h"

#define HOST_IRQ_STAT					0x08	/* interrupt status */

/* Some default Serdes parameters */
#define DEFAULT_SATA_TXBOOST_GAIN_SSD	{ 0x2, 0x2, 0x2 }
#define DEFAULT_SATA_TXBOOST_GAIN	{ 0x3, 0x3, 0x3 }
#define DEFAULT_SATA_TXEYEDIRECTION	{ 0x0, 0x0, 0x0 }
#define DEFAULT_SATA_TXEYETUNING	{ 0x8, 0x8, 0x8 }
#define DEFAULT_SATA_SPD_SEL		{ 0x1, 0x3, 0x7 }
#define DEFAULT_SATA_TXAMP		{ 0x5, 0x5, 0x5 }
#define DEFAULT_SATA_TXCN1		{ 0x2, 0x2, 0x2 }
#define DEFAULT_SATA_TXCN2		{ 0x0, 0x0, 0x0 }
#define DEFAULT_SATA_TXCP1		{ 0xa, 0xa, 0xa }
#define DEFAULT_SATA_DFE		{ 0x0, 0x0, 0x0 }


/* Max # of disk per a controller */
#define MAX_AHCI_CHN_PERCTR	 	2

#define SATA_ENET_MUX_OFFSET            0x00007000
#define SATA_SERDES_OFFSET		0x0000A000
#define SATA_CLK_OFFSET			0x0000C000
#define SATA_DIAG_OFFSET		0x0000D000
#define SATA_GLB_OFFSET			0x0000D850
#define SATA_SHIM_OFFSET		0x0000E000
#define SATA_MASTER_OFFSET		0x0000F000
#define SATA_PORT0_OFFSET		0x00000100
#define SATA_PORT1_OFFSET		0x00000180

/* SATA Clock/Reset CSR */
#define SATACLKENREG			0x00000000
#define SATASRESETREG     0x00000004
#define  SATA0_CORE_CLKEN		0x00000002
#define  SATA1_CORE_CLKEN		0x00000004
#define  SATA_MEM_RESET_MASK		0x00000020
#define  SATA_MEM_RESET_RD(src)		(((src) & 0x00000020) >> 5)
#define  SATA_SDS_RESET_MASK		0x00000004
#define  SATA_CSR_RESET_MASK		0x00000001
#define  SATA_CORE_RESET_MASK		0x00000002
#define  SATA_PMCLK_RESET_MASK		0x00000010
#define  SATA_PCLK_RESET_MASK		0x00000008

/* MUX CSR */
#define SATA_ENET_CONFIG_REG		0x00000000
#define  CFG_SATA_ENET_SELECT_MASK	0x00000001

/* SATA host controller CSR */
#define SLVRDERRATTRIBUTES		0x00000000
#define SLVWRERRATTRIBUTES		0x00000004
#define MSTRDERRATTRIBUTES		0x00000008
#define MSTWRERRATTRIBUTES		0x0000000c
#define BUSCTLREG			0x00000014
#define IOFMSTRWAUX			0x00000018
#define INTSTATUSMASK			0x0000002c
#define ERRINTSTATUS			0x00000030
#define ERRINTSTATUSMASK		0x00000034

/* SATA host AHCI CSR */
#define PORTCFG				0x000000a4
#define  PORTADDR_SET(dst, src) \
		(((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))
#define PORTPHY1CFG			0x000000a8
#define  PORTPHY1CFG_FRCPHYRDY_SET(dst, src) \
		(((dst) & ~0x00100000) | (((u32)(src) << 0x14) & 0x00100000))
#define PORTPHY2CFG			0x000000ac
#define PORTPHY3CFG			0x000000b0
#define PORTPHY4CFG			0x000000b4
#define PORTPHY5CFG			0x000000b8
#define  PORTPHY5CFG_RTCHG_SET(dst, src) \
		(((dst) & ~0xfff00000) | (((u32)(src) << 0x14) & 0xfff00000))
#define SCTL0				0x0000012C
#define PORTAXICFG			0x000000bc
#define  PORTAXICFG_EN_CONTEXT_SET(dst, src) \
		(((dst) & ~0x01000000) | (((u32)(src) << 0x18) & 0x01000000))
#define  PORTAXICFG_OUTTRANS_SET(dst, src) \
		(((dst) & ~0x00f00000) | (((u32)(src) << 0x14) & 0x00f00000))
#define PTC 				0xc8
#define PTC_RXWM_SET(dst, src)		\
		(((dst) & ~0x0000007f) | (((u32) (src) << 0) & 0x0000007f))

/* SATA host controller slave CSR */
#define INT_SLV_TMOMASK			0x00000010

/* Global Base Address     */
#define SATA01_CSR_REGS_I_BASE_ADDR                     0x01f210000ULL
#define SATA23_CSR_REGS_I_BASE_ADDR                     0x01f220000ULL
#define SATA_X2_CSR_REGS_I_BASE_ADDR                    0x01f230000ULL
#define PCIE2_CSR_BASE 					0x1f2d0000ULL

/* SATA global diagnostic CSR */
#define CFG_MEM_RAM_SHUTDOWN		0x00000070
#define BLOCK_MEM_RDY			0x00000074
#define DET0_RD(src)      (((src) & 0x0000000f))
#define DET0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32) (src)) & 0x0000000f))
#define X0_RD(src)        (((src) & 0x04000000) >> 26)
#define W0_RD(src)        (((src) & 0x00040000) >> 18)

#define SATA_SPD_SEL_GEN3		0x7
#define SATA_SPD_SEL_GEN2		0x3
#define SATA_SPD_SEL_GEN1		0x1

struct xgene_ahci_context {
	u8 cid;				/* Controller ID */
	int irq;
	void __iomem *csr_base;		/* CSR base address of IP */
	void __iomem *mmio_base;	/* AHCI I/O base address */

	struct xgene_phy_ctx phy;
};

static int xgene_ahci_init_memram(struct xgene_ahci_context *ctx)
{
	void __iomem *diagcsr = ctx->csr_base + SATA_DIAG_OFFSET;
	void *clk_base = ctx->csr_base + SATA_CLK_OFFSET;
	int try;
	u32 val;

	val = readl(clk_base + SATASRESETREG);
	val |= SATA_MEM_RESET_MASK;
	writel(val, clk_base + SATASRESETREG);
	writel(0xfffffff, diagcsr + CFG_MEM_RAM_SHUTDOWN);
	udelay(2000);
	val = readl(clk_base + SATASRESETREG);
	val &= ~SATA_MEM_RESET_MASK;
	writel(val, clk_base + SATASRESETREG);

	val = readl(diagcsr + CFG_MEM_RAM_SHUTDOWN);
	if (val == 0) {
		dev_dbg(ctx->dev, "memory already released from shutdown\n");
		return 0;
	}
	dev_dbg(ctx->dev, "Release memory from shutdown\n");
	/* SATA controller memory in shutdown. Remove from shutdown. */
	writel(0x0, diagcsr + CFG_MEM_RAM_SHUTDOWN);
	readl(diagcsr + CFG_MEM_RAM_SHUTDOWN); /* Force a barrier */

	/* Check for at least ~1ms */
	try = 1000;
	do {
		val = readl(diagcsr + BLOCK_MEM_RDY);
		if (val != 0xFFFFFFFF)
			usleep_range(1, 100);
	} while (val != 0xFFFFFFFF && try-- > 0);
	if (try <= 0) {
		dev_err(ctx->dev, "failed to release memory from shutdown\n");
		return -ENODEV;
	}
	return 0;
}

static void xgene_ahci_set_phy_cfg(struct xgene_ahci_context *ctx, int channel)
{
	void __iomem *mmio = ctx->mmio_base;
	u32 val;

	dev_dbg(ctx->dev, "port configure mmio 0x%p channel %d\n", mmio, channel);
	val = readl(mmio + PORTCFG);
	val = PORTADDR_SET(val, channel == 0 ? 2 : 3);
	writel(val, mmio + PORTCFG);
	readl(mmio + PORTCFG);  /* Force a barrier */
	/* Disable fix rate */
	writel(0x0001fffe, mmio + PORTPHY1CFG);
	readl(mmio + PORTPHY1CFG); /* Force a barrier */
	writel(0x28183219, mmio + PORTPHY2CFG);
	readl(mmio + PORTPHY2CFG); /* Force a barrier */
	writel(0x13081008, mmio + PORTPHY3CFG);
	readl(mmio + PORTPHY3CFG); /* Force a barrier */
	writel(0x00480815, mmio + PORTPHY4CFG);
	readl(mmio + PORTPHY4CFG); /* Force a barrier */
	/* Set window negotiation */
	val = readl(mmio + PORTPHY5CFG);
	val = PORTPHY5CFG_RTCHG_SET(val, 0x300);
	writel(val, mmio + PORTPHY5CFG);
	readl(mmio + PORTPHY5CFG); /* Force a barrier */
	val = readl(mmio + PORTAXICFG);
	val = PORTAXICFG_EN_CONTEXT_SET(val, 0x1); /* Enable context mgmt */
	val = PORTAXICFG_OUTTRANS_SET(val, 0xe); /* Set outstanding */
	writel(val, mmio + PORTAXICFG);
	readl(mmio + PORTAXICFG); /* Force a barrier */
	val = readl(mmio + PTC);
	val = PTC_RXWM_SET(val, 0x30);
	writel(val, mmio + PTC);
}

static int xgene_ahci_hw_init(struct xgene_ahci_context *hpriv)
{
	int i;
	int rc;
	u32 val;

	/* Remove IP RAM out of shutdown */
	rc = xgene_ahci_init_memram(hpriv);
	if (rc)
		return rc;

	for (i = 0; i < MAX_AHCI_CHN_PERCTR; i++)
		xgene_ahci_set_phy_cfg(hpriv, i);

	/* AXI disable Mask */
	writel(0xffffffff, hpriv->mmio_base + HOST_IRQ_STAT);
	readl(hpriv->mmio_base + HOST_IRQ_STAT); /* Force a barrier */
	writel(0, hpriv->csr_base + INTSTATUSMASK);
	val = readl(hpriv->csr_base + INTSTATUSMASK); /* Force a barrier */
	dev_dbg(ctx->dev, "top level interrupt mask 0x%X value 0x%08X\n",
		INTSTATUSMASK, val);

	writel(0x0, hpriv->csr_base + ERRINTSTATUSMASK);
	readl(hpriv->csr_base + ERRINTSTATUSMASK); /* Force a barrier */
	writel(0x0, hpriv->csr_base + SATA_SHIM_OFFSET + INT_SLV_TMOMASK);
	readl(hpriv->csr_base + SATA_SHIM_OFFSET + INT_SLV_TMOMASK);

	/* Enable AXI Interrupt */
	writel(0xffffffff, hpriv->csr_base + SLVRDERRATTRIBUTES);
	writel(0xffffffff, hpriv->csr_base + SLVWRERRATTRIBUTES);
	writel(0xffffffff, hpriv->csr_base + MSTRDERRATTRIBUTES);
	writel(0xffffffff, hpriv->csr_base + MSTWRERRATTRIBUTES);

	/* Enable coherency */
	val = readl(hpriv->csr_base + BUSCTLREG);
	val &= ~0x00000002;     /* Enable write coherency */
	val &= ~0x00000001;     /* Enable read coherency */
	writel(val, hpriv->csr_base + BUSCTLREG);

	val = readl(hpriv->csr_base + IOFMSTRWAUX);
	val |= (1 << 3);        /* Enable read coherency */
	val |= (1 << 9);        /* Enable write coherency */
	writel(val, hpriv->csr_base + IOFMSTRWAUX);
	val = readl(hpriv->csr_base + IOFMSTRWAUX);
	dev_dbg(ctx->dev, "coherency 0x%X value 0x%08X\n", IOFMSTRWAUX, val);

	return rc;
}

static int xgene_ahci_mux_select(struct xgene_ahci_context *ctx)
{
	void *mux_csr = ctx->csr_base + SATA_ENET_MUX_OFFSET;
	u32 val;

	dev_dbg(ctx->dev, "switch the MUX to SATA\n");
	val = readl(mux_csr + SATA_ENET_CONFIG_REG);
	val &= ~CFG_SATA_ENET_SELECT_MASK;
	writel(val, mux_csr + SATA_ENET_CONFIG_REG);
	val = readl(mux_csr + SATA_ENET_CONFIG_REG);
	return val & CFG_SATA_ENET_SELECT_MASK ? -1 : 0;
}

static void xgene_ahci_enable_sds_clk(struct xgene_ahci_context *ctx)
{
        void *clkcsr_base = ctx->csr_base + SATA_CLK_OFFSET;
        u32 val;

	/* Disable all reset */
	writel(0x0, clkcsr_base + SATASRESETREG);
	val = readl(clkcsr_base + SATASRESETREG);

	/* Enable all resets */
	writel(0xff, clkcsr_base + SATASRESETREG);
	val = readl(clkcsr_base + SATASRESETREG);

	/* Disable all clks */
	writel(0x00, clkcsr_base + SATACLKENREG);
	val = readl(clkcsr_base + SATACLKENREG);

	/* Enable all clks */
	writel(0xf9, clkcsr_base + SATACLKENREG);
	val = readl(clkcsr_base + SATACLKENREG);

	/* Get out of reset for:
	 * 	SDS, CSR
	 *
	 * CORE & MEM are still reset
	 */
	val = readl(clkcsr_base + SATASRESETREG);
	if (SATA_MEM_RESET_RD(val) == 1) {
		val &= ~(SATA_CSR_RESET_MASK | SATA_SDS_RESET_MASK);
		val |= SATA_CORE_RESET_MASK | SATA_PCLK_RESET_MASK |
			SATA_PMCLK_RESET_MASK | SATA_MEM_RESET_MASK;
	}
	writel(val, clkcsr_base + SATASRESETREG);
	val = readl(clkcsr_base + SATASRESETREG);
}

static void xgene_ahci_get_param(struct xgene_ahci_context *ctx,
				const char *name, u32 *buf,
				int count, u32 *default_val, u32 conv_factor)
{
	static u32 tx_boost_gain_ssd_a3[] = {	2, 2, 2, 2, 2, 2,
						2, 2, 2, 2, 2, 2,
						2, 2, 2, 2, 2, 2 };
	static u32 tx_boost_gain_a3[] = {	30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30 };
	static u32 tx_eye_tuning_a3[] = { 	10, 10, 10, 10, 10, 10,
						1, 10, 10, 2, 10, 10,
						1, 10, 10, 2, 10, 10 };
	static u32 tx_equalizer_a3[] = {         1, 1, 1, 1, 1, 1,
		                                 1, 1, 1, 1, 1, 1,
						 1, 1, 1, 1, 1, 1 };

	static u32 tx_speed_a3[] = {	1, 3, 7,
					1, 3, 7,
					1, 3, 7 };
	static u32 tx_pre_cursor1_a3[] =  {	36400, 36400, 36400, 36400, 36400, 36400,
					  	36400, 36400, 36400, 36400, 36400, 36400,
						36400, 36400, 36400, 36400, 36400, 36400 };
	static u32 tx_pre_cursor2_a3[] = {   0,0,0,0,0,0,
	                                0,0,0,0,0,0,
	                                0,0,0,0,0,0 };
	static u32 tx_post_cursor_a3[] = {
			182000, 182000, 182000, 182000, 182000, 182000,
			182000, 182000, 182000, 182000, 182000, 182000,
			182000, 182000, 182000, 182000, 182000, 182000 };
	static u32 tx_amplitude_a3[] = {
			106400, 106400, 106400, 106400, 106400, 106400,
			106400, 106400, 106400, 106400, 106400, 106400,
			106400, 106400, 106400, 106400, 106400, 106400 };
	int i;
	int preB0 = xgene_is_preB0();
	u32 *val_ptr;

	if (!strcmp("apm,tx-eye-tuning", name)) {
		val_ptr = preB0 ? &tx_eye_tuning_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-eye-direction", name)) {
		val_ptr = NULL;
	} else if (!strcmp("apm,tx-boost-gain", name)) {
		val_ptr = preB0 ? &tx_boost_gain_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-boost-gain-ssd", name)) {
		val_ptr = preB0 ? &tx_boost_gain_ssd_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-equalizer", name)) {
	        val_ptr = preB0 ? &tx_equalizer_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-amplitude", name)) {
		val_ptr = preB0 ? &tx_amplitude_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-pre-cursor1", name)) {
		val_ptr = preB0 ? &tx_pre_cursor1_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-pre-cursor2", name)) {
		val_ptr = preB0 ? &tx_pre_cursor2_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-post-cursor", name)) {
		val_ptr = preB0 ? &tx_post_cursor_a3[ctx->cid * count] : NULL;
	} else if (!strcmp("apm,tx-speed", name)) {
		val_ptr = preB0 ? &tx_speed_a3[ctx->cid * count] : NULL;
	} else {
		val_ptr = NULL;
	}

	if (val_ptr) {
		for (i = 0; i < count; i++)
			buf[i] = val_ptr[i] / conv_factor;
		return;
	}

	/* Does not exist, load default */
	for (i = 0; i < count; i++)
		buf[i] = default_val[i % 3];
}

INTN xgene_ahci_init(UINT64 serdes_base, UINT64 ahci_base, UINT64 pcie_clk_base,
		UINTN cid, UINTN irq)
{
	u32 default_spd[] = DEFAULT_SATA_SPD_SEL;
	u32 default_txboost_gain[] = DEFAULT_SATA_TXBOOST_GAIN;
	u32 default_txboost_gain_ssd[] = DEFAULT_SATA_TXBOOST_GAIN_SSD;
	u32 default_txeye_direction[] = DEFAULT_SATA_TXEYEDIRECTION;
	u32 default_txeye_tuning[] = DEFAULT_SATA_TXEYETUNING;
	u32 default_txamp[] = DEFAULT_SATA_TXAMP;
	u32 default_txcn1[] = DEFAULT_SATA_TXCN1;
	u32 default_txcn2[] = DEFAULT_SATA_TXCN2;
	u32 default_txcp1[] = DEFAULT_SATA_TXCP1;
	u32 default_dfe[]  = DEFAULT_SATA_DFE;
	struct xgene_ahci_context *hpriv;
	INTN rc;
	INTN i;

	hpriv = AllocateZeroPool(sizeof(struct xgene_ahci_context));
	if (!hpriv) {
		dev_err(ctx->dev, "can't alloc host context\n");
		return -1;
	}
	hpriv->cid = cid;
	hpriv->irq = irq;

	hpriv->csr_base = (VOID *) serdes_base;
	if (!hpriv->csr_base) {
		dev_err(ctx->dev, "can't map PHY CSR resource\n");
		rc = -1;
		goto error;
	}

	hpriv->mmio_base = (VOID *) ahci_base;
	if (!hpriv->mmio_base) {
		dev_err(ctx->dev, "can't map MMIO resource\n");
		rc = -1;
		goto error;
	}

	hpriv->phy.mode = MODE_SATA;
	hpriv->phy.clk_type = CLK_EXT_DIFF;
	hpriv->phy.lane = MAX_AHCI_CHN_PERCTR;
	hpriv->phy.sds_base = hpriv->csr_base + SATA_SERDES_OFFSET;
	hpriv->phy.clk_base = hpriv->csr_base + SATA_CLK_OFFSET;
	hpriv->phy.core_base = hpriv->csr_base;
	hpriv->phy.inited = 0;
	if (cid == 2) {
		hpriv->phy.ext_cmu_base = (VOID *) pcie_clk_base;
		hpriv->phy.ref_100MHz = 0;
	} else {
		hpriv->phy.ref_100MHz = 1;
	}

	/* Load override paramaters */
	xgene_ahci_get_param(hpriv, "apm,tx-eye-tuning",
		hpriv->phy.sata_param.txeyetuning, 6, default_txeye_tuning, 1);
	xgene_ahci_get_param(hpriv, "apm,tx-eye-direction",
		hpriv->phy.sata_param.txeyedirection, 6,
		default_txeye_direction, 1);
	xgene_ahci_get_param(hpriv, "apm,tx-boost-gain",
		hpriv->phy.sata_param.txboostgain, 6, default_txboost_gain, 1);
	xgene_ahci_get_param(hpriv, "apm,tx-boost-gain-ssd",
		hpriv->phy.sata_param.txboostgain_ssd, 6,
		default_txboost_gain_ssd, 1);
	xgene_ahci_get_param(hpriv, "apm,tx-amplitude",
		hpriv->phy.sata_param.txamplitude, 6, default_txamp, 13300);
	xgene_ahci_get_param(hpriv, "apm,tx-equalizer",
		hpriv->phy.sata_param.txequalizer, 6, default_dfe, 1);
	xgene_ahci_get_param(hpriv, "apm,tx-pre-cursor1",
		hpriv->phy.sata_param.txprecursor_cn1, 6, default_txcn1,
		18200);
	xgene_ahci_get_param(hpriv, "apm,tx-pre-cursor2",
		hpriv->phy.sata_param.txprecursor_cn2, 6, default_txcn2,
		18200);
	xgene_ahci_get_param(hpriv, "apm,tx-post-cursor",
		hpriv->phy.sata_param.txpostcursor_cp1, 6, default_txcp1,
		18200);
	xgene_ahci_get_param(hpriv, "apm,tx-speed",
		hpriv->phy.sata_param.txspeed, 3, default_spd, 1);
	for (i = 0; i < MAX_AHCI_CHN_PERCTR; i++) {
		hpriv->phy.sata_param.speed[i] = 2;	/* Default to Gen3 */
		hpriv->phy.sata_param.disk_type[i] = DISK_HDD;/* Default to HDD */
	}
	/* Select SATA if required */
	if (cid != 2)
		xgene_ahci_mux_select(hpriv);

	/* Enable SDS clock to configure the PHY */
	xgene_ahci_enable_sds_clk(hpriv);

	/* Initialize the PHY */
	rc = xgene_phy_hw_init(&hpriv->phy);
	if (rc != 0) {
		dev_err(ctx->dev, "SATA%d PHY initialize failed %d\n", cid, rc);
		rc = -1;
		goto error;
	}

	/* Configure the host controller */
	xgene_ahci_hw_init(hpriv);

	dev_dbg(ctx->dev, "SATA%d PHY initialized\n", cid);
	return 0;

error:
	FreePool(hpriv);
	return rc;
}
