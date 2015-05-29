/*加载头文件*/
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<bios.h>
#include<conio.h>

/*编译预处理，定义按键码*/
#define LEFT 0x4b00 
#define RIGHT 0x4d00 
#define DOWN 0x5000 
#define UP 0x4800 
/*若想在游戏中途退出, 可按 Esc 键*/
#define ESC 0x011b 
/*SPACE键表示落子*/
#define SPACE 0x3920

/*设置偏移量*/
#define OFFSET 20
#define OFFSET_x 4
#define OFFSET_y 3
/*定义数组大小*/
#define N 19 

/*定义全局变量*/
int status[N][N]; /*定义的数组，保存状态*/
int step_x,step_y;/*行走的坐标*/
int key ;         /*获取按下的键盘的键*/
int flag;         /*玩家标志*/

/*自定义函数原型*/
void DrawBoard();
void DrawCircle(int x,int y,int color);
void Alternation();
void JudgePlayer(int x,int y);
void Done();
int ResultCheck(int x,int y);
void WelcomeInfo();
void ShowMessage();

/*定义函数*/
/*显示欢迎信息函数*/
void WelcomeInfo()
{
    char ch ;
    /*移动光标到指定位置*/
    gotoxy(12,4);
    /*显示欢迎信息*/
    printf("Welcome you to gobang word!");
    gotoxy(12,6);
    printf("1.You can use the up,down,left and right key to move the chessman,");
    gotoxy(12,8);
    printf("  and you can press Space key to enter after you move it !");
    gotoxy(12,10);
    printf("2.You can use Esc key to exit the game too !");
    gotoxy(12,12);
    printf("3.Don not move the pieces out of the chessboard !");
    gotoxy(12,14);
    printf("DO you want to continue ?(Y/N)");
    ch=getchar();
    /*判断程序是否要继续进行*/
    if(ch=='n'||ch=='N')
    /*如果不继续进行，则推出程序*/
    exit(0);
}

