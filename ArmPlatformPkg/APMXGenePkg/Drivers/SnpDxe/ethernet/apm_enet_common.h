/**
 * AppliedMicro X-Gene Ethernet Common Header
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Ravi Patel <rapatel@apm.com>
 *                      Iyappan Subramanian <isubramanian@apm.com>
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
 * @file apm_enet_common.h
 *
 * This file implements X-Gene Ethernet Common Header
 *
 */

#ifndef __APM_ENET_COMMON_H__
#define __APM_ENET_COMMON_H__

#ifndef APM_XGENE
#include "../drivers/misc/xgene/qmtm/xgene_qmtm_main.h"
#include <misc/xgene/qmtm/xgene_qmtm.h>
#else
#include "../qm/xgene_qmtm_main.h"
#include "../qm/xgene_qmtm.h"
#endif

/* ===== APM MAC definitions =====*/

#define IPV4_HDR_SIZE		20
#define IPV6_HDR_SIZE		40
#ifndef UDP_HDR_SIZE
#define UDP_HDR_SIZE		2
#endif
#define IPV6_ADDR_LEN	    	16
#define MAX_ERR_LOG		10
#define PHY_ADDR		1
#define PHY_ADDR1		2
#define READ_CMD		0
#define WRITE_CMD		1
#define MAX_CMD			2

#define INTF_BYTE_MODE		2
#define INTF_NIBBLE_MODE	1

#define ENET_ALIGN_PTR16(x)	(((unsigned long) (x) + 15) & ~0xF)

/* Ethernet & XGENET port ids */
enum eth_port_ids {
	ENET_0 = 0,
	ENET_1,
	ENET_2,
	ENET_3,
	XGENET_0,
	XGENET_1,
	XGENET_2,
	XGENET_3,
	MENET,
	MAX_ENET_PORTS
};

/* TSO Parameters */
#define TSO_ENABLE		1
#define TSO_ENABLE_MASK		1
#define TSO_CHKSUM_ENABLE	1
#define TSO_INS_CRC_ENABLE	1
#define TSO_IPPROTO_TCP		1
#define TSO_IPPROTO_UDP		0
#define TSO_IP_HLEN_MASK	0X3F
#define TSO_TCP_HLEN_MASK	0X3F
#define TSO_ETH_HLEN_MASK	0XFF
#define TSO_MSS_SZ0		0    /* Default size 64B   */
#define TSO_MSS_SZ1		1    /* Default size 256B  */
#define TSO_MSS_SZ2		2    /* Default size 1024B */
#define TSO_MSS_SZ3		3    /* Default size 1518B */
#define TSO_MSS_MASK		0X3  /* 2b */
#define DEFAULT_TCP_MSS		1448

enum {
	APM_ENET_MSS0 = 0,
	APM_ENET_MSS1,
	APM_ENET_MSS2,
	APM_ENET_MSS3,
	APM_ENET_TSO_CFG,
	APM_ENET_INSERT_VLAN
};

/* TYPE_SEL for Ethernt egress message */
#define TYPE_SEL_TIMESTAMP_MSG	0
#define TYPE_SEL_WORK_MSG	1U

/* Blocks for defined regions */
enum {
	BLOCK_ETH_CSR = 1,
	BLOCK_ETH_CLE,
	BLOCK_ETH_QMI,
	BLOCK_ETH_SDS_CSR,
	BLOCK_ETH_CLKRST_CSR,
	BLOCK_ETH_DIAG_CSR,
	BLOCK_ETH_MDIO_CSR,

	BLOCK_ETH_INTPHY,
	BLOCK_ETH_EXTPHY,

	BLOCK_MCX_MAC,
	BLOCK_MCX_STATS,
	BLOCK_MCX_MAC_CSR,
	BLOCK_SATA_ENET_CSR,

	BLOCK_AXG_MAC,
	BLOCK_AXG_STATS,
	BLOCK_AXG_MAC_CSR,
	BLOCK_XGENET_PCS,
	BLOCK_XGENET_MDIO_CSR,
	BLOCK_XGENET_PCS_IND,

	BLOCK_ETH_MAX
};

/* Direct Adress mode */
#define BLOCK_ETH_CSR_OFFSET		0x2000
#define BLOCK_ETH_CLE_OFFSET		0x6000
#define BLOCK_ETH_QMI_OFFSET		0x9000
#define BLOCK_ETH_SDS_CSR_OFFSET	0xA000
#define BLOCK_ETH_CLKRST_CSR_OFFSET	0xC000
#define BLOCK_ETH_DIAG_CSR_OFFSET	0xD000

