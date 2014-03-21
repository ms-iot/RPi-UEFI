/** @file
*  Header defining RealView EB constants (Base addresses, sizes, flags)
*
*  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.
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
#define PMU_DISP1_CONFIGURATION_OFFSET		(0x40A0)
#define PMU_DISP1_STATUS_OFFSET				(0x40A4)

#define LOCAL_PWR_ENABLE						(0x07)

#define PMU_MIPI_PHY1_CONTROL_OFFSET			(0x0714)

// SYSTRCL Register
#define ARM_EB_SYSCTRL						0x10001000

#define PL011_CONSOLE_UART_SPEED				115200

// IRAM & RAM Base Address
#define CONFIG_PHY_SDRAM_BASE		(0x40000000)
#define CONFIG_PHY_IRAM_BASE		(0x02020000)
#define CONFIG_PHY_UEFI_BASE		(CONFIG_PHY_SDRAM_BASE)
#define CONFIG_SECURE_CONTEXT_BASE	(CONFIG_PHY_IRAM_BASE + 0x4c00)
#define CONFIG_PHY_TZSW_BASE		(CONFIG_PHY_IRAM_BASE + 0x8000)
#define CONFIG_PHY_IRAM_NS_BASE		(CONFIG_PHY_IRAM_BASE + 0x2F000)
#define CONFIG_IMAGE_INFO_BASE		(CONFIG_PHY_IRAM_NS_BASE + 0x11000)

// Exynos5250 DMC Base Address : Not used it.
#define Exynos5250_DMC_DELAY					0x3000
#define Exynos5250_DMC_0_BASE					0x10C00000
#define Exynos5250_DMC_1_BASE					0x10C10000


// Exynos5250 DMC Base Address
#define DMC_CTRL_BASE                                           0x10DD0000

#define DMC_CONCONTROL                                          0x00
#define DMC_MEMCONTROL                                          0x04
#define DMC_MEMCONFIG0                                          0x08
#define DMC_MEMCONFIG1						0x0C
#define DMC_DIRECTCMD						0x10
#define DMC_PRECHCONFIG						0x14
#define DMC_PHYCONTROL0						0x18
#define DMC_PWRDNCONFIG						0x28
#define DMC_TIMINGPZQ						0x2C
#define DMC_TIMINGAREF						0x30
#define DMC_TIMINGROW						0x34
#define DMC_TIMINGDATA						0x38
#define DMC_TIMINGPOWER						0x3C
#define DMC_PHYSTATUS						0x40
#define DMC_CHIPSTATUS_CH0					0x48
#define DMC_CHIPSTATUS_CH1					0x4C
#define DMC_MRSTATUS						0x54
#define DMC_QOSCONTROL0						0x60
#define DMC_QOSCONTROL1						0x68
#define DMC_QOSCONTROL2						0x70
#define DMC_QOSCONTROL3						0x78
#define DMC_QOSCONTROL4						0x80
#define DMC_QOSCONTROL5						0x88
#define DMC_QOSCONTROL6						0x90
#define DMC_QOSCONTROL7						0x98
#define DMC_QOSCONTROL8						0xA0
#define DMC_QOSCONTROL9						0xA8
#define DMC_QOSCONTROL10					0xB0
#define DMC_QOSCONTROL11					0xB8
#define DMC_QOSCONTROL12					0xC0
#define DMC_QOSCONTROL13					0xC8
#define DMC_QOSCONTROL14					0xD0
#define DMC_QOSCONTROL15					0xD8
#define DMC_IVCONTROL						0xF0
#define DMC_WRTRA_CONFIG					0x00F4
#define DMC_RDLVL_CONFIG					0x00F8
#define DMC_BRBRSVCONTROL					0x0100
#define DMC_BRBRSVCONFIG					0x0104
#define DMC_BRBQOSCONFIG					0x0108
#define DMC_MEMBASECONFIG0					0x010C
#define DMC_MEMBASECONFIG1					0x0110
#define DMC_WRLVL_CONFIG					0x0120
#define DMC_PMNC_PPC						0xE000
#define DMC_CNTENS_PPC						0xE010
#define DMC_CNTENC_PPC						0xE020
#define DMC_INTENS_PPC						0xE030
#define DMC_INTENC_PPC						0xE040
#define DMC_FLAG_PPC						0xE050
#define DMC_CCNT_PPC						0xE100
#define DMC_PMCNT0_PPC						0xE110
#define DMC_PMCNT1_PPC						0xE120
#define DMC_PMCNT2_PPC						0xE130
#define DMC_PMCNT3_PPC						0xE140

/* PHY Control Register */
#define PHY0_CTRL_BASE						0x10C00000
#define PHY1_CTRL_BASE						0x10C10000

