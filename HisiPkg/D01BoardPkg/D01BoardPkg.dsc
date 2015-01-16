#
#  Copyright (c) 2011-2012, Hisilicon Limited. All rights reserved.
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
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
  PLATFORM_NAME                  = D01-A15_MPCore
  PLATFORM_GUID                  = 3a91a0f8-3af4-409d-a71d-a199dc134357
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/D01
  SUPPORTED_ARCHITECTURES        = ARM
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = HisiPkg/D01BoardPkg/D01BoardPkg.fdf

!include HisiPkg/D01BoardPkg/D01BoardPkg.dsc.inc

[LibraryClasses.common]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf
  ArmCpuLib|ArmPkg/Drivers/ArmCpuLib/ArmCortexA15Lib/ArmCortexA15Lib.inf
  ArmPlatformLib|HisiPkg/D01BoardPkg/Library/D01LibRTSM/D01Lib.inf
  
  ArmPlatformSysConfigLib|ArmPlatformPkg/ArmVExpressPkg/Library/ArmVExpressSysConfigLib/ArmVExpressSysConfigLib.inf
  NorFlashPlatformLib|ArmPlatformPkg/ArmVExpressPkg/Library/NorFlashArmVExpressLib/NorFlashArmVExpressLib.inf

  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf 
  

  NetLib|MdeModulePkg/Library/DxeNetLib/DxeNetLib.inf
  DpcLib|MdeModulePkg/Library/DxeDpcLib/DxeDpcLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  UdpIoLib|MdeModulePkg/Library/DxeUdpIoLib/DxeUdpIoLib.inf
  IpIoLib|MdeModulePkg/Library/DxeIpIoLib/DxeIpIoLib.inf

[LibraryClasses.common.SEC]
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7LibSec.inf
  ArmPlatformSecLib|HisiPkg/D01BoardPkg/Library/D01SecLibRTSM/D01SecLib.inf
  ArmPlatformLib|ArmPlatformPkg/ArmVExpressPkg/Library/ArmVExpressLibRTSM/ArmVExpressLibSec.inf

[BuildOptions]

  RVCT:*_*_ARM_PLATFORM_FLAGS == --cpu Cortex-A15 --fpu=softvfp -I$(WORKSPACE)/HisiPkg/Include/Platform

  GCC:*_*_ARM_PLATFORM_FLAGS == -march=armv7-a -I$(WORKSPACE)/HisiPkg/Include/Platform

  XCODE:*_*_ARM_PLATFORM_FLAGS == -arch armv7 -I$(WORKSPACE)/HisiPkg/Include/Platform

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
!ifdef $(EDK2_SKIP_PEICORE)
  gArmPlatformTokenSpaceGuid.PcdSystemMemoryInitializeInSec|TRUE
  gArmPlatformTokenSpaceGuid.PcdSendSgiToBringUpSecondaryCores|TRUE
!endif
  
  ## If TRUE, Graphics Output Protocol will be installed on virtual handle created by ConsplitterDxe.
  #  It could be set FALSE to save size.
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutGopSupport|FALSE
  
