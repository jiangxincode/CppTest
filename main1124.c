/*
约瑟夫问题：
n个人（编号1 ~ n）围成一圈, 从第一个人开始顺序报数，从1报到m, 报到m的人出列,从出列的下一个人开始重新报数，报到m的人又出列。
如此重复直到所有人出列为止。问：最后出列的人是几号？
编程要求：
1. 编写函数void  joseph(int n,int m,int x[])模拟约瑟夫问题报数过程，将依次出列的所有人编号按出列顺序依次保存到x指向的一维数组中。
2. 编写main函数， 声明一维数组c，输入两个正整数(代表n和m)分别送变量a和b保存，用变量a、b和数组c做实参调用joseph函数。输出c数组中数据。
测试数据及输出结果:
    当 n=10,m=3时输出为：
    3    6    9    2    7    1    8    5    10    4 （依次出列的人员编号）
*/
#include<stdio.h>
void joseph(int n,int m,int x[])
{
    int a[100],i,*p,c=0,j=0;

    /*对a[]中的数进行赋值*/
    for(i=0; i<n; i++) a[i]=i+1;

    p=a;

    while(*p!=0)
    {
        for(i=1; i<=m; i++)
        {
            if(i==m)
            {
                x[j++]=*p;
                *p=0;
                c++;
            }

            do
            {
                p++;

                if(p>a+n-1) p=a;

                if(c==n)
                    break;
            }
            while(*p==0);
        }
    }
}
main1124()
{
    int a[100],n,m,i;
    printf("input the number of persons");
    scanf("%d",&n);
    printf("input the number of counter:");
    scanf("%d",&m);
    joseph(n,m,a);

    for(i=0; i<n; i++)
        printf("%d ",a[i]);
}

