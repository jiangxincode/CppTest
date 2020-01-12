#include <stdio.h>
#include <math.h>
double f2(double x)
{
    return exp(x)+x;
}
int main1084()
{
    double a=-1,b=0,c,x,eps=1e-6;

    if(fabs(f2(a))<eps)
    {
        x=a;
    }
    else if(fabs(f2(b))<eps)
    {
        x=b;
    }
    else
    {
        c=(a+b)/2;

        while(fabs(c)>eps&&fabs(b-a)>eps)
        {
            if(f2(a)*f2(c)<0)
            {
                b=c;
            }
            else
            {
                a=c;
            }

            c=(b+a)/2;
        }

        x=c;
    }

    printf("x=%f",x);
    return 0;
}


