/**
 * AppliedMicro APM88xxxx Ethernet Common Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Fushen Chen <fchen@apm.com>
 *                      Ravi Patel <rapatel@apm.com>
 *                      Iyappan Subramanian <isubramanian@apm.com>
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
 * @file apm_enet_common.c
 *
 * This file implements APM88xxxx Ethernet Common Driver
 *
 */

#include "apm_enet_access.h"
#include "apm_enet_common.h"

/*    Address ENET_MACIP_IND_CSR  Registers */
#define ENET_WRITE0_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define ENET_READ0_WR(src)                      (((u32)(src)<<30) & 0x40000000)

/*    Address PE_MCXMAC  Registers */
#define MII_MGMT_COMMAND_ADDR                                        0x00000024
#define MII_MGMT_ADDRESS_ADDR                                        0x00000028
#define MII_MGMT_CONTROL_ADDR                                        0x0000002c
#define MII_MGMT_STATUS_ADDR                                         0x00000030
#define MII_MGMT_INDICATORS_ADDR                                     0x00000034

#define BUSY_MASK                                                    0x00000001
#define READ_CYCLE_MASK                                              0x00000001
#define PHY_CONTROL_WR(src)                         (((u32)(src)) & 0x0000ffff)

/*    Address M_SGMII  Registers */
#define SGMII_CONTROL_ADDR                                           0x00000000
#define SGMII_STATUS_ADDR                                            0x00000004
#define SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR                0x00000014
#define SGMII_TBI_CONTROL_ADDR                                       0x00000044

#define PHY_ADDR_WR(src)                         (((u32)(src)<<8) & 0x00001f00)
#define REG_ADDR_WR(src)                            (((u32)(src)) & 0x0000001f)

/* No need to poll CSR faster than 1 ms */
#if defined(PHY_CSR_ACCESS_NO_DELAY)
#define PHY_CSR_POLL_DELAY
#else
#ifdef BOOTLOADER
#define PHY_CSR_POLL_DELAY
#else
#define PHY_CSR_POLL_DELAY      msleep(1);
#endif
#endif


