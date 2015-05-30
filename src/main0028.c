//下面给出的是用两个栈算法实现的程序的源代码：
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define MAXSIZE 100    //定义宏，数组最大长度为100

int static level(char op);//声明level函数
double static calvalue(double od1,double od2,char tempop); //声明calvalue函数

double static calculate(char str[])
{
    struct             //用结构体创建操作符栈
    {
        char data[MAXSIZE];//用来存放操作符
        int top;
    } op;
    struct          //用结构体创建值栈
    {
        double data[MAXSIZE];//用来存放操作数
        int top;
    } od;
    char ch;
    char tempch[20];//声明临时数组存储子串
    int j=0,t;
    double d;
    double od1,od2;//存储值栈依次pop出来的操作数
    char tempop;
    int length=strlen(str);//计算str数组的长度
    op.top=-1;//初始化操作符栈，令下标为-1
    od.top=-1;//初始化值栈

    while(j<length)
    {
        ch=str[j];

        if((ch>='0' && ch<='9') ||ch=='.')//若为数值或小数点
        {
            d=0;
            t=0;

            while((ch>='0' && ch<='9') ||ch=='.')//截取子串
            {
                tempch[t]=ch;
                t++;//赋值给临时数组
                j++;
                ch=str[j];
            }

            tempch[t]='\0';
            d=atof(tempch);//将子串转化成double类型的数
            od.top++;
            od.data[od.top]=d;//入值栈
        }
        //对操作符操作
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%' || ch == '(' || ch == ')')
        {
            if(ch=='(')//如果为(，直接进栈
            {
                op.top++;
                op.data[op.top]=ch;//进栈操作
            }
            else if(ch==')')//如果为),一直出栈直到遇到(
            {
                while(level(op.data[op.top])!=-1)//若栈顶元素不为(,进入while循环
                {
                    od2=od.data[od.top];
                    od.top--;
                    od1=od.data[od.top];
                    tempop=op.data[op.top];
                    op.top--;
                    od.data[od.top]=calvalue(od1,od2,tempop);//计算出结果后入值栈

                    if(op.top==-1)
                    {
                        break;    //如果操作符栈为空，跳出循环
                    }
                }

                op.top--;//左括号pop出来
            }
            else if(op.top==-1)//如果栈为空，直接进栈
            {
                op.top++;
                op.data[op.top]=ch;//进栈操作
            }
            //如果所扫描的操作符优先等级比栈顶元素高，直接进栈
            else if(level(ch)>level(op.data[op.top]))
            {
                op.top++;
                op.data[op.top]=ch;//进栈操作
            }
            else
            {
                //如果所扫描的操作符优先等级没有栈顶元素高，
                //一直出栈直到比栈顶元素优先级高
                while(level(ch)<=level(op.data[op.top]))
                {
                    od2=od.data[od.top];
                    od.top--;
                    od1=od.data[od.top];
                    tempop=op.data[op.top];
                    op.top--;
                    od.data[od.top]=calvalue(od1,od2,tempop);//计算结果后入值栈

                    if(op.top==-1)
                    {
                        break;    //如果栈为空，跳出循环
                    }
                }

                op.top++;
                op.data[op.top]=ch;//比栈顶元素优先级高，入操作符栈
            }

            j++;//str下标加1，向后扫描
        }
    }

    while(op.top!=-1)//扫描结束后如果操作符栈不为空，出栈直至为空
    {
        od2=od.data[od.top];
        od.top--;
        od1=od.data[od.top];
        tempop=op.data[op.top];
        op.top--;
        od.data[od.top]=calvalue(od1,od2,tempop);//计算结果后入值栈
    }

    return od.data[od.top];//将结束后值栈中的数pop出来，即为计算结果
}
int static level(char op)//判断操作符优先等级
{
    if(op == '+' || op == '-')//若为+、-，等级为1
    {
        return 1;
    }
    else if(op == '*' || op == '/' || op == '%')
    {
        return 2;    //若为*、/、%,等级为2
    }
    else if(op == '(')
    {
        return -1 ;    //若为(,等级为-1
    }
    else
    {
        return -3;    //其他等级为-3；
    }
}
double static calvalue(double od1,double od2,char tempop)//计算
{
    switch(tempop)
    {
    case '+':
        return od1 + od2;//计算加法

    case '-':
        return od1 - od2;//计算减法

    case '*':
        return od1 * od2;//计算乘法

    case '/':
        return od1 / od2;//计算除法

    case '%':
        return fmod(od1,od2);//求余
    }

    return 0;
}
int main0028()
{
    char str[MAXSIZE];//定义str数组存放数学表达式
    printf("输入算术表达式：\n");
    gets(str);       //从控制台输入算数表达式
    printf("结果是：%lf\n",calculate(str));//调用calculate函数，计算结果
    return 0;
}
