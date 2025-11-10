@echo off
title served_software.bat
color 07

:: Get the folder where this batch file is located
set "basepath=%~dp0"

:: Ensure admin privileges
net session >nul 2>&1
if %errorLevel% neq 0 (
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

cd %basepath%

:OfficeMenu
echo =================================================================================
echo       ##########                                                           
echo   #################                                                        
echo ########## ########         #######      ######  ######  #                    
echo ######     ########       ###########    ###    ###                           
echo ######     ########      ####      ###   ###### ######  ###   ######  #######  
echo ######     ########      ###       ###   ###    ###     ### ####     ###   ### 
echo ######     ########      ####      ###   ###    ###     ### ###     ########## 
echo ######     ########       ####   #####   ###    ###     ### ####     ####     
echo ####       ########        #########     ###    ###     ###  #######  #######  
echo     ###############                                                        
echo       ###########                                                                                                                                      
echo =================================================================================
echo [1] Microsoft 365
echo [2] Office 2024
echo [3] Office 2021
echo [4] Office 2019
echo [0] Skip Office Installation
echo.
set /p choice="Enter your choice: "

if "%choice%"=="1" goto O365ProPlusRetail.img
if "%choice%"=="2" goto ProPlus2024Retail.img
if "%choice%"=="3" goto ProPlus2021Retail.img
if "%choice%"=="4" goto ProPlus2019Retail.img
if "%choice%"=="0" goto PromptLINE
goto OfficeMenu

:O365ProPlusRetail.img
echo.
echo [ OK ] Downloading O365ProPlusRetail.img...
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/O365ProPlusRetail.img"
echo [ OK ] Extracting O365ProPlusRetail.img...
tar -xf "O365ProPlusRetail.img" -C "./"
start "" "%basepath%Setup.exe"
goto PromptLINE

:ProPlus2024Retail.img
echo.
echo [ OK ] Downloading ProPlus2024Retail.img...
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2024Retail.img"
echo [ OK ] Extracting ProPlus2024Retail.img...
tar -xf "ProPlus2024Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto PromptLINE

:ProPlus2021Retail.img
echo.
echo [ OK ] Downloading ProPlus2021Retail.img...
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2021Retail.img"
echo [ OK ] Extracting ProPlus2021Retail.img...
tar -xf "ProPlus2021Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto PromptLINE

:ProPlus2019Retail.img
echo.
echo [ OK ] Downloading ProPlus2019Retail.img...
curl --ssl-no-revoke -LO "https://officecdn.microsoft.com/db/492350f6-3a01-4f97-b9c0-c7c6ddf67d60/media/en-us/ProPlus2019Retail.img"
echo [ OK ] Extracting ProPlus2019Retail.img...
tar -xf "ProPlus2019Retail.img" -C "./"
start "" "%basepath%Setup.exe"
goto PromptLINE

:PromptLINE
echo.
echo    +++++        +++++ ++++++    +++++ ++++++++++++   
echo    +++++        +++++ +++++++   +++++ ++++++++++++   
echo    +++++        +++++ ++++++++  +++++ +++++          
echo    +++++        +++++ +++++++++++++++ ++++++++++++   
echo    +++++        +++++ +++++++++++++++ ++++++++++++   
echo    +++++        +++++ +++++  ++++++++ +++++          
echo    ++++++++++++ +++++ +++++   +++++++ ++++++++++++   
echo    ++++++++++++ +++++ +++++     +++++ ++++++++++++
echo.  
set /p choice="Install LINE? (Y/N): "
if /i "%choice%"=="Y" goto InstallLINE
if /i "%choice%"=="N" goto PromptmicroBlock
goto PromptLINE

:InstallLINE
echo.
echo [ OK ] Downloading LineInst.exe...
curl --ssl-no-revoke -LO "https://desktop.line-scdn.net/win/new/LineInst.exe"
start "" "%basepath%LineInst.exe"
goto PromptmicroBlock


:PromptmicroBlock
echo.                                                                                                                       
echo  ++++++++  ++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo +++++++++++++++++++++++++++++  
echo ++++++++++ ++++ ++++      +    
echo +++++++++  ++++++ +++++++++ +  
echo +++++++++  ++++++++ +++  ++++  
echo ++++++++++ ++++ + +++++++++ ++ 
echo ++++++++++++++++++++++         
echo ++++++++++++++++++++++         
echo  +++++++++++++++++++++         
echo    ++++++++++++++++++       
echo.                                                                                                                                                
set /p choice="Install microBlock IDE? (Y/N): "
if /i "%choice%"=="Y" goto InstallmicroBlock
if /i "%choice%"=="N" goto Promptc_robot.exe
goto PromptmicroBlock


:InstallmicroBlock
echo.
echo [ OK ] Downloading microBlock.IDE.V3.0.0.win.x86-64.msi...
curl --ssl-no-revoke -LO "https://github.com/microBlock-IDE/microBlock-IDE-offline/releases/download/V3.0.0/microBlock.IDE.V3.0.0.win.x86-64.msi"
start "" "%basepath%microBlock.IDE.V3.0.0.win.x86-64.msi"
goto Promptc_robot.exe

:Promptc_robot.exe
echo.                                                                                                                       
echo            ###########+++------#  
echo   ##-.....------------.-----++-#  
echo   ##------------+-+       ++++-#  
echo   ##-++++++++++++   +###.   ##-## 
echo    ##+++#######+.  #######  ##### 
echo    ##+####++ +.## +#######-  #### 
echo    ######. ####.+..####### .##### 
echo    ######.#####+-##...-...+-##### 
echo    #######-####+#####+-########+# 
echo     ########################+-..##
echo     #######+--++++++++-+-+##-##+##
echo     ####++-+.- -.-.-.+###+.  ##++#
echo     ######++.+ - -.+ +###-+..+##++
echo     ###+-+-+-+-+.+ - +-. .+##-##--
echo    ####+..---++++--- .....-##.+-..
echo +#####+--.-.-.......            .+
echo  #.+##...                .---+    
echo    #.   ......---                   
echo.                                                                                                                                                
set /p choice="Install c_robot.exe? (Y/N): "
if /i "%choice%"=="Y" goto Copyc_robot.exe
if /i "%choice%"=="N" goto goto PromptDeepFreeze
goto Promptc_robot.exe

:Copyc_robot.exe
echo.
echo [ OK ] Extracting c_robot.tar...
tar -xf "c_robot.tar" -C "./"
copy "%basepath%\c_robot.exe" "C:\Users\Public\Desktop"
goto goto PromptDeepFreeze

:PromptDeepFreeze
echo.
echo           ............          
echo         .      ...   ....       
echo           ............ ....     
echo      .##-.-##########-.-##---   
echo    .-+ . #            # . ++--  
echo     .- #+              +# ----- 
echo  .. .###                +##. -- 
echo ..  .#.     +.    .+     .#..-++
echo .. ..#                    #..-++
echo ... .##.    -      -     +#..-+ 
echo  .. +#+#-..-+ +##+ +.   #+++ ++ 
echo  ... .--#+--#- .. -#. .#--. ++# 
echo   --.  ...####+--+#+##-..  +#+  
echo    ---.                  -+#    
echo      ---.              -+##     
echo        -++---......-+++##       
echo            ++++++++++                 
echo.  
set /p choice="Install Faronics Deep Freeze? (Y/N): "
if /i "%choice%"=="Y" goto InstallDeepFreeze
if /i "%choice%"=="N" goto ServePayload
goto PromptDeepFreeze

:InstallDeepFreeze
echo.
echo [ OK ] Extracting FaronicsDeepFreeze8.71.020.5734Standard.tar...
tar -xf "FaronicsDeepFreeze8.71.020.5734Standard.tar" -C "./"
echo [ OK ] Starting DFStd.exe...
start "" "%basepath%FaronicsDeepFreeze8.71.020.5734Standard\DFStd.exe"
goto ServePayload

:ServePayload
set "payloadps1=%basepath%payload.ps1"
if exist "%payloadps1%" (
    echo.
    echo [ OK ] Running payload PowerShell script...
    powershell -ExecutionPolicy Bypass -File "%payloadps1%"
) else (
    echo Payload PowerShell script not found!
)




