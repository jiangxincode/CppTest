#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "api.h"


/*ȫ�ֱ�������*/
ParkingHisInfoNode *hisInfo = NULL; //��ʷ��Ϣ����
CardStatus PackingCard[CARD_COUNT]; //ͣ����
CarInfo_ST carInfo[MAX_AUTO_COUNT]; //����Ϣ���������ƺţ��Լ���ͣ������


ParkSysTime sysTime; //ϵͳʱ��


void main(int argc, char* argv[])
{
    OpReset();
    apiServerStart(argc,argv);
}


/*****************************************************************************
 �� �� ��  : OpReset
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,ϵͳ��ʼ��
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
void OpReset(void)
{
    int i=0;
    for(i=0; i<CARD_COUNT; i++)
    {
        PackingCard[i] = CARD_IDLE; //�����е�ͣ�������Ϊ����
    }

    if(hisInfo != NULL)
    {
        resetList(hisInfo); //�ͷ�����
    }

    hisInfo = initList(); //��ʼ������
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //ϵͳ�ڲ�����
    }

    /*��ʼ��������Ϣ*/
    for(i =0; i<MAX_AUTO_COUNT; i++)
    {
        carInfo[i].info.ParkingCount = 0; //ͣ������
        carInfo[i].info.AutoNo = 0; //���ƺ�
        carInfo[i].info.CardNo = CARD_COUNT; //����
        carInfo[i].info.AutoType = AUTO_TYPE_BUTT; //��������
        carInfo[i].isInSys = false; //�Ƿ��ڳ�����
        carInfo[i].isValidNo = false; //�Ƿ������Ƴ�
    }
    
    sysTime.hh = 0;
    sysTime.mm = 0;
    
    api_parksys_ret(OP_RESET_SUCC);
    
}

/*****************************************************************************
 �� �� ��  : OpGetin
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,��������ͣ����
 �������  : UL AutoNo ���ƺ�
 ParkSysAutoType AutoType ��������
 ParkSysTime InTime ��������ͣ����ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��9��
    ��    ��   :
    �޸�����   : �����ɺ���

 *****************************************************************************/
