#include<stdio.h>
#include<math.h>
void dec2hex(int x)
{
    int a;

    if(x/16>0)
    {
        dec2hex(x/16);
    }

    a=x%16;

    if(a<10)
        printf("%d",a);
    else
        printf("%c",a-10+'A');
}
main1102()
{
    int x;
    printf("in put a number:");
    scanf("%d",&x);
    dec2hex(x);
}






