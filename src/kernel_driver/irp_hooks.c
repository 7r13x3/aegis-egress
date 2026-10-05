#include "irp_hooks.h"

// Original function pointers (we save these to call the real function later)
PVOID g_OriginalDiskControl = NULL;
PVOID g_OriginalNicControl = NULL;

// ============================================================
// THE DISK HOOK
// ============================================================
// This is the core of the spoofer.
// Vanguard sends IOCTL_STORAGE_QUERY_PROPERTY to ask Windows:
// "What is the disk serial number?"
// We intercept that request, let the real driver answer,
// and then OVERWRITE the answer with our fake serial.

NTSTATUS HookedDiskControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    // 1. Call the original function first so the IRP completes normally
    NTSTATUS status = ((NTSTATUS(*)(PDEVICE_OBJECT, PIRP))g_OriginalDiskControl)(DeviceObject, Irp);
    
    // 2. If the call succeeded, we can modify the returned data
    if (NT_SUCCESS(status)) {
        PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
        ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

        // 3. Check if this is a storage query (the one Vanguard uses)
        if (code == IOCTL_STORAGE_QUERY_PROPERTY) {
            PSTORAGE_DEVICE_DESCRIPTOR descriptor = 
                (PSTORAGE_DEVICE_DESCRIPTOR)Irp->AssociatedIrp.SystemBuffer;
            
            if (descriptor && descriptor->SerialNumberOffset != 0) {
                // 4. Overwrite the real serial number with our fake one
                // TODO: Replace this with a dynamically generated fake serial
                char* fakeSerial = "FAKE-DISK-SERIAL-0001";
                char* realSerialLocation = (char*)descriptor + descriptor->SerialNumberOffset;
                RtlCopyMemory(realSerialLocation, fakeSerial, strlen(fakeSerial) + 1);

                DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, 
                    "[Aegis] Disk Serial Spoofed.\n");
            }
        }
    }
    return status;
}

// ============================================================
// THE NIC HOOK
// ============================================================
// Vanguard also asks: "What is the MAC address of the network card?"
// We intercept and return a fake MAC.

NTSTATUS HookedNicControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    NTSTATUS status = ((NTSTATUS(*)(PDEVICE_OBJECT, PIRP))g_OriginalNicControl)(DeviceObject, Irp);
    
    if (NT_SUCCESS(status)) {
        // TODO: Intercept IOCTL_NDIS_QUERY_GLOBAL_STATS
        // TODO: Overwrite the MAC address with a fake one
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] NIC Hook Triggered.\n");
    }
    return status;
}

// ============================================================
// INITIALIZATION
// ============================================================
// This is where we find the target driver in memory and replace
// its function pointers with our hooks.

NTSTATUS InitializeIrpHooks(PDRIVER_OBJECT DriverObject) {
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] Initializing IRP Hooks...\n");
    
    // TODO: Find storport.sys in kernel memory
    // TODO: Find stornvme.sys in kernel memory
    // TODO: Save the original function pointers into g_OriginalDiskControl
    // TODO: Replace the function pointers with HookedDiskControl
    
    // For now, this is a placeholder.
    // The real implementation requires scanning kernel memory for driver objects.
    
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] IRP Hooks Initialized (Placeholder).\n");
    return STATUS_SUCCESS;
}

VOID RemoveIrpHooks() {
    // TODO: Restore original function pointers
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] IRP Hooks Removed.\n");
}
