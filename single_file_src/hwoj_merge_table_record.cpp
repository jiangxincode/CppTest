/*
 * 题目：合并表记录

 描述
 数据表记录包含表索引和数值。请对表索引相同的记录进行合并，合并后表记录为相同索引表的数值求和

 知识点	栈
 运行时间限制	10M
 内存限制	128
 输入
 先输入键值对的个数
 然后输入成对的index和value值，以换行符隔开
 输出
 输出合并后的键值对（多行）
 样例输入	4 0 1 0 2 1 2 3 4
 样例输出	0 3 1 2 3 4
 因为题目没要求排序，所以使用unordered_map,那么问题来了，使用unordered_map编译不通过。
 然而使用map竟然就可以通过，但map对记录是排过序的的啊亲！
 */

#include<iostream>
#include<map>
using namespace std;
int main()
{
	int n, index, value;
	map<int, int> imap;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> index;
		cin >> value;
		if (imap.count(index))
		{
			imap[index] += value;
		}
		else
		{
			imap.insert(make_pair(index, value));
		}
	}
	for (map<int, int>::iterator it = imap.begin(); it != imap.end(); it++)
	{
		cout << it->first << endl << it->second << endl;
	}
	return 0;
}

