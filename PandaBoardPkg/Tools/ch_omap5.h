/*
   2  * ch_omap5.h
   3  *
   4  * Copyright(c) 2010 Texas Instruments.   All rights reserved.
   5  *
   6  * Texas Instruments, <www.ti.com>
   7  * Bastien Allibert <b-allibert@ti.com>
   8  * Olivier Deprez <o-deprez@ti.com>
   9  *
  10  * Redistribution and use in source and binary forms, with or without
  11  * modification, are permitted provided that the following conditions
  12  * are met:
  13  *
  14  *  * Redistributions of source code must retain the above copyright
  15  *    notice, this list of conditions and the following disclaimer.
  16  *  * Redistributions in binary form must reproduce the above copyright
  17  *    notice, this list of conditions and the following disclaimer in
  18  *    the documentation and/or other materials provided with the
  19  *    distribution.
  20  *  * Neither the name Texas Instruments nor the names of its
  21  *    contributors may be used to endorse or promote products derived
  22  *    from this software without specific prior written permission.
  23  *
  24  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  25  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  26  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  27  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  28  * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  29  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  30  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  31  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  32  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  33  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  34  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  35  */

#ifndef _CH_OMAP5_H
#define _CH_OMAP5_H

/* Define here all the data fields for each item */
CH_Field OMAP5_CHSETTINGS_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C1},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	{0x0008,0x04,"Flags","ClockSettings",0},
	//HAL_CKGEN_General_t
	{0x000C,0x04,"CM_CLKSEL_CORE","ClockSettings",0},
	{0x0010,0x04,"CM_BYPCLK_MPU","ClockSettings",0},
	{0x0014,0x04,"CM_BYPCLK_IVA","ClockSettings",0},
	{0x0018,0x04,"CM_MPU_CLK_CTRL","ClockSettings",0},
	{0x001C,0x04,"CM_CLKSEL_USB","ClockSettings",0},
	//HAL_CKGEN_DpllCommon_t MPU
	{0x0020,0x04,"CM_CLKMODE_DPLL_MPU","ClockSettings",0},
	{0x0024,0x04,"CM_AUTOIDLE_DPLL_MPU","ClockSettings",0},
	{0x0028,0x04,"CM_CLKSEL_DPLL_MPU","ClockSettings",0},
	{0x002C,0x04,"CM_DIV_M2_DPLL_MPU","ClockSettings",0},
	//HAL_CKGEN_DpllCommon_t CORE
	{0x0030,0x04,"CM_CLKMODE_DPLL_CORE","ClockSettings",0},
	{0x0034,0x04,"CM_AUTOIDLE_DPLL_CORE","ClockSettings",0},
	{0x0038,0x04,"CM_CLKSEL_DPLL_CORE","ClockSettings",0},
	{0x003C,0x04,"CM_DIV_M2_DPLL_CORE","ClockSettings",0},
	{0x0040,0x04,"CM_DIV_M3_DPLL_CORE","ClockSettings",0},
	{0x0044,0x04,"CM_DIV_H11_DPLL_CORE","ClockSettings",0},
	{0x0048,0x04,"CM_DIV_H12_DPLL_CORE","ClockSettings",0},
	{0x004C,0x04,"CM_DIV_H13_DPLL_CORE","ClockSettings",0},
	{0x0050,0x04,"CM_DIV_H14_DPLL_CORE","ClockSettings",0},
	{0x0054,0x04,"CM_DIV_H22_DPLL_CORE","ClockSettings",0},
	{0x0058,0x04,"CM_DIV_H23_DPLL_CORE","ClockSettings",0},
	//HAL_CKGEN_DpllCommon_t PER5
	{0x005C,0x04,"CM_CLKMODE_DPLL_PER","ClockSettings",0},
	{0x0060,0x04,"CM_AUTOIDLE_DPLL_PER","ClockSettings",0},
	{0x0064,0x04,"CM_CLKSEL_DPLL_PER","ClockSettings",0},
	{0x0068,0x04,"CM_DIV_M2_DPLL_PER","ClockSettings",0},
	{0x006C,0x04,"CM_DIV_M3_DPLL_PER","ClockSettings",0},
	{0x0070,0x04,"CM_DIV_H11_DPLL_PER","ClockSettings",0},
	{0x0074,0x04,"CM_DIV_H12_DPLL_PER","ClockSettings",0},
	{0x0078,0x04,"CM_DIV_H14_DPLL_PER","ClockSettings",0},
	//HAL_CKGEN_DpllCommon_t USB1
	{0x007C,0x04,"CM_CLKMODE_DPLL_USB","ClockSettings",0},
	{0x0080,0x04,"CM_AUTOIDLE_DPLL_USB","ClockSettings",0},
	{0x0084,0x04,"CM_CLKSEL_DPLL_USB","ClockSettings",0},
	{0x0088,0x04,"CM_DIV_M2_DPLL_USB","ClockSettings",0}
};
CH_Field OMAP5_CHRAM_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C2},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	{0x0008,0x04,"SdramConfig","SDRAM Configuration Register",0},
	{0x000C,0x04,"SdramConfig2","SDRAM Configuration Register",0},
	{0x0010,0x04,"SdramRefresh","SDRAM Refresh Control Register",0},
	{0x0014,0x04,"SdramRefreshShdw","SDRAM Refresh Control Shadow Register",0},
	{0x0018,0x04,"SdramTim1","SDRAM Timing 1 Register",0},
	{0x001C,0x04,"SdramTim2","SDRAM Timing 2 Register",0},
	{0x0020,0x04,"SdramTim3","SDRAM Timing 3 Register",0},
	{0x0024,0x04,"SdramTim1Shdw","SDRAM Timing 1 Shadow Register",0},
	{0x0028,0x04,"SdramTim2Shdw","SDRAM Timing 2 Shadow Register",0},
	{0x002C,0x04,"SdramTim3Shdw","SDRAM Timing 3 Shadow Register",0},
	{0x0030,0x04,"PwrMgtCtrl","Power mgt control Register",0},
	{0x0034,0x04,"PwrMgtCtrlShdw","Power mgt control Shadow Register",0},
	{0x0038,0x04,"DdrPhyCtrl1","DDR PHY Control 1 Register",0},
	{0x003C,0x04,"DdrPhyCtrl2","DDR PHY Control 2 Register",0},
	{0x0040,0x04,"DdrPhyCtrl1Shdw","DDR PHY Control 1 Register",0},
	{0x0044,0x04,"ExtPhyCtrl1","",0},
	{0x0048,0x04,"ExtPhyCtrl2","",0},
	{0x004C,0x04,"ExtPhyCtrl3","",0},
	{0x0050,0x04,"ExtPhyCtrl4","",0},
	{0x0054,0x04,"ExtPhyCtrl5","",0},
	{0x0058,0x04,"ExtPhyCtrl6","",0},
	{0x005C,0x04,"ExtPhyCtrl7","",0},
	{0x0060,0x04,"ExtPhyCtrl8","",0},
	{0x0064,0x04,"ExtPhyCtrl9","",0},
	{0x0068,0x04,"ExtPhyCtrl10","",0},
	{0x006C,0x04,"ExtPhyCtrl11","",0},
	{0x0070,0x04,"ExtPhyCtrl12","",0},
	{0x0074,0x04,"ExtPhyCtrl13","",0},
	{0x0078,0x04,"ExtPhyCtrl14","",0},
	{0x007C,0x04,"ExtPhyCtrl15","",0},
	{0x0080,0x04,"ExtPhyCtrl16","",0},
	{0x0084,0x04,"ExtPhyCtrl17","",0},
	{0x0088,0x04,"ExtPhyCtrl18","",0},
	{0x008C,0x04,"ExtPhyCtrl19","",0},
	{0x0090,0x04,"ExtPhyCtrl20","",0},
	{0x0094,0x04,"ExtPhyCtrl21","",0},
	{0x0098,0x04,"ExtPhyCtrl22","",0},
	{0x009C,0x04,"ExtPhyCtrl23","",0},
	{0x00A0,0x04,"ExtPhyCtrl24","",0},
	{0x00A4,0x04,"ExtPhyCtrl25","",0},
	{0x00A8,0x04,"ExtPhyCtrl26","",0},
	{0x00AC,0x04,"ExtPhyCtrl27","",0},
	{0x00B0,0x04,"ExtPhyCtrl28","",0},
	{0x00B4,0x04,"ExtPhyCtrl29","",0},
	{0x00B8,0x04,"ExtPhyCtrl30","",0},
	{0x00BC,0x04,"ModeReg","",0},
	{0x00C0,0x04,"CoreFreqConfigM2Div","",0},
	{0x00C4,0x04,"DMMLisaMap0","DMM LISA section 0 mapping",0},
	{0x00C8,0x04,"Flags","Configure the chip selects",0}
};

