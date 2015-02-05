#ifndef SUBWAYLIST_H
#define SUBWAYLIST_H

#include "SubwayCharge.h"
#include "api.h"

/*************************************************
Function      : CreateList
Description   : 创建链表头节点
Return        : 链表的头指针
*************************************************/
HistoryInfoNode* CreateList(void);

/*************************************************
Function      : FindNodeByCardNo
Description   : 根据卡号，查找某个节点
Input         : pHead 链表的头节点指针
                要查找的卡号
Return        : 正确:返回指定节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);


/*************************************************
Function      : PushBackNode
Description   : 向链表中尾部插入某个节点
Input         : pHead        链表的头节点指针
                pCardInfo    消费记录信息
Output        : 无
Return        : 正确:返回头节点指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo);

/*************************************************
Function      : RemoveNodeByCardNo
Description   : 从链表中删除指定卡号的记录
Input         : pHead       链表的头节点指针
                iCradNo     待删除的节点的卡号
Return        : 正确:返回链表头节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);

/*************************************************
Function      : RemoveList
Description   : 删除整个链表
Input         : pHead 链表的头节点指针
Return        : 正确:RET_OK
                失败:RET_ERROR
*************************************************/
int RemoveList(HistoryInfoNode *pHead);


#endif