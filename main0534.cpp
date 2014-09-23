/*
2014百度校园招聘笔试题
有一个数组，里面的元素相邻之间相差绝对值1，如{4,5,6,5,4,5,6,7,8,7,8,9}，
先给定已数据A请输出该数据在数组中的位置J？
*/
#include <iostream>
#include <cstdlib>
using namespace std;

int main0534()
{
    int N = 12,A;
    int *arr = new int[12]{4,5,6,5,4,5,6,7,8,7,8,9};
    int place[N/2+1];
    cin >> A;
    int j=0;
    for(int i=0;i<N;)
    {
        if(arr[i] == A)
        {
            place[j++] = i;
            i += 2;
        }
        else
        {

            i += abs(arr[i]-A);
        }
    }
    for(int i=0;i < j;i++)
    {
        cout << place[i] << " ";
    }
    return 0;
}
