/**
 * �̲�ʵ��13 ��7��
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "jiangxin.h"

#define MAX_NUM 100

int stoi(char *str)
{
    int result = 0;
    int i;

    for(i=0; str[i]!='\0'; i++)
    {
        if(!isdigit(str[i]))
        {
            return -1; //�������ַ�
        }

        result = result*10+(str[i]-'0');
    }

    return result;
}

int main1151(int argc,char*argv[])
{
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
            printf("%d ",arr[i]);
    }

    printf("\n");
    return 0;
}
