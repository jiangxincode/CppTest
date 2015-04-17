#include "unp.h"

int Socket(int family, int type, int protocol)
{
	int n;
	if((n = socket(family, type, protocol)) < 0)
	{
		err_sys("socket error");
	}
	return (n);
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

int Close(int fd)
{
	int n;
	if((n = close(fd)) < 0)
	{
		err_sys("close error");
	}
	return (n);
}
