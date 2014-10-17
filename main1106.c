#include<stdio.h>
#include<math.h>

double term(double x,int n)
{
    if(n==1)
        return x;
    else
        return term(x,n-1)*(2*n-3)*(-1)*(2*n-3)*x*x/(2*n-1)/(2*n-2);
}
double f1106(double x,double eps)
{
    double s=x;
    int n=1;

    while(fabs(term(x,n))>=eps)
    {
        n++;
        s=s+term(x,n);
    }

    return s;
}
int main1106()
{
    double x,eps,sum;
    scanf("%lf%lf",&x,&eps);
    sum=f1106(x,eps);
    printf("x=%lf,eps=%lf,sum=%lf",x,eps,sum);
    return 0;
}
