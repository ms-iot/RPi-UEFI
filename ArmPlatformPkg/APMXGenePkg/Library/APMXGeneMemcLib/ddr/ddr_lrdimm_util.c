/**
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
 
#undef DEBUG
#include "ddr_lib.h"
#include "ddr_lrdimm_util.h"
#ifdef APM_VBIOS
#include <iolib/i2c/apm_i2c.h>
#elif defined(APM_TIANOCORE)
#else
#include <i2c.h> 
#endif

/* LRDIMM Debug Utilities - iMB/iSC Registers */
#undef LRDIMM_MB_UTIL_EXTRA
#undef IMB_GET_REGS
#undef IMB_GET_MCK_TRAINING_RESULTS
#undef IMB_GET_CK_TRAINING_RESULTS

static void imb_write_and_check(unsigned char i2c_address, 
		unsigned int reg, unsigned int data, unsigned bytes)
{
	unsigned int temp_var;
	imb_write(i2c_address, reg, data, bytes);
	temp_var = imb_read(i2c_address, reg, bytes);
	if (temp_var != data) {
		if (bytes == 1) 
			debug("#### iSC CSR - Write: Reg %04X = %02X, "
				"Read Back: %02X\n", reg, data, temp_var);
		else if (bytes == 2) 
			debug("#### iSC CSR - Write: Reg %04X = %04X, "
				"Read Back: %04X\n", reg, data, temp_var);
		else if (bytes == 4) 
			debug("#### iSC CSR - Write: Reg %04X = %08X, "
				"Read Back: %08X\n", reg, data, temp_var);
	}
}

unsigned int lrdimm_mb_init_from_spd_preinit(void *p, unsigned int slot)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int value = 0;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug("\nConfigure LRDIMM MB Registers Over SMBus @0x%02X - Pre-Init...\n",
								 i2c_address);
	
	debug("Host Isolation WA fpr CKE Powerdown\n");
	value = imb_read(i2c_address, 0x0C, 0x1);
	imb_write_and_check(i2c_address, 0x0C, (value & 0x7F), 1);

	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);	

	return 1;
}

