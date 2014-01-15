/** @file
*  Header defining RealView EB constants (Base addresses, sizes, flags)
*
*  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#ifndef __ARMPLATFORM_H__
#define __ARMPLATFORM_H__

/*******************************************
// Platform Memory Map
*******************************************/

/*******************************************
// Motherboard peripherals
*******************************************/
//PMU DOMAIN offsets
#define SWRESET_OFFSET						(0x400)
#define PMU_LCD0_CONF_OFFSET					(0x3C80)
#define PMU_LCD0_STAT_OFFSET					(0x3C84)
#define ARM_EB_BOARD_PERIPH_BASE				0x10000000


#define LCD0_PWR_NRML_MODE					(0x07)

// SYSTRCL Register
#define ARM_EB_SYSCTRL						0x10001000
#define ARM_EB_SYS_FLAGS_REG					0x10020814
#define ARM_EB_SYS_FLAGS_SET_REG				0x10020814
#define ARM_EB_SYS_FLAGS_CLR_REG				0x10020814

#define PL011_CONSOLE_UART_SPEED				115200


// Exynos4210 DMC Base Address
#define Exynos4210_DMC_DELAY					0x3000
#define Exynos4210_DMC_0_BASE					0x10400000
#define Exynos4210_DMC_1_BASE					0x10410000

#define DMC_CONCONTROL						0x00
#define DMC_MEMCONTROL						0x04
#define DMC_MEMCONFIG0						0x08
#define DMC_MEMCONFIG1						0x0C
#define DMC_DIRECTCMD						0x10
#define DMC_PRECHCONFIG						0x14
#define DMC_PHYCONTROL0						0x18
#define DMC_PHYCONTROL1						0x1C
#define DMC_PHYCONTROL2						0x20
#define DMC_PWRDNCONFIG						0x28
#define DMC_TIMINGAREF						0x30
#define DMC_TIMINGROW						0x34
#define DMC_TIMINGDATA						0x38
#define DMC_TIMINGPOWER						0x3C
#define DMC_PHYSTATUS						0x40
#define DMC_PHYZQCONTROL					0x44
#define DMC_CHIP0STATUS						0x48
#define DMC_CHIP1STATUS						0x4C
#define DMC_AREFSTATUS						0x50
#define DMC_MRSTATUS						0x54
#define DMC_PHYTEST0						0x58
#define DMC_PHYTEST1						0x5C
#define DMC_QOSCONTROL0						0x60
#define DMC_QOSCONFIG0						0x64
#define DMC_QOSCONTROL1						0x68
#define DMC_QOSCONFIG1						0x6C
#define DMC_QOSCONTROL2						0x70
#define DMC_QOSCONFIG2						0x74
#define DMC_QOSCONTROL3						0x78
#define DMC_QOSCONFIG3						0x7C
#define DMC_QOSCONTROL4						0x80
#define DMC_QOSCONFIG4						0x84
#define DMC_QOSCONTROL5						0x88
#define DMC_QOSCONFIG5						0x8C
#define DMC_QOSCONTROL6						0x90
#define DMC_QOSCONFIG6						0x94
#define DMC_QOSCONTROL7						0x98
#define DMC_QOSCONFIG7						0x9C
#define DMC_QOSCONTROL8						0xA0
#define DMC_QOSCONFIG8						0xA4
#define DMC_QOSCONTROL9						0xA8
#define DMC_QOSCONFIG9						0xAC
#define DMC_QOSCONTROL10					0xB0
#define DMC_QOSCONFIG10						0xB4
#define DMC_QOSCONTROL11					0xB8
#define DMC_QOSCONFIG11						0xBC
#define DMC_QOSCONTROL12					0xC0
#define DMC_QOSCONFIG12						0xC4
#define DMC_QOSCONTROL13					0xC8
#define DMC_QOSCONFIG13						0xCC
#define DMC_QOSCONTROL14					0xD0
#define DMC_QOSCONFIG14						0xD4
#define DMC_QOSCONTROL15					0xD8
#define DMC_QOSCONFIG15						0xDC

