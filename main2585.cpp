/*
编写一个函数int squeeze(char s1[], const char s2[])
它从字符串s1中删除所有在s2里出现过的字符，并返回删除的字符个数。
*/
#include <cstdio>
#include <iostream>

using namespace std;

int squeeze(char s1[], const char s2[]);

int main2585()
{
    char *str = "Hello Nanjing University!";
    const char dict[3] = {'e','l','\0'};
    cout << "the string before operating is: " << str << endl;
    int num = squeeze(str,dict);
    cout << "Delete " << num << " characters" << endl;
}
int squeeze(char s1[], const char s2[])
{
    int count = 0;
    char str[100] = {'\0'};
    int k = 0;

    for(int i=0;s1[i]!='\0';i++)
    {
        bool is_find = false;
        for(int j=0;s2[j]!='\0';j++)
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
    cout << "the string after operating is: " << str << endl;
    return count;
}
