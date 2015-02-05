#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "list.h"

/*************************************************
Function      : CreateList
Description   : ��������ͷ�ڵ�(ͷ����в��������)
Return        : �����ͷָ��
*************************************************/
QUERY_RESULTNode* CreateList(void)
{
    QUERY_RESULTNode *pHead = NULL;
    pHead = (QUERY_RESULTNode *)malloc(sizeof(QUERY_RESULTNode));
    if (NULL == pHead)
    {
        api_print_result(E999);
        return NULL;
    }
    pHead->data.Index=0;
    pHead->data.Fee=0;
    pHead->data.Score=20;
    pHead->pNext = NULL;
    return pHead;
}


/*************************************************
Function      : PushBackNode
Description   : ��������β������ĳ���ڵ�
Input         : pHead    �����ͷ�ڵ�ָ��
                pInfo    Υ���¼��Ϣ
Output        : ��
Return        : ��ȷ:����ͷ�ڵ�ָ��
                ʧ��:���ؿ�ָ��
*************************************************/
QUERY_RESULTNode* PushBackNode(QUERY_RESULTNode *pHeadNode, QueryResult *pInfo)
{
    QUERY_RESULTNode *pTemp=NULL;
    QUERY_RESULTNode *pNewNode=NULL;
    
    if((NULL == pInfo)||(NULL == pHeadNode))
    {
        api_print_result(E999);
        return NULL;
    }
    
    pNewNode = (QUERY_RESULTNode *)malloc(sizeof(QUERY_RESULTNode));
    if(NULL == pNewNode)
    {
        api_print_result(E999);
        return NULL;
    }

    memcpy(&pNewNode->data,pInfo,sizeof(QueryResult));
    pTemp = pHeadNode;

    while(NULL != pTemp->pNext)/* �ҵ�β��� */
    {
        pTemp = pTemp->pNext;
    }
    
    pTemp->pNext = pNewNode;
    pNewNode->pNext = NULL;

    return pHeadNode;
}


/*************************************************
Function      : FindNodebyindex
Description   : ���������ҵ�ָ��Υ����ŵĽ��
Input         : pHead    �����ͷ�ڵ�ָ��
                index  Υ�����
Output        : ��
Return        : ��ȷ:���ظ�����������Ӧ�Ľ��
                ʧ��:���ؿ�ָ��
*************************************************/
QUERY_RESULTNode* FindNodebyindex(QUERY_RESULTNode *pHead, int index)
{
    QUERY_RESULTNode *pNode = NULL;
    if ((NULL == pHead) || (index <= 0))
    {
        api_print_result(E999);
        return NULL;
    }
    pNode = pHead->pNext;
    while ((NULL != pNode))
    {
        if (pNode->data.Index == index)
        {
            break;
        }
        pNode = pNode->pNext;
    }
    
    return pNode;
}


/*************************************************
Function      : RemoveList
Description   : ɾ����������
Input         : pHead �����ͷ�ڵ�ָ��
Return        : ��ȷ:1
                ʧ��:0
 *************************************************/
int RemoveList(QUERY_RESULTNode *pHead)
{
    QUERY_RESULTNode *pNode = NULL;
    QUERY_RESULTNode *pb = NULL;
    if (NULL == pHead)
    {
        api_print_result(E999);
        return 1;
    }

    pNode = pHead;
    pb = pNode->pNext;
    if (NULL == pb)/*���������һ��ֻ����ͷ���Ŀ�������ֻ��ɾ��ͷ���*/
    {
        free(pNode);
    }
    else/*��ͷ��㿪ʼ���ɾ��*/
    {
        while (NULL != pb)
        {
            free(pNode);
            pNode = pb;
            pb = pb->pNext;
        }
        free(pNode);
    }
    pNode = NULL;
    return 1;
}