/* Indirect & Direct  Address mode for MCX_MAC and AXG_MAC */
#define BLOCK_ETH_MAC_OFFSET		0x0000	/* MENET (RGMII) MCX MAC, ENET (SGMII) MCX MAC & XGENET (SGMII) MCX MAC */
#define BLOCK_AXG_MAC_OFFSET		0x0800	/* XGENET (XGMII) AXG only */
#define BLOCK_ETH_STATS_OFFSET		0x0014	/* MENET (RGMII) MCX MAC, ENET (SGMII) MCX MAC & XGENET (SGMII) MCX MAC */
#define BLOCK_AXG_STATS_OFFSET		0x0814	/* XGENET (XGMII) AXG only */
#define BLOCK_ETH_MAC_CSR_OFFSET	0x2800	/* MENET (RGMII) MCX MAC, ENET (SGMII) MCX MAC & XGENET (XGMII) AXG MAC */
#define BLOCK_MCX_MAC_CSR_OFFSET	0x3000	/* XGENET (SGMII) MCX only */

#define BLOCK_SATA_ENET_CSR_OFFSET	0x7000	/* ENET (SGMII) only */
#define BLOCK_XGENET_PCS_OFFSET		0x3800	/* XGENET only */
#define BLOCK_XGENET_MDIO_CSR_OFFSET	0x5000	/* XGENET only */

/* Constants for indirect registers */
#define MAC_ADDR_REG_OFFSET		0
#define MAC_COMMAND_REG_OFFSET		4
#define MAC_WRITE_REG_OFFSET		8
#define MAC_READ_REG_OFFSET		12
#define MAC_COMMAND_DONE_REG_OFFSET	16

#define STAT_ADDR_REG_OFFSET		0
#define STAT_COMMAND_REG_OFFSET		4
#define STAT_WRITE_REG_OFFSET		8
#define STAT_READ_REG_OFFSET		12
#define STAT_COMMAND_DONE_REG_OFFSET	16

#define MAX_LOOP_POLL_TIMES		500
#define MAX_LOOP_POLL_CNT		10
#define ACCESS_DELAY_TIMES		(MAX_LOOP_POLL_TIMES / MAX_LOOP_POLL_CNT)

#define DRV_VERSION			"1.0"

#if 0
#define PCM_LOOPBACK
#endif

enum apm_enum_speed {
	APM_ENET_SPEED_0 = 0xffff,
	APM_ENET_SPEED_10 = 10,
	APM_ENET_SPEED_100 = 100,
	APM_ENET_SPEED_1000 = 1000,
	APM_ENET_SPEED_10000 = 10000
};

enum apm_enet_mode {
	HALF_DUPLEX = 1,
	FULL_DUPLEX = 2
};

enum apm_enet_phy_mode {
PHY_MODE_NONE,
PHY_MODE_RGMII,
PHY_MODE_SGMII,
PHY_MODE_XGMII
};

#define CMU 0

/* ===== MII definitions ===== */

#define MII_CRC_LEN		0x4	/* CRC length in bytes */
#define MII_ETH_MAX_PCK_SZ      (ETHERMTU + SIZEOF_ETHERHEADER          \
				 + MII_CRC_LEN)
#define MII_MAX_PHY_NUM		0x20	/* max number of attached PHYs */
#define MII_MAX_REG_NUM         0x20    /* max number of registers */

#define MII_CTRL_REG		0x0	/* Control Register */
#define MII_STAT_REG		0x1	/* Status Register */
#define MII_PHY_ID1_REG		0x2	/* PHY identifier 1 Register */
#define MII_PHY_ID2_REG		0x3	/* PHY identifier 2 Register */
#define MII_AN_ADS_REG		0x4	/* Auto-Negotiation 	  */
					/* Advertisement Register */
#define MII_AN_PRTN_REG		0x5	/* Auto-Negotiation 	    */
					/* partner ability Register */
#define MII_AN_EXP_REG		0x6	/* Auto-Negotiation   */
					/* Expansion Register */
#define MII_AN_NEXT_REG		0x7	/* Auto-Negotiation 	       */
					/* next-page transmit Register */

#define MII_AN_PRTN_NEXT_REG	0x8  /* Link partner received next page */
#define MII_MASSLA_CTRL_REG	0x9  /* MATER-SLAVE control register */
#define MII_MASSLA_STAT_REG	0xa  /* MATER-SLAVE status register */
#define MII_EXT_STAT_REG	0xf  /* Extented status register */

/* MII control register bit  */

#define MII_CR_1000		0x0040		/* 1 = 1000mb when
						   MII_CR_100 is also 1 */
