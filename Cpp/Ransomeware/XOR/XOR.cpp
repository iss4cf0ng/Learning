#include <stdio.h>
#include <Windows.h>

ULONG hexdump(PUCHAR data, ULONG size)
{
    ULONG nResult = 0;
    for (ULONG i = 0; i < size; i += 16)
    {
        printf("%08X |", i);

        nResult += 16;
        for (ULONG j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                nResult += printf(" %02X", data[i + j]);
            }
            else
            {
                nResult += printf(" 00");
            }
        }

        nResult += printf(" | ");
        for (ULONG j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                UCHAR k = data[i + j];
                UCHAR c = k < 32 || k > 127 ? '.' : k;
                nResult += printf("%c", c);
            }
            else
            {
                nResult += printf(" ");
            }
        }

        nResult += printf("\n");
    }

    return nResult;
}

BOOL do_xor(PUCHAR lpData, ULONG cbData, UCHAR c)
{
    for (ULONG i = 0; i < cbData; i++)
    {
        lpData[i] ^= c;
    }

    return TRUE;
}

int main()
{
    char text[] = "This is a test, hello world!";
    
    printf("Text:\n");
    hexdump((PUCHAR)text, strlen(text));

    do_xor((PUCHAR)text, strlen(text), 0xFC);

    printf("Encrypted:\n");
    hexdump((PUCHAR)text, strlen(text));

    do_xor((PUCHAR)text, strlen(text), 0XFC);
    
    printf("Decrypted:\n");
    hexdump((PUCHAR)text, strlen(text));

    return 0;
}