@echo off
title served_honeypot.bat
color 04

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Get administrator permission
net session >nul 2>&1
if %errorLevel% neq 0 (
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

cd %basepath%
echo ==========================================================
echo          !!!   S E C U R I T Y    B R E A C H   !!!
echo ==========================================================
echo.
echo          YOU are about to dismantle ALL defenses.
echo      YOU are about to install Exploit + Vulnerability.
echo        YOU are about to kill ALL Security Protocols.
echo.
echo                ( Worse than Evil Corp. )
echo.
echo ----------------------------------------------------------
echo         [ fsociety ]  :: GOD MODE ACCESS GRANTED
echo              "Trust me... watch Mr. Robot."
echo ----------------------------------------------------------
echo [Y] I will kill the Security
echo [N] Exit
echo.
set /p choice="Enter your choice: "
if "%choice%"=="Y" echo You will kill the Security
if "%choice%"=="N" exit
pause
:: Paths relative to this batch file
set "payloadreg=%basepath%payload.reg"
set "payloadps1=%basepath%payload.ps1"

:: Run payload.reg
if exist "%payloadreg%" (
    echo.
    echo [ OK ] Installing payload registry file: %payloadreg%
    reg import "%payloadreg%"
    echo [ OK ] Disable Windows Defender
    echo [ OK ] Disable Security and Cloud Reporting
    echo [ OK ] Disable Security Notifications
    echo [ OK ] Disable Windows Firewall
    echo [ OK ] Disable Network Protection
    echo [ OK ] Disable User Account Control
    echo [ OK ] Disable Windows SmartScreen
    echo [ OK ] Disable Controlled Folder Access
    echo [ OK ] Disable Attack Surface Reduction Rules
    echo [ OK ] Disable Spectre and Meltdown Mitigations
    echo [ OK ] Disable Control Flow Guard
    echo [ OK ] Disable Driver Signature Enforcement checks
    echo [ OK ] Disable Credential Guard and Device Guard
    echo [ OK ] Disable Antimalware Scan Interface
    echo [ OK ] Disable Windows Automatic Updates
    echo [ OK ] Disable Windows Telemetry
    echo [ OK ] Enable PowerShell Execution Policy Unrestricted
) else (
    echo Payload registry not found: %payloadreg%
)

:: Serve payload.ps1
if exist "%payloadps1%" (
    echo.
    echo [ OK ] Serveing payload PowerShell script: %payloadps1%
    powershell -ExecutionPolicy Bypass -File "%payloadps1%"
) else (
    echo Payload PowerShell not found: %payloadps1%
)

echo.                                                                      
echo    #+                                    ##               
echo    #=  #############-     =############  ##               
echo    #=  #####*.                   +#####  ##               
echo    #=  ###                          ###  ##               
echo    #=  #                              #  ##               
echo    #=                                    ##               
echo    #=                                    ##               
echo    #=  #                              *  ##               
echo    #=  +#  ##  *###        ###*  ##  *.  ##               
echo    #=  *#        .###+  +###.        #=  ##               
echo    #=  *            +    *            *  ##               
echo    #=     =   ####*        *####   +     ##               
echo    #=        #*+###        ###+*#        ##               
echo    #=                .                   ##               
echo    #=     +        .               =     ##               
echo    #=   -#.                        .#-   ##               
echo    #=   ###     +####   -####+     ###   ##               
echo    #=   ##############################   ##               
echo    #=   =############################    ##               
echo    #=  #-  .=+++*+  -+**+: .#*+==-    #  ##               
echo    #=  ##        *###########        ##  ##               
echo    #=  ###          ######          ###  ##               
echo    #=  ###                          ###  ##               
echo    #=  ###+                        -###  ##               
echo    #=  ####*                      =####  ##               
echo    #=  ######*                  +######  ##               
echo    #=  ========               .========  ##               
echo    #=                                    ##               
echo    ::::::::::::::::::::::::::::::::::::::::                 
echo       ____                _      __
echo      / __/________  _____(_)__  / /___  __
echo     / /_/ ___/ __ \/ ___/ / _ \/ __/ / / /
echo    / __(__  ) /_/ / /__/ /  __/ /_/ /_/ /
echo   /_/ /____/\____/\___/_/\___/\__/\__, /
echo                                  /____/

pause



