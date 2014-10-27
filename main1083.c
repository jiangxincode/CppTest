#include <stdio.h>
#include <math.h>
int main1083()
{
    double x,x1,eps=1e-6,f;
    x=3.1415926;

    do
    {
        x1=x;
        f=cos(x1)-x1;
        x=x1-f/(-sin(x1)-1);
        f=cos(x)-x;
    }
    while(fabs(f)>eps||fabs(x-x1));

    printf("x=%f",x);
    return 0;
}