int apm_enet_write(struct apm_enet_priv *priv, u8 block_id,
		u32 reg_offset, u32 value)
{
	u32 command_done;
	u32 indirect = 0;
	u32 count = 0;
	void *addr_reg_offst, *cmd_reg_offst, *wr_reg_offst;
	void *cmd_done_reg_offst;

	switch (block_id) {
	case BLOCK_ETH_CSR:
		addr_reg_offst = priv->eth_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH CSR write\n");
		break;

	case BLOCK_ETH_MDIO_CSR:
		addr_reg_offst = priv->mac_mii_addr_v + reg_offset
			+ BLOCK_ETH_CSR_OFFSET;
		ENET_DEBUG_WR("BLOCK_ETH_MDIO_CSR write 0x%p\n", addr_reg_offst);
		break;

	case BLOCK_ETH_CLE:
		addr_reg_offst = priv->eth_cle_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH CLE write\n");
		break;

	case BLOCK_ETH_QMI:
		addr_reg_offst = priv->eth_qmi_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH QMI write\n");
		break;

	case BLOCK_ETH_SDS_CSR:
		addr_reg_offst = priv->eth_sds_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH SDS CSR write\n");
		break;

	case BLOCK_ETH_CLKRST_CSR:
		addr_reg_offst = priv->eth_clkrst_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH CLKRST CSR write\n");
		break;

	case BLOCK_ETH_DIAG_CSR:
		addr_reg_offst = priv->eth_diag_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("ETH DIAG CSR write\n");
		break;

	case BLOCK_MCX_MAC:
	case BLOCK_ETH_INTPHY:
		addr_reg_offst = priv->mcx_mac_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mcx_mac_addr_v + MAC_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->mcx_mac_addr_v + MAC_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->mcx_mac_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("MCX MAC/Internal PHY write\n");
		break;

	case BLOCK_ETH_EXTPHY:
		addr_reg_offst = priv->mac_mii_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mac_mii_addr_v + MAC_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->mac_mii_addr_v + MAC_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->mac_mii_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("MCX MAC/External PHY write\n");
		break;

	case BLOCK_MCX_STATS:
		addr_reg_offst = priv->mcx_stats_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mcx_stats_addr_v + STAT_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->mcx_stats_addr_v + STAT_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->mcx_stats_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("MCX STATS write\n");
		break;

	case BLOCK_MCX_MAC_CSR:
		addr_reg_offst = priv->mcx_mac_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("MCX MAC CSR write\n");
		break;

	case BLOCK_SATA_ENET_CSR:
		addr_reg_offst = priv->sata_enet_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("SATA ENET CSR write\n");
		break;

	case BLOCK_AXG_MAC:
		addr_reg_offst = priv->axg_mac_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->axg_mac_addr_v + MAC_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->axg_mac_addr_v + MAC_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->axg_mac_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("AXG MAC write\n");
		break;

	case BLOCK_AXG_STATS:
		addr_reg_offst = priv->axg_stats_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->axg_stats_addr_v + STAT_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->axg_stats_addr_v + STAT_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->axg_stats_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("AXG STATS write\n");
		break;

	case BLOCK_AXG_MAC_CSR:
		addr_reg_offst = priv->axg_mac_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("AXG MAC CSR write\n");
		break;

	case BLOCK_XGENET_PCS:
		addr_reg_offst = priv->xgenet_pcs_addr_v + reg_offset;
		ENET_DEBUG_WR("XGENET PCS write\n");
		break;

	case BLOCK_XGENET_PCS_IND:
		addr_reg_offst = priv->xgenet_pcs_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->xgenet_pcs_addr_v + STAT_COMMAND_REG_OFFSET;
		wr_reg_offst = priv->xgenet_pcs_addr_v + STAT_WRITE_REG_OFFSET;
		cmd_done_reg_offst = priv->xgenet_pcs_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_WR("XGENET PCS write\n");
		break;

	case BLOCK_XGENET_MDIO_CSR:
		addr_reg_offst = priv->xgenet_mdio_csr_addr_v + reg_offset;
		ENET_DEBUG_WR("XGENET MDIO CSR write\n");
		break;

	default:
		ENET_DEBUG_ERR("Invalid blockid in write reg: %d\n", block_id);
		return -1;
	}

	if (indirect) {
		/* Write the register offset in DCR */
		apm_enet_wr32(addr_reg_offst, reg_offset);
		ENET_DEBUG_WR("Indirect addr_reg_offst : 0x%p,"
				"value(reg_offset) 0x%X\n",
				addr_reg_offst, reg_offset);

		/* Write the data in the wrData register */
		apm_enet_wr32(wr_reg_offst, value);
		ENET_DEBUG_WR("Indirect wr_reg_offst: 0x%p, value 0x%X\n",
				wr_reg_offst, value);

		/* Invoke write command */
		apm_enet_wr32(cmd_reg_offst, ENET_WRITE0_WR(1));
		ENET_DEBUG_WR("Indirect cmd_reg_offst: 0x%p,"
				"value(cmd) 0x%X\n",
				cmd_reg_offst, ENET_WRITE0_WR(1));

		/* Check command done */
		while (1) {
			apm_enet_rd32(cmd_done_reg_offst, &command_done);
			ENET_DEBUG_WR("Indirect cmd_done_reg_offst: 0x%p,"
					"command_done:0x%X\n",
					cmd_done_reg_offst, command_done);

			if (command_done)
				break;

			udelay(ACCESS_DELAY_TIMES);

			if (count++ > MAX_LOOP_POLL_CNT) {
				ENET_DEBUG_ERR("Write failed for blk: %d\n",
					       	block_id);
				return -1;
			}
		}

		/* Reset command reg */
		ENET_DEBUG_WR("Reset command reg[0X%p]\n ", cmd_reg_offst);
		apm_enet_wr32(cmd_reg_offst, 0);
	} else {
		apm_enet_wr32(addr_reg_offst, value);
		ENET_DEBUG_WR("Direct write addr: 0x%p,"
				"value 0x%X\n", addr_reg_offst, value);
	}

	return 0;
}

