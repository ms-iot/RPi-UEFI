/** @file
*  Main file supporting the SMC call on ARM Platforms
*
*  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
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

#include "Smc.h"

#define SMC_CMD_LOAD_UEFI		(-230)
#define SMC_CMD_COLDBOOT		(-231)
#define SMC_CMD_WARMBOOT		(-232)

#define SIGNATURE_SIZE			0

#define MOVI_BLKSIZE			(1 << 9)
#define PART_SIZE_UEFI			(2560 * 1024)
#define PART_SIZE_TZSW			(156 * 1024)
#define MOVI_UEFI_BLKCNT		(PART_SIZE_UEFI / MOVI_BLKSIZE)
#define MOVI_TZSW_BLKCNT		(PART_SIZE_TZSW / MOVI_BLKSIZE)

typedef struct sdmmc_dev {
	/* for SDMMC */
	UINT32	image_pos;
	UINT32	blkcnt;
	UINT32	base_addr;
} sdmmc_t;

typedef struct emmc_dev {
	/* for eMMC */
	UINT32	blkcnt;
	UINT32	base_addr;
} emmc_t;

/* boot device */
typedef union boot_device_u {
	sdmmc_t		sdmmc;
	emmc_t		emmc;
} boot_device_t;

typedef struct ld_image_info {
	UINT32	image_base_addr;
	UINT32	size;
	UINT32	secure_context_base;
	UINT32	signature_size;
	boot_device_t bootdev;
} image_info;	

UINT32 exynos_smc(UINT32 cmd, UINT32 arg1, UINT32 arg2, UINT32 arg3)
{
	register UINT32 reg0 __asm__("r0") = cmd;
	register UINT32 reg1 __asm__("r1") = arg1;
	register UINT32 reg2 __asm__("r2") = arg2;
	register UINT32 reg3 __asm__("r3") = arg3;

	__asm__ volatile (
		".arch_extension sec\n"
		"smc	0\n"
		: "+r"(reg0), "+r"(reg1), "+r"(reg2), "+r"(reg3)

	);

	return reg0;
}

void load_uefi_image(UINT32 boot_device)
{
	image_info *info_image;

	info_image = (image_info *) CONFIG_IMAGE_INFO_BASE;

	if (boot_device == EMMC) {
		info_image->bootdev.emmc.blkcnt = MOVI_UEFI_BLKCNT;
		info_image->bootdev.emmc.base_addr = CONFIG_PHY_UEFI_BASE;
	}

	info_image->image_base_addr = CONFIG_PHY_UEFI_BASE;
	info_image->size = (MOVI_UEFI_BLKCNT * MOVI_BLKSIZE);
	info_image->secure_context_base = CONFIG_SECURE_CONTEXT_BASE;
	info_image->signature_size = SIGNATURE_SIZE;

	exynos_smc(SMC_CMD_LOAD_UEFI, boot_device, CONFIG_IMAGE_INFO_BASE, 0);
}

void coldboot(UINT32 boot_device, UINT32 JumpAddress)
{
	image_info *info_image;

	info_image = (image_info *) CONFIG_IMAGE_INFO_BASE;

	if (boot_device == EMMC) {
		info_image->bootdev.emmc.blkcnt = MOVI_TZSW_BLKCNT;
		info_image->bootdev.emmc.base_addr = CONFIG_PHY_TZSW_BASE;
	}

	info_image->image_base_addr = CONFIG_PHY_TZSW_BASE;
	info_image->size = (MOVI_TZSW_BLKCNT * MOVI_BLKSIZE);
	info_image->secure_context_base = CONFIG_SECURE_CONTEXT_BASE;
	info_image->signature_size = SIGNATURE_SIZE;

	exynos_smc(SMC_CMD_COLDBOOT, boot_device, CONFIG_IMAGE_INFO_BASE, JumpAddress);
}
