#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "api.h"


/*全局变量声明*/
ParkingHisInfoNode *hisInfo = NULL; //历史信息链表
CardStatus PackingCard[CARD_COUNT]; //停车卡
CarInfo_ST carInfo[MAX_AUTO_COUNT]; //车信息，包含车牌号，以及其停车次数


ParkSysTime sysTime; //系统时间


void main(int argc, char* argv[])
{
    OpReset();
    apiServerStart(argc,argv);
}


/*****************************************************************************
 函 数 名  : OpReset
 功能描述  : 需要考生实现的接口,系统初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpReset(void)
{
    int i=0;
    for(i=0; i<CARD_COUNT; i++)
    {
        PackingCard[i] = CARD_IDLE; //将所有的停车卡标记为空闲
    }

    if(hisInfo != NULL)
    {
        resetList(hisInfo); //释放链表
    }

    hisInfo = initList(); //初始化链表
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //系统内部错误
    }

    /*初始化汽车信息*/
    for(i =0; i<MAX_AUTO_COUNT; i++)
    {
        carInfo[i].info.ParkingCount = 0; //停车次数
        carInfo[i].info.AutoNo = 0; //车牌号
        carInfo[i].info.CardNo = CARD_COUNT; //卡号
        carInfo[i].info.AutoType = AUTO_TYPE_BUTT; //汽车类型
        carInfo[i].isInSys = false; //是否在车库中
        carInfo[i].isValidNo = false; //是否是套牌车
    }
    
    sysTime.hh = 0;
    sysTime.mm = 0;
    
    api_parksys_ret(OP_RESET_SUCC);
    
}

/*****************************************************************************
 函 数 名  : OpGetin
 功能描述  : 需要考生实现的接口,车辆进入停车场
 输入参数  : UL AutoNo 车牌号
 ParkSysAutoType AutoType 车辆类型
 ParkSysTime InTime 车辆进入停车场时间
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpGetin(UL AutoNo, ParkSysAutoType AutoType, ParkSysTime InTime)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //系统内部错误
        return;
    }
    int i = 0;
    int cardIdx = 0;
    bool isIdle = false;

    /*汽车车牌号合法性判断*/
    if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*汽车类型合法性判断*/
    if((AutoType != CAR) && (AutoType != BUS))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*进入时间合法性判断(h)*/
    if((InTime.hh < MIN_TIME_H) || (InTime.hh > MAX_TIME_H))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*进入时间合法性判断(m)*/
    if((InTime.mm< MIN_TIME_M) || (InTime.mm> MAX_TIME_M))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*时间逻辑判断*/
    if(InTime.hh < sysTime.hh ||
        ( InTime.hh == sysTime.hh && InTime.mm < sysTime.mm ))
    {
        api_parksys_ret(OP_E_TIME_LOGIC);
        return;
    }

    /*判断车位是否满*/
    for(i = 0; i<CARD_COUNT; i++)
    {  
        if(PackingCard[i] == CARD_IDLE)
        {
            isIdle = true;
            cardIdx = i;
            break;
        }
    }

    /*车位已满*/
    if(!isIdle)
    {
        api_parksys_ret(OP_E_PARKING_FULL);
        return;
    }
    
    for(i = 0; i < MAX_AUTO_COUNT; i++)
    {
        /*车信息已经存在*/
        if(AutoNo == carInfo[i].info.AutoNo)
        {
            /*车已经在车位*/
            if(carInfo[i].isInSys)
            {
                api_parksys_ret(OP_E_EXISTED_ATUO);
                return;
            }
            /*该车牌之前已经判断为套牌车*/
            if(carInfo[i].isValidNo)
            {
                api_parksys_ret(OP_E_MISMATCH_AUTO_TYPE);
                return;
            }
            /*前后车类型不同，为套牌车*/
            if(carInfo[i].info.AutoType!= AutoType)
            {
                api_parksys_ret(OP_E_MISMATCH_AUTO_TYPE);
                carInfo[i].isValidNo = true;
                deleteItemWithAutoNo(hisInfo,AutoNo);
                return;
            }
            
            PackingCard[cardIdx] = CARD_INUSE;
            
            carInfo[i].isInSys = true;
            carInfo[i].info.CardNo = cardIdx;
            carInfo[i].info.CurGetInTime = InTime;
            carInfo[i].info.ParkingCount++;
            
            sysTime = InTime;
            
            api_parksys_ret(OP_PARKING_SUCC);

            ParkingAutoHistoryInfo info;
            
            info.AutoNo = carInfo[i].info.AutoNo;
            info.AutoType = carInfo[i].info.AutoType;
            info.CardNo = carInfo[i].info.CardNo;
            info.Fee = 0;
            info.GetInTime = InTime;
            info.GetOutTime.hh = 99;
            info.GetOutTime.mm = 99;
            
            insertItem(hisInfo,info);

            return;
        }
    }

    /*该车信息之前不存在*/
    for(i = 0; i < MAX_AUTO_COUNT; i++)
    {
        if(carInfo[i].info.AutoNo == 0)
        {
            PackingCard[cardIdx] = CARD_INUSE;
            
            carInfo[i].info.AutoNo = AutoNo;
            carInfo[i].isInSys = true;
            carInfo[i].isValidNo = false;
            carInfo[i].info.AutoType = AutoType;
            carInfo[i].info.CardNo = cardIdx;
            carInfo[i].info.CurGetInTime = InTime;
            carInfo[i].info.ParkingCount ++;
            
            sysTime = InTime;
            
            api_parksys_ret(OP_PARKING_SUCC);

            ParkingAutoHistoryInfo info;
            
            info.AutoNo = carInfo[i].info.AutoNo;
            info.AutoType = carInfo[i].info.AutoType;
            info.CardNo = carInfo[i].info.CardNo;
            info.Fee = 0;
            info.GetInTime = InTime;
            info.GetOutTime.hh = 99;
            info.GetOutTime.mm = 99;
            
            insertItem(hisInfo,info);

            return;
        }
    }
}


