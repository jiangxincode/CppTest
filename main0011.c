/*
�ٶ�2014У԰��Ƹ-�з�����ʦ������
ʹ��C/C++��д������ʵ���ַ�����ת��Ҫ��ʹ���κ�ϵͳ��������ʱ�临�Ӷ���С��
����ԭ�ͣ�char* reverse_str(char* str)
��ʾ��
��ȡ��βָ�룬Ȼ����βָ��ָ���Ԫ�ؽ�����
����ָ��ָ����һ������βָ��ָ��ǰһ��������ָ��ָ���Ԫ�أ�Ȼ���ظ�ִ�У�
ֱ����βָ��������
*/

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


#include <stdio.h>
#define MAX_LENGTH 100
int main0011()
{
    char str[MAX_LENGTH];
    char *reverse;
    scanf("%s",str);
    printf("%s\n",str);
    reverse = reverse_str(str);
    printf("%s\n",reverse);
    return 0;
}
