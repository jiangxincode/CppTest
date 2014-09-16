/*
输入一串数，以','分隔，输出所有数中去掉最大值、最小值之后剩下的个数。
（其中最大值与最小值可能有多个）
Smple input：3,3,5,3,6,9,7,9   Sample outPut: 3
*/

#include <stdio.h>
#include <limits.h>

#define N 100

int main0005()
{
    int min = INT_MAX, max = INT_MIN;
    int n = 0;
    char c_temp = '\0';
    int i_temp;
    int array[N] = {0};

    while(c_temp != '\n')
    {
        scanf("%d", &i_temp);
        array[n++] = i_temp;

        if(i_temp < min)
        {
            min = i_temp;
        }

        if(i_temp > max)
        {
            max = i_temp;
        }

        c_temp = getchar();
    }

    i_temp = 0;

    for(int i=0; i<n; i++)
    {
        if(array[i]!=min && array[i]!=max)
        {
            i_temp ++;
        }
    }

    printf("%d",i_temp);
    return 0;
}
