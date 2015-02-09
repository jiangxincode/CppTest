#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "api.h"
#include "SubwayCharge.h"


/*其他全局变量定义考生根据需要补充*/
HistoryInfoNode *g_historyInfoNodeHead = NULL; //历史消费记录链表头结点
CardStat_EN g_CardStatusInfo[MAX_CARD_NUMBERS] = {CARD_VALID}; //将所有的票设为激活状态


/*****************************************************************************
 函 数 名  : main
 功能描述  : 主入口参数(考生无需更改)
 输入参数  : argc  程序启动时的参数个数
             argv  程序启动时的参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void main(int argc, char* argv[])
{
    /*启动Socket服务侦听5555端口(apiServerStart函数在lib库已实现)*/
    apiServerStart(argc, argv);
    return;
}

/*****************************************************************************
 函 数 名  : opResetProc
 功能描述  : 考生需要实现的接口
             完成程序初始化,或程序功能复位操作
             程序启动自动调用该函数,r/R命令时自动调用该函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void opResetProc(void)
{

	if(g_historyInfoNodeHead != NULL) //历史消费记录链表不为空，则删除历史消费记录链表
	{
		if(RemoveList(g_historyInfoNodeHead) != RET_OK)
		{
			return; //错误信息由RemoveList函数进行输出
		}
		g_historyInfoNodeHead = NULL;
	}
    
	g_historyInfoNodeHead = CreateList(); //创建历史消费记录链表
	if(g_historyInfoNodeHead == NULL)
	{
		return; //错误信息由CreateList函数进行输出
	}
	

	FILE *fp = NULL;
	fp = fopen(FILE_NAME, "w+"); //检测文件是否存在，如果不存在则创建，如果存在则清空 
	if(fp == NULL)
	{
		apiPrintErrInfo(E99); //E99:系统内部错误
		return;
	}
	fclose(fp);

    int i = 0;
    for(i = 0; i < MAX_CARD_NUMBERS; i++)
	{
        //将0~9的卡号设置为可用，之所以把0号卡设为CARD_VALID是统一操作，
        //在之后的函数中先进行卡号范围判断，再进行卡号有效性判断
        g_CardStatusInfo[i] = CARD_VALID;
	}
	
	return;
	
}

/*****************************************************************************
 函 数 名  : opChargeProc
 功能描述  : 考生需要实现的接口
             完成请求扣费的功能(详见试题规格说明)
             c/C命令时自动调用该函数
 输入参数  : pstTravelInfo  单次乘车记录信息
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void opChargeProc(TravelInfo_ST* pstTravelInfo)
{
    if(pstTravelInfo == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return;
    }
    
    int nCardNo = pstTravelInfo->nCardNo;
    
    //判断卡号范围是否正确
    if((nCardNo <= 0) || (nCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return;
    }
    
	//判断卡是否注销
	if(g_CardStatusInfo[nCardNo] == CARD_UNVAILD)
	{
		apiPrintErrInfo(E22); //操作失败，此票卡已经注销
		return;
	}
    
	//判断出站时间是否大于等于入站时间
	if(apiTimeDiff(pstTravelInfo->nInHour,pstTravelInfo->nInMinute,pstTravelInfo->nOutHour,pstTravelInfo->nOutMinute) > 0)
	{
		apiPrintErrInfo(E02); //参数错误(时间关系错误)
		apiWriteLog(0, pstTravelInfo, RET_ERROR);
		return;

	}

	//判断进出站是否有效
	int nDistance = 0;
	if(apiGetDistanceBetweenTwoStation(pstTravelInfo->sInStation ,pstTravelInfo->sOutStation, &nDistance) == RET_ERROR)
	{
		apiPrintOpStatusInfo(I10,pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //I10:扣费失败(无效路线)
		apiWriteLog(0, pstTravelInfo, RET_ERROR);
		return;
	}
    
	//计算扣费票价
	int nChargePrice = ComputeChargePrice(pstTravelInfo);
    if(nChargePrice == -1)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
    }
    
	//进行扣费，并将扣费记录写入链表尾
	ChargeProcess(nChargePrice, pstTravelInfo);
    
	return ;
}

/*****************************************************************************
 函 数 名  : opQueryLogProc
 功能描述  : 考生需要实现的接口
             完成查询乘车记录日志的功能(详见试题规格说明)
             q/Q命令时自动调用该函数
 输入参数  : pstQueryCond  日志查询条件
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void opQueryLogProc(QueryCond_ST* pstQueryCond)
{
	if(pstQueryCond == NULL)
	{
		apiPrintErrInfo(E99); //E99:系统内部错误
		return;
	}
	int nTimeDiff = apiTimeDiff(pstQueryCond->nStartHour,
        pstQueryCond->nStartMinute,
        pstQueryCond->nEndHour,
        pstQueryCond->nEndMinute);
	//查询终止时间是否大于查询开始时间
	if(nTimeDiff > 0)
	{
		apiPrintErrInfo(E02);
		return;
	}

	LogItem_ST tmpLogItem[MAX_LOG_RECORD_NUM];
	memset(tmpLogItem, 0, sizeof(LogItem_ST) * MAX_LOG_RECORD_NUM);
    
	int i = 0, j = 0;
	int nLogItemCnt = 0; //记录条目数
	
	LogItem_ST *pLogAddr = apiGetLogAddr();
	int nItems = apiGetLogNum();
	
	if(pstQueryCond->nCardNo == 0) //卡号为0
	{
		for(i = 1; i < MAX_CARD_NUMBERS; i++)
		{
			if(g_CardStatusInfo[i] == CARD_VALID)
			{
				for(j = 0; j < nItems; j++)
				{
					if((i == pLogAddr[j].nCardNo) && (IsCheckTimeValid(pstQueryCond,pLogAddr + j) == RET_OK))
					{
						memcpy(&(tmpLogItem[nLogItemCnt]),&(pLogAddr[j]),sizeof(LogItem_ST));
						nLogItemCnt++;
					}
				}
			}
		}
	}
	else //卡号不为0
	{
		if(g_CardStatusInfo[pstQueryCond->nCardNo] == CARD_UNVAILD) //卡无效
		{
			apiPrintErrInfo(E22);  
			return;
		}
		else //卡有效
		{
			for(j = 0; j < nItems; j++)
			{
				if((pstQueryCond->nCardNo == pLogAddr[j].nCardNo) && (IsCheckTimeValid(pstQueryCond,pLogAddr + j) ==RET_OK))
				   
				{
					memcpy(&(tmpLogItem[nLogItemCnt]), &(pLogAddr[j]), sizeof(LogItem_ST));
					nLogItemCnt++;
				}
			}
		}
	}

	if(nLogItemCnt <= 0)
	{
		apiPrintErrInfo(E21);
		return;
	}
	else
	{
		SortByCardID(tmpLogItem, nLogItemCnt);
		apiPrintLog(tmpLogItem, nLogItemCnt);
	}
	return;
}


/*****************************************************************************
 函 数 名  : opQueryHistoryChargeListProc
 功能描述  : 考生需要实现的接口
             完成查询指定卡号的票卡消费历史记录功能(详见试题规格说明)
             h/H命令时自动调用该函数
 输入参数  : iCardNo  待查询的票卡卡号
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void opQueryHistoryChargeListProc(int iCardNo)
{
    //HistoryItem pHistoryChargeList[MAX_LOG_RECORD_NUM];
    //memset(pHistoryChargeList, 0, MAX_LOG_RECORD_NUM*sizeof(HistoryItem));

    int count = 0;
	FILE *fp = fopen(FILE_NAME, "w+");
    if((iCardNo < 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
    } 
    else if(iCardNo == 0)
    {
        for(int i=1;i<MAX_CARD_NUMBERS;i++)
        {
            //注意此处不应该使用->pNext，因为FindNodeByCardNo中的参数是头结点，而不是第一个有效结点
            HistoryInfoNode *node = g_historyInfoNodeHead;
            
            while(node != NULL)
            {
                node= FindNodeByCardNo(node,i);
                if(node != NULL)
                {
                    count++;
                    apiPrintHistoryChargeList(&(node->data));
                    PrintToFile(fp, node->data);
                }
            }
        }
    }
    else
    {
        HistoryInfoNode *node = g_historyInfoNodeHead;
        
        while(node != NULL)
        {
            node = FindNodeByCardNo(node, iCardNo);
            if(node!= NULL)
            {
                count++;
                apiPrintHistoryChargeList(&(node->data));
                PrintToFile(fp, node->data);
            }
        }
    }
    fclose(fp);
    if(count <= 0)
    {
        apiPrintErrInfo(E21);
        return;
    }
}

/*****************************************************************************
 函 数 名  : opDestroyCardProc
 功能描述  : 考生需要实现的接口
             完成注销指定卡号的票卡消费历史记录功能(详见试题规格说明)
 输入参数  : iCardNo  待注销的票卡卡号
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void opDestroyCardProc(int iCardNo)
{
    if((iCardNo < 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return;
    }
    else if(iCardNo == 0) //注销所有票卡
    {
        if(RemoveList(g_historyInfoNodeHead) != RET_OK)
        {
            return;
        }
        for(int i=0;i<MAX_CARD_NUMBERS;i++)
        {
            if(g_CardStatusInfo[i] == CARD_VALID)
            {
                apiDeleteLog(i);
                g_CardStatusInfo[i] = CARD_UNVAILD;
            }
        }
        apiPrintOpStatusInfo(I22, 0, 0);
    }
    else //注销特定票卡
    {
        if(g_CardStatusInfo[iCardNo] == CARD_VALID) //该卡未注销
        {
            if(RemoveNodeByCardNo(g_historyInfoNodeHead,iCardNo) == NULL)
            {
                return;
            }
            apiDeleteLog(iCardNo);
            g_CardStatusInfo[iCardNo] = CARD_UNVAILD;
            apiPrintOpStatusInfo(I22, iCardNo,0);
        }
        else //该卡已注销
        {
            apiPrintErrInfo(E22);
            return;
        }
    }

    
}


/*其他函数定义考生根据功能需要补充*/