/*****************************************************************************
函 数 名  : OpGetout
功能描述  : 需要考生实现的接口,车辆离开停车场
输入参数  : UL AutoNo 车牌号
UL CardNo 卡号
ParkSysTime OutTime 车辆离开停车场时间
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年9月9日
   作    者   :
   修改内容   : 新生成函数

*****************************************************************************/
void OpGetout(UL AutoNo, UL CardNo, ParkSysTime OutTime)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR); //系统内部错误
        return;
    }

    /*车牌号合法性检查*/
    if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*卡号合法性检查*/
    if((CardNo < 0) || (CardNo >= CARD_COUNT))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*离开时间合法性检查(h)*/
    if((OutTime.hh < MIN_TIME_H) || (OutTime.hh > MAX_TIME_H))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*离开时间合法性检查(m)*/
    if((OutTime.mm < MIN_TIME_M) || (OutTime.mm > MAX_TIME_M))
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }

    /*离开时间逻辑检查*/
    if(OutTime.hh < sysTime.hh ||
        ( OutTime.hh == sysTime.hh && OutTime.mm < sysTime.mm ))
    {
        api_parksys_ret(OP_E_TIME_LOGIC);
        return;
    }
    
    int i = 0;
    int carIdx = 0;
    bool isInSys = false;

    /*检查是否存在该车信息*/
    for(i = 0; i<MAX_AUTO_COUNT; i++)
    {
        if(carInfo[i].info.AutoNo == AutoNo && carInfo[i].isInSys)
        {
            carIdx = i;
            isInSys = true;
            break;
        }
    }

    /*不在停车场*/
    if(!isInSys)
    {
        api_parksys_ret(OP_E_NOT_IN_PARKING);
        return;
    }

    /*车牌号和卡号不对应*/
    if(carInfo[carIdx].info.AutoNo != AutoNo ||
        carInfo[carIdx].info.CardNo != CardNo) {
        api_parksys_ret(OP_E_AUTONO_MISMATCH_CARDNO);
        return;
    }
    
    sysTime = OutTime;
    
    int fee = cost(carInfo[carIdx].info.CurGetInTime,OutTime,carInfo[carIdx].info.AutoType);
    api_parksys_fee(fee);
    
    carInfo[carIdx].isInSys = false;
    carInfo[carIdx].info.CardNo = 5;
    
    PackingCard[CardNo] = CARD_IDLE;

    updateItem(hisInfo,carInfo[carIdx].info.AutoNo,carInfo[carIdx].info.CurGetInTime,fee,OutTime);

    return;
}

