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
:: This scripts generates the machine code to get executed by all CPU cores from 
:: physical memory address 0
::

@echo off
setlocal
pushd %~dp0

:verifyenv

:verifyfilename
if "%1"=="" goto :verifyfilenameerror
set FILENAME=%1
goto :endverifyfilename
:verifyfilenameerror
goto :failedusage
:endverifyfilename

:verifysize
if "%2"=="" goto :verifysizeerror
set STARTUP_SIZE=%2
goto :endverifysize
:verifysizeerror
goto :failedusage
:endverifysize

:verifytempdir
if "%~3"=="" goto :verifytempdirerror
set TEMP_DIR=%~3
goto :endverifytempdir
:verifytempdirerror
goto :failedusage
:endverifytempdir

:endverifyenv

echo(
echo # Building %FILENAME%.S #
:: Build startup.S using GCC assembler which outputs the obj .elf file
arm-none-eabi-gcc.exe -c %FILENAME%.S -o "%TEMP_DIR%\%FILENAME%.o" -march=armv7-a
if %ERRORLEVEL% neq 0 goto :failed

:: Show generated objfile disassembly for verbosity
:: arm-none-eabi-objdump.exe -d "%TEMP_DIR%\%FILENAME%.o"

echo # Generating %FILENAME%.bin #
:: Strip out the executable machine code from the elf file leaving out all meta-data
:: --pad-to <size> appends the bin file with zeros to have total size of <size> bytes
arm-none-eabi-objcopy.exe "%TEMP_DIR%\%FILENAME%.o" -O binary --pad-to %STARTUP_SIZE% "%TEMP_DIR%\%FILENAME%.bin"
if %ERRORLEVEL% neq 0 goto :failed

:success
echo(
echo %FILENAME% Binary Blob Generation ## Succeeded ##
set EXITCODE=0
goto :exit

:failed
echo(
echo %FILENAME% Binary Blob Generation ## Failed ##
set EXITCODE=1
goto :exit

:failedusage
echo(
echo Error: Invalid usage %~nx0
echo Usage: %~nx0 ^<StartupFilenameOnly-NoExt^> ^<StartupOutputSize^> ^<TempDir^>
set EXITCODE=1
goto :exit

:exit
:: Cleanup: delete generated obj file
if exist "%TEMP_DIR%\%FILENAME%.o" ( del "%TEMP_DIR%\%FILENAME%.o" )

popd
exit /b %EXITCODE%