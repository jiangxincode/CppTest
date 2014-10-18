/**
 * 字符串与数字相互转换
 */

#include <stdlib.h>
#include <stdio.h>

int main00021()
{
    char *str_num = "1234";
    int i_num = atoi(str_num);
    printf("string:%s,int:%d",str_num,i_num);

    return 0;
}

/**
 * 该方法从int转成char *是不推荐的，被iso取消，但是大部分系统支持，
 * 主要优点是可以改变进制
 */
/*
int main00022()
{
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
    return 0;
}
*/

/**
 * 已知从0点开始的秒数(seconds) ，计算出字符串"H:M:S",  其中H是小时, M＝分钟，S＝秒
 */
int main00023()
{
    int H, M, S,seconds;
    char ctime[10];
    char *time_str;
    puts("Input the seconds");
    scanf("%d",&seconds);
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
    sscanf(str, "%d", &i); // 将字符串转换成整数   i = 15
    sscanf(str, "%f", &fp); // 将字符串转换成浮点数 fp = 15.455000
    printf("Integer: = %d ", i+1);
    printf("Real: = %f ", fp+1);
    return 0;
}

int main0002()
{
    main00023();
    return 0;
}
