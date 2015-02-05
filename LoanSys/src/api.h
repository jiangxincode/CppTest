/******************************************************************************

                  版权所有 (C), 2009-2009, 华为技术有限公司

 ******************************************************************************
  文 件 名   : api.h
  版 本 号   : 初稿
******************************************************************************/

#ifndef __API_H__
#define __API_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


//操作码定义
typedef enum
{
    OP_E_CMD           = 1,            //(考生不使用)其他命令错误
    OP_E_INIT_SUCCESS  = 2,            //初始化成功
    OP_E_IDX           = 3,            //贷款编号输入错误
    OP_E_SALARY        = 4,            //贷款人月收入输入错误
    OP_E_PRINCIPAL     = 5,            //贷款本金输入错误
    OP_E_YEAR          = 6,            //贷款年限输入错误 
    OP_E_APPLY_TIME    = 7,            //申请时间输入错误
    OP_E_APPLYTIME_SUB = 8,            //申请时间错误递减
    OP_E_MODIFY        = 9,            //贷款处理正常,不允许修改初始信息
    OP_E_SUCCESS       = 10,           //贷款申请成功
    OP_E_NO_VALIDAPPLY = 11,           //无有效的贷款申请
	OP_E_MONTH         = 12,           //还款月份无效
    OP_E_FUND_MONEY    = 13,           //住房公积金还款金额无效
    OP_E_QRY_TIME      = 14,           //查询时间输入错误
    OP_E_QRYTIME_SUB   = 15,           //查询时间错误递减
    OP_E_INFO          = 16            //个人贷款申请详细信息
}LoanOpRet;


//申请状态
typedef enum
{
	RE_LOAN    = 1,  //待重新申请
	WAIT_CHECK = 2,  //待审查
    WAIT_GRANT = 3,  //待发放
	SUCC_GRANT = 4   //发放成功
}LoanStatus;


//申请未通过原因
typedef enum
{
    OVER_YEAR      = 1, //贷款年限超出范围,审查贷款失败
    OVER_PRINCIPAL = 2, //贷款本金超出范围,审查贷款失败
	BANK_NOMOMEY   = 3, //银行无可用贷款,发放贷款失败
	SYS_DISABLE    = 4  //发放贷款系统能力不足,发放贷款失败
}Reason;

/* 贷款查询信息 */
typedef struct
{
    int loanIdx;        //贷款编号
	LoanStatus status;  //状态
	Reason reason;      //失败原因	
	int principal;      //贷款本金(万元)
	int monthAll;       //还款期数
	int rate;           //实际月利率(千分之)
	int monthCur;       //第x个月份
	int monthCurMoney;  //第x个月份的还款本息总金额
	int allMoney;       //需还款本息总金额
	int ownMoney;       //需个人还款本息总金额
} LoanInfo;



/*****************************************************************************
 函 数 名  : api_loansys_ret
 功能描述  : 系统提供的函数,供考生调用,打印操作结果信息。
 输入参数  : HospitalsysOpRet OpRet操作码定义
*****************************************************************************/
void api_loansys_ret(LoanOpRet OpRet);

/*****************************************************************************
 函 数 名  : api_loansys_loaninfo
 功能描述  : 系统提供的函数,供考生调用,打印贷款查询
 输入参数  : OpRet操作码定义
             BalanceInfo患者结算信息
*****************************************************************************/
void api_loansys_loaninfo(LoanInfo loanInfo);



/*****************************************************************************
 函 数 名  : api_server_start
 功能描述  : 启动socket服务端，以阻塞的方式接受用户输入
*****************************************************************************/
void api_server_start(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __API_H__ */