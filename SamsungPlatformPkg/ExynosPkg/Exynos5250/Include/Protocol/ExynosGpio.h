/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __EXYNOS_GPIO_H__
#define __EXYNOS_GPIO_H__

//
// Protocol interface structure
//
typedef struct _EXYNOS_GPIO   EXYNOS_GPIO;

//
// Data Types
//
typedef UINTN EXYNOS_GPIO_PIN;

#define GPIO(Port, Pin) ((EXYNOS_GPIO_PIN)(((Port) << (16)) | (Pin)))
#define GPIO_PIN(x)     ((EXYNOS_GPIO_PIN)(x) & (0xFFFF))
#define GPIO_PORT(x)    ((EXYNOS_GPIO_PIN)(x) >> (16))

typedef enum {
  GPIO_MODE_INPUT                 = 0x00,
  GPIO_MODE_OUTPUT_0              = 0x0E,
  GPIO_MODE_OUTPUT_1              = 0x0F,
  GPIO_MODE_SPECIAL_FUNCTION_2    = 0x02,
  GPIO_MODE_SPECIAL_FUNCTION_3    = 0x03,
  GPIO_MODE_SPECIAL_FUNCTION_4    = 0x04,
  GPIO_MODE_SPECIAL_FUNCTION_5    = 0x05,
  GPIO_MODE_SPECIAL_FUNCTION_6    = 0x06,
  GPIO_MODE_SPECIAL_FUNCTION_7    = 0x07
} EXYNOS_GPIO_MODE;

typedef enum {
  GPIO_PULL_NONE,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN
} EXYNOS_GPIO_PULL;

typedef enum {
  GPIO_DRV_1X,
  GPIO_DRV_2X,
  GPIO_DRV_3X,
  GPIO_DRV_4X
} EXYNOS_GPIO_STRN;

//
// Function Prototypes
//
typedef
EFI_STATUS
(EFIAPI *EXYNOS_GPIO_GET) (
  IN  EXYNOS_GPIO       *This,
  IN  EXYNOS_GPIO_PIN   Gpio,
  OUT UINTN               *Value
  );
/*++

Routine Description:

  Gets the state of a GPIO pin

Arguments:

  This  - pointer to protocol
  Gpio  - which pin to read
  Value - state of the pin

Returns:

  EFI_SUCCESS - GPIO state returned in Value

--*/


typedef
EFI_STATUS
(EFIAPI *EXYNOS_GPIO_SET) (
    IN EXYNOS_GPIO      *This,
    IN EXYNOS_GPIO_PIN  Gpio,
    IN EXYNOS_GPIO_MODE Mode
    );
/*++

Routine Description:

  Sets the state of a GPIO pin

Arguments:

  This  - pointer to protocol
  Gpio  - which pin to modify
  Mode  - mode to set

Returns:

  EFI_SUCCESS - GPIO set as requested

--*/


typedef
EFI_STATUS
(EFIAPI *EXYNOS_GPIO_GET_MODE) (
    IN  EXYNOS_GPIO         *This,
    IN  EXYNOS_GPIO_PIN     Gpio,
    OUT EXYNOS_GPIO_MODE    *Mode
    );
/*++

Routine Description:

  Gets the mode (function) of a GPIO pin

Arguments:

  This  - pointer to protocol
  Gpio  - which pin
  Mode  - pointer to output mode value

Returns:

  EFI_SUCCESS - mode value retrieved

--*/


typedef
EFI_STATUS
(EFIAPI *EXYNOS_GPIO_SET_PULL) (
    IN  EXYNOS_GPIO      *This,
    IN  EXYNOS_GPIO_PIN  Gpio,
    IN  EXYNOS_GPIO_PULL Direction
    );
/*++

Routine Description:

  Sets the pull-up / pull-down resistor of a GPIO pin

Arguments:

  This  - pointer to protocol
  Gpio  - which pin
  Direction - pull-up, pull-down, or none

Returns:

  EFI_SUCCESS - pin was set

--*/

typedef EFI_STATUS
(EFIAPI *EXYNOS_GPIO_DRV) (
    IN EXYNOS_GPIO      *This,
    IN EXYNOS_GPIO_PIN  Gpio,
    IN EXYNOS_GPIO_STRN  Strength
    );
/*++

Routine Description:

  Sets the Driving strength resistor of a GPIO pin

Arguments:

  This  - pointer to protocol
  Gpio  - which pin
  Strength - 0=1x,1=2x,2=3x,3=4x

Returns:

  EFI_SUCCESS - pin was set

--*/



struct _EXYNOS_GPIO {
  EXYNOS_GPIO_GET       Get;
  EXYNOS_GPIO_SET       Set;
  EXYNOS_GPIO_GET_MODE  GetMode;
  EXYNOS_GPIO_SET_PULL  SetPull;
  EXYNOS_GPIO_DRV	SetStrength;
};

extern EFI_GUID gSamsungPlatformGpioProtocolGuid;

#endif
