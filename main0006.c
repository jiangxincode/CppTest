//没看懂，运行也不知道要干什么？
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

void main0006()
{
    int i,k;
    fd_set file_rd;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    FD_ZERO(&file_rd);

    for(i = 0; i < 100; i++)
    {
        FD_SET(0, &file_rd);
        select(3, &file_rd, NULL, NULL, &tv);

        if(FD_ISSET(0, &file_rd))
        {
            fscanf(stdin, "%d", &k);
        }
        printf("%d\n", k);
        sleep(1);
    }
}

