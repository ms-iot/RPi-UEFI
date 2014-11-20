/*
 * APM X-Gene USB host controller driver
 *
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD
 * License which accompanies this distribution.  The full text of the license
 *  may be found at http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED.
 *
 */

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include "../../../Library/APMXGenePHYLib/phy-xgene.h"

#define USB30BID                       0x0000
#define HOSTPORTREG                    0x0030
#define POWERMNGTREG                   0x0038
#define  HOST_PORT_POWER_CONTROL_PRESENT (1 << 0)
#define  PORT_OVERCUR_ENABLE           (1 << 28)
#define  PORT_OVERCUR_INVERT           (1 << 29)
#define  PORT_POWER_DISABLE            (1 << 30)
#define HBFSIDEBANDREG                 0x003c
#define INTERRUPTSTATUSMASK            0x0064
#define PIPEUTMIREG                    0x0070
#define  CSR_PIPE_CLK_READY            (1 << 1)
#define  CSR_USE_UTMI_FOR_PIPE         (1 << 8)
#define  PIPE0_PHYSTATUS_OVERRIDE_EN   (1 << 30)
#define  PIPE0_PHYSTATUS_SYNC          (1 << 31)
#define USB_SDS_CMU_STATUS0            0xa020
#define USB_OTG_CTL                    0xa058
#define  USB_OTG_CTL_PORT_RESET_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32)(src) << 8) & 0x00000100))
#define  USB_OTG_CTL_REFCLKSEL_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32)(src) << 1) & 0x00000006))
#define  USB_OTG_CTL_REFCLKDIV_SET(dst, src) \
		(((dst) & ~0x00000018) | (((u32)(src) << 3) & 0x00000018))
#define USB_OTG_OVER                   0xa05c
#define USBCLKENREG                    0xc000
#define USBSRESETREG                   0xc008
#define GCTL                           0xc110
#define  GCTL_RAMCLKSEL_SET(dst, src) \
		(((dst) & ~0x000000C0) | (((u32)(src) << 6) & 0x000000C0))
#define  GCTL_CORESOFTRESET_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32)(src) << 11) & 0x00000800))
#define GSNPSID                        0xc120
#define GUSB2PHYCFG_0                  0xc200
#define  GUSB2PHYCFG_0_PHYSOFTRST_SET(dst, src) \
		(((dst) & ~0x80000000) | (((u32)(src) << 31) & 0x80000000))
#define  GUSB2PHYCFG_0_SUSPENDUSB20_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32)(src) << 6) & 0x00000040))
#define  GUSB2PHYCFG_0_PHYIF_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32)(src) << 3) & 0x00000008))
#define GUSB3PIPECTL_0                 0xc2c0
#define  GUSB3PIPECTL_0_PHYSOFTRST_SET(dst, src) \
		(((dst) & ~0x80000000) | (((u32)(src) << 31) & 0x80000000))
#define  GUSB3PIPECTL_0_HSTPRTCMPL_SET(dst, src) \
		(((dst) & ~0x40000000) | (((u32)(src) << 30) & 0x40000000))
#define  GUSB3PIPECTL_0_SUSPENDENABLE_SET(dst, src) \
		(((dst) & ~0x00020000) | (((u32)(src) << 17) & 0x00020000))
#define  GUSB3PIPECTL_0_DATWIDTH_SET(dst, src) \
		(((dst) & ~0x00018000) | (((u32)(src) << 15) & 0x00018000))
#define  GUSB3PIPECTL_0_RX_DETECT_TO_POLLING_LFPS_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32)(src) << 8) & 0x00000100))
#define CFG_MEM_RAM_SHUTDOWN           0xd070
#define BLOCK_MEM_RDY                  0xd074
#define INT_SLV_TMOMask                0xe010
#define CFG_AMA_MODE                   0xe014
#define  CFG_RD2WR_EN                  0x2
#define USBSTS                         0x0024
#define  USBSTS_CNR                    (1 << 11)
#define USB_SERDES_OFFSET              0xa000
#define USB_CLK_OFFSET                 0xc000


