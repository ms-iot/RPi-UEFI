/*
   2  * ch_omap4.h
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

#ifndef _CH_OMAP4_H
#define _CH_OMAP4_H

/* Define here all the data fields for each item */
CH_Field OMAP4_CHSETTINGS_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C1},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	
	{0x0008,0x04,"Flags","ClockSettings",0},
	{0x000C,0x04,"CM_CLKSEL_CORE","ClockSettings",0},
	{0x0010,0x04,"CM_DLL_CTRL","ClockSettings",0},
	{0x0014,0x04,"CM_AUTOIDLE_DPLL_MPU","ClockSettings",0},
	{0x0018,0x04,"CM_CLKSEL_DPLL_MPU","ClockSettings",0},
	{0x001C,0x04,"CM_DIV_M2_DPLL_MPU","ClockSettings",0},
	{0x0020,0x04,"CM_AUTOIDLE_DPLL_CORE","ClockSettings",0},
	{0x0024,0x04,"CM_CLKSEL_DPLL_CORE","ClockSettings",0},
	{0x0028,0x04,"CM_DIV_M2_DPLL_CORE","ClockSettings",0},
	{0x002C,0x04,"CM_DIV_M3_DPLL_CORE","ClockSettings",0},
	{0x0030,0x04,"CM_DIV_M4_DPLL_CORE","ClockSettings",0},
	{0x0034,0x04,"CM_DIV_M5_DPLL_CORE","ClockSettings",0},
	{0x0038,0x04,"CM_DIV_M6_DPLL_CORE","ClockSettings",0},
	{0x003C,0x04,"CM_DIV_M7_DPLL_CORE","ClockSettings",0},
	{0x0040,0x04,"CM_AUTOIDLE_DPLL_PER","ClockSettings",0},
	{0x0044,0x04,"CM_CLKSEL_DPLL_PER","ClockSettings",0},
	{0x0048,0x04,"CM_DIV_M2_DPLL_PER","ClockSettings",0},
	{0x004C,0x04,"CM_DIV_M3_DPLL_PER","ClockSettings",0},
	{0x0050,0x04,"CM_DIV_M4_DPLL_PER","ClockSettings",0},
	{0x0054,0x04,"CM_DIV_M5_DPLL_PER","ClockSettings",0},
	{0x0058,0x04,"CM_DIV_M6_DPLL_PER","ClockSettings",0},
	{0x005C,0x04,"CM_DIV_M7_DPLL_PER","ClockSettings",0},
	{0x0060,0x04,"CM_AUTOIDLE_DPLL_USB","ClockSettings",0},
	{0x0064,0x04,"CM_CLKSEL_DPLL_USB","ClockSettings",0},
	{0x0068,0x04,"CM_DIV_M2_DPLL_USB","ClockSettings",0}
};
CH_Field OMAP4_CHRAM_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C2},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	
	{0x0008,0x04,"SdramConfigEMIF1","SDRAM Configuration Register",0},
	{0x000C,0x04,"SdramRefreshEMIF1","SDRAM Refresh Control Register",0},
	{0x0010,0x04,"SdramTim1EMIF1","SDRAM Timing 1 Register",0},
	{0x0014,0x04,"SdramTim2EMIF1","SDRAM Timing 2 Register",0},
	{0x0018,0x04,"SdramTim3EMIF1","SDRAM Timing 3 Register",0},
	{0x001C,0x04,"PwrMgtCtrlEMIF1","Power mgt control Register",0},
	{0x0020,0x04,"DdrPhyCtrl1EMIF1","DDR PHY Control 1 Register",0},
	{0x0024,0x04,"DdrPhyCtrl2EMIF1","DDR PHY Control 2 Register",0},
	{0x0028,0x01,"ModeReg1EMIF1","Mode register MR1",0},
	{0x0029,0x01,"ModeReg2EMIF1","Mode register MR2",0},
	{0x002A,0x01,"ModeReg3EMIF1","Mode register MR3",0},
	{0x002B,0x01,"Reserved","Reserved",0},
	
	{0x002C,0x04,"SdramConfigEMIF2","SDRAM Configuration Register",0},
	{0x0030,0x04,"SdramRefreshEMIF2","SDRAM Refresh Control Register",0},
	{0x0034,0x04,"SdramTim1EMIF2","SDRAM Timing 1 Register",0},
	{0x0038,0x04,"SdramTim2EMIF2","SDRAM Timing 2 Register",0},
	{0x003C,0x04,"SdramTim3EMIF2","SDRAM Timing 3 Register",0},
	{0x0040,0x04,"PwrMgtCtrlEMIF2","Power mgt control Register",0},
	{0x0044,0x04,"DdrPhyCtrl1EMIF2","DDR PHY Control 1 Register",0},
	{0x0048,0x04,"DdrPhyCtrl2EMIF2","DDR PHY Control 2 Register",0},
	{0x004C,0x01,"ModeReg1EMIF2","Mode register MR1",0},
	{0x004D,0x01,"ModeReg2EMIF2","Mode register MR2",0},
	{0x004E,0x01,"ModeReg3EMIF2","Mode register MR3",0},
	{0x004F,0x01,"Reserved","Reserved",0},
	
	{0x0050,0x04,"DMMLisaMap0","DMM LISA section 0 mapping",0},
	{0x0054,0x04,"Flags","Configure the chip selects",0}
};
CH_Field OMAP4_CHFLASH_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C3},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},
	
	{0x0008,0x02,"GPMC_SYSCONFIG_LSB","Register Value",0},
	{0x000A,0x02,"GPMC_IRQENABLE_LSB","Register Value",0},
	{0x000C,0x02,"GPMC_TIMEOUT_CONTROL_LSB","Register Value",0},
	
	{0x000E,0x02,"GPMC_CONFIG_LSB","Register Value",0},
	{0x0010,0x04,"GPMC_CONFIG1_0","Register Value",0},
	{0x0014,0x04,"GPMC_CONFIG2_0","Register Value",0},
	{0x0018,0x04,"GPMC_CONFIG3_0","Register Value",0},
	{0x001C,0x04,"GPMC_CONFIG4_0","Register Value",0},
	{0x0020,0x04,"GPMC_CONFIG5_0","Register Value",0},
	{0x0024,0x04,"GPMC_CONFIG6_0","Register Value",0},
	{0x0028,0x04,"GPMC_CONFIG7_0","Register Value",0},

	{0x002C,0x04,"GPMC_PREFETCH_CONFIG1","Register Value",0},
	{0x0030,0x02,"GPMC_PREFETCH_CONFIG2_LSB","Register Value",0},
	{0x0032,0x02,"GPMC_PREFETCH_CONTROL_LSB","Register Value",0},
	{0x0034,0x02,"GPMC_ECC_CONFIG","Register Value",0},
	{0x0036,0x02,"GPMC_ECC_CONTROL","Register Value",0},
	{0x0038,0x04,"GPMC_ECC_SIZE_CONFIG_LSB","Register Value",0},
	{0x003C,0x04,"Enable_A1_A10","Enable A1-A10 pads",0}
};
CH_Field OMAP4_CHMMCSD_Fields[] = {
	{0x0000,0x04,"SectionKey","Key used for item verification",0xC0C0C0C4},
	{0x0004,0x01,"Valid","Enables / Disables the item",0},
	{0x0005,0x01,"Version","Configuration header version",1},
	{0x0006,0x02,"Reserved","Reserved",0},

	{0x0008,0x02,"MMC_SYSCTL_MSW","MMC_SYSCTL_MSW",0},
	{0x000A,0x02,"MMC_SYSCTL_LSW","MMC_SYSCTL_LSW",0},

	{0x000C,0x04,"BusWidth","BusWidth",0}
};