unsigned int lrdimm_mb_init_from_spd_mck(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	lrdimm_smbus_t *mbreg;
	unsigned char i2c_address;
	unsigned int value = 0;
	unsigned int temp_var = 0;
	int i, index = LRDIMM_LOW_SPEED;
	dimm_params_t *pdimm;
	pdimm = &mcu->dimm_params[slot];
	mcu_param_t *mp = &mcu->mcu_params;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	mbreg = &mcu->lrdimm_mbreg;

	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug("\nConfigure LRDIMM MB Registers Over SMBus @0x%02X - MCK Section...\n",
								i2c_address);

	/* MCK SECTION OF INIT */
	debug("#### MCK Init Section ####\n");

	/* check context register */
	temp_var = imb_read(i2c_address, 0x02AC, 2);
	debug("Check context register: 0x2AC = %04X\n", temp_var);


	/* Set MCK multiplier */
	debug("Check/Set MCK multiplier\n");
	i = 0;
	temp_var = imb_read(i2c_address, 0x5076, 0x2);
	while ((temp_var & 0x0001) == 0) {
		i++;
		DELAY(1);
		temp_var = imb_read(i2c_address, 0x5076, 0x2);
	};
	debug("#### Reg 5076 = %04X after %d us\n", temp_var, i);

	/* Enable MCK shadow registers */
	debug("Enable MCK shadow registers\n");
	imb_write_and_check(i2c_address, 0x0FEE, 0x02, 1);
	temp_var = imb_read(i2c_address, 0x0FEE, 0x1);
	debug("#### Enable MSK Shadow Registers: Reg FEE = %02X\n", temp_var);

	value = 0xA0C2;
	imb_write_and_check(i2c_address, 0x08, value, 2); 	/* Set F0 RC3-RC0 */	

	value = 0x0000;
	imb_write_and_check(i2c_address, 0x0C, value, 2);	/* Set F0 RC11-RC8 */

	value = 0x00AA;
	/* Set F0 RC6: 0x4 = iMB evaluates DODT0 and DODT1 */
	if (pdimm->n_ranks > 1) value |= 0x0400;		
	imb_write_and_check(i2c_address, 0x0A, value, 2);	/* Set F0 RC6-4 */

	switch (pdimm->n_ranks) {
	case 1: value = 0x30;			/* 1 rank */
		break;
	case 2: value = 0x60;			/* 2 ranks */
		break;
	case 4: value = 0x90;			/* 4 ranks */
		break;
	case 8: value = 0xC0;			/* 8 ranks */
		break;
	default: debug("ERROR: %d ranks not supported\n", pdimm->n_ranks);
		break;
	}
	value |= ((pdimm->component_width & 0x8) | pdimm->mirrored_dimm) << 8;
	imb_write_and_check(i2c_address, 0x0E, value, 2); /* Set F0 RC15-RC12 */

	value = 0;
	switch (pdimm->n_col_addr) {
	case 10: value = 0x00;	/* 10 bits, CA[9:0] */
		break;
	case 11: value = 0x10;	/* 11 bits, CA[11, 9:0] */
		break;
	case 12: value = 0x20;	/* 12 bits, CA[13, 11, 9:0] */
		break;
	case 3: value = 0x30;	/* 8 addresses, CA[2:0] - test only */
		break;
	default: debug("ERROR: %d columns not supported\n", pdimm->n_col_addr);
		break;
	}
	debug("CSR 0x1A (F2RC5_4): %d-bit column supported\n", pdimm->n_col_addr);
	switch (pdimm->n_row_addr) {
	case 13: value |= 0x00;			/* 13 bits, RA[12:0] */
		break;
	case 14: value |= 0x40;			/* 14 bits, RA[13:0] */
		break;
	case 15: value |= 0x80;			/* 15 bits, RA[14:0] */
		break;
	case 16: value |= 0xc0;			/* 16 bits, RA[15:0] */
		break;
	default: debug("ERROR: %d rows not supported\n", pdimm->n_row_addr);
		break;
	}
	debug("CSR 0x1A (F2RC5_4): %d-bit row supported\n", pdimm->n_row_addr);
	/* Set F2 RC5-RC4 */
	imb_write_and_check(i2c_address, 0x1A, value, 1); 			

	value = 0x307;
	imb_write_and_check(i2c_address, 0x20, value, 2);

	value = 0x3011;
	/* Set F3 RC11-RC8 */
	imb_write_and_check(i2c_address, 0x24, value, 2);

	if (pdimm->n_ranks > 1) { /* if 2 ranks or more */
		value = 0x3011;
		/* Set F4 RC11-RC8 */
		imb_write_and_check(i2c_address, 0x2C, value, 2);	
	
		if (pdimm->n_ranks > 2) {  /* if 4 ranks or more */
			value = (mbreg->f5rc[5][index] << 8) | mbreg->f3rc[4][index];
		 	/* Set F5 RC11-RC8 */
			imb_write_and_check(i2c_address, 0x34, value, 2);

			value = (mbreg->f6rc[5][index] << 8) | mbreg->f3rc[4][index];
 			/* Set F6 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x3C, value, 1);

			if (pdimm->n_ranks > 4) { /* if 8 ranks */
				value = (mbreg->f7rc[5][index] << 8) | 
							mbreg->f3rc[4][index];
				/* Set F7 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x44, value, 1);

				value = (mbreg->f8rc[5][index] << 8) | 
					mbreg->f3rc[4][index];
				/* Set F8 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x4C, value, 1); 

				value = (mbreg->f9rc[5][index] << 8) | 
					mbreg->f3rc[4][index];
				/* Set F9 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x54, value, 1);

				value = (mbreg->f10rc[5][index] << 8) | 
					mbreg->f3rc[4][index];
				/* Set F10 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x5C, value, 1);

			} /* if 8 ranks */
			else {
				value = 0x0011;
				/* Set F7 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x44, value, 2);
				/* Set F8 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x4C, value, 2);
				/* Set F9 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x54, value, 2);
				/* Set F10 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x5C, value, 2);
			}
		} /* if 4 ranks or more */
		else {
			value = 0x0011;
			/* Set F5 RC11-RC8 */
			imb_write_and_check(i2c_address, 0x34, value, 2);
			/* Set F6 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x3C, value, 2);
			/* Set F7 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x44, value, 2);
			/* Set F8 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x4C, value, 2);
			/* Set F9 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x54, value, 2);
			/* Set F10 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x5C, value, 2);
		}
	} /* if 2 ranks or more */
	else {
		value = 0x0011;
		/* Set F4 RC11-RC8 */
		imb_write_and_check(i2c_address, 0x2C, value, 2);
		/* Set F5 RC11-RC8 */
		imb_write_and_check(i2c_address, 0x34, value, 2);
		/* Set F6 RC9-RC8 */
		imb_write_and_check(i2c_address, 0x3C, value, 2);
		/* Set F7 RC9-RC8 */
		imb_write_and_check(i2c_address, 0x44, value, 2);
		/* Set F8 RC9-RC8 */
		imb_write_and_check(i2c_address, 0x4C, value, 2);
		/* Set F9 RC9-RC8 */
		imb_write_and_check(i2c_address, 0x54, value, 2);
		/* Set F10 RC9-RC8 */
		imb_write_and_check(i2c_address, 0x5C, value, 2);
	}


	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);

	/* Rank 0 to 7 DRAM MR1/MR2 Setting */
	debug("iMB - MR1/MR2 Settings:\n");
	for (i=0;i<pdimm->n_ranks;i++) {		 	
		value = 0x00;
		if (i==0) {
			/* re-use MRS config from MCU side since they should match */
			/* Dynamic ODT, from MR2 - bit [1:0] of MR1/MR2 register */
			value |= (mp->mode_reg[2] & 0x0600) >> 3;
			/* RttNom, from MR1 - bit [4:2] of MR1/MR2 register */
			value |= (mp->mode_reg[1] & 0x0004) | 
				((mp->mode_reg[1] & 0x0040) >> 3) | 
				((mp->mode_reg[1] & 0x0200) >> 5);
			/* Out Driver Impedance Control, from MR1 - bit [7:6] of MR1/MR2 register */
			value |= ((mp->mode_reg[1] & 0x0002) >> 1) | 
				((mp->mode_reg[1] & 0x0020) >> 8);
		}

		debug("       Rank %d: MR1/MR2 = 0x%02X\n",i, value);
		debug("       Dynamic ODT: RttWr = %X\n", (value & 0xC0) >> 6);
		debug("       RttNom = %X\n", (value & 0x1C) >> 2);
		debug("       Output Driver Impedance = %X\n", (value & 0x03));

		imb_write_and_check(i2c_address, (0xB8 + i), value, 1);
	}

	debug("iMB - MRS Snooping Registers:\n");
	/* PPD = Slow Exit, Read Burst = Nibble Sequential => value in Storm */
	/* tWR = 6, bits [3:2] swapped => CL = 6 at 800Mbps, no interleave, precharge PD to default */
	value = LRDIMM_MR0_MCKCONFIG & 0x1FFF;
	debug("       MRS0 = %04X\n", value);
	/* Set MR0 snoop register */
	imb_write_and_check(i2c_address, 0xC8, value, 2);	

	/* re-use MRS config from MCU side since they should match */
	value = LRDIMM_MR1_MCKCONFIG & 0x1899;
	/* Set MR1 snoop register */
	imb_write_and_check(i2c_address, 0xCA, value, 2);	
	debug("       MRS1 = %04X\n", value);

	/* re-use MRS config from MCU side since they should match */
	value = LRDIMM_MR2_MCKCONFIG & 0x00FF;
	debug("       MRS2 = %04X\n", value);
	/* Set MR2 snoop register */
	imb_write_and_check(i2c_address, 0xCC, value, 2);	

	/* re-use MRS config from MCU side since they should match */
	value = LRDIMM_MR3_MCKCONFIG;
	debug("       MRS3 = %04X\n", value);
	/* Set MR3 snoop register */
	imb_write_and_check(i2c_address, 0xCE, value, 2);	

#ifdef IMB_GET_REGS
	/* Pring MCK config */
	printf("#### Print MCK Shadow Registers After MCK configuration\n");
	print_lrdimm_mb_regs(i2c_address);
#endif

	/* Disable MCK shadow registers - required only for MCK INIT SECTION */
	imb_write_and_check(i2c_address, 0x0FEE, 0x00, 1);

	return 1;
}

unsigned int lrdimm_mb_init_from_spd_ck(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	lrdimm_smbus_t *mbreg;
	unsigned char i2c_address;
	unsigned int value = 0;
	int i, index = LRDIMM_LOW_SPEED;
	dimm_params_t *pdimm;
	pdimm = &mcu->dimm_params[slot];
	mcu_param_t *mp = &mcu->mcu_params;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	mbreg = &mcu->lrdimm_mbreg;
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug("\nConfigure LRDIMM MB Registers Over SMBus @0x%02X - CK Section...\n",
								i2c_address);

	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);	

	if (mcu->mcu_params.speed > 1080) {
		index  = LRDIMM_HIGH_SPEED;
		debug("Using HIGH SPEED Setup (1333 and above)\n");
	} else {
		index = LRDIMM_LOW_SPEED;
		debug("Using LOW SPEED Setup (1066 and below)\n");
	}
	

	/* MEMORY BUFFER SECTION OF INIT */
	debug("#### CK Init Section ####\n");

	imb_write_and_check(i2c_address, 0x0FEE, 0x0, 0x1);
	value = imb_read(i2c_address, 0x0FEE, 0x1);
	debug("Make sure MCK Shadow registers are disabled: #### Reg FEE = %02X\n", value);

	value = 0x60C2;
	/* Set F0 RC3-RC0 */	
	imb_write_and_check(i2c_address, 0x08, value, 2); 	


	if (mcu->mcu_params.speed > 1600) value = 0x0400;
	else if (mcu->mcu_params.speed > 1334) value = 0x0300;
	else if (mcu->mcu_params.speed > 1067) value = 0x0200;
	else if (mcu->mcu_params.speed > 800) value = 0x0100;

	/* Force Voltage to 1.5V - F0RC11[1:0] = 00 */
	value &= 0xCFFF;
	/* Force Parity Off - F0RC11[3:2] = 00 */
	value &= 0x3FFF;
	/* Set F0 RC11-RC8 */
	imb_write_and_check(i2c_address, 0x0C, value, 2);	


	value = 0x0055;
	/* Set F0 RC6: 0x4 = iMB evaluates DODT0 and DODT1 */
	if (pdimm->n_ranks > 1) value |= 0x0400;		
	/* Set F0 RC6-4 */
	imb_write_and_check(i2c_address, 0x0A, value, 2);	


	switch (pdimm->n_ranks) {
	case 1: value = 0x30;			/* 1 rank */
		break;
	case 2: value = 0x60;			/* 2 ranks */
		break;
	case 4: value = 0x90;			/* 4 ranks */
		break;
	case 8: value = 0xC0;			/* 8 ranks */
		break;
	default: debug("ERROR: %d ranks not supported\n", pdimm->n_ranks);
		break;
	}
	value |= ((pdimm->component_width & 0x8) | pdimm->mirrored_dimm) << 8;
	/* Set F0 RC15-RC12 */
	imb_write_and_check(i2c_address, 0x0E, value, 2);

	imb_write_and_check(i2c_address, 0x19, 0x10, 1);

	value = 0;
	switch (pdimm->n_col_addr) {
	case 10: value = 0x00;	/* 10 bits, CA[9:0] */
		break;
	case 11: value = 0x10;	/* 11 bits, CA[11, 9:0] */
		break;
	case 12: value = 0x20;	/* 12 bits, CA[13, 11, 9:0] */
		break;
	case 3: value = 0x30;	/* 8 addresses, CA[2:0] - test only */
		break;
	default: debug("ERROR: %d columns not supported\n", pdimm->n_col_addr);
		break;
	}
	debug("CSR 0x1A (F2RC5_4): %d-bit column supported\n", pdimm->n_col_addr);
	switch (pdimm->n_row_addr) {
	case 13: value |= 0x00;			/* 13 bits, RA[12:0] */
		break;
	case 14: value |= 0x40;			/* 14 bits, RA[13:0] */
		break;
	case 15: value |= 0x80;			/* 15 bits, RA[14:0] */
		break;
	case 16: value |= 0xc0;			/* 16 bits, RA[15:0] */
		break;
	default: debug("ERROR: %d rows not supported\n", pdimm->n_row_addr);
		break;
	}
	debug("CSR 0x1A (F2RC5_4): %d-bit row supported\n", pdimm->n_row_addr);
	/* Set F2 RC5-RC4 */
	imb_write_and_check(i2c_address, 0x1A, value, 1); 

	value = 0x307;
	imb_write_and_check(i2c_address, 0x20, value, 2);

	value = 0x00;
	imb_write_and_check(i2c_address, 0x23, value, 1);

	value = 0x3011;
					/* Set F3 RC11-RC8 */
	imb_write_and_check(i2c_address, 0x24, value, 2);

	if (pdimm->n_ranks > 1) { /* if 2 ranks or more */
		value = 0x3011;
		/* Set F4 RC11-RC8 */
		imb_write_and_check(i2c_address, 0x2C, value, 2);	

		if (pdimm->n_ranks > 2) {  /* if 4 ranks or more */
			value = (mbreg->f5rc[5][index] << 8) | mbreg->f3rc[4][index];
			/* Set F5 RC11-RC8 */
			imb_write_and_check(i2c_address, 0x34, value, 2);

			value = (mbreg->f6rc[5][index] << 8) | mbreg->f3rc[4][index];
			/* Set F6 RC9-RC8 */
			imb_write_and_check(i2c_address, 0x3C, value, 1); 

			if (pdimm->n_ranks > 4) { /* if 8 ranks */
				value = (mbreg->f7rc[5][index] << 8) | mbreg->f3rc[4][index];
				/* Set F7 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x44, value, 1);

				value = (mbreg->f8rc[5][index] << 8) | mbreg->f3rc[4][index];
				/* Set F8 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x4C, value, 1); 

				value = (mbreg->f9rc[5][index] << 8) | mbreg->f3rc[4][index];
				/* Set F9 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x54, value, 1);

				value = (mbreg->f10rc[5][index] << 8) | mbreg->f3rc[4][index];
				/* Set F10 RC9-RC8 */
				imb_write_and_check(i2c_address, 0x5C, value, 1); 

			} 
		} 
	} 
	

	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);

	debug("iMB - MR1/MR2 Settings:\n");
	/* Rank 0 to 7 DRAM MR1/MR2 Setting	*/
	for (i=0;i<pdimm->n_ranks;i++) {	
		value = 0x00;
		if (i==0) {
			/* re-use MRS config from MCU side since they should match */
			/* Dynamic ODT, from MR2 - bit [1:0] of MR1/MR2 register */
			value |= (mp->mode_reg[2] & 0x0600) >> 3;
			/* RttNom, from MR1 - bit [4:2] of MR1/MR2 register */
			value |= (mp->mode_reg[1] & 0x0004) | 
				((mp->mode_reg[1] & 0x0040) >> 3) | 
				((mp->mode_reg[1] & 0x0200) >> 5);
			/* Output Driver Impedance Control, from MR1 - bit [7:6] of MR1/MR2 register */
			value |= ((mp->mode_reg[1] & 0x0002) >> 1) | 
				((mp->mode_reg[1] & 0x0020) >> 8);
		}

		debug("       Rank %d: MR1/MR2 = 0x%02X\n",i, value);
		debug("       Dynamic ODT: RttWr = %X\n", (value & 0xC0) >> 6);
		debug("       RttNom = %X\n", (value & 0x1C) >> 2);
		debug("       Output Driver Impedance = %X\n", (value & 0x03));

		imb_write_and_check(i2c_address, (0xB8 + i), value, 1);
	}



	debug("iMB - MRS Snooping Registers:\n");
	/* PPD = Slow Exit, Read Burst = Nibble Sequential => value in Storm */
	/* 
	 * re-use MRS config from MCU side since they should match 
	 * ---- Note: a bug in the iMB design has bits [3:2] swapped 
	 */
	value = ((mp->mode_reg[0] & 0x1EF3) | 
			((mp->mode_reg[0] & 0x0004) << 1) | 
			((mp->mode_reg[0] & 0x0008) >> 1));
	debug("       MRS0 = %04X\n", value);
	/* Set MR0 snoop register */
	imb_write_and_check(i2c_address, 0xC8, value, 2);

	/* re-use MRS config from MCU side since they should match */
	value = (mp->mode_reg[1] & 0x1D99);
	/* Set MR1 snoop register */
	imb_write_and_check(i2c_address, 0xCA, value, 2);	
	debug("       MRS1 = %04X\n", value);

	/* re-use MRS config from MCU side since they should match */
	value = (mp->mode_reg[2] & 0x01FF);
	debug("       MRS2 = %04X\n", value);
	/* Set MR2 snoop register */
	imb_write_and_check(i2c_address, 0xCC, value, 2);	

	/* re-use MRS config from MCU side since they should match */
	value = mp->mode_reg[3];
	debug("       MRS3 = %04X\n", value);
	/* Set MR3 snoop register */
	imb_write_and_check(i2c_address, 0xCE, value, 2);	

	/* Memory Buffer Workarounds */
	imb_write_and_check(i2c_address, 0x3012, 0xFF, 1);
	
	if (mcu->mcu_params.speed < 1600) 
		value = 0x01;
	else 
		value = 0x02;
	imb_write_and_check(i2c_address, 0x011E, value, 1);

	if (mcu->mcu_params.speed < 1600) 
		value = 0x07;
	else 
		value = 0x3F;
	imb_write_and_check(i2c_address, 0x0C00, value, 1);

#ifdef IMB_GET_REGS
	/* Pring CK config */
	printf("#### Print CK Standard Registers After Memory Buffer Workarounds\n");
	print_lrdimm_mb_regs(i2c_address);
#endif

	return 1;
}

#if defined(LRDIMM_MB_UTIL_EXTRA)
static unsigned int lrdimm_mb_set_mrs_snooping(void *p, unsigned int slot, 
					unsigned int mrs, unsigned value)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug("\nConfigure LRDIMM MB, MRS%d to %04X...\n",mrs, value);
	/* Set MRS snoop register */
	imb_write_and_check(i2c_address, 0xC8+(mrs*2), value, 2);	


	value = imb_read(i2c_address, 0x1C2, 2);
	debug("\nLRDIMM - 1C2 = %04X...\n", value);

	value &= 0xFFC0;
	value |= 0x0006;
	/* Set MR register to configure in DRAM */
	imb_write_and_check(i2c_address, 0x1C2, value, 2);	
	value |= 0x0001;
	imb_write_and_check(i2c_address, 0x1C2, value, 2);	/* Send config */

	return 1;
}

