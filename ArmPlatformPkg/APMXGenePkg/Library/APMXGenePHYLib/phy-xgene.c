/*
 * AppliedMicro X-Gene Multi-purpose PHY driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *         Tuan Phan <tphan@apm.com>
 *         Suman Tripathi <stripathi@apm.com>
 *
 * This program and the accompanying materials
 *are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.	The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * Logical Layer Out Of HW module units:
 *
 * -----------------
 * | Internal      |    |------|
 * | Ref PLL CMU   |----|      |     -------------    ---------
 * ------------ ----    | MUX  |-----|PHY PLL CMU|----| Serdes|
 *                      |      |     |           |    ---------
 * External Clock ------|      |     -------------
 *                      |------|
 *
 * The Ref PLL CMU CSR (Configuration System Registers) is accessed
 * indirectly from the SDS offset at 0x2000. It is only required for
 * internal reference clock.
 * The PHY PLL CMU CSR is accessed indirectly from the SDS offset at 0x0000.
 * The Serdes CSR is accessed indirectly from the SDS offset at 0x0400.
 *
 * The Ref PLL CMU can be located within the same PHY IP or outside the PHY IP
 * due to shared Ref PLL CMU. For PHY with Ref PLL CMU shared with another IP,
 * it is located outside the PHY IP. This is the case for the PHY located
 * at 0x1f23a000 (SATA Port 4/5). For such PHY, another resource is required
 * to located the SDS/Ref PLL CMU module and its clock for that IP enabled.
 *
 */
#include "phy-xgene.h"

/* Register offset inside the PHY */
#define SERDES_PLL_INDIRECT_OFFSET	0x0000
#define SERDES_PIPE_INDIRECT_OFFSET	0x10000
#define SERDES_PLL_REF_INDIRECT_OFFSET	0x20000
#define SERDES_PLL2_INDIRECT_OFFSET	0x30000
#define SERDES_INDIRECT_OFFSET		0x0400
#define SERDES_LANE_STRIDE		0x0200
#define SERDES_LANE_X4_STRIDE           0x30000

/* PCIe SDS indirect access registers */
#define PCIE_IND_CMD_REG                0x014
#define PCIE_IND_RDATA_REG              0x018
#define PCIE_IND_WDATA_REG              0x01c

/* USB SDS indirect access registers */
#define USB_IND_CMD_REG                0x02c
#define USB_IND_RDATA_REG              0x050
#define USB_IND_WDATA_REG              0x054

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

#define SATA_SPD_SEL_GEN3		0x7
#define SATA_SPD_SEL_GEN2		0x3
#define SATA_SPD_SEL_GEN1		0x1

#define SSC_DISABLE			0
#define SSC_ENABLE			1

#define FBDIV_VAL_25M			0xef
#define REFDIV_VAL_25M			0x2
#define FBDIV_VAL_50M			0x77
#define REFDIV_VAL_50M			0x1
#define FBDIV_VAL_100M			0x3B
#define REFDIV_VAL_100M			0x0

/* SATA Clock/Reset CSR */
#define SATACLKENREG			0x00000000
#define SATASRESETREG			0x00000004
#define  SATA0_CORE_CLKEN		0x00000002
#define  SATA1_CORE_CLKEN		0x00000004
#define  SATA_MEM_RESET_MASK		0x00000020
#define  SATA_MEM_RESET_RD(src)		(((src) & 0x00000020) >> 5)
#define  SATA_SDS_RESET_MASK		0x00000004
#define  SATA_CSR_RESET_MASK		0x00000001
#define  SATA_CORE_RESET_MASK		0x00000002
#define  SATA_PMCLK_RESET_MASK		0x00000010
#define  SATA_PCLK_RESET_MASK		0x00000008

/* SDS CSR used for PHY Indirect access */
#define SATA_ENET_SDS_PCS_CTL0		0x00000000
#define  REGSPEC_CFG_I_TX_WORDMODE0_SET(dst, src) \
		(((dst) & ~0x00070000) | (((u32) (src) << 16) & 0x00070000))
#define  REGSPEC_CFG_I_RX_WORDMODE0_SET(dst, src) \
		(((dst) & ~0x00e00000) | (((u32) (src) << 21) & 0x00e00000))
#define SATA_ENET_SDS_CTL0		0x0000000c
#define  REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_SET(dst, src) \
		(((dst) & ~0x00007fff) | (((u32) (src)) & 0x00007fff))
#define SATA_ENET_SDS_CTL1		0x00000010
#define  CFG_I_SPD_SEL_CDR_OVR1_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src)) & 0x0000000f))
#define SATA_ENET_SDS_RST_CTL		0x00000024
#define SATA_ENET_SDS_IND_CMD_REG	0x0000003c
#define  CFG_IND_WR_CMD_MASK		0x00000001
#define  CFG_IND_RD_CMD_MASK		0x00000002
#define  CFG_IND_CMD_DONE_MASK		0x00000004
#define  CFG_IND_ADDR_SET(dst, src) \
		(((dst) & ~0x003ffff0) | (((u32) (src) << 4) & 0x003ffff0))
#define SATA_ENET_SDS_IND_RDATA_REG	0x00000040
#define SATA_ENET_SDS_IND_WDATA_REG	0x00000044
#define SATA_ENET_CLK_MACRO_REG		0x0000004c
#define  I_RESET_B_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src)) & 0x00000001))
#define  I_PLL_FBDIV_SET(dst, src) \
		(((dst) & ~0x001ff000) | (((u32) (src) << 12) & 0x001ff000))
#define  I_CUSTOMEROV_SET(dst, src) \
		(((dst) & ~0x00000f80) | (((u32) (src) << 7) & 0x00000f80))
#define  O_PLL_LOCK_RD(src)		(((src) & 0x40000000) >> 30)
#define  O_PLL_READY_RD(src)		(((src) & 0x80000000) >> 31)


/* PLL Clock Macro Unit (CMU) CSR accessing from SDS indirectly */
#define CMU_REG0			0x00000
#define  CMU_REG0_PLL_REF_SEL_MASK	0x00002000
#define  CMU_REG0_PLL_REF_SEL_SET(dst, src)	\
		(((dst) & ~0x00002000) | (((u32) (src) << 13) & 0x00002000))
#define  CMU_REG0_PDOWN_MASK		0x00004000
#define  CMU_REG0_CAL_COUNT_RESOL_SET(dst, src) \
		(((dst) & ~0x000000e0) | (((u32) (src) << 5) & 0x000000e0))
#define  CMU_REG0_PCIEGEN3_MASK		0x00000001
#define  CMU_REG0_PCIEGEN3_SET(dst, src)	\
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define  CMU_REG0_PDOWN_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define CMU_REG1			0x00002
#define  CMU_REG1_PLL_CP_SET(dst, src) \
		(((dst) & ~0x00003c00) | (((u32) (src) << 10) & 0x00003c00))
#define  CMU_REG1_PLL_MANUALCAL_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  CMU_REG1_PLL_CP_SEL_SET(dst, src) \
		(((dst) & ~0x000003e0) | (((u32) (src) << 5) & 0x000003e0))
#define  CMU_REG1_REFCLK_CMOS_SEL_MASK	0x00000001
#define  CMU_REG1_REFCLK_CMOS_SEL_SET(dst, src)	\
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define CMU_REG2			0x00004
#define  CMU_REG2_PLL_REFDIV_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define  CMU_REG2_PLL_LFRES_SET(dst, src) \
		(((dst) & ~0x0000001e) | (((u32) (src) << 1) & 0x0000001e))
#define  CMU_REG2_PLL_FBDIV_SET(dst, src) \
		(((dst) & ~0x00003fe0) | (((u32) (src) << 5) & 0x00003fe0))
#define CMU_REG3			0x00006
#define  CMU_REG3_VCOVARSEL_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define  CMU_REG3_VCO_MOMSEL_INIT_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define  CMU_REG3_VCO_MANMOMSEL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define CMU_REG4			0x00008
#define  CMU_REG4_VCOVARSEL_PCIE_MASK	0x0000000f
#define  CMU_REG4_VCOVARSEL_PCIE_SET(dst, src)	\
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define  CMU_REG4_MOMSEL_INIT_PCIE_MASK	0x000003f0
#define  CMU_REG4_MOMSEL_INIT_PCIE_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define  CMU_REG4_MANMOMSEL_PCIE_MASK	0x0000fc00
#define  CMU_REG4_MANMOMSEL_PCIE_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define CMU_REG5			0x0000a
#define  CMU_REG5_PLL_LFSMCAP_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define  CMU_REG5_PLL_LOCK_RESOLUTION_SET(dst, src) \
		(((dst) & ~0x0000000e) | (((u32) (src) << 1) & 0x0000000e))
#define  CMU_REG5_PLL_LFCAP_SET(dst, src) \
		(((dst) & ~0x00003000) | (((u32) (src) << 12) & 0x00003000))
#define  CMU_REG5_PLL_RESETB_MASK	0x00000001
#define CMU_REG6			0x0000c
#define  CMU_REG6_PLL_VREGTRIM_SET(dst, src) \
		(((dst) & ~0x00000600) | (((u32) (src) << 9) & 0x00000600))
#define  CMU_REG6_MAN_PVT_CAL_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define CMU_REG7			0x0000e
#define  CMU_REG7_PLL_CALIB_DONE_RD(src) ((0x00004000 & (u32) (src)) >> 14)
#define  CMU_REG7_VCO_CAL_FAIL_RD(src)	((0x00000c00 & (u32) (src)) >> 10)
#define CMU_REG8			0x00010
#define CMU_REG9			0x00012
#define  CMU_REG9_WORD_LEN_8BIT		0x000
#define  CMU_REG9_WORD_LEN_10BIT	0x001
#define  CMU_REG9_WORD_LEN_16BIT	0x002
#define  CMU_REG9_WORD_LEN_20BIT	0x003
#define  CMU_REG9_WORD_LEN_32BIT	0x004
#define  CMU_REG9_WORD_LEN_40BIT	0x005
#define  CMU_REG9_WORD_LEN_64BIT	0x006
#define  CMU_REG9_WORD_LEN_66BIT	0x007
#define  CMU_REG9_TX_WORD_MODE_CH1_SET(dst, src) \
		(((dst) & ~0x00000380) | (((u32) (src) << 7) & 0x00000380))
#define  CMU_REG9_TX_WORD_MODE_CH0_SET(dst, src) \
		(((dst) & ~0x00000070) | (((u32) (src) << 4) & 0x00000070))
#define  CMU_REG9_PLL_POST_DIVBY2_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  CMU_REG9_VBG_BYPASSB_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define  CMU_REG9_IGEN_BYPASS_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define CMU_REG10			0x00014
#define  CMU_REG10_VREG_REFSEL_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define CMU_REG11			0x00016
#define CMU_REG12			0x00018
#define  CMU_REG12_STATE_DELAY9_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#define CMU_REG13			0x0001a
#define  CMU_REG13_STATE_DELAY1_MASK	0x0000f000
#define  CMU_REG13_STATE_DELAY1_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#define  CMU_REG13_STATE_DELAY2_MASK	0x00000f00
#define  CMU_REG13_STATE_DELAY2_SET(dst, src) \
		(((dst) & ~0x00000f00) | (((u32) (src) << 8) & 0x00000f00))
#define  CMU_REG13_STATE_DELAY3_MASK	0x000000f0
#define  CMU_REG13_STATE_DELAY3_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#define  CMU_REG13_STATE_DELAY4_MASK	0x0000000f
#define  CMU_REG13_STATE_DELAY4_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define CMU_REG14			0x0001c
#define  CMU_REG14_STATE_DELAY8_MASK	0x0000000f
#define  CMU_REG14_STATE_DELAY8_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define  CMU_REG14_STATE_DELAY7_MASK	0x000000f0
#define  CMU_REG14_STATE_DELAY7_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#define  CMU_REG14_STATE_DELAY6_MASK	0x00000f00
#define  CMU_REG14_STATE_DELAY6_SET(dst, src) \
		(((dst) & ~0x00000f00) | (((u32) (src) << 8) & 0x00000f00))
#define  CMU_REG14_STATE_DELAY5_MASK	0x0000f000
#define  CMU_REG14_STATE_DELAY5_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#define CMU_REG15			0x0001e
#define CMU_REG16			0x00020
#define  CMU_REG16_PVT_DN_MAN_ENA_MASK	0x00000001
#define  CMU_REG16_DN_MAN_ENA_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define  CMU_REG16_PVT_UP_MAN_ENA_MASK	0x00000002
#define  CMU_REG16_UP_MAN_ENA_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(dst, src) \
		(((dst) & ~0x0000001c) | (((u32) (src) << 2) & 0x0000001c))
#define  CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define  CMU_REG16_BYPASS_PLL_LOCK_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define CMU_REG17			0x00022
#define  CMU_REG17_PVT_CODE_R2A_SET(dst, src) \
		(((dst) & ~0x00007f00) | (((u32) (src) << 8) & 0x00007f00))
#define  CMU_REG17_RESERVED_7_SET(dst, src) \
		(((dst) & ~0x000000e0) | (((u32) (src) << 5) & 0x000000e0))
#define  CMU_REG17_PVT_TERM_MAN_ENA_MASK	0x00008000
#define  CMU_REG17_TERM_MAN_ENA_SET(dst, src) \
		(((dst) & ~0x00008000) | (((u32) (src) << 15) & 0x00008000))
