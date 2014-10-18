/**
微软笔试题
只用4行代码编写出一个从字符串到长整形的转换函数
*/

#include <cctype>
#include <iostream>

using namespace std;

long atol(char *str) //字符串转长整形
{
    char c = *str;
    long value;

    if(!isdigit(c)) str++; //判断有无正负号

    for(value = 0; *str != '\0'; value = value * 10 + (*str -'0'),str++);

    return c == '-' ? -value : value ;
}

void stol(const char * des, long& num)
{
    for(int base = 1, i = 0; des[i] != '\0'; base = 10, ++i)
    {
        num *= base;
        num += (int)(des[i] - '0');
    }
}
/**
num 要初始化为0
*/

void stol0(const char * des, long& num)
{
    for(int i=num=0; des[i] != '\0'; i++)
    {
        num *= 10;
        num += (int)(des[i] - '0');
    }
}
void stol(char *str, long &num)
{
    while(*str != '\0')
    {
        num = num * 10 + (*str - '0');
        str++;
    }
}
void stol1(const char * des, long& num, int base)
{
    char p = des[0];

    for(int b = 1, pos = 1, base = 1; des[pos] != '\0'; b = 10, ++pos, base *= 10)
    {
        (num *= b) += (int)(des[pos] - '0');
    }

    p == '-' ? (num *= -1) : (num = (int)(des[0] - '0') * base + num);
}

/**
用STL，四行
*/
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

long ToLong(string& s)
{
    long l;
    istringstream iss(s);
    iss>>l;
    return l;
}
int main2()
{
    string s = "-12356";
    cout<<ToLong(s);
    return 0;
}

int main0545()
{
    cout << atol("123") << endl;
    return 0;
}


