#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "api.h"
#include "SubwayCharge.h"
#include "SubwayList.h"


/*����ȫ�ֱ������忼��������Ҫ����*/
HistoryInfoNode *g_historyInfoNodeHead = NULL; //��ʷ���Ѽ�¼����ͷ���
CardStat_EN g_CardStatusInfo[MAX_CARD_NUMBERS] = {CARD_VALID}; //�����е�Ʊ��Ϊ����״̬


/*****************************************************************************
 �� �� ��  : main
 ��������  : ����ڲ���(�����������)
 �������  : argc  ��������ʱ�Ĳ�������
             argv  ��������ʱ�Ĳ���
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void main(int argc, char* argv[])
{
    /*����Socket��������5555�˿�(apiServerStart������lib����ʵ��)*/
    apiServerStart(argc, argv);
    return;
}

/*****************************************************************************
 �� �� ��  : opResetProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɳ����ʼ��,������ܸ�λ����
             ���������Զ����øú���,r/R����ʱ�Զ����øú���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opResetProc(void)
{

	if(g_historyInfoNodeHead != NULL) //��ʷ���Ѽ�¼����Ϊ�գ���ɾ����ʷ���Ѽ�¼����
	{
		if(RemoveList(g_historyInfoNodeHead) != RET_OK)
		{
			return; //������Ϣ��RemoveList�����������
		}
		g_historyInfoNodeHead = NULL;
	}
    
	g_historyInfoNodeHead = CreateList(); //������ʷ���Ѽ�¼����
	if(g_historyInfoNodeHead == NULL)
	{
		return; //������Ϣ��CreateList�����������
	}
	

	FILE *fp = NULL;
	fp = fopen(FILE_NAME, "w+"); //����ļ��Ƿ���ڣ�����������򴴽��������������� 
	if(fp == NULL)
	{
		apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
		return;
	}
	fclose(fp);

    int i = 0;
    for(i = 0; i < MAX_CARD_NUMBERS; i++)
	{
        //��0~9�Ŀ�������Ϊ���ã�֮���԰�0�ſ���ΪCARD_VALID��ͳһ������
        //��֮��ĺ������Ƚ��п��ŷ�Χ�жϣ��ٽ��п�����Ч���ж�
        g_CardStatusInfo[i] = CARD_VALID;
	}
	
	return;
	
}

/*****************************************************************************
 �� �� ��  : opChargeProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             �������۷ѵĹ���(���������˵��)
             c/C����ʱ�Զ����øú���
 �������  : pstTravelInfo  ���γ˳���¼��Ϣ
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opChargeProc(TravelInfo_ST* pstTravelInfo)
{
    if(pstTravelInfo == NULL)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return;
    }
    
    int nCardNo = pstTravelInfo->nCardNo;
    
    //�жϿ��ŷ�Χ�Ƿ���ȷ
    if((nCardNo <= 0) || (nCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return;
    }
    
	//�жϿ��Ƿ�ע��
	if(g_CardStatusInfo[nCardNo] == CARD_UNVAILD)
	{
		apiPrintErrInfo(E22); //����ʧ�ܣ���Ʊ���Ѿ�ע��
		return;
	}
    
	//�жϳ�վʱ���Ƿ���ڵ�����վʱ��
	if(apiTimeDiff(pstTravelInfo->nInHour,pstTravelInfo->nInMinute,pstTravelInfo->nOutHour,pstTravelInfo->nOutMinute) > 0)
	{
		apiPrintErrInfo(E02); //��������(ʱ���ϵ����)
		apiWriteLog(0, pstTravelInfo, RET_ERROR);
		return;

	}

	//�жϽ���վ�Ƿ���Ч
	int nDistance = 0;
	if(apiGetDistanceBetweenTwoStation(pstTravelInfo->sInStation ,pstTravelInfo->sOutStation, &nDistance) == RET_ERROR)
	{
		apiPrintOpStatusInfo(I10,pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //I10:�۷�ʧ��(��Ч·��)
		apiWriteLog(0, pstTravelInfo, RET_ERROR);
		return;
	}
    
	//����۷�Ʊ��
	int nChargePrice = ComputeChargePrice(pstTravelInfo);
    if(nChargePrice == -1)
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
    }
    
	//���п۷ѣ������۷Ѽ�¼д������β
	ChargeProcess(nChargePrice, pstTravelInfo);
    
	return ;
}

/*****************************************************************************
 �� �� ��  : opQueryLogProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɲ�ѯ�˳���¼��־�Ĺ���(���������˵��)
             q/Q����ʱ�Զ����øú���
 �������  : pstQueryCond  ��־��ѯ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opQueryLogProc(QueryCond_ST* pstQueryCond)
{
	if(pstQueryCond == NULL)
	{
		apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
		return;
	}
	int nTimeDiff = apiTimeDiff(pstQueryCond->nStartHour,pstQueryCond->nStartMinute,pstQueryCond->nEndHour,pstQueryCond->nEndMinute);
	//��ѯ��ֹʱ���Ƿ���ڲ�ѯ��ʼʱ��
	if(nTimeDiff > 0)
	{
		apiPrintErrInfo(E02);
		return;
	}

	LogItem_ST tmpLogItem[MAX_LOG_RECORD_NUM];
	memset(tmpLogItem, 0, sizeof(LogItem_ST) * MAX_LOG_RECORD_NUM);
	int i = 0, j = 0;
	int nLogItemCnt = 0; //��¼��Ŀ��
	LogItem_ST *pLogAddr = apiGetLogAddr();
	int nItems = apiGetLogNum();
	
	if(pstQueryCond->nCardNo == 0) //����Ϊ0
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
	else //���Ų�Ϊ0
	{
		if(g_CardStatusInfo[pstQueryCond->nCardNo] == CARD_UNVAILD) //����Ч
		{
			apiPrintErrInfo(E22);  
			return;
		}
		else //����Ч
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
 �� �� ��  : opQueryHistoryChargeListProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɲ�ѯָ�����ŵ�Ʊ��������ʷ��¼����(���������˵��)
             h/H����ʱ�Զ����øú���
 �������  : iCardNo  ����ѯ��Ʊ������
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opQueryHistoryChargeListProc(int iCardNo)
{
    //HistoryItem pHistoryChargeList[MAX_LOG_RECORD_NUM];
    //memset(pHistoryChargeList, 0, MAX_LOG_RECORD_NUM*sizeof(HistoryItem));

    int count = 0;
    if((iCardNo < 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
    }
    else if(iCardNo == 0)
    {
        for(int i=1;i<MAX_CARD_NUMBERS;i++)
        {
            //ע��˴���Ӧ��ʹ��->pNext����ΪFindNodeByCardNo�еĲ�����ͷ��㣬�����ǵ�һ����Ч���
            HistoryInfoNode *node = g_historyInfoNodeHead;
            
            while(node != NULL)
            {
                if(FindNodeByCardNo(node,i) != NULL)
                {
                    count++;
                    //ע��˴�Ӧ��ʹ��->pNext
                    apiPrintHistoryChargeList(&(node->pNext->data));
                }
                node = node->pNext;
            }
        }
    }
    else
    {
        HistoryInfoNode *node = g_historyInfoNodeHead;
        while(node != NULL)
        {
            if(FindNodeByCardNo(node,iCardNo) != NULL)
            {
                count++;
                apiPrintHistoryChargeList(&(node->pNext->data));
            }
            node = node->pNext;
        }
    }
    if(count <= 0)
    {
        apiPrintErrInfo(E21);
        return;
    }
}

/*****************************************************************************
 �� �� ��  : opDestroyCardProc
 ��������  : ������Ҫʵ�ֵĽӿ�
             ���ע��ָ�����ŵ�Ʊ��������ʷ��¼����(���������˵��)
 �������  : iCardNo  ��ע����Ʊ������
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void opDestroyCardProc(int iCardNo)
{
    if((iCardNo < 0) || (iCardNo >= MAX_CARD_NUMBERS))
    {
        apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
        return;
    }
    else if(iCardNo == 0)
    {
        if(RemoveList(g_historyInfoNodeHead) != RET_OK)
        {
            apiPrintErrInfo(E99); //E99:ϵͳ�ڲ�����
            return;
        }
        for(int i=0;i<MAX_CARD_NUMBERS;i++)
        {
            if(g_CardStatusInfo[i] == CARD_VALID)
            {
                apiDeleteLog(i);
            }
        }
    }
    else
    {
        if(g_CardStatusInfo[iCardNo] == CARD_VALID)
        {
            apiDeleteLog(iCardNo);
        }
    }
}


/*�����������忼�����ݹ�����Ҫ����*/


