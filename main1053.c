#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main1053()
{
    int x,s=1;
    printf("input a number:");
    scanf("%11d",&x);

    if(x<100||x>1000)
    {
        printf("you can't do that");
        exit(1);
    }

    do
    {
        int a=x/100%10; //百位
        int b=x/10%10; //十位
        int c=x/1%10; //个位

        int t;
        if(a<=b)
        {
            t=a;
            a=b;
            b=t;
        }

        if(a<=c)
        {
            t=a;
            a=c;
            c=t;
        }

        if(b<=c)
        {
            t=b;
            b=c;
            c=t;
        }

        int max=a*100+b*10+c;
        int min=c*100+b*10+a;
        s++;
        printf("%d ",x);
        x=max-min;

        if(x==495)
        {
            printf("%d",x);
            break;
        }
    }
    while(x%111!=0||s<8);

    return 0;
}










