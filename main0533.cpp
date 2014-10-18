/*
2014百度校园招聘笔试题
有一个数据A = [a_1,a_2,a_3.....a_n],n的大小不定，
请设计算法将A中的所有数据组合进行输出。
我认为组合和排列是不同的，
组合：[a, b, c] == [b, a, c]
排列：[a, b, c] != [b, a, c]
有些人输出的结果是排列。
所以如果是组合的话那结果就简单多了
AllParts( A, n )   //A[1]...A[n]
{

}
*/
#include <iostream>
#include <cstdlib>

using namespace std;

#define MAXNUM 10

int main0533()
{
    int arr[MAXNUM];

    for(int i=0; i<MAXNUM; i++)
    {
        arr[i] = rand()%10;
    }

    for(int i=0; i<MAXNUM; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    for(int i=0; i<MAXNUM; i++) //
    {
        for(int j=i; j<MAXNUM; j++)
        {
            for(int k=i; k<=j; k++)
            {
                cout << arr[k] << " ";
            }

            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
