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



#ifndef __BSP_UART_H
#define __BSP_UART_H
    
#ifdef __cplusplus
        extern "C" {
#endif 		/* __cplusplus */

#include "Std.h"
#define UART_SEND_DELAY    (500000)  

#define SERIAL_0_BASE_ADR       0xe4007000
#define UART_THR_REG         (SERIAL_0_BASE_ADR + UART_RBR)
#define UART_RBR_REG         (SERIAL_0_BASE_ADR + UART_THR)
#define UART_DLL_REG         (SERIAL_0_BASE_ADR + UART_DLL)
#define UART_DLH_REG         (SERIAL_0_BASE_ADR + UART_DLH)
#define UART_IEL_REG         (SERIAL_0_BASE_ADR + UART_IEL)
#define UART_IIR_REG         (SERIAL_0_BASE_ADR + UART_IIR)
#define UART_FCR_REG         (SERIAL_0_BASE_ADR + UART_FCR)
#define UART_LCR_REG         (SERIAL_0_BASE_ADR + UART_LCR)
#define UART_LSR_REG         (SERIAL_0_BASE_ADR + UART_LSR)
#define UART_USR_REG         (SERIAL_0_BASE_ADR + UART_USR)

#define UART_RBR     0x00           
#define UART_THR     0x00         
#define UART_DLL     0x00         
#define UART_DLH     0x04      
#define UART_IEL     0x04      
#define UART_IIR     0x08         
#define UART_FCR     0x08       
#define UART_LCR     0x0C         
#define UART_MCR     0x10         
#define UART_LSR     0x14          
#define UART_USR     0x7C         
    
/* register definitions */
#define UART_FCR_EN		     0x01		
#define UART_FCR_RXCLR       0x02		
#define UART_FCR_TXCLR       0x04	
#define UART_FCR_CLEARFIFO   0x00     

#define UART_LCR_DLAB   0x80   
#define UART_LCR_EPS    0x10   
#define UART_LCR_PEN    0x08    
#define UART_LCR_STOP   0x04   
#define UART_LCR_DLS8   0x03    
#define UART_LCR_DLS7   0x02  
#define UART_LCR_DLS6   0x01    
#define UART_LCR_DLS5   0x00  

#define UART_LSR_TEMT       0x40   
#define UART_LSR_THRE       0x20  
#define UART_LSR_BI         0x10   
#define UART_LSR_FE         0x08  
#define UART_LSR_PE         0x04   
#define UART_LSR_R          0x02   
#define UART_LSR_DR         0x01  
    
#define UART_USR_BUSY       0x01   
#define UART_USR_TFNF       0x02  
#define UART_USR_TFE        0x04   
#define UART_USR_RFNE       0x08 
#define UART_USR_RFF        0x10   

#define HI1210_SC_PRECTRL3     0x34
#define HI1380_SC_PRECTRL1     0x20
#define HI1380_SC_PRECTRL9     0x50

#ifndef NULL
#define NULL 0
#endif

extern void BspSendChar(char scShowChar);
extern char BspGetChar(U32 ulTimeout);

#ifdef __cplusplus
     }
#endif /* __cplusplus */
 
#endif /* __BSP_UART_H */
