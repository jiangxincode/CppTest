#include <stdio.h>
#include <string.h>
#include "api.h"

#define MAX_COMMAND_LENGTH 128 //每个输入字符串以空格分解的命令最大长度
#define MAX_COMMAND_NUM 4 //最大命令数目澹

/*****************************************************************************
  函 数 名  : api_parksys_ret
  功能描述  : 系统提供的函数,供考生调用,打印操作结果信息
  输入参数  : ParkSysOpRet OpRet操作码定义
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_ret(ParkSysOpRet OpRet)
{
    switch(OpRet)
    {
    case OP_E_CMD :
        puts("无效命令");
        break;
    case OP_RESET_SUCC :
        puts("系统初始化成功");
        break;
    case OP_E_PARAMETER :
        puts("参数不合法");
        break;
    case OP_E_PARKING_FULL :
        puts("车位已满");
        break;
    case OP_E_EXISTED_ATUO :
        puts("该车已经在停车场");
        break;
    case OP_E_MISMATCH_AUTO_TYPE :
        puts("可能是套牌车不允许进入");
        break;
    case OP_E_NOT_IN_PARKING :
        puts("该车不在停车场");
    case OP_E_AUTONO_MISMATCH_CARDNO :
        puts("车牌号和卡号不对应不允许离开");
        break;
    case OP_E_TIME_LOGIC :
        puts("时间逻辑错误");
        break;
    case OP_PARKING_SUCC :
        puts("停车操作成功");
        break;
    case OP_SPEC_CAR_PARKING :
        puts("指定的车辆在停车场内尚未停过");
        break;
    case OP_ANY_CAR_PAKING :
        puts("停车场内尚未有任何车辆停过");
        break;
    case OP_INTERNAL_ERR :
        puts("系统内部错误");
        break;
    default :
        puts("fetal error");
        break;
    }
}

/*****************************************************************************
  函 数 名  : api_parksys_fee
  功能描述  : 系统提供的函数,供考生调用,车辆离开停车场后收取的费用
  输入参数  : UL fee当次停车收取的费用
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_fee(UL fee)
{
    printf("费用:%u元\n",fee);
    return;
}

/*****************************************************************************
  函 数 名  : api_parksys_idle_parkingspace_number
  功能描述  : 系统提供的函数,供考生调用,停车场空闲车位查询结果
  输入参数  : UL number空闲车位数
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_idle_parkingspace_number(UL number)
{
    printf("当前空闲车位数:%d\n", number);
    return;
}

/*****************************************************************************
  函 数 名  : api_parksys_card_status
  功能描述  : 系统提供的函数,供考生调用,指定卡状态查询结果
  输入参数  : CardStatus cardStatus指定卡状态
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_card_status(CardStatus cardStatus)
{
    switch(cardStatus)
    {
    case CARD_IDLE :
        printf("卡状态:未使用\n");
        break;
    case CARD_INUSE :
        printf("卡状态:已使用\n");
        break;
    default :
        break;
    }
    return;
}

/*****************************************************************************
  函 数 名  : api_parksys_parking_auto
  功能描述  : 系统提供的函数,供考生调用,停车场中指定车辆信息查询结果
  输入参数  : ParkingAutoInfo *pAutoInfo停车场中指定车辆信息
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_parking_auto(ParkingAutoInfo *pAutoInfo)
{
    printf("车牌号:%u 卡号:%u 当前进入时间:%02u:%02u 车型:%u 停车次数:%u\n",
        pAutoInfo->AutoNo,
        pAutoInfo->CardNo,
        pAutoInfo->CurGetInTime.hh,
        pAutoInfo->CurGetInTime.mm,
        (UL)pAutoInfo->AutoType,
        pAutoInfo->ParkingCount);
    return;
}

/*****************************************************************************
  函 数 名  : api_parksys_parking_auto_history_info
  功能描述  : 系统提供的函数,供考生调用,停车场中指定车辆信息查询结果
  输入参数  : ParkingAutoHistoryInfo *pAutoHistoryInfo停车场中历史车辆停车信息
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2009年9月9日
     作    者   :
     修改内容   : 新生成函数

*****************************************************************************/
void api_parksys_parking_auto_history_info(ParkingAutoHistoryInfo *pAutoHistoryInfo)
{
	printf("车牌号:%u 车辆类型:%u 卡号:%u 停车时间:%02u:%02u 取车时间:%2u:%2u 费用:%u\n",
        pAutoHistoryInfo->AutoNo,
        (UL)pAutoHistoryInfo->AutoType,
        pAutoHistoryInfo->CardNo,
        pAutoHistoryInfo->GetInTime.hh,
        pAutoHistoryInfo->GetInTime.mm,
        pAutoHistoryInfo->GetOutTime.hh,
        pAutoHistoryInfo->GetOutTime.mm,
        pAutoHistoryInfo->Fee);
    return;
}


