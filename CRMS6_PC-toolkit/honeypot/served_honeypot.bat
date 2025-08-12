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
    echo Installing payload registry file: %payloadreg%
    reg import "%payloadreg%"
    echo.
    echo Disable Smart Screen
    echo [ OK ]
    echo.
    echo Disable Windows Defender
    echo [ OK ]
    echo.
    echo Disable Windows Firewall
    echo [ OK ]
    echo.
    echo Disable Windows Update
    echo [ OK ]
    echo.
    echo Disable User Access Control
    echo [ OK ]
    echo.
    echo Disable Action Center
    echo [ OK ]
    echo.
    echo Enable PowerShell Script Execution
    echo [ OK ]
    echo.
    echo Disable Spectre/Meltdown mitigations
    echo [ OK ]
    echo.  
    echo Allow SYN Floods
    echo [ OK ]
    echo. 
    echo Enable Remote Desktop
    echo [ OK ]
    echo.
    echo Weaken password policy
    echo [ OK ]
    echo.
    echo Enable SMBv1
    echo [ OK ]
    echo.
    echo Enable File and Printer Sharing
    echo [ OK ]
    echo.
) else (
    echo Payload registry not found: %payloadreg%
)

:: Serve payload.ps1
if exist "%payloadps1%" (
    echo.
    echo Serveing payload PowerShell script: %payloadps1%
    echo [ OK ]
    echo.
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
