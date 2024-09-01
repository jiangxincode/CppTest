#include <iostream>
#include <cstdlib>

#define MAX_RANDOM_NUM 100

using namespace std;

/**
 * 对于给定整数数组，求出其所有极大值和极小值的位置。
 * source_array: 给定整数数组
 * length: 整数数组长度
 * target_array: 所有极大值和极小值的位置，其长度和source_array相同。
 * 如果对应位置是极大值，则标注为1；如果对应位置是极小值，则标注为-1；如果不是极值（端点不是极值），则标注为0.
 * 所有参数都需要调用参数保证合法性
 */
void get_max_min(int* source_array, int length, int* target_array)
{
	target_array[0] = 0;
	target_array[length] = 0;
	for (int i = 1; i < length - 1; i++)
	{
		if ((source_array[i] > source_array[i - 1])
				&& (source_array[i] > source_array[i + 1]))
		{
			target_array[i] = 1;
		}
		else if ((source_array[i] < source_array[i - 1])
				&& (source_array[i] < source_array[i + 1]))
		{
			target_array[i] = -1;
		}
		else
		{
			target_array[i] = 0;
		}
	}
}

/**
 * 生成一个长度为100的数组，其中的数据由随机函数产生（范围在1~100）。
 * 编程求出其中所有的极大值和极小值。（极大值是指某元素的值比它左右的值都大，极小值是指某元素的值比它左右的值都小。不考虑边界值。）
 */
int main()
{
	int source_array[MAX_RANDOM_NUM];
	int target_array[MAX_RANDOM_NUM];

	for (int i = 0; i < MAX_RANDOM_NUM; i++)
	{
		source_array[i] = rand();
		cout << source_array[i] << " ";
	}

	cout << endl;

	get_max_min(source_array, MAX_RANDOM_NUM, target_array);

	for (int i = 0; i < MAX_RANDOM_NUM; i++)
	{
		cout << target_array[i] << " ";
	}

	return 0;
}
