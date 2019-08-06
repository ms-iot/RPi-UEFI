#/** @file
# Pi3 board package.
#
#  Copyright (c), Microsoft Corporation. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#**/

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = Pi3BoardPkg
  PLATFORM_GUID                  = 32D40B56-E67D-42DD-B9D3-B65511042452
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/Pi3Board
  SUPPORTED_ARCHITECTURES        = ARM
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Pi3BoardPkg/Pi3BoardPkg.fdf

  DEFINE CONFIG_TPM_ENABLE       = FALSE
  DEFINE CONFIG_USE_DTPM         = FALSE

[LibraryClasses.common]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf
  ArmPlatformLib|Pi2BoardPkg/Library/Pi2BoardLib/Pi2BoardLib.inf
  ArmCpuLib|ArmPkg/Drivers/ArmCpuLib/ArmCortexA5xLib/ArmCortexA5xLib.inf

  ArmPlatformStackLib|ArmPlatformPkg/Library/ArmPlatformStackLib/ArmPlatformStackLib.inf
  ArmSmcLib|ArmPkg/Library/ArmSmcLib/ArmSmcLib.inf

  ArmGenericTimerCounterLib|ArmPkg/Library/ArmGenericTimerPhyCounterLib/ArmGenericTimerPhyCounterLib.inf
  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf
  RealTimeClockLib|Pi2BoardPkg/Library/VirtualRealTimeClockLib/VirtualRealTimeClockLib.inf

  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf

!if $(TARGET) == RELEASE
  # Comment/Uncomment to enable processing DEBUG messages and sending
  # them serially to the terminal
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  #DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
!else
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
!endif
  UncachedMemoryAllocationLib|ArmPkg/Library/UncachedMemoryAllocationLib/UncachedMemoryAllocationLib.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf

  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  MemoryInitPeiLib|ArmPlatformPkg/MemoryInitPei/MemoryInitPeiLib.inf

  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|ArmPkg/Library/BaseMemoryLibStm/BaseMemoryLibStm.inf

  EfiResetSystemLib|Pi2BoardPkg/Library/ResetSystemLib/ResetSystemLib.inf

  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf

  EfiFileLib|EmbeddedPkg/Library/EfiFileLib/EfiFileLib.inf

  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf

  #
  # The Standard IO window in the JTAG debugger will show an entry for each loaded/unloaded module
  # that consists of the module symbol path and the module load address which is useful for JTAG
  # source-level debugging
  #
  #PeCoffExtraActionLib|ArmPkg/Library/DebugPeCoffExtraActionLib/DebugPeCoffExtraActionLib.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf

  CacheMaintenanceLib|ArmPkg/Library/ArmCacheMaintenanceLib/ArmCacheMaintenanceLib.inf
  DefaultExceptionHandlerLib|ArmPkg/Library/DefaultExceptionHandlerLib/DefaultExceptionHandlerLib.inf
  CpuExceptionHandlerLib|MdeModulePkg/Library/CpuExceptionHandlerLibNull/CpuExceptionHandlerLibNull.inf
  PrePiLib|EmbeddedPkg/Library/PrePiLib/PrePiLib.inf

  #
  # BCM UART 1 is used for console output
  #
  SerialPortLib|Pi3BoardPkg/Library/SerialPortLib/SerialPortLib.inf

  SerialPortExtLib|EmbeddedPkg/Library/TemplateSerialPortExtLib/TemplateSerialPortExtLib.inf
  SemihostLib|ArmPkg/Library/SemihostLib/SemihostLib.inf

  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf

  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf

  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf

#
# Assume everything is fixed at build but system memory size
#
  PcdLib|Pi2BoardPkg/Library/Pi2PcdLib/Pi2PcdLib.inf

  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf

  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf

  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf

  # The I2C GPIO expander controls the LEDs.
  LedLib|Pi3BoardPkg/Library/BcmGpioVirtLedLib/BcmGpioVirtLedLib.inf
  BcmMailboxLib|Pi2BoardPkg/Library/BcmMailboxLib/BcmMailboxLib.inf

  ArmDisassemblerLib|ArmPkg/Library/ArmDisassemblerLib/ArmDisassemblerLib.inf
  DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
  DmaLib|ArmPkg/Library/ArmDmaLib/ArmDmaLib.inf

  ArmBdsHelperLib|ArmPkg/Library/ArmBdsHelperLib/ArmBdsHelperLib.inf
  BdsLib|ArmPkg/Library/BdsLib/BdsLib.inf
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf

  # Networking
  NetLib|MdeModulePkg/Library/DxeNetLib/DxeNetLib.inf