#define MII_CR_COLL_TEST	0x0080		/* collision test */
#define MII_CR_FDX		0x0100		/* FDX =1, half duplex =0 */
#define MII_CR_RESTART		0x0200		/* restart auto negotiation */
#define MII_CR_ISOLATE		0x0400		/* isolate PHY from MII */
#define MII_CR_POWER_DOWN	0x0800		/* power down */
#define MII_CR_AUTO_EN		0x1000		/* auto-negotiation enable */
#define MII_CR_100		0x2000		/* 0 = 10mb, 1 = 100mb */
#define MII_CR_LOOPBACK		0x4000		/* 0 = normal, 1 = loopback */
#define MII_CR_RESET		0x8000		/* 0 = normal, 1 = PHY reset */
#define MII_CR_NORM_EN		0x0000		/* just enable the PHY */
#define MII_CR_DEF_0_MASK       0xca7f          /* they must return zero */
#define MII_CR_RES_MASK       	0x003f          /* reserved bits,return zero */

/* MII Status register bit definitions */

#define MII_SR_LINK_STATUS	0x0004       	/* link Status -- 1 = link */
#define MII_SR_AUTO_SEL		0x0008       	/* auto speed select capable */
#define MII_SR_REMOTE_FAULT     0x0010      	/* Remote fault detect */
#define MII_SR_AUTO_NEG         0x0020      	/* auto negotiation complete */
#define MII_SR_EXT_STS		0x0100		/* extended sts in reg 15 */
#define MII_SR_T2_HALF_DPX	0x0200		/* 100baseT2 HD capable */
#define MII_SR_T2_FULL_DPX	0x0400		/* 100baseT2 FD capable */
#define MII_SR_10T_HALF_DPX     0x0800     	/* 10BaseT HD capable */
#define MII_SR_10T_FULL_DPX     0x1000    	/* 10BaseT FD capable */
#define MII_SR_TX_HALF_DPX      0x2000    	/* TX HD capable */
#define MII_SR_TX_FULL_DPX      0x4000     	/* TX FD capable */
#define MII_SR_T4               0x8000    	/* T4 capable */
#define MII_SR_ABIL_MASK        0xff80    	/* abilities mask */
#define MII_SR_EXT_CAP          0x0001    	/* extended capabilities */
#define MII_SR_SPEED_SEL_MASK 	0xf800           /* Mask to extract just speed
                                                  * capabilities  from status
                                                  * register.
                                                  */

/*  MII ID2 register bit mask */

#define MII_ID2_REVISON_MASK    0x000f
#define MII_ID2_MODE_MASK       0x03f0

/* MII AN advertisement Register bit definition */

#define MII_ANAR_10TX_HD        0x0020
#define MII_ANAR_10TX_FD        0x0040
#define MII_ANAR_100TX_HD       0x0080
#define MII_ANAR_100TX_FD       0x0100
#define MII_ANAR_100T_4         0x0200
#define MII_ANAR_PAUSE          0x0400
#define MII_ANAR_ASM_PAUSE      0x0800
#define MII_ANAR_REMORT_FAULT   0x2000
#define MII_ANAR_NEXT_PAGE      0x8000
#define MII_ANAR_PAUSE_MASK     0x0c00

/* MII Link Code word  bit definitions */

#define MII_BP_FAULT	0x2000       	/* remote fault */
#define MII_BP_ACK	0x4000       	/* acknowledge */
#define MII_BP_NP	0x8000       	/* nexp page is supported */

/* MII Next Page bit definitions */

#define MII_NP_TOGGLE	0x0800       	/* toggle bit */
#define MII_NP_ACK2	0x1000       	/* acknowledge two */
#define MII_NP_MSG	0x2000       	/* message page */
#define MII_NP_ACK1	0x4000       	/* acknowledge one */
#define MII_NP_NP	0x8000       	/* nexp page will follow */

/* MII Expansion Register bit definitions */

#define MII_EXP_FAULT	0x0010       	/* parallel detection fault */
#define MII_EXP_PRTN_NP	0x0008       	/* link partner next-page able */
#define MII_EXP_LOC_NP	0x0004       	/* local PHY next-page able */
#define MII_EXP_PR	0x0002       	/* full page received */
#define MII_EXP_PRT_AN	0x0001       	/* link partner auto negotiation able */

/* MII Master-Slave Control register bit definition */

#define MII_MASSLA_CTRL_1000T_HD    0x100
#define MII_MASSLA_CTRL_1000T_FD    0x200
#define MII_MASSLA_CTRL_PORT_TYPE   0x400
#define MII_MASSLA_CTRL_CONFIG_VAL  0x800
#define MII_MASSLA_CTRL_CONFIG_EN   0x1000

/* MII Master-Slave Status register bit definition */

#define MII_MASSLA_STAT_LP1000T_HD  0x400
#define MII_MASSLA_STAT_LP1000T_FD  0x800
#define MII_MASSLA_STAT_REMOTE_RCV  0x1000
#define MII_MASSLA_STAT_LOCAL_RCV   0x2000
#define MII_MASSLA_STAT_CONF_RES    0x4000
#define MII_MASSLA_STAT_CONF_FAULT  0x8000

/* MII Extented Status register bit definition */

