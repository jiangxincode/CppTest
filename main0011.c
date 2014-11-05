/*
百度2014校园招聘-研发工程师笔试题
使用C/C++编写函数，实现字符串反转，要求不使用任何系统函数，且时间复杂度最小，
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
