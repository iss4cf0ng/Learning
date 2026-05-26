// get_addr.cpp

#include <windows.h>
#include <cstdio>

int main()
{
    HMODULE user32 = LoadLibraryA("user32.dll");
    void *addr = (void *)GetProcAddress(user32, "MessageBoxA");
    printf("MessagBoxA is at: 0x%p\n", addr);

    return 0;
}