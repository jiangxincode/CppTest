/*
4. ��Ƴ���
��1������Ӽ��������һϵ�������ĺͣ�����-1������
��2������Ӽ��������һϵ�������ĺͣ�Ҫ�������������ĸ�����
*/
#include <iostream>

using namespace std;

int main2534()
{
    int result = 0;
    int input_integer;
    cout << "********************Test One********************" << endl;
    cout << "Input a integer: ";
    cin >> input_integer;

    while(input_integer!=-1)
    {
        result += input_integer;
        cout << "Input a integer: ";
        cin >> input_integer;
    }

    cout << "The result is: " << result << endl;
    cout << "********************Test Two********************" << endl;
    int input_num;
    result = 0;
    cout << "HOW MANY numbers that you want to input: ";
    cin >> input_num;

    for(int i=0; i<input_num; i++)
    {
        cout << "Input a integer: ";
        cin >> input_integer;
        result += input_integer;
    }

    cout << "The result is: " << result << endl;
    return 0;
}
