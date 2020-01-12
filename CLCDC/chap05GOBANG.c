/*����ͷ�ļ�*/
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<bios.h>
#include<conio.h>

/*����Ԥ�������尴����*/
#define LEFT 0x4b00 
#define RIGHT 0x4d00 
#define DOWN 0x5000 
#define UP 0x4800 
/*��������Ϸ��;�˳�, �ɰ� Esc ��*/
#define ESC 0x011b 
/*SPACE����ʾ����*/
#define SPACE 0x3920

/*����ƫ����*/
#define OFFSET 20
#define OFFSET_x 4
#define OFFSET_y 3
/*���������С*/
#define N 19 

/*����ȫ�ֱ���*/
int status[N][N]; /*��������飬����״̬*/
int step_x,step_y;/*���ߵ�����*/
int key ;         /*��ȡ���µļ��̵ļ�*/
int flag;         /*��ұ�־*/

/*�Զ��庯��ԭ��*/
void DrawBoard();
void DrawCircle(int x,int y,int color);
void Alternation();
void JudgePlayer(int x,int y);
void Done();
int ResultCheck(int x,int y);
void WelcomeInfo();
void ShowMessage();

/*���庯��*/
/*��ʾ��ӭ��Ϣ����*/
void WelcomeInfo()
{
    char ch ;
    /*�ƶ���굽ָ��λ��*/
    gotoxy(12,4);
    /*��ʾ��ӭ��Ϣ*/
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
    /*�жϳ����Ƿ�Ҫ��������*/
    if(ch=='n'||ch=='N')
    /*������������У����Ƴ�����*/
    exit(0);
}

