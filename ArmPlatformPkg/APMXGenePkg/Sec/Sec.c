/** @file
*  Main file supporting the SEC Phase on ARM Platforms
*
*  Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#include <Library/ArmTrustedMonitorLib.h>
#include <Library/TimerLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SerialPortLib.h>
#include <Library/ArmGicLib.h>
#include <Library/ArmPlatformSecLib.h>
#include <Library/ArmCpuLib.h>
#include <Library/DebugLib.h>

#include "SecInternal.h"

#define SEC_OCM_LOAD_ADDR    		(0x1D000000)
#define SEC_OCM_FIRST_LOAD_SIZE   	(0x8000) /* 32 KB of OCM */
#define CNTCR_BASE (0x10580000)
#define SerialPrint(txt)  SerialPortWrite ((UINT8*)txt, AsciiStrLen(txt)+1);

extern RETURN_STATUS
EFIAPI
TimerConstructor (
  VOID
  );

const char* ARM64Exceptions[] = {
	"Synchronous_CurrentELWithSP0",
	"IRQ_CurrentELWithSP0",
	"FIQ_CurrentELWithSP0",
	"SError_CurrentELWithSP0",
	"Synchronous_CurrentELWithSPx",
	"IRQ_CurrentELWithSPx",
	"FIQ_CurrentELWithSPx",
	"SError_CurrentELWithSPx",
	"Synchronous_LowerELWithAArch64",
	"IRQ_LowerELWithAArch64",
	"FIQ_LowerELWithAArch64",
	"SError_LowerELWithAArch64",
	"Synchronous_LowerELWithAArch32",
	"IRQ_LowerELWithAArch32",
	"FIQ_LowerELWithAArch32",
	"SError_LowerELWithAArch32",
};

const char* ARM64ExceptionClass[] = {
	"Unknown",
	"WFE/WFI",
	"0x2",
	"MCR/MRC-CP15",
	"MCRR/MRRC",
	"MCR/MRC-CP14",
	"LDC/STC",
	"Advanced SIMD/Floating Point",
	"MRC-CP10",
	"0x9",
	"0x10",
	"0xA",
	"0xB",
	"MCRR/MRCC-CP14",
	"0xD",
	"Ilegal Instruction",
	"0xF",
	"0x10",
	"SVC-AArch32",
	"HVC-AArch32",
	"SMC-AArch32",
	"0x14",
	"SVC-AArch32",
	"HVC-AArch32",
	"SMC-AArch32",
	"MSR/MRS-AAarch64",
	"0x19",
	"0x1A",
	"0x1B",
	"0x1C",
	"0x1D",
	"0x1E",
	"0x1F",
	"Instruction Abort (from lower EL)",
	"Instruction Abort (from current EL)",
	"PC Alignment",
	"0x23",
	"Data Abort (from lower EL)",
	"Data Abort (from current EL)",
	"Stack Pointer Alignment",
	"0x27",
	"Floating Point - Optional - AArch32",
	"0x29",
	"0x2A",
	"0x2B",
	"Floating Point - Optional - AArch64",
	"0x2D",
	"0x2E",
	"SError",
	"Debug"
};

extern EFI_STATUS EFIAPI apm88xxxx_ipp_load_file(CHAR8*, UINT64,
        UINTN, UINTN);

