#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void HandlingError(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        return 0;
    }
    
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;

    char message[30];
    int str_len = 0;
    int idx = 0;
    int read_len = 0;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
        HandlingError("WSAStartup() error");

    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        HandlingError("connect() error");

    while (read_len = recv(hSocket, &message[idx++], 1, 0))
    {
        if (read_len == -1)
            HandlingError("read() error");

        str_len += read_len;        
    }

    printf("Message from server %s\n", message);
    printf("Function read call time: %d\n", str_len);

    closesocket(hSocket);
    WSACleanup();

    return 0;
}

void HandlingError(char *message)
{

}