#include <stdio.h>

int main0032()
{
    char x;
    printf("        ���˵�\n");
    printf("    1.���빦��\n");
    printf("    2.��ѧ�Ų���\n");
    printf("    3.��ӡ���\n");
    printf("    0.�˳�\n");
    printf("  ��ѡ��(0-3):\n");

    do
    {
        scanf(" %c",&x);//c%֮ǰ��Ҫ�ո�����Ϊ���������ֲ��Կո������ʱ��scanf������ǿո���������֣�c%֮ǰ����ո��ֹ�ӻ���������ո�

        switch(x)
        {
        case '1':
            printf("������\n");
            break;

        case '2':
            printf("���������ѧ��ѧ��\n");
            break;

        case '3':
            printf("�������\n");
            break;

        case '0':
            printf("ллʹ��\n");
            break;

        default:
            printf("�������\n");
        }
    }
    while(x!='0');

    return 0;
}