VOID
CEntryPoint (
  IN  UINTN                     MpId,
  IN  UINTN                     SecBootMode
  )
{
  CHAR8           Buffer[80];
  UINTN           CharCount;
  UINTN           JumpAddress;
  UINT32          Val;
#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  CHAR8           UEFIImageName_Sec[16];
#endif
#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  CHAR8           UEFIImageName[16];
#endif

#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  /* avoid GCC put "tianocore" string to rodata section */
  UEFIImageName_Sec[0] = 't';
  UEFIImageName_Sec[1] = 'i';
  UEFIImageName_Sec[2] = 'a';
  UEFIImageName_Sec[3] = 'n';
  UEFIImageName_Sec[4] = 'o';
  UEFIImageName_Sec[5] = 'c';
  UEFIImageName_Sec[6] = 'o';
  UEFIImageName_Sec[7] = 'r';
  UEFIImageName_Sec[8] = 'e';
  UEFIImageName_Sec[9] = '_';
  UEFIImageName_Sec[10] = 's';
  UEFIImageName_Sec[11] = 'e';
  UEFIImageName_Sec[12] = 'c';
  UEFIImageName_Sec[13] = '\0';
#endif

#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  UEFIImageName[0] = 't';
  UEFIImageName[1] = 'i';
  UEFIImageName[2] = 'a';
  UEFIImageName[3] = 'n';
  UEFIImageName[4] = 'o';
  UEFIImageName[5] = 'c';
  UEFIImageName[6] = 'o';
  UEFIImageName[7] = 'r';
  UEFIImageName[8] = 'e';
  UEFIImageName[9] = '\0';
#endif

  // Invalidate the data cache. Doesn't have to do the Data cache clean.
  ArmInvalidateDataCache();

  // Invalidate Instruction Cache
  ArmInvalidateInstructionCache();

  // Invalidate I & D TLBs
  ArmInvalidateTlb();

  // CPU specific settings
  ArmCpuSetup (MpId);

#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  apm88xxxx_ipp_load_file(UEFIImageName_Sec, SEC_OCM_LOAD_ADDR, 0, 0xFFFFFFFF);
#elif defined(APM_XGENE_UHP) && !defined(APM_XGENE_GFC_FLASH)
  /* we map 0x0 to 0x1d000000 as we boot sec phase from 0x1d000000 */
  *(volatile UINT32 *)0x7e920074 = (((0x1D000000>>20)));
  *(volatile UINT32 *)0x7e920054 = ((0));
  *(volatile UINT32 *)0x7e920034 =((0x7FF));
#endif

  // Enable Floating Point Coprocessor if supported by the platform
  if (FixedPcdGet32 (PcdVFPEnabled)) {
    ArmEnableVFP();
  }

  // Primary CPU clears out the SCU tag RAMs, secondaries wait
  if (1) {
#if 0
    /* We don't support having secondary core continue execute to here */
    if (ArmIsMpCore()) {
      // Signal for the initial memory is configured (event: BOOT_MEM_INIT)
      ArmCallSEV ();
    }
#endif

    // SEC phase needs to run library constructors by hand. This assumes
    // we are linked against the SerialLib
    // In non SEC modules the init call is in autogenerated code.
    SerialPortInitialize();

    // Print board header
    if (FixedPcdGetPtr(PcdFirmwareVendor) != NULL) {
      CharCount = AsciiSPrint(Buffer, sizeof(Buffer), "%a\n\r",
                              FixedPcdGetPtr(PcdFirmwareVendor));

      SerialPortWrite((UINT8 *) Buffer, CharCount);
    }

    // Start talking
    CharCount = AsciiSPrint(Buffer, sizeof(Buffer),
                    "%afirmware (version %s built at %a on %a)\n\r",
		    FixedPcdGetBool(PcdTrustzoneSupport) ? "Secure " : "Boot ",
                    (CHAR16*) FixedPcdGetPtr(PcdFirmwareVersionString),
                    __TIME__, __DATE__);
    SerialPortWrite((UINT8 *) Buffer, CharCount);

    // TODO: Aarch64 debug agent setup
    // Initialize the Debug Agent for Source Level Debugging
#if 0
    InitializeDebugAgent (DEBUG_AGENT_INIT_PREMEM_SEC, NULL, NULL);
    SaveAndSetDebugTimerInterrupt (TRUE);
#endif

    // Now we've got UART, make the check:
    // - The Vector table must be 64-byte align
    ASSERT(((UINTN)SecVectorTable & ((1 << 6)-1)) == 0);

    // Enable the GIC distributor and CPU Interface
    // - no other Interrupts are enabled, doesn't have to worry about priority.
    // - all the cores are in secure state, use secure SGI's
    ArmGicEnableDistributor(PcdGet32(PcdGicDistributorBase));
    ArmGicEnableInterruptInterface(PcdGet32(PcdGicInterruptInterfaceBase));
  } else {
    // Enable the GIC CPU Interface
    ArmGicEnableInterruptInterface(PcdGet32(PcdGicInterruptInterfaceBase));
  }

  // Enable Full Access to CoProcessors
  ArmWriteCpacr (CPACR_CP_FULL_ACCESS);

  // Setup arch timer
  // enable counter
  Val = *(volatile UINT32 *)CNTCR_BASE;
  Val |= 1;
  *(volatile UINT32 *)CNTCR_BASE = Val;
  TimerConstructor();

  // Initialize peripherals that must be done at the early stage
  // Example: Some L2 controller, interconnect, clock, DMC, etc
  ArmPlatformSecInitialize (MpId);

#if defined(APM_XGENE_BOOT_SPI_NOR) && !defined(APM_XGENE_VHP)
  /* copy PEI+FVMAIN to DDR for phase 2 booting */
  apm88xxxx_ipp_load_file(UEFIImageName, FixedPcdGet64(PcdFdBaseAddress),
                          0, 0xFFFFFFFF);
#if defined(APM_XGENE_PINSTRAP_WORKAROUND)
  MicroSecondDelay(10000000);
#endif
#endif

  // Test if Trustzone is supported on this platform
  if (FixedPcdGetBool (PcdTrustzoneSupport)) {
    // With Trustzone support the transition from Sec to Normal world is done
    // by return_from_exception(). If we want to keep this function call we
    // need to ensure the SVC's SPSR point to the same Program Status Register
    // as the the current one (CPSR).
    // FIXME - copy_cpsr_into_spsr ();

    // Call the Platform specific function to execute additional actions if required
    JumpAddress = PcdGet64(PcdFvBaseAddress);

    ArmPlatformSecExtraAction(MpId, &JumpAddress);

    // FIXME
    ((void (*)(void))(JumpAddress))();
  } else {

    // Call the Platform specific function to execute additional actions if required
    JumpAddress = PcdGet64(PcdFvBaseAddress);

#if 1
    // FIXME
    ((void (*)(void))(JumpAddress))();
#else
    ArmPlatformSecExtraAction(MpId, &JumpAddress);

    NonTrustedWorldTransition(MpId, JumpAddress);
#endif
  }
  ASSERT(0); // We must never return from the above function
}

