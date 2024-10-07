#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "api.h"
#include "car.h"
#include "list.h" //by jiangxin
#include "malloc.h"

int recordNum = 0; //Υ���¼��
int lastTime = -1; //���һ��Υ���ʱ�䣬��Ϊ��ʼ���ı�־
int index = 0; //Υ�����
int score = 0; //û���κ�Υ���¼ʱ����Ϊ20
int flag = 0; //���Ƶ�����־(1��ʾû�б�����)
QUERY_RESULTNode *pHeadNode = NULL; //��ʷΥ����Ϣ����


/* main���� */
void main(int argc, char* argv[])
{
    /* ����Socket��������5555�˿�(sapi_server_start������lib����ʵ��)��
      * lib����ʵ�ִ�Socket���յ��ַ����������ַ�����
      * ����ֻ��Ҫʵ�ַַ���ĸ�����ɡ�
      */
    api_server_start(argc, argv);
    
// �˴�����ִ�е���ע�ⲻҪ�ڴ˴���Ӵ���
}


/*****************************************************************************
 �� �� ��  : opInit
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɡ�ϵͳ��ʼ��������
             ����ʵ����i
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2010��1��21��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
void opInit(void)
{
    if(pHeadNode != NULL) //��ʷΥ������Ϊ��
    {
        if(RemoveList(pHeadNode) != 1)
        {
            api_print_result(E999); //ϵͳ�ڲ�����
            return;
        }
        pHeadNode = NULL;
    }
    
    pHeadNode = CreateList();
    if(pHeadNode == NULL)
    {
        api_print_result(E999); //ϵͳ�ڲ�����
        return;
    }
    
    lastTime=0; //���һ��Υ���ʱ��
    recordNum = 0; //Υ���¼��
    index = 0; //Υ�����
    score = MAX_SCORE_VALUE; //û���κ�Υ���¼ʱ����Ϊ20
    flag = 1; //���Ƶ�����־(1��ʾû�б�����)
    api_print_result(S001); //��ʼ���ɹ�
    
    return;
}


/*****************************************************************************
 �� �� ��  : opRecord
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɡ�¼��Υ���¼������
             ����ʵ����r 0-1
 �������  : int Peccancy  :    Υ������(0:Υ��ͣ��;1:����;2:�����;3:����;4:��Ƽݳ�)
             int Days      :    ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2010��1��21��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
void opRecord(int PeccancyType, int Days)
{
    QueryResult Temp;
    int calCredit = -1; //�۷�
    int calFee = -1; //������
    
    if(lastTime == -1)
    {
        api_print_result(E001); //ϵͳδ��ʼ��
        return;
    }
    if(flag == 0)
    {
        api_print_result(E004); //�����ѵ��� ����ʧ��
        return;
    }
    if(recordNum >= MAX_PECCANCY_RECORD_NUM)
    {
        api_print_result(E009); //Υ���¼����
        return;
    }
    if((PeccancyType < PECCANCY_TYPE_0) || (PeccancyType > PECCANCY_TYPE_4))
    {
        api_print_result(E003); //����Υ�����ͳ���ϵͳ����Χ
        return;
    }
    if((Days < 0) || (Days > MAX_DAYS_VALUE))
    {
        api_print_result(E002); //����ʱ�䳬��ϵͳ����Χ
        return;
    }
    if(Days < lastTime)
    {
        api_print_result(E008); //ʱ�����С���ϴ�ʱ��
        return;
    }

    /* ���㷣�� */
    switch(PeccancyType)
    {
        case 0 : calFee = 100; break;
        case 1 : calFee = 200; break;
        case 2 : calFee = 300; break;
        case 3 : calFee = 400; break;
        case 4 : calFee = 500; break;
        default : calFee = -1; break;
    }

    /* ����۷� */
    switch(PeccancyType)
    {
        case 0 : calCredit = 1; break;
        case 1 : calCredit = 2; break;
        case 2 : calCredit = 3; break;
        case 3 : calCredit = 4; break;
        case 4 : calCredit = 5; break;
        default : calCredit = -1; break;
    }

    recordNum++;
    index++;
    
    Temp.Reason = PeccancyType; //Υ��ԭ��
    Temp.Time = Days; //Υ��ʱ��
    Temp.Index = index; //��ʷΥ����
    Temp.Score = score - calCredit; //ʣ�����
    Temp.Fee = calFee; //������
    Temp.PayFlag = STAT_NO_PAY; //�����Ƿ���ɷ���״̬Ϊδ����
    
    PushBackNode(pHeadNode,&Temp);

    if(score <= 0) //ʣ�����С��0
    {
        flag = 0; //����
        index = 0; //���Υ����
    }

    if(flag == 0) //������Ҫ�����ʷΥ���¼
    {
        RemoveList(pHeadNode);
    }

    api_print_result(S002); //¼����ʷΥ���¼�ɹ�
    
    return;
}