[LibraryClasses.common.SEC]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7LibSec.inf
  ArmPlatformSecLib|Pi3BoardPkg/Library/SecLib/SecLib.inf
  ArmTrustedMonitorLib|ArmPlatformPkg/Library/ArmTrustedMonitorLibNull/ArmTrustedMonitorLibNull.inf
  ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/Sec/SecArmPlatformGlobalVariableLib.inf

  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  ExtractGuidedSectionLib|EmbeddedPkg/Library/PrePiExtractGuidedSectionLib/PrePiExtractGuidedSectionLib.inf
  LzmaDecompressLib|IntelFrameworkModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf

  # Temp work around for Movt relocation issue.
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf

  HobLib|EmbeddedPkg/Library/PrePiHobLib/PrePiHobLib.inf
  PrePiHobListPointerLib|ArmPlatformPkg/Library/PrePiHobListPointerLib/PrePiHobListPointerLib.inf
  MemoryAllocationLib|EmbeddedPkg/Library/PrePiMemoryAllocationLib/PrePiMemoryAllocationLib.inf
  PlatformPeiLib|ArmPlatformPkg/PlatformPei/PlatformPeiLib.inf

[LibraryClasses.common.PEI_CORE]
  PcdLib|Pi2BoardPkg/Library/Pi2PcdLib/Pi2PcdLib.inf
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/PeiDxeDebugLibReportStatusCode/PeiDxeDebugLibReportStatusCode.inf

[LibraryClasses.common.DXE_CORE]
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/DxeReportStatusCodeLibFramework/DxeReportStatusCodeLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf

  PerformanceLib|MdeModulePkg/Library/DxeCorePerformanceLib/DxeCorePerformanceLib.inf

[LibraryClasses.common.DXE_DRIVER]
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/DxeReportStatusCodeLibFramework/DxeReportStatusCodeLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/Dxe/DxeArmPlatformGlobalVariableLib.inf

[LibraryClasses.common.UEFI_APPLICATION]
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/DxeReportStatusCodeLibFramework/DxeReportStatusCodeLib.inf
  UefiDecompressLib|IntelFrameworkModulePkg/Library/BaseUefiTianoCustomDecompressLib/BaseUefiTianoCustomDecompressLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf

[LibraryClasses.common.UEFI_DRIVER]
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/DxeReportStatusCodeLibFramework/DxeReportStatusCodeLib.inf
  UefiDecompressLib|IntelFrameworkModulePkg/Library/BaseUefiTianoCustomDecompressLib/BaseUefiTianoCustomDecompressLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  ReportStatusCodeLib|IntelFrameworkModulePkg/Library/DxeReportStatusCodeLibFramework/DxeReportStatusCodeLib.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf

  #
  # The Coff lib cannot be the PeCoffLib|EmbeddedPkg/Library/DxeHobPeCoffLib/DxeHobPeCoffLib.inf one
  # because it's rooted in PEI memory. As a result the call to SetVirtualAddressMap after ExitBootServices
  # will crash because the global memory (gPeCoffLoader) it uses is no longer mapped.
  #

  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf

[LibraryClasses.ARM]
  #
  # It is not possible to prevent the ARM compiler for generic intrinsic functions.
  # This library provides the instrinsic functions generate by a given compiler.
  # [LibraryClasses.ARM] and NULL mean link this library into all ARM images.
  #
  NULL|ArmPkg/Library/CompilerIntrinsicsLib/CompilerIntrinsicsLib.inf


