/** @file
  Timer Architecture Protocol driver of the ARM flavor

  Copyright (c) 2011 ARM Ltd. All rights reserved.<BR>
  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <PiDxe.h>

#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/ArmArchTimer.h>

#include <Protocol/Timer.h>
#include <Protocol/HardwareInterrupt.h>

// The notification function to call on every timer interrupt.
EFI_TIMER_NOTIFY      mTimerNotifyFunction     = (EFI_TIMER_NOTIFY)NULL;
EFI_EVENT             EfiExitBootServicesEvent = (EFI_EVENT)NULL;

// The current period of the timer interrupt
UINT64 mTimerPeriod = 0;

// Cached copy of the Hardware Interrupt protocol instance
EFI_HARDWARE_INTERRUPT_PROTOCOL *gInterrupt = NULL;

#define SRE_HITIMER_ADDR 0xe3000000

#define SRE_HITIMER32_OFFSET (0x00000020)

/****************** Timer32 register addresses offset start ***********************/
#define SRE_HITIMER32_LOAD_OFFSET              (0x0)
#define SRE_HITIMER32_VALUE_OFFSET             (0x4)
#define SRE_HITIMER32_CNTL_OFFSET              (0x8)
#define SRE_HITIMER32_INTC_OFFSET              (0xC)
#define SRE_HITIMER32_RIS_OFFSET               (0x10)
#define SRE_HITIMER32_MIS_OFFSET               (0x0014)
#define SRE_HITIMER32_BGLOAD_OFFSET            (0x18)
/****************** end ******************************/

#define SRE_HITIMER_NUM                        48
#define SRE_HITIMER64_START_INDEX              32
#define SRE_HITIMER_ENCLK_SEL_BIT              (1 << 7)   /* Timer enable flag */


#define SRE_HITIMER_CLK_IN_FREQ                187500000
#define SRE_HITIMER_MICROSECOND_PER_SECOND     1000000

#define SRE_HITIMER_DEFAULT_TICKS              100
#define SRE_HITIMER_RELOAD_TICKS               1

#define SRE_HITIMER_INT_CLEAR                  (0x01)
#define SRE_HITIMER_CNTL_ENABLE                (0x80)
#define SRE_HITIMER_CNTL_MODE                  (0x40)
#define SRE_HITIMER_CNTL_IRQ_ENABLE            (0x20)
#define SRE_HITIMER_CNTL_SIZEMODE              (0x2)


#define SRE_HITIMER_CNTL_MODE_ONCE             0
#define SRE_HITIMER_CNTL_MODE_CYCLE            1
#define SRE_HITIMER_CNTL_IRQ_ON                1
#define SRE_HITIMER_CNTL_IRQ_OFF               0


#define SRE_D01_HITIMER01_INTVEC             (256)
#define SRE_D01_HITIMER23_INTVEC             (257)
#define SRE_D01_HITIMER45_INTVEC             (258)
#define SRE_D01_HITIMER67_INTVEC             (259)
#define SRE_D01_HITIMER89_INTVEC             (260)
#define SRE_D01_HITIMER1011_INTVEC           (261)
#define SRE_D01_HITIMER1213_INTVEC           (262)
#define SRE_D01_HITIMER1415_INTVEC           (263)
#define SRE_D01_HITIMER1617_INTVEC           (264)
#define SRE_D01_HITIMER1819_INTVEC           (265)
#define SRE_D01_HITIMER2021_INTVEC           (266)
#define SRE_D01_HITIMER2223_INTVEC           (267)
#define SRE_D01_HITIMER2425_INTVEC           (268)
#define SRE_D01_HITIMER2627_INTVEC           (269)
#define SRE_D01_HITIMER2829_INTVEC           (270)
#define SRE_D01_HITIMER3031_INTVEC           (271)
#define SRE_D01_HITIMER3233_INTVEC           (272)
#define SRE_D01_HITIMER3435_INTVEC           (273)
#define SRE_D01_HITIMER3637_INTVEC           (274)
#define SRE_D01_HITIMER3839_INTVEC           (275)
#define SRE_D01_HITIMER4041_INTVEC           (276)
#define SRE_D01_HITIMER4243_INTVEC           (277)
#define SRE_D01_HITIMER4445_INTVEC           (278)
#define SRE_D01_HITIMER4647_INTVEC           (279)

