﻿#include <stdio.h>

#include "../utility.h"

int main11bsl30()
{
    int n,i;
    double x,y;

    for(i=1; i<=8; i++)
    {
        x=1.0*i;
        printf("x=%2.1f\n",x);

        for(n=1; n<=4; n++)                        /* 变型第一类贝塞尔函数*/
        {
            y=bsl3(n,x);
            printf("I(%d)=%e ",n,y);
        }

        printf("\n");

        for(n=1; n<=4; n++)                       /* 变型第二类贝塞尔函数*/
        {
            y=bsl4(n,x);
            printf("K(%d)=%e ",n,y);
        }

        printf("\n");
    }

    getchar();
    return 0;
}
