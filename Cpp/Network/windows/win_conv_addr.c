#undef UNICODE
#undef _UNICODE

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
    char *strAddr = "127.0.0.1:4444";

    char strAddrBuf[50];
    SOCKADDR_IN servAddr;
    int size;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    size = sizeof(servAddr);
    WSAStringToAddress(strAddr, AF_INET, NULL, (SOCKADDR *)&servAddr, &size);

    size = sizeof(strAddrBuf);
    WSAAddressToString((SOCKADDR *)&servAddr, sizeof(servAddr), NULL, strAddrBuf, &size);

    printf("Second conv result: %s\n", strAddrBuf);
    WSACleanup();

    return 0;
}