#define CMU_REG18			0x00024
#define CMU_REG19			0x00026
#define  CMU_REG19_PLL_VCOMOMSEL_MASK	0x0000fc00
#define  CMU_REG19_PLL_VCOMOMSEL_RD(src) \
		((0x0000fc00 & (u32) (src)) >> 10)
#define  CMU_REG19_PLL_VCOMOMSEL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define CMU_REG20			0x00028
#define CMU_REG21			0x0002a
#define CMU_REG22			0x0002c
#define CMU_REG23			0x0002e
#define CMU_REG24			0x00030
#define CMU_REG25			0x00032
#define CMU_REG26			0x00034
#define  CMU_REG26_FORCE_PLL_LOCK_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define CMU_REG27			0x00036
#define  CMU_REG27_VOLT_SEL_CH0_MASK	0x0000e000
#define  CMU_REG27_VOLT_SEL_CH0_SET(dst, src) \
		(((dst) & ~0x0000e000) | (((u32) (src) << 13) & 0x0000e000))
#define  CMU_REG27_VOLT_SEL_CH1_MASK	0x00001c00
#define  CMU_REG27_VOLT_SEL_CH1_SET(dst, src) \
		(((dst) & ~0x00001c00) | (((u32) (src) << 10) & 0x00001c00))
#define  CMU_REG27_VOLT_SEL_CH2_MASK	0x00000380
#define  CMU_REG27_VOLT_SEL_CH2_SET(dst, src) \
		(((dst) & ~0x00000380) | (((u32) (src) << 7) & 0x00000380))
#define  CMU_REG27_VOLT_SEL_CH3_MASK	0x00000070
#define  CMU_REG27_VOLT_SEL_CH3_SET(dst, src) \
		(((dst) & ~0x00000070) | (((u32) (src) << 4) & 0x00000070))
#define CMU_REG28			0x00038
#define CMU_REG29			0x0003a
#define CMU_REG30			0x0003c
#define  CMU_REG30_LOCK_COUNT_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32) (src) << 1) & 0x00000006))
#define  CMU_REG30_PCIE_MODE_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  CMU_REG30_REFDIV_GEN3_MASK	0x0000c000
#define  CMU_REG30_REFDIV_GEN3_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define  CMU_REG30_FBDIV_GEN3_MASK	0x00003fe0
#define  CMU_REG30_FBDIV_GEN3_SET(dst, src) \
		(((dst) & ~0x00003fe0) | (((u32) (src) << 5) & 0x00003fe0))
#define CMU_REG31			0x0003e
#define  CMU_REG31_OVERRIDE_CH0_MASK	0x00000008
#define  CMU_REG31_OVERRIDE_CH0_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  CMU_REG31_OVERRIDE_CH1_MASK	0x00000004
#define  CMU_REG31_OVERRIDE_CH1_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define  CMU_REG31_OVERRIDE_CH2_MASK	0x00000002
#define  CMU_REG31_OVERRIDE_CH2_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  CMU_REG31_OVERRIDE_CH3_MASK	0x00000001
#define  CMU_REG31_OVERRIDE_CH3_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define CMU_REG32			0x00040
#define  CMU_REG32_FORCE_VCOCAL_START_MASK	0x00004000
#define  CMU_REG32_VCOCAL_START_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define  CMU_REG32_PVT_CAL_WAIT_SEL_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32) (src) << 1) & 0x00000006))
#define  CMU_REG32_IREF_ADJ_SET(dst, src) \
		(((dst) & ~0x00000180) | (((u32) (src) << 7) & 0x00000180))
#define  CMU_REG32_FORCE_PVT_CAL_START_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32)(src) << 0xb) & 0x00000800))
#define CMU_REG33			0x00042
#define  CMU_REG33_CUST_MODE_INV_MASK	0x0000ffff
#define  CMU_REG33_CUST_MODE_INV_SET(dst, src) \
		(((dst) & ~0x0000ffff) | (((u32) (src) << 0) & 0x0000ffff))
#define CMU_REG34			0x00044
#define  CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define  CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(dst, src) \
		(((dst) & ~0x00000f00) | (((u32) (src) << 8) & 0x00000f00))
