#include<stdio.h>
#include<math.h>
int main1074()
{
    int y,m,d;
    printf("year=");
    scanf("%11d",&y);
    printf("month=");
    scanf("%11d",&m);
    printf("day=");
    scanf("%11d",&d);

    switch(m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
    {
        if(d>31)
            printf("wrong date");
        else
            printf("right date");
    }

    case 4:
    case 6:
    case 9:
    case 11:
    {
        if(d>30)
            printf("wrong date");
        else
            printf("right date");
    }

    case 2:
    {
        if((y%4==0 && y%100!=0) || (y%400==0))
        {
            if(d>29)
                printf("wrong date");
            else
                printf("right date");
        }
        else
        {
            if(d>28)
                printf("wrong date");
            else
                printf("right date");
        }
    }
    }

    return 0;
}
