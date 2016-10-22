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
pushd %~dp0

:verifyenv

:verifyedkroot
if "%EDKROOT_DIR%"=="" goto :verifyedkrooterror
:: Remove trailing backslash if exist
if "%EDKROOT_DIR:~-1%"=="\" set EDKROOT_DIR=%EDKROOT_DIR:~0,-1%
goto :endverifyedkroot
:verifyedkrooterror
echo Error: EDKROOT_DIR not set
goto :failed
:endverifyedkroot

goto :endsetuparm

:setuparm
pushd %EDKROOT_DIR%
cd ..
set ROOT=%cd%
popd
set PATH=%ROOT%\EDK2\BaseTools\Bin;%ROOT%\EDK2\BaseTools\Bin\Win32;%ROOT%\ToolChains\Arm\bin;%PATH%;
set CROSS_COMPILE=arm-none-eabi-
call %EDKROOT_DIR%\edksetup.bat
if %ERRORLEVEL% neq 0 goto :failed
:endsetuparm

:verifyworkspace
if "%WORKSPACE%"=="" goto :verifyworkspaceerror
if not "%WORKSPACE%"=="%EDKROOT_DIR%" (
    echo Error: Supplied Edk2RootPath does not match WORKSPACE
    echo EDKROOT_DIR = %EDKROOT_DIR%
    echo WORKSPACE = %WORKSPACE%
    goto :failedusage
)
goto :endverifyworkspace
:verifyworkspaceerror
echo Build window not configured, configuring it ...
goto :setuparm
:endverifyworkspace

:verifyconftarget
set CONF_TARGET_PATH=%EDKROOT_DIR%\Conf\target.txt
if not exist %CONF_TARGET_PATH% goto verifyconftargeterror
goto :endverifyconftarget
:verifyconftargeterror
echo %CONF_TARGET_PATH% does not exit, regenerating it ...
goto :setuparm
:endverifyconftarget

:endverifyenv

BuildConfGetTarget.exe "%CONF_TARGET_PATH%"
if %ERRORLEVEL% equ 2 (
    set TARGET=DEBUG
    goto :success
)
if %ERRORLEVEL% equ 3 (
    set TARGET=RELEASE
    goto :success
)
echo Error: BuildConfGetTarget exit code not recognized as either RELEASE or DEBUG
goto :failed

:success
if not "%NUMBER_OF_PROCESSORS%"=="1" (
    title EDK2 - Multi-processor %TARGET% Compilation #Cores=%NUMBER_OF_PROCESSORS%
) else (
    title EDK2 - %TARGET%
)
echo(
echo Config %TARGET% Build Window ## Succeeded ##
set EXITCODE=0
goto :exit

:failed
echo(
echo Config Build Window ## Failed ##
set EXITCODE=1
goto :exit

:exit
popd
exit /b %EXITCODE%