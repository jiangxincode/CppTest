#include <sys/time.h>
#include <stdio.h>

int main0003()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday (&tv, &tz);
    printf("tv_sec; %d\n", (int)tv.tv_sec);
    printf("tv_usec; %d\n", (int)tv.tv_usec);
    printf("tz_minuteswest; %d\n", (int)tz.tz_minuteswest);
    printf("tz_dsttime, %d\n", (int)tz.tz_dsttime);
    return 0;
}