/*****************************************************************************
 函 数 名  : OpListIdleParkingSpaceNumber
 功能描述  : 需要考生实现的接口,停车场空闲车位查询
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpListIdleParkingSpaceNumber(void)
{
    UL sum = 0;
    int i = 0;
    for(i=0; i<CARD_COUNT; i++)
    {
        if(PackingCard[i] == CARD_IDLE)
        {
            sum++;
        }
    }
    api_parksys_idle_parkingspace_number(sum);
}

/*****************************************************************************
 函 数 名  : OpListCardStatus
 功能描述  : 需要考生实现的接口,指定卡状态查询
 输入参数  : UL CardNo 卡号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpListCardStatus(UL CardNo)
{
    if(CardNo <0 || CardNo >= CARD_COUNT)
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }
    
    if(PackingCard[CardNo] == CARD_IDLE)
    {
        api_parksys_card_status(CARD_IDLE);
        return;
    }
    else
    {
        api_parksys_card_status(CARD_INUSE);
        return;
    }
}

/*****************************************************************************
 函 数 名  : OpListParkingAuto
 功能描述  : 需要考生实现的接口,停车场中指定车辆信息查询
 输入参数  : UL AutoNo 车牌号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpListParkingAuto(UL AutoNo)
{
    if((AutoNo < MIN_AUTONO) || AutoNo > MAX_AUTONO)
    {
        api_parksys_ret(OP_E_PARAMETER);
        return;
    }
    
    bool isInSys = false;
    int i = 0;
    
    for(i =0 ; i <11; i++)
    {
        if(carInfo[i].info.AutoNo == AutoNo)
        {
            if(carInfo[i].isInSys == true)
            {
                isInSys = true;
                break;
            }
        }
    }
    
    if(!isInSys)
    {
        api_parksys_ret(OP_E_NOT_IN_PARKING);
        return;
    }
    
    api_parksys_parking_auto(&carInfo[i].info);
    return;
}

/*****************************************************************************
 函 数 名  : OpListParkingAutoHistoryInfo
 功能描述  : 需要考生实现的接口,停车场中历史所有车辆停车信息查询
 输入参数  : UL AutoNo 车牌号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月9日
    作    者   :
    修改内容   : 新生成函数

 *****************************************************************************/
void OpListParkingAutoHistoryInfo(UL AutoNo)
{
    if(hisInfo == NULL)
    {
        api_parksys_ret(OP_INTERNAL_ERR);
        return;
    }
    if(AutoNo != 0)
    {
        if((AutoNo < MIN_AUTONO) || (AutoNo > MAX_AUTONO))
        {
            api_parksys_ret(OP_E_PARAMETER);
            return;
        }
    }
    
    bool flag = false;
    ParkingHisInfoNode * pTemp = hisInfo->pNext;
    if(AutoNo == 0)
    {
        while(pTemp != NULL)
        {
            api_parksys_parking_auto_history_info(&pTemp->data);
            if(!flag)
            {
                flag = true;
            }
            if(pTemp->pNext == NULL)
            {
                break;
            }
            pTemp = pTemp->pNext;
        }
        if(!flag)
        {
            api_parksys_ret( OP_ANY_CAR_PAKING);
        }
        return;
    }
    while(pTemp != NULL)
    {
        if(pTemp->data.AutoNo == AutoNo)
        {
            api_parksys_parking_auto_history_info(&pTemp->data);
            if(!flag)
            {
                flag = true;
            }
        }
        if(pTemp->pNext == NULL)
        {
            break;
        }
        pTemp = pTemp->pNext;
    }
    if(!flag)
    {
        api_parksys_ret(OP_SPEC_CAR_PARKING);
    }
    return;

}

