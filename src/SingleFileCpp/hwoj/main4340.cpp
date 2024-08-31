/**
 * Home Work GetMaxValue
 * 题目描述
 * 临近开学了，小C才想起来数学老师布置了暑假作业。暑假作业是很多张试卷，每张试卷所需的时间和获取的价值已知，请你帮他安排一下，用他仅剩的一点时间来做最有价值的作业。
 * 接口说明
 * 原型：
 * int GetMaxValue(int nPapers, int nRemain, int paper[][2], double* pMaxValue)
 * 输入参数：
 * int  nPapers：试卷的数目(1≤Papers≤20)
 * int  nRemain：表示剩余的时间(1≤nRemain≤10000)
 * int  paper[][2]：nPapers*2的数组，每一行的两个元素依次为做完这一份试卷所需的时间、做完这份试卷获取的价值。如果剩余时间不够做完一份卷子，可根据剩余时间获得卷子的部分价值。
 * 输出参数：
 * double * pMaxValue：获得的最大价值
 * 返回值：
 * 0:异常，1:成功
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>

int GetMaxValue(int nPapers, int nRemain, int paper[][2], double* pMaxValue)
{
    if (nPapers < 0 || nPapers > 200 || nRemain < 0 || nRemain > 10000)
    {
        return 0;
    }

    *pMaxValue = 0;

    int timesum = 0; //一共使用的时间
    int count = 0; //做完的试卷数目

    double average[20] = { 0 }; //存放每套试卷的价值时间比

    for (int i = 0; i < nPapers; i++)
    {
        average[i] = paper[i][1] / (double) paper[i][0];
    }

    do
    {
        double maxValue = 0;
        int maxValueIndex = 0;

        /*找到价值时间比最大的试卷*/
        for (int i = 0; i < nPapers; i++)
        {
            if (maxValue < average[i])
            {
                maxValue = average[i];
                maxValueIndex = i;
            }
        }
        average[maxValueIndex] = 0; //表示已经做完或者部分做完改试卷

        if (timesum + paper[maxValueIndex][0] < nRemain)
        {
            timesum += paper[maxValueIndex][0];
            *pMaxValue += paper[maxValueIndex][1];
        }
        else
        {
            *pMaxValue += (double) paper[maxValueIndex][1]
                          / (double) paper[maxValueIndex][0] * (nRemain - timesum);
            timesum = nRemain;
        }
        count++;
    } while (timesum < nRemain && count < nPapers);
    return 1;
}

int main()
{
    double Ret;
    int M = 4;
    int N = 20;
    int paper_type_value[][2] = {{4,10},{5,22},{10,3},{1,2}};
    GetMaxValue(M, N,paper_type_value, &Ret);

    std::cout << (abs(37.00 - Ret) <= 0.01) << std::endl;
}