/*****************************************************************************
 函 数 名  : ComputeBasePrice
 功能描述  : 计算基本票价
 输入参数  : distance  起点站和终点站之间的距离
 输出参数  : 无
 返 回 值  : 返回由距离计算出的基本票价
*****************************************************************************/
int ComputeBasePrice(int distance)
{
    //假设distance只有在进站和出站为同一站时才为0
    //对于同一站的情况应有其它函数进行处理，本函数只是直接返回-1
    //对于错误信息的输出应由调用函数进行处理
    if(distance <= 0)
    {
        return -1;
    }
    else if((distance > 0) && (distance <= 3))
    {
        return 2;
    }
    else if((distance > 3) && (distance <= 5))
    {
        return 3;
    }
    else if((distance >5) && (distance <= 10))
    {
        return 4;
    }
    else
    {
        return 5;
    }
}

/*****************************************************************************
 函 数 名  : GetSameStationChargePrice
 功能描述  : 计算起点站和终点站重合时的票价
 输入参数  : pstTravelInfo  旅客进出站信息
 输出参数  : 无
 返 回 值  : 起点站和终点站重合时的票价，若出错则返回-1
*****************************************************************************/
int GetSameStationChargePrice(TravelInfo_ST* pstTravelInfo)
{
    //此处只检测pstTravelInfo是否为NULL
    //对于pstTravelInfo的逻辑正确性需要由调用函数进行判断
    //为NULL时的错误信息显示由调用函数进行
    if(pstTravelInfo == NULL)
	{
		return -1;
	}
    
	int nMoney = pstTravelInfo->nCardMoney; //卡金额
	CardType_EN nCardType = pstTravelInfo->enCardType;
	int nTimeDiff = apiTimeDiff(pstTravelInfo->nOutHour, pstTravelInfo->nOutMinute, pstTravelInfo->nInHour, pstTravelInfo->nInMinute);
	if(nTimeDiff <= 30)
	{
		if(nCardType == CARDTYPE_A) //单程票
		{
			return nMoney;
		}
		else //普通票或者老年票
		{
			return 0;
		}
	}
	else
	{
		if(nCardType == CARDTYPE_A)  //单程票
		{
			return (nMoney>3 ? nMoney:3);
		}
		else //普通票或者老年票
		{
			return 3;
		}
	}
}


