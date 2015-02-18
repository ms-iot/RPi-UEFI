/**
 * AppliedMicro APM88xxxx Ethernet Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Iyappan Subramanian <isubramanian@apm.com>
 *                      Ravi Patel <rapatel@apm.com>
 *                      Fushen Chen <fchen@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * @file apm_xgenet_mac.c
 *
 * This file implements driver for XGMII and statistics blocks of
 * APM88xxxx Ethernet subsystem
 *
 */

#include "../mustang.h"
#include "apm_enet_access.h"
#include "apm_xgenet_mac.h"
#include "apm_xgenet_csr.h"

#define ENET_INTERFACE_MODE2_SET REGSPEC_INTERFACE_MODE2_SET
#define ENET_INTERFACE_MODE2_RD REGSPEC_INTERFACE_MODE2_RD
#define ENET_LHD_MODE_WR REGSPEC_LHD_MODE_WR
#define ENET_SRST_ADDR XGENET_SRST_ADDR
#define ENET_SRST_DEFAULT XGENET_SRST_DEFAULT
#define ENET_GHD_MODE_WR REGSPEC_GHD_MODE_WR
#define ENET_INTERFACE_MODE2_WR REGSPEC_INTERFACE_MODE2_WR

#ifdef CONFIG_STORM_VHP
#define COUNT_FOR_TIMEOUT 5
#else
#define COUNT_FOR_TIMEOUT 10000
#endif

#ifdef CONFIG_STORM
static u32 pll_manualcal = 0;
#endif

#ifdef CONFIG_SHADOWCAT
#define CONFIG_SHADOWCAT_SERDES
#define AN_CONTROL                                0x0
#define AN_CONFIGURATION_REGISTER                 0x58
#define  AN_CONFIGURATION_REGISTER_AUTO_CONFIGURATION_SET(dst, src)\
	(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))

#define  AN_CONTROL_AUTO_NEGOTIATION_ENABLE_SET(dst, src) \
	(((dst) & ~0x00001000) | (((u32) (src) << 12) & 0x00001000))

#define  XGENET_CLKEN_CFG_AN_CLK_EN_SET(dst, src)\
    (((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))

#define  XGENET_CLKEN_CFG_AD_CLK_EN_SET(dst, src)\
    (((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))

#define  XGENET_CLKEN_CFG_AN_REF_CLK_EN_SET(dst, src)\
    (((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))

#define  XGENET_CLKEN_CSR_CLKEN_SET(dst, src)\
    (((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))

#define  XGENET_SRST_CSR_RESET_SET(dst, src)\
    (((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))

#define  XGENET_CLKEN_CFG_PCS_CLK_EN_SET(dst, src)\
    (((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))

#define  XGENET_CLKEN_XGENET_CLKEN_SET(dst, src)\
    (((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))

#define  XGENET_SRST_XGENET_PCS_RESET_SET(dst, src)\
    (((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))

#define  XGENET_SRST_XGENET_RESET_SET(dst, src)\
    (((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))

#define XGENET_SDS_CMU_HSPLL_CTL1		0x44
#define XGENET_SDS_CMU_HSPLL_STATS		0x48
#define XGENET_SDS_CMU_CTL1			0x24
#define  XGENET_SDS_CMU_CTL1_CFG_CMU_I_USRCLK_DIV_SET(dst, src)\
    (((dst) & ~0x1c000000) | (((u32) (src) << 26) & 0x1c000000))
#define  XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_POST_DIV_RESETB_SET(dst, src)\
    (((dst) & ~0x00000080) | (((u32) (src) << 7) & 0x00000080))
#define  XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_REFCLK_DIV_RESETB_SET(dst, src)\
    (((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define  XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_PLLRESETB_SET(dst, src)\
    (((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define AN_OFFSET 0x20000

static void xfi_an_wr(struct xgene_phy_ctx *ctx, u32 reg, u32 data)
{
	serdes_wr(ctx, 0, reg + AN_OFFSET, data);
}

static void xfi_an_rd(struct xgene_phy_ctx *ctx, u32 reg, u32 *data)
{
	serdes_rd(ctx, 0, reg + AN_OFFSET, data);
}
#endif

static void apm_xgmac_rx_enable(struct apm_enet_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
				AXGMAC_CONFIG_1_ADDR, HSTRFEN1_SET(data, 1));

		apm_enet_read(priv, BLOCK_AXG_MAC_CSR,
				XGENET_RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_SET(data, 0);
		data = RX_DV_GATE_EN0_SET(data, 0);
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
				XGENET_RX_DV_GATE_REG_0_ADDR, data);
	} else {
		apm_enet_read(priv, BLOCK_MCX_MAC,
				MAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC,
				MAC_CONFIG_1_ADDR, RX_EN1_SET(data, 1));
	}
}

static void apm_xgmac_rx_disable(struct apm_enet_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC_CSR,
				XGENET_RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_SET(data, 1);
		data = RX_DV_GATE_EN0_SET(data, 1);
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
				XGENET_RX_DV_GATE_REG_0_ADDR, data);

		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
				AXGMAC_CONFIG_1_ADDR, HSTRFEN1_SET(data, 0));
	} else {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC,
				MAC_CONFIG_1_ADDR, RX_EN1_SET(data, 0));
	}
}

static void apm_xgmac_tx_enable(struct apm_enet_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
				AXGMAC_CONFIG_1_ADDR, HSTTFEN1_SET(data, 1));
	} else {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC,
				MAC_CONFIG_1_ADDR, TX_EN1_SET(data, 1));
	}
}

static void apm_xgmac_tx_disable(struct apm_enet_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
				AXGMAC_CONFIG_1_ADDR, HSTTFEN1_SET(data, 1));
	} else {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC,
				MAC_CONFIG_1_ADDR, TX_EN1_SET(data, 0));
	}
}

static int apm_xgmac_link_status(struct apm_enet_priv *priv)
{
	u32 data, speed;

	if (!priv->mac_to_mac) {
		if (!priv->phyless) {
			apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &data);
			priv->link_status = PORT_RD(data);
		} else {
			priv->link_status = 1;
		}
		if (!priv->link_status) {
			priv->speed = APM_ENET_SPEED_0;
			PHY_PRINT("Port%d is down\n", priv->port);
			return 0;
		}
		if (priv->phy_mode == PHY_MODE_XGMII) {
			priv->speed = APM_ENET_SPEED_10000;
		} else {
			/* Get the final speed information from SGMII */
			apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR >> 2, &data);
			speed = LINK_SPEED_F1_RD(data);
			switch(speed) {
			case PHY_SPEED_10:
				speed = APM_ENET_SPEED_10;
				break;
			case PHY_SPEED_100:
				speed = APM_ENET_SPEED_100;
				break;
			default:
				speed = APM_ENET_SPEED_1000;
				break;
			}
			PHY_PRINT("Phy Speed is :%d \n", speed);
			priv->speed = speed;
		}
	} else {
		priv->link_status = 1;
		priv->speed = priv->desired_speed;
	}
	return 1;
}


u32 enet_xgbaser_pcs_ind_csr_reg_rd(struct apm_enet_priv *priv, u32 offset)
{
	u32 PCS_Ind_Command_Done, data;

	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_ADDR_0_ADDR, offset);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR,
			REGSPEC_READ0_F8_WR(1));

	PCS_Ind_Command_Done = 0;
	while (PCS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_XGENET_PCS, IND_COMMAND_DONE_0_ADDR,
				&PCS_Ind_Command_Done);

	}
	apm_enet_read(priv, BLOCK_XGENET_PCS, IND_RDATA_0_ADDR, &data);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR, 0x0);
	PHY_PRINT("%a read %x <- %x\n", __func__, data, offset);
	return data;
}

void enet_xgbaser_pcs_ind_csr_reg_wr(struct apm_enet_priv *priv, u32 offset, u32 data)
{
	u32 PCS_Ind_Command_Done;

	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_ADDR_0_ADDR, offset);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_WDATA_0_ADDR, data);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR,
			REGSPEC_WRITE0_F8_WR(1));

	PCS_Ind_Command_Done = 0;
	while (PCS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_XGENET_PCS, IND_COMMAND_DONE_0_ADDR,
				&PCS_Ind_Command_Done);
	}
	PHY_PRINT("%a write %x -> %x\n", __func__, data, offset);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR, 0);
}

void sm_xgenet_module_level_eee_init(struct apm_enet_priv *priv)
{
	u32 xgenet_csr_config_reg;

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR,
			&xgenet_csr_config_reg);

	if (CFG_SGMII_EN_RD(xgenet_csr_config_reg) == 0x2) {/* xgmii mode */
		PHY_PRINT("Enable EEE capability...\n");
		enet_xgbaser_pcs_ind_csr_reg_wr(priv, PCS_EEE_CAPABILITY_ADDR,
				0x0000007f);
	} else {	/* SGMII mode */
		PHY_PRINT("Enable detect LPI...\n");
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_LPI_DETECT_0_ADDR, 0x00000201);
		/* Config EEE RX Timer */
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER0_0_ADDR, 0x00000100);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER1_0_ADDR, 0x00000100);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER2_0_ADDR, 0x00000100);
		PHY_PRINT("Clear LPI dectect interrupt mask...\n");
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_LPI_DETECT_INTR_0MASK_ADDR, 0xfffffffe);
	}
}

static void xgenet_config_qmi_assoc(struct apm_enet_priv *priv)
{
	/* Configure Ethernet QMI: WQ and FPQ association, QM_SOC for now */
	switch (priv->port) {
	case XGENET_0:
	case XGENET_1:
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIWQASSOC_ADDR, 0x0);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIFPQASSOC_ADDR, 0x0);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEFPQASSOC_ADDR, 0x0);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEWQASSOC_ADDR, 0x0);
		break;
	case XGENET_2:
	case XGENET_3:
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIWQASSOC_ADDR, 0x0);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIFPQASSOC_ADDR, 0x0);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEFPQASSOC_ADDR,
					0xffffffff);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEWQASSOC_ADDR,
					0xffffffff);
		apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMHOLD_ADDR,
					REGSPEC_QMLITE_HOLD_EN_WR(1));
		break;
	default:
		break;
	}
}

static void xgenet_sds_ind_csr_reg_wr(struct apm_enet_priv *priv,
	u32 offset, u32 data)
{
	u32 value;
	u32 SDS_Ind_Command_Addr;
	u32 SDS_Ind_Command_Done;

	/* write 1 to clear indirect error detected/ind cmd done */
	value = (CFG_IND_ADDR_WR(0)
			| CFG_IND_ERR_WR(1)
			| CFG_IND_CMD_DONE_WR(1)
			| CFG_IND_RD_CMD_WR(0)
			| CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	PHY_PRINT("%a cmd value=0x%x -> 0x%llx\n", __func__, value,
			XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);

	value = data;
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_WDATA_REG_ADDR, value);
	PHY_PRINT("%a data value=0x%x -> 0x%llx\n", __func__, value,
			XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_WDATA_REG_ADDR);

	SDS_Ind_Command_Addr = offset; /* offset[15:0] */
	value = (CFG_IND_ADDR_WR(SDS_Ind_Command_Addr)
			| CFG_IND_ERR_WR(0)
			| CFG_IND_CMD_DONE_WR(0)
			| CFG_IND_RD_CMD_WR(0)
			| CFG_IND_WR_CMD_WR(1));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	SDS_Ind_Command_Done = 0;
	while (SDS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, &value);
		PHY_PRINT("%a cmd_done=0x%x <- 0x%llx\n", __func__, value,
				XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);
		SDS_Ind_Command_Done = CFG_IND_CMD_DONE_RD(value);
	}
	mdelay(1);
}

