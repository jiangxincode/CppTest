/**
 * 找出字符串中第一个出现次数最多的字符
 * 找出字符串中第一个出现次数最多的字符
 * 详细描述：
 * 接口说明
 * 原型：
 * bool FindChar(char* pInputString, char* pChar);
 * 输入参数：
 * char* pInputString：字符串
 * 输出参数（指针指向的内存区域保证有效）：
 * char* pChar：出现次数最多的字符
 * 返回值：
 *         false 异常失败
 *           true  输出成功
 *
 */
#include <map>
#include <utility>
#include <cstring>
#include <iostream>

using namespace std;

/*
功能: 找出字符串中第一个出现次数最多的字符

输入: char* pInputString：字符串

输出: char* pChar：出现次数最多的字符

返回: false 异常失败
	  true  输出成功
*/

bool FindChar(char* pInputString, char* pChar)
{
    //在这里实现功能
    if((pInputString == NULL) || (strlen(pInputString) == 0))
    {
        return false;
    }
    map<char, unsigned int> char2int;
    for (unsigned int i=0;i<strlen(pInputString);i++)
    {
        if (char2int.find(pInputString[i]) != char2int.end())
        {
            char2int[pInputString[i]]++;
        }
        else
        {
            pair<char, unsigned int> p(pInputString[i],1);
            char2int.insert(p);
        }
    }

    unsigned int maxCount = 0;

    for(map<char,unsigned int>::iterator it=char2int.begin();it!=char2int.end();++it)
    {
        pair<char,unsigned int> p = *it;
        if (p.second > maxCount)
        {
            *pChar = p.first;
            maxCount = p.second;
        }
    }

    if (maxCount != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char acIutput[] = "!abcd ABCD!";
    char cResult = '!';
    char cOutput;
    bool bReturn;

    bReturn = FindChar(acIutput, &cOutput);

    std::cout << (true == bReturn) << std::endl;
    std::cout << (cResult == cOutput) << std::endl;
}
