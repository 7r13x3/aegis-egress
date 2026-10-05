#pragma once
#include <ntddk.h>

// Initializes all IRP hooks for disk, SMBIOS, and NIC
NTSTATUS InitializeIrpHooks(PDRIVER_OBJECT DriverObject);

// Removes all hooks (called on driver unload)
VOID RemoveIrpHooks();

// The hook function that replaces the original disk handler
NTSTATUS HookedDiskControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);

// The hook function that replaces the original NIC handler
NTSTATUS HookedNicControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