/*****************************************************************************
 函 数 名  : api_server_start
 功能描述  : 启动socket服务端，以阻塞的方式接受用户输入
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
void apiServerStart(int argc, char* argv[])
{
    while(1)
    {
        char command[MAX_COMMAND_NUM][MAX_COMMAND_LENGTH]; //每个输入字符串可以分解为若干个命令串
		char temp[MAX_COMMAND_LENGTH];

        int i = 0;
        int j = 0;
        
        /*初始化temp*/
        for(i=0; i<MAX_COMMAND_LENGTH; i++)
        {
            temp[i] = '\0';
        }

        /*初始化command*/
        for(i=0; i<MAX_COMMAND_NUM; i++)
        {
            for(j=0; j<MAX_COMMAND_LENGTH; j++)
            {
                command[i][j] = '\0';
            }
        }

        scanf("%s", command[0]);
		if(strncmp(command[0], "reset", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            OpReset();
			continue;
        }
		else if(strncmp(command[0], "listpn", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            OpListIdleParkingSpaceNumber();
			continue;
        }

		scanf("%s", temp);
        char *p = temp;
        i = 0;
        j = 1;

        while(*p != '\0')
        {
            while((*p != ' ') && (*p != '-') && (*p != ':') && (*p != '\0'))
            {
                command[j][i++] = *(p++);
            }
            i = 0;
            j++;
            if(*p != '\0')
            {
                p++;
            }
        }

        if(strncmp(command[0], "getin", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            ParkSysAutoType AutoType;
            ParkSysTime InTime;

            sscanf(command[1], "%u", &AutoNo);

            if(strncmp(command[2], "0", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
            {
                AutoType = CAR;
            }
            else if(strncmp(command[2], "1", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
            {
                AutoType = BUS;
            }
            else
            {
                AutoType = AUTO_TYPE_BUTT;
            }

            sscanf(command[3], "%uc", &InTime.hh);
            sscanf(command[4], "%uc", &InTime.mm);

            OpGetin(AutoNo, (ParkSysAutoType)AutoType, InTime);

        }
        else if(strncmp(command[0], "getout", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            UL CardNo;
            ParkSysTime OutTime;

            sscanf(command[1], "%u", &AutoNo);
            sscanf(command[2], "%u", &CardNo);
            sscanf(command[3], "%uc", &OutTime.hh);
            sscanf(command[4], "%uc", &OutTime.mm);

            OpGetout(AutoNo,CardNo,OutTime);
        }
        else if(strncmp(command[0], "listcs", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL CardNo;
            sscanf(command[1], "%u", &CardNo);
            OpListCardStatus(CardNo);
        }
        else if(strncmp(command[0], "listai", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            sscanf(command[1], "%u", &AutoNo);
            OpListParkingAuto(AutoNo);
        }
        else if(strncmp(command[0], "lisths", sizeof(char)*MAX_COMMAND_LENGTH) == 0)
        {
            UL AutoNo;
            sscanf(command[1], "%u", &AutoNo);
            OpListParkingAutoHistoryInfo(AutoNo);
        }
        else
        {
            puts("无效的命令");
        }
    }
}
