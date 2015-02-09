/******************************************************************************

                  ��Ȩ���� (C), 2010-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : SubwayCharge.h
  �� �� ��   : v1.0
  ��������   : SubwayCharge.cpp ��ͷ�ļ�
  �����б�   :

******************************************************************************/

#ifndef __SUBWAYCHARGE_H__
#define __SUBWAYCHARGE_H__

#include "api.h"

/*�궨�忼��������Ҫ����*/
#define MAX_CARD_NUMBERS (10)

#define FILE_NAME ("SubwayCharge.txt")


/*�ṹ���忼��������Ҫ����*/


/*****************************************************************************
 �� �� ��  : opResetProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɳ����ʼ��,������ܸ�λ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opResetProc(void);

/*****************************************************************************
 �� �� ��  : opChargeProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             �������۷ѵĹ���(���������˵��)
 �������  : pstTravelInfo  ���γ˳���¼��Ϣ
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opChargeProc(TravelInfo_ST* pstTravelInfo);

/*****************************************************************************
 �� �� ��  : opQueryLogProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɲ�ѯ�˳���¼��־�Ĺ���(���������˵��)
 �������  : pstQueryCond  ��־��ѯ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opQueryLogProc(QueryCond_ST* pstQueryCond);

/*****************************************************************************
 �� �� ��  : opQueryHistoryChargeListProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɲ�ѯָ�����ŵ�Ʊ��������ʷ��¼����(���������˵��)
 �������  : iCardNo  ����ѯ��Ʊ������
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opQueryHistoryChargeListProc(int iCardNo);

/*****************************************************************************
 �� �� ��  : opDestroyCardProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ���ע��ָ�����ŵ�Ʊ��������ʷ��¼����(���������˵��)
 �������  : iCardNo  ��ע����Ʊ������
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opDestroyCardProc(int iCardNo);


/*�������������������ݹ�����Ҫ����*/

HistoryInfoNode* CreateList(void);
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo);
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);
int RemoveList(HistoryInfoNode *pHead);
int ComputeBasePrice(int distance);
int GetSameStationChargePrice(TravelInfo_ST* pstTravelInfo);
int ComputeChargePrice(TravelInfo_ST* pstTravelInfo);
int ChargeProcess(int nChargePrice, TravelInfo_ST* pstTravelInfo);
int AddHistoryItemOnListTail(int nChargePrice, TravelInfo_ST* pstTravelInfo );
void Swap(LogItem_ST &logItemA, LogItem_ST &logItemB);
void SortByCardID(LogItem_ST logItems[], int nItems);
int IsCheckTimeValid(QueryCond_ST* pstQueryCond, LogItem_ST *logAddr);
void PrintToFile(FILE *fp, HistoryItem hisItem);

#endif /* __SUBWAYCHARGE_H__ */