#define  CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#define  CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#define CMU_REG35			0x00046
#define  CMU_REG35_PLL_SSC_MOD_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 9) & 0x0000fe00))
#define CMU_REG36				0x00048
#define  CMU_REG36_PLL_SSC_EN_SET(dst, src) \
		(((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))
#define  CMU_REG36_PLL_SSC_VSTEP_SET(dst, src) \
		(((dst) & ~0x0000ffc0) | (((u32) (src) << 6) & 0x0000ffc0))
#define  CMU_REG36_PLL_SSC_DSMSEL_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define CMU_REG37			0x0004a
#define  CMU_REG37_CAL_DONE_OVR_MASK	0x0000f000
#define  CMU_REG37_CAL_DONE_OVR_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#define  CMU_REG37_SEARCH_DONE_OVR_MASK	0x0000000f
#define  CMU_REG37_SEARCH_DONE_OVR_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#define CMU_REG38			0x0004c
#define CMU_REG39			0x0004e

/* PHY lane CSR accessing from SDS indirectly */
#define RXTX_REG0			0x000
#define  RXTX_REG0_CTLE_EQ_HR_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG0_CTLE_EQ_QR_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#define  RXTX_REG0_CTLE_EQ_FR_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#define RXTX_REG1			0x002
#define  RXTX_REG1_RXACVCM_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#define  RXTX_REG1_CTLE_EQ_SET(dst, src) \
		(((dst) & ~0x00000f80) | (((u32) (src) << 7) & 0x00000f80))
#define  RXTX_REG1_RXVREG1_SET(dst, src) \
                (((dst) & ~0x00000060) | (((u32) (src) << 5) & 0x00000060))
#define  RXTX_REG1_RXIREF_ADJ_SET(dst, src) \
               (((dst) & ~0x00000006) | (((u32) (src) << 1) &  0x00000006))
#define  RXTX_REG1_RXVREG1P2_SET(dst, src) \
                (((dst) & ~0x00000018) | (((u32) (src) << 3) & 0x00000018))
#define RXTX_REG2			0x004
#define  RXTX_REG2_VTT_ENA_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#define  RXTX_REG2_TX_FIFO_ENA_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define  RXTX_REG2_VTT_SEL_SET(dst, src) \
		(((dst) & ~0x000000c0) | (((u32) (src) << 6) & 0x000000c0))
#define  RXTX_REG2_RXPDBIAS_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define  RXTX_REG2_TX_PDOWN_SET(dst, src) \
		(((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))
#define  RXTX_REG2_RESETB_TERM_MASK	0x00004000
#define  RXTX_REG2_RESETB_TERM_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define  RXTX_REG2_RESETB_TXD_MASK	0x00001000
#define  RXTX_REG2_RESETB_TXD_SET(dst, src) \
		(((dst) & ~0x00001000) | (((u32) (src) << 12) & 0x00001000))
#define  RXTX_REG2_BIST_ENA_TX_MASK	0x00000800
#define  RXTX_REG2_BIST_ENA_TX_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32) (src) << 11) & 0x00000800))
#define  RXTX_REG2_TX_INV_MASK		0x00000400
#define  RXTX_REG2_TX_INV_SET(dst, src) \
		(((dst) & ~0x00000400) | (((u32) (src) << 10) & 0x00000400))
#define  RXTX_REG2_TX_FIFO_ENA_MASK	0x00000020
#define  RXTX_REG2_TX_FIFO_ENA_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define  RXTX_REG2_TX_RCVDET_SEL_MASK	0x0000000c
#define  RXTX_REG2_TX_RCVDET_SEL_SET(dst, src) \
		(((dst) & ~0x0000000c) | (((u32) (src) << 2) & 0x0000000c))
#define RXTX_REG4			0x008
#define  RXTX_REG4_TX_LOOPBACK_BUF_EN_MASK	0x00000040
#define  RXTX_REG4_TX_LOOPBACK_BUF_EN_SET(dst, src) \
		 (((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define  RXTX_REG4_TX_DATA_RATE_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define  RXTX_REG4_TX_WORD_MODE_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#define  RXTX_REG4_COUNTER_TIME_SEL_CP_SET(dst, src) \
        (((dst) & ~0x00000038) | (((u32)(src) << 0x3) & 0x00000038))
#define  RXTX_REG4_COUNTER_TIME_SEL_CN_SET(dst, src) \
        (((dst) & ~0x00000007) | (((u32)(src) << 0x0) & 0x00000007))
#define RXTX_REG5			0x00a
#define  RXTX_REG5_TX_CN1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG5_TX_CP1_SET(dst, src) \
		(((dst) & ~0x000007e0) | (((u32) (src) << 5) & 0x000007e0))
#define  RXTX_REG5_TX_CN2_SET(dst, src) \
		(((dst) & ~0x0000001f) | (((u32) (src) << 0) & 0x0000001f))
#define RXTX_REG6			0x00c
#define  RXTX_REG6_TXAMP_CNTL_SET(dst, src) \
		(((dst) & ~0x00000780) | (((u32) (src) << 7) & 0x00000780))
#define  RXTX_REG6_TXAMP_ENA_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define  RXTX_REG6_RX_BIST_ERRCNT_RD_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define  RXTX_REG6_TX_IDLE_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  RXTX_REG6_RX_BIST_RESYNC_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  RXTX_REG6_TX_CN2_INV_MASK	0x00004000
#define  RXTX_REG6_TX_CN2_INV_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define RXTX_REG7			0x00e
#define  RXTX_REG7_RESETB_RXD_MASK	0x00000100
#define  RXTX_REG7_RESETB_RXA_MASK	0x00000080
#define  RXTX_REG7_RX_DATA_RATE_MASK	0x00000600
#define  RXTX_REG7_LP_ENA_CTLE_MASK	0x00004000
#define  RXTX_REG7_BIST_ENA_RX_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define  RXTX_REG7_RX_WORD_MODE_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#define  RXTX_REG7_RX_DATA_RATE_RD(src)	((0x00000600 & (u32) (src)) >> 9)
#define  RXTX_REG7_RX_DATA_RATE_SET(dst, src) \
		(((dst) & ~0x00000600) | (((u32) (src) << 9) & 0x00000600))
#define  RXTX_REG7_RESETB_RXD_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#define  RXTX_REG7_RESETB_RXA_SET(dst, src) \
		(((dst) & ~0x00000080) | (((u32) (src) << 7) & 0x00000080))
#define  RXTX_REG7_LP_ENA_CTLE_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define RXTX_REG8			0x010
#define  RXTX_REG8_CDR_LOOP_ENA_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#define  RXTX_REG8_CDR_BYPASS_RXLOS_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32) (src) << 11) & 0x00000800))
#define  RXTX_REG8_SSC_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000200) | (((u32) (src) << 9) & 0x00000200))
#define  RXTX_REG8_SD_VREF_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#define  RXTX_REG8_SD_DISABLE_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#define RXTX_REG11			0x016
#define  RXTX_REG11_PHASE_ADJUST_LIMIT_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define RXTX_REG12			0x018
#define  RXTX_REG12_LATCH_OFF_ENA_SET(dst, src) \
		(((dst) & ~0x00002000) | (((u32) (src) << 13) & 0x00002000))
#define  RXTX_REG12_SUMOS_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define  RXTX_REG12_RX_DET_TERM_ENABLE_MASK	0x00000002
#define  RXTX_REG12_RX_DET_TERM_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  RXTX_REG12_RX_INV_MASK		0x00000800
#define  RXTX_REG12_RX_INV_SET(dst, src) \
		(((dst) & ~0x00000800) |(((u32) (src) << 11) & 0x00000800))
#define RXTX_REG13			0x01a
#define RXTX_REG14			0x01c
#define  RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(dst, src) \
		(((dst) & ~0x0000003f) | (((u32) (src) << 0) & 0x0000003f))
#define  RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#define RXTX_REG19               	0x026
#define  RXTX_REG19_ESCAN_TAP_RD(src) \
		((0x0000fe00 & (u32) (src)) >> 0x9)
#define  RXTX_REG19_ESCAN_TAP_WR(dst) \
		(0x0000fe00 & ((u32) (dst) << 0x9))
#define  RXTX_REG19_ESCAN_TAP_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 0x9) & 0x0000fe00))

#define  RXTX_REG19_ESCAN_VMARGIN_RD(src) \
	 	((0x000000fe & (u32) (src)) >> 0x1)
#define  RXTX_REG19_ESCAN_VMARGIN_WR(dst) \
		(0x000000fe & ((u32) (dst) << 0x1))
#define  RXTX_REG19_ESCAN_VMARGIN_SET(dst, src) \
	 	(((dst) & ~0x000000fe) | (((u32)(src) << 0x1) & 0x000000fe))
#define RXTX_REG20			0x028
#define RXTX_REG21			0x02a
#define  RXTX_REG21_DO_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#define  RXTX_REG21_XO_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#define  RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(src)	((0x0000000f & (u32)(src)))
#define RXTX_REG22			0x02c
#define  RXTX_REG22_SO_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#define  RXTX_REG22_EO_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#define  RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(src)	((0x0000000f & (u32)(src)))
#define RXTX_REG23			0x02e
#define  RXTX_REG23_DE_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#define  RXTX_REG23_XE_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#define RXTX_REG24			0x030
#define  RXTX_REG24_EE_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#define  RXTX_REG24_SE_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#define RXTX_REG26			0x034
#define  RXTX_REG26_PERIOD_ERROR_LATCH_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#define  RXTX_REG26_BLWC_ENA_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define RXTX_REG27			0x036
#define  RXTX_REG27_RXPD_CONFIG_MASK	0x0000c000
#define  RXTX_REG27_RXPD_CONFIG_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define RXTX_REG28			0x038
#define RXTX_REG28_DFE_TAP_ENA_RD(src)	((0x0000ffff & (u32)(src)))
#define RXTX_REG31			0x03e
#define RXTX_REG38			0x04c
#define  RXTX_REG38_CUSTOMER_PINMODE_INV_SET(dst, src) \
		(((dst) & 0x0000fffe) | (((u32) (src) << 1) & 0x0000fffe))
#define RXTX_REG39			0x04e
#define RXTX_REG40			0x050
#define RXTX_REG41			0x052
#define RXTX_REG42			0x054
#define RXTX_REG43			0x056
#define RXTX_REG44			0x058
#define RXTX_REG45			0x05a
#define RXTX_REG46			0x05c
#define RXTX_REG47			0x05e
#define RXTX_REG48			0x060
#define RXTX_REG49			0x062
#define RXTX_REG50			0x064
#define RXTX_REG51			0x066
#define RXTX_REG52			0x068
#define RXTX_REG53			0x06a
#define RXTX_REG54			0x06c
#define RXTX_REG55			0x06e
#define RXTX_REG61			0x07a
#define  RXTX_REG61_ISCAN_INBERT_SET(dst, src) \
		(((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))
#define  RXTX_REG61_LOADFREQ_SHIFT_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(dst, src) \
		(((dst) & ~0x000000c0) | (((u32) (src) << 6) & 0x000000c0))
#define  RXTX_REG61_SPD_SEL_CDR_SET(dst, src) \
		(((dst) & ~0x00003c00) | (((u32) (src) << 10) & 0x00003c00))
#define  RXTX_REG61_EYE_ACC_RESETB_RD(src) \
		((0x00000100 & (u32) (src)) >> 0x8)
#define  RXTX_REG61_EYE_ACC_RESETB_WR(dst) \
		(0x00000100 & ((u32) (dst) << 0x8))
#define  RXTX_REG61_EYE_ACC_RESETB_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32)(src) << 0x8) & 0x00000100))
#define RXTX_REG61_EYE_MONITOR_CAPTURE_RD(src) \
	((0x00000200 & (u32) (src)) >> 0x9)
#define RXTX_REG61_EYE_MONITOR_CAPTURE_WR(dst) \
	(0x00000200 & ((u32) (dst) << 0x9))
#define RXTX_REG61_EYE_MONITOR_CAPTURE_SET(dst, src) \
	(((dst) & ~0x00000200) | (((u32) (src) << 0x9) & 0x00000200))
#define RXTX_REG62			0x07c
#define  RXTX_REG62_PERIOD_H1_QLATCH_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#define  RXTX_REG62_SWITCH_H1_QLATCH_RD(src) \
		((0x00000400 & (u32) (src)) >> 0xa)
#define  RXTX_REG62_SWITCH_H1_QLATCH_WR(dst) \
		(0x00000400 & ((u32) (dst) << 0xa))
#define  RXTX_REG62_SWITCH_H1_QLATCH_SET(dst, src) \
		(((dst) & ~0x00000400) | (((u32) (src) << 0xa) & 0x00000400))
#define  RXTX_REG62_H1_QLATCH_SIGN_INV_RD(src) \
		((0x00004000 & (u32) (src)) >> 0xe)
#define  RXTX_REG62_H1_QLATCH_SIGN_INV_WR(dst) \
		(0x00004000 & ((u32) (dst) << 0xe))
#define  RXTX_REG62_H1_QLATCH_SIGN_INV_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 0xe) & 0x00004000))
#define RXTX_REG81			0x0a2
#define  RXTX_REG81_MU_DFE3_MASK	0x0000003e
#define  RXTX_REG81_MU_DFE3_SET(dst, src) \
		(((dst) & ~0x0000003e) |(((u32) (src) << 1) & 0x0000003e))
#define  RXTX_REG81_MU_DFE1_MASK	0x0000f800
#define  RXTX_REG81_MU_DFE1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG81_MU_DFE2_MASK	0x000007c0
#define  RXTX_REG81_MU_DFE2_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#define  RXTX_REG89_MU_TH7_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG89_MU_TH8_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#define  RXTX_REG89_MU_TH9_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#define RXTX_REG96			0x0c0
#define  RXTX_REG96_MU_FREQ1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG96_MU_FREQ2_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#define  RXTX_REG96_MU_FREQ3_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#define RXTX_REG99			0x0c6
#define  RXTX_REG99_MU_PHASE1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#define  RXTX_REG99_MU_PHASE2_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#define  RXTX_REG99_MU_PHASE3_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#define RXTX_REG100			0x0c8
#define  RXTX_REG100_MU_PHASE4_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((uint32_t)(src) << 0xb) & 0x0000f800))
#define  RXTX_REG100_MU_PHASE5_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((uint32_t)(src) << 0x6) & 0x000007c0))
#define  RXTX_REG100_MU_PHASE6_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((uint32_t)(src) << 0x1) & 0x0000003e))
#define RXTX_REG101			0x0ca
#define  RXTX_REG101_MU_PHASE7_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((uint32_t)(src) << 0xb) & 0x0000f800))
#define  RXTX_REG101_MU_PHASE8_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((uint32_t)(src) << 0x6) & 0x000007c0))
#define  RXTX_REG101_MU_PHASE9_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((uint32_t)(src) << 0x1) & 0x0000003e))
#define RXTX_REG102			0x0cc
#define  RXTX_REG102_FREQLOOP_LIMIT_SET(dst, src) \
		(((dst) & ~0x00000060) | (((u32) (src) << 5) & 0x00000060))
#define RXTX_REG114			0x0e4
#define	RXTX_REG118			0x0ec
#define  RXTX_REG118_ACC_FULL_FLAG_RD(src) \
		((0x00000010 & (u32) (src)) >> 0x4)
#define RXTX_REG121			0x0f2
#define  RXTX_REG121_SUMOS_CAL_CODE_RD(src) ((0x0000003e & (u32)(src)) >> 0x1)
#define RXTX_REG123              	0x0f6
#define RXTX_REG124	         	0x0f8
#define RXTX_REG125			0x0fa
#define  RXTX_REG125_PQ_REG_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 9) & 0x0000fe00))
#define  RXTX_REG125_SIGN_PQ_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#define  RXTX_REG125_SIGN_PQ_2C_SET(dst, src) \
		(((dst) & ~0x00000080) | (((u32) (src) << 7) & 0x00000080))
#define  RXTX_REG125_PHZ_MANUALCODE_SET(dst, src) \
		(((dst) & ~0x0000007c) | (((u32) (src) << 2) & 0x0000007c))
#define  RXTX_REG125_PHZ_MANUAL_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define RXTX_REG126                     0x0fc
#define  RXTX_REG126_QI_REG_RD(src) \
		((0x0000fe00 & (u32) (src)) >> 0x9)
#define  RXTX_REG126_QI_REG_WR(dst) \
		(0x0000fe00 & ((u32) (dst) << 0x9))
#define  RXTX_REG126_QI_REG_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 0x9) & 0x0000fe00))
#define  RXTX_REG126_SIGN_QI_REG_RD(src)	\
		((0x00000002 & (u32) (src)) >> 0x1)
#define  RXTX_REG126_SIGN_QI_REG_WR(dst) \
		(0x00000002 & ((u32) (dst) << 0x1))
#define  RXTX_REG126_SIGN_QI_REG_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 0x1) & 0x00000002))
#define RXTX_REG127			0x0fe
#define  RXTX_REG127_FORCE_SUM_CAL_START_MASK	0x00000002
#define  RXTX_REG127_FORCE_LAT_CAL_START_MASK	0x00000004
#define  RXTX_REG127_FORCE_SUM_CAL_START_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  RXTX_REG127_FORCE_LAT_CAL_START_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define  RXTX_REG127_LATCH_MAN_CAL_ENA_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#define  RXTX_REG127_DO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define  RXTX_REG127_XO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define RXTX_REG128			0x100
#define  RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(dst, src) \
		(((dst) & ~0x0000000c) | (((u32) (src) << 2) & 0x0000000c))
#define  RXTX_REG128_EO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define  RXTX_REG128_SO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define RXTX_REG129			0x102
#define  RXTX_REG129_DE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define  RXTX_REG129_XE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define RXTX_REG130			0x104
#define  RXTX_REG130_EE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#define  RXTX_REG130_SE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#define RXTX_REG144			0x120
#define  RXTX_REG144_USE_RAWSD_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#define RXTX_REG145			0x122
#define  RXTX_REG145_TX_IDLE_SATA_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#define  RXTX_REG145_RXES_ENA_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#define  RXTX_REG145_RXDFE_CONFIG_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#define  RXTX_REG145_RXVWES_LATENA_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#define RXTX_REG147			0x126
#define  RXTX_REG147_STMC_OVERRIDE_MASK	0x0000ffff
#define  RXTX_REG147_STMC_OVERRIDE_SET(dst, src) \
		(((dst) & ~0x0000ffff) | (((u32) (src) << 0) & 0x0000ffff))
#define RXTX_REG148			0x128
#define RXTX_REG158			0x13c
#define  RXTX_REG158_SUM_CALIB_DONE_RD(src) \
		((0x00008000 & (u32) (src)) >> 15)
#define  RXTX_REG158_SUM_CALIB_ERR_RD(src) \
		((0x00004000 & (u32) (src)) >> 14)
#define  RXTX_REG158_LAT_CALIB_DONE_RD(src) \
		((0x00008000 & (u32) (src)) >> 11)
#define RXTX_REG92        0xb8
#define RXTX_REG92_MU_BCA9_SET(dst, src) \
        (((dst) & ~0x0000003e) | (((u32) (src) << 0x1) & 0x0000003e))
#define RXTX_REG161              0x142
#define RXTX_REG162              0x144
#define INITIALIZED			1
#define UNINITIALIZED			0
#define DISK_SSD 			0
#define DISK_HDD			1

/* Clock macro type */
enum cmu_type_t {
	REF_CMU = 0,	/* Clock macro is the internal reference clock */
	PHY_CMU = 1,	/* Clock macro is the PLL for the Serdes */
	PHY2_CMU = 2,	/* Clock macro is the 2nd PLL for the Serdes */
};

enum mux_type_t {
	MUX_SELECT_ATA = 0,	/* Switch the MUX to ATA */
	MUX_SELECT_SGMMII = 0,	/* Switch the MUX to SGMII */
};

static void sds_wr(void __iomem *csr_base, u32 indirect_cmd_reg,
		   u32 indirect_data_reg, u32 addr, u32 data)
{
	unsigned long deadline = jiffies + HZ;
	u32 val;
	u32 cmd;

	cmd = CFG_IND_WR_CMD_MASK | CFG_IND_CMD_DONE_MASK;
	cmd = CFG_IND_ADDR_SET(cmd, addr);
	writel(data, csr_base + indirect_data_reg);
	readl(csr_base + indirect_data_reg); /* Force a barrier */
	writel(cmd, csr_base + indirect_cmd_reg);
	readl(csr_base + indirect_cmd_reg); /* Force a barrier */
	do {
		val = readl(csr_base + indirect_cmd_reg);
	} while (!(val & CFG_IND_CMD_DONE_MASK) &&
		 time_before(jiffies, deadline));
	if (!(val & CFG_IND_CMD_DONE_MASK))
		pr_err("SDS WR timeout at 0x%p offset 0x%08X value 0x%08X\n",
		       csr_base + indirect_cmd_reg, addr, data);
}

static void sds_rd(void __iomem *csr_base, u32 indirect_cmd_reg,
		   u32 indirect_data_reg, u32 addr, u32 *data)
{
	unsigned long deadline = jiffies + HZ;
	u32 val;
	u32 cmd;

	cmd = CFG_IND_RD_CMD_MASK | CFG_IND_CMD_DONE_MASK;
	cmd = CFG_IND_ADDR_SET(cmd, addr);
	writel(cmd, csr_base + indirect_cmd_reg);
	readl(csr_base + indirect_cmd_reg); /* Force a barrier */
	do {
		val = readl(csr_base + indirect_cmd_reg);
	} while (!(val & CFG_IND_CMD_DONE_MASK)&&
		 time_before(jiffies, deadline));
	*data = readl(csr_base + indirect_data_reg);
	if (!(val & CFG_IND_CMD_DONE_MASK))
		pr_err("SDS WR timeout at 0x%p offset 0x%08X value 0x%08X\n",
		       csr_base + indirect_cmd_reg, addr, *data);
}

static void cmu_wr(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
		   u32 reg, u32 data)
{
	void __iomem *sds_base;
	u32 cmd_reg;
	u32 wr_reg;
	u32 rd_reg;
	u32 val;

	if (cmu_type == REF_CMU && ctx->ext_cmu_base &&
	    (ctx->clk_type == CLK_INT_DIFF || ctx->clk_type == CLK_INT_SING))
		/* Reference CMU out side of the IP */
		sds_base = ctx->ext_cmu_base;
	else
		sds_base = ctx->sds_base;

	if (ctx->mode == MODE_PCIE) {
		cmd_reg = PCIE_IND_CMD_REG;
		wr_reg = PCIE_IND_WDATA_REG;
		rd_reg = PCIE_IND_RDATA_REG;
	} else if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		wr_reg = USB_IND_WDATA_REG;
		rd_reg = USB_IND_RDATA_REG;
	} else {
		cmd_reg = SATA_ENET_SDS_IND_CMD_REG;
		wr_reg = SATA_ENET_SDS_IND_WDATA_REG;
		rd_reg = SATA_ENET_SDS_IND_RDATA_REG;
	}

	if (cmu_type == REF_CMU)
		reg += SERDES_PLL_REF_INDIRECT_OFFSET;
	else if (cmu_type == PHY_CMU)
		reg += SERDES_PLL_INDIRECT_OFFSET;
	else
		reg += SERDES_PLL2_INDIRECT_OFFSET;
	sds_wr(sds_base, cmd_reg, wr_reg, reg, data);
	sds_rd(sds_base, cmd_reg, rd_reg, reg, &val);
	pr_debug("CMU WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data, val);
}

static void cmu_rd(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
		   u32 reg, u32 *data)
{
	void __iomem *sds_base;
	u32 cmd_reg;
	u32 rd_reg;

	if (cmu_type == REF_CMU && ctx->ext_cmu_base &&
	    (ctx->clk_type == CLK_INT_DIFF || ctx->clk_type == CLK_INT_SING))
		/* Reference CMU out side of the IP */
		sds_base = ctx->ext_cmu_base;
	else
		sds_base = ctx->sds_base;

	if (ctx->mode == MODE_PCIE) {
		cmd_reg = PCIE_IND_CMD_REG;
		rd_reg = PCIE_IND_RDATA_REG;
	} else if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		rd_reg = USB_IND_RDATA_REG;
	} else {
		cmd_reg = SATA_ENET_SDS_IND_CMD_REG;
		rd_reg = SATA_ENET_SDS_IND_RDATA_REG;
	}

	if (cmu_type == REF_CMU)
		reg += SERDES_PLL_REF_INDIRECT_OFFSET;
	else if (cmu_type == PHY_CMU)
		reg += SERDES_PLL_INDIRECT_OFFSET;
	else
		reg += SERDES_PLL2_INDIRECT_OFFSET;
	sds_rd(sds_base, cmd_reg, rd_reg, reg, data);
	pr_debug("CMU RD addr 0x%X value 0x%08X\n", reg, *data);
}

static void cmu_toggle1to0(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
			   u32 reg, u32 bits)
{
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val |= bits;
	cmu_wr(ctx, cmu_type, reg, val);
	cmu_rd(ctx, cmu_type, reg, &val);
	val &= ~bits;
	cmu_wr(ctx, cmu_type, reg, val);
}

static void cmu_clrbits(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
			u32 reg, u32 bits)
{
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val &= ~bits;
	cmu_wr(ctx, cmu_type, reg, val);
}

static void cmu_setbits(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
			u32 reg, u32 bits)
{
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val |= bits;
	cmu_wr(ctx, cmu_type, reg, val);
}

static void serdes_wr(struct xgene_phy_ctx *ctx, int lane, u32 reg, u32 data)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 cmd_reg;
	u32 wr_reg;
	u32 rd_reg;
	u32 val;

	if (ctx->mode == MODE_PCIE) {
		cmd_reg = PCIE_IND_CMD_REG;
		wr_reg = PCIE_IND_WDATA_REG;
		rd_reg = PCIE_IND_RDATA_REG;
	} else if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		wr_reg = USB_IND_WDATA_REG;
		rd_reg = USB_IND_RDATA_REG;
	} else {
		cmd_reg = SATA_ENET_SDS_IND_CMD_REG;
		wr_reg = SATA_ENET_SDS_IND_WDATA_REG;
		rd_reg = SATA_ENET_SDS_IND_RDATA_REG;
	}

	reg += (lane / 4) * SERDES_LANE_X4_STRIDE;
	reg += SERDES_INDIRECT_OFFSET;
	reg += (lane % 4) * SERDES_LANE_STRIDE;
	sds_wr(sds_base, cmd_reg, wr_reg, reg, data);
	sds_rd(sds_base, cmd_reg, rd_reg, reg, &val);
	pr_debug("SERDES WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data,
		 val);
}

static void serdes_rd(struct xgene_phy_ctx *ctx, int lane, u32 reg, u32 *data)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 cmd_reg;
	u32 rd_reg;

	if (ctx->mode == MODE_PCIE) {
		cmd_reg = PCIE_IND_CMD_REG;
		rd_reg = PCIE_IND_RDATA_REG;
	} else if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		rd_reg = USB_IND_RDATA_REG;
	} else {
		cmd_reg = SATA_ENET_SDS_IND_CMD_REG;
		rd_reg = SATA_ENET_SDS_IND_RDATA_REG;
	}

	reg += (lane / 4) * SERDES_LANE_X4_STRIDE;
	reg += SERDES_INDIRECT_OFFSET;
	reg += (lane % 4) * SERDES_LANE_STRIDE;
	sds_rd(sds_base, cmd_reg, rd_reg, reg, data);
	pr_debug("SERDES RD addr 0x%X value 0x%08X\n", reg, *data);
}

static void serdes_clrbits(struct xgene_phy_ctx *ctx, int lane, u32 reg,
			   u32 bits)
{
	u32 val;

	serdes_rd(ctx, lane, reg, &val);
	val &= ~bits;
	serdes_wr(ctx, lane, reg, val);
}

static void serdes_setbits(struct xgene_phy_ctx *ctx, int lane, u32 reg,
			   u32 bits)
{
	u32 val;

	serdes_rd(ctx, lane, reg, &val);
	val |= bits;
	serdes_wr(ctx, lane, reg, val);
}

static void pipe_wr(struct xgene_phy_ctx *ctx, u32 reg, u32 data)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 cmd_reg;
	u32 rd_reg;
	u32 wr_reg;
	u32 val;

	reg += SERDES_PIPE_INDIRECT_OFFSET;
	if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		rd_reg = USB_IND_RDATA_REG;
		wr_reg = USB_IND_WDATA_REG;
	} else {
		cmd_reg = PCIE_IND_CMD_REG;
		rd_reg = PCIE_IND_RDATA_REG;
		wr_reg = PCIE_IND_WDATA_REG;
	}
	sds_wr(sds_base, cmd_reg, wr_reg, reg, data);
	sds_rd(sds_base, cmd_reg, rd_reg, reg, &val);
	pr_debug("PIPE WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data, val);
}

