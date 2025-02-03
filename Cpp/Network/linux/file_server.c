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
    int serv_sd, clnt_sd;
    FILE * fp;
    char buf[BUF_SIZE];
    int read_cnt;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    bind(serv_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_sd, 5);

    clnt_addr_sz = sizeof(clnt_addr);
    clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);

    while (1)
    {
        read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE)
        {
            write(clnt_sd, &buf, read_cnt);
            break;
        }
        write(clnt_sd, &buf, BUF_SIZE);
    }

    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s\n", buf);

    fclose(fp);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}