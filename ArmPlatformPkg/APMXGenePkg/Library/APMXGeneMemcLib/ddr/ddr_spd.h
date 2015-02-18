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

#ifndef _DDR_SPD_H_
#define _DDR_SPD_H_

/*
 * Format from "JEDEC Standard No. 21-C,
 * Appendix D: Rev 1.0: SPD's for DDR SDRAM
 */
typedef struct ddr3_spd_eeprom_s {
	/* General Section: Bytes 0-59 */
	unsigned char info_size_crc;	/* 0 # bytes written into serial memory,
					     CRC coverage */
	unsigned char spd_rev;		/* 1 Total # bytes of SPD mem device */
	unsigned char mem_type;		/* 2 Key Byte / Fundamental mem type */
	unsigned char module_type;	/* 3 Key Byte / Module Type */
	unsigned char density_banks;	/* 4 SDRAM Density and Banks */
	unsigned char addressing;	/* 5 SDRAM Addressing */
	unsigned char module_vdd;	/* 6 Module nominal voltage, VDD */
	unsigned char organization;	/* 7 Module Organization */
	unsigned char bus_width;	/* 8 Module Memory Bus Width */
	unsigned char ftb_div;		/* 9 Fine Timebase (FTB)
				    	     Dividend / Divisor */
	unsigned char mtb_dividend;	/* 10 Medium Timebase (MTB) Dividend */
	unsigned char mtb_divisor;	/* 11 Medium Timebase (MTB) Divisor */
	unsigned char tCK_min;		/* 12 SDRAM Minimum Cycle Time */
	unsigned char res_13;		/* 13 Reserved */
	unsigned char caslat_lsb;	/* 14 CAS Latencies Supported,
					      Least Significant Byte */
	unsigned char caslat_msb;	/* 15 CAS Latencies Supported,
					      Most Significant Byte */
	unsigned char tAA_min;		/* 16 Min CAS Latency Time */
	unsigned char tWR_min;		/* 17 Min Write REcovery Time */
	unsigned char tRCD_min;		/* 18 Min RAS# to CAS# Delay Time */
	unsigned char tRRD_min;		/* 19 Min Row Active to
				   	      Row Active Delay Time */
	unsigned char tRP_min;		/* 20 Min Row Precharge Delay Time */
	unsigned char tRAS_tRC_ext;	/* 21 Upper Nibbles for tRAS and tRC */
	unsigned char tRAS_min_lsb;	/* 22 Min Active to Precharge
					      Delay Time */
	unsigned char tRC_min_lsb;	/* 23 Min Active to Active/Refresh
					      Delay Time, LSB */
	unsigned char tRFC_min_lsb;	/* 24 Min Refresh Recovery Delay Time */
	unsigned char tRFC_min_msb;	/* 25 Min Refresh Recovery Delay Time */
	unsigned char tWTR_min;		/* 26 Min Internal Write to
				   	      Read Command Delay Time */
	unsigned char tRTP_min;		/* 27 Min Internal Read to Precharge
				   	      Command Delay Time */
	unsigned char tFAW_msb;		/* 28 Upper Nibble for tFAW */
	unsigned char tFAW_min;		/* 29 Min Four Activate Window
				   	      Delay Time */
	unsigned char opt_features;	/* 30 SDRAM Optional Features */
	unsigned char therm_ref_opt;	/* 31 SDRAM Thermal and Refresh Opts */
	unsigned char res_32_59[28];	/* 32-59 Reserved, General Section */

	/* Module-Specific Section: Bytes 60-116 */
	union {
		struct {
			/* 60 (Unbuffered) Module Nominal Height */
			unsigned char mod_height;
			/* 61 (Unbuffered) Module Maximum Thickness */
			unsigned char mod_thickness;
			/* 62 (Unbuffered) Reference Raw Card Used */
			unsigned char ref_raw_card;
			/* 63 (Unbuffered) Address Mapping from
			   Edge Connector to DRAM */
			unsigned char addr_mapping;
			/* 64-116 (Unbuffered) Reserved */
			unsigned char res_64_116[53];
		} unbuffered;
		struct {
			/* 60 (Registered) Module Nominal Height */
			unsigned char mod_height;
			/* 61 (Registered) Module Maximum Thickness */
			unsigned char mod_thickness;
			/* 62 (Registered) Reference Raw Card Used */
			unsigned char ref_raw_card;
		} registered;
		unsigned char uc[57];
	} mod_section;

	/* Unique Module ID: Bytes 117-125 */
	unsigned char mmid_lsb;		/* 117 Module MfgID Code LSB - JEP-106 */
	unsigned char mmid_msb;		/* 118 Module MfgID Code MSB - JEP-106 */
	unsigned char mloc;		/* 119 Mfg Location */
	unsigned char mdate[2];		/* 120-121 Mfg Date */
	unsigned char sernum[4];	/* 122-125 Module Serial Number */

	/* CRC: Bytes 126-127 */
	unsigned char crc[2];		/* 126-127 SPD CRC */

	/* Other Manufacturer Fields and User Space: Bytes 128-255 */
	unsigned char mpart[18];	/* 128-145 Mfg's Module Part Number */
	unsigned char mrev[2];		/* 146-147 Module Revision Code */

	unsigned char dmid_lsb;		/* 148 DRAM MfgID Code LSB - JEP-106 */
	unsigned char dmid_msb;		/* 149 DRAM MfgID Code MSB - JEP-106 */

	unsigned char msd[26];		/* 150-175 Mfg's Specific Data */
	unsigned char cust[80];		/* 176-255 Open for Customer Use */

} spd_eeprom_t;

