/**
 * 周期串问题
 * 题目标题：
 * 题目描述
 * 如果一个字符串可以由某个长度为k的字符串重复多次得到，我们说该串以k为周期。例如，abcabcabcabc以3为周期（注意，它也可以6和12为周期,结果取最小周期3）。字符串的长度小于等于100，由调用者保证。
 *
 * 详细描述：
 * 接口说明
 * 原型：
 *     int GetMinPeriod(char *inputstring);
 * 输入参数：
 *     char * inputstring：字符串
 * 返回值：
 *     int 字符串最小周期
 *
 */
#include <string.h>
#include <iostream>


/*
功能:计算字符串的最小周期。
原型：
    int GetMinPeriod(char *string);

输入参数：
    char * string：字符串。

返回值：
    int 字符串最小周期。

*/

/*这道题提示很简单，在纸上画画就行 */
int GetMinPeriod(char *inputstring)
{
    if((inputstring == NULL) || (strlen(inputstring)) <= 0)
    {
        return 0;
    }
    int minPeriod = 1;
    while(minPeriod < strlen(inputstring))
    {
        if (strlen(inputstring) % minPeriod != 0)
        {
            minPeriod++;
            continue;
        }
        int i = 0;
        for (;i<minPeriod;i++) //周期内循环
        {
            int j = 1;
            for (;j<strlen(inputstring)/minPeriod;j++) //都和第一个周期进行对比
            {
                if (inputstring[j*minPeriod+i] != inputstring[0+i])
                {
                    break;
                }
            }
            if (j != strlen(inputstring)/minPeriod)
            {
                break;
            }
        }
        if (i == minPeriod)
        {
            break;
        }
        else
        {
            minPeriod++;
        }
    }


    return minPeriod;
}

int main()
{
    {
        int iRet;

        char inputstring[13] = "abcabcabcabc";

        iRet = GetMinPeriod(inputstring);

        std::cout << (iRet == 3) << std::endl;
    }

    {
        int iRet;

        char inputstring[13] = "abcdef";

        iRet = GetMinPeriod(inputstring);

        std::cout << (iRet == 6) << std::endl;
    }

    {
        int iRet;

        char inputstring[13] = "abcdabcdabcd";

        iRet = GetMinPeriod(inputstring);

        std::cout << (iRet == 4) << std::endl;
    }

    {
        int iRet;

        char inputstring[13] = "\0";

        iRet = GetMinPeriod(inputstring);

        std::cout << (iRet == 0) << std::endl;
    }

}