[BuildOptions]
  XCODE:*_*_ARM_PLATFORM_FLAGS == -arch armv7

  GCC:*_*_ARM_PLATFORM_FLAGS == -march=armv7-a
  # Uncomment to allow generation of mixed source/assembly list files
  ; GCC:*_*_ARM_ARCHCC_FLAGS ==  -S -Wa,-adhlns="$@.lst" -fverbose-asm

  RVCT:*_*_ARM_PLATFORM_FLAGS == --cpu Cortex-A8

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
  gEfiMdePkgTokenSpaceGuid.PcdComponentNameDisable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnosticsDisable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdComponentName2Disable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnostics2Disable|TRUE

  #
  # Control what commands are supported from the UI
  # Turn these on and off to add features or save size
  #
  gEmbeddedTokenSpaceGuid.PcdEmbeddedMacBoot|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedDirCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedHobCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedHwDebugCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPciDebugCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedIoEnable|FALSE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedScriptCmd|FALSE

  gEmbeddedTokenSpaceGuid.PcdCacheEnable|TRUE

  # Use the Vector Table location in CpuDxe. We will not copy the Vector Table at PcdCpuVectorBaseAddress
  gArmTokenSpaceGuid.PcdRelocateVectorTable|FALSE

  gEmbeddedTokenSpaceGuid.PcdPrePiProduceMemoryTypeInformationHob|TRUE
  gArmTokenSpaceGuid.PcdCpuDxeProduceDebugSupport|FALSE

  gEfiMdeModulePkgTokenSpaceGuid.PcdTurnOffUsbLegacySupport|TRUE

  ## If TRUE, Graphics Output Protocol will be installed on virtual handle created by ConsplitterDxe.
  #  It could be set FALSE to save size.
  # ConsplitterDxe is currently not used
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutGopSupport|TRUE

  # The secondary cores are parked in the Pi3 boot firwmware. This flag triggers
  # the Pre Pi MP core component to send a signal releasing them (in the Pi 2 case
  # this is the write of the jump address into a mailbox implemented in the
  # BCM specific GIC component in order to match the ARM GIC case)
  gArmPlatformTokenSpaceGuid.PcdSendSgiToBringUpSecondaryCores|TRUE

[PcdsFixedAtBuild.common]
  gArmPlatformTokenSpaceGuid.PcdFirmwareVendor|"Pi3 Board"
  gArmPlatformTokenSpaceGuid.PcdCoreCount|4

  gEmbeddedTokenSpaceGuid.PcdEmbeddedPrompt|"Pi3Edk2"
  gEfiMdePkgTokenSpaceGuid.PcdMaximumUnicodeStringLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdMaximumAsciiStringLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdMaximumLinkedListLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdSpinLockTimeout|10000000
  gEfiMdePkgTokenSpaceGuid.PcdDebugClearMemoryValue|0xAF
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|1
  gEfiMdePkgTokenSpaceGuid.PcdPostCodePropertyMask|0
  gEfiMdePkgTokenSpaceGuid.PcdUefiLibMaxPrintBufferSize|320

  # Default table revision to be ACPI 5.0 compliant
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiRevision|0x20

# DEBUG_ASSERT_ENABLED       0x01
# DEBUG_PRINT_ENABLED        0x02
# DEBUG_CODE_ENABLED         0x04
# CLEAR_MEMORY_ENABLED       0x08
# ASSERT_BREAKPOINT_ENABLED  0x10
# ASSERT_DEADLOOP_ENABLED    0x20
!if $(TARGET) == RELEASE
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x21
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2f
!endif

  #  DEBUG_INIT       0x00000001  // Initialization
  #  DEBUG_WARN       0x00000002  // Warnings
  #  DEBUG_LOAD       0x00000004  // Load events
  #  DEBUG_FS         0x00000008  // EFI File system
  #  DEBUG_POOL       0x00000010  // Alloc & Free's
  #  DEBUG_PAGE       0x00000020  // Alloc & Free's
  #  DEBUG_INFO       0x00000040  // Verbose
  #  DEBUG_DISPATCH   0x00000080  // PEI/DXE Dispatchers
  #  DEBUG_VARIABLE   0x00000100  // Variable
  #  DEBUG_TIMER_INT  0x00000200  // Timer & Interrupt Drivers
  #  DEBUG_BM         0x00000400  // Boot Manager
  #  DEBUG_BLKIO      0x00001000  // BlkIo Driver
  #  DEBUG_NET        0x00004000  // SNI Driver
  #  DEBUG_MMCHOST_SD 0x00008000  // MMCHost Miniport Driver
  #  DEBUG_UNDI       0x00010000  // UNDI Driver
  #  DEBUG_LOADFILE   0x00020000  // UNDI Driver
  #  DEBUG_EVENT      0x00040000  // Verbose
  #  DEBUG_EVENT      0x00080000  // Event messages
  #  DEBUG_GCD        0x00100000  // Global coherency database.
  #  DEBUG_ERROR      0x80000000  // Error
  #
  # By default only enable init, error, warning and load debug prints to minimize
  # debug messages. Use "0x8FEF4DCF" for detailed debugging purposes.
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel| 0x80000003 # 0x8FEF4DCF

  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x07

  gEmbeddedTokenSpaceGuid.PcdEmbeddedAutomaticBootCommand|""
  gEmbeddedTokenSpaceGuid.PcdEmbeddedDefaultTextColor|0x07
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxVariableSize|0x000F0000
  gEmbeddedTokenSpaceGuid.PcdEmbeddedMemVariableStoreSize|0x10000

