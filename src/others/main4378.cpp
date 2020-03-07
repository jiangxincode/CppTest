/**
 * 营救公主
 * 500年前，Jesse是我国最卓越的剑客。他英俊潇洒，而且机智过人^_^。
 * 突然有一天，Jesse心爱的公主被魔王困在了一个巨大的迷宫中。Jesse听说这个消息已经是两天以后了，他知道公主在迷宫中还能坚持T天，他急忙赶到迷宫，开始到处寻找公主的下落。 时间一点一点的过去，Jesse还是无法找到公主。最后当他找到公主的时候，美丽的公主已经死了。从此Jesse郁郁寡欢，茶饭不思，一年后追随公主而去了。T_T 500年后的今天，Jesse托梦给你，希望你帮他判断一下当年他是否有机会在给定的时间内找到公主。
 * 他会为你提供迷宫的地图以及所剩的时间T。请你判断他是否能救出心爱的公主。
 *
 * 题目包括多组测试数据。 每组测试数据以三个整数N,M,T(0 < n, m <= 20,0 < t <= 100000)开头，分别代表迷宫的长和高，以及公主能坚持的天数。 紧接着有m行，n列字符，由"."，"*"，"p"，"s"组成。其中 "." 代表能够行走的空地。 "*" 代表墙壁，jesse不能从此通过。 "p" 是公主所在的位置。 "s" 是jesse的起始位置。 每个时间段里jesse只能选择“上、下、左、右”任意一方向走一步。 输入以0 0 0结束。
 *
 * 样例输入
 * m = 4, n = 4, t = 10
 * 迷宫图如下
 * ....
 * ....
 * ....
 * S**P
 *
 */
#include<stdio.h>
#include<string.h>
#include "iostream"

/*
Description
     每组测试数据以三个整数N,M,T(0<n, m≤20, t>0)开头，分别代表迷宫的长和高，以及公主能坚持的天数。
	 紧接着有M行，N列字符，由"."，"*"，"P"，"S"组成。其中 "." 代表能够行走的空地。 "*" 代表墙壁，Jesse不能从此通过。
	 "P" 是公主所在的位置。 "S" 是Jesse的起始位置。 每个时间段里Jesse只能选择“上、下、左、右”任意一方向走一步。
Prototype
     int SSaveP (int *maze[], int M, int n, int t)
Input Param
     maze            迷宫布局（这里用二维数组实现布局）
	 M               迷宫（数组）行数
     N               迷宫（数组）列数
	 T               公主能坚持的天数
Output Param
                     无
Return Value
     0         可以救出公主
     -1        不可以救出公主

*/

int SSavep(char *visited, int t, int n, int m)
{
    // 这里面添加函数功能
    return 0;
}

int main()
{
    int N = 4;
    int M = 4;
    int T = 10;
    char a[4][4] = {'.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.','S', '*', '*','P'};
    char *p = &a[0][0];
    int  Ret;

    Ret = SSavep(p, T, N, M);

    std::cout << (Ret == 0) << std::endl;
}