CH_Field OMAP5_CHFLASH_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C3},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	{0x0008,0x02,"GPMC_SYSCONFIG_LSB","",0},
	{0x000A,0x02,"GPMC_IRQENABLE_LSB","",0},
	{0x000C,0x02,"GPMC_TIMEOUT_CONTROL_LSB","",0},
	{0x000E,0x02,"GPMC_CONFIG_LSB","",0},
	{0x0010,0x04,"GPMC_CONFIG1","",0},
	{0x0014,0x04,"GPMC_CONFIG2","",0},
	{0x0018,0x04,"GPMC_CONFIG3","",0},
	{0x001C,0x04,"GPMC_CONFIG4","",0},
	{0x0020,0x04,"GPMC_CONFIG5","",0},
	{0x0024,0x04,"GPMC_CONFIG6","",0},
	{0x0028,0x04,"GPMC_CONFIG7","",0},
	{0x002C,0x04,"GPMC_PREFETCH_CONFIG1","",0},
	{0x0030,0x02,"GPMC_PREFETCH_CONFIG2_LSB","",0},
	{0x0032,0x02,"GPMC_PREFETCH_CONTROL_LSB","",0},
	{0x0034,0x02,"GPMC_ECC_CONFIG","",0},
	{0x0036,0x02,"GPMC_ECC_CONTROL","",0},
	{0x0038,0x04,"GPMC_ECC_SIZE_CONFIG_LSB","",0},
	{0x003C,0x04,"Enable_A1_A10","Enable A1-A10 pads",0}
};
CH_Field OMAP5_CHMMCSD_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C4},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	{0x0008,0x04,"CLOCK","",0},
	{0x000C,0x04,"BusWidth","",0}
};
CH_Field OMAP5_CHSATA_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C5},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	{0x0008,0x04,"MultiSectorReadEn","",0}
};

