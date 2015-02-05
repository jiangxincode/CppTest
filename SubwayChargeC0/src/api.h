/******************************************************************************

                  版权所有 (C), 2010-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : api.h
  版 本 号   : v1.0
  功能描述   : Lib库提供给考生使用的公共定义或函数声明(考生不要更改)
  函数列表   :

******************************************************************************/


#ifndef __API__
#define __API__


/*内存日志记录的最大条数*/
#define MAX_LOG_RECORD_NUM      (10)

/*站点名称的最大ASCI字符长度(不包含字符串结束符的长度)*/
#define MAX_STATION_NAME_LEN    (2)

/* 函数返回码 */
typedef enum tagRetCode
{
    RET_OK,   /* 成功 */
    RET_ERROR /* 失败 */
} RetCode_EN;

/* 操作成功返回码 */
typedef enum tagOpStatus
{
    I00,  /* I00:欢迎使用地铁收费系统 */

    I10,  /* I10:扣费失败(无效路线) */

    I11,  /* I11:扣费成功 */
    I12,  /* I12:扣费成功(余额过低) */

    I13,  /* I13:扣费失败(余额不足) */

    I22   /* I22:票卡注销成功 */
} OpStatus_EN;

/* 操作失败返回码 */
typedef enum tagErrCode
{
    E01,  /* E01:非法命令 */
    E02,  /* E02:参数错误(时间关系错误) */

    E21,  /* E21:查询失败(无相应记录)*/

    E22,  /* E22:操作失败，此票卡已经注销 */

    E99,  /* E99:系统内部错误 */
} ErrCode_EN;

/*交通卡类型 枚举*/
typedef enum tagCardType
{
    CARDTYPE_A = 0,           /*单程票*/
    CARDTYPE_B = 1,           /*老年卡*/
    CARDTYPE_C = 2,           /*普通卡*/
    CARDTYPE_BUTT             /*无效值*/
} CardType_EN;

/*"相邻站点间里程表" 记录结构*/
typedef struct tagStationDistanceItem
{
    char sStation1[MAX_STATION_NAME_LEN + 1];    /*站点1名称*/
    char sStation2[MAX_STATION_NAME_LEN + 1];    /*站点2名称*/
    int nDistance;                               /*2站之间的里程距离(单位:千米)*/
} StationDistanceItem_ST;

/*请求扣费操作命令参数 结构*/
typedef struct tagTravelInfo
{
    int nCardNo;              /*卡号*/
    CardType_EN enCardType;   /*卡类型*/
    int nCardMoney;           /*卡内当前金额*/
    int nInHour;              /*进站时间:钟点(范围: 0 ~ 23)*/
    int nInMinute;            /*进站时间:分钟(范围: 0 ~ 59)*/
    char sInStation[MAX_STATION_NAME_LEN + 1];   /*进站站点名称*/
    int nOutHour;             /*出站时间:钟点(范围: 0 ~ 23)*/
    int nOutMinute;           /*出站时间:分钟(范围: 0 ~ 59)*/
    char sOutStation[MAX_STATION_NAME_LEN + 1];  /*出站站点名称*/
} TravelInfo_ST;

/*乘车记录信息 日志记录结构*/
typedef struct tagLogItem
{
    int nCardNo;
    int nInHour;                                 /*进站时间:钟点(范围: 0 ~ 23)*/
    int nInMin;                                  /*进站时间:分钟(范围: 0 ~ 59)*/
    char sInStation[MAX_STATION_NAME_LEN + 1];   /*进站站点名称*/
    int nOutHour;                                /*出站时间:钟点(范围: 0 ~ 23)*/
    int nOutMin;                                 /*出站时间:分钟(范围: 0 ~ 59)*/
    char sOutStation[MAX_STATION_NAME_LEN + 1];  /*出站站点名称*/
    int nMoney;                                  /*扣款金额(元)*/
    RetCode_EN enOpFlg;                          /*操作成功与否标志*/
} LogItem_ST;

/*查询扣费日志操作命令参数 结构*/
typedef struct tagQueryCond
{
    int nCardNo;              /*卡号*/
    int nStartHour;           /*开始时间:钟点(范围: 0 ~ 23)*/
    int nStartMinute;         /*开始时间:分钟(范围: 0 ~ 59)*/
    int nEndHour;             /*结束时间:钟点(范围: 0 ~ 23)*/
    int nEndMinute;           /*结束时间:分钟(范围: 0 ~ 59)*/
} QueryCond_ST;

/*历史消费信息记录结构*/
typedef struct tagHistoryItem
{
    int nCardNo;
    CardType_EN enCardType;                      /*卡类型*/
    int nInHour;                                 /*进站时间:钟点(范围: 0 ~ 23)*/
    int nInMin;                                  /*进站时间:分钟(范围: 0 ~ 59)*/
    char sInStation[MAX_STATION_NAME_LEN + 1];   /*进站站点名称*/
    int nOutHour;                                /*出站时间:钟点(范围: 0 ~ 23)*/
    int nOutMin;                                 /*出站时间:分钟(范围: 0 ~ 59)*/
    char sOutStation[MAX_STATION_NAME_LEN + 1];  /*出站站点名称*/
    int nMoney;                                  /*扣款金额(元)*/
} HistoryItem;


