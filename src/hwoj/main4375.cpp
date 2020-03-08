/**
 * 一元多项式乘法运算和化简
 * 一元多项式乘法运算和化简
 * 编程实现如下功能：对两个输入的一元多项式，进行多项式乘法运算，输出结果一元多项式，要求结果中除单项式外不再含乘法，并经过化简（同类项合并，并按指数降序排序）。
 *
 * 说明：
 * 1、多项式由若干个单项式组成，单项式之间为加、减（+,-）关系。
 * 2、单项式指数字与字母幂的乘积构成的代数式。对一元多项式，字母只有一种。
 * 3、多项式乘法：一个多项式的每一项分别乘以另一个多项式每一项（系数相乘，指数相加），再把所得的积相加减。
 * 4、同类项合并指将多项式中指数相同的单项式，系数经过加减求和，合并为一个单项式。按指数降序指多项式中，单项式按指数从大到小顺序相连。
 *
 * 格式说明
 * 一元多项式输入输出时以字符串形式表示，格式如下
 * 1、单项式之间用单个加减运算符相连，运算符：+,-
 * 2单项式由系数、字母、指数标识符、指数依次直接相连组成，各部分均不能省略。
 * 系数：只由若干0到9数字字符组成（系数不等于0，且不以0开头）
 * 字母：X
 * 指数标识符：^
 * 指数：只由若干0到9数字字符组成（指数可等于0，不等于0时不以0开头）
 *
 * 其他约定
 * 输入不为空串，输出若为0则以空串表示
 * 字符串中除以上字符，不包含空格等其他字符，字符串尾部以’\0’结束
 * 多项式中第一个单项式前加运算时省略+符号,减运算时有-符号
 *
 * 注意：输入多项式符合上述格式，无需检查；输出多项式格式由考生程序保证
 *
 * 规格:
 * 输入多项式满足如下规格，考生程序无需检查：
 * –0<单项式系数<=1000
 * –0<=单项式指数<=3000
 * –单项式个数不限制，但相乘运算和同类项合并处理后，单项式的系数小于65535。
 *
 * 示例:
 * 例一
 * 输入：
 *  "7X^4"
 *  "-7X^4"
 * 输出：
 *  "-49X^8"
 *
 * 例二
 * 输入：
 *  "7X^4-5X^3+3X^3+1X^0"
 *  "-7X^4+5X^3-3X^3+3X^3+1X^0"
 * 输出：
 *  "-49X^8+49X^7-10X^6+3X^3+1X^0"
 *
 */


/******************************************************************************************************

 Description : 对两个输入的一元多项式，进行多项式乘法运算，输出结果一元多项式
 Prototype : void PolynomialMultiple (char* InputString1, char* InputString2, char* OutputString)
 Input Param : char* InputString1 乘数1多项式字符串
               char* InputString2 乘数2多项式字符串
 Output Param : char* OutputString 乘积多项式字符串
 Return Value : void
 ********************************************************************************************************/
//review
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>


#define OK 1
#define Error 0

typedef struct Node
{
    int top;
    int front;
    struct Node* next;
} Node;

int InitList(Node **L)
{
    *L=(Node*)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
        return Error;
    (*L)->next=NULL; /* 指针域为空 */
    return OK;
}

int insert_list(Node** link_list,int para_top,int para_front)
{
    int j=1;
    Node* p;
    Node* insert_node = NULL;
    Node* pNext;
    p = *link_list;
    pNext = p->next;
    while(pNext != NULL)
    {
        if (pNext->top == para_top)
        {
            pNext->front += para_front;
            return OK;
        }
        else if (pNext->top > para_top)
        {
            p = pNext;
            pNext = p->next;
        }
        else
        {
            insert_node = (Node*)malloc(sizeof(Node));
            insert_node->next = pNext;
            insert_node->top = para_top;
            insert_node->front = para_front;
            p->next = insert_node;
            return OK;
        }
    }
    insert_node = (Node*)malloc(sizeof(Node));
    insert_node->next = pNext;
    insert_node->top = para_top;
    insert_node->front = para_front;
    p->next = insert_node;
    return OK;
}



int insertData(char* InputString,Node** pHeadInput)

