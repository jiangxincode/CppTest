#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "api.h"
#include "Loan.h"

AllInfo *allInfo = NULL;
BankInfo *bankInfo = NULL;

AllInfo *allInfoCopy = NULL;
BankInfo *bankInfoCopy = NULL;

int systemTime = 0; //ϵͳʱ��
int checkQueueTime = 0; //��˴������ʱ��
int releaseQueueTime = 0; //���Ŵ������ʱ��
int loanNo = 0; //����˳����ˮ��
int count = 0; //ʵ�ʴ������

void main(int argc, char* argv[])
{
    CmdReset(); 
    /* 
    ����Socket��������5555�˿�(sapi_server_start������lib����ʵ��)��
    lib����ʵ�ִ�Socket���յ��ַ����������ַ�����
    */
    api_server_start(argc, argv);
    // �˴�����ִ�е���ע�ⲻҪ�ڴ˴���Ӵ���
}


/*****************************************************************************
 �� �� ��  : CmdReset
 ��������  : ��������ʵ�֣�ʵ��ϵͳ��ʼ��
*****************************************************************************/
void CmdReset()
{
    systemTime = 0;
    checkQueueTime = 0;
    releaseQueueTime = 0;
    loanNo = 0;
    count  = 0;

    /*��bankInfo���г�ʼ������*/
    if(bankInfo != NULL)
    {
        free(bankInfo); //�ͷ�֮ǰ����Ŀռ�
    }
    bankInfo = (BankInfo*)malloc(sizeof(BankInfo));
    if(bankInfo == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }

    /*��allInfo���г�ʼ������*/
    if(allInfo != NULL)
    {
        free(allInfo); //�ͷ�֮ǰ����Ŀռ�
    }
    allInfo = (AllInfo*)malloc(sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    if(allInfo == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }

    /*��bankInfoCopy���г�ʼ������*/
    if(bankInfoCopy != NULL)
    {
        free(bankInfoCopy); //�ͷ�֮ǰ����Ŀռ�
    }
    bankInfoCopy = (BankInfo*)malloc(sizeof(BankInfo));
    if(bankInfoCopy == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }

    /*��allInfoCopy���г�ʼ������*/
    if(allInfoCopy != NULL)
    {
        free(allInfoCopy); //�ͷ�֮ǰ����Ŀռ�
    }
    allInfoCopy = (AllInfo*)malloc(sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    if(allInfoCopy == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }

    bankInfo->grantMoney = 0;
    bankInfo->grantNum = 0;

    api_loansys_ret(OP_E_INIT_SUCCESS);
    
    return;
}

/*****************************************************************************
 �� �� ��  : ReqeustLoan
 ��������  : ��������ʵ�֣�ʵ�ִ�����������
 �������  : loanIdx:������
             salary:������������
             principal:�����ܶ�
			 reqTime:����ʱ��
*****************************************************************************/
void ReqeustLoan(int loanIdx, float salary, int principal, int years, int reqTime)
{
    int ret = Request(loanIdx,salary,principal,years,reqTime);
    if(ret == 0)
    {
        Check(loanIdx,salary,principal,years,reqTime);
        Release(loanIdx,salary,principal,years,reqTime);
    }
    return;
}

/*****************************************************************************
 �� �� ��  : CmdLst
 ��������  : ��������ʵ�֣�ʵ�ִ�����Ϣ��ѯ
 �������  : loanIdx:������
             month:��ѯ���·�
             fund:�����𻹿��
			 lstTime:��ѯʱ��
*****************************************************************************/
void CmdLst(int loanIdx, int month, int fund, int lstTime)
{
    CalcAfterQuery(loanIdx,month,fund,lstTime);

    /*������������*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return;
    }

    /*�����·������飬�˴�ֻ����һ���Լ�飬�����ִ����˵Ĵ������޵�����*/
    if((month < INSTALLMENTS_MIN) || (month > INSTALLMENTS_HIGH_MAX))
    {
        api_loansys_ret(OP_E_MONTH);
        return;
    }

    /*ס����������*/
    if((fund < MIN_FUND) || (fund > MAX_FUND))
    {
        api_loansys_ret(OP_E_FUND_MONEY);
        return;
    }

    /*��ѯʱ����*/
    if((lstTime < QUERY_TIME_MIN) || (lstTime > QUERY_TIME_MAX))
    {
        api_loansys_ret(OP_E_QRY_TIME);
        return;
    }
    if(lstTime < systemTime)
    {
        api_loansys_ret(OP_E_QRYTIME_SUB);
        return;
    }

    /*����allInfo��bankInfo��Ϣ��allInfoCopy��bankInfoCopy��*/
    memcpy(allInfoCopy,allInfo,sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    memcpy(bankInfo,bankInfoCopy,sizeof(BankInfo));

    int flag = 0; //��־�Ƿ��ҵ���Ӧ��¼

    for(int i=0; i<count; i++)
    {
        if(allInfoCopy[i].loanIndex = loanIdx)
        {
            flag = 1;
            
            checkQueueTime = lstTime - systemTime;
            releaseQueueTime = lstTime - systemTime;

            Check(loanIdx,allInfoCopy[i].salary,allInfoCopy[i].principal,
                allInfoCopy[i].monthAll/MONTH_EVERY_YEAR,lstTime);
            Release(loanIdx,allInfoCopy[i].salary,allInfoCopy[i].principal,
                allInfoCopy[i].monthAll/MONTH_EVERY_YEAR,lstTime);

            LoanInfo *loanInfo = (LoanInfo*)malloc(sizeof(LoanInfo));
            
            loanInfo->monthAll = allInfoCopy[i].monthAll;
            loanInfo->principal = allInfoCopy[i].principal;
            loanInfo->reason = allInfoCopy[i].reason;
            loanInfo->status = allInfoCopy[i].status;
            loanInfo->monthCur = month;
            loanInfo->loanIdx = loanIdx;

            LoanRate(loanInfo, fund);

            api_loansys_loaninfo(*loanInfo);

            break;
        }
    }
    if(flag == 0)
    {
        api_loansys_ret(OP_E_NO_VALIDAPPLY);
    }
    return;
}






/* -----------------------
�������Զ���ʵ�ֵĺ���
------------------------ */

int CalcBeforeQuery(int principal, int years, float *actualMonthRate, int *allMoney)
{
    return 0;
}


int CalcAfterQuery(int loanIdx, int month, int fund, int lstTime)
{
    return 0;
}


int Request(int loanIdx, float salary, int principal, int years, int reqTime)
{
    return 0;
}


int Check(int loanIdx, float salary, int principal, int years, int reqTime)
{
    return 0;
}


int Release(int loanIdx, float salary, int principal, int years, int reqTime)
{
    return 0;
}

