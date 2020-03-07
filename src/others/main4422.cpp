/**
 * 地铁最佳路径
 * 背景概述
 * •城市的地铁网络由多条线路组成
 * •每条线路上有多个车站，线路自身没有交叉点
 * •线路间交叉或重叠时，共用车站，在这些车站上可相互换乘
 * •每条线路都是双向行车
 * •线路有两种：I形线和O形线
 * –I形线有两个端点，乘客在端点处只能乘坐开往另外一端的地铁，在非端点处则有两个方向可选择。（如图中8号线）
 * –O形线所有车站形成环，没有端点，乘客在任一站都有两个方向可选择。（如图中4号线）
 *  
 *  
 *  
 *  
 * 功能需求
 * 在地铁网络中任选一站为起点，任选另一站为终点，中途可换乘，要求输出 
 * 1）最短路线长度：从起点到终点经过的最少站数（站数计算不含起点，含终点）
 * 2）最短路线：满足最短路线长度要求的所有路线（可能有多条路线，每条路线从起点到终点顺序输出途经的所有站点，包括起点和终点） 
 * 3）最优路线：换乘次数最少的最短路线（可能有多条路线） 
 * 输入说明
 * 地铁网络中的每一个站点用一个唯一的ID标识，ID是一个32位正整数；
 * 一次输入一条线路，线路表示为一个站点ID数组；
 * –例如{2, 3, 6, 9, 10}，表示这是一条I形线，2和10为两端，数组元素顺序和从一端到另一端途经站点的顺序一致；
 * –例如{1, 3, 6, 7, 4, 1}，首尾站点一样，表示这是一条O形线，数组元素顺序和从站点1出发按某方向绕行一圈途经站点的顺序一致；
 * 两条线路中出现了相同站点（如上面的3、6），表示两条线路在这些站点可相互换乘。 
 *  
 * 示例
 * 某城市的地铁信息，如图 
 * Line1：{1,2,3,4,5};
 * Line2：{1,10,9,7,6};
 * Line3：{5,7,8};
 * Line4：{11,5};
 *  
 * 从起点站1到终点站11    
 * 1）最短路线长度是5
 * 2）最短路线有2条，分别是{1, 2, 3, 4,5,11}和{1,10,9,7,5,11}
 * 3）最优路线有1条：{1, 2, 3, 4,5,11} （换乘一次）
 *  
 *   
 *  
 * 请实现如下接口：
 * 说明：所有接口相互独立，没有调用顺序的要求（所谓“调用顺序”是例如：必须先调用2，再调用3，才能保证3的功能正确）
 * (1) AddLine
 * Description     
 *          增加某条地铁线路 
 *  Prototype
 *          void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)；
 *  Input Param
 *          LineNo 地铁线路号；
 *          StationNum 该条地铁线中的站点数目，由调用者保证不小于2；
 *          pStationArray 该条地铁线的所有站点信息，pStationArray指向的存储空间在函数外会被释  放，请自行申请存储空间；
 * Output Param 
 *          无
 *  Return Value
 *          无
 * (2) CalcMinPathLen
 * Description
 *          计算从起点站到终点站的最短路线长度 
 *  Prototype
 *          int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)；
 *  Input Param    
 *         SrcStation  起点站；
 *      DesStation 终点站；
 *  Output Param
 *         无
 *  Return Value
 *     起点站到终点站的最短路线长度
 *     -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
 * (3) SearchMinPathes
 * Description     
 *          输出从起点站到终点站的最短路线
 *  Prototype
 *          int SearchMinPathes(unsigned int SrcStation, unsigned int DesStation, unsigned int* pPathNum, unsigned int* pPathLen,unsigned int **ppPathes);
 *  Input Param
 *          SrcStation 起点站；
 *      DesStation 终点站；
 *  Output Param 
 *          pPathNum 最短路线条数; 
 *          pPathLen  最短路线长度;
 *          ppPathes 存储最短路线的内存地址，内存格式见下图,内存空间在本函数内申请，调用者释放；
 *  Return Value 
 *      0：成功
 *      -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
 *  
 * 
 * (4) SearchBestPathes（附加题）
 * Description     
 *          输出从起点站到终点站的最优路线
 *  Prototype
 *          int SearchBestPathes(unsigned int SrcStation,unsigned int DesStation,unsigned int *pPathNum, unsigned int* pPathLen,unsigned int** ppPathes);
 *  Input Param
 *          SrcStation 起点站；
 *      DesStation 终点站；
 *  Output Param
 *          pPathNum 最优路线条数; 
 *          pPathLen  最短路线长度;
 *          ppPathes 存储最短路线的内存地址，内存格式见下图,内存空间在本函数内申请，调用者释放；
 *  Return Value 
 *      0：成功
 *      -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
 *  
 * (5) Clear
 * Description     
 *          清空所有的线路信息
 *  Prototype
 *          void Clear();
 *  Input Param
 *          无
 *  Output Param
 *          无
 *  Return Value
 *          无
 * 
 * 算法提示
 * 说明：提示的并不是本题的唯一算法，考生可根据情况自行选择是否采用。
 * 1）最短路线长度算法提示
 * step1: 找到从起点出发，前进一站能到达的所有车站，记为SET1，若终点已包含在SET1中，则最短路线长度为1。
 * step2：对SET1中所有车站，找到前进一站能到达的所有车站，记为SET2，若终点已包含在SET2中，则最短路线长度为2。
 * ...以此类推...
 * stepn：对SETn-1中所有车站，找到前进一站能到达的所有车站，记为SETn，若终点已包含在SETn中，则最短路线长度为n。
 * 2）最短路线算法提示
 * 最短路线长度算法在遍历过程中未记录路径信息，需要增加用作记录的数据结构设计，该数据结构在最短路线长度的计算过程中生成。
 * 3）最优路线算法提示
 * 在求出最短路线的基础上，对每一条路线计算换乘最小次数，从所有路线方案中选择最优解。
 * 
 */




