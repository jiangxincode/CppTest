/**
 * 阿姆斯特朗数
 * 如果一个正整数等于其各个数字的立方和，则该数称为阿姆斯特朗数(亦称为自恋性数)，1除外，如407 = 43+03+73就是一个阿姆斯特朗数。试编程求n(n ≤ 65536)以内的所有阿姆斯特朗数。
 * 接口说明
 * 原型：
 *     int CalcArmstrongNumber(int n);
 * 输入参数：
 *     int n: n ≤ 65536
 *
 * 返回值：
 *         n以内的阿姆斯特朗数的数量
 */
#include <iostream>

using namespace std;

/*
 * 判断是否是阿姆斯特朗数
 */
int is_armstrong(int num)
{
    int temp = num;
    int result = 0;
    int bit_count = 0; //数字的位数
    int bit[11]; //存放各位数字

    if(num <= 0) //只对正整数进行判断
    {
        return 0;
    }

    for(int i=0; i<11; i++) //初始化
    {
        bit[i] = -1;
    }

    while(temp)
    {
        bit[bit_count++] = temp%10;
        temp /= 10;
    }

    for(int i=0; bit[i]!=-1; i++)
    {
        int itemp = 1;
        for (int j=0;j<3;j++)
        {
            itemp *= bit[i];
        }
        result += itemp;
    }

    if(result == num)
    {
        return 1;
    }
    else return 0;
}
/*
功能: 求n(n ≤ 65536)以内的所有阿姆斯特朗数
原型：
    int CalcArmstrongNumber(int n);

输入参数：
    int n: n ≤ 65536

返回值：
    n以内的阿姆斯特朗数的数量。
*/

int CalcArmstrongNumber(int n)
{
    /*在这里实现功能*/
    int result = 0;
    for(int i=2;i<n;i++)
    {
        if (is_armstrong(i))
        {
            result++;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    std::cout << (CalcArmstrongNumber(400) == 3) << std::endl;
}
