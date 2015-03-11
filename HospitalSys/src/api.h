#ifndef __API_H__
#define __API_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

//本文件中的宏、结构体、API函数供考生使用，但不需更改
#define min(a,b)    (((a) < (b)) ? (a) : (b))

//医生初始信息的记录数
#define MAX_DOCTOR_RECORD       1

//病人初始信息的记录数
#define MAX_PATIENT_RECORD      6

//医生允许排队就诊的病人最大数量
#define MAX_DOCTOR_CAPABILITY   4

//挂号费
#define REG_FEE                 10

//处方费
#define DIAG_FEE                50

//命名字符串最大长度
#define CMD_LEN                 10000

//命令分隔符
#define CMD_SEPARATRIX          ","

//操作码定义
typedef enum _OpRet
{
    E000_INITITIAL_SUCC             = 0, //E000:初始化成功
    E002_DIAGNOSE_NOT_END           = 2, //E002:本次看病未结束
    E003_QUEUE_EXCEED_OF_PER_DOCTOR = 3, //E003:医生排队人数达到上限
    E004_LACK_FEE_FOR_REGISTER      = 4, //E004:无足够挂号费用
    E005_DIAGNOSE_SUCC              = 5, //E005:诊治成功
    E006_NO_PATIENT_IN_QUEUE        = 6, //E006:无病人排队
    E007_PAY_SUCC                   = 7, //E007:缴费成功
    E008_BALANCE_NOT_ENOUGH         = 8, //E008:余额不足
    E014_PATIENT_NOT_BE_PAY_STATUS  = 14, //E014:无该病人待缴费
    E016_NO_PATIENT_IN_HOSP         = 16, //E016:本院无该病人
    E017_DCT_DIAG_NOBODY            = 17, //E017:医生尚未诊断过任何病人
}OpRet;

//病人就诊的状态
typedef enum _PatientStatus
{
    PS_IDLE,    //未挂号
    PS_IN_QUEUE,//待就诊
    PS_WAIT_PAY,//待缴费
}PatientStatus;

//病人类型
typedef enum _PayMethod
{
    PM_CREDIT,  //无社保病人
    PM_INSURE,  //有社保病人
 //在挂号和缴费是有区别
}PayMethod;

//查询方式
typedef enum _QueryType
{
    Q_DOCTOR,   //按医生ID查询
    Q_PATIENT,  //按病人ID查询
}QueryType;

//单条的病人初始信息记录
typedef struct
{
    const char *patientId;  //病人ID
    int patientLevel;       //病人类型
    int creditBalance;      //现金金额
    int insureBalance;      //社保金额
}PatientIni;

//查询医生的信息结果
typedef struct
{
    int queueNum;                               //排队的病人数量
    char *pPatientIdInfo[MAX_DOCTOR_CAPABILITY];//排队的病人ID列表
 //用指针数组，Queue->pPatientIdInfo[0]表示的为排在第一位的病人。
}DoctorQueue;



/*****************************************************************************
 函 数 名  : api_print_operation_result
 功能描述  : 系统提供的函数,供考生调用,打印操作结果信息
 输入参数  : OpRet opRet 操作码定义
*****************************************************************************/
void api_print_operation_result(OpRet opRet);

/*****************************************************************************
 函 数 名  : api_print_register_succ
 功能描述  : 系统提供的函数,供考生调用,挂号成功返回的信息
*****************************************************************************/
void api_print_register_succ(void);

/*****************************************************************************
 函 数 名  : api_print_patient_query_info
 功能描述  : 系统提供的函数,供考生调用,按照病人方式查询的结果
 输入参数  : const char *pPatientId 病人ID
             PatientStatus patientStatus 病人就诊的状态
             int sequence 病人正在排队就诊时的序号,仅在patientStatus为PS_IN_QUEUE有效
                          patientStatus为其他值时sequence可以输入任意值
             int insureBalance 社保帐户余额
             int creditBalance 现金帐户余额
*****************************************************************************/
void api_print_patient_query_info(const char *pPatientId,
                                  PatientStatus patientStatus,
                                  int sequence,
                                  int insureBalance,
                                  int creditBalance);

/*****************************************************************************
 函 数 名  : api_print_doctor_query_info
 功能描述  : 系统提供的函数,供考生调用,按照医生方式查询的结果
 输入参数  : DoctorQueue *pDoctorQueue 医生名下的病人排队情况
*****************************************************************************/
void api_print_doctor_query_info(DoctorQueue *pDoctorQueue);

//需考生实现的函数声明 BEGIN
void OpInit(void);
void OpRegister(const char *pPatientId);
void OpDiag();
void OpPay(const char *pPatientId);
void OpQuery(QueryType queryType, const char *pQueryId);
//需考生实现的函数声明 END

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __API_H__ */
