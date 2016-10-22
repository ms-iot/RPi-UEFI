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

#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>

// Included to be able to initialize the GIT.
 #include <Library/ArmGenericTimerCounterLib.h>

// Included to initialize the PL011 UART
#include <Drivers/PL011Uart.h>

#include <Bcm2836.h>
#include <Pi2Board.h>


#define TICKS_PER_MICRO_SEC     (PcdGet32 (PcdArmArchTimerFreqInHz)/1000000U)

#define C_ASSERT(e) { typedef char __C_ASSERT__[(e)?0:-1]; __C_ASSERT__ c; (void)c; }

/**
  Initialize the Secure peripherals and memory regions

  If Trustzone is supported by your platform then this function makes the required initialization
  of the secure peripherals and memory regions.

**/
VOID
ArmPlatformSecTrustzoneInit (
  IN  UINTN                     MpId
  )
{
  // Secondary cores might have to set the Secure SGIs into the GICD_IGROUPR0
  if (!ArmPlatformIsPrimaryCore (MpId)) {
    return;
  }

  ASSERT(FALSE);
}

/**
  Initialize controllers that must setup at the early stage

  Some peripherals must be initialized in Secure World.
  For example, some L2x0 requires to be initialized in Secure World

**/
RETURN_STATUS
ArmPlatformSecInitialize (
  IN  UINTN                     MpId
  )
{
  // Setup the GPIO routing for the serial ports before any ports are used.

  //
  // Function select registers are laid out in the following fashion:
  // 1. Each register describes 10 pins (bit 0 to 27)
  // 2. Each pin consumes 3 bits in the register.
  //

  if (ArmPlatformIsPrimaryCore (MpId))
  {
    // Configure pins 0-9 (GPFSEL0)
    {
      const UINT32 modifyMask =
        (GPIO_FSEL_MASK << (0 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (1 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (2 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (3 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (4 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (5 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (6 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (7 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (8 * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (9 * GPIO_FSEL_BITS_PER_PIN));

      const UINT32 fixedPinsFunctionMask =
        (GPIO_FSEL_INPUT << (0 * GPIO_FSEL_BITS_PER_PIN)) |     // Firmware reserved
        (GPIO_FSEL_INPUT << (1 * GPIO_FSEL_BITS_PER_PIN)) |     // Firmware reserved
        (GPIO_FSEL_INPUT << (4 * GPIO_FSEL_BITS_PER_PIN)) |     // GPIO4
        (GPIO_FSEL_INPUT << (5 * GPIO_FSEL_BITS_PER_PIN)) |     // GPIO5
        (GPIO_FSEL_INPUT << (6 * GPIO_FSEL_BITS_PER_PIN));      // GPIO6

      C_ASSERT((fixedPinsFunctionMask & ~modifyMask) == 0);

      // Default configuration of I2C1 pins (2,3)  and SPI0 pins (7,8,9)
      // depends on whether runtime muxing is supported by the OS
      UINT32 muxablePinsFunctionMask;
      if (FixedPcdGetBool (PcdRuntimeMuxingEnabled) != FALSE)
      {
        // If muxing is enabled, configure pins as GPIO inputs by default
        const UINT32 muxingEnabledMask =
          (GPIO_FSEL_INPUT << (2 * GPIO_FSEL_BITS_PER_PIN)) |   // GPIO2
          (GPIO_FSEL_INPUT << (3 * GPIO_FSEL_BITS_PER_PIN)) |   // GPIO3
          (GPIO_FSEL_INPUT << (7 * GPIO_FSEL_BITS_PER_PIN)) |   // GPIO7
          (GPIO_FSEL_INPUT << (8 * GPIO_FSEL_BITS_PER_PIN)) |   // GPIO8
          (GPIO_FSEL_INPUT << (9 * GPIO_FSEL_BITS_PER_PIN));    // GPIO9

        C_ASSERT((muxingEnabledMask & ~modifyMask) == 0);

        muxablePinsFunctionMask = muxingEnabledMask;
      }
      else
      {
        // If muxing is not enabled, configure pins as I2C and SPI by default
        const UINT32 muxingDisabledMask =
          (GPIO_FSEL_ALT0 << (2 * GPIO_FSEL_BITS_PER_PIN)) |    // I2C1_SDA
          (GPIO_FSEL_ALT0 << (3 * GPIO_FSEL_BITS_PER_PIN)) |    // I2C1_SCL
          (GPIO_FSEL_ALT0 << (7 * GPIO_FSEL_BITS_PER_PIN)) |    // SPI0_CE1
          (GPIO_FSEL_ALT0 << (8 * GPIO_FSEL_BITS_PER_PIN)) |    // SPI0_CE0
          (GPIO_FSEL_ALT0 << (9 * GPIO_FSEL_BITS_PER_PIN));     // SPI0_MISO

        C_ASSERT((muxingDisabledMask & ~modifyMask) == 0);

        muxablePinsFunctionMask = muxingDisabledMask;
      }

      UINT32 u32GPSEL0 = MmioRead32(GPIO_GPFSEL0);

      u32GPSEL0 &= ~modifyMask;
      u32GPSEL0 |= fixedPinsFunctionMask;
      u32GPSEL0 |= muxablePinsFunctionMask;

      MmioWrite32(GPIO_GPFSEL0, u32GPSEL0);
    } // GPFSEL0

    // Configure pins 10-19 (GPFSEL1)
    {
      const UINT32 modifyMask =
        (GPIO_FSEL_MASK << (10 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (11 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (12 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (13 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (14 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (15 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (16 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (17 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (18 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (19 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));

      const UINT32 fixedPinsFunctionMask =
        (GPIO_FSEL_INPUT << (12 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |      // GPIO12
        (GPIO_FSEL_INPUT << (13 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |      // GPIO13
        (GPIO_FSEL_ALT0 << (14 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |       // UART0_TX
        (GPIO_FSEL_ALT0 << (15 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |       // UART0_RX
        (GPIO_FSEL_INPUT << (16 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |      // GPIO16
        (GPIO_FSEL_INPUT << (17 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |      // GPIO17
        (GPIO_FSEL_INPUT << (18 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |      // GPIO18
        (GPIO_FSEL_INPUT << (19 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));       // GPIO19

      C_ASSERT((fixedPinsFunctionMask & ~modifyMask) == 0);

      UINT32 muxablePinsFunctionMask;
      if (FixedPcdGetBool (PcdRuntimeMuxingEnabled) != FALSE)
      {
        // if muxing enabled, set as GPIO
        const UINT32 muxingEnabledMask =
          (GPIO_FSEL_INPUT << (10 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |    // GPIO10
          (GPIO_FSEL_INPUT << (11 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));     // GPIO11

        C_ASSERT((muxingEnabledMask & ~modifyMask) == 0);

        muxablePinsFunctionMask = muxingEnabledMask;
      }
      else
      {
        // if muxing disabled, set as SPI
        const UINT32 muxingDisabledMask =
          (GPIO_FSEL_ALT0 << (10 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |     // SPI0_MOSI
          (GPIO_FSEL_ALT0 << (11 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));      // SPI0_SCKL

        C_ASSERT((muxingDisabledMask & ~modifyMask) == 0);

        muxablePinsFunctionMask = muxingDisabledMask;
      }

      UINT32 u32GPSEL1 = MmioRead32(GPIO_GPFSEL1);

      u32GPSEL1 &= ~modifyMask;
      u32GPSEL1 |= fixedPinsFunctionMask;
      u32GPSEL1 |= muxablePinsFunctionMask;

      MmioWrite32(GPIO_GPFSEL1, u32GPSEL1);
    } // GPFSEL1

    // Configure pins 20-27 (GPFSEL2)
    if (FixedPcdGetBool (PcdJtagEnabled) == FALSE)
    {
      const UINT32 modifyMask =
        (GPIO_FSEL_MASK << (20 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (21 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (22 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (23 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (24 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (25 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (26 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (27 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));

      const UINT32 fixedPinsFunctionMask =
        (GPIO_FSEL_INPUT << (20 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO20
        (GPIO_FSEL_INPUT << (21 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO21
        (GPIO_FSEL_INPUT << (22 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO22
        (GPIO_FSEL_INPUT << (23 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO23
        (GPIO_FSEL_INPUT << (24 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO24
        (GPIO_FSEL_INPUT << (25 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO25
        (GPIO_FSEL_INPUT << (26 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |  // GPIO26
        (GPIO_FSEL_INPUT << (27 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));   // GPIO27

      C_ASSERT((fixedPinsFunctionMask & ~modifyMask) == 0);

      UINT32 u32GPSEL2 = MmioRead32(GPIO_GPFSEL2);

      u32GPSEL2 &= ~modifyMask;
      u32GPSEL2 |= fixedPinsFunctionMask;

      MmioWrite32(GPIO_GPFSEL2, u32GPSEL2);
    } // GPFSEL2

    // Configure pins 48-49 (GPFSEL4)
    {
      const UINT32 modifyMask =
        (GPIO_FSEL_MASK << (48 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (49 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));

      const UINT32 functionMask =
        (GPIO_FSEL_ALT0 << (48 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |     // SD0_CLK
        (GPIO_FSEL_ALT0 << (49 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));      // SD0_CMD

      C_ASSERT((functionMask & ~modifyMask) == 0);

      UINT32 u32GPSEL4 = MmioRead32(GPIO_GPFSEL4);

      // Mask off to 0 the 3 function bits for these GPIO pins
      u32GPSEL4 &= ~modifyMask;

      // OR in the GPIO pins required setting
      u32GPSEL4 |= functionMask;

      MmioWrite32(GPIO_GPFSEL4, u32GPSEL4);
    } // GPFSEL4

    // Configure pins 50-53 (GPFSEL5)
    {
      const UINT32 modifyMask =
        (GPIO_FSEL_MASK << (50 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (51 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (52 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |
        (GPIO_FSEL_MASK << (53 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));

      const UINT32 functionMask =
        (GPIO_FSEL_ALT0 << (50 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |     // SD0_DAT0
        (GPIO_FSEL_ALT0 << (51 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |     // SD0_DAT1
        (GPIO_FSEL_ALT0 << (52 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN)) |     // SD0_DAT2
        (GPIO_FSEL_ALT0 << (53 % GPIO_FSEL_PINS_PER_REGISTER * GPIO_FSEL_BITS_PER_PIN));      // SD0_DAT3

      C_ASSERT((functionMask & ~modifyMask) == 0);

      UINT32 u32GPSEL5 = MmioRead32(GPIO_GPFSEL5);

      // Mask off to 0 the 3 function bits for these GPIO pins
      u32GPSEL5 &= ~modifyMask;

      // OR in the GPIO pins required setting
      u32GPSEL5 |= functionMask;

      MmioWrite32(GPIO_GPFSEL5, u32GPSEL5);
    } // GPFSEL5

    //
    // Enable AUXSPI1. The AUX_AUXENB register is shared between all AUX
    // peripherals and cannot be modified without synchronization once
    // the OS loads.
    //
    {
        UINT32 u32AUXENB = MmioRead32(AUX_AUXENB);
        u32AUXENB |= AUX_AUXENB_SPI1_BIT;
        MmioWrite32(AUX_AUXENB, u32AUXENB);
    }

    // Initialize the serial port now so we can see the asserts here.
    SerialPortInitialize ();

    // Enter debug after the serial port can print it.
    DEBUG ((DEBUG_INIT, "ArmPlatformSecInitialize: Enter: MpId=0x%8.8X\n", MpId));
  }

  // Check if the ARM Generic Timer Extension is implemented.
  // It's only possible to initialize the timer in secure mode so we need
  // to do it as part of the secure platform initialization.
  // I'm suprised this isn't part of the "default" ARM platform package or
  // apparently a function provided by the TimerLib since it appears to be
  // an ARM architecture+security extension requirement.

  if (ArmIsArchTimerImplemented ()) {

    // Check if Architectural Timer frequency is valid number (should not be 0)
    ASSERT (PcdGet32 (PcdArmArchTimerFreqInHz));

    // Check if ticks/uS is not 0. The Architectural timer runs at constant
    // frequency irrespective of CPU frequency. According to General Timer Ref
    // manual lower bound of the frequency is in the range of 1-10MHz
    ASSERT (TICKS_PER_MICRO_SEC);

    // Perform the setup of the timer.
    {
        UINTN TimerFreq = ArmGenericTimerGetTimerFreq();
        UINTN PcdTimerFreq = PcdGet32(PcdArmArchTimerFreqInHz);

        // When the firmware sets up the timer it assumes that the frequency will be set
        // by the OS to 19.2MHz to match it. Therefore do that now so that Windows will
        // see the correct frequency.
        if (ArmPlatformIsPrimaryCore(MpId))
        {
            MmioWrite32(CORE_TIMER_PRESCALER, 0x80000000);
        }

        // If the timer is not set then go ahead and set it now. If the timer
        // has already been set then there is nothing to do.
        if (TimerFreq == 0)
        {
            ArmGenericTimerSetTimerFreq(PcdTimerFreq);
        }
        else
        {
            // The timer has already been set and it should match the platform setting.
            if (TimerFreq != PcdTimerFreq)
            {
                DEBUG ((DEBUG_WARN, "WARNING: TimerFreq(%d) != PcdTimerFreq(%d)\n", TimerFreq, PcdTimerFreq));
            }
        }
    }
  }

  DEBUG ((DEBUG_INIT, "ArmPlatformSecInitialize: Exit:\n"));

  return RETURN_SUCCESS;
}

/**
  Call before jumping to Normal World

  This function allows the firmware platform to do extra actions before
  jumping to the Normal World

**/
VOID
ArmPlatformSecExtraAction (
  IN  UINTN         MpId,
  OUT UINTN*        JumpAddress
  )
{
  *JumpAddress = PcdGet64(PcdFvBaseAddress);
}
