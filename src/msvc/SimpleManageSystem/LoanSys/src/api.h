/******************************************************************************
  �� �� ��   : api.h
  �� �� ��   : ����
******************************************************************************/

#ifndef __API_H__
#define __API_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


//�����붨��
typedef enum
{
    OP_E_CMD           = 1,            //(������ʹ��)�����������
    OP_E_INIT_SUCCESS  = 2,            //��ʼ���ɹ�
    OP_E_IDX           = 3,            //�������������
    OP_E_SALARY        = 4,            //�������������������
    OP_E_PRINCIPAL     = 5,            //������������
    OP_E_YEAR          = 6,            //��������������� 
    OP_E_APPLY_TIME    = 7,            //����ʱ���������
    OP_E_APPLYTIME_SUB = 8,            //����ʱ�����ݼ�
    OP_E_MODIFY        = 9,            //���������,�������޸ĳ�ʼ��Ϣ
    OP_E_SUCCESS       = 10,           //��������ɹ�
    OP_E_NO_VALIDAPPLY = 11,           //����Ч�Ĵ�������
	OP_E_MONTH         = 12,           //�����·���Ч
    OP_E_FUND_MONEY    = 13,           //ס�������𻹿�����Ч
    OP_E_QRY_TIME      = 14,           //��ѯʱ���������
    OP_E_QRYTIME_SUB   = 15,           //��ѯʱ�����ݼ�
    OP_E_INFO          = 16            //���˴���������ϸ��Ϣ
}LoanOpRet;


//����״̬
typedef enum
{
	RE_LOAN    = 1,  //����������
	WAIT_CHECK = 2,  //�����
    WAIT_GRANT = 3,  //������
	SUCC_GRANT = 4   //���ųɹ�
}LoanStatus;


//����δͨ��ԭ��
typedef enum
{
    OVER_YEAR      = 1, //�������޳�����Χ,������ʧ��
    OVER_PRINCIPAL = 2, //����𳬳���Χ,������ʧ��
	BANK_NOMOMEY   = 3, //�����޿��ô���,���Ŵ���ʧ��
	SYS_DISABLE    = 4  //���Ŵ���ϵͳ��������,���Ŵ���ʧ��
}Reason;

/* �����ѯ��Ϣ */
typedef struct
{
    int loanIdx;        //������
	LoanStatus status;  //״̬
	Reason reason;      //ʧ��ԭ��	
	int principal;      //�����(��Ԫ)
	int monthAll;       //��������
	int rate;           //ʵ��������(ǧ��֮)
	int monthCur;       //��x���·�
	int monthCurMoney;  //��x���·ݵĻ��Ϣ�ܽ��
	int allMoney;       //�軹�Ϣ�ܽ��
	int ownMoney;       //����˻��Ϣ�ܽ��
} LoanInfo;



/*****************************************************************************
 �� �� ��  : api_loansys_ret
 ��������  : ϵͳ�ṩ�ĺ���,����������,��ӡ���������Ϣ��
 �������  : HospitalsysOpRet OpRet�����붨��
*****************************************************************************/
void api_loansys_ret(LoanOpRet OpRet);

/*****************************************************************************
 �� �� ��  : api_loansys_loaninfo
 ��������  : ϵͳ�ṩ�ĺ���,����������,��ӡ�����ѯ
 �������  : OpRet�����붨��
             BalanceInfo���߽�����Ϣ
*****************************************************************************/
void api_loansys_loaninfo(LoanInfo loanInfo);



/*****************************************************************************
 �� �� ��  : api_server_start
 ��������  : ����socket����ˣ��������ķ�ʽ�����û�����
*****************************************************************************/
void api_server_start(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __API_H__ */