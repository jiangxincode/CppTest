/**
 * 字符串分割
 * 连续输入字符串(输出次数为N,字符串长度小于100)，请按长度为8拆分每个字符串后输出到新的字符串数组，
 * 长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
 * 例如：
 * 输入：
 * abc
 * 123456789
 * 输出：
 * abc00000
 * 12345678
 * 90000000
 *
 */
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


vector<string> vec_output;

/*****************************************************************
功能:存储输入的字符

输入:字符串

输出:无

返回:0表示成功,其它返回-1
****************************************************************/
int  AddString(char *strValue)
{
    if ((strValue == NULL) || (strlen(strValue) <= 0) || (strlen(strValue) >= 100))
    {
        return -1;
    }
    string str(strValue);
    while (str.length() > 8)
    {
        vec_output.push_back(str.substr(0,8));
        str = str.substr(8);
    }
    while (str.length() < 8)
    {
        str.append("0");
    }
    vec_output.push_back(str);
    return 0;
}

/****************************************************************
功能:获取补位后的二维数组的长度

输入:无

输出:无

返回:二维数组长度
******************************************************************/
int  GetLength()
{
    return (int)vec_output.size();
}

/*****************************************************************************
功能:将补位后的二维数组，与输入的二维数组做比较

输入:strInput:输入二维数组,iLen：输入的二维数组的长度

输出:无

返回:若相等,返回0;不相等,返回-1.其它:-1;
******************************************************************************/
int  ArrCmp(char strInput[][9],int iLen)
{
    vector<string> vec_input;
    if (iLen != vec_output.size())
    {
        return -1;
    }

    for (int i=0;i<iLen;i++)
    {
        vec_input.push_back(strInput[i]);
    }
    if (equal(vec_input.begin(),vec_input.end(),vec_output.begin()))
    {
        return 0;
    }
    return -1;
}

int main()
{
    AddString("434353f");
    AddString("ABCDEFG1234");
    AddString("1234567890");

    char strRst[][9] = {"434353f0","ABCDEFG1","23400000","12345678","90000000"};

    std::cout << (5 == GetLength()) << std::endl;
    std::cout << (0 == ArrCmp(strRst,5)) << std::endl;
}
