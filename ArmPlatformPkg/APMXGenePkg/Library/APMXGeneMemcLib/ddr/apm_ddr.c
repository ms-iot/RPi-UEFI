/**
 * APM X-Gene DDR3 controller
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#undef CONFIG_CMD_STORM_DDR
#if defined(APM_TIANOCORE)

#include "apm_ddr_sdram.h"
#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "ddr_spd.h"
#define CONFIG_NR_DRAM_BANKS 4
#else

#include <common.h>
#include <command.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include <asm/arch/apm_scu.h>
#include <asm/arch/apm_ipp_csr.h>
#include "config.h"
#include "ddr/ddr_lib.h"

DECLARE_GLOBAL_DATA_PTR;
#endif

//  UBOOT
#define CONFIG_BOARD_TYPE_MUSTANG	1
#define CONFIG_BOARD_TYPE_BLACKBIRD	0

struct ddr_config_env {
	int  ddrecc;
	int  ddrrankintlv;
	int  ddrmcbintlv;
	int  ddrmcuintlv;
	int  ddrrankhashen;
	int  ddrrankhash;
	int  ddrbase_2g;
	int  ddrzqcal;
	int  ddrspeed;
	int  ddrmargin;
	int  ddrforcepll;
}; 

struct ddr_config_env ddr_media_env;
int board_type;

static int apm88xxx_chip_revision(void)
{
#define EFUSE0_SHADOW_VERSION_SHIFT     28
#define EFUSE0_SHADOW_VERSION_MASK      0xF
#define SCU_JTAG0                       0x17000004
#define EFUSE0_SHADOW_ADDR_ABS          0x1054a000
  volatile u32 *addr;
  addr = (u32 *)EFUSE0_SHADOW_ADDR_ABS;

  u32 val = (*(addr) >> EFUSE0_SHADOW_VERSION_SHIFT)
              & EFUSE0_SHADOW_VERSION_MASK;
  switch (val){
  case 0x00:
    addr = (u32 *)SCU_JTAG0;
    return (*addr & 0x10000000)? 2: 1;
  case 0x01:
    return 2;
  case 0x02:
    return 3;
  }
  return 0;
}


#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
void ddr_media_getenv(char *name, char *value)
{
	if(!strcmp(name, "DDRECC"))
		ddr_media_env.ddrecc = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRRANKINTLV"))
		ddr_media_env.ddrrankintlv = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRMCBINTLV"))
		ddr_media_env.ddrmcbintlv = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRMCUINTLV"))
		ddr_media_env.ddrmcuintlv = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRRANKHASHEN"))
		ddr_media_env.ddrrankhashen = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRRANKHASH"))
		ddr_media_env.ddrrankhash = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRBASE2G"))
		ddr_media_env.ddrbase_2g = simple_strtoul(value, NULL, 10);
	if(!strcmp(name, "DDRZQCAL"))
		ddr_media_env.ddrzqcal = simple_strtoul(value, NULL, 10);
	if(!strcmp(name, "DDRSPEED"))
		ddr_media_env.ddrspeed = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRMARGIN"))
		ddr_media_env.ddrmargin = simple_strtoul(value, NULL, 10); 
	if(!strcmp(name, "DDRFORCEPLL"))
		ddr_media_env.ddrforcepll = simple_strtoul(value, NULL, 10); 
}

void ddr_spi_env_detect(void)
{
	const char sep = '\0';
	int size = CONFIG_ENV_SIZE;
	char *data, *sp, *dp, *name, *value;	

	data = (char*)CONFIG_ENV_OCM_ADDR;
	/* skip 4 bytes CRC */
	dp = data + 4; 
	do {
		/* skip leading white space */
                while (isblank(*dp))
                        ++dp;
		/* skip comment lines */
                if (*dp == '#') {
                        while (*dp && (*dp != sep))
                                ++dp;
                        ++dp;
                        continue;
                }
		/* parse name */
                for (name = dp; *dp != '=' && *dp && *dp != sep; ++dp) 
                        ;
		/* deal with name */
		if (*dp == sep || *(dp + 1) == sep) {
			if (*dp == '=')
                                *dp++ = '\0';
                        *dp++ = '\0';   /* terminate name */
		}
		*dp++ = '\0';   /* terminate name */
		/* parse value; deal with escapes */
                for (value = sp = dp; *dp && (*dp != sep); ++dp) {
                        if ((*dp == '\\') && *(dp + 1))
                                ++dp;
                        *sp++ = *dp;
                }
                *sp++ = '\0';   /* terminate value */
		/* detect to get DDR config env */
		ddr_media_getenv(name, value);
		++dp;
	} while((dp < data + size) && *dp);    /* size check needed for text */
}
#endif /* CONFIG_ENV_IS_IN_SPI_FLASH */

/*
 * Check for invalid parameters
 * Avoid user's mistake 
 */