static void pipe_rd(struct xgene_phy_ctx *ctx, u32 reg, u32 *data)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 cmd_reg;
	u32 rd_reg;

	reg += SERDES_PIPE_INDIRECT_OFFSET;
	if (ctx->mode == MODE_USB) {
		cmd_reg = USB_IND_CMD_REG;
		rd_reg = USB_IND_RDATA_REG;
	} else {
		cmd_reg = PCIE_IND_CMD_REG;
		rd_reg = PCIE_IND_RDATA_REG;
	}
	sds_rd(sds_base, cmd_reg, rd_reg, reg, data);
	pr_debug("PIPE RD addr 0x%X value 0x%08X\n", reg, *data);
}

static void xgene_phy_cfg_cmu_clk_type(struct xgene_phy_ctx *ctx,
				       enum cmu_type_t cmu_type,
				       enum clk_type_t clk_type)
{
	u32 val;

	/* Set the reset sequence delay for TX ready assertion */
	cmu_rd(ctx, cmu_type, CMU_REG12, &val);
	val = CMU_REG12_STATE_DELAY9_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG12, val);
	/* Set the programmable stage delays between various enable stages */
	cmu_wr(ctx, cmu_type, CMU_REG13, 0x0222);
	cmu_wr(ctx, cmu_type, CMU_REG14, 0x2225);

	/* Configure clock type */
	if (clk_type == CLK_EXT_DIFF) {
		/* Select external clock mux */
		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);
		/* Select CMOS as reference clock  */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set external reference clock\n");
	} else if (clk_type == CLK_INT_DIFF) {
		/* Select internal clock mux */
		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);
		/* Select CMOS as reference clock  */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set internal reference clock\n");
	} else if (clk_type == CLK_INT_SING) {
		/*
		 * NOTE: This clock type is NOT support for controller
		 *	 whose internal clock shared in the PCIe controller
		 *
		 * Select internal clock mux
		 */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		/* Select CML as reference clock */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev,
			"Set internal single ended reference clock\n");
	}
}

int __weak xgene_phy_cmu_reg10_vreg_refsel(struct xgene_phy_ctx *ctx,
   					   enum cmu_type_t cmu_type,
					   enum clk_type_t clk_type)
{
	/* Default value of CMU REG10 VREF REFSEL value */
	return 0x1;
}

int __weak xgene_phy_cmu_reg32_iref_adj(struct xgene_phy_ctx *ctx,
   					enum cmu_type_t cmu_type,
					enum clk_type_t clk_type)
{
	/* Default value of CMU REG32 IREF ADJ value */
	return 0x1;
}

static void xgene_phy_sata_cfg_cmu_core(struct xgene_phy_ctx *ctx,
					enum cmu_type_t cmu_type,
					enum clk_type_t clk_type)
{
	u32 val;
	int ref_100MHz;

	if (cmu_type == REF_CMU) {
		/* Set VCO calibration voltage threshold */
		cmu_rd(ctx, cmu_type, CMU_REG34, &val);
		val = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(val, 0x7);
		val = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(val, 0xc);
		val = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(val, 0x3);
		val = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(val, 0x8);
		cmu_wr(ctx, cmu_type, CMU_REG34, val);
	}

	/* Set the VCO calibration counter */
	cmu_rd(ctx, cmu_type, CMU_REG0, &val);
	if (cmu_type == REF_CMU)
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x4);
	else
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, val);

	/* Configure PLL for calibration */
	cmu_rd(ctx, cmu_type, CMU_REG1, &val);
	val = CMU_REG1_PLL_CP_SET(val, 0x1);
	if (cmu_type == REF_CMU)
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x5);
	else
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x3);
	if (cmu_type == REF_CMU)
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x0);
	else
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG1, val);

	if (cmu_type != REF_CMU) {
		cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
		cmu_rd(ctx, cmu_type, CMU_REG5, &val);
	}

	/* Configure the PLL for either 100MHz or 50MHz */
	cmu_rd(ctx, cmu_type, CMU_REG2, &val);
	if (cmu_type == REF_CMU) {
		val = CMU_REG2_PLL_LFRES_SET(val, 0xa);
		ref_100MHz = ctx->ref_100MHz;
	} else {
		val = CMU_REG2_PLL_LFRES_SET(val, 0x3);
		if (clk_type == CLK_EXT_DIFF) {
			ref_100MHz = 0;
		}
		else
			ref_100MHz = 1;
	}
	if (ref_100MHz) {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_100M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_100M);
	} else {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_50M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_50M);
	}
	cmu_wr(ctx, cmu_type, CMU_REG2, val);

	/* Configure the VCO */
	cmu_rd(ctx, cmu_type, CMU_REG3, &val);
	if (cmu_type == REF_CMU) {
		val = CMU_REG3_VCOVARSEL_SET(val, 0x3);
		val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x10);
	} else {
		val = CMU_REG3_VCOVARSEL_SET(val, 0xF);
		val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x1a);
		val = CMU_REG3_VCO_MANMOMSEL_SET(val, 0x15);
	}
	cmu_wr(ctx, cmu_type, CMU_REG3, val);

	/* Disable force PLL lock */
	cmu_rd(ctx, cmu_type, CMU_REG26, &val);
	val = CMU_REG26_FORCE_PLL_LOCK_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG26, val);

	cmu_rd(ctx, cmu_type, CMU_REG27, &val);
	val = CMU_REG27_VOLT_SEL_CH0_SET(val, 0x1);
	val = CMU_REG27_VOLT_SEL_CH1_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG27, val);
	cmu_rd(ctx, cmu_type, CMU_REG31, &val);
	val = CMU_REG31_OVERRIDE_CH0_SET(val, 0x1);
	val = CMU_REG31_OVERRIDE_CH1_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG31, val);

	/* Setup PLL loop filter */
	cmu_rd(ctx, cmu_type, CMU_REG5, &val);
	val = CMU_REG5_PLL_LFSMCAP_SET(val, 0x3);
	val = CMU_REG5_PLL_LFCAP_SET(val, 0x3);
	if (cmu_type == REF_CMU || !xgene_is_preB0())
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x7);
	else
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x4);
	cmu_wr(ctx, cmu_type, CMU_REG5, val);

	/* Enable or disable manual calibration */
	cmu_rd(ctx, cmu_type, CMU_REG6, &val);
	val = CMU_REG6_PLL_VREGTRIM_SET(val, 0x2);
	val = CMU_REG6_MAN_PVT_CAL_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG6, val);

	/* Configure lane for 20-bits */
	if (cmu_type == PHY_CMU) {
		cmu_rd(ctx, cmu_type, CMU_REG9, &val);
		val = CMU_REG9_TX_WORD_MODE_CH1_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_TX_WORD_MODE_CH0_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_PLL_POST_DIVBY2_SET(val, 0x1);
		val = CMU_REG9_VBG_BYPASSB_SET(val, 0x0);
		val = CMU_REG9_IGEN_BYPASS_SET(val , 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG9, val);

		cmu_rd(ctx, cmu_type, CMU_REG10, &val);
		val = CMU_REG10_VREG_REFSEL_SET(val,
			xgene_phy_cmu_reg10_vreg_refsel(ctx, cmu_type,
							clk_type));
		cmu_wr(ctx, cmu_type, CMU_REG10, val);
	}

	cmu_rd(ctx, cmu_type, CMU_REG16, &val);
	val = CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(val, 0x1);
	val = CMU_REG16_BYPASS_PLL_LOCK_SET(val, 0x1);
	if (cmu_type == REF_CMU)
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x4);
	else
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG16, val);

	/* Configure for SATA */
	cmu_rd(ctx, cmu_type, CMU_REG30, &val);
	val = CMU_REG30_PCIE_MODE_SET(val, 0x0);
	if (xgene_is_preB0())
		val = CMU_REG30_LOCK_COUNT_SET(val, 0x3);
	else
		val = CMU_REG30_LOCK_COUNT_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG30, val);

	/* Disable state machine bypass */
	cmu_wr(ctx, cmu_type, CMU_REG31, 0xF);

	cmu_rd(ctx, cmu_type, CMU_REG32, &val);
	if (xgene_is_preB0())
		val = CMU_REG32_PVT_CAL_WAIT_SEL_SET(val, 0x3);
	else
		val = CMU_REG32_PVT_CAL_WAIT_SEL_SET(val, 0x7);

	if (cmu_type == REF_CMU)
		val = CMU_REG32_IREF_ADJ_SET(val, 0x3);
	else
		val = CMU_REG32_IREF_ADJ_SET(val,
			xgene_phy_cmu_reg32_iref_adj(ctx, cmu_type, clk_type));
	cmu_wr(ctx, cmu_type, CMU_REG32, val);

	/* Set VCO calibration threshold */
	cmu_wr(ctx, cmu_type, CMU_REG34, 0x8967);

	/* Set CTLE Override and override waiting from state machine */
	cmu_wr(ctx, cmu_type, CMU_REG37, 0xF00F);
}

