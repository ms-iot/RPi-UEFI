/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensouRete.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EmbeddedGpio.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>

#include <APMXGeneAHBCCsr.h>
#include "Gpio.h"

VOID XGeneAHBCWriteReg(IN UINT32 Reg, IN UINT32 Value)
{
  volatile UINT64 Addr = (UINT64)(FixedPcdGet64 (PcdAHBCRegisterBase) + Reg);
  DBG_IO("XGeneAHBCWriteReg : write Reg 0x%llx value:0x%x\n", Addr, Value);
  *(UINT32 *)Addr = Value;
}

UINT32 XGeneAHBCReadReg(IN UINT32 Reg)
{
  volatile UINT64 Addr = (UINT64)(FixedPcdGet64 (PcdAHBCRegisterBase) + Reg);
  UINT32 Val = *(UINT32 *)Addr;
  DBG_IO("XGeneAHBCReadReg : read Reg 0x%llx value:0x%x\n", Addr, Val);
  return Val;
}

VOID XgeneGpioWrite(IN UINT32 Offset, IN UINT32 Val)
{
	volatile UINT64 Addr = (UINT64)(FixedPcdGet64 (PcdGPIORegisterBase) + Offset);
	DBG_IO("WR: 0x%016llx = 0x%08x\n", (UINT64)Addr, Val);
	*(UINT32 *)Addr = Val;
}

VOID XgeneGpioRead(IN UINT32 Offset, OUT UINT32 *Val)
{
	volatile UINT64 Addr = (UINT64)(FixedPcdGet64 (PcdGPIORegisterBase) + Offset);
	*Val = *(UINT32 *)Addr;
	DBG_IO("RD: 0x%016llx = 0x%08x\n", (UINT64)Addr, *Val);
}

VOID XGeneGpioWriteBit(IN UINT32 Pin, IN UINT32 Val)
{
	UINT32 Reg = 0;
	UINT32 GpioPin = 0;
	UINT32 ReadVal = 0;

	if (Pin < GPIO_MUX_MAX) {
		GpioPin = Pin;
		Reg = GPIO_SWPORTA_DR_ADDR;
	} else {
		return;
	}

	XgeneGpioRead(Reg, &ReadVal);
	if (Val) {
		XgeneGpioWrite(Reg, ReadVal | GPIO_MUX_VAL(GpioPin));
	} else {
		XgeneGpioWrite(Reg, ReadVal & ~GPIO_MUX_VAL(GpioPin));
	}
}

UINTN XgeneGpioReadBit(IN UINT32 Pin)
{
	UINT32 Reg = 0;
	UINT32 Val = 0;
	UINT32 GpioPin = 0;

	GpioPin = Pin;
	Reg = GPIO_EXT_PORTA_ADDR;

	XgeneGpioRead(Reg, &Val);
	return (Val & GPIO_MUX_VAL(GpioPin) ? 1 : 0);
}

EFI_STATUS XgeneGpioConfig(IN UINT32 Pin, IN UINT32 InOut, IN UINT32 GpioAlt)
{
	EFI_STATUS Ret = EFI_SUCCESS;
	UINT32 Val;
	INTN PinMux = Pin;
	UINT64 Reg = CFG_PIN_MUX_SEL_0_ADDR;

	DBG("Pin: %d\n", Pin);
	/* Select Register to configure gpio mux Pin */
	if (Pin > GPIO_MUX_MAX - 1) {
		ERROR("Not support GPIO_[%d]!!!\n", Pin);
		Ret = EFI_INVALID_PARAMETER;
		return Ret;
	} else if (Pin > 7 && Pin < 24) {
		Reg = CFG_PIN_MUX_SEL_1_ADDR;
		PinMux -= 8;
	} else if(Pin > 23 && Pin < 32) {
		Reg = CFG_PIN_MUX_SEL_2_ADDR;
		PinMux -= 24;
	}

	/* set mux alternative as GPIO */
	Val = XGeneAHBCReadReg(Reg);
	Val = GPIO_MUX_ALT_CLEAR(Val, PinMux);
	XGeneAHBCWriteReg(Reg, Val | GPIO_MUX_ALT_MASK_VAL(GpioAlt, PinMux));

	/* Set Direction for GPIO Function */
	if (GpioAlt == GPIO_ALT3) {
		/*
		 * Caculate GPIO Pin Number for Direction Register
		 * GPIO_SWPORTA_DDR for GPIO[31...0]
		 * GPIO_SWPORTB_DDR for GPIO[51...32]
		 *
		 */
		if (Pin < GPIO_MUX_MAX) {
			Reg = GPIO_SWPORTA_DDR_ADDR;
		} else {
			Ret = EFI_INVALID_PARAMETER;
			return Ret;
		}

		XgeneGpioRead(Reg, &Val);
		if (InOut == GPIO_OUT) {
			Val |= GPIO_MUX_VAL(Pin);
		} else {
			Val &= ~GPIO_MUX_VAL(Pin);
		}
		XgeneGpioWrite(Reg, Val);
	}

	return Ret;
}

