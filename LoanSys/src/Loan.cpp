#include <stdio.h>
#include <string.h>
#include "api.h"
#include "Loan.h"

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

/* -----------------------
供考生自定义实现的函数
------------------------ */

/*****************************************************************************
 函 数 名  : CmdReset
 功能描述  : 考生自行实现，实现系统初始化
*****************************************************************************/
void CmdReset()
{
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
    return;
}