#define MII_EXT_STAT_1000T_HD       0x1000
#define MII_EXT_STAT_1000T_FD       0x2000
#define MII_EXT_STAT_1000X_HD       0x4000
#define MII_EXT_STAT_1000X_FD       0x8000

/* technology ability field bit definitions */

#define MII_TECH_10BASE_T	0x0020	/* 10Base-T */
#define MII_TECH_10BASE_FD	0x0040	/* 10Base-T Full Duplex */
#define MII_TECH_100BASE_TX	0x0080	/* 100Base-TX */
#define MII_TECH_100BASE_TX_FD	0x0100	/* 100Base-TX Full Duplex */
#define MII_TECH_100BASE_T4	0x0200	/* 100Base-T4 */

#define MII_TECH_PAUSE		0x0400  /* PAUSE */
#define MII_TECH_ASM_PAUSE	0x0800  /* Asym pause */
#define MII_TECH_PAUSE_MASK	0x0c00

#define MII_ADS_TECH_MASK	0x1fe0	/* technology abilities mask */
#define MII_TECH_MASK		MII_ADS_TECH_MASK
#define MII_ADS_SEL_MASK	0x001f	/* selector field mask */

#define MII_AN_FAIL             0x10    /* auto-negotiation fail */
#define MII_STAT_FAIL           0x20    /* errors in the status register */
#define MII_PHY_NO_ABLE     	0x40    /* the PHY lacks some abilities */

/* MII management frame structure */

#define MII_MF_PREAMBLE		0xffffffff	/* preamble pattern */
#define MII_MF_ST		0x1		/* start of frame pattern */
#define MII_MF_OP_RD		0x2		/* read operation pattern */
#define MII_MF_OP_WR		0x1		/* write operation pattern */

#define MII_MF_PREAMBLE_LEN	0x20		/* preamble lenght in bit */
#define MII_MF_ST_LEN		0x2		/* start frame lenght in bit */
#define MII_MF_OP_LEN		0x2		/* op code lenght in bit */
#define MII_MF_ADDR_LEN		0x5		/* PHY addr lenght in bit */
#define MII_MF_REG_LEN		0x5		/* PHY reg lenght in bit */
#define MII_MF_TA_LEN		0x2		/* turnaround lenght in bit */
#define MII_MF_DATA_LEN		0x10		/* data lenght in bit */

/* defines related to the PHY device */

#define MII_PHY_PRE_INIT    	0x0001          /* PHY info pre-initialized */
#define MII_PHY_AUTO        	0x0010          /* auto-negotiation allowed */
#define MII_PHY_TBL         	0x0020          /* use negotiation table */
#define MII_PHY_100         	0x0040          /* PHY may use 100Mbit speed */
#define MII_PHY_10          	0x0080          /* PHY may use 10Mbit speed */
#define MII_PHY_FD          	0x0100          /* PHY may use full duplex */
#define MII_PHY_HD          	0x0200          /* PHY may use half duplex */
#define MII_PHY_ISO		0x0400          /* isolate all PHYs */
#define MII_PHY_PWR_DOWN    	0x0800          /* power down mode */
#define MII_PHY_DEF_SET		0x1000		/* set a default mode */
#define MII_ALL_BUS_SCAN	0x2000		/* scan the all bus */
#define MII_PHY_MONITOR		0x4000		/* monitor the PHY's status */
#define MII_PHY_INIT		0x8000		/* PHY info initialized */
#define MII_PHY_1000T_FD	0x10000		/* PHY may use 1000-T full duplex */
#define MII_PHY_1000T_HD	0x20000		/* PHY mau use 1000-T half duplex */
#define MII_PHY_TX_FLOW_CTRL	0x40000		/* Transmit flow control */
#define MII_PHY_RX_FLOW_CTRL	0x80000		/* Receive flow control */
#define MII_PHY_GMII_TYPE	0x100000        /* GMII = 1, MII = 0 */
#define MII_PHY_ISO_UNAVAIL	0x200000        /* ctrl reg isolate func not available */

/* miscellaneous defines */

#define MII_PHY_DEF_DELAY   300             /* max delay before link up, etc. */
#define MII_PHY_NO_DELAY    0x0		    /* do not delay */
#define MII_PHY_NULL        0xff            /* PHY is not present */
#define MII_PHY_DEF_ADDR    0x0             /* default PHY's logical address */

#define MII_PHY_LINK_UNKNOWN	0x0       /* link method - Unknown */
#define MII_PHY_LINK_AUTO	0x1       /* link method - Auto-Negotiation */
#define MII_PHY_LINK_FORCE	0x2       /* link method - Force link */

/*
 * these values may be used in the default phy mode field of the load
 * string, since that is used to force the operating mode of the PHY
 * in case any attempt to establish the link failed.
 */

