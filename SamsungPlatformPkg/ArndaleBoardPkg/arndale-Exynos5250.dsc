#
#  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = Arndale-Exynos-A15_MPCore
  PLATFORM_GUID                  = 66a5a01d-be0a-4398-9b74-5af4a261381f
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/Arndale-Exynos
  SUPPORTED_ARCHITECTURES        = ARM
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SamsungPlatformPkg/ArndaleBoardPkg/arndale-Exynos5250.fdf

!include SamsungPlatformPkg/ArndaleBoardPkg/ArndaleBoardPkg.dsc.inc

[LibraryClasses.common]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf
  ArmCpuLib|ArmPkg/Drivers/ArmCpuLib/ArmCortexA15Lib/ArmCortexA15Lib.inf
  ArmPlatformLib|SamsungPlatformPkg/ArndaleBoardPkg/Library/ArndaleBoardLib/Exynos5250/BoardLib.inf

  # Exynos5250 ArndaleBoard Specific Libraries
  SerialPortLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/SerialPortLib/SerialPortLib_Evt1.inf
  TimerLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/TimerLib/TimerLib.inf
  RealTimeClockLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/RealTimeClockLib/RealTimeClockLib.inf
  ExynosLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/ExynosLib/ExynosLib.inf
  EfiResetSystemLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/ResetSystemLib/ResetSystemLib.inf
  GdbSerialLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/GdbSerialLib/GdbSerialLib.inf
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf

  # ARM PL390 General Interrupt Driver in Secure and Non-secure
  ArmGicSecLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/Gic400Dxe/PL390GicSecLib.inf
  ArmGicLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/Gic400Dxe/PL390GicLib.inf
  ArmSmcLib|ArmPkg/Library/ArmSmcLibNull/ArmSmcLibNull.inf

[LibraryClasses.common.SEC]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7LibSec.inf

  ArmPlatformSecLib|SamsungPlatformPkg/ArndaleBoardPkg/Library/ArndaleBoardLib/Exynos5250/BoardSecLib.inf

[BuildOptions]
  RVCT:*_*_ARM_PLATFORM_FLAGS == --cpu Cortex-A8 --fpu=softvfp -I$(WORKSPACE)/SamsungPlatformPkg/ExynosPkg/Exynos5250/Include/Platform

  GCC:*_*_ARM_PLATFORM_FLAGS == -march=armv7-a -I$(WORKSPACE)/SamsungPlatformPkg/ExynosPkg/Exynos5250/Include/Platform

  XCODE:*_*_ARM_PLATFORM_FLAGS == -arch armv7 -I$(WORKSPACE)/SamsungPlatformPkg/ExynosPkg/Exynos5250/Include/Platform


################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
  gEfiMdePkgTokenSpaceGuid.PcdComponentNameDisable|FALSE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnosticsDisable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdComponentName2Disable|FALSE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnostics2Disable|TRUE

!ifdef $(EDK2_SKIP_PEICORE)
  gArmPlatformTokenSpaceGuid.PcdSystemMemoryInitializeInSec|TRUE
  gArmPlatformTokenSpaceGuid.PcdSendSgiToBringUpSecondaryCores|TRUE
!endif

  ## If TRUE, Graphics Output Protocol will be installed on virtual handle created by ConsplitterDxe.
  #  It could be set FALSE to save size.
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutGopSupport|TRUE

  # Install Debugger Exception Handlers.
  gArmTokenSpaceGuid.PcdDebuggerExceptionSupport|TRUE

  gEfiMdeModulePkgTokenSpaceGuid.PcdVariableCollectStatistics|TRUE

