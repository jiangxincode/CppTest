/*
 *����˹����Դ����
 */
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h>  /*ͼ�κ�����*/

/*���尴����*/
#define VK_LEFT  0x4b00
#define VK_RIGHT 0x4d00
#define VK_DOWN  0x5000
#define VK_UP    0x4800
#define VK_ESC   0x011b
#define TIMER 0x1c      /*�����жϺ�*/

/*���峣��*/
#define MAX_BOX 19          /*�ܹ���19�ָ���̬�ķ���*/
#define BSIZE 20            /*����ı߳���20������*/
#define Sys_x 160           /*��ʾ�����������Ͻ�x����*/
#define Sys_y 25            /*��ʾ�����������Ͻ�y����*/
#define Horizontal_boxs 10  /*ˮƽ�ķ����Է���Ϊ��λ�ĳ���*/
#define Vertical_boxs 15    /*��ֱ�ķ����Է���Ϊ��λ�ĳ���,Ҳ��˵����15������*/
#define Begin_boxs_x Horizontal_boxs/2  /*������һ������ʱ���ֵ���ʼλ��*/

#define FgColor 3       /*ǰ����ɫ,������.2-green*/
#define BgColor 0       /*������ɫ.0-blac*/

#define LeftWin_x Sys_x+Horizontal_boxs*BSIZE+46        /*�ұ�״̬����x����*/

#define false 0
#define true 1
/*�ƶ��ķ���*/
#define MoveLeft 1
#define MoveRight 2
#define MoveDown 3
#define MoveRoll 4
/*�Ժ������ÿ��������Կ��������ص���BSIZE*BSIZE��������*/
/*����ȫ�ֱ���*/
int current_box_numb;   /*���浱ǰ������*/
int Curbox_x=Sys_x+Begin_boxs_x*BSIZE,Curbox_y=Sys_y;/*x,y�Ǳ��淽��ĵ�ǰ�����*/
int flag_newbox=false;  /*�Ƿ�Ҫ�����·���ı��0*/
int speed=0;            /*�����ٶ�*/
int score=0;            /*�ܷ�*/
int speed_step=30;       /*ÿ�ȼ�����Ҫ����*/
void interrupt (*oldtimer)(void);/* ָ��ԭ��ʱ���жϴ��������ڵ��жϴ�����ָ�� */

struct BOARD            /*��Ϸ�װ�ṹ,��ʾÿ���������е�����*/
{
    int var;            /*��ǰ״̬ ֻ��0��1,1��ʾ�˵��ѱ�ռ��*/
    int color;          /*��ɫ,��Ϸ�װ��ÿ�������ӵ�в�ͬ����ɫ.��ǿ����*/
}Table_board[Vertical_boxs][Horizontal_boxs];

/*����ṹ*/
struct SHAPE
{
    char box[2];            /*һ���ֽڵ���8λ,ÿ4λ����ʾһ�������һ��
                              ��:box[0]="0x88",box[1]="0xc0"��ʾ����:
                              1000
                              1000
                              1100
                              0000*/
    int color;              /*ÿ���������ɫ*/
    int next;               /*�¸�����ı��*/
};


/*��ʼ����������.������MAX_BOX��SHAPE���͵Ľṹ���飬����ʼ��*/
struct SHAPE shapes[MAX_BOX]=
{
/*
 *   ��     �ڿڿ�   �ڿ�      ��
 *   ��     ��         ��  �ڿڿ�
 *   �ڿ�              ��        
 */