static void xgene_phy_ssc_enable(struct xgene_phy_ctx *ctx,
				 enum cmu_type_t cmu_type)
{
	u32 val;

	/* Set SSC modulation value */
	cmu_rd(ctx, cmu_type, CMU_REG35, &val);
	val = CMU_REG35_PLL_SSC_MOD_SET(val, 98);
	cmu_wr(ctx, cmu_type, CMU_REG35, val);

	/* Enable SSC, set vertical step and DSM value */
	cmu_rd(ctx, cmu_type, CMU_REG36, &val);
	val = CMU_REG36_PLL_SSC_VSTEP_SET(val, 30);
	val = CMU_REG36_PLL_SSC_EN_SET(val, 1);
	val = CMU_REG36_PLL_SSC_DSMSEL_SET(val, 1);
	cmu_wr(ctx, cmu_type, CMU_REG36, val);

	/* Reset the PLL */
	cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
	cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Force VCO calibration to restart */
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
}

static void xgene_phy_sata_cfg_lanes(struct xgene_phy_ctx *ctx)
{
	u32 val;
	u32 reg;
	int i;
	int lane;

	for (lane = 0; lane < ctx->lane; lane++) {
		serdes_wr(ctx, lane, RXTX_REG147, 0x6);

		/* Set boost control for quarter, half, and full rate */
		serdes_rd(ctx, lane, RXTX_REG0, &val);
		val = RXTX_REG0_CTLE_EQ_HR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_QR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_FR_SET(val, 0x10);
		serdes_wr(ctx, lane, RXTX_REG0, val);

		/* Set boost control value */
		serdes_rd(ctx, lane, RXTX_REG1, &val);
		val = RXTX_REG1_RXACVCM_SET(val, 0x7);
		val = RXTX_REG1_CTLE_EQ_SET(val,
			ctx->sata_param.txboostgain[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG1_RXVREG1_SET(val, 0x2);
		val = RXTX_REG1_RXIREF_ADJ_SET(val, 0x2);
		if (!xgene_is_preB0())
			val = RXTX_REG1_RXVREG1P2_SET(val, 0x2);
		serdes_wr(ctx, lane, RXTX_REG1, val);

		/* Latch VTT value based on the termination to ground and
		   enable TX FIFO */
		serdes_rd(ctx, lane, RXTX_REG2, &val);
		val = RXTX_REG2_VTT_ENA_SET(val, 0x1);
		val = RXTX_REG2_VTT_SEL_SET(val, 0x1);
		val = RXTX_REG2_TX_FIFO_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG2, val);

		/* Configure Tx for 20-bits */
		serdes_rd(ctx, lane, RXTX_REG4, &val);
		val = RXTX_REG4_TX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG4, val);

		/* Set pre-emphasis first 1 and 2, and post-emphasis values */
		serdes_rd(ctx, lane, RXTX_REG5, &val);
		val = RXTX_REG5_TX_CN1_SET(val,
			ctx->sata_param.txprecursor_cn1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CP1_SET(val,
			ctx->sata_param.txpostcursor_cp1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CN2_SET(val,
			ctx->sata_param.txprecursor_cn2[lane * 3 +
			ctx->sata_param.speed[lane]]);
		serdes_wr(ctx, lane, RXTX_REG5, val);

		/* Set TX amplitude value */
		serdes_rd(ctx, lane, RXTX_REG6, &val);
		val = RXTX_REG6_TXAMP_CNTL_SET(val,
			ctx->sata_param.txamplitude[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG6_TXAMP_ENA_SET(val, 0x1);
		val = RXTX_REG6_TX_IDLE_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_RESYNC_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_ERRCNT_RD_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG6, val);

		/* Configure Rx for 20-bits */
		serdes_rd(ctx, lane, RXTX_REG7, &val);
		val = RXTX_REG7_BIST_ENA_RX_SET(val, 0x0);
		val = RXTX_REG7_RX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG7, val);

		/* Set CDR and LOS values and enable Rx SSC */
		serdes_rd(ctx, lane, RXTX_REG8, &val);
		val = RXTX_REG8_CDR_LOOP_ENA_SET(val, 0x1);
		val = RXTX_REG8_CDR_BYPASS_RXLOS_SET(val, 0x0);
		val = RXTX_REG8_SSC_ENABLE_SET(val, 0x1);
		val = RXTX_REG8_SD_DISABLE_SET(val, 0x0);
		val = RXTX_REG8_SD_VREF_SET(val, 0x4);
		serdes_wr(ctx, lane, RXTX_REG8, val);

		/* Set phase adjust upper/lower limits */
		serdes_rd(ctx, lane, RXTX_REG11, &val);
		val = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG11, val);

		/* Enable Latch Off; disable SUMOS and Tx termination */
		serdes_rd(ctx, lane, RXTX_REG12, &val);
		val = RXTX_REG12_LATCH_OFF_ENA_SET(val, 0x1);
		val = RXTX_REG12_SUMOS_ENABLE_SET(val, 0x0);
		val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG12, val);

		/* Set period error latch to 512T and enable BWL */
		serdes_rd(ctx, lane, RXTX_REG26, &val);
		val = RXTX_REG26_PERIOD_ERROR_LATCH_SET(val, 0x0);
		val = RXTX_REG26_BLWC_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG26, val);

		serdes_wr(ctx, lane, RXTX_REG28, 0x0);

		/* Set DFE loop preset value */
		serdes_wr(ctx, lane, RXTX_REG31, 0x0);

		/* Set Eye Monitor counter width to 12-bit */
		serdes_rd(ctx, lane, RXTX_REG61, &val);
		val = RXTX_REG61_ISCAN_INBERT_SET(val, 0x1);
		val = RXTX_REG61_LOADFREQ_SHIFT_SET(val, 0x0);
		val = RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG61, val);

		serdes_rd(ctx, lane, RXTX_REG62, &val);
		val = RXTX_REG62_PERIOD_H1_QLATCH_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG62, val);

		/* Set BW select tap X for DFE loop */
		for (i = 0; i < 9; i++) {
			reg = RXTX_REG81 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG89_MU_TH7_SET(val, 0xe);
			val = RXTX_REG89_MU_TH8_SET(val, 0xe);
			val = RXTX_REG89_MU_TH9_SET(val, 0xe);
			serdes_wr(ctx, lane, reg, val);
		}

		/* Set BW select tap X for frequency adjust loop */
		for (i = 0; i < 3; i++) {
			reg = RXTX_REG96 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG96_MU_FREQ1_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ2_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ3_SET(val, 0x10);
			serdes_wr(ctx, lane, reg, val);
		}

		/* Set BW select tap X for phase adjust loop */
		for (i = 0; i < 3; i++) {
			reg = RXTX_REG99 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG99_MU_PHASE1_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE2_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE3_SET(val, 0x7);
			serdes_wr(ctx, lane, reg, val);
		}

		serdes_rd(ctx, lane, RXTX_REG102, &val);
		val = RXTX_REG102_FREQLOOP_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG102, val);

		serdes_wr(ctx, lane, RXTX_REG114, 0xffe0);

		serdes_rd(ctx, lane, RXTX_REG125, &val);
		val = RXTX_REG125_SIGN_PQ_SET(val,
			ctx->sata_param.txeyedirection[lane * 3 +
			ctx->sata_param.speed[lane]]);
	 	val = RXTX_REG125_PQ_REG_SET(val,
			ctx->sata_param.txeyetuning[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG125_PHZ_MANUAL_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG125, val);

		serdes_rd(ctx, lane, RXTX_REG127, &val);
		val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG127, val);

		serdes_rd(ctx, lane, RXTX_REG128, &val);
		val = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(val, 0x3);
		serdes_wr(ctx, lane, RXTX_REG128, val);

		serdes_rd(ctx, lane, RXTX_REG145, &val);
		val = RXTX_REG145_RXDFE_CONFIG_SET(val, 0x3);
		val = RXTX_REG145_TX_IDLE_SATA_SET(val, 0x0);
		val = RXTX_REG145_RXES_ENA_SET(val, preB0Chip ? 0x0 : 0x1);
		val = RXTX_REG145_RXVWES_LATENA_SET(val, preB0Chip ? 0x0: 0x1);
		serdes_wr(ctx, lane, RXTX_REG145, val);

		if (xgene_is_preB0()) {
			/*
		 	 * Set Rx LOS filter clock rate, sample rate, and threshold
		 	 * windows
		  	*/
			for (i = 0; i < 4; i++) {
				reg = RXTX_REG148 + i * 2;
				serdes_wr(ctx, lane, reg, 0xFFFF);
			}
		}
	}
}

static int xgene_phy_cal_rdy_chk(struct xgene_phy_ctx *ctx,
				 enum cmu_type_t cmu_type,
				 enum clk_type_t clk_type)
{
	void __iomem *csr_serdes;
	int loop;
	u32 val;

	if (cmu_type == REF_CMU && ctx->ext_cmu_base &&
	    (clk_type == CLK_INT_DIFF || clk_type == CLK_INT_SING))
		/* Ref CMU is located outside the IP */
		csr_serdes = ctx->ext_cmu_base;
	else
		csr_serdes = ctx->sds_base;

	/* Release PHY main reset */
	writel(0xdf, csr_serdes + SATA_ENET_SDS_RST_CTL);
	readl(csr_serdes + SATA_ENET_SDS_RST_CTL); /* Force a barrier */

	if (cmu_type != REF_CMU) {
		cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
		/*
		 * As per PHY design spec, the PLL reset requires a minimum
		 * of 800us.
		 */
		usleep_range(800, 1000);

		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		/*
		 * As per PHY design spec, the PLL auto calibration requires
		 * a minimum of 800us.
		 */
		usleep_range(800, 1000);

		cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
			       CMU_REG32_FORCE_VCOCAL_START_MASK);
		/*
		 * As per PHY design spec, the PLL requires a minimum of
		 * 800us to settle.
		 */
		usleep_range(800, 1000);
	}

	/* Poll the PLL calibration completion status for at least 1 ms */
	loop = 100;
	do {
		cmu_rd(ctx, cmu_type, CMU_REG7, &val);
		if (CMU_REG7_PLL_CALIB_DONE_RD(val) &&
		   (CMU_REG7_VCO_CAL_FAIL_RD(val) == 0))
			break;
    		 if (CMU_REG7_VCO_CAL_FAIL_RD(val)) {
        		writel(0xde, csr_serdes + SATA_ENET_SDS_RST_CTL);
      		        writel(0xdf, csr_serdes + SATA_ENET_SDS_RST_CTL);
			/*
		 	 * As per PHY design spec, serdes reset requires
			 * minimum of 800us to settle.
		 	 */
			usleep_range(800, 1000);

        		cmu_rd(ctx, cmu_type, CMU_REG32, &val);
        		val = CMU_REG32_VCOCAL_START_SET(val, 1);
        		cmu_wr(ctx, cmu_type, CMU_REG32, val);

      			cmu_rd(ctx, cmu_type, CMU_REG32, &val);
        		val = CMU_REG32_VCOCAL_START_SET(val, 0);
        		cmu_wr(ctx, cmu_type, CMU_REG32, val);

			/*
		 	 * As per PHY design spec, VCO calib requires
			 * minimum of 800us to settle.
		 	 */
      			usleep_range(800, 1000);
     	   	}

		/*
		 * As per PHY design spec, PLL calibration status requires
		 * a minimum of 10us to be updated.
		 */
		usleep_range(10, 100);

	} while (--loop > 0);

	cmu_rd(ctx, cmu_type, CMU_REG7, &val);
	dev_dbg(ctx->dev, "PLL calibration %s\n",
		CMU_REG7_PLL_CALIB_DONE_RD(val) ? "done" : "failed");
	if (CMU_REG7_VCO_CAL_FAIL_RD(val)) {
		dev_dbg(ctx->dev,
			"PLL calibration failed due to VCO failure\n");
		return -1;
	}
	dev_dbg(ctx->dev, "PLL calibration successful\n");

  	writel(0xdf, csr_serdes + SATA_ENET_SDS_RST_CTL);

	if (xgene_is_preB0()) {
		cmu_rd(ctx, cmu_type, CMU_REG15, &val);
		dev_dbg(ctx->dev, "PHY Tx is %sready\n", val & 0x300 ? "" : "not ");
	}

	return 0;
}

