#include <iostream>
#include <windows.h>
#include <tchar.h>

#define DEBUG(__VA_ARGS__...) (fprintf(stderr, __VA_ARGS__))

ULONG hexdump(PUCHAR data, ULONG size)
{
    ULONG nResult = 0;
    for (ULONG i = 0; i < size; i += 16)
    {
        nResult += DEBUG("%08X |", i);
        for (ULONG j = 0; j < 16; j++)
        {
            if (i + j < size) {

            }
        }
    }

    return nResult;
}

int main()
{
    char aString[] = "Hello world!";
    int len = strlen(aString);
    hexdump((PUCHAR)aString, len);

    return 0;
}