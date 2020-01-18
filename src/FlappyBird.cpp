#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>


#define PR_Box printf("■")
#define PR_Gold printf("★")
#define PR_Ag printf("☆")
#define PR_FBird printf("Ю")
#define PR_DBird printf("Ф")
#define PR_Land printf("┳┳┯")
#define PR_Bg_TL printf("╔")
#define PR_Bg_TR printf("╗")
#define PR_Bg_DL printf("╚")
#define PR_Bg_DR printf("╝")
#define PR_Bg_X printf("═")
#define PR_Bg_Y printf("║")
#define PR_Blank printf(" ");


int Grade = 1, C_Gold = 0, C_Ag = 0, Score = 0, Delay_time = 1000, Max_blank = 9, Distance = 18; //init the environment

struct Birds
{
    int x, y;
    int condition;
};
Birds *Bird = (Birds *)malloc(sizeof(Birds));
struct Bg
{
    int x, y;
    int l_blank;
    int reward[9];
    Bg *pri;
    Bg *next;
};
Bg *Bg1 = new Bg[sizeof(Bg)];
void Position(int x, int y)
{
    COORD pos = { x - 1, y - 1 };
    HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}
void CreatBird()
{
    Bird->x = 41;
    Bird->y = 10;
    Bird->condition = 0;
}
void CreatBg()
{
    Bg *Bg2 = (Bg *)malloc(sizeof(Bg));


    Bg1->x = 90;
    Bg1->y = 8;
    Bg2->x = Bg1->x + Distance;
    Bg2->y = 9;


    Bg1->l_blank = Max_blank - Grade;
    Bg2->l_blank = Max_blank - Grade;


    Bg1->next = Bg2;
    Bg1->pri = Bg2;
    Bg2->next = Bg1;
    Bg2->pri = Bg1;
}
void InsertBg(Bg *p)
{
    int temp;
    Bg *Bgs = (Bg *)malloc(sizeof(Bg));
    Bgs->x = p->pri->x + Distance;
    Bgs->l_blank = Max_blank - Grade;
    srand((int)time(0));
    temp = rand();
    if(temp % 2 == 0) //++
    {
        if((temp % 4 + p->pri->y + Max_blank - Grade) < 21)
            Bgs->y = p->pri->y + temp % 4;
        else
            Bgs->y = p->pri->y;
    }
    else
    {
        if((p->pri->y - temp % 4) > 2)
            Bgs->y = p->pri->y - temp % 4;
        else
            Bgs->y = p->pri->y;
    }


    Bgs->pri = p->pri;
    Bgs->next = p;
    p->pri->next = Bgs;
    p->pri = Bgs;
}
void Check_Bg(Bg *q)
{
    Bg *p = q;
    int i = 0, temp;
    while(++i <= 5)
    {
        if(p->x > -4)
            p = p->next;
        else
        {
            srand((int)time(0));
            temp = rand();
            if(temp % 2 == 0) //++
            {
                if((temp % 4 + p->y + Max_blank - Grade) < 21)
                    p->y = p->y + temp % 4;
                else
                    p->y = p->y;
                p->x = p->pri->x + Distance;
                p->l_blank = Max_blank - Grade;
            }
            else
            {
                if((p->y - temp % 4) > 2)
                    p->y = p->y - temp % 4;
                else
                    p->y = p->y;
                p->x = p->pri->x + Distance;
                p->l_blank = Max_blank - Grade;
            }
        }

    }

}
void Loop_Bg(Bg *q)
{
    Bg *p = q;
    int i = 0;
    while(++i <= 5)
    {
        p->x = p->x - 1;
        p = p->next ;
        if(Bird->x == p->x)
        {
            Score += 1;
            if(Score % 4 == 0 && Grade < 4)
                Grade++;
        }
    }
}
void Prt_Bg(Bg *q)
{
    Bg *p = q;
    int i = 0, k, j;
    while(++i <= 5)
    {
        if(p->x > 0 && p->x <= 78)
        {
            for(k = 2; k < p->y; k++)
            {
                Position(p->x + 1, k);
                PR_Box;
                PR_Box;
                PR_Blank
            }
            Position(p->x, p->y);
            PR_Box;
            PR_Box;
            PR_Box;
            PR_Blank;
            Position(p->x, p->y + p->l_blank);
            PR_Box;
            PR_Box;
            PR_Box;
            PR_Blank;
            k = k + p->l_blank + 1;
            for(k; k <= 22; k++)
            {
                Position(p->x + 1, k);
                PR_Box;
                PR_Box;
                PR_Blank;
            }
            Position(p->x, 23);
            for(k = 1; k < Distance / 3 - 2; k++)
                PR_Land;
        }
        p = p->next;
        if(p->x == 0)
        {
            for(j = 2; j < p->y; j++)
            {
                Position(p->x + 1, j);
                PR_Blank;
                PR_Blank;
            }
            Position(p->x + 1, p->y);
            PR_Blank;
            PR_Blank;
            PR_Blank;
            Position(p->x + 1, p->y + Max_blank - Grade);
            PR_Blank;
            PR_Blank;
            PR_Blank;
            j = j + Max_blank - Grade + 1;
            for(j; j <= 22; j++)
            {
                Position(p->x + 1, j);
                PR_Blank;
                PR_Blank;
            }
        }
    }
}
void PrtBg()
{
    int i;
    Position(1, 1);
    PR_Bg_TL;
    Position(79, 1);
    PR_Bg_TR;
    Position(1, 24);
    PR_Bg_DL;
    Position(79, 24);
    PR_Bg_DR;
    for(i = 3; i <= 78; i += 2)
    {
        Position(i, 1);
        PR_Bg_X;
        Position(i, 24);
        PR_Bg_X;
    }
    /*for(i=2;i<=23;i++)
    { Position(1,i);PR_Bg_Y;printf("%d",i-1);
    Position(79,i);PR_Bg_Y;
    }*/
}
void PrtBird()
{
    Position(Bird->x, Bird->y - 1);
    PR_Blank;
    Position(Bird->x, Bird->y);
    PR_FBird;
    Position(38, 2);
    printf("Score:%d", Score);
}
int CheckYN(Bg *q)
{
    Bg *p = q;
    int i = 0;
    while(++i <= 5)
    {
        if(Bird->y > 23)
            return 0;
        if(Bird->x == p->x && Bird->y <= p->y)
            return 0;
        if((Bird->x == p->x || Bird->x == p->x + 1 || Bird->x == p->x + 2) && Bird->y == p->y)
            return 0;
        if(Bird->x == p->x && Bird->y > p->y + p->l_blank)
            return 0;
        if((Bird->x == p->x || Bird->x == p->x + 1 || Bird->x == p->x + 2) && Bird->y == p->y + p->l_blank)
            return 0;
        p = p->next;
    }
    return 1;
}
void Prtfirst()
{
    printf("══════════════════════════════════════\n");
    printf(" ■■ ■■\n");
    printf(" ■■ ■■\n");
    printf(" ■■ ■■\n");
    printf(" ■■ ■■\n");
    printf(" ■■■ ■■ 游戏说明：\n");
    printf(" ■■ 1-按上箭头使鸟起飞\n");
    printf(" ■■ 2-等级越高，难度越大！\n");
    printf(" Ю ■■■\n");
    printf("\n");
    printf(" \n\n\n\n\n\n\n\n");
    printf(" ┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳┳┯┳\n");
    system("pause");
    Position(1, 1);
    int i = 0;
    while(i++ < 40 * 25)
        PR_Blank;
}
int main()
{
    int i = 0;
    char ch;
    Prtfirst();

    PrtBg();
    CreatBg();
    InsertBg(Bg1);
    InsertBg(Bg1);
    InsertBg(Bg1);
    CreatBird();
    while(1)
    {
        if(!CheckYN(Bg1))
            break;
        Check_Bg(Bg1);
        Prt_Bg(Bg1);
        PrtBird();
        Loop_Bg(Bg1);
        Bird->y = Bird->y + 1;
        if(GetAsyncKeyState(VK_UP))
        {
            Position(Bird->x, Bird->y - 1);
            PR_Blank;
            Bird->y = Bird->y - 4;
        }
        while(i++ < 500);
        {
            Sleep(100);
        }
        i = 0;
    }
    Position(38, 10);
    printf("You Lost!");
    Position(1, 25);
    system("pause");

}


