/**
 * 蜂窝小区最短距离
 * 详细说明见：<https://blog.csdn.net/nys001/article/details/12637201>
 */
//review
#include "iostream"

struct POS
{
    POS(int val):x(0),y(0),z(0)
    {
        int i = 0, v = 1;
        //find the ring (i) that val belongs to.
        for (; v<val; v+=6*(++i));
        //get x,y,z;
        if(i > 0)
        {
            int side = (v-val)/i;
            int step = (v-val)%i;
            switch (side)
            {
                case 0:
                    x = i;
                    y = -i+step;
                    z = x+y;
                    break;
                case 1:
                    z = i;
                    y = step;
                    x = z-y;
                    break;
                case 2:
                    y = i;
                    z = i-step;
                    x = z-y;
                    break;
                case 3:
                    x = -i;
                    y = i-step;
                    z = x+y;
                    break;
                case 4:
                    z = -i;
                    y = -step;
                    x = z-y;
                    break;
                case 5:
                    y = -i;
                    z = -i+step;
                    x = z-y;
                    break;
                default:
                    break;
            }
        }
    }
    int operator - (const POS &p) const
    {
        int i = x>p.x ? x-p.x : p.x-x;
        int j = y>p.y ? y-p.y : p.y-y;
        int k = z>p.z ? z-p.z : p.z-z;
        return i>j ? (i>k?i:k) : (j>k?j:k);
    }
private:
    int x, y, z;
};


static int g_max;
/************************************************************************
Description  : 初始化蜂窝小区信息
Prototype    : void InitCellularDistrict(int iMaxSeqValue)
               Input Param  :iMaxSeqValue 蜂窝小区的最大值编号，注：编号从1开始
              Output Param : 无
              Return Value : 成功返回0，失败返回-1
************************************************************************/
int InitCellularDistrict(int iMaxSeqValue)
{
    if (iMaxSeqValue>0 && iMaxSeqValue<=100000)
    {
        g_max = iMaxSeqValue;
        return 0;
    }
    return -1;
}


/************************************************************************
Description  : 计算出蜂窝小区指定两点（编号值）之间的最短距离
Prototype    : int GetShortestPathLength(int iFirstValue, intiSecondValue)
               Input Param  :iFirstValue 起点编号值， iSecondValue 终点编号值
              Output Param : 无
              Return Value : 计算成功返回最短距离，失败返回-1
************************************************************************/
int GetShortestPathLength(int iFirstValue, int iSecondValue)
{
    if (0<iFirstValue && iFirstValue<=g_max
        && 0<iSecondValue &&iSecondValue<=g_max)
    {
        POS first(iFirstValue), second(iSecondValue);
        return first-second;
    }
    return -1;
}


/************************************************************************
Description  : 清空相关信息
Prototype    : void Clear()
               Input Param  : 无
              Output Param : 无
              Return Value : 无
************************************************************************/
void Clear()
{
    g_max = 0;
}

int main() {
    InitCellularDistrict(60);
    std::cout << (GetShortestPathLength(19, 30) == 5) << std::endl;
    Clear();
}
