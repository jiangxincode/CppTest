/*
����һ������Ϊ100�����飬���е����������������������Χ��1~100�����������������еļ���ֵ�ͼ�Сֵ��
������ֵ��ָĳԪ�ص�ֵ�������ҵ�ֵ���󣬼�Сֵ��ָĳԪ�ص�ֵ�������ҵ�ֵ��С����
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

    cout << "������ݣ�" << endl;

    for(int i=0; i<100; i++)
    {
        cout << i_array[i] << " ";
    }

    cout << "����ֵ��" << endl;

    for(int i=0,j=1,k=2; k<100; i++,j++,k++)
    {
        if(i_array[j]>i_array[i]&&i_array[j]>i_array[k])
        {
            cout << i_array[j] << " ";
        }
    }

    cout << endl;
    cout << "��Сֵ��" << endl;

    for(int i=0,j=1,k=2; k<100; i++,j++,k++)
    {
        if(i_array[j]<i_array[i]&&i_array[j]<i_array[k])
        {
            cout << i_array[j] << " ";
        }
    }
    return 0;
}