unsigned int spd_check(spd_eeprom_t * spd);
unsigned long long compute_ranksize(spd_eeprom_t * spd);
unsigned int compute_dimm_parameters(void *, unsigned int dimm_number);
unsigned int compute_timing_params(void *);
unsigned int compute_cas_latency(void *);
unsigned int rdiv(unsigned int a, unsigned int b);
unsigned int compute_cas_write_latency(void *);
unsigned int get_memory_clk_period_ps(void *);

typedef struct lrdimm_smbus_s {
	unsigned char vid_low;			/*  00 Vendor ID [7:0] */
	unsigned char vid_high;			/*  01 Vendor ID [15:8] */
	unsigned char did_low;			/*  02 Device ID [7:0] */
	unsigned char did_high;			/*  03 Device ID [15:8] */
	unsigned char rid;			/*  04 Revision ID [7:0] */

	unsigned char attributes;		/*  Module Attributes (from SPD) */
	
	unsigned char min_delay_1V5;		/* min delay time for 1.5V */
	unsigned char max_delay_1V5;		/* min delay time for 1.5V */
	unsigned char min_delay_1V35;		/* min delay time for 1.35V */
	unsigned char max_delay_1V35;		/* min delay time for 1.35V */

	/* MR1,2 */
	unsigned char mr1_mr2[2];

	/* Registers F0RC1/0 to F0RC15/14 */
	unsigned char f0rc[8][2];		/*  08 to 0F [7:4] = F0RCnn+1, [3:0] = F0RCnn */
	/* Registers F1RC1/0 to F1RC15/14 */
	unsigned char f1rc[8][2];		/*  10 to 17 [7:4] = F1RCnn+1, [3:0] = F1RCnn */
	/* Registers F2RC1/0 to F2RC15/14 */
	unsigned char f2rc[8][2];		/*  18 to 1F [7:4] = F2RCnn+1, [3:0] = F2RCnn */
	/* Registers F3RC1/0 to F3RC15/14 */
	unsigned char f3rc[8][2];		/*  20 to 27 [7:4] = F3RCnn+1, [3:0] = F3RCnn */
	/* Registers F4RC1/0 to F4RC15/14 */
	unsigned char f4rc[8][2];		/*  28 to 2F [7:4] = F4RCnn+1, [3:0] = F4RCnn */
	/* Registers F5RC1/0 to F5RC15/14 */
	unsigned char f5rc[8][2];		/*  30 to 37 [7:4] = F5RCnn+1, [3:0] = F5RCnn */
	/* Registers F6RC1/0 to F6RC15/14 */
	unsigned char f6rc[8][2];		/*  38 to 3F [7:4] = F6RCnn+1, [3:0] = F6RCnn */
	/* Registers F7RC1/0 to F7RC15/14 */
	unsigned char f7rc[8][2];		/*  40 to 47 [7:4] = F7RCnn+1, [3:0] = F7RCnn */
	/* Registers F8RC1/0 to F8RC15/14 */
	unsigned char f8rc[8][2];		/*  48 to 4F [7:4] = F8RCnn+1, [3:0] = F8RCnn */
	/* Registers F9RC1/0 to F9RC15/14 */
	unsigned char f9rc[8][2];		/*  50 to 57 [7:4] = F9RCnn+1, [3:0] = F9RCnn */
	/* Registers F10RC1/0 to F10RC15/14 */
	unsigned char f10rc[8][2];		/*  58 to 5F [7:4] = F10RCnn+1, [3:0] = F10RCnn */
	/* Registers F11RC1/0 to F11RC15/14 */
	unsigned char f11rc[8][2];		/*  60 to 67 [7:4] = F11RCnn+1, [3:0] = F11RCnn */
	/* Registers F12RC1/0 to F12RC15/14 */
	unsigned char f12rc[8][2];		/*  68 to 6F [7:4] = F12RCnn+1, [3:0] = F12RCnn */
	/* Registers F13RC1/0 to F13RC15/14 */
	unsigned char f13rc[8][2];		/*  70 to 77 [7:4] = F13RCnn+1, [3:0] = F13RCnn */
	/* Registers F14RC1/0 to F14RC15/14 */
	unsigned char f14rc[8][2];		/*  78 to 7F [7:4] = F14RCnn+1, [3:0] = F14RCnn */
	/* Registers F15RC1/0 to F15RC15/14 */
	unsigned char f15rc[8][2];		/*  80 to 87 [7:4] = F15RCnn+1, [3:0] = F15RCnn */
	
} lrdimm_smbus_t;

