/**
 * 编写一个函数int squeeze(char s1[], const char s2[])
 * 它从字符串s1中删除所有在s2里出现过的字符，并返回删除的字符个数
*/
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_LENGTH 100

int squeeze(char s1[], const char s2[])
{
    int count = 0;
    char str[MAX_LENGTH];
    int k = 0;
    int i,j;

    for(i=0; s1[i]!='\0'; i++)
    {
        bool is_find = false;

        for(j=0; s2[j]!='\0'; j++)
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
    for(i=0;i<k;i++)
    {
        s1[i] = str[i];
    }
    return count;
}

int main2585()
{
    char str[MAX_LENGTH] = "Hello Nanjing University!";
    const char dict[MAX_LENGTH] = "el";
    cout << "the string before operating is: " << str << endl;
    int num = squeeze(str,dict);
    cout << "Delete " << num << " characters" << endl;
    cout << "the string after operating is: " << str << endl;
    return 0;
}
