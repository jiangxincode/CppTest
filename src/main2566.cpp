/*
生成一个长度为100的数组，其中的数据由随机函数产生（范围在1~100），编程求出其中所有的极大值和极小值。
（极大值是指某元素的值比它左右的值都大，极小值是指某元素的值比它左右的值都小。）
*/
#include <iostream>
#include <cstdlib>

using namespace std;

int main2566()
{
    int i_array[100];

    for(int i=0; i<100; i++)
    {
        i_array[i] = rand();
    }

    cout << "随机数据：" << endl;

    for(int i=0; i<100; i++)
    {
        cout << i_array[i] << " ";
    }

    cout << "极大值：" << endl;

    for(int i=0,j=1,k=2; k<100; i++,j++,k++)
    {
        if(i_array[j]>i_array[i]&&i_array[j]>i_array[k])
        {
            cout << i_array[j] << " ";
        }
    }

    cout << endl;
    cout << "极小值：" << endl;

    for(int i=0,j=1,k=2; k<100; i++,j++,k++)
    {
        if(i_array[j]<i_array[i]&&i_array[j]<i_array[k])
        {
            cout << i_array[j] << " ";
        }
    }

    return 0;
}