#define xgene_dbg(fmt, args...) \
	DEBUG((EFI_D_INFO, "XGeneUsb: " fmt "\n", ## args))

#define xgene_err(fmt, args...) \
	DEBUG((EFI_D_ERROR, "XGeneUsb: " fmt "\n", ## args))

#define xhci_udelay(x) MicroSecondDelay(x)

struct xgene_xhci_context {
	u8 cid;				/* Controller ID */
	int irq;
	u32 clk2_sel;
	u32 ovrcur_en;
	u32 ovrcur_ivrt;
	void __iomem *csr_base;		/* CSR base address of IP */
	void __iomem *mmio_base;	/* XHCI I/O base address */

	struct xgene_phy_ctx phy;
};


/*
 * Wait until a register has a specific value or timeout.
 * Unit for interval and timeout parameters are micro-second
 */
u32 xgene_xhci_wait_register(void *reg, u32 mask, u32 val,
		UINTN interval, u64 timeout)
{
	unsigned long deadline = 0;
	u32 tmp;

	tmp = readl(reg);
	while (((tmp & mask) != val) && (deadline < timeout)) {
		xhci_udelay(interval);
		tmp = readl(reg);
		deadline += interval;
	}

	return tmp;
}

static void xgene_xhci_enable(struct xgene_xhci_context *hpriv)
{
	void *csr_base = hpriv->csr_base;

	/* Enable clock */
	writel(0xF, csr_base + USBCLKENREG);

	/* Place blocks under reset */
	writel(0x7F, csr_base + USBSRESETREG);

	/* Remove blocks under reset */
	writel(0x0, csr_base + USBSRESETREG);
}

static int xgene_xhci_init_memblk(struct xgene_xhci_context *hpriv)
{
	void *csr_base = hpriv->csr_base;
	u32 dt;
	UINTN try;

	/* Clear memory shutdown */
	dt = readl(csr_base + CFG_MEM_RAM_SHUTDOWN);
	if (dt == 0) {
		xgene_dbg("memory already released from shutdown\n");
		return 0;
	}

	/* USB controller memory in shutdown. Remove from shutdown. */
	xgene_dbg("Release memory from shutdown\n");
	writel(0, csr_base + CFG_MEM_RAM_SHUTDOWN);
	dt = readl(csr_base + CFG_MEM_RAM_SHUTDOWN);

	/* Check for at least ~1ms */
	try = 1000;
	do {
		dt = readl(csr_base + BLOCK_MEM_RDY);
		if (dt != 0xFFFFFFFF)
			xhci_udelay(1);
	} while (dt != 0xFFFFFFFF && try-- > 0);
	if (try <= 0) {
		xgene_err("failed to release memory from shutdown\n");
		return -1;
	}
	return 0;
}

UINTN xgene_xhci_hw_init(struct xgene_xhci_context *hpriv)
{
	VOID *csr_base = hpriv->csr_base;
	VOID *fabric_base = hpriv->mmio_base;
	u32 dt;
	INTN rc = 0;
	INTN phy_init = 0;

	xgene_dbg("USB Initialization ...\n");

	/* Enable USB controller */
	xgene_xhci_enable(hpriv);

	dt = readl(csr_base + POWERMNGTREG);
	dt |= PORT_POWER_DISABLE;
	writel(dt, csr_base + POWERMNGTREG);

	/* Read BID and Global SynopsysID */
	dt = readl(fabric_base + GSNPSID);
	xgene_dbg("SynopsysID=%04x - RN=%04x\n", (u16) (dt >> 16), (u16) dt);

	/* Read/Write Coherency Override Enable */
	dt = readl(csr_base + HBFSIDEBANDREG);
	dt |= 0xF;
	writel(dt, csr_base + HBFSIDEBANDREG);

	/* Initialize the PHY */
	rc = xgene_phy_hw_init(&hpriv->phy);
	if (rc != 0)
		xgene_err("USB%d PHY initialize failed %d\n", hpriv->cid, rc);
	else
		phy_init = 1;

	/* Initialize RAM shutdown */
	xgene_xhci_init_memblk(hpriv);

	/* Tune eye pattern */
	writel(0x001c0365, csr_base + USB_OTG_OVER);

	/* Reset Ref. clock select to default and enable port reset */
	dt = readl(csr_base + USB_OTG_CTL);
	dt = USB_OTG_CTL_REFCLKSEL_SET(dt, 0);
	dt = USB_OTG_CTL_REFCLKDIV_SET(dt, 0);
	dt = USB_OTG_CTL_PORT_RESET_SET(dt, 1);
	dt |= (hpriv->clk2_sel << 1);
	writel(dt, csr_base + USB_OTG_CTL);
	xgene_dbg("clk2_sel=0x%x\n", hpriv->clk2_sel);

	/* Enable core interrupt */
	xgene_dbg("Enable core interrupt\n");
	writel(0xFFFFFFF0, csr_base + INTERRUPTSTATUSMASK);

	/* Enable AXI Interrupts */
	writel(0x0, csr_base + INT_SLV_TMOMask);

	/* Control/Monitor status of PIPE or UTMI signals */
	if (!phy_init) {
		dt = readl(csr_base + PIPEUTMIREG);
		dt |= PIPE0_PHYSTATUS_OVERRIDE_EN;
		dt |= CSR_USE_UTMI_FOR_PIPE;
		writel(dt, csr_base + PIPEUTMIREG);
	}

	/* Configure Power Management Register */
	dt = readl(csr_base + POWERMNGTREG);
	if (hpriv->ovrcur_en) {
		xgene_dbg("Enable port over current\n");
		dt |= PORT_OVERCUR_ENABLE;
		if (hpriv->ovrcur_ivrt) {
			xgene_dbg("Set port over current inverted\n");
			dt |= PORT_OVERCUR_INVERT;
		}
	}
	dt |= HOST_PORT_POWER_CONTROL_PRESENT;
	writel(dt, csr_base + POWERMNGTREG);

	/* Disable USB 3.0 support when no PHY available */
	if (!phy_init) {
		xgene_dbg("Disable USB3.0 capability\n");
		dt = readl(csr_base + HOSTPORTREG);
		dt |= 0x1;
		writel(dt, csr_base + HOSTPORTREG);
	}

	/* PHY Controller Configuration */
	xgene_dbg("Clear USB3 PHY soft reset\n");
	dt = readl(fabric_base + GUSB3PIPECTL_0);
	dt = GUSB3PIPECTL_0_HSTPRTCMPL_SET(dt, 0);
	dt = GUSB3PIPECTL_0_SUSPENDENABLE_SET(dt, 0);
	dt = GUSB3PIPECTL_0_RX_DETECT_TO_POLLING_LFPS_SET(dt, 1);
	dt = GUSB3PIPECTL_0_DATWIDTH_SET(dt, 1);	/* 16 bit */
	dt = GUSB3PIPECTL_0_PHYSOFTRST_SET(dt, 0);
	writel(dt, fabric_base + GUSB3PIPECTL_0);

	/* Clear USB2 PHY soft reset  */
	xgene_dbg("Clear USB2 PHY soft reset\n");
	dt = readl(fabric_base + GUSB2PHYCFG_0);
	dt = GUSB2PHYCFG_0_PHYSOFTRST_SET(dt, 0);
	dt = GUSB2PHYCFG_0_SUSPENDUSB20_SET(dt, 0);
	dt = GUSB2PHYCFG_0_PHYIF_SET(dt, 0);
	writel(dt, fabric_base + GUSB2PHYCFG_0);

	/* Clear CORE soft reset */
	xgene_dbg("Clear USB CORE reset\n");
	dt = readl(fabric_base + GCTL);
	dt = GCTL_RAMCLKSEL_SET(dt, 0);
	dt = GCTL_CORESOFTRESET_SET(dt, 0);
	writel(dt, fabric_base + GCTL);

	/* Clear OTG PHY reset */
	xgene_dbg("Clear OTG PHY reset\n");
	dt = readl(csr_base + USB_OTG_CTL);
	dt = USB_OTG_CTL_PORT_RESET_SET(dt, 0);
	writel(dt, csr_base + USB_OTG_CTL);

	if (phy_init) {
		/* Wait 10 */
		dt = xgene_xhci_wait_register(csr_base + USB_SDS_CMU_STATUS0,
					      0x7, 0x7, 100, 100000);
		if ((dt & 0x3) == 0x3)
			xgene_dbg("SERDES is ready\n");
		else
			xgene_err("SERDES is not ready\n");

		/* Waiting when CLK is stable */
		dt = xgene_xhci_wait_register(csr_base + PIPEUTMIREG,
					      PIPE0_PHYSTATUS_SYNC, 0, 100,
					      100000);
		if ((dt & PIPE0_PHYSTATUS_SYNC) != 0) {
			xgene_err("Timeout waiting for PHY Status deasserted\n");
			return -1;
		}
		xgene_dbg("PHY Status de-asserted\n");

		dt = xgene_xhci_wait_register(csr_base + PIPEUTMIREG,
					      CSR_PIPE_CLK_READY,
					      CSR_PIPE_CLK_READY, 100, 100000);
		if ((dt & CSR_PIPE_CLK_READY) == 0)
			xgene_err("Timeout waiting for PIPE clock ready\n");
		else
			xgene_dbg("PIPE clock is ready\n");
	}

	dt = readl(csr_base + POWERMNGTREG);
	dt &= ~PORT_POWER_DISABLE;
	writel(dt, csr_base + POWERMNGTREG);

	/*  Poll register CNR until its cleared */
	dt = xgene_xhci_wait_register(fabric_base + USBSTS,
				      USBSTS_CNR, 0x0, 100, 2000000);
	if (dt & USBSTS_CNR) {
		xgene_err("Timeout waiting for USB controller ready\n");
		return -1;
	} else {
		xgene_dbg("USB Controller is ready\n");
	}

	return rc;
}

INTN xgene_xhci_init(UINT64 serdes_base, UINT64 xhci_base, UINTN irq,
		UINTN cid, UINT32 clk2_sel, UINT32 ovrcur_en, UINT32 ovrcur_ivrt)
{
	struct xgene_xhci_context *hpriv;
	INTN rc;

	hpriv = AllocateZeroPool(sizeof(struct xgene_xhci_context));
	if (!hpriv) {
		xgene_err("can't alloc host context\n");
		return -1;
	}
	hpriv->csr_base = (VOID *) serdes_base;
	if (!hpriv->csr_base) {
		xgene_err("can't map PHY CSR resource\n");
		rc  = -1;
		goto error;
	}

	hpriv->mmio_base = (VOID *) xhci_base;
	if (!hpriv->mmio_base) {
		xgene_err("can't map MMIO resource\n");
		rc  = -1;
		goto error;
	}

	hpriv->cid = cid;
	hpriv->irq = irq;
	hpriv->clk2_sel = clk2_sel;
	hpriv->ovrcur_en = ovrcur_en;
	hpriv->ovrcur_ivrt = ovrcur_ivrt;

	hpriv->phy.mode = MODE_USB;
	hpriv->phy.clk_type = CLK_EXT_DIFF;
	hpriv->phy.lane = 1;
	hpriv->phy.sds_base = hpriv->csr_base + USB_SERDES_OFFSET;
	hpriv->phy.clk_base = hpriv->csr_base + USB_CLK_OFFSET;
	hpriv->phy.core_base = hpriv->csr_base;
	hpriv->phy.inited = 0;
	hpriv->phy.ref_100MHz = 1;

	/* Configure the host controller */
	xgene_xhci_hw_init(hpriv);

	xgene_dbg("USB%d PHY initialized\n", cid);
	return 0;

error:
	FreePool(hpriv);
	return rc;
}
