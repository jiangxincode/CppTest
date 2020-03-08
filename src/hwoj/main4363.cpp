/**
 * 删除重复字符
 * 题目标题：
 * 删除重复字符
 * 给定一个字符串，将字符串中所有和前面重复多余的字符删除，其余字符保留，输出处理后的字符串。需要保证字符出现的先后顺序，并且区分大小写。
 * 详细描述：
 * 接口说明
 * 原型：
 * int GetResult(const char *input, char *output)
 * 输入参数：
 *      input     输入的字符串
 * 输出参数（需考虑指针指向的内存区域是否有效）：
 *     output    输出的字符串
 * 返回值：
 *         0         成功
 *          -1        失败及异常
 * 举例：
 * 输入: abadcbad，那么该单词中红色部分的字符在前面已经出现过。
 * 则：输出abdc，返回0。
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

/*
Description
         给定一个字符串，将字符串中所有和前面重复多余的字符删除，其余字符保留，输出处理后的字符串。需要保证字符出现的先后顺序?
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
    if(!input||!output)
    {
        return -1;
    }
    int a[CHAR_MAX+1]={0}; //注意方法
    int i=0,j=0;

    while(input[j]!='\0')
    {

        if(a[input[j]]<1)
        {
            a[input[j]]=1;
            output[i++]=input[j++];

        }
        else
        {
            j++;
        }

    }
    output[i]='\0';


    return 0;
}

int main() {
    {
        char result[1024] = {0};
        std::cout << (GetResult("abadcbad",result) == 0) << std::endl;
        std::cout << (strcmp(result, "abdc")==0) << std::endl;
    }

    {
        char result[1024] = {0};
        std::cout << (GetResult("abcabcdeabc",result) == 0) << std::endl;
        std::cout << (strcmp(result, "abcde")==0) << std::endl;
    }

    {
        char result[1024] = {0};
        std::cout << (GetResult("aaaaaaaa",result) == 0) << std::endl;
        std::cout << (strcmp(result, "a")==0) << std::endl;
    }


    {
        char result[1024] = {0};
        std::cout << (GetResult("",result) == 0) << std::endl;
        std::cout << (strcmp(result, "")==0) << std::endl;
    }

    {
        char *result = NULL;
        std::cout << (GetResult("",result) == -1) << std::endl;
    }
}
