/*
����һ��int�ͱ��������丳ֵ��
�ٴ���һ������Ϊ5��int�Ͷ�̬���飬�Ӽ�����������Ԫ�ص�ֵ��
Ȼ�������̬�����Ͷ�̬�����ֵ
*/
#include <iostream>
#include <vector>

using namespace std;

int main2579()
{
    int i_num;
    cout << "Input an integer: ";
    cin >> i_num;

    vector<int> vec_num(5);
    cout << "Input 5 numbers:";
    for(int i=0;i<5;i++)
    {
        int temp;
        cin >> temp;
        vec_num[i] = temp;
    }
    cout << "The integer is: " << i_num << endl;
    cout << "The array is: " << endl;
    for(int i=0;i<5;i++)
    {
        cout << vec_num[i] << " ";
    }
}