// Exynos4210 UART Register
#define Exynos4210_UART_BASE			0x13810000

#define ULCON_OFFSET							0x00
#define UCON_OFFSET								0x04
#define UFCON_OFFSET							0x08
#define UMCON_OFFSET							0x0C
#define UTRSTAT_OFFSET						0x10
#define UERSTAT_OFFSET						0x14
#define UFSTAT_OFFSET							0x18
#define UMSTAT_OFFSET							0x1C
#define UTXH_OFFSET								0x20
#define URXH_OFFSET								0x24
#define UBRDIV_OFFSET							0x28
#define UDIVSLOT_OFFSET						0x2C
#define UINTP_OFFSET							0x30
#define UINTSP_OFFSET							0x34
#define UINTM_OFFSET							0x38


#define UARTLCR_H                      ULCON_OFFSET
#define UARTECR                        UFCON_OFFSET
#define UARTCR                         UCON_OFFSET
#define UARTIBRD                       UBRDIV_OFFSET
#define UARTFBRD                       UDIVSLOT_OFFSET

#define UART_TX_EMPTY_FLAG_MASK		(0x02)
#define UART_RX_EMPTY_FLAG_MASK		(0x01)
// Exynos4210 TZPC Register
#define Exynos4210_TZPC0_BASE			0x10110000
#define Exynos4210_TZPC1_BASE			0x10120000
#define Exynos4210_TZPC2_BASE			0x10130000
#define Exynos4210_TZPC3_BASE			0x10140000
#define Exynos4210_TZPC4_BASE			0x10150000
#define Exynos4210_TZPC5_BASE			0x10160000


#define TZPC0_OFFSET			0x10000
#define TZPC1_OFFSET			0x20000
#define TZPC2_OFFSET			0x30000
#define TZPC3_OFFSET			0x40000
#define TZPC4_OFFSET			0x50000
#define TZPC5_OFFSET			0x60000

#define TZPC_DECPROT0SET_OFFSET		0x804
#define TZPC_DECPROT1SET_OFFSET		0x810
#define TZPC_DECPROT2SET_OFFSET		0x81C
#define TZPC_DECPROT3SET_OFFSET		0x828


// Exynos4210 CMU Base Address
#define Exynos4210_CMU_DELAY				0x2000
#define Exynos4210_CMU_BASE				0x10030000
#define	Exynos4210_CMU_DIV_DMC0				0x10500

#define CONFIG_CLK_1000_400_200

#if defined(CONFIG_CLK_800_330_165)
#define APLL_MDIV	0xC8
#define APLL_PDIV	0x6
#define APLL_SDIV	0x1

#define MPLL_MDIV	0x6E
#define MPLL_PDIV	0x4
#define MPLL_SDIV	0x1
#elif defined(CONFIG_CLK_800_400_200)
#define APLL_MDIV	0xC8
#define APLL_PDIV	0x6
#define APLL_SDIV	0x1

#define MPLL_MDIV	0xC8
#define MPLL_PDIV	0x6
#define MPLL_SDIV	0x1
#elif defined(CONFIG_CLK_1000_330_165)
#define APLL_MDIV	0xFA
#define APLL_PDIV	0x6
#define APLL_SDIV	0x1

#define MPLL_MDIV	0x6E
#define MPLL_PDIV	0x4
#define MPLL_SDIV	0x1
#elif defined(CONFIG_CLK_1000_400_200) || defined(CONFIG_CLK_1000_200_200)
#define APLL_MDIV	0xFA
#define APLL_PDIV	0x6
#define APLL_SDIV	0x1

#define MPLL_MDIV	0xC8
#define MPLL_PDIV	0x6
#define MPLL_SDIV	0x1
#endif

#define APLL_AFC_ENB		0x1
#define APLL_AFC			0xC
#define APLL_CON1_VAL	((APLL_AFC_ENB << 31) | (APLL_AFC))

