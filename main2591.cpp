/*
ʵ�ֽ������ַ���ת��Ϊ�������͵Ĺ��ܣ�
�����ù����ú������з�װ��
���磬���롰0.142�������Ϊһ��double���ͣ���ֵΪ0.142��
������ʹ��atoi��atof��atol�Ⱥ�����
*/

#include <stdio.h>
#include <iostream>

using namespace std;
float atof(char *c)
{
    float f=0,t=0,te=1;
    int i,op=1,eop=0,ep=0,cf=0;;
    for (i = 0; c[i]; i++)
    {
        if (c[i]=='.')
        {
            op=0;
        }
        if (c[i]=='e'||c[i]=='E')
        {
            eop=1;
            op=2;
        }
        if (eop&&c[i]=='-')
        {
            cf=1;
        }
        else if (eop&&c[i]=='+')
        {
            cf=0;
        }
        if (op==1&&c[i]>='0'&&c[i]<='9')
        {
            f=f*10+(c[i]-'0');
        }
        else if(!op&&c[i]>='0'&&c[i]<='9')
        {
            te*=10;
            t=t*10+c[i]-'0';
        }
        else if (eop&&c[i]>='0'&&c[i]<='9')
        {
            ep=ep*10+c[i]-'0';
        }
    }
    f=f+t/te;
    te=1;

    for (i = 0; i<ep; i++)
    {
        te*=10;
    }
    if (cf)
    {
        return f/te;
    }
    else return f*te;
}
int main2591()
{
    float f=0;
    char a[]="0.142";
    f=atof(a);
    cout << f;
    return 0;
}
