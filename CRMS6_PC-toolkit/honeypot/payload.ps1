Write-Host "[ OK ] Disable all Spectre/Meltdown mitigations to mimic an unpatched system"
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverride" -Value 3 -Type DWord
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverrideMask" -Value 3 -Type DWord

Write-Host "[ OK ] Change DNS"
$adapter = Get-NetAdapter | Where-Object {$_.Status -eq "Up"}

Set-DnsClientServerAddress -InterfaceIndex $adapter.InterfaceIndex -ServerAddresses ("1.1.1.1", "8.8.8.8")
