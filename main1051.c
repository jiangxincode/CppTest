#include<stdio.h>
#include<math.h>
int main1051()
{
    double x,m,p;
    int n=0;
    printf("Input a double number x:\n");
    scanf("%lf",&x);
    p=fabs(x);

    if(p>0.1&&p<1)
        m=p;
    else
    {
        while(p>=1)
        {
            p=p/10;
            n=n+1;
        }

        while(x<=0.1)
        {
            p=p*10;
            n=n-1;
        }

        m=p;
    }

    if(x>=0)
        printf("%lfe%d",m,n);
    else
        printf("-%lfe%d",m,n);
    return 0;
}
