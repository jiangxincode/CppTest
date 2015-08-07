#include "unp.h"

int Socket(int family, int type, int protocol)
{
	int n;
	if((n = socket(family, type, protocol)) < 0)
	{
		err_sys("socket error");
	}
	return n;
}

int Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    int n;
    if((n = connect(sockfd, addr, addrlen)) < 0)
    {
        err_sys("connect error");
    }
    return 0;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int n;
	if((n = bind(sockfd, addr, addrlen)) < 0)
	{
		err_sys("bind error");
	}
	return (n);
}

int Listen(int sockfd, int backlog)
{
	int n;
	if((n = listen(sockfd, backlog)) < 0)
	{
		err_sys("listen error");
	}
	return(n);
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int n;
	if((n = accept(sockfd, addr, addrlen)) < 0)
	{
		err_sys("accept error");
	}
	return (n);
}

int Write(int fd, const void *buf, size_t count)
{
	int n;
	if((n = write(fd, buf, count)) < 0)
	{
		err_sys("write error");
	}
	return (n);
}

ssize_t Recvfrom(int sockfd, void *buff, size_t nbytes, int flags,
        struct sockaddr *from, socklen_t *addrlen)
{
    ssize_t n;
    if((n = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
    {
        err_sys("recvfrom error");
    }
    return n;
}

ssize_t Sendto(int sockfd, void *buff, size_t nbytes, int flags,
        const struct sockaddr *to, socklen_t addrlen)
{
    ssize_t n;
    if((n = sendto(sockfd, buff, nbytes, flags, to, addrlen)) < 0)
    {
        err_sys("sendto error");
    }
    return n;
}

int Close(int fd)
{
	int n;
	if((n = close(fd)) < 0)
	{
		err_sys("close error");
	}
	return (n);
}

pid_t Fork()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    return pid;
}


ssize_t Writen(int fd, const void *vptr, size_t n)
{
    ssize_t result;
    if((result = writen(fd, vptr, n)) < 0)
    {
        err_sys("writen error");
    }
    return (result);
}

ssize_t ReadLine(int fd, void *vptr, size_t maxlen)
{
    ssize_t result;
    if((result = readline(fd, vptr, maxlen)) < 0)
    {
        err_sys("readline error");
    }
    return result;
}

char* Fgets(char *s, int size, FILE *stream)
{
    char * result;
    if((result = fgets(s, size, stream)) == NULL)
    {
        err_sys("fgets error");
    }
    return result;
}

int Fputs(const char *s, FILE *stream)
{
    int result;
    if((result = fputs(s, stream)) < 0)
    {
        err_sys("fputs error");
    }
    return result;
}

int Inet_pton(int family, const char *strptr, void *addrptr)
{
    int n;
    if((n = inet_pton(family, strptr, addrptr)) <= 0)
    {
        err_sys("inet_pton error for %s", strptr);
    }
    return n;
}