UINT32 gRegBase = SRE_HITIMER_ADDR;
#define SC_CTRL 0xe3e00000

void HITIMER_Start()
{
               UINT32 ulRegAddr;
               UINT32 ulVal = 0;
               UINT32 ulMask;

        ulVal = *(UINT32*)SC_CTRL;
        ulVal |= BIT17 | BIT16 | BIT18 | BIT19;
        *(UINT32*)SC_CTRL = ulVal;

               /*timer mode*/
               ulMask = SRE_HITIMER_CNTL_MODE; //BIT6
               ulRegAddr = gRegBase + SRE_HITIMER32_CNTL_OFFSET;
               ulVal = *(UINT32*)ulRegAddr;
               ulVal = ulVal;
               ulVal |= ulMask; /*cycle*/
        *(UINT32*)ulRegAddr = ulVal;

               /*int mode*/
               ulMask = SRE_HITIMER_CNTL_IRQ_ENABLE; //BIT5
               ulRegAddr = gRegBase + SRE_HITIMER32_CNTL_OFFSET;
               ulVal = *(UINT32*)ulRegAddr;
               ulVal = ulVal;
               ulVal |= ulMask;
        //DEBUG((EFI_D_ERROR, "int mode = %0x at %0x\n", ulVal, ulRegAddr));
               *(UINT32*)ulRegAddr = ulVal;

               /*start up*/
               ulMask = (SRE_HITIMER_ENCLK_SEL_BIT | SRE_HITIMER_CNTL_SIZEMODE); //BIT7 | BIT1
               ulRegAddr = gRegBase + SRE_HITIMER32_CNTL_OFFSET;
               ulVal = *(UINT32*)ulRegAddr;
               ulVal = ulVal;
               ulVal |= ulMask;
        //DEBUG((EFI_D_ERROR, "start up = %0x at %0x\n", ulVal, ulRegAddr));
               *(UINT32*)ulRegAddr = ulVal;

}

void HITMER_ClearInt()
{
       UINT32 ulRegAddr;
       UINT32 ulVal = 0;


       ulRegAddr = gRegBase + SRE_HITIMER32_INTC_OFFSET;
       ulVal = SRE_HITIMER_INT_CLEAR;
    //DEBUG((EFI_D_ERROR, "HITMER_ClearInt = %0x at %0x\n", ulVal, ulRegAddr));
       *(UINT32*)ulRegAddr = ulVal;

}

void DisableTimer()
{
       UINT32 ulRegAddr;
       UINT32 ulVal = 0;
       UINT32 ulMask;

       /*disable*/
       ulMask = SRE_HITIMER_ENCLK_SEL_BIT;
       ulRegAddr = gRegBase + SRE_HITIMER32_CNTL_OFFSET;
       ulVal = *(UINT32*)ulRegAddr;
       ulVal = ulVal;
       ulVal &= (~ulMask);
    //DEBUG((EFI_D_ERROR, "DisableTimer = %0x at %0x\n", ulVal, ulRegAddr));
       *(UINT32*)ulRegAddr = ulVal;

}

void EnableTimer()
{
       UINT32 ulRegAddr;
       UINT32 ulVal = 1;
       UINT32 ulMask;

       /*disable*/
       ulMask = SRE_HITIMER_ENCLK_SEL_BIT;
       ulRegAddr = gRegBase + SRE_HITIMER32_CNTL_OFFSET;
       ulVal = *(UINT32*)ulRegAddr;
       ulVal = ulVal;
       ulVal |= ulMask;
    //DEBUG((EFI_D_ERROR, "EnableTimer = %0x at %0x\n", ulVal, ulRegAddr));
       *(UINT32*)ulRegAddr = ulVal;

}