#include<iostream>
#include<cstring>
//#include<algorithm>
//#include<cmath>
#include<vector>
#include<queue>
//#include<stack>
//#include<iomanip>
using namespace std;

#define MAX 535
int flag[MAX];
vector<int>station_reach[MAX];
static vector<int>myfront[MAX];
/*******************************************************************************************************************
函数说明： 增加某条地铁线路
函数原型： void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)；
输入参数：
           LineNo        地铁线路号；
           StationNum    该条地铁线中的站点数目，由调用者保证不小于2；
           pStationArray 该条地铁线的所有站点信息，pStationArray指向的存储空间在函数外会被释放，请自行申请存储空间；
输出参数： 无
返回值  ： 无
********************************************************************************************************************/
void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)
{
    /* 在这里实现功能 */

    int i;
    for(i=1;i<StationNum;i++)
    {
        station_reach[pStationArray[i]].push_back(pStationArray[i-1]);
        station_reach[pStationArray[i-1]].push_back(pStationArray[i]);
    }

    return;

}

/*********************************************************************************************************************
函数说明：计算从起点站到终点站的最短路线长度
函数原型：int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)；
输入参数：
          SrcStation  起点站；
          DesStation 终点站；
输出参数：无
返回值  ：
          起点站到终点站的最短路线长度
          -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
**********************************************************************************************************************/
int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)
{

    /* 在这里实现功能 */
    if(SrcStation==DesStation)return -1;
    int i,j,newsta;
    int minlen=1,count=0;
    queue<int>qsta;
    /*
     for(i=1;i<11;i++)
     {
         cout<<i<<"站"<<":";
         for(j=0;j<station_reach[i].size();j++)
             cout<<station_reach[i][j]<<" ";
         cout<<endl;
     }
     cout<<endl;
 */
    memset(flag,0,sizeof(flag));

    for(i=0;i<station_reach[SrcStation].size();i++)
    {
        if(station_reach[SrcStation][i]==DesStation)return minlen;
        qsta.push(station_reach[SrcStation][i]);
        //count++;
    }
    flag[SrcStation]=1;
    int ss=qsta.size();
    while(!qsta.empty())
    {

        minlen++;
        count=qsta.size();
        while(count--){
            newsta=qsta.front();
            flag[newsta]=1;
            for(i=0;i<station_reach[newsta].size();i++)
            {
                if(station_reach[newsta][i]==DesStation)return minlen;
                if(flag[station_reach[newsta][i]]==0)qsta.push(station_reach[newsta][i]);
            }
            qsta.pop();
        }
    }
    if(qsta.empty()) return -1;

    return 0;

};




/**********************************************************************************************************
函数说明：输出从起点站到终点站的最短路线
函数原型：int SearchMinPathes(unsigned int SrcStation,
                              unsigned int DesStation,
                              unsigned int* pPathNum,
                              unsigned int* pPathLen,
                              unsigned int **ppPathes);
输入参数：
          SrcStation 起点站；
          DesStation 终点站；
          Output Param
          pPathNum 最短路线条数;
          pPathLen  最短路线长度;
          ppPathes 存储最短路线的内存地址，内存空间在本函数内申请，调用者释放，内存空间的存储格式请见PPT要求；
返回值  ：
          0 ：成功
          -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）

************************************************************************************************************/
void dfs(unsigned int SrcStation,
         unsigned int DesStation,
         unsigned int minlen,
         unsigned int *pPathLen,
         unsigned int* pPathNum,
         unsigned int **pPathes
)
{
    int i,j;

    if(minlen==1)
    {
        if(myfront[DesStation][0]==SrcStation)
        {
            (*pPathNum)++;
            pPathes[(*pPathNum)-1]=(unsigned int *)malloc((*pPathLen+1)*sizeof(unsigned int));
            memset(pPathes[(*pPathNum)-1],0,(*pPathLen+1)*sizeof(unsigned int));
            pPathes[(*pPathNum)-1][minlen-1]=SrcStation;
            pPathes[(*pPathNum)-1][minlen]=DesStation;

            //cout<<DesStation<<" "<<minlen<<" "<<*pPathNum<<endl;
        }
        return;
    }

    for(i=0;i<myfront[DesStation].size();i++)
    {
        j=myfront[DesStation][i];
        //cout<<j<<" "<<minlen-1<<endl;
        dfs(SrcStation,j,minlen-1,pPathLen,pPathNum,pPathes);
        pPathes[(*pPathNum)-1][minlen]=DesStation;
        if(*pPathNum>1 && pPathes[(*pPathNum)-2][minlen]==0)
            pPathes[(*pPathNum)-2][minlen]=DesStation;
    }
}

