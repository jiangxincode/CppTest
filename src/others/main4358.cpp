/**
 * 求车速
 * 一辆以固定速度行驶的汽车，司机在上午10点看到里程表(里程表有6位)上的读数是一个对称数(即这个数从左向右读和从右向左读是完全一样的，例如95859公里)。两小时后里程表上出现了一个新的对称数。问该车的速度(公里/小时)是多少？
 *
 * 接口说明
 * 原型：
 *     int CalcSpeedOfCar(int iCurrentMileage, int * piCarSpeed);
 * 输入参数：
 *     int pcCurrentMileage:当前里程数(为对称数) (pcCurrentMileage ≤ 999999)
 *
 * 输出参数：
 *     int * piCarSpeed:汽车速度
 *
 * 返回值：
 *     0：汽车速度计算成功
 *         1：汽车速度计算失败，在里程表的范围内找不到下一个对称数
 *
 */
# include <iostream>

using namespace std;


/*
功能: 根据里程计算车速
原型：
    int CalcSpeedOfCar(int iCurrentMileage, int * piCarSpeed);

输入参数：
    int pcCurrentMileage:当前里程数(为对称数)(pcCurrentMileage ≤ 999999)

返回值：
    汽车速度(公里/小时)
*/

bool isReverseEqual(int num)
{
    int num_reverse,temp;
    temp=num;
    num_reverse=0;

    while(temp)
    {
        num_reverse=num_reverse*10+temp%10;
        temp/=10;
    }

    return(num==num_reverse);
}


int CalcSpeedOfCar(int iCurrentMileage, int * piCarSpeed)
{
    /*在这里实现功能*/

    if(!isReverseEqual(iCurrentMileage))
    {
        return 1;
    }
    for(int i=iCurrentMileage+1;i<1000000;i++)
    {
        if(isReverseEqual(i))
        {
            *piCarSpeed = (i-iCurrentMileage)/2;
            return 0;
        }

    }
    return 1;
}


int main()
{
    int iRet;
    int iCarSpeed;

    iRet = CalcSpeedOfCar(95859, &iCarSpeed);

    std::cout << (0 == iRet) << std::endl;
    std::cout << (50 == iCarSpeed) << std::endl;
}
