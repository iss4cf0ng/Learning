#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void HandlingError(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    int szClntAddr;
    char message[] = "Hello World";

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        HandlingError("WSAStartup() error!");

    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hServSock == INVALID_SOCKET)
        HandlingError("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        HandlingError("bind() error");

    if (listen(hServSock, 100) == SOCKET_ERROR)
        HandlingError("listen() error");

    szClntAddr = sizeof(clntAddr);
    hClntSock = accept(hServSock, (SOCKADDR *)&clntAddr, &szClntAddr);
    if (hClntSock == INVALID_SOCKET)
        HandlingError("accept() error");
    
    send(hClntSock, message, sizeof(message), 0);
    closesocket(hClntSock);
    closesocket(hServSock);
    WSACleanup();

    return 0;
}

void HandlingError(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}