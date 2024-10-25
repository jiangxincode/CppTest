#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "api.h"
#include "Loan.h"

AllInfo *allInfo = NULL;
BankInfo *bankInfo = NULL;

AllInfo *allInfoCopy = NULL;

int systemTime = 0; //系统时间
int checkQueueTime = 0; //审核贷款队列时间
int releaseQueueTime = 0; //发放贷款队列时间
int loanNo = 0; //申请顺序流水号，重新申请时会更新流水号
int count = 0; //实际贷款笔数

void main(int argc, char* argv[])
{
    CmdReset();
    /*
    启动Socket服务侦听5555端口(sapi_server_start函数在lib库已实现)。
    lib库已实现从Socket接收到字符串后的命令分发处理；
    */
    api_server_start(argc, argv);
    // 此处不会执行到，注意不要在此处添加代码
}


/*****************************************************************************
 函 数 名  : CmdReset
 功能描述  : 考生自行实现，实现系统初始化
*****************************************************************************/
void CmdReset()
{
    systemTime = 0;
    checkQueueTime = 0;
    releaseQueueTime = 0;
    loanNo = 0;
    count  = 0;

    /*对bankInfo进行初始化处理*/
    if(bankInfo != NULL)
    {
        free(bankInfo); //释放之前分配的空间
    }
    bankInfo = (BankInfo*)malloc(sizeof(BankInfo));
    if(bankInfo == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }
    memset(bankInfo, 0, sizeof(BankInfo));

    /*对allInfo进行初始化处理*/
    if(allInfo != NULL)
    {
        free(allInfo); //释放之前分配的空间
    }
    allInfo = (AllInfo*)malloc(sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1)); //0号空间保留
    if(allInfo == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }
    memset(allInfo, 0, sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    /*对allInfoCopy进行初始化处理*/
    if(allInfoCopy != NULL)
    {
        free(allInfoCopy); //释放之前分配的空间
    }
    allInfoCopy = (AllInfo*)malloc(sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1)); //0号空间保留
    if(allInfoCopy == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }
    memset(allInfoCopy, 0, sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    bankInfo->grantMoney = 0;
    bankInfo->grantNum = 0;

    api_loansys_ret(OP_E_INIT_SUCCESS); //初始化成功

    return;
}