/**
  This function registers the handler NotifyFunction so it is called every time
  the timer interrupt fires.  It also passes the amount of time since the last
  handler call to the NotifyFunction.  If NotifyFunction is NULL, then the
  handler is unregistered.  If the handler is registered, then EFI_SUCCESS is
  returned.  If the CPU does not support registering a timer interrupt handler,
  then EFI_UNSUPPORTED is returned.  If an attempt is made to register a handler
  when a handler is already registered, then EFI_ALREADY_STARTED is returned.
  If an attempt is made to unregister a handler when a handler is not registered,
  then EFI_INVALID_PARAMETER is returned.  If an error occurs attempting to
  register the NotifyFunction with the timer interrupt, then EFI_DEVICE_ERROR
  is returned.

  @param  This             The EFI_TIMER_ARCH_PROTOCOL instance.
  @param  NotifyFunction   The function to call when a timer interrupt fires. This
                           function executes at TPL_HIGH_LEVEL. The DXE Core will
                           register a handler for the timer interrupt, so it can know
                           how much time has passed. This information is used to
                           signal timer based events. NULL will unregister the handler.
  @retval EFI_SUCCESS           The timer handler was registered.
  @retval EFI_UNSUPPORTED       The platform does not support timer interrupts.
  @retval EFI_ALREADY_STARTED   NotifyFunction is not NULL, and a handler is already
                                registered.
  @retval EFI_INVALID_PARAMETER NotifyFunction is NULL, and a handler was not
                                previously registered.
  @retval EFI_DEVICE_ERROR      The timer handler could not be registered.

**/
EFI_STATUS
EFIAPI
TimerDriverRegisterHandler (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN EFI_TIMER_NOTIFY         NotifyFunction
  )
{
  if ((NotifyFunction == NULL) && (mTimerNotifyFunction == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((NotifyFunction != NULL) && (mTimerNotifyFunction != NULL)) {
    return EFI_ALREADY_STARTED;
  }

  mTimerNotifyFunction = NotifyFunction;

  return EFI_SUCCESS;
}

/**
    Disable the timer
**/
VOID
EFIAPI
ExitBootServicesEvent (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  DisableTimer ();
}

/**

  This function adjusts the period of timer interrupts to the value specified
  by TimerPeriod.  If the timer period is updated, then the selected timer
  period is stored in EFI_TIMER.TimerPeriod, and EFI_SUCCESS is returned.  If
  the timer hardware is not programmable, then EFI_UNSUPPORTED is returned.
  If an error occurs while attempting to update the timer period, then the
  timer hardware will be put back in its state prior to this call, and
  EFI_DEVICE_ERROR is returned.  If TimerPeriod is 0, then the timer interrupt
  is disabled.  This is not the same as disabling the CPU's interrupts.
  Instead, it must either turn off the timer hardware, or it must adjust the
  interrupt controller so that a CPU interrupt is not generated when the timer
  interrupt fires.

  @param  This             The EFI_TIMER_ARCH_PROTOCOL instance.
  @param  TimerPeriod      The rate to program the timer interrupt in 100 nS units. If
                           the timer hardware is not programmable, then EFI_UNSUPPORTED is
                           returned. If the timer is programmable, then the timer period
                           will be rounded up to the nearest timer period that is supported
                           by the timer hardware. If TimerPeriod is set to 0, then the
                           timer interrupts will be disabled.


  @retval EFI_SUCCESS           The timer period was changed.
  @retval EFI_UNSUPPORTED       The platform cannot change the period of the timer interrupt.
  @retval EFI_DEVICE_ERROR      The timer period could not be changed due to a device error.

**/
EFI_STATUS
EFIAPI
TimerDriverSetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                   TimerPeriod
  )
{
  UINT64      TimerTicks;

  UINT32 ulRegAddr;

  // always disable the timer
  DisableTimer ();

  if (TimerPeriod != 0) {
    // Convert TimerPeriod to micro sec units
    #if 0
    TimerTicks = DivU64x32 (TimerPeriod, 10);

    TimerTicks = MultU64x32 (TimerTicks, (PcdGet32(PcdArmArchTimerFreqInHz)/1000000));
    #endif

    TimerTicks = DivU64x32 (TimerPeriod, 100);
    TimerTicks = MultU64x32 (TimerTicks, (PcdGet32(PcdArmArchTimerFreqInHz)/100000));

    //ArmArchTimerSetTimerVal((UINTN)TimerTicks);

    ulRegAddr = gRegBase + SRE_HITIMER32_LOAD_OFFSET;
    //DEBUG((EFI_D_ERROR, "TimerTicks1 = %0x at %0x ======\n", TimerTicks, ulRegAddr));
    *(UINT32*)ulRegAddr = TimerTicks;
    ulRegAddr = gRegBase + SRE_HITIMER32_BGLOAD_OFFSET;
    //DEBUG((EFI_D_ERROR, "TimerTicks2 = %0x at %0x  \n", TimerTicks, ulRegAddr));
    *(UINT32*)ulRegAddr = TimerTicks;

    // Enable the timer
    EnableTimer ();
  }

  // Save the new timer period
  mTimerPeriod = TimerPeriod;
  return EFI_SUCCESS;
}

/**
  This function retrieves the period of timer interrupts in 100 ns units,
  returns that value in TimerPeriod, and returns EFI_SUCCESS.  If TimerPeriod
  is NULL, then EFI_INVALID_PARAMETER is returned.  If a TimerPeriod of 0 is
  returned, then the timer is currently disabled.

  @param  This             The EFI_TIMER_ARCH_PROTOCOL instance.
  @param  TimerPeriod      A pointer to the timer period to retrieve in 100 ns units. If
                           0 is returned, then the timer is currently disabled.


  @retval EFI_SUCCESS           The timer period was returned in TimerPeriod.
  @retval EFI_INVALID_PARAMETER TimerPeriod is NULL.

**/
EFI_STATUS
EFIAPI
TimerDriverGetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL   *This,
  OUT UINT64                   *TimerPeriod
  )
{
  if (TimerPeriod == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *TimerPeriod = mTimerPeriod;
  return EFI_SUCCESS;
}

/**
  This function generates a soft timer interrupt. If the platform does not support soft
  timer interrupts, then EFI_UNSUPPORTED is returned. Otherwise, EFI_SUCCESS is returned.
  If a handler has been registered through the EFI_TIMER_ARCH_PROTOCOL.RegisterHandler()
  service, then a soft timer interrupt will be generated. If the timer interrupt is
  enabled when this service is called, then the registered handler will be invoked. The
  registered handler should not be able to distinguish a hardware-generated timer
  interrupt from a software-generated timer interrupt.

  @param  This             The EFI_TIMER_ARCH_PROTOCOL instance.

  @retval EFI_SUCCESS           The soft timer interrupt was generated.
  @retval EFI_UNSUPPORTED       The platform does not support the generation of soft timer interrupts.

**/
EFI_STATUS
EFIAPI
TimerDriverGenerateSoftInterrupt (
  IN EFI_TIMER_ARCH_PROTOCOL  *This
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Interface structure for the Timer Architectural Protocol.

  @par Protocol Description:
  This protocol provides the services to initialize a periodic timer
  interrupt, and to register a handler that is called each time the timer
  interrupt fires.  It may also provide a service to adjust the rate of the
  periodic timer interrupt.  When a timer interrupt occurs, the handler is
  passed the amount of time that has passed since the previous timer
  interrupt.

  @param RegisterHandler
  Registers a handler that will be called each time the
  timer interrupt fires.  TimerPeriod defines the minimum
  time between timer interrupts, so TimerPeriod will also
  be the minimum time between calls to the registered
  handler.

  @param SetTimerPeriod
  Sets the period of the timer interrupt in 100 nS units.
  This function is optional, and may return EFI_UNSUPPORTED.
  If this function is supported, then the timer period will
  be rounded up to the nearest supported timer period.


  @param GetTimerPeriod
  Retrieves the period of the timer interrupt in 100 nS units.

  @param GenerateSoftInterrupt
  Generates a soft timer interrupt that simulates the firing of
  the timer interrupt. This service can be used to invoke the   registered handler if the timer interrupt has been masked for
  a period of time.

**/
EFI_TIMER_ARCH_PROTOCOL   gTimer = {
  TimerDriverRegisterHandler,
  TimerDriverSetTimerPeriod,
  TimerDriverGetTimerPeriod,
  TimerDriverGenerateSoftInterrupt
};

/**

  C Interrupt Handler called in the interrupt context when Source interrupt is active.


  @param Source         Source of the interrupt. Hardware routing off a specific platform defines
                        what source means.

  @param SystemContext  Pointer to system register context. Mostly used by debuggers and will
                        update the system context after the return from the interrupt if
                        modified. Don't change these values unless you know what you are doing

**/
VOID
EFIAPI
TimerInterruptHandler (
  IN  HARDWARE_INTERRUPT_SOURCE   Source,
  IN  EFI_SYSTEM_CONTEXT          SystemContext
  )
{
  EFI_TPL      OriginalTPL;

  //
  // DXE core uses this callback for the EFI timer tick. The DXE core uses locks
  // that raise to TPL_HIGH and then restore back to current level. Thus we need
  // to make sure TPL level is set to TPL_HIGH while we are handling the timer tick.
  //
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
  OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // Check if the timer interrupt is active
  //if ((*(UINT32*)(gRegBase + SRE_HITIMER32_RIS_OFFSET)) & BIT0) {
      //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
    HITMER_ClearInt();

    // Signal end of interrupt early to help avoid losing subsequent ticks from long duration handlers
    gInterrupt->EndOfInterrupt (gInterrupt, Source);


    if (mTimerNotifyFunction) {
      mTimerNotifyFunction (mTimerPeriod);
    }

    // Reload the Timer
    //TimerDriverSetTimerPeriod (&gTimer, FixedPcdGet32(PcdTimerPeriod));
  //}
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // Enable timer interrupts
  //gInterrupt->EnableInterruptSource (gInterrupt, Source);
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  gBS->RestoreTPL (OriginalTPL);
}




/**
  Initialize the state information for the Timer Architectural Protocol and
  the Timer Debug support protocol that allows the debugger to break into a
  running program.

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
TimerInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE  Handle = NULL;
  EFI_STATUS  Status;


  // Find the interrupt controller protocol.  ASSERT if not found.
  Status = gBS->LocateProtocol (&gHardwareInterruptProtocolGuid, NULL, (VOID **)&gInterrupt);
  ASSERT_EFI_ERROR (Status);
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // Disable the timer
  Status = TimerDriverSetTimerPeriod (&gTimer, 0);
  ASSERT_EFI_ERROR (Status);

  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
  // Install secure and Non-secure interrupt handlers
  // Note: Because it is not possible to determine the security state of the
  // CPU dynamically, we just install interrupt handler for both sec and non-sec
  // timer PPI
  Status = gInterrupt->RegisterInterruptSource (gInterrupt, 256, TimerInterruptHandler);
  ASSERT_EFI_ERROR (Status);

  //Status = gInterrupt->RegisterInterruptSource (gInterrupt, PcdGet32 (PcdArmArchTimerIntrNum), TimerInterruptHandler);
  //ASSERT_EFI_ERROR (Status);

  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
  // Unmask timer interrupts
  HITIMER_Start();

  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // Set up default timer
  Status = TimerDriverSetTimerPeriod (&gTimer, FixedPcdGet32(PcdTimerPeriod)); // TIMER_DEFAULT_PERIOD
  ASSERT_EFI_ERROR (Status);
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // Install the Timer Architectural Protocol onto a new handle
  Status = gBS->InstallMultipleProtocolInterfaces(
                  &Handle,
                  &gEfiTimerArchProtocolGuid,      &gTimer,
                  NULL
                  );
  ASSERT_EFI_ERROR(Status);
  //DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));

  // enable Secure timer interrupts
  Status = gInterrupt->EnableInterruptSource (gInterrupt, 256);

  // enable NonSecure timer interrupts
  //Status = gInterrupt->EnableInterruptSource (gInterrupt, PcdGet32 (PcdArmArchTimerIntrNum));

  // Register for an ExitBootServicesEvent
  Status = gBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_NOTIFY, ExitBootServicesEvent, NULL, &EfiExitBootServicesEvent);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
