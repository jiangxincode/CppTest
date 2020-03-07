/**
 * 铁路栈问题
 * 题目标题：铁路栈问题
 * 铁路的调度站如下：
 *
 * 火车编号为：1~9，且不重复。
 * 如：编号分别为“1”、“2”、“3”、“4”、“5”的5个火车顺序进站，那么进站序列为“12345”，全部进站后再顺序出站，则出站序列为“54321”，如果先进1,2，然后2出站，然后1出站，然后再3进站、出站，4进站、出站，5进站、出站，那么出站序列就为21345.
 * 详细描述：
 * int JudgeTrainSequence (int maxNum, char *pOutSeq);
 * 输入参数：
 *     int maxNum：进站的火车最大编号
 *     char* pOutSeq：使用字符串表示火车出站序列
 * 输出参数（指针指向的内存区域保证有效）：
 *     无。
 * 返回值：
 *     Int: 根据输入的进站序列判断，如果输入的出站序列是可能的，返回1，否则返回0；
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

/*
 详细描述：
 int JudgeTrainSequence (int maxNum, char *pOutSeq);
 输入参数：
 int maxNum：进站的火车最大编号
 char* pOutSeq：使用字符串表示火车出站序列
 输出参数（指针指向的内存区域保证有效）：
 无。
 返回值：
 Int: 根据输入的进站序列判断，如果输入的出战序列是可能的，返回1，否则返回0；

 */

int JudgeTrainSequence(int maxNum, char *pOutSeq)
{
    //maxNum和pOutSeq长度可能不是相同的，比如maxNum=10，pOutSeq可能只是43251
    if ((pOutSeq == NULL) || (maxNum < 1) || (maxNum < strlen(pOutSeq)))
    {
        return 0;
    }

    for (int i = 0; i < maxNum; i++)
    {
        int m = 0;
        for (int j = i + 1; j < maxNum; j++)
        {
            if (pOutSeq[i] > pOutSeq[j])
            {
                m++;
            }
        }

        for (int j = i+1; j < i+m; j++)
        {
            if(pOutSeq[j] < pOutSeq[j+1])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int maxNum = 5;
    char *outSeq = "34215";

    std::cout << (1 == JudgeTrainSequence(maxNum, outSeq)) << std::endl;

    return 0;
}

