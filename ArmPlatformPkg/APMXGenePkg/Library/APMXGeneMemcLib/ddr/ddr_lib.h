/**
 * APM X-Gene DDR3 controller code
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Feng Kan <fkan@apm.com>.
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

#ifndef _DDR_LIB_H_
#define _DDR_LIB_H_

/* Turn on all debug messages */
#if defined(DEBUG_ALL)
#define DEBUG
#endif

#ifdef APM_SIM
#include "apm_ddr_sdram.h"
extern void exec_dsb(void);
#define DSB_SY_CALL     exec_dsb()
#define DSB_SY_CALL_WDELAY   {DELAY(5);exec_dsb();}

#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#include <Library/IoLib.h>
#include <Include/APMXGeneSlimPROCSR.h>
#include <Library/I2CLib/I2CLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#define CONFIG_SYS_SCU_BASE     0x17000000
#define APM_MPA_REG_OFFSET      0x1000
#define APM_MARKERN(num)
#define APM_MARKERN_WRITE32(_ocm_addr, _data32)
#define flush_dcache_all() DSB_SY_CALL
#define DSB_SY_CALL     asm volatile("dsb sy")
#define DSB_SY_CALL_WDELAY     {DELAY(5);asm volatile("dsb sy");}
#define debug0(fmt,args...)	printf(fmt ,##args)
#define debug1(fmt,args...)	debug(fmt ,##args)
#define debug2(fmt,args...)	debug(fmt ,##args)
#define debug3(fmt,args...)	
#define pr_err(fmt,args...)	printf(fmt ,##args)
#define getenv_ulong(x, y, z)	(z)
#define printf		info
#define readl		MmioRead32
#define writel(v, a)	MmioWrite32((a), (v))
#define i2c_read	I2c_Read
#define i2c_write	I2c_Write
#define memset(p, v, s) SetMem((p), (s), (v))
#define memcpy(p, s, t) CopyMem((p), (s), (t))
#define udelay		MicroSecondDelay
#ifndef max
#define max(a,b) (a > b ? a : b)
#endif
#ifndef min
#define min(a,b) (a < b ? a : b)
#endif

#define disable_interrupts()
/*FIXME: Add reset cpu */
#define reset_cpu(x)

typedef UINT32    u32;
typedef UINT32    uint32_t;
typedef UINT64    u64;
extern void print_size (unsigned long long size, const char *s);

#define DDR_INFO
#undef DDR_DBG

#ifdef DDR_DBG
#define debug(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define debug(arg...) DEBUG ((0x10000000,## arg))
#endif

#ifdef DDR_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif

#else /* APM_SIM */
#include <common.h>
#define DSB_SY_CALL     asm volatile("dsb sy")
#define DSB_SY_CALL_WDELAY     {DELAY(5); asm volatile("dsb sy");}
#ifdef APM_VBIOS
#include <apm_ddr_sdram.h>
#else 
/* U-boot */
#include <asm/arch/apm_ddr_sdram.h>
#endif
#endif
#include "ddr_lrdimm_util.h"

#define DDR_SCU_WRITE32(_scu_offset, _data32) \
	(*(volatile unsigned int*)(SCU_BASE_ADDR+_scu_offset) = (_data32))
#define DDR_SCU_READ32(_scu_offset) \
	((unsigned int)(*(volatile unsigned int*)(SCU_BASE_ADDR+_scu_offset)))

/*
 * PHY/MCU Bugs/Workarounds
 */
/*** ZQ-CAL ***/
#define DO_INIT_SEQ_CTLUPDATE 0x1U
#define PHY_ZQCAL_CODE_VALUE 0x731 
#define PHY_ZQCAL_COUNT 0xFFF0U
#define PHY_EN_SW_CTL_UP_ZQ 1
/* #define PHY_FIX_BROKEN_ZQCAL */

/*** WR-LVL ***/
/* WRLVL-PRIME DQ [0: AND-GATE (Non Micron DIMMs), 1: OR-GATE - default] */ 
#define PHY_WRLVL_USE_OR_GATE 1	

