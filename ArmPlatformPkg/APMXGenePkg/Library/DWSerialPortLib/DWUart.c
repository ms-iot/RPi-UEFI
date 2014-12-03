/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 *
 * CFG_UART_REFCLK=1
 * UART_SERCLK --------------------> UART CLK OUPUT
 *
 * CFG_UART_REFCLK=0 && CFG_UART_INT_REFLCK=0
 *  SYS_REFLCK  --------------------> UART CLK OUPUT
 *
 * CFG_UART_REFCLK=0 && CFG_UART_INT_REFLCK=1
 *  AHBC CLK -----------------------> UART CLK OUPUT
 *
 **/
#include <Library/ArmLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/TimerLib.h>

#include "DWUart.h"

#define STORM_SLIMPRO_CSR_BASE                  0x17000000
#define SCU_SOCPLL_ADDR                         0x00000120
#define SCU_SOCAHBDIV_ADDR                      0x00000164
#define CLKR_RD(src)                            (((src) & 0x07000000)>>24)
#define CLKOD_RD(src)                           (((src) & 0x00300000)>>20)
#define CLKF_RD(src)                            (((src) & 0x000001ff))
#define AHB_FREQ_SEL_RD(src)                    (((src) & 0x0000001f))

#define UART1_REG_BASE_ADDR     0x1c021000
#define UART0_REG_BASE_ADDR     0x1c020000

#define UART_CLK_INPUT    (50*1000*1000)

UINTN GetAHBCCSRBase(VOID)
{
  return (UINTN) PcdGet64(PcdAHBCRegisterBase) + 0xC000;
}

UINTN GetBaseClk(VOID)
{
  return (UINTN) PcdGet32(PcdSysClkInHz);
}

UINT64 GetSOCClk(VOID)
{
	/**
         * Fref = Reference Clock / NREF;
	 * Fvco = Fref * NFB;
	 * Fout = Fvco / NOUT;
	 */
	volatile UINT32 SocPLL = MmioRead32(STORM_SLIMPRO_CSR_BASE + SCU_SOCPLL_ADDR);
	UINT32 NRef = CLKR_RD(SocPLL) + 1;
	UINT32 NOut = CLKOD_RD(SocPLL) + 1;
	UINT32 NFb = CLKF_RD(SocPLL);
	UINT64 Fref = GetBaseClk() / NRef;
	UINT64 Fvco = Fref * NFb;
	return Fvco / NOut;
}

UINT64 GetAHBClk(VOID)
{
	UINT64 SocClk = GetSOCClk();
	volatile UINT32 SocAHB = MmioRead32(STORM_SLIMPRO_CSR_BASE + SCU_SOCAHBDIV_ADDR);
	return SocClk / 2 / AHB_FREQ_SEL_RD(SocAHB);
}

VOID ConfigureUart(
  IN UINTN               UartBase,
  IN UINT64              BaudRate,
  IN EFI_PARITY_TYPE     Parity,
  IN UINT8               DataBits,
  IN EFI_STOP_BITS_TYPE  StopBits,
  IN UINT32              Divider
)
{
  volatile UINT32 Data;

  /* Configure for 8-Data bit No parity 1 stop bit 0x3 (8N1) */
  Data = MmioRead32(UartBase + LCR);
  Data &= ~0x3;     /* Clear Data bits */
  Data |= (DataBits - 5) & 0x3; /* 00 = 5bits, 01 = 6bits, 10 = 7bits 11 = 8 bits */
  Data &= ~0x4;     /* Clear stop bit */
  Data |= ((StopBits - 1) & 0x1) << 2; /* 0 = 1 stop bit, 1 = 1.5/2 stop bits */
  Data &= ~0x8;     /* Clear parity bit */
  Data |= (Parity & 0x1) << 3;
  MmioWrite32(UartBase + LCR, Data | 0x80 /* DLBA */);
  Data = MmioRead32(UartBase + LCR);

  /* Set divisor baud rate */
  MmioWrite32(UartBase + DLL, Divider & 0xFF);
  MmioWrite32(UartBase + DLH, (Divider >> 8) & 0xFF);

  /* Clear LCR DLAB bit */
  Data = MmioRead32(UartBase + LCR);
  MmioWrite32(UartBase + LCR, Data & ~0x80);
  Data = MmioRead32(UartBase + LCR);

  /* Enable FIFO and set transmit level in FCR */
  MmioWrite32(UartBase + FCR, DW_FCR_CLEAR_XMIT | DW_FCR_CLEAR_RCVR | DW_FCR_ENABLE_FIFO);

  /* Disable Interrupts */
  MmioWrite32(UartBase + IER, 0x0);

}

/**
 * Initialize DW UART
 */
