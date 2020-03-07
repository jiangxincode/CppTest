/**
 * 大数相乘
 * 请编写”长整数相乘”程序，实现两个任意长度的长整数(正数)相乘，输出结果.
 * 提示: 将长整数用一个字节链表表示，逐字节相乘，要考虑进位
 * 乘数A = ∑Am*10m     ( 0 ≤ m ＜∞, 0 ≤ Am ≤ 9 ), 首位可以为0
 * 乘数B = ∑Bn*10n       ( 0 ≤ n ＜∞,  0 ≤ Bn≤ 9 ), 首位可以为0
 * Result = 乘数A *乘数B
 * Example1:
 * 乘数A = 1*101 + 2*100 = 12   ( m = 1, A1= 1, A0= 2)
 * 乘数B = 3*101 + 4*100 = 34   ( n = 1,  B1= 3, B0= 4)
 * Example2:
 * 乘数A = 0*102 + 0*101 + 0*100 = 000   ( m = 2, A2= 0, A1= 0, A0= 0)
 * 乘数B = 0*103 + 5*102 + 6*101 + 0*100 = 0560   ( n = 3, B3= 0, B2= 5, B1= 6, B0= 0)
 */
#include <string>
#include <iostream>

using namespace std;

int multiply (const std::string strMultiplierA,const std::string strMultiplierB, std::string &strRst)
{
    /* 在这里实现功能 */
    if((strMultiplierA.length()==0)||(strMultiplierB.length()==0))
    {
        return -1;
    }
    string::size_type maxlen = strMultiplierA.length() + strMultiplierB.length();
    string::size_type minlen = strMultiplierA.length() > strMultiplierB.length() ? strMultiplierB.length() : strMultiplierA.length();

    unsigned int *temp=new unsigned int[minlen*maxlen]; //中间变量
    unsigned int *result=new unsigned int[maxlen];

    for(string::size_type i=0;i<minlen*maxlen;i++) //初始化
    {
        temp[i]=0;
    }
    for(string::size_type i=0;i<maxlen;i++) //初始化
    {
        result[i]=0;
    }


    if(strMultiplierA.length() > strMultiplierB.length())
    {
        int add=0;
        for(string::size_type i=0;i<minlen;i++)
        {
            for(string::size_type j=0;j<maxlen-minlen;j++)
            {
                temp[i*maxlen+j+add]=(strMultiplierB[minlen-i-1]-'0') * (strMultiplierA[maxlen-minlen-j-1]-'0');
            }
            add++;
        }
    }
    else
    {
        int add=0;
        for(string::size_type i=0;i<minlen;i++)
        {
            for(string::size_type j=0;j<maxlen-minlen;j++)
            {
                temp[i*(maxlen)+j+add]=(strMultiplierA[minlen-i-1]-'0') * (strMultiplierB[maxlen-minlen-j-1]-'0');
            }
            add++;
        }

    }

    for(string::size_type i=0;i<maxlen;i++)
    {
        for(string::size_type t=0;t<minlen;t++)
        {
            result[i] += temp[t*(maxlen)+i];
        }
    }


    for(string::size_type i=0;i<maxlen-1;i++) //考虑进位情况
    {
        if(result[i] >= 10)
        {
            result[i+1] = result[i+1] + result[i] / 10;
            result[i] = result[i] % 10;
        }
    }


    //记录非零首位的绝对位置
    int pos=0;
    for(int i=(int)maxlen-1;i>=0;i--)
    {
        if(result[i] != 0)
        {
            pos = i;
            break;
        }
    }

    //数组转换到字符串里面去
    for(int j=pos;j>=0;j--)
    {
        char app=result[j]+'0';
        strRst.push_back(app);
    }

    return 0;
}

int main()
{
    int iRet = 0;
    std::string  sExpectedResult("30");
    std::string strResult = "";

    iRet = multiply("5", "6", strResult);
    std::cout << (iRet == 0) << std::endl;
    std::cout << (sExpectedResult == strResult) << std::endl;
}
