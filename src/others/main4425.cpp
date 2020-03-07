/**
 * 迭代器
 * 背景
 * 在科学计算中经常需要用到多维数组存储数据，例如，一维数组用来保存音频数据，二维数组可以用来保存灰阶影像，三维数组可以用来保存彩色影像，四维数组可以用来保存音乐会期间现场空间中的压力值，更高维的数组通常也是很有用的。
 * 通常，需要在这些数据上进行的一种典型操作叫切片，即选中一个区域，然后对该区域中的所有元素进行迭代操作。例如，对一个裁剪后的图像区域内的像素增加曝光值，或是统计某个时间段指定空间区域内压力值的变化规律。
 * 题目概述
 * 请完成如下任务：设计实现一种通用的迭代器，该迭代器用于在某个多维整型数组中，按实际存储顺序逐个遍历指定切片范围内的元素，以便进行任意操作。
 * 1）需要为该迭代器实现四个接口：初始化，获取当前元素在数组中的地址，跳到下一个，遍历是否结束。
 * 2）基于该迭代器，创建一个切片数组的拷贝，只包含指定切片内的元素，保持原有存储顺序不变。
 * 切片举例：
 * 	一个整数类型的三维数组 F[10][10][3]的切片SLICE[2:4][0:6][1:2]表示:
 * 	从左到右，第1维下标取值从2开始到4，第2维下标从0到6，第3维下标从1到2。
 * SLICE[2:4][0:6][1:2]由多维数组切片描述符结构SliceDesc来表示，见下一页
 * 定义说明
 * 多维数组切片描述符结构SliceDesc定义如下：
 * typedef struct
 * {
 *     int* first_element_of_orignal_array;//原始数组的第一个元素指针
 *     unsigned long coord_num; //维度个数，最大取值为MAX_COORD_NUM，值为10
 *     //原始数组从左到右各维度下标属性表示如下(从0到coord_num-1)
 *     unsigned long coord_spec[MAX_COORD_NUM];//原始数组每个维度下标的最大取值
 *     CoordSlice coord_slice[MAX_COORD_NUM];//切片在每个维度上的起止下标
 * }SliceDesc;
 * 坐标切片结构CoordSlice定义如下：
 * typedef struct
 * {
 *     unsigned long start;//起始下标
 *     unsigned long end; //结束下标
 * }CoordSlice;
 * 因此，上页中的数组F[10][10][3]的切片SLICE[2:4][0:6][1:2] 应表示为：
 * SliceDesc slice_desc = {&F[0][0][0],3,{9,9,2},{{2,4},{0,6},{1,2}}};
 * 请实现如下接口
 * int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator)
 * 功能：初始化一个切片迭代器，使其指向切片内的第一个元素
 * 输入：
 * 	       slice_desc    :  切片描述符指针（合法性由考生检查）
 *             slice_iterator：切片迭代器指针
 * 输出： slice_iterator：初始化后的切片迭代器的指针
 * 返回：0:成功，-1:失败
 * 说明：1）SliceIterator结构需要由考生自行设计和定义
 * 	       2）迭代器内存由调用者申请，大小仅为sizeof(SliceIterator)，函数内部不 得额外申请动态内存
 *             3）用例保证其他接口的输入不会是未初始化过的迭代器指针
 * int* SliceIteratorGetCurr(const SliceIterator* slice_iterator)
 * 功能：获取当前元素指针
 * 输入：
 * 	       slice_iterator:   迭代器指针
 * 输出：无
 * 返回：指向当前元素的指针。若迭代结束，应返回空指针。
 *
 * void SliceIteratorNext(SliceIterator* slice_iterator)
 * 功能：移动到下一个元素
 * 输入：
 * 	       slice_iterator：迭代器指针
 * 输出：
 * 	       slice_iterator：更新后的迭代器
 * 返回：无
 *
 * int SliceIteratorEnd(const SliceIterator* slice_iterator)
 * 功能：迭代是否结束
 * 输入：
 * 	      slice_iterator:   迭代器指针
 * 输出：无
 * 返回：1: 迭代已结束; 0:迭代未结束
 *
 * int CopySlice (const SliceDesc* slice_desc,
 * 		int** first_element_of_slice_array,
 * 		unsigned long* slice_element_num)
 * 功能：创建一个数组切片的拷贝
 * 输入：slice_desc:  切片描述符指针（合法性由考生检查）
 * 输出：
 *            first_element_of_slice_array:新的切片数组的第一个元素指针
 *            slice_element_num:新的切片数组中元素个数
 * 返回：
 *            0：成功，-1：失败
 * 说明：first_element_of_slice_array的内存由考生在函数内申请，调用者释放
 *
 */
