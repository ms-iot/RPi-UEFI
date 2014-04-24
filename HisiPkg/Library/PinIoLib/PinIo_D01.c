/************************************************************
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

#include "PinIo_Api.h"
#include "PinIo_D01.h"
#ifndef ERROR
#define ERROR -1
#endif


extern U32  rom_int_lock(void);

extern void rom_int_unlock(U32 ulLock);

void D01_PortInit( U32 ulPortNo, U32 ulPinNo, U32 ulDir, U32 ulOpenDrain )
{
    U32 ulRegVal = 0;    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_INT_EN_REG,ulRegVal);
    ulRegVal &= ~ulPinNo;
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_INT_EN_REG,ulRegVal);
    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    if (OUTPUT_PIN == ulDir)
    {
        ulRegVal |= ulPinNo;
    }
    else
    {
        ulRegVal &= ~ulPinNo;
    }    
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    
    return;
}

void D01_SetPortLevel( U32 ulPortNo, U32 ulPinNo, U32 ulLevel )
{
    U32 ulRegVal = 0; 
    U32 ulLock = 0;
    
    ulLock = rom_int_lock();
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_OUTPUT_REG,ulRegVal);
    if (LOW_LEVEL == ulLevel)
    {
        ulRegVal &= ~ulPinNo;
    }
    else
    {
        ulRegVal |= ulPinNo;
    }
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_OUTPUT_REG,ulRegVal);

    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    ulRegVal |= ulPinNo;
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_OUTPUT_REG,ulRegVal);
    if (LOW_LEVEL == ulLevel)
    {
        ulRegVal &= ~ulPinNo;
    }
    else
    {
        ulRegVal |= ulPinNo;
    }
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_OUTPUT_REG,ulRegVal);
    rom_int_unlock(ulLock);
}
U32 D01_GetPortLevel( U32 ulPortNo, U32 ulPinNo )
{
    U32 ulRegVal = 0;    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    ulRegVal &= ~ulPinNo;
    HI_CPU_GPIO_REG_WRITE(ulPortNo,HI_CPU_GPIO_DIR_REG,ulRegVal);
    
    HI_CPU_GPIO_REG_READ(ulPortNo,HI_CPU_GPIO_INPUT_REG,ulRegVal);
    
    if (ulRegVal&ulPinNo)
    {
        return HIGH_LEVEL;
    }
    else
    {
        return LOW_LEVEL;
    }
}