void ddr_param_valid_check(int param_type, unsigned int *param)
{
	unsigned int val;	
	/* DDRSPEED */
	if (param_type == 0){
		val = *param;
		switch (val) {
		case 800:
		case 1066:
		case 1333:
		case 1550:
		case 1600:
		case 1866:
			break;
		default:
			printf("Error: Unsupported DDRSPEED %d!!!\n", *param);
			*param = 1600;
		}
	}
}

void check_valid_interleave_mode_config (struct apm_memc *memc)
{
	unsigned int i;
	int first_dimm = -1;
	int rnk_err = 0;

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		if (!memc->mcu[i].enabled)
			continue;
		/* Detect the first populated DIMM */
		if (first_dimm < 0) {
			first_dimm = i;
			continue;
		}
		/* Invalid number of rank or rank size */ 
		rnk_err = (memc->mcu[i].dimm_params[0].n_ranks !=
			memc->mcu[first_dimm].dimm_params[0].n_ranks)? 1 : 0;
		rnk_err += (memc->mcu[i].dimm_params[0].rank_density !=
			memc->mcu[first_dimm].dimm_params[0].rank_density)? 1 : 0;
		if (rnk_err > 0) { 
			printf(" ## DRAM Interleave mode ERROR:"
				" please install identical DIMMs and REBOOT ##\n");
			while(1);
		}
	}
}

int bb_storm_a1_ddr_speed_limit (struct apm_memc memc)
{
	unsigned int i;
	
	switch (memc.mcu_mask) {
		case 0x3:
		case 0x5:
		case 0xC:
		case 0xF:
			if ((memc.mcu[0].dimm_params[0].n_ranks == 2) &&
				(memc.mcu[0].mcu_ud.ud_speed >= 1600)) {
				for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) 
					memc.mcu[i].mcu_ud.ud_speed = 1550;
			}
		break;
	}
	return memc.p_spdcal(&memc, 0);
}

void ddr_dimm_config(struct apm_memc *memc)
{
	unsigned int iia;

	memc->mcb_intrlv = memc->mc_ud.ud_mcb_intrlv;
	memc->dual_mcb = memc->mcb_intrlv;
	memc->mcu_mask = 0;
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) 
		memc->mcu_mask |= memc->mcu[iia].enabled << iia;
	/*
	 * Setup MCB/MCU and Interleave Mode
	 */
	memc->mcb[0].dual_mcu = 0;
	memc->mcb[0].mcu_intrlv = 0;
	memc->mcb[1].dual_mcu = 0;
	memc->mcb[1].mcu_intrlv = 0;
	memc->dual_mcb = 0;
	memc->mcb_intrlv = 0;
	switch (memc->mcu_mask) {
	case 0x1:
		/* 1 channel MCU0 */
		break;
	case 0x3:
		/* 2 channels MCU0-MCU1 */
		memc->mcb[0].dual_mcu = 1;
		memc->mcb[0].mcu_intrlv = memc->mcb[0].mcb_ud.ud_mcu_intrlv;
		break;
	case 0x4:
		/* 1 channel MCU2 */
		memc->dual_mcb = 1;
		break;

	case 0x5:
		/* 2 channels MCU0-MCU2 */
		memc->dual_mcb = 1;
		memc->mcb_intrlv = memc->mc_ud.ud_mcb_intrlv;
		break;
	case 0xf:
		/* 4 channels */
		memc->dual_mcb = 1;
		memc->mcb[0].dual_mcu = 1;
		memc->mcb[1].dual_mcu = 1;
		memc->mcb_intrlv = memc->mc_ud.ud_mcb_intrlv;
		memc->mcb[0].mcu_intrlv = memc->mcb[0].mcb_ud.ud_mcu_intrlv;
		memc->mcb[1].mcu_intrlv = memc->mcb[1].mcb_ud.ud_mcu_intrlv;
		break;
	case 0x0:
		printf("Error! No DIMM detected!!!\n");
		break;
	default:
		printf("\nInvalid DDR configuration - "
			"MCU mask: %x\n", memc->mcu_mask);
		printf("Force using minimum DDR configuration"
			" single channel MCU0 alone\n");
		break;
	}
}

int get_spd(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	generic_spd_eeprom_t *spd;
	unsigned char dimm_type = 0;
	unsigned char i2c_address;
	int err = 0;

	spd = &mcu->spd_info[slot];
	memset(spd, 0, sizeof(generic_spd_eeprom_t));
	/* If a mux is provisioned, set the mux correctly first */
	if (mcu->spd_mux){
		err = i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1);
		if (err){
			debug("Can not send comment to MUX");
			return 0;
		}
	}
	i2c_address = mcu->spd_addr[slot];
	/* If no spd address, assume not populated */
	if (i2c_address == 0)
		return 0;
	dimm_type = 0;
	/* Check for DIMM type before reading */
        err = i2c_read(i2c_address, 2, 1, &dimm_type, 1);
        if (dimm_type == SPD_MEMTYPE_DDR3) {
                debug("MCU[%d]-Slot[%d]-DDR3-DIMM-FOUND\n", mcu->id, slot);
                debug("\tReading DIMM SPD data @0x%llx...\n", 
						(unsigned long long)spd);
                err += i2c_read(i2c_address, 0, 1, (unsigned char *)spd,
                                sizeof(spd_eeprom_t));
        } else {
                debug("\tMCU[%d]-Slot[%d]-NO-DIMM\n", mcu->id, slot);
                return 0;
        }

        return (!err)? 1: 0;
}

