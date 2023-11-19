#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "stdlib.h"

#include "api.h"

/*****************************************************************************
 函 数 名  : libOutputStr
 功能描述  : 内部函数: 考试系统的输出打印函数，考生无须关注
 输入参数  : pcStr  输出打印字符串
*****************************************************************************/
void libOutputStr(char* pcStr);

/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用的函数,考生无需关注
*****************************************************************************/
void cmd_process(int argc, char* argv[]);

int main(int argc, char* argv[])
{
#ifdef OI_OUTPUT
    cmd_process(argc,argv);
#else
    while(true)
    {
        cmd_process(argc,argv);
    }
#endif
    return 0;
}

//执行命令函数
void cmd_dispatch(char *pszCmd)
{
    char    Buff1[32];
    char    Buff2[32];
    char    Buff3[32];
    int     tmpParaA;
    int             GetParaCount;
    const char      *p = NULL;
    const char      *p1 = NULL;
    if (NULL == pszCmd)
    {
        return;
    }
    p = pszCmd;
    memset(Buff1, 0, sizeof(Buff1));
    memset(Buff2, 0, sizeof(Buff2));
    memset(Buff3, 0, sizeof(Buff3));
    //若为i则执行初始化函数
    if (p == strstr(p, "i"))
    {
        OpInit();
        return;
    }
    //若为挂号，则Buff1存储挂号的病人的ID，并执行挂号函数
    else if (p == strstr(p, "reg_"))
    {
        GetParaCount = sscanf(p, "reg_%s", Buff1);
        if (1 == GetParaCount)
        {
            OpRegister(Buff1);
            return;
        }
    }
    //若为诊治，则执行诊治函数
    else if (p == strstr(p, "diag"))
    {
        OpDiag();
        return;
    }
    //若为缴费则让病人Buff1进行缴费。
    else if (p == strstr(p, "pay"))
    {
        GetParaCount = sscanf(p, "pay_%s", Buff1);
        if (1 == GetParaCount)
        {
            OpPay(Buff1);
            return;
        }
    }
    else if (p == strstr(p, "qu"))
    {
        GetParaCount = sscanf(p, "qu_%d-%s", &tmpParaA, Buff1);
        //若为查询命令则执行查询，当tmpParaA为0，buffer1==dct是表示表示查询医生当前的病人排队情况
        //若tmpParaA为1，buffer1==patID则表示查询ID为pat01的病人信息。
        if (2 == GetParaCount)
        {
            OpQuery((QueryType)tmpParaA, Buff1);
            return;
        }
    }
    libOutputStr("无效命令");
    return;
}

void user_cmdproc(char *pszCmd, int iLen)
{
    if (NULL == pszCmd)
    {
        return;
    }
    cmd_dispatch(pszCmd);
    return;
}

void api_print_operation_result(OpRet opRet)
{
    switch (opRet)
    {
        case E000_INITITIAL_SUCC:
            libOutputStr("E000"); //:初始化成功
            break;
        case E002_DIAGNOSE_NOT_END:
            libOutputStr("E002"); //:本次看病未结束
            break;
        case E003_QUEUE_EXCEED_OF_PER_DOCTOR:
            libOutputStr("E003");  //:医生排队人数达到上限
            break;
        case E004_LACK_FEE_FOR_REGISTER:
            libOutputStr("E004"); //:无足够挂号费用
            break;
        case E005_DIAGNOSE_SUCC:
            libOutputStr("E005"); //:诊治成功
            break;
        case E006_NO_PATIENT_IN_QUEUE:
            libOutputStr("E006"); //:无病人排队
            break;
        case E007_PAY_SUCC:
            libOutputStr("E007"); //:缴费成功
            break;
        case E008_BALANCE_NOT_ENOUGH:
            libOutputStr("E008"); //:余额不足
            break;
        case E014_PATIENT_NOT_BE_PAY_STATUS:
            libOutputStr("E014"); //:无该病人待缴费
            break;
        case E016_NO_PATIENT_IN_HOSP:
            libOutputStr("E016"); //:本院无该病人
            break;
        case E017_DCT_DIAG_NOBODY:
            libOutputStr("E017"); //:医生尚未诊断过任何病人
            break;
        default:
            break;
    }
    return;
}

