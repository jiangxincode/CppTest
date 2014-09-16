#include<stdio.h>
#include<math.h>
main1063()
{
    int n,a,i=2;

    while(i<=100)
    {
        a=2;
        n=0;

        while(a<i)
        {
            if(i%a==0)
                n=n+1;

            a=a+1;
        }

        if(n==0)
            printf("%d ",i);

        i=i+1;
    }
}