static u32 xgenet_sds_ind_csr_reg_rd(struct apm_enet_priv *priv, u32 offset)
{
	u32 value;
	u32 SDS_Ind_Command_Addr;
	u32 SDS_Ind_Command_Done;

	PHY_PRINT("%a offset=0x%x\n", __func__, offset);
	/* write 1 to clear indirect error detected/ind cmd done */
	value = (CFG_IND_ADDR_WR(0)
			| CFG_IND_ERR_WR(1)
			| CFG_IND_CMD_DONE_WR(1)
			| CFG_IND_RD_CMD_WR(0)
			| CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	PHY_PRINT("%a value=0x%x -> 0x%llx\n", __func__, value,
			XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);

	SDS_Ind_Command_Addr = offset; /* offset[15:0] */
	value = (CFG_IND_ADDR_WR(SDS_Ind_Command_Addr)
			| CFG_IND_ERR_WR(0)
			| CFG_IND_CMD_DONE_WR(0)
			| CFG_IND_RD_CMD_WR(1)
			| CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	PHY_PRINT("%a cmd value=0x%x\n", __func__, value);

	SDS_Ind_Command_Done = 0;
	while (SDS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, &value);
		PHY_PRINT("%a read cmd_done=0x%x <- 0x%llx\n", __func__, value,
				XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);
		SDS_Ind_Command_Done = CFG_IND_CMD_DONE_RD(value);
	}

	apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_RDATA_REG_ADDR, &value);
	PHY_PRINT("%a value=0x%x\n", __func__, value);
	mdelay(1);

	return value;
}

static u32 sm_xgenet_set(u32 ori_val, u32 set_val, u32 end, u32 start)
{
	u32 mask = 0, new_val;
	int i;

	for (i = 0; i < 16; i++) {
		if ((i < start)||(i > end))
			mask = mask | (1 << i);
		else
			mask = mask | (0 << i);
	}
	new_val = (ori_val & mask) | (set_val << start);
	return new_val;
}

static void serdes_reset_rxd_rxa(struct apm_enet_priv *priv, int port)
{
	u32 value;
	int inst_base;

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Reset Digital ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 8, 8); /* digital reset == 1'b0 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);

	PHY_PRINT(" CH0 RX Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 7, 7); /* analog reset == 1'b0 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);

	PHY_PRINT(" CH0 RX Remove Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 7, 7); /* analog reset == 1'b1 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);

	PHY_PRINT(" CH0 RX Remove Reset Digital ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 8, 8); /* digital reset == 1'b1 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
}
#ifdef CONFIG_STORM
static void serdes_reset_rxd(struct apm_enet_priv *priv)
{
	u32 value;
	int inst_base;

	inst_base = 0x0400;
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 8, 8); /* digital reset == 1'b0 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 8, 8); /* digital reset == 1'b1 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);
}

void serdes_reset_rxa(struct apm_enet_priv *priv)
{
	u32 value;
	int inst_base;

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 7, 7); /* analog reset == 1'b0 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);

	PHY_PRINT(" CH0 RX Remove Reset Analog ...\n\r");
	value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 7, 7); /* analog reset == 1'b1 */
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
	mdelay(8);
}

static void serdes_calib(struct apm_enet_priv *priv, u32 rev)
{
	u32 value; 
	u32 inst_base;
	u32 infmode = 1;
	int man_pvt_cal = 0;

	inst_base = 0x0400;
	if (rev <= 2)
		man_pvt_cal = 1;
 
	if (priv->phy_mode == PHY_MODE_SGMII) {
		infmode = 0;
		/* CMU_reg6  : Enable Manual PVT calibration - Anil */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
		value = sm_xgenet_set(value,infmode ?
			man_pvt_cal : man_pvt_cal, 2, 2);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

		/* TERM CALIBRATION KC_SERDES_CMU_REGS_CMU_REG17__ADDR */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x0D << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value |= (1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		/* DOWN CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x2A << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= 1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* UP CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x2B << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= (1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~(1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* Anil adding 5-2-2013 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value &= ~0x7F;  /* mask */
		value |= 0x0E; /*Anil 02/08/13 */
		xgenet_sds_ind_csr_reg_wr(priv,inst_base + 14*2, value);
	} else { /* XGMII */
		/* CMU_reg6  : Enable Manual PVT calibration - Anil */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
		value = sm_xgenet_set(value,
			infmode ? man_pvt_cal: man_pvt_cal, 2, 2);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

		/* TERM CALIBRATION KC_SERDES_CMU_REGS_CMU_REG17__ADDR */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		if (rev < 2)
			value |= 0x0D << 8;
		else
			value |= 0x12 << 8;

		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value |= 1 << 15;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		/* DOWN CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= 0x2A << 8; /* 07/31/2013 */
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= 1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* UP CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= 0x2B << 8; /* 07/31/2013 */
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= (1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~(1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* Anil adding 5-2-2013 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value &= ~0x7F;  /* mask */
		value |= 0x0E; /*Anil 02/08/13 */
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 14*2, value);
	}
	udelay(10);
}

static void xgenet_sds_CMU_cfg(struct apm_enet_priv *priv, u32 rev)
{
	u32 value;
	u32 infmode = 1; /* xgmii */
	u32 tmp;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		infmode = 0;
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*12);
		value = sm_xgenet_set(value, 1, 7, 4);
		xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*12);
		/* CMU_reg13 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*13);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12); */
		value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8); */
		value = sm_xgenet_set(value,infmode ? 15 : 1, 11, 8);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 7, 4);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*13, value);

		/* CMU_reg14 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*14);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 15, 12);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 11, 8);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4); */
		value = sm_xgenet_set(value,infmode ? 15 : 1, 7, 4);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0); */
		value = sm_xgenet_set(value,infmode ? 15 : 4, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*14, value);
		ENET_DEBUG("%a PHY_MODE_SGMII\n", __func__);
	}
	/* CMU_reg1 */
	value =  xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	value = sm_xgenet_set(value, 0, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);
	/* CMU_reg2 */
	value =  xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*2);
	/* Ref clk divider setting */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 14);
	/* Feedback divider setting */
	value = sm_xgenet_set(value,infmode ? 32 : 49, 13, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*2, value);

	/* CMU_reg9 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*9);
	/* Post Divider */
	value = sm_xgenet_set(value,infmode ? 0 : 1, 3, 3);
	/* Word mode for PClk */
	value = sm_xgenet_set(value,infmode ? 6 : 1, 6, 4);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*9, value);

	/* CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	/* PLL BW setting */
	value = sm_xgenet_set(value,infmode ? 11 : 10, 13, 10);
	/*  PLL BW setting */
	value = sm_xgenet_set(value,infmode ? 5 : 1, 9, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);

	/* CMU_reg3 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*3);
	value = sm_xgenet_set(value,infmode ? 15 : 0, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*3, value);

	/* CMU_reg2 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*2);
	value = sm_xgenet_set(value,infmode ? 5 : 15, 4, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*2, value);

	/* CMU_reg5 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*5);
	value = sm_xgenet_set(value,infmode ? 0 : 3, 15, 14);
	value = sm_xgenet_set(value,infmode ? 0 : 3, 13, 12);
	value = sm_xgenet_set(value,infmode ? 4 : 7, 3, 1);
	/* pll_lock_resolution. Provided by Anil */
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*5, value);

	/*  CMU_reg4 */
	/*
	   value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*4);
	   value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 0);
	   xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*4, value);
	 */

	/* CMU_reg8 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*8);
	/* ucdiv. added by satish for correct usr clock - 01 Feb */
	value = sm_xgenet_set(value,infmode ? 7 : 7, 7, 5);
	/* tx_data_rate_ch3,2,1,0 = 2'h2 */
	value = sm_xgenet_set(value, infmode ? 0: 0xAA, 15, 8);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*8, value);

	/* CMU_reg6 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
	tmp = (rev == 4) ? 0 : 0;
	value = sm_xgenet_set(value,infmode ? tmp : 0, 10, 9);
	value = sm_xgenet_set(value,infmode ? 1 : 0, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

	/* CMU_reg32 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	/* Bias Current adj */
	tmp = (rev == 4) ? 3 : 3;
	value = sm_xgenet_set(value,infmode ? tmp : 3, 8, 7);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);

	/*  CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	/* Manual cal enable */
	value = sm_xgenet_set(value,infmode ?
			pll_manualcal : pll_manualcal, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);

	/* CMU_reg3 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*3);
	value = sm_xgenet_set(value,infmode ? 5 : 0xd, 15, 10);
	/* Init Momsel */
	value = sm_xgenet_set(value,infmode ? 16 : 0xd, 9, 4);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*3, value);

	/* CMU_reg34 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*34);
	value = sm_xgenet_set(value,infmode ? 2 : 2, 15, 12);
	value = sm_xgenet_set(value,infmode ? 10 : 10, 11, 8);
	value = sm_xgenet_set(value,infmode ? 2 : 2, 7, 4);
	value = sm_xgenet_set(value,infmode ? 10 : 10, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*34, value);

	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	value = sm_xgenet_set(value,infmode ? 7 : 7, 7, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	/* CMU_reg16 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
	value = sm_xgenet_set(value,infmode ? 7 : 7, 4, 2);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

	/* CMU_reg30 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*30);
	/* Lock count Wait time */
	value = sm_xgenet_set(value,infmode ? 3 : 3, 2, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*30, value);
	if (infmode) {
		/* CMU_reg13 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*13);
		/* Delay time between state transition */
		value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*13, value);

		/*  CMU_reg14 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*14);
		/* Delay time between state transition. */
		value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4);
		value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*14, value);
	}

	/* CMU_reg30 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*30);
	/*
	 * Ref Divider for PCI Gen3 mode - dont care,
	 * FB divider for Gen3 mode - dont care
	 * Post Divider for Gen3 mode - dont care
	 */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*30, value);

	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* PCIE gen3 , driven by Pipe */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	/* CMU_reg32 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	value = sm_xgenet_set(value,infmode ? 3 : 3, 2, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);

	/* CMU_reg31 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*31);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*31, value);

	/* CMU_reg37 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*37);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*37, value);
}

static void xgenet_sds_rxtx_cfg(struct apm_enet_priv *priv, u32 rev)
{
	u32 infmode = 1; /* xgmii */
	u32 value, inst, inst_base;
	u32 pq_reg = 0xa, tmp;

	if (priv->phy_mode == PHY_MODE_SGMII)
		infmode = 0;
	for(inst = 0;inst < 1;inst++) {
		inst_base = 0x0400 + inst*0x0200;
		/**  Tx CONTROL **/
		/* rxtx_reg4 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 4*2);
		value = sm_xgenet_set(value,infmode ? 0 : 2, 15, 14);
		value = sm_xgenet_set(value,infmode ? 6 : 1, 13, 11);
		value = sm_xgenet_set(value,infmode ? 4 : 4, 10, 8);
		xgenet_sds_ind_csr_reg_wr(priv,inst_base + 4*2, value);

		/* CMU_reg16 */
		/* TX Rate Change enable: Toggle 0-1-0 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU +2*16);
		value = sm_xgenet_set(value, 0, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 5, 5);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg6 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 6, 6);
		value = sm_xgenet_set(value,infmode ? 15 : 8, 10, 7);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/* rxtx_reg5 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 5*2);
		value = sm_xgenet_set(value,infmode ? 2 : 0, 15, 11);
		value = sm_xgenet_set(value,infmode ? 15 : 0, 10, 5);
		value = sm_xgenet_set(value,infmode ? 2 : 0, 4, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 5*2, value);

		/* rxtx_reg61 - Don't care */

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg4 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 4*2);
		/* TX Forward Loopback enable */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 4*2, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg6 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/* rxtx_reg145 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 145*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 145*2, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/** RX Control **/
		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 14, 14);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 7, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg1 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 1*2);
		if (infmode) {
			value = sm_xgenet_set(value,infmode ? 7 : 7, 15, 12);
			/* RXIREF_ADJ  */
			value = sm_xgenet_set(value,infmode ? 3 : 7, 4, 1);
		}
		else {
			/* RX AC common model select */
			value = sm_xgenet_set(value,infmode ? 7 : 7, 15, 12);
		}
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 1*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 1, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg61 - Don't care */

		/* rxtx_reg7 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 7*2);
		value = sm_xgenet_set(value,infmode ? 4 : 4, 5, 3);
		value = sm_xgenet_set(value,infmode ? 6 : 1, 13, 11);
		value = sm_xgenet_set(value,infmode ? 0 : 2, 10, 9);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 7*2, value);

		/* CMU_reg16 */
		/* RX rate change enable: Toggle 0-1-0 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		/* rxtx_reg148 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 148*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 148*2, value);

		/* rxtx_reg149 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 149*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 149*2, value);

		/* rxtx_reg150 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 150*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 150*2, value);

		/* rxtx_reg151 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 151*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 151*2, value);

		/* rxtx_reg147 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 147*2);
		value = sm_xgenet_set(value,infmode ? 6 : 6, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 147*2, value);

		/* rxtx_reg1 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 1*2);
		tmp = 16;
		if (rev == 4) {
			switch (priv->port) {
			case XGENET_0:
				tmp = 24;
				break;
			case XGENET_1:
				tmp = 28;
				break;
			case XGENET_2:
				tmp = 16;
				break;
			case XGENET_3:
				tmp = 28;
				break;
			}
		}
		value = sm_xgenet_set(value,infmode ? tmp : 28, 11, 7);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 1*2, value);

		/* rxtx_reg0 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0*2);
		value = sm_xgenet_set(value,infmode ? 16 : 13, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 13, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 13, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0*2, value);

		/* rxtx_reg14 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 14*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		/* SUM Offset enable */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 2, 2);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		/* Latch Offset Enable */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg128 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 128*2);
		value = sm_xgenet_set(value,infmode ? 3 : 3, 3, 2);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 128*2, value);

		/* rxtx_reg127 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);

		/* rxtx_reg8 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 14, 14);
		value = sm_xgenet_set(value,infmode ? 0 : 1, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/* rxtx_reg61 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 61*2);
		value = sm_xgenet_set(value,infmode ? 7 : 1, 13, 10);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 61*2, value);

		/* rxtx_reg125 */
		/* NOTE: Need to implement per port contrl */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 125*2);
		/* IQ phase different */
		/* A2 xgmii port0-2=0xa port3=0x10 
		      sgmii 0
		   A1 xgmii 0xa
		      sgmii 0
		*/
		if (infmode) {
			if ((rev >= 2) && (priv->port == XGENET_3))
				pq_reg = 0x10;
		} else
			pq_reg = 0;
		value = sm_xgenet_set(value,infmode ? pq_reg: 0, 15, 9);
		/* Phase loop adaptation manual enable */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 1, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 125*2, value);

		/* rxtx_reg11 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 11*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 11*2, value);

		/* rxtx_reg61 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 61*2);
		value = sm_xgenet_set(value,infmode ? 1 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 61*2, value);

		/* rxtx_reg102 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 102*2);
		value = sm_xgenet_set(value,infmode ? 3 : 3, 6, 5);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 102*2, value);

		/* rxtx_reg8 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/* rxtx_reg96 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 96*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 96*2, value);

		/* rxtx_reg97 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 97*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 97*2, value);

		/* rxtx_reg98 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 98*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 98*2, value);

		/* rxtx_reg99 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 99*2);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 99*2, value);

		/* rxtx_reg100 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 100*2);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 100*2, value);

		/* rxtx_reg101 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 101*2);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		/* CDR Phase Loop BW */
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 101*2, value);

		/* rxtx_reg8 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		/* RX los disable */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/* rxtx_reg26 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 26*2);
		/* BLWC Enable */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 26*2, value);

		/* rxtx_reg31 */
		if (infmode == 0) {
			value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 31*2);
			/* H0 prese */
			value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 9);
			xgenet_sds_ind_csr_reg_wr(priv, inst_base + 31*2, value);
		}

		/* rxtx_reg81 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 81*2);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 81*2, value);

		/* rxtx_reg82 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 82*2);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 82*2, value);

		/* rxtx_reg83 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 83*2);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE BW select */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 83*2, value);

		/* rxtx_reg84 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 84*2);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 84*2, value);

		/* rxtx_reg85 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 85*2);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 85*2, value);

		/* rxtx_reg86 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 86*2);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* CDR phase Adaptation Loop BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 86*2, value);

		/* rxtx_reg87 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 87*2);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 87*2, value);

		/* rxtx_reg88 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 88*2);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 88*2, value);

		/* rxtx_reg89 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 89*2);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		/* DFE Main Tap (Threshold) BW */
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 89*2, value);

		/* rxtx_reg145 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 145*2);
		/* DFE Configuration Selection */
		value = sm_xgenet_set(value,infmode ? 3 : 3, 15, 14);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 145*2, value);

		/* rxtx_reg28 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 28*2);
		/* DFE tap enables */
		value = sm_xgenet_set(value,infmode ? 0x7 : 0x0, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 28*2, value);

		/* rxtx_reg7 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 7*2);
		/* RX Resetn */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		/* RX Forward Loopback enable */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 14, 14);
		/* RX Bist enable for PRBS transfer */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 7*2, value);

		/* rxtx_reg6 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		/* Bert Error count capture */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		/* RX Serial Data swap(P and N polarity) */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);
	}
}

