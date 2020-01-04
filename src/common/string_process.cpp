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


/**
 * 在一个字符串中找到所有只出现一次的字符,采用hash表，复杂的为O(n)
 */
void FindOne(char *input, char *output)
{
    int HashTable[256] = {0};
    int length = 0;
    int k = 0;

    for(int i=0; input[i]!='\0'; i++)
    {
        HashTable[input[i]-'\0']++;
        length++;
    }

    for(int i=0; i<256; i++)
    {
        if(HashTable[i] == 1)
        {
            output[k++] = i;
        }
    }
    output[k] = '\0';
}

/**
实现字符串反转，要求不使用任何系统函数，且时间复杂度最小，
函数原型：char* reverse_str(char* str)
提示：
获取首尾指针，然后将首尾指针指向的元素交换，
将首指针指向下一个，将尾指针指向前一个，交换指针指向的元素，然后重复执行，
直到首尾指针相遇。
*/
#include <stdio.h>
char* reverse_str(char* str)
{
    int i;
    char *start = str;

    for(i=0; str[i]!='\0'; i++); //get the length of the string

    char *end = &str[--i];

    while(start < end) //Do not write start = end, otherwise if length is an even,start can not meet end
    {
        char temp = *end;
        *end = *start;
        *start = temp;
        start ++;
        end --;
    }

    return str;
}

/** \cond */
int main0011()
{
    char str[100];
    char *reverse;
    scanf("%99s",str);
    printf("%s\n",str);
    reverse = reverse_str(str);
    printf("%s\n",reverse);
    return 0;
}
/** \endcond */
