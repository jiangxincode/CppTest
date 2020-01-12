/**
 * 教材实验13 第7题
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

/** \brief 判断一个正整数是否为素数
 *
 * \param int n 带判断的正整数
 * \return 0 不是素数
 *         1 是素数
 *
 */
int prime(int n)
{
    int flag = 0;
    int i = 0;

    if(n <= 1)
    {
        return 0;
    }

    for(i=2; i<n; i++)
    {
        if((n%i)==0)
        {
            flag++;
        }
    }

    if(flag == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int stoi(char *str)
{
    int result = 0;
    int i;

    for(i=0; str[i]!='\0'; i++)
    {
        if(!isdigit(str[i]))
        {
            return -1; //非数字字符
        }

        result = result*10+(str[i]-'0');
    }

    return result;
}

int main(int argc,char*argv[])
{
    const int MAX_NUM = 100;
    int arr[MAX_NUM];
    int i,j;
    int count = 0;

    if(argc > MAX_NUM)
    {
        printf("too many arguments!");
        exit(1);
    }

    for(i=1,j=0; i<argc; i++)
    {
        if(stoi(argv[i]) != -1)
        {
            count ++;
            arr[j++] = stoi(argv[i]);
        }
    }

    printf("%d\n",count);

    for(i=0; i<count; i++)
    {
        if(prime(arr[i]))
        {
            printf("%d ",arr[i]);
        }
    }

    printf("\n");

    for(i=0; i<count; i++)
    {
        if(!prime(arr[i]))
        {
            printf("%d ",arr[i]);
        }
    }

    printf("\n");
    return 0;
}