#define DMC_PHY_CON0						0x00
#define DMC_PHY_CON1						0x04
#define DMC_PHY_CON2						0x08
#define DMC_PHY_CON3						0x0C
#define DMC_PHY_CON4						0x10
#define DMC_PHY_CON6						0x18
#define DMC_PHY_CON8						0x20
#define DMC_PHY_CON10						0x28
#define DMC_PHY_CON11						0x2C
#define DMC_PHY_CON12						0x30
#define DMC_PHY_CON13						0x34
#define DMC_PHY_CON14						0x38
#define DMC_PHY_CON15						0x3C
#define DMC_PHY_CON16						0x40
#define DMC_PHY_CON17						0x48
#define DMC_PHY_CON18						0x4C
#define DMC_PHY_CON19						0x50
#define DMC_PHY_CON20						0x54
#define DMC_PHY_CON21						0x58
#define DMC_PHY_CON22						0x5C
#define DMC_PHY_CON23						0x60
#define DMC_PHY_CON24						0x64
#define DMC_PHY_CON25						0x68
#define DMC_PHY_CON26						0x6C
#define DMC_PHY_CON27						0x70
#define DMC_PHY_CON28						0x74
#define DMC_PHY_CON29						0x78
#define DMC_PHY_CON30						0x7C
#define DMC_PHY_CON31						0x80
#define DMC_PHY_CON32						0x84
#define DMC_PHY_CON33						0x88
#define DMC_PHY_CON34						0x8C
#define DMC_PHY_CON35						0x90
#define DMC_PHY_CON36						0x94
#define DMC_PHY_CON37						0x98
#define DMC_PHY_CON38						0x9C
#define DMC_PHY_CON39						0xA0
#define DMC_PHY_CON40						0xA4
#define DMC_PHY_CON41						0xA8
#define DMC_PHY_CON42						0xAC






// Exynos5250 UART Register
#define Exynos5250_UART_BASE					0x12C10000

#define ULCON_OFFSET						0x00
#define UCON_OFFSET						0x04
#define UFCON_OFFSET						0x08
#define UMCON_OFFSET						0x0C
#define UTRSTAT_OFFSET						0x10
#define UERSTAT_OFFSET						0x14
#define UFSTAT_OFFSET						0x18
#define UMSTAT_OFFSET						0x1C
#define UTXH_OFFSET						0x20
#define URXH_OFFSET						0x24
#define UBRDIV_OFFSET						0x28
#define UDIVSLOT_OFFSET						0x2C
#define UINTP_OFFSET						0x30
#define UINTSP_OFFSET						0x34
#define UINTM_OFFSET						0x38


#define UARTLCR_H						ULCON_OFFSET
#define UARTECR							UFCON_OFFSET
#define UARTCR							UCON_OFFSET
#define UARTIBRD						UBRDIV_OFFSET
#define UARTFBRD						UDIVSLOT_OFFSET

#define UART_TX_EMPTY_FLAG_MASK					(0x02)
#define UART_RX_EMPTY_FLAG_MASK					(0x01)
// Exynos5250 TZPC Register
#define Exynos5250_TZPC0_BASE					0x10100000
#define Exynos5250_TZPC1_BASE					0x10110000
#define Exynos5250_TZPC2_BASE					0x10120000
#define Exynos5250_TZPC3_BASE					0x10130000
#define Exynos5250_TZPC4_BASE					0x10140000
#define Exynos5250_TZPC5_BASE					0x10150000
#define Exynos5250_TZPC6_BASE					0x10160000
#define Exynos5250_TZPC7_BASE					0x10170000
#define Exynos5250_TZPC8_BASE					0x10180000
#define Exynos5250_TZPC9_BASE					0x10190000


#define TZPC0_OFFSET						0x00000
#define TZPC1_OFFSET						0x10000
#define TZPC2_OFFSET						0x20000
#define TZPC3_OFFSET						0x30000
#define TZPC4_OFFSET						0x40000
#define TZPC5_OFFSET						0x50000
#define TZPC6_OFFSET						0x60000
#define TZPC7_OFFSET						0x70000
#define TZPC8_OFFSET						0x80000
#define TZPC9_OFFSET						0x90000