/*�����̺���*/
void DrawBoard()
{
    int x1,x2;
    int y1,y2;
    /*���ñ���ɫ*/
    setbkcolor(2);
    /*����������ɫ*/
    setcolor(1);
    /*����������񡢿��*/
    setlinestyle(DOTTED_LINE,1,1);

    /*����Ԥ���ƫ������ʼ������*/
    for(x1=1,y1=1,y2=18;x1<=18;x1++)
        line((x1+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET,(x1+OFFSET_x)*OFFSET,(y2+OFFSET_y)*OFFSET);
    for(x1=1,y1=1,x2=18;y1<=18;y1++)
        line((x1+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET,(x2+OFFSET_x)*OFFSET,(y1+OFFSET_y)*OFFSET);
    /*���������״̬����Ϊ0*/
    for(x1=1;x1<=18;x1++)
        for(y1=1;y1<=18;y1++)
            status[x1][y1]=0;

    /*��ʾ������Ϣ*/
    setcolor(14);
    /*�������塢��С*/
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

/*��Բ����*/
void DrawCircle(int x,int y,int color)
{
    setcolor(color);
    /*���û�Բ�����ķ�񣬿�ȣ���������Ϊ����*/
    setlinestyle(SOLID_LINE,0,1);
    x=(x+OFFSET_x)*OFFSET;
    y=(y+OFFSET_y)*OFFSET;
    /*��(x,y)ΪԲ�ģ�8Ϊ�뾶��Բ*/
    circle(x,y,8);
}



/*�������巽����*/
void Alternation()
{
    if(flag==1)
        flag=2 ;
    else 
        flag=1 ;
}   

/*�Բ�ͬ�����巽����ͬ��ɫ��Բ����*/
void JudgePlayer(int x,int y)
{
    if(flag==1)
        DrawCircle(x,y,15);
    if(flag==2)
        DrawCircle(x,y,4);
}

/*�жϵ�ǰ���巽�Ƿ��ʤ����*/
int ResultCheck(int x,int y)
{
    int j,k;
    int n1,n2 ;
    while(1)
    {

        /*��ˮƽ��������ж��Ƿ���5��ͬɫ��Բ*/
        n1=0;
        n2=0;
        /*ˮƽ������*/
        for(j=x,k=y;j>=1;j--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*ˮƽ������*/
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

        /*�Դ�ֱ��������ж��Ƿ���5��ͬɫ��Բ*/
        n1=0;
        n2=0;
        /*��ֱ������*/
        for(j=x,k=y;k>=1;k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break ;
        }
        /*��ֱ������*/
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

        /*�����Ϸ������·������ж��Ƿ���5��ͬɫ��Բ*/
        n1=0;
        n2=0;
        /*�����Ϸ���*/
        for(j=x,k=y;(j>=1)&&(k>=1);j--,k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*�����·���*/
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

        /*�����Ϸ������·������ж��Ƿ���5��ͬɫ��Բ*/
        n1=0;
        n2=0;
        /*�����Ϸ���*/
        for(j=x,k=y;(j<=18)&&(k>=1);j++,k--)
        {
            if(status[j][k]==flag)
                n1++;
            else
                break;
        }
        /*�����·���*/
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

/*ִ�����庯��*/
void Done()
{
    int i ;
    int j ;
    /*���ݲ�ͬ��keyֵ���в�ͬ�Ĳ���*/
    switch(key)
    {
    /*����������ƶ���*/
    case LEFT:
        /*�����һ������������߽���ʲôҲ����*/
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
    /*����������ƶ���*/
    case RIGHT :
        /*�����һ�����������ұ߽���ʲôҲ����*/
        if(step_x+1>18)
            break ;
        else
        {
            for(i=step_x+1,j=step_y;i<=18;i++)
                if(status[i][j]==0)
                {
                    /*ÿ�ƶ�һ����һ��Բ����ʾ�ƶ��Ĺ���*/
                    DrawCircle(step_x,step_y,2);
                    break ;
                }
            if(i>18)break ;
                step_x=i ;
            /*���ݲ�ͬ�������߻���ͬ��ɫ��Բ*/
            JudgePlayer(step_x,step_y);
            /*��ʾ����һ����˭*/
            break ;
        }
    /*����������ƶ���*/
    case DOWN :
        /*�����һ�����������±߽���ʲôҲ����*/
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
    /*����������ƶ���*/
    case UP :
        /*�����һ�����������ϱ߽���ʲôҲ����*/
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
    /*������˳���*/
    case ESC :
        break ;
    /*�����ȷ����*/
    case SPACE:
        /*���������������֮��*/
        if(step_x>=1&&step_x<=18&&step_y>=1&&step_y<=18)
        {
            /*����ȷ������������ӵ�ǰλ�õ�״̬Ϊ0*/
            if(status[step_x][step_y]==0)
            {
                /*��������ӵ�ǰλ�õ�״̬��flag����ʾ���ĸ��������е���*/
                status[step_x][step_y]=flag ;
                /*����жϵ�ǰ�����߻�ʤ*/
                if(ResultCheck(step_x,step_y)==1)
                {
                    /*��ָ��Ƶ�ʴ�PC������*/
                    sound(1000);
                    /*�������ķ���ʱ�䣬Ϊ1����*/
                    delay(1000);
                    nosound();
                    gotoxy(30,4);
                    setbkcolor(BLUE);
                    /*���ͼ����Ļ*/
                    cleardevice();
                    /*Ϊͼ��������õ�ǰ�ӿ�*/
                    setviewport(100,100,540,380,1);
                    /*��ɫʵ���*/
                    setfillstyle(1,2);
                    setcolor(YELLOW);
                    rectangle(0,0,439,279);
                    floodfill(50,50,14);
                    setcolor(12);
                    settextstyle(1,0,5);
                    /*���رʻ�����, ˮƽ�Ŵ�5��*/
                    outtextxy(20,20,"Congratulation !");
                    setcolor(15);
                    settextstyle(3,0,4);
                    /*�����Player1��ʤ����ʾ��ʤ��Ϣ*/
                    if(flag==1)
                    {
                        /*�޳ıʻ�����, ˮƽ�Ŵ�5��*/
                        outtextxy(20,120,"Player1 win the game !");
                    }
                    /*�����Player1��ʤ����ʾ��ʤ��Ϣ*/
                    if(flag==2)
                    {
                        /*�޳ıʻ�����, ˮƽ�Ŵ�5��*/
                        outtextxy(20,120,"Player2 win the game !");
                    }
            
                    setcolor(14);
                    settextstyle(2,0,8);
                    getch();
                    exit(0);
                }
                /*�����ǰ������û�л�ʤ���򽻻����巽*/
                Alternation();
                /*��ʾ���巽��˭*/
                ShowMessage();
                break;
            }
       }
       else
          break ;
   }
}

/*��ʾ���巽����*/
void ShowMessage()
{
    /*�ֵ�Player1����*/
    if(flag==1)
    {
        setcolor(2);
        settextstyle(1,0,1);
        gotoxy(100,30);
        /*����ԭ�е��ּ�*/
        outtextxy(100,30,"It's turn to Player2 !");
        setcolor(12);
        settextstyle(1,0,1);
        outtextxy(100,30,"It's turn to Player1 !");
    }
    /*�ֵ�Player2����*/
    if(flag==2)
    {
        setcolor(2);
        settextstyle(1,0,1);
        /*����ԭ�е��ּ�*/
        outtextxy(100,30,"It's turn to Player1 !");
        setcolor(12);
        settextstyle(1,0,1);
        gotoxy(100,20);
        outtextxy(100,30,"It's turn to Player2 !");

    }
}

/*������*/
int main()
{
    int gdriver;
    int gmode;
    int errorcode;
    /*����ı�ģʽ����*/
    clrscr();
    /*��ʾ��ӭ��Ϣ*/
    WelcomeInfo();
    gdriver=DETECT;
    gmode=0;
    /*��ʼ��ͼ��ϵͳ*/
    initgraph(&gdriver,&gmode,"");
    /*�������һ�β��ɹ���ͼ�β����Ĵ������*/
    errorcode=graphresult();
    if (errorcode!= grOk)  
    {
        /*���ݴ���������������Ϣ��*/
        printf("\nNotice:Error occured when grphics initialization: %s\n",grapherrormsg(errorcode));
        printf("Press any key to quit!");
        getch(); 
        exit(1);            
    }

    /*����flag��ʼֵ��Ĭ����Player1����*/
    flag=1;
    /*������*/
    DrawBoard();
    ShowMessage();
    do 
    {
        step_x=0 ;
        step_y=0 ;
        JudgePlayer(step_x-1,step_y-1);
        do 
        {
            /*���û�м����£���bioskey(1)����������0*/
            while(bioskey(1)==0);
            /*��ȡ�Ӽ��̰��µļ�ֵ*/
            key=bioskey(0);
            /*���ݻ�õļ�ֵ�����������*/
            Done();
        }while(key!=SPACE&&key!=ESC);
    }while(key!=ESC);
    /*�ر�ͼ��ϵͳ*/
    closegraph();
    return 0;
}



