#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char *argv[])
{
    int sock;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); //my addr
    serv_adr.sin_port = htons(9190);

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect error");

    //read from server until close
    read_routine(sock, buf);

    close(sock);
    return 0;
}

void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if (str_len == 0){
            return;
        }

        buf[str_len] = 0;
        printf("Received: %s", buf);
    }
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
