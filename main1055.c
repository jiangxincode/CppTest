/**
 * 所谓Armstrong数，就是n位数的各位数的n次方之和等于该数
 * 要求判断编写一个函数判断某个正整数是否是一个Armstrong数
 */
#include <stdio.h>
#include <math.h>
#include <limits.h>


int is_armstrong(int num)
{
    int MAX_DIGITS = 11; //don't change
    int temp = num;
    int result = 0;
    int bit_count = 0; //数字的位数
    int bit[MAX_DIGITS]; //存放各位数字

    if(num <= 0) //只对正整数进行判断
    {
        return 0;
    }

    for(int i=0; i<MAX_DIGITS; i++) //初始化
    {
        bit[i] = -1;
    }

    while(temp)
    {
        bit[bit_count++] = temp%10;
        temp /= 10;
    }

    for(int i=0; bit[i]!=-1; i++)
    {
        result += pow(bit[i],bit_count);
    }

    if(result == num)
    {
        return 1;
    }
    else return 0;
}

int main1055()
{
    for(int i=0; i<INT_MAX; i++)
    {
        if(is_armstrong(i))
        {
            printf("%d\n",i);
        }
    }

    return 0;
}




