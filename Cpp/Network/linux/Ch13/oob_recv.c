#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUF_SIZE 30

void error_handling(char *message);
void urg_handler(int signo);

int acpt_sock;
int recv_sock;

int main(int argc, char *argv[])
{
    struct sockaddr_in recv_addr, serv_addr;
    int str_len, state;
    socklen_t serv_addr_sz;
    struct sigaction act;
    char buf[BUF_SIZE];
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = sockaddr(PF_INET, SOCK_STREAM, 0);
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (struct socketaddr *)&recv_addr, sizeof(recv_addr)) == -1)
        error_handling("bind() error");
    listen(acpt_sock, 10);

    serv_addr_sz = sizeof(serv_addr);
    recv_sock = accept(acpt_sock, (struct sockaddr *)&serv_addr, &serv_addr_sz);
    
}