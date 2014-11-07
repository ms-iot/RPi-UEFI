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

#ifndef __APM_XGENE_REGDUMP_H
#define __APM_XGENE_REGDUMP_H

#define APMXGENE_GET_SYSREG(reg, val) \
	asm  volatile ("mrs %0, " #reg "" : "=r"(val) : :) 
				                
#define APMXGENE_PRINT_SYSREG(reg,val,desc)  \
	APMXGENE_GET_SYSREG(reg, val); \
	DEBUG((EFI_D_WARN, "%15a : 0x%016lX :: %a\n", #reg , val, desc));  \
	ASSERT(1);

#endif