void common_usr_ddr_params(struct apm_memc *pmemc)
{
	struct apm_mcu *mcu;
	unsigned int i, k;
	unsigned int desired_fix_wrdq_dly[4][18] = {
		{0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 
			0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48},
		{0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 
			0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48},
		{0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 
			0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48},
		{0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 
			0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48},
	};

	/* Enable SPEC read always */
	pmemc->mcb[0].mcb_ud.spec_read = 1;
	pmemc->mcb[1].mcb_ud.spec_read = 1;
	pmemc->mc_ud.ud_ignore_init_cecc_err = 1;
	pmemc->mc_ud.ud_reset_on_err = 
				getenv_ulong("DDRRESETONERR", 10, 1);
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		mcu = (struct apm_mcu *)&pmemc->mcu[i];
		ddr_param_valid_check(0, &mcu->mcu_ud.ud_speed);
#if defined(CONFIG_OCM_U_BOOT)
		mcu->mcu_ud.ud_ECCscheme = 0;
#endif
		if (is_storm_revA())
			mcu->mcu_ud.ud_zqcal_en = 0; 
		/* Set user drive strength and slew rate */
		mcu->mcu_ud.ud_bit_dq_stren = 6;
		mcu->mcu_ud.ud_bit_ad_stren = 4;
		mcu->mcu_ud.ud_bit_cmd_stren = 4;
		mcu->mcu_ud.ud_bit_ctl_stren = 4;
		mcu->mcu_ud.ud_bit_clk_stren = 6;
		mcu->mcu_ud.ud_bit_odt_stren = 4;

		mcu->mcu_ud.ud_bit_dq_slew = 3;
		mcu->mcu_ud.ud_bit_ad_slew = 3;
		mcu->mcu_ud.ud_bit_cmd_slew = 3;
		mcu->mcu_ud.ud_bit_ctl_slew = 3;
		mcu->mcu_ud.ud_bit_clk_slew = 2;

		/* PHY training bypass */
		mcu->mcu_ud.fix_wrdq_flg = 1;

		if (mcu->mcu_ud.fix_wrdq_flg) {
			for (k = 0; k < 18; k++) 
				mcu->mcu_ud.fix_wrdq_dly[k] =
						desired_fix_wrdq_dly[i][k];
		}

		/* PHY use SW rdlvl */
		if (!is_storm_revA())
			mcu->mcu_ud.ud_sw_rdlvl = 
				getenv_ulong("DDRSWRDELVL", 10, 1);
	}
	/* Spd content passed into ddrlib */
	pmemc->p_spd_get = get_spd;
#if !defined(CONFIG_SYS_CACHE_ENABLED)
	pmemc->mc_ud.ud_is_cache_on = 0;
#endif
}

int mustang_usr_ddr_params(void *ptr)
{
	struct apm_memc *pmemc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int i;

	pmemc->mc_ud.ud_mcu_mask = 0x5;
	/* Init DDR config default values Media boot*/
	ddr_media_env.ddrecc = 3;
	ddr_media_env.ddrrankintlv = 1;
	ddr_media_env.ddrmcbintlv = 1;
	ddr_media_env.ddrmcuintlv = 1;
	ddr_media_env.ddrrankhashen = 0;
	ddr_media_env.ddrrankhash = 4;
	ddr_media_env.ddrbase_2g = 0;
	ddr_media_env.ddrzqcal = 1;
	ddr_media_env.ddrspeed = 1600;
	ddr_media_env.ddrmargin = -1; /* default depends on speed */
	ddr_media_env.ddrforcepll = 0;
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
	ddr_spi_env_detect();
#endif

	pmemc->mc_ud.ud_mcb_intrlv = ddr_media_env.ddrmcbintlv; 
	pmemc->mcb[0].mcb_ud.ud_mcu_intrlv = 
		pmemc->mcb[1].mcb_ud.ud_mcu_intrlv = ddr_media_env.ddrmcuintlv;
	pmemc->mc_ud.ud_mcu_base_2g = ddr_media_env.ddrbase_2g;
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		mcu = (struct apm_mcu *)&pmemc->mcu[i];
		mcu->mcu_ud.ud_rank_intrlv = ddr_media_env.ddrrankintlv;
		mcu->mcu_ud.ud_rank_hash_en = ddr_media_env.ddrrankhashen;
		mcu->mcu_ud.ud_rank_hash = ddr_media_env.ddrrankhash;
		mcu->mcu_ud.ud_ECCscheme = ddr_media_env.ddrecc;
		mcu->mcu_ud.ud_speed = ddr_media_env.ddrspeed;
		if (ddr_media_env.ddrmargin < 0) {
			if (mcu->mcu_ud.ud_speed == 1866)
				ddr_media_env.ddrmargin = 0x210000;
			else
				ddr_media_env.ddrmargin = 0x110000;
		}
		/* rank rd2wr|rank wr2rd|margin0|margin1|rank rd2rd|rank wr2wr */
		mcu->mcu_ud.ud_tmargin = ddr_media_env.ddrmargin;
		mcu->mcu_ud.ud_pllforce = ddr_media_env.ddrforcepll; 
		mcu->mcu_ud.ud_zqcal_en = ddr_media_env.ddrzqcal;
		
		mcu->mcu_ud.ud_zqcal_code = 0x731;

		/* PHY training bypass */
		mcu->mcu_ud.fix_gtlvl_flg = 0;
		mcu->mcu_ud.fix_rdlvl_flg = 0;
		mcu->mcu_ud.fix_wrlvl_flg = 0;
	}
	/* Load common user defined DDR params */
	common_usr_ddr_params(pmemc);

	return 0;
}

