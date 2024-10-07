#include <stdio.h>
#include "api.h"

#define OJ_OUTPUT

void api_print_result(enum OP_RST_INFO enResultCode)
{
    switch (enResultCode)
    {
    case S001:
#ifdef OJ_OUTPUT
        puts("S001");
#else
        puts("初始化成功");
#endif
        break;

    case S002:
#ifdef OJ_OUTPUT
        puts("S002");
#else
        puts("订单已经加入到购物车");
#endif
        break;

    case S003:
#ifdef OJ_OUTPUT
        puts("S003");
#else
        puts("订单已从购物车中删除");
#endif
        break;

    case E001:
#ifdef OJ_OUTPUT
        puts("E001");
#else
        puts("非法命令");
#endif
        break;

    case E002:
#ifdef OJ_OUTPUT
        puts("E002");
#else
        puts("参数错误");
#endif
        break;

    case E003:
#ifdef OJ_OUTPUT
        puts("E003");
#else
        puts("购物车已满");
#endif
        break;

    case E004:
#ifdef OJ_OUTPUT
        puts("E004");
#else
        puts("待删除的订单不存在");
#endif
        break;

    case E005:
#ifdef OJ_OUTPUT
        puts("E005");
#else
        puts("购物车中没有商品订单");
#endif
        break;

    case E006:
#ifdef OJ_OUTPUT
        puts("E006");
#else
        puts("购物卡余额或积分不足");
#endif
        break;

    default:puts("无效参数");
        break;
    }
    return;
}

