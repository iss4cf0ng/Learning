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
        printf("Usage: %s <IP> <port>", argv[0]);
        exit(1);
    }

    int sd;
    FILE *fp;

    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_addr;

    fp = fopen("receive.dat", "wb");
    sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while ((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
        fwrite((void *)buf, 1, read_cnt, fp);

    puts("Received file data");
    write(sd, "bye", 4);

    fclose(fp);
    close(sd);

    return 0;
}

void error_handling(char *message)
{
    
}