void sm_xgenet_module_program_all_regs(struct apm_enet_priv *priv, u32 rev)
{
	xgenet_sds_CMU_cfg(priv, rev);
	xgenet_sds_rxtx_cfg(priv, rev);
}

static void  serdes_pdown_force_vco(struct apm_enet_priv *priv)
{
}

static void force_lat_summer_cal(struct apm_enet_priv *priv)
{
	u32 inst_base = 0x400;
	u32 value;

	/* SUMMer calib 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 1, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	mdelay(4);
	/* SUMMer calib 0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 0, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	mdelay(4);
	/* Latch calib 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 1, 2, 2);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	mdelay(4);
	/* Latch calib 0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 0, 2, 2);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	mdelay(4);
}

static u32 apm_xgenet_serdes_init(struct apm_enet_priv *priv, u32 rev)
{
	u32 value, loop;
	u32 refclksel, refclk_cmos_sel;
	u32 rx_clk_inv = 0;
	u32 pll_ready;
	u32 port_addr, i, infmode;
	u32 pll_lock, vco_calibration;
	u32 tx_ready, rx_ready;
#ifdef PHY_DEBUG
	u32 rndrefclk;
#endif
	int man_pvt_cal = 0;

	if (rev <= 2) {
		man_pvt_cal = 1;
		if (rev < 2)
			rx_clk_inv = 1;
	}

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR, &value);
	/* xgmii, infmode = 1 */
	infmode = CFG_SGMII_EN_RD(value) == 2 ? 1: 0;
	PHY_PRINT("%a infmode = 0x%x\n", __func__, infmode);
	/* module_init_enet_serdes */
	refclksel = 0;
	refclk_cmos_sel = 0;
#ifdef PHY_DEBUG
	rndrefclk = (refclksel << 1) | refclk_cmos_sel;
#endif
	PHY_PRINT("INIT_SERDES : Config Ref Clock\n");
	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	value = sm_xgenet_set(value, refclksel, 13, 13);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);
	/* CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	value = sm_xgenet_set(value, refclk_cmos_sel, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);
	/* CMU_reg37 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*37);
	/* CMU_reg36 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*36);
	/* CMU_reg16 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

	if (infmode) /* xgmii */
		value = 0x306430;
	else		/* SGMII */
		value = 0x305030;

	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_CFG_ADDR, value);
	if (refclk_cmos_sel) {
		i = 0;
		do {
			apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_STAT_ADDR, &value);
			PHY_PRINT("INIT_SERDES : waiting for XGENET PLL to lock\n");
			if (i++ > 10)
				break;
			udelay(100);
		} while (value == 0);
	}
	/* program PLL output clock divider value after PLL has locked */
	if (infmode) /* xgmii */
		value = 0x4;
	else /* SGMII */
		value = 0x5;
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_DIV_CFG_ADDR, value);

	/* XGENET_SDS_RST_CTL, Assert all reset */
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0xDE);
	udelay(2);

	PHY_PRINT("INIT_SERDES : REFCLK using -- %a\n",
		(rndrefclk == 0) ? "External differential clk" : "Internal single ended (cmos) clk");
	PHY_PRINT("INIT_SERDES : %a/ENET using -- LSPLL\n",infmode ? "XGMII" : "SGMII");

	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CTL0_ADDR, 0);
	sm_xgenet_module_program_all_regs(priv, rev);

	if (rx_clk_inv) {
		PHY_PRINT("INIT_SERDES : Enable RXCLK Inversion.");
		for (i = 0; i < 1;  i++) {
			PHY_PRINT("INIT_SERDES : RXTX Inst %x\n", i);
			port_addr = 0x0400 + i*0x0200;
			value = xgenet_sds_ind_csr_reg_rd(priv, port_addr + 0xD*2);
			value = sm_xgenet_set(value, 1, 13, 13);
			xgenet_sds_ind_csr_reg_wr(priv, port_addr + 0xD*2, value);
		}
	}