#
# Optional feature to help prevent EFI memory map fragments
# Turned on and off via: PcdPrePiProduceMemoryTypeInformationHob
# Values are in EFI Pages (4K). DXE Core will make sure that
# at least this much of each type of memory can be allocated
# from a single memory range. This way you only end up with
# maximum of two fragements for each type in the memory map
# (the memory used, and the free memory that was prereserved
# but not used).
#
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiACPIReclaimMemory|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiACPIMemoryNVS|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiReservedMemoryType|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiRuntimeServicesData|80
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiRuntimeServicesCode|40
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiBootServicesCode|400
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiBootServicesData|3000
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiLoaderCode|10
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiLoaderData|0

#
# Pi3 board Specific PCDs
#
  #
  # ARM PL011 UART 0 settings to be used when it's included as the default serial port.
  #
  gArmPlatformTokenSpaceGuid.PL011UartClkInHz|16000000 # 16MHz this must match config.txt default is 3MHz

  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0x3F201000 # NOTE: Datasheet errata!

  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|921600
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultDataBits|8
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultParity|1   # NoParity
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultStopBits|1 # OneStopBit

  gArmTokenSpaceGuid.PcdVFPEnabled|1

  # Reserve the lower 2MB of physical memory for UEFI
  gPi2BoardTokenSpaceGuid.PcdBootRegionBase|0x0
  gPi2BoardTokenSpaceGuid.PcdBootRegionSize|0x200000

  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x00200000

  # Size of the region used by UEFI in permanent memory (Reserved 16MB)
  gArmPlatformTokenSpaceGuid.PcdSystemMemoryUefiRegionSize|0x01000000

  # Size of the region reserved for fixed address allocations (Reserved 32MB)
  gArmTokenSpaceGuid.PcdArmLinuxKernelMaxOffset|0x02000000

  #
  # Fixed allocation memory for initial boot.
  # This region lives at offset 0xE0000 (896Kb) with length 0x20000 (128Kb)
  #
  # 0xE0000 -> 0xE0FFF - 1 x 4Kb page for the exception vector table.
  # 0xE1000 -> 0xE1FFF - 1 x 4Kb page for the first entry in the HOB list (dynamic memory)
  # 0xE2000 -> 0xE3FFF - 2 x 4Kb page for the Secure execution stacks (four stacks of 2Kb each)
  # 0xE4000 -> 0xEBFFF - 8 x 4Kb pages for the Primary Core normal stack (32Kb)
  # 0xEC000 -> 0xEEFFF - 3 x 4Kb pages for the Secondary Core normal stacks (three stacks of 4Kb each)
  # 0xEF000 -> 0xF0000 - 1 x 4Kb page unused (accidental GIC access)
  # 0xF0000 -> 0xF3FFF - 4 x 4Kb pages for the Multi-Processor Parking Protocol mailboxes (four of 4Kb)
  # 0xF4000 -> 0xF4FFF - 1 x 4Kb pages for shared global memory

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x000E0000  # Exception vector table.
  gEmbeddedTokenSpaceGuid.PcdPrePiHobBase|0x000E1000     # First page, head of the HOB list.

  #
  # Stacks for MPCores in Secure World
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecStackBase|0x000E2000
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecPrimaryStackSize|0x800
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecSecondaryStackSize|0x800

  #
  # Stacks for MPCores in Normal World
  # This is *required* to be used for the Multi-Processor Parking Protocol as used by Windows
  # because the secondary cores are started after ExitBootServices such that UEFI memory has already
  # been released. Therefore, the memory represented by PcdCPUCoresStackBase *must* be outside of the
  # System Memory declared to UEFI such that it's always available for use at any time.
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0x000E4000
  gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x8000
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecondaryStackSize|0x1000

  #
  # ARM General Interrupt Controller settings
  #
  # Since the 2836 doesn't have an ARM GIC we use the BCM "stub" library instead to provide only
  # enough functionality to be able to get the platform started and support multi-processor through
  # the MP Parking Protocol.
  # Therefore, these values are unused and set to point to unused memory in case something trys to
  # use it.
  #
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x000EF000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x000EF100

  # Mailbox base for the Multi-Processor Parking Protocol (uses one 4Kb page per core, thus 16Kb)
  #
  # NOTE: This value is also reflected in the ACPI tables in the GIC Parked Address (mailbox address)
  #       fields for the four cores as 0x000F0000, 0x000F1000, 0x000F2000 & 0x000F3000. Therefore, if
  #       changed here it MUST also be changed in the ACPI tables to match.
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresMPPPMailboxBase|0x000F0000

  #
  # In the BCM Gic implementation this represents the address of the secondary
  # core start as written into the mailbox to be picked up by the Pi 3 boot
  # firmware. The net effect is to boot the secondary cores in exactly the same
  # way as the primary cores (through Sec and Pre Pi etc).
  #
  gArmTokenSpaceGuid.PcdCpuResetAddress|0x00108000  # Pi3 image load & start

  #
  # The Pi3 cores are in cluster 0
  #
  gArmTokenSpaceGuid.PcdArmPrimaryCore|0x0
  gPi2BoardTokenSpaceGuid.PcdCoresClusterId|0x0

  #
  # The timer frequency is set by the ARM core timer prescaler to 19.2MHz.
  # Since the GIC CntFrq register is set in secure mode by the boot firmware
  # to 19.2MHz the UEFI platform init sets the prescaler to match the 19.2MHz
  # that's been set. Therefore, the value below is a constant and must be set to
  # 19.2MHz to match it.
  #

  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000  # 19.2MHz

  #
  # Timer interrupt routing.
  # If the GIC is used, these two lines can be removed as the ARM package defaults
  # are correct for the routing of the GIT interrupts to the GIC. Since the BCM2836 doesn't
  # use the GIC, these values represent the bit number in the Timer Control and IRQ Source
  # registers.
  #
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|0  #Interrupt Source/Vector 0
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|1     #Interrupt Source/Vector 1

  #
  # Set the tick period for UEFI polling and timeouts expressed in 100ns units.
  #  100000 ==  10ms (usual)
  # 1000000 == 100ms (can be used if DEBUG_TIMER_INT is on)
  #
  gEmbeddedTokenSpaceGuid.PcdTimerPeriod|100000  #10ms tick.

  # TBD if the below are correct.
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPerformanceCounterPeriodInNanoseconds|77
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPerformanceCounterFrequencyInHz|13000000

  #
  # ARM Pcds
  #
  gArmTokenSpaceGuid.PcdArmUncachedMemoryMask|0x0000000040000000

