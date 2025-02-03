#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    char msg1[] = "Hi!";
    char msg2[] = "hello world";
    char msg3[] = "Here is the test";

    struct sockaddr_in your_addr;
    socklen_t your_addr_sz;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&your_addr, 0, sizeof(your_addr));
    your_addr.sin_family = AF_INET;
    your_addr.sin_addr.s_addr = inet_addr(argv[1]);
    your_addr.sin_port = htons(atoi(argv[2]));

    your_addr_sz = sizeof(your_addr);
    sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&your_addr, your_addr_sz);
    sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr *)&your_addr, your_addr_sz);
    sendto(sock, msg3, sizeof(msg3), 0, (struct sockaddr *)&your_addr, your_addr_sz);

    close(sock);

    return 0;
}

void error_handling(char *message)
{

}