/* MPLL_CON1	*/
#define MPLL_AFC_ENB	0x0
#if defined(CONFIG_CLK_800_330_165) || defined(CONFIG_CLK_1000_330_165)
#define MPLL_AFC		0xD
#elif defined(CONFIG_CLK_1000_400_200) || defined(CONFIG_CLK_1000_200_200) || defined(CONFIG_CLK_800_400_200)
#define MPLL_AFC		0x1C
#endif
#define MPLL_CON1_VAL ((MPLL_AFC_ENB << 31) | (MPLL_AFC))

#define EPLL_MDIV	0x30
#define EPLL_PDIV	0x3
#define EPLL_SDIV	0x2
#define EPLL_K		0x0
#define EPLL_CON1_VAL	(EPLL_K)

#define VPLL_MDIV	0x35
#define VPLL_PDIV	0x3
#define VPLL_SDIV	0x2

#define VPLL_SSCG_EN	0x0
#define VPLL_SEL_PF	0x0
#define VPLL_MRR	0x11
#define VPLL_MFR	0x0
#define VPLL_K		0x400
#define VPLL_CON1_VAL	((VPLL_SSCG_EN <<31) \
						| (VPLL_SEL_PF <<29) \
						| (VPLL_MRR <<24)	\
						| (VPLL_MFR << 16)	\
						| (VPLL_K))
/********************************************************/

/* Set PLL	*/
#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

#define APLL_CON0_VAL	set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_CON0_VAL	set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)
#define EPLL_CON0_VAL	set_pll(EPLL_MDIV,EPLL_PDIV,EPLL_SDIV)
#define VPLL_CON0_VAL	set_pll(VPLL_MDIV,VPLL_PDIV,VPLL_SDIV)

/* CLK_SRC_CPU	*/
/* 0 = MOUTAPLL,  1 = SCLKMPLL	*/
#define MUX_HPM_SEL_MOUTAPLL	0
#define MUX_HPM_SEL_SCLKMPLL	1
#define MUX_CORE_SEL_MOUTAPLL	0
#define MUX_CORE_SEL_SCLKMPLL	1

/* 0 = FILPLL, 1 = MOUT */
#define MUX_MPLL_SEL_FILPLL	0
#define MUX_MPLL_SEL_MOUTMPLLFOUT	1

#define MUX_APLL_SEL_FILPLL	0
#define MUX_APLL_SEL_MOUTMPLLFOUT	1

#define CLK_SRC_CPU_VAL_FINPLL	        ((MUX_HPM_SEL_MOUTAPLL << 20)    \
                                | (MUX_CORE_SEL_MOUTAPLL <<16)   \
                                | (MUX_MPLL_SEL_FILPLL << 8)   \
                                | (MUX_APLL_SEL_FILPLL <<0))

#define CLK_SRC_CPU_VAL_MOUTMPLLFOUT		((MUX_HPM_SEL_MOUTAPLL << 20)    \
                                | (MUX_CORE_SEL_MOUTAPLL <<16)   \
                                | (MUX_MPLL_SEL_MOUTMPLLFOUT << 8)   \
                                | (MUX_APLL_SEL_MOUTMPLLFOUT <<0))

/* CLK_DIV_CPU0	*/
#define APLL_RATIO	0x1
#define PCLK_DBG_RATIO	0x1
#define ATB_RATIO	0x3
#define PERIPH_RATIO	0x3
#define COREM1_RATIO	0x7
#define COREM0_RATIO	0x3
#define CORE_RATIO	0x0
#define CLK_DIV_CPU0_VAL        ((APLL_RATIO << 24)     \
                                | (PCLK_DBG_RATIO << 20)\
                                | (ATB_RATIO << 16)     \
                                | (PERIPH_RATIO <<12)   \
				| (COREM1_RATIO << 8)   \
                                | (COREM0_RATIO << 4)   \
                                | (CORE_RATIO))

/* CLK_DIV_CPU1	*/
#define HPM_RATIO	0x0
#define COPY_RATIO	0x3
#define CLK_DIV_CPU1_VAL	((HPM_RATIO << 4) | (COPY_RATIO))

