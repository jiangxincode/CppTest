#include "unp.h"

ssize_t writen(int fd, const void *vptr, size_t n)
{
    return (n);
}

ssize_t Writen(int fd, const void *vptr, ssize_t n)
{
    ssize_t result;
    if((result = writen(fd, vptr, n)) < 0)
    {
        err_sys("writen error");
    }
    return (result);
}
