#include<stdio.h>
#include<math.h>
#include "jiangxin.h"
int main1093()
{
    int m,n,a,b;
    printf("Input two int numbers");
    scanf("%d,%d",&m,&n);

    for(a=m; a<=n-2; a++)
        if(b=prime(a)&&prime(a+2))
            printf("(%d  %d)\n",a,a+2);
}

