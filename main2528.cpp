/*
��������� d1~d2 ֮�䣨��d1��d2�����ܱ����� d3 ����������
���û�ÿ����һ��d1��d2��d3��ֵ�������һ�ν��������0��������
*/
#include <iostream>
using namespace std;
int main2528()
{
    int d1,d2,d3;
    cout << "\nInput d1,d2 and d3: ";
    cin >> d1 >> d2 >> d3;
    while(d3!=0)
    {
        for(int i=d1;i<=d2;i++)
        {
            if(i%d3!=0)
            {
                cout << i << "\t";
            }
        }
        cout << "\nInput d1,d2 and d3: ";
        cin >> d1 >> d2 >> d3;
    }
}
