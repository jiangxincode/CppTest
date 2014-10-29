#include<stdio.h>

/**
 * 验证变量名长度的限制（与具体实现有关）
 */
int main1023()
{
    int abcdefghijklmnopqrstuvwxyz012345678 = 1;
    int abcdefghijklmnopqrstuvwxyz0123456789 = 2;
    printf("%d,%d",abcdefghijklmnopqrstuvwxyz012345678,abcdefghijklmnopqrstuvwxyz0123456789);
    return 0;
}

