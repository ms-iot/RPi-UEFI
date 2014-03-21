A. Overview
===========

The Panda packages are hosted on http://gitorious.org/omap-romcode/omap-edk2
This repository contains the latest developments concerning UEFI on PandaBoard.
Contact: o-deprez@ti.com

Patches from omap-edk2 tree are regularly merged on need basis to
http://git.linaro.org/gitweb?p=arm/uefi/uefi-next.git by Linaro maintainer.

B. Environment setup
====================

	1. Toolchain
	------------

PandaBoardPkg was built/tested using gcc version 4.6 on an Ubuntu Precise machine.

For a list of possible toolchains visit:
http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=ArmPkg/Toolchain

	2. Install necessary package
	----------------------------

Install uuid-dev package if not present already:

sudo apt-get install uuid-dev

C. Building
===========

Build information is found on uefi-next summary page:
http://git.linaro.org/gitweb?p=arm/uefi/uefi-next.git;a=summary

After cloning the Linaro EDK2 tree and before compiling the PandaBoardPkg,
you must apply following patch to ArmPlatformPkg:

  git apply PandaBoardPkg/patches/0001-Add-call-to-early-prepi-init-in-ModuleEntryPoint.patch

Compilation is done with following command:

  cd PandaBoardPkg
  ./build.sh -b RELEASE

Note: the Debug version is compiled by invoking build.sh without parameters or:

  ./build.sh -b DEBUG

D. Running EDK2 on Panda
========================

    1. UEFI Shell
    -------------

If you just intend to see how UEFI boots up and make a try with the shell, you
can do a raw copy of the firmware image to an SD card (e.g. /dev/sdc):

    dd if=edk2/Build/PandaBoard/RELEASE_ARMGCC/FV/MLO of=/dev/sdc

Open your favorite serial terminal e.g. 
    minicom -b 115200 -D /dev/ttyS0 -8 --color=on -w -o

Plug serial and power cables.

After few seconds, the following boot menu shall pop up:

    [1] Linux from SD
            - VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(1,MBR,0x00000000,0x3F,0
    x19FC0)/uImage
            - Initrd: VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(1,MBR,0x0000000
    0,0x3F,0x19FC0)/uInitrd
            - Arguments: console=ttyO2,115200n8 root=/dev/mmcblk0p2 earlyprintk root
    wait ro fixrtc nocompcache vram=48M omapfb.vram=0:24M
            - LoaderType: Linux kernel with global FDT
    -----------------------
    Global FDT Config
            - VenHw(100C2CFA-B586-4198-9B4C-1683D195B1DA)/HD(1,MBR,0x00000000,0x3F,0
    x19FC0)/board.dtb
    -----------------------
    [a] Boot Manager
    [b] Shell
    Start:

From there, type 'b' for starting the shell.

    2. Starting a Linux kernel
    --------------------------

Check following page: http://releases.linaro.org/13.01/ubuntu/panda

The easiest way is to get a full boot+filesystem image:
wget http://releases.linaro.org/13.01/ubuntu/boards/panda/panda-quantal_developer_20130128-58.img.gz

Unzip and dd to an sd card as described on Linaro's website.

Note: on OMAP, usage of earlyprintk statement on kernel command line looks incompatible with device tree.
Indeed early print routines use legacy machine type id to identify which uart module to use.
In case of device tree based boot  the machine type passed to kernel entry by Bds is 0xFFFFFFFF,
which is unknown to earlyprintk routines and result in a hang.

E. Boards tested
================

PandaBoard Rev EA2    - EBL and linux boot (PANDA_EDK2_080912)
PandaBoard Rev A3     - Shell and linux boot (PANDA_EDK2_030113)
PandaBoard ES Rev B1  - Shell (PANDA_EDK2_030113)

Note: Panda ES did not fully boot up linaro 13.01 image thru UEFI (stuck at L2 cache init).

F. chtool
=========

The PandaBoardPkg/Tools directory contains a tool called chtool for creating
a Configuration Header block for use with the ROM Code boot sequence (in this port
it serves as configuration of OMAP DPLLs, system clocks, and initlization of external SDRAM).

This tool is tracked in the following tree: git://gitorious.org/omap-romcode/chtool.git

The version of chtool present in PandaBoardPkg is v0.4.

G. History
==========

03/01/2013 PANDA_EDK2_030113
    Added patch early PrePi init patch to ArmPlatformPkg
	Board revision
	Cleaned up Pad conf
	Cleaned up setup clocks acceleration
	Enable 1GB support
	Add usb host support
	Use null sd card's uuid

01/28/2013 PANDA_EDK2_012813
    Created an edk2 top dir, moved packages in this dir

11/21/2012 PANDA_EDK2_112112
    Add TWL6030 PMIC support
    Update GPMC base address
	Remove unused drivers (Flash, MMCHSDxe, InterruptDxe, SemihostFs)
    Change PcdCoreCount to 2
	Change default boot type to Fdt
	Update linux machine type to PandaBoard

11/09/2012 PANDA_EDK2_110912
    Fix build.sh removing tmp.bin temporary file
    Fix SerialPollGetControl with returning correct Control parm
    Comment out Semihostfs from PandaBoardPkg.fdf

08/09/2012 PANDA_EDK2_080912
	Boots linux "OMAP Ubuntu Core" kernel

06/25/2012 PANDA_EDK2_062512
	First drop able to boot EBL

H. Resources
============

Panda Board - TI OMAP4
*http://pandaboard.org

Beagle Board - TI OMAP3
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=BeagleBoardPkg

ArmPlatformPkg - Generic package for ARM platforms
*http://sourceforge.net/apps/mediawiki/tianocore/index.php?title=ArmPlatformPkg

I. To do/next steps
===================

-Enable Network
-Enable display/gui
-Add a CHMMCSD item in ROM's Configuration Header to accelerate image copy from SD to external RAM

-DONE 03/01/2013 Enable USB host capability
-DONE 03/01/2013 Enable >512MiB external SDRAM
-DONE 03/01/2013 Clean PandaBoardLib for: detection of PandaBoard revision, pad conf, clocks speed up (if necessary)
-DONE 11/21/2012 Add PMIC management e.g. for SD card detection
-DONE 08/09/2012 Boot up linux kernel
-DONE 08/09/2012 Switch to linaro-uefi-2012.04 tag
