/*
��Ϊ
���´����ǰ�һ���ַ�����ת���硰abcd��������Ϊ��dcba��
*/
#include <iostream>
#include <cstring>

using namespace std;

int main05411()
{
    char src[] = "Happy New Year!";
    int len = strlen(src);

    for(int i=0; i<len/2; i++)
    {
        char temp = src[i];
        src[i] = src[len-1-i];
        src[len-1-i] = temp;
    }

    cout << src << endl;
    return 0;
}

int main05412()
{
    const char *src = "Happy New Year!";
    int len = strlen(src);
    char *dest = new char[len+1];
    char *d = dest;
    dest += len;
    *dest = '\0';
    dest--;

    while(*src != '\0')
    {
        *dest-- = *src++;
    }

    cout << d << endl;
    delete []dest;
    dest = NULL;
    return 0;
}

int main05413()
{
    const char *src = "Happy New Year!";
    int len = strlen(src);
    char *dest = new char[len+1];
    int i;

    for(i=0; i<len; i++)
    {
        dest[i] = src[len-1-i];
    }

    *(dest+len) = '\0';
    cout << dest << endl;
    delete []dest;
    return 0;
}

int main0541()
{
    main05412();
    return 0;
}