#define AHBC_CLKRST_REG_ADDR			0x0C000

EFI_STATUS XGeneGpioInit(VOID)
{
	UINT32 Data;

	/* Set AHBC GPIO Enable bit */
	Data = XGeneAHBCReadReg(AHBC_CLKRST_REG_ADDR + AHBC_CLKEN_ADDR);
	XGeneAHBCWriteReg(AHBC_CLKRST_REG_ADDR + AHBC_CLKEN_ADDR, Data | 0x4);
	Data = XGeneAHBCReadReg(AHBC_CLKRST_REG_ADDR + AHBC_CLKEN_ADDR);

	/* Clear AHBC SRST reset bit */
	Data = XGeneAHBCReadReg(AHBC_CLKRST_REG_ADDR + AHBC_SRST_ADDR);
	XGeneAHBCWriteReg(AHBC_CLKRST_REG_ADDR + AHBC_SRST_ADDR, Data & ~0x4);
	Data = XGeneAHBCReadReg(AHBC_CLKRST_REG_ADDR + AHBC_SRST_ADDR);

	return EFI_SUCCESS;
}

EFI_STATUS
Get (
  IN  EMBEDDED_GPIO     *This,
  IN  EMBEDDED_GPIO_PIN Gpio,
  OUT UINTN               *Value
  )
{
  UINTN  Pin;

  if (Value == NULL)
  {
    return EFI_UNSUPPORTED;
  }

  /* We don't need port */
  Pin     = GPIO_PIN(Gpio);

  *Value = XgeneGpioReadBit(Pin);

  return EFI_SUCCESS;
}

EFI_STATUS
Set (
  IN  EMBEDDED_GPIO       *This,
  IN  EMBEDDED_GPIO_PIN   Gpio,
  IN  EMBEDDED_GPIO_MODE  Mode
  )
{
  UINTN  Pin;

  /* We don't need port */
  Pin     = GPIO_PIN(Gpio);

  switch (Mode)
  {
    case GPIO_MODE_INPUT:
      XgeneGpioConfig(Pin, GPIO_IN, GPIO_ALT3);
      break;

    case GPIO_MODE_OUTPUT_0:
	  XgeneGpioConfig(Pin, GPIO_OUT, GPIO_ALT3);
	  XGeneGpioWriteBit(Pin, 0);
      break;

    case GPIO_MODE_OUTPUT_1:
      XgeneGpioConfig(Pin, GPIO_OUT, GPIO_ALT3);
      XGeneGpioWriteBit(Pin, 1);
      break;

    default:
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetMode (
  IN  EMBEDDED_GPIO       *This,
  IN  EMBEDDED_GPIO_PIN   Gpio,
  OUT EMBEDDED_GPIO_MODE  *Mode
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
SetPull (
  IN  EMBEDDED_GPIO       *This,
  IN  EMBEDDED_GPIO_PIN   Gpio,
  IN  EMBEDDED_GPIO_PULL  Direction
  )
{
  return EFI_UNSUPPORTED;
}

EMBEDDED_GPIO XGeneGpio = {
  Get,
  Set,
  GetMode,
  SetPull
};

EFI_STATUS
GpioInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;

  //
  // Make sure the Gpio protocol has not been installed in the system yet.
  //
  ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &gEmbeddedGpioProtocolGuid);
  
  XGeneGpioInit();

  Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle, &gEmbeddedGpioProtocolGuid, &XGeneGpio, NULL);
  return Status;
}
