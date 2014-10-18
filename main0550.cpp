/**
ʵ�ֺ���atoi��itoa


*/
int atoi(const char *s)
{
    int dat = 0;
    bool neg = false;

    if(*s == '-')
    {
        s++;
        neg = true;
    }

    while(*s)
    {
        dat *= 10;

        if(*s >= '0' || *s <= '9')
            dat += *s - '0';
        else
            return -1;

        s++;
    }

    return neg ? (-1*dat) : dat;
}

/**
num����ת�������ͱ���   str��ָ���Ž��    radix:����
*/
char *itoa(int num, char *str, int radix)
{
    const char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = str;

    if(num == 0)
    {
        //��ֵΪ0ʱ
        *ptr++ = '0';
        *ptr = '\0';
        return str;
    }

    bool neg = false;

    if(num < 0)
    {
        //��ֵС��0ʱ����Ӹ��ţ�����ָ�����
        neg = true;
        num *= -1;
        *ptr++ = '-';
    }

    while(num)
    {
        *ptr++ = table[num % radix];
        num /= radix;
    }

    *ptr = '\0';
    //��ת�ַ���
    char *beg = (neg ? str +1 : str);
    ptr--;

    while(beg < ptr)
    {
        int temp = *beg;
        *beg  = *ptr;
        *ptr  = temp;
        beg++;
        ptr--;
    }

    return str;
}
