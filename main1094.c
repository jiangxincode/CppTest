#include<stdio.h>
#include<math.h>
#include<conio.h>
#include "jiangxin.h"

int  guest(int t)
{
    int p;

    for(p=2; p<(t/2); p++)
    {
        if(prime(p)==1&&prime(t-p)==1&&p!=(t-p))
            printf("%d=%d+%d   ",t,p,t-p);
    }
}
main1094()
{
    int d;

    for(d=6; d<51; d=d+2)
    {
        if(guest(d)!=0)
            printf("%d  ",guest(d));
    }

    getch();
}


