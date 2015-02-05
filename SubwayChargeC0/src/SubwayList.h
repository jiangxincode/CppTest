#ifndef SUBWAYLIST_H
#define SUBWAYLIST_H

#include "SubwayCharge.h"
#include "api.h"

/*************************************************
Function      : CreateList
Description   : ��������ͷ�ڵ�
Return        : �����ͷָ��
*************************************************/
HistoryInfoNode* CreateList(void);

/*************************************************
Function      : FindNodeByCardNo
Description   : ���ݿ��ţ�����ĳ���ڵ�
Input         : pHead �����ͷ�ڵ�ָ��
                Ҫ���ҵĿ���
Return        : ��ȷ:����ָ���ڵ��ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);


/*************************************************
Function      : PushBackNode
Description   : ��������β������ĳ���ڵ�
Input         : pHead        �����ͷ�ڵ�ָ��
                pCardInfo    ���Ѽ�¼��Ϣ
Output        : ��
Return        : ��ȷ:����ͷ�ڵ�ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo);

/*************************************************
Function      : RemoveNodeByCardNo
Description   : ��������ɾ��ָ�����ŵļ�¼
Input         : pHead       �����ͷ�ڵ�ָ��
                iCradNo     ��ɾ���Ľڵ�Ŀ���
Return        : ��ȷ:��������ͷ�ڵ��ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);

/*************************************************
Function      : RemoveList
Description   : ɾ����������
Input         : pHead �����ͷ�ڵ�ָ��
Return        : ��ȷ:RET_OK
                ʧ��:RET_ERROR
*************************************************/
int RemoveList(HistoryInfoNode *pHead);


#endif