#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "api.h"
#include "Loan.h"

AllInfo *allInfo = NULL;
BankInfo *bankInfo = NULL;

AllInfo *allInfoCopy = NULL;

int systemTime = 0; //ϵͳʱ��
int checkQueueTime = 0; //��˴������ʱ��
int releaseQueueTime = 0; //���Ŵ������ʱ��
int loanNo = 0; //����˳����ˮ�ţ���������ʱ�������ˮ��
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
    memset(bankInfo, 0, sizeof(BankInfo));

    /*��allInfo���г�ʼ������*/
    if(allInfo != NULL)
    {
        free(allInfo); //�ͷ�֮ǰ����Ŀռ�
    }
    allInfo = (AllInfo*)malloc(sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1)); //0�ſռ䱣��
    if(allInfo == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }
    memset(allInfo, 0, sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    /*��allInfoCopy���г�ʼ������*/
    if(allInfoCopy != NULL)
    {
        free(allInfoCopy); //�ͷ�֮ǰ����Ŀռ�
    }
    allInfoCopy = (AllInfo*)malloc(sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1)); //0�ſռ䱣��
    if(allInfoCopy == NULL)
    {
        return; //û�ж�Ӧ�����룬�������������Ϣ
    }
    memset(allInfoCopy, 0, sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    bankInfo->grantMoney = 0;
    bankInfo->grantNum = 0;

    api_loansys_ret(OP_E_INIT_SUCCESS); //��ʼ���ɹ�

    return;
}

