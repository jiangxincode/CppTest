/**
 * 生成一个长度为100的数组，其中的数据由随机函数产生（范围在1~100）。
 * 编程求出其中所有的极大值和极小值。（极大值是指某元素的值比它左右的值都大，极小值是指某元素的值比它左右的值都小。）
 */

#include <iostream>
#include <cstdlib>

#define MAX_RANDOM_NUM 100

using namespace std;

int main2566()
{
    int i_array[MAX_RANDOM_NUM];

    for(int i=0; i<MAX_RANDOM_NUM; i++)
    {
        i_array[i] = rand();
    }

    cout << "The original random data:" << endl;

    for(int i=0; i<MAX_RANDOM_NUM; i++)
    {
        cout << i_array[i] << " ";
    }

    cout << endl;
    cout << "The maximum value:" << endl;

    for(int i=1; i<MAX_RANDOM_NUM-1; i++)
    {
        if( (i_array[i] > i_array[i-1]) && (i_array[i] > i_array[i+1]) )
        {
            cout << i_array[i] << " ";
        }
    }

    cout << endl;
    cout << "The minimum value:" << endl;

    for(int i=1; i<MAX_RANDOM_NUM-1; i++)
    {
        if( (i_array[i] < i_array[i-1]) && (i_array[i] < i_array[i+1]) )
        {
            cout << i_array[i] << " ";
        }
    }

    return 0;
}
