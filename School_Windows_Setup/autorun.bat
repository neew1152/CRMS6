@echo off
title Autorun

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Paths relative to this batch file
set "regfile=%basepath%honeypot\honeypot.reg"
set "ps1file=%basepath%honeypot\honeypot.ps1"

:: Run .reg file
if exist "%regfile%" (
    echo Importing registry file: %regfile%
    reg import "%regfile%"
) else (
    echo Registry file not found: %regfile%
)

:: Run .ps1 file
if exist "%ps1file%" (
    echo Running PowerShell script: %ps1file%
    powershell -ExecutionPolicy Bypass -File "%ps1file%"
) else (
    echo PowerShell file not found: %ps1file%
)

echo.
pause
