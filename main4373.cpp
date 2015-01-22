//warning ccbbbbcc dbcc ddbd 题目不严谨，有两种可能
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "oj.h"

/**
将给定字符串中连续出现3次的小写字母替换为改小写字母在字母表中的下一个字母（z变为a），
大写字母和其他字符不处理，仍然保留。
要求最终输出的字符串中不再存在任何连续出现3次的小写字母。
例如字符串”ATRcccert893#45ae”经过处理后应该为”ATRdert893#45ae”

详细描述：

接口说明

原型：

int ChangeString(char *pInStr,char *pOutStr)

输入参数：

char *pInStr 输入字符串

输出参数：

char *pOutStr 输出字符串，内存空间已分配好，可直接使用

返回值：

int 0：处理成功 -1：出现异常


举例：

pInStr：jkds*^*(HKEEEklIdddjilfff
pOutStr：jkds*^*(HKEEEklIejilg
*/


int ChangeString(char *pInStr,char *pOutStr)
{
    strcpy(pOutStr, pInStr);
    bool bChange = false;
    int iCnt = -1;

    do
    {
        bChange = false;
        iCnt = 0;

        while(*(pOutStr + iCnt) != '\0')
        {
            ++iCnt;
        }

        iCnt--;

        for(int i = 0; i < iCnt; ++i)
        {
            char *pCur = pOutStr + i;

            if(*pCur != '\0'
                    && *(pCur + 1) != '\0'
                    && *(pCur + 2) != '\0'
                    && *pCur == *(pCur + 1)
                    && *(pCur + 1) == *(pCur + 2)
                    && *pCur <= 'z'
                    && *pCur >= 'a')
            {
                if(*pCur != 'z')
                {
                    ++*pCur;
                }
                else
                {
                    *pCur = 'a';
                }

                int j;

                for(j = 3; *(pCur + j) != '\0'; ++j)
                {
                    *(pCur + j - 2) = *(pCur + j);
                }

                *(pCur + j - 2) = '\0';
                bChange = true;
                break;
            }
        }
    }
    while(bChange);

    return 0;
}

int main4373()
{
    char* pInStr= "aaaaaaaaacc";
    char pOutStr[1024]= "";

    if(0 == ChangeString(pInStr, pOutStr))
    {
        printf("In : %s\n", pInStr);
        printf("Out : %s\n", pOutStr);
    }
    return 0;
}
