# CRMS6 PC Payloads System

<img width="960" height="540" alt="image" src="https://github.com/user-attachments/assets/b40b7d75-d14f-42f7-ba0b-32aa507894d9" />
### [Clean Installation Windows 11 PC](https://github.com/neew1152/Clean-Installation-Windows-11-Personal-User)

---

## Overview

This repository contains a set of scripts designed to:
1. Simulate a vulnerable honeypot system to attract and study attacker behavior
2. Install common software packages for system setup

**Warning**: The honeypot payloads will significantly weaken your system's security. Only use in controlled, isolated environments.

## Directory Structure

```
main/
├── served_payloads.bat          # Main menu system
├── honeypot/
│   ├── payload.ps1              # PowerShell script to weaken security
│   ├── payload.reg              # Registry modifications for vulnerabilities
│   └── served_honeypot.bat      # Honeypot deployment script
└── software/
    ├── payload.ps1              # Software installation script
    └── served_software.bat      # Office suite installer
```

## Usage Instructions

### Main Menu (served_payloads.bat)
Run this script to access the main menu:
1. Run honeypot payloads
2. Run software payloads
3. Run all payloads
0. Exit

The script will automatically request administrator privileges when needed.

### Honeypot Payloads
**Danger**: These scripts will:
- Disable Windows Defender and firewall
- Enable vulnerable protocols (SMBv1, RDP)
- Weaken password policies
- Disable security mitigations
- Enable extensive logging

Usage:
1. Run `served_honeypot.bat`
2. Confirm the warning message
3. The script will apply registry changes and PowerShell modifications

### Software Payloads
These scripts will install:
- 7-Zip
- Arduino IDE
- Google Chrome
- Microsoft Office suites (2019-2024 options)
- LINE desktop client
- .NET Framework 3.5

Usage:
1. Run `served_software.bat`
2. Select your preferred Office version
3. The script will download and install components

## Security Warning

The honeypot scripts:
- Should ONLY be used in controlled virtual environments
- Will make your system extremely vulnerable to attacks
- Are designed for security research purposes only
- May violate organizational security policies if used improperly

## Credits

Maintained by neew1152  
Inspired by security research methodologies  
References Mr. Robot themes for educational purposes

## Legal Disclaimer

This software is provided for educational and research purposes only. The authors are not responsible for any misuse of these tools. Use at your own risk in appropriate environments.
