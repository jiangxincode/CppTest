#include <stdio.h>
int main1081()
{
    int a,b,c,d,n=0;

    for(a=1; a<=9; a++)
        for(b=1; b<=8; b++)
            for(c=1; c<=7; c++)
                for(d=1; d<=6; d++)
                {
                    if(a+b+c+d==23)
                    {
                        n++;
                        printf("%d %d %d %d\n",a,b,c,d);
                    }
                }

    printf("%d",n);
}

