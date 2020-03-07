/**
 * 水仙花数
 * 类似：
 * https://www.nowcoder.com/practice/11c9f023a9f84418a15b48792a5f7c70
 * https://www.nowcoder.com/practice/dc943274e8254a9eb074298fb2084703
 * 水仙花数又称阿姆斯特朗数。
 * 水仙花数是指一个n 位数( n≥3 )，它的每个位上的数字的n 次幂之和等于它本身。（例如：1^3 + 5^3 + 3^3 = 153）
 * 求输入的数字是否为水仙花数
 */
#include <vector>
#include <iostream>

using namespace std;

unsigned int IsDaffodilNum(unsigned int  nValue)
{
    vector<unsigned int> vec;

    unsigned int temp = nValue;

    while(temp > 0)
    {
        unsigned int bit = temp%10;
        vec.push_back(bit);
        temp /= 10;
    }

    unsigned int sum = 0;
    for(vector<unsigned int>::iterator it=vec.begin();it!=vec.end();it++)
    {
        unsigned int temp = *it;
        unsigned int mul = 1;
        for(unsigned int i=0;i<vec.size();i++)
        {
            mul *= temp;
        }
        sum += mul;
    }

    if(sum == nValue)
    {
        return 1;
    }
    return 0;
}

int main()
{
    unsigned int nResult = IsDaffodilNum(153);

    std::cout << (1 == nResult) << std::endl;

    nResult = IsDaffodilNum(151);

    std::cout << (0 == nResult) << std::endl;
}