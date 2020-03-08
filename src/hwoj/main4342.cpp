/**
 * N皇后 Queen
 * •	要求任何两个皇后不同行，不同列也不再同一条斜线上。我们能不能把N个皇后放在棋盘(N×N)上，它们中的任何一个都无法攻击其余的皇后?请编写程序找出一共有几种方法。
 * 详细描述：
 * •	接口说明
 * 原型：
 * •	intPlaceQueenMethodNum(int n);
 * 输入参数：
 *     int n: 皇后的个数
 * 返回值：
 *         int: 放置n皇后方案的个数
 */
#include <math.h>
#include <iostream>


static const int N = 100;
class Queen
{
public:
    Queen()
    {
        count=0;
    }
    int Check(int i,int k); //判断位置是否符合要求
    void Queens(int k,int n); //递归调用
    int getCount()
    {
        return count; //计数
    }
private:
    int q[N]; //记录皇后的位置
    int count;
};

//计算出皇后的排列，k是当前皇后数量，n是数量上限
void Queen::Queens(int k,int n)
{
    if(k>n) //如果达到要求的数量输出皇后排列
    {
        count ++;
    }
    else //否则在适当的位置添加一个新皇后
    {
        for(int j=1; j<=n; j++)
            if(Check(k,j)) //判断第k个皇后放置在第j列是否满足条件
            {
                q[k]=j; //记录第k个皇后在第几列
                Queens(k+1,n); //放置下一行的皇后
            }
    }
}
int Queen::Check(int k,int j)
{
    for(int i=1; i<k; i++)
    {
        //q[i]==j检验第i个皇后是否在第j列
        //abs(i-k)==abs(q[i]-j)检验第i个皇后与第k个皇后位置是否在一条斜线上
        //检验是否在一条斜线的方法是判断行与列的差值相同
        if((q[i]==j) || abs(i-k)==abs(q[i]-j))
            return 0;
    }

    return 1;
}


/*
功能: 求解放置8皇后方案的个数。
输入：
    无
返回：
    int：放置8皇后方案的个数
*/

int PlaceQueenMethodNum(int n)
{
    /*在这里实现功能*/
    Queen Q;
    Q.Queens(1, n);
    return Q.getCount();
}

int main()
{
    int  iRet;

    iRet = PlaceQueenMethodNum(3);

    std::cout << (iRet == 0) << std::endl;
}


