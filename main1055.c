/**
 * ��νArmstrong��������nλ���ĸ�λ����n�η�֮�͵��ڸ���
 * Ҫ���жϱ�дһ�������ж�ĳ���������Ƿ���һ��Armstrong��
 */
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX_DIGITS 11

int is_armstrong(int num)
{
    int temp = num;
    int result = 0;
    int bit_count = 0; //���ֵ�λ��
    int bit[MAX_DIGITS]; //��Ÿ�λ����

    if(num <= 0) //ֻ�������������ж�
    {
        return 0;
    }

    for(int i=0;i<MAX_DIGITS;i++) //��ʼ��
    {
        bit[i] = -1;
    }
    while(temp)
    {
        bit[bit_count++] = temp%10;
        temp /= 10;
    }
    for(int i=0;bit[i]!=-1;i++)
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
    for(int i=0;i<INT_MAX;i++)
    {
        if(is_armstrong(i))
        {
            printf("%d\n",i);
        }
    }
    return 0;
}




