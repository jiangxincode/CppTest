//unsolved 时间超时
//#include "ObjMgt.h"

#include <vector>
#include <algorithm>

using namespace std;

vector<vector<unsigned>> vec;

/*************************************************************************
功能：增加单个对象
输入：
key1  外部关键字 KEY1
key2  外部关键字KEY2
key3  外部关键字KEY3
输出：无
返回：
      -1 :失败(对象已经存在或者其它异常)
       0 :成功
***************************************************************************/
int AddObject (unsigned int key1, unsigned int key2, unsigned int key3)
{
    /*请实现*/
	vector<unsigned> temp;
	temp.push_back(key1);
	temp.push_back(key2);
	temp.push_back(key3);
	if(find(vec.begin(),vec.end(),temp) == vec.end())
	{
		vec.push_back(temp);
		return 0;
	}

    return -1;
}

/********************************************************************************
功能：删除一个或多个对象
输入：
      key1 外部关键字 KEY1
      key2 外部关键字 KEY2
      key3 外部关键字 KEY3
输出：无
返回：无

说明：用例保证参数取值为合法值和通配符0xFFFFFFFF, 通配符表示0~65535范围内的任意值;
      举例:key1=1,key2=2,key3= 0xFFFFFFFF，表示删除key1=1,key2=2的所有对象;
           key1,key2,key3取值全为0xFFFFFFFF时,表示删除所有对象。
*********************************************************************************/
void DeleteObject (unsigned int key1, unsigned int key2, unsigned int key3)
{
    /*请实现*/
	vector<unsigned> temp;
	temp.push_back(key1);
	temp.push_back(key2);
	temp.push_back(key3);

	vector<vector<unsigned>>::iterator it=vec.begin();
	while(it != vec.end())
	{
		vector<unsigned> temp_it = *it;

		bool isExist0 = false;
		bool isExist1 = false;
		bool isExist2 = false;

		if(temp[0] == 0xFFFFFFFF || temp[0] == temp_it[0])
		{
			isExist0 = true;
		}
		if(temp[1] == 0xFFFFFFFF || temp[1] == temp_it[1])
		{
			isExist1 = true;
		}
		if(temp[2] == 0xFFFFFFFF || temp[2] == temp_it[2])
		{
			isExist2 = true;
		}

		if(isExist0 && isExist1 && isExist2)
		{
			it = vec.erase(it);
		}
		else
		{
			it ++;
		}
	}
    return ;
}

/********************************************************************************
功能：查询单个对象是否存在
输入：
      key1 外部关键字 KEY1
      key2 外部关键字 KEY2
      key3 外部关键字 KEY3
输出：无
返回：
      0：不存在
      1：存在
**********************************************************************************/
int IsObjectExist (unsigned int key1, unsigned int key2, unsigned int key3)
{
    /*请实现*/
	vector<unsigned> temp;
	temp.push_back(key1);
	temp.push_back(key2);
	temp.push_back(key3);

	if(find(vec.begin(),vec.end(),temp) == vec.end())
	{
		return 0;
	}
    return 1;
}

/******************************************************************************************************
Description     清空所有对象
Prototype       void Clear();
Input Param     无
Output Param    无
Return Value    无

********************************************************************************************************/
void Clear(void)
{
    /*在这里实现功能*/
	vec.clear();
    return;
}
