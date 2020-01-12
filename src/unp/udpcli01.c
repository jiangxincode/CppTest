#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    
    if(argc != 2)
    {
        err_quit("usage: udpcli <IPaddress>");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    while(Fgets(sendline, MAXLINE, stdin) != NULL)
    {
        Sendto(sockfd, sendline, strlen(sendline), 0, (SA*)&servaddr, sizeof(servaddr));
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
