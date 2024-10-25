#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "stdlib.h"

#include "api.h"

/*****************************************************************************
 �� �� ��  : libOutputStr
 ��������  : �ڲ�����: ����ϵͳ�������ӡ���������������ע
 �������  : pcStr  �����ӡ�ַ���
*****************************************************************************/
void libOutputStr(char* pcStr);

/*****************************************************************************
 �� �� ��  : cmd_process
 ��������  : ϵͳ���õĺ���,���������ע
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

//ִ�������
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
    //��Ϊi��ִ�г�ʼ������
    if (p == strstr(p, "i"))
    {
        OpInit();
        return;
    }
    //��Ϊ�Һţ���Buff1�洢�ҺŵĲ��˵�ID����ִ�йҺź���
    else if (p == strstr(p, "reg_"))
    {
        GetParaCount = sscanf(p, "reg_%s", Buff1);
        if (1 == GetParaCount)
        {
            OpRegister(Buff1);
            return;
        }
    }
    //��Ϊ���Σ���ִ�����κ���
    else if (p == strstr(p, "diag"))
    {
        OpDiag();
        return;
    }
    //��Ϊ�ɷ����ò���Buff1���нɷѡ�
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
        //��Ϊ��ѯ������ִ�в�ѯ����tmpParaAΪ0��buffer1==dct�Ǳ�ʾ��ʾ��ѯҽ����ǰ�Ĳ����Ŷ����
        //��tmpParaAΪ1��buffer1==patID���ʾ��ѯIDΪpat01�Ĳ�����Ϣ��
        if (2 == GetParaCount)
        {
            OpQuery((QueryType)tmpParaA, Buff1);
            return;
        }
    }
    libOutputStr("��Ч����");
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
            libOutputStr("E000"); //:��ʼ���ɹ�
            break;
        case E002_DIAGNOSE_NOT_END:
            libOutputStr("E002"); //:���ο���δ����
            break;
        case E003_QUEUE_EXCEED_OF_PER_DOCTOR:
            libOutputStr("E003");  //:ҽ���Ŷ������ﵽ����
            break;
        case E004_LACK_FEE_FOR_REGISTER:
            libOutputStr("E004"); //:���㹻�Һŷ���
            break;
        case E005_DIAGNOSE_SUCC:
            libOutputStr("E005"); //:���γɹ�
            break;
        case E006_NO_PATIENT_IN_QUEUE:
            libOutputStr("E006"); //:�޲����Ŷ�
            break;
        case E007_PAY_SUCC:
            libOutputStr("E007"); //:�ɷѳɹ�
            break;
        case E008_BALANCE_NOT_ENOUGH:
            libOutputStr("E008"); //:����
            break;
        case E014_PATIENT_NOT_BE_PAY_STATUS:
            libOutputStr("E014"); //:�޸ò��˴��ɷ�
            break;
        case E016_NO_PATIENT_IN_HOSP:
            libOutputStr("E016"); //:��Ժ�޸ò���
            break;
        case E017_DCT_DIAG_NOBODY:
            libOutputStr("E017"); //:ҽ����δ��Ϲ��κβ���
            break;
        default:
            break;
    }
    return;
}

void api_print_register_succ(void)
{
    libOutputStr("E001"); //:�Һųɹ�
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
            sprintf(pBuff, "E012:%s 1 %d,%d,%d",  //������ ���ڵ�%dλ,�籣�ʻ����:%d,�ֽ��ʻ����:%d
                    pPatientId, sequence, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;
        case PS_IDLE:
            sprintf(pBuff, "E012:%s 0 %d,%d",//δ�Һ� �籣�ʻ����:%d,�ֽ��ʻ����:%d
                    pPatientId, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;
        case PS_WAIT_PAY:
            sprintf(pBuff, "E012:%s 2 %d,%d", //���ɷ� �籣�ʻ����:%d,�ֽ��ʻ����:%d
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
        libOutputStr("E013:dct 0"); //�����Ŷ�
    }
    else
    {
        int i;
        sprintf(pBuff, "E013:dct"); //�ȴ�����
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
 �� �� ��  : libOutputStr
 ��������  : �ڲ�����: ����ϵͳ�������ӡ����
 �������  : pcStr  �����ӡ�ַ���
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void libOutputStr(char* pcStr)
{
    if (NULL != pcStr )
    {
        printf("%s\n", pcStr);
    }
}

/*****************************************************************************
 �� �� ��  : cmd_process
 ��������  : ϵͳ���ú���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void cmd_process(int argc, char* argv[])
{
    char *pszCmd = NULL;
    int iCmdNum =0;
    //�ڴ����ʧ�ܣ��˳�����
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
        //��ȡ����pszCmd��
        iCmdNum = scanf("%s", pszCmd);
        pszCmd[CMD_LEN-1] = 0;
        if (1 == iCmdNum)
        {
            char *pComma = pszCmd;
            char *pCmdStartPos = pszCmd;
            char pszCmdBuffer[512];
            // �������Զ��ŷָ�
            pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
            //���ڶ�����ʱ������
            while (NULL != pComma)
            {
                size_t uiCpyLen = 0;
                //��Դ��ڶ�����ŵ����⣬һֱ�ҵ���һ����Ϊ���ŵ�λ��pCmdStartPos��pCommaΪpCmdStartPos��ĵ�һ�����ŵ�λ��
                if (pComma == pCmdStartPos)
                {
                    pCmdStartPos = pComma+1;
                    pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
                    continue;
                }
                memset(pszCmdBuffer, 0, sizeof(pszCmdBuffer));
                //uiCpyLenΪ��һ������ĳ��ȣ�������һ������Ƹ�pszCmdBuffer��
                uiCpyLen = min(sizeof(pszCmdBuffer), (size_t)(pComma - pCmdStartPos));

                strncpy(pszCmdBuffer, pCmdStartPos, uiCpyLen);
                //ִ��pszCmdBuffer��������Ӧ�Ĳ���
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
