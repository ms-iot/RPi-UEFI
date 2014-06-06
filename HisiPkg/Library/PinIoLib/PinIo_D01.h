/*****************************************************************
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


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef _PINIO_HI1380_H_
#define _PINIO_HI1380_H_
#include <Library/PcdLib.h>
#ifndef HIGH_LEVEL
#define HIGH_LEVEL 1
#endif
#ifndef LOW_LEVEL
#define LOW_LEVEL  0
#endif
    
#ifndef INPUT_PIN
#define INPUT_PIN 0
#endif
#ifndef OUTPUT_PIN
#define OUTPUT_PIN 1
#endif

#define HI1380_GPIO_PORT_NUM    2
#define HI1380_GPIO0            0
#define HI1380_GPIO1            1


#define HI1210_GPIO_PORT_NUM    4
#define HI1210_GPIO0            0
#define HI1210_GPIO1            1
#define HI1210_GPIO2            2
#define HI1210_GPIO3            3


#define GPIO0      0x00000001
#define GPIO1      0x00000002
#define GPIO2      0x00000004
#define GPIO3      0x00000008
#define GPIO4      0x00000010
#define GPIO5      0x00000020
#define GPIO6      0x00000040
#define GPIO7      0x00000080
#define GPIO8      0x00000100
#define GPIO9      0x00000200
#define GPIO10     0x00000400
#define GPIO11     0x00000800
#define GPIO12     0x00001000
#define GPIO13     0x00002000
#define GPIO14     0x00004000
#define GPIO15     0x00008000
#define GPIO16     0x00010000                                
#define GPIO17     0x00020000                                
#define GPIO18     0x00040000                                
#define GPIO19     0x00080000                                
#define GPIO20     0x00100000                                
#define GPIO21     0x00200000                                
#define GPIO22     0x00400000                                
#define GPIO23     0x00800000                                
#define GPIO24     0x01000000                                
#define GPIO25     0x02000000                                
#define GPIO26     0x04000000 
#define GPIO27     0x08000000 
#define GPIO28     0x10000000 
#define GPIO29     0x20000000 
#define GPIO30     0x40000000 
#define GPIO31     0x80000000 


#define HI_CPU_GPIO_BASE            PcdGet32(PcdGPIO0Base)

#define HI_CPU_GPIO_OUTPUT_REG      (0x0)  
#define HI_CPU_GPIO_DIR_REG         (0x4)   
#define HI_CPU_GPIO_PORT_CTRL_REG   (0x8)   
#define HI_CPU_GPIO_INT_EN_REG      (0x30)  
#define HI_CPU_GPIO_INT_MASK_REG    (0x34) 
#define HI_CPU_GPIO_INT_TYPE_REG    (0x38)  
#define HI_CPU_GPIO_INT_POLARITY    (0x3c)  
#define HI_CPU_GPIO_INT_CLR_REG     (0x4c)  
#define HI_CPU_GPIO_INPUT_REG       (0x50) 
#define HI_CPU_GPIO_SYNC_REG        (0x60) 

#define HI_CPU_GPIO_REG_READ(port,reg,val)\
{\
    val = *(volatile U32 *)(HI_CPU_GPIO_BASE + (port)*0x1000 + (reg));\
}

#define HI_CPU_GPIO_REG_WRITE(port,reg,val)\
{\
    *(volatile U32 *)(HI_CPU_GPIO_BASE + (port)*0x1000 + (reg)) = (val);\
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

