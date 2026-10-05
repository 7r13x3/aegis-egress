# Architecture Map

| Layer | What It Must Spoof | Method | Ref |
|---|---|---|---|
| Kernel Driver | Disk, SMBIOS, NIC | IRP Hooking in storport.sys | Arty3/HWID-Spoofer |
| TPM Bypass | TPM 2.0 Attestation | Hypervisor MMIO Trapping | Void Permanent Spoofer |
| WMI Consistency | WMI/Registry Data | DLL Injection (CWbemObject::Get) | wmic_block |
| DMA Engine | N/A | DEAD FOR VALORANT (IOMMU bricking) | vibheksoni/dma-spoofer |
