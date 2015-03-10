#ifndef __API_H__
#define __API_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define INIT_MONEY 3000 //初始余额
#define INIT_SCORE 150 //初始积分
#define MAX_ORDER_NUM 5 //最大商品订单条数
#define MAX_GOOD_NUM 100 //最大商品数量
#define GOOD_TYPE_AMOUNT 3 //可供选择的商品种类


//返回操作信息
enum OP_RST_INFO
{
    S001,        //初始化成功
    S002,        //订单已经加入到购物车
    S003,        //订单已从购物车中删除

    E001,        //非法命令
    E002,        //参数错误
    E003,        //购物车已满
    E004,        //待删除的订单不存在
    E005,        //购物车中没有商品订单
    E006,        //购物卡余额或积分不足
};

//商品种类
enum GOOD_TYPE
{
    G_FOOD,      //食品
    G_CLOTHING,  //服装
    G_BOOK,      //书籍
};

//优惠方案
enum DISCOUNT_TYPE
{
    D_NO_DISCOUNT, //无优惠
    D_DISCOUNT, //打折
    D_REDUCE, //直减
};

void api_print_result(OP_RST_INFO enResultCode);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __API_H__ */