    {0x88,  0xc0,   CYAN,   1},
    {0xe8,  0x0,    CYAN,   2},
    {0xc4,  0x40,   CYAN,   3},
    {0x2e,  0x0,    CYAN,   0},
/*
 *   ��        �ڿ� �ڿڿ�
 *   �� ��     ��       ��
 * �ڿ� �ڿڿ� ��    
 */
    {0x44,  0xc0,   MAGENTA,  5},
    {0x8e,  0x0,    MAGENTA,  6},
    {0xc8,  0x80,   MAGENTA,  7},
    {0xe2,  0x0,    MAGENTA,  4},

/*
 *   ��
 *   �ڿ�         �ڿ�
 *     ��       �ڿ�
 */
    {0x8c,  0x40,   YELLOW, 9},
    {0x6c,  0x0,    YELLOW, 8},

/*
 *   ��        �ڿ�
 * �ڿ�          �ڿ�
 * ��
 */
    {0x4c,  0x80,   BROWN,  11},
    {0xc6,  0x0,    BROWN,  10},

/*
 *   ��       ��                ��
 * �ڿڿ�     �ڿ�   �ڿڿ�   �ڿ�
 *            ��       ��       ��
 */
    {0x4e,  0x0,    WHITE,  13},
    {0x8c,  0x80,   WHITE,  14},
    {0xe4,  0x0,    WHITE,  15},
    {0x4c,  0x40,   WHITE,  12},

/* ��
 * ��
 * ��       �ڿڿڿ�
 * ��
 */
    {0x88,  0x88,   RED,    17},
    {0xf0,  0x0,    RED,    16},

/*
 * �ڿ�
 * �ڿ�
 */

    {0xcc,  0x0,    BLUE,   18}

};


unsigned int TimerCounter=0;  /*��ʱ����������*/

/* �µ�ʱ���жϴ����� */
void interrupt newtimer(void)
{
    (*oldtimer)();   /* call the old routine */
    TimerCounter++;/* increase the global counter */
}

/* �����µ�ʱ���жϴ������ */
void SetTimer(void interrupt(*IntProc)(void))
{
    oldtimer=getvect(TIMER); /*��ȡ�жϺ�ΪTIMER���жϴ���������ڵ�ַ*/
    disable(); /* �����µ�ʱ���жϴ������ʱ����ֹ�����ж� */
    setvect(TIMER,IntProc);
    /*���жϺ�ΪTIMER���жϴ���������ڵ�ַ��ΪIntProc()��������ڵ�ַ
    ���жϷ���ʱ��������IntProc()������*/
    enable();  /* �����ж� */
}

/* �ָ�ԭ�е�ʱ���жϴ������ */
void KillTimer()
{
    disable();
    setvect(TIMER,oldtimer);
    enable();
}


void show_intro(int xs,int ys)
{
 char stemp[50];
 setcolor (15);
 rectangle(xs,ys,xs+239,ys+100);
 sprintf(stemp," -Roll  -Downwards");
 stemp[0]=24;
 stemp[8]=25;
 setcolor(14);
 outtextxy(xs+40,ys+30,stemp);

 sprintf(stemp," -Turn Left   -Turn Right");
 stemp[0]=27;
 stemp[13]=26;

 outtextxy(xs+40,ys+45,stemp);
 outtextxy(xs+40,ys+60,"Esc-Exit ");
 setcolor(FgColor);
}

/*��ʾ����*/
void ShowScore(int score)
{
    int x,y;
    char score_str[5];/*������Ϸ�÷�*/
    setfillstyle(SOLID_FILL,BgColor);
    x=LeftWin_x;
    y=100;
    bar(x-BSIZE,y,x+BSIZE*3,y+BSIZE*3);
    sprintf(score_str,"%3d",score);
    outtextxy(x,y,"SCORE");
    outtextxy(x,y+10,score_str);
}

/*��ʾ�ٶ�*/
void ShowSpeed(int speed)
{
    int x,y;
    char speed_str[5];/*�����ٶ�ֵ*/
    setfillstyle(SOLID_FILL,BgColor);
    x=LeftWin_x;
    y=150;
    bar(x-BSIZE,y,x+BSIZE*3,y+BSIZE*3);
    /*ȷ��һ����(x1,y1)Ϊ���Ͻ�,(x2,y2)Ϊ���½ǵľ��δ���, �ٰ��涨ͼģ����ɫ��䡣*/
    sprintf(speed_str,"%3d",speed+1);
    outtextxy(x,y,"Level");
    outtextxy(x,y+10,speed_str);
    /*����ַ���ָ��speed_str��ָ���ı��ڹ涨��(x, y)λ��*/
    outtextxy(x,y+50,"Nextbox");
}