/* 
 * RTTNOM: Custom during WR-LVL, else default: 40ohm typical 
 * FIX_RTTNOM_WRLVL_VAL is decoded as below:
 * 	0: OFF   : RTTNOM OFF during WR-LVL 
 * 	1: 60ohm : RZQ/4 during WR-LVL (better for 2DPC) 
 * 	2: 120ohm: RZQ/2 during WR-LVL 
 * 	3: 40ohm : RZQ/6 during WR-LVL (better for 2DPC)
 */
/* #define FIX_RTTNOM_WRLVL */
#if defined(FIX_RTTNOM_WRLVL)
#define FIX_RTTNOM_WRLVL_VAL	1	
#endif

#define FIX_WRLVL_BACKOFF
/* #define FIX_WRLVL_BACKOFF_NOTFULL */   
#if defined(FIX_WRLVL_BACKOFF_NOTFULL)
#define FIX_WRLVL_BACKOFF_MVALUE 0x2U	/* Multiply - for doing 2/3rd backoff */
#define FIX_WRLVL_BACKOFF_DVALUE 0x3U	/* Divide - for doing 2/3rd backoff */
#endif

/*** WR-CAL ***/
#define FIX_WRLVL_BIT8_BEFOREWRCAL
#define CHANGE_WRCAL_PAT1 0xFF00FF00
#define CHANGE_WRCAL_PAT2 0xAA5555AA

/* PEVM WR-CAL for 2DPC else SW-WR-CAL for 2DPC */
#define PEVM2DPC_MCU_OTD_DRIVE   
#ifdef PEVM2DPC_MCU_OTD_DRIVE
#undef OFF_DUMMY_BIST_FOR_2S_LVL
#endif

/*** WR-DQ-DQS ***/
#define FIX_BROKEN_WRDQ_PERMACRO
#define CMP_BROKEN_WRDQ_VALUE_LO 0x30
#define CMP_BROKEN_WRDQ_VALUE_HI 0x70
#define FIX_BROKEN_WRDQ_VALUE 0x48
#define FIX_BROKEN_WRDQ_VALUE_1866 0x58

/*** RD-GATE ***/
#define FIX_RDG_BROKEN_WINDOW
#define DUMMY_BIST_FOR_2S_LVL
#define OFF_DUMMY_BIST_FOR_2S_LVL
#define DUMMY_BIST_FOR_2S_LVL_BEFORE_DESKEW
#define DUMMY_BIST_FOR_2S_LVL_BEFORE_2NDLVL
#define CHECK_BROKEN_RDG2S 

/* #define FIX_DEFAULT_RDG_PERMACRO_2S */  /* Not for RDIMM */
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1600R_H 	0x400U  
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1600R_L 	0x300U 
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1600U 	0x400U  
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1333 	0x300U  
/* #define FIX_BROKEN_RDG_AFTER_2NDLVL */
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1066_LRDIMM 0x280U  
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1333_LRDIMM 0x300U 
#define FIX_DEFAULT_RDG_PERMACRO_VALUE_1600_LRDIMM 0x480U 

/*** RD-EYE ***/
#define DEFAULT_RDEYE_VALUE  0x20U
#define FIX_DEFAULT_RDE
#define FIX_DEFAULT_RDE_BFRDSK
/* #define FIX_DEFAULT_RDE_BEF2ND */

#define CMP_BROKEN_RDEYE_VALUE_LO 0x18U
#define CMP_BROKEN_RDEYE_VALUE_HI 0x60U
#define FIX_BROKEN_RDEYE_PERMACRO
/* These values might change based on DIMM/SPEED/LOAD/RD-DESKEW */
#define FIX_BROKEN_RDEYE_VALUE_2S 0x30U 
#define FIX_BROKEN_RDEYE_VALUE_1S 0x40U	
/* #define FIX_BROKEN_RDE_AFTER_2NDLVL */

/* Set to move DQS from the right edge of DQ eye */
#define FIX_RDLVL_BACKOFF

#define EN_RDDESKEW 0
#define EN_RDLVL2ND 0
#define EN_WRDESKEW 1
#define DESKEW_RANK_NO 0