#define PHY_10BASE_T            0x00     /* 10 Base-T */
#define PHY_10BASE_T_FDX        0x01     /* 10 Base Tx, full duplex */
#define PHY_100BASE_TX          0x02     /* 100 Base Tx */
#define PHY_100BASE_TX_FDX      0x03     /* 100 Base TX, full duplex */
#define PHY_100BASE_T4          0x04     /* 100 Base T4 */
#define PHY_AN_ENABLE          	0x05     /* re-enable auto-negotiation */


#define MII_AN_TBL_MAX		20	/* max number of entries in the table */

/* allowed PHY's speeds */
#define MII_1000MBS         1000000000      /* bits per sec */
#define MII_100MBS          100000000       /* bits per sec */
#define MII_10MBS           10000000        /* bits per sec */

/* ===== Realtek PHY definitions ===== */

#define PHY_SPEED_RES   		3
#define PHY_SPEED_1000  		2
#define PHY_SPEED_100   		1
#define PHY_SPEED_10    		0
#define RTL_PHYSR_ADR			0X11
#define RTL_PHYSR_SPEED_RD(src)    	(((src) & 0x0000C000) >> 14)
#define RTL_PHYSR_LINK_RD(src)    	(((src) & 0x00000400) >> 10)

/* */
#define RTL_BMCR_ADR            0
#define RTL_BMSR_ADR            1
#define RTL_PHYID1_ADR          2
#define RTL_PHYID2_ADR          3
#define RTL_PHYSR_ADR           0X11

/* No need to poll CSR faster than 1 ms */
#define PHY_CSR_POLL_DELAY

/* SGMII related functions */
#define INT_PHY_ADDR	0x1E
#define apm_miiphy_write(priv, reg, data) \
	apm_genericmiiphy_write(priv, INT_PHY_ADDR, reg, data)
#define apm_miiphy_read(priv, reg, data) \
	apm_genericmiiphy_read(priv, INT_PHY_ADDR, reg, data)

/* LErr(3b) Decoding */
enum apm_enet_lerr {
	ENET_NO_ERR = 0,	    /**< No Error */
	ENET_AXI_WR_ERR = 1,	    /**< AXI write data error due to RSIF */
	ENET_ING_CRC_ERR = 2,	    /**< Rx packet had CRC */
	ENET_AXI_RD_ERR = 3,	    /**< AXI read data error when processing
				       a work message in TSIF */
	ENET_LL_RD_ERR = 4,	    /**< AXI Link List read error when
				       processing a work message in TSIF */
	ENET_ING_ERR = 5,	    /**< Rx packet had ingress processing
				       error */
	ENET_CHKSUM_ERR	= 5,	    /**< Checksum error */
	ENET_BAD_MSG_ERR = 6,	    /**< Bad message to subsytem */
	ENET_MISC_ERR = 7,	    /**< Other ingress processing error */
	ENET_MAC_TRUNC_ERR = 7,	    /**< MAX truncated */
	ENET_MAC_LEN_ERR = 8,	    /**< Packet length error */
	ENET_PKT_LESS64_ERR = 9,    /**< MAC length lesser than 64B */
	ENET_MAC_OVERRUN_ERR = 10,  /**< FIFO overrun on ingress */
	ENET_UNISEC_CHKSUM_ERR = 11, /**< Rx pacekt checksum error */
	ENET_UNISEC_LEN_ERR = 12,   /**< Rx pkt length mismatch QM message */
	ENET_UNISEC_ICV_ERR = 13,   /**< Rx pkt ICV error */
	ENET_UNISEC_PROTO_ERR = 14, /**< Rx pkt protocol field mismatch */
	ENET_FP_TIMEOUT_ERR = 15    /**< Free pool buffer timeout */
};

/* Statistics related variables */

/* Error TX/RX Statistics - maintained by software */
struct apm_emac_error_stats {
	u64 rx_hw_errors;
	u64 rx_hw_overrun;
	u64 tx_dropped;
};

/**
 * @struct  eth_frame_stats
 * @brief   This is the transmit and receive frames combine statistics
 **
 */
struct eth_frame_stats {
	u32 c_64B_frames;	/**< Tx & Rx 64 Byte	Frame Counter */
	u32 c_65_127B_frames;	/**< Tx & Rx 65 to 127 Byte Frame Counter */
	u32 c_128_255B_frames;	/**< Tx & Rx 128 to 255 Byte Frame Counter */
	u32 c_256_511B_frames;	/**< Tx & Rx 256 to 511 Byte Frame Counter */
	u32 c_512_1023B_frames;	/**< Tx & Rx 512 to 1023 Byte Frame Counter */
	u32 c_1024_1518B_frames;/**< Tx & Rx 1024 to 1518 Byte Frame Counter */
	u32 c_1519_1522B_frames;/**< Tx & Rx 1519 to 1522 Byte Frame Counter */
};

/**
 * @struct  eth_rx_stats
 * @brief   This is the receive frames statistics
 **
 */
