/**
 * 报文转换
 * 功能: 将给定的报文按规则转换成另一个报文后输出。
 * 转换规则如下：
 * 报文中如果出现0x7E，转义成为2个字节0x7D 0x5E，如果出现0x7D，转义成为2个字节0x7D 0x5D。
 * 最后在报文头尾各加上一个0x7E定界。
 *
 * 示例（每个字节以十六进制数表示）
 * 给定原始报文：1D 2B 3C 4D 5E 7E 6F 7D 7E
 * 转换后的报文：7E 1D 2B 3C 4D 5E 7D 5E 6F 7D 5D 7D 5E 7E
 *
 * 输入:
 * char* pInput: 给定的输入报文，内存空间由调用者申请和释放
 * int iLen: 给定报文的长度
 *
 * 输出:
 * char* pOutput：转换后的报文，内存空间由调用者申请和释放
 *
 * 返回:
 * int： 成功 0， 失败 -1
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;


int PktTrans(char *pInput, int iLen, char *pOutput) {
    /*参数合法性判断*/
    if ((pInput == NULL) || (pOutput == NULL) || (iLen < 0)) {
        return -1;
    }

    /*根据所给测试用例推断，当iLen为0时要直接返回0，而不是在报文头尾各加上一个0x7E（题目表意不明）*/
    if (iLen == 0) {
        return 0;
    }

    int j = 0;
    pOutput[j++] = 0x7E; //在报文头加上一个0x7E定界

    for (int i = 0; i < iLen; i++) {
        if (pInput[i] == 0x7E) //如果出现0x7E，转义成为2个字节0x7D 0x5E
        {
            pOutput[j++] = 0x7D;
            pOutput[j++] = 0x5E;
        } else if (pInput[i] == 0x7D) //如果出现0x7D，转义成为2个字节0x7D 0x5D
        {
            pOutput[j++] = 0x7D;
            pOutput[j++] = 0x5D;
        } else {
            pOutput[j++] = pInput[i];
        }
    }

    pOutput[j] = 0x7E; //在报文尾加上一个0x7E定界

    return 0;
}

int main() {
    {
        char szInput[100] = {0x1D, 0x2B, 0x3C, 0x4D, 0x5E, 0x7E, 0x6F, 0x7D, 0x7E};
        char szResult[100] = {0x7E, 0x1D, 0x2B, 0x3C, 0x4D, 0x5E, 0x7D, 0x5E, 0x6F, 0x7D, 0x5D, 0x7D, 0x5E, 0x7E};
        char szOutput[100] = {0};

        cout << (0 == PktTrans(szInput, 9, szOutput)) << endl;
        cout << (0 == strncmp(szResult, szOutput, 14)) << endl;
    }

    {
        char szInput[100] = {};
        char szResult[100] = {0};
        char szOutput[100] = {0};

        cout << (0 == PktTrans(szInput, 0, szOutput)) << endl;
        cout << (0 == strncmp(szResult, szOutput, 0)) << endl;
    }

    {
        char szInput[100] = {0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E};
        char szResult[100] = {0x7E, 0x7D, 0x5E, 0x7D, 0x5E, 0x7D, 0x5E, 0x7D, 0x5E, 0x7D, 0x5E, 0x7D, 0x5E, 0x7E};
        char szOutput[100] = {0};

        cout << (0 == PktTrans(szInput, 6, szOutput)) << endl;
        cout << (0 == strncmp(szResult, szOutput, 14)) << endl;
    }

    {
        char szInput[100] = {0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D};
        char szResult[100] = {0x7E, 0x7D, 0x5D, 0x7D, 0x5D, 0x7D, 0x5D, 0x7D, 0x5D, 0x7D, 0x5D, 0x7D, 0x5D, 0x7E};
        char szOutput[100] = {0};

        cout << (0 == PktTrans(szInput, 6, szOutput)) << endl;
        cout << (0 == strncmp(szResult, szOutput, 14)) << endl;
    }

}