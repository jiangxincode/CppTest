//unsolved

/**
描述:  老师想知道从某某同学到某某同学当中，分数最高的是多少。
现在请你编程模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。

输入:
输入包含多组测试数据。
每组输入第一行是两个正整数N和M（0<N<=30000,0<M<5000），分表代表学生的数目和操作的数目。
学生ID编号从1编到N。
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
接下来有M行。每一行有一个字符C(只取‘Q’或‘U’)，和两个正整数A，B。
当C为‘Q’的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。
当C为‘U’的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。

输出:
对于每一次询问操作，在一行里面输出最高成绩。

样例输入: 5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5

样例输出:
5
6
5
9

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

int main4268()
{
    int student_num;
    int operation_num;
    vector<pair<int,int>> vecStuSco;
    vector<int> vecResult;

    cin >> student_num >> operation_num;
    for(int i=1;i<=student_num;i++)
    {
        int score;
        cin >> score;
        pair<int,int> pairStuSco(i,score);
        vecStuSco.push_back(pairStuSco);
    }
    for(int i=1;i<=operation_num;i++)
    {
        string str;
        int operator1,operator2;

        cin >> str >> operator1 >> operator2;
        if(str == "Q")
        {
            int maxScore = 0;
            for(int j=operator1;j<=operator2;j++)
            {
                if(vecStuSco[j].second>maxScore)
                {
                    maxScore = vecStuSco[j].second;
                }
            }
            vecResult.push_back(maxScore);
        }
        else if(str == "U")
        {
            vecStuSco[operator1].second = operator2;
        }
    }

    for(vector<int>::iterator it=vecResult.begin();it!=vecResult.end();it++)
    {
        int temp = *it;
        cout << temp << endl;
    }

    return 0;
}
