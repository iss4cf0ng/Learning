// bsod.c

#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT driverObject)
{
    UNREFERENCED_PARAMETER(driverObject);
    KdPrint(("DriverUnload: out\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PUNICODE_STRING registryPath)
{
    UNREFERENCED_PARAMETER(registryPath);

    KdPrint(("DriverEntry: BSOD\n"));

    driverObject->DriverUnload = DriverUnload;

    KeBugCheckEx(0xDEADBEEF, 0x1111, 0x2222, 0x3333, 0x4444);

    return STATUS_SUCCESS;
}