[PcdsFixedAtBuild.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"Exynos5250 Arndale"
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVersionString|L"0.90"
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPrompt|"ARNDALE%"
  gArmTokenSpaceGuid.PcdTrustzoneSupport|FALSE

  gArmTokenSpaceGuid.PcdArmScr|0x31

  # Stack for CPU Cores in Secure Mode
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecStackBase|0x4B000000
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecMonStackBase|0x4A000000
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0x48000000

  # Stacks for MPCores in Monitor Mode
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecMonStackBase|0x4A000000  # Top of SEC Stack for Monitor World
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecMonStackSize|0x2000		    # Stack for each of the 4 CPU cores

  # Non Sec UEFI Firmware: These two PCDs must match PcdFlashFvMainBase/PcdFlashFvMainSize
  gArmTokenSpaceGuid.PcdFdBaseAddress |0x40000000       # Must be equal to gEmbeddedTokenSpaceGuid.PcdFlashFvMainBase
  gArmTokenSpaceGuid.PcdFdSize|0x00200000              # Must be equal to gEmbeddedTokenSpaceGuid.PcdFlashFvMainSize

  # System Memory (256MB)
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x40000000
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x50000000

  #FDT offset
  gArmTokenSpaceGuid.PcdArmLinuxFdtMaxOffset|0x9000000

  # Size of the region used by UEFI in permanent memory (Reserved 64MB)
  gArmPlatformTokenSpaceGuid.PcdSystemMemoryUefiRegionSize|0x04000000

    # Framebuffer Base Address and size
  gExynosPkgTokenSpaceGuid.PcdFrameBufferBase|0x4E000000
  gExynosPkgTokenSpaceGuid.PcdFrameBufferSize|0x02000000

  gExynosPkgTokenSpaceGuid.PcdMpSharedArgsBase|0x4D000000
  gExynosPkgTokenSpaceGuid.PcdMpSharedArgsSize|0x100000

  # Memory Partition : Shared memory 1MB (0x4000_0000 -- 0x4010_0000)
  gExynosPkgTokenSpaceGuid.PcdSmemBaseAddress|0x40200000
  gExynosPkgTokenSpaceGuid.PcdSmemSize|0x00100000

  # Memory Partition : EMMC DMA buffer Address and Size 1MB (0x4030_0000 -- 0x4040_0000)
  gExynosPkgTokenSpaceGuid.PcdEmmcDMABufferBase|0x40300000
  #gExynosPkgTokenSpaceGuid.PcdEmmcDMABufferSize|0x00100000

  ## iRam Base Address and size.
  gExynosPkgTokenSpaceGuid.PcdiRamBootBase|0x02020000
  gExynosPkgTokenSpaceGuid.PcdiRamBootSize|0x00040000

  ## iRam Stack Base Address and size.
  gExynosPkgTokenSpaceGuid.PcdiRamStackBase|0x02050100
  gExynosPkgTokenSpaceGuid.PcdiRamStackSize|0x00000100

  gEmbeddedTokenSpaceGuid.PcdTimerPeriod|100000        # expressed in 100ns units, 100,000 x 100 ns = 10,000,000 ns = 10 ms

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x40200000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00020000     # 128K stack

  #
  # ARM Pcds
  #
  gArmTokenSpaceGuid.PcdArmUncachedMemoryMask|0x0000000040000000

  ## PL011 - Serial Terminal
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0x12C10000
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|115200

  #
  # ARM Exynos PCDS
  #
  gExynosPkgTokenSpaceGuid.PcdConsoleUartBase|0x12C20000
  gExynosPkgTokenSpaceGuid.PcdExynos5250Evt1|TRUE
  gExynosPkgTokenSpaceGuid.PcdWinDebugUartBase|0x12C30000
  gExynosPkgTokenSpaceGuid.PcdCmuBase|0x10010000
  gExynosPkgTokenSpaceGuid.PcdPWMTimerBase|0x12DD0000
  gExynosPkgTokenSpaceGuid.PcdPmuBase|0x10040000

  gExynosPkgTokenSpaceGuid.PcdGpioPart1Base|0x11400000
  gExynosPkgTokenSpaceGuid.PcdGpioPart2Base|0x13400000
  gExynosPkgTokenSpaceGuid.PcdGpioPart3Base|0x10D10000
  gExynosPkgTokenSpaceGuid.PcdGpioPart4Base|0x03860000

  gExynosPkgTokenSpaceGuid.PcdSdMmcCH0Base|0x12200000
  gExynosPkgTokenSpaceGuid.PcdSdMmcBase|0x12220000
  gExynosPkgTokenSpaceGuid.PcdSysBase|0x10050000
  gExynosPkgTokenSpaceGuid.PcdFIMD1Base|0x14400000
  gExynosPkgTokenSpaceGuid.PcdDSIM1Base|0x14500000
  gExynosPkgTokenSpaceGuid.PcdGICBase|0x10500000
  gExynosPkgTokenSpaceGuid.PcdTZPCBase|0x10100000
  gExynosPkgTokenSpaceGuid.PcdRtcBase|0x101E0000
  gExynosPkgTokenSpaceGuid.PcdCryptoBase|0x10830000

  #
  # ARM PL390 General Interrupt Controller
  #
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x10481000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x10482000
  #gArmTokenSpaceGuid.PcdGicNumInterrupts|160

  #
  # ARM Architectual Timer Frequency
  #
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|60000000


[PcdsPatchableInModule]
  ## This PCD defines the Console output column and the default value is 25 according to UEFI spec
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|53

  ## This PCD defines the Console output row and the default value is 80 according to UEFI spec
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|75


################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]

  #
  # SEC
  #
  #ArmPlatformPkg/Sec/Sec.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Sec/Sec.inf {
		<LibraryClasses>
      ArmGicLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/Gic400Dxe/PL390GicSecLib.inf
	}

  #
  # PEI Phase modules
  #
