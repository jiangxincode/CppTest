#include<stdio.h>
#include<math.h>
int main1071()
{
    double term,s,x;
    int n=1;
    printf("x=");
    scanf("%20lf",&x);
    s=x;
    term=x;

    while(fabs(term)>=1e-6)
    {
        term = (-1)*(term *x *x) / ((2*n+1)*(2*n))  ;
        s=s+term;
        n++;
    }

    printf("%.5f",s);
    return 0;
}
