# CRMS6 PC Toolkit
This toolkit contains a collection of batch and PowerShell scripts designed to automate the setup and configuration of a Windows environment.
### [Clean Installation Windows 11 PC](https://github.com/neew1152/Clean-Installation-Windows-11-Personal-User)

---

## Overview
<img width="1128" height="634" alt="image" src="https://github.com/user-attachments/assets/33bec98a-526a-455d-bd1c-d0daf16402d5" />

The CRMS6 PC Toolkit is a comprehensive system management tool designed for two primary purposes:
1. **Honeypot Configuration** - Deliberately weakens system security to attract attackers for monitoring
2. **Software Deployment** - Installs essential software packages with automated workflows

**Warning**: The honeypot component disables critical security features - use only in controlled environments

## Key Features
### Honeypot Module (`/honeypot`)
- Disables critical security protections:
  - Windows Defender & Firewall
  - SmartScreen and UAC
  - Spectre/Meltdown mitigations
  - Password complexity requirements
- Enables vulnerable services:
  - Remote Desktop (RDP)
  - SMBv1 protocol
  - Guest account
- Configures weak cryptography settings
- Enables detailed attack logging

### Software Module (`/software`)
- Installs essential development tools:
  - Arduino IDE, VS Code, microBlock IDE
- Deploys popular browsers:
  - Chrome, Firefox, Tor Browser
- Installs utilities:
  - Windows Camera, Microsoft Photos, 7-Zip, .NET Framework
- Microsoft Office deployment:
  - Supports 2019, 2021, 2024, and 365
- Specialized tools:
  - LINE messenger
  - c_robot robotics software
  - Faronics Deep Freeze system protection

## Usage Instructions
1. **Run the main menu**:
   ```batch
   served_payloads.bat
   ```
2. **Administrator Privileges**:
   - The toolkit will automatically request admin rights if needed

## Security Warning
The honeypot module deliberately weakens system security. Only use in:
- Controlled research environments
- Security training labs
- Authorized penetration testing scenarios

**Never deploy on production systems or internet-exposed machines**

## Disclaimer
This project is provided for educational and research purposes only. The author is not responsible for any damage, data loss, or security compromises that may result from using these scripts. By running any of these scripts, you acknowledge the risks involved and agree that you are fully responsible for your actions.

## Credits
Maintained by neew1152  
Inspired by Mr. Robot themes
