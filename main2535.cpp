/*
��Ƴ��򣬽���24Сʱ�Ʊ�ʾ��ʱ��ת��Ϊ12Сʱ�Ʊ�ʾ��ʱ�䡣���磬
����20��16��20��16�֣������8:16pm��
����8��16��8��16�֣������8:16am��
*/
#include <iostream>

using namespace std;

int main2535()
{
    short hour,minute;
    cout << "Input the HOUR and MINUTE: ";
    cin >> hour >> minute;

    if(hour <= 12 && hour >=0)
    {
        cout << "The time is: " << hour << ":" << minute << "am";
    }
    else if(hour >12 && hour <= 24)
    {
        cout << "The time is: " << hour%12 << ":" << minute << "pm";
    }
    return 0;
}
