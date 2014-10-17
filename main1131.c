/*
二维数组的局部鞍点定义如下：
对任意一个二维数组中的元素，若该元素的值比其上下2个相邻元素的值都小
并且比其左右2个相邻元素的值都大，则称该元素是一个局部鞍点。
位于矩阵拐角和边界的元素分别只有2个和3个相邻元素。
函数localmin的形参a指向输入数组，b指向输出数组。
该函数的功能是找出输入数组中所有局部鞍点，
若输入数组的某个元素是局部鞍点，则将输出数组的相同位置处的元素置1；否则置0。
*/
#include <stdio.h>
#define MIN -32768
#define MAX 32767
void localmax(int a[6][6],int b[6][6])
{
    int i,j,k,m;

    for(i=1; i<=4; i++)
        for(j=1; j<=4; j++)
        {
            b[i][j]=1;

            for(k=-1; k<=1; k++)
                for(m=-1; m<=1; m++)
                {
                    if((k==-1||k==1) && (m==-1||m==1)) continue;

                    if((k==0&&a[i][j]>a[i+m][j+k])||(m==0&&a[i][j]<a[i+m][j+k]))
                        b[i][j]=0;
                }
        }
}
int main1131()
{
    int b[6][6];
    int i,j,a[6][6]= {{0},{0,6,9,2,4},{0,3,6,8,5},{0,2,1,4,1},{0,6,2,9,4}};

    for(j=0; j<6; j++)
    {
        a[0][j]=MAX;
        a[j][0]=MIN;
        a[5][j]=MAX;
        a[j][5]=MIN;
    }

    localmax(a,b);

    for(i=1; i<=4; i++)
    {
        for(j=1; j<=4; j++)  printf("%8d",a[i][j]);

        printf("\n");
    }

    for(i=1; i<=4; i++)
    {
        for(j=1; j<=4; j++)  printf("%8d",b[i][j]);

        printf("\n");
    }

    return 0;
}