/* Now define here the TOC entry for each item */
CH_Item_t OMAP5_CHSETTINGS_Item = {	{0x0,0x8C,{0,0,0},"CHSETTINGS"},
										OMAP5_CHSETTINGS_Fields,
										sizeof(OMAP5_CHSETTINGS_Fields)/sizeof(CH_Field) };

CH_Item_t OMAP5_CHRAM_Item = {	{0x0,0xCC,{0,0,0},"CHRAM"},
									OMAP5_CHRAM_Fields,
									sizeof(OMAP5_CHRAM_Fields)/sizeof(CH_Field) };
	
CH_Item_t OMAP5_CHFLASH_Item = {	{0x0,0x40,{0,0,0},"CHFLASH"},
									OMAP5_CHFLASH_Fields,
									sizeof(OMAP5_CHFLASH_Fields)/sizeof(CH_Field) };
	
CH_Item_t OMAP5_CHMMCSD_Item = {	{0x0,0x10,{0,0,0},"CHMMCSD"},
									OMAP5_CHMMCSD_Fields,
									sizeof(OMAP5_CHMMCSD_Fields)/sizeof(CH_Field) };

CH_Item_t OMAP5_CHSATA_Item = {	{0x0,0x0C,{0,0,0},"CHSATA"},
									OMAP5_CHSATA_Fields,
									sizeof(OMAP5_CHSATA_Fields)/sizeof(CH_Field) };

/* Make sure to list here each defined item */
CH_Item_t* OMAP5_ItemsList[] = {	&OMAP5_CHSETTINGS_Item,
									&OMAP5_CHRAM_Item,
									&OMAP5_CHFLASH_Item,
									&OMAP5_CHMMCSD_Item,
									&OMAP5_CHSATA_Item };

/* Define here your top platform entity, pointing to the item list */
const OMAP_Platform_t CH_OMAP5_Platform = {"OMAP5",512,OMAP5_ItemsList,sizeof(OMAP5_ItemsList)/sizeof(CH_Item_t*)};

#endif // _CH_OMAP5_H
