#include <ntddk.h>

// Forward declaration for IRP hooking logic
NTSTATUS InitializeIrpHooks(PDRIVER_OBJECT DriverObject);

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] Driver Unloaded\n");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] Driver Loading...\n");
    
    // TODO: Uncomment this when we write the IRP hooking code
    // InitializeIrpHooks(DriverObject);
    
    DriverObject->DriverUnload = UnloadDriver;
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[Aegis] Driver Loaded Successfully.\n");
    return STATUS_SUCCESS;
}
