/*����ͷ�ļ�*/
#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <conio.h>

/*���峣��*/
/*���Ƽ�*/
#define LEFT 0x4b00
/*���Ƽ�*/
#define RIGHT 0x4d00
/*���Ƽ�*/
#define DOWN 0x5000
/*���Ƽ�*/
#define UP 0x4800
/*���Ϸ�ҳ�Ƽ�*/
#define PAGEUP 0x4900
/*���·�ҳ�Ƽ�*/
#define PAGEDOWN 0x5100
/*Сд��ĸq*/
#define QLOWER 0x1071
/*��д��ĸQ*/
#define QUPPER 0x1051
/*�ո��*/
#define SPACE 0x3920
/*Escape��*/
#define ESC 0x011b


/*����ȫ�ֱ���*/
struct date sysTime;
int currentYear;
int currentMonth;
int currentDay;
int n_currentMon;
int n_lastMon;

/*-----------�Զ��庯��-------------------------*/
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

/*���������Ч�Ժ���*/
void checkDate()
{
    /*�����������������ݲ���Ϊ��������0*/
    if(currentYear<=0)
    {
        gotoxy(1,27);
        printf("The year should be a positive number !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*�Ե�ǰϵͳʱ�����¸�ֵ*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*����������������·ݲ���Ϊ����,Ϊ0���ߴ���12*/
    if(currentMonth>12||currentMonth<1)
    {
        gotoxy(1,27);
        printf("The month should be a number between 1 and 12 !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*�Ե�ǰϵͳʱ�����¸�ֵ*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*�����������������������Ϊ����,Ϊ0���ߴ���31*/
    if(currentDay>31||currentDay<1)
    {
        gotoxy(1,27);
        printf("The day should be a number between 1 and 31 !\n");
        gotoxy(1,28);
        printf("Press any key to continue......");
        getchar();
        getchar();
        /*�Ե�ǰϵͳʱ�����¸�ֵ*/
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
     }
}

/*�ж��Ƿ������꺯��*/
int isLeapyear(int year)
{
    /*������ж�:(1)year��4����,����year����100����
               ��(2)year��4����,����year��400����*/
    if(year%4==0&&year%100||year%400==0)
        return 1 ;
    else
        return 0 ;
}

/*���ݸ������ڼ������ں���*/
int getWeek(int year,int month,int day)
{
    int leapFlag;
    int week;
    int i ;
    /*���������ڱ���ÿ���µ�����*/
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int count=0 ;

    /*�жϸ�������Ƿ�������*/
    leapFlag=isLeapyear(year);
    /*�����������2�·ݵ�����Ӧ��29��*/
    if(leapFlag==1)
        a[2]++;
    /*����Ӹ�����ݵ�1��1�յ������·ݵ�1��֮�������*/

    for(i=1;i<month;i++)
    {
        count+=a[i];
    }
    /*����Ӹ�����ݵ�1��1�յ���������֮�������*/
    count+=day;
    /*��������*/
    week=(year+1+(year-1)/4+(year-1)/100+(year-1)/400+count)%7 ;
    return week ;
}

/*���ָ���������ո���*/
void printSpace(int n)
{
    int i ;
    for(i=0;i<n;i++)
        printf(" ");
}

/*����ָ��ߺ���*/
void printSeparator()
{
    int i ;
    for(i=0;i<38;i++)
    {
        printf("=");
    }
    printf("\n");
}

/*���ʹ�÷�������*/
void printUsage()
{
    gotoxy(45,3);
    /*�趨������ɫ*/
    textcolor(YELLOW);
    /*�͸�ʽ���������Ļ*/
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
    /*���üĴ���,��ʾ��ָ��λ�����һ��ָ�����ַ�*/
    _CX=01;
    _AH=0xa;
    /*ָ������ַ�Ϊ���ϵļ�ͷ*/
    _AL=24;
    /*����һ���ж�,������ϵļ�ͷ*/
    geninterrupt(0x10);

    gotoxy(61,7);
    _CX=01;
    _AH=0xa;
    /*ָ������ַ�Ϊ���µļ�ͷ*/
    _AL=25;
    geninterrupt(0x10);

    gotoxy(62,9);
    _CX=01;
    _AH=0xa;
    _AL=26;
    /*ָ������ַ�Ϊ���ҵļ�ͷ*/
    geninterrupt(0x10);

    gotoxy(61,11);
    _CX=01;
    _AH=0xa;
    /*ָ������ַ�Ϊ����ļ�ͷ*/
    _AL=27;
    geninterrupt(0x10);
    /*��ԭ������ɫ*/
    textcolor(7);
}

/*����ϵͳ����������ں���*/
void printWeek()
{
    int day ;
    /*����ϵͳ���ڻ������*/
    day=getWeek(currentYear,currentMonth,currentDay);
    textcolor(11);

    /*�������,0��ʾ������,1��ʾ����һ......6��ʾ������*/
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

/*���ָ�����ں���*/
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

/*��ʾ��������*/
void showCalendar(int year,int month,int day)
{
    int i;
    int j;
    /*���������*/
    int outDay;
    int leapFlag;
    /*���µ�һ��������,�����µ�����*/
    int dayLastMon;
    int week;
    /*���������ڱ���ÿ���µ�����*/
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    outDay=0;
    dayLastMon=0;
    week=0;

    /*�жϸ�������Ƿ�������*/
    leapFlag=isLeapyear(year);
    /*�����������2��Ӧ����29��*/
    if(leapFlag==1)
    {
        a[2]++;
    }

    /*���������������,�������ڸ��µ��������*/
    if(day>a[month])
    {
        printf("The number of this month's day is %d at most !\n",a[month]);
        printf("Press any key to continue......\n");
        getchar();
        getchar();
        /*�Ե�ǰϵͳʱ�����¸�ֵ*/
        year=sysTime.da_year;
        month=sysTime.da_mon;
        day=sysTime.da_day ;
        currentYear=sysTime.da_year;
        currentMonth=sysTime.da_mon;
        currentDay=sysTime.da_day ;
    }

    /*��ǰ�µ�����*/
    n_currentMon=a[month];
    /*��һ�µ�����*/
    n_lastMon=a[month-1];
    /*���ݸ�������,��ȡ�����·�1�ŵ�����*/
    week=dayLastMon=getWeek(year,month,1);


    /*����ı�ģʽ����*/
    clrscr();
    printf("\nThe calendar of %d",year);
    textcolor(10);

    /*��ʾ��������Ƿ�������*/
    if(leapFlag==1)
        cprintf(" [leap year]",year);
    if(leapFlag==0)
        cprintf(" [not leap year]",year);
    printf("\n");
    textcolor(7);
    printSeparator();
    textcolor(YELLOW);

    /*����·���ʾ,1-12�ֱ��ʾ1�µ�12��*/
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

    /*��Ϊһ�����������6������,����ѭ����0��5*/
    for(i=0;i<6;i++)
    {
        /*����Ǹ��µĵ�һ������*/
        if(i==0)
        {
            /*��һ�������л�Ҫ7-dayLastMon�챾��,��dayLastMon�����ϸ���,
            �������dayLastMon*4���ո��,ÿ��������������ռ��4���ո�*/
            printSpace(dayLastMon*4);
            /*ʣ���ڱ��µĵ�һ�������е�����Ϊ7-dayLastMon*/
            for(j=0;j<7-dayLastMon;j++)
            {
                /*����day��ǰһ��ʱ,���++outDay*/
                if(outDay==day-1)
                {
                    /*�û�ɫ����ͻ����ʾ*/
                    textcolor(YELLOW);
                    cprintf(" [%d]",++outDay);
                    textcolor(7);
                }
                /*����day����ʱ,���Ҳ���������*/
                else if(outDay==day && week!=0)
                {
                    printf("%3d",++outDay);
                }
                /*����day����ʱ,������������*/
                else
                {
                    printf("%4d",++outDay);
                }
                /*���㵱�������,���ǰһ����������(6),������������(0),
                ���������ֱ�����ڼ�1*/
                week=(week<6)?week+1:0;
            }
            printf("\n\n");
        }

        /*������Ǹ��µĵ�һ������*/
        else
        {
            /*������������е�7��*/
            for(j=0;j<7;j++)
            {
                /*���������С�ڸ��µ��������*/
                if(outDay<a[month])
                {
                    /*����day��ǰһ��ʱ,���++outDay*/
                    if(outDay==day-1)
                    {
                        /*���һλ����*/
                        if(outDay<9)
                        {
                            textcolor(YELLOW);
                            cprintf(" [%d]",++outDay);
                            textcolor(7);
                        }
                        /*�����λ����*/
                        else
                        {
                            textcolor(YELLOW);
                            cprintf(" [%2d]",++outDay);
                            textcolor(7);
                        }
                    }
                    /*����day����ʱ,���Ҳ���������*/
                    else if(outDay==day && week!=0)
                    {
                        printf("%3d",++outDay);
                    }
                    /*����day����ʱ,������������*/
                    else
                    {
                        printf("%4d",++outDay);
                    }
                }
                /*���㵱������*/
                week=(week<6)?week+1:0;
            }
            printf("\n\n");
            if(outDay==a[month])break ;
        }
    }
    /*����ָ���*/
    printSeparator();

    /*�����ǰѡ������ں�����*/
    printf("The day you choose is:\n\n");
    printWeek();
    gotoxy(1,22);
    textcolor(10);
    cprintf("--------------------\n");
    textcolor(7);

    /*���ϵͳ���ں�����*/
    printf("\nToday is: %d-%d-%d",sysTime.da_year,sysTime.da_mon,sysTime.da_day);
    printWeek2(getWeek(sysTime.da_year,sysTime.da_mon,sysTime.da_day));
    printf("\n\n");
    /*��ʾ��������*/
    printUsage();
    gotoxy(1,25);
}

/*ͨ�����̵������ں���*/
void getKeyValue()
{
    int key ;
    char ch;
    /*Ĭ����ʾ��ǰϵͳ���ں�����*/
    currentYear=sysTime.da_year;
    currentMonth=sysTime.da_mon;
    currentDay=sysTime.da_day ;
    showCalendar(currentYear,currentMonth,currentDay);

    while(1)
    {
        /*��ȡ��ֵ,���ݼ�ֵ�����������*/
        key=bioskey(0);
        /*���Ƽ�,�����·�*/
        if(key==RIGHT)
        {
            /*�·�ֵ��1��12֮�䣬��ֱ�Ӽ�1*/
            if(currentMonth<12 && currentMonth>=1)
            {
                currentMonth++;
            }
            /*����·�Ϊ12�����1���λ������ݼ�1���·ݱ�Ϊ1*/
            else
            {
                currentYear++;
                currentMonth=1 ;
            }
        }
        /*���Ƽ�,�����·�*/
        if(key==LEFT)
        {
            /*�·�ֵ��1��12֮�䣬��ֱ�Ӽ�1*/
            if(currentMonth<=12 && currentMonth>1)
            {
                currentMonth--;
            }
            /*����·�Ϊ1�����1�󣬵���һ�꣬�·ݱ�Ϊ12*/
            else
            {
                currentYear--;
                currentMonth=12 ;
            }
        }
        /*���Ƽ�,�������*/
        if(key==UP)
        {
            currentYear++;
        }
        /*���Ƽ�,�������*/
        if(key==DOWN)
        {
            currentYear--;
        }
        /*���Ƽ�,��������*/
        if(key==PAGEUP)
        {
            /*��ǰ�ղ��Ǹ��µĵ�һ�죬������ֱ�Ӽ�1*/
            if(currentDay!=1)
            {
                currentDay--;
            }
            /*��ǰ���Ǹ��µĵ�һ�죬�����Ǹ���ĵ�һ���£���1��1�գ���
            ��������1�󣬱�Ϊ��һ������һ���µ����һ�죨��12��31�գ�*/
            else if(currentDay==1 && currentMonth==1)
            {
                currentYear--;
                currentMonth=12 ;
                currentDay=31 ;
            }
            /*��ǰ���Ǹ�����ĳһ���µ����һ�죬��������1��
            ��Ϊ�ϸ��µ����һ��*/
            else
            {
                currentMonth--;
                currentDay=n_lastMon ;
            }
        }
        /*���Ƽ�,��������*/
        if(key==PAGEDOWN)
        {
            /*��ǰ�ղ��Ǹ��µ����һ�죬������ֱ�Ӽ�1*/
            if(n_currentMon!=currentDay)
            {
                currentDay++;
            }
            /*��ǰ���Ǹ�������һ�죨��12��31�գ�����������1��
            ��Ϊ��һ��ĵ�һ���µĵ�һ�죨��1��1�գ�*/
            else if(n_currentMon==currentDay && currentMonth==12)
            {
                currentYear++;
                currentMonth=1 ;
                currentDay=1 ;
            }
            /*��ǰ���Ǹ�����ĳһ���µ����һ�죬��������1��
            ��Ϊ�¸��µĵ�һ��*/
            else
            {
                currentMonth++;
                currentDay=1 ;
            }
        }
        /*Q����q������ʾ��ѯָ�����ڵ�����*/
        if(key==QLOWER||key==QUPPER)
        {

            {
                printf("Input date(eg,%d-%d-%d):",sysTime.da_year,sysTime.da_mon,sysTime.da_day);
                scanf("%d-%d-%d",&currentYear,&currentMonth,&currentDay);
                checkDate();
            }
        }
        /*�ո�������õ�ϵͳ����*/
        if(key==SPACE)
        {
            currentYear=sysTime.da_year;
            currentMonth=sysTime.da_mon;
            currentDay=sysTime.da_day ;
        }
        /*Escpe���˳�ϵͳ*/
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

/*������*/
void main()
{
    /*����ı�ģʽ����*/
    clrscr();
    /*������Ļ��ʾ��ʽ*/
    _AL=03;
    _AH=0;
    geninterrupt(0x10);
    getdate(&sysTime);
    getKeyValue();
}
