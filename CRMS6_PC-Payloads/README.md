# CRMS6 PC Payloads
This repository contains a collection of batch and PowerShell scripts designed to automate the setup and configuration of a Windows environment.
### [Clean Installation Windows 11 PC](https://github.com/neew1152/Clean-Installation-Windows-11-Personal-User)
<img width="960" height="540" alt="image" src="https://github.com/user-attachments/assets/b40b7d75-d14f-42f7-ba0b-32aa507894d9" />

---

## 🚨 WARNING: READ BEFORE USE 🚨

 ### Honeypot Payload
 The `honeypot` scripts are designed to **intentionally and severely weaken** a system's security defenses. They will:
 *   Disable Windows Defender (Antivirus)
 *   Disable Windows Firewall
 *   Disable User Account Control (UAC)
 *   Disable Windows Update
 *   Weaken password policies
 *   Enable insecure services like SMBv1 and Remote Desktop
 *   Disable CPU-level security mitigations (Spectre/Meltdown)

 **DO NOT RUN THESE SCRIPTS ON A PERSONAL, WORK, OR PRODUCTION COMPUTER.** Use them only on a completely isolated, disposable Virtual Machine (VM) intended for security research, malware analysis, or educational purposes. Running these scripts on a machine connected to a network could expose it and other devices to immediate compromise.

 ### Software Payload
 The `software` scripts automate the installation of legitimate software. However, they also include a command to run an **unofficial Microsoft Activation Script (`irm https://get.activated.win | iex`)**. Using such tools may violate Microsoft's license agreements and pose a potential security risk, as you are executing code from an untrusted third-party source. Use this feature at your discretion and understand the legal and security implications.

---

## Project Structure

```
main
│   README.md
│   served_payloads.bat
│
├───honeypot
│       payload.ps1
│       payload.reg
│       served_honeypot.bat
│
└───software
        payload.ps1
        served_software.bat
```

---

## Components Explained

### 1. Main Script (`served_payloads.bat`)

This is the central entry point for the entire collection. It provides a simple command-line menu to choose which payload(s) to execute.

*   **[1] Run honeypot_payloads**: Executes the scripts in the `honeypot` directory.
*   **[2] Run software_payloads**: Executes the scripts in the `software` directory.
*   **[3] Run all payloads**: Executes both the honeypot and software payloads sequentially.
*   **[0] Exit**: Closes the script.

The script automatically requests Administrator privileges, which are required for most of its operations.

### 2. Honeypot Payload (`/honeypot`)

This payload's goal is to make a Windows machine as insecure as possible to attract and study potential attacks.

*   **`served_honeypot.bat`**: The orchestrator for this payload. It displays a dramatic warning banner and requires confirmation before proceeding to apply the dangerous changes.
*   **`payload.reg`**: A registry file that systematically disables core security features like Windows Defender, SmartScreen, Firewall, UAC, Windows Update, and various security notifications. It also enables insecure protocols like SMBv1.
*   **`payload.ps1`**: A PowerShell script that complements the `.reg` file. It disables Spectre/Meltdown mitigations, enables Remote Desktop, weakens account password policies, activates the Guest account, and enables extensive security and network logging to monitor attacker activity.

### 3. Software Payload (`/software`)

This payload is designed for rapidly provisioning a machine with common software and utilities.

*   **`served_software.bat`**: A menu-driven script that first offers to download and install various retail versions of **Microsoft Office (2019, 2021, 2024, 365)** directly from Microsoft's CDN. It also downloads and initiates the installer for the **LINE messenger** client. Afterwards, it runs the accompanying `payload.ps1` script.
*   **`payload.ps1`**: A PowerShell script that performs the following actions:
    *   Installs **winget-cli** (The Windows Package Manager).
    *   Uses winget to install **7-Zip**, **Arduino IDE**, and **Google Chrome**.
    *   **Activates Windows and Office** using the online Microsoft Activation Scripts (MAS).
    *   Installs **.NET Framework 3.5**.

---

## How to Use

1.  Ensure you are running these scripts in a safe, isolated environment (preferably a VM that you can reset).
2.  Clone or download the repository to your target Windows machine.
3.  Navigate to the `main` directory.
4.  Right-click `served_payloads.bat` and select "Run as administrator," or simply double-click it and approve the UAC prompt for elevation.
5.  Follow the on-screen menu instructions to select and run the desired payload(s).
6.  The scripts require an active internet connection to download software installers.

## Prerequisites

*   Windows Operating System
*   Administrator privileges
*   An internet connection (for the software payload)

## Disclaimer

This project is provided for educational and research purposes only. The author is not responsible for any damage, data loss, or security compromises that may result from using these scripts. By running any of these scripts, you acknowledge the risks involved and agree that you are fully responsible for your actions.

## Credits

Maintained by neew1152  
Inspired by Mr. Robot themes
