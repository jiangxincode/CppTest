/*
Ҫ��5������ѡȡ2������Ϊ���ǣ�����ÿ���˵���߷�ΧΪ160-190��
Ҫ��2���˵���߲�ֵ��С�������ֵ��ͬ�Ļ���ѡȡ������ߵ����ˣ���
��������������˵���ߡ�
Smple input��161 189 167 172 188 Sample outPut: 188 189
*/
#include <stdio.h>
#include <stdlib.h>

#define N 5

int comp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
int main0006()
{
    int height[N];

    for(int i=0; i<N; i++)
    {
        scanf("%d",&height[i]);
    }

    qsort(height,N,sizeof(int),comp); //��ߴӵ͵�������
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