/* CLK_SRC_DMC	*/
#define MUX_PWI_SEL	        0x0
#define MUX_CORE_TIMERS_SEL	0x0
#define MUX_DPHY_SEL		0x0
#define MUX_DMC_BUS_SEL		0x0
#define CLK_SRC_DMC_VAL         ((MUX_PWI_SEL << 16)            \
                                | (MUX_CORE_TIMERS_SEL << 12)   \
                                | (MUX_DPHY_SEL << 8)           \
                                | (MUX_DMC_BUS_SEL << 4))

/* CLK_DIV_DMC0	*/
#if defined(CONFIG_CLK_1000_200_200)
#define CORE_TIMERS_RATIO	0x1
#define COPY2_RATIO		0x3
#define DMCP_RATIO		0x1
#define DMCD_RATIO		0x0
#define DMC_RATIO		0x3
#define DPHY_RATIO		0x1
#define ACP_PCLK_RATIO		0x1
#define ACP_RATIO		0x3
#else
#define CORE_TIMERS_RATIO	0x1
#define COPY2_RATIO		0x3
#define DMCP_RATIO		0x1
#define DMCD_RATIO		0x1
#define DMC_RATIO		0x1
#define DPHY_RATIO		0x1
#define ACP_PCLK_RATIO		0x1
#define ACP_RATIO		0x3
#endif
#define CLK_DIV_DMC0_VAL	((CORE_TIMERS_RATIO << 28) \
							| (COPY2_RATIO << 24) \
							| (DMCP_RATIO << 20)	\
							| (DMCD_RATIO << 16)	\
							| (DMC_RATIO << 12)	\
							| (DPHY_RATIO << 8)	\
							| (ACP_PCLK_RATIO << 4)	\
							| (ACP_RATIO))

/* CLK_DIV_DMC1	*/
#define DPM_RATIO	0x1
#define DVSEM_RATIO	0x1
#define PWI_RATIO	0x1
#define CLK_DIV_DMC1_VAL	((DPM_RATIO << 24) \
						| (DVSEM_RATIO << 16) \
						| (PWI_RATIO << 8))

/* CLK_SRC_TOP0	*/
#define MUX_ONENAND_SEL 0x0 /* 0 = DOUT133, 1 = DOUT166		*/
#define MUX_ACLK_133_SEL	0x0	/* 0 = SCLKMPLL, 1 = SCLKAPLL	*/
#define MUX_ACLK_160_SEL	0x0
#define MUX_ACLK_100_SEL	0x0
#define MUX_ACLK_200_SEL	0x0
#define MUX_VPLL_SEL	0x0
#define MUX_EPLL_SEL	0x0
#define CLK_SRC_TOP0_VAL	((MUX_ONENAND_SEL << 28)	\
							| (MUX_ACLK_133_SEL << 24)	\
							| (MUX_ACLK_160_SEL << 20)	\
							| (MUX_ACLK_100_SEL << 16)	\
							| (MUX_ACLK_200_SEL << 12)	\
							| (MUX_VPLL_SEL << 8)	\
							| (MUX_EPLL_SEL << 4))

/* CLK_SRC_TOP1	*/
#define VPLLSRC_SEL	0x0	/* 0 = FINPLL, 1 = SCLKHDMI27M	*/
#define CLK_SRC_TOP1_VAL	(VPLLSRC_SEL)

/* CLK_DIV_TOP	*/
#define ONENAND_RATIO	0x0
#define ACLK_133_RATIO	0x5
#define ACLK_160_RATIO	0x4
#define ACLK_100_RATIO	0x7
#define ACLK_200_RATIO	0x3
#define CLK_DIV_TOP_VAL	((ONENAND_RATIO << 16) \
							| (ACLK_133_RATIO << 12)	\
							| (ACLK_160_RATIO << 8)	\
							| (ACLK_100_RATIO << 4)	\
							| (ACLK_200_RATIO))

/* CLK_SRC_LEFTBUS	*/
#define MUX_GDL_SEL	0x0
#define CLK_SRC_LEFTBUS_VAL	(MUX_GDL_SEL)

