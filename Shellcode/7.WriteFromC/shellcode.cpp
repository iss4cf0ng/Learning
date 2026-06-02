#include <windows.h>
#include <winternl.h>

// Force section sorting alignment
#pragma code_seg(".text$A")

extern "C" void ShellcodeEntry();
extern "C" ULONG_PTR GetKernel32Base();
extern "C" ULONG_PTR CustomGetProcAddress(ULONG_PTR moduleBase, const char* funcName);

typedef HMODULE(WINAPI* fnLoadLibraryA)(LPCSTR);
typedef int(WINAPI* fnMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);

// Entry point is strictly forced to the front of the segment
extern "C" __attribute__((section(".text$A"))) void ShellcodeEntry() {
    ULONG_PTR kernel32 = GetKernel32Base();
    if (!kernel32) return;

    char strLoadLibrary[] = { 'L','o','a','d','L','i','b','r','a','r','y','A', 0 };
    fnLoadLibraryA pLoadLibraryA = (fnLoadLibraryA)CustomGetProcAddress(kernel32, strLoadLibrary);
    if (!pLoadLibraryA) return;

    char strUser32[] = { 'u','s','e','r','3','2','.','d','l','l', 0 };
    char strMessageBox[] = { 'M','e','s','s','a','g','e','B','o','x','A', 0 };
    char strTitle[] = { 'P','w','n','e','d','!', 0 };
    char strMsg[] = { 'H','e','l','l','o',' ','f','r','o','m',' ','C','!','!', 0 };

    HMODULE hUser32 = pLoadLibraryA(strUser32);
    if (!hUser32) return;
    
    fnMessageBoxA pMessageBoxA = (fnMessageBoxA)CustomGetProcAddress((ULONG_PTR)hUser32, strMessageBox);
    if (!pMessageBoxA) return;

    pMessageBoxA(NULL, strMsg, strTitle, MB_OK | MB_ICONINFORMATION);
}

// Helper functions sit safely behind the entry point
extern "C" __attribute__((section(".text$B"))) ULONG_PTR GetKernel32Base() {
    __asm__ (
        ".intel_syntax noprefix\n"
        "mov eax, fs:[0x30]\n"
        "mov eax, [eax + 0x0C]\n"
        "mov eax, [eax + 0x14]\n"
        "mov eax, [eax]\n"
        "mov eax, [eax]\n"
        "mov eax, [eax + 0x10]\n"
        "ret\n"
        ".att_syntax\n"
    );

    return 0;
}

extern "C" __attribute__((section(".text$C"))) ULONG_PTR CustomGetProcAddress(ULONG_PTR moduleBase, const char* funcName) {
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)moduleBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)(moduleBase + dosHeader->e_lfanew);
    DWORD exportDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    if (!exportDirRVA) return 0;

    PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY)(moduleBase + exportDirRVA);
    DWORD* nameRVAs = (DWORD*)(moduleBase + exportDir->AddressOfNames);
    WORD* ordinals = (WORD*)(moduleBase + exportDir->AddressOfNameOrdinals);
    DWORD* functions = (DWORD*)(moduleBase + exportDir->AddressOfFunctions);

    for (DWORD i = 0; i < exportDir->NumberOfNames; i++) {
        char* currentName = (char*)(moduleBase + nameRVAs[i]);
        
        // Fixed string comparison logic
        const char* f1 = funcName;
        char* f2 = currentName;
        while (*f1 && (*f1 == *f2)) { f1++; f2++; }
        
        if (*f1 == 0 && *f2 == 0) { 
            WORD ordinal = ordinals[i];
            return moduleBase + functions[ordinal];
        }
    }
    return 0;
}