!if $(RAMDISK_BOOT_ENABLE)
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"Windows Boot from RAM Disk"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(B615F1F5-5088-43CD-809C-A16E52487D00)/HD(1,MBR,0x00000000,0x3F,0x19FC0)/bootarm.efi" # RAMDISK BOOT
!elseif $(MBRGPT_WORKAROUND_ENABLE)
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"Windows Boot from SD-Card"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(1,GPT,112A7328-F81F-11D2-BA4B-00A0C93EC93B,0x3000,0x30FC0)/bootarm.efi" # SD CARD BOOT MBR+GPT
!else
  # PcdDefaultBootAppPath defined the default boot application path.
  # Mobile FFU
  #gArmPlatformTokenSpaceGuid.PcdDefaultBootAppPath|L"\\Windows\\boot\\Efi\\bootmgfw.efi"
  # Desktop FFU
  gArmPlatformTokenSpaceGuid.PcdDefaultBootAppPath|L"\\efi\\microsoft\\boot\\bootmgfw.efi"

  # Default boot path for a typical FFU. Currently unused but keeping around for reference
  #gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"Windows Boot from SD-Card"
  #gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(2,MBR,0xAE420040,0x1000,0x20000)/Windows\\boot\\Efi\\bootmgfw.efi"# FFU MBR BOOT
