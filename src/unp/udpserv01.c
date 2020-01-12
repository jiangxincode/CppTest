#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    char mesg[MAXLINE];

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

    for( ; ; )
    {
        clilen = sizeof(cliaddr);
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, &cliaddr, &clilen);

        Sendto(sockfd, mesg, n, 0, &cliaddr, clilen);
    }
    
}
