﻿#include<stdio.h>
#include<math.h>

int main1052()
{
    unsigned int a;
    int n=1;
    printf("Input a unsigned int number:\n");
    scanf("%10u",&a);

    while(a>=10)
    {
        a=a/10;
        n=n+1;
    }

    printf("%d",n);
    return 0;
}