!endif

  gArmPlatformTokenSpaceGuid.PcdDefaultBootArgument|"console=tty0 console=ttyS2,115200n8 root=UUID=a4af765b-c2b5-48f4-9564-7a4e9104c4f6 rootwait ro earlyprintk"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootType|0 # 0 - EFI App, 1 - LINUX_ATAG, 2 - LINUX_FDT
  gArmPlatformTokenSpaceGuid.PcdFdtDevicePath|L"VenHw(B615F1F5-5088-43CD-809C-A16E52487D00)/HD(1,MBR,0x00000000,0x3F,0x19FC0)/Bcm3-Pi2.dtb"

  #
  # Boot time is set 0 to avoid user input from halting boot. Typically
  # WinDBG would be connected and generate a ping to the board which
  # is interpreted as an input and would halt UEFI from loading the OS.
  # An advance user could still enable input instead if needed by specifying
  # a timeout value.
  #
  gArmPlatformTokenSpaceGuid.PcdPlatformBootTimeOut|0

  gArmPlatformTokenSpaceGuid.PcdDefaultConOutPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8,N,1)/VenPcAnsi();VenHw(c5deae31-fad2-4030-841b-cfc9644d2c5b)"
  gArmPlatformTokenSpaceGuid.PcdDefaultConInPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8,N,1)/VenPcAnsi()"

  #
  # ARM OS Loader
  #
  # Pi2Board machine type (BCM3_Pi2 = 1546) required for ARM Linux:
  gArmTokenSpaceGuid.PcdArmMachineType|1546

  #
  # MBR+GPT Workaround for SD Card
  #
!if $(RAMDISK_BOOT_ENABLE)
  # gPi2BoardTokenSpaceGuid.PcdArasanSDCardMBRGPTWorkaroundEnabled|0
!elseif $(MBRGPT_WORKAROUND_ENABLE)
  gPi2BoardTokenSpaceGuid.PcdArasanSDCardMBRGPTWorkaroundEnabled|1
  # This should be the same value passed to param <LBA Offset of GPT Header> of MBRPlusGPT.exe
  gPi2BoardTokenSpaceGuid.PcdArasanSDCardMBRGPTWorkaroundGPTOffsetLba|0x0009d000
!else
  gPi2BoardTokenSpaceGuid.PcdArasanSDCardMBRGPTWorkaroundEnabled|0
!endif

  # JTAG enable flag enabled on DEBUG build only
!if $(TARGET) == DEBUG
  gPi2BoardTokenSpaceGuid.PcdJtagEnabled|TRUE
!endif

  # Set this if the OS supports runtime pin muxing. This will leave pins as
  # GPIO by default, and it is the OS's responsibility to mux them away.
  gPi2BoardTokenSpaceGuid.PcdRuntimeMuxingEnabled|TRUE

[PcdsDynamicDefault]
  # This Pcd is declared as both Fixed and Dynamic in the Arm package dec file
  # The default is Fixed unless we redeclare it in the dsc as Dynamic
  # The value of 0 assigned here will be ignored, the actual PcdSystemMemorySize
  # will be calculated in runtime by means of UEFI<->VideoCore communication
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x0

[PcdsPatchableInModule]
  # Console Resolution
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1024
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|768


