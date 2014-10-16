#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;


#define OK 1
#define ERROR -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 20

/* 定义字符类型栈 */
typedef struct
{
    int stacksize;
    char *base;
    char *top;
} Stack;

/* 定义整型栈 */
typedef struct
{
    int stacksize;
    int *base;
    int *top;
} Stack2;

/* 全局变量 */
Stack OPTR;/* 定义运算符栈*/
Stack2 OPND; /* 定义操作数栈 */
char expr[255] = ""; /* 存放表达式串 */
char *ptr = expr;

int InitStack(Stack *s) /*构造运算符栈*/
{
    s->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!s->base) return ERROR;
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
    return OK;
}
int InitStack2(Stack2 *s) /*构造操作数栈*/
{
    s->base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!s->base) return ERROR;
    s->stacksize=STACK_INIT_SIZE;
    s->top=s->base;
    return OK;
}

int In(char ch) /*判断字符是否是运算符，运算符即返回1*/
{
    return(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#');
}
int Push(Stack *s,char ch) /*运算符栈插入ch为新的栈顶元素*/
{
    *s->top=ch;
    s->top++;
    return 0;
}
int Push2(Stack2 *s,int ch)/*操作数栈插入ch为新的栈顶元素 */
{
    *s->top=ch;
    s->top++;
    return 0;
}
char Pop(Stack *s) /*删除运算符栈s的栈顶元素，用p返回其值*/
{
    char p;
    s->top--;
    p=*s->top;
    return p;
}
int Pop2(Stack2 *s)/*删除操作数栈s的栈顶元素，用p返回其值 */
{
    int p;
    s->top--;
    p=*s->top;
    return p;
}
char GetTop(Stack s)/*用p返回运算符栈s的栈顶元素*/
{
    char p=*(s.top-1);
    return p;
}
int GetTop2(Stack2 s) /*用p返回操作数栈s的栈顶元素*/
{
    int p=*(s.top-1);
    return p;
}
/* 判断运算符优先权，返回优先权高的 */
char Precede(char c1,char c2)
{
    int i=0,j=0;
    static char array[49]=
    {
        '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '<', '>', '>',
        '>', '>', '>', '>', '<', '>', '>',
        '<', '<', '<', '<', '<', '=', '!',
        '>', '>', '>', '>', '!', '>', '>',
        '<', '<', '<', '<', '<', '!', '='
    };
    switch(c1)
    {
    /* i为下面array的横标 */
    case '+' :
        i=0;
        break;
    case '-' :
        i=1;
        break;
    case '*' :
        i=2;
        break;
    case '/' :
        i=3;
        break;
    case '(' :
        i=4;
        break;
    case ')' :
        i=5;
        break;
    case '#' :
        i=6;
        break;
    }
    switch(c2)
    {
    /* j为下面array的纵标 */
    case '+' :
        j=0;
        break;
    case '-' :
        j=1;
        break;
    case '*' :
        j=2;
        break;
    case '/' :
        j=3;
        break;
    case '(' :
        j=4;
        break;
    case ')' :
        j=5;
        break;
    case '#' :
        j=6;
        break;
    }
    return (array[7*i+j]); /* 返回运算符 */
}
/*操作函数 */
int Operate(int a,char op,int b)
{
    switch(op)
    {
    case '+' :
        return (a+b);
    case '-' :
        return (a-b);
    case '*' :
        return (a*b);
    case '/' :
        return (a/b);
    }
    return 0;
}
int num(int n)/*返回操作数的长度*/
{
    string str_num = to_string(n);
    return str_num.length();
    //char p[10];
    //itoa(n,p,10);
    //n=strlen(p);
    //return n;
}
int EvalExpr()/*主要操作函数 */
{
    char c,theta;
    //char x;
    int n,m;
    int a,b;
    c = *ptr++;
    while(c!='#'||GetTop(OPTR)!='#')
    {
        if(!In(c))
        {
            if(!In(*(ptr-1))) ptr=ptr-1;
            m=atoi(ptr);/*取字符串前面的数字段*/
            n=num(m);
            Push2(&OPND,m);
            ptr=ptr+n;
            c=*ptr++;
        }
        else
            switch(Precede(GetTop(OPTR),c))
            {
            case '<':
                Push(&OPTR,c);
                c = *ptr++;
                break;
            case '=':
                //x=Pop(&OPTR);
                c = *ptr++;
                break;
            case '>':
                theta=Pop(&OPTR);
                b=Pop2(&OPND);
                a=Pop2(&OPND);
                Push2(&OPND,Operate(a,theta,b));
                break;
            }
    }
    return GetTop2(OPND);
}
int main0513()
{
    printf("请输入正确的表达式:");
    do
    {
        gets(expr);
    }
    while(!*expr);
    InitStack(&OPTR); /* 初始化运算符栈 */
    Push(&OPTR,'#'); /* 将#压入运算符栈 */
    InitStack2(&OPND); /* 初始化操作数栈 */
    printf("表达式结果为:%d\n", EvalExpr());
    return 0;
}




