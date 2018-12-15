/*
 华为公司2014届校园招聘软件类上机考试样题
 一条长廊里依次装有n(1 ≤ n ≤ 65535)盏电灯，从头到尾编号1、2、3、…n-1、n。
 每盏电灯由一个拉线开关控制。开始，电灯全部关着。有n个学生从长廊穿过。
 第一个学生把号码凡是1的倍数的电灯的开关拉一下；
 接着第二个学生把号码凡是2的倍数的电灯的开关拉一下；
 接着第三个学生把号码凡是3的倍数的电灯的开关拉一下；
 如此继续下去，最后第n个学生把号码凡是n的倍数的电灯的开关拉一下。
 n个学生按此规定走完后，长廊里电灯有几盏亮着。
 注：电灯数和学生数一致。

 输入：电灯的数量
 输出：亮着的电灯数量
 样例输入：3
 样例输出：1
 样例输入：1000
 样例输出：31
 */

#include <iostream>
#include <utility>
#include <map>

using namespace std;

/*int main()
 {
 map<int, bool> map_lamp;
 int num;
 cin >> num;

 for (int i = 1; i <= num; i++)
 {
 map_lamp.insert(pair<int, bool>(i, false));
 }

 for (int i = 1; i <= num; i++)
 {
 for (int j = 1; j <= num; j++)
 {
 if (j % i == 0)
 {
 map_lamp[j] = !map_lamp[j];
 }
 }
 }

 int result = 0;

 for (int i = 1; i <= num; i++)
 {
 if (map_lamp[i] == true)
 {
 result++;
 }
 }

 cout << result;
 return 0;
 }*/

/**
 * 对于任何一盏灯，由于它原来不亮，那么当它的开关被按奇数次时，灯是开着的；当它的开关被按偶数次时，灯是关着的；
 * 一盏灯的开关被按的次数，恰等于这盏灯的编号的因数的个数；
 * 要求哪些灯还亮着，就是问哪些灯的编号的因数有奇数个．显然完全平方数有奇数个因数。
 * 每个数除以一个数A等于另一个数B，那么A和B都是它的因数，于是因数是成对出现的，但是要因数是奇数，就必须A=B所以这个数就必须是一个是的平方得到的。
 */
int main()
{
	int num;
	cin >> num;
	int count = 0;
	for (int i = 1; i * i <= num; i++)
	{
		count++;
	}
	cout << count;
	return 0;
}