/**********��ʼ������*******
 *����˵��:
 *      x,yΪ���Ͻ�����
 *      m,n��Ӧ��Vertical_boxs,Horizontal_boxs
 *      �ֱ��ʾ�ݺ᷽���Ϸ���ĸ���(�Է���Ϊ��λ)
 *      BSIZE Sys_x Sys_y
 **********************************/
void initialize(int x,int y,int m,int n)
{

    int i,j,oldx;
    oldx=x;
    for(j=0;j<n;j++)
    {
        for(i=0;i<m;i++)
        {

            Table_board[j][i].var=0;
            Table_board[j][i].color=BgColor;
            line(x,y,x+BSIZE,y);
            line(x,y,x,y+BSIZE);
            line(x,y+BSIZE,x+BSIZE,y+BSIZE);
            line(x+BSIZE,y,x+BSIZE,y+BSIZE);
            x+=BSIZE;
        }
        y+=BSIZE;
        x=oldx;
    }
    Curbox_x=x;
    Curbox_y=y;/*x,y�Ǳ��淽��ĵ�ǰ�����*/
    flag_newbox=false;  /*�Ƿ�Ҫ�����·���ı��0*/
    speed=0;            /*�����ٶ�*/
    score=0;            /*�ܷ�*/
    ShowScore(score);
    ShowSpeed(speed);

}


/*   ɾ��һ���������
 *   �����yΪ������һ��Ϊ��
 */
int DelFullRow(int y)
{
    /*������Ϸ��������һ��*/
    int n,top=0;                /*top������ǵ�ǰ��ߵ�,����һ��ȫ�վͱ�ʾΪ�����,�ƶ��ǵ���ߵ����*/
    register m,totoal;
    for(n=y;n>=0;n--)/*�ӵ�ǰ�����Ͽ�*/
    {
        totoal=0;
        for(m=0;m<Horizontal_boxs;m++)
        {
            if(!Table_board[n][m].var)totoal++;             /*ûռ�з���+1*/
            if(Table_board[n][m].var!=Table_board[n-1][m].var)  /*���в��������оͰ����д������� xor��ϵ*/
            {
                Table_board[n][m].var=Table_board[n-1][m].var;
                Table_board[n][m].color=Table_board[n-1][m].color;
            }
        }
        if(totoal==Horizontal_boxs)                     /*���������������Ŀ�����ǰ����*/
        {
            top=n;
            break;
        }
    }
    return(top);                /*������ߵ�*/
}


/*�ҵ�һ���������*/
void setFullRow(int t_boardy)
{
    int n,full_numb=0,top=0;            /*top������ǵ�ǰ�������ߵ�*/
    register m;
/*
t_boardy ��       5
         ��       6
   �ڿڿڿڿڿ�   7
n  �ڿڿڿڿڿ�   8
 */
    for(n=t_boardy+3;n>=t_boardy;n--)
    {
        if(n<0 || n>=Vertical_boxs ){continue;} /*����������*/
        for(m=0;m<Horizontal_boxs;m++)          /*ˮƽ�ķ���*/
        {
            if(!Table_board[n+full_numb][m].var)break;      /*������һ���ǿվ���������*/
        }
        if(m==Horizontal_boxs)                  /*�ҵ�������*/
        {
            if(n==t_boardy+3)                   /*��һ���׸���n,��ߵ�*/
                top=DelFullRow(n+full_numb);        /*�����Ϸ����ĸ���,����������*/
            else
                DelFullRow(n+full_numb);
            full_numb++;                        /*ͳ���ҵ�������*/

        }
    }
    if(full_numb)
    {
        int oldx,x=Sys_x,y=BSIZE*top+Sys_y;
        oldx=x;
        score=score+full_numb*10;              /*�ӷ���*/
        /*�����൱�����Ե�ɫ��*/
        for(n=top;n<t_boardy+4;n++)
        {
            if(n>=Vertical_boxs)continue;   /*����������*/
            for(m=0;m<Horizontal_boxs;m++)  /*ˮƽ�ķ���*/
            {
                if(Table_board[n][m].var)
                    setfillstyle(SOLID_FILL,Table_board[n][m].color);/*Table_board[n][m].color*/
                else
                    setfillstyle(SOLID_FILL,BgColor);

                bar(x,y,x+BSIZE,y+BSIZE);
                line(x,y,x+BSIZE,y);
                line(x,y,x,y+BSIZE);
                line(x,y+BSIZE,x+BSIZE,y+BSIZE);
                line(x+BSIZE,y,x+BSIZE,y+BSIZE);
                x+=BSIZE;
            }
            y+=BSIZE;
            x=oldx;
        }
        ShowScore(score);
        if(speed!=score/speed_step)
          {speed=score/speed_step; ShowSpeed(speed);}
        else
          {ShowSpeed(speed);}
    }
}


