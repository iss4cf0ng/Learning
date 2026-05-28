// loader.cpp

#include <windows.h>
#include <cstdio>
#include <cstring>

unsigned char shellcode[] = {
    0xe8, 0x23, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77,
    0x6f, 0x72, 0x6c, 0x64, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x6d, 0x73,
    0x67, 0x62, 0x6f, 0x78, 0x2e, 0x61, 0x73, 0x6d, 0x00, 0x54, 0x65, 0x73,
    0x74, 0x20, 0x32, 0x00, 0x5e, 0x6a, 0x00, 0x8d, 0x46, 0x1c, 0x50, 0x56,
    0x6a, 0x00, 0xb8, 0xef, 0xbe, 0xad, 0xde, 0xff, 0xd0, 0xc3
};

int main()
{
    HMODULE user32 = LoadLibraryA("user32.dll");
    DWORD fn = (DWORD)(uintptr_t)GetProcAddress(user32, "MessageBoxA");
    printf("[*] MessageBoxA = 0x%08X\n", fn);

    DWORD sentinel = 0xDEADBEEF;
    for (size_t i = 0; i < sizeof(shellcode) - 4; i++)
    {
        if (memcmp(shellcode + i, &sentinel, 4) == 0)
        {
            printf("[*] Patching at offset %zu\n", i);
            memcpy(shellcode + i, &fn, 4);

            break;
        }
    }

    void* mem = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(mem, shellcode, sizeof(shellcode));

    printf("[*] Jumping into shellcode...\n");
    
    ((void(*)())mem)();
    
    printf("[*] Returned cleanly.\n");

    VirtualFree(mem, 0, MEM_RELEASE);
    
    return 0;
}