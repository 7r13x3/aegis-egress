# 2026 Vanguard Threat Model

## The Real Ops We Got

### 1. Hardware ID (HWID) Blacklisting
Vanguard enforces bans by blacklisting specific component IDs (CPU, Motherboard, Disk Serials). A recent case in October 2026 proved this is working as intended: a user bought a used AMD Ryzen 7 5800X3D and was immediately banned because that exact CPU's serial number had been blacklisted. The ban duration is four months, and it is tied to the physical CPU, not the account.

### 2. TPM 2.0 + Secure Boot + IOMMU + VBS + HVCI
As of 2026, Vanguard's "Pre-Check" system requires players to run Windows 11 25H2 or newer and have Secure Boot, TPM 2.0, IOMMU, VBS (Virtualization-Based Security), and Hypervisor-Protected Code Integrity (HVCI) all enabled. This is not optional. If any of these are disabled, Vanguard will not launch.

### 3. DMA Hardware Destruction
In May 2026, Riot deployed an update that uses IOMMU enforcement to generate repeated page faults that interfere with DMA cheat firmware, corrupting the FPGA and rendering both the DMA device and the associated SSD unusable. Riot publicly called the destroyed hardware "a $6k paperweight". If you were planning a DMA-based spoofer, that path is now a hardware death sentence.

### 4. Hypervisor Detection (VAN 9100)
Vanguard actively detects and blocks virtualized environments. Error code VAN 9100 means Vanguard has detected that the game is running in a virtual machine or unsupported virtualized environment. This means any hypervisor-based spoofer must be completely invisible to Vanguard's detection routines.

## The Only Viable Architecture
A Full-Spectrum Consistency Engine that solves the consistency problem across every surface Vanguard inspects.
