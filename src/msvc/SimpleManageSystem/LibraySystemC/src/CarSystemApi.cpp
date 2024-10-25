#include <stdio.h>
#include <string.h>

#include "api.h"
#include "car.h"


#define MAX_COMMAND_NUM 3 //������������Ӷ���
#define MAX_COMMAND_LENGTH 128 //��������ÿ���Ӷε���󳤶�

/*****************************************************************************
�� �� ��  : api_print_result
��������  : ��ӡ��������Ϣ��socket���ߴ���
�������  : enum OP_RST_INFO enResultCode
�������  : ��
�� �� ֵ  : extern void
���ú���  :
��������  :
�޸���ʷ  :
1.��    ��   : 2010��1��21��
��    ��   :
�޸�����   : �����ɺ���
*****************************************************************************/
void api_print_result(enum OP_RST_INFO enResultCode)
{
    switch (enResultCode)
    {
    case S001:puts("��ʼ���ɹ�");
        break;
    case S002:puts("Υ���¼¼��ɹ�");
        break;
    case E001:puts("ϵͳδ��ʼ��");
        break;
    case E002:puts("����ʱ�䳬��ϵͳ����Χ");
        break;
    case E003:puts("����δ�����ͳ���ϵͳ����Χ");
        break;
    case E004:puts("�����ѵ��� ����ʧ��");
        break;
    case E005:puts("������ɽ���ϵͳ����Χ");
        break;
    case E006:puts("���ɶ�����Ч");
        break;
    case E007:puts("��Υ���¼ ����Ҫ���ɷ���");
        break;
    case E008:puts("ʱ�����С���ϴβ���ʱ��");
        break;
    case E009:puts("Υ���¼����");
        break;
    case E010:puts("��Υ���¼");
        break;
    case E999:puts("ϵͳ�ڲ�����");
        break;
    default:puts("��Ч����");
        break;
    }
    return;
}


/*****************************************************************************
�� �� ��  : api_print_query_info
��������  : ��ӡ��ѯ��Ϣ��socket���ߴ���
�������  : QueryResult *pResult
�������  : ��
�� �� ֵ  : extern void
���ú���  :
��������  :
�޸���ʷ  :

1.��    ��   : 2010��1��21��
��    ��   :
�޸�����   : �����ɺ���

*****************************************************************************/
void api_print_query_info(QueryResult *pResult)
{
    printf("<<---------- Υ����Ϣ%d---------->>\n", pResult->Index);

    printf("Υ��ʱ�� = %d\n", pResult->Time);

    switch(pResult->Reason)
    {
    case PECCANCY_TYPE_0:printf("Υ��ԭ�� = Υ��ͣ��\n");break;
    case PECCANCY_TYPE_1:printf("Υ��ԭ�� = ����\n");break;
    case PECCANCY_TYPE_2:printf("Υ��ԭ�� = �����\n");break;
    case PECCANCY_TYPE_3:printf("Υ��ԭ�� = ����\n");break;
    case PECCANCY_TYPE_4:printf("Υ��ԭ�� = ��Ƽݳ�\n");break;
    default:printf("��Ч����\n");break;
    }

    printf("������ = %d\n", pResult->Fee);

    switch(pResult->PayFlag)
    {
    case STAT_NO_PAY:printf("�ѽ��ɷ��� = ��\n");break;
    case STAT_HAVE_PAY:printf("�ѽ��ɷ��� = ��\n");break;
    default:printf("��Ч����\n");break;
    }

    printf("ʣ����� = %d\n", pResult->Score);

    return;
}


/*****************************************************************************
�� �� ��  : api_print_pay_info
��������  : ��ӡ������Ϣ��socket���ߴ���
�������  : PayResult  *pResult
�������  : ��
�� �� ֵ  : extern void
���ú���  :
��������  :
�޸���ʷ  :
1.��    ��   : 2010��1��21��
��    ��   :
�޸�����   : �����ɺ���
*****************************************************************************/
void api_print_pay_info(PayResult  *pResult)
{
    printf("<<---------- ������Ϣ---------->>\n");
    printf("���� = %d\n", pResult->ReturnMoney);
    printf("ʣ����� = %d\n", pResult->Score);
    printf("ʣ��Υ���¼�� = %d\n", pResult->PeccancyNo);
    printf("ʣ�෣���� = %d\n", pResult->Fee);

    return;
}


/*****************************************************************************
�� �� ��  : api_server_start
��������  : ����socket����˪��������ķ�ʽ�����û�����
�������  : ��
�������  : ��
�� �� ֵ  : extern void
���ú���  :
��������  :
�޸���ʷ  :
1.��    ��   : 2010��1��21��
��    ��   :
�޸�����   : �����ɺ���
*****************************************************************************/
void api_server_start(int argc, char* argv[])
{
    printf("ϵͳ����\n");

    while(1)
    {
        char command;
        scanf("%c", &command);

        if(command == 'i')
        {
            opInit();
        }
        else if(command == 'r')
        {
            int Peccancy;
            int Days;
            scanf("%d-%d", &Peccancy, &Days);
            opRecord(Peccancy, Days);
        }
        else if(command == 'q')
        {
            opQuery();
        }
        else if(command == 'p')
        {
            int Money;
            scanf("%d", &Money);
            opPay(Money);
        }
        else
        {
            printf("��Ч����\n");
            continue;
        }
    }
    return;
}

