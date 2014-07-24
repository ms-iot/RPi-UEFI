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

#ifndef __PINIO_H__
#define __PINIO_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "Std.h"
#ifndef INPUT_PIN
#define INPUT_PIN 0
#endif

#ifndef OUTPUT_PIN
#define OUTPUT_PIN 1
#endif
#ifndef OPEN_DRAIN
#define OPEN_DRAIN     1
#endif

#ifndef NO_OPEN_DRAIN
#define NO_OPEN_DRAIN  0
#endif

#ifndef LOW_LEVEL
#define LOW_LEVEL 0
#endif

#ifndef HIGH_LEVEL
#define HIGH_LEVEL 1
#endif


extern U32 GetPortLevel( U32 port, U32 pin );
extern void PortInit( U32 port, U32 pin, U32 dir, U32 openDrain );
extern void SetPortLevel( U32 port, U32 pin, U32 level );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PINIO_H__ */
