#include<stdio.h>
#include<math.h>
double term1112(double x,int n)
{
    static double y=1;

    if(n>1)
    {
        y=y*(-1)*x*(2*n-3)/(2*n-2);
    }

    return y;
}
main1112()
{
    double x,y,s=0;
    int n=1;
    scanf("%lf",&x);

    do
    {
        y=term1112(x,n);
        s+=y;
        n++;
    }
    while(fabs(y)>=1e-6);

    printf("\n x=%f,%f,%f",x,1/sqrt(1+x),s);
}


