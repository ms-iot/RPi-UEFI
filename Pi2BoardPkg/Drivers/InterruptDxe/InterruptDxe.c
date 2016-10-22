/** @file
*
*  Implementation for the BCM2836 interrupt controller
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

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/ArmLib.h>

#include <Protocol/Cpu.h>
#include <Protocol/HardwareInterrupt.h>

#include <Bcm2836.h>

//
// Notifications
//
EFI_EVENT EfiExitBootServicesEvent = (EFI_EVENT)NULL;


HARDWARE_INTERRUPT_HANDLER  gRegisteredInterruptHandlers[INT_CORE_MAX_NUM_VECTORS];

/**
  Shutdown our hardware

  DXE Core will disable interrupts and turn off the timer and disable interrupts
  after all the event handlers have run.

  @param[in]  Event   The Event that is being processed
  @param[in]  Context Event Context
**/
VOID
EFIAPI
ExitBootServicesEvent (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
    UINTN CoreId = 0;

    // TODO: Strictly this should be core specific. For now assume core 0 only.
    // TODO: Only supports Timer sources for now.

    {
        UINT32 TCtrl = MmioRead32(INT_CORE_TIMERS_CONTROL(CoreId));

        TCtrl &= ~(0xFF); // Clear all the timer IRQ bits

        DEBUG ((DEBUG_TIMER_INT, "ExitBootServicesEvent: TCtrl=0x%8.8X\n", TCtrl));

        MmioWrite32 (INT_CORE_TIMERS_CONTROL(CoreId), TCtrl);
    }

    // Add code here to disable all FIQs as debugger may have turned one on
}

/**
  Register Handler for the specified interrupt source.

  @param This     Instance pointer for this protocol
  @param Source   Hardware source of the interrupt
  @param Handler  Callback for interrupt. NULL to unregister

  @retval EFI_SUCCESS Source was updated to support Handler.
  @retval EFI_DEVICE_ERROR  Hardware could not be programmed.

**/
EFI_STATUS
EFIAPI
RegisterInterruptSource (
  IN EFI_HARDWARE_INTERRUPT_PROTOCOL    *This,
  IN HARDWARE_INTERRUPT_SOURCE          Source,
  IN HARDWARE_INTERRUPT_HANDLER         Handler
  )
{
    if (Source > INT_CORE_MAX_VECTOR)
    {
        ASSERT(FALSE);
        return EFI_UNSUPPORTED;
    }

    if ((Handler == NULL) && (gRegisteredInterruptHandlers[Source] == NULL))
    {
        return EFI_INVALID_PARAMETER;
    }

    if ((Handler != NULL) && (gRegisteredInterruptHandlers[Source] != NULL))
    {
        return EFI_ALREADY_STARTED;
    }

    gRegisteredInterruptHandlers[Source] = Handler;

    DEBUG ((DEBUG_TIMER_INT, "RegisterInterruptSource: Source=0x%x Handler=0x%8.8p\n", Source, Handler));

    if (Handler != NULL)
    {
        return This->EnableInterruptSource(This, Source);
    }
    else
    {
        return This->DisableInterruptSource(This, Source);
    }
}


/**
  Enable interrupt source Source.

  @param This     Instance pointer for this protocol
  @param Source   Hardware source of the interrupt

  @retval EFI_SUCCESS       Source interrupt enabled.
  @retval EFI_DEVICE_ERROR  Hardware could not be programmed.

**/
EFI_STATUS
EFIAPI
EnableInterruptSource (
  IN EFI_HARDWARE_INTERRUPT_PROTOCOL    *This,
  IN HARDWARE_INTERRUPT_SOURCE          Source
  )
{
    UINTN CoreId = 0;

    if (Source > INT_CORE_MAX_VECTOR)
    {
        ASSERT(FALSE);
        return EFI_UNSUPPORTED;
    }

    // TODO: Assign the Core ID

    // TODO: Only supports Timer sources for now.
    // Check to see if this is the Timer interrupt block (Sources 0-3)
    if (Source < 4)
    {
        UINT32 Bit   = 1UL << Source;
        UINT32 TCtrl = MmioRead32(INT_CORE_TIMERS_CONTROL(CoreId));

        TCtrl |= Bit; // Set the IRQ routing bit to enable.

        DEBUG ((DEBUG_TIMER_INT, "EnableInterruptSource: Source=0x%x TCtrl=0x%8.8X\n", Source, TCtrl));

        MmioWrite32 (INT_CORE_TIMERS_CONTROL(CoreId), TCtrl);
    }
    else
    {
        // Latest linaro implementation would register virtual interrupt. Although it is unsupported
        // for RPi2 it still expects to return EFI_SUCCESS. So do nothing and return EFI_SUCCESS.
        DEBUG((DEBUG_TIMER_INT, "EnableInterruptSource: Source=0x%x (Not Supported)\n", Source));
    }

    return EFI_SUCCESS;
}


