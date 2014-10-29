/*
假设一整型数组中的元素按从小到大的顺序排列，编写C语言函数，删除其中的重复元素。
比如，若一维数组中的数据是：2 2 2 3 4 4 5 6 6 6 6 7 7 8 9 9 10 10 10，
函数执行后，该一维数组中的数据是：2 3 4 5 6 7 8 9 10。
*/
#include <iostream>
#include <set>

using namespace std;

int main2564()
{
    int i_array_1[100] = {2,2,2,3,4,4,5,6,6,6,6,7,7,8,9,9,10,10,10};
    set<int> my_set;
    int i_array_2[100] = {};

    for(int i=0; i_array_1[i]!=0; i++)
    {
        cout << i_array_1[i] << " ";
        my_set.insert(i_array_1[i]);
    }

    cout << endl;
    int array_end = 0;

    for(int elem:my_set) //需要编译器支持C11标准
    {
        i_array_2[array_end] = elem;
        array_end++;
    }

    for(int i=0; i_array_2[i]!=0; i++)
    {
        cout << i_array_2[i] << " ";
    }

    return 0;
}