/*****************************************************************************
 函 数 名  : ReqeustLoan
 功能描述  : 考生自行实现，实现贷款申请命令
 输入参数  : loanIdx:贷款编号
             salary:贷款人月收入
             principal:本金总额(万元)
			 reqTime:申请时间
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
 函 数 名  : CmdLst
 功能描述  : 考生自行实现，实现贷款信息查询
 输入参数  : loanIdx:贷款编号
             month:查询的月份
             fund:公积金还款额
			 lstTime:查询时间
*****************************************************************************/
void CmdLst(int loanIdx, int month, int fund, int lstTime)
{
    /*贷款编号输入检查*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return;
    }

    /*还款月份输入检查，此处只进行一般性检查，不区分贷款人的贷款年限的区别*/
    if((month < MIN_REPAY_DATE) || (month > MAX_REPAY_DATE))
    {
        api_loansys_ret(OP_E_MONTH);
        return;
    }

    /*住房公积金检查*/
    if((fund < MIN_FUND) || (fund > MAX_FUND))
    {
        api_loansys_ret(OP_E_FUND_MONEY);
        return;
    }

    /*查询时间检查*/
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

    /*拷贝allInfo和bankInfo信息到allInfoCopy和bankInfoCopy中*/
    memcpy(allInfoCopy,allInfo,sizeof(AllInfo)*(MAX_APPLY_AMOUNT+1));

    /*更新时间，注意此处不要更新系统时间*/
    checkQueueTime = lstTime - systemTime;
    releaseQueueTime = lstTime - systemTime;

    int flag = 0; //标志是否找到相应记录

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
供考生自定义实现的函数
------------------------ */

int Request(int loanIdx, float salary, int principal, int years, int reqTime)
{
    /*贷款编号检查*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return -1;
    }

    /*贷款人月收入检查*/
    if((salary < INCOME_LOW_MIN) || (salary > INCOME_HIGH_MAX))
    {
        api_loansys_ret(OP_E_SALARY);
        return -1;
    }

    /*本金检查*/
    if((principal < AMOUNT_MIN/MONEY_UNIT_TRANSFORM) ||
            (principal > AMOUNT_HIGH_MAX/MONEY_UNIT_TRANSFORM))
    {
        api_loansys_ret(OP_E_PRINCIPAL);
        return -1;
    }

    /*贷款年限检查*/
    if((years < INSTALLMENTS_MIN/MONTH_EVERY_YEAR) ||
            (years > INSTALLMENTS_HIGH_MAX/MONTH_EVERY_YEAR))
    {
        api_loansys_ret(OP_E_PRINCIPAL);
        return -1;
    }

    /*申请时间检查*/
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

    /*判断申请状态*/
    int seq = 0; //如果有重新申请，则标记重新申请的序号
    for(int i=1; i<= count; i++)
    {
        /*已有对应编号*/
        if(allInfo[i].loanIndex == loanIdx)
        {
            if(allInfo[i].status != RE_LOAN) //不是重新申请
            {
                api_loansys_ret(OP_E_MODIFY);
                return -1;
            }
            else //是重新申请
            {
                seq = i;
            }
            break;
        }
    }

    api_loansys_ret(OP_E_SUCCESS); //申请成功

    /*更新各个时间参数*/
    checkQueueTime = reqTime - systemTime;
    releaseQueueTime = reqTime - systemTime;
    systemTime = reqTime;

    loanNo++; //流水账号更新

    if(seq == 0) //不是重新申请
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
    else //重新申请
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

    if(flag == 0) //非拷贝信息
    {
        p1 = allInfo;
    }
    else //拷贝信息
    {
        p1 = allInfoCopy;
    }

    int time = 0; //记录时间的增长

    while(checkQueueTime > 0)
    {
        int minReqTime = INT_MAX;
        int minLoanNo = INT_MAX;
        int index = 0;

        /*找到待审查贷款*/
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

        if(index != 0) //存在待审查贷款
        {
            time++;
            checkQueueTime--;
            p1[index].checkTime = p1[index].reqTime + time;

            if((salary >= INCOME_LOW_MIN) && (salary <= INCOME_LOW_MAX)) //低收入
            {
                /*本金输入检查*/
                int principal_temp = principal * MONEY_UNIT_TRANSFORM; //本金，单位:元
                if((principal_temp < AMOUNT_MIN) || (principal_temp > AMOUNT_LOW_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_PRINCIPAL;
                    continue;
                }

                /*贷款年限输入检查*/
                int months = years * MONTH_EVERY_YEAR; //贷款总月份
                if((months < INSTALLMENTS_MIN) || (months > INSTALLMENTS_LOW_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_YEAR;
                    continue;
                }
            }
            else if((salary >= INCOME_HIGH_MIN) && (salary <= INCOME_HIGH_MAX)) //高收入
            {
                /*本金输入检查*/
                int principal_temp = principal * MONEY_UNIT_TRANSFORM; //本金，单位:元
                if((principal_temp < AMOUNT_MIN) || (principal_temp > AMOUNT_HIGH_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_PRINCIPAL;
                    continue;
                }

                /*贷款年限输入检查*/
                int months = years * MONTH_EVERY_YEAR; //贷款总月份
                if((months < INSTALLMENTS_MIN) || (months > INSTALLMENTS_HIGH_MAX))
                {
                    p1[index].status = RE_LOAN;
                    p1[index].reason = OVER_YEAR;
                    continue;
                }
            }

            /*审核通过*/
            p1[index].status = WAIT_GRANT;

        }
        else //不存在代审查贷款
        {
            checkQueueTime = 0;
        }
    }
    return 0;
}


int Release(int loanIdx, float salary, int principal, int years, int reqTime, int flag)
{
    AllInfo *p1 = NULL;

    if(flag == 0) //非拷贝信息
    {
        p1 = allInfo;
    }
    else //拷贝信息
    {
        p1 = allInfoCopy;
    }

    int time = 0; //记录时间的增长

    while(releaseQueueTime > 0)
    {
        int minCheckTime = INT_MAX;
        int minLoanNo = INT_MAX;
        int index = 0;

        /*找到待发放贷款*/
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

        if(index != 0) //存在待发放贷款
        {
            time++;
            releaseQueueTime--;
            p1[index].grantTime = p1[index].checkTime + time;

            if(bankInfo->grantNum >= BANK_LOAN_COUNT_LIMIT) //成功发放贷款笔数超额
            {
                p1[index].reason = SYS_DISABLE;
                p1[index].status = RE_LOAN;
                continue;
            }
            if(bankInfo->grantMoney + p1[index].principal > BANK_LOAN_AMOUNT_LIMIT/MONEY_UNIT_TRANSFORM) //成功发放贷款金额超额
            {
                p1[index].reason = BANK_NOMOMEY;
                p1[index].status = RE_LOAN;
                continue;
            }

            p1[index].status = SUCC_GRANT;
            
            bankInfo->grantMoney += p1[index].principal;
            bankInfo->grantNum++;
            

        }
        else //不存在待发放贷款
        {
            releaseQueueTime = 0;
        }
    }
    return 0;

}

