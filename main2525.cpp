/*
�Ͼ�����ͨ���⳵���շѱ�׼�ǣ�
3�������ڣ���3����շ�9Ԫ��
����3����Ĳ��֣�ÿ�����շ�2.4Ԫ������ÿ���μ���2Ԫȼ�͸��ӷѡ�
��Ƴ��򣬼�������Ĺ�����x����Ӧ�ĳ���y���������
*/
#include <iostream>
using namespace std;

int main2525()
{
    float f_miles = 0.0,f_price = 0.0;
    cout << "��������ʻ�Ĺ������� ";
    cin >> f_miles;

    if(f_miles <= 3)
    {
        f_price = 9.0;
    }
    else
    {
        f_price = 9.0 +(f_miles-3)*2.4+2.0;
    }

    cout << "����Ϊ�� " << f_price;
    return 0;
}
