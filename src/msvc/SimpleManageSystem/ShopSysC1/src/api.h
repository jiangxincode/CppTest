/******************************************************************************
   �� �� ��   : api.h
   �� �� ��   : ����
   ��    ��   :
   ��������   : 2009��9��9��
   ����޸�   :
   ��������   : api.cpp ��ͷ�ļ�
   �����б�   :
   �޸���ʷ   :
    1.��    ��   : 2009��9��9��
      ��    ��   :
      �޸�����   : �����ļ�
******************************************************************************/

#ifndef __API_H__
#define __API_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CARD_COUNT   5       //��������
#define MIN_AUTONO   10      //��С���ƺ�
#define MAX_AUTONO   20      //����ƺ�

typedef unsigned char UC;
typedef unsigned long UL;

//��������
typedef enum {
    CAR,     //С�γ�
    BUS,     //���
    AUTO_TYPE_BUTT,
} ParkSysAutoType;

//��״̬
typedef enum {
    CARD_IDLE  = 0,  //������
    CARD_INUSE = 1,  //���Ѿ�ʹ��
} CardStatus;

//�����붨��
typedef enum {
    OP_E_CMD                    = 0,  //(������ʹ��)��Ч������
    OP_RESET_SUCC               = 1,  //ϵͳ��ʼ���ɹ�
    OP_E_PARAMETER              = 2,  //�������Ϸ�
    OP_E_PARKING_FULL           = 3,  //��λ����
    OP_E_EXISTED_ATUO           = 4,  //�ó��Ѿ���ͣ����
    OP_E_MISMATCH_AUTO_TYPE     = 5,  //���������Ƴ����������
    OP_E_NOT_IN_PARKING         = 6,  //�ó�����ͣ����
    OP_E_AUTONO_MISMATCH_CARDNO = 7,  //���ƺźͿ��Ų���Ӧ�������뿪
    OP_E_TIME_LOGIC             = 8,  //ʱ���߼�����
    OP_PARKING_SUCC             = 9,  //ͣ�������ɹ�
    OP_SPEC_CAR_PARKING         = 10, //ָ���ĳ�����ͣ��������δͣ��
    OP_ANY_CAR_PAKING           = 11, //ͣ��������δ���κγ���ͣ��
    OP_INTERNAL_ERR             =999, //�ڲ�ϵͳ����
} ParkSysOpRet;

//ʱ��
typedef struct {
    UC hh;  //Сʱ
    UC mm;  //����
} ParkSysTime;

//��ͣ�����еĳ�����Ϣ
typedef struct {
    UL              AutoNo;       //���ƺ�
    ParkSysTime     CurGetInTime; //��ǰ����ʱ��
    UL              CardNo;       //����
    ParkSysAutoType AutoType;     //����
    UC              ParkingCount; //ͣ������
} ParkingAutoInfo;

//ͣ�����г�����ʷͣ����Ϣ
typedef struct {
    UL              AutoNo;       //���ƺ�
    ParkSysAutoType AutoType;     //��������
    UL              CardNo;       //����
    ParkSysTime     GetInTime;    //ͣ��ʱ��
    ParkSysTime     GetOutTime;   //ȡ��ʱ��
    UL              Fee;          //ͣ������
} ParkingAutoHistoryInfo;

/*****************************************************************************
  �� �� ��  : api_parksys_ret
  ��������  : ϵͳ�ṩ�ĺ���,����������,��ӡ���������Ϣ
  �������  : ParkSysOpRet OpRet�����붨��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_ret(ParkSysOpRet OpRet);

/*****************************************************************************
  �� �� ��  : api_parksys_fee
  ��������  : ϵͳ�ṩ�ĺ���,����������,�����뿪ͣ��������ȡ�ķ���
  �������  : UL fee����ͣ����ȡ�ķ���
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_fee(UL fee);

/*****************************************************************************
  �� �� ��  : api_parksys_idle_parkingspace_number
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ�������г�λ��ѯ���
  �������  : UL number���г�λ��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_idle_parkingspace_number(UL number);

/*****************************************************************************
  �� �� ��  : api_parksys_card_status
  ��������  : ϵͳ�ṩ�ĺ���,����������,ָ����״̬��ѯ���
  �������  : CardStatus cardStatusָ����״̬
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_card_status(CardStatus cardStatus);

/*****************************************************************************
  �� �� ��  : api_parksys_parking_auto
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ������ָ��������Ϣ��ѯ���
  �������  : ParkingAutoInfo *pAutoInfoͣ������ָ��������Ϣ
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_parking_auto(ParkingAutoInfo *pAutoInfo);

/*****************************************************************************
  �� �� ��  : api_parksys_parking_auto_history_info
  ��������  : ϵͳ�ṩ�ĺ���,����������,ͣ������ָ��������Ϣ��ѯ���
  �������  : ParkingAutoHistoryInfo *pAutoHistoryInfoͣ��������ʷ����ͣ����Ϣ
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :
  �޸���ʷ  :
   1.��    ��   : 2009��9��9��
     ��    ��   :
     �޸�����   : �����ɺ���
*****************************************************************************/
void api_parksys_parking_auto_history_info(ParkingAutoHistoryInfo *pAutoHistoryInfo);


/*****************************************************************************
 �� �� ��  : api_server_start
 ��������  : ����socket����ˣ��������ķ�ʽ�����û�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2009��9��9��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
void apiServerStart(int argc, char* argv[]);


// ������ʵ�ֵĺ���

void OpReset(void);

void OpGetin(UL AutoNo, ParkSysAutoType AutoType, ParkSysTime InTime);

void OpGetout(UL AutoNo, UL CardNo, ParkSysTime OutTime);

void OpListIdleParkingSpaceNumber(void);

void OpListCardStatus(UL CardNo);

void OpListParkingAuto(UL AutoNo);

void OpListParkingAutoHistoryInfo(UL AutoNo);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __API_H__ */
