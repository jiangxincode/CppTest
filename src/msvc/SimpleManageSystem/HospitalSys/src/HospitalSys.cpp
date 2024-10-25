#include <stdlib.h>
#include <string.h>

#include "api.h"

//������Ϣ�����Ե����ݣ������������������ֵ
static PatientIni gPatientIniCfg[] =
{
    //����ID  �������� �ֽ��� �籣���
    {"pat01", 0,       100,     0  ,},
    {"pat02", 1,       100,     100,},
    {"pat03", 0,       100,     0  ,},
    {"pat04", 1,       100,     50 ,},
    {"pat05", 1,       10 ,     10 ,},
    {"pat06", 1,       20 ,     10 ,},
};

static PatientStatus patientStatus[] = {PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE};
static DoctorQueue doctorQueue = {0,""};

//��ΪgPatientIniCfg�е������ǲ����޸ĵģ�����ʹ��patient����һ������
PatientIni patient[MAX_PATIENT_RECORD];


/*****************************************************************************
�� �� ��  : OpInit
��������  : ��Ҫ����ʵ�ֵĽӿ�,ϵͳ��ʼ��
*****************************************************************************/
void OpInit(void)
{
    doctorQueue.queueNum = 0;
    for(int i=0;i<6;i++)
    {
        doctorQueue.pPatientIdInfo[i] = NULL;
        patient[i] = gPatientIniCfg[i];
        patientStatus[i] = PS_IDLE;
    }
    api_print_operation_result(E000_INITITIAL_SUCC); //��ʼ���ɹ�
};

/*****************************************************************************
�� �� ��  : OpRegister
��������  : ��Ҫ����ʵ�ֵĽӿ�,���˹Һ�
�������  : const char *pPatientId ����ID
*****************************************************************************/
void OpRegister(const char *pPatientId)
{
    int index = 0; //��¼�ò��˵����
    for(int i=0;i<MAX_PATIENT_RECORD;i++)
    {
        if(strcmp(patient[i].patientId,pPatientId)==0)
        {
            if(patientStatus[i]!=PS_IDLE) //�жϸò����Ƿ���δ�Һ�״̬
            {
                api_print_operation_result(E002_DIAGNOSE_NOT_END);
                return ;
            }
            index = i;
            break;
        }
    }

    if(doctorQueue.queueNum == MAX_DOCTOR_CAPABILITY) //��������
    {
        api_print_operation_result(E003_QUEUE_EXCEED_OF_PER_DOCTOR);
        return ;
    }

    if(patient[index].patientLevel == PM_INSURE) //���籣�Ĳ���
    {
        if(patient[index].insureBalance >= REG_FEE) //�籣������
        {
            patient[index].insureBalance -= REG_FEE;
        }
        else //�籣����
        {
            if(patient[index].creditBalance >= REG_FEE) //�ֽ����
            {
                patient[index].creditBalance -= REG_FEE;
            }
            else //�ֽ���
            {
                api_print_operation_result(E004_LACK_FEE_FOR_REGISTER);
                return ;
            }
        }
    }
    else //û���籣�Ĳ���
    {
        if(patient[index].creditBalance >= REG_FEE) //�ֽ����
        {
            patient[index].creditBalance -= REG_FEE;
        }
        else
        {
            api_print_operation_result(E004_LACK_FEE_FOR_REGISTER);
            return ;
        }
    }

    doctorQueue.pPatientIdInfo[doctorQueue.queueNum] = (char *)patient[index].patientId;
    doctorQueue.queueNum++;
    patientStatus[index] = PS_IN_QUEUE;
    api_print_register_succ(); //�Һųɹ�
    return ;
}


