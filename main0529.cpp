/*
二分查找x是否在一个有序数组中，返回其在数组中最先出现的位置（从0开始），比如：
1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 4 5
若x=3则返回2
非递归，不能左右探测
*/
#include <iostream>

using namespace std;

#define MAXNUM 1000

int main0529()
{
    int arr[MAXNUM];
    for(int i=0;i<MAXNUM;i++)
    {
        arr[i] = i/5;
        //arr[i] = i;
    }
    for(int i=0;i<MAXNUM;i++)
    {
        cout << arr[i] << " ";
        if(i % 10 == 9)
        {
            cout << endl;
        }
    }
    int x;
    cin >> x;
    int low = 0, high = MAXNUM-1;
    int mid;
    while(low <= high)
    {
        mid = (low+high)/2;
        if(arr[mid] < x)
        {
            low = mid+1;
        }
        else if(arr[mid] > x)
        {
            high = mid-1;
        }
        else
        {
            break;
        }
    }
    low = 0; high = mid;
    while(low <= high)
    {
        mid = (low+high)/2;
        if(arr[mid] == x)
        {
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }
    cout << mid;
    return 0;
}
