/*
华为面试
编写一个函数，要求输入年月日时分秒，输出该年月日时分秒的下一秒。
如输入：
2004年12月31日23时59分59秒
则输出：
2005年1月1日0时0分0秒

*/
void ResetTheTime(int *year,int *month,int *date,int *hour,int *minute,int*second)
{
    int dayOfMonth[12]= {31,28,31,30,31,30,31,31,30,31,30,31};

    if(*year < 0   || *month < 1 || *month > 12 ||
            *date < 1   || *date > 31 || *hour < 0   || *hour > 23 ||
            *minute < 0 ||*minute > 59|| *second <0 || *second >60)
        return;

    if((*year%400 == 0) || (*year%100 != 0 && *year%4 == 0))
        dayOfMonth[1] = 29;

    if(*second >= 60)
    {
        *second = 0;
        *minute += 1;

        if(*minute >= 60)
        {
            *minute = 0;
            *hour += 1;

            if(*hour >= 24)
            {
                *hour = 0;
                *date += 1;

                if(*date > dayOfMonth[*month-1])
                {
                    *date = 1;
                    *month += 1;

                    if(*month > 12)
                    {
                        *month=1;
                        *year += 1;
                    }
                }
            }
        }
    }

    return;
}