int blackbird_usr_ddr_params(void *ptr)
{
	struct apm_memc *pmemc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int i, j, k;
	unsigned int desired_fix_rd_lvl[4][2][18] = {
		{{0x29, 0, 0x29, 0, 0x29, 0, 0x29, 0, 0x29, 0, 
			0x35, 0, 0x29, 0, 0x29, 0, 0x36, 0}, 
		 {0x29, 0, 0x29, 0, 0x29, 0, 0x29, 0, 0x29, 0, 
			0x35, 0, 0x29, 0, 0x29, 0, 0x34, 0}}, 
		{{0x2D, 0, 0x30, 0, 0x30, 0, 0x30, 0, 0x2a, 0, 
			0x30, 0, 0x39, 0, 0x3a, 0, 0x35, 0},
		 {0x2D, 0, 0x30, 0, 0x30, 0, 0x30, 0, 0x2a, 0, 
			0x30, 0, 0x39, 0, 0x3a, 0, 0x35, 0}},
		{{0x30, 0, 0x30, 0, 0x30, 0, 0x30, 0, 0x30, 0, 
			0x30, 0, 0x30, 0, 0x30, 0, 0x33, 0},
		 {0x30, 0, 0x30, 0, 0x30, 0, 0x30, 0, 0x30, 0, 
			0x30, 0, 0x30, 0, 0x30, 0, 0x32, 0}},
		{{0x35, 0, 0x3a, 0, 0x3a, 0, 0x40, 0, 0x3b, 0, 
			0x2f, 0, 0x42, 0, 0x3a, 0, 0x34, 0},
		 {0x36, 0, 0x3c, 0, 0x3b, 0, 0x3f, 0, 0x3a, 0, 
			0x30, 0, 0x49, 0, 0x3c, 0, 0x37, 0}},
	};
	unsigned int desired_fix_gt_lvl[4][2][18] = {
                {{0x41b, 0, 0x422, 0, 0x420, 0, 0x46b, 0, 0x4A4, 0, 
			0x4c2, 0, 0x4e3, 0, 0x50c, 0, 0x48d, 0},
                 {0x41d, 0, 0x41c, 0, 0x421, 0, 0x46e, 0, 0x4A4, 0, 
			0x4BF, 0, 0x4DD, 0, 0x50b, 0, 0x48e, 0}},
                {{0x42A, 0, 0x45a, 0, 0x486, 0, 0x4a8, 0, 0x50d, 0, 
			0x518, 0, 0x568, 0, 0x58e, 0, 0x4c4, 0},
                 {0x421, 0, 0x466, 0, 0x488, 0, 0x4ac, 0, 0x516, 0, 
			0x522, 0, 0x56a, 0, 0x590, 0, 0x4c8, 0}},
                {{0x472, 0, 0x46d, 0, 0x478, 0, 0x4bc, 0, 0x4b9, 0, 
			0x4d8, 0, 0x503, 0, 0x520, 0, 0x4b4, 0},
                 {0x471, 0, 0x470, 0, 0x484, 0, 0x4c0, 0, 0x4c2, 0, 
			0x4e0, 0, 0x503, 0, 0x524, 0, 0x4bf, 0}},
                {{0x42c, 0, 0x476, 0, 0x494, 0, 0x4ba, 0, 0x524, 0, 
			0x525, 0, 0x582, 0, 0x5ae, 0, 0x4e2, 0},
                 {0x46a, 0, 0x478, 0, 0x493, 0, 0x4b6, 0, 0x521, 0, 
			0x524, 0, 0x582, 0, 0x5ae, 0, 0x4da, 0}},
        };
	unsigned int desired_fix_wr_lvl[4][2][18] = {
		{{0x163, 0, 0x1a9, 0, 0x1ef, 0, 0x21f, 0, 0x289, 0, 
			0x2c1, 0, 0x2e7, 0, 0x305, 0, 0x23F, 0}, 
		 {0x163, 0, 0x1aa, 0, 0x1e9, 0, 0x225, 0, 0x285, 0, 
			0x2b5, 0, 0x2e7, 0, 0x304, 0, 0x239, 0}},
		{{0x1a1, 0, 0x1e2, 0, 0x1f6, 0, 0x239, 0, 0x254, 0, 
			0x295, 0, 0x2eb, 0, 0x310, 0, 0x245, 0},
		 {0x1a9, 0, 0x1f6, 0, 0x1fa, 0, 0x23a, 0, 0x256, 0, 
			0x298, 0, 0x2f7, 0, 0x304, 0, 0x23f, 0}},
		{{0x1a1, 0, 0x1e2, 0, 0x1f6, 0, 0x239, 0, 0x254, 0, 
			0x295, 0, 0x2eb, 0, 0x310, 0, 0x225, 0},
		 {0x1a9, 0, 0x1f6, 0, 0x1fa, 0, 0x23a, 0, 0x256, 0, 
			0x298, 0, 0x2f7, 0, 0x304, 0, 0x225, 0}},
		{{0x19f, 0, 0x1cb, 0, 0x1f4, 0, 0x229, 0, 0x25d, 0, 
			0x28d, 0, 0x2a1, 0, 0x2b0, 0, 0x245, 0},
		 {0x1a6, 0, 0x1c8, 0, 0x1f4, 0, 0x230, 0, 0x264, 0, 
			0x281, 0, 0x29a, 0, 0x2af, 0, 0x245, 0}},
	};

	pmemc->mcb[0].mcb_ud.ud_mcu_intrlv = 
		pmemc->mcb[1].mcb_ud.ud_mcu_intrlv = 
					getenv_ulong("DDRMCUINTLV", 10, 1);
	pmemc->mc_ud.ud_mcb_intrlv = getenv_ulong("DDRMCBINTLV", 10, 1);
	pmemc->mc_ud.ud_mcu_base_2g = getenv_ulong("DDRBASE2G", 10, 0);

	pmemc->mc_ud.ud_mcu_mask = getenv_ulong("DDRMCU", 16, 0xF);
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		mcu = (struct apm_mcu *)&pmemc->mcu[i];
		mcu->mcu_ud.ud_speed = getenv_ulong("DDRSPEED", 10, 1600);
		if (mcu->mcu_ud.ud_speed == 1866) 
			mcu->mcu_ud.ud_tmargin =
				getenv_ulong("DDRMARGIN", 16, 0x210000);
		else
			mcu->mcu_ud.ud_tmargin =
				getenv_ulong("DDRMARGIN", 16, 0x110000);

		mcu->mcu_ud.ud_pllforce = getenv_ulong("DDRFORCEPLL", 10, 0);	
		mcu->mcu_ud.ud_ECCscheme = getenv_ulong("DDRECC", 10, 3);
		mcu->mcu_ud.ud_zqcal_en = getenv_ulong("DDRZQCAL", 10, 1);

		/* user's desired rank interleave config */
		mcu->mcu_ud.ud_rank_intrlv =
				getenv_ulong("DDRRANKINTLV", 10, 1);
		/* 
		 * user's desired rank has config 
		 * rank hash size:
 		 * 0:64K - 1:128K - 2:256K - 3:512K - 4:1M - 5:2M 
		 */
		mcu->mcu_ud.ud_rank_hash_en =
				getenv_ulong("DDRRANKHASHEN", 10, 0);
		mcu->mcu_ud.ud_rank_hash = getenv_ulong("DDRRANKHASH", 10, 4);

		/* PHY training bypass */
		mcu->mcu_ud.fix_gtlvl_flg = 0;
		mcu->mcu_ud.fix_rdlvl_flg = 0;
		mcu->mcu_ud.fix_wrlvl_flg = 0;
		/* Support fix leveling values for each MCU */
		if (mcu->mcu_ud.fix_rdlvl_flg) {
			for (j =0; j < 2; j++) {
				for (k = 0; k < 18; k++) 
					mcu->mcu_ud.fix_rd_lvl[j][k] = 
						desired_fix_rd_lvl[i][j][k];
			}
		}
		if (mcu->mcu_ud.fix_gtlvl_flg) {
			for (j =0; j < 2; j++) {
				for (k = 0; k < 18; k++) 
					mcu->mcu_ud.fix_gt_lvl[j][k] = 
						desired_fix_gt_lvl[i][j][k];
			}
		}
		if (mcu->mcu_ud.fix_wrlvl_flg) {
			for (j =0; j < 2; j++) {
				for (k = 0; k < 18; k++) 
					mcu->mcu_ud.fix_wr_lvl[j][k] = 
						desired_fix_wr_lvl[i][j][k];
			}
		}
	}
	pmemc->mcu[0].mcu_ud.ud_zqcal_code = getenv_ulong("ZQ0", 16, 0x731);
	pmemc->mcu[1].mcu_ud.ud_zqcal_code = getenv_ulong("ZQ1", 16, 0x731);
	pmemc->mcu[2].mcu_ud.ud_zqcal_code = getenv_ulong("ZQ2", 16, 0x731);
	pmemc->mcu[3].mcu_ud.ud_zqcal_code = getenv_ulong("ZQ3", 16, 0x731);

	/* Load common user defined DDR params */
	common_usr_ddr_params(pmemc);

	return 0;
}

