#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "api.h"
#include "car.h"
#include "list.h" //by jiangxin
#include "malloc.h"

int recordNum = 0; //违规记录数
int lastTime = -1; //最后一次违规的时间，作为初始化的标志
int index = 0; //违规序号
int score = 0; //没有任何违规记录时积分为20
int flag = 0; //车牌吊销标志(1表示没有被吊销)
QUERY_RESULTNode *pHeadNode = NULL; //历史违规信息链表


/* main函数 */
void main(int argc, char* argv[])
{
    /* 启动Socket服务侦听5555端口(sapi_server_start函数在lib库已实现)。
      * lib库已实现从Socket接收到字符串后的命令分发处理
      * 考生只需要实现分发后的各命令即可。
      */
    api_server_start(argc, argv);
    
// 此处不会执行到注意不要在此处添加代码
}


/*****************************************************************************
 函 数 名  : opInit
 功能描述  : 考生需要实现的接口
             完成“系统初始化”操作
             命令实例i
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2010年1月21日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
void opInit(void)
{
    if(pHeadNode != NULL) //历史违规链表不为空
    {
        if(RemoveList(pHeadNode) != 1)
        {
            api_print_result(E999); //系统内部错误
            return;
        }
        pHeadNode = NULL;
    }
    
    pHeadNode = CreateList();
    if(pHeadNode == NULL)
    {
        api_print_result(E999); //系统内部错误
        return;
    }
    
    lastTime=0; //最后一次违规的时间
    recordNum = 0; //违规记录数
    index = 0; //违规序号
    score = MAX_SCORE_VALUE; //没有任何违规记录时积分为20
    flag = 1; //车牌吊销标志(1表示没有被吊销)
    api_print_result(S001); //初始化成功
    
    return;
}


/*****************************************************************************
 函 数 名  : opRecord
 功能描述  : 考生需要实现的接口
             完成“录入违规记录”操作
             命令实例r 0-1
 输入参数  : int Peccancy  :    违规类型(0:违章停车;1:超速;2:闯红灯;3:超载;4:醉酒驾车)
             int Days      :    时间
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2010年1月21日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
void opRecord(int PeccancyType, int Days)
{
    QueryResult Temp;
    int calCredit = -1; //扣分
    int calFee = -1; //罚款金额
    
    if(lastTime == -1)
    {
        api_print_result(E001); //系统未初始化
        return;
    }
    if(flag == 0)
    {
        api_print_result(E004); //车牌已吊销 操作失败
        return;
    }
    if(recordNum >= MAX_PECCANCY_RECORD_NUM)
    {
        api_print_result(E009); //违规记录已满
        return;
    }
    if((PeccancyType < PECCANCY_TYPE_0) || (PeccancyType > PECCANCY_TYPE_4))
    {
        api_print_result(E003); //输入违规类型超出系统允许范围
        return;
    }
    if((Days < 0) || (Days > MAX_DAYS_VALUE))
    {
        api_print_result(E002); //输入时间超出系统允许范围
        return;
    }
    if(Days < lastTime)
    {
        api_print_result(E008); //时间参数小于上次时间
        return;
    }

    /* 计算罚款 */
    switch(PeccancyType)
    {
        case 0 : calFee = 100; break;
        case 1 : calFee = 200; break;
        case 2 : calFee = 300; break;
        case 3 : calFee = 400; break;
        case 4 : calFee = 500; break;
        default : calFee = -1; break;
    }

    /* 计算扣分 */
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
    
    Temp.Reason = PeccancyType; //违规原因
    Temp.Time = Days; //违规时间
    Temp.Index = index; //历史违规编号
    Temp.Score = score - calCredit; //剩余积分
    Temp.Fee = calFee; //罚款金额
    Temp.PayFlag = STAT_NO_PAY; //设置是否缴纳罚款状态为未缴纳
    
    PushBackNode(pHeadNode,&Temp);

    if(score <= 0) //剩余积分小于0
    {
        flag = 0; //吊销
        index = 0; //清空违规编号
    }

    if(flag == 0) //吊销需要清空历史违规记录
    {
        RemoveList(pHeadNode);
    }

    api_print_result(S002); //录入历史违规记录成功
    
    return;
}


/*****************************************************************************
 函 数 名  : opQuery
 功能描述  : 考生需要实现的接口
             完成查询违规记录操作
             命令实例q
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2010年1月21日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
void opQuery(void)
{
    QUERY_RESULTNode* pTemp = NULL;
    QueryResult Temp;
    
    if(recordNum == -1)
    {
        api_print_result(E001); //系统未初始化
        return;
    }

    if(flag == 0)
    {
        api_print_result(E004); //车牌已吊销 操作失败
        return;
    }

    if(index == 0)
    {
        api_print_result(E010); //无违规记录
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
 函 数 名  : opPay
 功能描述  : 考生需要实现的接口
             完成缴纳违规罚款操作
             命令实例p 100
 输入参数  : int  Money       :    缴纳金额
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2010年1月21日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
void opPay(int Money)
{
    PayResult pr;
    QUERY_RESULTNode *wpay[MAX_PECCANCY_RECORD_NUM]; //指针数组
    int i = 0, j = 0;
    int flag = 0;
    int pFee;
    QUERY_RESULTNode *pNode = NULL;

    if((Money < 1) || (Money > MAX_MONEY_VALUE))
    {
        api_print_result(S002); //输入缴纳金额超出系统允许范围
        return;
    }

    if(recordNum == 0)
    {
        api_print_result(E007); //无违规记录 不需要缴纳罚款
        return;
    }

    pr.Fee = 0; //初始化剩余罚款金额

    pNode = pHeadNode->pNext;
    while(pNode != NULL) //遍历所有未缴纳罚款记录
    {
        if(pNode->data.PayFlag == STAT_NO_PAY)
        {
            wpay[i++] = pNode;
            pr.Fee += pNode->data.Fee; //累加剩余罚款金额澹(头结点罚款金额为0)
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
        api_print_result(E006); //缴纳动作无效
    }
}