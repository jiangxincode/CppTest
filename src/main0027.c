//下面给出的是用中缀转后缀算法实现的程序的源代码：
//参考Test main0524.cpp
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define MAXSIZE 100 //定义宏，数组最大长度为100
//函数实现中缀转后缀，将存储数学表达式的数组str传参进来，exp存储后缀表达式
void trans(char str[],char exp[])
{
    struct
    {
        char data[MAXSIZE];//用来存放操作符
        int top;//数组下标
    } op; //用结构体创建操作符栈
    char ch;
    int i=0,j=0,tempi=0;
    op.top=-1;//给操作符栈初始化，令下标为-1

    while(ch!='\0')
    {
        ch=str[i]; //取str数组的第i个元素赋值给ch

        if((ch>='0'&& ch<='9') || ch=='.')//对数值操作
        {
            tempi=i;//若ch为数字或小数点，将其下标值赋给临时下标tempi

            //依次向后扫描str数组，若一直为数字，跳入while循环
            while((ch>='0' && ch<= '9') || ch == '.')
            {
                tempi++;
                exp[j]=ch;//将数字存入exp数组中
                j++;
                ch=str[tempi];//取str数组中下标为tempi的元素赋给ch
            }

            exp[j]='#';
            j++;//用#做分隔符，将数值分隔开
            i=tempi;//跳出循环，将此时的tempi赋给i,继续向后扫描
        }
        //对操作符操作
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%' || ch == '(' || ch == ')')
        {
            int level(char op);//声明level函数

            if(ch=='(')//如果为(，直接进栈
            {
                op.top++;
                op.data[op.top]=ch;//进栈操作
            }
            else if(ch==')')
            {
                //如果为),一直出栈直到遇到(
                while(level(op.data[op.top])!=-1)//若栈顶元素不为(,进入while循环
                {
                    exp[j]=op.data[op.top];//操作符出栈，存入exp数组中
                    op.top--;
                    j++;

                    if(op.top==-1)
                    {
                        break;    //如果栈为空，跳出循环
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
                    exp[j]=op.data[op.top];//出栈存入exp数组中
                    op.top--;
                    j++;

                    if(op.top==-1)
                    {
                        break;    //如果栈为空，跳出循环
                    }
                }

                op.top++;
                op.data[op.top]=ch;//比栈顶元素优先级高，入栈
            }

            i++;//str下标加1，向后扫描
        }
    }

    while(op.top!=-1)//扫描结束后如果操作符栈不为空，出栈直至为空
    {
        exp[j]=op.data[op.top];//出栈存入exp数组中
        op.top--;
        j++;
    }

    exp[j]='\0';//赋\0结束exp字符数组
}
int level(char op)//判断操作符优先等级
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
double calvalue(double od1,double od2,char tempop)//计算
{
    switch(tempop)
    {
    case '+':
        return od1 + od2; //计算加法

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
double calculate(char exp[])//计算后缀表达式
{
    struct  //用结构体创建值栈
    {
        double data[MAXSIZE]; //存储数值
        int top;
    } od;
    double d;  //声明d变量存储数值
    double od1,od2; //存储值栈依次pop出来的操作数
    char ch;
    char tempch[20]; //声明临时数组存储子串
    int j=0,t;
    int length=strlen(exp);//计算exp数组的长度
    od.top=-1; //初始化值栈，令下标为-1

    while(j<length)
    {
        ch=exp[j];//提取exp中第j个元素

        if(ch!='+' && ch!='-' && ch!= '*' && ch!='/' && ch!='%')
        {
            //如果为数字或小数点
            d=0;
            t=0;

            while((ch>='0' && ch<='9') ||ch=='.')
            {
                tempch[t]=ch;
                t++;//依次存放到临时数组中
                j++;
                ch=exp[j];
            }

            tempch[t]='\0';//结束tempch数组
            d=atof(tempch);//将子串转化成double类型的数
            od.top++;
            od.data[od.top]=d;//入值栈
        }
        else                   //若为操作符，从值栈中pop出两个数计算
        {
            od2=od.data[od.top];
            od.top--;//先出栈的赋给od2
            od1=od.data[od.top];         //后出栈的赋给od1
            od.data[od.top]=calvalue(od1,od2,ch); //计算出结果后再入栈
        }

        j++;
    }

    return od.data[od.top];//将结束后值栈中的数pop出来，即为计算结果
}
int main0027()
{
    char str[MAXSIZE],exps[MAXSIZE];  //定义两个数组
    printf("请输入算术表达式：\n");
    gets(str);                        //从控制台输入算数表达式
    printf("表达式为： %s\n",str);
    trans(str,exps);                  //调用trans函数，得到后缀表达式
    printf("后缀表达式：%s\n",exps);
    printf("结果为：%lf\n",	calculate(exps));	//调用calculate函数，计算结果
    return 0;
}

