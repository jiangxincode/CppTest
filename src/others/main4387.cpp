/**
 * 正数相减
 * 请编写程序实现：
 *
 * 两个任意长度的正数相减，这两个正数可以带小数点，也可以是整数，请输出结果.
 *
 * 系统假设：
 *
 * 输入的字符串中，不会出现除了数字与小数点以外的其它字符，不会出现多个小数点以及小数点在第一个字符的位置等非法情况，所以考生的程序中无须考虑输入的数值字符串非法的情况。
 *
 * 详细要求以及系统约束
 * 1.输入均为正数，但输出可能为负数
 * 2.输入输出均为字符串形式，输入的字符串以“\0”结束，输出的结果字符串也必须以“\0”结束
 * 3.如果输出是正数则不需要带符号，如果为负数，则输出的结果字符串需要带负号
 *   例如：2.2-1.1 直接输出为“1.1”，1.1-2.2 则需要输出为“-1.1”
 *
 * 4.输出的结果字符串需要过滤掉整数位前以及小数位后无效的0，小数位为全0的，直接输出整数位
 *   例如相减结果为11.345，此数值前后均不可以带0，“011.345”或者“0011.34500”等等前后带无效0的均视为错误
 *   输出。例如1.1-1.1结果为0.0，则直接输出0。
 *
 * 5.输出的字符串内存由考生的程序负责分配，测试程序负责释放
 *
 */
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

bool isborr(string a1,string b1,char *c)
{
    bool result = 0;

    int length=a1.length()>b1.length()?a1.length():b1.length();
//实现a的复制
    int t=0;
    char *a=new char[length+1];
    while(a1[t]!='\0')
    {
        a[t]=a1[t];
        t++;
    }
    a[t]='\0';

    t=0;
    char *b=new char[length+1];
    while(b1[t]!='\0')
    {
        b[t]=b1[t];
        t++;
    }
    b[t]='\0';

    if(a1.length()<=b1.length())
    {
        for(int i=a1.length(); i<b1.length(); i++)
            a[i]='0';
        a[length]='\0';
    }
    else
    {
        for(int i=b1.length(); i<a1.length(); i++)
            b[i]='0';
        b[length]='\0';
    }
    if(strcmp(a,b)<0)
    {
        result=1;
        a[0]+=10;
    }

    for(int i=length-1; i>=0; i--)
    {
        if(a[i]>=b[i])
            c[i]=a[i]-b[i]+'0';
        else
        {
            a[i-1]-=1;
            c[i]=10+a[i]-b[i]+'0';
        }
    }
    c[length]='\0';
    //进行末尾0判断

    while(c[length-1]=='0'&&length>=1)
    {
        c[length-1]='\0';
        length--;
    }
    if(strlen(c)==0)
    {
        c[0]='0';
        c[1]='\0';
    }

    return result;
}

void calbrofedot(string a1,string b1,char *c)
{
    int length=a1.length()>b1.length()?a1.length():b1.length();
    int t=0;
    char *a=new char[length+1];
    while(a1[t]!='\0')
    {
        a[t]=a1[t];
        t++;
    }
    a[t]='\0';

    t=0;
    char *b=new char[length+1];
    int temp=a1.length();
    for(int i=b1.length()-1 ; i>=0 ; i--)
    {
        b[temp-1]=b1[i];
        temp--;
    }
    b[a1.length()]='\0';

    for(int j=0; j<a1.length()-b1.length(); j++)
        b[j]='0';


    for(int i=a1.length()-1; i>=0; i--)
    {
        if(a[i]>=b[i])
            c[i]=a[i]-b[i]+'0';
        else
        {
            a[i-1]-=1;
            c[i]=10+a[i]-b[i]+'0';
        }
    }

    c[length]='\0';
    int z=0,count=0;
    while(c[z]=='0')
    {
        count++;
        z++;
        if(c[z]!='0')
            break;
    }
    int w=0;
    for(; w<strlen(c)-count; w++)
        c[w]=c[w+count];
    c[w]='\0';

    if(strlen(c)==0)
    {
        c[0]='0';
        c[1]='\0';
    }


}

