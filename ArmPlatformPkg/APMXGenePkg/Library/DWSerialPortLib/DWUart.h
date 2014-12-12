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
 **/

#ifndef DW_UART_H
#define DW_UART_H

#include <Uefi.h>
#include <Protocol/SerialIo.h>

enum DWUartReg {
	RBR   = 0x00,
	THR   = 0x00,
	DLL   = 0x00,
	DLH   = 0x04,
	IER   = 0x04,
	IIR   = 0x08,
	FCR   = 0x08,
	LCR   = 0x0C,
	MCR   = 0x10,
	LSR   = 0x14,
	MSR   = 0x18,
	SCR   = 0x1C,
	LPDLL = 0x20,
	LPDLH = 0x24,
	SRBR  = 0x30,
	STHR  = 0x30,
	FAR   = 0x70,
	TFR   = 0x74,
	RFW   = 0x78,
	USR   = 0x7C,
	TFL   = 0x80,
	RFL   = 0x84,
	SRR   = 0x88,
	SRTS  = 0x8C,
	SBCR  = 0x90,
	SBMAM = 0x94,
	SFE   = 0x98,
	SRT   = 0x9C,
	STET  = 0xA0,
	HTX   = 0xA4,
	DMASA = 0xA8,
	CPR   = 0xF4,
	UCV   = 0xF8,
	CTR   = 0xFC
};

#define DW_LSR_THRE 0x20U
#define DW_LSR_DR   0x1U

#define DW_FCR_ENABLE_FIFO	0x01
#define DW_FCR_CLEAR_RCVR	0x02
#define DW_FCR_CLEAR_XMIT	0x04

enum DWOper { DW_OPER_READ, DW_OPER_WRITE };

RETURN_STATUS
EFIAPI
DWUartInitializePort (
  IN UINT64              BaudRate,
  IN EFI_PARITY_TYPE     Parity,
  IN UINT8               DataBits,
  IN EFI_STOP_BITS_TYPE  StopBits
  );

UINTN
EFIAPI
DWUartWrite (
  IN UINTN  UartBase,
  IN UINT8  *Buffer,
  IN UINTN  NumberOfBytes
  );

UINTN
EFIAPI
DWUartRead (
  IN  UINTN     UartBase,
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
);

BOOLEAN
EFIAPI
DWUartPoll (
  IN  UINTN     UartBase,
  IN  enum      DWOper dwOper
  );

#endif
