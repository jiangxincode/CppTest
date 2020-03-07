/**
 * 字节流解析
 * 题目标题：
 * 根据数值占用BIT数，按顺序从输入字节流中解析出对应数值，解析顺序按输入数组astElement索引升序。
 * 详细描述：
 * 接口说明
 * 原型：
 * void Decode(unsigned int uiIutputLen, unsigned char aInputByte[], unsigned int uiElementNum, ELEMENT_STRU  astElement[]);
 * 输入参数：
 * unsigned int uiIutputLen：字节数组（流）长度
 * unsigned char aInputByte：字节数组（流）
 * unsigned int uiElementNum：解析数值个数
 * ELEMENT_STRU astElement[]：数值的结构数组指针，含义如下
 * Struct
 * {
 *      unsigned int uiElementLength;    //表示uiElementValue占用BIT数，范围1~32
 *      unsigned int uiElementValue;     //从字节流中按顺序解析的数值，用于输出
 * }ELEMENT_STRU;
 * 输出参数（指针指向的内存区域保证有效）：
 *     参见上述ELEMENT_STRU中uiElementValue描述
 * 返回值：
 *     Void
 * 举例：
 * 输入:
 * 字节数组长度uiIutputLen为2；
 * 字节数组aInputByte[2]为{0x62, 0x80}，对应二进制为“01100010 1 000 0000”；
 * 解析数值个数uiElementNum为2；
 * 数值[0]的值占4个bit，即astElement[0].uiElementLength = 4；
 * 数值[1]的值占5个bit，即astElement[1].uiElementLength = 5；
 * 输出：
 * 数值[0]的值为6，二进制为“0110”，即astElement[0].uiElementValue = 6；
 * 数值[1]的值为5，二进制为“0010 1”，即astElement[1].uiElementValue = 5。
 *
 */
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

typedef struct
{
    unsigned int uiElementLength;	//表示数值uiElementValue占用BIT数，范围1~32
    unsigned int uiElementValue;	//表示编码的数值
}ELEMENT_STRU;

/* 求2的m次方 */
unsigned int mypow(unsigned int m)
{
    unsigned int result = 1;
    for (unsigned int i=1;i<=m;i++)
    {
        result *= 2;
    }
    return result;
}
/*
功能: 根据数值占用BIT数，按顺序从输入字节流中解析出对应数值，解析顺序按输入数组astElement索引升序

输入:unsigned int uiIutputLen：字节数组（流）长度
	 unsigned char aInputByte：字节数组（流）
     unsigned int uiElementNum：解析数值个数
	 ELEMENT_STRU astElement[]：数值的结构数组指针，含义如下
	 Struct
	 {
	 	unsigned int uiElementLength;	//表示uiElementValue占用BIT数，范围1~32
		unsigned int uiElementValue;	//从字节流中按顺序解析的数值，用于输出
	 }ELEMENT_STRU;

输出:参见上述ELEMENT_STRU中uiElementValue描述

返回:void
*/
void Decode(unsigned int uiIutputLen, unsigned char aInputByte[], unsigned int uiElementNum, ELEMENT_STRU astElement[])
{
    /*在这里实现功能*/

    string input = "";
    for (unsigned int i=0;i<uiIutputLen;i++)
    {
        unsigned int temp = (unsigned int)aInputByte[i];
        string str = "";
        while (temp > 0)
        {
            if (temp % 2 == 0)
            {
                str = string("0").append(str);
            }
            else
            {
                str = string("1").append(str);
            }
            temp /= 2;
        }
        while (str.length() < 8)
        {
            str = string("0").append(str);
        }
        input.append(str);
    }


    for (unsigned int i=0;i<uiElementNum;i++)
    {
        string str = input.substr(0,astElement[i].uiElementLength);

        astElement[i].uiElementValue = 0;
        for (unsigned int j=0;j<astElement[i].uiElementLength;j++)
        {
            astElement[i].uiElementValue += (str[j]-'0') * mypow(astElement[i].uiElementLength-1-j);
        }

        input = input.substr(astElement[i].uiElementLength);
    }

    return;
}

int main() {
    {
        ELEMENT_STRU  astElement[2];
        unsigned int  uiIutputLen;
        unsigned char aucIutput[2];

        uiIutputLen = 2;
        aucIutput[0] = 0x62;
        aucIutput[1] = 0x80;

        astElement[0].uiElementLength = 4;
        astElement[1].uiElementLength = 5;

        Decode(uiIutputLen, aucIutput, 2, astElement);

        std::cout << (astElement[0].uiElementValue == 6) << std::endl;
        std::cout << (astElement[1].uiElementValue == 5) << std::endl;
    }

    {
        ELEMENT_STRU  astElement[3];
        unsigned int  uiIutputLen;
        unsigned char aucIutput[2];

        uiIutputLen = 2;
        aucIutput[0] = 0x62;
        aucIutput[1] = 0x80;

        astElement[0].uiElementLength = 4;
        astElement[1].uiElementLength = 4;
        astElement[2].uiElementLength = 4;

        Decode(uiIutputLen, aucIutput, 3, astElement);

        std::cout << (astElement[0].uiElementValue == 6) << std::endl;
        std::cout << (astElement[1].uiElementValue == 2) << std::endl;
        std::cout << (astElement[2].uiElementValue == 8) << std::endl;
    }

}


