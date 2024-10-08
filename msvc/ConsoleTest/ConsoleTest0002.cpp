#include <stdio.h>
#include <math.h>

#define eps (1e-8)

int main()
{
    double x;
    scanf_s("%lf",&x);
    printf("%lf\n",x);

    float y;
    scanf_s("%f",&y);
    printf("%f\n",y);

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
        printf("right!\nx=%lf\nleft=%lf\nright=%lf",x,left,right);
    else
        printf("wrong!");

    return 0;
}
