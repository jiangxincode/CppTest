/**
 * 水仙花数
 * https://www.nowcoder.com/practice/11c9f023a9f84418a15b48792a5f7c70
 * https://www.nowcoder.com/practice/dc943274e8254a9eb074298fb2084703
 * 水仙花数又称阿姆斯特朗数。
 * 水仙花数是指一个n 位数( n≥3 )，它的每个位上的数字的n 次幂之和等于它本身。（例如：1^3 + 5^3 + 3^3 = 153）
 * 求输入的数字是否为水仙花数
 */


/**
 * 阿姆斯特朗数
 * 如果一个正整数等于其各个数字的立方和，则该数称为阿姆斯特朗数(亦称为自恋性数)，1除外，如407 = 43+03+73就是一个阿姆斯特朗数。试编程求n(n ≤ 65536)以内的所有阿姆斯特朗数。
 * 接口说明
 * 原型：int CalcArmstrongNumber(int n);
 * 输入参数：int n: n ≤ 65536
 * 返回值：n以内的阿姆斯特朗数的数量
 */

#include <iostream>

using namespace std;

int is_armstrong(int num)
{
    int temp = num;
    int result = 0;
    int bit_count = 0; //数字的位数
    int bit[1024]; //存放各位数字

    if(num <= 0) //只对正整数进行判断
    {
        return 0;
    }

    for(int i=0; i<1024; i++) //初始化
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
        for (int j=0;j<bit_count;j++)
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

int CalcArmstrongNumber(int n)
{
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

int main(int argc, char* argv[]) {
    //cout << CalcArmstrongNumber(400) << endl; // 3
    //cout << is_armstrong(153) << endl; // 1
    //cout << is_armstrong(151) << endl; // 0

    size_t begin;
    size_t end;
    while (scanf("%u %u", &begin, &end) > 0) {
        bool isFirst = true;
        for (size_t i = begin; i<= end; i++) {
            if (is_armstrong(i) == 1) {
                if (isFirst) {
                    cout << i;
                    isFirst = false;
                } else {
                    cout << " " << i;
                }
            }
        }
        if (isFirst) {
            cout << "no" << endl;
        } else {
            cout << endl;
        }
    }
}
