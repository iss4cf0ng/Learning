// loader.cpp

#include <windows.h>
#include <cstdio>

int main()
{
    FILE *f = fopen("shellcode.bin", "rb");
    if (!f)
    {
        printf("[-] shellcode.bin not found\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *mem = (char *)VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    fread(mem, 1, size, f);

    fclose(f);

    printf("[*] %ld bytes at %p, executing...\n", size, mem);
    fflush(stdout);

    ((void(*)())mem)();
    printf("[*] returned\n");

    VirtualFree(mem, 0, MEM_RELEASE);

    return 0;
}