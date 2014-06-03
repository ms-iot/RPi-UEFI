#!/bin/bash

# set the default image filename, this can be overwritten by a parameter
IMAGE=../../../../Build/Arndale-Exynos/DEBUG_ARMLINUXGCC/FV/ARNDALE_EFI.fd

# set the default SoC, this can be overwritten by a parameter
SOC=5250

function usage
{
	echo "Usage: $0"
	echo "	--disk  path to the SD card device to write to, eg /dev/sdd"
	echo "	        This can be found by looking at dmesg output"
	echo "	--image The image to write to the SD card"
	echo "	        This defaults to:"
	echo "	            $IMAGE"
	echo "	--soc   Which SoC we are using"
	echo "	        This defaults to: 5250"
}

while [ "$1" != "" ]; do
    case $1 in
        -s | --soc )
			shift
			SOC=$1
            ;;

        -d | --disk )
			shift
			DISK=$1
            ;;

        -i | --image )
			shift
			IMAGE=$1
            ;;

        /h | /? | -? | -h | --help )
            usage
            exit
            ;;
        -* )
            usage
			echo "unknown arg $1"
            exit 1
    esac
    shift
done

echo "Config:"
echo "IMAGE    $IMAGE"
echo "SoC      $SOC"
echo "DISK     $DISK"


if [ ! -b "$DISK" ]
then
	echo "You must specify a valid --disk option"
	exit 1
fi

if [ ! -f $IMAGE ]
then
	echo ""
	echo "ERROR: UEFI image $IMAGE does not exist.."
	echo ""
	exit
fi

# make mkbl2
if [ ! -f mkbl2 ]
then
	make
fi

# make BL2
./mkbl2 $IMAGE

if [ ! -f fwbl2.bin ]
then
	echo ""
	echo "ERROR: Failed to create BL2 image."
	echo ""
	exit
fi

# select platform
if [ "$SOC" = "5250" ]
then
	# write BL1
	dd if=./5250/fwbl1_5250.bin of=$DISK seek=1 count=16
else
	echo ""
	echo "ERROR: Please select platform.."
	echo ""
	exit
fi


# write BL2
dd if=./fwbl2.bin of=$DISK seek=17 count=32

# write bootloader file e.g. u-boot or UEFI firmware image
dd if=$IMAGE of=$DISK seek=49

sync