void OpGetin(UL AutoNo, ParkSysAutoType AutoType, ParkSysTime InTime)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //ϵͳ�ڲ�����
        return;
    }
    int i = 0;
    int cardIdx = 0;
    bool isIdle = false;

    /*�������ƺźϷ����ж�*/
    if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*�������ͺϷ����ж�*/
    if((AutoType != CAR) && (AutoType != BUS))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*����ʱ��Ϸ����ж�(h)*/
    if((InTime.hh < MIN_TIME_H) || (InTime.hh > MAX_TIME_H))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*����ʱ��Ϸ����ж�(m)*/
    if((InTime.mm< MIN_TIME_M) || (InTime.mm> MAX_TIME_M))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*ʱ���߼��ж�*/
    if(InTime.hh < sysTime.hh ||
        ( InTime.hh == sysTime.hh && InTime.mm < sysTime.mm ))
    {
        api_parksys_ret(OP_E_TIME_LOGIC);
        return;
    }

    /*�жϳ�λ�Ƿ���*/
    for(i = 0; i<CARD_COUNT; i++)
    {  
        if(PackingCard[i] == CARD_IDLE)
        {
            isIdle = true;
            cardIdx = i;
            break;
        }
    }

    /*��λ����*/
    if(!isIdle)
    {
        api_parksys_ret(OP_E_PARKING_FULL);
        return;
    }
    
    for(i = 0; i < MAX_AUTO_COUNT; i++)
    {
        /*����Ϣ�Ѿ�����*/
        if(AutoNo == carInfo[i].info.AutoNo)
        {
            /*���Ѿ��ڳ�λ*/
            if(carInfo[i].isInSys)
            {
                api_parksys_ret(OP_E_EXISTED_ATUO);
                return;
            }
            /*�ó���֮ǰ�Ѿ��ж�Ϊ���Ƴ�*/
            if(carInfo[i].isValidNo)
            {
                api_parksys_ret(OP_E_MISMATCH_AUTO_TYPE);
                return;
            }
            /*ǰ�����Ͳ�ͬ��Ϊ���Ƴ�*/
            if(carInfo[i].info.AutoType!= AutoType)
            {
                api_parksys_ret(OP_E_MISMATCH_AUTO_TYPE);
                carInfo[i].isValidNo = true;
                deleteItemWithAutoNo(hisInfo,AutoNo);
                return;
            }
            
            PackingCard[cardIdx] = CARD_INUSE;
            
            carInfo[i].isInSys = true;
            carInfo[i].info.CardNo = cardIdx;
            carInfo[i].info.CurGetInTime = InTime;
            carInfo[i].info.ParkingCount++;
            
            sysTime = InTime;
            
            api_parksys_ret(OP_PARKING_SUCC);

            ParkingAutoHistoryInfo info;
            
            info.AutoNo = carInfo[i].info.AutoNo;
            info.AutoType = carInfo[i].info.AutoType;
            info.CardNo = carInfo[i].info.CardNo;
            info.Fee = 0;
            info.GetInTime = InTime;
            info.GetOutTime.hh = 99;
            info.GetOutTime.mm = 99;
            
            insertItem(hisInfo,info);

            return;
        }
    }

    /*�ó���Ϣ֮ǰ������*/
    for(i = 0; i < MAX_AUTO_COUNT; i++)
    {
        if(carInfo[i].info.AutoNo == 0)
        {
            PackingCard[cardIdx] = CARD_INUSE;
            
            carInfo[i].info.AutoNo = AutoNo;
            carInfo[i].isInSys = true;
            carInfo[i].isValidNo = false;
            carInfo[i].info.AutoType = AutoType;
            carInfo[i].info.CardNo = cardIdx;
            carInfo[i].info.CurGetInTime = InTime;
            carInfo[i].info.ParkingCount ++;
            
            sysTime = InTime;
            
            api_parksys_ret(OP_PARKING_SUCC);

            ParkingAutoHistoryInfo info;
            
            info.AutoNo = carInfo[i].info.AutoNo;
            info.AutoType = carInfo[i].info.AutoType;
            info.CardNo = carInfo[i].info.CardNo;
            info.Fee = 0;
            info.GetInTime = InTime;
            info.GetOutTime.hh = 99;
            info.GetOutTime.mm = 99;
            
            insertItem(hisInfo,info);

            return;
        }
    }
}


/*****************************************************************************
�� �� ��  : OpGetout
��������  : ��Ҫ����ʵ�ֵĽӿ�,�����뿪ͣ����
�������  : UL AutoNo ���ƺ�
UL CardNo ����
ParkSysTime OutTime �����뿪ͣ����ʱ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2009��9��9��
   ��    ��   :
   �޸�����   : �����ɺ���

*****************************************************************************/
void OpGetout(UL AutoNo, UL CardNo, ParkSysTime OutTime)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //ϵͳ�ڲ�����
        return;
    }

    /*���ƺźϷ��Լ��*/
    if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*���źϷ��Լ��*/
    if((CardNo < 0) || (CardNo >= CARD_COUNT))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*�뿪ʱ��Ϸ��Լ��(h)*/
    if((OutTime.hh < MIN_TIME_H) || (OutTime.hh > MAX_TIME_H))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*�뿪ʱ��Ϸ��Լ��(m)*/
    if((OutTime.mm < MIN_TIME_M) || (OutTime.mm > MAX_TIME_M))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*�뿪ʱ���߼����*/
    if(OutTime.hh < sysTime.hh ||
        ( OutTime.hh == sysTime.hh && OutTime.mm < sysTime.mm ))
    {
        api_parksys_ret(OP_E_TIME_LOGIC);
        return;
    }
    
    int i = 0;
    int carIdx = 0;
    bool isInSys = false;

    /*����Ƿ���ڸó���Ϣ*/
    for(i = 0; i<MAX_AUTO_COUNT; i++)
    {
        if(carInfo[i].info.AutoNo == AutoNo && carInfo[i].isInSys)
        {
            carIdx = i;
            isInSys = true;
            break;
        }
    }

    /*����ͣ����*/
    if(!isInSys)
    {
        api_parksys_ret(OP_E_NOT_IN_PARKING);
        return;
    }

    /*���ƺźͿ��Ų���Ӧ*/
    if(carInfo[carIdx].info.AutoNo != AutoNo ||
        carInfo[carIdx].info.CardNo != CardNo) {
        api_parksys_ret(OP_E_AUTONO_MISMATCH_CARDNO);
        return;
    }
    
    sysTime = OutTime;
    
    int fee = cost(carInfo[carIdx].info.CurGetInTime,OutTime,carInfo[carIdx].info.AutoType);
    api_parksys_fee(fee);
    
    carInfo[carIdx].isInSys = false;
    carInfo[carIdx].info.CardNo = 5;
    
    PackingCard[CardNo] = CARD_IDLE;

    updateItem(hisInfo,carInfo[carIdx].info.AutoNo,carInfo[carIdx].info.CurGetInTime,fee,OutTime);

    return;
}

