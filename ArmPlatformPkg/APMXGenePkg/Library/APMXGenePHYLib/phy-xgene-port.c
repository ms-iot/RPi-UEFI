/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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

#include "phy-xgene.h"
#include "phy-xgene-port.h"

#define MIDR_EL1_REV_MASK		0x0000000f
#define REVIDR_EL1_MINOR_REV_MASK	0x00000007
#define EFUSE0_SHADOW_VERSION_SHIFT	28
#define EFUSE0_SHADOW_VERSION_MASK	0xF

int xgene_is_preB0(void)
{
	u32 val;
	asm volatile("mrs %0, midr_el1" : "=r" (val));
        val &= MIDR_EL1_REV_MASK;
	return val == 0 ? 1 : 0;
}

int xgene_is_preA3(void)
{
	volatile void *efuse = (volatile void *) 0x1054A000ULL;
	u32 efuse0;

	/* Check for B0 and above */
	if (!xgene_is_preB0())
		return 0;

	/* Check for below B0 */
	efuse0 = (readl(efuse) >> EFUSE0_SHADOW_VERSION_SHIFT)
			& EFUSE0_SHADOW_VERSION_MASK;
	switch (efuse0) {
	case 0x00: /* Not efused - assume A3 */
		return 0;
	case 0x01: /* A2 */
		return 1;
	case 0x02: /* A3 */
		return 0;
	default:   /* Unknown */
		return 0;
	}
}