/*****************************************************************************
 函 数 名  : GetDifferentStationChargePrice
 功能描述  : 计算起点站和终点站不重合时的票价
 输入参数  : pstTravelInfo  旅客进出站信息
 输出参数  : 无
 返 回 值  : 起点站和终点站重合时的票价，若出错则返回-1
*****************************************************************************/
int GetDifferentStationChargePrice(TravelInfo_ST* pstTravelInfo)
{
    //此处只检测pstTravelInfo是否为NULL
    //对于pstTravelInfo的逻辑正确性需要由调用函数进行判断
    //为NULL时的错误信息显示由调用函数进行
    if(pstTravelInfo == NULL)
	{
		return -1;
	}

    //计算基本票价，此处距离计算可以假设正确，因为调用函数已经进行了判断
    int nDistance = 0;
    apiGetDistanceBetweenTwoStation(pstTravelInfo->sInStation ,pstTravelInfo->sOutStation, &nDistance);
	int nBasePrice = ComputeBasePrice(nDistance);
    if(nBasePrice == -1)
    {
        return -1;
    }
    
    if(pstTravelInfo->enCardType == CARDTYPE_A) //票卡为单程票
    {
        return (pstTravelInfo->nCardMoney > nBasePrice) ? pstTravelInfo->nCardMoney : nBasePrice;  
    }
    else //票卡为非单程票
    {
        int nInHour = pstTravelInfo->nInHour;
        int nInMin = pstTravelInfo->nInMinute;
    
        int CompSeven = apiTimeDiff(nInHour, nInMin, 7, 0);  
        int CompNine = apiTimeDiff(nInHour, nInMin, 9, 0);  
        int CompSixteenThirty = apiTimeDiff(nInHour, nInMin, 16, 30);  
        int CompEighteenThirty = apiTimeDiff(nInHour, nInMin, 18, 30);
        int CompTen= apiTimeDiff(nInHour, nInMin, 10, 0);  
        int CompEleven = apiTimeDiff(nInHour, nInMin, 11, 0);  
        int CompFifteen = apiTimeDiff(nInHour, nInMin, 15, 0);                 
        int CompSixteen = apiTimeDiff(nInHour, nInMin, 16, 0); 
    
        if (((CompSeven >= 0) && (CompNine < 0)) || ((CompSixteenThirty >= 0) && (CompEighteenThirty < 0))) //特殊非优惠时段
        {
            return nBasePrice;
        }
        else if (((CompTen >= 0) && (CompEleven <0))|| ((CompFifteen >= 0) && (CompSixteen < 0))) //特殊优惠时段
        {
            return (int)(nBasePrice*0.5); //出现小数，向下取整
        }
        else //非特殊时段
        {
            if(CARDTYPE_C == pstTravelInfo->enCardType) //普通卡
            {
                return nBasePrice;  
            }
            else if(CARDTYPE_B == pstTravelInfo->enCardType) //老年卡
            {
                return (int)(nBasePrice*0.9); //出现小数，向下取整
            }
            else
            {
                return -1; //出现错误
            }
        }
    }

}


