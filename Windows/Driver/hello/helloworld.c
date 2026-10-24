// helloworld.c

#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJverObject)
{
    UNREFERENCED_PARAMETER(driverObject);
    KdPrint(("DriverUnload: Bye bye!\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PUNICODE_STRING registryPath)
{
    UNREFERENCED_PARAMETER(registryPath);

    KdPrint(("DriverEntry: Hello world driver demo!\n"));

    driverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}