VOID
TrustedWorldInitialization (
  IN  UINTN                     MpId,
  IN  UINTN                     SecBootMode
  )
{
  // TODO : AArch64
}

VOID
NonTrustedWorldTransition (
  IN  UINTN                     MpId,
  IN  UINTN                     JumpAddress
  )
{
// FIXME: This code needs to be cleaned up to allow switching to different EL and security levels.

// TODO : We need to check in which EL we are running before doing any of this.
//        We could be starting in EL3, EL2 or EL1.

  // If PcdArmNonSecModeTransition is defined then set this specific mode to CPSR before the transition
  // By not set, the mode for Non Secure World is SVC
  if (PcdGet32 (PcdArmNonSecModeTransition) != 0) {

// TODO - AArch64 - we should get this from the inf file. Currently hardocoded in th asm.
//      - Sec/Sec.inf:76:  gArmTokenSpaceGuid.PcdArmNonSecModeTransition
//      - ArmPkg.dec:141:  gArmTokenSpaceGuid.PcdArmNonSecModeTransition|0x0|UINT32|0x0000003E

    set_non_secure_mode ((ARM_PROCESSOR_MODE)PcdGet32 (PcdArmNonSecModeTransition));
  }

  return_from_exception (JumpAddress);

  //-------------------- Non Secure Mode ---------------------

  // PEI Core should always load and never return
  ASSERT (FALSE);
}

VOID
SecCommonExceptionEntry (
  IN UINT64 Type,
  IN UINT64 ESR,
  IN UINT64 ELR
  )
{
  CHAR8           Buffer[200];
  UINTN           CharCount;

  UINT64 EC = ESR >> 26ULL;
  UINT64 ISS = ESR & 0x1FFFFFF;
  INT32 ECLoc = (INT32)((EC >= 0x30) ? 0x30 : EC);
  INT32 TypeLoc = (INT32)(Type >> 7ULL);

  CharCount = AsciiSPrint (Buffer,sizeof (Buffer),
		  "Exception: Type 0x%llX Syndrome: 0x%llX at: 0x%llX\n\r"
		  "Type: %a (0x%llX)\n\r"
		  "EC: %a (0x%llX)\n\r"
		  "ISS: 0x%llX\n\r"
		  "TypeLoc: 0x%X ECLoc 0x%X\n\r",
		  Type, ESR, ELR,
		  ARM64Exceptions[TypeLoc], Type,
		  ARM64ExceptionClass[ECLoc], EC,
		  ISS,
		  TypeLoc, ECLoc
		  );
  SerialPortWrite ((UINT8 *) Buffer, CharCount);
  while(1);
}
