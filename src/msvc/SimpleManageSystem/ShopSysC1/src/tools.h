#include "api.h"


#ifndef __TOOLS_H__
#define __TOOLS_H__

/*历史停车信息*/
typedef struct ParkingHisInfoNode {
    ParkingAutoHistoryInfo    data;
    struct ParkingHisInfoNode * pNext;
} ParkingHisInfoNode;

/*车辆信息*/
typedef struct {
    ParkingAutoInfo info;
    bool isInSys;     //是否在车库中
    bool isValidNo;     //是否为套牌车
} CarInfo_ST;

#define MAX_AUTO_COUNT 11 //最大车辆数目[10,20]
#define MIN_TIME_H 0 //时间最小值 h
#define MAX_TIME_H 23 //时间最大值 h
#define MIN_TIME_M 0 //时间最小值 m
#define MAX_TIME_M 59 //时间最大值 m


ParkingHisInfoNode* initList();
bool insertItem(ParkingHisInfoNode* hisInfo,ParkingAutoHistoryInfo dataItem);
void resetList(ParkingHisInfoNode * hisInfo);
bool deleteItemWithAutoNo(ParkingHisInfoNode * hisInfo,UL AutoNo);
void updateItem(ParkingHisInfoNode* hisInfo,UL AutoNo,ParkSysTime inTime,UL fee,ParkSysTime outTime);
int cost(ParkSysTime inTime,ParkSysTime outTime,ParkSysAutoType AutoType);


#endif
