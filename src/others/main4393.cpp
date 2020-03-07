/**
 * 字符串替换
 * 写出一个程序，接受三个参数，分别是一个字符串和两个字符，然后输出替换字符后的字符串。区分大小写。
 * 例如1：
 * 输入：ABCDEF，A，B
 * 输出：BBCDEF
 * 例如2:
 * 输入：AABCDEF，A，C
 * 输出：CCBCDEF
 *
 */
//unsolved 一个测试用例未通过


#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

/*
功能:

输入:

输出:

返回:成功0,其它-1

*/

int ProcessString(char * strInput,char chSrc,char chDes ,char * strOutput)
{
    if((strInput == NULL) || (strOutput == NULL))
    {
        return -1;
    }
    unsigned i = 0;
    while(*(strInput+i) != '\0')
    {
        if(*(strInput+i) == chSrc)
        {
            *(strOutput+i) = chDes;
        }
        else
        {
            *(strOutput+i) = *(strInput+i);
        }
        i++;
    }
    strOutput[i] = '\0';
    return 0;
}

int main() {
    {
        char strInput[] = "d545a";
        char strSrc[] = "d545d";
        char strOutput[10] = "";
        ProcessString(strInput,'a','d',strOutput);
        std::cout << (0 == strcmp(strOutput, strSrc)) << std::endl;
    }

    {
        char strInput[] = "d545a";
        char strSrc[] = "d545c";
        char strOutput[10] = "";
        ProcessString(strInput,'a','c',strOutput);
        std::cout << (0 == strcmp(strOutput, strSrc)) << std::endl;
    }

    {
        char* strInput = NULL;
        char strSrc[] = "d545c";
        char strOutput[10] = "";
        std::cout << (-1 == ProcessString(strInput,'a','c',strOutput)) << std::endl;
    }

    {
        char strInput[] = "d545a";
        char* strOutput = NULL;
        std::cout << (-1 == ProcessString(strInput,'a','c',strOutput)) << std::endl;
    }
}