/* CLK_DIV_LEFRBUS	*/
#define GPL_RATIO	0x1
#define GDL_RATIO	0x3
#define CLK_DIV_LEFRBUS_VAL	((GPL_RATIO << 4) \
								| (GDL_RATIO))

/* CLK_SRC_RIGHTBUS	*/
#define MUX_GDR_SEL	0x0
#define CLK_SRC_RIGHTBUS_VAL	(MUX_GDR_SEL)

/* CLK_DIV_RIGHTBUS	*/
#define GPR_RATIO	0x1
#define GDR_RATIO	0x3
#define CLK_DIV_RIGHTBUS_VAL	((GPR_RATIO << 4) \
								| (GDR_RATIO))

#define PLL_LOCKTIME	0x1C20
/* APLL_LOCK		*/
#define APLL_LOCK_VAL	(PLL_LOCKTIME)
/* MPLL_LOCK	*/
#define MPLL_LOCK_VAL	(PLL_LOCKTIME)
/* EPLL_LOCK		*/
#define EPLL_LOCK_VAL	(PLL_LOCKTIME)
/* VPLL_LOCK		*/
#define VPLL_LOCK_VAL	(PLL_LOCKTIME)

/* CLK_SRC_PERIL0	*/
#define PWM_SEL		0
#define UART5_SEL	6
#define UART4_SEL	6
#define UART3_SEL	6
#define UART2_SEL	6
#define UART1_SEL	6
#define UART0_SEL	6
#define CLK_SRC_PERIL0_VAL	((PWM_SEL << 24)\
								| (UART5_SEL << 20)  \
								| (UART4_SEL << 16) \
								| (UART3_SEL << 12) \
								| (UART2_SEL<< 8)	\
								| (UART1_SEL << 4)	\
								| (UART0_SEL))

/* CLK_DIV_PERIL0	*/
#if defined(CONFIG_CLK_800_330_165) || defined(CONFIG_CLK_1000_330_165)
#define UART5_RATIO	7
#define UART4_RATIO	7
#define UART3_RATIO	7
#define UART2_RATIO	7
#define UART1_RATIO	7
#define UART0_RATIO	7
#elif defined(CONFIG_CLK_1000_400_200) || defined(CONFIG_CLK_1000_200_200) || defined(CONFIG_CLK_800_400_200)
#define UART5_RATIO	8
#define UART4_RATIO	8
#define UART3_RATIO	8
#define UART2_RATIO	8
#define UART1_RATIO	8
#define UART0_RATIO	8
#endif
#define CLK_DIV_PERIL0_VAL	((UART5_RATIO << 20) \
								| (UART4_RATIO << 16) \
								| (UART3_RATIO << 12)	\
								| (UART2_RATIO << 8)	\
								| (UART1_RATIO << 4)	\
								| (UART0_RATIO))

#define MPLL_DEC (MPLL_MDIV * MPLL_MDIV / (MPLL_PDIV * 2^(MPLL_SDIV-1)))

#define SCLK_UART               MPLL_DEC/ (UART1_RATIO+1)
#if defined(CONFIG_CLK_800_330_165) || defined(CONFIG_CLK_1000_330_165)
#define UART_UBRDIV_VAL	0x2B/* (SCLK_UART/(115200*16) -1) */
#define UART_UDIVSLOT_VAL	0xC		/*((((SCLK_UART*10/(115200*16) -10))%10)*16/10)*/
#elif defined(CONFIG_CLK_1000_400_200) || defined(CONFIG_CLK_1000_200_200) || defined(CONFIG_CLK_800_400_200)
#define UART_UBRDIV_VAL	0x2F     /* (SCLK_UART/(115200*16) -1) */
#define UART_UDIVSLOT_VAL 0x3		/*((((SCLK_UART*10/(115200*16) -10))%10)*16/10)*/
#endif

#define UART_115200_IDIV       UART_UBRDIV_VAL
#define UART_115200_FDIV       UART_UDIVSLOT_VAL

#define UART_38400_IDIV       UART_UBRDIV_VAL
#define UART_38400_FDIV       UART_UDIVSLOT_VAL

