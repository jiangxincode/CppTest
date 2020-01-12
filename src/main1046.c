#include <stdio.h>
#include <math.h>
int main1046()
{
    int m,n=1;
    float s,x=0;
    printf("Input the m");
    scanf("%11d",&m);

    while(n<=m)
    {
        x=x+log(n);
        n++;
    }

    s=sqrt(x);
    printf("%f",s);
    return 0;
}
