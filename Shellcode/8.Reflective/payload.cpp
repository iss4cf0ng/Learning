// payload.cpp

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, "Reflective DLL Loaded via Network Stager!", "Success", MB_OK | MB_ICONINFORMATION);
            break;
    }
    return TRUE;
}