RETURN_STATUS
EFIAPI
DWUartInitializePort (
  IN UINT64              BaudRate,
  IN EFI_PARITY_TYPE     Parity,
  IN UINT8               DataBits,
  IN EFI_STOP_BITS_TYPE  StopBits
  )
{
  volatile UINTN UartBase;
  volatile UINT32 Data;
  UINT32 Divider;
  UINT32 UartClkDiv;

  volatile UINTN AHBCBase = GetAHBCCSRBase();

  /* Set AHBC Clk CSR/APB_PERI Enable bit */
  Data = MmioRead32(AHBCBase + 0x8);
  MmioWrite32(AHBCBase + 0x8, Data | 0x201);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x8);	/* Ensure barrier */

  /* Clear AHBC APB_PERI reset bit */
  Data = MmioRead32(AHBCBase + 0x0);
  MmioWrite32(AHBCBase + 0x0, Data & ~0x200);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x0);	/* Ensure barrier */

  /* Clear AHBC CSR reset bit */
  Data = MmioRead32(AHBCBase + 0x0);
  MmioWrite32(AHBCBase + 0x0, Data & ~0x001);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x0);	/* Ensure barrier */


  /* Compute the Divider for 25MHz UART input clock or close to */
  UartClkDiv = GetAHBClk() / UART_CLK_INPUT;

  /* UART intialization */
  /* Set AHB-APB Clock ratio */
  /* Use 200MHz AHB Clock to run UART, div by 4 to get 50MHz */
  Data = MmioRead32(AHBCBase + 0x10);
  Data &= ~0x7FF;
  Data |= 0x2;		/* APB clock = AHBC clock by 2 */
  Data |= (1 << 3);	/* Select Serial Clock from AHB */
  Data |= (UartClkDiv << 4);	/* Divder the UART input clock by 4 for 50Mhz */
  MmioWrite32(AHBCBase + 0x10, Data);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x10);	/* Ensure barrier */

  /* Set Clk UART0 Enable bit */
  Data = MmioRead32(AHBCBase + 0x08);
  MmioWrite32(AHBCBase + 0x08, Data | 0x8);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x08);

  /* Clear UART0 reset bit */
  Data = MmioRead32(AHBCBase + 0x00);
  MmioWrite32(AHBCBase + 0x00, Data & ~0x8);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x00);

  /* Set Clk UART1 Enable bit */
  Data = MmioRead32(AHBCBase + 0x08);
  MmioWrite32(AHBCBase + 0x08, Data | 0x10);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x08);

  /* Clear UART1 reset bit */
  Data = MmioRead32(AHBCBase + 0x00);
  MmioWrite32(AHBCBase + 0x00, Data & ~0x10);
  ArmDataMemoryBarrier();
  Data = MmioRead32(AHBCBase + 0x00);

  /* Set divisor baud rate */
  Divider = GetAHBClk() / UartClkDiv / BaudRate / 16;

  /* we initialize UART0, 1 */
  UartBase = UART0_REG_BASE_ADDR;
  ConfigureUart(UartBase, BaudRate, Parity, DataBits, StopBits, Divider);

  UartBase = UART1_REG_BASE_ADDR;
  ConfigureUart(UartBase, BaudRate, Parity, DataBits, StopBits, Divider);

  return EFI_SUCCESS;
}

/**
 * Write Data to DW UART
 */
UINTN
EFIAPI
DWUartWrite (
  IN UINTN  UartBase,
  IN UINT8  *Buffer,
  IN UINTN  NumberOfBytes
  )
{
  UINTN Count = 0;
  for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
    if (DWUartPoll(UartBase,DW_OPER_WRITE) == FALSE)
      break;
    MmioWrite8 (UartBase + THR, *Buffer);
  }
  return Count;
}

UINTN
EFIAPI
DWUartRead (
  IN  UINTN     UartBase,
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
)
{
  UINTN Count = 0;

  for (Count = 0; Count < NumberOfBytes; Count++, Buffer++) {
    if (DWUartPoll(UartBase,DW_OPER_READ) == FALSE)
      break;
    *Buffer = (volatile UINT8) MmioRead8(UartBase + RBR);
  }
  return Count;
}

BOOLEAN
EFIAPI
DWUartPoll (
  IN  UINTN     UartBase,
  IN  enum      DWOper dwOper
  )
{
  volatile UINT32 val;
  UINTN timeout;

  if (dwOper == DW_OPER_READ)
    timeout = 0x3000;
  else
    timeout = 0x50000;

  do {
    val = MmioRead32(UartBase + LSR);
    if (dwOper == DW_OPER_READ) {
      if (val & DW_LSR_DR) {
        return TRUE;
      }
    } else {
      if (val & DW_LSR_THRE)
        return TRUE;
    }
  } while (--timeout > 0);

  return FALSE;
}
