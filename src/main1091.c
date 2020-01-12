#include <stdio.h>
int find(int n)
{
    int d,m;
    m=n;

    for(d=0; n>0; n/=10)
    {
        d=d*10+n%10;
    }

    if(d==9*m)
    {
        return d;
    }
    else
    {
        return 0;
    }
}
int main1091()
{
    int n;

    for(n=1000; n<10000; n++)
    {
        if(find(n)!=0)
        {
            printf("%d----%d\n",n,find(n));
        }
    }

    return 0;
}

