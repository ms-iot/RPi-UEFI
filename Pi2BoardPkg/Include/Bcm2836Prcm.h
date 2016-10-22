/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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

#ifndef __BCM2836PRCM_H__
#define __BCM2836PRCM_H__

#define PRCM_BASE_ADDRESS  (0x3F100000)

#define PRCM_RSTC_OFF  (0x1c)
#define PRCM_RSTS_OFF  (0x20)
#define PRCM_WDOG_OFF  (0x24)

#define PRCM_PASSWORD         (0x5a000000)
#define PRCM_RSTC_WRCFG_MASK  (0x00000030)

#define PRCM_RSTS_FULL_RESET           (0x00000010)
#define PRCM_RSTC_WRCFG_FULL_RESET     (0x00000020)
#define PRCM_RSTC_WRCFG_HARDWARE_RESET (0x00000040)
#define PRCM_RSTC_WRCFG_ALL_RESET      (0x00000070)


#endif // __BCM2836PRCM_H__

