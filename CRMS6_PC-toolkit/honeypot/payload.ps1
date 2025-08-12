# Disable all Spectre/Meltdown mitigations to mimic an unpatched system
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverride" -Value 3 -Type DWord
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverrideMask" -Value 3 -Type DWord

# Weaken Crypto Settings to allow outdated protocols
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\SecurityProviders\SCHANNEL" -Name "Enabled" -Value 1

# Allow Remote Desktop connections to lure attackers
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Terminal Server" -Name "fDenyTSConnections" -Value 0 -Type DWord
Enable-NetFirewallRule -DisplayGroup "Remote Desktop"

# Weaken password policy to attract brute-force attempts
net accounts /minpwlen:4 /maxpwage:7

# Enable detailed security event logging to capture attacker activity
Auditpol /set /category:"System" /success:enable /failure:enable
Auditpol /set /category:"Logon/Logoff" /success:enable /failure:enable
Auditpol /set /category:"Object Access" /success:enable /failure:enable

# Enable Guest account to make the system more accessible
net user Guest /active:yes
