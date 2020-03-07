/**
 * 一元多项式化简
 * 背景:
 * 编程实现如下功能：对输入的一元多项式，进行同类项合并，并按指数降序排序，输出处理后的一元多项式。
 *
 * 说明：
 * 	多项式由若干个单项式组成，单项式之间为加、减（+,-）关系。
 * 	单项式指数字与字母幂的乘积构成的代数式。对一元多项式，字母只有一种。
 * 	同类项合并指：将多项式中指数相同的单项式，系数经过加减求和，合并为一个单项式。按指数降序指：多项式中，单项式按指数从大到小顺序相连。
 *
 * 格式说明
 * 一元多项式输入输出时以字符串形式表示，格式如下
 * 	单项式之间用单个加减运算符相连，运算符：+,-
 * 	单项式由系数、字母、指数标识符、指数依次直接相连组成，各部分均不能省略。
 * 	系数：只由若干0到9数字字符组成（系数不等于0，且不以0开头）
 * 	字母：X
 * 	指数标识符：^
 * 	指数：只由若干0到9数字字符组成（指数可等于0，不等于0时不以0开头）
 * 其他约定
 * 	输入不为空串，输出若为0则以空串表示
 * 	字符串中除以上字符，不包含空格等其他字符，字符串尾部以’\0’结束
 * 	多项式中第一个单项式前加运算时省略+符号,减运算时有-符号
 * 注意：输入多项式符合上述格式，无需检查；输出多项式格式由考生程序保证
 *
 * 规格
 * 输入多项式满足如下规格，考生程序无需检查：
 * 	0<单项式系数<=1000
 * 	0<=单项式指数<=3000
 * 	单项式个数不限制，但同类项合并处理后，单项式的系数小于65535。
 *
 * 示例
 * 例一
 * 输入：
 *  "7X^4-5X^6+3X^3"
 * 输出：
 *  "-5X^6+7X^4+3X^3"
 * 例二
 * 输入：
 *  "-7X^4+5X^6-3X^3+3X^3+1X^0"
 * 输出：
 *  "5X^6-7X^4+1X^0"
 *
 */
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

bool comparator(pair<int,int> p1, pair<int,int> p2)
{
    return (p1.first > p2.first);
}
/******************************************************************************************************
Description     : 对输入的一元多项式，进行同类项合并，输出处理后的一元多项式
Prototype       : void OrderPolynomial (char* InputString, char* OutputString)
Input Param     : char* InputString 输入多项式字符串
Output Param    : char* OutputString 输出多项式字符串
Return Value    : void

********************************************************************************************************/
void OrderPolynomial (char* InputString, char* OutputString)
{
    /*在这里实现功能*/
    char* temp = (char*)malloc(sizeof(char)*(strlen(InputString)+1));
    int i = 0, j = 0;
    for(i=0;i<(int)strlen(InputString);i++) //去除X和^字符
    {
        if (InputString[i] == 'X') //去除X和^字符
        {
            temp[j++] = ' ';
            i++;
        }
        else if ((InputString[i] == '+') || (InputString[i] == '-')) //对数字进行分割
        {
            temp[j++] = ' ';
            temp[j++] = InputString[i];
        }
        else
        {
            temp[j++] = InputString[i];
        }
    }
    temp[j] = '\0';
    stringstream io(temp);

    map<int,int> m; //<index,coefficient>，注意第一个是指数，第二个是系数

    int coefficient, index;
    while(io >> coefficient)
    {
        io >> index;
        if (m.find(index) == m.end())
        {
            pair<int,int> p(index,coefficient);
            m.insert(p);
        }
        else
        {
            m[index] = m[index] + coefficient;
        }
    }
    vector<pair<int,int>> vec;
    for(map<int,int>::iterator it=m.begin();it!=m.end();++it)
    {
        pair<int,int> p = *it;
        vec.push_back(p);
    }

    sort(vec.begin(),vec.end(),comparator); //按系数进行排序

    string output = "";
    for(vector<pair<int,int>>::iterator it=vec.begin();it!=vec.end();++it)
    {
        pair<int,int> p = *it;
        if (p.second != 0)
        {
            char str_temp[BUFSIZ];
            sprintf_s(str_temp, "%+dX^%d", p.second, p.first);
            output.append(str_temp);
        }
    }

    i = 0;
    j = 0;
    if (output[i] == '+')
    {
        i++;
    }
    for(;i<(int)output.length();i++)
    {
        OutputString[j++] = output[i];
    }
    OutputString[j] = '\0';

    return;
}

int main()
{
    {
        char *InputString = "7X^4-5X^6+3X^3";
        char *OutputString = NULL;

        OutputString = (char*)malloc(strlen(InputString)+2);
        memset(OutputString,0,strlen(InputString)+2);

        OrderPolynomial(InputString,OutputString);

        std::cout << (strcmp(OutputString, "-5X^6+7X^4+3X^3") == 0) << std::endl;

        free(OutputString);
    }



    {
        char *InputString = "-7X^4+5X^6-3X^3+3X^3+1X^0";
        char *OutputString = NULL;

        OutputString = (char*)malloc(strlen(InputString)+2);
        memset(OutputString,0,strlen(InputString)+2);

        OrderPolynomial(InputString,OutputString);

        std::cout << (strcmp(OutputString, "5X^6-7X^4+1X^0") == 0) << std::endl;

        free(OutputString);
    }
}

