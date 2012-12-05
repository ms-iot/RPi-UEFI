#!/bin/bash


IMAGE=../../../../../edk2-git/edk2/Build/Arndale-Exynos/DEBUG_ARMLINUXGCC/FV/ARNDALE_EFI.fd

if [ $# -ne 2 ]
then
	echo ""
	echo "ERROR: Not input parameter for making image"
	echo ""
	echo "USAGE:"
	echo "    sudo ./imgburn.sh 5250 /dev/sdb"
	echo ""
	exit
fi

# make mkbl2
if [ ! -f mkbl2 ]
then
	make
fi

# make BL2
if [ -f $IMAGE ]
then
	./mkbl2 $IMAGE
	echo "BL2 image is created."
	echo ""
	echo ":::: You SHOULD check platform of ARNDALE_EFI.fd"
	echo ""
else
	echo ""
	echo "ERROR: UEFI is not built.."
	echo ""
	exit
fi

# select platform
if [ "$1" = "5250" ]
then
	# write BL1
	dd if=./5250/fwbl1_5250.bin of=$2 seek=1 count=16
else
	echo ""
	echo "ERROR: Please select platform.."
	echo ""
	exit
fi


# write BL2
dd if=./fwbl2.bin of=$2 seek=17 count=32

# write bootloader file e.g. u-boot or UEFI firmware image
dd if=$IMAGE of=$2 seek=49

sync