/*****************************************************************************
 �� �� ��  : ReqeustLoan
 ��������  : ��������ʵ�֣�ʵ�ִ�����������
 �������  : loanIdx:������
             salary:������������
             principal:�����ܶ�(��Ԫ)
			 reqTime:����ʱ��
*****************************************************************************/
void ReqeustLoan(int loanIdx, float salary, int principal, int years, int reqTime)
{
    int ret = Request(loanIdx,salary,principal,years,reqTime);
    if(ret == 0)
    {
        Check(loanIdx,salary,principal,years,reqTime,0);
        Release(loanIdx,salary,principal,years,reqTime,0);
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
    /*������������*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return;
    }

    /*�����·������飬�˴�ֻ����һ���Լ�飬�����ִ����˵Ĵ������޵�����*/
    if((month < MIN_REPAY_DATE) || (month > MAX_REPAY_DATE))
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
    memcpy(allInfoCopy,allInfo,sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    /*����ʱ�䣬ע��˴���Ҫ����ϵͳʱ��*/
    checkQueueTime = lstTime - systemTime;
    releaseQueueTime = lstTime - systemTime;

    int flag = 0; //��־�Ƿ��ҵ���Ӧ��¼

    for(int i=1; i<=count; i++)
    {
        if(allInfoCopy[i].loanIndex == loanIdx)
        {
            flag = 1;

            Check(loanIdx,allInfoCopy[i].salary,allInfoCopy[i].principal,
                  allInfoCopy[i].monthAll/MONTH_EVERY_YEAR,lstTime,1);
            Release(loanIdx,allInfoCopy[i].salary,allInfoCopy[i].principal,
                    allInfoCopy[i].monthAll/MONTH_EVERY_YEAR,lstTime,1);

            LoanInfo *loanInfo = (LoanInfo*)malloc(sizeof(LoanInfo));

            loanInfo->monthAll = allInfoCopy[i].monthAll;
            loanInfo->principal = allInfoCopy[i].principal;
            loanInfo->reason = allInfoCopy[i].reason;
            loanInfo->status = allInfoCopy[i].status;
            loanInfo->monthCur = month;
            loanInfo->loanIdx = loanIdx;

            if(loanInfo->status == SUCC_GRANT)
            {
                LoanRate(loanInfo, fund);
            }
            else
            {
                loanInfo->rate = 0;
                loanInfo->allMoney = 0;
                loanInfo->ownMoney = 0;
                loanInfo->monthCurMoney = 0;
            }

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

int Request(int loanIdx, float salary, int principal, int years, int reqTime)
{
    /*�����ż��*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return -1;
    }

    /*��������������*/
    if((salary < INCOME_LOW_MIN) || (salary > INCOME_HIGH_MAX))
    {
        api_loansys_ret(OP_E_SALARY);
        return -1;
    }

    /*������*/
    if((principal < AMOUNT_MIN/MONEY_UNIT_TRANSFORM) ||
            (principal > AMOUNT_HIGH_MAX/MONEY_UNIT_TRANSFORM))
    {
        api_loansys_ret(OP_E_PRINCIPAL);
        return -1;
    }

    /*�������޼��*/
    if((years < INSTALLMENTS_MIN/MONTH_EVERY_YEAR) ||
            (years > INSTALLMENTS_HIGH_MAX/MONTH_EVERY_YEAR))
    {
        api_loansys_ret(OP_E_PRINCIPAL);
        return -1;
    }

    /*����ʱ����*/
    if((reqTime < APPLY_TIME_MIN) || (reqTime > APPLY_TIME_MAX))
    {
        api_loansys_ret(OP_E_APPLY_TIME);
        return -1;
    }
    if(reqTime < systemTime)
    {
        api_loansys_ret(OP_E_APPLYTIME_SUB);
        return -1;
    }

    /*�ж�����״̬*/
    int seq = 0; //������������룬����������������
    for(int i=1; i<= count; i++)
    {
        /*���ж�Ӧ���*/
        if(allInfo[i].loanIndex == loanIdx)
        {
            if(allInfo[i].status != RE_LOAN) //������������
            {
                api_loansys_ret(OP_E_MODIFY);
                return -1;
            }
            else //����������
            {
                seq = i;
            }
            break;
        }
    }

    api_loansys_ret(OP_E_SUCCESS); //����ɹ�

    /*���¸���ʱ�����*/
    checkQueueTime = reqTime - systemTime;
    releaseQueueTime = reqTime - systemTime;
    systemTime = reqTime;

    loanNo++; //��ˮ�˺Ÿ���

    if(seq == 0) //������������
    {
        count++;
        allInfo[count].loanIndex = loanIdx;
        allInfo[count].status = WAIT_CHECK;
        allInfo[count].principal = principal;
        allInfo[count].monthAll = years * MONTH_EVERY_YEAR;
        allInfo[count].loanNo = loanNo;
        allInfo[count].reqTime = reqTime;
        allInfo[count].salary = salary;
    }
    else //��������
    {
        allInfo[seq].loanIndex = loanIdx;
        allInfo[seq].status = WAIT_CHECK;
        allInfo[seq].principal = principal;
        allInfo[seq].monthAll = years * MONTH_EVERY_YEAR;
        allInfo[seq].loanNo = loanNo;
        allInfo[seq].reqTime = reqTime;
        allInfo[seq].salary = salary;
    }

    return 0;
}


int Check(int loanIdx, float salary, int principal, int years, int reqTime, int flag)
{
    AllInfo *p1 = NULL;

    if(flag == 0) //�ǿ�����Ϣ
    {
        p1 = allInfo;
    }
    else //������Ϣ
    {
        p1 = allInfoCopy;
    }

    int time = 0; //��¼ʱ�������

    while(checkQueueTime > 0)
    {
        int minReqTime = INT_MAX;
        int minLoanNo = INT_MAX;
        int index = 0;

        /*�ҵ���������*/
        for(int i=1; i<=count; i++)
        {
            if(p1[i].status == WAIT_CHECK)
            {
                if(p1[i].reqTime < minReqTime)
                {
                    minReqTime = p1[i].reqTime;
                    minLoanNo = p1[i].loanNo;
                    index = i;
                }
                if((p1[i].reqTime == minReqTime) &&
                        (p1[i].loanNo < minLoanNo))
                {
                    minLoanNo = p1[i].loanNo;
                    index = i;
                }
            }
        }

        if(index != 0) //���ڴ�������
        {
            time++;
            checkQueueTime--;
            p1[index].checkTime = p1[index].reqTime + time;

            if((salary >= INCOME_LOW_MIN) && (salary <= INCOME_LOW_MAX)) //������
            {
                /*����������*/
                int principal_temp = principal * MONEY_UNIT_TRANSFORM; //���𣬵�λ:Ԫ
                if((principal_temp < AMOUNT_MIN) || (principal_temp > AMOUNT_LOW_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_PRINCIPAL;
                    continue;
                }

                /*��������������*/
                int months = years * MONTH_EVERY_YEAR; //�������·�
                if((months < INSTALLMENTS_MIN) || (months > INSTALLMENTS_LOW_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_YEAR;
                    continue;
                }
            }
            else if((salary >= INCOME_HIGH_MIN) && (salary <= INCOME_HIGH_MAX)) //������
            {
                /*����������*/
                int principal_temp = principal * MONEY_UNIT_TRANSFORM; //���𣬵�λ:Ԫ
                if((principal_temp < AMOUNT_MIN) || (principal_temp > AMOUNT_HIGH_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_PRINCIPAL;
                    continue;
                }

                /*��������������*/
                int months = years * MONTH_EVERY_YEAR; //�������·�
                if((months < INSTALLMENTS_MIN) || (months > INSTALLMENTS_HIGH_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_YEAR;
                    continue;
                }
            }

            /*���ͨ��*/
            p1[index].status = WAIT_GRANT;

        }
        else //�����ڴ�������
        {
            checkQueueTime = 0;
        }
    }
    return 0;
}


int Release(int loanIdx, float salary, int principal, int years, int reqTime, int flag)
{
    AllInfo *p1 = NULL;

    if(flag == 0) //�ǿ�����Ϣ
    {
        p1 = allInfo;
    }
    else //������Ϣ
    {
        p1 = allInfoCopy;
    }

    int time = 0; //��¼ʱ�������

    while(releaseQueueTime > 0)
    {
        int minCheckTime = INT_MAX;
        int minLoanNo = INT_MAX;
        int index = 0;

        /*�ҵ������Ŵ���*/
        for(int i=1; i<=count; i++)
        {
            if(p1[i].status == WAIT_GRANT)
            {
                if(p1[i].checkTime < minCheckTime)
                {
                    minCheckTime = p1[i].checkTime;
                    minLoanNo = p1[i].loanNo;
                    index = i;
                }
                if((p1[i].checkTime == minCheckTime) &&
                        (p1[i].loanNo < minLoanNo))
                {
                    minLoanNo = p1[i].loanNo;
                    index = i;
                }
            }
        }

        if(index != 0) //���ڴ����Ŵ���
        {
            time++;
            releaseQueueTime--;
            p1[index].grantTime = p1[index].checkTime + time;

            if(bankInfo->grantNum >= BANK_LOAN_COUNT_LIMIT) //�ɹ����Ŵ����������
            {
                p1[index].reason = SYS_DISABLE;
                p1[index].status = RE_LOAN;
                continue;
            }
            if(bankInfo->grantMoney + p1[index].principal > BANK_LOAN_AMOUNT_LIMIT/MONEY_UNIT_TRANSFORM) //�ɹ����Ŵ������
            {
                p1[index].reason = BANK_NOMOMEY;
                p1[index].status = RE_LOAN;
                continue;
            }

            p1[index].status = SUCC_GRANT;
            
            bankInfo->grantMoney += p1[index].principal;
            bankInfo->grantNum++;
            

        }
        else //�����ڴ����Ŵ���
        {
            releaseQueueTime = 0;
        }
    }
    return 0;

}

