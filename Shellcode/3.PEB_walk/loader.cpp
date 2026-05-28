// loader.cpp

#include <windows.h>
#include <cstdio>

unsigned char shellcode[] = {
    0x64, 0xa1, 0x30, 0x00, 0x00, 0x00, 0x8b, 0x40, 0x0c, 0x8b, 0x40, 0x14,
    0x8b, 0x00, 0x8b, 0x00, 0x8b, 0x58, 0x10, 0x89, 0xd8, 0xc3
};

int main()
{
    void *mem = VirtualAlloc(nullptr, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!mem)
    {
        printf("[-] VirtualAlloc failed: %1u\n", GetLastError());
        return 1;
    }

    memcpy(mem, shellcode, sizeof(shellcode));

    // call shellcode: it returns kernel32 base in EAX
    using GetBaseFn = DWORD(*)();
    DWORD sc_base = ((GetBaseFn)mem)();

    DWORD real_base = (DWORD)(uintptr_t)GetModuleHandleA("kernel32.dll");

    printf("[shellcode] Kernel base = 0x%08X\n", sc_base);
    printf("[WinAPI] kernel32 base = 0x%08X\n", real_base);

    if (sc_base == real_base)
        printf("[+] MATCH! PEB walk works!\n");
    else
        printf("[-] MISMATCH! something went wrong :(\n");

    VirtualFree(mem, 0, MEM_RELEASE);
    return 0;
}