#ifdef APM_XGENET_XGMII_TX2RX_LOOPBACK	/* one port only */
	/* rxtx.reg4.tx_loopback_buf_en = 1 */
	PHY_PRINT("INIT_SERDES : SERDES XGMII Tx2Rx Loopback\n");
	value = xgenet_sds_ind_csr_reg_rd(priv, 0x0400 + 0x4*2);
	value = sm_xgenet_set(value, 1, 6, 6);
	xgenet_sds_ind_csr_reg_wr(priv, 0x0400 + 0x4*2, value);
	/* rxtx.reg7.loopback_ena_ctle = 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, 0x0400 + 0x7*2);
	value = sm_xgenet_set(value, 1, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, 0x0400 + 0x7*2, value);
#endif
	/* De-assert all reset */
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0xDF);
	udelay(2);

	if (infmode && !rx_clk_inv )
		serdes_pdown_force_vco(priv);
	if (man_pvt_cal) {
		serdes_calib(priv, rev);
		serdes_reset_rxd_rxa(priv, 0);
	}

	/* INIT_SERDES : Check PLL Ready/LOCK and VCO Calibration status */
	PHY_PRINT("INIT_SERDES : Check PLL Ready/LOCK and VCO Calibration status\n");
	loop = 1000;
	do {
		mdelay(1);
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CMU_STATUS0_ADDR, &value);
		pll_ready = CFG_CMU_O_PLL_READY0_RD(value);
		vco_calibration = CFG_CMU_O_VCO_CALDONE0_RD(value) ;
		pll_lock = CFG_CMU_O_PLL_LOCK0_RD(value);
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RXTX_STATUS_ADDR, &value);
		tx_ready = CFG_TX_O_TX_READY_RD(value);
		rx_ready = CFG_RX_O_RX_READY_RD(value);
		if (((pll_ready && pll_lock && vco_calibration)) &&
			(tx_ready && rx_ready))
			break;
		loop--;

	} while (loop != 0);

	if (!loop) {
		ENET_PRINT("INIT_SERDES : PLL is %aREADY\n", pll_ready ? "" : "not ");
		ENET_PRINT("INIT_SERDES : PLL %aLOCKed\n",
			pll_lock ? "" : "not ");
		ENET_PRINT("INIT_SERDES : PLL VCO Calibration %a\n",
			vco_calibration ? "Successful" : "not Successful");
		PHY_PRINT("INIT_SERDES : Check TX/RX Ready\n");
		ENET_PRINT("INIT_SERDES : TX is %aready\n", tx_ready ? "" : "not ");
		ENET_PRINT("INIT_SERDES : RX is %aready\n", rx_ready ? "" : "not ");
		ENET_PRINT("INIT_SERDES : loop %d\n", loop);
	}
	return pll_ready;
}

static int get_avg(int accum,int samples){
  return ((accum + (samples/2))/samples);
}

static void gen_avg_val(struct apm_enet_priv *priv)
{
	int avg_loop = 10;
	int MAX_LOOP = 10;
	int lat_do = 0, lat_xo = 0, lat_eo = 0, lat_so = 0;
	int lat_de = 0, lat_xe = 0, lat_ee = 0, lat_se = 0;
	int sum_cal = 0;
	int lat_do_itr,lat_xo_itr,lat_eo_itr,lat_so_itr;
	int lat_de_itr,lat_xe_itr,lat_ee_itr,lat_se_itr;
	int sum_cal_itr = 0;
	int fail_even = 0;
	int fail_odd = 0;
	u32 inst_base = 0x400;
	u32 value;

	ENET_DEBUG("\n Generating Average calibration Value for Port %d \n",priv->port);
	/* Enable RX Hi-Z termination enable */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
	value = sm_xgenet_set(value,1, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);
	/* Turn off DFE  */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 28*2);
	value = sm_xgenet_set(value, 0x0, 15, 0);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 28*2, value);
	/* DFE Presets to zero  */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 31*2);
	value = sm_xgenet_set(value, 0x0, 15, 0);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 31*2, value);

	while (avg_loop > 0) {
		force_lat_summer_cal(priv);
		mdelay(40);
		value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG21__ADDR);
		lat_do_itr = FIELD_RXTX_REG21_DO_LATCH_CALOUT_RD(value);
		lat_xo_itr = FIELD_RXTX_REG21_XO_LATCH_CALOUT_RD(value);
		fail_odd   = FIELD_RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(value);

		value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG22__ADDR);
		lat_eo_itr = FIELD_RXTX_REG22_EO_LATCH_CALOUT_RD(value);
		lat_so_itr = FIELD_RXTX_REG22_SO_LATCH_CALOUT_RD(value);
		fail_even  = FIELD_RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(value);

		value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG23__ADDR);
		lat_de_itr = FIELD_RXTX_REG23_DE_LATCH_CALOUT_RD(value);
		lat_xe_itr = FIELD_RXTX_REG23_XE_LATCH_CALOUT_RD(value);

		value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG24__ADDR);
		lat_ee_itr = FIELD_RXTX_REG24_EE_LATCH_CALOUT_RD(value);
		lat_se_itr = FIELD_RXTX_REG24_SE_LATCH_CALOUT_RD(value);

		value  = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG121__ADDR);
		sum_cal_itr = FIELD_RXTX_REG121_SUMOS_CAL_CODE_RD(value);

		if ((fail_even == 0 || fail_even == 1) &&
				(fail_odd == 0 || fail_odd == 1)) {
			lat_do += lat_do_itr;
			lat_xo += lat_xo_itr;
			lat_eo += lat_eo_itr;
			lat_so += lat_so_itr;
			lat_de += lat_de_itr;
			lat_xe += lat_xe_itr;
			lat_ee += lat_ee_itr;
			lat_se += lat_se_itr;
			sum_cal += sum_cal_itr;
			avg_loop--;
		}
		serdes_reset_rxd(priv);
	}

	/* Update with Average Value */
	/* Latch Calibration Value */
	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG127__ADDR);
	value = FIELD_RXTX_REG127_DO_LATCH_MANCAL_SET(value,get_avg(lat_do,MAX_LOOP));
	value = FIELD_RXTX_REG127_XO_LATCH_MANCAL_SET(value,get_avg(lat_xo,MAX_LOOP));
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG127__ADDR, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG128__ADDR);
	value = FIELD_RXTX_REG128_EO_LATCH_MANCAL_SET(value,get_avg(lat_eo,MAX_LOOP));
	value = FIELD_RXTX_REG128_SO_LATCH_MANCAL_SET(value,get_avg(lat_so,MAX_LOOP));
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG128__ADDR, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG129__ADDR);
	value = FIELD_RXTX_REG129_DE_LATCH_MANCAL_SET(value,get_avg(lat_de,MAX_LOOP));
	value = FIELD_RXTX_REG129_XE_LATCH_MANCAL_SET(value,get_avg(lat_xe,MAX_LOOP));
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG129__ADDR, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG130__ADDR);
	value = FIELD_RXTX_REG130_EE_LATCH_MANCAL_SET(value,get_avg(lat_ee,MAX_LOOP));
	value = FIELD_RXTX_REG130_SE_LATCH_MANCAL_SET(value,get_avg(lat_se,MAX_LOOP));
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG130__ADDR, value);

	/* Summer Calibration Value */
	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG14__ADDR);
	value = FIELD_RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(value,get_avg(sum_cal,MAX_LOOP));
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG14__ADDR, value);
	if (priv->phy_mode == PHY_MODE_SGMII)
		mdelay(40);
	ENET_DEBUG("\n Average Value : \n");
	ENET_DEBUG("DO=0x%x  XO=0x%x  EO=0x%x  SO=0x%x\n",
		get_avg(lat_do,MAX_LOOP),get_avg(lat_xo,MAX_LOOP),
		get_avg(lat_eo,MAX_LOOP),get_avg(lat_so,MAX_LOOP));
	ENET_DEBUG("DE=0x%x  XE=0x%x  EE=0x%x  SE=0x%x\n",
		get_avg(lat_de,MAX_LOOP),get_avg(lat_xe,MAX_LOOP),
		get_avg(lat_ee,MAX_LOOP),get_avg(lat_se,MAX_LOOP));
	ENET_DEBUG("sum_cal = 0x%x\n",get_avg(sum_cal,MAX_LOOP));

	/* Manual Summer Calibration */
	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG14__ADDR);
	value = FIELD_RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(value,0x1);
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG14__ADDR, value);
	ENET_DEBUG("Manual Summer Calibration Enabled\n");
	mdelay(40);

	/* Manual Latch Calibration */
	value = xgenet_sds_ind_csr_reg_rd(priv, KC_SERDES_RXTX_REGS_RXTX_REG127__ADDR);
	value = FIELD_RXTX_REG127_LATCH_MAN_CAL_ENA_SET(value,0x1);
	xgenet_sds_ind_csr_reg_wr(priv, KC_SERDES_RXTX_REGS_RXTX_REG127__ADDR, value);
	ENET_DEBUG("Manual Latch Calibration Enabled\n");
	mdelay(40);

	/* Turn on DFE  */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 28*2);
	value = sm_xgenet_set(value,0x7, 15, 0);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 28*2, value);
	/* DFE Presets to 0x2a00(default) */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 31*2);
	value = sm_xgenet_set(value, 0x2a00, 15, 0);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 31*2, value);
	/* Disable RX Hi-Z termination enable */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
	value = sm_xgenet_set(value,0, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);
	mdelay(10);
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 121*2);
}
#endif

void xgenet_serdes_deassert(struct apm_enet_priv *priv)
{
	u32 data;

	/* Clear Software Reset for Serdes */
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, ENET_SRST_ADDR, &data);
	PHY_PRINT("%a read 0x%x <- 0x%llx\n", __func__,
			data, XGENET_CLKRST_CSR_BASE_ADDR + ENET_SRST_ADDR);

	data = ENET_SRST_DEFAULT;
	PHY_PRINT("%a write 0x%x -> 0x%llx\n", __func__,
			data, XGENET_CLKRST_CSR_BASE_ADDR+ ENET_SRST_ADDR);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, ENET_SRST_ADDR, data);
	udelay(2);
}

void apm_xgmac_set_preamble_length(struct apm_enet_priv *priv, u8 length)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR,
				PREAMBLE_LENGTH2_SET(data, length));
	}
}

void apm_xgmac_set_intf_mode(struct apm_enet_priv *priv, u8 intf_mode)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR,
				ENET_INTERFACE_MODE2_SET(data, intf_mode));
	}
}

int apm_xgmac_get_intf_mode(struct apm_enet_priv *priv)
{
	u32 data = 0;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);
		data = ENET_INTERFACE_MODE2_RD(data);
	}

	return data;
}

void apm_xgmac_huge_frame_enable(struct apm_enet_priv *priv, u8 enable)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		if (enable)
			data |= HUGE_FRAME_EN2_MASK;
		else
			data &= ~HUGE_FRAME_EN2_MASK;

		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, data);
	}
}

void apm_xgmac_len_field_check_enable(struct apm_enet_priv *priv, u8 enable)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		if (enable)
			data |= LENGTH_CHECK2_MASK;
		else
			data &= ~LENGTH_CHECK2_MASK;

		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, data);
	}
}

