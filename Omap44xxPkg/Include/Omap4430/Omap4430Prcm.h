/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __OMAP4430PRCM_H__
#define __OMAP4430PRCM_H__

// CONTROL_CORE

#define CONTROL_CORE_U_BASE                          (0x4A002000)
#define CONTROL_CORE_ID_CODE                         (CONTROL_CORE_U_BASE+0x204)
#define CONTROL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL        (CONTROL_CORE_U_BASE+0x320)
#define CONTROL_CORE_LDOSRAM_MPU_VOLTAGE_CTRL        (CONTROL_CORE_U_BASE+0x324)
#define CONTROL_CORE_LDOSRAM_CORE_VOLTAGE_CTRL       (CONTROL_CORE_U_BASE+0x328)

#define CONTROL_CORE_LDOSRAM_VOLTAGE_CTRL_VAL               (0x0401040F)

#define CONTROL_PBIAS_LITE                                  (0x4a100600)
#define PBIASVMODE3V                                        (BIT21)
#define PBIASLITEPWRDNZ                                     (BIT22)
#define PBIASVMODEERR                                       (BIT23)
#define PBIASHIZ                                            (BIT25)
#define PBIASPWRDNZ                                         (BIT26)

// PRM

#define PRM_U_BASE                                          (0x4A307B00)

#define PRM_RSTCTRL                                         (PRM_U_BASE+0x0)
#define PRM_RSTST                                           (PRM_U_BASE+0x4)

#define PRM_RSTST_GLOBAL_COLD_RST_MASK                      (0x1)

#define PRM_RSTCTRL_RST_GLOBAL_COLD_SW_VAL                  (0x2)

#define PRM_VC_VAL_BYPASS                                   (PRM_U_BASE+0xA0)
#define PRM_VC_VAL_BYPASS_REGADDR_POS                       (8)
#define PRM_VC_VAL_BYPASS_DATA_POS                          (16)

#define PRM_VC_CFG_I2C_MODE                                 (PRM_U_BASE+0xA8)
#define PRM_VC_CFG_I2C_CLK                                  (PRM_U_BASE+0xAC)

#define VC_CFG_I2C_MODE_VAL                                 (0x0)
#define VC_CFG_I2C_CLK_VAL                                  (0x167FFB)

#define PMIC_SMPS_ID0_SLAVE_ADDR                            (0x12)
#define PMIC_VCORE3_CFG_FORCE_REGADDR                       (0x61)
#define PMIC_VCORE1_CFG_FORCE_REGADDR                       (0x55)
#define PMIC_VCORE2_CFG_FORCE_REGADDR                       (0x5B)
#define PMIC_VCORE3_CFG_FORCE_VSEL                          (0x28)
#define PMIC_VCORE1_CFG_FORCE_VSEL_VDD_MPU_4430             (0x32)
#define PMIC_VCORE1_CFG_FORCE_VSEL_VDD_CORE_4460            (0x28)
#define PMIC_VCORE2_CFG_FORCE_VSEL                          (0x28)

#define TPS62361_SLAVE_ADDR                                 (0x60)
#define TPS62361_SET1_REG_ADDR                              (0x01)
#define TPS62361_SET1_REG_VAL                               (0x46)

// CKGEN_CM1

#define CKGEN_CM1_U_BASE                                    (0x4A004100)

#define CKGEN_CM1_CM_DIV_M3_DPLL_CORE                       (CKGEN_CM1_U_BASE+0x34)
#define CKGEN_CM1_CM_DIV_M4_DPLL_CORE                       (CKGEN_CM1_U_BASE+0x38)
#define CKGEN_CM1_CM_DIV_M5_DPLL_CORE                       (CKGEN_CM1_U_BASE+0x3C)
#define CKGEN_CM1_CM_DIV_M6_DPLL_CORE                       (CKGEN_CM1_U_BASE+0x40)
#define CKGEN_CM1_CM_DIV_M7_DPLL_CORE                       (CKGEN_CM1_U_BASE+0x44)

#define CKGEN_CM1_CM_DIV_M2_DPLL_MPU                        (CKGEN_CM1_U_BASE+0x70)

#define CKGEN_CM1_CM_CLKMODE_DPLL_IVA                       (CKGEN_CM1_U_BASE+0xA0)
#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA                        (CKGEN_CM1_U_BASE+0xAC)
#define CKGEN_CM1_CM_DIV_M4_DPLL_IVA                        (CKGEN_CM1_U_BASE+0xB8)
#define CKGEN_CM1_CM_DIV_M5_DPLL_IVA                        (CKGEN_CM1_U_BASE+0xBC)
#define CKGEN_CM1_CM_BYPCLK_DPLL_IVA                        (CKGEN_CM1_U_BASE+0xDC)

