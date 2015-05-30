#include <stdio.h>

int main0032()
{
    char x;
    printf("        主菜单\n");
    printf("    1.输入功能\n");
    printf("    2.按学号查找\n");
    printf("    3.打印输出\n");
    printf("    0.退出\n");
    printf("  请选择(0-3):\n");

    do
    {
        scanf(" %c",&x);//c%之前需要空格是因为当按下数字并以空格键结束时，scanf读入的是空格而不是数字，c%之前加入空格防止从缓冲区读入空格；

        switch(x)
        {
        case '1':
            printf("请输入\n");
            break;

        case '2':
            printf("请输入查找学生学号\n");
            break;

        case '3':
            printf("正在输出\n");
            break;

        case '0':
            printf("谢谢使用\n");
            break;

        default:
            printf("输入错误\n");
        }
    }
    while(x!='0');

    return 0;
}
