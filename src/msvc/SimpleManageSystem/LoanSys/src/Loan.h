/******************************************************************************
  �� �� ��   : api.h
  �� �� ��   : ����
  ��    ��   : 
  ��������   : 2011��8��18��
  ����޸�   :
  ��������   : api.cpp ��ͷ�ļ�
******************************************************************************/

#ifndef __HOSPITAL_H__
#define __HOSPITAL_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
// �����ŵı߽�ֵ
#define LOANID_MIN  1
#define LOANID_MAX  10

// ������ı߽�ֵ
// ���������Сֵ
#define  INCOME_LOW_MIN   1000
// �͵���������ֵ
#define  INCOME_LOW_MAX   5000
// �ߵ��������Сֵ
#define  INCOME_HIGH_MIN  5001
// �ߵ���������ֵ
#define  INCOME_HIGH_MAX   10000

// �������޵ı߽�ֵ
// ��Сֵ
#define  INSTALLMENTS_MIN   12
// ��������Ⱥ���޵����ֵ
#define  INSTALLMENTS_LOW_MAX   120
// ��������Ⱥ���޵����ֵ
#define  INSTALLMENTS_HIGH_MAX   240
// ���޵������ۿ۹յ�
#define  INSTALLMENTS_RATE_DISCOUNT   120

// ������ı߽�ֵ
// ��Сֵ
#define  AMOUNT_MIN   100000
// ��������Ⱥ�������ֵ
#define  AMOUNT_LOW_MAX   500000
// ��������Ⱥ�������ֵ
#define  AMOUNT_HIGH_MAX   1000000
// �����ۿ۵Ĺյ�
#define  AMOUNT_RATE_DISCOUNT   400000

// ����ʱ��ı߽�ֵ
#define  APPLY_TIME_MIN   1
#define  APPLY_TIME_MAX   10

// ��ѯʱ��ı߽�ֵ
#define  QUERY_TIME_MIN   1
#define  QUERY_TIME_MAX   24

// �����ʵ�����
#define  LOAN_RATE_TYPE_0_24   0.024
#define  LOAN_RATE_TYPE_0_48   0.048

// ���ʵ��ۿ�����
#define  LOAD_RATE_DISCOUNT_TYPE_0_5   0.5

// ���еĴ����޶�
#define  BANK_LOAN_AMOUNT_LIMIT   3000000
// �����ܹ���������ķ�������
#define  BANK_LOAN_COUNT_LIMIT   5


/* -----------------------
�������Զ���Ľṹ����
------------------------ */
typedef struct
{
    int grantMoney; //�ѷ��Ŵ�����(��Ԫ)
    int grantNum; //�ѷ��Ŵ������
}BankInfo;

typedef struct
{
    int loanIndex; //������
    LoanStatus status; //״̬
    Reason reason; //ʧ��ԭ��
    int principal; //������(��Ԫ)
    int monthAll; //��������(��)
    float salary; //��������н
    int loanNo; //����˳����ˮ��
    int reqTime; //����ʱ��
    int checkTime; //���ʱ��
    int grantTime; //����ʱ��
}AllInfo;


/* -----------------------
�������Զ���ĺ����
------------------------ */
#define MAX_APPLY_AMOUNT (LOANID_MAX-LOANID_MIN+1) //����������
#define MONTH_EVERY_YEAR 12 //ÿ����12����
#define MONEY_UNIT_TRANSFORM 10000 //�����λת���(��Ԫ->Ԫ)
#define MAX_FUND 100 //ס��������������(��Ԫ)
#define MIN_FUND 0 //ס����������С���(��Ԫ)
#define MIN_REPAY_DATE 1 //��С��������(��)
#define MAX_REPAY_DATE 240 //��󻹿�����(��)


/* -----------------------
�������Զ���ʵ�ֵĺ���
------------------------ */
int Request(int loanIdx, float salary, int principal, int years, int reqTime);
int Check(int loanIdx, float salary, int principal, int years, int reqTime, int flag);
int Release(int loanIdx, float salary, int principal, int years, int reqTime, int flag);
void LoanRate(LoanInfo *QueryLoadInfo, int fund);


/* ϵͳ��ʼ������ */
void CmdReset();

/* ������������ */
void ReqeustLoan(int loanIdx, float salary, int principal, int years, int reqTime);

/* ��ѯ */
void CmdLst(int loanIdx, int month, int fund, int lstTime);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __HOSPITAL_H__ */