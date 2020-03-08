/**
 * 独木桥
 * 题目描述
 * 在河上有一座独木桥，一只青蛙想沿着独木桥从河的一侧跳到另一侧。在桥上有一些石子，青蛙很讨厌踩在这些石子上。由于桥的长度和青蛙一次跳过的距离都是正整数，我们可以把独木桥上青蛙可能到达的点看成数轴上的一串整点：0，1，……，L（其中L是桥的长度）。坐标为0的点表示桥的起点，坐标为L的点表示桥的终点。青蛙从桥的起点开始，不停的向终点方向跳跃。一次跳跃的距离是S到T之间的任意正整数（包括S,T）。当青蛙跳到或跳过坐标为L的点时，就算青蛙已经跳出了独木桥。
 * 题目给出独木桥的长度L，青蛙跳跃的距离范围S,T，桥上石子的位置。你的任务是确定青蛙要想过河，最少需要踩到的石子数。
 * 对于30%的数据，L <= 10000；对于全部的数据，L <= 10^9。
 * 输入
 * 输入的第一行有一个正整数L（1 <= L <= 10^9），表示独木桥的长度。第二行有三个正整数S，T，M，分别表示青蛙一次跳跃的最小距离，最大距离，及桥上石子的个数，其中1 <= S <= T <= 10，1 <= M <= 100。第三行有M个不同的正整数分别表示这M个石子在数轴上的位置（数据保证桥的起点和终点处没有石子）。所有相邻的整数之间用一个空格隔开。
 * 输出
 * 输出只包括一个整数，表示青蛙过河最少需要踩到的石子数。
 * 样例输入
 * 10
 * 2 3 5
 * 2 3 5 6 7
 * 接口说明
 * 原型：
 * int GetResult(int bridge_len,int min_hops,int max_hops,int stone_num,int *stone_pos)
 * 输入参数：
 *   int min_step:青蛙一次跳跃的最小距离
 *   int max_step：青蛙一次跳跃的最大距离
 *   int stone_num：桥上石子的个数
 *   int bridge_len：木桥的长度1 <= bridge_len<= 10^9
 *   int *stone_pos：表示这stone_num个石子在数轴上的位置
 *   其中1 <= min_step <= max_step<= 10，1 <= stone_num<= 100
 * 输出参数（指针指向的内存区域保证有效）：
 * 返回值：
 *        int 表示青蛙过河最少需要踩到的石子数
 *
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


int GetResult(int bridge_len,int min_hops,int max_hops,int stone_num,int *stone_pos)
{


    return 0;
}


int main()
{
    int stone_pos[5]={2,3,5,6,7};
    int rect=GetResult(10,2,3,5,stone_pos);
    std::cout << (2==rect) << std::endl;
}