/*****************************************************************************
 �� �� ��  : ComputeBasePrice
 ��������  : �������Ʊ��
 �������  : distance  ���վ���յ�վ֮��ľ���
 �������  : ��
 �� �� ֵ  : �����ɾ��������Ļ���Ʊ��
*****************************************************************************/
int ComputeBasePrice(int distance)
{
    //����distanceֻ���ڽ�վ�ͳ�վΪͬһվʱ��Ϊ0
    //����ͬһվ�����Ӧ�������������д���������ֻ��ֱ�ӷ���-1
    //���ڴ�����Ϣ�����Ӧ�ɵ��ú������д���
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
 �� �� ��  : GetSameStationChargePrice
 ��������  : �������վ���յ�վ�غ�ʱ��Ʊ��
 �������  : pstTravelInfo  �ÿͽ���վ��Ϣ
 �������  : ��
 �� �� ֵ  : ���վ���յ�վ�غ�ʱ��Ʊ�ۣ��������򷵻�-1
*****************************************************************************/
int GetSameStationChargePrice(TravelInfo_ST* pstTravelInfo)
{
    //�˴�ֻ���pstTravelInfo�Ƿ�ΪNULL
    //����pstTravelInfo���߼���ȷ����Ҫ�ɵ��ú��������ж�
    //ΪNULLʱ�Ĵ�����Ϣ��ʾ�ɵ��ú�������
    if(pstTravelInfo == NULL)
	{
		return -1;
	}
    
	int nMoney = pstTravelInfo->nCardMoney; //�����
	CardType_EN nCardType = pstTravelInfo->enCardType;
	int nTimeDiff = apiTimeDiff(pstTravelInfo->nOutHour, pstTravelInfo->nOutMinute, pstTravelInfo->nInHour, pstTravelInfo->nInMinute);
	if(nTimeDiff <= 30)
	{
		if(nCardType == CARDTYPE_A) //����Ʊ
		{
			return nMoney;
		}
		else //��ͨƱ��������Ʊ
		{
			return 0;
		}
	}
	else
	{
		if(nCardType == CARDTYPE_A)  //����Ʊ
		{
			return (nMoney>3 ? nMoney:3);
		}
		else //��ͨƱ��������Ʊ
		{
			return 3;
		}
	}
}


/*****************************************************************************
 �� �� ��  : GetDifferentStationChargePrice
 ��������  : �������վ���յ�վ���غ�ʱ��Ʊ��
 �������  : pstTravelInfo  �ÿͽ���վ��Ϣ
 �������  : ��
 �� �� ֵ  : ���վ���յ�վ�غ�ʱ��Ʊ�ۣ��������򷵻�-1
*****************************************************************************/
int GetDifferentStationChargePrice(TravelInfo_ST* pstTravelInfo)
{
    //�˴�ֻ���pstTravelInfo�Ƿ�ΪNULL
    //����pstTravelInfo���߼���ȷ����Ҫ�ɵ��ú��������ж�
    //ΪNULLʱ�Ĵ�����Ϣ��ʾ�ɵ��ú�������
    if(pstTravelInfo == NULL)
	{
		return -1;
	}

    //�������Ʊ�ۣ��˴����������Լ�����ȷ����Ϊ���ú����Ѿ��������ж�
    int nDistance = 0;
    apiGetDistanceBetweenTwoStation(pstTravelInfo->sInStation ,pstTravelInfo->sOutStation, &nDistance);
	int nBasePrice = ComputeBasePrice(nDistance);
    if(nBasePrice == -1)
    {
        return -1;
    }
    
    if(pstTravelInfo->enCardType == CARDTYPE_A) //Ʊ��Ϊ����Ʊ
    {
        return (pstTravelInfo->nCardMoney > nBasePrice) ? pstTravelInfo->nCardMoney : nBasePrice;  
    }
    else //Ʊ��Ϊ�ǵ���Ʊ
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
    
        if (((CompSeven >= 0) && (CompNine < 0)) || ((CompSixteenThirty >= 0) && (CompEighteenThirty < 0))) //������Ż�ʱ��
        {
            return nBasePrice;
        }
        else if (((CompTen >= 0) && (CompEleven <0))|| ((CompFifteen >= 0) && (CompSixteen < 0))) //�����Ż�ʱ��
        {
            return (int)(nBasePrice*0.5); //����С��������ȡ��
        }
        else //������ʱ��
        {
            if(CARDTYPE_C == pstTravelInfo->enCardType) //��ͨ��
            {
                return nBasePrice;  
            }
            else if(CARDTYPE_B == pstTravelInfo->enCardType) //���꿨
            {
                return (int)(nBasePrice*0.9); //����С��������ȡ��
            }
            else
            {
                return -1; //���ִ���
            }
        }
    }

}