/*画棋盘函数*/
void DrawBoard()
{
    int x1,x2;
    int y1,y2;
    /*设置背景色*/
    setbkcolor(2);
    /*设置线条颜色*/
    setcolor(1);
    /*设置线条风格、宽度*/
    setlinestyle(DOTTED_LINE,1,1);

    /*按照预设的偏移量开始画棋盘*/
    for(x1=1,y1=1,y2=18;x1<=18;x1++)
        line((x1+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET,(x1+OFFSET_x)*OFFSET,(y2+OFFSET_y)*OFFSET);
    for(x1=1,y1=1,x2=18;y1<=18;y1++)
        line((x1+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET,(x2+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET);
    /*将各个点的状态设置为0*/
    for(x1=1;x1<=18;x1++)
        for(y1=1;y1<=18;y1++)
            status[x1][y1]=0;

    /*显示帮助信息*/
    setcolor(14);
    /*设置字体、大小*/
    settextstyle(1,0,1);
    outtextxy((19+OFFSET_x)*OFFSET,(2+OFFSET_y)*OFFSET,"Player key:");
    setcolor(9);
    settextstyle(3,0,1);
    outtextxy((19+OFFSET_x)*OFFSET,(4+OFFSET_y)*OFFSET,"UP--up ");
    outtextxy((19+OFFSET_x)*OFFSET,(6+OFFSET_y)*OFFSET,"DOWN--down ");
    outtextxy((19+OFFSET_x)*OFFSET,(8+OFFSET_y)*OFFSET,"LEFT--left");
    outtextxy((19+OFFSET_x)*OFFSET,(10+OFFSET_y)*OFFSET,"RIGHT--right");
    outtextxy((19+OFFSET_x)*OFFSET,(12+OFFSET_y)*OFFSET,"ENTER--space");
    setcolor(14);
    settextstyle(1,0,1);
    outtextxy((19+OFFSET_x)*OFFSET,(14+OFFSET_y)*OFFSET,"Exit:");
    setcolor(9);
    settextstyle(3,0,1);
    outtextxy((19+OFFSET_x)*OFFSET,(16+OFFSET_y)*OFFSET,"ESC");
}

/*画圆函数*/
void DrawCircle(int x,int y,int color)
{
    setcolor(color);
    /*设置画圆线条的风格，宽度，这里设置为虚线*/
    setlinestyle(SOLID_LINE,0,1);
    x=(x+OFFSET_x)*OFFSET;
    y=(y+OFFSET_y)*OFFSET;
    /*以(x,y)为圆心，8为半径画圆*/
    circle(x,y,8);
}



/*交换行棋方函数*/
void Alternation()
{
    if(flag==1)
        flag=2 ;
    else 
        flag=1 ;
}   

/*对不同的行棋方画不同颜色的圆函数*/
void JudgePlayer(int x,int y)
{
    if(flag==1)
        DrawCircle(x,y,15);
    if(flag==2)
        DrawCircle(x,y,4);
}

/*判断当前行棋方是否获胜函数*/
int ResultCheck(int x,int y)
{
    int j,k;
    int n1,n2 ;
    while(1)
    {

        /*对水平方向进行判断是否有5个同色的圆*/
        n1=0;
        n2=0;
        /*水平向左数*/
        for(j=x,k=y;j>=1;j--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*水平向右数*/
        for(j=x,k=y;j<=18;j++)
        {
            if(status[j][k]==flag)
            n2++;
            else
                break;
        }
        if(n1+n2-1>=5)
        {
            return(1);
        }

        /*对垂直方向进行判断是否有5个同色的圆*/
        n1=0;
        n2=0;
        /*垂直向上数*/
        for(j=x,k=y;k>=1;k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break ;
        }
        /*垂直向下数*/
        for(j=x,k=y;k<=18;k++)
        {
            if(status[j][k]==flag)
                n2++;
            else
                break ;
        }
        if(n1+n2-1>=5)
        {
            return(1);
        }

        /*从左上方到右下方进行判断是否有5个同色的圆*/
        n1=0;
        n2=0;
        /*向左上方数*/
        for(j=x,k=y;(j>=1)&&(k>=1);j--,k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*向右下方数*/
       for(j=x,k=y;(j<=18)&&(k<=18);j++,k++)
        {
            if(status[j][k]==flag)
                n2++;
            else
                break;
        }
        if(n1+n2-1>=5)
        {
            return(1);
        }

        /*从右上方到左下方进行判断是否有5个同色的圆*/
        n1=0;
        n2=0;
        /*向右上方数*/
        for(j=x,k=y;(j<=18)&&(k>=1);j++,k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*向左下方数*/
        for(j=x,k=y;(j>=1)&&(k<=18);j--,k++)
        {
            if(status[j][k]==flag)
                n2++;
            else
                break;
        }
        if(n1+n2-1>=5)
        {
            return(1);
        }
        return(0);
    }
}

/*执行下棋函数*/
void Done()
{
    int i ;
    int j ;
    /*根据不同的key值进行不同的操作*/
    switch(key)
    {
    /*如果是向左移动的*/
    case LEFT:
        /*如果下一步超出棋盘左边界则什么也不作*/
        if(step_x-1<0)
            break ;
        else 
        {
            for(i=step_x-1,j=step_y;i>=1;i--)
                if(status[i][j]==0)
                {
                    DrawCircle(step_x,step_y,2);
                    break ;
                }
            if(i<1)
                break ;
            step_x=i ;
            JudgePlayer(step_x,step_y);
            break ;
        }
    /*如果是向右移动的*/
    case RIGHT :
        /*如果下一步超出棋盘右边界则什么也不作*/
        if(step_x+1>18)
            break ;
        else
        {
            for(i=step_x+1,j=step_y;i<=18;i++)
                if(status[i][j]==0)
                {
                    /*每移动一步画一个圆，显示移动的过程*/
                    DrawCircle(step_x,step_y,2);
                    break ;
                }
            if(i>18)break ;
                step_x=i ;
            /*根据不同的行棋者画不同颜色的圆*/
            JudgePlayer(step_x,step_y);
            /*显示行棋一方是谁*/
            break ;
        }
    /*如果是向下移动的*/
    case DOWN :
        /*如果下一步超出棋盘下边界则什么也不作*/
        if((step_y+1)>18)
            break ;
        else 
        {
            for(i=step_x,j=step_y+1;j<=18;j++)
            if(status[i][j]==0)
            {
                DrawCircle(step_x,step_y,2);
                break ;
            }
            if(j>18)break ;
                step_y=j ;
            JudgePlayer(step_x,step_y);
            break ;
        }
    /*如果是向上移动的*/
    case UP :
        /*如果下一步超出棋盘上边界则什么也不作*/
        if((step_y-1)<0)
            break ;
        else 
        {
            for(i=step_x,j=step_y-1;j>=1;j--)
                if(status[i][j]==0)
                {
                    DrawCircle(step_x,step_y,2);
                    break ;
                }
            if(j<1)break ;
                step_y=j ;
            JudgePlayer(step_x,step_y);
            break ;
        }
    /*如果是退出键*/
    case ESC :
        break ;
    /*如果是确定键*/
    case SPACE:
        /*如果操作是在棋盘之内*/
        if(step_x>=1&&step_x<=18&&step_y>=1&&step_y<=18)
        {
            /*按下确定键后，如果棋子当前位置的状态为0*/
            if(status[step_x][step_y]==0)
            {
                /*则更改棋子当前位置的状态在flag，表示是哪个行棋者行的棋*/
                status[step_x][step_y]=flag ;
                /*如果判断当前行棋者获胜*/
                if(ResultCheck(step_x,step_y)==1)
                {
                    /*以指定频率打开PC扬声器*/
                    sound(1000);
                    /*扬声器的发生时间，为1秒钟*/
                    delay(1000);
                    nosound();
                    gotoxy(30,4);
                    setbkcolor(BLUE);
                    /*清除图形屏幕*/
                    cleardevice();
                    /*为图形输出设置当前视口*/
                    setviewport(100,100,540,380,1);
                    /*绿色实填充*/
                    setfillstyle(1,2);
                    setcolor(YELLOW);
                    rectangle(0,0,439,279);
                    floodfill(50,50,14);
                    setcolor(12);
                    settextstyle(1,0,5);
                    /*三重笔划字体, 水平放大5倍*/
                    outtextxy(20,20,"Congratulation !");
                    setcolor(15);
                    settextstyle(3,0,4);
                    /*如果是Player1获胜，显示获胜信息*/
                    if(flag==1)
                    {
                        /*无衬笔划字体, 水平放大5倍*/
                        outtextxy(20,120,"Player1 win the game !");
                    }
                    /*如果是Player1获胜，显示获胜信息*/
                    if(flag==2)
                    {
                        /*无衬笔划字体, 水平放大5倍*/
                        outtextxy(20,120,"Player2 win the game !");
                    }
            
                    setcolor(14);
                    settextstyle(2,0,8);
                    getch();
                    exit(0);
                }
                /*如果当前行棋者没有获胜，则交换行棋方*/
                Alternation();
                /*提示行棋方是谁*/
                ShowMessage();
                break;
            }
       }
       else
          break ;
   }
}

/*显示行棋方函数*/
void ShowMessage()
{
    /*轮到Player1行棋*/
    if(flag==1)
    {
        setcolor(2);
        settextstyle(1,0,1);
        gotoxy(100,30);
        /*覆盖原有的字迹*/
        outtextxy(100,30,"It's turn to Player2 !");
        setcolor(12);
        settextstyle(1,0,1);
        outtextxy(100,30,"It's turn to Player1 !");
    }
    /*轮到Player2行棋*/
    if(flag==2)
    {
        setcolor(2);
        settextstyle(1,0,1);
        /*覆盖原有的字迹*/
        outtextxy(100,30,"It's turn to Player1 !");
        setcolor(12);
        settextstyle(1,0,1);
        gotoxy(100,20);
        outtextxy(100,30,"It's turn to Player2 !");

    }
}

/*主函数*/
int main()
{
    int gdriver;
    int gmode;
    int errorcode;
    /*清空文本模式窗口*/
    clrscr();
    /*显示欢迎信息*/
    WelcomeInfo();
    gdriver=DETECT;
    gmode=0;
    /*初始化图形系统*/
    initgraph(&gdriver,&gmode,"");
    /*返回最后一次不成功的图形操作的错误代码*/
    errorcode=graphresult();
    if (errorcode!= grOk)  
    {
        /*根据错误代码输出错误信息串*/
        printf("\nNotice:Error occured when grphics initialization: %s\n",grapherrormsg(errorcode));
        printf("Press any key to quit!");
        getch(); 
        exit(1);            
    }

    /*设置flag初始值，默认是Player1先行*/
    flag=1;
    /*画棋盘*/
    DrawBoard();
    ShowMessage();
    do 
    {
        step_x=0 ;
        step_y=0 ;
        JudgePlayer(step_x-1,step_y-1);
        do 
        {
            /*如果没有键按下，则bioskey(1)函数将返回0*/
            while(bioskey(1)==0);
            /*获取从键盘按下的键值*/
            key=bioskey(0);
            /*根据获得的键值进行下棋操作*/
            Done();
        }while(key!=SPACE&&key!=ESC);
    }while(key!=ESC);
    /*关闭图形系统*/
    closegraph();
    return 0;
}



