#include<stdio.h>
#include<math.h>
main1115()
{
    int j,m=0,n1,n2,f,t[10],d[10];
    long x,y,i;
    scanf("%d%d",&n1,&n2);

    for(i=n1; i<=n2; i++)
    {
        for(j=0; j<10; j++)d[j]=0;

        f=1;

        for(j=2; j<i; j++)
            if(i%j==0)
            {
                f=0;
                break;
            }

        if(f==0)
            continue;

        x=y=i*i;
        m=0;

        while(y>0)
        {
            t[m]=y%10;
            m++;
            y=y/10;
        }

        for(j=0; j<m; j++)
        {
            d[t[j]]++;

            if(d[t[j]]>1)
            {
                f=0;
                break;
            }
        }

        if(f) printf("\n%ld %ld",i,x);
    }
}
