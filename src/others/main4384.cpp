/**
 * 整数相除
 * 说明：
 * Char *pResult的空间由调用者提供，结果中最多保存十位整数，五位小数，整数部分超出十位，返回失败；小数部分超出五位，四舍五入；
 * 存储结果以字符串形式显示，整数和小数部分需加上小数点。如结果为2.05，则输出的结果为”2.05”。
 *
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

/***********************************************************************
 Description  : 整数相除。
 Input        : unsigned int dividend ：被除数，取值为无符号整数。
                unsigned int divisor： 除数，取值为无符号整数。
 Output       : Char *pResult       ： 运算结果。
 Return Value : 0:成功； -1：失败；
***********************************************************************/
int IntegerDivision (unsigned int dividend,
                     unsigned int divisor,
                     char *pResult)
{
    /*在这里完成代码*/
    double result = (double)dividend/divisor;
    double integer, decimal; //整数部分和小数部分
    decimal = modf(result,&integer);
    if (integer > pow(10.0,10))
    {
        return -1;
    }
    if (dividend%divisor == 0)
    {
        sprintf(pResult,"%d",dividend/divisor);
    }
    else
    {
        sprintf(pResult,"%.5f",result+pow(0.1,6)*5);
    }
    return 0;
}

//下面的是网上的答案
int IntegerDivision1 (unsigned int dividend,unsigned int divisor, char *pResult)
{
    /*在这里完成代码*/
    // 返回-1的情况    除数为0   或者整数部分大于十位的时候  unsigned int最大为多少？
    //int数据类型，在32位系统中（现在基本上int都是32位），范围-2147483648~+2147483647。unsigned类型 的int 范围：0~4294967295 即 0~（2的32次方-1）
    //介  据题目意思   65535  不可能超过十位数啊   所以应该是后面那种即使


    if(divisor==0)
        return -1;

    unsigned int  temp=dividend%divisor;
    if(temp==0)
    {
        unsigned int num=dividend/divisor;
        if(num>999999999)return -1;

        sprintf(pResult,"%d",num);
        return 0;
    }
    else
    {
        double num=(double)dividend/(double)divisor;

        char result[20];
        sprintf(result,"%.5f",num);
        string s=result;

        int pos=s.find_first_of('.');
        if(pos>=11)return -1;

        int len=s.size()-1,nzeropos=len;
        bool iszero=true;
        while(iszero)
        {
            if(result[nzeropos]=='0')
                nzeropos--;
            else
                iszero=false;

        }
        int relpos=0;

        nzeropos=(result[nzeropos]=='.')?(nzeropos-1):nzeropos;
        for(;relpos<=nzeropos;relpos++)
        {
            pResult[relpos]=result[relpos];
        }
        pResult[nzeropos+1]='\0';


    }

    return 0;
}
#define RES_LEN  100
int main() {
    {
        char Result[RES_LEN] = "0";
        unsigned int ret = IntegerDivision(1, 1, Result);
        std::cout << (ret == 0) << std::endl;
        std::cout << (0 == strcmp(Result, "1")) << std::endl;
    }

    {
        char Result[RES_LEN] = "0";
        unsigned int ret = IntegerDivision(8, 2, Result);
        std::cout << (ret == 0) << std::endl;
        std::cout << (0 == strcmp(Result, "4")) << std::endl;
    }
    {
        char Result[RES_LEN] = "0";
        unsigned int ret = IntegerDivision(120, 6, Result);
        std::cout << (ret == 0) << std::endl;
        std::cout << (0 == strcmp(Result, "20")) << std::endl;
    }
}
