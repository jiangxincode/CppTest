#include <stdio.h>
int main1028()
{
    int a;
    scanf("%11d",&a);

    if(a%5==0 && a%3==0)
    {
        printf("yes!");
    }
    else
    {
        printf("no!");
    }

    return 0;
}