static void xgene_phy_pdwn_force_vco(struct xgene_phy_ctx *ctx,
				     enum cmu_type_t cmu_type,
				     enum clk_type_t clk_type)
{
	u32 val;

	dev_dbg(ctx->dev, "Reset VCO and re-start again\n");
	if (cmu_type == PHY_CMU) {
		cmu_rd(ctx, cmu_type, CMU_REG16, &val);
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
		cmu_wr(ctx, cmu_type, CMU_REG16, val);
	}

	cmu_toggle1to0(ctx, cmu_type, CMU_REG0, CMU_REG0_PDOWN_MASK);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
}

void xgene_phy_sata_force_gen(struct xgene_phy_ctx *ctx,
			      int lane, int gen)
{
	u32 val;

	serdes_rd(ctx, lane, RXTX_REG38, &val);
	val = RXTX_REG38_CUSTOMER_PINMODE_INV_SET(val, gen == 0x7 ? 0x0 : 0x400);
	serdes_wr(ctx, lane, RXTX_REG38, val);

	/* Set boost control value */
	serdes_rd(ctx, lane, RXTX_REG1, &val);
	val = RXTX_REG1_RXACVCM_SET(val, 0x7);
	val = RXTX_REG1_CTLE_EQ_SET(val,
			            ctx->sata_param.txboostgain[lane * 3 +
			            ctx->sata_param.speed[lane]]);
	serdes_wr(ctx, lane, RXTX_REG1, val);

	serdes_rd(ctx, lane, RXTX_REG125, &val);
	val = RXTX_REG125_PQ_REG_SET(val,
			             ctx->sata_param.txeyetuning[lane * 3 +
			             ctx->sata_param.speed[lane]]);
	serdes_wr(ctx, lane, RXTX_REG125, val);

	serdes_rd(ctx, lane, RXTX_REG61, &val);
	val = RXTX_REG61_SPD_SEL_CDR_SET(val,
		ctx->sata_param.txspeed[ctx->sata_param.speed[lane]]);
 	serdes_wr(ctx, lane, RXTX_REG61, val);
}

int xgene_phy_set_ctle(struct xgene_phy_ctx *ctx, int lane, u32 disk_type)
{
	u32 val;
	u32 val_old;

	serdes_rd(ctx, lane, RXTX_REG1, &val);
	val_old = val;
	val = RXTX_REG1_RXACVCM_SET(val, 0x7);
	val = RXTX_REG1_CTLE_EQ_SET(val, (disk_type == DISK_SSD ?
				     ctx->sata_param.txboostgain_ssd[lane * 3 +  ctx->sata_param.speed[lane]]:
			             ctx->sata_param.txboostgain[lane * 3 + ctx->sata_param.speed[lane]])) ;
	if (val_old == val)
		return 0;
	serdes_wr(ctx, lane, RXTX_REG1, val);
	return 1;
}


static int xgene_phy_hw_init_sata(struct xgene_phy_ctx *ctx,
				  enum clk_type_t clk_type, int ssc_enable)
{
	void __iomem *sds_base = ctx->sds_base;
	u32 val;
	int i;

	/* Configure the PHY for operation */
	dev_dbg(ctx->dev, "Reset PHY\n");
	/* Place PHY into reset */
	writel(0x0, sds_base + SATA_ENET_SDS_RST_CTL);
	val = readl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */
	/* Release PHY lane from reset (active high) */
	writel(0x20, sds_base + SATA_ENET_SDS_RST_CTL);
	readl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */
	/* Release all PHY module out of reset except PHY main reset */
	writel(0xde, sds_base + SATA_ENET_SDS_RST_CTL);
	readl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */

	/* Set the operation speed */
	val = readl(sds_base + SATA_ENET_SDS_CTL1);
	val = CFG_I_SPD_SEL_CDR_OVR1_SET(val,
		ctx->sata_param.txspeed[ctx->sata_param.speed[0]]);
	writel(val, sds_base + SATA_ENET_SDS_CTL1);

	dev_dbg(ctx->dev, "Set the customer pin mode to SATA\n");
	val = readl(sds_base + SATA_ENET_SDS_CTL0);
	val = REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_SET(val, 0x4421);
	writel(val, sds_base + SATA_ENET_SDS_CTL0);

	/* Configure the clock macro unit (CMU) clock type */
	xgene_phy_cfg_cmu_clk_type(ctx, PHY_CMU, clk_type);

	/* Configure the clock macro */
	xgene_phy_sata_cfg_cmu_core(ctx, PHY_CMU, clk_type);

	/* Enable SSC if enabled */
	if (ssc_enable)
		xgene_phy_ssc_enable(ctx, PHY_CMU);

	/* Configure PHY lanes */
	xgene_phy_sata_cfg_lanes(ctx);

	/* Set Rx/Tx 20-bit */
	val = readl(sds_base + SATA_ENET_SDS_PCS_CTL0);
	val = REGSPEC_CFG_I_RX_WORDMODE0_SET(val, 0x3);
	val = REGSPEC_CFG_I_TX_WORDMODE0_SET(val, 0x3);
	writel(val, sds_base + SATA_ENET_SDS_PCS_CTL0);

	/* Start PLL calibration and try for three times */
	i = 100;
	do {
		if (!xgene_phy_cal_rdy_chk(ctx, PHY_CMU, clk_type))
			break;
		/* If failed, toggle the VCO power signal and start again */
		xgene_phy_pdwn_force_vco(ctx, PHY_CMU, clk_type);
		/*
		 * As per PHY design spec, minimum of 10us
		 * settle the powerdown VCO.
		 */
     		usleep_range(10, 100);
	} while (--i > 0);
	/* Even on failure, allow to continue any way */

	if (i <= 0)
		dev_err(ctx->dev, "PLL calibration failed after 100 retry \n");

	return 0;
}

static int xgene_phy_hw_init_ref_cmu(struct xgene_phy_ctx *ctx,
				     enum clk_type_t clk_type)
{
	void __iomem *sds_base;
	int loop = 10;
	u32 val;

	if (ctx->ext_cmu_base)
		sds_base = ctx->ext_cmu_base;
	else
		sds_base = ctx->sds_base;

	dev_dbg(ctx->dev, "Configure Ref CMU (internal clock)\n");
	val = readl(sds_base + SATA_ENET_CLK_MACRO_REG);
	val = I_RESET_B_SET(val, 0x0);
	if (!ctx->ext_cmu_base)
		val = I_PLL_FBDIV_SET(val, 0x27);
	val = I_CUSTOMEROV_SET(val, 0x0);
	writel(val, sds_base + SATA_ENET_CLK_MACRO_REG);

	/* Configure the clock macro */
	xgene_phy_sata_cfg_cmu_core(ctx, REF_CMU, clk_type);

	val = readl(sds_base + SATA_ENET_CLK_MACRO_REG);
	val = I_RESET_B_SET(val, 0x1);
	val = I_CUSTOMEROV_SET(val, 0x0);
	writel(val, sds_base + SATA_ENET_CLK_MACRO_REG);

	/* Start PLL calibration and try for three times */
	do {
		if (!xgene_phy_cal_rdy_chk(ctx, REF_CMU, clk_type))
			break;
		/* If failed, toggle the VCO power signal and start again */
		xgene_phy_pdwn_force_vco(ctx, REF_CMU, clk_type);
		/*
		 * As per PHY design spec, minimum of 10us
		 * settle the powerdown VCO.
		 */
     		usleep_range(10, 100);
	} while (--loop > 0);
	if (loop <= 0) {
		dev_err(ctx->dev, "Ref PLL clock macro not ready...\n");
		return -1;
	}
	val = readl(sds_base + SATA_ENET_CLK_MACRO_REG);
	dev_dbg(ctx->dev, "Ref PLL clock macro is %slocked...\n",
		O_PLL_LOCK_RD(val) ? "" : "un-");
	dev_dbg(ctx->dev, "Ref PLL clock macro is %sready...\n",
		O_PLL_READY_RD(val) ? "" : "not ");
	return 0;
}

#include "phy-xgene-pcie.c"
#include "phy-xgene-usb.c"

static int xgene_phy_hw_initialize(struct xgene_phy_ctx *ctx,
				   enum clk_type_t clk_type,
				   int ssc_enable)
{
	int rc;

	dev_dbg(ctx->dev, "PHY init clk type %d\n", clk_type);

	/* Configure internal ref clock CMU */
	if (clk_type == CLK_INT_DIFF || clk_type == CLK_INT_SING)
		if (xgene_phy_hw_init_ref_cmu(ctx, clk_type))
			return -ENODEV;

	if (ctx->mode == MODE_SATA) {
		rc = xgene_phy_hw_init_sata(ctx, clk_type, ssc_enable);
		if (rc)
			return rc;
	} else if (ctx->mode == MODE_PCIE) {
		rc = xgene_phy_hw_init_pcie(ctx, clk_type, ssc_enable);
		if (rc)
			return rc;
	} else if (ctx->mode == MODE_USB) {
		rc = xgene_phy_hw_init_usb(ctx, clk_type, ssc_enable);
		if (rc)
			return rc;
	} else {
		dev_err(ctx->dev, "Un-supported customer pin mode %d\n",
			ctx->mode);
		return -ENODEV;
	}

	return 0;
}

void xgene_phy_reset_rxd(struct xgene_phy_ctx *ctx, int lane)
{
	/* Reset digital Rx */
	serdes_clrbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
	/* As per PHY design spec, the reset requires a minimum of 100us. */
	usleep_range(100, 150);
	serdes_setbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
}

static int xgene_phy_get_avg(int accum, int samples)
{
		return (accum / samples);
}