/*****************************************************************************
�� �� ��  : OpDiag
��������  : ��Ҫ����ʵ�ֵĽӿ�,����
*****************************************************************************/
void OpDiag(void)
{
    if(doctorQueue.queueNum == 0) //�޲����Ŷ�
    {
        api_print_operation_result(E006_NO_PATIENT_IN_QUEUE);
        return ;
    }
    for(int i=0;i<MAX_PATIENT_RECORD;i++)
    {
        if(strcmp(doctorQueue.pPatientIdInfo[0],patient[i].patientId)==0)
        {
            patientStatus[i] = PS_WAIT_PAY;
            break;
        }
    }

    for(int i=0;i<doctorQueue.queueNum;i++)
    {
        doctorQueue.pPatientIdInfo[i] = doctorQueue.pPatientIdInfo[i+1];
    }
    doctorQueue.queueNum--;

    api_print_operation_result(E005_DIAGNOSE_SUCC); //���γɹ�
    return ;
}


/*****************************************************************************
�� �� ��  : OpPay
��������  : ��Ҫ����ʵ�ֵĽӿ�,�ɷ�
�������  : const char *pPatientId ����ID
*****************************************************************************/
void OpPay(const char *pPatientId)
{
    int index;
    for(int i=0;i<MAX_PATIENT_RECORD;i++)
    {
        if(strcmp(patient[i].patientId,pPatientId)==0)
        {
            index = i;
            break;
        }
    }
    if(patientStatus[index] != PS_WAIT_PAY) //�ò��˲��Ǵ��ڴ��ɷ�״̬
    {
        api_print_operation_result(E014_PATIENT_NOT_BE_PAY_STATUS);
        return ;
    }

    patientStatus[index] = PS_IDLE; //�����Ƿ�ɷѳɹ�������δ�Һ�״̬
    if(patient[index].patientLevel == PM_INSURE) //���籣�Ĳ���
    {
        if(patient[index].insureBalance >= DIAG_FEE) //�籣��������
        {
            patient[index].insureBalance -= DIAG_FEE;
            api_print_operation_result(E007_PAY_SUCC);
            return ;
        }
        else
        {
            if(patient[index].creditBalance >= DIAG_FEE) //�ֽ����
            {
                patient[index].creditBalance -= DIAG_FEE;
                api_print_operation_result(E007_PAY_SUCC);
                return ;
            }
            else //�ֽ���
            {
                api_print_operation_result(E008_BALANCE_NOT_ENOUGH);
                return ;
            }
        }
    }
    else //û���籣�Ĳ���
    {
        if(patient[index].creditBalance >= DIAG_FEE) //�ֽ����
        {
            patient[index].creditBalance -= DIAG_FEE;
            api_print_operation_result(E007_PAY_SUCC);
            return ;
        }
        else //�ֽ���
        {
            api_print_operation_result(E008_BALANCE_NOT_ENOUGH);
            return ;
        }
    }

}


/*****************************************************************************
�� �� ��  : OpQuery
��������  : ��Ҫ����ʵ�ֵĽӿ�,��ѯ
�������  : QueryType queryType ��ѯ��ʽ
const char *pQueryId ҽ��/����ID
*****************************************************************************/
void OpQuery(QueryType queryType, const char *pQueryId)
{
    if(queryType == Q_DOCTOR) //��ҽ��ID��ѯ
    {
        api_print_doctor_query_info(&doctorQueue);
    }
    else //������ID��ѯ
    {
        int index = 0; //��¼�ò��˵����
        int seq = 0; //��¼�����Ŷ�λ��
        for(int i=0;i<doctorQueue.queueNum;i++)
        {
            if(strcmp(doctorQueue.pPatientIdInfo[i],pQueryId) == 0)
            {
                seq = i;
                break;
            }
        }
        for(int i=0;i<6;i++)
        {
            if(strcmp(patient[i].patientId,pQueryId) == 0)
            {
                index = i;
                break;
            }
        }
        api_print_patient_query_info(pQueryId,patientStatus[index],seq+1,patient[index].insureBalance,patient[index].creditBalance);
    }

}