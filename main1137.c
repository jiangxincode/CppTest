#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main1137()
{
    int a[9][9]= {0};
    int i,j,m,n1,n2,n3,n;
    srand((signed)time(NULL));

    for(m=0; m<10; m++)
    {
        i=rand()%9;
        j=rand()%9;

        if(a[i][j]==0)
            a[i][j]=-1;
    }

    for(i=0; i<9; i++)
    {
        for(j=0; j<9; i++)
        {
            if(a[i][j]==-1)
                printf("%c",15);
            else
            {
                n1=(i>0&&j>0&&a[i-1][j-1]==-1)+(i>0&&a[i-1][j]==-1)+(i>0&&j<8&&a[i-1][j+1]==-1);
                n2=(j>0&&a[i][j-1]==-1)+(j<8&&a[i][j+1]==-1);
                n3=(i<8&&j>0&&a[i+1][j-1]==-1)+(i<8&&a[i+1][j]==-1)+(i<8&&j<8&&a[i+1][j+1]==-1);
                n=n1+n2+n3;

                if(n==0)
                    printf("%c",32);
                else
                    printf("%d",n);
            }
        }

        printf("\n");
    }

    return 0;
}


