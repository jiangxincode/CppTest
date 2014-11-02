/**
 * 输入一串数，以','分隔，输出所有数中去掉最大值、最小值之后剩下的个数。
 * 其中最大值与最小值可能有多个
 * Smple input：3,3,5,3,6,9,7,9   Sample outPut: 3
 */

#include <stdio.h>
#include <limits.h>

int main0005()
{
    int min = INT_MAX, max = INT_MIN;
    int n = 0; //记录输入的数字个数
    int ch = '\0';
    int array[100] = {0};

    while(ch != '\n')
    {
        int temp;
        scanf("%20d", &temp);
        array[n++] = temp;

        if(temp < min)
        {
            min = temp;
        }

        if(temp > max)
        {
            max = temp;
        }

        ch = getchar();
    }

    int result = 0;

    for(int i=0; i<n; i++)
    {
        if(array[i]!=min && array[i]!=max)
        {
            result ++;
        }
    }
    printf("%d",result);
    return 0;
}
