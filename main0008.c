/*
������2014����Ƹ������
5.
��������stackģ��queue
(��ָoffer�ϵ�ԭ�⣬�Ŷ�oj��ר�ŵ���ϰ)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    int top;
    int seq[100000];
} stack;

/**
 * ��Ӳ���
 *
 * T = O(1)
 *
 */
void pushQueue(stack *s1, int data)
{
    s1->seq[s1->top ++] = data;
}

/**
 * ���Ӳ���
 *
 * T = O(n)
 *
 */
void popQueue(stack *s1, stack *s2)
{
    if(s2->top > 0)
    {
        printf("%d\n", s2->seq[-- s2->top]);
    }
    else
    {
        while(s1->top > 0)
        {
            s2->seq[s2->top ++] = s1->seq[-- s1->top];
        }

        if(s2->top > 0)
            printf("%d\n", s2->seq[-- s2->top]);
        else
            printf("-1\n");
    }
}


int main0008(void)
{
    int data, n;
    stack *s1, *s2;
    char str[5];

    while(scanf("%d", &n) != EOF)
    {
        // ��ʼ��
        s1 = (stack *)malloc(sizeof(stack));
        s2 = (stack *)malloc(sizeof(stack));
        s1->top = s2->top = 0;

        while(n --)
        {
            scanf("%s", str);

            if(strcmp(str, "PUSH") == 0)    // �����
            {
                scanf("%d", &data);
                pushQueue(s1, data);
            }
            else        // ������
            {
                popQueue(s1, s2);
            }
        }

        free(s1);
        free(s2);
    }

    return 0;
}
