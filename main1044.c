#include<stdio.h>
int main1044()
{
    float x;
    printf("Input the x");
    scanf("%f",&x);

    if(x>0)
        printf("y=1");
    else
    {
        if(x==0)
            printf("y=0");
        else
            printf("y=-1");
    }

    return 0;
}
