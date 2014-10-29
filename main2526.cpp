/*
用switch语句实现：
从键盘输入一个星期的某一天(用0表示星期天；用1表示星期一；…)，输出其对应的英语单词。
*/
#include <iostream>
using namespace std;
int main2526()
{
    short s_day;
    string str_day;
    cout << "请输入一个星期的某一天： ";
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
