/**
 * 圆桌游戏
 * 详细描述：
 * N个人围坐在一个圆桌上，顺时针报数，报数的初始值为第一个人设置。当有成员报出的数字为7的倍数或数字中包含7，则该人退出圆桌，而后由下一个人开始重新继续该游戏。
 * 实现以下接口：
 *   1、设定输入原始的圆桌游戏的人数。以最先开始报数的人编号为1，顺时针排序。
 *   2、设定第一个人的初始值，获取按照规则退出圆桌的人的编号。
 *   3、结束游戏。
 *
 * 样例:
 * 比如初始化为4人的游戏：第1轮初始值为1，退出为3；第2轮初始值为4，退出为4号；第三轮初始值为16，退出为2号；第四轮初始值为6，退出为1号；
 *
 */
#include <stdlib.h>
#include "iostream"

bool has_seven(int i)
{
    if (i % 7 == 0)
    {
        return true;
    }
    while(i > 0)
    {
        if (i % 10 == 7)
        {
            return true;
        }
        i /= 10;
    }
    return false;
}

int *p; //标记玩家是否出列
unsigned int num; //玩家个数
int j; //当前第j+1个人在数


// 功能：设置玩家的个数
// 输入： unsigned int  nPlayNum   玩家的个数 0 < nPlayNum < 10000;
// 输出：无
// 返回：无
void SetPlayerNum (unsigned int  nPlayNum)
{
    num = nPlayNum;
    j = 0;
    p = (int*)malloc(sizeof(int)*(num));
    for (int i=0;i<num;i++)
    {
        p[i] = 1;
    }
}

// 功能：根据nInitialNum的值，获取到根据规则下桌的人的编号
// 输入：unsigned int  nInitialNum  本轮的初始值 0 < nInitialNum < 10000；
// 输出：无
// 返回：本轮退出圆桌的人的编号
unsigned int GetPlayerOut (unsigned int  nInitialNum)
{
    int i = nInitialNum; //本轮正在数几

    while (true)
    {
        if (has_seven(i) && (p[j%num] == 1))
        {
            p[j%num] = 0;
            j++;
            return (j-1)%num+1;
        }
        else if (p[j%num] == 1)
        {
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }
    return 0;
}
// 功能：游戏结束,释放资源
// 输入：无
// 输出：无
// 返回：无
void GameOver()
{
    free(p);
}

int main() {
    {
        SetPlayerNum(4);
        unsigned int nResult = GetPlayerOut(1);
        std::cout << (3 == nResult) << std::endl;

        nResult = GetPlayerOut(4);
        std::cout << (4 == nResult) << std::endl;

        nResult = GetPlayerOut(16);
        std::cout << (2 == nResult) << std::endl;

        nResult = GetPlayerOut(6);
        std::cout << (1 == nResult) << std::endl;


        GameOver();
    }
    {
        SetPlayerNum(1);
        unsigned int nResult = GetPlayerOut(9999);
        std::cout << (1 == nResult) << std::endl;


        GameOver();
    }
    {
        SetPlayerNum(4);
        std::cout <<  (3 == GetPlayerOut (8)) << std::endl;
        std::cout <<  (4 == GetPlayerOut (4)) << std::endl;
        std::cout <<  (2 == GetPlayerOut (16)) << std::endl;
        std::cout <<  (1 == GetPlayerOut (2)) << std::endl;

        GameOver();
    }

    {
        SetPlayerNum(30);
        std::cout <<  (2 == GetPlayerOut (69)) << std::endl;
        std::cout <<  (4 == GetPlayerOut (699)) << std::endl;
        std::cout <<  (6 == GetPlayerOut (1399)) << std::endl;
        GameOver();
    }
    {
        SetPlayerNum(8);
        std::cout <<  (7 == GetPlayerOut (1)) << std::endl;
        std::cout <<  (1 == GetPlayerOut (16)) << std::endl;
        GameOver();
    }

}