void mustang_board_ddr_cfg(struct apm_memc *pmemc)
{
	unsigned int i;
	unsigned int val;
	unsigned long long base = CONFIG_SYS_SCU_BASE + APM_MPA_REG_OFFSET;

	/* Enable SPD access: GPIO_DS16 = 1 */
	val = readl(base + MPA_GPIO_SEL_HI_ADDR);
	val &= ~0x00000003;
	writel(val, base + MPA_GPIO_SEL_HI_ADDR);
	val = readl(base + MPA_GPIO_OE_ADDR);
	val |= 0x00010000;
	writel(val, base + MPA_GPIO_OE_ADDR);
	val = readl(base + MPA_GPIO_OUT_ADDR);
	val |= 0x00010000;
	writel(val, base + MPA_GPIO_OUT_ADDR);

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		/*
		 * Setup SPD I2C configuration
		 */
		pmemc->mcu[i].spd_mux = 0;
		pmemc->mcu[i].spd_mux_addr = 0;
		pmemc->mcu[i].spd_addr[0] = (i == 0) ? 0x54 : 0x57;
		pmemc->mcu[i].spd_addr[1] = 0;
	}
}


void blackbird_board_ddr_cfg(struct apm_memc *pmemc)
{
	unsigned int i;

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		/*
		 * Setup SPD I2C configuration
		 */
		pmemc->mcu[i].spd_mux = 0x70;
		pmemc->mcu[i].spd_mux_addr = 1 << i;

		pmemc->mcu[i].spd_addr[0] = 0x54;
		pmemc->mcu[i].spd_addr[1] = 0x55;
	}
}

