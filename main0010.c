/**
函数名: gcvt
用 法: char *gcvt(double value, int ndigit, char *buf);
包含头文件:<stdlib.h>
参数
value——被转换的值。
Digits——存储的有效数字位数。
Buffe——结果的存储位置。
返回值
返回一个指向结果的存储位置的指针[1]
说明
gcvt函数把一个浮点值转换成一个字符串(包括一个小数点和可能的符号字节)并存储该字符串在buffer中。
该buffer应足够大以便容纳转换的值加上结尾的空字符('\0'),它是自动添加的。
如果一个缓冲区的尺寸为digits的尺寸+1,该函数覆盖该缓冲区的末尾。
这是因为转换的字符串包括一个小数点以及可能包含符号和指数信息。不提供上溢出。
gcvt试图以十进制格式产生digits数字,如果不可能,它以指数格式产生digits数字,在转换时可能截除尾部的0。

标准里面并没有这个函数，但是大多数实现中有该函数
*/
#include <stdlib.h>
#include <stdio.h>
int main0010()
{
        char str[25];
        double num;
        int sig = 5; /* significant digits */
        /* a regular number */
        num = 9.876;
        gcvt(num, sig, str);
        printf("string = %s\n", str);
        /* a negative number */
        num = -123.4567;
        gcvt(num, sig, str);
        printf("string = %s\n", str);
        /* scientific notation */
        num = 0.678e5;
        gcvt(num, sig, str);
        printf("string = %s\n", str);
        return(0);
}
