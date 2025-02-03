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

int swap(UCHAR arr[256], ULONG i, ULONG j)
{
	arr[i] = arr[i] - arr[j];
	arr[j] = arr[i] + arr[j];
	arr[j] = arr[i] - arr[j];

	return 0;
}

int rc4_sbox_1(unsigned char sbox[256])
{
	for (int i = 0; i < 256; i++)
	{
		sbox[i] = i;
	}

	return 0;
}

int rc4_sbox_2(unsigned char sbox[256], const unsigned char* password)
{
	int len = strlen((char*)password);
	for (int i = 0, j = 0; i < 256; i++)
	{
		j = (j + sbox[i] + password[i % len]) % 256;
		swap(sbox, i, j);
	}

	return 0;
}

int rc4_encrypt(
	unsigned char sbox[256],
	unsigned char* data,
	int size,
	unsigned char* output
)
{
	for (int i = 0, j = 0, k, p = 0; p < size; p++)
	{
        i = (i + 1) % 256;
        j = (j + sbox[i]) % 256;

        swap(sbox, i, j);

        k = (sbox[i] + sbox[j]) % 256;
        output[p] = data[p] ^ sbox[k];
	}

    return 0;
}

int main()
{
	unsigned char sbox[256];
	unsigned char text[1024] = "this is a test";

	int len = strlen((char*)text);
	
	unsigned char cipher[1024];
	unsigned char plain[1024];

    //Init

	printf("Text:\n");
    hexdump(text, len);

    //Encryption

    rc4_sbox_1(sbox); //1-st stage
    rc4_sbox_2(sbox, (unsigned char *)"password"); //2-nd stage

    rc4_encrypt(sbox, text, len, cipher);

    printf("RC4 Encrypt:\n");
    hexdump(cipher, len);

    //Decryption

    rc4_sbox_1(sbox); //1-st stage
    rc4_sbox_2(sbox, (unsigned char*)"password"); //2-nd stage

    rc4_encrypt(sbox, cipher, len, plain);

    printf("RC4 Decrypt:\n");
    hexdump(plain, len);
}