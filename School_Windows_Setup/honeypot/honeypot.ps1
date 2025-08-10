# Disable all Spectre/Meltdown mitigations
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverride" -Value 3 -Type DWord
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" -Name "FeatureSettingsOverrideMask" -Value 3 -Type DWord

# Disable Hypervisor protections
Disable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-All -NoRestart
bcdedit /set hypervisorlaunchtype Off

# Weaken Crypto Settings
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\SecurityProviders\SCHANNEL" -Name "Enabled" -Value 1

# Windows Components (via DISM)
Enable-WindowsOptionalFeature -Online -FeatureName "LegacyComponents" -All
Enable-WindowsOptionalFeature -Online -FeatureName "DirectPlay" -All