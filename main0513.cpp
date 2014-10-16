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

/* �����ַ�����ջ */
typedef struct
{
    int stacksize;
    char *base;
    char *top;
} Stack;

/* ��������ջ */
typedef struct
{
    int stacksize;
    int *base;
    int *top;
} Stack2;

/* ȫ�ֱ��� */
Stack OPTR;/* ���������ջ*/
Stack2 OPND; /* ���������ջ */
char expr[255] = ""; /* ��ű��ʽ�� */
char *ptr = expr;

int InitStack(Stack *s) /*���������ջ*/
{
    s->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!s->base) return ERROR;
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
    return OK;
}
int InitStack2(Stack2 *s) /*���������ջ*/
{
    s->base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!s->base) return ERROR;
    s->stacksize=STACK_INIT_SIZE;
    s->top=s->base;
    return OK;
}

int In(char ch) /*�ж��ַ��Ƿ���������������������1*/
{
    return(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#');
}
int Push(Stack *s,char ch) /*�����ջ����chΪ�µ�ջ��Ԫ��*/
{
    *s->top=ch;
    s->top++;
    return 0;
}
int Push2(Stack2 *s,int ch)/*������ջ����chΪ�µ�ջ��Ԫ�� */
{
    *s->top=ch;
    s->top++;
    return 0;
}
char Pop(Stack *s) /*ɾ�������ջs��ջ��Ԫ�أ���p������ֵ*/
{
    char p;
    s->top--;
    p=*s->top;
    return p;
}
int Pop2(Stack2 *s)/*ɾ��������ջs��ջ��Ԫ�أ���p������ֵ */
{
    int p;
    s->top--;
    p=*s->top;
    return p;
}
char GetTop(Stack s)/*��p���������ջs��ջ��Ԫ��*/
{
    char p=*(s.top-1);
    return p;
}
int GetTop2(Stack2 s) /*��p���ز�����ջs��ջ��Ԫ��*/
{
    int p=*(s.top-1);
    return p;
}
/* �ж����������Ȩ����������Ȩ�ߵ� */
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
    /* iΪ����array�ĺ�� */
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
    /* jΪ����array���ݱ� */
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
    return (array[7*i+j]); /* ��������� */
}
/*�������� */
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
int num(int n)/*���ز������ĳ���*/
{
    string str_num = to_string(n);
    return str_num.length();
    //char p[10];
    //itoa(n,p,10);
    //n=strlen(p);
    //return n;
}
int EvalExpr()/*��Ҫ�������� */
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
            m=atoi(ptr);/*ȡ�ַ���ǰ������ֶ�*/
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
    printf("��������ȷ�ı��ʽ:");
    do
    {
        gets(expr);
    }
    while(!*expr);
    InitStack(&OPTR); /* ��ʼ�������ջ */
    Push(&OPTR,'#'); /* ��#ѹ�������ջ */
    InitStack2(&OPND); /* ��ʼ��������ջ */
    printf("���ʽ���Ϊ:%d\n", EvalExpr());
    return 0;
}




