/** @file
*  Header file supporting the SMC call on ARM Platforms
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

#ifndef __SMC_H__
#define __SMC_H__

#include <Platform/ArmPlatform.h>

/* Boot Device */
#define SDMMC_CH2			0x0
#define SDMMC_CH0			0x4
#define EMMC				0x14

/* SMC call define */
#define SMC_CMD_INIT            (-1)
#define SMC_CMD_INFO            (-2)
/* For Power Management */
#define SMC_CMD_SLEEP           (-3)
#define SMC_CMD_CPU1BOOT        (-4)
#define SMC_CMD_CPU0AFTR        (-5)
/* For CP15 Access */
#define SMC_CMD_C15RESUME       (-11)
/* For L2 Cache Access */
#define SMC_CMD_L2X0CTRL        (-21)
#define SMC_CMD_L2X0SETUP1      (-22)
#define SMC_CMD_L2X0SETUP2      (-23)
#define SMC_CMD_L2X0INVALL      (-24)
#define SMC_CMD_L2X0DEBUG       (-25)

/* For Accessing CP15/SFR (General) */
#define SMC_CMD_REG             (-101)

/* MACRO for SMC_CMD_REG */
#define SMC_REG_CLASS_CP15      (0x0 << 30)
#define SMC_REG_CLASS_SFR_W     (0x1 << 30)
#define SMC_REG_CLASS_SFR_R     (0x3 << 30)
#define SMC_REG_CLASS_MASK      (0x3 << 30)
#define SMC_REG_ID_CP15(CRn, Op1, CRm, Op2) \
           (SMC_REG_CLASS_CP15 | \
            ((CRn) << 10) | ((Op1) << 7) | ((CRm) << 3) | (Op2))
#define SMC_REG_ID_SFR_W(ADDR)  (SMC_REG_CLASS_SFR_W | ((ADDR) >> 2))
#define SMC_REG_ID_SFR_R(ADDR)  (SMC_REG_CLASS_SFR_R | ((ADDR) >> 2))

void load_uefi_image(UINT32 boot_device);
void coldboot(UINT32 boot_device, UINT32 JumpAddress);
UINT32 exynos_smc(UINT32 cmd, UINT32 arg1, UINT32 arg2, UINT32 arg3);

#endif /* __SMC_H__ */