static unsigned int lrdimm_mb_get_mrs_snooping(void *p, unsigned int slot, 
				unsigned int mrs, unsigned value)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	/* read MRS snoop register */
	value = imb_read(i2c_address, 0xC8+(mrs*2), 2);	

	debug("Read LRDIMM MB, MRS%d = %04X...\n",mrs, value);

	return 1;
}

static void print_lrdimm_mb_training_results(unsigned char i2c_address, 
							unsigned int bdp)
{
	unsigned int temp_var = 0;

	temp_var = imb_read(i2c_address, 0x0210 + (bdp*0x100), 0x2);
	printf("%02X10 = 0x%04X\t\t(PI Control Fine DQS)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x0212 + (bdp*0x100), 0x2);
	printf("%02X12 = 0x%04X\t\t(PI Control Fine DQ)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x0216 + (bdp*0x100), 0x2);
	printf("%02X16 = 0x%04X\t\t(PI Control Coarse DQ/DQS)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x0218 + (bdp*0x100), 0x2);
	printf("%02X18 = 0x%04X\t\t(PI Control Slave)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x022c + (bdp*0x100), 0x2);
	printf("%02X2C = 0x%04X\t\t(WL Control/Status)\n", bdp+2, temp_var);
	if (temp_var & 0x6000) printf("#### ERROR In Fine Write Leveling ####\n");
	temp_var = imb_read(i2c_address, 0x0278 + (bdp*0x100), 0x2);
	printf("%02X78 = 0x%04X\t\t(WL Fine FSM Train Output)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x02a2 + (bdp*0x100), 0x2);
	printf("%02XA2 = 0x%04X\t\t(WL Coarse Status)\n", bdp+2, temp_var);
	if (temp_var & 0x2020) printf ("#### ERROR In Coarse Write Leveling ####\n");
	temp_var = imb_read(i2c_address, 0x021c + (bdp*0x100), 0x2);
	printf("%02X1C = 0x%04X\t\t(Read Trained Delay)\n", bdp+2, temp_var);
	temp_var = imb_read(i2c_address, 0x021e + (bdp*0x100), 0x2);
	printf("%02X1E = 0x%04X\t\t(Read Trained Delay)\n", bdp+2, temp_var);
	

	printf("\n");
}
	
static void print_lrdimm_mb_training(unsigned char i2c_address, 
						unsigned int context)
{
	unsigned int value = 0;
	unsigned int org_0E_value;
	unsigned int org_2AC_value;
	const char *prt[4];
	int i;
	int err = 0;
	
#if defined(DEBUG)
	int force_print = 1;
#else
	int force_print = 0;
#endif

	prt[0] = "CK";
	prt[2] = "MCK";
	prt[1] = "##### ##### Context 1 ##### #####";
	prt[3] = "##### ##### Context 3 ##### #####";

	printf("\n#### Print iSC NVDIMM %s Training Results ####\n", prt[context]);

	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);
	/* select training context */
	printf("\n#### Select training context = %d\n", context);
	org_0E_value = imb_read(i2c_address, 0x0E, 0x1);

	value = org_0E_value & 0xF7;	/* set bit 3 to 0 */
	value |= ((context & 0x1) << 3);
	imb_write_and_check(i2c_address, 0x0e, value, 1);

	org_2AC_value = imb_read(i2c_address, 0x2ac, 0x2);
	value = ((context & 0x2) << 14) | (org_2AC_value & 0x7FFF);
	imb_write_and_check(i2c_address, 0x02ac, value | 0x3, 2);

	printf("#### Training Context %d, before changing to %s - 0x0E =  "
			"%04X, 0x2AC =  %04X\n", context, prt[context], 
			org_0E_value, org_2AC_value);
	printf("#### %s Training Context Before Training - \t\t0x0E =  %04X, "
			"0x2AC =  %04X\n", prt[context], 
			imb_read(i2c_address, 0x0E, 0x2), 
			imb_read(i2c_address, 0x2ac, 0x2));

	printf("%s Training: checking leveling errors "
		"after switching to context %d\n", prt[context], context);
	/* Checking for leveling errors - WLF */
	value = imb_read(i2c_address, 0x02a2, 0x2);
	if ((value & 0x2020) != 0) {
		printf("%s Training: Detected WRITE LEVELING COARSE ERRORS"
				" - CSR 0x2A2 = 0x%04X\n", prt[context], value);
		err++;
	} else {
		printf("%s Training: No WLC Error\n", prt[context]);
	}
	
	/* Checking for leveling errors - WLC */
	value = imb_read(i2c_address, 0x022c, 0x1);
	if ((value & 0x6000) != 0) {
		printf("%s Training: Detected WRITE LEVELING FINE ERRORS"
				" - CSR 0x22C = 0x%04X\n", prt[context], value);
		err++;
	} else {
		printf("%s Training: No WLF Error\n", prt[context]);
	}
	
	if (err || force_print) {
		/* Print MCK Training Results */
		printf("\n%s Overall Training Results:\n", prt[context]);

		value = 0x0000;
		imb_write_and_check(i2c_address, 0x01c0, value, 2);
		printf("CSR 0x1C0 =%04X\n", value);

		print_lrdimm_mb_training_results(i2c_address, 0);

		for (i=0;i<9;i++) {
			printf("%s Individual Training Results: ", prt[context]);

			if (i==9) printf("RDP\n");
			else if (i==10) printf("TSR\n");
			else printf("BDP%d\n", i);

			value = 0xFDFF^(0x0001 << i);
			imb_write_and_check(i2c_address, 0x01c0, value, 2);
			printf("CSR 0x1C0 =%04X\n", value);

			print_lrdimm_mb_training_results(i2c_address, i);
		}	

		/* revert 0x1c0 to original setting */
		imb_write_and_check(i2c_address, 0x01c0, 0x0000, 2);
	}

	/* revert 0x0E to original setting */
	imb_write_and_check(i2c_address, 0x0e, org_0E_value, 1);
	imb_write_and_check(i2c_address, 0x02ac, org_2AC_value | 0x3, 2);
	printf("#### Training Context, Restored - \t\t0x0E =  %04X, 0x2AC =  %04X\n",
			imb_read(i2c_address, 0x0E, 0x2), 
			imb_read(i2c_address, 0x2ac, 0x2));
}
#endif

unsigned int lrdimm_mb_mck_training(void *p, unsigned int slot)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	dimm_params_t *pdimm;
	pdimm = &mcu->dimm_params[slot];
	int err = 0, i;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 0;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug1("\nStarting iSC NVDIMM MCK Training Over SMBus @0x%02X...\n",i2c_address);

	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);	

	/* Start Backup MCK Clock Training */
	debug("\n#########################################\n");
	debug("#### Start Backup MCK Clock Training ####\n");
	debug("#########################################\n\n");
	imb_write_and_check(i2c_address, 0x5018, 0xA710, 2);

	for (i=0;i<pdimm->n_ranks;i++) {
		DELAY(4000); /* wait 4ms per rank */
	}
	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);
	
	temp_var = imb_read(i2c_address, 0x5018, 0x2);
	if (temp_var != 0x2710) {
		debug1("Reg 0x5018 = %04X, expected %04X\n", temp_var, 0x2710);
		debug1("MCK Training Not Done Yet After 4ms - Keep Polling...\n");
		for (i=0;i<100;i++) {
			DELAY(1000); /* wait 1ms */
			temp_var = imb_read(i2c_address, 0x5018, 0x2);
			if (temp_var == 0x2710) {
				debug1("MCK Training Done after another %dms...\n",i);
				break;
			}
		}
		if (i>99) {
			debug1("MCK Training Not Done after another %dms...\n",i);
			err++;
		}
	} else {
		debug1("MCK Training Done...\n");
	}

#ifdef IMB_GET_MCK_TRAINING_RESULTS
	/* Print Training Results */
	print_lrdimm_mb_training(i2c_address, 2);
#endif

	return (err)? 0 : 1; 
}

unsigned int lrdimm_mb_ck_training(void *p, unsigned int slot)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	unsigned int value = 0;
	int i;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug1("\nConfigure LRDIMM MB, Start MB to DRAM Training...\n");
	/* Memory Buffer Init */
	debug("Enable Inphi proprietary CSR access\n");
	imb_write_and_check(i2c_address, 0x78, 0x0B, 1);

	/* Now, start training */
	temp_var = imb_read(i2c_address, 0x0E, 0x1);
	value = (temp_var & 0xF8) | 0x02;
	imb_write_and_check(i2c_address, 0x0E, value, 1);

	debug1("\n###########################\n");
	debug1("#### Start CK Training ####\n");
	debug1("###########################\n\n");
	temp_var = imb_read(i2c_address, 0x0E, 0x1);
	debug1("Training Started: Reg 0E = %02X, expected %02X\n", temp_var, value);

	for (i=0;i<200;i++) {
		DELAY(1000); /* wait 1ms between polling */
		/* read F2RC3_2 for training status */
		temp_var = imb_read(i2c_address, 0x19, 0x1);	
		temp_var &= 0x60;
		if (temp_var == 0x40) {
			debug1("STATUS: MB to DRAM Training Successful - F2RC3"
						" = %01x\n", (temp_var >> 4));

#ifdef IMB_GET_CK_TRAINING_RESULTS
			/* Print Training Results */
			print_lrdimm_mb_training(i2c_address, 0);
#endif
			return 1;			/* training successful */
		} else if (temp_var == 0x20) {
			debug1("ERROR: MB to DRAM Training Failed - F2RC3 "
						"= %01x\n", (temp_var >> 4));

#ifdef IMB_GET_CK_TRAINING_RESULTS
			/* Print Training Results */
			print_lrdimm_mb_training(i2c_address, context);
#endif
			return 0;			/* Training Failed */
		}
	}

	/* loop finished, then training timed out */
	debug1("ERROR: MB to DRAM Training Timed Out - F2RC3 = %01x\n", 
							(temp_var >> 4));

#ifdef IMB_GET_CK_TRAINING_RESULTS
	/* Print Training Results */
	print_lrdimm_mb_training(i2c_address, context);
#endif

	return 0;
}