/*****************************************************************************
 �� �� ��  : ComputeChargePrice
 ��������  : ����۷�Ʊ��
 �������  : baseprice  ����Ʊ��
           : pstTravelInfo  �ÿͽ���վ��Ϣ
 �������  : ��
 �� �� ֵ  : �۷�Ʊ��
*****************************************************************************/
int ComputeChargePrice(TravelInfo_ST* pstTravelInfo)
{
	if(strcmp(pstTravelInfo->sInStation, pstTravelInfo->sOutStation) == 0) //ͬվ����
	{
		return GetSameStationChargePrice(pstTravelInfo);
	}
	else //��ͬվ����
	{
        return GetDifferentStationChargePrice(pstTravelInfo);
	}
}

/*****************************************************************************
 �� �� ��  : ChargeProcess
 ��������  : ���ÿͽ��п۷Ѵ�����ӡ״̬��Ϣ��д����־��Ϣ
 �������  : nChargePrice  �ÿ�Ӧ��Ʊ��
           : pstTravelInfo  �ÿͽ���վ��Ϣ
 �������  : ��
 �� �� ֵ  : �۷ѳɹ�: RET_OK
           : �۷�ʧ��: RET_ERROR
*****************************************************************************/
int ChargeProcess(int nChargePrice, TravelInfo_ST* pstTravelInfo) 
{

	int nCardID = pstTravelInfo->nCardNo;
	int nLogItems = apiGetLogNum();
	
	if(nChargePrice > pstTravelInfo->nCardMoney) //�жϿ۷�Ʊ���Ƿ���ڿ������
	{
		apiPrintOpStatusInfo(I13,nCardID, pstTravelInfo->nCardMoney); //�������״̬����,I13:�۷�ʧ��(����)
		apiWriteLog(0,pstTravelInfo,RET_ERROR);
		return RET_ERROR;
	}
	
	pstTravelInfo->nCardMoney = pstTravelInfo->nCardMoney - nChargePrice;
	if(pstTravelInfo->enCardType == CARDTYPE_A) //����Ʊ
	{
		apiPrintOpStatusInfo(I11, nCardID, pstTravelInfo->nCardMoney); //�������״̬����,I11:�۷ѳɹ�
	}
	else //�ǵ���Ʊ
	{
		if(pstTravelInfo->nCardMoney >= 20)
		{
			apiPrintOpStatusInfo(I11, pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //�������״̬����,I11:�۷ѳɹ�
		}
		else
		{
			apiPrintOpStatusInfo(I12, pstTravelInfo->nCardNo, pstTravelInfo->nCardMoney); //�������״̬����,I11:�۷ѳɹ�(������)
		}
	}
	
	apiWriteLog(nChargePrice, pstTravelInfo, RET_OK); //д��־
	
	if(AddHistoryItemOnListTail(nChargePrice,pstTravelInfo) == RET_OK) //���۷Ѽ�¼��ӵ�����β
	{
		return RET_OK;
	}
	else
	{
		return RET_ERROR;
	}
		
}

/*****************************************************************************
 �� �� ��  : AddHistoryItemOnListTail
 ��������  : ���۷Ѽ�¼��ӵ�����β����
 �������  : nChargePrice  �ÿ�Ӧ��Ʊ��
           : pstTravelInfo  �ÿͽ���վ��Ϣ
 �������  : ��
 �� �� ֵ  : д��ɹ�: RET_OK
           : д��ʧ��: RET_ERROR
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
 �� �� ��  : Swap
 ��������  : ����������־��Ϣ
 �������  : logItemA  ��־��Ϣ��ĿA
           : logItemB  ��־��Ϣ��ĿB
 �������  : �����������ͬ
 �� �� ֵ  : ��
*****************************************************************************/
void Swap(LogItem_ST &logItemA, LogItem_ST &logItemB)
{
	LogItem_ST tmp;
	memcpy(&tmp, &logItemA, sizeof(LogItem_ST));
	memcpy(&logItemA, &logItemB, sizeof(LogItem_ST));
	memcpy(&logItemB, &tmp, sizeof(LogItem_ST));
}

/*****************************************************************************
 �� �� ��  : SortByCardID
 ��������  : ����ð������Կ��Ž�������
 �������  : logItems  ��־��Ϣ��Ŀ����
           : nItems  ��־��Ϣ��Ŀ����
 �������  : logItems  ��־��Ϣ��Ŀ����
 �� �� ֵ  : ��
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
 �� �� ��  : IsCheckTimeValid
 ��������  : ���ߺ���������ʱ����Ч�ԣ�����opQueryLogProc����
 �������  : pstQueryCond  ��ѯ�۷���־����������� �ṹ
           : logAddr  �˳���¼��Ϣ ��־��¼�ṹ
 �������  : ��
 �� �� ֵ  : д��ɹ�: RET_OK
           : д��ʧ��: RET_ERROR
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




