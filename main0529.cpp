/*
���ֲ���x�Ƿ���һ�����������У������������������ȳ��ֵ�λ�ã���0��ʼ�������磺
1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 4 5
��x=3�򷵻�2
�ǵݹ飬��������̽��
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
