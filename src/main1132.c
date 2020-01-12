#include <stdio.h>

#include "jiangxin.h"

int qiusushu(int n)
{
    for(n=n+1;; n++)
        if(prime(n))
        {
            return n;
        }
        else
        {
            continue;
        }
}
int main1132(void)
{
    int a[4][4]= {{3,6,4,17},{8,5,9,10},{9,19,7,20},{4,14,21,23}},
    b[4][4],count=0,i,j;

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            b[i][j]=a[i][j];
        }

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            if(i>=j)
            {
                if(prime(b[i][j]))
                {
                    b[i][j]=qiusushu(b[i][j]);
                    count++;
                }
                else
                {
                    b[i][j]=0;
                }
            }

    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%4d",b[i][j]);
        }

        printf("\n");
    }

    printf("count=%d\n",count);
    return 0;
}



