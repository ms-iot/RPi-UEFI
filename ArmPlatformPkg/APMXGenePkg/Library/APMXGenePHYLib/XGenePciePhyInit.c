/*
 * APM X-Gene PCIE host controller PHY driver
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
 * This driver produces IDE_CONTROLLER_INIT protocol for APM X-Gene PCIE
 * controllers.
 */
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include "phy-xgene.h"

#define PCIE_SERDES_OFFSET		0x0000A000
#define PCIE_CLK_OFFSET			0x0000C000
#define PCIE_DIAG_OFFSET		0x0000D000

/* PCIE Clock/Reset CSR */
#define PCIESRESETREG				0x00000000
#define PCIECLKENREG				0x00000008
#define PCIE_APB_CORE_CLKEN			0x00000008
#define PCIE_AXI_CORE_CLKEN			0x00000004
#define PCIE_CORE_CLKEN				0x00000002
#define PCIE_CSR_CLKEN				0x00000001
#define PCIE_PHY_SDS_RESET_MASK		0x00000100
#define PCIE_APB_CORE_RESET_MASK	0x00000008
#define PCIE_AXI_CORE_RESET_MASK	0x00000004
#define PCIE_CORE_RESET_MASK		0x00000002
#define PCIE_CSR_RESET_MASK			0x00000001

/* MUX CSR */
#define PCISDSMUXREG		0x90
#define PCIE_SDS_MUX_FULL_WIDTH_MASK	0x1

/* PCIE global diagnostic CSR */
#define CFG_MEM_RAM_SHUTDOWN		0x00000070
#define BLOCK_MEM_RDY		0x00000074

#define CFG_CONSTANTS_383_352   0x202c
#define BYPASS_RECEIVER_DETECTION_SET(dst, src) (((dst) & ~0x10000000) | \
            (((u32)(src) << 0x1c)  & \
            0x10000000))

static void xgene_pcie_enable_sds_clk(struct xgene_phy_ctx *ctx)
{
	void *clkcsr_base = ctx->clk_base;
	void *sdscsr_base = ctx->sds_base;
	u32 val;

	/* Disable all clks */
	writel(~(PCIE_APB_CORE_CLKEN |
			 PCIE_AXI_CORE_CLKEN |
			 PCIE_CORE_CLKEN |
			 PCIE_CSR_CLKEN), clkcsr_base + PCIECLKENREG);
	val = readl(clkcsr_base + PCIECLKENREG);

	/* Enable all resets */
	writel((PCIE_PHY_SDS_RESET_MASK |
			PCIE_APB_CORE_RESET_MASK |
			PCIE_AXI_CORE_RESET_MASK |
			PCIE_CORE_RESET_MASK |
			PCIE_CSR_RESET_MASK), clkcsr_base + PCIESRESETREG);
	val = readl(clkcsr_base + PCIESRESETREG);

	/* Enable clk */
	writel((PCIE_APB_CORE_CLKEN |
			PCIE_AXI_CORE_CLKEN |
			PCIE_CSR_CLKEN), clkcsr_base + PCIECLKENREG);
	val = readl(clkcsr_base + PCIECLKENREG);

	writel(~(PCIE_APB_CORE_RESET_MASK |
			PCIE_AXI_CORE_RESET_MASK |
			PCIE_CSR_RESET_MASK), clkcsr_base + PCIESRESETREG);
	val = readl(clkcsr_base + PCIESRESETREG);

	if (ctx->lane == 8) {
		val = readl(sdscsr_base + PCISDSMUXREG);
		val |= PCIE_SDS_MUX_FULL_WIDTH_MASK;
		writel(val, sdscsr_base + PCISDSMUXREG);
	}
}

static int xgene_pcie_init_memram(struct xgene_phy_ctx *ctx)
{
	void __iomem *diagcsr = ctx->core_base + PCIE_DIAG_OFFSET;
	int try;
	u32 val;

	val = readl(diagcsr + CFG_MEM_RAM_SHUTDOWN);
	if (val == 0) {
		dev_dbg(ctx->dev, "memory already released from shutdown\n");
		return 0;
	}
	dev_dbg(ctx->dev, "Release memory from shutdown\n");
	/* PCIE controller memory in shutdown. Remove from shutdown. */
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

static void xgene_pcie_bypass_rcvr_detect(struct xgene_phy_ctx *hpriv)
{
	void __iomem *csr = hpriv->core_base;
	u32 val;

	val = readl(csr + CFG_CONSTANTS_383_352);
	val = BYPASS_RECEIVER_DETECTION_SET(val, 0x1);
	writel(val, csr + CFG_CONSTANTS_383_352);
	readl(csr + CFG_CONSTANTS_383_352); /* Force a barrier */
}

static int xgene_pcie_hw_init(struct xgene_phy_ctx *hpriv)
{
	int rc;

	xgene_pcie_bypass_rcvr_detect(hpriv);

	/* Remove IP RAM out of shutdown */
	rc = xgene_pcie_init_memram(hpriv);

	return rc;
}

INTN xgene_pcie_init(UINT64 csr_base, UINTN lane, UINTN port)
{
	struct xgene_phy_ctx *hpriv;
	INTN rc;

	hpriv = AllocateZeroPool(sizeof(struct xgene_phy_ctx));
	if (!hpriv) {
		dev_err(ctx->dev, "can't alloc PCIE host context\n");
		return -1;
	}

	hpriv->core_base = (VOID *) csr_base;
	if (!hpriv->core_base) {
		dev_err(ctx->dev, "can't map PHY core resource\n");
		rc	= -1;
		goto error;
	}

	hpriv->sds_base = (VOID *) hpriv->core_base + PCIE_SERDES_OFFSET;
	if (!hpriv->sds_base) {
		dev_err(ctx->dev, "can't map PHY CSR resource\n");
		rc	= -1;
		goto error;
	}

	hpriv->mode = MODE_PCIE;
	hpriv->lane = lane;
	hpriv->clk_base = hpriv->core_base + PCIE_CLK_OFFSET;
	hpriv->inited = 0;
	hpriv->ssc = 0;

	/* Enable SDS clock to configure the PHY */
	xgene_pcie_enable_sds_clk(hpriv);

	/* Initialize the PHY */
	rc = xgene_phy_hw_init(hpriv);
	if (rc != 0) {
		dev_err(ctx->dev, "PCIE%d PHY initialize failed :%d\n", port, rc);
		rc = -1;
		goto error;
	}

	/* Configure the host controller */
	xgene_pcie_hw_init(hpriv);

	dev_dbg(ctx->dev, "PCIE%d PHY initialized\n", port);
	return 0;

error:
	FreePool(hpriv);
	return rc;
}
