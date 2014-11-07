/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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

#ifndef __PHY_XGENE_H__
#define __PHY_XGENE_H__

#include "phy-xgene-port.h"

/* Max 8 lanes per a PHY unit */
#define MAX_LANE			8

enum clk_type_t {
	CLK_EXT_DIFF = 0,	/* External differential */
	CLK_INT_DIFF = 1,	/* Internal differential */
	CLK_INT_SING = 2,	/* Internal single ended */
};

enum disk_type {
	DISK_SSD = 0,
	DISK_HDD = 1
};

enum phy_mode {
	MODE_SATA	= 0,	/* List them for simple reference */
	MODE_SGMII	= 1,
	MODE_PCIE	= 2,
	MODE_USB	= 3,
	MODE_XFI	= 4,
	MODE_MAX
};

struct xgene_sata_override_param {
	enum disk_type disk_type[MAX_LANE];
	u32 speed[MAX_LANE]; /* Index for override parameter per lane */
	u32 txspeed[3]; 		/* Tx speed */
	u32 txboostgain_ssd[MAX_LANE*3];/* Tx freq boost and gain control */
	u32 txboostgain[MAX_LANE*3];	/* Tx freq boost and gain control */
	u32 txeyetuning[MAX_LANE*3]; 	/* Tx eye tuning */
	u32 txeyedirection[MAX_LANE*3]; /* Tx eye tuning direction */
	u32 txamplitude[MAX_LANE*3];	/* Tx amplitude control */
	u32 txprecursor_cn1[MAX_LANE*3]; /* Tx emphasis taps 1st pre-cursor */
	u32 txprecursor_cn2[MAX_LANE*3]; /* Tx emphasis taps 2nd pre-cursor */
	u32 txpostcursor_cp1[MAX_LANE*3]; /* Tx emphasis taps post-cursor */
	u32 txequalizer[MAX_LANE*3];      /* Tx equalizer enable/disable */
};

struct xgene_phy_ctx {
	struct device *dev;
	struct phy *phy;
	enum phy_mode mode;		/* Mode of operation */
	enum clk_type_t clk_type;	/* Input clock selection */
	int ssc;			/* Enable SSC */
	int lane;			/* # of lane used */
	void __iomem *sds_base;		/* PHY CSR base addr */
	void __iomem *clk_base;		/* PHY clock CSR base addr */
	void __iomem *core_base;	/* Core base if PCIE PHY */
	void __iomem *ext_cmu_base;	/* PHY SDS/Ref PLL CMU external */
	struct clk *clk;		/* Optional clock */
	int ref_100MHz;			/* Reference clock 100Mhz */
	int inited;			/* Initialized? */

	/* Override Serdes parameters */
	struct xgene_sata_override_param sata_param;
};

int xgene_phy_hw_init(struct xgene_phy_ctx *ctx);
int xgene_is_preA3(void);
int xgene_is_preB0(void);
void xgene_phy_reset_rxd(struct xgene_phy_ctx *ctx, int lane);
int xgene_phy_set_ctle(struct xgene_phy_ctx *ctx, int lane, u32 disk_type);
void xgene_phy_sata_force_gen(struct xgene_phy_ctx *ctx, int lane, int gen);
void xgene_dump_serdes(struct xgene_phy_ctx *ctx, int lane);
void xgene_eyescan(struct xgene_phy_ctx *ctx , int lane); 
void dump_momsel(struct xgene_phy_ctx *ctx , int lane);
void xgene_reprogram_vco(struct xgene_phy_ctx *ctx, int ref_clk);
#endif /* __XGENEPHY_H__ */