int SearchMinPathes(unsigned int SrcStation,
                    unsigned int DesStation,
                    unsigned int* pPathNum,
                    unsigned int* pPathLen,
                    unsigned int **ppPathes)
{
    /* 在这里实现功能 */

    if(SrcStation==DesStation)return -1;
    int i,j,newsta,findflag=0;
    int minlen=1,count=0;
    int pathnum=0;
    int sum=0;
    queue<int>qsta;


    for(i=0;i<MAX;i++)
        myfront[i].clear();

    memset(flag,0,sizeof(flag));

    for(i=0;i<station_reach[SrcStation].size();i++)
    {
        myfront[station_reach[SrcStation][i]].push_back(SrcStation);
        if(station_reach[SrcStation][i]==DesStation)
        {
            *pPathNum=1;
            *pPathLen=1;
            *ppPathes=(unsigned int *)malloc(2*sizeof(unsigned int));
            (*ppPathes)[0]=SrcStation;
            (*ppPathes)[1]=DesStation;
            return 0;
        }
        qsta.push(station_reach[SrcStation][i]);
        //count++;
    }
    flag[SrcStation]=1;

    findflag=0;
    while(!qsta.empty() && !findflag)
    {

        minlen++;
        count=qsta.size();
        while(count--){
            newsta=qsta.front();
            flag[newsta]=1;
            for(i=0;i<station_reach[newsta].size();i++)
            {
                if(flag[station_reach[newsta][i]]==0)
                    for(j=0;j<myfront[station_reach[newsta][i]].size();j++)
                        if(myfront[station_reach[newsta][i]][j]==newsta)break;
                if(j==myfront[station_reach[newsta][i]].size())
                    myfront[station_reach[newsta][i]].push_back(newsta);
                if(station_reach[newsta][i]==DesStation)
                {
                    findflag=1;
                    break;
                    /*
                    *ppPathes=(unsigned int *)malloc((minlen+1)*sizeof(unsigned int));
                    (*ppPathes)[minlen]=DesStation;
                    for(j=minlen-1,k=DesStation;j>=0;j--)
                        (*ppPathes)[j]=front[(*ppPathes)[j+1]];
                    pathnum++;
                    */
                }
                if(flag[station_reach[newsta][i]]==0)qsta.push(station_reach[newsta][i]);
            }
            qsta.pop();
        }
    }

    //if(qsta.empty()) return -1;
/*
	for(i=1;i<12;i++){
		cout<<i<<"站：";
	   for(j=0;j<myfront[i].size();j++)
		   cout<<myfront[i][j]<<" ";
	   cout<<endl;
	   }
	   */
    if(findflag)
    {
        *pPathLen=minlen;
        *pPathNum=0;
        dfs(SrcStation,DesStation,minlen,pPathLen,pPathNum,ppPathes);

    }
    else return -1;
    //cout<<minlen<<" "<<DesStation<<" "<<sum<<endl;
    return 0;
}


/*************************************************************************************************
函数说明：输出从起点站到终点站的最优路线
函数原型：int SearchBestPathes(unsigned int SrcStation,
                               unsigned int DesStation,
                               unsigned int *pPathNum,
                               unsigned int* pPathLen,
                               unsigned int** ppPathes);
输入参数：
         SrcStation 起点站；
         DesStation 终点站；
         Output Param
         pPathNum 最优路线条数;
         pPathLen  最短路线长度;
         ppPathes 存储最短路线的内存地址，内存格式见下图,内存空间在本函数内申请，调用者释放；
返回值 ：
         0：成功
         -1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
**************************************************************************************************/
int SearchBestPathes(unsigned int SrcStation,
                     unsigned int DesStation,
                     unsigned int *pPathNum,
                     unsigned int* pPathLen,
                     unsigned int** ppPathes)
{
    /* 在这里实现功能 */

    return 0;
}

/*************************************************************************************************
函数说明：清空所有的线路信息
函数原型：void Clear();
输入参数：无
输出参数：无
返回值  ：无
**************************************************************************************************/
void Clear()
{

    /* 在这里实现功能 */
//	vector<int>station_reach[MAX];
    for(int i=0;i<MAX;i++)
        station_reach[i].clear();
    return ;

};

int main() {
    unsigned int Line1[] = {1,2,3,4,5};
    int Ret;

    AddLine(1,5,&Line1[0]);

    Ret = CalcMinPathLen(2,4);
    std::cout << (2 == Ret) << std::endl;

    Clear();
}
