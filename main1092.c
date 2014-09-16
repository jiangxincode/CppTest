#include<stdio.h>
int huiwen(long n)
{
    int d,m;
    m=n;

    for(d=0; n>0; n/=10)
        d=d*10+n%10;

    if(d==m)
        return 1;
    else
        return 0;
}
int main1092()
{
    int n,m,a,b;

    for(n=0; n<300; n++)
    {
        b=n;

        if((m=huiwen(n))&&(a=huiwen(n*n)))
            printf("n=%d,%d^%d=%d\n",b,b,b,b*b);
    }
}


