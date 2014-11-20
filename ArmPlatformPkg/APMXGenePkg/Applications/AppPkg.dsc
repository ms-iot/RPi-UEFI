##
#  Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
##

[Defines]
  PLATFORM_NAME                  = APMXGene-Mustang-Apps
  PLATFORM_GUID                  = 0c74c420-a335-11e3-a5e2-0800200c9a66
  PLATFORM_VERSION               = 0.01
  DSC_SPECIFICATION              = 0x00010006
  OUTPUT_DIRECTORY               = Build/APMXGene-Mustang
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

#
#  Debug output control
#
  # DEBUG_ASSERT_ENABLED       0x01
  # DEBUG_PRINT_ENABLED        0x02
  # DEBUG_CODE_ENABLED         0x04
  # CLEAR_MEMORY_ENABLED       0x08
  # ASSERT_BREAKPOINT_ENABLED  0x10
  # ASSERT_DEADLOOP_ENABLED    0x20
!if $(TARGET) == RELEASE
  DEFINE DEBUG_PROPERTY_MASK      = 0x21
  DEFINE DEBUG_ENABLE_OUTPUT      = FALSE       # Set to TRUE to enable debug output
!else
  DEFINE DEBUG_PROPERTY_MASK      = 0x2f
  DEFINE DEBUG_ENABLE_OUTPUT      = TRUE       # Set to TRUE to enable debug output
!endif
  
  DEFINE DEBUG_PRINT_ERROR_LEVEL  = 0x80000040  # Flags to control amount of debug output

[BuildOptions]
  GCC:*_*_AARCH64_ARCHCC_FLAGS = -mgeneral-regs-only -DARM_CPU_AARCH64 -DAPM_XGENE
  GCC:*_*_AARCH64_PP_FLAGS = -DARM_CPU_AARCH64
  GCC:*_*_AARCH64_PLATFORM_FLAGS == -I$(WORKSPACE)/ArmPlatformPkg/APMXGenePkg/Include -I$(WORKSPACE)/ArmPlatformPkg/APMXGenePkg/Modules/ArmPlatformPkg/Include -I$(WORKSPACE)/ArmPlatformPkg/APMXGenePkg/Modules/EmbeddedPkg/Include -I$(WORKSPACE)/ArmPlatformPkg/APMXGenePkg/Modules/MdePkg/Include

[PcdsFeatureFlag]

[PcdsFixedAtBuild]
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|$(DEBUG_PROPERTY_MASK)
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|$(DEBUG_PRINT_ERROR_LEVEL)
  #
  # ARM Architectual Timer Frequency
  #
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|50000000

[LibraryClasses]
  #
  # Entry Point Libraries
  #
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  #
  # Common Libraries
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  !if $(DEBUG_ENABLE_OUTPUT)
    DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
    DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  !else   ## DEBUG_ENABLE_OUTPUT
    DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  !endif  ## DEBUG_ENABLE_OUTPUT

  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf

  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  FileHandleLib|ShellPkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  SortLib|ShellPkg/Library/UefiSortLib/UefiSortLib.inf
  PathLib|MdeModulePkg/Library/BasePathLib/BasePathLib.inf

  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf

  ArmLib|ArmPkg/Library/ArmLib/AArch64/AArch64Lib.inf
  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf  
  I2CLib|ArmPlatformPkg/APMXGenePkg/Library/I2CLib/I2CLib.inf
  SlimproLib|ArmPlatformPkg/APMXGenePkg/Library/SlimproLib/SlimproLib.inf

###################################################################################################
#
# Components Section - list of the modules and components that will be processed by compilation
#                      tools and the EDK II tools to generate PE32/PE32+/Coff image files.
#
# Note: The EDK II DSC file is not used to specify how compiled binary images get placed
#       into firmware volume images. This section is just a list of modules to compile from
#       source into UEFI-compliant binaries.
#       It is the FDF file that contains information on combining binary files into firmware
#       volume images, whose concept is beyond UEFI and is described in PI specification.
#       Binary modules do not need to be listed in this section, as they should be
#       specified in the FDF file. For example: Shell binary (Shell_Full.efi), FAT binary (Fat.efi),
#       Logo (Logo.bmp), and etc.
#       There may also be modules listed in this section that are not required in the FDF file,
#       When a module listed here is excluded from FDF file, then UEFI-compliant binary will be
#       generated for it, but the binary will not be put into any firmware volume.
#
###################################################################################################

[Components]

#### Sample Applications.
  ArmPlatformPkg/APMXGenePkg/Applications/UpgradeFirmware/UpgradeFirmware.inf        # No LibC includes or functions.
  ShellPkg/Library/UefiShellLib/UefiShellLib.inf


##############################################################################
#
# Specify whether we are running in an emulation environment, or not.
# Define EMULATE if we are, else keep the DEFINE commented out.
#
# DEFINE  EMULATE = 1

##############################################################################
#
#  Include Boilerplate text required for building with the Standard Libraries.
#
##############################################################################
#!include StdLib/StdLib.inc
#!include AppPkg/Applications/Sockets/Sockets.inc
