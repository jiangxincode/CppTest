#include "api.h"


#ifndef __TOOLS_H__
#define __TOOLS_H__

/*��ʷͣ����Ϣ*/
typedef struct ParkingHisInfoNode {
    ParkingAutoHistoryInfo    data;
    struct ParkingHisInfoNode * pNext;
} ParkingHisInfoNode;

/*������Ϣ*/
typedef struct {
    ParkingAutoInfo info;
    bool isInSys;     //�Ƿ��ڳ�����
    bool isValidNo;     //�Ƿ�Ϊ���Ƴ�
} CarInfo_ST;

#define MAX_AUTO_COUNT 11 //�������Ŀ[10,20]
#define MIN_TIME_H 0 //ʱ����Сֵ h
#define MAX_TIME_H 23 //ʱ�����ֵ h
#define MIN_TIME_M 0 //ʱ����Сֵ m
#define MAX_TIME_M 59 //ʱ�����ֵ m


ParkingHisInfoNode* initList();
bool insertItem(ParkingHisInfoNode* hisInfo,ParkingAutoHistoryInfo dataItem);
void resetList(ParkingHisInfoNode * hisInfo);
bool deleteItemWithAutoNo(ParkingHisInfoNode * hisInfo,UL AutoNo);
void updateItem(ParkingHisInfoNode* hisInfo,UL AutoNo,ParkSysTime inTime,UL fee,ParkSysTime outTime);
int cost(ParkSysTime inTime,ParkSysTime outTime,ParkSysAutoType AutoType);


#endif
