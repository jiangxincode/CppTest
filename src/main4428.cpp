#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "oj.h"


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

    for(unsigned i=0; i<strlen(intputstr); i++)
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

    for(int i=maxLength-1; i>=0; i--)
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
