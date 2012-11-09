
Overview
=========

The Panda packages are hosted on http://gitorious.org/omap-romcode/omap-edk2
This repository contains the latest developments concerning UEFI on PandaBoard.
Contact: o-deprez@ti.com

Patches from omap-edk2 tree are regularly merged on need basis to
http://git.linaro.org/gitweb?p=arm/uefi/uefi-next.git by ARM LT team.

History
========

11/09/2012 PANDA_EDK2_110912
    Rebased to uefi-next commit-id 99af201b87a6048c26f372e3f75a46d291b2f683
    Fix build.sh removing tmp.bin temporary file
    Fix SerialPollGetControl with returning correct Control parm
    Comment out Semihostfs from PandaBoardPkg.fdf

08/09/2012 PANDA_EDK2_080912
	Rebased to linaro-uefi-2012.04 label
	Boots linux "OMAP Ubuntu Core" kernel

06/25/2012 PANDA_EDK2_062512
	First drop able to boot EBL

Environment setup
==================

	1. General setup
	----------------

bash
mkdir panda_uefi; cd panda_uefi
export PANDA_UEFI=`pwd`

	2. Toolchain
	------------

For a list of possible toolchains visit:
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=ArmPkg/Toolchain

PandaBoardPkg was built using gcc version 4.5.1 (Sourcery G++ Lite 2010.09-51).
If you want to use the same compiler, use below commands (copy/paste from above webpage):

wget http://www.codesourcery.com/sgpp/lite/arm/portal/package7813/public/arm-none-eabi/arm-2010.09-51-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
tar xjf arm-2010.09-51-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
rm !$

$ Add arm gcc compiler to path
export PATH=$PANDA_UEFI/arm-2010.09/bin:$PATH

	3. Install necessary package
	----------------------------

# Install uuid-dev package if not present already
sudo apt-get install uuid-dev

Note: the build was done an Ubuntu 10.04 machine.

Building
=========

Build information is found on uefi-next summary page:
http://git.linaro.org/gitweb?p=arm/uefi/uefi-next.git;a=summary

cd PandaBoardPkg
./build.sh RELEASE

Note: you can build the debug version by invoking the build.sh command without parameters.

Running EDK2 on Panda
======================

    1. UEFI EBL shell
    -----------------

If you just intend to see how UEFI boots up and make a try with EBL, you
can just do a raw copy of the firmware image to an SD card (e.g. /dev/sdc):

    dd if=edk2/Build/PandaBoard/RELEASE_ARMGCC/FV/MLO of=/dev/sdc

Open your favorite serial terminal e.g. 
    minicom -b 115200 -D /dev/ttyS0 -8 --color=on -w -o

Plug serial and power cables.

After few seconds, you should see following boot menu:

    The default boot selection will start in   1 seconds
    ERROR: Did not find Linux kernel.
    [1] Linux from SD
    [2] EBL
    [3] Boot Manager
Start: 

[Type 2 for starting EBL.]

More info on EBL:
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=EDK_Boot_Loader_(EBL)_WiKi

    2. Starting a Linux kernel
    --------------------------

As a matter of testing linux boot, you can clone "OMAP Ubuntu Core" kernel, instructions located here:
*http://omappedia.org/wiki/OMAP_Ubuntu_Core

1. Copy/pasted the relevant commands for cloning and building omap linux kernel:

	bash
	export PATH=<path to your toolchain>:$PATH
	export ARCH=arm
	export CROSS_COMPILE=arm-none-linux-gnueabi-

	git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
	cd linux; git checkout -b v3.3-rc1 v3.3-rc1
	make omap2plus_defconfig
	make zImage 

2. InPandaBoardPkg.dsc, update the boot device path with the one matching your SD card:
	gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(1,MBR,0x00000000,0x3F,0x2348A)/zImage"

Note: this device path changes any time your swap/change SD card. If ever you need to boot up same build or another SD card, you need to re-build with updated device path.

3. Re-build PandaBoardPkg

4. Format the SD card with a FAT32 and an ext3 partiton

More information on how to format an SD card here:
*http://www.omappedia.com/wiki/SD_Configuration

5. Drop following files in FAT32 partition:
	edk2/Build/PandaBoard/RELEASE_ARMGCC/FV/MLO
	linux/arch/arm/boot/zImage generated at step 1

6. Insert SD card and boot up Panda board.
   You should see the boot menu and kernel starting after 3 seconds.

Boards tested
==================

PandaBoard Rev EA2    - EBL and linux boot (PANDA_EDK2_080912)
PandaBoard Rev A3     - EBL and linux boot (PANDA_EDK2_080912)
PandaBoard ES Rev B1  - EBL (PANDA_EDK2_062512)

chtool
=======

The PandaBoardPkg/Tools directory contains a tool called chtool for creating
a Configuration Header block for use with the ROM Code boot sequence (in this port
it serves as configuration of OMAP DPLLs, system clocks, and initlization of external SDRAM).

This tool is tracked in the following tree: git://gitorious.org/omap-romcode/chtool.git

The version of chtool present in PandaBoardPkg is v0.4.

Resources
=========

Panda Board - TI OMAP4
*http://pandaboard.org

Beagle Board - TI OMAP3
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=BeagleBoardPkg

ArmPlatformPkg - Generic package for ARM platforms
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=ArmPlatformPkg

To do/next steps
======================
-Enable >512MiB external SDRAM
-Add PMIC management e.g. for SD card detection
-Enable display/gui
-Clean PandaBoardLib for: detection of PandaBoard revision, pad conf, clocks speed up (if necessary)
-Add a CHMMCSD item in ROM's Configuration Header to accelerate image copy from SD to external RAM

-DONE 08/09/2012 Boot up linux kernel
-DONE 08/09/2012 Switch to linaro-uefi-2012.04 tag

