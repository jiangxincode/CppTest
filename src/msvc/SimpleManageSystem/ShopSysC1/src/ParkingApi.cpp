#include <stdio.h>
#include <string.h>
#include "api.h"

#define MAX_COMMAND_LENGTH 128 //ÿ�������ַ����Կո�ֽ��������󳤶�
#define MAX_COMMAND_NUM 4 //���������Ŀ�

/*****************************************************************************
  �� �� ��  : api_parksys_ret
  ��������  : ϵͳ�ṩ�ĺ���,����������,��ӡ���������Ϣ
  �������  : ParkSysOpRet OpRet�����붨��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_ret(ParkSysOpRet OpRet)
{
    switch(OpRet)
    {
    case OP_E_CMD :
        puts("��Ч����");
        break;
    case OP_RESET_SUCC :
        puts("ϵͳ��ʼ���ɹ�");
        break;
    case OP_E_PARAMETER :
        puts("�������Ϸ�");
        break;
    case OP_E_PARKING_FULL :
        puts("��λ����");
        break;
    case OP_E_EXISTED_ATUO :
        puts("�ó��Ѿ���ͣ����");
        break;
    case OP_E_MISMATCH_AUTO_TYPE :
        puts("���������Ƴ����������");
        break;
    case OP_E_NOT_IN_PARKING :
        puts("�ó�����ͣ����");
    case OP_E_AUTONO_MISMATCH_CARDNO :
        puts("���ƺźͿ��Ų���Ӧ�������뿪");
        break;
    case OP_E_TIME_LOGIC :
        puts("ʱ���߼�����");
        break;
    case OP_PARKING_SUCC :
        puts("ͣ�������ɹ�");
        break;
    case OP_SPEC_CAR_PARKING :
        puts("ָ���ĳ�����ͣ��������δͣ��");
        break;
    case OP_ANY_CAR_PAKING :
        puts("ͣ��������δ���κγ���ͣ��");
        break;
    case OP_INTERNAL_ERR :
        puts("ϵͳ�ڲ�����");
        break;
    default :
        puts("fetal error");
        break;
    }
}

/*****************************************************************************
  �� �� ��  : api_parksys_fee
  ��������  : ϵͳ�ṩ�ĺ���,����������,�����뿪ͣ��������ȡ�ķ���
  �������  : UL fee����ͣ����ȡ�ķ���
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_fee(UL fee)
{
    printf("����:%uԪ\n",fee);
    return;
}

/*****************************************************************************
  �� �� ��  : api_parksys_idle_parkingspace_number
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ�������г�λ��ѯ���
  �������  : UL number���г�λ��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_idle_parkingspace_number(UL number)
{
    printf("��ǰ���г�λ��:%d\n", number);
    return;
}

/*****************************************************************************
  �� �� ��  : api_parksys_card_status
  ��������  : ϵͳ�ṩ�ĺ���,����������,ָ����״̬��ѯ���
  �������  : CardStatus cardStatusָ����״̬
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_card_status(CardStatus cardStatus)
{
    switch(cardStatus)
    {
    case CARD_IDLE :
        printf("��״̬:δʹ��\n");
        break;
    case CARD_INUSE :
        printf("��״̬:��ʹ��\n");
        break;
    default :
        break;
    }
    return;
}

/*****************************************************************************
  �� �� ��  : api_parksys_parking_auto
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ������ָ��������Ϣ��ѯ���
  �������  : ParkingAutoInfo *pAutoInfoͣ������ָ��������Ϣ
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_parking_auto(ParkingAutoInfo *pAutoInfo)
{
    printf("���ƺ�:%u ����:%u ��ǰ����ʱ��:%02u:%02u ����:%u ͣ������:%u\n",
        pAutoInfo->AutoNo,
        pAutoInfo->CardNo,
        pAutoInfo->CurGetInTime.hh,
        pAutoInfo->CurGetInTime.mm,
        (UL)pAutoInfo->AutoType,
        pAutoInfo->ParkingCount);
    return;
}

/*****************************************************************************
  �� �� ��  : api_parksys_parking_auto_history_info
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ������ָ��������Ϣ��ѯ���
  �������  : ParkingAutoHistoryInfo *pAutoHistoryInfoͣ��������ʷ����ͣ����Ϣ
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void api_parksys_parking_auto_history_info(ParkingAutoHistoryInfo *pAutoHistoryInfo)
{
	printf("���ƺ�:%u ��������:%u ����:%u ͣ��ʱ��:%02u:%02u ȡ��ʱ��:%2u:%2u ����:%u\n",
        pAutoHistoryInfo->AutoNo,
        (UL)pAutoHistoryInfo->AutoType,
        pAutoHistoryInfo->CardNo,
        pAutoHistoryInfo->GetInTime.hh,
        pAutoHistoryInfo->GetInTime.mm,
        pAutoHistoryInfo->GetOutTime.hh,
        pAutoHistoryInfo->GetOutTime.mm,
        pAutoHistoryInfo->Fee);
    return;
}


/*****************************************************************************
 �� �� ��  : api_server_start
 ��������  : ����socket����ˣ��������ķ�ʽ�����û�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���

*****************************************************************************/
void apiServerStart(int argc, char* argv[])
{
    while(1)
    {
        char command[MAX_COMMAND_NUM][MAX_COMMAND_LENGTH]; //ÿ�������ַ������Էֽ�Ϊ���ɸ����
		char temp[MAX_COMMAND_LENGTH];

        int i = 0;
        int j = 0;
        
        /*��ʼ��temp*/
        for(i=0; i<MAX_COMMAND_LENGTH; i++)
        {
            temp[i] = '\0';
        }

        /*��ʼ��command*/
        for(i=0; i<MAX_COMMAND_NUM; i++)
        {
            for(j=0; j<MAX_COMMAND_LENGTH; j++)
            {
                command[i][j] = '\0';
            }
        }

        scanf("%s", command[0]);
		if(strncmp(command[0], "reset", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            OpReset();
			continue;
        }
		else if(strncmp(command[0], "listpn", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            OpListIdleParkingSpaceNumber();
			continue;
        }

		scanf("%s", temp);
        char *p = temp;
        i = 0;
        j = 1;

        while(*p != '\0')
        {
            while((*p != ' ') && (*p != '-') && (*p != ':') && (*p != '\0'))
            {
                command[j][i++] = *(p++);
            }
            i = 0;
            j++;
            if(*p != '\0')
            {
                p++;
            }
        }

        if(strncmp(command[0], "getin", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            ParkSysAutoType AutoType;
            ParkSysTime InTime;

            sscanf(command[1], "%u", &AutoNo);

            if(strncmp(command[2], "0", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
            {
                AutoType = CAR;
            }
            else if(strncmp(command[2], "1", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
            {
                AutoType = BUS;
            }
            else
            {
                AutoType = AUTO_TYPE_BUTT;
            }

            sscanf(command[3], "%uc", &InTime.hh);
            sscanf(command[4], "%uc", &InTime.mm);

            OpGetin(AutoNo, (ParkSysAutoType)AutoType, InTime);

        }
        else if(strncmp(command[0], "getout", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            UL CardNo;
            ParkSysTime OutTime;

            sscanf(command[1], "%u", &AutoNo);
            sscanf(command[2], "%u", &CardNo);
            sscanf(command[3], "%uc", &OutTime.hh);
            sscanf(command[4], "%uc", &OutTime.mm);

            OpGetout(AutoNo,CardNo,OutTime);
        }
        else if(strncmp(command[0], "listcs", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL CardNo;
            sscanf(command[1], "%u", &CardNo);
            OpListCardStatus(CardNo);
        }
        else if(strncmp(command[0], "listai", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            sscanf(command[1], "%u", &AutoNo);
            OpListParkingAuto(AutoNo);
        }
        else if(strncmp(command[0], "lisths", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            sscanf(command[1], "%u", &AutoNo);
            OpListParkingAutoHistoryInfo(AutoNo);
        }
        else
        {
            puts("��Ч������");
        }
    }
}
