/***************************************************************************
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
#include "config.h"
extern void D01_PortInit( U32 ulPortNo, U32 ulPinNo, U32 ulDir, U32 ulOpenDrain );
extern void D01_SetPortLevel( U32 ulPortNo, U32 ulPinNo, U32 ulLevel );
extern U32 D01_GetPortLevel( U32 ulPortNo, U32 ulPinNo );

#define BSP_OUTPUT 0
#define BSP_INPUT 1

void PortInit( U32 ulPortNo, U32 ulPinNo, U32 ulDir, U32 ulOpenDrain )
{
    D01_PortInit(ulPortNo, ulPinNo, ulDir,ulOpenDrain);
}

void SetPortLevel( U32 ulPortNo, U32 ulPinNo, U32 ulLevel)
{
    /*lint -e553*/
    D01_SetPortLevel(ulPortNo, ulPinNo, ulLevel);
}
U32 GetPortLevel( U32 ulPortNo, U32 ulPinNo )
{
    return D01_GetPortLevel(ulPortNo, ulPinNo);
}