#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA_CLKSEL_VAL             (0x19c10)
#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA_M4_VAL                 (4)
#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA_M5_VAL                 (7)
#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA_BYCLK_VAL              (1)
#define CKGEN_CM1_CM_CLKSEL_DPLL_IVA_CLKMODE_VAL            (7)

#define CKGEN_CM1_CM_CLKMODE_DPLL_ABE                       (CKGEN_CM1_U_BASE+0xE0)
#define CKGEN_CM1_CM_CLKSEL_DPLL_ABE                        (CKGEN_CM1_U_BASE+0xEC)
#define CKGEN_CM1_CM_DIV_M2_DPLL_ABE                        (CKGEN_CM1_U_BASE+0xF0)
#define CKGEN_CM1_CM_DIV_M3_DPLL_ABE                        (CKGEN_CM1_U_BASE+0xF4)

#define CKGEN_CM1_CM_CLKSEL_DPLL_ABE_VAL                    (0x82ee00)
#define CKGEN_CM1_CM_DIV_M2_DPLL_ABE_VAL                    (1)
#define CKGEN_CM1_CM_DIV_M3_DPLL_ABE_VAL                    (1)
#define CKGEN_CM1_CM_CLKMODE_DPLL_ABE_VAL                   (0xf27)

#define CKGEN_CM1_CM_SHADOW_FREQ_CONFIG1                    (CKGEN_CM1_U_BASE+0x160)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_CORE_M2_DIV_OPP100      (1<<11)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_CORE_DPLL_EN_LOCK       (7<<8)
#define CM_SHADOW_FREQ_CONFIG1_DLL_RESET_RST                (1<<3)
#define CM_SHADOW_FREQ_CONFIG1_FREQ_UPDATE_START            (1<<0)

#define CM_DIV_M2_DPLL_MPU_OPP100_VAL                       (1)
#define CM_DIV_M3_DPLL_CORE_OPP100_VAL                      (5)
#define CM_DIV_M4_DPLL_CORE_OPP100_VAL                      (8)
#define CM_DIV_M5_DPLL_CORE_OPP100_VAL                      (4)
#define CM_DIV_M6_DPLL_CORE_OPP100_VAL                      (6)
#define CM_DIV_M7_DPLL_CORE_OPP100_VAL                      (5)

// CKGEN_CM2

#define CKGEN_CM2_U_BASE                                    (0x4A008100)

#define CKGEN_CM2_CM_CLKMODE_DPLL_USB                       (CKGEN_CM2_U_BASE+0x80)
#define CKGEN_CM2_CM_CLKSEL_DPLL_USB                        (CKGEN_CM2_U_BASE+0x8C)
#define CKGEN_CM2_CM_DIV_M2_DPLL_USB                        (CKGEN_CM2_U_BASE+0x90)

#define CKGEN_CM2_CM_CLKSEL_DPLL_USB_VAL                    (0x25817)
#define CKGEN_CM2_CM_DIV_M2_DPLL_USB_VAL                    (0x282)
#define CKGEN_CM2_CM_CLKMODE_DPLL_USB_VAL                   (0x7)

// RESTORE_CM1

#define RESTORE_CM1_U_BASE                                  (0x4A004E00)

#define RESTORE_CM1_CM_DIV_M2_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x4)
#define RESTORE_CM1_CM_DIV_M3_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x8)
#define RESTORE_CM1_CM_DIV_M5_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x10)
#define RESTORE_CM1_CM_DIV_M6_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x14)
#define RESTORE_CM1_CM_DIV_M7_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x18)
#define RESTORE_CM1_CM_CLKSEL_DPLL_CORE_RESTORE             (RESTORE_CM1_U_BASE+0x1C)
#define RESTORE_CM1_CM_SHADOW_FREQ_CONFIG1_RESTORE          (RESTORE_CM1_U_BASE+0x30)

// SCRM

#define SCRM_U_BASE                                         (0x4A30A000)

#define SCRM_AUXCLK3                                        (SCRM_U_BASE+0x31C)
#define SCRM_AUXCLK3_VAL                                    (0x00010100)

#endif // __OMAP4430PRCM_H__

