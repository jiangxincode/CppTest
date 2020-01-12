#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_YEAR_LIMIT 9999
#define MAX_MONTH_LIMIT 12
#define MAX_DAY_LIMIT 31

typedef struct _DATE_
{
    int day;
    int month;
    int year;
} DATE;


/**计算所给日期是当年的第几天*/
int day_of_year(const DATE date)
{
    int days = 0; //记录所求天数

    /*年份合法性判断*/
    if((date.year <= 0) || (date.year > MAX_YEAR_LIMIT))
    {
        return -1;
    }

    /*月份合法性判断*/
    if((date.month <= 0) || (date.month > MAX_MONTH_LIMIT))
    {
        return -1;
    }

    /*天数合法性判断*/
    if((date.day <= 0) || (date.day > MAX_DAY_LIMIT))
    {
        return -1;
    }

    /*计算普通年份天数*/
    switch(date.month)
    {
    case 1:
        days = date.day;
        break;

    case 2:
        days = 31 + date.day;
        break;

    case 3:
        days = 31 + 28 + date.day;
        break;

    case 4:
        days = 31*2 + 28 + date.day;
        break;

    case 5:
        days = 31*2 + 30 + 28 + date.day;
        break;

    case 6:
        days = 31*3 + 30 + 28 + date.day;
        break;

    case 7:
        days = 31*3 + 30*2 + 28 + date.day;
        break;

    case 8:
        days = 31*4 + 30*2 + 28 + date.day;
        break;

    case 9:
        days = 31*5 +30*2 + 28 + date.day;
        break;

    case 10:
        days = 31*5 + 30*3 + 28 + date.day;
        break;

    case 11:
        days = 31*6 + 30*3 + 28 + date.day;
        break;

    case 12:
        days = 31*6 + 30*4 + 28 + date.day;
        break;

    default:
        return -1;
    }

    /*计算闰年天数*/
    if(((date.year % 4 == 0) && (date.year %100 != 0)) ||
            (date.year % 400 == 0))
    {
        if(date.month > 2)
        {
            days++;
        }
    }

    return days;
}

int main1154()
{
    DATE date;
    /**TestCase01 2001/01/01*/
    date.year = 2001;
    date.month = 1;
    date.day = 1;
    day_of_year(date) == 1 ? printf("TestCase01: success\n") : printf("TestCase01: fail\n");
    /**TestCase02 2000/03/01*/
    date.year = 2000;
    date.month = 3;
    date.day = 1;
    day_of_year(date) == 61 ? printf("TestCase02: success\n") : printf("TestCase02: fail\n");
    /**TestCase03 2500/03/01*/
    date.year = 2500;
    date.month = 3;
    date.day = 1;
    day_of_year(date) == 60 ? printf("TestCase03: success\n") : printf("TestCase03: fail\n");
    /**TestCase04 10000/03/01*/
    date.year = 10000;
    date.month = 3;
    date.day = 1;
    day_of_year(date) == -1 ? printf("TestCase04: success\n") : printf("TestCase04: fail\n");
    /**TestCase05 -1/03/01*/
    date.year = -1;
    date.month = 3;
    date.day = 1;
    day_of_year(date) == -1 ? printf("TestCase05: success\n") : printf("TestCase05: fail\n");
    /**TestCase06 2001/0/01*/
    date.year = 2001;
    date.month = 0;
    date.day = 1;
    day_of_year(date) == -1 ? printf("TestCase06: success\n") : printf("TestCase06: fail\n");
    return 0;
}

