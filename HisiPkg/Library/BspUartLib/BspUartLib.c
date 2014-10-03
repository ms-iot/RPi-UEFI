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


#include "BspUartLib.h"
#include "BrdCommon.h"
#include "config.h"
#include <Library/DebugLib.h>
#include <Library/ResetWdtLib.h>
#include <Library/DebugLib.h>


#define BSP_UartDelay(loop) delayuart(2 * loop)
void delayuart(unsigned long ulCount)
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


UINT8 ROM_UartChkSndEnd(void)
{
    if(!(*(volatile UINT8 *)UART_LSR_REG & UART_LSR_THRE))
    {
        WDT_ResetWatchdog();
        return 0;
    }
    else
    {
        return 1;
    }
}

void ROM_UartSendChar(UINT8 scShowChar)
{
    UINT32 i = 0;

    while(i < UART_SEND_DELAY)
    {
        WDT_ResetWatchdog();
        if ((*(volatile UINT8 *)(UART_USR_REG) & UART_USR_TFNF) == UART_USR_TFNF)
        {
            break;
        }
        i++;
    }

    *(volatile UINT8 *)(UART_THR_REG) = scShowChar;


    i = 0;
    while (i < UART_SEND_DELAY)
    {
        if (ROM_UartChkSndEnd())
        {
            break;
        }
        i++;
    }

    return;

}

void BspSendUintHex(register UINT32 ulData)
{
    INT8 Buff[8];
    INT32 i;
    UINT32 uTemp = 0x0f;

    for(i = 0; i < 8; i++)
    {
        Buff[i] = ((INT8)(ulData & uTemp));
        ulData = ulData >> 4;
    }

    ROM_UartSendChar('0');
    ROM_UartSendChar('x');

    for(i = 0; i < 8; i++)
    {
        if(Buff[7 - i] < (char)10)
        {
            Buff[7 - i] += '0';
            ROM_UartSendChar(Buff[7 - i]);
        }
        else
        {
            Buff[7 - i] = Buff[7 - i] - 10 + 'A';
            ROM_UartSendChar(Buff[7-i]);
        }
    }
    return;

}

void BspSendString(char *pShow)
{
    if( NULL == pShow)
    {
        return;
    }
    while( *((char *)pShow) )
    {
        WDT_ResetWatchdog();
        ROM_UartSendChar( * ( (char *) pShow ) );
        pShow++;
    }
    return;
}

char BspGetChar(UINT32 ulTimeOut)
{
    UINT32 i = 0;
    register UINT8 recvchar = 0;
    for(;;)
    {
        if ((*(UINT8 *)(UART_LSR_REG) & UART_LSR_DR) == UART_LSR_DR)
        {
            break;
        }
        WDT_ResetWatchdog();

        if (i > ulTimeOut)
        {
            WDT_ResetWatchdog();
            return recvchar;
        }
        
        BSP_UartDelay(10000);
        
        i++;
	}
    recvchar = (*(volatile UINT8 *)(UART_RBR_REG));

    *(volatile UINT8 *)(UART_THR_REG) = recvchar;

    return recvchar;
}