/*** WR-DESKEW ***/
#define CLEAR_WRDESKEW_TRIM

/*** RD-DESKEW ***/
/* #define CLEAR_RDDESKEW_TRIM */

#ifdef APM_SIM
#define SKIP_SPD_INIT      0x1
#define SKIP_TIMING_CONFIG 0x1
#else
#define SKIP_SPD_INIT      0
#define SKIP_TIMING_CONFIG 0
#endif

#define DIMM_ADDR_MIRROR_CTRL 0xAAU
/* Single rank 1 UDIMM (DIMM-staticODT=40ohm, DIMM-dynamicODT=OFF) */
#define DIMM_MR1_RTTNOM_U1R_DIC		0x46U	
#define DIMM_MR2_RTTWR_U1R		0x0U	            
/* Dual rank 1 UDIMM (DIMM-staticODT=40ohm, DynamicODT=OFF) */
#define DIMM_MR1_RTTNOM_U2R_DIC		DIMM_MR1_RTTNOM_U1R_DIC	
#define DIMM_MR2_RTTWR_U2R1S		0x0U              
/* Quad Rank 1 RDIMM (DIMM-staticODT Even Rank =20ohm, DIMM-dynamicODT=ON) */
#define DIMM_MR1_RTTNOM_R4R_DIC		0x202U
#define DIMM_MR2_RTTWR_R4R		0x2U	                 

/* Dual rank 2 UDIMMs  (DIMM-dynamicODT=120ohm) */
#define DIMM_MR2_RTTWR_U2R2S		0x2U       
/* 2S - FarEndSlot (DIMM-staticODT Even Rank =40ohm) */
#define DIMM_MR1_RTTNOM_U2R2S0_DIC	0x46U  
/* 2S - CloserSlot (DIMM-staticODT Even Rank =40ohm) */
#define DIMM_MR1_RTTNOM_U2R2S1_DIC	0x46U 
/*  Backwards compatibility.. using original */
#define DIMM_MR1_RTTNOM_DIC		DIMM_MR1_RTTNOM_U1R_DIC	
#define DIMM_MR2_RTTWR			DIMM_MR2_RTTWR_U1R
#define DIMM_RANK_MASK  0x1U
#define DIMM_DESKEW_RANK_MASK 0x0U

#define LRDIMM_LOW_SPEED 0      /* 800 and 1066 */
#define LRDIMM_HIGH_SPEED 1     /* 1333 and 1600 */
#define LRDIMM_DQS_DELAY_BASE 1800
#define LRDIMM_CMDCK_DELAY_BASE 2200
/* only change from Inphi recommended value is Burst Type Sequential */
#define LRDIMM_MR0_MBCONFIG     0x1000          
/* Note: CL, CWL, WR are not set here as they depend on frequency */
#define LRDIMM_MR1_MBCONFIG     0x0006 
#define LRDIMM_MR2_MBCONFIG     0x0440
#define LRDIMM_MR3_MBCONFIG     0x0000

/* only change from Inphi recommended value is Burst Type Sequential */
#define LRDIMM_MR0_MCKCONFIG    0x1420          
/* Note: CL, CWL, WR are set here because MCK fixed to 800Mbps */
#define LRDIMM_MR1_MCKCONFIG    0x0006
#define LRDIMM_MR2_MCKCONFIG    0x0440
#define LRDIMM_MR3_MCKCONFIG    0x0000

#define MCU_PHY_EARLY_RDGATELVL_ENAB 0

#define PHY_PEVM_RETRAIN_EN 0x0U
#define PHY_PEVM_RETRAIN_WRLVL_EN 0x1U
#define PHY_PEVM_RETRAIN_GTLVL_EN 0x0U
#define PHY_PEVM_RETRAIN_RDLVL_EN 0x1U
#define PHY_PEVM_RETRAIN_DIS_DYNODT 0x1U

#define PHY_DIS_UP_54_58_5C               0x1U
#define PHY_INIT_VAL_CMD_ADDR_DELAY_54_58 0x80U
#define PHY_INIT_VAL_CTL_DELAY_5C         0x80U

