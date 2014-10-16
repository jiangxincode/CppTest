/**
微软 microsoft
写一个函数找出一个整数数组中，第二大的数
*/
#include <iostream>
#include <climits>
using namespace std;

int second_max(int arr[], int num)
{
    int fir_max = arr[0];
    int sec_max = INT_MIN;
    for(int i=0;i<num;i++)
    {
        if(fir_max < arr[i])
        {
            sec_max = fir_max;
            fir_max = arr[i];
        }
        else if((fir_max > arr[i]) && (sec_max < arr[i]))
        {
            sec_max = arr[i];
        }
    }
    return sec_max;
}
#define MAXNUM 20

int main0549()
{
    int arr[MAXNUM];
    for(int i=0;i<MAXNUM;i++)
    {
        arr[i] = rand()%100;
    }
    for(int i=0;i<MAXNUM;i++)
    {
        cout << arr[i] << " ";
    }
    cout <<  endl;
    cout << second_max(arr,MAXNUM) << " ";
    return 0;
}
