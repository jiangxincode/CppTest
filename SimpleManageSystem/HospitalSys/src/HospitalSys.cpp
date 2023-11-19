#include <stdlib.h>
#include <string.h>

#include "api.h"

//病人信息，测试的依据，考生不允许更改其数值
static PatientIni gPatientIniCfg[] =
{
    //病人ID  病人类型 现金金额 社保金额
    {"pat01", 0,       100,     0  ,},
    {"pat02", 1,       100,     100,},
    {"pat03", 0,       100,     0  ,},
    {"pat04", 1,       100,     50 ,},
    {"pat05", 1,       10 ,     10 ,},
    {"pat06", 1,       20 ,     10 ,},
};

static PatientStatus patientStatus[] = {PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE,PS_IDLE};
static DoctorQueue doctorQueue = {0,""};

//因为gPatientIniCfg中的数据是不能修改的，所以使用patient复制一份数据
PatientIni patient[MAX_PATIENT_RECORD];


/*****************************************************************************
函 数 名  : OpInit
功能描述  : 需要考生实现的接口,系统初始化
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
    api_print_operation_result(E000_INITITIAL_SUCC); //初始化成功
};

/*****************************************************************************
函 数 名  : OpRegister
功能描述  : 需要考生实现的接口,病人挂号
输入参数  : const char *pPatientId 病人ID
*****************************************************************************/
void OpRegister(const char *pPatientId)
{
    int index = 0; //记录该病人的序号
    for(int i=0;i<MAX_PATIENT_RECORD;i++)
    {
        if(strcmp(patient[i].patientId,pPatientId)==0)
        {
            if(patientStatus[i]!=PS_IDLE) //判断该病人是否处于未挂号状态
            {
                api_print_operation_result(E002_DIAGNOSE_NOT_END);
                return ;
            }
            index = i;
            break;
        }
    }

    if(doctorQueue.queueNum == MAX_DOCTOR_CAPABILITY) //队列已满
    {
        api_print_operation_result(E003_QUEUE_EXCEED_OF_PER_DOCTOR);
        return ;
    }

    if(patient[index].patientLevel == PM_INSURE) //有社保的病人
    {
        if(patient[index].insureBalance >= REG_FEE) //社保余额充足
        {
            patient[index].insureBalance -= REG_FEE;
        }
        else //社保余额不足
        {
            if(patient[index].creditBalance >= REG_FEE) //现金充足
            {
                patient[index].creditBalance -= REG_FEE;
            }
            else //现金不足
            {
                api_print_operation_result(E004_LACK_FEE_FOR_REGISTER);
                return ;
            }
        }
    }
    else //没有社保的病人
    {
        if(patient[index].creditBalance >= REG_FEE) //现金充足
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
    api_print_register_succ(); //挂号成功
    return ;
}


/*****************************************************************************
函 数 名  : OpDiag
功能描述  : 需要考生实现的接口,就诊
*****************************************************************************/
void OpDiag(void)
{
    if(doctorQueue.queueNum == 0) //无病人排队
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

    api_print_operation_result(E005_DIAGNOSE_SUCC); //诊治成功
    return ;
}


/*****************************************************************************
函 数 名  : OpPay
功能描述  : 需要考生实现的接口,缴费
输入参数  : const char *pPatientId 病人ID
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
    if(patientStatus[index] != PS_WAIT_PAY) //该病人不是处于待缴费状态
    {
        api_print_operation_result(E014_PATIENT_NOT_BE_PAY_STATUS);
        return ;
    }

    patientStatus[index] = PS_IDLE; //无论是否缴费成功都进入未挂号状态
    if(patient[index].patientLevel == PM_INSURE) //有社保的病人
    {
        if(patient[index].insureBalance >= DIAG_FEE) //社保卡余额充足
        {
            patient[index].insureBalance -= DIAG_FEE;
            api_print_operation_result(E007_PAY_SUCC);
            return ;
        }
        else
        {
            if(patient[index].creditBalance >= DIAG_FEE) //现金充足
            {
                patient[index].creditBalance -= DIAG_FEE;
                api_print_operation_result(E007_PAY_SUCC);
                return ;
            }
            else //现金不足
            {
                api_print_operation_result(E008_BALANCE_NOT_ENOUGH);
                return ;
            }
        }
    }
    else //没有社保的病人
    {
        if(patient[index].creditBalance >= DIAG_FEE) //现金充足
        {
            patient[index].creditBalance -= DIAG_FEE;
            api_print_operation_result(E007_PAY_SUCC);
            return ;
        }
        else //现金不足
        {
            api_print_operation_result(E008_BALANCE_NOT_ENOUGH);
            return ;
        }
    }

}


/*****************************************************************************
函 数 名  : OpQuery
功能描述  : 需要考生实现的接口,查询
输入参数  : QueryType queryType 查询方式
const char *pQueryId 医生/病人ID
*****************************************************************************/
void OpQuery(QueryType queryType, const char *pQueryId)
{
    if(queryType == Q_DOCTOR) //按医生ID查询
    {
        api_print_doctor_query_info(&doctorQueue);
    }
    else //按病人ID查询
    {
        int index = 0; //记录该病人的序号
        int seq = 0; //记录病人排队位置
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