#define TZPC_DECPROT0SET_OFFSET					0x804
#define TZPC_DECPROT1SET_OFFSET					0x810
#define TZPC_DECPROT2SET_OFFSET					0x81C
#define TZPC_DECPROT3SET_OFFSET					0x828


// Exynos5250 CMU Base Address
#define Exynos5250_CMU_DELAY					0x2000
#define Exynos5250_CMU_BASE					0x10010000
#define	Exynos5250_CMU_DIV_DMC0					0x10500

#define APLL_AFC_ENB		0x1
#define APLL_AFC			0xC

/* MPLL_CON1	*/
#define MPLL_AFC_ENB	0x0
#if defined(CONFIG_CLK_800_330_165) || defined(CONFIG_CLK_1000_330_165)
#define MPLL_AFC		0xD
#elif defined(CONFIG_CLK_1000_400_200) || defined(CONFIG_CLK_1000_200_200) || defined(CONFIG_CLK_800_400_200)
#define MPLL_AFC		0x1C
#endif

#define EPLL_PDIV	0x3
#define EPLL_K		0x0
#define VPLL_PDIV	0x3
#define VPLL_SDIV	0x2

#define VPLL_SSCG_EN	0x0
#define VPLL_SEL_PF	0x0
#define VPLL_MRR	0x11
#define VPLL_MFR	0x0
#define VPLL_K		0x400
/********************************************************/

/* Set PLL	*/
#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

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
#define COREM1_RATIO	0x7
#define COREM0_RATIO	0x3
#define CORE_RATIO	0x0

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

/* CLK_SRC_TOP1	*/
#define VPLLSRC_SEL	0x0	/* 0 = FINPLL, 1 = SCLKHDMI27M	*/

/* CLK_DIV_TOP	*/
#define ONENAND_RATIO	0x0
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

// System Configuration Controller register Base addresses
#define SYS_DISP1BLK_CFG_OFFSET		(0x0214)
#define FIMDBYPASS_DISP1				(0x01 << 15)

//FIMD register offsets
#define VIDCON0_OFFSET	(0x00)
#define VIDCON1_OFFSET	(0x20004)/* Video control 1 */
#define VIDCON2_OFFSET	(0x0008)	/* Video control 2 */
#define VIDTCON0_OFFSET	(0x20010)	/* Video time control 0 */
#define VIDTCON1_OFFSET	(0x20014)	/* Video time control 1 */
#define VIDTCON2_OFFSET	(0x20018)	/* Video time control 2 */
#define SHADOWCON_OFFSET	(0x0034)	/* Window Shadow control */
#define WINCON_OFFSET(x)	(0x0020 + (x * 0x04))
#define VIDOSD_A_OFFSET(x)	(0x0040 + (x * 0x10))
#define VIDOSD_B_OFFSET(x)	(0x0044 + (x * 0x10))
#define VIDOSD_C_OFFSET(x)	(0x0048 + (x * 0x10))
#define VIDADDR_START0_OFFSET(x)(0x00A0 + (x * 0x08))
#define VIDADDR_END0_OFFSET(x)	(0x00D0 + (x * 0x08))
#define VIDADDR_SIZE_OFFSET(x)	(0x0100 + (x * 0x04))

// MIPI-DSIM register offsets
#define DSIM_STATUS			(0x00)
#define DSIM_SWRST			(0x04)
#define DSIM_CLKCTRL		(0x08)
#define DSIM_TIMEOUT		(0x0C)
#define DSIM_CONFIG			(0x10)
#define DSIM_ESCMODE		(0x14)
#define DSIM_MDRESOL		(0x18)
#define DSIM_MVPORCH		(0x1C)
#define DSIM_MHPORCH		(0x20)
#define DSIM_MSYNC			(0x24)
#define DSIM_SDRESOL		(0x28)
#define DSIM_INTSRC			(0x2C)
#define DSIM_INTMSK			(0x30)
#define DSIM_PKTHDR			(0x34)
#define DSIM_PAYLOAD		(0x38)
#define DSIM_RXFIFO			(0x3C)
#define DSIM_FIFOTHLD		(0x40)
#define DSIM_FIFOCTRL		(0x44)
#define DSIM_MEMACCHR		(0x48)
#define DSIM_PLLCTRL		(0x4C)
#define DSIM_PLLTMR			(0x50)
#define DSIM_PHYACCHR		(0x54)
#define DSIM_PHYACCHR1		(0x58)

