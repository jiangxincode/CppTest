/*
2014�ٶ�У԰��Ƹ������
��һ������A = [a_1,a_2,a_3.....a_n],n�Ĵ�С������
������㷨��A�е�����������Ͻ��������
����Ϊ��Ϻ������ǲ�ͬ�ģ�
��ϣ�[a, b, c] == [b, a, c]
���У�[a, b, c] != [b, a, c]
��Щ������Ľ�������С�
�����������ϵĻ��ǽ���ͼ򵥶���
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