[PcdsFixedAtBuild.common]

  gArmPlatformTokenSpaceGuid.PcdFirmwareVendor|"ARM D01"
  
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPrompt|"D01"

  gArmPlatformTokenSpaceGuid.PcdCoreCount|2

  #
  # NV Storage PCDs. Use base of 0x0C000000 for NOR1
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0xf10C0000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize|0x00010000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|0xf10D0000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize|0x00010000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|0xf10E0000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize|0x00010000

  gArmTokenSpaceGuid.PcdVFPEnabled|0
  
  # Stacks for MPCores in Secure World
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecStackBase|0x40000000
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecPrimaryStackSize|0x8000
  
  # Stacks for MPCores in Monitor Mode
  gArmPlatformTokenSpaceGuid.PcdCPUCoresSecMonStackBase|0x40028000
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecMonStackSize|0x8000

  gHwTokenSpaceGuid.PcdEmbeddedBiosVersion|"Linaro_BIOS_V1.9"
      
 
  # System Memory (1GB) 
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x10000000
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x60000000
  
  # Size of the region used by UEFI in permanent memory (Reserved 64MB)
  gArmPlatformTokenSpaceGuid.PcdSystemMemoryUefiRegionSize|0x60000000
    
  #
  # ARM Pcds
  #
  gArmTokenSpaceGuid.PcdArmUncachedMemoryMask|0x0000000040000000
  #
  # ARM PrimeCell
  #

  
  ## PL011 - Serial Terminal
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0xe4007000
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|115200
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultDataBits|8
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultParity|1
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultStopBits|1

  gEmbeddedTokenSpaceGuid.PcdTimerPeriod|10000

  
  #
  # ARM PL390 General Interrupt Controller
  #
  gArmTokenSpaceGuid.PcdGicDistributorBase|0xe0C01000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0xe0C02000

  #
  # ARM OS Loader
  #
  # Versatile Express machine type (ARM VERSATILE EXPRESS = 2272) required for ARM Linux: 
  gArmTokenSpaceGuid.PcdArmMachineType|0xffffffff
  #gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"SemiHosting"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"Ramdisk"
  #gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(C5B9C74A-6D72-4719-99AB-C59F199091EB)/zImage"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenMsg(06ED4DD0-FF78-11D3-BDC4-00A0C94053D1,0000000000000000)/uImage"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootInitrdPath|L"VenMsg(06ED4DD0-FF78-11D3-BDC4-00A0C94053D1,0000000000000000)/initrd"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootArgument|"mem=256M console=ttyAMA0,115200"
  gArmPlatformTokenSpaceGuid.PcdDefaultBootType|1

  # Use the serial console (ConIn & ConOut) and the Graphic driver (ConOut)
  #gArmPlatformTokenSpaceGuid.PcdDefaultConOutPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8,N,1)/VenPcAnsi();VenHw(407B4008-BF5B-11DF-9547-CF16E0D72085)"
  #gArmPlatformTokenSpaceGuid.PcdDefaultConInPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8,N,1)/VenPcAnsi()"
  #gArmPlatformTokenSpaceGuid.PcdPlatformBootTimeOut|10

  #
  # ARM L2x0 PCDs
  #
  gArmTokenSpaceGuid.PcdL2x0ControllerBase|0xeE00A000
  
  #
  # ARM Architectual Timer Frequency
  #
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|50000000

  gHwTokenSpaceGuid.PcdNorFlashBase|0xf0000000

  gHwTokenSpaceGuid.PcdGPIO0Base|0xe4000000
  gArmTokenSpaceGuid.PcdSysCtrlBase|0xe3e00000
  gArmTokenSpaceGuid.PcdTimerBase|0xe3000000
  gArmTokenSpaceGuid.PcdTimer0InterruptNum|130
  
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVersionString|L"EVB_SECURE_UEFI_BIOS"
  
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  
  #
  # SEC
  #
  HisiPkg/D01BoardPkg/Sec/Sec/Sec.inf {
    <LibraryClasses>
      # Use the implementation which set the Secure bits
      #ArmGicLib|HisiPkg/Drivers/HisiliconD01Gic/HisiliconD01GicSecLib.inf
      ArmGicLib|ArmPkg/Drivers/ArmGic/ArmGicSecLib.inf
  }
  
  #
  # PEI Phase modules
  #
