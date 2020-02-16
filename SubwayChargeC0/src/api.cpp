#include "cstdlib"
#include "api.h"

extern void apiServerStart(int argc, char* argv[])
{

}


void apiPrintOpStatusInfo(OpStatus_EN enStatus, int nCardNo, int nRemain)
{

}


void apiPrintErrInfo(ErrCode_EN enErrCode)
{

}


void apiPrintLog(LogItem_ST* pstOutLogAddr, int nOutLogNum)
{

}


void apiPrintHistoryChargeList(HistoryItem* pstOutHistoryChargeList)
{

}


int apiGetDistanceBetweenTwoStation(char* sStartStation, char* sObjectStation, int* pnDistance)
{
    return 0;
}


void apiWriteLog(int nMoney, TravelInfo_ST* pstTravelInfo, RetCode_EN enOpFlg)
{

}


void apiDeleteLog(int iCardNo)
{

}


LogItem_ST* apiGetLogAddr(void)
{
    return NULL;
}


int apiGetLogNum(void)
{
    return 0;
}


int apiTimeDiff(int nHour1, int nMinute1, int nHour2, int nMinute2)
{
    return 0;
}