static int get_board_type (void)
{
	unsigned char muxaddr = 1;

	if (i2c_read(0x70, 0, 1, &muxaddr, 1)) 
		return CONFIG_BOARD_TYPE_MUSTANG; 
	else
		return CONFIG_BOARD_TYPE_BLACKBIRD; 
}

void dram_board_init(struct apm_memc *pmemc)
{
	/*
	 * Lets do a simple board detection here first
	 * Need to figure out if it is black bird or mustang
	 */
	switch (get_board_type()) {
		case CONFIG_BOARD_TYPE_BLACKBIRD:
			debug("DRAM: Blackbird Board detected.\n");
			blackbird_board_ddr_cfg(pmemc);
			pmemc->p_usr_setup = blackbird_usr_ddr_params;
			break;
		case CONFIG_BOARD_TYPE_MUSTANG:
			debug("DRAM: Mustang Board detected.\n");
			mustang_board_ddr_cfg(pmemc);
			pmemc->p_usr_setup = mustang_usr_ddr_params;
			break;
	}

	pmemc->p_setup = ddr_sys_setup;
	pmemc->p_spdcal = ddr_sys_spd_calc;
	pmemc->p_init = ddr_sys_init;
	pmemc->full_addr = 1;	/* 1: 42 bit mode */
}

