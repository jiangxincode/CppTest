#include<stdio.h>
#include<math.h>
#include<conio.h>
double integral(double a,double b,double n)
{
    double d,e,c,h,m=0;
    int i;
    h=(b-a)/n;

    for(i=1; i<n; i++)
    {
        d=a+i*h;
        c=cos(d)+sin(d);
        m=m+c;
    }

    e=h*((cos(a)+sin(a)+cos(b)+sin(b))/2+m);
    return e;
}
main1096()
{
    double t,p,k;
    scanf("%lf%ld%lf",&t,&p,&k);
    printf("s=%lf",integral(t,p,k));
}


