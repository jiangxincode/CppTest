#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
struct date
{
    int day,month,year;
} s1;
int main1154()
{
    int x;
    printf("Please input a date like \"2011-12-24\"\n");
    scanf("%11d-%11d-%11d",&s1.year,&s1.month,&s1.day);

    if(s1.year<0)
        printf("An error");

    switch(s1.month)
    {
    case 1:
        x=s1.day;
        break;

    case 2:
        x=31+s1.day;
        break;

    case 3:
        x=31+28+s1.day;
        break;

    case 4:
        x=31*2+28+s1.day;
        break;

    case 5:
        x=31*2+30+28+s1.day;
        break;

    case 6:
        x=31*3+30+28+s1.day;
        break;

    case 7:
        x=31*3+30*2+28+s1.day;
        break;

    case 8:
        x=31*4+30*2+28+s1.day;
        break;

    case 9:
        x=31*5+30*2+28+s1.day;
        break;

    case 10:
        x=31*5+30*3+28+s1.day;
        break;

    case 11:
        x=31*6+30*3+28+s1.day;
        break;

    case 12:
        x=31*6+30*4+28+s1.day;
        break;

    default:
        printf("An error");
    }

    if(x>2&&((x%4==0&&x%100!=0)||(x%400==0)))
        x++;

    printf("%d",x);
    return 0;
}

