#
#  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.
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
  PLATFORM_NAME                  = ExynosPkg
  PLATFORM_GUID                  = 216e3ea0-f2b3-4d6f-a286-4d71431185c6
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/ExynosPkg
  SUPPORTED_ARCHITECTURES        = ARM
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  DEFINE TARGET_HACK             = DEBUG

[LibraryClasses.common]
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  ArmLib|ArmPkg/Library/ArmLib/ArmV7/ArmV7Lib.inf

  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf

  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf

  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf

  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf

  DmaLib|ArmPkg/Library/ArmDmaLib/ArmDmaLib.inf
  TimerLib|SamsungPlatformPkg/ExynosPkg/Library/TimerLib/TimerLib.inf
  UncachedMemoryAllocationLib|ArmPkg/Library/DebugUncachedMemoryAllocationLib/DebugUncachedMemoryAllocationLib.inf

  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf

[LibraryClasses.common.DXE_DRIVER]
 DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
 ExynosLib|SamsungPlatformPkg/ExynosPkg/Library/ExynosLib/ExynosLib.inf

[LibraryClasses.ARM]
  #
  # It is not possible to prevent the ARM compiler for generic intrinsic functions.
  # This library provides the instrinsic functions generate by a given compiler.
  # [LibraryClasses.ARM] and NULL mean link this library into all ARM images.
  #
  NULL|ArmPkg/Library/CompilerIntrinsicsLib/CompilerIntrinsicsLib.inf

[BuildOptions]
  RVCT:*_*_ARM_ARCHCC_FLAGS  == --cpu Cortex-A9 --thumb --fpu=softvfp
  RVCT:*_*_ARM_ARCHASM_FLAGS == --cpu Cortex-A9
  RVCT:RELEASE_*_*_CC_FLAGS  = -DMDEPKG_NDEBUG

  GCC:*_*_ARM_ARCHCC_FLAGS    == -march=armv7-a -mthumb
  GCC:*_*_ARM_ARCHASM_FLAGS   == -march=armv7-a
  GCC:RELEASE_*_*_CC_FLAGS    = -DMDEPKG_NDEBUG

  XCODE:*_*_ARM_ARCHCC_FLAGS     == -arch armv7 -march=armv7
  XCODE:*_*_ARM_ARCHASM_FLAGS    == -arch armv7
  XCODE:*_*_ARM_ARCHDLINK_FLAGS  == -arch armv7
  XCODE:RELEASE_*_*_CC_FLAGS     = -DMDEPKG_NDEBUG


################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]

[PcdsFixedAtBuild.common]

  gExynosPkgTokenSpaceGuid.PcdGdbUartBase|0x1000a000
  gExynosPkgTokenSpaceGuid.PcdConsoleUartBase|0x13810000
  gExynosPkgTokenSpaceGuid.PcdCmuBase|0x10030000
  gExynosPkgTokenSpaceGuid.PcdPWMTimerBase|0x139d0000
  gExynosPkgTokenSpaceGuid.PcdPmuBase|0x10020000
  gExynosPkgTokenSpaceGuid.PcdGpioPart1Base|0x11400000
  gExynosPkgTokenSpaceGuid.PcdGpioPart2Base|0x11000000
  gExynosPkgTokenSpaceGuid.PcdSdMmcBase|0x12530000
  gExynosPkgTokenSpaceGuid.PcdSysBase|0x10010000
  gExynosPkgTokenSpaceGuid.PcdFIMD0Base|0x11C00000
  gExynosPkgTokenSpaceGuid.PcdGICBase|0x10500000
  gExynosPkgTokenSpaceGuid.PcdTZPCBase|0x10100000

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  SamsungPlatformPkg/ExynosPkg/Library/GdbSerialLib/GdbSerialLib.inf
  SamsungPlatformPkg/ExynosPkg/Library/ResetSystemLib/ResetSystemLib.inf
  SamsungPlatformPkg/ExynosPkg/Library/SerialPortLib/SerialPortLib.inf
  SamsungPlatformPkg/ExynosPkg/Library/ExynosLib/ExynosLib.inf

  SamsungPlatformPkg/ExynosPkg/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  SamsungPlatformPkg/ExynosPkg/SDHCDxe/SDHCDxe.inf
  SamsungPlatformPkg/ExynosPkg/TimerDxe/TimerDxe.inf
  SamsungPlatformPkg/ExynosPkg/Gpio/Gpio.inf
