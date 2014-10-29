#include<stdio.h>
int Union(int (*a)[6],int res[]);

int main1134(void)
{
    int sec[5][6]= {{4,12,35,3,9},{3,2,35,9},{5,35,12,0,1,9},{1,90},{2,9,0}};
    int unisec[30],n,i;
    n=Union(sec,unisec);

    for(i=0; i<n; i++)printf("%5d",unisec[i]);

    printf("\n");
    return 0;
}
int Union(int (*a)[6],int res[])
{
    int i,j,k,count=0,flag=0;

    for(i=0; i<5; i++)
        for(j=1; j<=a[i][0]; j++)
        {
            for(flag=0,k=0; k<count; k++)
                if(a[i][j]==res[k])
                {
                    flag=1;
                    break;
                }

            if(flag==0) 	res[count++]=a[i][j];
        }

    return count;
}