/* 0: 1T mode, 1: 2T mode */
#define MCU_ENABLE_2T_MODE                	0x0U 
/* PHY Mimic 2T: Failed Expriment - Never set this bit. */
#define PHY_EN_POSTTR_2T_ADJ_CMD_ADDR     	0x0U  
/* PHY Mimic 2T: Expriment with PHY cmd / ad timing push-pull */
#define PHY_POSTTR_ADJ_VAL_2T_CMD_ADDR_DELAY 	0x80U 

#define KCPHY_ADD_T_CRL_MARGIN         0x1
#define KCPHY_SUB_T_CWL_MARGIN         0x0
#define KCPHY_FIXED_READEN_DELAY       0x7
#define KCPHY_USE_READ_W_FIXED_DELAY   0x1

#define KCPHY_DISABLE_PULLUP           0x0U
#define KCPHY_PEVM_WRLVL_SMPL_PER_DLY  0x6U
#define KCPHY_PEVM_WRLVL_MIN_SMPLS     0x20U
#define KCPHY_PEVM_GTLVL_SMPL_PER_DLY  0x7U
#define KCPHY_PEVM_GTLVL_MIN_SMPLS     0xA0U
#define KCPHY_PEVM_RDLVL_SMPL_PER_DLY  0xDU

#define KCPHY_SHORT_GT_PREAMBLE_EN 0x1U
/* RDG pull back */
#define KCPHY_SHORT_GT_PREAMBLE_VAL 0x80U 

#define KCPHY_CFG_MACRO_x8_MASK    0x15555U
#define KCPHY_CFG_MACRO_x4_MASK    0x3FFFFU
#define KCPHY_CFG_MACRO_ENABLE_VAL 0x3FFFFU
#define KCPHY_CFG_MACRO_NOECC_MASK 0x0FFFFU
#define KCPHY_PRBS_DM_STATUS_MASK  0x000U

#define KCPHY_BIT_DQ_STREN    0x6U
#define KCPHY_BIT_AD_STREN    0x4U
#define KCPHY_BIT_CMD_STREN   0x4U
#define KCPHY_BIT_CTL_STREN   0x4U
#define KCPHY_BIT_CLK_STREN   0x6U
#define KCPHY_BIT_ODT_STREN   0x4U

#define KCPHY_BIT_DQ_SLEW     0x3U
#define KCPHY_BIT_AD_SLEW     0x3U
#define KCPHY_BIT_CMD_SLEW    0x3U
#define KCPHY_BIT_CTL_SLEW    0x3U
#define KCPHY_BIT_CLK_SLEW    0x2U

/* Arch timer delays */
#if defined(APM_SIM)
extern void arch_timer_udelay(unsigned int usec);
#define DELAY(x)    arch_timer_udelay(x)
#define DELAYP(x)   arch_timer_udelay(x)
#elif defined(APM_VBIOS)
#define DELAY(x)    USDELAY(x)
#define DELAYP(x)   MSDELAY(x)
#else
#define DELAY(x)    udelay(x)
#define DELAYP(x)   udelay(x*1000)
#endif

unsigned int csw_read_reg(void *, unsigned int);
void csw_write_reg(void *, unsigned int, unsigned int);
unsigned int mcu_read_reg(void *p, unsigned int reg);
void mcu_write_reg(void *p, unsigned int reg, unsigned int value);
unsigned int mcu_regmod(void *p, unsigned int reg, unsigned int value,
			unsigned int bh, unsigned int bl);
unsigned int mcb_read_reg(void *p, unsigned int reg);
void mcb_write_reg(void *p, unsigned int reg, unsigned int value);
unsigned int phy_read_reg(void *p, unsigned int reg);
void phy_write_reg(void *p, unsigned int reg, unsigned int value);

int mcu_pre_init(void *);
int mcu_post_init(void *);

/* Generic paramters populate_mc_default_parms() - calls functions for Speed */
int populate_mc_default_parms(void *ptr);

/* ddr_fixed_configs.c */
int mcu_csr_config(void *ptr);
int mcu_post_train_setup(void *ptr);

/* ddr_mcu.c */
int mcu_reset_status_poll(void *p, unsigned int status, unsigned int mask,
			  unsigned int flag);