struct eth_rx_stat {
	u32 rx_byte_count;	/**< Receive Byte Counter */
	u32 rx_packet_count;	/**< Receive Packet Counter */
	u32 rx_fcs_err_count;	/**< Receive FCS Error Counter */
	u32 rx_multicast_pkt_count;	/**< Receive Multicast Packet Counter */
	u32 rx_broadcast_pkt_count;	/**< Receive Broadcast Packet Counter */
	u32 rx_cntrl_frame_pkt_count;	/**< Rx Control Frame Packet Counter */
	u32 rx_pause_frame_pkt_count;	/**< Rx Pause Frame Packet Counter */
	u32 rx_unknown_op_pkt_count;	/**< Rx Unknown Opcode Packet Counter */
	u32 rx_alignment_err_pkt_count;	/**< Rx Alignment Err Packet Counter */
	u32 rx_frm_len_err_pkt_count;	/**< Rx Frame Len Err Packet Counter */
	u32 rx_code_err_pkt_count;	/**< Rx Code Error Packet Counter */
	u32 rx_carrier_sense_err_pkt_count;	/**< Rx Carrier Sense Err Pkt*/
	u32 rx_undersize_pkt_count;	/**< Receive Undersize Packet Counter */
	u32 rx_oversize_pkt_count;	/**< Receive Oversize Packet Counter */
	u32 rx_fragment_count;	/**< Receive Fragment Counter */
	u32 rx_jabber_count;	/**< Receive Jabber Counter */
	u32 rx_drop_pkt_count;	/**< Receive Drop Packet Counter */
};

/**
 * @struct  eth_tx_stats
 * @brief   This is the transmit frames statistics
 **
 */
struct eth_tx_stats {
	u32 tx_byte_count;		/**< Tx Byte cnt */
	u32 tx_pkt_count;		/**< Tx pkt cnt */
	u32 tx_multicast_pkt_count;	/**< Tx Multicast Pkt cnt */
	u32 tx_broadcast_pkt_count;	/**< Tx Broadcast pkt cnt */
	u32 tx_pause_frame_count;	/**< Tx Pause Control Frame cnt */
	u32 tx_deferral_pkt_count;	/**< Tx Deferral pkt cnt */
	u32 tx_exesiv_def_pkt_count;	/**< Tx Excessive Deferral pkt cnt */
	u32 tx_single_coll_pkt_count;	/**< Tx Single Collision pkt cnt */
	u32 tx_multi_coll_pkt_count;	/**< Tx Multiple Collision pkt cnt */
	u32 tx_late_coll_pkt_count;	/**< Tx Late Collision pkt cnt */
	u32 tx_exesiv_coll_pkt_count;	/**< Tx Excessive Collision pkt cnt */
	u32 tx_toll_coll_pkt_count;	/**< Tx Toll Collision pkt cnt */
	u32 tx_pause_frm_hon_count;	/**< Tx Pause Frame Honored cnt */
	u32 tx_drop_frm_count;		/**< Tx Drop Frame cnt */
	u32 tx_jabber_frm_count;	/**< Tx Jabber Frame cnt */
	u32 tx_fcs_err_frm_count;	/**< Tx FCS Error Frame cnt */
	u32 tx_control_frm_count;	/**< Tx Control Frame cnt */
	u32 tx_oversize_frm_count;	/**< Tx Oversize Frame cnt */
	u32 tx_undersize_frm_count;	/**< Tx Undersize Frame cnt */
	u32 tx_fragments_frm_count;	/**< Tx Fragments Frame cnt */
};

/**
 * @struct  eth_detailed_stats
 * @brief   This is the detailed statistics counts for Ethernet device
 **
 */
struct eth_detailed_stats {
	struct eth_frame_stats eth_combined_stats;
					/**< Tx, Rx combined stats */
	struct eth_rx_stat rx_stats;	/**< Rx statistics */
	struct eth_tx_stats tx_stats;	/**< Tx statistics */
	struct apm_emac_error_stats estats;
};

/* Ethernet private structure */
struct apm_enet_priv {
	void *eth_csr_addr_v;        /**< Virtual base addr of xNET CSR */
	void *eth_cle_addr_v;        /**< Virtual base addr of xNET CLE */
	void *eth_qmi_addr_v;        /**< Virtual base addr of xNET QMI */
	void *eth_sds_csr_addr_v;    /**< Virtual base addr of xNET Serdes CSR */
	void *eth_clkrst_csr_addr_v; /**< Virtual base addr of xNET CLKRST CSR */
	void *eth_diag_csr_addr_v;   /**< Virtual base addr of xNET DIAG CSR */
	void *mac_mii_addr_v;        /**< Virtual base addr of MAC MII Indirect */

