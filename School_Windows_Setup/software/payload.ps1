# Install winget-cli
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
Install-Script -Name winget-install -Force
winget-install.ps1

# https://winget.run/
winget install -e --id 7zip.7zip
winget install -e --id ArduinoSA.IDE.stable
winget install -e --id Google.Chrome

# Microsoft Activation Scripts
irm https://get.activated.win | iex

# Install .NET Framework 3.5
Enable-WindowsOptionalFeature -Online -FeatureName "NetFx3" -All -NoRestart