#define UART_19200_IDIV       UART_UBRDIV_VAL
#define UART_19200_FDIV       UART_UDIVSLOT_VAL

#define UART_LCON_VAL          0x03
#define UART_ECR_VAL           0x111
#define UART_CR_VAL            0x3C5

// Exynos4210 CMU Register definition
#define CLK_SRC_LEFTBUS_OFFSET		0x04200
#define CLK_DIV_LEFTBUS_OFFSET		0x04500

#define CLK_SRC_RIGHTBUS_OFFSET		0x08200
#define CLK_DIV_RIGHTBUS_OFFSET		0x08500

#define EPLL_LOCK_OFFSET		0x0C010
#define VPLL_LOCK_OFFSET		0x0C020
#define EPLL_CON0_OFFSET		0x0C110
#define EPLL_CON1_OFFSET		0x0C114
#define VPLL_CON0_OFFSET		0x0C120
#define VPLL_CON1_OFFSET		0x0C124

#define CLK_SRC_TOP0_OFFSET		0x0C210
#define CLK_SRC_TOP1_OFFSET		0x0C214
#define CLK_SRC_PERIL0_OFFSET		0x0C250

#define CLK_SRC_FSYS_OFFSET		(0x0C240)
#define CLK_DIV_FSYS1_OFFSET		(0x0C544)
#define CLK_DIV_FSYS2_OFFSET		(0x0C548)
#define CLK_DIV_FSYS3_OFFSET		(0x0C54C)

#define CLK_DIV_PERIL0_OFFSET		0x0C550
#define CLK_DIV_TOP_OFFSET		0x0C510

#define CLK_SRC_DMC_OFFSET		0x10200
#define CLK_DIV_DMC0_OFFSET		0x10500
#define CLK_DIV_DMC1_OFFSET		0x10504

#define APLL_LOCK_OFFSET		0x14000
#define MPLL_LOCK_OFFSET		0x14008
#define APLL_CON0_OFFSET		0x14100
#define APLL_CON1_OFFSET		0x14104
#define MPLL_CON0_OFFSET		0x14108
#define MPLL_CON1_OFFSET		0x1410C

#define CLK_SRC_CPU_OFFSET		0x14200
#define CLK_DIV_CPU0_OFFSET		0x14500
#define CLK_DIV_CPU1_OFFSET		0x14504

#define CLKGATE_IP_LCD0_OFFSET		(0xC934)
#define CLKSRC_LCD0_OFFSET		(0xC234)
#define CLKDIV_LCD0_OFFSET		(0xC534)
#define CLKSRC_MASK_LCD0_OFFSET		(0xC334)

#define FIMD0_SCLKMPLL			(0x06)
#define FIMD0_CLK_DIV			(0x05)

#define CLK_PPMULCD0_MASK		(0x01 << 0x05)
#define CLKGATE_FIMD0_MASK		(0x01 << 0x00)
#define CLKSRC_FIMD0_MASK		(0x0F << 0x00)
#define CLKDIV_FIMD0_MASK		(0x0F << 0x00)

#define CLKSRC_FIMD0_SEL(x)		((x) << 0x00)
#define CLKDIV_FIMD0_SEL(x)		((x) << 0x00)
#define FIMD0_UNMASK			(0x01 << 0x00)

#define CLK_DIV_FSYS2		(CLK_BASE + 0xC548)
#define CLK_DIV_FSYS3		(CLK_BASE + 0xC54C)

// Exynos4210 MIU Base Address
#define Exynos4210_MIU_BASE					0x10600000

#define MIU_INTLV_CONFIG					0x400
#define MIU_INTLV_START_ADDR				0x808
#define MIU_MAPPING_UPDATE					0x800
#define MIU_INTLV_END_ADDR					0x810

#define MIU_SINGLE_MAPPING0_START_ADDR		0x818
#define MIU_SINGLE_MAPPING0_END_ADDR		0x820
#define MIU_SINGLE_MAPPING1_START_ADDR		0x828
#define MIU_SINGLE_MAPPING1_END_ADDR		0x830