/*
 * ������״�ķ����������Ϸ���ϣ������ش˷����
 */
int MkNextBox(int box_numb)
{

    int mask=128,t_boardx,t_boardy,n,m;
    t_boardx=(Curbox_x-Sys_x)/BSIZE;
    t_boardy=(Curbox_y-Sys_y)/BSIZE;
    for(n=0;n<4;n++)
    {
        for(m=0;m<4;m++)
        {
            if( ((shapes[current_box_numb].box[n/2]) & mask) )
            {
                Table_board[t_boardy+n][t_boardx+m].var=1;/*����������Ϸ��*/
                Table_board[t_boardy+n][t_boardx+m].color=shapes[current_box_numb].color;/*����������Ϸ��*/
            }
            mask=mask/(2);
            if(mask==0)mask=128;
        }
    }
    setFullRow(t_boardy);
    Curbox_x=Sys_x+Begin_boxs_x*BSIZE,Curbox_y=Sys_y;/*�ٴγ�ʼ������*/
    if(box_numb==-1) box_numb=rand()%MAX_BOX;
    current_box_numb=box_numb;
    flag_newbox=false;
    return(rand()%MAX_BOX);
}

/*
 *  ����(x,y)λ�ÿ�ʼ�ı��Ϊbox_numb��box.
 */
