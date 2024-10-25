#include <stdlib.h>
#include <memory.h>

#include "tools.h"


ParkingHisInfoNode* initList()
{
    ParkingHisInfoNode * head;
    head = (ParkingHisInfoNode*)malloc(sizeof(ParkingHisInfoNode));
    if(head == NULL)
    {
        return NULL; //分配内存错误
    }
    memset(head,0,sizeof(ParkingHisInfoNode));
    head->pNext = NULL;
    return head;
}

bool insertItem(ParkingHisInfoNode* hisInfo,ParkingAutoHistoryInfo dataItem)
{
    ParkingHisInfoNode *pTemp;
    ParkingHisInfoNode *pTempData;
    if(NULL == hisInfo)
    {
        return false;
    }
    pTemp = hisInfo;
    while(pTemp ->pNext != NULL && pTemp->pNext->data.AutoNo < dataItem.AutoNo)
    {
        pTemp = pTemp->pNext;
    }
    pTempData = (ParkingHisInfoNode*)malloc(sizeof(ParkingHisInfoNode));
    if(NULL == pTempData)
    {
        return false;
    }
    pTempData->data = dataItem;
    pTempData->pNext = pTemp->pNext;
    pTemp->pNext = pTempData;
    
    return true;
}

void resetList(ParkingHisInfoNode * hisInfo)
{
    ParkingHisInfoNode *pTemp;
    while(hisInfo != NULL)
    {
        pTemp = hisInfo->pNext;
        free(hisInfo);
        hisInfo = pTemp;
    }
}

bool deleteItemWithAutoNo(ParkingHisInfoNode * hisInfo,UL AutoNo)
{
    bool ret = false;
    if(NULL == hisInfo)
    {
        return false;
    }
    ParkingHisInfoNode * pTemp = NULL;
    ParkingHisInfoNode * pTempTail = NULL;
    pTemp = hisInfo;
    while(pTemp != NULL && pTemp->pNext != NULL)
    {
        if(pTemp->pNext->data.AutoNo == AutoNo)
        {
            pTempTail = pTemp->pNext->pNext;
            free(pTemp->pNext);
            pTemp->pNext = pTempTail;
            if(!ret)
            {
                ret = true;
            }
        }
        pTemp = pTemp->pNext;
    }
    return ret;

}

void updateItem(ParkingHisInfoNode* hisInfo,UL AutoNo,ParkSysTime inTime,UL fee,ParkSysTime outTime)
{
    if(hisInfo == NULL)
    {
        return;
    }
    ParkingHisInfoNode *pTemp;
    pTemp = hisInfo->pNext;
    bool flag = false;
    while(pTemp != NULL)
    {
        if(pTemp->data.AutoNo == AutoNo && pTemp->data.GetInTime.hh == inTime.hh && pTemp->data.GetInTime.mm == inTime.mm)
        {
            flag = true;
            break;
        }
        else
        {
            if(pTemp->pNext != NULL)
            {
                pTemp = pTemp->pNext;
            }
            else
            {
                break;
            }
        }
    }
    if(!flag)
    {
        return;
    }
    pTemp->data.Fee = fee;
    pTemp->data.GetOutTime = outTime;
}

/*计算停车费函数*/
int cost(ParkSysTime inTime,ParkSysTime outTime,ParkSysAutoType AutoType)
{
    int inTimeSum = inTime.hh*60+inTime.mm;
    int outTimeSum = outTime.hh*60+outTime.mm;
    int time = outTimeSum - inTimeSum;

    if(time <= 30)
        return 0;
    if(time <= 120) {
        if(AutoType == CAR)
            return 10;
        return 20;
    }
    if(time > 12*60) {
        if(CAR == AutoType)
            return 20;
        return 30;
    }
    time -= 120;
    int i = time/60;
    int j = time%60;
    if( j != 0)
        i++;
    if(CAR == AutoType)
        return 10+i;
    return 20+i;
}

