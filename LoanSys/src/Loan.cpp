#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "api.h"
#include "Loan.h"

AllInfo *allInfo = NULL;
BankInfo *bankInfo = NULL;

AllInfo *allInfoCopy = NULL;
BankInfo *bankInfoCopy = NULL;

int systemTime = 0; //系统时间
int checkQueueTime = 0; //审核贷款队列时间
int releaseQueueTime = 0; //发放贷款队列时间
int loanNo = 0; //申请顺序流水号
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

    /*对allInfo进行初始化处理*/
    if(allInfo != NULL)
    {
        free(allInfo); //释放之前分配的空间
    }
    allInfo = (AllInfo*)malloc(sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    if(allInfo == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }

    /*对bankInfoCopy进行初始化处理*/
    if(bankInfoCopy != NULL)
    {
        free(bankInfoCopy); //释放之前分配的空间
    }
    bankInfoCopy = (BankInfo*)malloc(sizeof(BankInfo));
    if(bankInfoCopy == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }

    /*对allInfoCopy进行初始化处理*/
    if(allInfoCopy != NULL)
    {
        free(allInfoCopy); //释放之前分配的空间
    }
    allInfoCopy = (AllInfo*)malloc(sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    if(allInfoCopy == NULL)
    {
        return; //没有对应返回码，不再输出错误信息
    }

    bankInfo->grantMoney = 0;
    bankInfo->grantNum = 0;

    api_loansys_ret(OP_E_INIT_SUCCESS);
    
    return;
}

/*****************************************************************************
 函 数 名  : ReqeustLoan
 功能描述  : 考生自行实现，实现贷款申请命令
 输入参数  : loanIdx:贷款编号
             salary:贷款人月收入
             principal:本金总额
			 reqTime:申请时间
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
 函 数 名  : CmdLst
 功能描述  : 考生自行实现，实现贷款信息查询
 输入参数  : loanIdx:贷款编号
             month:查询的月份
             fund:公积金还款额
			 lstTime:查询时间
*****************************************************************************/
void CmdLst(int loanIdx, int month, int fund, int lstTime)
{
    CalcAfterQuery(loanIdx,month,fund,lstTime);

    /*贷款编号输入检查*/
    if((loanIdx < LOANID_MIN) || (loanIdx > LOANID_MAX))
    {
        api_loansys_ret(OP_E_IDX);
        return;
    }

    /*还款月份输入检查，此处只进行一般性检查，不区分贷款人的贷款年限的区别*/
    if((month < INSTALLMENTS_MIN) || (month > INSTALLMENTS_HIGH_MAX))
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
    memcpy(allInfoCopy,allInfo,sizeof(AllInfo)*MAX_APPLY_AMOUNT);
    memcpy(bankInfo,bankInfoCopy,sizeof(BankInfo));

    int flag = 0; //标志是否找到相应记录

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
供考生自定义实现的函数
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