void EraseBox(int x,int y,int box_numb)
{
    int mask=128,t_boardx,t_boardy,n,m;
    setfillstyle(SOLID_FILL,BgColor);
    for(n=0;n<4;n++)
    {
        for(m=0;m<4;m++)    /*��������ĸ���Ԫ*/
        {
            if( ((shapes[box_numb].box[n/2]) & mask) )/*������з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
            {
                bar(x+m*BSIZE,y+n*BSIZE,x+m*BSIZE+BSIZE,y+n*BSIZE+BSIZE);
                line(x+m*BSIZE,y+n*BSIZE,x+m*BSIZE+BSIZE,y+n*BSIZE);
                line(x+m*BSIZE,y+n*BSIZE,x+m*BSIZE,y+n*BSIZE+BSIZE);
                line(x+m*BSIZE,y+n*BSIZE+BSIZE,x+m*BSIZE+BSIZE,y+n*BSIZE+BSIZE);
                line(x+m*BSIZE+BSIZE,y+n*BSIZE,x+m*BSIZE+BSIZE,y+n*BSIZE+BSIZE);
            }
            mask=mask/(2);
            if(mask==0)mask=128;
        }
    }

}



 void ErasePreBox(int x,int y,int box_numb)
{
    int mask=128,t_boardx,t_boardy,n,m;
    setfillstyle(SOLID_FILL,BgColor);
    for(n=0;n<4;n++)
    {
        for(m=0;m<4;m++)    /*��������ĸ���Ԫ*/
        {
            if( ((shapes[box_numb].box[n/2]) & mask) )/*������з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
            {
                bar(x+m*BSIZE,y+n*BSIZE,x+m*BSIZE+BSIZE,y+n*BSIZE+BSIZE);

            }
            mask=mask/(2);
            if(mask==0)mask=128;
        }
    }

}

/* �ж��Ƿ�����ƶ�
 * x,yΪ��ǰ����λ��
 * box_numbΪ�����
 * direction �����־ 
 *  ����true ��false
 #define MoveLeft -1
 #define MoveRight 1
 #define MoveDown 0
 */
int MoveAble(int x,int y,int box_numb,int direction)
{
    int n,m,t_boardx,t_boardy;          /*t_boardx ��ǰ�������������Ϸ���λ��*/
    int mask;
    if(direction==MoveLeft)             /*���������*/
    {
        mask=128;
        x-=BSIZE;
        t_boardx=(x-Sys_x)/BSIZE;
        t_boardy=(y-Sys_y)/BSIZE;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*��������ĸ���Ԫ*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*������з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
                {
                    if((x+BSIZE*m)<Sys_x)return(false);/*�����������*/
                    else if(Table_board[t_boardy+n][t_boardx+m].var) /*����һ������󣬴�4*4����������Ϸ���г�ͻ*/
                    {
                        return(false);
                    }
                }
                mask=mask/(2);
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else if(direction==MoveRight)       /*���������*/
    {
        x+=BSIZE;
        t_boardx=(x-Sys_x)/BSIZE;
        t_boardy=(y-Sys_y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*�����ұ��ĸ���Ԫ*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*���ұ��з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
                {
                    if((x+BSIZE*m)>=(Sys_x+BSIZE*Horizontal_boxs) )return(false);/*�������ұ���*/
                    else if( Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        return(false);
                    }
                }
                mask=mask/(2);
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else if(direction==MoveDown)        /*���������*/
    {
        y+=BSIZE;
        t_boardx=(x-Sys_x)/BSIZE;
        t_boardy=(y-Sys_y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*�����±��ĸ���Ԫ*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*���±��з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
                {
                    if((y+BSIZE*n)>=(Sys_y+BSIZE*Vertical_boxs) ||  Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        flag_newbox=true;
                        break;
                    }
                }
                mask=mask/(2);
                /*mask����Ϊ:10000000,01000000,00100000,00010000
                             00001000,00000100,00000010/00000001
                 */
                if(mask==0)mask=128;
            }
        }
        if(flag_newbox)
        {
            return(false);
        }
        else
            return(true);
    }
    else if(direction==MoveRoll)        /*ת��*/
    {
        t_boardx=(x-Sys_x)/BSIZE;
        t_boardy=(y-Sys_y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*�����±��ĸ���Ԫ*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*���±��з��鲢�ҵ�ǰ��Ϸ��Ҳ�з���*/
                {
                    if((y+BSIZE*n)>=(Sys_y+BSIZE*Vertical_boxs) )return(false);/*�������±���*/
                    if((x+BSIZE*n)>=(Sys_x+BSIZE*Horizontal_boxs) )return(false);/*�����������*/
                    if((x+BSIZE*m)>=(Sys_x+BSIZE*Horizontal_boxs) )return(false);/*�������ұ���*/

                    else if( Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        return(false);
                    }
                }
                mask=mask/(2);
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else
    {
        return(false);
    }

}

/*
 *��ʾָ���ķ���
 */
void show_box(int x,int y,int box_numb,int color)
{
    int i,ii,ls_x=x;
    if(box_numb<0 || box_numb>=MAX_BOX)/*ָ���ķ��鲻����*/
        box_numb=MAX_BOX/2;
    setfillstyle(SOLID_FILL,color);
/********************************* 
 *   ��λ���жϵ���һλ��1
 *   ������ÿ1���ð���ֽ�����ʾ
 *   128d=1000 0000b
 *********************************/
    for(ii=0;ii<2;ii++) 
    {
        int mask=128;
        for(i=0;i<8;i++)
        {
            if(i%4==0 && i!=0)              /*��ʾת���������һ����*/
            {
                y+=BSIZE;
                x=ls_x;
            }
                       if((shapes[box_numb].box[ii])&mask)
            {
                bar(x,y,x+BSIZE,y+BSIZE);
                line(x,y,x+BSIZE,y);
                line(x,y,x,y+BSIZE);
                line(x,y+BSIZE,x+BSIZE,y+BSIZE);
                line(x+BSIZE,y,x+BSIZE,y+BSIZE);
            }
            x+=BSIZE;
            mask/=2;
        }
        y+=BSIZE;
        x=ls_x;
    }
}




void main()
{
    int GameOver=0;
    int key,nextbox; 
    int Currentaction=0;/*��ǵ�ǰ����״̬*/
    int gd=VGA,gm=VGAHI,errorcode;

    initgraph(&gd,&gm,"");
    errorcode = graphresult(); 
    if (errorcode != grOk)  
    {
        printf("\nNotice:Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to quit!");
        getch(); 
        exit(1);            
    }
    setbkcolor(BgColor);
    setcolor(FgColor);
    randomize();
    SetTimer(newtimer);

    initialize(Sys_x,Sys_y,Horizontal_boxs,Vertical_boxs);/*��ʼ��*/


    nextbox=MkNextBox(-1);

    show_box(Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);
    show_box(LeftWin_x,Curbox_y+200,nextbox,shapes[nextbox].color);
    show_intro(Sys_x,Curbox_y+320);
    getch();
    while(1)
    {
        /* Currentaction=0;
        flag_newbox=false;
        ����Ƿ��а���*/
        if (bioskey(1)){key=bioskey(0);     }
        else            {           key=0;      }

        switch(key)
        {
            case VK_LEFT:
                if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MoveLeft))
                {EraseBox(Curbox_x,Curbox_y,current_box_numb);Curbox_x-=BSIZE;Currentaction=MoveLeft;}
                break;
            case VK_RIGHT:
                if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MoveRight))
                {EraseBox(Curbox_x,Curbox_y,current_box_numb);Curbox_x+=BSIZE;Currentaction=MoveRight;}
                break;
            case VK_DOWN:
                if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MoveDown))
                {EraseBox(Curbox_x,Curbox_y,current_box_numb);Curbox_y+=BSIZE;Currentaction=MoveDown;}
                else flag_newbox=true;
                break;
            case VK_UP:/*��ת����*/
                if(MoveAble(Curbox_x,Curbox_y,shapes[current_box_numb].next,MoveRoll))
                {EraseBox(Curbox_x,Curbox_y,current_box_numb);current_box_numb=shapes[current_box_numb].next;
                    Currentaction=MoveRoll;
                }
                break;
            
            case VK_ESC:
                GameOver=1;
                break;
            default:
                break;
        }

        if(Currentaction)
        {   /*��ʾ��ǰ�ж���,�ƶ���ת��*/
            show_box(Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);
            Currentaction=0;
        }

            /*�������¼�������������,�Ͳ����·���*/
        if(flag_newbox)
        {
            /*��ʱ�൱�ڷ��鵽�ײ���,�����г��ֵ���һ�е���ȥ����0*/
            ErasePreBox(LeftWin_x,Sys_y+200,nextbox);
            nextbox=MkNextBox(nextbox);
            show_box(LeftWin_x,Curbox_y+200,nextbox,shapes[nextbox].color);
            if(!MoveAble(Curbox_x,Curbox_y,current_box_numb,MoveDown))/*��һ��ʼ,��Ϸ����*/
            {
                show_box(Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);
                GameOver=1;
            }
            else
            {
                flag_newbox=false;
            }
            Currentaction=0;
        }
        else    /*��������*/
        {
            if (Currentaction==MoveDown || TimerCounter> (20-speed*2))
            {
                if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MoveDown))
                {
                    EraseBox(Curbox_x,Curbox_y,current_box_numb);Curbox_y+=BSIZE;
                    show_box(Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);
                }
                TimerCounter=0;
            }
        }

        if(GameOver )/*|| flag_newbox==-1*/
        {
            printf("game over,thank you! your score is %d",score);
            getch();
            break;
        }
    }
    getch();
    KillTimer();
    closegraph();
}
