#ifndef __API_H__
#define __API_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

//���ļ��еĺꡢ�ṹ�塢API����������ʹ�ã����������
#define min(a,b)    (((a) < (b)) ? (a) : (b))

//ҽ����ʼ��Ϣ�ļ�¼��
#define MAX_DOCTOR_RECORD       1

//���˳�ʼ��Ϣ�ļ�¼��
#define MAX_PATIENT_RECORD      6

//ҽ�������ŶӾ���Ĳ����������
#define MAX_DOCTOR_CAPABILITY   4

//�Һŷ�
#define REG_FEE                 10

//������
#define DIAG_FEE                50

//�����ַ�����󳤶�
#define CMD_LEN                 10000

//����ָ���
#define CMD_SEPARATRIX          ","

//�����붨��
typedef enum _OpRet
{
    E000_INITITIAL_SUCC             = 0, //E000:��ʼ���ɹ�
    E002_DIAGNOSE_NOT_END           = 2, //E002:���ο���δ����
    E003_QUEUE_EXCEED_OF_PER_DOCTOR = 3, //E003:ҽ���Ŷ������ﵽ����
    E004_LACK_FEE_FOR_REGISTER      = 4, //E004:���㹻�Һŷ���
    E005_DIAGNOSE_SUCC              = 5, //E005:���γɹ�
    E006_NO_PATIENT_IN_QUEUE        = 6, //E006:�޲����Ŷ�
    E007_PAY_SUCC                   = 7, //E007:�ɷѳɹ�
    E008_BALANCE_NOT_ENOUGH         = 8, //E008:����
    E014_PATIENT_NOT_BE_PAY_STATUS  = 14, //E014:�޸ò��˴��ɷ�
    E016_NO_PATIENT_IN_HOSP         = 16, //E016:��Ժ�޸ò���
    E017_DCT_DIAG_NOBODY            = 17, //E017:ҽ����δ��Ϲ��κβ���
}OpRet;

//���˾����״̬
typedef enum _PatientStatus
{
    PS_IDLE,    //δ�Һ�
    PS_IN_QUEUE,//������
    PS_WAIT_PAY,//���ɷ�
}PatientStatus;

//��������
typedef enum _PayMethod
{
    PM_CREDIT,  //���籣����
    PM_INSURE,  //���籣����
 //�ڹҺźͽɷ���������
}PayMethod;

//��ѯ��ʽ
typedef enum _QueryType
{
    Q_DOCTOR,   //��ҽ��ID��ѯ
    Q_PATIENT,  //������ID��ѯ
}QueryType;

//�����Ĳ��˳�ʼ��Ϣ��¼
typedef struct
{
    const char *patientId;  //����ID
    int patientLevel;       //��������
    int creditBalance;      //�ֽ���
    int insureBalance;      //�籣���
}PatientIni;

//��ѯҽ������Ϣ���
typedef struct
{
    int queueNum;                               //�ŶӵĲ�������
    char *pPatientIdInfo[MAX_DOCTOR_CAPABILITY];//�ŶӵĲ���ID�б�
 //��ָ�����飬Queue->pPatientIdInfo[0]��ʾ��Ϊ���ڵ�һλ�Ĳ��ˡ�
}DoctorQueue;



/*****************************************************************************
 �� �� ��  : api_print_operation_result
 ��������  : ϵͳ�ṩ�ĺ���,����������,��ӡ���������Ϣ
 �������  : OpRet opRet �����붨��
*****************************************************************************/
void api_print_operation_result(OpRet opRet);

/*****************************************************************************
 �� �� ��  : api_print_register_succ
 ��������  : ϵͳ�ṩ�ĺ���,����������,�Һųɹ����ص���Ϣ
*****************************************************************************/
void api_print_register_succ(void);

/*****************************************************************************
 �� �� ��  : api_print_patient_query_info
 ��������  : ϵͳ�ṩ�ĺ���,����������,���ղ��˷�ʽ��ѯ�Ľ��
 �������  : const char *pPatientId ����ID
             PatientStatus patientStatus ���˾����״̬
             int sequence ���������ŶӾ���ʱ�����,����patientStatusΪPS_IN_QUEUE��Ч
                          patientStatusΪ����ֵʱsequence������������ֵ
             int insureBalance �籣�ʻ����
             int creditBalance �ֽ��ʻ����
*****************************************************************************/
void api_print_patient_query_info(const char *pPatientId,
                                  PatientStatus patientStatus,
                                  int sequence,
                                  int insureBalance,
                                  int creditBalance);

/*****************************************************************************
 �� �� ��  : api_print_doctor_query_info
 ��������  : ϵͳ�ṩ�ĺ���,����������,����ҽ����ʽ��ѯ�Ľ��
 �������  : DoctorQueue *pDoctorQueue ҽ�����µĲ����Ŷ����
*****************************************************************************/
void api_print_doctor_query_info(DoctorQueue *pDoctorQueue);

//�迼��ʵ�ֵĺ������� BEGIN
void OpInit(void);
void OpRegister(const char *pPatientId);
void OpDiag();
void OpPay(const char *pPatientId);
void OpQuery(QueryType queryType, const char *pQueryId);
//�迼��ʵ�ֵĺ������� END

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __API_H__ */
