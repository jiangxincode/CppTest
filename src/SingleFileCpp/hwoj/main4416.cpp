/**
 * Arrange an Array to Form a Smallest Digit SmallestDigit
 * Question:
 * Input an array of positive integers, arrange the integers to form new digits, and output the smallest digit among all the new ones.
 *
 * Input Example 1:
 * {2, 1}
 * Output Example 1:
 * 12
 *
 * Input Example 2:
 * {32, 321}
 * Output Example 2:
 * 32132
 *
 * Input Example 3:
 * {4589, 101,41425,9999}
 * Output Example 3:
 * 1014142545899999;
 *
 * Interface:
 * int  smallestDigit(int a[],int nCount,char * strRst)
 * Function: Arrange digits in the input array to form a smallest digit.
 * Input: int a[]: an array of integers
 * int nCount: length of the array
 * char * strRst: returned value
 * Output: none
 * Return: 0 indicates success and -1 indicates exception.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
// 功能：将输入的数组排成最小的数
// 输入： int a[]:整型数组
//        int nCount:数组长度
//        char * strRst 返回值
// 输出：
// 返回：成功返回0  异常返回-1
int  smallestDigit(int a[],int nCount,char * strRst)
{
    if ((nCount <= 0) || (strRst == NULL))
    {
        return -1;
    }
    strRst[0] = '\0';
    vector<string> vec;
    for(int i=0;i<nCount;i++)
    {
        string str;
        stringstream io;
        io << a[i];
        io >> str;
        vec.push_back(str);
    }
    sort(vec.begin(),vec.end());
    for (vector<string>::iterator it=vec.begin();it!=vec.end();++it)
    {
        strcat(strRst,(*it).c_str());
    }
    return 0;
}

int main()
{
    int a[] = {2,1};
    char szRst[10]  = {0};
    char *strExpect = "12";
    smallestDigit(a,2,szRst);
    std::cout << (0 == strcmp(szRst,strExpect)) << std::endl;
}

