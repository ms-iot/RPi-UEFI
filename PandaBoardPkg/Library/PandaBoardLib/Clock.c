/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/IoLib.h>
#include <Library/DebugLib.h>

#include <PandaBoard.h>
#include <Omap4430/Omap4430.h>

VOID
VolConSetup (
  IN  UINTN                     PmcSlaveAddr,
  IN  UINTN                     SmpsAddr,
  IN  UINTN                     Data
  )
{
  // Setup VolCon command
  MmioWrite32 (PRM_VC_VAL_BYPASS,
               ((Data<<PRM_VC_VAL_BYPASS_DATA_POS)|
               (SmpsAddr<<PRM_VC_VAL_BYPASS_REGADDR_POS)|
               (PmcSlaveAddr)) );

  // Validate command
  MmioOr32 (PRM_VC_VAL_BYPASS, BIT24);
  
  // Wait for command completion
  while( MmioRead32(PRM_VC_VAL_BYPASS) & BIT24 );
}

VOID
VolConInit (
  VOID
  )
{
  // Sram Ldo Voltage Control Override (MPU, CORE, IVA)
  MmioWrite32 (CONTROL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL,
               CONTROL_CORE_LDOSRAM_VOLTAGE_CTRL_VAL);
  MmioWrite32 (CONTROL_CORE_LDOSRAM_MPU_VOLTAGE_CTRL,
               CONTROL_CORE_LDOSRAM_VOLTAGE_CTRL_VAL);
  MmioWrite32 (CONTROL_CORE_LDOSRAM_CORE_VOLTAGE_CTRL,
               CONTROL_CORE_LDOSRAM_VOLTAGE_CTRL_VAL);

  // Voltage controller setup
  MmioWrite32 (PRM_VC_CFG_I2C_MODE, VC_CFG_I2C_MODE_VAL);
  MmioWrite32 (PRM_VC_CFG_I2C_CLK, VC_CFG_I2C_CLK_VAL);
}

VOID
ClockModuleEnable (
  IN  UINTN                     Addr,
  IN  UINTN                     Mode
  )
{
  MmioOr32 (Addr, Mode);
  while( (MmioRead32(Addr) & (BIT16|BIT17)) != 0 );
}