static void module_xgenet_config_sgmii_autoneg(struct apm_enet_priv *priv, int autoneg)
{
	u32 data, speed, times = 0;

	/* All internal PHY addresses are shifted by 2 bits */
reset_phy:
	ENET_DEBUG("%a autoneg=%d\n", __func__, autoneg);
	apm_genericmiiphy_write(priv, INT_PHY_ADDR,
			SGMII_TBI_CONTROL_ADDR >> 2, 0x0);
	apm_genericmiiphy_read(priv, INT_PHY_ADDR,
			SGMII_TBI_CONTROL_ADDR >> 2, &data);
	if (!priv->mac_to_mac) {
		if (autoneg) {
			/* Bring PHY out of reset; Enable An, autonegotiation */
			PHY_PRINT(" Bring PHY out of reset; Enable An\n");
			apm_genericmiiphy_write(priv, INT_PHY_ADDR,
					SGMII_CONTROL_ADDR >> 2, 0x9140);
		}
		else {
			/* Bring PHY out of reset; No autonegotiation */
			PHY_PRINT(" Bring PHY out of reset; NO An\n");
			apm_genericmiiphy_write(priv, INT_PHY_ADDR,
					SGMII_CONTROL_ADDR >> 2, 0x8000);
		}
		udelay(1000);
		if (autoneg) {
			int loop = 50;

			/* Check autonegotiation status */
			apm_genericmiiphy_read(priv, INT_PHY_ADDR,
					SGMII_STATUS_ADDR >> 2, &data);
			PHY_PRINT(" autonegotiation status=0x%x\n", data);
			while  (AUTO_NEGOTIATION_COMPLETE_RD(data) == 0 ||
					LINK_STATUS_RD(data) == 0) {
				PHY_PRINT(" Autonegotiation status=0x%x\n", data);
				apm_genericmiiphy_read(priv, INT_PHY_ADDR,
						SGMII_STATUS_ADDR >> 2, &data);
				if (loop-- == 0)
					break;
				udelay(100);
				PHY_PRINT(" Autonegotiation status=0x%x %a\n", data, __func__);
			}
			if (LINK_STATUS_RD(data) == 0) {/*  no link wih SGMII */
				if (times ++ < 5) {
					PHY_PRINT(".");
					apm_genericmiiphy_write(priv, INT_PHY_ADDR,
							SGMII_TBI_CONTROL_ADDR >> 2, 0x8000);
					serdes_reset_rxd_rxa(priv, 0);
					goto reset_phy;
				}
			}
		} else {
			PHY_PRINT(" %a non-autoneg NOT supported\n", __func__);
		}
		if (!priv->phyless) {
			apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &data);
			priv->link_status = PORT_RD(data);
		} else
			priv->link_status = 1;
		/* Get the final speed information from SGMII */
		apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR >> 2, &data);
		speed = LINK_SPEED_F1_RD(data);
	} else {
		speed = priv->desired_speed;
		priv->link_status = 1;
	}

	switch(speed) {
	case PHY_SPEED_10:
		speed = APM_ENET_SPEED_10;
		break;
	case PHY_SPEED_100:
		speed = APM_ENET_SPEED_100;
		break;
	default:
		speed = APM_ENET_SPEED_1000;
		break;
	}

	if (priv->link_status)
		PHY_PRINT("Phy Speed is :%d \n", speed);
	else
		PHY_PRINT("Port%d is down\n", priv->port);

	priv->speed = speed;
}

static int apm_mcxmac_init(struct apm_enet_priv *priv,
		unsigned char *dev_addr, int speed, int crc)
{
	u32 value;
	u32 temp;
	u32 addr_hi;
	u32 addr_lo;

	u32 interface_control;
	u32 mac_config_2;
	u32 icm_config0 = 0x0008503f;
	u32 ecm_config0 = 0x00000032;
	u32 enet_spare_cfg = 0x00006040;

	ENET_DEBUG("%a priv->phy_mode=0x%x\n", __func__, priv->phy_mode);

	/*sm_xgenet_module_level_eee_init(priv); */
	value = RESET_TX_FUN1_WR(1) |
		RESET_RX_FUN1_WR(1) |
		RESET_TX_MC1_WR(1)  |
		RESET_RX_MC1_WR(1)  |
		SIM_RESET1_WR(1)    |
		SOFT_RESET1_WR(1);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, value);
	apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &temp);
	udelay(1);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, 0);

	/* Initialize the MAC configuration #1 register */
	value = TX_EN1_WR(1)	  |
		TX_FLOW_EN1_WR(0) |
		LOOP_BACK1_WR(0)  |
		RX_FLOW_EN1_WR(0);

	/* Need this? rd_phy_reg_per_port(port_id,0x1e,M_SGMII_SGMII_TBI_CONTROL__ADDR,&data); */

	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, value);

#ifdef APM_ENET_SERDES_LOOPBACK
	module_xgenet_config_sgmii_autoneg(priv, 0);
#else
	if (!priv->mac_to_mac) {
		if (priv->autoneg_set) {
			if (!priv->link_status || priv->phyless)
				module_xgenet_config_sgmii_autoneg(priv, 1);
		}
	} else {
		module_xgenet_config_sgmii_autoneg(priv, 0);
	}
#endif
	/* SGMII follows */
	apm_enet_read(priv, BLOCK_ETH_CSR,
			ENET_SPARE_CFG_REG_ADDR, &enet_spare_cfg);

	if (speed == APM_ENET_SPEED_10) {
		interface_control = ENET_LHD_MODE_WR(0) |
			ENET_GHD_MODE_WR(0);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(1) | /* 10Mbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);
		icm_config0 = 0x0000503f;
		ecm_config0 = 0x600032;
	} else if (speed == APM_ENET_SPEED_100) {
		interface_control = ENET_LHD_MODE_WR(1);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(1) | /* 100Mbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);
		icm_config0 = 0x0004503f;
		ecm_config0 = 0x600032;
	} else {
		interface_control = ENET_GHD_MODE_WR(1);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(2) | /* 1Gbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);

		icm_config0 = 0x0008503f;
		ecm_config0 = 0x32;
	}
	enet_spare_cfg |= 0x00006040;

	/* Initialize the MAC configuration #2 register */
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, mac_config_2);

	/* Initialize the Interface Control Register */
	apm_enet_write(priv, BLOCK_MCX_MAC, INTERFACE_CONTROL_ADDR,
			interface_control);

	/* Initialize the Maximum Frame Length register */
	value = MAX_FRAME_LEN_WR(APM_ENET_FRAME_LEN);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAX_FRAME_LEN_ADDR, value);

	/* Program the station MAC address */
	addr_hi = *(u32 *) &dev_addr[0];
	addr_lo = *(u16 *) &dev_addr[4];
	addr_lo <<= 16;

	if (priv->phy_mode == PHY_MODE_SGMII)
		addr_lo = (addr_lo & 0xFFFF0100) | 0x1e;
	else
		addr_lo |= (priv->phy_addr & 0xFFFF);

	ENET_DEBUG("MAC addr hi: %x\n", addr_hi);
	apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR0_ADDR, addr_hi);
	ENET_DEBUG("MAC addr lo: %x\n", addr_lo);
	apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR1_ADDR, addr_lo);

	/* Rtype should be copied from FP */
	value = 0;
	apm_enet_write(priv, BLOCK_ETH_CSR,
			RSIF_RAM_DBG_REG0_ADDR, value);

	apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			ICM_CONFIG0_REG_0_ADDR, icm_config0);

	apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			ECM_CONFIG0_REG_0_ADDR, ecm_config0);

	/* TCP MSS  */
	apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &value);

	apm_enet_write(priv, BLOCK_ETH_CSR, TSIF_MSS_REG0_0_ADDR,
			CFG_TSIF_MSS_SZ00_SET(value, DEFAULT_TCP_MSS));

	apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &value);

	if (speed != APM_ENET_SPEED_10 && speed != APM_ENET_SPEED_100) {
		apm_enet_read(priv, BLOCK_ETH_CSR, DEBUG_REG_ADDR, &value);
		value |= CFG_BYPASS_UNISEC_TX_WR(1) |
			CFG_BYPASS_UNISEC_RX_WR(1);
		apm_enet_write(priv, BLOCK_ETH_CSR, DEBUG_REG_ADDR, value);
	}
	apm_enet_read(priv, BLOCK_MCX_STATS, TBYT_ADDR, &value);
	ENET_DEBUG("XG MCX TBYT register: %x\n", value);
	apm_enet_read(priv, BLOCK_MCX_STATS, RBYT_ADDR, &value);
	ENET_DEBUG("XG MCX RBYT register: %x\n", value);
	return 0;
}

#ifdef CONFIG_STORM
static int vco_status(struct apm_enet_priv *priv)
{
	int rd_val, pll_lock,vco_calibration;
	int pll_det;
	int vco_cal_fail;

	rd_val = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*7);

	pll_lock = (rd_val >> 15) & 0x1;
	vco_calibration = (rd_val >> 14) & 0x1;
	pll_det = (rd_val >> 12) & 0x3;
	vco_cal_fail = (rd_val >> 10) & 0x3;

	if (!vco_calibration) {
		ENET_PRINT("VCO_CALIB: PLL %aLOCKed\n", pll_lock ? "" : "not ");
		ENET_PRINT("VCO_CALIB: PLL VCO Calibration %a\n",
			vco_calibration ? "DONE" : "not done");
		ENET_PRINT("VCO_CALIB: PLL VCO Calibration %a : 0x%x\n",
			vco_cal_fail == 0 ? "NO FAILURE" : "FAILED",vco_cal_fail);
		ENET_PRINT("VCO_CALIB: PLL DET : %d\n", pll_det);
	}
	return (((vco_cal_fail<<3) | (pll_det<<1) | (pll_lock == 0)));
}
#endif

static void apm_xg_serdes_init(struct apm_enet_priv *priv)
{
#ifdef CONFIG_SHADOWCAT_SERDES 
	struct xgene_phy_ctx phy_ctx;

	phy_ctx.mode = (priv->phy_mode == PHY_MODE_XGMII) ?
		MODE_XFI : MODE_SGMII;
	phy_ctx.lane = 1;
	phy_ctx.sds_base =(u64 *)priv->eth_sds_csr_addr_v;
	phy_ctx.clk_type = CLK_EXT_DIFF;
	xgene_phy_hw_init(&phy_ctx);
#endif
#ifdef CONFIG_STORM
	u32 rev = 4;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_xgenet_serdes_init(priv, rev);
	} else {
		int vco_fail = 0, loop = 30;
		u32 pll_ready;

		do {
			udelay(100);
			pll_ready = apm_xgenet_serdes_init(priv, rev);

			udelay(10);
			if (pll_manualcal == 0)
				vco_fail = vco_status(priv);
			loop--;

		} while (((vco_fail & 0x1e) || (pll_ready == 0)) && (loop != 0));
		force_lat_summer_cal(priv);
	}
	gen_avg_val(priv);
#endif
}

static void apm_xg_select_mode(struct apm_enet_priv *priv)
{
	if (priv->phy_mode == PHY_MODE_SGMII)
		apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR,
			XGENET_CONFIG_REG_ADDR, 0x1);
	else /* XGMII mode, CLE clock same as AXI clock, 250 MHz */
		apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR,
			XGENET_CONFIG_REG_ADDR, 0x02);
}

static void apm_xg_init_ecc(struct apm_enet_priv *priv)
{
	u32 wrdata, rddata;
	int i;

	ENET_DEBUG ("XG Waking up RAM\n");

	wrdata = 0;
	apm_enet_write( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_CFG_MEM_RAM_SHUTDOWN_ADDR, wrdata);

	apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
	while (REGSPEC_MEM_RDY_RD(rddata) != REGSPEC_BLOCK_MEM_RDY_DEFAULT) {
		apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
	}

	for (i = 0 ; i < 5 ; i++)
		apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
}

#define PLL_POLLING_LOOP 100
static void apm_xg_clk_rst_cfg(struct apm_enet_priv *priv)
{
#ifdef CONFIG_STORM
	u32 wrdata;
	ENET_DEBUG ("XG CLK_RST configuration\n");

	wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(1);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
	mdelay(10);

	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, 0);
	mdelay(10);

	apm_xg_select_mode(priv);
	wrdata = CSR_CLKEN_WR(1)
		| XGENET_CLKEN_WR(1);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, wrdata );
	udelay(1000);

	wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(0);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
	udelay(10);

	wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(0) | XGENET_SDS_RESET_WR(0);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
	udelay(10);

	apm_enet_write( priv, BLOCK_XGENET_PCS , XGBASER_CONFIG_REG1_ADDR, 0 );
	apm_xg_serdes_init(priv);

	wrdata = XGENET_RESET_WR(0) | CSR_RESET_WR(0) | XGENET_SDS_RESET_WR(0);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
	udelay(400);

	apm_xg_init_ecc( priv );
