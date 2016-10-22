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
::  Important Note: This script has to run from EDK2 root dir
::

@echo off
pushd %~dp0

set EDKROOT_DIR=%~dp0
:: Remove trailing backslash if exist
if "%EDKROOT_DIR:~-1%"=="\" set EDKROOT_DIR=%EDKROOT_DIR:~0,-1%
set SCRIPTS_DIR=%EDKROOT_DIR%\Pi3BoardPkg\Scripts
set PI3_PKG_PATH=%EDKROOT_DIR%\Pi3BoardPkg\Pi3BoardPkg.dsc

call %SCRIPTS_DIR%\BuildPiBoard Pi3 "%PI3_PKG_PATH%"

popd