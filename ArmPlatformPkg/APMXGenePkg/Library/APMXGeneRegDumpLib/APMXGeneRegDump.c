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

#include "APMXGeneRegDump.h"
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <ArmPlatform.h>

void apmXGeneRegDump(void)
{
	UINT64 val = 0;
	APMXGENE_PRINT_SYSREG( MIDR_EL1, val,       " Main ID Register                               " );
	APMXGENE_PRINT_SYSREG( CTR_EL0, val,        " Cache Type Register                            " );
	APMXGENE_PRINT_SYSREG( MPIDR_EL1, val,      " Multiprocessor Affinity Register               " );
	APMXGENE_PRINT_SYSREG( DCZID_EL0, val,      " Data Cache Zero ID Register                    " );
	APMXGENE_PRINT_SYSREG( CCSIDR_EL1, val,     " Cache side ID Register                         " );
	APMXGENE_PRINT_SYSREG( CLIDR_EL1, val,      " Cache Level ID Register                        " );
	APMXGENE_PRINT_SYSREG( CSSELR_EL1, val,     " Cache Size Selection Register                  " );
	APMXGENE_PRINT_SYSREG( REVIDR_EL1, val,     " Revision ID Register                           " );
	APMXGENE_PRINT_SYSREG( AIDR_EL1, val,       " Auxilary ID Register                           " );
	APMXGENE_PRINT_SYSREG( SCTLR_EL1, val,      " System Control Register                        " );
	APMXGENE_PRINT_SYSREG( ACTLR_EL1, val,      " Auxilary Control Register                      " );
	APMXGENE_PRINT_SYSREG( CPACR_EL1, val,      " Coprocessor Access Control Register            " );
	APMXGENE_PRINT_SYSREG( TTBR0_EL1, val,      " Translation Table Base Register 0              " );
	APMXGENE_PRINT_SYSREG( TTBR1_EL1, val,      " Translation Table Base Register 1              " );
	APMXGENE_PRINT_SYSREG( TCR_EL1, val,        " Translation Control Register                   " );
	APMXGENE_PRINT_SYSREG( AFSR0_EL1, val,      " Auxilary Fault Status Register                 " );
	APMXGENE_PRINT_SYSREG( AFSR1_EL1, val,      " Auxilary Fault Status Register                 " );
	APMXGENE_PRINT_SYSREG( ESR_EL1, val,        " Exception Syndrome Register                    " );
	APMXGENE_PRINT_SYSREG( FAR_EL1, val,        " Fault Address Register                         " );
//	APMXGENE_PRINT_SYSREG( HPFAR_EL1, val,      " Hyp IPA Fault Address Register                 " );
//	APMXGENE_PRINT_SYSREG( PAR_EL1, val,        " Physical Address Register                      " );
	APMXGENE_PRINT_SYSREG( MAIR_EL1, val,       " Memory Attribute Indirection Register          " );
	APMXGENE_PRINT_SYSREG( AMAIR_EL1, val,      " Auxilary Memory Attribute Indirection Register " );
	APMXGENE_PRINT_SYSREG( VBAR_EL1, val,       " Vector Base Address Register                   " );
//	APMXGENE_PRINT_SYSREG( RVBAR_EL1, val,      " Reset Vector Base Address Register             " );
//	APMXGENE_PRINT_SYSREG( RMR_EL1, val,        " Reset Management Register                      " );
	APMXGENE_PRINT_SYSREG( ISR_EL1, val,        " Interrupt Status Register                      " );
	APMXGENE_PRINT_SYSREG( CONTEXTIDR_EL1, val, " Context ID Register                            " );
	APMXGENE_PRINT_SYSREG( TPIDR_EL0, val,      " Software Thread ID Register                    " );
	APMXGENE_PRINT_SYSREG( TPIDR_EL1, val,      " Software Thread ID Register                    " );
	APMXGENE_PRINT_SYSREG( TPIDRRO_EL0, val,    " Software Thread  ID Register                   " );
//	APMXGENE_PRINT_SYSREG( TEECR32_EL1, val,    " ThumbEE Configuration Register                 " );
}


						