#elif defined(CONFIG_SHADOWCAT)
	struct xgene_phy_ctx phy_ctx, *ctx = &phy_ctx;
	u32 rd_data;
	int loop = 0;

	ENET_DEBUG ("Shadowcat XG CLK_RST configuration\n");
	phy_ctx.mode = (priv->phy_mode == PHY_MODE_XGMII) ?
			MODE_XFI : MODE_SGMII;
	phy_ctx.lane = 1;
	phy_ctx.clk_type = CLK_EXT_DIFF;
	phy_ctx.sds_base =(u64 *)priv->eth_sds_csr_addr_v;
	apm_xg_select_mode(priv);

	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, 0x11);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, 0x7b);
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0x0);
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CTL0_ADDR, 0);
	udelay(10);
	apm_xg_serdes_init(priv);
	udelay(10);
#ifdef CONFIG_SHADOWCAT_SERDES
	rd_data = apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CMU_CTL1, &rd_data);
	rd_data = XGENET_SDS_CMU_CTL1_CFG_CMU_I_USRCLK_DIV_SET (rd_data, 0x4);
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CMU_CTL1, rd_data);
	/*deassert Serdes Reset of HS and LSPLL*/
	/*Order is important*/
	apm_enet_read( priv, BLOCK_ETH_SDS_CSR , XGENET_SDS_CMU_HSPLL_CTL1, &rd_data );
	rd_data = XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_POST_DIV_RESETB_SET(rd_data, 0x1);
	rd_data = XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_REFCLK_DIV_RESETB_SET(rd_data, 0x1);
	rd_data = XGENET_SDS_CMU_HSPLL_CTL1_CFG_I_HS_PLLRESETB_SET(rd_data, 0x1);
 	/*eth_wr (XGENET_SDS_CMU_HSPLL_CTL1, rd_data, eth_intf); */
	apm_enet_write( priv, BLOCK_ETH_SDS_CSR , XGENET_SDS_CMU_HSPLL_CTL1, rd_data );
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0xDF);

	/*Check PLLReady/LOCK and VCO Calibration Status of HSPLL*/
	if (priv->phy_mode == PHY_MODE_XGMII) {
		enum cmu_type_t cmu_type;
		for (cmu_type = ETH_HSPLL; cmu_type >= ETH_LSPLL; cmu_type--) {
			/* Start HSPLL calibration and try for 10 times */
			do { 
				/* force calib */
				if (!xgene_phy2_cal_rdy_chk(ctx, cmu_type, 0))
					break;
				/* If failed, toggle the VCO power */
				xgene_phy2_pdwn_force_vco(ctx, cmu_type,
					CLK_EXT_DIFF);
			} while (++loop > 10);
			if (loop >= 10) {
				ENET_DEBUG("(cmu = %d) calibration failed\n",
					cmu_type);
				return;
			}
		}
		xgene_phy_cmu_ready(ctx, PHY_CMU);
		xgene_phy_rxtx_ready(ctx, 0);

	} else {	
		/*Check PLLReady/LOCK and VCO Calibration Status*/
		do {
			apm_enet_read(priv, BLOCK_ETH_SDS_CSR,
				XGENET_SDS_CMU_STATUS0_ADDR, &rd_data);
			++loop;
			mdelay(10);
		} while ((rd_data != 0x7) && (loop <= PLL_POLLING_LOOP));
		if (loop >= PLL_POLLING_LOOP) {
			ENET_DEBUG("VCO lock Failed: %x\n", rd_data);
			return;
		}
	}
	/*Program AN_CONTROL.Auto_Negotiation_enable <- 0
	  Indirect write AN_CONFIGURATION_REGISTER.auto_configuration <- 0 */
	xfi_an_rd(ctx, AN_CONTROL, &rd_data);
	rd_data = AN_CONTROL_AUTO_NEGOTIATION_ENABLE_SET(rd_data, 0x0);
	xfi_an_wr(ctx, AN_CONTROL, rd_data);
  
	xfi_an_rd(ctx, AN_CONFIGURATION_REGISTER, &rd_data);
	rd_data = AN_CONFIGURATION_REGISTER_AUTO_CONFIGURATION_SET(rd_data, 0x0);
	xfi_an_wr(ctx, AN_CONFIGURATION_REGISTER, rd_data);
#endif 
	/*Software work around for a bug fix*/
	/*Enable 10GBaseKR AN and AD block clocks*/
	/*rd_data = eth_rd(SM_XGENET_CLKEN__ADDR, eth_intf); */
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, &rd_data);
	rd_data = XGENET_CLKEN_CFG_AN_CLK_EN_SET (rd_data, 0x1);
	rd_data = XGENET_CLKEN_CFG_AD_CLK_EN_SET (rd_data, 0x1);
	/*eth_wr (SM_XGENET_CLKRST_CLKEN__ADDR, rd_data, eth_intf); */
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, rd_data);

	/*Disable 10GBaseKR AN and AD block clocks*/
	/*rd_data = eth_rd(XGENET_CLKEN, eth_intf); */
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, &rd_data);
	rd_data = XGENET_CLKEN_CFG_AN_CLK_EN_SET (rd_data, 0x0);
	rd_data = XGENET_CLKEN_CFG_AD_CLK_EN_SET (rd_data, 0x0);
	rd_data = XGENET_CLKEN_CFG_AN_REF_CLK_EN_SET (rd_data, 0x0);
	/*eth_wr (SM_XGENET_CLKRST_CLKEN__ADDR, rd_data, eth_intf); */
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, rd_data);

	/*Assert CSR clock enable and Deassert CSR reset*/
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, &rd_data);
	rd_data = XGENET_CLKEN_CSR_CLKEN_SET (rd_data, 0x1);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, rd_data);

	apm_enet_read( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, &rd_data);
	rd_data =  XGENET_SRST_CSR_RESET_SET (rd_data, 0x0);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, rd_data);

	/*Enable XGMII block clock, followed by removal of block reset*/
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, &rd_data);
	rd_data = XGENET_CLKEN_CFG_PCS_CLK_EN_SET (rd_data, 0x1);
	rd_data = XGENET_CLKEN_XGENET_CLKEN_SET (rd_data, 0x1);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, rd_data);

	apm_enet_read( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, &rd_data);
	if (priv->phy_mode == PHY_MODE_XGMII)
		rd_data = XGENET_SRST_XGENET_PCS_RESET_SET (rd_data, 0x0);
	rd_data = XGENET_SRST_XGENET_RESET_SET (rd_data, 0x0);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, rd_data);

	apm_xg_init_ecc(priv);
#endif
}

/* 10GBaseR TX to RX loopback */
static void apm_xg_loopback_cfg( struct apm_enet_priv *priv )
{
#ifdef APM_XG_AXGMAC_TX2RX_LOOPBACK
	u32 wrdata;
	ENET_DEBUG ("XG loopback (TX to RX) configuration\n");

	wrdata = CFG_XGBASER_TX2RX_LOOPBACK1_WR(1);
	apm_enet_write( priv, BLOCK_XGENET_PCS , XGBASER_CONFIG_REG1_ADDR, wrdata );

#endif
#ifdef IXIA_RXTX_LOOPBACK
	apm_enet_write(priv, BLOCK_ETH_CSR, DEBUG_REG_ADDR, 0x003e03fe);
#endif

#ifdef APM_XGENET_XGMII_TX2RX_LOOPBACK
	u32 wrdata;
	ENET_DEBUG ("XG XGMII loopback (TX to RX) configuration\n");

	wrdata = CFG_I_TX_SER_LPBK0_WR(1);
	apm_enet_write( priv, BLOCK_ETH_SDS_CSR , XGENET_SDS_CTL0_ADDR, wrdata );
#endif
}

void apm_xgmac_reset(struct apm_enet_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		ENET_DEBUG ("XG reset AXGMAC\n");

		data = 0xe601;
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_0_ADDR, data);
		udelay(1);

		ENET_DEBUG ("XG deassert AXGMAC reset\n");
		data = 0x0;
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_0_ADDR, data);
		udelay(5);
	} else {
		data = (RESET_RX_MC1_MASK   |
				RESET_RX_FUN1_MASK  |
				RESET_TX_MC1_MASK   |
				RESET_TX_FUN1_MASK  |
				SIM_RESET1_MASK     |
				SOFT_RESET1_MASK);

		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, data);
	}
	apm_xg_loopback_cfg( priv );
}

static int apm_axgmac_init (struct apm_enet_priv *priv,
		unsigned char *dev_addr, int speed, int crc)
{
	u32 wrdata, data;
	u32 addr_hi, addr_lo;

	ENET_DEBUG("XG Initialize XG MAC\n");

	apm_xgmac_reset(priv);

	ENET_DEBUG ("XG configure AXGMAC\n");
	data = (HSTTCTLEN1_WR(1)
			| HSTTFEN1_WR(1)
			| HSTRCTLEN1_WR(1)
			| HSTRFEN1_WR(1)
#if !defined(BOOTLOADER)
			| HSTPPEN1_WR(1)
#endif
			| HSTLENCHK1_WR(1));
	if (crc)
		data |= (HSTGENFCS1_WR(1) | REGSPEC_HSTPADMODE1_WR(1));
	data = HSTDRPLT641_SET(data, 0);
	ENET_DEBUG ("XG AXGMAC config_1: %x\n", data);

	apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, data );
	udelay(1);

	wrdata = HSTMXFRMWCTX_WR(APM_ENET_FRAME_LEN)
		| HSTMXFRMBCRX_WR(APM_ENET_FRAME_LEN);
	apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_MAXFRAME_LENGTH_ADDR, wrdata );
	apm_enet_read( priv, BLOCK_AXG_MAC, AXGMAC_MAXFRAME_LENGTH_ADDR, &data );
	ENET_DEBUG ("XG AXGMAC maxframe length: %x\n", data);

	addr_hi = *(u32 *) &dev_addr[0];
	addr_lo = *(u16 *) &dev_addr[4];
	ENET_DEBUG ("XG devaddr: %a\n", dev_addr);
	addr_lo <<= 16;
	apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_LSW_ADDR, addr_hi );
	apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_MSW_ADDR, addr_lo );

	apm_enet_read( priv, BLOCK_AXG_STATS, TBYT_ADDR, &data );
	ENET_DEBUG("XG TBYT register: %x\n", data);
	apm_enet_read( priv, BLOCK_AXG_STATS, RBYT_ADDR, &data );
	ENET_DEBUG("XG RBYT register: %x\n", data);

	return 0;
}


