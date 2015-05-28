#include<stdio.h>
#include "jiangxin.h"

int countvalue(int aa[])
{
    int i,k=0;

    for(i=500; i<=800; i++)
        if(prime(i))
        {
            aa[k]=i;
            k++;
        }

    return k;
}
int main1116()
{
    int aa[150],cnt,k;
    cnt=countvalue(aa);

    for(k=0; k<cnt; k++)
        if(aa[k]!=0)
        {
            printf("%6d",aa[k]);

            if((k+1)%10==0)
            {
                printf("\n");
            }
        }

    return 0;
}


