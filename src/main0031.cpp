//calender
#include <stdio.h>
int main0031()
{
    void print_head(int x,int y);       /*打印头文件*/
    void print_month(int x,int y);      /*打印月历*/
    int days_of_month(int x,int y);     /*计算指定年月的天数*/
    int leap(int x,int y);              /*计算指定年月1号是星期几*/
    int days,year,month,firstday;
    char choose;

    do
    {
        printf("\n\nplease input the year(0000~9999):\n\n");
        scanf("%d",&year);

        if(year<0||year>9999)
        {
            printf("WANNING:ERROR,please input again!");
        }
    }
    while(year<0||year>9999);

    printf("\n\n");

    do
    {
        printf("please input the month(0~12)\n\n\n");
        scanf("%d",&month);

        if(month<=0||month>12)
        {
            printf("WANNING:ERROR,please input again!");
        }
    }
    while(month<=0||month>12);

    printf("\n\n");
    days=days_of_month(year,month);       /*调用函数*/
    firstday=leap(year,month);
    print_head(year,month);
    print_month(firstday,days);
    choose=getchar();/*为什么这里会有一个getch函数，后面不是已经有了scanf函数了么？*/
    printf("\n\n\n");
    printf("would you like to continue(y/n):\n\n");
    scanf("%c",&choose);

    if(choose=='y'||choose=='Y')
    {
        main0031();
    }

    return 0;
}

int days_of_month(int x,int y)
{
    int z;

    switch(y)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        z=31;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        z=30;
        break;

    case 2:
    {
        if((x%4==0&&x%100!=0)||(x%400==0))
        {
            z=29;
        }
        else
        {
            z=28;
        }

        break;
    }
    }

    return z;
}

int leap(int x,int y)
{
    int z,i,moday;
    z=(x+(x-1)/4-(x-1)/100+(x-1)/400)%7;

    for(i=1; i<y; i++)
    {
        moday=days_of_month(x,i);       /*钳套调用函数*/
        z=(z+moday)%7;
    }

    return z;
}

void print_head(int x,int y)
{
    printf("\n\n********************************************************************************\n\n");
    printf("\t\t\t\t%d       %d\n\n",x,y);
    printf("\t\t\t SUN MON TUE WED THU FRI SAT\n");
    printf("\t\t\t");
}

void print_month(int x,int y)
{
    int i;
    char space[7]= {' '};

    for(i=1; i<=x; i++)
    {
        printf("%4c",space[i]);
    }

    for(i=1; i<=y; i++)
    {
        if((i+x)%7==1)
        {
            printf("\n\t\t\t%4d",i);
        }
        else
        {
            printf("%4d",i);
        }
    }

    printf("\n\n********************************************************************************\n\n");
}
