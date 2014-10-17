#include<stdio.h>
#include<math.h>

int main1045()
{
    int a, n=1;
    printf("input a number:");
    scanf("%d",&a);

    while(n<=a)
    {
        if(a%n==0)
            printf("%d",n);

        n++;
    }

    return 0;
}

