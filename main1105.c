#include<stdio.h>
#include<math.h>
#include<conio.h>
#define PI 3.1415926
double f1105(double a,double b,int n,double(*p)(double))
{
    double h;
    h=(b-a)/n;

    if(n==1)
        return (p(a)+p(b))*h/2;
    else
    {
        return (p(b)+p(b-h))*h/2+f(a,b-h,n-1,p);
    }
}
main1105()
{
    double a,b;
    int n;
    printf("in put n");
    scanf("%d",&n);
    a=-PI/2;
    b=PI/2;
    printf("%lf",f1105(a,b,n,cos));
    getch();
}


