/**
 * 对象管理器
 * 题目概述
 * 实现对象管理器功能，其中管理的对象有3个外部关键字，要求实现:
 *         增加对象;
 *         删除对象;
 *         判断对象是否存在;
 * 说明: 对象的三个外部关键字分别以KEY1,KEY2,KEY3表示。
 *
 * 规格说明
 * 对象的3个外部关键字KEY1,KEY2,KEY3, 其取值范围都为:0~65535;
 *        对象总个数小于等于10000;
 *        以上规格由用例保证。
 *
 * 请实现如下接口
 * int  AddObject (unsigned int key1, unsigned int key2, unsigned int key3)
 * 功能：增加单个对象
 * 输入：
 *         key1 外部关键字KEY1
 *         key2 外部关键字KEY2
 *         key3 外部关键字KEY3
 * 输出：  无
 * 返回：  -1：失败(对象已经存在或者其它异常)
 *          0：成功
 * 说明: 用例保证入参合法取值
 *
 * void  DeleteObject (unsigned int key1, unsigned int key2, unsigned int key3)
 * 功能：删除一个或多个对象
 * 输入：
 * 	  key1 外部关键字KEY1
 *            key2 外部关键字 KEY2
 *            key3 外部关键字 KEY3
 * 输出：无
 * 返回：无
 * 说明：用例保证参数取值为合法值和通配符0xFFFFFFFF, 通配符表示0~65535范围内的
 *       任意值;
 *       举例:key1=1,key2=2,key3= 0xFFFFFFFF，表示删除key1=1,key2=2的所有对象;
 *            key1,key2,key3取值全为0xFFFFFFFF时,表示删除所有对象。
 *
 * int  IsObjectExist (unsigned int key1, unsigned int key2, unsigned int key3)
 * 功能：查询单个对象是否存在
 * 输入：
 *       key1 外部关键字KEY1
 *       key2 外部关键字KEY2
 *       key3 外部关键字KEY3
 * 输出：无
 * 返回：0：不存在
 *       1：存在
 * 说明：用例保证入参合法取值
 *
 */
//可以和ObjMgt.cpp.backup做效率对比
#include <iostream>

unsigned int vec[10000][3];
unsigned int vec_temp[10000][3];
unsigned int vec_size = 0;

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
    for(unsigned int i=0;i<vec_size;i++)
    {
        if((vec[i][0]==key1) && (vec[i][1]==key2) && (vec[i][2]==key3))
        {
            return -1;
        }
    }

    vec[vec_size][0] = key1;
    vec[vec_size][1] = key2;
    vec[vec_size][2] = key3;

    vec_size++;

    return 0;
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
    unsigned int j = 0;

    for(unsigned int i=0;i<vec_size;i++)
    {
        if (((key1 == 0xFFFFFFFF) || (key1 == vec[i][0])) &&
            ((key2 == 0xFFFFFFFF) || (key2 == vec[i][1])) &&
            ((key3 == 0xFFFFFFFF) || (key3 == vec[i][2])))
        {
            continue;
        }
        else
        {
            vec_temp[j][0] = vec[i][0];
            vec_temp[j][1] = vec[i][1];
            vec_temp[j][2] = vec[i][2];
            j++;
        }
    }
    for(unsigned int i=0;i<j;i++)
    {
        vec[i][0] = vec_temp[i][0];
        vec[i][1] = vec_temp[i][1];
        vec[i][2] = vec_temp[i][2];
    }
    vec_size = j;

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
    for (unsigned int i=0;i<vec_size;i++)
    {
        if((vec[i][0]==key1) && (vec[i][1]==key2) && (vec[i][2]==key3))
        {
            return 1;
        }
    }

    return 0;
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
    vec_size=0;
    return;
}

int main() {
    {
        //接口未实现,用例将执行失败
        std::cout << (0 == AddObject(1, 2, 3)) << std::endl;
        std::cout << (0 == AddObject(1, 2, 4)) << std::endl;
        std::cout << (0 == AddObject(1, 5, 1)) << std::endl;
        std::cout << (0 == AddObject(1, 5, 3)) << std::endl;
        std::cout << (0 == AddObject(2, 3, 4)) << std::endl;
        std::cout << (0 == AddObject(2, 3, 5)) << std::endl;
        std::cout << (0 == AddObject(2, 4, 5)) << std::endl;
        std::cout << (0 == AddObject(2, 3, 6)) << std::endl;

        //已经存在,增加失败
        std::cout << (-1 == AddObject(2, 3, 6)) << std::endl;

        int result =IsObjectExist(1, 5, 3);
        std::cout << (1 == result) << std::endl;

        //使用通配符删除多个对象
        DeleteObject(2, 0xFFFFFFFF, 5);
        result = IsObjectExist(2, 3, 5);
        std::cout << (0 == result) << std::endl;
    }

    {
        std::cout << (-1 == AddObject(1, 2, 4)) << std::endl;
        std::cout << (1 == IsObjectExist(1, 2, 4)) << std::endl;
        DeleteObject(1, 2, 4);
        std::cout << (0 == IsObjectExist(1, 2, 4)) << std::endl;

    }

}

/*
// 另一种实现
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<unsigned>> vec;


int AddObject(unsigned int key1, unsigned int key2, unsigned int key3)
{
    if((key1 > 65536) || (key2 > 65536) || (key3 > 65536) || (vec.size() > 10000))
    {

        return -1;
    }
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

void DeleteObject(unsigned int key1, unsigned int key2, unsigned int key3)
{

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
            ++it;
        }
    }

    return ;
}


int IsObjectExist(unsigned int key1, unsigned int key2, unsigned int key3)
{
    if((key1 > 65536) || (key2 > 65536) || (key3 > 65536) || (vec.size() == 0))
    {

        return 0;
    }
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

void Clear(void)
{
    vec.clear();
    return;
}
*/