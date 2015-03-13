#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main0008()
{
    int x, y, k;
    x = 10;
    y = 10;
    fd_set file_rd;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    FD_ZERO(&file_rd);

    printf("\033[?25l");//隐藏光标
    for(;;)
    {
        if(k == 'l')	x++;
        if(k == 'h')	x--;
        if(k == 'j')	y++;
        if(k == 'k')	y--;
        fprintf(stderr, "\033[%d;%dHo", y, x);
        FD_SET(0, &file_rd);
        select(1, &file_rd, NULL, NULL, &tv);
        if(FD_ISSET(0, &file_rd))
        {
            k = getchar();
            fprintf(stderr, " ");
        }
        usleep(100000);
        fprintf(stderr, "\033[%d;%dH ", y, x);
    }
    printf("\033[30m\033[47m\n\n\n\n\n");
}