static void xgene_phy_gen_avg_val(struct xgene_phy_ctx *ctx, int lane)
{
	int max_loop = 10;
	int avg_loop = 0;
	int lat_do = 0, lat_xo = 0, lat_eo = 0, lat_so = 0;
	int lat_de = 0, lat_xe = 0, lat_ee = 0, lat_se = 0;
	int sum_cal = 0;
	int lat_do_itr, lat_xo_itr, lat_eo_itr, lat_so_itr;
	int lat_de_itr, lat_xe_itr, lat_ee_itr, lat_se_itr;
	int sum_cal_itr = 0;
	int fail_even;
	int fail_odd;
	u32 val;
	u32 dfepreset_old;
	u32 dfe_tap;
	int loop;

	dev_dbg(ctx->dev, "Generating avg calibration value for lane %d\n",
		lane);

	/* Enable RX Hi-Z termination */
	serdes_setbits(ctx, lane, RXTX_REG12,
		       RXTX_REG12_RX_DET_TERM_ENABLE_MASK);

	/* Turn off DFE */
	serdes_rd(ctx, lane, RXTX_REG28, &dfe_tap);
	serdes_wr(ctx, lane, RXTX_REG28, 0x0000);
	/* DFE Presets to zero */
	serdes_rd(ctx, lane, RXTX_REG31, &dfepreset_old);
	serdes_wr(ctx, lane, RXTX_REG31, 0x0000);

	/*
	 * Receiver Offset Calibration:
	 * Calibrate the receiver signal path offset in two steps - summar
	 * and latch calibration.
	 * Runs the "Receiver Offset Calibration multiple times to determine
	 * the average value to use.
	 */
	 while (avg_loop < max_loop) {
		/* Start SUMMER calibration */
		serdes_setbits(ctx, lane, RXTX_REG127,
			       RXTX_REG127_FORCE_SUM_CAL_START_MASK);
		/*
	 	 * As per PHY design spec, the Summer calibration requires a minimum
	 	 * of 100us to complete.
	 	 */
		usleep_range(100, 500);
		serdes_clrbits(ctx, lane, RXTX_REG127,
				RXTX_REG127_FORCE_SUM_CAL_START_MASK);
		/*
	 	 * As per PHY design spec, the auto calibration requires a minimum
	 	 * of 100us to complete.
	 	 */
		usleep_range(100, 500);
		loop = 100;
    		do {
   	  		serdes_rd(ctx, lane, RXTX_REG158, &val);
      			if (RXTX_REG158_SUM_CALIB_DONE_RD(val) &&
		   		(RXTX_REG158_SUM_CALIB_ERR_RD(val) == 0))
			break;

			usleep_range(10, 100);
		} while (--loop > 0);

		serdes_rd(ctx, lane, RXTX_REG158, &val);
		if (RXTX_REG158_SUM_CALIB_DONE_RD(val) &&
	   		(RXTX_REG158_SUM_CALIB_ERR_RD(val) == 0))  {
			dev_dbg(ctx->dev, " rxtx_channel%d  summer calib pass \n", lane);
			serdes_rd(ctx, lane, RXTX_REG121, &val);
			sum_cal_itr = RXTX_REG121_SUMOS_CAL_CODE_RD(val);
			sum_cal += sum_cal_itr;
			++avg_loop;
		}
		xgene_phy_reset_rxd(ctx, lane);
	}

	/* Update SUMMER calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(val,
		xgene_phy_get_avg(sum_cal, max_loop));
	serdes_wr(ctx, lane, RXTX_REG14, val);

	dev_dbg(ctx->dev, "SUM 0x%x\n",
		xgene_phy_get_avg(sum_cal, max_loop));

	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(val, 0x1);
	serdes_wr(ctx, lane, RXTX_REG14, val);
	dev_dbg(ctx->dev, "Enable Manual Summer calibration\n");

	avg_loop = 0;

	while (avg_loop < max_loop) {
		/* Start latch calibration */
		serdes_setbits(ctx, lane, RXTX_REG127,
		       RXTX_REG127_FORCE_LAT_CAL_START_MASK);
		/*
		 * As per PHY design spec, the latch calibration requires a minimum
		 * of 100us to complete.
		 */
		usleep_range(100, 500);
		serdes_clrbits(ctx, lane, RXTX_REG127,
		       RXTX_REG127_FORCE_LAT_CAL_START_MASK);

	        /* check lat calib,
      		 * The lat_calib is take about 200ms to be done
      		 * after release serdes reset.
      		 * It only occured 1time
      		 */
		usleep_range(100, 500);
    		loop = 1000;
    		do {
   			serdes_rd(ctx, lane, RXTX_REG158, &val);
      	 		if (RXTX_REG158_LAT_CALIB_DONE_RD(val))
				break;
            	 	usleep_range(100, 500);

    		} while (--loop > 0);

    		serdes_rd(ctx, lane, RXTX_REG158, &val);
    		if (RXTX_REG158_LAT_CALIB_DONE_RD(val))
			dev_dbg(ctx->dev, " rxtx_channel%d  lat calib pass and time taken =%dms \n",
				 lane, (1000-loop)*2);
		else
         		dev_err(ctx->dev, " rxtx_channel%d  lat calib failed even after %d loops\n",
			 	 lane, (1000-loop));

		serdes_rd(ctx, lane, RXTX_REG21, &val);
		lat_do_itr = RXTX_REG21_DO_LATCH_CALOUT_RD(val);
		lat_xo_itr = RXTX_REG21_XO_LATCH_CALOUT_RD(val);
		fail_odd = RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(val);

		usleep_range(100, 100);

		serdes_rd(ctx, lane, RXTX_REG22, &val);
		lat_eo_itr = RXTX_REG22_EO_LATCH_CALOUT_RD(val);
		lat_so_itr = RXTX_REG22_SO_LATCH_CALOUT_RD(val);
		fail_even = RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(val);

		usleep_range(100, 100);

		serdes_rd(ctx, lane, RXTX_REG23, &val);
		lat_de_itr = RXTX_REG23_DE_LATCH_CALOUT_RD(val);
		lat_xe_itr = RXTX_REG23_XE_LATCH_CALOUT_RD(val);

		usleep_range(100, 100);

		serdes_rd(ctx, lane, RXTX_REG24, &val);
		lat_ee_itr = RXTX_REG24_EE_LATCH_CALOUT_RD(val);
		lat_se_itr = RXTX_REG24_SE_LATCH_CALOUT_RD(val);

		usleep_range(100, 100);

		/* Check for failure. If passed, sum them for averaging */
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

			dev_dbg(ctx->dev, "Iteration %d:\n", avg_loop);
			dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
				lat_do_itr, lat_xo_itr, lat_eo_itr,
				lat_so_itr);
			dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
				lat_de_itr, lat_xe_itr, lat_ee_itr,
				lat_se_itr);
			dev_dbg(ctx->dev, "SUM 0x%x\n", sum_cal_itr);
			++avg_loop;
		} else {
			dev_err(ctx->dev,
				"Receiver calibration failed at %d loop\n",
				avg_loop);
		}
		xgene_phy_reset_rxd(ctx, lane);
	}

	/* Update latch manual calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_DO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_do, max_loop));
	val = RXTX_REG127_XO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xo, max_loop));
	serdes_wr(ctx, lane, RXTX_REG127, val);

	serdes_rd(ctx, lane, RXTX_REG128, &val);
	val = RXTX_REG128_EO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_eo, max_loop));
	val = RXTX_REG128_SO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_so, max_loop));
	serdes_wr(ctx, lane, RXTX_REG128, val);

	serdes_rd(ctx, lane, RXTX_REG129, &val);
	val = RXTX_REG129_DE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_de, max_loop));
	val = RXTX_REG129_XE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xe, max_loop));
	serdes_wr(ctx, lane, RXTX_REG129, val);

	serdes_rd(ctx, lane, RXTX_REG130, &val);
	val = RXTX_REG130_EE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_ee, max_loop));
	val = RXTX_REG130_SE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_se, max_loop));
	serdes_wr(ctx, lane, RXTX_REG130, val);

	dev_dbg(ctx->dev, "Average Value:\n");
	dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
		 xgene_phy_get_avg(lat_do, max_loop),
		 xgene_phy_get_avg(lat_xo, max_loop),
		 xgene_phy_get_avg(lat_eo, max_loop),
		 xgene_phy_get_avg(lat_so, max_loop));
	dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
		 xgene_phy_get_avg(lat_de, max_loop),
		 xgene_phy_get_avg(lat_xe, max_loop),
		 xgene_phy_get_avg(lat_ee, max_loop),
		 xgene_phy_get_avg(lat_se, max_loop));
	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x1);
	dev_dbg(ctx->dev, "Enable Manual Latch calibration\n");
	serdes_wr(ctx, lane, RXTX_REG127, val);

	usleep_range(800, 1000);

	/* Disable RX Hi-Z termination */
	serdes_rd(ctx, lane, RXTX_REG12, &val);
	val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0);
	serdes_wr(ctx, lane, RXTX_REG12, val);


	/* Turn on/off DFE */
	if (ctx->mode == MODE_SATA)
		serdes_wr(ctx, lane, RXTX_REG28,
			  (ctx->sata_param.txequalizer[lane * 3 +
			  ctx->sata_param.speed[lane]]) ? 0x0007 : 0x0000);
	else if (ctx->mode == MODE_PCIE)
		serdes_wr(ctx, lane, RXTX_REG28, dfe_tap);
	else
		serdes_wr(ctx, lane, RXTX_REG28, 0x7);

	if (ctx->mode == MODE_PCIE) {
		serdes_rd(ctx, lane, RXTX_REG8, &val);
		val = RXTX_REG8_CDR_LOOP_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG8, val);
	}

	/* Restore DFE Presets */
	if (ctx->mode == MODE_SATA)
		serdes_wr(ctx, lane, RXTX_REG31,
			  ctx->sata_param.txequalizer[lane * 3 +
			  ctx->sata_param.speed[lane]] ? 0x7e00 : 0x0000);
	else
		serdes_wr(ctx, lane, RXTX_REG31, dfepreset_old);
}

int xgene_phy_rxtx_rdy(struct xgene_phy_ctx *ctx, int lane)
{
   	u32 val;
   	int loop;
        int rc;

   	/*Check sum_cal */
   	loop = 100;
    	do {
   	  	serdes_rd(ctx, lane, RXTX_REG158, &val);
      		if (RXTX_REG158_SUM_CALIB_DONE_RD(val) &&
		   (RXTX_REG158_SUM_CALIB_ERR_RD(val) == 0))
			break;

		usleep_range(10, 100);
	} while (--loop > 0);

	serdes_rd(ctx, lane, RXTX_REG158, &val);
	if (RXTX_REG158_SUM_CALIB_DONE_RD(val) &&
	   (RXTX_REG158_SUM_CALIB_ERR_RD(val) == 0)) {
		dev_dbg(ctx->dev, " rxtx_channel%d  summer calib pass \n", lane);
		rc = 0;
	} else {
		dev_err(ctx->dev, " rxtx_channel%d  summer calib fail \n", lane);
		rc = 1;
	}

     	/* check lat calib,
      	* The lat_calib is take about 200ms to be done
      	* after release serdes reset.
      	* It only occured 1time
      	*/
    	loop = 1000;
    	do {
   		serdes_rd(ctx, lane, RXTX_REG158, &val);
      	 	if (RXTX_REG158_LAT_CALIB_DONE_RD(val))
			break;

		usleep_range(2000, 2000);
    	} while (--loop > 0);

    	serdes_rd(ctx, lane, RXTX_REG158, &val);
    	if (RXTX_REG158_LAT_CALIB_DONE_RD(val)) {
		dev_dbg(ctx->dev, " rxtx_channel%d  lat calib pass and time taken =%dms \n",
			 lane, (1000-loop)*2);
		rc = 0;
	} else {
         	dev_dbg(ctx->dev, " rxtx_channel%d  lat calib failed even after %d loops\n",
			 lane, (1000-loop));
		rc = 1;
	}

    	serdes_rd(ctx, lane, RXTX_REG28, &val);
        dev_dbg(ctx->dev, " RXTX_REG28_DFE_TAP_ENA_SET =0x%x \n",RXTX_REG28_DFE_TAP_ENA_RD(val));

	return rc;
}

static void xgene_phy_pclk_reset(struct xgene_phy_ctx *ctx)
{
	void *clkcsr_base = ctx->clk_base;
	u32 val;

	val = readl(clkcsr_base + SATASRESETREG);
	val &= ~SATA_PCLK_RESET_MASK;
	writel(val, clkcsr_base + SATASRESETREG);
}

static void xgene_phy_pmclk_reset(struct xgene_phy_ctx *ctx)
{
	void *clkcsr_base = ctx->clk_base;
	u32 val;

	val = readl(clkcsr_base + SATASRESETREG);
	val &= ~(SATA_CORE_RESET_MASK |
		SATA_PMCLK_RESET_MASK |
		SATA_SDS_RESET_MASK);
	writel(val, clkcsr_base + SATASRESETREG);
}

static void xgene_phy_force_pvt_cal(struct xgene_phy_ctx *ctx)
{
	int i;
	u32 val;

	for (i = 0; i < (ctx->lane/4); i++) {
		cmu_rd(ctx, PHY_CMU+i, CMU_REG32, &val);
		val = CMU_REG32_FORCE_PVT_CAL_START_SET(val, 0x1);
		cmu_wr(ctx, PHY_CMU+i, CMU_REG32, val);

		cmu_rd(ctx, PHY_CMU+i, CMU_REG32, &val);
		val = CMU_REG32_FORCE_PVT_CAL_START_SET(val, 0x0);
		cmu_wr(ctx, PHY_CMU+i, CMU_REG32, val);
	}
}

int xgene_phy_hw_init(struct xgene_phy_ctx *ctx)
{
	int rc;
	int i;

	rc = xgene_phy_hw_initialize(ctx, ctx->clk_type, ctx->ssc);
	if (rc) {
		dev_err(ctx->dev, "PHY initialize failed %d\n", rc);
		return rc;
	}

	/* Setup clock properly after PHY configuration */
	switch (ctx->mode) {
	case MODE_SATA:
		writel(0xff, ctx->clk_base + SATACLKENREG);
		readl(ctx->clk_base + SATACLKENREG);
		xgene_phy_pmclk_reset(ctx);
		xgene_phy_pclk_reset(ctx);
		break;
	case MODE_USB:
		goto init_done;
	default:
		break;
	}

	/* Compute average value */
	for (i = 0; i < ctx->lane; i++) {
		xgene_phy_gen_avg_val(ctx, i);
		xgene_phy_rxtx_rdy(ctx, i);
	}
	if (ctx->mode == MODE_PCIE)
		xgene_phy_force_pvt_cal(ctx);

init_done:
	ctx->inited = INITIALIZED;
	dev_dbg(ctx->dev, "PHY initialized\n");
	return 0;
}

