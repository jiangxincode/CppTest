/**
 * 取给定正整数的指定bit位开始的指定长度的数据
 * 接口说明
 * 原型：
 * unsigned int GetBitsValue(unsigned int input, unsigned int startbit, unsigned int bitlen)
 * 输入参数：
 *         input      输入的整数
 *          startbit   需要获取的开始bit
 *          bitlen     需要获取的bit长度
 * 输出参数（指针指向的内存区域保证有效）：
 *     无
 * 返回值：
 *         对应的bit取值
 * 举例：
 * 输入：4, 2, 2
 * 返回：2
 * 4对应的二进制为100（bit0和bit1为0，bit2为1），那么从bit2开始的2位为10，那么对应的十进制为2。
 * 
 */
#include <string>
#include <iostream>

using namespace std;


/*
Description  
         取给定正整数的指定bit位开始的指定长度的数据。bit位从右向左从0开始计算。
Prototype
         unsigned int GetBitsValue(unsigned int input, unsigned int startbit, unsigned int bitlen)
Input Param 
         input      输入的整数
         startbit   需要获取的开始bit
         bitlen     需要获取的bit长度
Output Param 
         无
Return Value
		 对应的bit取值
*/

unsigned int GetBitsValue(unsigned int input, unsigned int startbit, unsigned int bitlen)
{
    /*在这里实现功能*/
    string str = "";
    unsigned int result = 0;

    while(input > 0)
    {
        if(input % 2 == 1)
        {
            str = string("1").append(str);
        }
        else
        {
            str = string("0").append(str);
        }
        input /= 2;
    }
    str = str.substr(str.length()-startbit-1,bitlen);
    for(string::iterator it=str.begin();it!=str.end();it++)
    {
        if(*it == '1')
        {
            result = result*2+1;
        }
        else
        {
            result = result*2;
        }
    }
    return result;
}

int main() {
    std::cout << (GetBitsValue(4, 2, 1)==1) << std::endl;
    std::cout << (GetBitsValue(4, 2, 2)==2) << std::endl;
}
