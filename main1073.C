#include <stdio.h>
#include <math.h>

#define eps (1e-8)

int main1073()
{
    double x = 0.0;
    scanf("%10lf",&x); //最大支持10位字段宽度

    double left=(x*x+1+(1/x))*exp(-1*x)-(1/x);

    int n = 1;

    double item = (-1)*x/2;
    double right = item;

    //item(n) = ((-1)^n)*(n^3)*(x^n)/(n+1)!
    //item(n+1) = ((-1)^(n+1))*((n+1)^3)*(x^(n+1))/(n+2)!
    //item(n+1) = (-1)*((n+1)^3)*x/(n^3)/(n+2)
    while(fabs(item)>eps)
    {
        item *= (-1)*((n+1)*(n+1)*(n+1))*x/(n*n*n)/(n+2);
        right += item;
        n++;
    }

    if(fabs(right-left)/(fabs(right)+fabs(left))<1e-6)
        printf("right!\nx=%.20f\nleft=%.20f\nright=%.20f",x,left,right);
    else
        printf("wrong!");

    return 0;
}
