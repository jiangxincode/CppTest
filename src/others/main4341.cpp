/**
 * Jam的记数法 JamCounter
 * •	题目描述
 * Jam是个喜欢标新立异的科学怪人。他不使用阿拉伯数字计数，而是使用小写英文字母计数，他觉得这样做，会使世界更加丰富多彩。在他的计数法中，每个数字的位数都是相同的（使用相同个数的字母），英文字母按原先的顺序，排在前面的字母小于排在它后面的字母。我们把这样的“数字”称为Jam数字。在Jam数字中，每个字母互不相同，而且从左到右是严格递增的。每次，Jam还指定使用字母的范围，例如，从2到10，表示只能使用{b,c,d,e,f,g,h,i,j}这些字母。如果再规定位数为5，那么，紧接在Jam数字“bdfij”之后的数字应该是“bdghi”。（如果我们用U、V依次表示Jam数字“bdfij”与“bdghi”，则U<V，且不存在Jam数字P，使U<P<V）。你的任务是：对于从文件读入的一个Jam数字，按顺序输出紧接在后面
 * 输入举例：
 * 输入文件counting.in 有2行，第1行为3个正整数，用一个空格隔开：
 * InMinSeq InMaxSeq InNumbLen
 * （其中InMinSeq为所使用的最小的字母的序号，InMaxSeq为所使用的最大的字母的序号。InNumbLen为数字的位数，这3个数满足：1≤InMinSeq < InMaxSeq≤26, 2≤InNumbLen≤InMaxSeq - InMinSeq < InMaxSeq）
 * 第2行为具有InNumbLen个小写字母的字符串，为一个符合要求的Jam数字。
 * 所给的数据都是正确的，不必验证。
 * 输出举例：
 * 输出文件counting.out 最多为5行，为紧接在输入的Jam数字后面的5个Jam数字，如果后面没有那么多Jam数字，那么有几个就输出几个。每行只输出一个Jam数字，是由InNumbLen个小写字母组成的字符串，不要有多余的空格
 * •	接口说明
 * 原型：
 * void GetResult(int InMinSeq, int InMaxSeq, int InNumbLen, char *InChaStr, char *pBufOutData);
 * 输入参数：
 *   Char InMinSeq：输入最小的字母的序号
 *   char InMaxSeq: 输入最大的字母的序号
 *   int InNumbLen：输入字符的位数
 *   char InChaStr: 输入具有InNumbLen个字符的字符串
 * 输出参数（指针指向的内存区域保证有效）：
 *   char* pBufOutData：输出转换后的字符列表，以‘\n’区分
 * 返回值
 *   Void
 *
 */
#include <string>
#include <cstring>
#include <iostream>

using namespace std;


void GetResult(int InMinSeq, int InMaxSeq, int InNumbLen, char *InChaStr, char *pBufOutData)
{
    int i = 0, j = 0;

    pBufOutData[0] = '\0'; //如果不进行初始化可能会造成之后strcat函数出错

    char alphaTable[28] = {0}; //26个字符，alphaTable[0]留空，并保证最后至少剩下一个字符空间添加'\0'
    for (i=InMinSeq;i<=InMaxSeq;i++)
    {
        alphaTable[i] = 'a' + i - 1;
    }
    alphaTable[i] = '\0';

    char charTemp[28]; //InNumbLen最大值为26，加上一个'\n'与一个'\0'
    strcpy(charTemp,InChaStr);

    i = InNumbLen - 1; //对charTemp进行索引
    j = InMaxSeq; //对alphaTable进行索引
    int count=0; //记录输出的数目
    while ((count <= 4) && (charTemp[0] != alphaTable[InMaxSeq-(InNumbLen-1)]))
    {
        if (charTemp[i] != alphaTable[j])
        {
            charTemp[i] = charTemp[i]+1;
            for (int k=i+1; k<InNumbLen; k++) //位置i之后的所有位置的字符均变成前一个字符+1
            {
                charTemp[k] = charTemp[k-1] + 1;
            }
            charTemp[InNumbLen]='\n';
            charTemp[InNumbLen+1]='\0';

            strcat(pBufOutData, charTemp);

            count++;

            i = InNumbLen-1;
            j = InMaxSeq;
        }
        else
        {
            i--;
            j--;
        }

    }
    pBufOutData[strlen(pBufOutData)-1] = '\0'; //将最后一个'\n'转换成'\0'

}

int main()
{
    int InMinSeq = 2;
    int InMaxSeq = 10;
    int InNumbLen = 5;
    char InChaStr[30] = "bdfij";

    char pBufOutData[1024] = {0};

    GetResult(InMinSeq, InMaxSeq, InNumbLen, InChaStr, pBufOutData);

    std::cout << (0 == strcmp( pBufOutData,"bdghi\nbdghj\nbdgij\nbdhij\nbefgh")) << std::endl;
}
