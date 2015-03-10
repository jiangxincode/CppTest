#include <iostream>
#include <string>

using namespace std;

const int maxnum=5;
class goodslist
{
public:
    int num;
    int type;

};
goodslist List[maxnum];//购物单
int Listnum=0;// 购物车里面数量
int price[3]= {10,120,30}; //价格
int money=0;
int score=0;
int costscore=0;

void init()// 初始化
{
    money=3000;
    score=150;
    cout<<"S001"<<endl;
}


void choice(char type,char goodnum[])// 订单的加入
{
    if(Listnum==5)
    {
        cout<<"E003"<<endl;
        return;
    }

    int numin=atoi(goodnum);

    if((type-'0')>2||(type-'0')<0||numin<=0||numin>100)
    {
        cout<<"E002"<<endl;
        return;
    }

    List[Listnum].num=numin;
    List[Listnum].type=type-'0';
    cout<<"S002"<<endl;
    Listnum++;
}

void cancel(char type,char goodnum[])// 订单的取消
{
    if(Listnum==0)//订单为空
    {
        cout<<"E005"<<endl;
        return;
    }

    int numin=atoi(goodnum);

    if((type-'0')>2||(type-'0')<0||numin<=0||numin>100)//不在范围内
    {
        cout<<"E002"<<endl;
        return;
    }

//订单的查询删除  这里设置有一个变量判断
    for(int i=0; i<Listnum; i++)
    {
        //如果能够匹配订单
        if(List[i].num==numin&&List[i].type==(type-'0'))
        {
            //删除的实现  只有移动了；
            for(; i<Listnum-1; i++) //
            {
                List[i].num=List[i+1].num;
                List[i].type=List[i+1].type;
            }

            Listnum--;
            cout<<"S003"<<endl;
            return;
        }
    }

// 订单不存在  上面执行完了还没有
    cout<<"E004"<<endl;
    return;
}


void check(char temp)// 命令查询
{
    int check=temp-'0';

    if(check>1||check<0)
    {
        cout<<"E002"<<endl;
        return ;
    }

    if(check==0)//查询购物卡 余额 积分
    {
        cout<<money<<endl<<score<<endl;
        return;
    }

    if(check==1)//订单数量以及商品没中的总数
    {
        cout<<Listnum<<endl;
        int  food=0,cloth=0,book=0;

        for(int i=0; i<Listnum; i++)
        {
            if(List[i].type==0)
            {
                food=food+List[i].num;
            }

            if(List[i].type==1)
            {
                cloth=cloth+List[i].num;
            }

            if(List[i].type==2)
            {
                book=book+List[i].num;
            }
        }

        cout<<food<<endl<<cloth<<endl<<book<<endl;
    }
}

//结算 购物
void buygoods()
{
    //购物车为空
    if(Listnum==0)
    {
        cout<<"E005"<<endl;
        return;
    }

//结算计算出优惠方案
    int sumevery[3]= {0};

    for(int i=0; i<Listnum; i++)
    {
        sumevery[List[i].type]+=List[i].num*price[List[i].type];//求和   因为type和价格对应
    }

    int billever[3][3]= {{0}};

    for(int i=0; i<3; i++)
    {
        billever[i][0]=sumevery[i];
    }

    billever[0][1]=(int)(billever[0][0]*0.9);
    billever[0][2]=billever[0][0]-billever[0][0]/100*18;
    billever[1][1]=billever[1][0]-billever[1][0]/200*40;
    billever[2][1]=(int)(billever[2][0]*0.5);
    //判断总体方案是否优惠
    int paymoney=0x7fffffff;//需要支付的钱
    int count=0,jifenshiyong=0;

    for(int i=0; i<3; i++)
        for(int j=0; j<2; j++)
            for(int k=0; k<2; k++)
            {
                count=billever[0][i]+billever[1][j]+billever[2][k];

                if(count>=500)
                {
                    //付款这个怎么比较哪个更好呢？  就是付钱出去最少？？？ 不考虑以后积分
                    if(score>=120)//积分120
                    {
                        if(count*0.8>count-120)
                        {
                            count-=120;
                            jifenshiyong=120;
                        }
                        else
                        {
                            count=count*0.8;
                        }
                    }
                    else//积分没有120
                    {
                        if(count*0.8>count-score)
                        {
                            count-=score;
                            jifenshiyong=score;
                        }
                        else
                        {
                            count=count*0.8;
                        }
                    }
                }

                if(count<paymoney)
                {
                    paymoney=count;
                    costscore=jifenshiyong;
                }
            }//三个for循环的括号

    //以上处理完了最后的结账的总数
    if(money<paymoney)
    {
        cout<<"E006"<<endl;
        return;
    }
    else
    {
        //输出消费金额  消费积分  新增积分
        cout<<paymoney<<endl<<costscore<<endl<<paymoney/10<<endl;
        money-=paymoney;
        score=score-costscore+(paymoney/10);
        //成功了清空购物车
        Listnum=0;

        for(int i=0; i<5; i++)
        {
            List[i].num=0;
            List[i].type=0;
        }
    }
}




int main()
{
    char input[10]="";

    //下面进行输入判断；
    while(gets(input))
    {
        // 输入后就判断命令问题
        //因为命令合法性都不需要考虑  所以对于正确性的检测不必
        char goodnum[4]="";

        switch(input[0])
        {
        case 'r':
            init();
            break;

        case 'o':// 订单加入
            goodnum[0]=input[4],goodnum[1]=input[5],goodnum[2]=input[6];
            choice(input[2],goodnum);
            break;

        case 'c'://订单取消
            goodnum[0]=input[4],goodnum[1]=input[5],goodnum[2]=input[6];
            cancel(input[2],goodnum);
            break;

        case 'b'://买
            buygoods();
            break;

        case 'l'://查询
            check(input[2]);
            break;

        case 'e':// 结束
            return 0;

        default:
            break;
        }
    }
}







