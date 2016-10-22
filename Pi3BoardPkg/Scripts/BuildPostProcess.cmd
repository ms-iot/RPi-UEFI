::
::  Copyright (c), Microsoft Corporation. All rights reserved.
::
::  This program and the accompanying materials
::  are licensed and made available under the terms and conditions of the BSD License
::  which accompanies this distribution.  The full text of the license may be found at
::  http://opensource.org/licenses/bsd-license.php
::
::  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
::  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
::

@echo off
setlocal
pushd %~dp0

:verifyenv

:verifypiflavor
if "%~1"=="" goto :verifypiflavorerror
set PI_FLAVOR=%~1
if /I "%PI_FLAVOR%"=="Pi2" goto :endverifypiflavor
if /I "%PI_FLAVOR%"=="Pi3" goto :endverifypiflavor
if /I "%PI_FLAVOR%"=="Pi2Pi3" goto :endverifypiflavor
:verifypiflavorerror
goto :failedusage
:endverifypiflavor

:endverifyenv

set BOOT_IMAGE_NAME=kernel.img
set OUTPUT_DIR=%EDKROOT_DIR%\Build\%PI_FLAVOR%Board\%TARGET%_ARMGCC
set TEMP_DIR=%OUTPUT_DIR%\Temp
set PI2_IMAGE_FULLPATH=%EDKROOT_DIR%\Build\Pi2Board\%TARGET%_ARMGCC\FV\PI2BOARD_EFI.fd
set PI3_IMAGE_FULLPATH=%EDKROOT_DIR%\Build\Pi3Board\%TARGET%_ARMGCC\FV\PI3BOARD_EFI.fd

echo(
echo ## Pi Boot Image Post Process for TARGET=%TARGET% ##

if not exist "%OUTPUT_DIR%" ( md "%OUTPUT_DIR%" )
if not exist "%TEMP_DIR%" ( md "%TEMP_DIR%" )

echo(
echo # Generating startup.bin #

:: Build a 32KB startup.bin which gets prepended to the UEFI binary image
call startup_build.cmd startup 0x8000 "%TEMP_DIR%"
if %ERRORLEVEL% neq 0 (
    set EXITCODE=%ERRORLEVEL%
    goto :failed
)

echo(
echo Composing %PI_FLAVOR% %BOOT_IMAGE_NAME% ...

if /I "%PI_FLAVOR%"=="Pi2" (

    if not exist "%PI2_IMAGE_FULLPATH%" (
        echo Error: %PI2_IMAGE_FULLPATH% does not exist, build Pi2 %TARGET% package first
        set EXITCODE=1
        goto :failed
    )

    echo(
    echo # Composing %PI_FLAVOR% %BOOT_IMAGE_NAME% #

    REM Binary concatenate all blobs that make up the boot image to look as follows:
    REM +------------+  0x00000000
    REM |startup.bin |
    REM +------------+  0x00008000
    REM | Pi2 UEFI   |
    REM +------------+
    REM
    copy /b "%TEMP_DIR%\startup.bin" + "%PI2_IMAGE_FULLPATH%" "%OUTPUT_DIR%\%BOOT_IMAGE_NAME%"
    if %ERRORLEVEL% neq 0 (
        set EXITCODE=%ERRORLEVEL%
        goto :failed
    )
)

if /I "%PI_FLAVOR%"=="Pi3" (

    if not exist "%PI3_IMAGE_FULLPATH%" (
        echo Error: %PI3_IMAGE_FULLPATH% does not exist, build Pi3 %TARGET% package first
        set EXITCODE=1
        goto :failed
    )

    REM Generate a pad of zeros required by the boot image physical layout
    fsutil file createnew "%TEMP_DIR%\pad.bin" 0x100000
    if %ERRORLEVEL% neq 0 (
        set EXITCODE=%ERRORLEVEL%
        goto :failed
    )

    REM Binary concatenate all blobs that make up the boot image to look as follows:
    REM +------------+  0x00000000
    REM |startup.bin |
    REM +------------+  0x00008000
    REM | Pad        |
    REM +------------+  0x00108000
    REM | Pi3 UEFI   |
    REM +------------+
    REM
    copy /b "%TEMP_DIR%\startup.bin" + "%TEMP_DIR%\pad.bin" + "%PI3_IMAGE_FULLPATH%" "%OUTPUT_DIR%\%BOOT_IMAGE_NAME%"
    if %ERRORLEVEL% neq 0 (
        set EXITCODE=%ERRORLEVEL%
        goto :failed
    )
)

if /I "%PI_FLAVOR%"=="Pi2Pi3" (

    if not exist "%PI2_IMAGE_FULLPATH%" (
        echo Error: %PI2_IMAGE_FULLPATH% does not exist, build Pi2 %TARGET% package first
        set EXITCODE=1
        goto :failed
    )

    if not exist "%PI3_IMAGE_FULLPATH%" (
        echo Error: %PI3_IMAGE_FULLPATH% does not exist, build Pi3 %TARGET% package first
        set EXITCODE=1
        goto :failed
    )

    REM Generate a pad of zeros required by the boot image physical layout
    fsutil file createnew "%TEMP_DIR%\pad.bin" 0x28000
    if %ERRORLEVEL% neq 0 (
        set EXITCODE=%ERRORLEVEL%
        goto :failed
    )

    REM Binary concatenate all blobs that make up the boot image to look as follows:
    REM +------------+  0x00000000
    REM |startup.bin |
    REM +------------+  0x00008000
    REM | Pi2 UEFI   |
    REM +------------+
    REM | Pad        |
    REM +------------+  0x00108000
    REM | Pi3 UEFI   |
    REM +------------+
    REM
    copy /b "%TEMP_DIR%\startup.bin" + "%PI2_IMAGE_FULLPATH%" + "%TEMP_DIR%\pad.bin" + "%PI3_IMAGE_FULLPATH%" "%OUTPUT_DIR%\%BOOT_IMAGE_NAME%"
    if %ERRORLEVEL% neq 0 (
        set EXITCODE=%ERRORLEVEL%
        goto :failed
    )
)

echo Done Composing %BOOT_IMAGE_NAME%

:success
echo(
echo Build Post Process ## Succeeded ##
echo Created %BOOT_IMAGE_NAME% %TARGET% at %OUTPUT_DIR%\%BOOT_IMAGE_NAME%
set EXITCODE=0
goto :exit

:failed
echo(
echo Build Post Process ## Failed ##
set EXITCODE=1
goto :exit

:failedusage
echo(
echo Error: Invalid usage %~nx0
echo Usage: %~nx0 ^<Edk2RootPath^> (Pi2^|Pi3^|Pi2Pi3)
set EXITCODE=1
goto :exit

:exit
:: Cleanup: delete temp dir recursively
if exist "%TEMP_DIR%" ( rmdir /s /q "%TEMP_DIR%" )

popd
exit /b %EXITCODE%