int dram_hw_init(void)
{
	struct apm_memc ddr;
	unsigned int err = 0;
	unsigned int i;
	unsigned int spd_err = 0;
	unsigned long long ram_size = 0;

	/* Init the apm_memc structure */
	printf("DRAM: ");
        memset(&ddr, 0, sizeof(struct apm_memc));

	/* Do some board related DDR structure setup */
	dram_board_init(&ddr);

	/* Setup Data Struct & functions */
	err += ddr.p_setup(&ddr, 0);

	/* Discover SPD and Dimm params etc */
	spd_err = ddr.p_spdcal(&ddr, 0);

	/* For Storm A1 Black Bird 2 channels or 4 channels 2 ranks support upto 1550Mhz */
	if (apm88xxx_chip_revision() == 1
			&&  get_board_type() == CONFIG_BOARD_TYPE_BLACKBIRD) 
		spd_err = bb_storm_a1_ddr_speed_limit(ddr);

	/*
	 * Setup interleave mode
	 */
	ddr_dimm_config(&ddr);

	/* Check if MCB/MCU interleave mode DIMM configuration is valid */
	if (ddr.mcb_intrlv || ddr.mcb[0].mcu_intrlv || ddr.mcb[1].mcu_intrlv)
		check_valid_interleave_mode_config(&ddr);	

	/* Memory controller initialization */
	err += ddr.p_init(&ddr, 0);

#if !defined(APM_TIANOCORE)
	/* Uboot always allocate within first DDR region */
	gd->ram_start = ddr.memspace.str_addr[0];
	gd->ram_size =
		(ddr.memspace.end_addr[0] - ddr.memspace.str_addr[0]) + 1;
#endif

	/* 
	 * Update all the valid DRAM banks 
	 * XXX Don't expose memory ranges bigger than 256GB due to kernel limit
	 */
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++){
		if (ddr.memspace.str_addr[i] == ddr.memspace.end_addr[i])
			break;

#if !defined(APM_TIANOCORE)
		if ((ddr.memspace.end_addr[i] - gd->ram_start) >=
				0x4000000000ULL){
#else
		if ((ddr.memspace.end_addr[i] - ddr.memspace.str_addr[0]) >=
				0x4000000000ULL){
#endif
			ddr.memspace.str_addr[i] = 0;
			ddr.memspace.end_addr[i] = 0;
			ddr.memspace.num_mem_regions--;
			continue;
		}
#if !defined(APM_TIANOCORE)
		gd->sys_mem[i].start = ddr.memspace.str_addr[i];
		gd->sys_mem[i].size = 
			(ddr.memspace.end_addr[i] - ddr.memspace.str_addr[i]) +
			1; 
#endif
		ram_size += (ddr.memspace.end_addr[0] - ddr.memspace.str_addr[0]) + 1;			
	}
	print_size(ram_size, "");
	printf(" @ %dMHz\n", ddr.mcu[0].mcu_params.speed);

	if (ddr.memspace.num_mem_regions > 1) { 
		printf("    Non-contiguous multiple bank memory detected:\n");
		for (i = 0; i < ddr.memspace.num_mem_regions; i++) 
			printf("\tDDR region[%d]: 0x%010llx - 0x%010llx\n", i,
				ddr.memspace.str_addr[i], ddr.memspace.end_addr[i]);	
	}

	if (spd_err & 0x2)
		printf("Warning: SPD checksum incorrect.\n");

	return err;
}

#ifdef CONFIG_CMD_STORM_DDR
int do_ddr_tp(struct apm_memc *memc, cmd_tbl_t * cmdtp, int flag, int argc,
	      char *const argv[])
{
	unsigned char i;
	struct apm_mcu *mcu;
	unsigned int mtb_ps;
	generic_spd_eeprom_t *spd;
	dimm_params_t *pdimm;

	printf("\nDDR Timing Parameters\n");
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {

		if (memc->mcu[i].enabled == 0)
			continue;

		mcu = &memc->mcu[0];

		spd = &mcu->spd_info[0];
		pdimm = &mcu->dimm_params[0];
		printf("\tDIMM Capacity (%d ranks): total 0x%llx\n",
		       pdimm->n_ranks, pdimm->capacity);

		switch (spd->module_type & 0xf) {
		case 0x01:		/* RDIMM */
		case 0x05:		/* Mini-RDIMM */
			printf("\tRegister DIMM detected: Type 0x%X\n",
			      spd->module_type & 0xf);
			break;
		case 0x0B:		/* LRDIMM */
			printf("\tLRDIMM detected: Type 0x%X\n",
			       spd->module_type & 0xf);
			break;
		case 0x02:		/* UDIMM */
		case 0x03:		/* SO-DIMM */
		case 0x04:		/* Micro-DIMM */
		case 0x06:		/* Mini-UDIMM */
			printf("\tUnbuffered DIMM detected: Type 0x%X\n",
			      spd->module_type & 0xf);
			break;

		default:
			printf("\tUnknown dimm_type: 0x%02X\n",
			       spd->module_type);
			return 1;
		}

		printf("\tAddressing: Row: %d Col: %d Bank: %d\n",
		       pdimm->n_row_addr, pdimm->n_col_addr,
		       pdimm->n_banks_per_sdram_device);

		mtb_ps = (spd->mtb_dividend * 1000) / spd->mtb_divisor;
		printf("\tMTB(ps): %d\n", mtb_ps);

		pdimm->tCKmin_X_ps = (spd->tCK_min * mtb_ps);
		printf("\tCK min(ps): %d (min-supported by DIMM)\n",
		       pdimm->tCKmin_X_ps);

		pdimm->caslat_X =
		    ((spd->caslat_msb << 8) | spd->caslat_lsb) << 4;
		printf("\tSPD CAS Latency: 0x%4x\n", pdimm->caslat_X);

		pdimm->tAA_ps = spd->tAA_min * mtb_ps;
		printf("\tAA min(ps): %d\n", pdimm->tAA_ps);

		pdimm->tWR_ps = spd->tWR_min * mtb_ps;
		printf("\tWR min(ps): %d\n", pdimm->tWR_ps);

		pdimm->tRCD_ps = spd->tRCD_min * mtb_ps;
		printf("\tRCD min(ps): %d\n", pdimm->tRCD_ps);

		pdimm->tRRD_ps = spd->tRRD_min * mtb_ps;
		printf("\tRRD min(ps): %d\n", pdimm->tRRD_ps);

		pdimm->tRP_ps = spd->tRP_min * mtb_ps;
		printf("\tRP min(ps): %d\n", pdimm->tRP_ps);

		pdimm->tRAS_ps =
		    (((spd->tRAS_tRC_ext & 0xf) << 8) | spd->tRAS_min_lsb)
		    * mtb_ps;
		printf("\tRAS min(ps): %d\n", pdimm->tRAS_ps);

		pdimm->tRC_ps =
		    (((spd->tRAS_tRC_ext & 0xf0) << 4) | spd->tRC_min_lsb)
		    * mtb_ps;
		printf("\tRC min(ps): %d\n", pdimm->tRC_ps);

		pdimm->tRFC_ps = ((spd->tRFC_min_msb << 8) | spd->tRFC_min_lsb)
		    * mtb_ps;
		printf("\tRFC min(ps): %d\n", pdimm->tRFC_ps);

		pdimm->tWTR_ps = spd->tWTR_min * mtb_ps;
		printf("\tWTR (ps): %d\n", pdimm->tWTR_ps);

		pdimm->tRTP_ps = spd->tRTP_min * mtb_ps;
		printf("\tRTP (ps): %d\n", pdimm->tRTP_ps);

		pdimm->refresh_rate_ps = (7800U * 8 * mtb_ps);	// div by tclks is done while calculating actual ref-int for CSR
		printf("\tREF-INT (ps): %d\n", pdimm->refresh_rate_ps);

		pdimm->tFAW_ps = (((spd->tFAW_msb & 0xf) << 8) | spd->tFAW_min)
		    * mtb_ps;
		printf("\tFAW (ps): %d\n", pdimm->tFAW_ps);
		printf("\n");

		break;
	}
	return 0;
}