// Dynamic Memory C#define PWM_TIMER_Tontroller Base
#define ARM_EB_DMC_BASE                     0x10018000

// Static Memory Controller Base
#define ARM_EB_SMC_CTRL_BASE                    0x10080000

// System Configuration Controller register Base addresses
#define SYS_DISPLAY_CONTROL_OFFSET	(0x0210)
#define FIMDBYPASS_LBLK0		(0x01 << 0x01)

//FIMD register offsets
#define VIDCON0_OFFSET	(0x00)
#define VIDCON1_OFFSET	(0x0004)	/* Video control 1 */
#define VIDCON2_OFFSET	(0x0008)	/* Video control 2 */
#define VIDTCON0_OFFSET	(0x0010)	/* Video time control 0 */
#define VIDTCON1_OFFSET	(0x0014)	/* Video time control 1 */
#define VIDTCON2_OFFSET	(0x0018)	/* Video time control 2 */
#define WINSHMAP_OFFSET	(0x0034)	/* Window Shadow control */
#define WINCON_OFFSET(x)	(0x0020 + (x * 0x04))
#define VIDOSD_A_OFFSET(x)	(0x0040 + (x * 0x10))
#define VIDOSD_B_OFFSET(x)	(0x0044 + (x * 0x10))
#define VIDOSD_C_OFFSET(x)	(0x0048 + (x * 0x10))
#define VIDADDR_START0_OFFSET(x)(0x00A0 + (x * 0x08))
#define VIDADDR_END0_OFFSET(x)	(0x00D0 + (x * 0x08))
#define VIDADDR_SIZE_OFFSET(x)	(0x0100 + (x * 0x04))
/*******************************************
// Interrupt Map
*******************************************/

// Timer Interrupts
#define TIMER01_INTERRUPT_NUM               34
#define TIMER23_INTERRUPT_NUM				35

#define Exynos4210_INT_NUM(x)				((x) + 32)

#define PWM_TIMER0_INTERRUPT_NUM			Exynos4210_INT_NUM(37)
#define PWM_TIMER1_INTERRUPT_NUM			Exynos4210_INT_NUM(38)
#define PWM_TIMER2_INTERRUPT_NUM			Exynos4210_INT_NUM(39)
#define PWM_TIMER3_INTERRUPT_NUM			Exynos4210_INT_NUM(40)
#define PWM_TIMER4_INTERRUPT_NUM			Exynos4210_INT_NUM(41)

/*******************************************
// EFI Memory Map in Permanent Memory (DRAM)
*******************************************/

// This region is allocated at the bottom of the DRAM. It will be used
// for fixed address allocations such as Vector Table
#define ARM_EB_EFI_FIX_ADDRESS_REGION_SZ        SIZE_8MB

// This region is the memory declared to PEI as permanent memory for PEI
// and DXE. EFI stacks and heaps will be declared in this region.
#define ARM_EB_EFI_MEMORY_REGION_SZ             0x1000000

//gpio definitions as required by the Embedded gpio module
#define DISTANCE_BTWN_PORTS	(0x20)

#define GPIO_CON		(0x00)
#define GPIO_DATAIN		(0x04)
#define GPIO_PUD		(0x08)
#define GPIO_DRV		(0x0C)

#define GPIO_DATAIN_MASK(x)     (1UL << (x))
#define GPIO_PUD_MASK(x)        (3UL << (x*2))
#define GPIO_DRV_MASK(x)        (3UL << (x*2))
#define GPIO_SFN_MASK(x)	(15UL <<(x*4))

#define GPIO_SFN_EN(x)		(2UL << (x*4))
#define GPIO_OP_EN(x)		(1UL << (x*4))

#define GPIO_PUD_DIS(x)		(0UL << (x*2))
#define GPIO_PDN_EN(x)		(1UL << (x*2))
#define GPIO_PUP_EN(x)		(3UL << (x*2))
#define GPIO_DATA_HIGH(x)	(1UL << (x))
#define GPIO_DATA_LOW(x)	(0UL << (x))

#define GPIO_DRV_SET(strength,pin)	(strength << (pin*2))

