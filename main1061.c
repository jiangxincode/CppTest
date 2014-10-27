/**
 * 实验4 实验内容第6题 分解合数
 */
#include <stdio.h>
#include <math.h>

int main1061()
{
    unsigned int num,n=2;
    printf("Please input a int number;\n");
    scanf("%12u",&num);

    while(n<=num)
    {
        if(num%n==0)
        {
            printf("%u\n",n);
            num=num/n;
        }
        else
        {
            n++;
        }
    }

    return 0;
}




