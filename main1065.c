#include<stdio.h>
#include<math.h>
main1065()
{
    int a,b,c,x,y;
    a=1;

    while(a<50)
    {
        b=99-a;
        x=b;
        y=a;

        while(y!=0)
            c=x%y,x=y,y=c;

        c=x;

        if(c%3==0)
            printf("(%d,%d)\n",a,b);

        a=a+1;
    }
}


