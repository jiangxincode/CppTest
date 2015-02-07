#include <stdio.h>
#include <math.h>

double f1(double x)
{
    return(-6+x*(3+x*(2*x-4)));
}
int main1085()
{
    double a=0,b=3,c,x,eps=1e-6;

    if(fabs(f1(a))<eps)
        x=a;
    else if(fabs(f1(b))<eps)
        x=b;
    else
    {
        c=(a*f1(b)-b*f1(a))/(f1(b)-f1(a));

        while(fabs(f1(c))>eps&&fabs(b-a)>eps)
        {
            if(f1(a)*f1(c)<0)
                b=c;
            else
                a=c;

            c=(a*f1(b)-b*f1(a))/(f1(b)-f1(a));
        }

        x=c;
    }

    printf("x=%f",x);
    return 0;
}