/*历史消费记录链表结构*/
typedef struct tagHistoryInfoNode
{
    HistoryItem                  data;          /*历史消息数据*/
    struct tagHistoryInfoNode    *pNext;
}HistoryInfoNode;

/*票卡状态*/
typedef enum tagCardStatus
{
    CARD_VALID      = 0,                        /*票卡可用*/
    CARD_UNVAILD    = 1                         /*票卡已注销*/
}CardStat_EN;


/*****************************************************************************
 函 数 名  : apiServerStart
 功能描述  : 启动socket服务侦听5555端口(考试框架已自动调用)
 输入参数  : argc  程序启动时的参数个数
             argv  程序启动时的参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
extern void apiServerStart(int argc, char* argv[]);

/*****************************************************************************
 函 数 名  : apiPrintOpStatusInfo
 功能描述  : 提供给考生的API函数: 输出操作状态函数
 输入参数  : enStatus  操作状态码
             nCardNo   卡号
             nRemain   卡内余额
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintOpStatusInfo(OpStatus_EN enStatus, int nCardNo, int nRemain);

/*****************************************************************************
 函 数 名  : apiPrintErrInfo
 功能描述  : 提供给考生的API函数: 输出错误信息函数
 输入参数  : enErrCode  错误码枚举值
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintErrInfo(ErrCode_EN enErrCode);

/*****************************************************************************
 函 数 名  : apiPrintLog
 功能描述  : 提供给考生的API函数: 输出日志记录的函数
 输入参数  : pstOutLogAddr  输出日志记录数组的首地址
                            本函数只读取该指针指向空间的内容(不负责分配或释放其空间)
             nOutLogNum     从输出日志记录数组首地址开始连续输出的日志记录条数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintLog(LogItem_ST* pstOutLogAddr, int nOutLogNum);

/*****************************************************************************
 函 数 名  : apiPrintHistoryChargeList
 功能描述  : 提供给考生的API函数: 输出票卡消费历史记录
 输入参数  : pstOutHistoryChargeList  输出日志记录数组的首地址
             本函数只读取该指针指向空间的内容(不负责分配或释放其空间)
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintHistoryChargeList(HistoryItem* pstOutHistoryChargeList);

/*****************************************************************************
 函 数 名  : apiGetDistanceBetweenTwoStation
 功能描述  : 提供给考生的API函数: 从"相邻站点间里程表"中计算任意两站点之间的里程
             对于指针参数,本函数只读取该指针指向空间的内容(不负责分配或释放其空间)
 输入参数  : sStartStation   进站站点
             sObjectStation  出站站点
             pnDistance      存储进站站点与出站站点之间的里程值的地址空间
 输出参数  : *pnDistance     进站站点与出站站点之间的里程值
 返 回 值  : RET_OK    - 计算成功
             RET_ERROR - 不存在相应路线
*****************************************************************************/
int apiGetDistanceBetweenTwoStation(char* sStartStation, char* sObjectStation, int* pnDistance);

/*****************************************************************************
 函 数 名  : apiWriteLog
 功能描述  : 提供给考生的API函数: 记录内存日志的函数(最大条数MAX_LOG_RECORD_NUM,超出后丢弃不记录)
 输入参数  : nMoney         本次扣费金额
             pstTravelInfo  本次乘车记录信息
                            对于指针参数,本函数只读取该指针指向空间的内容(不负责分配或释放其空间)
             enOpFlg        扣费成功失败标志
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiWriteLog(int nMoney, TravelInfo_ST* pstTravelInfo, RetCode_EN enOpFlg);

/*****************************************************************************
 函 数 名  : apiDeleteLog
 功能描述  : 提供给考生的API函数: 删除内存日志中指定卡号的信息
 输入参数  : iCardNo    票卡卡号
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiDeleteLog(int iCardNo);

/*****************************************************************************
 函 数 名  : apiGetLogAddr
 功能描述  : 提供给考生的API函数: 获取日志记录表空间首地址(查询日志时使用)
             日志记录表空间由系统负责分配和释放,内容由apiWriteLog()写入
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 日志记录表空间首地址
*****************************************************************************/
LogItem_ST* apiGetLogAddr(void);

/*****************************************************************************
 函 数 名  : apiGetLogNum
 功能描述  : 提供给考生的API函数: 获取日志记录有效条数(查询日志时使用)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 日志记录有效条数
*****************************************************************************/
int apiGetLogNum(void);

/*****************************************************************************
 函 数 名  : apiTimeDiff
 功能描述  : 提供给考生的API函数: 计算(时间1 - 时间2)相差分钟数
             不考虑跨天的情形
 输入参数  : nHour1    时间1的小时值
             nMinute1  时间1的分钟值
             nHour2    时间2的小时值
             nMinute2  时间2的分钟值
 输出参数  : 无
 返 回 值  : (时间1 - 时间2)相差分钟数
*****************************************************************************/
int apiTimeDiff(int nHour1, int nMinute1, int nHour2, int nMinute2);


#endif /* __API__ */