#include <iostream>


#define MAX_COORD_NUM 10

typedef struct
{
    unsigned long start;//起始下标
    unsigned long end; //结束下标
}CoordSlice;

typedef struct
{
    int* first_element_of_orignal_array;//原始数组的第一个元素指针
    unsigned long coord_num; //维度个数，最大取值为MAX_COORD_NUM，值为10
    //原始数组从左到右各维度下标属性表示如下(从0到coord_num-1):
    unsigned long coord_spec[MAX_COORD_NUM];//原始数组每个维度下标的最大取值
    CoordSlice coord_slice[MAX_COORD_NUM];//切片在每个维度上的起止下标
}SliceDesc;

typedef struct
{
    //结构内容由考生自行设计定义
}SliceIterator;

/******************************************************************************
功能：初始化一个切片迭代器，使其指向切片内的第一个元素
输入：
	  slice_desc    ： 切片描述符指针（合法性由考生检查）
	  slice_iterator： 切片迭代器指针
输出：
	  slice_iterator： 初始化后的切片迭代器的指针
返回：
	  0：成功，-1：失败

说明：
1）SliceIterator结构需要由考生自行设计和定义
2）迭代器内存由调用者申请，大小仅为sizeof(SliceIterator)，函数内部不得额外申请动态内存
3）用例保证其他接口的输入不会是未初始化过的迭代器指针
******************************************************************************/
int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator)

{
    /* 在这里实现功能 */
    return 0;
}

/******************************************************************************
功能：获取当前元素指针
输入：
	  slice_iterator：迭代器指针
输出：无
返回：指向当前元素的指针。若迭代结束，应返回空指针。
******************************************************************************/
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator)
{
    /* 在这里实现功能 */
    return 0;
}

/******************************************************************************
功能：移动到下一个元素
输入：
	  slice_iterator  迭代器指针
输出：
	  slice_iterator  更新后的迭代器
返回：无
******************************************************************************/
void SliceIteratorNext(SliceIterator* slice_iterator)
{
    /* 在这里实现功能 */
    return;
}

/******************************************************************************
功能：迭代是否结束
输入：
	  slice_iterator:   迭代器指针
输出：无
返回：1: 迭代已结束; 0:迭代未结束
******************************************************************************/
int SliceIteratorEnd(const SliceIterator* slice_iterator)
{
    /* 在这里实现功能 */
    return 1;
}

/******************************************************************************
功能：创建一个数组切片的拷贝
输入：slice_desc:  切片描述符指针（合法性由考生检查）
输出：
	  first_element_of_slice_array:新的切片数组的第一个元素指针
	  slice_element_num:新的切片数组中元素个数
返回：0：成功，-1:失败

说明：first_element_of_slice_array内存在函数内申请，调用者释放
******************************************************************************/
int CopySlice(const SliceDesc* slice_desc,int** first_element_of_slice_array, unsigned long* slice_element_num)
{
    /* 在这里实现功能 */
    return 0;
}

int main() {
    {
        int A[10][10][3];
        int total = 0;
        int new_total = 0;

        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                for(int k=0;k<3;k++)
                {
                    A[i][j][k] = i*j*k;
                    total += A[i][j][k];
                }

        SliceIterator slice_iterator;
        SliceDesc slice_desc = {&A[0][0][0],3,{9,9,2},{{2,4},{0,6},{1,2}}};

        for(SliceIteratorInit(&slice_desc,&slice_iterator);1!=SliceIteratorEnd(&slice_iterator);SliceIteratorNext(&slice_iterator) )
        {
            *SliceIteratorGetCurr(&slice_iterator) += 1;
        }


        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                for(int k=0;k<3;k++)
                {
                    new_total += A[i][j][k];
                }

        std::cout << (new_total > total) << std::endl;

    }

    {
        int A[10][10][3];
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                for(int k=0;k<3;k++)
                {
                    A[i][j][k] = 1;
                }

        SliceDesc slice_desc = {&A[0][0][0],3,{9,9,2},{{2,4},{0,6},{1,2}}};
        int* first_element_of_slice_array = NULL;
        unsigned long slice_element_num = 0;

        int ret = CopySlice(&slice_desc,&first_element_of_slice_array,&slice_element_num);

        std::cout << (0 == ret) << std::endl;
        for(int i=0;i<slice_element_num; i++)
        {
            std::cout << (1 == first_element_of_slice_array[i]) << std::endl;
        }
        free(first_element_of_slice_array);
    }

}
