/**
 * RTOSck-软中断调度器
 * 一、背景介绍
 *    RTOSck是中软欧拉开发部自研的一款嵌入式实时操作系统。主要面向中低端嵌入式环境，具有体积小、效率高、易维测等特定。为了实现无上下文及栈切换的高效业务处理，RTOSck支持一种称为软中断的线程机制。软中断具有与中断类似的特性，支持优先级及优先级抢占，处理过程不能挂起。与硬中断通过硬件激活不同，软中断需要通过主动调用软中断激活函数进行激活。
 * 二、题目描述
 *   请模拟实现一个简单软中断调度器。该软中断调度器支持32个优先级（0~31，数值越小，优先级越高）。并支持如下调度行为：
 *   1、在低优先级软中断中激活高优先级软中断，高优先级软中断将立即抢占执行；
 *   2、在高优先级软中断中激活低优先级软中断，需要在高优先级软中断执行完成后才能得到调度；
 *   3、低优先级软中断需要在所有直接或间接抢占的所有高优先级软中断执行完成后，再次恢复执行；
 *   4、同优先级软中断按照先入先出顺序进行调度；
 *   5、同一软中断可以连续多次激活，并响应同样多次。
 * 三、实现接口
 *   1、软中断创建
 *    int SwiCreate(unsigned int swiId, unsigned int prio, void (* proc)(void))；
 *     swiId为软中断ID，用于唯一标识一个软中断。测试用例保证取值范围[0-99]；
 *     prio为优先级；
 *     proc为软中断处理函数；处理函数里面可能会调用SwiActivate激活其它软中断，测试用例保证不会出现函数内部死循环，或者环状互相激活而造成死循环；
 *     成功返回0， 其它情况返回-1(重复创建、优先级无效、proc为空等）
 *   2、软中断激活
 *     int SwiActivate(unsigned int swiId)；
 *      swiId为待激活软中断ID；
 *      成功返回0， 其它情况返回-1（未创建等）
 *   3、清空所有信息
 *     void Clear(void)；
 *
 */

//review
#include<map>
#include<queue>
#include<iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class process{
public:
    int swiId;
    int prio;
    void (*proc)(void);
    friend bool operator <(process proc1,process proc2)// 我们在优先队里面需要进行比较 看哪个优先 还可以用函数来进行比较小
    {
        return proc1.prio>proc2.prio;
    }

};

map<int,process> processsavemap;
priority_queue<process> prqueue;
int currentID=100;//以后判断当前ID
/*************************************************************************************************
函数说明：创建软中断
输入参数：
      swiId： 创建软中断ID；
	  prio：  创建软中断优先级；
      proc：  创建软中断处理函数。
输出参数：无3
返回值  ：成功返回0， 其它情况返回-1
**************************************************************************************************/
int SwiCreate(unsigned int swiId, unsigned int prio, void (* proc)(void))
{
    //TODO: 添加代码...
    if(swiId>99||prio>31||proc==NULL)
        return -1;
    process add;
    add.swiId=swiId;
    add.prio=prio;
    add.proc=proc;
    if(processsavemap.count(add.swiId)!=0)//判断里面是不是存在着这个id
        return -1;
    else
        processsavemap[add.swiId]=add;// 如果符合条件则添加进map

    return 0;
}

/*************************************************************************************************
函数说明：软中断激活
输入参数：swiId： 待激活软中断ID
输出参数：无
返回值  ：成功返回0， 其它情况返回-1
**************************************************************************************************/
int SwiActivate(unsigned int swiId)
{
    //TODO: 添加代码...
    if(processsavemap.count(swiId)==0)//在map里面没有当然肯定要返回-1
        return -1;
    //开始的时候将 swiId加入到优先队列里面、、 这里有有排列好的优先
    prqueue.push(processsavemap[swiId]);
    // 运行  一直运行到优先队列里面没有的时候为止
    while(!prqueue.empty())
    {
        process topprocess=prqueue.top();
        if(currentID!=topprocess.swiId)
        {
            int beforeID=currentID;
            currentID=topprocess.swiId;
            topprocess.proc();
            currentID=beforeID;
            prqueue.pop();//出队列

        }
        else
        {
            break;//是同一个的时候当然继续就行了 不用管
        }

    }
    return 0;
}

/*************************************************************************************************
函数说明：清空所有的信息
输入参数：无
输出参数：无
返回值  ：无
**************************************************************************************************/
void Clear(void)
{
    //TODO: 添加代码...
    currentID=100;
    processsavemap.clear();
    while(!prqueue.empty())
    {
        prqueue.pop();
    }
}

static unsigned int * schedTrace;
static unsigned int   schedTraceCnt;
static unsigned int   schedTraceSize;

void SchedTraceInit(unsigned int * p, unsigned int size)
{
    schedTrace = p;
    schedTraceCnt = 0;
    schedTraceSize = size;
}

void SchedTraceRecord(unsigned int pid)
{
    if (schedTraceCnt < schedTraceSize)
        schedTrace[schedTraceCnt++] = pid;
}
\
static void TestCase01_proc1()
{
    SchedTraceRecord(1);
    SwiActivate(2);
    SchedTraceRecord(1);
}

static void TestCase01_proc2()
{
    SchedTraceRecord(2);
    SwiActivate(3);
    SchedTraceRecord(2);
}
static void TestCase01_proc3()
{
    SchedTraceRecord(3);
}

int main()
{
    int ret;
    unsigned int trace[10];
    unsigned int expect[] = {1, 2, 2, 3, 1};

    SchedTraceInit(trace, 10);
    Clear();

    ret = SwiCreate(1, 5, TestCase01_proc1);
    std::cout << (0 == ret) << std::endl;

    ret = SwiCreate(2, 3, TestCase01_proc2);
    std::cout << (0 == ret) << std::endl;

    ret = SwiCreate(3, 4, TestCase01_proc3);
    std::cout << (0 == ret) << std::endl;

    ret = SwiActivate(1);
    std::cout << (0 == ret) << std::endl;

    std::cout << (5 == schedTraceCnt) << std::endl;
    std::cout << (0 == memcmp(expect, trace, sizeof(expect))) << std::endl;
}
