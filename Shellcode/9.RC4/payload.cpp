// payload.cpp

#include <windows.h>

__declspec(dllexport)
void payload_run(void)
{
    MessageboxA(NULL, "Hello from RC4-ecnrypted sRDI.", "OK!", MB_OK);
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID r)
{
    return TRUE;
}