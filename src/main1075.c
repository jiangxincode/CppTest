#include<stdio.h>
#include<math.h>

int ye(int y)
{
    if((y%4==0 && y%100!=0) || (y%400==0))
        return 1;
    else
        return 0;
}
int mo(int m, int y)
{
    switch(m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    case 2:
    {
        if(ye(y)==1)
            return 29;
        else
            return 28;
    }
    }

    return 0;
}
int main1075()
{
    int i,j,y,m,d,s=0,week;
    printf("year=");
    scanf("%11d",&y);
    printf("month=");
    scanf("%11d",&m);
    printf("day=");
    scanf("%11d",&d);

    for(i=1990; i<y; i++)
    {
        int t=ye(i);

        if(t==1)
            s=s+366;
        else
            s=s+365;
    }

    for(j=1; j<m; j++)
    {
        s=s+mo(j,y);
    }

    s=s+d;
    week=s%7;
    printf("days=%d ",s);
    printf("week=%d ",week);

    switch(week)
    {
    case 1:
        printf("Mon");
        break;

    case 2:
        printf("Tue");
        break;

    case 3:
        printf("Wed");
        break;

    case 4:
        printf("Thu");
        break;

    case 5:
        printf("Fri");
        break;

    case 6:
        printf("Sat");
        break;

    case 0:
        printf("Sun");
        break;
    }

    printf("\n");
    return 0;
}