unsigned int lrdimm_mb_WRleveling(void *p, unsigned int slot)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	unsigned int value = 0;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug1("\nConfigure LRDIMM MB, Enable DQ interface for Host Write Leveling...\n");

	temp_var = imb_read(i2c_address, 0x0E, 0x1);
	value = (temp_var & 0xF8) | 0x01;
	imb_write_and_check(i2c_address, 0x0E, value, 1);

	return 0;
}


unsigned int lrdimm_mb_normal_op(void *p, unsigned int slot)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	unsigned int value = 0;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	debug1("\nConfigure LRDIMM MB, Resume Normal Operations...\n");

	/* Now, start training */
	temp_var = imb_read(i2c_address, 0x0E, 0x1);
	value = (temp_var & 0xF8);
	imb_write_and_check(i2c_address, 0x0E, value, 1);

	DELAY(10000); /* wait 10ms */

	return 0;
}

#if defined(LRDIMM_MB_UTIL_EXTRA)
static unsigned int get_lrdimm_mb(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	lrdimm_smbus_t *mbreg;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	unsigned int value = 0;
	int i, j, index, offset;

#ifndef IMB_GET_REGS
	return 1;
#endif

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	mbreg = &mcu->lrdimm_mbreg;

	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	printf("\nLRDIMM MB Registers Over SMBus @0x%02X...\n",i2c_address);

	if (mcu->mcu_params.speed > 1080) {
		index  = LRDIMM_HIGH_SPEED;
		printf("Using HIGH SPEED Setup (1333 and above)\n");
	} else {
		index = LRDIMM_LOW_SPEED;
		printf("Using LOW SPEED Setup (1066 and below)\n");
	}
	
	
	printf("\n Source:                \tiMB \tSPD \n");
	for (i=0;i<16;i++) {
		for (j=0;j<8;j++) {
			offset = ((i+1)*8)+j;
			
			switch(i) {
			case 0: 
				value = mbreg->f0rc[j][index]; 
				break;
			case 1: 
				value = mbreg->f1rc[j][index]; 
				break;
			case 2: 
				value = mbreg->f2rc[j][index]; 
				break;
			case 3: 
				value = mbreg->f3rc[j][index]; 
				break;
			case 4: 
				value = mbreg->f4rc[j][index]; 
				break;
			case 5: 
				value = mbreg->f5rc[j][index]; 
				break;
			case 6: 
				value = mbreg->f6rc[j][index]; 
				break;
			case 7: 
				value = mbreg->f7rc[j][index]; 
				break;
			case 8: 
				value = mbreg->f8rc[j][index]; 
				break;
			case 9: 
				value = mbreg->f9rc[j][index]; 
				break;
			case 10:
				value = mbreg->f10rc[j][index]; 
				break;
			case 11: 
				value = mbreg->f11rc[j][index]; 
				break;
			case 12: 
				value = mbreg->f12rc[j][index]; 
				break;
			case 13: 
				value = mbreg->f13rc[j][index]; 
				break;
			case 14: 
				value = mbreg->f14rc[j][index]; 
				break;
			case 15: 
				value = mbreg->f15rc[j][index]; 
				break;
			}
	
			temp_var = imb_read(i2c_address, offset, 0x1);
			printf(" At Offset %02X, F%dRC%d_%d: \t0x%02X\t0x%02X",
					offset,i,j*2+1,j*2,temp_var,value);
			if (temp_var != value) 
				printf("\t-> NO MATCH");
			printf("\n");
		}
	}

	printf("\n Source: MRregisters and Snoop\n");
	offset = 0x00B8;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BA;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BC;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BE;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);

	offset = 0x00C8;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CA;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CC;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CE;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);

	printf("\n Source: Extended Regs\n");
	offset = 0x5076;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x0FEE;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x3012;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x011E;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x0C00;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x5018;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x02AC;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x022C;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x02A2;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);

	temp_var = imb_read(i2c_address, 0x08, 0x1);
	printf("#### Reg 08 = %02X, expected 0xC2\n", temp_var);

	printf("\n");
	return 1;
}

