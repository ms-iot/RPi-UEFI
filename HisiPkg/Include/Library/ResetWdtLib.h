/*******************************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/
#ifndef __WATCHDOG_RESET__
#define __WATCHDOG_RESET__
extern void Delay(unsigned long ulCount);
extern void WDT_ResetWatchdog(void);
 
#define GPIO_MASK(index)                    (0x1UL << index)

#define GPIO3_BASE_ADDR         0xe4003000

#define HIP04_IOPAD_REG          0xe400c000
#define HIP04_WDOG_PORT          0x1A0        //GPIO98
#define HIP04_SGMI_PORT          0x1AC        //GPIO101
#define HIP04_MII_PORT           0x1B0        //GPIO102
#define HIP04_RST_PORT           0x1B4        //GPIO103

#define writel_wdt(val,addr)                 ((*(volatile unsigned int *)(addr)) = (val))
#define outl_wdt(val,addr)                   ((void) writel_wdt ((val),addr))
#define readl_wdt(addr)                      (*(volatile unsigned int *)(addr))
#define inl_wdt(addr)                        (readl_wdt(addr))

#endif