int apm_enet_read(struct apm_enet_priv *priv, u8 block_id,
		u32 reg_offset, u32 *value)
{
	u32 command_done;
	u32 indirect = 0;
	u32 count = 0;
	void *addr_reg_offst, *cmd_reg_offst, *rd_reg_offst;
	void *cmd_done_reg_offst;

	switch (block_id) {
	case BLOCK_ETH_CSR:
		addr_reg_offst = priv->eth_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH CSR read\n");
		break;

	case BLOCK_ETH_MDIO_CSR:
		addr_reg_offst = priv->mac_mii_addr_v + reg_offset
			+ BLOCK_ETH_CSR_OFFSET;
		ENET_DEBUG_RD("BLOCK_ETH_MDIO_CSR read 0x%p\n", addr_reg_offst);
		break;

	case BLOCK_ETH_CLE:
		addr_reg_offst = priv->eth_cle_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH CLE read\n");
		break;

	case BLOCK_ETH_QMI:
		addr_reg_offst = priv->eth_qmi_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH QMI read\n");
		break;

	case BLOCK_ETH_SDS_CSR:
		addr_reg_offst = priv->eth_sds_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH SDS CSR read\n");
		break;

	case BLOCK_ETH_CLKRST_CSR:
		addr_reg_offst = priv->eth_clkrst_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH CLKRST CSR read\n");
		break;

	case BLOCK_ETH_DIAG_CSR:
		addr_reg_offst = priv->eth_diag_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("ETH DIAG CSR read\n");
		break;

	case BLOCK_MCX_MAC:
	case BLOCK_ETH_INTPHY:
		addr_reg_offst = priv->mcx_mac_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mcx_mac_addr_v + MAC_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->mcx_mac_addr_v + MAC_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->mcx_mac_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("MCX MAC/Internal PHY read\n");
		break;

	case BLOCK_ETH_EXTPHY:
		addr_reg_offst = priv->mac_mii_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mac_mii_addr_v + MAC_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->mac_mii_addr_v + MAC_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->mac_mii_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("MCX MAC/External PHY read\n");
		break;

	case BLOCK_MCX_STATS:
		addr_reg_offst = priv->mcx_stats_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->mcx_stats_addr_v + STAT_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->mcx_stats_addr_v + STAT_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->mcx_stats_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("MCX STATS read\n");
		break;

	case BLOCK_MCX_MAC_CSR:
		addr_reg_offst = priv->mcx_mac_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("MCX MAC CSR read\n");
		break;

	case BLOCK_SATA_ENET_CSR:
		addr_reg_offst = priv->sata_enet_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("SATA ENET CSR read\n");
		break;

	case BLOCK_AXG_MAC:
		addr_reg_offst = priv->axg_mac_addr_v + MAC_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->axg_mac_addr_v + MAC_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->axg_mac_addr_v + MAC_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->axg_mac_addr_v
		       	+ MAC_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("AXG MAC read\n");
		break;

	case BLOCK_AXG_STATS:
		addr_reg_offst = priv->axg_stats_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->axg_stats_addr_v + STAT_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->axg_stats_addr_v + STAT_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->axg_stats_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("AXG STATS read\n");
		break;

	case BLOCK_AXG_MAC_CSR:
		addr_reg_offst = priv->axg_mac_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("AXG MAC CSR read\n");
		break;

	case BLOCK_XGENET_PCS:
		addr_reg_offst = priv->xgenet_pcs_addr_v + reg_offset;
		ENET_DEBUG_RD("XGENET PCS read\n");
		break;

	case BLOCK_XGENET_PCS_IND:
		addr_reg_offst = priv->xgenet_pcs_addr_v + STAT_ADDR_REG_OFFSET;
		cmd_reg_offst = priv->xgenet_pcs_addr_v + STAT_COMMAND_REG_OFFSET;
		rd_reg_offst = priv->xgenet_pcs_addr_v + STAT_READ_REG_OFFSET;
		cmd_done_reg_offst = priv->xgenet_pcs_addr_v
		       	+ STAT_COMMAND_DONE_REG_OFFSET;
		indirect = 1;
		ENET_DEBUG_RD("XGENET PCS read\n");
		break;

	case BLOCK_XGENET_MDIO_CSR:
		addr_reg_offst = priv->xgenet_mdio_csr_addr_v + reg_offset;
		ENET_DEBUG_RD("XGENET MDIO CSR read\n");
		break;

	default:
		ENET_DEBUG_ERR("Invalid blockid in read reg: %d\n", block_id);
		return -1;
	}

	if (indirect) {
		/* Write the MAC register offset in DCR */
		apm_enet_wr32(addr_reg_offst, reg_offset);
		ENET_DEBUG_RD("Indirect addr_reg_offst: 0x%p,"
				"value(reg_offset) 0x%X\n",
				addr_reg_offst, reg_offset);

		/* Invoke read command */
		apm_enet_wr32(cmd_reg_offst, ENET_READ0_WR(1));
		ENET_DEBUG_RD("Indirect cmd_reg_offst: 0x%p,"
				"value(cmd) 0x%X\n",
				cmd_reg_offst,  ENET_READ0_WR(1));

		/* Poll for command done */
		while (1) {
			apm_enet_rd32(cmd_done_reg_offst, &command_done);
			ENET_DEBUG_RD("Indirect cmd_done_reg_offst: 0x%p,"
					"command_done:0x%X\n",
					cmd_done_reg_offst, command_done);

			if (command_done)
				break;

			udelay(ACCESS_DELAY_TIMES);

			if (count++ > MAX_LOOP_POLL_CNT) {
				ENET_DEBUG_ERR("Read failed for blk: %d\n",
						block_id);
				return -1;
			}
		}

		apm_enet_rd32(rd_reg_offst, value);
		ENET_DEBUG_RD("Indirect rd_reg_offst: 0x%p, value 0x%X\n",
				rd_reg_offst, *value);

		/* Reset command reg */
		ENET_DEBUG_RD("Reset command reg[0X%p]\n ", cmd_reg_offst);
		apm_enet_wr32(cmd_reg_offst, 0);
	} else {
		apm_enet_rd32(addr_reg_offst, value);
		ENET_DEBUG_RD("Direct read addr: 0x%p, value: 0x%X\n",
				addr_reg_offst, *value);
	}

	return 0;
}

