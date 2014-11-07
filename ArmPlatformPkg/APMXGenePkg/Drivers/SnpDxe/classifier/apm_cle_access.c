/**
 * AppliedMicro APM88xxxx SoC Classifier Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Mahesh Pujara <mpujara@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * @file apm_cle_access.c
 *
 * This file implements access layer for APM88xxxx SoC Classifier driver
 *
 */

#ifndef APM_XGENE
#include <misc/xgene/cle/apm_preclass_data.h>
#include <asm/io.h>
#else
#include "apm_cle_access.h"
#include "apm_preclass_data.h"
#endif

u64 apm_class_base_addr_p[MAX_CLE_ENGINE];
void *apm_class_base_addr[MAX_CLE_ENGINE];

int apm_gbl_cle_rd32(u32 cid, u32 reg_offset, u32  *value)
{
	void *addr;

#ifdef CLE_DBG	   
	if (value == NULL) {
		PCLS_DBG("Error: Null value pointer in calling %a \n",
			__FUNCTION__);
		return APM_RC_INVALID_PARM;
	}
#endif
	addr = apm_class_base_addr[cid] + reg_offset;
	*value = readl((u64)addr);

	PCLS_DBG("CLE CSR Read at addr 0x%0llX value 0x%08X \n", (unsigned long long)addr, *value);
	return APM_RC_OK;
}

int apm_gbl_cle_wr32(u32 cid, u32 reg_offset, u32 value)
{
	void *addr;

	addr = apm_class_base_addr[cid] + reg_offset;

	PCLS_DBG("CLE CSR Write at addr 0x%0llX value 0x%08X \n", (unsigned long long)addr, value);
	writel(value, (u64)addr);
	return APM_RC_OK;
}
