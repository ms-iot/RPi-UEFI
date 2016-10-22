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
:: This helper script copies the boot image from its output dir to a destination dir
:: specified by a script parameter
::

@echo off

:verifyenv

call %~dp0ConfigBuildWindow.cmd
if %ERRORLEVEL% neq 0 goto :failed

:: Start localizing current script env vars only after setting the build
:: window, this will keep all vars defined by the config script global
:: across the build window, which avoids the need to rerun it again each
:: compilation
setlocal

:verifypiflavor
if "%~1"=="" goto :verifypiflavorerror
set PI_FLAVOR=%~1
if /I "%PI_FLAVOR%"=="Pi2" goto :endverifypiflavor
if /I "%PI_FLAVOR%"=="Pi3" goto :endverifypiflavor
if /I "%PI_FLAVOR%"=="Pi2Pi3" goto :endverifypiflavor
:verifypiflavorerror
goto :failedusage
:endverifypiflavor

:verifydeploydir
if "%~2"=="" goto :verifydeploydirerror
set DEPLOY_DIR=%~2
goto :endverifydeploydir
:verifydeploydirerror
goto :failedusage
:endverifydeploydir

:endverifyenv

set OUTPUT_DIR=%EDKROOT_DIR%\Build\%PI_FLAVOR%Board\%TARGET%_ARMGCC
set IMAGE_NAME=kernel.img

xcopy "%OUTPUT_DIR%\%IMAGE_NAME%" "%DEPLOY_DIR%" /Y /J
if %ERRORLEVEL% neq 0 goto :failed

:success
echo Copied %OUTPUT_DIR%\%IMAGE_NAME% to %DEPLOY_DIR%
echo(
echo Pi Boot %TARGET% Image Deploy ## Succeeded ##
set EXITCODE=0
goto :exit

:failed
echo(
echo Pi Boot %TARGET% Image Deploy ## Failed ##
set EXITCODE=1
goto :exit

:failedusage
echo(
echo Error: Invalid usage %~nx0
echo Usage: %~nx0 (Pi2^|Pi3^|Pi2Pi3) <DeployPath>
set EXITCODE=1
goto :exit

:exit
exit /b %EXITCODE%