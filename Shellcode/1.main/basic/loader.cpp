// loader.cpp

#include <windows.h>
#include <cstdio>

/*
shellcode:

BITS 32
    xor eax, eax    ; zero out eax
    ret             ; return cleanly to caller
*/
unsigned char shellcode[] = {
    0x31, 0xc0,     // xor eax, eax
    0xc3,           // ret
};

int main(int argc, char *argv[])
{
    void* mem = VirtualAlloc(
        nullptr,
        sizeof(shellcode),
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!mem)
    {
        printf("VirtualAlloc failed: %lu\n", GetLastError());
        return 1;
    }

    memcpy(mem, shellcode, sizeof(shellcode));

    // cast to function pointer and call
    using ShellcodeFn = void(*)();
    auto fn = reinterpret_cast<ShellcodeFn>(mem);
    fn();

    printf("Shellcode is executed successfully.\n");

    // cleanup
    VirtualFree(mem, 0, MEM_RELEASE);

    return 0;
}