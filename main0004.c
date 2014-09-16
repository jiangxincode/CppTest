/* itoa example */
#include <stdio.h>
#include <stdlib.h>

void jx_swap_integer(int* i_num1,int* i_num2,short method)
{
    if(method == 0)
    {
        int temp = *i_num1;
        *i_num1 = *i_num2;
        *i_num2 = temp;
    }
    else if(method == 1) //�����������ͱ�����ֵ�����������������
    {
        *i_num1 = *i_num1 + *i_num2;
        *i_num2 = *i_num1 - *i_num2;
        *i_num1 = *i_num1 - *i_num2;
    }
    else if(method == 2) //�����������ͱ�����ֵ�����������������
    {
        *i_num2 = *i_num2 - *i_num1;
        *i_num1 = *i_num2 + *i_num1;
        *i_num2 = *i_num1 - *i_num2;
    }
    else if(method == 3) //�����������ͱ�����ֵ�����������������
    {
        *i_num1 = *i_num1 ^ *i_num2;
        *i_num2 = *i_num1 ^ *i_num2;
        *i_num1 = *i_num1 ^ *i_num2;
    }
}

int main0004()
{
    int a=15,b=17;
    jx_swap_integer(&a,&b,1);
    printf("%d,%d",a,b);
    return 0;
}

