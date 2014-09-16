#include<stdio.h>
main1113()
{
    int t,m,i,j,a,x[10]= {0,1,2,3,4,5,6,7,8,9};
    scanf("%d%d",&t,&m);

    if(t==0)
        for(i=0; i<m; i++)
        {
            a=x[0];

            for(j=0; j<9; j++)
                x[j]=x[j+1];

            x[j]=a;
        }
    else
        for(i=0; i<m; i++)
        {
            a=x[9];

            for(j=9; j>0; j--)
                x[j]=x[j-1];

            x[0]=a;
        }

    for(i=0; i<10; i++)
        printf("%d ",x[i]);
}
