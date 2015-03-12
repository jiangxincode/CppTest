/**
 * 实验5 实验内容第2题
 */

#include <stdio.h>
#include <math.h>

#include "jiangxin.h"

int main1064()
{
    for(int i=0; i<20; i++)
    {
        int m = pow(2,i)-1;

        if(prime(i) && prime(m))
        {
            printf("%d ",m);
        }
    }

    return 0;
}






