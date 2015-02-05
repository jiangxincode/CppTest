#include "api.h"

/*****************************************************************************
 �� �� ��  : LoanRate
 ��������  : �������ʺͻ�����ʾ��
 �������  : QueryLoadInfo������Ϣ�е�monthAll  : �ܻ�������
             						  principal	: �����ܶ�(��Ԫ)
             						  monthCur	: ��x����
             fund		: �����𻹿��(��Ԫ)

 �������  : QueryLoadInfo������Ϣ�е�rate			: ʵ��������(ǧ��֮)
     								  monthCurMoney : ��x���·ݵĻ��Ϣ�ܽ��(Ԫ)
    								  allMoney      : �軹�Ϣ�ܽ��(Ԫ)
    								  ownMoney		: ����˻��Ϣ�ܽ��(Ԫ)
*****************************************************************************/
void LoanRate(LoanInfo *QueryLoadInfo, int fund)
{
	int YearRate = 0;		/* ������(ǧ��֮) */
	int Year = 0;			/* �������� */
	int MonthPrincipal = 0;	/* ��̯��ÿ���µı���(Ԫ) */
	int MonthInterest = 0;	/* ������Ϣ(Ԫ) */
	int AllInterest = 0;	/* ����Ϣ(Ԫ) */

	/* ---------- 1.���ݸ��ۿۻ��Ƽ���������� ----------*/
	Year = QueryLoadInfo->monthAll / 12;

	/* ��������[1,10],��ʼ������:2.4%����������(10,20],��ʼ������:4.8% */
	YearRate = (1 <= Year && 10 >= Year) ? 24 : 48;	/* ��λΪǧ��֮���ֵΪ24��48 */

	/* ����� [10,40],�������ۿ�:100%�������(40,100],�������ۿ�:50% */
    YearRate = ((10 <= QueryLoadInfo->principal) && ( 40 >= QueryLoadInfo->principal)) ? YearRate : ( YearRate / 2 );

	/* ������ת���������� */
    QueryLoadInfo->rate = YearRate / 12;



	/* ---------- 2.���ݵ�ǰ�·������㵱�»����ܽ�� ----------*/
	/* ÿ�»����=�����/�������� */
	MonthPrincipal = QueryLoadInfo->principal * 10000 / QueryLoadInfo->monthAll;

	/* ��x���»�����Ϣ=ÿ�»����*(��������-x+1)*ʵ�������� */
	MonthInterest = MonthPrincipal * (QueryLoadInfo->monthAll - QueryLoadInfo->monthCur + 1) * QueryLoadInfo->rate / 1000;

	/* ���»����ܽ��Ϊ:��̯��ÿ���µı��� + ÿ���µ���Ϣ */
	QueryLoadInfo->monthCurMoney = MonthPrincipal + MonthInterest;



	/* ---------- 3.���㱾Ϣ�ܽ�� ----------*/
	/* ��������Ϣ=�����*ʵ��������*(��������+1)/2 */
	AllInterest = QueryLoadInfo->principal * 10000 * (QueryLoadInfo->rate / 1000) * (QueryLoadInfo->monthAll + 1) / 2;

	/* ���Ϣ�ܽ��=�����+��������Ϣ */
	QueryLoadInfo->allMoney = QueryLoadInfo->principal * 10000 + AllInterest;


	/* ---------- 4.������˻��Ϣ�ܽ�� ----------*/
	/* ���˻��Ϣ�ܽ��=���Ϣ�ܽ��-ס�������𻹿���*50% */
	QueryLoadInfo.ownMoney = QueryLoadInfo.allMoney - (fund * 10000 / 2);
}