int apm_genericmiiphy_write(struct apm_enet_priv *priv, u8 phy_id,
			   unsigned char reg, u32 data)
{
	u32 value;
	u32 blockid = BLOCK_ETH_EXTPHY;

	if (priv->port == MENET)
		phy_id = priv->phy_addr;

	/* All PHYs lie on MII bus of Port0 MAC due to this
	 * each port should access its PHY through Port0 MAC.
	 * Hence we allow access to PHY_ID associated with this
	 * port only.
	 */
	/* INT_PHY_ADDR is a hack for SGMII
	 * If the phy id is of the internal phy id, we need to
	 * access accordingly. Otherwise, the incorrect register
	 * will be read.
	 */
	if ((phy_id == INT_PHY_ADDR) &&
	    ((reg == (SGMII_CONTROL_ADDR >> 2)) ||
	     (reg == (SGMII_TBI_CONTROL_ADDR >> 2)))) {
		blockid = BLOCK_ETH_INTPHY;
	}

	/* Write PHY number and address in MII Mgmt Address */
	value = PHY_ADDR_WR(phy_id) | REG_ADDR_WR(reg);
	PHY_PRINT("%a write MII_MGMT_ADDRESS_ADDR phy_id=0x%x, reg=0x%x, \
			value=0x%x\n", __func__, phy_id, reg << 2, value);
	apm_enet_write(priv, blockid,
			MII_MGMT_ADDRESS_ADDR,value);

	/* Write 16 bit data to MII MGMT CONTROL */
	value = PHY_CONTROL_WR(data);
	PHY_PRINT(" Write MII_MGMT_CONTROL_ADDR  phy_id=0x%x, reg=0x%x, \
			value=0x%x %a\n", phy_id, reg << 2, value, __func__);
	apm_enet_write(priv, blockid,
			MII_MGMT_CONTROL_ADDR, value);

	/* wait until the write is complete */
	while (1) {
		apm_enet_read(priv, blockid,
			       MII_MGMT_INDICATORS_ADDR, &value);
		if (!(value & BUSY_MASK))
			break;
		PHY_CSR_POLL_DELAY
	}

	/* Wait for sometime.
	 * This will give reliable writes on flicky boards.
	 */
	udelay(1000);
	return 0;
}

