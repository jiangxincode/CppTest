﻿#include <stdio.h>
#include <math.h>

double integral(double a,double b,double n)
{
    double e,h,m=0;
    int i;
    h=(b-a)/n;

    for(i=1; i<n; i++)
    {
        double d=a+i*h;
        double c=cos(d)+sin(d);
        m=m+c;
    }

    e=h*((cos(a)+sin(a)+cos(b)+sin(b))/2+m);
    return e;
}
int main()
{
    double t,p,k;
    scanf("%20lf%20lf%20lf",&t,&p,&k);
    printf("s=%lf",integral(t,p,k));
    return 0;
}


