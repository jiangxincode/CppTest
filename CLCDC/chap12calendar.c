/*加载头文件*/
#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <conio.h>

/*定义常量*/
/*左移键*/
#define LEFT 0x4b00
/*右移键*/
#define RIGHT 0x4d00
/*下移键*/
#define DOWN 0x5000
/*上移键*/
#define UP 0x4800
/*向上翻页移键*/
#define PAGEUP 0x4900
/*向下翻页移键*/
#define PAGEDOWN 0x5100
/*小写字母q*/
#define QLOWER 0x1071
/*大写字母Q*/
#define QUPPER 0x1051
/*空格键*/
#define SPACE 0x3920
/*Escape键*/
#define ESC 0x011b


/*定义全局变量*/
struct date sysTime;
int currentYear;
int currentMonth;
int currentDay;
int n_currentMon;
int n_lastMon;

/*-----------自定义函数-------------------------*/
void checkDate();
int isLeapyear(int year);
int getWeek(int year,int month,int day);

void printSpace(int n);
void printSeparator();
void printUsage();
void printWeek();
void printWeek2(int week);

void showCalendar(int year,int month,int day);

void getKeyValue();
/*--------------------------------------------*/

/*检查日期有效性函数*/
void checkDate()
{
    /*如果给定的日期中年份部分为负数或者0*/
    if(currentYear<=0)
    {
        gotoxy(1,27);
        printf("The year should be a positive number !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*以当前系统时间重新赋值*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*如果给定的日期中月份部分为负数,为0或者大于12*/
    if(currentMonth>12||currentMonth<1)
    {
        gotoxy(1,27);
        printf("The month should be a number between 1 and 12 !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*以当前系统时间重新赋值*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*如果给定的日期中天数部分为负数,为0或者大于31*/
    if(currentDay>31||currentDay<1)
    {
        gotoxy(1,27);
        printf("The day should be a number between 1 and 31 !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*以当前系统时间重新赋值*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
     }
}

/*判断是否是闰年函数*/
int isLeapyear(int year)
{
    /*闰年的判断:(1)year被4整除,并且year不被100整除
               或(2)year被4整除,并且year被400整除*/
    if(year%4==0&&year%100||year%400==0)
        return 1 ;
    else
        return 0 ;
}

/*根据给定日期计算星期函数*/
int getWeek(int year,int month,int day)
{
    int leapFlag;
    int week;
    int i ;
    /*该数组用于保存每个月的天数*/
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int count=0 ;

    /*判断给定年份是否是闰年*/
    leapFlag=isLeapyear(year);
    /*如果是闰年则2月份的日期应该29天*/
    if(leapFlag==1)
        a[2]++;
    /*计算从给定年份的1月1日到给定月份的1号之间的天数*/

    for(i=1;i<month;i++)
    {
        count+=a[i];
    }
    /*计算从给定年份的1月1日到给定日期之间的天数*/
    count+=day;
    /*计算星期*/
    week=(year+1+(year-1)/4+(year-1)/100+(year-1)/400+count)%7 ;
    return week ;
}

/*输出指定个数个空格函数*/
void printSpace(int n)
{
    int i ;
    for(i=0;i<n;i++)
        printf(" ");
}

/*输出分隔线函数*/
void printSeparator()
{
    int i ;
    for(i=0;i<38;i++)
    {
        printf("=");
    }
    printf("\n");
}

/*输出使用方法函数*/
void printUsage()
{
    gotoxy(45,3);
    /*设定字体颜色*/
    textcolor(YELLOW);
    /*送格式化输出至屏幕*/
    cprintf("-----------Usage-----------");

    gotoxy(45,5);
    textcolor(YELLOW);
    cprintf("YEAR");
    gotoxy(50,5);
    printf("  Up key( ) to increase;\n");
    gotoxy(50,7);
    printf("  Down key( ) to decrease.\n");

    gotoxy(45,9);
    textcolor(YELLOW);
    cprintf("MONTH:");
    gotoxy(50,9);
    printf("  Right key( ) to increase;\n");
    gotoxy(50,11);
    printf("  Left key( ) to decrease.\n");

    gotoxy(45,13);
    textcolor(YELLOW);
    cprintf("DAY");
    gotoxy(50,13);
    printf("  PageDown key to increase;\n");
    gotoxy(50,15);
    printf("  PageUp key to decrease.\n" );

    gotoxy(45,17);
    textcolor(YELLOW);
    cprintf("QUERY");
    gotoxy(50,17);
    printf("  Q/q key\n");

    textcolor(YELLOW);
    gotoxy(45,19);
    cprintf("RESET");
    gotoxy(50,19);
    printf("  SPACE key.\n");

    gotoxy(45,21);
    textcolor(YELLOW);
    cprintf("EXIT");
    gotoxy(50,21);
    printf("  Esc key\n");

    gotoxy(59,5);
    /*设置寄存器,表示在指定位置输出一次指定的字符*/
    _CX=01;
    _AH=0xa;
    /*指定输出字符为向上的箭头*/
    _AL=24;
    /*产生一次中断,输出向上的箭头*/
    geninterrupt(0x10);

    gotoxy(61,7);
    _CX=01;
    _AH=0xa;
    /*指定输出字符为向下的箭头*/
    _AL=25;
    geninterrupt(0x10);

    gotoxy(62,9);
    _CX=01;
    _AH=0xa;
    _AL=26;
    /*指定输出字符为向右的箭头*/
    geninterrupt(0x10);

    gotoxy(61,11);
    _CX=01;
    _AH=0xa;
    /*指定输出字符为向左的箭头*/
    _AL=27;
    geninterrupt(0x10);
    /*还原字体颜色*/
    textcolor(7);
}

/*根据系统日期输出星期函数*/
void printWeek()
{
    int day ;
    /*根据系统日期获得星期*/
    day=getWeek(currentYear,currentMonth,currentDay);
    textcolor(11);

    /*输出星期,0表示星期天,1表示星期一......6表示星期六*/
    if(day==0)
        cprintf("%d-%d-%d,Sunday!",currentYear,currentMonth,currentDay);
    if(day==1)
        cprintf("%d-%d-%d,Monday!",currentYear,currentMonth,currentDay);
    if(day==2)
        cprintf("%d-%d-%d,Tuesday!",currentYear,currentMonth,currentDay);
    if(day==3)
        cprintf("%d-%d-%d,Wednesday!",currentYear,currentMonth,currentDay);
    if(day==4)
        cprintf("%d-%d-%d,Thursday!",currentYear,currentMonth,currentDay);
    if(day==5)
        cprintf("%d-%d-%d,Friday!",currentYear,currentMonth,currentDay);
    if(day==6)
        cprintf("%d-%d-%d,Saturday!",currentYear,currentMonth,currentDay);
    textcolor(7);
}

/*输出指定星期函数*/
void printWeek2(int week)
{
    if(week==0)
        cprintf(",Sunday");
    if(week==1)
        cprintf(",Monday");
    if(week==2)
        cprintf(",Tuesday");
    if(week==3)
        cprintf(",Wendesday");
    if(week==4)
        cprintf(",Thursday");
    if(week==5)
        cprintf(",Friday");
    if(week==6)
        cprintf(",Staturday");
}

/*显示日历函数*/
void showCalendar(int year,int month,int day)
{
    int i;
    int j;
    /*输出的日期*/
    int outDay;
    int leapFlag;
    /*本月第一个星期中,在上月的天数*/
    int dayLastMon;
    int week;
    /*该数组用于保存每个月的天数*/
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    outDay=0;
    dayLastMon=0;
    week=0;

    /*判断给定年份是否是闰年*/
    leapFlag=isLeapyear(year);
    /*如果是闰年则2月应该是29天*/
    if(leapFlag==1)
    {
        a[2]++;
    }

    /*如果给定的日期中,天数大于该月的最大天数*/
    if(day>a[month])
    {
        printf("The number of this month's day is %d at most !\n",a[month]);
        printf("Press any key to continue......\n");
        getchar();
        getchar();
        /*以当前系统时间重新赋值*/
        year=sysTime.da_year;
        month=sysTime.da_mon;
        day=sysTime.da_day ;
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*当前月的天数*/
    n_currentMon=a[month];
    /*上一月的天数*/
    n_lastMon=a[month-1];
    /*根据给定日期,获取给定月份1号的星期*/
    week=dayLastMon=getWeek(year,month,1);


    /*清除文本模式窗口*/
    clrscr();
    printf("\nThe calendar of %d",year);
    textcolor(10);

    /*显示给定年份是否是闰年*/
    if(leapFlag==1)
        cprintf(" [leap year]",year);
    if(leapFlag==0)
        cprintf(" [not leap year]",year);
    printf("\n");
    textcolor(7);
    printSeparator();
    textcolor(YELLOW);

    /*输出月份提示,1-12分别表示1月到12月*/
    switch(month)
    {
    case 1 :
        cprintf(" January 1 ");
        break ;
    case 2 :
        cprintf(" February 2 ");
        break ;
    case 3 :
        cprintf(" March 3 ");
        break ;
    case 4 :
        cprintf(" April 4 ");
        break ;
    case 5 :
        cprintf(" May 5 ");
        break ;
    case 6 :
        cprintf(" June 6 ");
        break ;
    case 7 :
        cprintf(" July 7 ");
        break ;
    case 8 :
        cprintf(" August 8 ");
        break ;
    case 9 :
        cprintf(" September 9 ");
        break ;
    case 10 :
        cprintf(" October 10 ");
        break ;
    case 11 :
        cprintf(" Nevember 11 ");
        break ;
    case 12 :
        cprintf(" December 12");
        break ;
    }
    textcolor(7);
    printf("\n\n");
    textcolor(13);
    cprintf(" Sun Mon Tue Wed Thu Fri Sat");
    textcolor(7);
    printf("\n\n");

    /*因为一个月中最多跨度6个星期,所以循环从0到5*/
    for(i=0;i<6;i++)
    {
        /*如果是该月的第一个星期*/
        if(i==0)
        {
            /*第一个星期中还要7-dayLastMon天本月,有dayLastMon天在上个月,
            所以输出dayLastMon*4个空格符,每个日期在日历中占用4个空格*/
            printSpace(dayLastMon*4);
            /*剩余在本月的第一个星期中的天数为7-dayLastMon*/
            for(j=0;j<7-dayLastMon;j++)
            {
                /*到达day的前一天时,输出++outDay*/
                if(outDay==day-1)
                {
                    /*用黄色字体突出显示*/
                    textcolor(YELLOW);
                    cprintf(" [%d]",++outDay);
                    textcolor(7);
                }
                /*到达day当天时,并且不是星期天*/
                else if(outDay==day && week!=0)
                {
                    printf("%3d",++outDay);
                }
                /*到达day当天时,并且是星期天*/
                else
                {
                    printf("%4d",++outDay);
                }
                /*计算当天的星期,如果前一天是星期六(6),则当天是星期天(0),
                其他情况则直接星期加1*/
                week=(week<6)?week+1:0;
            }
            printf("\n\n");
        }

        /*如果不是该月的第一个星期*/
        else
        {
            /*则输出该星期中的7天*/
            for(j=0;j<7;j++)
            {
                /*输出的天数小于该月的最大天数*/
                if(outDay<a[month])
                {
                    /*到达day的前一天时,输出++outDay*/
                    if(outDay==day-1)
                    {
                        /*输出一位数字*/
                        if(outDay<9)
                        {
                            textcolor(YELLOW);
                            cprintf(" [%d]",++outDay);
                            textcolor(7);
                        }
                        /*输出两位数字*/
                        else
                        {
                            textcolor(YELLOW);
                            cprintf(" [%2d]",++outDay);
                            textcolor(7);
                        }
                    }
                    /*到达day当天时,并且不是星期天*/
                    else if(outDay==day && week!=0)
                    {
                        printf("%3d",++outDay);
                    }
                    /*到达day当天时,并且是星期天*/
                    else
                    {
                        printf("%4d",++outDay);
                    }
                }
                /*计算当天星期*/
                week=(week<6)?week+1:0;
            }
            printf("\n\n");
            if(outDay==a[month])break ;
        }
    }
    /*输出分隔线*/
    printSeparator();

    /*输出当前选择的日期和星期*/
    printf("The day you choose is:\n\n");
    printWeek();
    gotoxy(1,22);
    textcolor(10);
    cprintf("--------------------\n");
    textcolor(7);

    /*输出系统日期和星期*/
    printf("\nToday is: %d-%d-%d",sysTime.da_year,sysTime.da_mon,sysTime.da_day);
    printWeek2(getWeek(sysTime.da_year,sysTime.da_mon,sysTime.da_day));
    printf("\n\n");
    /*显示按键操作*/
    printUsage();
    gotoxy(1,25);
}

/*通过键盘调整日期函数*/
void getKeyValue()
{
    int key ;
    char ch;
    /*默认显示当前系统日期和星期*/
    currentYear=sysTime.da_year;
    currentMonth=sysTime.da_mon;
    currentDay=sysTime.da_day ;
    showCalendar(currentYear,currentMonth,currentDay);

    while(1)
    {
        /*获取键值,根据键值调整日历输出*/
        key=bioskey(0);
        /*右移键,增加月份*/
        if(key==RIGHT)
        {
            /*月份值在1－12之间，则直接加1*/
            if(currentMonth<12 && currentMonth>=1)
            {
                currentMonth++;
            }
            /*如果月份为12，则加1后进位，即年份加1，月份变为1*/
            else
            {
                currentYear++;
                currentMonth=1 ;
            }
        }
        /*左移键,减少月份*/
        if(key==LEFT)
        {
            /*月份值在1－12之间，则直接减1*/
            if(currentMonth<=12 && currentMonth>1)
            {
                currentMonth--;
            }
            /*如果月份为1，则减1后，到上一年，月份变为12*/
            else
            {
                currentYear--;
                currentMonth=12 ;
            }
        }
        /*上移键,增加年份*/
        if(key==UP)
        {
            currentYear++;
        }
        /*下移键,减少年份*/
        if(key==DOWN)
        {
            currentYear--;
        }
        /*上移键,减少天数*/
        if(key==PAGEUP)
        {
            /*当前日不是该月的第一天，则天数直接减1*/
            if(currentDay!=1)
            {
                currentDay--;
            }
            /*当前日是该月的第一天，并且是该年的第一个月（即1月1日），
            则天数减1后，变为上一年的最后一个月的最后一天（即12月31日）*/
            else if(currentDay==1 && currentMonth==1)
            {
                currentYear--;
                currentMonth=12 ;
                currentDay=31 ;
            }
            /*当前日是该年中某一个月的最后一天，则天数减1后，
            变为上个月的最后一天*/
            else
            {
                currentMonth--;
                currentDay=n_lastMon ;
            }
        }
        /*下移键,增加天数*/
        if(key==PAGEDOWN)
        {
            /*当前日不是该月的最后一天，则天数直接加1*/
            if(n_currentMon!=currentDay)
            {
                currentDay++;
            }
            /*当前日是该年的最后一天（即12月31日），则天数加1后，
            变为下一年的第一个月的第一天（即1月1日）*/
            else if(n_currentMon==currentDay && currentMonth==12)
            {
                currentYear++;
                currentMonth=1 ;
                currentDay=1 ;
            }
            /*当前日是该年中某一个月的最后一天，则天数加1后，
            变为下个月的第一天*/
            else
            {
                currentMonth++;
                currentDay=1 ;
            }
        }
        /*Q或者q键，表示查询指定日期的星期*/
        if(key==QLOWER||key==QUPPER)
        {

            {
                printf("Input date(eg,%d-%d-%d):",sysTime.da_year,sysTime.da_mon,sysTime.da_day);
                scanf("%d-%d-%d",&currentYear,&currentMonth,&currentDay);
                checkDate();
            }
        }
        /*空格键，重置到系统日期*/
        if(key==SPACE)
        {
            currentYear=sysTime.da_year;
            currentMonth=sysTime.da_mon;
            currentDay=sysTime.da_day ;
        }
        /*Escpe键退出系统*/
        if(key==ESC)
        {
            printf("Do you really want to quit?(Y/N)");
            ch=getchar();
            if(ch=='y'||ch=='Y')
                break ;
        }
        showCalendar(currentYear,currentMonth,currentDay);
    }
}

/*主函数*/
void main()
{
    /*清除文本模式窗口*/
    clrscr();
    /*设置屏幕显示方式*/
    _AL=03;
    _AH=0;
    geninterrupt(0x10);
    getdate(&sysTime);
    getKeyValue();
}
