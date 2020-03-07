/**
 * 查找同构数的数量
 * 找出1至n之间同构数的个数。同构数是这样一组数：它出现在平方数的右边。例如：5是25右边的数，25是625右边的数，5和25都是同构数。
 * 详细描述：
 * 接口说明
 * 原型：
 * intSearchSameConstructNum(int n);
 * 输入参数：
 *     int n：查找1至n之间的全部同构数
 * 返回值：
 *         int：1至n之间同构数的个数
 */
#include <iostream>

int SearchSameConstructNum(int n)
{
    /*在这里实现功能*/
    int count=0;
    for(int i=1;i<=n;i++)
    {
        int bit_count=0;
        int square = i * i;

        int temp = square;
        while(temp > 0)
        {
            temp /= 10;
            bit_count++;
        }

        temp = 1;
        for(int j=0;j<bit_count;j++)
        {
            temp *= 10;
            if(square % temp == i)
            {
                count++;
                break;
            }
        }
    }
    return count;
}

int main()
{
    int  iRet;

    iRet = SearchSameConstructNum(5);

    std::cout << (iRet == 2) << std::endl;
}
