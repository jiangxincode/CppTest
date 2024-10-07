#include <stdio.h>
#include <string.h>

#include "api.h"
#include "car.h"


#define MAX_COMMAND_NUM 3 //输入命令最大子段数
#define MAX_COMMAND_LENGTH 128 //输入命令每个子段的最大长度

/*****************************************************************************
函 数 名  : api_print_result
功能描述  : 打印返回码信息到socket工具窗口
输入参数  : enum OP_RST_INFO enResultCode
输出参数  : 无
返 回 值  : extern void
调用函数  :
被调函数  :
修改历史  :
1.日    期   : 2010年1月21日
作    者   :
修改内容   : 新生成函数
*****************************************************************************/
void api_print_result(enum OP_RST_INFO enResultCode)
{
    switch (enResultCode)
    {
    case S001:puts("初始化成功");
        break;
    case S002:puts("违规记录录入成功");
        break;
    case E001:puts("系统未初始化");
        break;
    case E002:puts("输入时间超出系统允许范围");
        break;
    case E003:puts("输入未归类型超出系统允许范围");
        break;
    case E004:puts("车牌已吊销 操作失败");
        break;
    case E005:puts("输入缴纳金额超出系统允许范围");
        break;
    case E006:puts("缴纳动作无效");
        break;
    case E007:puts("无违规记录 不需要缴纳罚款");
        break;
    case E008:puts("时间参数小于上次操作时间");
        break;
    case E009:puts("违规记录已满");
        break;
    case E010:puts("无违规记录");
        break;
    case E999:puts("系统内部错误");
        break;
    default:puts("无效参数");
        break;
    }
    return;
}


/*****************************************************************************
函 数 名  : api_print_query_info
功能描述  : 打印查询信息到socket工具窗口
输入参数  : QueryResult *pResult
输出参数  : 无
返 回 值  : extern void
调用函数  :
被调函数  :
修改历史  :

1.日    期   : 2010年1月21日
作    者   :
修改内容   : 新生成函数

*****************************************************************************/
void api_print_query_info(QueryResult *pResult)
{
    printf("<<---------- 违规信息%d---------->>\n", pResult->Index);

    printf("违规时间 = %d\n", pResult->Time);

    switch(pResult->Reason)
    {
    case PECCANCY_TYPE_0:printf("违规原因 = 违章停车\n");break;
    case PECCANCY_TYPE_1:printf("违规原因 = 超速\n");break;
    case PECCANCY_TYPE_2:printf("违规原因 = 闯红灯\n");break;
    case PECCANCY_TYPE_3:printf("违规原因 = 超载\n");break;
    case PECCANCY_TYPE_4:printf("违规原因 = 醉酒驾车\n");break;
    default:printf("无效参数\n");break;
    }

    printf("罚款金额 = %d\n", pResult->Fee);

    switch(pResult->PayFlag)
    {
    case STAT_NO_PAY:printf("已缴纳罚款 = 否\n");break;
    case STAT_HAVE_PAY:printf("已缴纳罚款 = 是\n");break;
    default:printf("无效参数\n");break;
    }

    printf("剩余积分 = %d\n", pResult->Score);

    return;
}


/*****************************************************************************
函 数 名  : api_print_pay_info
功能描述  : 打印缴纳信息到socket工具窗口
输入参数  : PayResult  *pResult
输出参数  : 无
返 回 值  : extern void
调用函数  :
被调函数  :
修改历史  :
1.日    期   : 2010年1月21日
作    者   :
修改内容   : 新生成函数
*****************************************************************************/
void api_print_pay_info(PayResult  *pResult)
{
    printf("<<---------- 缴纳信息---------->>\n");
    printf("找零 = %d\n", pResult->ReturnMoney);
    printf("剩余积分 = %d\n", pResult->Score);
    printf("剩余违规记录数 = %d\n", pResult->PeccancyNo);
    printf("剩余罚款金额 = %d\n", pResult->Fee);

    return;
}


/*****************************************************************************
函 数 名  : api_server_start
功能描述  : 启动socket服务端以阻塞的方式接受用户输入
输入参数  : 无
输出参数  : 无
返 回 值  : extern void
调用函数  :
被调函数  :
修改历史  :
1.日    期   : 2010年1月21日
作    者   :
修改内容   : 新生成函数
*****************************************************************************/
void api_server_start(int argc, char* argv[])
{
    printf("系统启动\n");

    while(1)
    {
        char command;
        scanf("%c", &command);

        if(command == 'i')
        {
            opInit();
        }
        else if(command == 'r')
        {
            int Peccancy;
            int Days;
            scanf("%d-%d", &Peccancy, &Days);
            opRecord(Peccancy, Days);
        }
        else if(command == 'q')
        {
            opQuery();
        }
        else if(command == 'p')
        {
            int Money;
            scanf("%d", &Money);
            opPay(Money);
        }
        else
        {
            printf("无效参数\n");
            continue;
        }
    }
    return;
}