int apm_genericmiiphy_read(struct apm_enet_priv *priv, u8 phy_id,
			  unsigned char reg, u32 *data)
{
	u32 value;
	u32 blockid = BLOCK_ETH_EXTPHY;
	u32 timeout = 10;

	if (priv->port == MENET)
		phy_id = priv->phy_addr;

	/* Wait for sometime.
	 * This will give reliable reads on flicky boards.
	 */
	udelay(1000);

	/* All PHYs lie on MII bus of Port0 MAC due to this
	 * each port should access its PHY through Port0 MAC.
	 * Hence we allow access to PHY_ID associated with this
	 * port only.
	 */
	/* INT_PHY_ADDR is a hack for SGMII
	 * If the phy id is of the internal phy id, we need to
	 * access accordingly. Otherwise, the incorrect register
	 * will be read.
	 */
	if ((phy_id == INT_PHY_ADDR) &&
	    ((reg == (SGMII_CONTROL_ADDR >> 2)) ||
   	     (reg == (SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR) >> 2) ||
	     (reg == (SGMII_STATUS_ADDR >> 2)) ||
	     (reg == (SGMII_TBI_CONTROL_ADDR >> 2)))) {
		blockid = BLOCK_ETH_INTPHY;
	}

read_again:
	/* Write PHY number and address in MII Mgmt Address */
	value = PHY_ADDR_WR(phy_id) | REG_ADDR_WR(reg);
	PHY_PRINT("%a MII_MGMT_ADDRESS_ADDR phy_id=0x%x, reg=0x%x, \
			value=0x%x\n", __func__, phy_id, reg << 2, value);
	apm_enet_write(priv, blockid, MII_MGMT_ADDRESS_ADDR, value);

	/* Write read command */
	apm_enet_write(priv, blockid, MII_MGMT_COMMAND_ADDR,
			READ_CYCLE_MASK);

	/* wait until the write is complete */
	while (1) {
		apm_enet_read(priv, blockid,
			       MII_MGMT_INDICATORS_ADDR, &value);
		if (!(value & BUSY_MASK))
			break;
		PHY_CSR_POLL_DELAY
	}

	apm_enet_read(priv, blockid, MII_MGMT_STATUS_ADDR, data);
	PHY_PRINT("Read data=0X%x from MII_MGMT_STATUS_ADDR %a\n",
		       	*data, __func__);

	/* reset mii_mgmt_command register */
	apm_enet_write(priv, blockid, MII_MGMT_COMMAND_ADDR, 0);

	/* if invalid value detected then read again */
	if ((((*data) & 0xFFFF) == 0xFFFF) && (timeout-- > 0))
		goto read_again;

	return 0;
}

void apm_enet_port_reset(struct apm_enet_priv *priv, u32 mii_mode)
{
	if (priv->port_reset)
		priv->port_reset(priv, mii_mode);
}

void apm_enet_mac_reset(struct apm_enet_priv *priv)
{
	if (priv->mac_reset)
		priv->mac_reset(priv);
}

void apm_enet_serdes_reset(struct apm_enet_priv *priv)
{
	if (priv->serdes_reset)
		priv->serdes_reset(priv, priv->port);
}

int apm_enet_get_link_status(struct apm_enet_priv *priv)
{
	int ret = 0;
	if (priv->get_link_status)
		ret = priv->get_link_status(priv);
	return ret;
}

void apm_enet_autoneg(struct apm_enet_priv *priv, int autoneg)
{
	if (priv->autoneg)
		priv->autoneg(priv, autoneg);
}

int apm_enet_mac_init(struct apm_enet_priv *priv,
		unsigned char *dev_addr, int speed, int crc)
{
	int rc = 0;

	if (priv->mac_init)
		rc = priv->mac_init(priv, dev_addr, speed, crc);

	return rc;
}

void apm_enet_mac_tx_state(struct apm_enet_priv *priv, u32 enable)
{
	if (priv->mac_tx_state)
		priv->mac_tx_state(priv, enable);
}

void apm_enet_mac_rx_state(struct apm_enet_priv *priv, u32 enable)
{
	if (priv->mac_rx_state)
		priv->mac_rx_state(priv, enable);
}

void apm_enet_mac_set_ipg(struct apm_enet_priv *priv, u16 ipg)
{
	if (priv->mac_set_ipg)
		priv->mac_set_ipg(priv, ipg);
}

void apm_enet_get_stats(struct apm_enet_priv *priv, struct eth_detailed_stats *stats)
{
	if (priv->get_stats)
		priv->get_stats(priv, stats);
}

void apm_enet_set_mac_addr(struct apm_enet_priv *priv, unsigned char *dev_addr)
{
	if (priv->set_mac_addr)
		priv->set_mac_addr(priv, dev_addr);
}

void apm_enet_cle_bypass(struct apm_enet_priv *priv, u32 dstqid, u32 fpsel,
	u32 nxtfpsel, int bypass_en)
{
	if (priv->cle_bypass)
		priv->cle_bypass(priv, dstqid, fpsel, nxtfpsel, bypass_en);
}

void apm_enet_tx_offload(struct apm_enet_priv *priv, u32 command, u32 value)
{
	if (priv->tx_offload)
		priv->tx_offload(priv, command, value);
}

void apm_enet_port_shutdown(struct apm_enet_priv *priv)
{
	if (priv->port_shutdown)
		priv->port_shutdown(priv);
}

inline enum xgene_qmtm_qaccess apm_enet_get_qacess(void)
{
	enum xgene_qmtm_qaccess qaccess;
#ifdef CONFIG_ARCH_MSLIM
	qaccess = QACCESS_QMI;
#else
	qaccess = QACCESS_ALT;
#endif
	return qaccess;
}
