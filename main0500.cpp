#include <iostream>

using namespace std;

int main0500() //����������֮�ͣ�Ҫ���ں������ڲ���ʹ��+��-��*��/�����������
{
    int i_num1,i_num2; // The numbers that user inputs
    cout << "Input two int nums like this: 34 56 Enter" << endl;
    cin >> i_num1 >> i_num2;
    while(i_num2 !=0 )
    {
        int temp = i_num1; //�Ƚ���bitλ��ӣ����ƽ�λ����һ��������m^nʵ��
        i_num1 = i_num1 ^ i_num2;
        i_num2 = (temp & i_num2) << 1; //�ɵõ���λ��Ҫ�ӵ�1��λ��
    }
    cout << "The result of is: " << i_num1 << endl;
    return 0;
}
