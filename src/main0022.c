#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 字符串与数字相互转换问题
 * 所有自定义函数均以n作为前缀(new)
 */


/**
 * 实现将输入字符串转化为浮点类型的函数，要求支持科学计数法
 * 无需考虑错误输入
 * 不允许使用atoi、atof、atol等函数
 * 测试用例
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
    int sign = 1; //标记正负号，默认为正
    int dot = -1; //标记小数点的位置，默认没有小数点
    int sci = -1; //标记e的位置，默认不采用科学计数法
    int index = 0; //以科学计数法表示时的指数，默认不用科学技术法表示

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
        else if((str[i]>='0'&&str[i]<='9') && (dot<0) && (sci<0)) //整数部分
        {
            result = result*10+(str[i]-'0');
        }
        else if((str[i]>='0'&&str[i]<='9') && (dot>0) && (sci<0)) //小数部分
        {
            result = result+pow(0.1,(i-dot))*(str[i]-'0');
        }
        else if((str[i]>='0'&&str[i]<='9') && (sci>=0)) //指数部分
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
 * 实现函数atoi函数的功能
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
 * 实现itoa函数的功能
 * num：待转换的整型变量   str：指向存放结果    radix:基数
 */
char *nitoa(int num, char *str, int radix)
{
    const char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = str;

    if(num == 0)
    {
        //数值为0时
        *ptr++ = '0';
        *ptr = '\0';
        return str;
    }

    bool neg = false;

    if(num < 0)
    {
        //数值小于0时，添加负号，并将指针后移
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
    //反转字符串
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
 * 转换函数的应用
 * 已知从0点开始的秒数(seconds) ，计算出字符串"H:M:S",  其中H是小时, M＝分钟，S＝秒
 */
int time_convert()
{
    int H, M, S,seconds;
    char ctime[10];
    char *time_str;
    puts("Input the seconds");
    scanf("%11d",&seconds);
    H=seconds/3600;
    M=(seconds%3600)/60;
    S=(seconds%3600)%60;
    sprintf(ctime, "%d:%d:%d", H, M, S); // 将整数转换成字符串
    time_str=ctime;
    puts(time_str);
    //与sprintf对应的是 sscanf 函数, 可以将字符串转换成数字.
    char str[] = "15.455";
    int i;
    float fp;
    sscanf(str, "%11d", &i); // 将字符串转换成整数   i = 15
    sscanf(str, "%20f", &fp); // 将字符串转换成浮点数 fp = 15.455000
    printf("Integer: = %d ", i+1);
    printf("Real: = %f ", fp+1);
    return 0;
}


int main0022()
{
    char str[100];
    scanf("%99s",str);
    printf("%f",natod(str));
    const char *str_num = "1234";
    int i_num = atoi(str_num);
    printf("string:%s,int:%d",str_num,i_num);
    /**
    * 该方法从int转成char *是不推荐的，被iso取消，但是大部分系统支持，
    * 主要优点是可以改变进制
    */
//    int i;
//    char buffer [33];
//    printf("Enter a number: ");
//    scanf("%d",&i);
//    itoa(i,buffer,10);
//    printf("decimal: %s\n",buffer);
//    itoa(i,buffer,16);
//    printf("hexadecimal: %s\n",buffer);
//    itoa(i,buffer,2);
//    printf("binary: %s\n",buffer);
    return 0;
}
