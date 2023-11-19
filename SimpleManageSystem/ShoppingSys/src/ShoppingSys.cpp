#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "api.h"


typedef struct
{
    int num;
    int type;

} ORDER_LIST;

int priceList[GOOD_TYPE_AMOUNT] = {10,120,30}; //价格

ORDER_LIST orderList[MAX_ORDER_NUM]; //购物单
int listNum = 0; // 购物车里面数量
int money = 0; //余额
int score = 0; //积分

/**
 * 系统初始化 r
 */
void reset()
{
    money = INIT_MONEY;
    score = INIT_SCORE;
    listNum = 0;
    api_print_result(S001);
}

/**
 * 订单的加入 o 商品序号-商品数量
 */
void order(int type, int goodNum)
{
    if(listNum == MAX_ORDER_NUM) //购物车已满
    {
        api_print_result(E003);
        return;
    }
    if((type != G_BOOK) && (type != G_CLOTHING) && (type != G_FOOD)) //商品类型参数错误
    {
        api_print_result(E002);
        return;
    }
    if((goodNum <= 0) || (goodNum > MAX_GOOD_NUM)) //商品数量参数错误
    {
        api_print_result(E002);
        return;
    }

    orderList[listNum].num = goodNum;
    orderList[listNum].type = type;
    listNum++;

    api_print_result(S002);
}

/**
 * 订单的取消 c 商品序号-商品数量
 */
void cancel(int type, int goodNum)
{
    if(listNum==0) //订单为空
    {
        api_print_result(E005);
        return;
    }
    if((type != G_BOOK) && (type != G_CLOTHING) && (type != G_FOOD)) //商品类型参数错误
    {
        api_print_result(E002);
        return;
    }
    if((goodNum <= 0) || (goodNum > MAX_GOOD_NUM)) //商品数量参数错误
    {
        api_print_result(E002);
        return;
    }

    for(int i=0; i<listNum; i++)
    {
        if((orderList[i].num==goodNum) && (orderList[i].type==type)) //匹配订单
        {
            for(; i<listNum-1; i++) //没有真正的删除，只是将后面的数据往前移
            {
                orderList[i].num=orderList[i+1].num;
                orderList[i].type=orderList[i+1].type;
            }
            listNum--;
            api_print_result(S003);
            return;
        }
    }

    // 订单不存在
    api_print_result(E004);
    return;
}

/**
 * 结算 b
 */
void balance()
{
    if(listNum == 0) //购物车为空
    {
        api_print_result(E005);
        return;
    }

    //结算计算出优惠方案
    int sumEveryTypeGood[GOOD_TYPE_AMOUNT]= {0}; //每种商品的价格总和
    for(int i=0; i<listNum; i++)
    {
        sumEveryTypeGood[orderList[i].type] += orderList[i].num * priceList[orderList[i].type];
    }

    int billEvery[GOOD_TYPE_AMOUNT][3]= {{0}};

    for(int i=0; i<GOOD_TYPE_AMOUNT; i++)
    {
        billEvery[i][0]=sumEveryTypeGood[i];
    }

    billEvery[0][1] = (int)(billEvery[0][0]*0.9);
    billEvery[0][2] = billEvery[0][0] - billEvery[0][0] / 100 * 18;
    billEvery[1][1] = billEvery[1][0] - billEvery[1][0] / 200 * 40;
    billEvery[2][1] = (int)(billEvery[2][0] * 0.5);
    
    int minCost = INT_MAX; //需要支付的最低花销
    int costScore = 0; //此次花费的积分

     //判断总体方案是否优惠，假设花费最少的一种方式就是每次花出的钱都是最少的，不考虑以后的积分
    for(int i=0; i<3; i++) //食品有三种优惠方式
        for(int j=0; j<2; j++) //服装有两种优惠方式
            for(int k=0; k<2; k++) //书籍有两种优惠方式
            {
                int tempCost = billEvery[0][i] + billEvery[1][j] + billEvery[2][k];
                int tempScoreUsed = 0;

                if(tempCost >= 500) //所有商品单项优惠后总消费金额大于等于500时，可以再使用“积分抵现”或“折上折”优惠
                {
                    if(score >= 120) //积分超过120
                    {
                        if(tempCost*0.8 > tempCost-120)
                        {
                            tempCost -= 120;
                            tempScoreUsed = 120;
                        }
                        else
                        {
                            tempCost = (int)(tempCost*0.8);
                        }
                    }
                    else //积分不到120
                    {
                        if(tempCost*0.8 > tempCost-score)
                        {
                            tempCost -= score;
                            tempScoreUsed = score;
                        }
                        else
                        {
                            tempCost = (int)(tempCost*0.8);
                        }
                    }
                }

                if(tempCost < minCost)
                {
                    minCost = tempCost;
                    costScore = tempScoreUsed;
                }
            }

    if(money < minCost) //余额不足
    {
        api_print_result(E006);
        return;
    }
    else
    {
        //输出消费金额  消费积分  新增积分
        printf("%d\n%d\n%d\n", minCost, costScore, minCost/10);
        money -= minCost;
        score = score - costScore + (minCost/10);

        listNum=0; //成功了清空购物车

        for(int i=0; i<MAX_ORDER_NUM; i++)
        {
            orderList[i].num=0;
            orderList[i].type=0;
        }
    }
}


/**
 * 查询 l 查询类别
 */
void list(int check)
{

    if((check > 1) || (check < 0)) //参数错误
    {
        api_print_result(E002);
        return ;
    }
    if(check == 0) //查询购物卡的余额和积分
    {
        printf("%d\n%d\n",money,score);
        return;
    }
    else if(check == 1) //订单数量以及商品每种的总数
    {
        printf("%d\n",listNum);
        int  food = 0, clothing = 0,book = 0;

        for(int i=0; i<listNum; i++)
        {
            if(orderList[i].type == G_FOOD)
            {
                food += orderList[i].num;
            }
            else if(orderList[i].type == G_CLOTHING)
            {
                clothing += orderList[i].num;
            }
            else if(orderList[i].type == G_BOOK)
            {
                book += orderList[i].num;
            }
        }
        printf("%d\n%d\n%d\n",food,clothing,book);
    }
}

int main()
{
    char input[BUFSIZ];

    //考生不需要关注输入命令格式的合法性
    while(gets_s(input))
    {
        if(strlen(input) == 0) //读入空行
        {
            continue;
        }
        else if(input[0] == 'r') //系统初始化
        {
            reset();
        }
        else if(input[0] == 'o') //挑选商品
        {
            int goodSeq; //商品序号
            int goodNum; //商品数量
            char ch;
            sscanf_s(input,"%c %d-%d\n",&ch,sizeof(char),&goodSeq,&goodNum); //注意此处用法
            order(goodSeq,goodNum);
        }
        else if(input[0] == 'c') //删除商品订单记录
        {
            int goodSeq; //商品序号
            int goodNum; //商品数量
            char ch;
            sscanf_s(input,"%c %d-%d\n",&ch,sizeof(char),&goodSeq,&goodNum); //注意此处用法
            cancel(goodSeq,goodNum);
        }
        else if(input[0] == 'b') //结算
        {
            balance();
        }
        else if(input[0] == 'l') //查询
        {
            int queryType; //查询类别
            char ch;
            sscanf_s(input, "%c %d",&ch, sizeof(char), &queryType);
            list(queryType);
        }
        else if(input[0] == 'e') //结束
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}