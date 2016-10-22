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

call ConfigBuildWindow.cmd
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
echo Error: Invalid Pi flavor
goto :failedusage
:endverifypiflavor

:verifypkgpath
if /I "%PI_FLAVOR%"=="Pi2" (
    if "%~2"=="" goto :verifypkgpatherror
    set PI2_PKG_PATH=%~2
    goto :endverifypkgpath
)
if /I "%PI_FLAVOR%"=="Pi3" (
    if "%~2"=="" goto :verifypkgpatherror
    set PI3_PKG_PATH=%~2
    goto :endverifypkgpath
)
if /I "%PI_FLAVOR%"=="Pi2Pi3" (
    if "%~2"=="" goto :verifypkgpatherror
    set PI2_PKG_PATH=%~2
    if "%~3"=="" goto :verifypkgpatherror
    set PI3_PKG_PATH=%~3
    goto :endverifypkgpath
)
:verifypkgpatherror
echo Error: Invalid Pkg path
goto :failedusage
:endverifypkgpath

echo(
echo EDKROOT_DIR = %EDKROOT_DIR%
echo PI_FLAVOR = %PI_FLAVOR%
if /I "%PI_FLAVOR%"=="Pi2" echo PI2_PKG_PATH = %PI2_PKG_PATH%
if /I "%PI_FLAVOR%"=="Pi3" echo PI3_PKG_PATH = %PI3_PKG_PATH%
if /I "%PI_FLAVOR%"=="Pi2Pi3" echo PI2_PKG_PATH = %PI2_PKG_PATH%
if /I "%PI_FLAVOR%"=="Pi2Pi3" echo PI3_PKG_PATH = %PI3_PKG_PATH%

:endverifyenv

:buildstart

if /I "%PI_FLAVOR%"=="Pi2" build -p "%PI2_PKG_PATH%" -a ARM -n %NUMBER_OF_PROCESSORS% -t ARMGCC
if /I "%PI_FLAVOR%"=="Pi3" build -p "%PI3_PKG_PATH%" -a ARM -n %NUMBER_OF_PROCESSORS% -t ARMGCC
if /I "%PI_FLAVOR%"=="Pi2Pi3" build -p "%PI2_PKG_PATH%" -a ARM -n %NUMBER_OF_PROCESSORS% -t ARMGCC
if %ERRORLEVEL% neq 0 goto :failed
if /I "%PI_FLAVOR%"=="Pi2Pi3" build -p "%PI3_PKG_PATH%" -a ARM -n %NUMBER_OF_PROCESSORS% -t ARMGCC
if %ERRORLEVEL% neq 0 goto :failed

call BuildPostProcess.cmd %PI_FLAVOR%
if %ERRORLEVEL% neq 0 goto :failed

:success
echo(
echo %PI_FLAVOR% Boot Image Build ## Succeeded ##
set EXITCODE=0
goto :exit

:failed
echo(
echo %PI_FLAVOR% Boot Image Build ## Failed ##
set EXITCODE=1
goto :exit

:failedusage
echo(
echo Error: Invalid usage %~nx0
echo Usage: %~nx0 (Pi2 ^<Pi2PkgPath^>^|Pi3 ^<Pi3PkgPath^>^|Pi2Pi3 ^<Pi2PkgPath^> ^<Pi3PkgPath^>)
set EXITCODE=1
goto :exit

:exit
popd
exit /b %EXITCODE%