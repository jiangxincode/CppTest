/**
 * ʵ��11������
 * δ���
 */

#include<stdio.h>

void line_sort(int a[][4],int b[],int n)
{
    int temp;
    int c[n]; //�洢��������������ڵĺ���

    for(int i=0; i<5; i++)
    {
        b[i]=0;

        for(int j=0; j<4; j++)
        {
            b[i]+=a[i][j];
        }
    }

    for(int i=0; i<n; i++)
    {
        printf("%d ",b[i]);
    }

    printf("\n");

    //����Ч�����⣬Ӧ���ȶ�b��������
    for(int i=0; i<n; i++)
    {
        int count = 0;

        for(int j=0; j<n; j++)
        {
            if((b[j] < b[i]) || ((b[j] == b[i])&&(i>j)))
            {
                count ++;
            }

            c[i] = count;
        }
    }

    for(int i=0; i<n; i++)
    {
        printf("%d ",c[i]);
    }

    printf("\n");

    for(int i=0; i<n; i++)
    {
        int pos;

        for(int k=0; k<n; k++)
        {
            if(c[k] == i)
            {
                pos = k;
            }
        }

        for(int j=0; j<4; j++)
        {
            temp = a[i][j];
            a[i][j] = a[pos][j];
            a[pos][j] = temp;
        }
    }
}
int main1133(void)
{
    int a[5][4]= {{1,4,5,7},{3,5,7,8},{9,10,2,3},{1,3,4,2},{1,2,1,1}},b[5];
    int i,j,n=5;

    for(i=0; i<n; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%d\t",a[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    line_sort(a,b,n);

    for(i=0; i<n; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%d\t",a[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    return 0;
}






