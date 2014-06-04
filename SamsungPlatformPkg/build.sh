#!/bin/bash
unset ARCH
unset ARMLINUXGCC_TOOLS_PATH
unset EDK_TOOLS_PATH
unset WORKSPACE

if [ "$1" = "help" ]
then
        echo ""
        echo "USAGE:"
        echo "    ./build help      : shows this message"
        echo "    ./build           : build with BaseTools, GccShellPkg"
        echo "    ./build init      : build with BaseTools Only"
        echo "    ./build shell     : build with GccShellPkg Only"
        echo "    ./build arndale   : build with SamsungPlatformPkg for Arndale"
        echo ""
	exit 
fi

export ARMLINUXGCC_TOOLS_PATH=/usr/local/arm/bin/
export EDK_TOOLS_PATH=`pwd`/BaseTools
. ./edksetup.sh BaseTools

DEFINE_CMD=

for arg in "$@"; do
    args="${args} ${arg}"
done

DEFINE_CMD=$args



if [ "$1" = "arndale" ] 
then
	DEFINE_CMD=" -D EXYNOS5250_EVT1 -D DDR3"
else
	DEFINE_CMD=
fi

echo "  Parameter is ["$DEFINE_CMD"]"
if [ "$1" = "init" ]
then
	if [ ! -d BaseTools/Source/C/bin ]
	then
		cd ./BaseTools
		make clean
		cd ../
		make -C ./BaseTools
	else
		echo "Already build BaseTools....."
		echo ""
	fi

elif [ "$1" = "shell" ]
then
	if [ -d GccShellPkg ]
	then
		build -p GccShellPkg/GccShellPkg.dsc -a ARM -t ARMLINUXGCC -b DEBUG
		if [ -f Build/GccShellPkg/DEBUG_ARMLINUXGCC/ARM/ShellFull.efi ]
		then
			cp Build/GccShellPkg/DEBUG_ARMLINUXGCC/ARM/ShellFull.efi EdkShellBinPkg/FullShell/ARM/Shell_Full.efi
			echo "To copy ShellFull.efi to EdkShellBinPkg/FullShell/ARM is done......"
			echo ""
		fi
	else
		echo ""
		echo "Not found Directory : --------->  GccShellPkg !!!!"
		echo ""
		exit
	fi

elif [ "$1" = "arndale" ]
then
	if [ ! -d BaseTools/Source/C/bin ]
	then
		cd ./BaseTools
		make clean
		cd ../
		make -C ./BaseTools
	else
		echo "Already build BaseTools....."
		echo ""
	fi

	if [ -d SamsungPlatformPkg ]
	then
		build -p SamsungPlatformPkg/ArndaleBoardPkg/arndale-Exynos5250.dsc -a ARM -t ARMLINUXGCC -b DEBUG $DEFINE_CMD 
		echo "ARNDALE_EFI.fd can be found in path Build/Arndale-Exynos/DEBUG_ARMLINUXGCC/FV/"
	else
		echo ""
		echo "Not found Directory : --------->  SamsungPlatformPkg !!!!"
		echo ""
		exit
	fi

else
	# Build BaseTools
	if [ ! -d BaseTools/Source/C/bin ]
	then
		cd ./BaseTools
		make clean
		cd ../
		make -C ./BaseTools
	else
		echo "Already build BaseTools....."
		echo ""
	fi

	# Build GccShellPkg
	if [ -d GccShellPkg ]
	then
		build -p GccShellPkg/GccShellPkg.dsc -a ARM -t ARMLINUXGCC -b DEBUG
		if [ -f Build/GccShellPkg/DEBUG_ARMLINUXGCC/ARM/ShellFull.efi ]
		then
			cp Build/GccShellPkg/DEBUG_ARMLINUXGCC/ARM/ShellFull.efi EdkShellBinPkg/FullShell/ARM/Shell_Full.efi
			echo "To copy ShellFull.efi to EdkShellBinPkg/FullShell/ARM is done......"
			echo ""
		fi
	else
		echo ""
		echo "Not found Directory : --------->  GccShellPkg !!!!"
		echo ""
	fi

fi