VOID
ClockInit (
  PANDABOARD_REVISION BoardRevision
  )
{
  // Init Voltage Controller
  VolConInit ();

  // Setup CORE, MPU, IVA voltages for OPP100 operation

  ClockModuleEnable (0x4A307838, 0x1); //cm_wkup_gpio1_clkctrl: AUTO

  if( BoardRevision == PANDABOARD_REVISION_PANDAES ) {
    //   TPS62361       => VDD_MPU
    //   TWL6030 VCORE2 => VDD_IVA
    //   TWL6030 VCORE1 => VDD_CORE

	// Setup CORE voltage
    VolConSetup(PMIC_SMPS_ID0_SLAVE_ADDR,
	            PMIC_VCORE1_CFG_FORCE_REGADDR,
                PMIC_VCORE1_CFG_FORCE_VSEL_VDD_CORE_4460);

    // Clear TPS VSEL0
    MmioAnd32 (GPIO1_BASE + GPIO_OE, ~BIT7);
    MmioOr32 (GPIO1_BASE + GPIO_CLEARDATAOUT, BIT7);

	// Setup MPU voltage
    VolConSetup(TPS62361_SLAVE_ADDR,
	            TPS62361_SET1_REG_ADDR,
                TPS62361_SET1_REG_VAL);

    // Set TPS VSEL0
    MmioOr32 (GPIO1_BASE + GPIO_SETDATAOUT, BIT7);
  }
  else {
    //   TWL6030 VCORE1 => VDD_MPU
    //   TWL6030 VCORE2 => VDD_IVA
    //   TWL6030 VCORE3 => VDD_CORE

	// Setup CORE voltage
    VolConSetup(PMIC_SMPS_ID0_SLAVE_ADDR,
	            PMIC_VCORE3_CFG_FORCE_REGADDR,
                PMIC_VCORE3_CFG_FORCE_VSEL);

	// Setup MPU voltage
    VolConSetup(PMIC_SMPS_ID0_SLAVE_ADDR,
	            PMIC_VCORE1_CFG_FORCE_REGADDR,
                PMIC_VCORE1_CFG_FORCE_VSEL_VDD_MPU_4430);
  }

  // Setup IVA voltage
  VolConSetup(PMIC_SMPS_ID0_SLAVE_ADDR,
              PMIC_VCORE2_CFG_FORCE_REGADDR,
              PMIC_VCORE2_CFG_FORCE_VSEL);
  
  // Accelerate MPU frequency
  MmioWrite32 (CKGEN_CM1_CM_DIV_M2_DPLL_MPU, CM_DIV_M2_DPLL_MPU_OPP100_VAL);

  // Accelerate CORE clocks
  MmioWrite32 (CKGEN_CM1_CM_DIV_M3_DPLL_CORE, CM_DIV_M3_DPLL_CORE_OPP100_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M4_DPLL_CORE, CM_DIV_M4_DPLL_CORE_OPP100_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M5_DPLL_CORE, CM_DIV_M5_DPLL_CORE_OPP100_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M6_DPLL_CORE, CM_DIV_M6_DPLL_CORE_OPP100_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M7_DPLL_CORE, CM_DIV_M7_DPLL_CORE_OPP100_VAL);

  // Start core frequency update
  MmioWrite32 ( CKGEN_CM1_CM_SHADOW_FREQ_CONFIG1,
               (CM_SHADOW_FREQ_CONFIG1_DPLL_CORE_M2_DIV_OPP100|
                CM_SHADOW_FREQ_CONFIG1_DPLL_CORE_DPLL_EN_LOCK|
                CM_SHADOW_FREQ_CONFIG1_DLL_RESET_RST|
                CM_SHADOW_FREQ_CONFIG1_FREQ_UPDATE_START));

  // Wait for core frequency update completion
  while( (MmioRead32(CKGEN_CM1_CM_SHADOW_FREQ_CONFIG1) & (BIT0)) != 0 );

  // Setup and lock IVA DPLL
  MmioWrite32 (CKGEN_CM1_CM_CLKSEL_DPLL_IVA,
               CKGEN_CM1_CM_CLKSEL_DPLL_IVA_CLKSEL_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M4_DPLL_IVA,
               CKGEN_CM1_CM_CLKSEL_DPLL_IVA_M4_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M5_DPLL_IVA,
               CKGEN_CM1_CM_CLKSEL_DPLL_IVA_M5_VAL);
  MmioWrite32 (CKGEN_CM1_CM_BYPCLK_DPLL_IVA,
               CKGEN_CM1_CM_CLKSEL_DPLL_IVA_BYCLK_VAL);
  MmioWrite32 (CKGEN_CM1_CM_CLKMODE_DPLL_IVA,
               CKGEN_CM1_CM_CLKSEL_DPLL_IVA_CLKMODE_VAL);

  // Setup and lock ABE DPLL
  MmioWrite32 (CKGEN_CM1_CM_CLKSEL_DPLL_ABE,
               CKGEN_CM1_CM_CLKSEL_DPLL_ABE_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M2_DPLL_ABE,
               CKGEN_CM1_CM_DIV_M2_DPLL_ABE_VAL);
  MmioWrite32 (CKGEN_CM1_CM_DIV_M3_DPLL_ABE,
               CKGEN_CM1_CM_DIV_M3_DPLL_ABE_VAL);
  MmioWrite32 (CKGEN_CM1_CM_CLKMODE_DPLL_ABE,
               CKGEN_CM1_CM_CLKMODE_DPLL_ABE_VAL);

  // Setup and lock USB DPLL
  MmioWrite32 (CKGEN_CM2_CM_CLKSEL_DPLL_USB,
               CKGEN_CM2_CM_CLKSEL_DPLL_USB_VAL);
  MmioWrite32 (CKGEN_CM2_CM_DIV_M2_DPLL_USB,
               CKGEN_CM2_CM_DIV_M2_DPLL_USB_VAL);
  MmioWrite32 (CKGEN_CM2_CM_CLKMODE_DPLL_USB,
               CKGEN_CM2_CM_CLKMODE_DPLL_USB_VAL);

  MmioOr32 (0x4A009020, 0x100); //ISS_CLKCTRL_OPTFCLKEN
  MmioOr32 (0x4A009120, 0xF00); //DSS_CLKCTRL_OPTFCLKEN

  MmioWrite32 (0x4A008900, 0x2); //cm_mpu_m3_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A008F00, 0x2); //cm_ivahd_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A004400, 0x2); //cm_dsp_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A009100, 0x2); //cm_dss_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A009200, 0x2); //cm_sgx_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A004500, 0x2); //cm1_abe_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A008C00, 0x2); //cm_c2c_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A009000, 0x2); //cm_cam_clkstctrl: SW_WKUP
  MmioWrite32 (0x4A008A00, 0x2); //cm_sdma_clkstctrl: SW_WKUP

  MmioWrite32 (0x4A008E20, 0x1); //cm_l3instr_l3_3_clkctrl: AUTO
  MmioWrite32 (0x4A008E28, 0x1); //cm_l3instr_l3_instr_clkctrl: AUTO
  MmioWrite32 (0x4A008E40, 0x1); //cm_l3instr_intrconn_wp1_clkctrl: AUTO
  MmioWrite32 (0x4A009338, 0x1); //cm_l3init_hsi_clkctrl: AUTO
  
  ClockModuleEnable (0x4A004528, 0x2); //cm1_abe_aess_clkctrl: ENABLE
  
  // TODO: pdm needs clock enabled externally to make it functional
  MmioWrite32 (0x4A004530, 0x2); //cm1_abe_pdm_clkctrl: ENABLE

  ClockModuleEnable (0x4A004538, 0x2); //cm1_abe_dmic_clkctrl: ENABLE
  ClockModuleEnable (0x4A004540, 0x2); //cm1_abe_mcasp_clkctrl: ENABLE
  ClockModuleEnable (0x4A004548, 0x2); //cm1_abe_mcbsp1_clkctrl: ENABLE
  ClockModuleEnable (0x4A004550, 0x2); //cm1_abe_mcbsp2_clkctrl: ENABLE
  ClockModuleEnable (0x4A004558, 0x2); //cm1_abe_mcbsp3_clkctrl: ENABLE
  ClockModuleEnable (0x4A004560, 0x2); //cm1_abe_slimbus_clkctrl: ENABLE
  ClockModuleEnable (0x4A004568, 0x2); //cm1_abe_timer5_clkctrl: ENABLE
  ClockModuleEnable (0x4A004570, 0x2); //cm1_abe_timer6_clkctrl: ENABLE
  ClockModuleEnable (0x4A004578, 0x2); //cm1_abe_timer7_clkctrl: ENABLE
  ClockModuleEnable (0x4A004580, 0x2); //cm1_abe_timer8_clkctrl: ENABLE
  ClockModuleEnable (0x4A004588, 0x2); //cm1_abe_wdt3_clkctrl: ENABLE
  ClockModuleEnable (0x4A009450, 0x2); //cm_l4per_gptimer9_clkctrl: ENABLE
  ClockModuleEnable (0x4A009428, 0x2); //cm_l4per_gptimer10_clkctrl: ENABLE
  ClockModuleEnable (0x4A009430, 0x2); //cm_l4per_gptimer11_clkctrl: ENABLE
  ClockModuleEnable (0x4A009440, 0x2); //cm_l4per_gptimer3_clkctrl: ENABLE
  ClockModuleEnable (0x4A009448, 0x2); //cm_l4per_gptimer4_clkctrl: ENABLE
  ClockModuleEnable (0x4A009488, 0x2); //cm_l4per_hdq1w_clkctrl: ENABLE
  ClockModuleEnable (0x4A0094E0, 0x2); //cm_l4per_mcbsp4_clkctrl: ENABLE
  ClockModuleEnable (0x4A0094F8, 0x2); //cm_l4per_mcspi2_clkctrl: ENABLE
  ClockModuleEnable (0x4A009500, 0x2); //cm_l4per_mcspi3_clkctrl: ENABLE
  ClockModuleEnable (0x4A009508, 0x2); //cm_l4per_mcspi4_clkctrl: ENABLE
  ClockModuleEnable (0x4A009520, 0x2); //cm_l4per_mmcsd3_clkctrl: ENABLE
  ClockModuleEnable (0x4A009528, 0x2); //cm_l4per_mmcsd4_clkctrl: ENABLE
  ClockModuleEnable (0x4A009560, 0x2); //cm_l4per_mmcsd5_clkctrl: ENABLE
  ClockModuleEnable (0x4A009540, 0x2); //cm_l4per_uart1_clkctrl: ENABLE
  ClockModuleEnable (0x4A009548, 0x2); //cm_l4per_uart2_clkctrl: ENABLE
  ClockModuleEnable (0x4A009558, 0x2); //cm_l4per_uart4_clkctrl: ENABLE
  ClockModuleEnable (0x4A009438, 0x2); //gptimer2: ENABLE
  ClockModuleEnable (0x4A009460, 0x1); //gpio2: AUTO
  ClockModuleEnable (0x4A009468, 0x1); //gpio3: AUTO
  ClockModuleEnable (0x4A009470, 0x101); //gpio4: AUTO+FCLK
  ClockModuleEnable (0x4A009478, 0x1); //gpio5: AUTO
  ClockModuleEnable (0x4A009480, 0x1); //gpio6: AUTO
  ClockModuleEnable (0x4A0094A8, 0x2); //i2c2: ENABLE
  ClockModuleEnable (0x4A0094B0, 0x2); //i2c3: ENABLE
  ClockModuleEnable (0x4A0094B8, 0x2); //i2c4: ENABLE
  ClockModuleEnable (0x4A0094F0, 0x2); //mcspi1: ENABLE
  ClockModuleEnable (0x4A307878, 0x2); //cm_wkup_keyboard_clkctrl: ENABLE
  ClockModuleEnable (0x4A009020, 0x2); //cm_cam_iss_clkctrl: ENABLE
  ClockModuleEnable (0x4A009028, 0x2); //cm_cam_fdif_clkctrl: ENABLE
  ClockModuleEnable (0x4A009120, 0x2); //cm_dss_dss_clkctrl: ENABLE
  ClockModuleEnable (0x4A009220, 0x2); //cm_sgx_sgx_clkctrl: ENABLE
  ClockModuleEnable (0x4A009328, 0x1040002); //mmchs1: ENABLE
  ClockModuleEnable (0x4A009330, 0x1040002); //mmchs2: ENABLE
  ClockModuleEnable (0x4A009358, 0xFF02); //cm_l3init_hsusbhost_clkctrl: ENABLE
  ClockModuleEnable (0x4A009368, 0x1); //usbtll: AUTO

  MmioWrite32 (0x4A008900, 0x3); //cm_mpu_m3_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A008F00, 0x3); //cm_ivahd_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A004400, 0x3); //cm_dsp_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A009100, 0x3); //cm_dss_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A009200, 0x3); //cm_sgx_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A004500, 0x3); //cm1_abe_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A008C00, 0x3); //cm_c2c_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A008A00, 0x3); //cm_sdma_clkstctrl: HW_AUTO
  MmioWrite32 (0x4A009400, 0x3); //l4per: HW_AUTO
  MmioWrite32 (0x4A009300, 0x3); //l3init: HW_AUTO
  MmioWrite32 (0x4A008B00, 0x3); //memif: HW_AUTO
  MmioWrite32 (0x4A008D00, 0x3); //l4cfg: HW_AUTO
  MmioWrite32 (0x4A009000, 0x0); //cm_cam_clkstctrl: NO_SLEEP
}
