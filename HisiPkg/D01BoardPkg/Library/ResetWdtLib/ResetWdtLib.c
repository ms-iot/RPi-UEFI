/*******************************************************************
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
#include <Library/ResetWdtLib.h>
#include <Library/DebugLib.h>
#include <Library/SerialPortLib/SerialPortLib.h>  

void Delay(unsigned long ulCount)
{
    unsigned int ulRet, ulNumber;
    for(ulRet = 0; ulRet < 2; ulRet++)
    {
        ulNumber = ulCount;
        while ( ulNumber-- )
        {
            ;
        }
    }
}
void WDT_ResetWatchdog(void)
{
    outl_wdt((inl_wdt(GPIO3_BASE_ADDR) | GPIO_MASK(21)), GPIO3_BASE_ADDR);
    Delay(100);
    outl_wdt((inl_wdt(GPIO3_BASE_ADDR) & (~GPIO_MASK(21))), GPIO3_BASE_ADDR);
    return;
}

