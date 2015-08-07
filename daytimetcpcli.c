#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        err_quit("usage: a.out <IPaddress>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); /* daytime server */
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline, stdout) == EOF)
        {
            err_sys("fputs error");
        }
    }
    if(n < 0)
    {
        err_sys("read error");
    }
    exit(0);
}