static unsigned int get_lrdimm_mb_MRSsnoop(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	unsigned int temp_var = 0;
	int offset;

#ifndef IMB_GET_REGS
	return 1;
#endif

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	printf("\nLRDIMM MB Registers Over SMBus @0x%02X...\n",i2c_address);
	printf("\n Source: MRregisters and Snoop\n");
	offset = 0x00B8;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BA;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BC;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00BE;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);

	offset = 0x00C8;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CA;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CC;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);
	offset = 0x00CE;
	temp_var = imb_read(i2c_address, offset, 0x2);
	printf("Offset %04X = 0x%04X\n",offset,temp_var);

	printf("\n");
	return 1;
}

static unsigned int print_lrdimm_mb(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned char i2c_address;
	int i, j, k, offset, value;

	if (slot) {
		printf("LRDIMM Memory Buffer: supported only in slot 0\n");
		return 1;
	}
	
	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send command to MUX");
			return 0;
		}
	}

	i2c_address = (mcu->spd_addr[slot] & 0x07)| 0x58;

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	printf("\nLRDIMM MB Registers Register Dump @0x%02X...\n",i2c_address);

	for (k=0;k<4;k++) {
		printf("\nByte offset: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07"
				" 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F\n");
		for (i=0;i<16;i++) {
			printf("      0x%01X%01X0:",k,i);
			for (j=0;j<16;j++) {
				offset = (k*0x100) + (i*0x10) + j;
				value = imb_read(i2c_address, offset, 0x1);
				printf(" 0x%02X",value);
			}
			printf("\n");
		}
	}

	printf("\n");
	return 1;
}
#endif

#ifdef IMB_GET_REGS
static unsigned int print_lrdimm_mb_regs(unsigned char i2c_address)
{
	int i, j, k, offset, value;

	printf("\nLRDIMM MB Registers Register Dump...\n");

	for (k = 0; k < 1; k++) {
		printf("\nByte offset: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07"
				" 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F\n");
		for (i= 0; i < 16; i++) {
			printf("      0x%01X%01X0:",k,i);
			for (j = 0; j < 16; j++) {
				offset = (k*0x100) + (i*0x10) + j;
				value = imb_read(i2c_address, offset, 0x1);
				printf(" 0x%02X",value);
			}
			printf("\n");
		}
	}

	printf("\n");
	return 1;
}
#endif

