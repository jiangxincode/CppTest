/*
成绩平均分、绩点的输入和计算。
包括两种计算方法：
1. 直接按照成绩计算；
2. 按照等级计算 A90以上 B80以上 C70以上 D60以上 E其他。
实现功能：
1. 录入成绩、录入学分；
2. 按照成绩输出当前绩点；
3. 按照等级计算当前绩点；
4. 清空当前记录；
5. 结束。
通过命令行提示用户输入数字以执行相应的功能。注意录入成绩和学分应可以在前面成绩的基础上。
注：
1. 学分用来与成绩进行加权；
2. 按照等级计算即按照五分制计算绩点，绩点可为小数。
*/
#include <iostream>

using namespace std;

void calc_GPA();

int main()
{
    calc_GPA();

    while(1)
    {
        cout << "You want to flush the content or to quit the program(f/q): ";
        char ch;
        cin >> ch;

        if(ch == 'f')
        {
            calc_GPA();
        }
        else
        {
            return 0;
        }
    }
}
void calc_GPA()
{
    float score;
    float sum_score_100=0.0,sum_score_5=0.0; //百分制和五分制
    short credit,sum_credit=0;
    cout << "Input the score and credit,separate with space(quit with \"-1 -1\"): ";
    cin >> score >> credit;

    while(credit != -1)
    {
        sum_score_100 += score*credit;
        sum_score_5 += (score/10-5)*credit;
        sum_credit += credit;
        cout
                << "Now your weighted average GPA is: "
                << sum_score_100/sum_credit
                <<" Or "
                <<sum_score_5/sum_credit
                << endl;
        cout << endl;
        cout << "Input the score and credit,separate with space,(quit with \"-1 -1\"): ";
        cin >> score >> credit;
    }
}
