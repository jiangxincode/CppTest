/*
��switch���ʵ�֣�
�Ӽ�������һ�����ڵ�ĳһ��(��0��ʾ�����죻��1��ʾ����һ����)��������Ӧ��Ӣ�ﵥ�ʡ�
*/
#include <iostream>
using namespace std;
int main2526()
{
    short s_day;
    string str_day;
    cout << "������һ�����ڵ�ĳһ�죺 ";
    cin >> s_day;

    switch(s_day)
    {
    case 1:
        str_day = "Monday";
        break;

    case 2:
        str_day = "Tuesday";
        break;

    case 3:
        str_day = "Wednesday";
        break;

    case 4:
        str_day = "Thursday";
        break;

    case 5:
        str_day = "Friday";
        break;

    case 6:
        str_day = "Saturday";
        break;

    case 0:
        str_day = "Sunday";
        break;

    default:
        str_day = "";
        break;
    }

    if(str_day.empty())
    {
        cout << "Something Error!" << endl;
    }
    else
    {
        cout << "The English is: " << str_day;
    }

    return 0;
}