/*****************************************************************************
 �� �� ��  : OpListIdleParkingSpaceNumber
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,ͣ�������г�λ��ѯ
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
void OpListIdleParkingSpaceNumber(void)
{
    UL sum = 0;
    int i = 0;
    for(i=0; i<CARD_COUNT; i++)
    {
        if(PackingCard[i] == CARD_IDLE)
        {
            sum++;
        }
    }
    api_parksys_idle_parkingspace_number(sum);
}

/*****************************************************************************
 �� �� ��  : OpListCardStatus
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,ָ����״̬��ѯ
 �������  : UL CardNo ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��9��
    ��    ��   :
    �޸�����   : �����ɺ���

 *****************************************************************************/
void OpListCardStatus(UL CardNo)
{
    if(CardNo <0 || CardNo >= CARD_COUNT)
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }
    
    if(PackingCard[CardNo] == CARD_IDLE)
    {
        api_parksys_card_status(CARD_IDLE);
        return;
    }
    else
    {
        api_parksys_card_status(CARD_INUSE);
        return;
    }
}

/*****************************************************************************
 �� �� ��  : OpListParkingAuto
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,ͣ������ָ��������Ϣ��ѯ
 �������  : UL AutoNo ���ƺ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��9��
    ��    ��   :
    �޸�����   : �����ɺ���

 *****************************************************************************/
void OpListParkingAuto(UL AutoNo)
{
    if((AutoNo < MIN_AUTONO) || AutoNo > MAX_AUTONO)
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }
    
    bool isInSys = false;
    int i = 0;
    
    for(i =0 ; i <11; i++)
    {
        if(carInfo[i].info.AutoNo == AutoNo)
        {
            if(carInfo[i].isInSys == true)
            {
                isInSys = true;
                break;
            }
        }
    }
    
    if(!isInSys)
    {
        api_parksys_ret(OP_E_NOT_IN_PARKING);
        return;
    }
    
    api_parksys_parking_auto(&carInfo[i].info);
    return;
}

/*****************************************************************************
 �� �� ��  : OpListParkingAutoHistoryInfo
 ��������  : ��Ҫ����ʵ�ֵĽӿ�,ͣ��������ʷ���г���ͣ����Ϣ��ѯ
 �������  : UL AutoNo ���ƺ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��9��
    ��    ��   :
    �޸�����   : �����ɺ���

 *****************************************************************************/
void OpListParkingAutoHistoryInfo(UL AutoNo)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR);
        return;
    }
    if(AutoNo != 0)
    {
        if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
        {
            api_parksys_ret(OP_E_PARAMETER);
            return;
        }
    }
    
    bool flag = false;
    ParkingHisInfoNode * pTemp = hisInfo->pNext;
    if(AutoNo == 0)
    {
        while(pTemp != NULL)
        {
            api_parksys_parking_auto_history_info(&pTemp->data);
            if(!flag)
            {
                flag = true;
            }
            if(pTemp->pNext == NULL)
            {
                break;
            }
            pTemp = pTemp->pNext;
        }
        if(!flag)
        {
            api_parksys_ret( OP_ANY_CAR_PAKING);
        }
        return;
    }
    while(pTemp != NULL)
    {
        if(pTemp->data.AutoNo == AutoNo)
        {
            api_parksys_parking_auto_history_info(&pTemp->data);
            if(!flag)
            {
                flag = true;
            }
        }
        if(pTemp->pNext == NULL)
        {
            break;
        }
        pTemp = pTemp->pNext;
    }
    if(!flag)
    {
        api_parksys_ret(OP_SPEC_CAR_PARKING);
    }
    return;

}

