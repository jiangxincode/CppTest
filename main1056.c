#include<stdio.h>
#include<conio.h>
main1056()
{
    int i=100000,a,b,c,d,e,f;

    while(i<10000000)
    {
        a=i/100000%10;
        b=i/10000%10;
        c=i/1000%10;
        d=i/100%10;
        e=i/10%10;
        f=i%10;

        if(i==(f*100000+e*10000+d*1000+c*100+b*10+a))
            printf("%d ",i);

        i++;
    }

    getch();
}