/*****************************************************************************
Description  : 两个任意长度的正数相减
Prototype    : int Decrease(const char *pMinuend, const char *pSubtrahend, char **ppResult)
Input Param  : const char *pMinuend     被减数，以\0表示字符串结束
               const char *pSubtrahend  减数，以\0表示字符串结束
Output       : char **ppResult          减法结果，必须以\0表示字符串结束
Return Value : 成功返回0   失败返回-1
*****************************************************************************/
int Decrease(const char *pMinuend, const char *pSubtrahend, char **ppResult)
{

    /* 在这里实现功能 */
    if(pMinuend == NULL || pSubtrahend == NULL || pMinuend[0] == '\0' || pSubtrahend[0] == '\0' || pSubtrahend[0] == '\0')
    {
        return -1;
    }
    string a=pMinuend,b=pSubtrahend;
    string MinuendInteger="";
    string SubtrahendInteger="";
    string MinuendFractional="";
    string SubtrahendFractional="";
    int dotpospMinuend=a.find_first_of('.');
    int dotpospSubtrahend=b.find_first_of('.');
    if(dotpospMinuend==-1)//拆分 小数点前后
    {
        MinuendInteger=pMinuend;
    }
    else
    {
        MinuendInteger=a.substr(0,dotpospMinuend);
        MinuendFractional=a.substr(dotpospMinuend+1,a.length());
    }

    if(dotpospSubtrahend==-1)//拆分 小数点前后
    {
        SubtrahendInteger=pSubtrahend;
    }
    else
    {
        SubtrahendInteger=b.substr(0,dotpospSubtrahend);
        SubtrahendFractional=b.substr(dotpospSubtrahend+1,b.length());
    }
    bool isfushu=0;//先判断结果是否为负数
    if(MinuendInteger.length()<SubtrahendInteger.length())
    {
        isfushu=1;
    }
    else if(MinuendInteger.length()==SubtrahendInteger.length()&&MinuendInteger<SubtrahendInteger)
    {
        isfushu=1;
    }
    else if(MinuendInteger==SubtrahendInteger)
    {
        if(MinuendFractional<SubtrahendFractional)
            isfushu=1;
    }

    //进行减法计算,先进行小数计算
    int length=SubtrahendFractional.length()>MinuendFractional.length()?SubtrahendFractional.length():MinuendFractional.length();
    char *c=new char[length+1];
    bool  borr=0;
    if(isfushu==1)
    {
        borr=isborr(SubtrahendFractional,MinuendFractional,c);
    }
    else
    {
        borr=isborr(MinuendFractional,SubtrahendFractional,c);
    }
    // 前面进行了小数点以后的计算
    int lengthzheng=MinuendInteger.length()>SubtrahendInteger.length()?MinuendInteger.length():SubtrahendInteger.length();
    char *d=new char[lengthzheng+1];
    if(isfushu==1)
    {
        if(borr==1) SubtrahendInteger[SubtrahendInteger.length()-1]-=1;
        calbrofedot(SubtrahendInteger,MinuendInteger,d);
    }
    else
    {
        if(borr==1) MinuendInteger[MinuendInteger.length()-1]-=1;
        calbrofedot(MinuendInteger,SubtrahendInteger,d);
    }
//进行小数点和整数的组合  判断返回的cd是否为空  否结果为0

    string result="";
    if(c[0]=='0'&&c[1]=='\0'&&d[0]=='0')
    {
        result="0";
    }
    else if(c[0]=='0'&&c[1]=='\0'&&d[0]!='0')
    {
        if(isfushu==1)
        {
            result="-";
            result=result+d;
        }
        else
        {
            result=d;
        }
    }
    else if(c[0]=='0'&&c[1]=='\0'&&d[0]=='0')
    {
        if(isfushu==1)
        {
            result="-0.";
            result=result+c;
        }
        else
        {
            result="0.";
            result=result+c;
        }
    }
    else //if(strlen(c)!=0&&d[0]!='0')
    {
        if(isfushu==1)
        {
            result="-";
            result=result+d;
            result=result+".";
            result=result+c;
        }
        else
        {
            result=result+d;
            result=result+".";
            result=result+c;
        }
    }
    int count=a.length()+b.length();
    char *p=new char[count+2];//开这个空间特别注意   比如 0.00000000001   100000000.1 这一样的就不是他们最长的
    *ppResult=p;
    int z=0;
    while(result[z]!='\0')
    {
        p[z]=result[z];
        z++;
    }
    p[z]='\0';

    return 0;

}

int main() {
    {
        const char * pMinuend = "85";
        const char * pSubtrahend = "79";
        char * pResult = NULL;
        Decrease(pMinuend, pSubtrahend, &pResult);
        std::cout << (pResult != NULL) << std::endl;
        std::cout << (strcmp(pResult, "6") == 0) << std::endl;
        free(pResult);
    }


    {
        const char * pMinuend = "8.5";
        const char * pSubtrahend = "0.91";
        char * pResult = NULL;
        Decrease(pMinuend, pSubtrahend, &pResult);
        std::cout << (pResult != NULL) << std::endl;
        std::cout << (strcmp(pResult, "7.59") == 0) << std::endl;
        free(pResult);
    }

    {
        const char * pMinuend = "8.5";
        const char * pSubtrahend = "7.5";
        char * pResult = NULL;
        Decrease(pMinuend, pSubtrahend, &pResult);
        std::cout << (pResult != NULL) << std::endl;
        std::cout << (strcmp(pResult, "1") == 0) << std::endl;
        free(pResult);
    }

    {
        const char * pMinuend = "12.34";
        const char * pSubtrahend = "17.24";
        char * pResult = NULL;
        Decrease(pMinuend, pSubtrahend, &pResult);
        std::cout << (pResult != NULL) << std::endl;
        std::cout << (strcmp(pResult, "-4.9") == 0) << std::endl;
        free(pResult);
    }

}
