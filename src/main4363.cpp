//unsolved 两个测试用例未通过
#include "OJ.h"

#include <cstdlib>
#include <iostream>

using namespace std;

/*
Description
         给定一个字符串，将字符串中所有和前面重复多余的字符删除，其余字符保留，
         输出处理后的字符串。需要保证字符出现的先后顺序。
Prototype
         int GetResult(const char *input, char *output)
Input Param
         input     输入的字符串
Output Param
         output    输出的字符串
Return Value
         0         成功
         -1        失败及异常
*/
int GetResult(const char *input, char *output)
{
    if((input==NULL) || (output==NULL))
    {
        return -1;
    }

    unsigned int bit = 0; //input的长度，不包括'\0'

    while(*(input+bit) != '\0')
    {
        bit ++;
    }

    char* temp = (char*)malloc(sizeof(char)*(bit+1));
    temp[0] = input[0];

    for(unsigned int i=1; i<bit; i++)
    {
        for(unsigned int j=0; j<i; j++)
        {
            if(input[j] == input[i])
            {
                temp[i] = '\0';
                break ;
            }
            else
            {
                temp[i] = input[i];
            }
        }
    }

    unsigned int index = 0;

    for(unsigned int i=0; i<bit; i++)
    {
        if(temp[i] != '\0')
        {
            output[index++] = temp[i];
        }
    }

    temp[index] = '\0';
    return 0;
}

int main4363()
{
    char result[1024] = {0};
    cout << GetResult("abcabcdeabc",result) << " " << result << endl;
//    CPPUNIT_ASSERT(GetResult("abadcbad",result) == 0);
//    CPPUNIT_ASSERT(strcmp(result, "abdc")==0);
    return 0;
}
