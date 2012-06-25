
Environment setup
==================

bash
mkdir panda_uefi; cd panda_uefi
export PANDA_UEFI=`pwd`

Toolchain
===========

For a list of possible toolchains visit:
    http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=ArmPkg/Toolchain

This package was built using gcc version 4.5.1 (Sourcery G++ Lite 2010.09-51).
If you want to use the same compiler, use below commands (copy/pasted from above webpage):

wget http://www.codesourcery.com/sgpp/lite/arm/portal/package7813/public/arm-none-eabi/arm-2010.09-51-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
tar xjf arm-2010.09-51-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
rm !$

Build setup
============

Note: the build was done an Ubuntu 10.04 machine.

$ Add arm gcc compiler to path
export PATH=$PANDA_UEFI/arm-2010.09/bin:$PATH

# Install uuid-dev package if not present
sudo apt-get install uuid-dev

# Clone Panda board pkg
cd $PANDA_UEFI
git clone git://gitorious.org/omap-romcode/omap-edk2.git
cd omap-edk2
git checkout PANDA_EDK2_062512

# Clone EDK2 from linaro
cd $PANDA_UEFI
git clone git://git.linaro.org/arm/uefi/uefi.git linaro-uefi-2012.01
cd linaro-uefi-2012.01
git checkout linaro-uefi-2012.01

#Apply base tools patches from ARM pkg
cd edk2
patch -p1 < ArmPlatformPkg/Documentation/patches/BaseTools-Pending-Patches.patch

#Apply PandaBoardPkg patch for fixing SD card driver
patch -p1 < PandaBoardPkg/patches/0001-fixes-sd-card-identification-on-panda.patch

# Link Panda pkgs to EDK2
ln -s $PANDA_UEFI/omap-edk2/PandaBoardPkg $PANDA_UEFI/linaro-uefi-2012.01/edk2
ln -s $PANDA_UEFI/omap-edk2/Omap44xxPkg $PANDA_UEFI/linaro-uefi-2012.01/edk2

# Build
cd PandaBoardPkg
./build.sh RELEASE

Note: you can build the debug version by invoking the build.sh command without parameters.

Running EDK2 on Panda
======================

    1. UEFI EBL shell

If you just intend to see how UEFI boots up and make a try with EBL, you
can just do a raw copy of the firmware image to an SD card (e.g. /dev/sdc):

    dd if=$PANDA_UEFI/linaro-uefi-2012.01/edk2/Build/PandaBoard/RELEASE_ARMGCC/FV/MLO of=/dev/sdc

Plug and play.

Alternatively, you can drop the MLO file to a fresh FAT32 formatted SD card.
More information on how to format an SD card here:

    http://www.omappedia.com/wiki/SD_Configuration

Boards tested
==================

PandaBoard Rev EA2
PandaBoard Rev A3
PandaBoard ES Rev B1

chtool
=======

The PandaBoardPkg/Tools contains a tool called chtool for creating a Configuration Header
block for use with the ROM Code boot sequence (in this port it serves as configuration of
OMAP DPLLs, system clocks, and initlization of external SDRAM).

This tool is tracked in the following tree: git://gitorious.org/omap-romcode/chtool.git

The version of chtool present in PandaBoardPkg is v0.4.

To do/next steps
======================
-Switch to linaro-uefi-2012.04 tag
-Configure clocks to OPP100 from uefi fw
-Add PMIC management e.g. for SD card detection
-Eanble display/gui
