// libjiangxin.cpp

#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "jiangxin.h"

char jx_getchar(short option)
{
    char ch,temp;
    ch = getchar();
    if(ch == '\n') //ֱ������س�������'\n'
        return '\n';
    else if((temp=getchar())!='\n') //����һЩ�ַ�����ֹһ������Ȼ��س�����������ַ��󷵻�'\n'
    {
        while((temp=getchar())!='\n' && temp!=EOF);
        return '\n';
    }
    else //����һ���ַ������س��������������Сдת����ֱ�ӷ���
    {
        switch(option)
        {
            case 1:ch = tolower(ch);break;
            case 2:ch = toupper(ch);break;
            default:
                perror("Error Argument:option\n");
                break;
        }
        return ch;
    }
}
void jx_PrintBye(void)
{
    puts("\nThanks for your use!");
}
void jx_PrintAuthorInfo()
{
    puts("Do you want to see the detail infomation about the program(Y/N):");
    char ch = jx_getchar((short)1);
    while((ch!='y') && (ch!= 'n'))
    {
        puts("Invalid Input,Please Input Again!");
        ch = jx_getchar((short)1);
    }
    if(ch == 'y')
    {
        #ifdef _windows_
            system("notepad.exe README.txt");
        #endif
        #ifdef _linux_
            system("vim README.txt");
        #endif
    }
}
