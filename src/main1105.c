#include <stdio.h>
#include <math.h>


double f1105(double a,double b,int n,double(*p)(double))
{
    double h;
    h=(b-a)/n;

    if(n==1)
    {
        return (p(a)+p(b))*h/2;
    }
    else
    {
        return (p(b)+p(b-h))*h/2+f1105(a,b-h,n-1,p);
    }
}
int main1105()
{
    static const double PI = 3.14159;
    double a,b;
    int n;
    printf("in put n");
    scanf("%11d",&n);
    a=-PI/2;
    b=PI/2;
    printf("%lf",f1105(a,b,n,cos));
    return 0;
}


