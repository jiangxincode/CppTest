﻿#include <stdio.h>
#include <math.h>

double power(double x,int y)
{
    if(y==0)
    {
        return 1;
    }
    else if(y>0)
    {
        return x*power(x,y-1);
    }
    else
    {
        return power(x,y+1)/x;
    }
}
int main()
{
    double x;
    int y;
    printf("in put x,y  ");
    scanf("%20lf%11d",&x,&y);
    printf("%lf",power(x,y));
    return 0;
}