/* Now define here the TOC entry for each item */
CH_Item_t OMAP4_CHSETTINGS_Item = {	{0x0,0x6C,{0,0,0},"CHSETTINGS"},
										OMAP4_CHSETTINGS_Fields,
										sizeof(OMAP4_CHSETTINGS_Fields)/sizeof(CH_Field) };

CH_Item_t OMAP4_CHRAM_Item = {	{0x0,0x58,{0,0,0},"CHRAM"},
									OMAP4_CHRAM_Fields,
									sizeof(OMAP4_CHRAM_Fields)/sizeof(CH_Field) };
	
CH_Item_t OMAP4_CHFLASH_Item = {	{0x0,0x40,{0,0,0},"CHFLASH"},
									OMAP4_CHFLASH_Fields,
									sizeof(OMAP4_CHFLASH_Fields)/sizeof(CH_Field) };
	
CH_Item_t OMAP4_CHMMCSD_Item = {	{0x0,0x10,{0,0,0},"CHMMCSD"},
									OMAP4_CHMMCSD_Fields,
									sizeof(OMAP4_CHMMCSD_Fields)/sizeof(CH_Field) };

/* Make sure to list here each defined item */
CH_Item_t* OMAP4_ItemsList[] = {	&OMAP4_CHSETTINGS_Item,
									&OMAP4_CHRAM_Item,
									&OMAP4_CHFLASH_Item,
									&OMAP4_CHMMCSD_Item };

/* Define here your top platform entity, pointing to the item list */
const OMAP_Platform_t CH_OMAP4_Platform = {"OMAP4",512,OMAP4_ItemsList,sizeof(OMAP4_ItemsList)/sizeof(CH_Item_t*)};

#endif // _CH_OMAP4_H