static void apm_xg_bypass_resume_cfg(struct apm_enet_priv *priv)
{
	u32 wrdata;
	ENET_DEBUG ("XG bypass resume configuration\n");

	wrdata = RESUME_TX_WR(1);
	apm_enet_write( priv, BLOCK_ETH_CSR, CFG_BYPASS_ADDR, wrdata);

	if (priv->phy_mode == PHY_MODE_SGMII)
		wrdata = 0x1;
	else
		wrdata = 0x0;
	apm_enet_write( priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, wrdata);

	wrdata = TX_PORT0_WR(1);
	apm_enet_write( priv, BLOCK_ETH_CSR, CFG_LINK_AGGR_RESUME_0_ADDR, wrdata);

	wrdata = 0x22407040;
	apm_enet_write( priv, BLOCK_ETH_CSR, ENET_SPARE_CFG_REG_ADDR, wrdata);

#ifdef CONFIG_SHADOWCAT
	wrdata = 0x44;
	apm_enet_write( priv, BLOCK_ETH_CSR, ENET_SPARE_CFG_REG_1_ADDR, wrdata);
#endif

	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC_CSR, RX_DV_GATE_REG_0_ADDR, &wrdata);
		wrdata = TX_DV_GATE_EN0_F2_SET(wrdata, 0);
		wrdata = RX_DV_GATE_EN0_F2_SET(wrdata, 0);
		wrdata = RESUME_RX0_F2_SET(wrdata, 1);
		ENET_DEBUG ("%a XGENET_RX_DV_GATE_REG_0_ADDR=0x%x\n", __func__, wrdata);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
				RX_DV_GATE_REG_0_ADDR, wrdata);

	} else
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
				XGENET_RX_DV_GATE_REG_0_ADDR, 0);
}


static void apm_xg_cle_bypass_mode_cfg(struct apm_enet_priv *priv,
	u32 cle_dstqid, u32 cle_fpsel, u32 cle_nxtfpsel, int bypass_en)
{
	u32 reg;
	int enable = bypass_en ? 1 : 0;

	ENET_DEBUG("XG Bypass CLE\n");

	apm_enet_read(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG0_ADDR, &reg);
	reg = CFG_CLE_BYPASS_EN0_SET(reg, enable);
	reg = CFG_CLE_IP_PROTOCOL0_SET(reg, 3);
	apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG0_ADDR, reg);

	apm_enet_read(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG1_ADDR, &reg);
	reg = CFG_CLE_DSTQID1_SET(reg, cle_dstqid);
	reg = CFG_CLE_FPSEL1_SET(reg, cle_fpsel);
	reg = CFG_CLE_NXTFPSEL1_SET(reg, cle_nxtfpsel);
	apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG1_ADDR, reg);
}

static void apm_xgmac_get_tx_rx_stats(struct apm_enet_priv *priv,
		struct eth_frame_stats *tx_rx_stats)
{
	u32 block_mac_stats;
	u32 counter;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	/* Read Stats */
	apm_enet_read(priv, block_mac_stats, TR64_ADDR,
			&counter);
	tx_rx_stats->c_64B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TR127_ADDR,
			&counter);
	tx_rx_stats->c_65_127B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TR255_ADDR,
			&counter);
	tx_rx_stats->c_128_255B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TR511_ADDR,
			&counter);
	tx_rx_stats->c_256_511B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TR1K_ADDR,
			&counter);
	tx_rx_stats->c_512_1023B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TRMAX_ADDR,
			&counter);
	tx_rx_stats->c_1024_1518B_frames += counter;

	apm_enet_read(priv, block_mac_stats, TRMGV_ADDR,
			&counter);
	tx_rx_stats->c_1519_1522B_frames += counter;

	/* Mask out unnecessary bits in all the fields */
	tx_rx_stats->c_64B_frames &= TX_RX_64B_FRAME_CNTR4_MASK;
	tx_rx_stats->c_65_127B_frames &= TX_RX_127B_FRAME_CNTR7_MASK;
	tx_rx_stats->c_128_255B_frames &= TX_RX_255B_FRAME_CNTR5_MASK;
	tx_rx_stats->c_256_511B_frames &= TX_RX_511B_FRAME_CNTR1_MASK;
	tx_rx_stats->c_512_1023B_frames &= TX_RX_1KB_FRAME_CNTR_MASK;
	tx_rx_stats->c_1024_1518B_frames &= TX_RX_MAXB_FRAME_CNTR_MASK;
	tx_rx_stats->c_1519_1522B_frames &= TRMGV_MASK;
}

static void apm_xgmac_get_rx_stats(struct apm_enet_priv *priv,
	struct eth_rx_stat *rx_stat)
{
	u32 block_mac_stats;
	u32 counter;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	apm_enet_read(priv, block_mac_stats, RFCS_ADDR,
			&counter);
	rx_stat->rx_fcs_err_count += counter;

	apm_enet_read(priv, block_mac_stats, RMCA_ADDR,
			&counter);
	rx_stat->rx_multicast_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RBCA_ADDR,
			&counter);
	rx_stat->rx_broadcast_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RXCF_ADDR,
			&counter);
	rx_stat->rx_cntrl_frame_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RXPF_ADDR,
			&counter);
	rx_stat->rx_pause_frame_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RXUO_ADDR,
			&counter);
	rx_stat->rx_unknown_op_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RALN_ADDR,
			&counter);
	rx_stat->rx_alignment_err_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RFLR_ADDR,
			&counter);
	rx_stat->rx_frm_len_err_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RCDE_ADDR,
			&counter);
	rx_stat->rx_code_err_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RCSE_ADDR,
			&counter);
	rx_stat->rx_carrier_sense_err_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RUND_ADDR,
			&counter);
	rx_stat->rx_undersize_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, ROVR_ADDR,
			&counter);
	rx_stat->rx_oversize_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, RFRG_ADDR,
			&counter);
	rx_stat->rx_fragment_count += counter;

	apm_enet_read(priv, block_mac_stats, RJBR_ADDR,
			&counter);
	rx_stat->rx_jabber_count += counter;

	apm_enet_read(priv, block_mac_stats, RDRP_ADDR,
			&counter);
	rx_stat->rx_drop_pkt_count += counter;

	/* Mask out unnecessary bits in all the fields */
	rx_stat->rx_fcs_err_count &= RX_FCS_ERROR_CNTR_MASK;
	rx_stat->rx_multicast_pkt_count &= RX_MC_PKT_CNTR_MASK;
	rx_stat->rx_broadcast_pkt_count &= RX_BC_PKT_CNTR_MASK;
	rx_stat->rx_cntrl_frame_pkt_count &= RX_CTRL_PKT_CNTR_MASK;
	rx_stat->rx_pause_frame_pkt_count &= RX_PAUSE_PKT_CNTR_MASK;
	rx_stat->rx_unknown_op_pkt_count &= RX_UNK_OPCODE_CNTR_MASK;
	rx_stat->rx_alignment_err_pkt_count &= RX_ALIGN_ERR_CNTR_MASK;
	rx_stat->rx_frm_len_err_pkt_count &= RX_LEN_ERR_CNTR_MASK;
	rx_stat->rx_code_err_pkt_count &= RX_CODE_ERR_CNTR_MASK;
	rx_stat->rx_carrier_sense_err_pkt_count &= RX_FALSE_CARRIER_CNTR_MASK;
	rx_stat->rx_undersize_pkt_count &= RX_UNDRSIZE_PKT_CNTR_MASK;
	rx_stat->rx_oversize_pkt_count &= RX_OVRSIZE_PKT_CNTR_MASK;
	rx_stat->rx_fragment_count &= RX_FRAG_CNTR_MASK;
	rx_stat->rx_jabber_count &= RX_JABBER_CNTR_MASK;
	rx_stat->rx_drop_pkt_count &= RX_DROPPED_PKT_CNTR_MASK;
}

static void apm_xgmac_get_tx_stats(struct apm_enet_priv *priv,
		struct eth_tx_stats *tx_stats)
{
	u32 block_mac_stats;
	u32 counter;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	/* Read Stats */
	apm_enet_read(priv, block_mac_stats, TMCA_ADDR,
			&counter);
	tx_stats->tx_multicast_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TBCA_ADDR,
			&counter);
	tx_stats->tx_broadcast_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TXPF_ADDR,
			&counter);
	tx_stats->tx_pause_frame_count += counter;

	apm_enet_read(priv, block_mac_stats, TDFR_ADDR,
			&counter);
	tx_stats->tx_deferral_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TEDF_ADDR,
			&counter);
	tx_stats->tx_exesiv_def_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TSCL_ADDR,
			&counter);
	tx_stats->tx_single_coll_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TMCL_ADDR,
			&counter);
	tx_stats->tx_multi_coll_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TLCL_ADDR,
			&counter);
	tx_stats->tx_late_coll_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TXCL_ADDR,
			&counter);
	tx_stats->tx_exesiv_coll_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TNCL_ADDR,
			&counter);
	tx_stats->tx_toll_coll_pkt_count += counter;

	apm_enet_read(priv, block_mac_stats, TPFH_ADDR,
			&counter);
	tx_stats->tx_pause_frm_hon_count += counter;

	apm_enet_read(priv, block_mac_stats, TDRP_ADDR,
			&counter);
	tx_stats->tx_drop_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TJBR_ADDR,
			&counter);
	tx_stats->tx_jabber_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TFCS_ADDR,
			&counter);
	tx_stats->tx_fcs_err_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TXCF_ADDR,
			&counter);
	tx_stats->tx_control_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TOVR_ADDR,
			&counter);
	tx_stats->tx_oversize_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TUND_ADDR,
			&counter);
	tx_stats->tx_undersize_frm_count += counter;

	apm_enet_read(priv, block_mac_stats, TFRG_ADDR,
			&counter);
	tx_stats->tx_fragments_frm_count += counter;

	/* Mask values with appropriate width of the fields */
	tx_stats->tx_multicast_pkt_count &= TX_MC_PKT_CNTR_MASK;
	tx_stats->tx_broadcast_pkt_count &= TX_BC_PKT_CNTR_MASK;
	tx_stats->tx_pause_frame_count &= TX_PAUSE_PKT_CNTR_MASK;
	tx_stats->tx_deferral_pkt_count &= TX_DEFER_PKT_CNTR_MASK;
	tx_stats->tx_exesiv_def_pkt_count &= TX_EXC_DEFER_PKT_CNTR_MASK;
	tx_stats->tx_single_coll_pkt_count &= TX_COL_PKT_CNTR_MASK;
	tx_stats->tx_multi_coll_pkt_count &= TX_MUL_COL_PKT_CNTR_MASK;
	tx_stats->tx_late_coll_pkt_count &= TX_LATE_COL_PKT_CNTR_MASK;
	tx_stats->tx_exesiv_coll_pkt_count &= TX_EXC_COL_PKT_CNTR_MASK;
	tx_stats->tx_toll_coll_pkt_count &= TX_TOTAL_COL_CNTR_MASK;
	tx_stats->tx_pause_frm_hon_count &= TX_PAUSE_FRAME_CNTR_MASK;
	tx_stats->tx_drop_frm_count &= TX_DROP_FRAME_CNTR_MASK;
	tx_stats->tx_jabber_frm_count &= TX_JABBER_FRAME_CNTR_MASK;
	tx_stats->tx_fcs_err_frm_count &= TX_FCS_ERROR_CNTR_MASK;
	tx_stats->tx_control_frm_count &= TX_CTRL_FRAME_CNTR_MASK;
	tx_stats->tx_oversize_frm_count &= TX_OVRSIZE_FRAME_CNTR_MASK;
	tx_stats->tx_undersize_frm_count &= TX_UNDSIZE_FRAME_CNTR_MASK;
	tx_stats->tx_fragments_frm_count &= TX_FRAG_CNTR_MASK;
}

static void apm_xgmac_get_detailed_stats(struct apm_enet_priv *priv,
		struct eth_detailed_stats *stats)
{
	apm_xgmac_get_tx_rx_stats(priv, &(stats->eth_combined_stats));
	apm_xgmac_get_rx_stats(priv, &(stats->rx_stats));
	apm_xgmac_get_tx_stats(priv, &(stats->tx_stats));
}