!ifndef $(EDK2_SKIP_PEICORE)
  ArmPlatformPkg/PrePi/PeiMPCore.inf{
    <LibraryClasses>
      ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf
      ArmPlatformLib|HisiPkg/D01BoardPkg/Library/D01LibRTSM/D01Lib.inf
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
  ArmPlatformPkg/PlatformPei/PlatformPeim.inf
  #ArmPlatformPkg/MemoryInitPei/MemoryInitPeim.inf
  ArmPkg/Drivers/CpuPei/CpuPei.inf
  IntelFrameworkModulePkg/Universal/StatusCode/Pei/StatusCodePei.inf
  Nt32Pkg/BootModePei/BootModePei.inf
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
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf
  MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  #MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf 
  EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
  EmbeddedPkg/ResetRuntimeDxe/ResetRuntimeDxe.inf
  EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf

  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
  EmbeddedPkg/SerialDxe/SerialDxe.inf

  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

  HisiPkg/Drivers/HisiliconD01Gic/HisiliconD01GicDxe.inf
  #ArmPkg/Drivers/ArmGic/ArmGicDxe.inf

  #ArmPlatformPkg/Drivers/NorFlashDxe/NorFlashDxe.inf
  #ArmPkg/Drivers/TimerDxe/TimerDxe.inf
  HisiPkg/Drivers/TimerDxe/TimerDxe.inf
  #ArmPlatformPkg/Drivers/LcdGraphicsOutputDxe/PL111LcdGraphicsOutputDxe.inf
  #ArmPlatformPkg/Drivers/SP805WatchdogDxe/SP805WatchdogDxe.inf 
  MdeModulePkg/Universal/Variable/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  #HisiPkg/Drivers/WatchDogDriver/WatchDogDriver.inf
  #

  #
  # Semi-hosting filesystem
  #
  #ArmPkg/Filesystem/SemihostFs/SemihostFs.inf
  
  # RamDisk filesystem
  #
  HisiPkg/Drivers/ramdisk/ramdisk.inf

  #HisiPkg/Drivers/FlashDriver/FlashDriver.inf
  
  #HisiPkg/Drivers/NandFlash/NandFlashDxe.inf

  #
  # Multimedia Card Interface
  #
  #EmbeddedPkg/Universal/MmcDxe/MmcDxe.inf
  #ArmPlatformPkg/Drivers/PL180MciDxe/PL180MciDxe.inf
  
  #
  # FAT filesystem + GPT/MBR partitioning
  #
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  #FatPkg/EnhancedFatDxe/Fat.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

  #
  # network
  #
  #HisiPkg/D01BoardPkg/Drivers/SnpPV600Dxe/SnpPV600Dxe.inf
  MdeModulePkg/Universal/Network/ArpDxe/ArpDxe.inf
  MdeModulePkg/Universal/Network/Dhcp4Dxe/Dhcp4Dxe.inf
  MdeModulePkg/Universal/Network/DpcDxe/DpcDxe.inf
  MdeModulePkg/Universal/Network/Ip4ConfigDxe/Ip4ConfigDxe.inf
  MdeModulePkg/Universal/Network/Ip4Dxe/Ip4Dxe.inf
  MdeModulePkg/Universal/Network/MnpDxe/MnpDxe.inf
  MdeModulePkg/Universal/Network/Mtftp4Dxe/Mtftp4Dxe.inf
  MdeModulePkg/Universal/Network/Tcp4Dxe/Tcp4Dxe.inf
  MdeModulePkg/Universal/Network/Udp4Dxe/Udp4Dxe.inf
  MdeModulePkg/Universal/Network/UefiPxeBcDxe/UefiPxeBcDxe.inf
  MdeModulePkg/Universal/Network/VlanConfigDxe/VlanConfigDxe.inf

  #
  # Application
  #  
  #EmbeddedPkg/Ebl/Ebl.inf
  #HisiPkg/D01BoardPkg/Application/Ebl/Ebl.inf

  #
  # Bds
  #
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  HisiPkg/D01BoardPkg/Bds/Bds.inf

  HisiPkg/Drivers/LinuxAtagList/LinuxAtagList.inf

  #HisiPkg/Drivers/AtaAtapiPassThru/AtaAtapiPassThru.inf
  MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
  