	void *mcx_mac_addr_v;        /**< Virtual base addr of MCX MAC Indirect */
	void *mcx_stats_addr_v;      /**< Virtual base addr of MCX STAT Indirect */
	void *mcx_mac_csr_addr_v;    /**< Virtual base addr of MCX MAC CSR */
	void *sata_enet_csr_addr_v;  /**< Virtual base addr of SATA_ENET CSR */

	void *axg_mac_addr_v;        /**< Virtual base addr of AXG MAC Indirect */
	void *axg_stats_addr_v;      /**< Virtual base addr of AXG STAT Indirect */
	void *axg_mac_csr_addr_v;    /**< Virtual base addr of AXG MAC CSR */
	void *xgenet_pcs_addr_v;     /**< Virtual base addr of XGENET PCS Indirect */
	void *xgenet_mdio_csr_addr_v;/**< Virtual base addr of XGENET MDIO CSR */

	u64 paddr_base;		    /**< Base physical address of device */
	void *vaddr_base;	    /**< Base Virtual address for the device */
	u64 ppaddr_base;	    /**< Per port physical address of device */
	void *vpaddr_base;	    /**< Per port Virtual address of device */

	u32 phy_addr;		    /**< Virtual address for PHY */
	u32 phy_mode;		    /**< PHY mode */
	u32 port;		    /**< Port Id */
	u32 speed;		    /**< Forced Link Speed */
	u32 link_status;
	u32 crc;		    /**< CRC enable / disable */
	u32 autoneg_set;	   /**< Reserved */
	u32 mac_to_mac;		   /**< Tell traffic is MAC-to-MAC */
	u32 desired_speed;	   /**< In case of MAC-to-MAC, no autoneg,
				    ** tell the desired speed to setup */
	u32 phyless;		   /**< PHY stays away from board on
				    ** common server board design */
	u32 force_serdes_reset;	   /**< Force analog reset till stable state */
	u32 std_alone;		   /**< Ethernet is not used in pair,
				    ** only ENET_1 OR ENET_3, 
				    ** allow to force controller reset */

	/* Function pointers */
	void (*port_reset)(struct apm_enet_priv *priv, u32 mii_mode);
	int (*phy_autoneg_done)(struct apm_enet_priv *priv);
	void (*phy_link_mode)(struct apm_enet_priv *priv, u32 *speed, u32 *state);
	void (*mac_reset)(struct apm_enet_priv *priv);
	int (*mac_init)(struct apm_enet_priv *priv,
			unsigned char *dev_addr, int speed, int crc);
	void (*mac_rx_state)(struct apm_enet_priv *priv, u32 enable);
	void (*mac_tx_state)(struct apm_enet_priv *priv, u32 enable);
	void (*mac_set_ipg)(struct apm_enet_priv *priv, u16 new_ipg);
	void (*get_stats)(struct apm_enet_priv *priv, struct eth_detailed_stats *stats);
	void (*set_mac_addr)(struct apm_enet_priv *priv, unsigned char *dev_addr);
	void (*cle_bypass)(struct apm_enet_priv *priv,
		u32 cle_dstqid, u32 cle_fpsel, u32 cle_nxtfpsel, int bypass_en);
	void (*tx_offload)(struct apm_enet_priv *priv, u32 command, u32 value);
	void (*qmi_assoc)(struct apm_enet_priv *priv);
	int (*get_link_status)(struct apm_enet_priv *priv);
	void (*port_shutdown)(struct apm_enet_priv *priv);
	void (*serdes_reset)(struct apm_enet_priv *priv, int port);
	void (*autoneg)(struct apm_enet_priv *priv, int autoneg);
};

/**
 * @brief   This function writes into Ethernet CSR
 * @param   priv MAC private stucture
 * @param   block_id  CSR block id within Ethernet
 * @param   reg_offset	Register offset to write
 * @return  value  value to be written
 **
 */
int apm_enet_write(struct apm_enet_priv *priv, u8 block_id,
		u32 reg_offset, u32 value);

/**
 * @brief   This function reads Ethernet CSR
 * @param   priv MAC private stucture
 * @param   block_id  CSR block id within Ethernet
 * @param   reg_offset	Register offset to read
 * @return  value  Pointer to value
 **
 */
int apm_enet_read(struct apm_enet_priv *priv, u8 block_id,
		 u32 reg_offset, u32 *value);

/**
 * @brief   This function reads from the MII Manangement registers
 * @param   priv Ethernet private structure
 *	    phy_id Which phy_addr to use
 *	    reg	   Which register to read
 *	    data   Read value copied to this variable
 * @return  0 - success or -1 - failure
 **
 */
int apm_genericmiiphy_read(struct apm_enet_priv *priv, u8 phy_id,
			   unsigned char reg, u32 *data);
/**
 * @brief   This function writes to the MII Management registers
 * @param   priv Ethernet private structure
 *	    phy_id Which phy_addr to use
 *	    reg	   Which register to write
 *	    data   Value to be written
 * @return  0 - success or -1 - failure
 **
 */