!ifdef $(EDK2_SKIP_PEICORE)
  ArmPlatformPkg/PrePi/PeiMPCore.inf {
    <LibraryClasses>
      ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf
      ArmPlatformLib|SamsungPlatformPkg/ArndaleBoardPkg/Library/ArndaleBoardLib/Exynos5250/BoardLib.inf
      ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/PrePi/PrePiArmPlatformGlobalVariableLib.inf
  }
!else
  ArmPlatformPkg/PrePeiCore/PrePeiCoreMPCore.inf {
    <LibraryClasses>
      ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/Pei/PeiArmPlatformGlobalVariableLib.inf
  }
  MdeModulePkg/Core/Pei/PeiMain.inf
  MdeModulePkg/Universal/PCD/Pei/Pcd.inf  {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }
  SamsungPlatformPkg/ExynosPkg/Exynos5250/PlatformPei/PlatformPeim.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/MemoryInitPei/MemoryInitPeim.inf
  ArmPkg/Drivers/CpuPei/CpuPei.inf
  IntelFrameworkModulePkg/Universal/StatusCode/Pei/StatusCodePei.inf
  MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
    <LibraryClasses>
      NULL|IntelFrameworkModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
!endif

  #
  # DXE
  #
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
      NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
  }

  #
  # Architectural Protocols
  #
  ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/Variable/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
  MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf
  EmbeddedPkg/ResetRuntimeDxe/ResetRuntimeDxe.inf
  EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf

  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
  EmbeddedPkg/SimpleTextInOutSerial/SimpleTextInOutSerial.inf

  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

  SamsungPlatformPkg/ArndaleBoardPkg/FvbDxe/FvbDxe.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/TimerDxe/TimerDxe.inf
  #
  # ACPI Support
  #
  MdeModulePkg/Universal/Acpi/AcpiPlatformDxe/AcpiPlatformDxe.inf
  MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf

  #
  # Samsung specific Driver
  #
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/Gic400Dxe/PL390GicDxe.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/Gpio/Gpio.inf{
    <LibraryClasses>
       ExynosLib|SamsungPlatformPkg/ExynosPkg/Exynos5250/Library/ExynosLib/ExynosLib.inf
  }

  #
  # Multimedia Card Interface
  #
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/eMMCDxe/eMMCDxe.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/SDHCDxe_EVT1/SDHCDxe.inf
  #
  # FAT filesystem + GPT/MBR partitioning
  #
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

  #
  # Application
  #
  #
  # Bds
  #
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  ArmPlatformPkg/Bds/Bds.inf

  #
  # VariableServicesTestNonSec
  #
  SamsungPlatformPkg/Apps/TestApps/VariableServicesTestNonSec/VariableServicesTestNonSec.inf

  #
  # TimeServicesTest
  #
  SamsungPlatformPkg/Apps/TestApps/TimeServicesTest/TimeServicesTest.inf

  #
  # MiscellaneousServicesTest
  #
  SamsungPlatformPkg/Apps/TestApps/MiscellaneousServicesTest/MiscellaneousServicesTest.inf

  #
  # usb host : ehci + bus + pci_emul + mass_storage
  #
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/PciEmulation/PciEmulation.inf
  MdeModulePkg/Bus/Pci/EhciDxe/EhciDxe.inf
  MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf

  #
  # Graphics for Exynos
  #
  MdeModulePkg/Universal/ReportStatusCodeRouter/Pei/ReportStatusCodeRouterPei.inf
  MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  SamsungPlatformPkg/ExynosPkg/Exynos5250/Drivers/DisplayDxe/DisplayDxe.inf

  MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTablePei/FirmwarePerformancePei.inf {
    <LibraryClasses>
      LockBoxLib|MdeModulePkg/Library/LockBoxNullLib/LockBoxNullLib.inf
  }

  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
  SamsungPlatformPkg/Apps/Tools/fwupdate/fwupdate_5250.inf

  #
  # Crypto for Exynos
  #

  #
  # Rng for Exynos
  #
