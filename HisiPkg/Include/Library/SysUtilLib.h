/*************************************************************
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
#ifndef __SYS_UTIL_LIB__
#define __SYS_UTIL_LIB__

#include "Std.h"
 
#define SC_PCB_BIT                      (16)
#define SC_PCB_MASK                     (0xF)


extern U32 GET_ClkFreq(U32* psysClkReg);
extern U32 GET_InterTimerRefPreq(void);
extern U32 BSP_GetStartBootNo(void);

extern void TMBInit (void);
extern void sysUsDelay(U32 delay);
extern void delayUSec(U32 delay);
extern U32 BSP_GetTimeBaseVal(U32 *pulTimeL, U32 *pulTimeH );
extern U32 BSP_GetTimeBase(U32 *pulTimeL, U32 *pulTimeH );
extern void TMB_Read(U32* pulValueHigh, U32* pulValueLow);
extern int bUnzipPlus(
    long  lInputLen,   
    void* pInputBuf,   
    void* pOutputBuf,   
    long* plOutputLen, 
    long  lCheckLen ,  
    char  compresstype  
    );
#endif
