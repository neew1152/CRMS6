@echo off
title served_payloads.bat

:: Get administrator permission
net session >nul 2>&1
if %errorLevel% neq 0 (
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Paths relative to this batch file
set "honeypot_payloads=%basepath%honeypot\served_honeypot.bat"
set "software_payloads=%basepath%software\served_software.bat"

:menu
cls
color 07
echo ===============================
echo       CRMS6 PC Playloads
echo            neew1152
echo ===============================
echo.
echo [1] Run honeypot_payloads
echo [2] Run software_payloads
echo [3] Run all payloads
echo [0] Exit
echo.
set /p choice="Enter your choice: "

if "%choice%"=="1" goto run_honeypot
if "%choice%"=="2" goto run_software
if "%choice%"=="3" goto run_all
if "%choice%"=="0" exit
goto menu

:run_honeypot
if exist "%honeypot_payloads%" (
    echo Running honeypot_payloads: %honeypot_payloads%
    call "%honeypot_payloads%"
) else (
    echo honeypot_payloads not found: %honeypot_payloads%
)
pause
goto menu

:run_software
if exist "%software_payloads%" (
    echo Running software_payloads: %software_payloads%
    call "%software_payloads%"
) else (
    echo software_payloads not found: %software_payloads%
)
pause
goto menu

:run_all
if exist "%honeypot_payloads%" (
    echo Running honeypot_payloads: %honeypot_payloads%
    call "%honeypot_payloads%"
) else (
    echo honeypot_payloads not found: %honeypot_payloads%
)

if exist "%software_payloads%" (
    echo Running software_payloads: %software_payloads%
    call "%software_payloads%"
) else (
    echo software_payloads not found: %software_payloads%
)

pause
goto menu
