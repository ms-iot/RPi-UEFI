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
#ifndef __APM_XGENE_H
#define __APM_XGENE_H

#ifdef APM_XGENE_GFC_FLASH
#define APM_XGENE_NOR0_BASE 		0x0           	/* NOR FLASH      */
#define APM_XGENE_SYS_FLASH_LEN        	(64 << 20)	/* Flash size */
#define APM_XGENE_GFC_BASE    		0x17010000  	/* GFC */
#define APM_XGENE_SYS_FLASH_CFI_WIDTH   2    		/* 16 bit */
#define APM_XGENE_SYS_MAX_FLASH_SECT    (4+254+4)

#ifndef __ASSEMBLY__
extern void apmXGeneRegDump(void);
#endif
#endif
#endif

