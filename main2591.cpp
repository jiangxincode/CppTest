#include <cmath>
#include <float.h>
#include <iostream>

using namespace std;

/**
 * �ַ����������໥ת������
 * �����Զ��庯������n��Ϊǰ׺(new)
 */


/**
 * ʵ�ֽ������ַ���ת��Ϊ�������͵ĺ�����Ҫ��֧�ֿ�ѧ������
 * ���迼�Ǵ�������
 * ������ʹ��atoi��atof��atol�Ⱥ���
 * ��������
 * input output
 * +3.1367 3.1367
 * -45.78 -45.78
 * 23.78e2 2378
 * 3e4 30000
 * e4 10000
*/
double natod(const char *str)
{
    float result = 0.0;
    int sign = 1; //��������ţ�Ĭ��Ϊ��
    int dot = -1; //���С�����λ�ã�Ĭ��û��С����
    int sci = -1; //���e��λ�ã�Ĭ�ϲ����ÿ�ѧ������
    int index = 0; //�Կ�ѧ��������ʾʱ��ָ����Ĭ�ϲ��ÿ�ѧ��������ʾ

    for(int i=0; str[i]; i++)
    {
        if(str[i] == '+')
        {
            sign = 1;
        }
        else if(str[i] == '-')
        {
            sign = -1;
        }
        else if(str[i] == '.')
        {
            dot = i;
        }
        else if(str[i] == 'e')
        {
            sci = i;
        }
        else if((str[i]>='0'&&str[i]<='9') && (dot<0) && (sci<0)) //��������
        {
            result = result*10+(str[i]-'0');
        }
        else if((str[i]>='0'&&str[i]<='9') && (dot>0) && (sci<0)) //С������
        {
            result = result+pow(0.1,(i-dot))*(str[i]-'0');
        }
        else if((str[i]>='0'&&str[i]<='9') && (sci>=0)) //ָ������
        {
            index = 10*index+(str[i]-'0');
        }
        else
        {
            return 0.0;
        }
    }

    if(fabs(result)<DBL_EPSILON)
    {
        result = 1.0;
    }

    return result*sign*pow(10,index);
}



/**
 * ʵ�ֺ���atoi�����Ĺ���
 */
int natoi(const char *str)
{
    int dat = 0;
    bool neg = false;

    if(*str == '-')
    {
        str++;
        neg = true;
    }

    while(*str)
    {
        dat *= 10;

        if(*str >= '0' || *str <= '9')
            dat += *str - '0';
        else
            return -1;

        str++;
    }

    return neg ? (-1*dat) : dat;
}

/**
 * ʵ��itoa�����Ĺ���
 * num����ת�������ͱ���   str��ָ���Ž��    radix:����
 */
char *nitoa(int num, char *str, int radix)
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


/**
 * ת��������Ӧ��
 * ��֪��0�㿪ʼ������(seconds) ��������ַ���"H:M:S",  ����H��Сʱ, M�����ӣ�S����
 */
int time_convert()
{
    int H, M, S,seconds;
    char ctime[10];
    char *time_str;
    puts("Input the seconds");
    scanf("%d",&seconds);
    H=seconds/3600;
    M=(seconds%3600)/60;
    S=(seconds%3600)%60;
    sprintf(ctime, "%d:%d:%d", H, M, S); // ������ת�����ַ���
    time_str=ctime;
    puts(time_str);
    //��sprintf��Ӧ���� sscanf ����, ���Խ��ַ���ת��������.
    char str[] = "15.455";
    int i;
    float fp;
    sscanf(str, "%d", &i); // ���ַ���ת��������   i = 15
    sscanf(str, "%f", &fp); // ���ַ���ת���ɸ����� fp = 15.455000
    printf("Integer: = %d ", i+1);
    printf("Real: = %f ", fp+1);
    return 0;
}


int main2591()
{
    char str[100];
    cin >> str;
    cout << natod(str);


    const char *str_num = "1234";
    int i_num = atoi(str_num);
    printf("string:%s,int:%d",str_num,i_num);

    /**
    * �÷�����intת��char *�ǲ��Ƽ��ģ���isoȡ�������Ǵ󲿷�ϵͳ֧�֣�
    * ��Ҫ�ŵ��ǿ��Ըı����
    */
    /*
    int i;
    char buffer [33];
    printf("Enter a number: ");
    scanf("%d",&i);
    itoa(i,buffer,10);
    printf("decimal: %s\n",buffer);
    itoa(i,buffer,16);
    printf("hexadecimal: %s\n",buffer);
    itoa(i,buffer,2);
    printf("binary: %s\n",buffer);
    */

    return 0;
}
