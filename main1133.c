/*实验11第五题*/
#include<stdio.h>
void line_sort(int a[][4],int b[],int n)
{
    int i,j,p,q,t,flag,c[4];

    for(i=0; i<5; i++)
    {
        b[i]=0;

        for(j=0; j<4; j++)
            b[i]+=a[i][j];
    }

    for(p=0; p<n-1; p++)
    {
        flag=1;

        for(q=0; q<n-1-i; q++)
            if(b[q]>b[q+1])
            {
                t=b[q];
                b[q]=b[q+1];
                b[q+1]=t;

                for(j=0; j<4; j++)
                {
                    c[j]=a[q][j];
                    a[q][j]=a[q+1][j];
                    a[q+1][j]=c[j];
                }

                flag=0;
            }
    }
}
int main1133(void)
{
    int a[5][4]= {{1,4,5,7},{3,5,7,8},{9,10,2,3},{1,3,4,2},{1,2,1,1}},b[5],
    i,j,n=5;

    for(i=0; i<n; i++)
    {
        for(j=0; j<4; j++)
            printf("%4d",a[i][j]);

        printf("\n");
    }

    line_sort(a,b,n);

    for(i=0; i<n; i++)
    {
        for(j=0; j<4; j++)
            printf("%4d",a[i][j]);

        printf("\n");
    }

    for(i=0; i<5; i++)
        printf("%4d",b[i]);

    printf("\n");
}