################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]

  #
  # SEC
  #
  ArmPlatformPkg/Sec/Sec.inf {
    <LibraryClasses>
      # Since the 2836 doesn't have an ARM GIC we use the BCM "stub" library instead to provide only
      # enough functionality to be able to get the platform started and support multi-processor through
      # the MP Parking Protocol. The BCM interrupt controller has no secure/none-secure knowledge.
      # Real interrupts for EFI are supported on the BCM part in the Interrupt DXE implementation.
      ArmGicLib|Pi2BoardPkg/Library/BcmGicLib/BcmGicLib.inf

      # Always use UART1 so we can verify both UART0 & UART1 work together when UART0 is enabled.
      SerialPortLib|Pi3BoardPkg/Library/SerialPortLib/SerialPortLib.inf

      # This is included so that the default configuration can be set based on the hardware settings.
      PL011UartLib|ArmPlatformPkg/Drivers/PL011Uart/PL011Uart.inf
  }

  #
  # PEI
  #
  # The Multi-Processor implementation is used that supports the Parking Protcol as required
  # by Windows.
  #
  ArmPlatformPkg/PrePi/PeiMPCoreMPPP.inf {
    <LibraryClasses>
      # Use the implementation which has the none-secure bits.
      ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf

      # Since the 2836 doesn't have an ARM GIC we use the BCM "stub" library instead to provide only
      # enough functionality to be able to get the platform started and support multi-processor through
      # the MP Parking Protocol. The BCM interrupt controller has no secure/none-secure knowledge.
      # Real interrupts for EFI are supported on the BCM part in the Interrupt DXE implementation.
      ArmGicLib|Pi2BoardPkg/Library/BcmGicLib/BcmGicLib.inf

      ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/PrePi/PrePiArmPlatformGlobalVariableLib.inf
  }

  #
  # DXE
  #
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      PcdLib|Pi2BoardPkg/Library/Pi2PcdLib/Pi2PcdLib.inf
      NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
      NULL|EmbeddedPkg/Library/LzmaHobCustomDecompressLib/LzmaHobCustomDecompressLib.inf
  }

  ArmPkg/Drivers/CpuDxe/CpuDxe.inf

  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/Variable/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
  EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf

  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  # Remove console splitter as it needs to be fixed to recognized valid
  # console input, output and error
  #MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  EmbeddedPkg/SerialDxe/SerialDxe.inf
  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf

  EmbeddedPkg/ResetRuntimeDxe/ResetRuntimeDxe.inf
  EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf

  #
  # Semi-hosting filesystem
  #
  ArmPkg/Filesystem/SemihostFs/SemihostFs.inf

  #
  # FAT filesystem + GPT/MBR partitioning
  #
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

  #
  # MMC/SD
  #
  Pi3BoardPkg/Drivers/MmcDxe/MmcDxe.inf
  Pi3BoardPkg/Drivers/SdHostDxe/SdHostDxe.inf

  #
  # ARM GIC+GIT Drivers
  #
  # NOTE: The BCM2836 does not include an ARM GIC so we must use
  #       a device specific driver for interrupts.
  #
  # IN GENERAL IT IS MANDATORY THAT DEVICES USE THE ARM GIC FOR INTERRUPTS
  # AND THE ARM GIT FOR TIMERS FOR WINDOWS SUPPORT.
  #
  Pi2BoardPkg/Drivers/InterruptDxe/InterruptDxe.inf
#  ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
  ArmPkg/Drivers/TimerDxe/TimerDxe.inf

  #
  # Display Support
  #
  Pi2BoardPkg/Drivers/DisplayDxe/DisplayDxe.inf

  #
  # ACPI Support
  #
  MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
  MdeModulePkg/Universal/Acpi/AcpiPlatformDxe/AcpiPlatformDxe.inf
!if $(CONFIG_TPM_ENABLE)
!if $(CONFIG_USE_DTPM)
  Pi3BoardPkg/AcpiTables/AcpiTablesWithDTpm.inf
!else
  Pi3BoardPkg/AcpiTables/AcpiTablesWithSTpm.inf
!endif
!else
  Pi3BoardPkg/AcpiTables/AcpiTables.inf
!endif

  #
  # SMBIOS Support
  #
  Pi3BoardPkg/Drivers/PlatformSmbiosDxe/PlatformSmbiosDxe.inf
  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf

  #
  # Bds
  #
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  ArmPlatformPkg/Bds/Bds.inf