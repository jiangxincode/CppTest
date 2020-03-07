/**
 * 求M的N次方的最后三位
 * 正整数M 的N次方有可能是一个非常大的数字，我们只求该数字的最后三位
 * 例1：
 * 比如输入5和3 ，5的3次方为125，则输出为125
 * 例2：
 * 比如输入2和10  2的10次方为1024 ，则输出结果为24
 * 例3：
 * 比如输入111和5  111的5次方为116850581551，则输出结果为551
 *
 */
#include <stdlib.h>
#include <iostream>



unsigned int  GetLastThreeNumOfResult(unsigned int  m, unsigned int  n)
{

    unsigned int lastThreeNum = m % 1000;
    unsigned int result = 1;

    for(unsigned int i=0;i<n;i++)
    {
        result = (result % 1000) * lastThreeNum;
    }

    return result % 1000;
}

int main() {
    {
        unsigned int nResult =  GetLastThreeNumOfResult (5,3);


        std::cout << (125 == nResult) << std::endl;
    }

    {
        unsigned int nResult =  GetLastThreeNumOfResult (34567,9);


        std::cout << (GetLastThreeNumOfResult (567,9) == nResult) << std::endl;
    }

    {
        unsigned int nResult =  GetLastThreeNumOfResult (4562,2);


        std::cout << (GetLastThreeNumOfResult (562,2) == nResult) << std::endl;
    }
}
