/*
设计程序，将用24小时制表示的时间转换为12小时制表示的时间。例如，
输入20和16（20点16分），输出8:16pm；
输入8和16（8点16分），输出8:16am。
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
