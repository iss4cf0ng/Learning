#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void HandlingError(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %S <IP> <port>\n", argv[0]);
        exit(1);
    }

    WSAData wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;

    char message[30];
    int str_len;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        HandlingError("WSAStartup() error!");

    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        HandlingError("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        HandlingError("connect() error");

    str_len = recv(hSocket, message, sizeof(message)-1, 0);
    if (str_len == -1)
        HandlingError("recv() error");
    printf("Message from server: %s\n", message);

    closesocket(hSocket);
    WSACleanup();

    return 0;
}

void HandlingError(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}