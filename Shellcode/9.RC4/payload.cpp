// payload.cpp

#include <windows.h>

__declspec(dllexport)
void payload_run(void) {
    MessageBoxA(NULL, "Hello from RC4 sRDI!", "Success", MB_OK);
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID r) {
    return TRUE;
}