int mcu_init_done_poll(void *p);
int mr_prog_done_poll(void *p);
void mcu_reset_FSM_poll(void *p, unsigned int status, unsigned int flag);
int mcu_pre_assert_mc_pwr(void *ptr);
int mcu_assert_mc_pwr_ok(void *);
int mcu_post_assert_mc_pwr(void *ptr);
int mcu_post_assert_mc_pwr_tc(void *ptr);
int dimm_mcu_fsm_init(void *ptr);
int phy_sw_adj_ctrlupdate(void *ptr);
int mcu_en_traffic_mem_init_done(void *ptr);
int mcu_error_status(void *ptr);   
int memc_ecc_init_en(void *ptr);
int mcu_phy_ctl_update_loop(void *ptr);
void mcu_phy_rdfifo_reset(void *ptr);
int mcu_dummy_bist_2s_calib(void *ptr, unsigned int rank0, unsigned int turnon);
void mcu_set_SWISS_TRNLOAD(void *p);
void mcu_set_SWISS_ODTADDR(void *ptr, int unsigned enab, int unsigned bnk, 
		int unsigned addr, int unsigned odtRd, int unsigned odtWr);
void mcu_set_SWISS_TRNCTL(void *ptr, int unsigned enab, int unsigned wrlvl_en, 
			int unsigned rdlvl_gate_en, int unsigned rdlvl_en, 
			int unsigned wrlvl_cs_n, int unsigned rdlvl_cs_n);
void mcu_set_SWISS_OPCTL(void *ptr, int unsigned sendOp, int unsigned rddata_en, 
					int unsigned cmd_n, int unsigned cs_n);
unsigned int mr_addmirror_add(unsigned int in);
unsigned int mr_addmirror_bnk(unsigned int in);
void mcu_rank_mr_update(void *ptr, unsigned int rank, unsigned int mr, 
						unsigned int value);

/* ddr_phy.c */
void phy_restore_train_dly_csrs(void *p, int unsigned rankmask,
		int unsigned setWr, int unsigned setGt, int unsigned setRd);
void phy_save_train_dly_csrs(void *p);
void phy_display_post_train_csrs(void *p, unsigned int rankmask);
void init_phy_tr_dly_vals(void *p);
int mcu_kc_phy_setup_tc(void *ptr);
int calib_pevm_custom_steps(void *ptr);
int phy_correct_rdeye_delays(void *ptr, unsigned int rank);
int phy_redo_check_rdeye(void *ptr, unsigned int rank, unsigned int redo);
void phy_clear_wrdsk_trim(void *p);
void phy_clear_rddsk_trim(void *p);
int kc_phy_wrcal_deskew(void *ptr, int unsigned rank, int unsigned checktrainerr);
int kc_phy_wrcal(void *ptr, int unsigned rank, int unsigned checktrainerr);
int kc_phy_deskew(void *ptr);
int kc_phy_2ndlvl(void *ptr);
int sw_phy_retrain(void *ptr);

/* ddr_util.c */
int memsys_unreset(void *p);
void CSWCR_setup(void *p, unsigned int mask);
void mcb_mode_setup(void *p, unsigned int mode, unsigned int spec_read);
int mcb_mcu_init_clock_deassert_reset(void *p);
int phy_poll_reg(void *p, unsigned int reg, unsigned int value,
		  					unsigned int mask);
int memc_addr_cfg(void *ptr);
int mcu_rank_addr_cfg(void *p, unsigned int mcb_intrlv, unsigned int mcu_intrlv,
						      unsigned int full_addr);

/* ddr_config.c */
int ddr_spd_init(void *);
int mcu_timing_config(void *);
unsigned int getRttNomfromMR1(unsigned int mr1val);
unsigned int putRttNomintoMR1(unsigned int mr1val, unsigned int rttnom);
unsigned int minAllowedRankHash(unsigned int hash_size, unsigned int rank_size,
		unsigned int rank_config, unsigned int rank_base_low);

int memc_dummy_fn(void *);
int is_storm_revA(void);
#endif /* _DDR_LIB_H_ */