/*****************************************************************************
 函 数 名  : ComputeChargePrice
 功能描述  : 计算扣费票价
 输入参数  : baseprice  基本票价
           : pstTravelInfo  旅客进出站信息
 输出参数  : 无
 返 回 值  : 扣费票价
*****************************************************************************/
int ComputeChargePrice(TravelInfo_ST* pstTravelInfo)
{
	if(strcmp(pstTravelInfo->sInStation, pstTravelInfo->sOutStation) == 0) //同站进出
	{
		return GetSameStationChargePrice(pstTravelInfo);
	}
	else //非同站进出
	{
        return GetDifferentStationChargePrice(pstTravelInfo);
	}
}

/*****************************************************************************
 函 数 名  : ChargeProcess
 功能描述  : 对旅客进行扣费处理，打印状态信息，写入日志信息
 输入参数  : nChargePrice  旅客应付票价
           : pstTravelInfo  旅客进出站信息
 输出参数  : 无
 返 回 值  : 扣费成功: RET_OK
           : 扣费失败: RET_ERROR
*****************************************************************************/
int ChargeProcess(int nChargePrice, TravelInfo_ST* pstTravelInfo) 
{

	int nCardID = pstTravelInfo->nCardNo;
	int nLogItems = apiGetLogNum();
	
	if(nChargePrice > pstTravelInfo->nCardMoney) //判断扣费票价是否大于卡上余额
	{
		apiPrintOpStatusInfo(I13,nCardID, pstTravelInfo->nCardMoney); //输出操作状态函数,I13:扣费失败(余额不足)
		apiWriteLog(0,pstTravelInfo,RET_ERROR);
		return RET_ERROR;
	}
	
	pstTravelInfo->nCardMoney = pstTravelInfo->nCardMoney - nChargePrice;
	if(pstTravelInfo->enCardType == CARDTYPE_A) //单程票
	{
		apiPrintOpStatusInfo(I11, nCardID, pstTravelInfo->nCardMoney); //输出操作状态函数,I11:扣费成功
	}
	else //非单程票
	{
		if(pstTravelInfo->nCardMoney >= 20)
		{
			apiPrintOpStatusInfo(I11, pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //输出操作状态函数,I11:扣费成功
		}
		else
		{
			apiPrintOpStatusInfo(I12, pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //输出操作状态函数,I11:扣费成功(余额过低)
		}
	}
	
	apiWriteLog(nChargePrice, pstTravelInfo, RET_OK); //写日志
	
	if(AddHistoryItemOnListTail(nChargePrice,pstTravelInfo) == RET_OK) //将扣费记录添加到链表尾
	{
		return RET_OK;
	}
	else
	{
		return RET_ERROR;
	}
		
}

/*****************************************************************************
 函 数 名  : AddHistoryItemOnListTail
 功能描述  : 将扣费记录添加到链表尾函数
 输入参数  : nChargePrice  旅客应付票价
           : pstTravelInfo  旅客进出站信息
 输出参数  : 无
 返 回 值  : 写入成功: RET_OK
           : 写入失败: RET_ERROR
*****************************************************************************/
int AddHistoryItemOnListTail(int nChargePrice, TravelInfo_ST* pstTravelInfo )
{
	HistoryItem historyItem;
	memset(&historyItem, 0, sizeof(HistoryItem)); 

	historyItem.enCardType = pstTravelInfo->enCardType;
	historyItem.nCardNo = pstTravelInfo->nCardNo;
	historyItem.nInHour = pstTravelInfo->nInHour;
	historyItem.nInMin = pstTravelInfo->nInMinute;
	historyItem.nMoney = nChargePrice;
	historyItem.nOutHour = pstTravelInfo->nOutHour;
	historyItem.nOutMin = pstTravelInfo->nOutMinute;

	int nInStationLen = strlen(pstTravelInfo->sInStation);
	int nOutStationLen = strlen(pstTravelInfo->sOutStation);
	memcpy(historyItem.sInStation, pstTravelInfo->sInStation, nInStationLen);
	memcpy(historyItem.sOutStation, pstTravelInfo->sOutStation, nOutStationLen);

	
	if(PushBackNode(g_historyInfoNodeHead,&historyItem) == NULL)
	{
		return RET_ERROR;
	}
	else
	{
		return RET_OK;
	}

}

/*****************************************************************************
 函 数 名  : Swap
 功能描述  : 交换两个日志信息
 输入参数  : logItemA  日志信息条目A
           : logItemB  日志信息条目B
 输出参数  : 与输入参数相同
 返 回 值  : 无
*****************************************************************************/
void Swap(LogItem_ST &logItemA, LogItem_ST &logItemB)
{
	LogItem_ST tmp;
	memcpy(&tmp, &logItemA, sizeof(LogItem_ST));
	memcpy(&logItemA, &logItemB, sizeof(LogItem_ST));
	memcpy(&logItemB, &tmp, sizeof(LogItem_ST));
}

/*****************************************************************************
 函 数 名  : SortByCardID
 功能描述  : 利用冒泡排序对卡号进行排序
 输入参数  : logItems  日志信息条目数组
           : nItems  日志信息条目数量
 输出参数  : logItems  日志信息条目数组
 返 回 值  : 无
*****************************************************************************/
void SortByCardID(LogItem_ST logItems[], int nItems)
{
	if((logItems == NULL) || (nItems <= 0))
	{
		return;
	}
	int i = 0, k = nItems;
	int flag = 1;
	while(flag)
	{
		flag = 0;
		for (i = 1; i < k; i++)
		{
			if (logItems[i - 1].nCardNo > logItems[i].nCardNo)
			{
				Swap(logItems[i - 1], logItems[i]);
				flag = 1;
			}
		}
		k--;
	}
}

/*****************************************************************************
 函 数 名  : IsCheckTimeValid
 功能描述  : 工具函数，检验时间有效性，用于opQueryLogProc函数
 输入参数  : pstQueryCond  查询扣费日志操作命令参数 结构
           : logAddr  乘车记录信息 日志记录结构
 输出参数  : 无
 返 回 值  : 写入成功: RET_OK
           : 写入失败: RET_ERROR
*****************************************************************************/
int IsCheckTimeValid(QueryCond_ST* pstQueryCond, LogItem_ST *logAddr)
{
	if((pstQueryCond == NULL) || (logAddr == NULL))
	{
		apiPrintErrInfo(E99);
		return RET_ERROR;
	}
	int nQueryStartHour = pstQueryCond->nStartHour;
	int nQueryStartMin = pstQueryCond->nStartMinute;
	int nQueryEndHour = pstQueryCond->nEndHour;
	int nQueryEndMin = pstQueryCond->nEndMinute;

	int nLogStartHour = logAddr->nInHour;
	int nLogStartMin = logAddr->nInMin;
	int nLogEndHour = logAddr->nOutHour;
	int nLogEndMin = logAddr->nOutMin;

	if((apiTimeDiff(nQueryStartHour, nQueryStartMin, nLogEndHour, nLogEndMin) <= 0)
		&& (apiTimeDiff(nLogEndHour,nLogEndMin,nQueryEndHour,nQueryEndMin) <= 0))
	{
		return RET_OK;
	}
	else
	{
		return RET_ERROR;
	}

}

/*****************************************************************************
 函 数 名  : PrintToFile
 功能描述  : 工具函数，将指定的HistoryItem信息写入文件
 输入参数  : fp  待写人的文件指针
           : hisItem  乘车历史信息
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void PrintToFile(FILE *fp, HistoryItem hisItem)
{
    fprintf(fp, "卡号:%d ", hisItem.nCardNo);
    switch(hisItem.enCardType)
    {
        case CARDTYPE_A:fprintf(fp, "卡类型:单程票 ");break;
        case CARDTYPE_B:fprintf(fp, "卡类型:老年卡 ");break;
        case CARDTYPE_C:fprintf(fp, "卡类型:普通卡 ");break;
        default:break;
    }
    fprintf(fp, "进站时间:%02d:%02d 进站名称:%s 出站时间:%02d:%02d 出站名称:%s 费用:%d",
                        hisItem.nInHour,
                        hisItem.nInMin,
                        hisItem.sInStation,
                        hisItem.nOutHour,
                        hisItem.nOutMin,
                        hisItem.sOutStation,
                        hisItem.nMoney);
    fprintf(fp, "\n");
    
}

/*************************************************
Function      : CreateList
Description   : 创建链表头节点
Return        : 链表的头指针
*************************************************/
HistoryInfoNode* CreateList(void)
{
    HistoryInfoNode *pHead = NULL;

    pHead = (HistoryInfoNode *)malloc(sizeof(HistoryInfoNode));
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }

    pHead->data.nCardNo = 0; //设置头结点
    pHead->pNext = NULL;

    return pHead;
}

/*************************************************
Function      : FindNodeByCardNo
Description   : 根据卡号，查找某个节点
Input         : pHead 链表的头节点指针
                要查找的卡号
Return        : 正确:返回指定节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* FindNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //该函数只负责处理正常结点(1-9)，对于卡号为0的通配情况需要调用函数自己处理
    if((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        return NULL;
    }

    HistoryInfoNode *pNode = pHead->pNext;
    while (pNode != NULL)
    {
        if (pNode->data.nCardNo == iCardNo)
        {
            break;
        }
        pNode = pNode->pNext;
    }

    return pNode; //注意此处没有问题，当然写成return &(*pNode)也是对的
}

/*************************************************
Function      : PushBackNode
Description   : 向链表中尾部插入某个节点
Input         : pHead        链表的头节点指针
                pCardInfo    消费记录信息
Output        : 无
Return        : 正确:返回头节点指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* PushBackNode(HistoryInfoNode *pHead, HistoryItem *pCardInfo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //传入的pCardInfo需要由调用函数保证逻辑正确性，此函数只对是否为NULL进行判断
    if ((pHead == NULL) || (pCardInfo == NULL))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }
    
    HistoryInfoNode* pNode = NULL;
    pNode = pHead;
    while (pNode->pNext != NULL)
    {
        pNode = pNode->pNext;
    }
    
    HistoryInfoNode* pNewNode   = NULL;
    pNewNode = (HistoryInfoNode *)malloc(sizeof(HistoryInfoNode));
    if (pNewNode == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }

    pNode->pNext = pNewNode;
    pNewNode->pNext = NULL;

    memcpy(&(pNewNode->data), pCardInfo, sizeof(HistoryItem));

    return pHead;
}

/*************************************************
Function      : RemoveNodeByCardNo
Description   : 从链表中删除指定卡号的所有记录
Input         : pHead       链表的头节点指针
                iCradNo     待删除的节点的卡号
Return        : 正确:返回链表头节点的指针
                失败:返回空指针
*************************************************/
HistoryInfoNode* RemoveNodeByCardNo(HistoryInfoNode *pHead, int iCardNo)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    //该函数只负责处理正常结点(1-9)，对于卡号为0的通配情况需要调用函数自己处理
    if ((pHead == NULL) || (iCardNo <= 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return NULL;
    }
    
    HistoryInfoNode *pNode = pHead;
    while (pNode->pNext != NULL)
    {
        if (pNode->pNext->data.nCardNo == iCardNo)
        {
            HistoryInfoNode *pDelNode = pNode->pNext;
            pNode->pNext = pDelNode->pNext;
            free(pDelNode);
        }
        else
        {
            pNode = pNode->pNext;
        }
    }

    return pHead;
}


/*************************************************
Function      : RemoveList
Description   : 删除整个链表
Input         : pHead 链表的头节点指针
Return        : 正确:RET_OK
                失败:RET_ERROR
*************************************************/
int RemoveList(HistoryInfoNode *pHead)
{
    //由于链表存在头结点，所以正常情况下pHead不可能为NULL，即使还没有向链表中插入记录
    if (pHead == NULL)
    {
        apiPrintErrInfo(E99); //E99:系统内部错误
        return RET_ERROR;
    }
    
    HistoryInfoNode *pNode = NULL;
    HistoryInfoNode *pb = NULL;
    pNode = pHead;

    pb = pNode->pNext;
    if (pb == NULL)
    {
        free(pNode);
    }
    else
    {
        while (pb != NULL)
        {
            free(pNode);
            pNode = pb;
            pb = pb->pNext;
        }
        free(pNode);
    }

    pNode = NULL;

    return RET_OK;
}


