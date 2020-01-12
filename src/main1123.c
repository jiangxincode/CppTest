/**
编程要求：
1.编写函数void movesort(int x[],int n)，对x指向的数组前n个元素做如下处理:
(1)将其中的所有奇数移到数组前半部分存储，所有偶数移到数组后半部分存储；
(2)对数组前半部分所有奇数降序排序，后半部分所有偶数升序排序。
2.编写main函数，声明一维数组a并用测试数据初始化，调用movesort函数对a数组全部元素做数据处理，
输出处理后a数组中全部数据。
测试数据及输出结果:
   处理前a数组： 1  2  3  4  5  6
   处理后a数组： 5  3  1  2  4  6
*/
#include <stdio.h>
#include <math.h>
void movesort(int x[],int n)
{
    int i,j,t,k,count,flag,a[3]= {0},b[3]= {0};

    /*把数组x[6]中的奇数放到a[3]中,偶数放到b[3]中*/
    for(i=0,k=0,count=0; i<n; i++)
    {
        if(x[i]%2!=0)
        {
            a[k]=x[i];
            k++;
        }
        else
        {
            b[count]=x[i];
            count++;
        }
    }

    /*把数组a[3]中的数按降序排列*/
    for(i=0; i<k-1; i++)
    {
        flag=1;

        for(j=0; j<k-i-1; j++)
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                flag=0;
            }

        if(flag)
        {
            break;
        }
    }

    /*把数组a[3]中的数依次输出*/
    for(i=0; i<k; i++)
    {
        printf("%d ",a[i]);
    }

    /*把数组b[3]中的数按升序排列*/
    for(i=0; i<count-1; i++)
    {
        flag=1;

        for(j=0; j<count-i-1; j++)
            if(b[i]>b[i+1])
            {
                t=b[i];
                b[i]=b[i+1];
                b[i+1]=t;
                flag=0;
            }

        if(flag)
        {
            break;
        }
    }

    /*把数组b[3]中的数依次输出*/
    for(i=0; i<3; i++)
    {
        printf("%d ",b[i]);
    }

    printf("\n");
}
int main1123(void)
{
    int x[6]= {1,2,3,4,5,6},i,n=6;

    for(i=0; i<6; i++)
    {
        printf("%d ",x[i]);
    }

    printf("\n");
    movesort(x,n);
    return 0;
}








