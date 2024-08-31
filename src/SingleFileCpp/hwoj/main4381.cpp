/**
 * 在字符串中找出连续最长的数字串(4381/4428)
 * 题目描述
 *  请一个在字符串中找出连续最长的数字串，并把这个串的长度返回；如果存在长度相同的连续数字串，返回最后一个连续数字串；
 * 注意：数字串只需要是数字组成的就可以，并不要求顺序，比如数字串“1234”的长度就小于数字串“1359055”，如果没有数字，则返回空字符串（“”）而不是NULL！
 * 样例输入
 * abcd12345ed125ss123058789
 * abcd12345ss54761
 *
 * 样例输出
 * 输出123058789，函数返回值9
 * 输出54761，函数返回值5
 * 接口说明
 * 函数原型：
 *    unsignedint Continumax(char** pOutputstr,  char* intputstr)
 * 输入参数：
 *    char* intputstr  输入字符串；
 * 输出参数：
 *    char** pOutputstr: 连续最长的数字串，如果连续最长的数字串的长度为0，应该返回空字符串；如果输入字符串是空，也应该返回空字符串；
 * 返回值：
 *   连续最长的数字串的长度
 *
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "iostream"


/* 功能：在字符串中找出连续最长的数字串，并把这个串的长度返回
函数原型：
   unsigned int Continumax(char** pOutputstr,  char* intputstr)
输入参数：
   char* intputstr  输入字符串
输出参数：
   char** pOutputstr: 连续最长的数字串，如果连续最长的数字串的长度为0，应该返回空字符串
   pOutputstr 指向的内存应该在函数内用malloc函数申请，由调用处负责释放

返回值：
  连续最长的数字串的长度

 */
unsigned int Continumax(char** pOutputstr,  char* intputstr)
{
    int maxLength = 0;
    int maxLengthIndex = -1;
    int currentLength = 0;
    for(unsigned i=0;i<strlen(intputstr);i++)
    {
        if(isdigit(*(intputstr+i)))
        {
            if((++currentLength)>=maxLength)
            {
                maxLength = currentLength;
                maxLengthIndex = i;
            }
        }
        else
        {
            currentLength = 0;
        }
    }
    char* temp = (char*)malloc(sizeof(char)*(maxLength+1));
    for(int i=maxLength-1;i>=0;i--)
    {
        temp[i] = intputstr[maxLengthIndex--];
    }
    temp[maxLength] = '\0';

    /**
     * pOutputstr = &temp;是不正确的，因为虽然temp是在堆区，但是对其取地址之后这个地址是在栈区，调用之后消失
     */
    *pOutputstr = temp;
    return maxLength;
}

int main()
{
    char* intputstr = "abcd12345ed125ss123456789" ;
    char *pOutputstr = NULL;
    unsigned int nLength = Continumax(&pOutputstr, intputstr);
    std::cout << (nLength == 9) << std::endl;
    std::cout << ((pOutputstr != NULL) && (strcmp(pOutputstr,"123456789") == 0)) << std::endl;
    free(pOutputstr);
}