/*****************************************************************************
 �� �� ��  : opQuery
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɲ�ѯΥ���¼����
             ����ʵ����q
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2010��1��21��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
void opQuery(void)
{
    QUERY_RESULTNode* pTemp = NULL;
    QueryResult Temp;
    
    if(recordNum == -1)
    {
        api_print_result(E001); //ϵͳδ��ʼ��
        return;
    }

    if(flag == 0)
    {
        api_print_result(E004); //�����ѵ��� ����ʧ��
        return;
    }

    if(index == 0)
    {
        api_print_result(E010); //��Υ���¼
        return;
    }

    for(pTemp = pHeadNode->pNext; pTemp != NULL; pTemp = pTemp->pNext)
    {
        memcpy(&Temp,&(pTemp->data),sizeof(QueryResult));
        api_print_query_info(&Temp);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : opPay
 ��������  : ������Ҫʵ�ֵĽӿ�
             ��ɽ���Υ�淣�����
             ����ʵ����p 100
 �������  : int  Money       :    ���ɽ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2010��1��21��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
void opPay(int Money)
{
    PayResult pr;
    QUERY_RESULTNode *wpay[MAX_PECCANCY_RECORD_NUM]; //ָ������
    int i = 0, j = 0;
    int flag = 0;
    int pFee;
    QUERY_RESULTNode *pNode = NULL;

    if((Money < 1) || (Money > MAX_MONEY_VALUE))
    {
        api_print_result(S002); //������ɽ���ϵͳ����Χ
        return;
    }

    if(recordNum == 0)
    {
        api_print_result(E007); //��Υ���¼ ����Ҫ���ɷ���
        return;
    }

    pr.Fee = 0; //��ʼ��ʣ�෣����

    pNode = pHeadNode->pNext;
    while(pNode != NULL) //��������δ���ɷ����¼
    {
        if(pNode->data.PayFlag == STAT_NO_PAY)
        {
            wpay[i++] = pNode;
            pr.Fee += pNode->data.Fee; //�ۼ�ʣ�෣�����(ͷ��㷣����Ϊ0)
        }
        pNode=pNode->pNext;
    }

    for(i=0; i<recordNum; i++)
    {
        if(wpay[i]->data.Fee <= Money)
        {
            flag = 1;
            recordNum--;
            pFee = wpay[i]->data.Fee;

            /*if((wpay[i+1]->data.Time==wpay[i]->data.Time)&&(wpay[i+1]->data.Fee<=Money)&&(

            wpay[i+1]->data.Fee>pFee))

                               pFee=wpay[i+1]->data.Fee;*/
            break;
        }
    }

    pr.PeccancyNo = recordNum;
    pr.ReturnMoney = Money-pFee;
    pr.Score = score;
    pr.Fee -= pFee;

    api_print_pay_info(&pr);

    if(flag == 0)
    {
        api_print_result(E006); //���ɶ�����Ч
    }
}