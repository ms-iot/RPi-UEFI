/**
 * AppliedMicro APM88xxxx Ethernet Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Keyur Chudgar <kchudgar@apm.com>
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
 * @file apm_enet_mac.h
 *
 * Header file for MAC, RGMII and Statistics blocks of Ethernet.
 *
 */

#ifndef __APM_ENET_MAC_H__
#define __APM_ENET_MAC_H__

#include "apm_enet_common.h"
#include "apm_enet_csr.h"
#ifndef APM_XGENE
#ifdef BOOTLOADER
#include <asm/arch-storm/apm88xxxx_scu.h>
#else
#include <misc/xgene/slimpro/apm88xxxx_slimpro.h>
#endif
#endif

/* MAC APIs */
void apm_gmac_pad_crc_enable(struct apm_enet_priv *priv, u8 enable);
void apm_gmac_crc_enable(struct apm_enet_priv *priv, u8 enable);
void apm_gmac_set_ipg(struct apm_enet_priv *priv, u16 ipg);
void apm_gmac_reset(struct apm_enet_priv *priv);
int apm_gmac_phy_autoneg_done(struct apm_enet_priv *priv);
void apm_gmac_phy_init(struct apm_enet_priv *priv);
int apm_gmac_init(struct apm_enet_priv *priv, unsigned char *dev_addr, 
		int speed, int crc);
void apm_gmac_phy_link_mode(struct apm_enet_priv *priv, u32 *speed, u32 *state);
int apm_gmac_phy_enable_scan_cycle(struct apm_enet_priv *priv, int enable);
void apm_gmac_set_mac_addr(struct apm_enet_priv *priv, unsigned char *dev_addr);
int apm_get_link_speed(struct apm_enet_priv *priv);
void enet_reset(struct apm_enet_priv *priv);
void apm_enet_init_priv(struct apm_enet_priv *priv, void *port_vaddr, 
		void *gbl_vaddr, void *mii_vaddr);
void apm_menet_config_qmi_assoc(struct apm_enet_priv *priv);
void apm_enet_config_qmi_assoc(struct apm_enet_priv *priv);
void apm_enet_cle_bypass_mode_cfg(struct apm_enet_priv *priv, u32 cle_dstqid, 
		u32 cle_fpsel, u32 cle_nxtfpsel, int en);
void apm_menet_clk_rst_cfg( struct apm_enet_priv *priv );

/* Statistics APIs */
void apm_gmac_get_detailed_stats(struct apm_enet_priv *priv,
			struct eth_detailed_stats *detailed_stats);
void apm_gmac_get_tx_rx_stats(struct apm_enet_priv *priv,
			struct eth_frame_stats *eth_tx_rx_stats);
void apm_gmac_get_rx_stats(struct apm_enet_priv *priv,
			struct eth_rx_stat *rx_stat);
void apm_gmac_get_tx_stats(struct apm_enet_priv *priv,
			struct eth_tx_stats *tx_stats);

#endif	/* __APM_ENET_MAC_H__ */
