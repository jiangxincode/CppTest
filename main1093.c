#include<stdio.h>
#include<math.h>

#include "jiangxin.h"

int main1093()
{
    int m,n,a;
    printf("Input two int numbers");
    scanf("%11d,%11d",&m,&n);

    for(a=m; a<=n-2; a++)
        if(prime(a)&&prime(a+2))
            printf("(%d  %d)\n",a,a+2);

    return 0;
}