static int apm_xgmac_init(struct apm_enet_priv *priv,
		unsigned char *dev_addr, int speed, int crc)
{
	u32 ret;
	u32 value;

	if (priv->phy_mode == PHY_MODE_XGMII)
		ret = apm_axgmac_init(priv, dev_addr, APM_ENET_SPEED_10000, crc);
	else
		ret = apm_mcxmac_init(priv, dev_addr, speed, crc);

	/* Enable drop if FP not available */
	apm_enet_read(priv, BLOCK_ETH_CSR, RSIF_CONFIG_REG_ADDR, &value);
	value |= CFG_RSIF_FPBUFF_TIMEOUT_EN_WR(1);
	apm_enet_write(priv, BLOCK_ETH_CSR, RSIF_CONFIG_REG_ADDR, value);

	apm_enet_read(priv, BLOCK_ETH_CSR, AVB_PER_Q_CONFIG1_0_ADDR, &value);
	value = CFG_ETH_Q_ARB_TYPE0_SET(value, 0x5555);
	apm_enet_write(priv, BLOCK_ETH_CSR, AVB_PER_Q_CONFIG1_0_ADDR, value);

	apm_enet_write(priv, BLOCK_ETH_CSR, AVB_PER_Q_HI_CREDIT_0_ADDR, 0x44444444);

	apm_enet_read(priv, BLOCK_ETH_CSR, AVB_COMMON_CONFIG1_0_ADDR, &value);
	value = MAC_SPEED0_SET(value, 2);
	value = CFG_AVB_ADD_OVERHEAD0_SET(value, 1);
	value = CFG_AVB_OVERHEAD0_SET(value, 20);
	apm_enet_write(priv, BLOCK_ETH_CSR, AVB_COMMON_CONFIG1_0_ADDR, value);

	apm_enet_read(priv, BLOCK_ETH_CSR, AVB_COMMON_CONFIG2_0_ADDR, &value);
	value = CFG_WRR_CREDIT_RESET_EN0_SET(value, 1);
	value = CFG_AVB_CALC_INT_HUNDREDNSEC_CNT0_SET(value, 0x0004);
	apm_enet_write(priv, BLOCK_ETH_CSR, AVB_COMMON_CONFIG2_0_ADDR, value);

	return ret;
}

void apm_xgmac_rx_state(struct apm_enet_priv *priv, u32 enable)
{
	if (enable)
		apm_xgmac_rx_enable(priv);
	else
		apm_xgmac_rx_disable(priv);
}

void apm_xgmac_tx_state(struct apm_enet_priv *priv, u32 enable)
{
	if (enable)
		apm_xgmac_tx_enable(priv);
	else
		apm_xgmac_tx_disable(priv);
}

void apm_xgmac_set_ipg(struct apm_enet_priv *priv, u16 ipg)
{
	u32 data;

	if (priv->phy_mode != PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC, IPG_IFG_ADDR, &data);
		apm_enet_write(priv, BLOCK_MCX_MAC, IPG_IFG_ADDR,
				B2B_IPG_SET(data, ipg));
	}

	ENET_DEBUG("Setting IPG to %d bits", ipg);
}

static void apm_xgmac_set_mac_addr(struct apm_enet_priv *priv,
		unsigned char *dev_addr)
{
	u32 a_hi;
	u32 a_lo;

	a_hi = *(u32 *) &dev_addr[0];
	a_lo = (u32) *(u16 *) &dev_addr[4];
	a_lo <<= 16;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_LSW_ADDR, a_hi);
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_MSW_ADDR, a_lo);
	} else {
		/* Write higher 4 octects to station register */
		apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR0_ADDR, a_hi);
		a_lo |= (priv->phy_addr & 0xFFFF);
		/* Write lower 2 octects to station register */
		apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR1_ADDR, a_lo);
	}
}

void apm_xgmac_tx_offload(struct apm_enet_priv *priv, u32 command, u32 value)
{
	u32 data;

	switch (command) {
	/* TCP MSS 0 */
	case APM_ENET_MSS0:
		apm_enet_read(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG0_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG0_0_ADDR,
				CFG_TSIF_MSS_SZ00_SET(data, value));
		break;
		/* TCP MSS 1 */
	case APM_ENET_MSS1:
		apm_enet_read(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG0_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG0_0_ADDR,
				CFG_TSIF_MSS_SZ10_SET(data, value));
		break;
		/* TCP MSS 2 */
	case APM_ENET_MSS2:
		apm_enet_read(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG1_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG1_0_ADDR,
				CFG_TSIF_MSS_SZ20_SET(data, value));
		break;
		/* TCP MSS 3 */
	case APM_ENET_MSS3:
		apm_enet_read(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG1_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
				TSIF_MSS_REG1_0_ADDR,
				CFG_TSIF_MSS_SZ30_SET(data, value));
		break;
		/* Program TSO config */
	case APM_ENET_TSO_CFG:
		apm_enet_write(priv, BLOCK_ETH_CSR, TSO_CFG_0_ADDR, value);
		break;
		/* Insert Inser tVLAN TAG */
	case APM_ENET_INSERT_VLAN:
		apm_enet_write(priv, BLOCK_ETH_CSR,
				TSO_CFG_INSERT_VLAN_0_ADDR, value);
		break;
	}
}

static void apm_xgport_reset(struct apm_enet_priv *priv, u32 mii_mode)
{
	priv->phy_mode = mii_mode;
	apm_xg_clk_rst_cfg(priv);
	xgenet_config_qmi_assoc(priv);
	apm_xg_bypass_resume_cfg(priv);
}

static void apm_xgport_shutdown(struct apm_enet_priv *priv)
{
#ifdef CONFIG_STORM
	u32 val;

	/* reset serdes, csr and xgenet core */
	val = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(1);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, val);

	/* disable csr and xgenet clock */
	val = CSR_CLKEN_WR(0) | XGENET_CLKEN_WR(0);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, val);
#else
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, 0x0);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, 0x7f);
#endif
}

void apm_xgenet_init_priv(struct apm_enet_priv *priv, void *port_vaddr,
		void *gbl_vaddr, void *mii_vaddr)
{
	/* Setup the ethernet base address and mac address */
	priv->vaddr_base = gbl_vaddr;
	priv->vpaddr_base = port_vaddr;

	/* Initialize base addresses for direct access */
	priv->eth_csr_addr_v        = gbl_vaddr + BLOCK_ETH_CSR_OFFSET;
	priv->eth_cle_addr_v        = gbl_vaddr + BLOCK_ETH_CLE_OFFSET;
	priv->eth_qmi_addr_v        = gbl_vaddr + BLOCK_ETH_QMI_OFFSET;
	priv->eth_sds_csr_addr_v    = gbl_vaddr + BLOCK_ETH_SDS_CSR_OFFSET;
	priv->eth_clkrst_csr_addr_v = gbl_vaddr + BLOCK_ETH_CLKRST_CSR_OFFSET;
	priv->eth_diag_csr_addr_v   = gbl_vaddr + BLOCK_ETH_DIAG_CSR_OFFSET;

	/* Initialize base addresses for Per Port MII Indirect access */
	priv->mac_mii_addr_v = mii_vaddr;

	/* Initialize base addresses for Per Port indirect & direct MCX MAC access */
	priv->mcx_mac_addr_v       = port_vaddr + BLOCK_ETH_MAC_OFFSET;
	priv->mcx_stats_addr_v     = port_vaddr + BLOCK_ETH_STATS_OFFSET;
	priv->mcx_mac_csr_addr_v   = gbl_vaddr + BLOCK_MCX_MAC_CSR_OFFSET;

	/* Initialize base addresses for Per Port indirect & direct AXG MAC access */
	priv->axg_mac_addr_v         = gbl_vaddr + BLOCK_AXG_MAC_OFFSET;
	priv->axg_stats_addr_v       = gbl_vaddr + BLOCK_AXG_STATS_OFFSET;
	priv->axg_mac_csr_addr_v     = gbl_vaddr + BLOCK_ETH_MAC_CSR_OFFSET;
	priv->xgenet_pcs_addr_v      = gbl_vaddr + BLOCK_XGENET_PCS_OFFSET;
	priv->xgenet_mdio_csr_addr_v = gbl_vaddr + BLOCK_XGENET_MDIO_CSR_OFFSET;

	ENET_DEBUG("           ETH%d VADDR: 0x%p\n", priv->port, priv->vpaddr_base);
	ENET_DEBUG("            ETH VADDR: 0x%p\n", priv->vaddr_base);
	ENET_DEBUG("        ETH CSR VADDR: 0x%p\n", priv->eth_csr_addr_v);
	ENET_DEBUG("        ETH CLE VADDR: 0x%p\n", priv->eth_cle_addr_v);
	ENET_DEBUG("        ETH QMI VADDR: 0x%p\n", priv->eth_qmi_addr_v);
	ENET_DEBUG("    ETH SDS CSR VADDR: 0x%p\n", priv->eth_sds_csr_addr_v);
	ENET_DEBUG(" ETH CLKRST CSR VADDR: 0x%p\n", priv->eth_clkrst_csr_addr_v);
	ENET_DEBUG("       ETH DIAG VADDR: 0x%p\n", priv->eth_diag_csr_addr_v);
	ENET_DEBUG("        MAC MII VADDR: 0x%p\n", priv->mac_mii_addr_v);
	ENET_DEBUG("        MCX MAC VADDR: 0x%p\n", priv->mcx_mac_addr_v);
	ENET_DEBUG("       MCX STAT VADDR: 0x%p\n", priv->mcx_stats_addr_v);
	ENET_DEBUG("    MCX MAC CSR VADDR: 0x%p\n", priv->mcx_mac_csr_addr_v);
	ENET_DEBUG("        AXG MAC VADDR: 0x%p\n", priv->axg_mac_addr_v);
	ENET_DEBUG("       AXG STAT VADDR: 0x%p\n", priv->axg_stats_addr_v);
	ENET_DEBUG("    AXG MAC CSR VADDR: 0x%p\n", priv->axg_mac_csr_addr_v);
	ENET_DEBUG("     XGENET PCS VADDR: 0x%p\n", priv->xgenet_pcs_addr_v);
	ENET_DEBUG("XGENET MDIO CSR VADDR: 0x%p\n", priv->xgenet_mdio_csr_addr_v);

	/* Initialize priv handlers */
	priv->autoneg_set = 1;
	priv->port_reset = apm_xgport_reset;
	priv->mac_reset = apm_xgmac_reset;
	priv->get_link_status = apm_xgmac_link_status;
	if (priv->force_serdes_reset)
		priv->serdes_reset = serdes_reset_rxd_rxa;
	priv->mac_init = apm_xgmac_init;
	priv->mac_rx_state = apm_xgmac_rx_state;
	priv->mac_tx_state = apm_xgmac_tx_state;
	priv->mac_set_ipg = apm_xgmac_set_ipg;
	priv->get_stats = apm_xgmac_get_detailed_stats;
	priv->set_mac_addr = apm_xgmac_set_mac_addr;
	priv->cle_bypass = apm_xg_cle_bypass_mode_cfg;
	priv->tx_offload = apm_xgmac_tx_offload;
	priv->port_shutdown = apm_xgport_shutdown;
}
