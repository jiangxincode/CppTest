#include <stdio.h>
#include <math.h>

#include "jiangxin.h"

int mpsort(int x[],int a)
{
    int i,j,m=0,n,count,t;

    for(i=1; i<a; i++)
    {
        if(x[i]%2==0&&x[i]>x[m])/*如果第一个数一个比较大的奇数怎么办？*/
        {
            m=i;
        }
    }

    for(i=a-1; i>=0; i--)
        if(prime(x[i]))
        {
            break;
        }

    n=i;

    for(i=m; i<n; i++)
    {
        for(j=m; j<n-i; j++)
            if(x[j]>x[j+1])
            {
                t=x[j];
                x[j]=x[j+1];
                x[j+1]=t;
            }
    }

    count=n-m+1;
    return count;
}
int main1122(void)
{
    int x[10],n=10,i=0,count;

    for(i=0; i<10; i++)
    {
        scanf("%11d",&x[i]);
    }

    count=mpsort(x,n);

    for(i=0; i<10; i++)
    {
        printf("%5d",x[i]);
    }

    printf("\n%d",count);
    return 0;
}