int do_ddr_spd(struct apm_memc *memc, cmd_tbl_t * cmdtp, int flag, int argc,
	       char *const argv[])
{
	unsigned char *ptr = 0;
	spd_eeprom_t *spd = 0;
	unsigned char i, j, k;
	struct apm_mcu *mcu;

	printf("\nDDR SPD Configuration\n");
	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		mcu = &memc->mcu[i];
		if (!mcu->enabled)
			continue;

		for (j = 0; j < 2; j++) {
			if (!(mcu->mcu_params.activeslots & (1 << j)))
				continue;

			printf("MCU %d Slot %d:\n", i, j);
			spd = (spd_eeprom_t *)&mcu->spd_info[j];
			ptr =  spd->mpart;
			printf("\tDIMM Vendor : 0x%X%X\n", spd->dmid_lsb,
						       spd->dmid_msb);
			printf("\tDIMM Part : ");
			printf("%c", *ptr++);
			for (k = 0; k < 18; k++)
				printf("%c", *ptr++);
			printf("\n\t");
			switch (spd->module_type & 0xf) {
			case 0x01:		/* RDIMM */
				printf("RDIMM: ");
				break;
			case 0x05:		/* Mini-RDIMM */
				printf("Mini-RDIMM: ");
				break;
			case 0x02:		/* UDIMM */
				printf("UDIMM: ");
				break;
			case 0x03:		/* SO-DIMM */
				printf("SODIMM: ");
				break;
			case 0x04:		/* Micro-DIMM */
				printf("Micro-DIMM: ");
				break;
			case 0x06:		/* Mini-UDIMM */
				printf("Mini-UDIMM ");
				break;
			case 0x0B:		/* LRDIMM */
				printf("LRDIMM: ");
				break;
			default:
				printf("Unknown DIMM: ");
				break;
			}
			printf("%lldMB/rank\n",
			       compute_ranksize(spd) / (1024 * 1024));
			printf("\tRanks:%d\n", mcu->dimm_params[j].n_ranks);
			printf("\tMirrored Dimm: %s\n",
			       mcu->dimm_params[j].
			       mirrored_dimm ? "yes" : "no");
			printf("\n");
		}
	}
	return 0;
}

int do_ddr_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	static struct apm_memc ddr;

	if (argc < 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	if (ddr.p_setup == NULL) {
		dram_board_init(&ddr);
		ddr.p_setup(&ddr, 0);
		ddr.p_spdcal(&ddr, 0);
	}

	if (!strncmp(argv[1], "sp", 2))
		return do_ddr_spd(&ddr, cmdtp, flag, argc, argv);

	if (!strncmp(argv[1], "tp", 2))
		return do_ddr_tp(&ddr, cmdtp, flag, argc, argv);

	return 0;
}

U_BOOT_CMD(ddr, 2, 0, do_ddr_cmd,
	"DDR sub-system commands\n",
	"status 	- read DDR status\n"
	"ddr tp 	- read DDR Timing Parameters\n"
	"ddr spd 	- read DDR SPD information\n"
	"ddr cal 	- read DDR calibration results\n");
#endif