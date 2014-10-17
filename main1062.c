#include<stdio.h>
#include<math.h>

int main1062()
{
    int a=2,p,n;

    while(a<=1000)
    {
        n=1;
        p=0;

        while(n<a)
        {
            if(a%n==0)
            {
                p=p+n;
            }

            n=n+1;
        }

        if(p==a)
            printf("%d\n",a);

        a=a+1;
    }

    return 0;
}
