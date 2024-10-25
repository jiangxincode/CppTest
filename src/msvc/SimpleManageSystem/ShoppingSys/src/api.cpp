#include <stdio.h>
#include "api.h"

#define OJ_OUTPUT

void api_print_result(enum OP_RST_INFO enResultCode)
{
    switch (enResultCode)
    {
    case S001:
#ifdef OJ_OUTPUT
        puts("S001");
#else
        puts("��ʼ���ɹ�");
#endif
        break;

    case S002:
#ifdef OJ_OUTPUT
        puts("S002");
#else
        puts("�����Ѿ����뵽���ﳵ");
#endif
        break;

    case S003:
#ifdef OJ_OUTPUT
        puts("S003");
#else
        puts("�����Ѵӹ��ﳵ��ɾ��");
#endif
        break;

    case E001:
#ifdef OJ_OUTPUT
        puts("E001");
#else
        puts("�Ƿ�����");
#endif
        break;

    case E002:
#ifdef OJ_OUTPUT
        puts("E002");
#else
        puts("��������");
#endif
        break;

    case E003:
#ifdef OJ_OUTPUT
        puts("E003");
#else
        puts("���ﳵ����");
#endif
        break;

    case E004:
#ifdef OJ_OUTPUT
        puts("E004");
#else
        puts("��ɾ���Ķ���������");
#endif
        break;

    case E005:
#ifdef OJ_OUTPUT
        puts("E005");
#else
        puts("���ﳵ��û����Ʒ����");
#endif
        break;

    case E006:
#ifdef OJ_OUTPUT
        puts("E006");
#else
        puts("���￨������ֲ���");
#endif
        break;

    default:puts("��Ч����");
        break;
    }
    return;
}

