#include<stdio.h>
#include<math.h>
main1064()
{
    int p,c,k,t,r;
    double m;
    p=2;
    c=5;

    while(c>0)
    {
        k=2;
        m=pow(2,p)-1;
        t=0;
        r=0;

        while(k<p)
        {
            if(p%k==0)
                t=t+1;

            k=k+1;
        }

        while(k<m)
        {
            if((int)m%k==0)
                r=r+1;

            k=k+1;
        }

        if(t==0&&r==0)
        {
            printf("%d \n",(int)m);
            c=c-1;
        }

        p=p+1;
    }
}