void api_print_register_succ(void)
{
    libOutputStr("E001"); //:挂号成功
    return;
}

void api_print_patient_query_info(const char *pPatientId, PatientStatus patientStatus, int sequence, int insureBalance, int creditBalance)
{
    char pBuff[512];
    if (NULL == pPatientId)
    {
        return;
    }
    memset(pBuff, 0, sizeof(pBuff));
    switch (patientStatus)
    {
        case PS_IN_QUEUE:
            sprintf(pBuff, "E012:%s 1 %d,%d,%d",  //待就诊 排在第%d位,社保帐户余额:%d,现金帐户余额:%d
                    pPatientId, sequence, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;
        case PS_IDLE:
            sprintf(pBuff, "E012:%s 0 %d,%d",//未挂号 社保帐户余额:%d,现金帐户余额:%d
                    pPatientId, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;
        case PS_WAIT_PAY:
            sprintf(pBuff, "E012:%s 2 %d,%d", //待缴费 社保帐户余额:%d,现金帐户余额:%d
                    pPatientId, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;
        default:
            break;
    }
    return;
}

void api_print_doctor_query_info(DoctorQueue *pDoctorQueue)
{
    char pBuff[512];
    if (NULL == pDoctorQueue)
    {
        return;
    }
    memset(pBuff, 0, sizeof(pBuff));
    if (0 == pDoctorQueue->queueNum)
    {
        libOutputStr("E013:dct 0"); //无人排队
    }
    else
    {
        int i;
        sprintf(pBuff, "E013:dct"); //等待队列
        for (i = 0; i < pDoctorQueue->queueNum; i++)
        {
            strcat(pBuff, " ");
            strcat(pBuff, pDoctorQueue->pPatientIdInfo[i]);
        }
        libOutputStr(pBuff);
    }
    return;
}

/*****************************************************************************
 函 数 名  : libOutputStr
 功能描述  : 内部函数: 考试系统的输出打印函数
 输入参数  : pcStr  输出打印字符串
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void libOutputStr(char* pcStr)
{
    if (NULL != pcStr )
    {
        printf("%s\n", pcStr);
    }
}

/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void cmd_process(int argc, char* argv[])
{
    char *pszCmd = NULL;
    int iCmdNum =0;
    //内存分配失败，退出函数
    pszCmd = (char*)malloc(CMD_LEN);
    if (NULL == pszCmd)
    {
        return;
    }

#ifdef _WIN32
    //    while (true)
#endif
    {
        iCmdNum =0;
        memset(pszCmd, 0, CMD_LEN);
        //获取命令pszCmd。
        iCmdNum = scanf("%s", pszCmd);
        pszCmd[CMD_LEN-1] = 0;
        if (1 == iCmdNum)
        {
            char *pComma = pszCmd;
            char *pCmdStartPos = pszCmd;
            char pszCmdBuffer[512];
            // 多命令以逗号分割
            pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
            //存在多命令时处理方法
            while (NULL != pComma)
            {
                size_t uiCpyLen = 0;
                //针对存在多个逗号的问题，一直找到第一个不为逗号的位置pCmdStartPos，pComma为pCmdStartPos后的第一个逗号的位置
                if (pComma == pCmdStartPos)
                {
                    pCmdStartPos = pComma+1;
                    pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
                    continue;
                }
                memset(pszCmdBuffer, 0, sizeof(pszCmdBuffer));
                //uiCpyLen为第一个命令的长度，并将第一个命令复制给pszCmdBuffer。
                uiCpyLen = min(sizeof(pszCmdBuffer), (size_t)(pComma - pCmdStartPos));

                strncpy(pszCmdBuffer, pCmdStartPos, uiCpyLen);
                //执行pszCmdBuffer命令所对应的操作
                cmd_dispatch(pszCmdBuffer);

                pCmdStartPos = pComma+1;
                while(' ' == *pCmdStartPos)
                {
                    pCmdStartPos ++;
                }
                pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
            }
            cmd_dispatch(pCmdStartPos);
        }
        else
        {
            libOutputStr("Get command fail.");
        }
    }

    free(pszCmd);
    return;
}
