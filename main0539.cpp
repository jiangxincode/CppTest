/*
趋势科技2013面试题
1：首先上来先写了个小程序，很简单，可是写完了，面试官给我指出一堆问题，用指针没判空，用数组没动态分配内存
输入："abcdefgh" 循环移位3位输出 "defghabc"
*/
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void shift1(char *str, int length, int shift_bit) //less time,more space
{
    if(str == NULL)
    {
        return ;
    }

    char *result = new char[length+1];

    if(result == NULL)
    {
        cerr << "error:allocate";
        exit(1);
    }

    if(shift_bit >= 0) //shift left
    {
        for(int i=0; i<length; i++)
        {
            result[i] = str[(i+shift_bit)%length];
        }
    }
    else //shift right
    {
        for(int i=0; i<length; i++)
        {
            result[(i-shift_bit)%length] = str[i];
        }
    }

    for(int i=0; i<length; i++)
    {
        str[i] = result[i];
    }
    delete []result;
}

void shift2(char *str, int length, int shift_bit) //less space, more time
{
    int count = 0;
    int i = 0;

    if(shift_bit >= 0) //shift left
    {
        while(count < length)
        {
            char *temp = str+i;
            str[i] = str[(i+3)%length];
            str[(i+3)%length] = *temp;
            i = (i+3)%length;
            count ++;
        }
    }
    else //shift right
    {
        while(count < length)
        {
            char *temp = str+i;
            str[i] = str[(i+(length+shift_bit))%length];
            str[(i+(length+shift_bit))%length] = *temp;
            i = (i+(length+shift_bit))%length;
            count ++;
        }
    }
}
int main0539()
{
    char str[BUFSIZ];
    scanf("%s",str);
    shift2(str,strlen(str),-3);
    cout << str;
    return 0;
}
