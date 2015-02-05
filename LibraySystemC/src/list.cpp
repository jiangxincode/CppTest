#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "list.h"

/*************************************************
Function      : CreateList
Description   : 创建链表头节点(头结点中不存放数据)
Return        : 链表的头指针
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
Description   : 向链表中尾部插入某个节点
Input         : pHead    链表的头节点指针
                pInfo    违规记录信息
Output        : 无
Return        : 正确:返回头节点指针
                失败:返回空指针
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

    while(NULL != pTemp->pNext)/* 找到尾结点 */
    {
        pTemp = pTemp->pNext;
    }
    
    pTemp->pNext = pNewNode;
    pNewNode->pNext = NULL;

    return pHeadNode;
}


/*************************************************
Function      : FindNodebyindex
Description   : 在链表中找到指定违规序号的结点
Input         : pHead    链表的头节点指针
                index  违规序号
Output        : 无
Return        : 正确:返回该索引号所对应的结点
                失败:返回空指针
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
Description   : 删除整个链表
Input         : pHead 链表的头节点指针
Return        : 正确:1
                失败:0
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
    if (NULL == pb)/*如果链表是一个只包含头结点的空链表则只需删除头结点*/
    {
        free(pNode);
    }
    else/*从头结点开始逐个删除*/
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