/*
 * Byte 2 Fundamental Memory Types.
 */
#define SPD_MEMTYPE_FPM			(0x01)
#define SPD_MEMTYPE_EDO			(0x02)
#define SPD_MEMTYPE_PIPE_NIBBLE		(0x03)
#define SPD_MEMTYPE_SDRAM		(0x04)
#define SPD_MEMTYPE_ROM			(0x05)
#define SPD_MEMTYPE_SGRAM		(0x06)
#define SPD_MEMTYPE_DDR			(0x07)
#define SPD_MEMTYPE_DDR2		(0x08)
#define SPD_MEMTYPE_DDR2_FBDIMM		(0x09)
#define SPD_MEMTYPE_DDR2_FBDIMM_PROBE	(0x0A)
#define SPD_MEMTYPE_DDR3		(0x0B)

/*
 * Byte 3 Key Byte / Module Type for DDR3 SPD
 */
#define SPD_MODULETYPE_RDIMM		(0x01)
#define SPD_MODULETYPE_UDIMM		(0x02)
#define SPD_MODULETYPE_SODIMM		(0x03)
#define SPD_MODULETYPE_MICRODIMM	(0x04)
#define SPD_MODULETYPE_MINIRDIMM	(0x05)
#define SPD_MODULETYPE_MINIUDIMM	(0x06)
#define SPD_MODULETYPE_LRDIMM           (0x0B)

#endif /* _DDR_SPD_H_ */
