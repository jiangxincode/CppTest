/**
 * 整型反序
 * 简要描述：给出一个不多于5位的整数, 进行反序处理
 * 要求:
 * 1、求出它是几位数
 * 2、分别输出每一位数字
 * 3、按逆序输出各位数字，例如原数为321,应输出123（仅数字间以空格间隔, 负号与数字之间不需要间隔）
 *
 * 例如：输入：12345
 * 输出：5
 * 1 2 3 4 5
 * 54321
 *
 * 注意：如果是负数，负号加在第一个数字之前, 与数字没有空格间隔
 * 比如
 *        输入：-12345
 * 输出：5
 * -1 2 3 4 5
 * -54321
 *
*/
#include <stdlib.h>
#include "iostream"
#include <cstring>


/*
功能:
	给出一个不多于5位的整数，
	要求:
		1、求出它是几位数
		2、分别输出每一位数字
		3、按逆序输出各位数字，例如原数为321,应输出123
输入:
	整型 iInput,位数不大于5的整数

输出:
    整数位数		iNum
	空格间隔输出结果    strRst
	逆序整数		iOutput

返回:
	0  成功
	-1 输入无效
*/

int ProcessX(int iInput, int& iNum, char * strRst, int& iOutput)
{
    if ((iInput <= -100000) || (iInput >= 100000)) //参数错误
    {
        return -1;
    }

    int index = 0;
    iNum = 0;
    iOutput = 0;

    if (iInput < 0)
    {
        iInput *= -1; //转为非负数
        strRst[index++] = '-';
    }

    int temp = iInput;
    while(temp > 0)
    {
        iOutput = iOutput * 10 + (temp % 10);
        temp /= 10;
        iNum++;
    }

    temp = iOutput;
    while(temp > 0)
    {
        strRst[index++] = '0' + temp % 10;
        strRst[index++] = ' ';
        temp /= 10;
    }
    strRst[--index] = '\0'; //过滤掉最后一个空格

    if (strRst[0] == '-')
    {
        iOutput *= -1;
    }

    return 0;
}

int main() {
    {
        int iInput = 23546;

        int iNum = 0;
        char strRst[10] = "";
        int iOutput = 0;
        std::cout << (0 == ProcessX(iInput, iNum, strRst, iOutput)) << std::endl;
        std::cout << (5 == iNum) << std::endl;
        std::cout << (0 == strcmp(strRst,"2 3 5 4 6")) << std::endl;
        std::cout << (iOutput == 64532) << std::endl;
    }

    {
        int iInput = -23546;

        int iNum = 0;
        char strRst[10] = "";
        int iOutput = 0;
        std::cout << (0 == ProcessX(iInput, iNum, strRst, iOutput)) << std::endl;
        std::cout << (5 == iNum) << std::endl;
        std::cout << (0 == strcmp(strRst,"-2 3 5 4 6")) << std::endl;
        std::cout << (iOutput == -64532) << std::endl;
    }

    {
        int iInput = 1000000;

        int iNum = 0;
        char strRst[10] = "";
        int iOutput = 0;
        std::cout << (-1 == ProcessX(iInput, iNum, strRst, iOutput)) << std::endl;
    }
}