// RTC register offset
#define EXYNOS_RTCREG(x) (x)
#define EXYNOS_INTP            EXYNOS_RTCREG(0x30)
#define EXYNOS_INTP_ALM        (1 << 1)
#define EXYNOS_INTP_TIC        (1 << 0)

#define EXYNOS_RTCCON        EXYNOS_RTCREG(0x40)
#define EXYNOS_RTCCON_RTCEN  (1<<0)
#define EXYNOS_RTCCON_CLKSEL (1<<1)
#define EXYNOS_RTCCON_CNTSEL (1<<2)
#define EXYNOS_RTCCON_CLKRST (1<<3)
#define EXYNOS_RTCCON_TICEN  (1<<8)

#define EXYNOS_RTCCON_TICMSK (0xF<<7)
#define EXYNOS_RTCCON_TICSHT (7)

#define EXYNOS_TICNT         EXYNOS_RTCREG(0x44)
#define EXYNOS_TICNT_ENABLE  (1<<7)

#define EXYNOS_RTCALM        EXYNOS_RTCREG(0x50)
#define EXYNOS_RTCALM_ALMEN  (1<<6)
#define EXYNOS_RTCALM_YEAREN (1<<5)
#define EXYNOS_RTCALM_MONEN  (1<<4)
#define EXYNOS_RTCALM_DAYEN  (1<<3)
#define EXYNOS_RTCALM_HOUREN (1<<2)
#define EXYNOS_RTCALM_MINEN  (1<<1)
#define EXYNOS_RTCALM_SECEN  (1<<0)

#define EXYNOS_RTCALM_ALL \
  EXYNOS_RTCALM_ALMEN | EXYNOS_RTCALM_YEAREN | EXYNOS_RTCALM_MONEN |\
  EXYNOS_RTCALM_DAYEN | EXYNOS_RTCALM_HOUREN | EXYNOS_RTCALM_MINEN |\
  EXYNOS_RTCALM_SECEN


#define EXYNOS_ALMSEC        EXYNOS_RTCREG(0x54)
#define EXYNOS_ALMMIN        EXYNOS_RTCREG(0x58)
#define EXYNOS_ALMHOUR       EXYNOS_RTCREG(0x5c)

#define EXYNOS_ALMDAY        EXYNOS_RTCREG(0x60)
#define EXYNOS_ALMMON        EXYNOS_RTCREG(0x64)
#define EXYNOS_ALMYEAR       EXYNOS_RTCREG(0x68)

//#define EXYNOS_RTCRST        EXYNOS_RTCREG(0x6c)

#define EXYNOS_BCDSEC        EXYNOS_RTCREG(0x70)
#define EXYNOS_BCDMIN        EXYNOS_RTCREG(0x74)
#define EXYNOS_BCDHOUR       EXYNOS_RTCREG(0x78)
#define EXYNOS_BCDDAY        EXYNOS_RTCREG(0x7c)
#define EXYNOS_BCDDAYWEEK    EXYNOS_RTCREG(0x80)
#define EXYNOS_BCDMON        EXYNOS_RTCREG(0x84)
#define EXYNOS_BCDYEAR       EXYNOS_RTCREG(0x88)

// Kimoon add RTC clock gate
#define CLK_GATE_IP_PERIR       (0xC960)
#define CLK_RTC_OFFSET          (0x1 << 15)
#define CLK_RTC_MASK            (0x0 << 15)
#define CLK_RTC_UNMASK          (0x1 << 15)

//#define CLK_DIV_FSYS2           (CLK_BASE + 0xC548)
//#define CLK_DIV_FSYS3           (CLK_BASE + 0xC54C)


/*******************************************
* Interrupt Map
*******************************************/

// Timer Interrupts
#define Exynos5250_INT_NUM(x)				((x) + 32)

#define PWM_TIMER0_INTERRUPT_NUM			Exynos5250_INT_NUM(36)
#define PWM_TIMER1_INTERRUPT_NUM			Exynos5250_INT_NUM(37)
#define PWM_TIMER2_INTERRUPT_NUM			Exynos5250_INT_NUM(38)
#define PWM_TIMER3_INTERRUPT_NUM			Exynos5250_INT_NUM(39)
#define PWM_TIMER4_INTERRUPT_NUM			Exynos5250_INT_NUM(40)