int apm_genericmiiphy_write(struct apm_enet_priv *priv, u8 phy_id,
			    unsigned char reg, u32 data);

/**
 * @brief   This function resets the entire part of Ethernet IP
            and initiliaze in specified mii_mode
 * @param   priv MAC private stucture
 * @param   MII mode to initialize with
 * @return  None
 * @note    It will put entire Ethernet Subsystem block
            in reset and then init with specified mii_mode.
 **
 */
void apm_enet_port_reset(struct apm_enet_priv *priv, u32 mii_mode);

/**
 * @brief   This function resets the entire part of MAC
            and minimal init for phy access
 * @param   priv MAC private stucture
 * @return  None
 * @note    It will put both Transmit and Receive MAC Control block
            in reset and then init.
 **
 */
void apm_enet_mac_reset(struct apm_enet_priv *priv);
void apm_enet_serdes_reset(struct apm_enet_priv *priv);
int apm_enet_get_link_status(struct apm_enet_priv *priv);
void apm_enet_autoneg(struct apm_enet_priv *privi, int autoneg);

/**
 * @brief   This function initializes the MAC
 * @param   priv Private structure of MAC
 * @param   dev_addr MAC address
 * @param   The gmac init link speed (i.e. 10 or 100 or 1000 Mbps)
 * @param   Maximum transmission unit
 * @param   CRC enable/disable
 * @return  0 - success or -1 - failure
 **
 */
int apm_enet_mac_init(struct apm_enet_priv *priv, unsigned char *dev_addr,
			int speed, int crc);

/**
 * @brief   This function Enables/Disables Receive interface of MAC
 * @param   priv MAC private stucture
 * @param   enable 0/1 Disable/Enable Receive interface
 * @return  None
 * @note    Enabling MAC Receive interface will allow the MAC
 *	    to receive frames from the PHY. Disabling MAC Receive
 *	    interface will prevent the reception of frames.
 **
 */
void apm_enet_mac_rx_state(struct apm_enet_priv *priv, u32 enable);

/**
 * @brief   This function Enables/Disabled Transmit interface of MAC
 * @param   priv MAC private stucture
 * @param   enable 0/1 Disable/Enable Transmit interface
 * @return  None
 * @note    Enabling MAC Transmit interface will allow the MAC to transmit
 *	    frames from the system. Disabling MAC Transmit interface will
 *	    prevent the transmission of frames.
 **
 */
void apm_enet_mac_tx_state(struct apm_enet_priv *priv, u32 enable);

/**
 * @brief   Set InterFrameGap in terms of bits
 * @param   priv MAC private stucture
 * @param   ifg Inter Frame Gap in terms of bits
 * @return  None
 *
 */
void apm_enet_mac_set_ipg(struct apm_enet_priv *priv, u16 ipg);

/**
 * @brief   This function returns detailed statistics counts for the device
 * @param   priv Device structure of MAC
 * @param   detailed_stats Detailed statistics structure to be filled up
 * @return  None
 **
 */
void apm_enet_get_stats(struct apm_enet_priv *priv,
				struct eth_detailed_stats *detailed_stats);

/**
 * @brief   This function configures the MAC address of given MAC device
 * @param   priv MAC private stucture
 * @param   mac_addr_hi Higher 4 octects of MAC address
 *	    mac_addr_lo Lower 2 octects of MAC address
 * @return  None.
 **
 */
void apm_enet_set_mac_addr(struct apm_enet_priv *priv, unsigned char *dev_addr);

/**
 * @brief   This function configures the Ethernet to bypass Classifier block
 * @param   priv MAC private stucture
 * @param   dstqid Ethernet RX work queue ID
 *	    fpsel  Ethernet FP PBN
 *	    nxtfpsel  Ethernet Next FP PBN
 * @return  None.
 **
 */
void apm_enet_cle_bypass(struct apm_enet_priv *priv, u32 dstqid,
		 u32 fpsel, u32 nxtfpsel, int en);

/**
 * @brief   This function configures the Ethernet TX Offload configuration like
 *          setting MSS, setting TCP flags position for TSO,
 *          setting vlan id for TX VLAN offloading
 * @param   priv MAC private stucture
 * @param   command TSO configuration paramter
 *	    value TSO configuration parameter value
 * @return  None.
 **
 */
void apm_enet_tx_offload(struct apm_enet_priv *priv, u32 command, u32 value);

/**
 * @brief   This function resets the Ethernet csr, core and serdes
 *          and disables clock to etherent csr and core
 * @param   priv MAC private stucture
 * @return  None.
 **
 */
void apm_enet_port_shutdown(struct apm_enet_priv *priv);

enum xgene_qmtm_qaccess apm_enet_get_qacess(void);

#endif	/* __APM_ENET_COMMON_H__ */
