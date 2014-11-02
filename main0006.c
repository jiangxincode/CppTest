/**
 * 要从5个人中选取2个人作为礼仪，其中每个人的身高范围为160-190，
 * 要求2个人的身高差值最小（如果差值相同的话，选取其中最高的两人），
 * 以升序输出两个人的身高。
 * Smple input：161 189 167 172 188 Sample outPut: 188 189
 */
#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
int main0006()
{
    const int N = 5;
    int height[N];

    for(int i=0; i<N; i++)
    {
        scanf("%3d",&height[i]); //身高以三位数表示已经足够
    }

    qsort(height,N,sizeof(int),comp); //身高从低到高排序
    int min = height[N-1] - height[N-2];
    int higher = height[N-1],lower = height[N-2];

    for(int i=N-1; i>0; i--)
    {
        if(height[i]-height[i-1]<min)
        {
            min = height[i]-height[i-1];
            higher = height[i];
            lower = height[i-1];
        }
    }

    printf("%d %d",lower,higher);
    return 0;
}
