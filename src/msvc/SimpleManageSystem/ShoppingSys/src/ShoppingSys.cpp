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

int priceList[GOOD_TYPE_AMOUNT] = {10,120,30}; //�۸�

ORDER_LIST orderList[MAX_ORDER_NUM]; //���ﵥ
int listNum = 0; // ���ﳵ��������
int money = 0; //���
int score = 0; //����

/**
 * ϵͳ��ʼ�� r
 */
void reset()
{
    money = INIT_MONEY;
    score = INIT_SCORE;
    listNum = 0;
    api_print_result(S001);
}

/**
 * �����ļ��� o ��Ʒ���-��Ʒ����
 */
void order(int type, int goodNum)
{
    if(listNum == MAX_ORDER_NUM) //���ﳵ����
    {
        api_print_result(E003);
        return;
    }
    if((type != G_BOOK) && (type != G_CLOTHING) && (type != G_FOOD)) //��Ʒ���Ͳ�������
    {
        api_print_result(E002);
        return;
    }
    if((goodNum <= 0) || (goodNum > MAX_GOOD_NUM)) //��Ʒ������������
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
 * ������ȡ�� c ��Ʒ���-��Ʒ����
 */
void cancel(int type, int goodNum)
{
    if(listNum==0) //����Ϊ��
    {
        api_print_result(E005);
        return;
    }
    if((type != G_BOOK) && (type != G_CLOTHING) && (type != G_FOOD)) //��Ʒ���Ͳ�������
    {
        api_print_result(E002);
        return;
    }
    if((goodNum <= 0) || (goodNum > MAX_GOOD_NUM)) //��Ʒ������������
    {
        api_print_result(E002);
        return;
    }

    for(int i=0; i<listNum; i++)
    {
        if((orderList[i].num==goodNum) && (orderList[i].type==type)) //ƥ�䶩��
        {
            for(; i<listNum-1; i++) //û��������ɾ����ֻ�ǽ������������ǰ��
            {
                orderList[i].num=orderList[i+1].num;
                orderList[i].type=orderList[i+1].type;
            }
            listNum--;
            api_print_result(S003);
            return;
        }
    }

    // ����������
    api_print_result(E004);
    return;
}

/**
 * ���� b
 */
void balance()
{
    if(listNum == 0) //���ﳵΪ��
    {
        api_print_result(E005);
        return;
    }

    //���������Żݷ���
    int sumEveryTypeGood[GOOD_TYPE_AMOUNT]= {0}; //ÿ����Ʒ�ļ۸��ܺ�
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
    
    int minCost = INT_MAX; //��Ҫ֧������ͻ���
    int costScore = 0; //�˴λ��ѵĻ���

     //�ж����巽���Ƿ��Żݣ����軨�����ٵ�һ�ַ�ʽ����ÿ�λ�����Ǯ�������ٵģ��������Ժ�Ļ���
    for(int i=0; i<3; i++) //ʳƷ�������Żݷ�ʽ
        for(int j=0; j<2; j++) //��װ�������Żݷ�ʽ
            for(int k=0; k<2; k++) //�鼮�������Żݷ�ʽ
            {
                int tempCost = billEvery[0][i] + billEvery[1][j] + billEvery[2][k];
                int tempScoreUsed = 0;

                if(tempCost >= 500) //������Ʒ�����Żݺ������ѽ����ڵ���500ʱ��������ʹ�á����ֵ��֡��������ۡ��Ż�
                {
                    if(score >= 120) //���ֳ���120
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
                    else //���ֲ���120
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

    if(money < minCost) //����
    {
        api_print_result(E006);
        return;
    }
    else
    {
        //������ѽ��  ���ѻ���  ��������
        printf("%d\n%d\n%d\n", minCost, costScore, minCost/10);
        money -= minCost;
        score = score - costScore + (minCost/10);

        listNum=0; //�ɹ�����չ��ﳵ

        for(int i=0; i<MAX_ORDER_NUM; i++)
        {
            orderList[i].num=0;
            orderList[i].type=0;
        }
    }
}


/**
 * ��ѯ l ��ѯ���
 */
void list(int check)
{

    if((check > 1) || (check < 0)) //��������
    {
        api_print_result(E002);
        return ;
    }
    if(check == 0) //��ѯ���￨�����ͻ���
    {
        printf("%d\n%d\n",money,score);
        return;
    }
    else if(check == 1) //���������Լ���Ʒÿ�ֵ�����
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

    //��������Ҫ��ע���������ʽ�ĺϷ���
    while(gets_s(input))
    {
        if(strlen(input) == 0) //�������
        {
            continue;
        }
        else if(input[0] == 'r') //ϵͳ��ʼ��
        {
            reset();
        }
        else if(input[0] == 'o') //��ѡ��Ʒ
        {
            int goodSeq; //��Ʒ���
            int goodNum; //��Ʒ����
            char ch;
            sscanf_s(input,"%c %d-%d\n",&ch,sizeof(char),&goodSeq,&goodNum); //ע��˴��÷�
            order(goodSeq,goodNum);
        }
        else if(input[0] == 'c') //ɾ����Ʒ������¼
        {
            int goodSeq; //��Ʒ���
            int goodNum; //��Ʒ����
            char ch;
            sscanf_s(input,"%c %d-%d\n",&ch,sizeof(char),&goodSeq,&goodNum); //ע��˴��÷�
            cancel(goodSeq,goodNum);
        }
        else if(input[0] == 'b') //����
        {
            balance();
        }
        else if(input[0] == 'l') //��ѯ
        {
            int queryType; //��ѯ���
            char ch;
            sscanf_s(input, "%c %d",&ch, sizeof(char), &queryType);
            list(queryType);
        }
        else if(input[0] == 'e') //����
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