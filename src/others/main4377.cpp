/**
 * 英文金曲大赛
 * 题目描述
 * 我们在“渊子数”的题目中已经了解了渊子是个什么样的人了，他在大一的时候参加过工商学院的“英语聚乐部”。告诉你个秘密，这个俱乐部是个好地方，不但活动精彩而且有MM。 这不，英语俱乐部举办了一个叫做“英文金曲大赛”的节目。这个节目有好多人参加，这不，成绩出来了，渊子当时很勇敢，自告奋勇接下了算出大家的总得分的任务。 当时有7个评委，每个评委都要给选手打分，现在要求去掉一个最高分和去掉一个最低分，再算出平均分。结果精确到小数点后两位。
 * 样例输入
 * 10 10 10 10 10 10 9 xiaoyuanwang
 * 0 0 0 0 0 0 0 beast
 * 样例输出
 * xiaoyuanwang 10.00\nbeast 0.00
 * 接口说明
 * 函数原型：
 *     void GetResult(char* pInput[], int Num, char* pResult);
 * 输入参数（指针指向的内存区域保证有效）：
 *    char* pInputString：字符串数组，是输入的成绩和姓名。分数是0-10的整数，名字的长度不超过30个字符
 *   int Num：整数，参赛选手的数量，2 <= Num <= 26。
 * 输出参数（指针指向的内存区域保证有效）：
 *    char* pResult：一块buffer，输出所有参赛者的姓名和平均分（保留2位小数）。格式要求如下：
 *    1、姓名在前，平均分在后，中间由一个空格隔开；
 *    2、每行参赛者的成绩占一行（最后一个参赛者成绩之后不要换行符）；
 *    3、输出成绩按输入顺序排序。
 * 返回值：
 *   void
 *
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/*
功能:	计算所有选 手的平均得分。

输入参数（指针指向的内存区域保证有效）：
	 	char* pInputString：字符串数组，是输入的成绩和姓名。分数是0-10的整数，名字的长度不超过30个字符
		int Num：整数，参赛选手的数量，2 <= Num <= 26。
输出参数（指针指向的内存区域保证有效）：
	 	char* pResult：一块buffer，输出所有参赛者的姓名和平均分（保留2位小数）。格式要求如下：
			1、姓名在前，平均分在后，中间由一个空格隔开；
			2、每行参赛者的成绩占一行（最后一个参赛者成绩之后不要换行符）；
			3、输出成绩按输入顺序排序。
返回值：
		void

*/


void GetResult(char* pInput[], int Num, char *pResult)
{
    pResult[0] = '\0';
    for(int i=0;i<Num;i++)
    {
        stringstream io(pInput[i]);
        vector<int> vec;
        for(int j=0;j<7;j++)
        {
            int i_temp;
            io >> i_temp;
            vec.push_back(i_temp);
        }
        vec.erase(find(vec.begin(),vec.end(),*max_element(vec.begin(),vec.end()))); //删除最大值
        vec.erase(find(vec.begin(),vec.end(),*min_element(vec.begin(),vec.end()))); //删除最小值

        int i_temp = 0;
        for (vector<int>::iterator it=vec.begin();it!=vec.end();++it)
        {
            i_temp += *it;
        }

        char str_temp[BUFSIZ];
        io >> str_temp;

        strcat(pResult, str_temp);
        sprintf_s(str_temp, " %.2f\n", i_temp/5.0f);
        strcat(pResult, str_temp);
    }
    pResult[strlen(pResult)-1] = '\0';
    return;
}

int main() {
    {
        char *input[] = {"10 10 10 10 10 10 9 xiaoyuanwang"};
        char result[100] = {0};
        GetResult(input, 1, result);
        std::cout << (0 == strcmp(result, "xiaoyuanwang 10.00") ) << std::endl;
    }



    {
        char *input[] = {"10 10 10 10 10 10 9 xiaoyuanwang","0 0 0 0 0 0 0 beast"};
        char result[100] = {0};
        GetResult(input, 2, result);
        std::cout << (0 == strcmp(result, "xiaoyuanwang 10.00\nbeast 0.00") ) << std::endl;
    }
}
