#ifndef SUBWAYLIST_H
#define SUBWAYLIST_H

#include "api.h"
#include "SubwayCharge.h"

HistoryInfoNode* CreateList(void);
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo);
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCradNo);
int RemoveList(HistoryInfoNode *pHead);


#endif