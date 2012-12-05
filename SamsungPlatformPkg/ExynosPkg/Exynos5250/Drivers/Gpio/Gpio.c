/** @file

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>
#include <Library/ExynosLib.h>



EFI_STATUS
Get (
  IN  EXYNOS_GPIO     *This,
  IN  EXYNOS_GPIO_PIN Gpio,
  OUT UINTN               *Value
  )
{
  UINTN  Port;
  UINTN  Pin;
  UINT32 DataInRegister;

  if (Value == NULL)
  {
    return EFI_UNSUPPORTED;
  }

  Port    = GPIO_PORT(Gpio);
  Pin     = GPIO_PIN(Gpio);

  DataInRegister = GpioBase(Port) + GPIO_DATAIN;

  if (MmioRead32 (DataInRegister) & GPIO_DATAIN_MASK(Pin)) {
    *Value = 1;
  } else {
    *Value = 0;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
Set (
  IN  EXYNOS_GPIO       *This,
  IN  EXYNOS_GPIO_PIN   Gpio,
  IN  EXYNOS_GPIO_MODE  Mode
  )
{
  UINTN  Port;
  UINTN  Pin;
  UINT32 OutputRegister;

  Port    = GPIO_PORT(Gpio);
  Pin     = GPIO_PIN(Gpio);
  OutputRegister = GpioBase(Port) + GPIO_CON;
  DEBUG ((EFI_D_INFO, "Gpio->Set: Gpio(0x%x), Port (0x%x), Pin (0x%x), Register (0x%x).\n", Gpio, Port, Pin, OutputRegister));
  switch (Mode)
  {
    case GPIO_MODE_INPUT:
      break;
    case GPIO_MODE_OUTPUT_0:
         MmioAndThenOr32(OutputRegister, ~GPIO_SFN_MASK(Pin), GPIO_OP_EN(Pin));
         MmioAndThenOr32((GpioBase(Port) + GPIO_DATAIN), ~GPIO_DATAIN_MASK(Pin), GPIO_DATA_LOW(Pin));
      break;
    case GPIO_MODE_OUTPUT_1:
         MmioAndThenOr32(OutputRegister, ~GPIO_SFN_MASK(Pin), GPIO_OP_EN(Pin));
         MmioAndThenOr32((GpioBase(Port) + GPIO_DATAIN), ~GPIO_DATAIN_MASK(Pin), GPIO_DATA_HIGH(Pin));
      break;
    case GPIO_MODE_SPECIAL_FUNCTION_2:
         MmioAndThenOr32(OutputRegister, ~GPIO_SFN_MASK(Pin), GPIO_SFN_EN(Pin));
      break;
    default:
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetMode (
  IN  EXYNOS_GPIO       *This,
  IN  EXYNOS_GPIO_PIN   Gpio,
  OUT EXYNOS_GPIO_MODE  *Mode
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
SetPull (
  IN  EXYNOS_GPIO       *This,
  IN  EXYNOS_GPIO_PIN   Gpio,
  IN  EXYNOS_GPIO_PULL  Direction
  )
{
  UINTN  Port;
  UINTN  Pin;
  UINT32 OutputRegister;

  Port    = GPIO_PORT(Gpio);
  Pin     = GPIO_PIN(Gpio);
  OutputRegister = GpioBase(Port) + GPIO_PUD;
  DEBUG ((EFI_D_INFO, "Gpio->SetPull: Gpio(0x%x), Port (0x%x), Pin (0x%x), Register (0x%x).\n", Gpio, Port, Pin, OutputRegister));
  switch (Direction)
  {
    case GPIO_PULL_NONE:
         MmioAndThenOr32(OutputRegister, ~GPIO_PUD_MASK(Pin), GPIO_PUD_DIS(Pin));
      break;
    case GPIO_PULL_UP:
         MmioAndThenOr32(OutputRegister, ~GPIO_PUD_MASK(Pin), GPIO_PUP_EN(Pin));
      break;
    case GPIO_PULL_DOWN:
         MmioAndThenOr32(OutputRegister, ~GPIO_PUD_MASK(Pin), GPIO_PDN_EN(Pin));
      break;
    default:
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}



EFI_STATUS
SetStrength (
    IN EXYNOS_GPIO      *This,
    IN EXYNOS_GPIO_PIN  Gpio,
    IN EXYNOS_GPIO_STRN  Strength
    )
{
  UINTN  Port;
  UINTN  Pin;
  UINT32 OutputRegister;

  Port    = GPIO_PORT(Gpio);
  Pin     = GPIO_PIN(Gpio);
  OutputRegister = GpioBase(Port) + GPIO_DRV;
  MmioAndThenOr32(OutputRegister, ~GPIO_DRV_MASK(Pin), GPIO_DRV_SET(Strength,Pin));

  return EFI_SUCCESS;
}



EXYNOS_GPIO Gpio = {
  Get,
  Set,
  GetMode,
  SetPull,
  SetStrength
};

EFI_STATUS
GpioInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle, &gSamsungPlatformGpioProtocolGuid, &Gpio, NULL);
  return Status;
}
