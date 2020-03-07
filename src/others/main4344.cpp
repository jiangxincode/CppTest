/**
 * 百分制成绩
 * 简要描述：
 * 给出一百分制成绩，要求输出成绩等级‘A’、‘B’、‘C’、‘D’、‘E’。90分以上为A 80-89分为B 70-79分为C 60-69分为D 60分以下为E
 * 输入：
 * 一个整数0－100以内
 * 输出：
 * 一个字符，表示成绩等级
 * 例如：
 * 输入：90
 * 输出：A
 */
#include <stdlib.h>
#include <iostream>

int ScoreLevel(int score)
{
    if((score < 0) || (score > 100))
    {
        return -1;
    }
    else if(score < 60)
    {
        return 'E';
    }
    else if(score < 70)
    {
        return 'D';
    }
    else if(score < 80)
    {
        return 'C';
    }
    else if(score < 90)
    {
        return 'B';
    }
    else
    {
        return 'A';
    }
}

int main()
{
    std::cout << (-1 == ScoreLevel(-1)) << std::endl;
    std::cout << ('A' == ScoreLevel(90)) << std::endl;
}
