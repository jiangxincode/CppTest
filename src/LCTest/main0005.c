#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("\033[10;10H"); //设置光标位置
    printf("\033[32m Hello"); //设置前景为绿色
    printf("\033[12;10H"); //设置光标属性
    printf("\033[41m World"); //设置背景为红色
    printf("\033[30m\033[47m\n\n\n\n\n"); //设置前景为黑色，背景为白色
    printf("\033[31m The ......\n\033[0m"); //设置前景为红色，然后恢复默认设置
    printf("\033[2;7;1mHEOO.\n\033[2;7;0m");
    printf("\033[41;36msomthe here\n\033[0m");
    return 0;
}

