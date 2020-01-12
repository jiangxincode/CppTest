#include <stdio.h>
#include <math.h>

double f1103(double x)
{
    return x*x/4-sin(x);
}
double root(double a,double b)
{
    double  eps=1e-6;

    if(fabs(f1103((a+b)/2))<eps)
    {
        return (a+b)/2;
    }
    else if(fabs(f1103((a+b)/2))>eps&&f1103(a)*f1103((a+b)/2)<0)
    {
        return root(a,(a+b)/2);
    }
    else if(fabs(f1103((a+b)/2))>eps&&f1103((a+b)/2)*f1103(b)<0)
    {
        return root((a+b)/2,b);
    }
    else
    {
        return 0.0;    //for others
    }
}
int main()
{
    double a=1,b=2;

    if(f1103(a)*f1103(b)<0)
    {
        printf("x=%lf",root(a,b));
    }
    else
    {
        printf("There is no root in this area");
    }

    return 0;
}




