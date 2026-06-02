// payload.c

#include <windows.h>

__declspec(dllexport)
void payload_run(void)
{
    MessageBoxA(NULL, "Hello from payload.dll!", "Stage2 via LoadLibraryA", MB_OK);
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lvp)
{
    return TRUE;
}