#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "SubwayList.h"
#include "malloc.h"
#include <stdarg.h>

/*************************************************
Function      : CreateList
Description   : ��������ͷ�ڵ�
Return        : �����ͷָ��
*************************************************/
HistoryInfoNode* CreateList(void)
{
    HistoryInfoNode *pHead = NULL;

    pHead = (HistoryInfoNode *)malloc(sizeof(HistoryInfoNode));
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }

    pHead->data.nCardNo = 0; //����ͷ���
    pHead->pNext = NULL;

    return pHead;
}

/*************************************************
Function      : FindNodeByCardNo
Description   : ���ݿ��ţ�����ĳ���ڵ�
Input         : pHead �����ͷ�ڵ�ָ��
                Ҫ���ҵĿ���
Return        : ��ȷ:����ָ���ڵ��ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //�����������ͷ��㣬�������������pHead������ΪNULL����ʹ��û���������в����¼
    //�ú���ֻ�������������(1-9)�����ڿ���Ϊ0��ͨ�������Ҫ���ú����Լ�����
    if((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }

    HistoryInfoNode *pNode = NULL;
    pNode = pHead->pNext;
    while (pNode != NULL)
    {
        if (pNode->data.nCardNo == iCardNo)
        {
            break;
        }
        pNode = pNode->pNext;
    }

    return pNode; //ע��˴�û�����⣬��Ȼд��return &(*pNode)Ҳ�ǶԵ�
}

/*************************************************
Function      : PushBackNode
Description   : ��������β������ĳ���ڵ�
Input         : pHead        �����ͷ�ڵ�ָ��
                pCardInfo    ���Ѽ�¼��Ϣ
Output        : ��
Return        : ��ȷ:����ͷ�ڵ�ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo)
{
    //�����������ͷ��㣬�������������pHead������ΪNULL����ʹ��û���������в����¼
    //�����pCardInfo��Ҫ�ɵ��ú�����֤�߼���ȷ�ԣ��˺���ֻ���Ƿ�ΪNULL�����ж�
    if ((pHead == NULL) || (pCardInfo == NULL))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }
    
    HistoryInfoNode* pNode = NULL;
    pNode = pHead;
    while (pNode->pNext != NULL)
    {
        pNode = pNode->pNext;
    }
    
    HistoryInfoNode* pNewNode   = NULL;
    pNewNode = (HistoryInfoNode *)malloc(sizeof(HistoryInfoNode));
    if (pNewNode == NULL)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }

    pNode->pNext = pNewNode;
    pNewNode->pNext = NULL;

    memcpy(&(pNewNode->data), pCardInfo, sizeof(HistoryItem));

    return pHead;
}

/*************************************************
Function      : RemoveNodeByCardNo
Description   : ��������ɾ��ָ�����ŵļ�¼
Input         : pHead       �����ͷ�ڵ�ָ��
                iCradNo     ��ɾ���Ľڵ�Ŀ���
Return        : ��ȷ:��������ͷ�ڵ��ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //�����������ͷ��㣬�������������pHead������ΪNULL����ʹ��û���������в����¼
    //�ú���ֻ�������������(1-9)�����ڿ���Ϊ0��ͨ�������Ҫ���ú����Լ�����
    if ((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }
    
    HistoryInfoNode* pNode = NULL;
    pNode = pHead;
    while (pNode->pNext != NULL)
    {
        if (pNode->pNext->data.nCardNo == iCardNo)
        {
            break;
        }
        pNode = pNode->pNext;
    }

    HistoryInfoNode* pDelNode = NULL;
    pDelNode = pNode->pNext;
    if (pDelNode == NULL)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return NULL;
    }

    pNode->pNext = pDelNode->pNext;
    free(pDelNode);

    pDelNode = NULL;

    return pHead;
}


/*************************************************
Function      : RemoveList
Description   : ɾ����������
Input         : pHead �����ͷ�ڵ�ָ��
Return        : ��ȷ:RET_OK
                ʧ��:RET_ERROR
*************************************************/
int RemoveList(HistoryInfoNode *pHead)
{
    //�����������ͷ��㣬�������������pHead������ΪNULL����ʹ��û���������в����¼
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return RET_ERROR;
    }
    
    HistoryInfoNode *pNode = NULL;
    HistoryInfoNode *pb = NULL;
    pNode = pHead;

    pb = pNode->pNext;
    if (pb == NULL)
    {
        free(pNode);
    }
    else
    {
        while (pb != NULL)
        {
            free(pNode);
            pNode = pb;
            pb = pb->pNext;
        }
        free(pNode);
    }

    pNode = NULL;

    return RET_OK;
}

