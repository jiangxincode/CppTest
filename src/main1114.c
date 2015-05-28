#include<stdio.h>
int main1114()
{
    int a[6],b[6]= {0},i,j;

    for(i=0; i<6; i++)
    {
        scanf("%11d",&a[i]);
    }

    for(i=0; i<6; i++)
        for(j=0; j<i; j++)
            if(a[j]<a[i])
            {
                b[i]++;
            }

    for(i=0; i<6; i++)
    {
        printf("%d",a[i]);
    }

    printf("\n");

    for(i=0; i<6; i++)
    {
        printf("%d",b[i]);
    }

    return 0;
}

