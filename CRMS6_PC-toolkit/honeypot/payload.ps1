Write-Host "[ OK ] Disable all Spectre/Meltdown mitigations to mimic an unpatched system"
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverride" -Value 3 -Type DWord
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverrideMask" -Value 3 -Type DWord

Write-Host "[ OK ] Weaken Crypto Settings to allow outdated protocols"
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\SecurityProviders\SCHANNEL" -Name "Enabled" -Value 1

Write-Host "[ OK ] Allow Remote Desktop connections to lure attackers"
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Terminal Server" -Name "fDenyTSConnections" -Value 0 -Type DWord
Enable-NetFirewallRule -DisplayGroup "Remote Desktop"

Write-Host "[ OK ] Weaken password policy to attract brute-force attempts"
net accounts /minpwlen:4 /maxpwage:7

Write-Host "[ OK ] Enable detailed security event logging to capture attacker activity"
Auditpol /set /category:"System" /success:enable /failure:enable
Auditpol /set /category:"Logon/Logoff" /success:enable /failure:enable
Auditpol /set /category:"Object Access" /success:enable /failure:enable

Write-Host "[ OK ] Enable Guest account to make the system more accessible"
net user Guest /active:yes

Write-Host "[ OK ] Change DNS"
$adapter = Get-NetAdapter | Where-Object {$_.Status -eq "Up"}
Set-DnsClientServerAddress -InterfaceIndex $adapter.InterfaceIndex -ServerAddresses ("1.1.1.1", "8.8.8.8")