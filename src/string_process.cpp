#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

/**
 * 编写一个函数int squeeze(char s1[], const char s2[])
 * 它从字符串s1中删除所有在s2里出现过的字符，并返回删除的字符个数
*/
int squeeze(char s1[], const char s2[])
{
    int count = 0;
    char str[BUFSIZ];
    int k = 0;

    for(int i=0; s1[i]!='\0'; i++)
    {
        bool is_find = false;

        for(int j=0; s2[j]!='\0'; j++)
        {
            if(s2[j]==s1[i])
            {
                count ++;
                is_find = true;
                break;
            }
        }

        if(!is_find)
        {
            str[k++] = s1[i];
        }
    }

    str[k] = '\0';

    for(int i=0; i<=k; i++)
    {
        s1[i] = str[i];
    }

    return count;
}


/**
 * 已知一段英文密文的加密方法为：对原文中的每个字母，分别用字母表中该字母之后的第5个字母替换
 * 比如：
 * “I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME”
 * 的密文为
 * “N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ”
 * 编写解密函数
*/
int decode(string &str_src)
{
    for(auto &ch : str_src)
    {
        if(islower(ch))
        {
            auto diff = ch - 'a' - 5;
            ch = (diff<0)?(ch-5+26):(ch-5);
        }
        else if(isupper(ch))
        {
            auto diff = ch - 'A' - 5;
            ch = (diff<0)?(ch-5+26):(ch-5);
        }
    }
    return 0;
}


/**
 * 设计程序，将用24小时制表示的时间转换为12小时制表示的时间。例如，
 * 输入20和16（20点16分），输出8:16pm
 * 输入8和16（8点16分），输出8:16am
*/
int time_convert(string &time24)
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