#define PIN0	(0x00)
#define PIN1	(0x01)
#define PIN2	(0x02)
#define PIN3	(0x03)
#define PIN4	(0x04)
#define PIN5	(0x05)
#define PIN6	(0x06)
#define PIN7	(0x07)

#define GPA0	(0x00)
#define GPA1	(0x01)
#define GPB	(0x02)
#define GPC0	(0x03)
#define GPC1	(0x04)
#define GPD0	(0x05)
#define GPD1	(0x06)
#define GPE0	(0x07)
#define GPE1	(0x08)
#define GPE2	(0x09)
#define GPE3	(0x0A)
#define GPE4	(0x0B)
#define GPF0	(0x0C)
#define GPF1	(0x0D)
#define GPF2	(0x0E)
#define GPF3	(0x0F)
#define GPJ0	(0x10)
#define GPJ1	(0x11)
#define GPK0	(0x12)
#define GPK1	(0x13)
#define GPK2	(0x14)
#define GPK3	(0x15)
#define GPL0	(0x16)
#define GPL1	(0x17)
#define GPL2	(0x18)
#define GPX0	(0x19)
#define GPX1	(0x1A)
#define GPX2	(0x1B)
#define GPX3	(0x1C)
#define GPY	(0x1D)
#define GPZ	(0x1E)

/* LCD GPIO Pin Configurations*/
#define LCD_HSYNC	GPIO(GPF0,PIN0)
#define LCD_VSYNC	GPIO(GPF0,PIN1)
#define LCD_VDEN	GPIO(GPF0,PIN2)
#define LCD_VCLK	GPIO(GPF0,PIN3)
#define LCD_VD_0	GPIO(GPF0,PIN4)
#define LCD_VD_1	GPIO(GPF0,PIN5)
#define LCD_VD_2	GPIO(GPF0,PIN6)
#define LCD_VD_3	GPIO(GPF0,PIN7)

#define LCD_VD_4	GPIO(GPF1,PIN0)
#define LCD_VD_5	GPIO(GPF1,PIN1)
#define LCD_VD_6	GPIO(GPF1,PIN2)
#define LCD_VD_7	GPIO(GPF1,PIN3)
#define LCD_VD_8	GPIO(GPF1,PIN4)
#define LCD_VD_9	GPIO(GPF1,PIN5)
#define LCD_VD_10	GPIO(GPF1,PIN6)
#define LCD_VD_11	GPIO(GPF1,PIN7)

#define LCD_VD_12	GPIO(GPF2,PIN0)
#define LCD_VD_13	GPIO(GPF2,PIN1)
#define LCD_VD_14	GPIO(GPF2,PIN2)
#define LCD_VD_15	GPIO(GPF2,PIN3)
#define LCD_VD_16	GPIO(GPF2,PIN4)
#define LCD_VD_17	GPIO(GPF2,PIN5)
#define LCD_VD_18	GPIO(GPF2,PIN6)
#define LCD_VD_19	GPIO(GPF2,PIN7)

#define LCD_VD_20	GPIO(GPF3,PIN0)
#define LCD_VD_21	GPIO(GPF3,PIN1)
#define LCD_VD_22	GPIO(GPF3,PIN2)
#define LCD_VD_23	GPIO(GPF3,PIN3)
#define VSYNC_LDI	GPIO(GPF3,PIN4)
#define SYS_OE		GPIO(GPF3,PIN5)

#define LCD_BACKLIGHT	GPIO(GPD0,PIN1)

/* SDHC GPIO Pin Configuration*/
#define SD_2_CLK	GPIO(GPK2,PIN0)
#define SD_2_CMD	GPIO(GPK2,PIN1)
#define SD_2_CDn	GPIO(GPK2,PIN2)
#define SD_2_DATA0	GPIO(GPK2,PIN3)
#define SD_2_DATA1	GPIO(GPK2,PIN4)
#define SD_2_DATA2	GPIO(GPK2,PIN5)
#define SD_2_DATA3	GPIO(GPK2,PIN6)

#endif