/*******************************************
* EFI Memory Map in Permanent Memory (DRAM)
*******************************************/

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

// 0x1140_0000
#define GPA0	(0x00)
#define GPA1	(0x01)
#define GPA2	(0x02)
#define GPB0	(0x03)
#define GPB1	(0x04)
#define GPB2	(0x05)
#define GPB3	(0x06)
#define GPC0	(0x07)
#define GPC1	(0x08)
#define GPC2	(0x09)
#define GPC3	(0x0A)
#define GPD0	(0x0B)
#define GPD1	(0x0C)
#define GPY0	(0x0D)
#define GPY1	(0x0E)
#define GPY2	(0x0F)
#define GPY3	(0x10)
#define GPY4	(0x11)
#define GPY5	(0x12)
#define GPY6	(0x13)
#define GPX0	(0x60)
#define GPX1	(0x61)
#define GPX2	(0x62)
#define GPX3	(0x63)

// 0x1340_0000
#define GPE0	(0x70)
#define GPE1	(0x71)
#define GPF0	(0x72)
#define GPF1	(0x73)
#define GPG0	(0x74)
#define GPG1	(0x75)
#define GPG2	(0x76)
#define GPH0	(0x77)
#define GPH1	(0x78)

// 0x10D1_0000
#define GPV0	(0x80)
#define GPV1	(0x81)
// ETC5PUD
#define GPV2	(0x83)
#define GPV3	(0x84)
// ETC8PUD
#define GPV4	(0x86)

// 0x0386_0000
#define GPZ	(0x90)

#define LCD_BACKLIGHT	GPIO(GPB2,PIN0)
#define LCD_RESET		GPIO(GPX1,PIN5)
#define LCD_POWER		GPIO(GPX3,PIN0)

/* SDHC GPIO Pin Configuration for GAIA */
#define SD_2_EVT1_CLK	GPIO(GPC3,PIN0)
#define SD_2_EVT1_CMD	GPIO(GPC3,PIN1)
#define SD_2_EVT1_CDn	GPIO(GPC3,PIN2)
#define SD_2_EVT1_DATA0	GPIO(GPC3,PIN3)
#define SD_2_EVT1_DATA1	GPIO(GPC3,PIN4)
#define SD_2_EVT1_DATA2	GPIO(GPC3,PIN5)
#define SD_2_EVT1_DATA3	GPIO(GPC3,PIN6)

#define SD_2_CLK	GPIO(GPC2,PIN0)
#define SD_2_CMD	GPIO(GPC2,PIN1)
#define SD_2_CDn	GPIO(GPC2,PIN2)
#define SD_2_DATA0	GPIO(GPC2,PIN3)
#define SD_2_DATA1	GPIO(GPC2,PIN4)
#define SD_2_DATA2	GPIO(GPC2,PIN5)
#define SD_2_DATA3	GPIO(GPC2,PIN6)
#define SD_2_DATA4      GPIO(GPC3,PIN3)
#define SD_2_DATA5      GPIO(GPC3,PIN4)
#define SD_2_DATA6      GPIO(GPC3,PIN5)
#define SD_2_DATA7      GPIO(GPC3,PIN6)

/* USB 2.0 GPIO Pin Configuration for GAIA Evt1 */
#define USB_2_EVT1 GPIO(GPX2,PIN6)

/* SDHC CH0 GPIO Pin Configuration for GAIA */
#define SD_0_CLK	GPIO(GPC0,PIN0)
#define SD_0_CMD	GPIO(GPC0,PIN1)
#define SD_0_CDn	GPIO(GPC0,PIN2)
#define SD_0_DATA0	GPIO(GPC0,PIN3)
#define SD_0_DATA1	GPIO(GPC0,PIN4)
#define SD_0_DATA2	GPIO(GPC0,PIN5)
#define SD_0_DATA3	GPIO(GPC0,PIN6)
#define SD_0_DATA4      GPIO(GPC1,PIN0)
#define SD_0_DATA5      GPIO(GPC1,PIN1)
#define SD_0_DATA6      GPIO(GPC1,PIN2)
#define SD_0_DATA7      GPIO(GPC1,PIN3)


#define CLK_DIV_FSYS1_OFFSET	0x1054C
#define CLK_DIV_FSYS2_OFFSET	0x10550

#endif