void xgene_dump_serdes(struct xgene_phy_ctx *ctx, int lane)
{
	u32 val;
	void *sds_base = ctx->sds_base;
	enum cmu_type_t cmu_type = PHY_CMU;
	
	val = readl(ctx->clk_base + SATACLKENREG);
	printf("CLKEN %x", val);
	val = readl(ctx->clk_base + SATASRESETREG);
	printf("RESET %x", val);

	val = readl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */
	printf("SATA_ENET_SDS_RST_CTL %x", val);
	val = readl(sds_base + SATA_ENET_SDS_CTL1);
	printf("SATA_ENET_SDS_CTL1 %x", val);
	val = readl(sds_base + SATA_ENET_SDS_PCS_CTL0);
	printf("SATA_ENET_SDS_PCS_CTL0 %x", val);
	val = readl(sds_base + SATA_ENET_SDS_CTL0);
	printf("SATA_ENET_SDS_CTL0 %x", val);

	cmu_rd(ctx, cmu_type, CMU_REG0, &val);
	printf("CMU_REG0 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG1, &val);
	printf("CMU_REG1 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG5, &val);
	printf("CMU_REG5 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG2, &val);
	printf("CMU_REG2 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG3, &val);
	printf("CMU_REG3 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG7, &val);
	printf("CMU_REG7 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG6, &val);
	printf("CMU_REG6 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG9, &val);
	printf("CMU_REG9 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG10, &val);
	printf("CMU_REG10 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG12, &val);
	printf("CMU_REG12 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG16, &val);
	printf("CMU_REG16 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG26, &val);
	printf("CMU_REG26 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG27, &val);
	printf("CMU_REG27 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG31, &val);
	printf("CMU_REG31 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG30, &val);
	printf("CMU_REG30 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG32, &val);
	printf("CMU_REG32 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG34, &val);
	printf("CMU_REG34 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG37, &val);
	printf("CMU_REG37 %x", val);
	cmu_rd(ctx, cmu_type, CMU_REG19, &val);
	printf("CMU_REG19 %x", val);
	val = CMU_REG19_PLL_VCOMOMSEL_RD(val); 
	printf("CMU_REG19 PLL_VCOMOMSEL %x", val);

	serdes_rd(ctx, lane, RXTX_REG0, &val);
	printf("RXTX_REG0 %x", val);
	serdes_rd(ctx, lane, RXTX_REG1, &val);
	printf("RXTX_REG1 %x", val);
	serdes_rd(ctx, lane, RXTX_REG2, &val);
	printf("RXTX_REG2 %x", val);
	serdes_rd(ctx, lane, RXTX_REG4, &val);
	printf("RXTX_REG4 %x", val);
	serdes_rd(ctx, lane, RXTX_REG5, &val);
	printf("RXTX_REG5 %x", val);
	serdes_rd(ctx, lane, RXTX_REG6, &val);
	printf("RXTX_REG6 %x", val);
	serdes_rd(ctx, lane, RXTX_REG7, &val);
	printf("RXTX_REG7 %x", val);
	serdes_rd(ctx, lane, RXTX_REG8, &val);
	printf("RXTX_REG8 %x", val);
	serdes_rd(ctx, lane, RXTX_REG11, &val);
	printf("RXTX_REG11 %x", val);
	serdes_rd(ctx, lane, RXTX_REG12, &val);
	printf("RXTX_REG12 %x", val);
	serdes_rd(ctx, lane, RXTX_REG14, &val);
	printf("RXTX_REG14 %x", val);
	serdes_rd(ctx, lane, RXTX_REG21, &val);
	printf("RXTX_REG21 %x", val);
	serdes_rd(ctx, lane, RXTX_REG22, &val);
	printf("RXTX_REG22 %x", val);
	serdes_rd(ctx, lane, RXTX_REG23, &val);
	printf("RXTX_REG23 %x", val);
	serdes_rd(ctx, lane, RXTX_REG24, &val);
	printf("RXTX_REG24 %x", val);
	serdes_rd(ctx, lane, RXTX_REG26, &val);
	printf("RXTX_REG26 %x", val);
	serdes_rd(ctx, lane, RXTX_REG28, &val);
	printf("RXTX_REG28 %x", val);
	serdes_rd(ctx, lane, RXTX_REG31, &val);
	printf("RXTX_REG31 %x", val);
	serdes_rd(ctx, lane, RXTX_REG61, &val);
	printf("RXTX_REG61 %x", val);
	serdes_rd(ctx, lane, RXTX_REG62, &val);
	printf("RXTX_REG62 %x", val);
	int i; 
	u32 reg; 
	for (i = 0; i < 9; i++) {
		reg = RXTX_REG81 + i * 2;
		serdes_rd(ctx, lane, reg, &val);
		printf("RXTX_REG81 reg %x val %x", reg, val);
	}

	for (i = 0; i < 3; i++) {
		reg = RXTX_REG96 + i * 2;
		serdes_rd(ctx, lane, reg, &val);
		printf("RXTX_REG96 reg %x val %x", reg, val);
	}

	for (i = 0; i < 3; i++) {
		reg = RXTX_REG99 + i * 2;
		serdes_rd(ctx, lane, reg, &val);
		printf("RXTX_REG99 reg %x val %x", reg, val);
	}

	serdes_rd(ctx, lane, RXTX_REG102, &val);
	printf("RXTX_REG102 %x", val);
	serdes_rd(ctx, lane, RXTX_REG114, &val);
	printf("RXTX_REG114 %x", val);
	serdes_rd(ctx, lane, RXTX_REG121, &val);
	printf("RXTX_REG121 %x", val);
	serdes_rd(ctx, lane, RXTX_REG125, &val);
	printf("RXTX_REG125 %x", val);
	serdes_rd(ctx, lane, RXTX_REG127, &val);
	printf("RXTX_REG127 %x", val);
	serdes_rd(ctx, lane, RXTX_REG128, &val);
	printf("RXTX_REG128 %x", val);
	serdes_rd(ctx, lane, RXTX_REG129, &val);
	printf("RXTX_REG129 %x", val);
	serdes_rd(ctx, lane, RXTX_REG130, &val);
	printf("RXTX_REG130 %x", val);
	serdes_rd(ctx, lane, RXTX_REG145, &val);
	printf("RXTX_REG145 %x", val);
	serdes_rd(ctx, lane, RXTX_REG147, &val);
	printf("RXTX_REG147 %x", val);
	serdes_rd(ctx, lane, RXTX_REG158, &val);
	printf("RXTX_REG158 %x", val);
	printf("SUM CALIB DONE %x\n ",RXTX_REG158_SUM_CALIB_DONE_RD(val));
	printf("SUM_CALIB_ERR_RD %x\n",RXTX_REG158_SUM_CALIB_ERR_RD(val));
	printf("LAT_CALIB_DONE %x\n", RXTX_REG158_LAT_CALIB_DONE_RD(val));
}

void es_singlephase(struct xgene_phy_ctx *ctx, int vRange, int vskip, int lane) 
{

   	int vm;
   	int fullFlag;
   	u32 es_data;
   	u32 es_data1;
   	u32 es_data2;
   	u32 est_data;
   	u32 est_data1;
   	u32 est_data2;
	u32 val;


   	// function to sweep voltage level
   	for (vm=0; vm < vRange; vm = vm + vskip) {
      
		serdes_rd(ctx, lane, RXTX_REG19, &val);
      		val = RXTX_REG19_ESCAN_VMARGIN_SET(val, vm);
  		serdes_wr(ctx, lane, RXTX_REG19, val);
      		
		// toggle resetb
		serdes_rd(ctx, lane, RXTX_REG61, &val);
     		val = RXTX_REG61_EYE_ACC_RESETB_SET(val, 0);
  		serdes_wr(ctx, lane, RXTX_REG61, val);
      
		serdes_rd(ctx, lane, RXTX_REG61, &val);
      		val = RXTX_REG61_EYE_ACC_RESETB_SET(val, 1);
  		serdes_wr(ctx, lane, RXTX_REG61, val);
      
		// poll for data full flag
      
      		do {
			serdes_rd(ctx, lane, RXTX_REG118, &val);
	     		fullFlag = RXTX_REG118_ACC_FULL_FLAG_RD(val);

     		} while (fullFlag == 0);

      		// trigger data capture
		serdes_rd(ctx, lane, RXTX_REG61, &val);
      		val = RXTX_REG61_EYE_MONITOR_CAPTURE_SET(val, 1);
  		serdes_wr(ctx, lane, RXTX_REG61, val);
      
		serdes_rd(ctx, lane, RXTX_REG61, &val);
      		val = RXTX_REG61_EYE_MONITOR_CAPTURE_SET(val, 0);
  		serdes_wr(ctx, lane, RXTX_REG61, val);

      		// read data to string
      		es_data =0;
      		est_data =0;
		serdes_rd(ctx, lane, RXTX_REG123, &es_data1);
		serdes_rd(ctx, lane, RXTX_REG124, &es_data2);
      		es_data = es_data1*65536 + es_data2;
		serdes_rd(ctx, lane, RXTX_REG161, &est_data1);
		serdes_rd(ctx, lane, RXTX_REG162, &est_data2);
      		est_data = est_data1*65536 + est_data2;
      
     		printf ("es_str: %d \n", es_data);
      		printf ("est_str: %d \n", est_data);
   	}
    
  	printf("endscan\n");  // this print to determine the place es_str + ="n" in the python
}   


void xgene_eyescan(struct xgene_phy_ctx *ctx , int lane) 
{
   	int vRange;
   	int qinit;
   	int qend;
   	int qskip;
  	int  qi;
   	int pqsign, pqval;
   	u32 val;
	
   	vRange = 64;
   	qinit = -64;
   	qend = 64;
   	qskip = 1;
	
	serdes_rd(ctx, lane, RXTX_REG145, &val);
  	val = RXTX_REG145_RXVWES_LATENA_SET(val, 1);
  	val = RXTX_REG145_RXES_ENA_SET(val, 1);
  	serdes_wr(ctx, lane, RXTX_REG145, val);

	serdes_rd(ctx, lane, RXTX_REG62, &val);
  	val = RXTX_REG62_PERIOD_H1_QLATCH_SET(val, 2);
  	val = RXTX_REG62_SWITCH_H1_QLATCH_SET(val, 1);
  	val = RXTX_REG62_H1_QLATCH_SIGN_INV_SET(val, 0);
  	serdes_wr(ctx, lane, RXTX_REG62, val);
  
	serdes_rd(ctx, lane, RXTX_REG61, &val);
  	val = RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(val, 2);
  	serdes_wr(ctx, lane, RXTX_REG61, val);
  
   	for (qi = qinit ; qi < qend; qi= qi+qskip) {
		serdes_rd(ctx, lane, RXTX_REG126, &val);

      		if (qi < 0) {
			pqsign = 1;
        		pqval = qi * -1;
      		} else {
        		pqsign = 0;
        		pqval = qi;
      		};
      		val = RXTX_REG126_SIGN_QI_REG_SET(val, pqsign);
     		val = RXTX_REG126_QI_REG_SET(val, pqval);
      		printf("qi %d sign_qi %d\n", pqval, pqsign);
      		serdes_wr(ctx, lane, RXTX_REG126, val);

      		es_singlephase(ctx, vRange, qskip, lane);
   	}
   
	serdes_rd(ctx, lane, RXTX_REG19, &val);
   	val = RXTX_REG19_ESCAN_VMARGIN_SET(val, 0);
      	serdes_wr(ctx, lane, RXTX_REG19, val);
} 

void dump_momsel(struct xgene_phy_ctx *ctx, int lane)
{
	enum cmu_type_t cmu_type = PHY_CMU;
	u32 val;

	cmu_rd(ctx, cmu_type, CMU_REG19, &val);
	printf("CMU_REG19 %x \n", val);
	val = CMU_REG19_PLL_VCOMOMSEL_RD(val); 
	printf("CMU_REG19 PLL_VCOMOMSEL %x \n", val);

}

void xgene_reprogram_vco(struct xgene_phy_ctx *ctx, int ref_clk)
{
	u32 val;
	int i;

	printf("remove manual summer and latch calibration lanes \n");

	for(i = 0; i < ctx->lane ; i++) {
		serdes_rd(ctx, i, RXTX_REG14, &val);
		val = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(val, 0x0);
		serdes_wr(ctx, i, RXTX_REG14, val);

		serdes_rd(ctx, i, RXTX_REG127, &val);
		val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x0);
		serdes_wr(ctx, i, RXTX_REG127, val);
	}	

	/* Configure the PLL for either 100MHz or 50MHz */
	cmu_rd(ctx, PHY_CMU, CMU_REG2, &val);
	if (ref_clk == 0) {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_100M)	;
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_100M);
                printf(" PLL IS RUNING WITH REFCLK = 100MHZ \n");
	} else if(ref_clk == 1) {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_50M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_50M);
                printf(" PLL IS RUNING WITH REFCLK = 50MHZ \n");
	} else {
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_25M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_25M);
                printf(" PLL IS RUNING WITH REFCLK = 25MHZ \n");
	}
	cmu_wr(ctx, PHY_CMU, CMU_REG2, val);

	/* Start PLL calibration and try for three times */
	i = 100;
	do {
		if (!xgene_phy_cal_rdy_chk(ctx, PHY_CMU, ctx->clk_type))
			break;
		/* If failed, toggle the VCO power signal and start again */
		xgene_phy_pdwn_force_vco(ctx, PHY_CMU, ctx->clk_type);
		/*
		 * As per PHY design spec, minimum of 10us
		 * settle the powerdown VCO.
		 */
     		usleep_range(10, 100);
	} while (--i > 0);
	/* Even on failure, allow to continue any way */
	if (i <= 0)
		dev_err(ctx->dev, "PLL calibration failed after 100 retry \n");
	
	for(i = 0; i < ctx->lane; i++) {
		xgene_phy_gen_avg_val(ctx, i);
		xgene_phy_rxtx_rdy(ctx, i);
	}	
}
