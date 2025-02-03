#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt");

#ifdef _DEBUG
#define DEBUG(...) (_tprintf(stderr, __VA_ARGS__))
#else
#endif // _DEBUG

#ifdef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif // NT_SUCCESS
#ifdef STATUS_UNSUCCESSFUL
#define STATUS_UNSUCCESSFUL 0xC0000001
#endif // STATUS_UNSUCCESSFUL

#define CHECKERR(n, m) { if (!(NT_SUCCESS(n)) { printf("Error: %s\n", m); exit(1); } }

int rc4_sbox_1(unsigned char sbox[256])
{

}