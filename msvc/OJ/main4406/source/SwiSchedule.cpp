//review
#include<map>
#include<queue>

using namespace std;

class process
{
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
