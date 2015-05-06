#include "unp.h"

ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwriten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if((nwriten = write(fd, vptr, n)) <= 0)
        {
            if(nwriten < 0 && errno == EINTR)
            {
                nwriten = 0; // and call write() again
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwriten;
        ptr += nwriten;
    }
    return (n);
}

