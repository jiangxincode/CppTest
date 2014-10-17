/**
阶乘相关问题
*/

/**
求n阶阶乘问题的递归算法
*/
long int factorial(int n)
{
    if(n==0||n==1)
        return 1;
    else
        return n*factorial(n-1);
}


/**
模拟高精度阶乘手工计算:
    对于n!的计算，当n大于12时n!的计算结果已超出long int的最大值。
    例如15!=1307674368000 ，该运算结果无法用一个long int变量存储。
    用数组可模拟高精度阶乘手工计算。
	用int型数组m[MAX]存放n!运算的中间结果和最终结果的十进制表示，即每个数组元素存放一个十进制数中的一个数字位
   （即：m[0]存储个位，m[1]存储十位，…  其它位以此类推）。
编程要求：
1. 编写函数int fact(int n) ，声明局部一维数组m[MAX], 计算并输出n!值。
当计算到m[MAX-1]时若仍有向高位的进位，视为溢出，输出“overflow”,函数返回0。
若无溢出函数返回1。
    注意：MAX是符号常量，请自行定义其值。
2. 编写main函数，2次调用fact函数分别计算并输出7!和15! 。
测试数据和运行结果： 7!=5040， 15!=1307674368000
*/
#include <stdio.h>
int fact(int n)
{
    int i,j;
    int m[10]= {0};
    m[0]=1;

    for(i=2; i<=n; i++)
    {
        for(j=0; j<10; j++)
            m[j]*=i;

        for(j=0; j<10-1; j++)
        {
            if(m[j]>9)
            {
                m[j+1]+=m[j]/10;
                m[j]=m[j]%10;
            }
        }

        if(m[10-1]>9) return 0;
    }

    for(i=10; j>=0; j--) printf("%d",m[j]);

    return 1;
}

int main1125()
{
    int n,k;
    printf("\nThe factorial number:");
    scanf("%d",&n);
    k=fact(n);

    if(k==0) printf("OVERFLOW!!!");

    return 0;
}