{
    if (NULL==InputString || NULL==pHeadInput)
    {
        return OK;
    }
    char* pInput = InputString;
    size_t len = strlen(InputString);
    int para_top,para_front;
    unsigned int i,j,k;
    int flag = 1;
    for(i=0; i<len; i++)
    {
        if (pInput[i]=='X' && pInput[i+1]=='^')
        {
            // 获取指数
            para_top=0,para_front=0;
            for(j=i+2; j<len; j++)
            {
                if (pInput[j]>='0' && pInput[j]<='9')
                {
                    para_top = para_top*10 + pInput[j]-'0';
                }
                else
                {
                    break;
                }
            }
            //获取系数
            k=i-1;
            while (k>=0 && (pInput[k]>='0'&& pInput[k]<='9'))
            {
                k--;
            }
            if (k<0)
            {
                flag = 1;
            }
            else
            {
                if (pInput[k] == '-')
                {
                    flag = -1;
                }
                else
                {
                    flag = 1;
                }
            }
            k++;
            for (; k<i; k++)
            {
                if (pInput[k]>='0' && pInput[j]<='9')
                {
                    para_front = para_front*10 + pInput[k]-'0';
                }
            }
            insert_list(pHeadInput,para_top,para_front*flag);
        }
    }
    return OK;
}



Node* getData(Node* pHeadInput)
{
    if (NULL == pHeadInput)
    {
        return NULL;
    }
    Node* data = (Node*)malloc(sizeof(Node));
    data->front = pHeadInput->front;
    data->top = pHeadInput->top;
    data->next = pHeadInput->next;
    return data;
}

void cpdata2str(char* str, int data)
{
    char* end = str;
    char* begin = str;
    while (data != 0)
    {
        *end = '0' + data%10;
        end++;
        data = data/10;
    }
    end--;
    char tmp;
    while (begin < end)
    {
        tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
        end--;
    }
}



void PolynomialMultiple (char* InputString1, char* InputString2, char* OutputString)
{
    /*在这里实现功能*/
    if (NULL==InputString1 || NULL==InputString2 || NULL == OutputString)
    {
        return;
    }
    Node* pHeadInput1 = NULL;
    Node* pHeadInput2 = NULL;
    Node* pOutput = NULL;
    char* pInput1 = InputString1;
    char* pInput2 = InputString2;
    char* pOutputstr = OutputString;
    InitList(&pHeadInput1);
    InitList(&pHeadInput2);
    InitList(&pOutput);
    insertData(pInput1,&pHeadInput1);
    insertData(pInput2,&pHeadInput2);
    Node* pHead1 = NULL;
    Node* pHead2 = NULL;
    Node* pTmp1 = pHeadInput1;
    Node* pTmp2;
    while ( (pHead1 = getData(pTmp1->next)) != NULL )
    {
        pTmp2 = pHeadInput2;
        while ( (pHead2 = getData(pTmp2->next)) != NULL)
        {
            insert_list(&pOutput,pHead1->top+pHead2->top,pHead1->front*pHead2->front);
            pTmp2 = pHead2;
        }
        pTmp1 = pHead1;
    }
    char str_data[10]= {0};
    Node* pHead = NULL;
    int i = 0;
    size_t len=0;
    while ( (pHead = getData(pOutput->next)) != NULL )
    {
        if (pHead->front > 0)
        {
            cpdata2str(str_data, pHead->front);
            len = strlen(str_data);
            if (i!=0)
            {
                *pOutputstr++ = '+';
            }
            strncpy(pOutputstr,str_data,len);
            pOutputstr += len;
            strncpy(pOutputstr,"X^",2);
            pOutputstr += 2;
            memset(str_data,'\0',10);
            cpdata2str(str_data, pHead->top);
            len = strlen(str_data);
            if(len == 0)
            {
                *pOutputstr = '0';
                pOutputstr ++;
            }
            else
            {
                strncpy(pOutputstr,str_data,len);
                pOutputstr += len;
            }
        }
        else if(pHead->front < 0)
        {
            cpdata2str(str_data, -(pHead->front));
            len = strlen(str_data);
            *pOutputstr++ = '-';
            strncpy(pOutputstr,str_data,len);
            pOutputstr += len;
            strncpy(pOutputstr,"X^",2);
            pOutputstr += 2;
            memset(str_data,'\0',10);
            cpdata2str(str_data, pHead->top);
            len = strlen(str_data);
            if(len == 0)
            {
                *pOutputstr = '0';
                pOutputstr ++;
            }
            else
            {
                strncpy(pOutputstr,str_data,len);
                pOutputstr += len;
            }
        }
        pOutput = pHead;
        memset(str_data,'\0',10);
        i++;
    }
    *pOutputstr = '\0';
    return;
}

int main()
{
    char *InputString1 = "7X^4";
    char *InputString2 = "-7X^4";
    char *OutputString = NULL;

    OutputString = (char*)malloc(40000);
    memset(OutputString,0,40000);

    PolynomialMultiple(InputString1,InputString2,OutputString);

    std::cout << (strcmp(OutputString, "-49X^8") == 0) << std::endl;

    free(OutputString);
}
