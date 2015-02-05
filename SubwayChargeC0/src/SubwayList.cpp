#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "SubwayList.h"
#include "malloc.h"
#include <stdarg.h>

/*************************************************
Function      : CreateList
Description   : 创建链表头节点
Return        : 链表的头指针
*************************************************/
HistoryInfoNode* CreateList(void)
{
    HistoryInfoNode *pHead = NULL;

    pHead = (HistoryInfoNode *)malloc(sizeof(HistoryInfoNode));
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }

    pHead->data.nCardNo = 0; //设置头结点
    pHead->pNext = NULL;

    return pHead;
}

/*************************************************
Function      : FindNodeByCardNo
Description   : 根据卡号，查找某个节点
Input         : pHead 链表的头节点指针
                要查找的卡号
Return        : 正确:返回指定节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //该函数只负责处理正常结点(1-9)，对于卡号为0的通配情况需要调用函数自己处理
    if((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
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

    return pNode; //注意此处没有问题，当然写成return &(*pNode)也是对的
}

/*************************************************
Function      : PushBackNode
Description   : 向链表中尾部插入某个节点
Input         : pHead        链表的头节点指针
                pCardInfo    消费记录信息
Output        : 无
Return        : 正确:返回头节点指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //传入的pCardInfo需要由调用函数保证逻辑正确性，此函数只对是否为NULL进行判断
    if ((pHead == NULL) || (pCardInfo == NULL))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
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
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }

    pNode->pNext = pNewNode;
    pNewNode->pNext = NULL;

    memcpy(&(pNewNode->data), pCardInfo, sizeof(HistoryItem));

    return pHead;
}

/*************************************************
Function      : RemoveNodeByCardNo
Description   : 从链表中删除指定卡号的记录
Input         : pHead       链表的头节点指针
                iCradNo     待删除的节点的卡号
Return        : 正确:返回链表头节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //该函数只负责处理正常结点(1-9)，对于卡号为0的通配情况需要调用函数自己处理
    if ((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
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
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }

    pNode->pNext = pDelNode->pNext;
    free(pDelNode);

    pDelNode = NULL;

    return pHead;
}


/*************************************************
Function      : RemoveList
Description   : 删除整个链表
Input         : pHead 链表的头节点指针
Return        : 正确:RET_OK
                失败:RET_ERROR
*************************************************/
int RemoveList(HistoryInfoNode *pHead)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
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

