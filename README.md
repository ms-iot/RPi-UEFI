# RaspberryPi2/3 UEFI
RaspberryPi UEFI is based on [Linaro EDK2](https://git.linaro.org/uefi/linaro-edk2.git) release 2015.01

You can grab latest RaspberryPi GPU Firmware binaries from here: https://github.com/raspberrypi/firmware. However, the GPU Firmware binaries (bootcode.bin, kernel.img, etc..) that come as part of Windows 10 IoT Core image for RaspberryPi are the only verified and guaranteed to work version.

For information on how to bring-up Windows 10 on a new device, please refer to [Windows 10 Bring-up Guide](https://msdn.microsoft.com/en-us/windows/hardware/drivers/bringup/index) and specifically [Boot and UEFI](https://msdn.microsoft.com/en-us/windows/hardware/drivers/bringup/boot-and-uefi) documentation as well as the UEFI to Windows Handoff Requirements [section 2.3.5 in UEFI 2.6 specifications](http://www.uefi.org/sites/default/files/resources/UEFI%20Spec%202_6.pdf).

# EDK2 Setup
**Important**: *The ```RPi-UEFI``` and ```Toolchains``` folder must be in the same location for the scripts in this repo to work. For example ```D:\RPi-UEFI``` and ```D:\Toolchains``` or ```C:\projects\rpi_image\RPi-UEFI``` and ```C:\projects\rpi_image\Toolchains```*
1. Clone repo to your machine at D:\RPi-UEFI for example. We will refer to that path as EDK_ROOT. `git clone https://github.com/ms-iot/RPi-UEFI.git`
2. Switch to branch ms-iot. `git checkout ms-iot`
3. Install [GNU ARM Embedded Toolchain 4.8 series](https://launchpad.net/gcc-arm-embedded/4.8) to D:\Toolchains\Arm

# Building
The output of compiling RaspberryPi2/3 UEFI is kernel.img which you put on the SDCard. If RaspberryPi can't find kernel.img on the SDCard it won't boot and it will just blink the green LED.

1. From a CMD window, run `BuildPi2Pi3Board.cmd` to build UEFI
  * To build a Pi2 ONLY UEFI, use BuildPi2Board.bat. Output kernel.img will be at %EDK_ROOT%\Build\Pi2Board\DEBUG_ARMGCC\kernel.img
  * To build a Pi3 ONLY UEFI, use BuildPi3Board.bat. Output kernel.img will be at %EDK_ROOT%\Build\Pi3Board\DEBUG_ARMGCC\kernel.img
  * To build a UEFI that boots both Pi2 and Pi3, use BuildPi2Pi3Board.bat. Output kernel.img will be at %EDK_ROOT%\Build\Pi2Pi3Board\DEBUG_ARMGCC\kernel.img
2. Copy kernel.img to the SDCard boot partition (e.g EFIESP) and overwrite the existing kernel.img

By default, EDK2 is configured to build DEBUG images. To change that to RELEASE instead, go to: %EDK_ROOT%\Conf\target.txt and locate the line with `TARGET = DEBUG` and change that to `TARGET = RELEASE` and rebuild. The output path DEBUG_ARMGCC part will change to RELEASE_ARMGCC.

===

This project has adopted the [Microsoft Open Source Code of Conduct](http://microsoft.github.io/codeofconduct). For more information see the [Code of Conduct FAQ](http://microsoft.github.io/codeofconduct/faq.md) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
