# CRMS6 PC Payloads
A collection of Windows payload scripts designed for system configuration, security testing, and software deployment.

Warning: The honeypot payloads will significantly weaken your system's security. Only use in controlled, isolated environments.
### [Clean Installation Windows 11 PC](https://github.com/neew1152/Clean-Installation-Windows-11-Personal-User)
<img width="960" height="540" alt="image" src="https://github.com/user-attachments/assets/b40b7d75-d14f-42f7-ba0b-32aa507894d9" />

---

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Usage](#usage)
- [Security Considerations](#security-considerations)
- [Disclaimer](#disclaimer)

## Project Overview

CRMS6 PC Payloads is a toolkit for Windows system administrators and security researchers. It offers two primary functions:

1. **Honeypot Configuration**: Creates deliberately vulnerable systems for security testing and monitoring attacker behavior
2. **Software Deployment**: Installs common applications along with activation tools

**Note**: This toolkit contains scripts that modify system security settings. Use only in controlled environments for legitimate testing purposes.

## Features

### Honeypot Features
- Disables security features (Windows Defender, Firewall, SmartScreen)
- Weakens password policies to attract brute-force attempts
- Enables remote desktop access
- Disables Windows Update to mimic outdated systems
- Enables detailed security event logging to monitor attacker activity
- Configures system to appear as an unpatched, vulnerable target

### Software Deployment Features
- Installs Winget package manager
- Deploys common applications (7zip, Chrome, Arduino)
- Includes Microsoft Activation Scripts (MAS) for Windows activation
- Provides Office installation options (Microsoft 365, 2024, 2021, 2019)
- Installs LINE messenger
- Enables .NET Framework 3.5

## Directory Structure

```
main/
├── served_payloads.bat          # Main menu interface
├── honeypot/
│   ├── payload.ps1              # PowerShell script for security weakening
│   ├── payload.reg              # Registry modifications for vulnerabilities
│   └── served_honeypot.bat      # Execution script for honeypot setup
└── software/
    ├── payload.ps1              # PowerShell script for software installation
    └── served_software.bat      # Execution script for software deployment
```

## Usage

1. Run `served_payloads.bat` as administrator
2. Choose from the menu options:
   - **Option 1**: Configure a honeypot system (deliberately vulnerable)
   - **Option 2**: Install software packages
   - **Option 3**: Run both the honeypot configuration and the software installation
   - **Option 0**: Exit

### Honeypot Configuration
- When selecting the honeypot option, you'll see a security warning banner
- Confirm you understand the risks by selecting option 1
- The system will automatically:
  * Import registry modifications (`payload.reg`)
  * Execute PowerShell security weakening commands (`payload.ps1`)

### Software Deployment
- When selecting the software option, you'll be prompted to choose:
  * Microsoft 365
  * Office 2024
  * Office 2021
  * Office 2019
  * Bypass Office installation
- After Office selection, the script will:
  * Download and extract the selected Office version
  * Install LINE messenger
  * Run the software installation PowerShell script

## Security Considerations

⚠️ **IMPORTANT**: This toolkit contains scripts that deliberately weaken system security. 

- **Never** run these scripts on production systems or personal computers
- Only use in isolated, controlled environments dedicated to security testing
- The honeypot configuration disables critical security features, including:
  * Windows Defender
  * Windows Firewall
  * SmartScreen protection
  * Security updates
  * UAC (User Account Control)
- Systems configured with the honeypot payloads will be extremely vulnerable to attacks

## Disclaimer

This toolkit is provided for educational and research purposes only. The authors are not responsible for any misuse of these tools. Use at your own risk in appropriate environments.

- The creator is not responsible for any misuse of these scripts
- Use only on systems you own or have explicit permission to test
- Microsoft Activation Scripts (MAS) are included for demonstration purposes only
- Bypassing software licensing agreements may violate terms of service and local laws

By using this toolkit, you agree to use it responsibly and only in appropriate, legal contexts.

## Credits

Maintained by neew1152  
Inspired by security research methodologies  
References Mr. Robot themes for educational purposes