/**
  Disable interrupt source Source.

  @param This     Instance pointer for this protocol
  @param Source   Hardware source of the interrupt

  @retval EFI_SUCCESS       Source interrupt disabled.
  @retval EFI_DEVICE_ERROR  Hardware could not be programmed.

**/
EFI_STATUS
EFIAPI
DisableInterruptSource (
  IN EFI_HARDWARE_INTERRUPT_PROTOCOL    *This,
  IN HARDWARE_INTERRUPT_SOURCE          Source
  )
{
    UINTN CoreId = 0;

    if (Source > INT_CORE_MAX_VECTOR) {
    ASSERT(FALSE);
    return EFI_UNSUPPORTED;
    }

    // TODO: Assign the Core ID

    // TODO: Only supports Timer sources for now.
    // Check to see if this is the Timer interrupt block (Sources 0-3)
    if (Source < 4)
    {
        UINT32 Bit   = 1UL << Source;
        UINT32 TCtrl = MmioRead32(INT_CORE_TIMERS_CONTROL(CoreId));

        TCtrl &= ~Bit; // Clear the IRQ routing bit to disable.

        DEBUG ((DEBUG_TIMER_INT, "DisableInterruptSource: Source=0x%x TCtrl=0x%8.8X\n", Source, TCtrl));

        MmioWrite32 (INT_CORE_TIMERS_CONTROL(CoreId), TCtrl);
    }
    else
    {
        ASSERT(FALSE);
        return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS;
}



/**
  Return current state of interrupt source Source.

  @param This     Instance pointer for this protocol
  @param Source   Hardware source of the interrupt
  @param InterruptState  TRUE: source enabled, FALSE: source disabled.

  @retval EFI_SUCCESS       InterruptState is valid
  @retval EFI_DEVICE_ERROR  InterruptState is not valid

**/
EFI_STATUS
EFIAPI
GetInterruptSourceState (
  IN EFI_HARDWARE_INTERRUPT_PROTOCOL    *This,
  IN HARDWARE_INTERRUPT_SOURCE          Source,
  IN BOOLEAN                            *InterruptState
  )
{
    UINTN CoreId = 0;

    if (InterruptState == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    if (Source > INT_CORE_MAX_VECTOR)
    {
        ASSERT(FALSE);
        return EFI_UNSUPPORTED;
    }

    // TODO: Only supports Timer sources for now.
    // Check to see if this is the Timer interrupt block (Sources 0-3)
    if (Source < 4)
    {
        UINT32 Bit = 1UL << Source;
        UINT32 TCtrl = MmioRead32(INT_CORE_TIMERS_CONTROL(CoreId));

        DEBUG ((DEBUG_TIMER_INT, "GetInterruptSourceState: Source=0x%x TCtrl=0x%8.8X\n", Source, TCtrl));

        if ((TCtrl & Bit) == Bit)
        {
            *InterruptState = TRUE;
        }
        else
        {
            *InterruptState = FALSE;
        }
    }
    else
    {
        ASSERT(FALSE);
        return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS;
}

/**
  Signal to the hardware that the End Of Intrrupt state
  has been reached.

  @param This     Instance pointer for this protocol
  @param Source   Hardware source of the interrupt

  @retval EFI_SUCCESS       Source interrupt EOI'ed.
  @retval EFI_DEVICE_ERROR  Hardware could not be programmed.

**/
EFI_STATUS
EFIAPI
EndOfInterrupt (
  IN EFI_HARDWARE_INTERRUPT_PROTOCOL    *This,
  IN HARDWARE_INTERRUPT_SOURCE          Source
  )
{
    // As far as I can tell, there is nothing to do here and the individual source
    // must take care of clearing it's interrupt generation state.

    DEBUG ((DEBUG_TIMER_INT, "EndOfInterrupt: Source=0x%x\n", Source));

    return EFI_SUCCESS;
}


/**
  EFI_CPU_INTERRUPT_HANDLER that is called when a processor interrupt occurs.

  @param  InterruptType    Defines the type of interrupt or exception that
                           occurred on the processor.This parameter is processor architecture specific.
  @param  SystemContext    A pointer to the processor context when
                           the interrupt occurred on the processor.

  @return None

**/
VOID
EFIAPI
IrqInterruptHandler (
  IN EFI_EXCEPTION_TYPE InterruptType,
  IN EFI_SYSTEM_CONTEXT SystemContext
  )
{
    UINT32 CoreId = 0;
    UINT32 Source = 0;

    // There is no obvious conceptual priority or idea on what
    // interrupt source actually fired. Therefore, we just go through
    // all the sources and fire them off if they are set.

    UINT32 IrqSrc = MmioRead32(INT_CORE_IRQ_SOURCE(CoreId));

    DEBUG ((DEBUG_TIMER_INT, "IrqInterruptHandler: IrqSrc=0x%x\n", IrqSrc));

    // TODO: For now we only support Timer and Core 0
    for ( ; Source < 4 ; Source++)
    {
        UINT32 IrqSrcBit = 1UL << Source;

        if ((IrqSrc & IrqSrcBit) == IrqSrcBit)
        {
            HARDWARE_INTERRUPT_HANDLER Handler = gRegisteredInterruptHandlers[Source];

            if (Handler != NULL)
            {
                DEBUG ((DEBUG_TIMER_INT, "IrqInterruptHandler: Source=0x%x Handler=0x%8.8p\n", Source, Handler));

                // Call the registered interrupt handler.
                Handler (Source, SystemContext);
            }
            else
            {
                DEBUG ((EFI_D_ERROR, "IrqInterruptHandler: Spurious interrupt, Source=0x%x\n", Source));
            }
        }
    }
}

//
// Making this global saves a few bytes in image size
//
EFI_HANDLE  gHardwareInterruptHandle = NULL;

//
// The protocol instance produced by this driver
//
EFI_HARDWARE_INTERRUPT_PROTOCOL gHardwareInterruptProtocol = {
  RegisterInterruptSource,
  EnableInterruptSource,
  DisableInterruptSource,
  GetInterruptSourceState,
  EndOfInterrupt
};

/**
  Initialize the state information for the CPU Architectural Protocol

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
InterruptDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS Status;
    EFI_CPU_ARCH_PROTOCOL *Cpu;

    // Make sure the Interrupt Controller Protocol is not already installed in the system.
    ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &gHardwareInterruptProtocolGuid);

    DEBUG ((DEBUG_TIMER_INT, "InterruptDxeInitialize:\n"));

    {
        UINTN CoreId = 0;

        // TODO: Strictly this should be core specific. For now assume core 0 only.
        // TODO: Only supports Timer sources for now.

        {
            UINT32 TCtrl = MmioRead32(INT_CORE_TIMERS_CONTROL(CoreId));

            TCtrl &= ~(0xFF); // Clear all the timer IRQ bits

            DEBUG ((DEBUG_TIMER_INT, "InterruptDxeInitialize: TCtrl=0x%8.8X\n", TCtrl));

            MmioWrite32 (INT_CORE_TIMERS_CONTROL(CoreId), TCtrl);
        }
    }

    Status = gBS->InstallMultipleProtocolInterfaces(&gHardwareInterruptHandle,
                                                    &gHardwareInterruptProtocolGuid,
                                                    &gHardwareInterruptProtocol,
                                                    NULL);
    ASSERT_EFI_ERROR(Status);

    //
    // Get the CPU protocol that this driver requires.
    //
    Status = gBS->LocateProtocol(&gEfiCpuArchProtocolGuid, NULL, (VOID **)&Cpu);
    ASSERT_EFI_ERROR(Status);

    //
    // Unregister the default exception handler.
    //
    Status = Cpu->RegisterInterruptHandler(Cpu, EXCEPT_ARM_IRQ, NULL);
    ASSERT_EFI_ERROR(Status);

    //
    // Register to receive interrupts
    //
    Status = Cpu->RegisterInterruptHandler(Cpu, EXCEPT_ARM_IRQ, IrqInterruptHandler);
    ASSERT_EFI_ERROR(Status);

    // Register for an ExitBootServicesEvent
    Status = gBS->CreateEvent(EVT_SIGNAL_EXIT_BOOT_SERVICES,
                              TPL_NOTIFY,
                              ExitBootServicesEvent,
                              NULL,
                              &EfiExitBootServicesEvent);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

