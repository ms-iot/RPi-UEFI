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

#ifndef __BCM2836UART_H__
#define __BCM2836UART_H__

#define AUX_BASE_ADDRESS  (0x3F215000)

#define AUX_AUXENB        (AUX_BASE_ADDRESS + 0x04)

#define AUX_MU_IO_REG     (AUX_BASE_ADDRESS + 0x40)
#define AUX_MU_LCR_REG    (AUX_BASE_ADDRESS + 0x4C)

#define AUX_MU_STAT_REG   (AUX_BASE_ADDRESS + 0x64)
#define AUX_MU_BAUD_REG   (AUX_BASE_ADDRESS + 0x68)

#define AUX_AUXENB_MINIUART_BIT 0x1
#define AUX_AUXENB_SPI1_BIT 0x2
#define AUX_AUXENB_SPI2_BIT 0x4

#endif // __BCM2836UART_H__
