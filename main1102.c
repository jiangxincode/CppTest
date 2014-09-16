#include<stdio.h>
#include<math.h>
#include<conio.h>
void itoah(int x)
{
    int a;

    if(x/16>0) itoah(x/16);

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
    itoah(x);
    getch();
}






