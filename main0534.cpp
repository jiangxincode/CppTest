/*
2014�ٶ�У԰��Ƹ������
��һ�����飬�����Ԫ������֮��������ֵ1����{4,5,6,5,4,5,6,7,8,7,8,9}��
�ȸ���������A������������������е�λ��J��
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
