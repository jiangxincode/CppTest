#include "api.h"

/*****************************************************************************
 函 数 名  : LoanRate
 功能描述  : 计算利率和还款金额示例
 输入参数  : QueryLoadInfo贷款信息中的monthAll  : 总还款期数
             						  principal	: 本金总额(万元)
             						  monthCur	: 第x个月
             fund		: 公积金还款额(万元)

 输出参数  : QueryLoadInfo贷款信息中的rate			: 实际月利率(千分之)
     								  monthCurMoney : 第x个月份的还款本息总金额(元)
    								  allMoney      : 需还款本息总金额(元)
    								  ownMoney		: 需个人还款本息总金额(元)
*****************************************************************************/
void LoanRate(LoanInfo *QueryLoadInfo, int fund)
{
	int YearRate = 0;		/* 年利率(千分之) */
	int Year = 0;			/* 贷款年限 */
	int MonthPrincipal = 0;	/* 分摊到每个月的本金(元) */
	int MonthInterest = 0;	/* 当月利息(元) */
	int AllInterest = 0;	/* 总利息(元) */

	/* ---------- 1.根据各折扣机制计算出月利率 ----------*/
	Year = QueryLoadInfo->monthAll / 12;

	/* 贷款年限[1,10],初始年利率:2.4%，贷款年限(10,20],初始年利率:4.8% */
	YearRate = (1 <= Year && 10 >= Year) ? 24 : 48;	/* 单位为千分之因此值为24、48 */

	/* 贷款本金 [10,40],年利率折扣:100%，贷款本金(40,100],年利率折扣:50% */
    YearRate = ((10 <= QueryLoadInfo->principal) && ( 40 >= QueryLoadInfo->principal)) ? YearRate : ( YearRate / 2 );

	/* 年利率转换成月利率 */
    QueryLoadInfo->rate = YearRate / 12;



	/* ---------- 2.根据当前月份数计算当月还款总金额 ----------*/
	/* 每月还款本金=贷款本金/还款期数 */
	MonthPrincipal = QueryLoadInfo->principal * 10000 / QueryLoadInfo->monthAll;

	/* 第x个月还款利息=每月还款本金*(还款期数-x+1)*实际月利率 */
	MonthInterest = MonthPrincipal * (QueryLoadInfo->monthAll - QueryLoadInfo->monthCur + 1) * QueryLoadInfo->rate / 1000;

	/* 当月还款总金额为:分摊到每个月的本金 + 每个月的利息 */
	QueryLoadInfo->monthCurMoney = MonthPrincipal + MonthInterest;



	/* ---------- 3.计算本息总金额 ----------*/
	/* 还款总利息=贷款本金*实际月利率*(还款期数+1)/2 */
	AllInterest = QueryLoadInfo->principal * 10000 * (QueryLoadInfo->rate / 1000) * (QueryLoadInfo->monthAll + 1) / 2;

	/* 还款本息总金额=贷款本金+还款总利息 */
	QueryLoadInfo->allMoney = QueryLoadInfo->principal * 10000 + AllInterest;


	/* ---------- 4.计算个人还款本息总金额 ----------*/
	/* 个人还款本息总金额=还款本息总金额-住房公积金还款金额*50% */
	QueryLoadInfo.ownMoney = QueryLoadInfo.allMoney - (fund * 10000 / 2);
}


