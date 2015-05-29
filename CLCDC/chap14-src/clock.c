/*����ʱ��Դ����*/
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<dos.h>
#define PI 3.1415926 /*���峣��*/
#define UP 0x4800   /*���ơ������޸�ʱ��*/
#define DOWN 0x5000 /*���ơ������޸�ʱ��*/
#define ESC 0x11b   /*ESC�� �� �˳�ϵͳ*/
#define TAB 0xf09   /*TAB�� �� �ƶ����*/
/*��������*/
int keyhandle(int,int); /*���̰����жϣ���������غ�������*/
int timeupchange(int);  /*�������ư���*/
int timedownchange(int); /*�������ư���*/
int digithour(double); /*��double�͵�Сʱ��ת����int��*/
int digitmin(double);  /*��double�͵ķ�����ת����int��*/
int digitsec(double);   /*��double�͵�������ת����int��*/
void digitclock(int,int,int ); /*��ָ��λ����ʾʱ�ӻ���ӻ�������*/
void drawcursor(int); /*����һ�����*/
void clearcursor(int);/*����ǰһ�����*/
void clockhandle(); /*ʱ�Ӵ���*/

double h,m,s; /*ȫ�ֱ���:Сʱ���֣���*/
double x,x1,x2,y,y1,y2; /*ȫ�ֱ���:����ֵ*/
struct time t[1];/*����һ��time�ṹ���͵�����*/
main()
{
 int driver, mode=0,i,j;
 driver=DETECT; /*�Զ������ʾ�豸*/
 initgraph(&driver, &mode, "");/*��ʼ��ͼ��ϵͳ*/
 setlinestyle(0,0,3); /*���õ�ǰ���߿�Ⱥ�����:���������ʵ��*/
 setbkcolor(0);/*�õ�ɫ�����õ�ǰ������ɫ*/
 setcolor(9); /*���õ�ǰ������ɫ*/
 line(82,430,558,430);
 line(70,62,70,418);
 line(82,50,558,50);
 line(570,62,570,418);
 line(70,62,570,62);
 line(76,56,297,56);
 line(340,56,564,56);       /*�������ܵı�ֱ��*/
 /*arc(int x, int y, int stangle, int endangle, int radius)*/
 arc(82,62,90,180,12);
 arc(558,62,0,90,12);
 setlinestyle(0,0,3);
 arc(82,418,180,279,12);
 setlinestyle(0,0,3);
 arc(558,418,270,360,12);   /*�������ܵı߽ǻ���*/
 setcolor(15);
 outtextxy(300,53,"CLOCK"); /*��ʾ����*/
 setcolor(7);
 rectangle(342,72,560,360); /*��һ������,��Ϊʱ�ӵĿ��*/

 setwritemode(0); /*�涨���ߵķ�ʽ��mode=0, ���ʾ����ʱ������λ�õ�ԭ����Ϣ����*/
 setcolor(15);
 outtextxy(433,75,"CLOCK");/*ʱ�ӵı���*/
 setcolor(7);
 line(392,310,510,310);
 line(392,330,510,330);
 arc(392,320,90,270,10);
 arc(510,320,270,90,10); /*���Ƶ��Ӷ���ʱ���µ�����ʱ�ӵı߿��*/
 /*��������ʱ�ӵ�ʱ����ķָ���*/
 setcolor(5);
 for(i=431;i<=470;i+=39)
   for(j=317;j<=324;j+=7){
   setlinestyle(0,0,3);
   circle(i,j,1); /*��(i, y)ΪԲ��,1Ϊ�뾶��Բ*/
  }
 setcolor(15);
 line(424,315,424,325); /*�����е���ʱ��ǰ�Ȼ�һ�����*/
 /*���Ʊ�ʾСʱ��Բ��*/
 for(i=0,m=0,h=0;i<=11;i++,h++){
    x=100*sin((h*60+m)/360*PI)+451;
    y=200-100*cos((h*60+m)/360*PI);
    setlinestyle(0,0,3);
    circle(x,y,1);
 }
 /*���Ʊ�ʾ���ӻ����ӵ�Բ��*/
 for(i=0,m=0;i<=59;m++,i++){
    x=100*sin(m/30*PI)+451;
    y=200-100*cos(m/30*PI);
    setlinestyle(0,0,1);
    circle(x,y,1);
 }
 /*�ڵ��ӱ����ߴ�ӡ������ʾ��Ϣ*/
 setcolor(4);
 outtextxy(184,125,"HELP");
 setcolor(15);
 outtextxy(182,125,"HELP");
 setcolor(5);
 outtextxy(140,185,"TAB : Cursor move");
 outtextxy(140,225,"UP  : Time ++");
 outtextxy(140,265,"DOWN: Time --");
 outtextxy(140,305,"ESC : Quit system!");
 outtextxy(140,345,"Version : 2.0");
 setcolor(12);
 outtextxy(150,400,"Nothing is more important than time!");
 clockhandle();/*��ʼ����ʱ�Ӵ������*/
 closegraph(); /*�ر�ͼ��ϵͳ*/
 return 0; /*��ʾ������������,�����ϵͳ����һ��0ֵ*/
 }

void clockhandle()
{
 int k=0,count;
 setcolor(15);
 gettime(t);/*ȡ��ϵͳʱ��,������time�ṹ���͵����������*/
 h=t[0].ti_hour;
 m=t[0].ti_min;
 x=50*sin((h*60+m)/360*PI)+451; /*ʱ���x����ֵ*/
 y=200-50*cos((h*60+m)/360*PI); /*ʱ���y����ֵ*/
 line(451,200,x,y);/*�ڵ��ӱ��л���ʱ��*/

 x1=80*sin(m/30*PI)+451; /*�����x����ֵ*/
 y1=200-80*cos(m/30*PI); /*�����y����ֵ*/
 line(451,200,x1,y1); /*�ڵ��ӱ��л��Ʒ���*/

 digitclock(408,318,digithour(h)); /*������ʱ���У���ʾ��ǰ��Сʱֵ*/
 digitclock(446,318,digitmin(m)); /*������ʱ���У���ʾ��ǰ�ķ���ֵ*/
 setwritemode(1);
 /*�涨���ߵķ�ʽ,���mode=1,���ʾ����ʱ���������Ե���
������֮��ԭ�е��߽������(XOR)����,ʵ���ϻ���������ԭ���������ڹ涨
���߽�������Ľ�������, ���ߵ����Բ���, �������λ��߲����൱��û�� 
���ߣ����ڵ�ǰλ�ô������ԭ���Ļ���*/
 for(count=2;k!=ESC;){ /*��ʼѭ����ֱ���û�����ESC������ѭ��*/
   setcolor(12);/*����ɫ*/
   sound(500);/*��ָ��Ƶ�ʴ�PC������,����Ƶ��Ϊ500Hz*/
   delay(700);/*��һ��Ƶ��Ϊ500Hz������,ά��700����*/
   sound(200);/*��ָ��Ƶ�ʴ�PC������,����Ƶ��Ϊ200Hz*/
   delay(300);
   /*�������ֲ�ͬƵ�ʵ��������ɷ����ӱ�ת��ʱ��������*/
   nosound(); /*�ر�PC������*/
   s=t[0].ti_sec;
   m=t[0].ti_min;
   h=t[0].ti_hour;

   x2=98*sin(s/30*PI)+451; /*�����x����ֵ*/
   y2=200-98*cos(s/30*PI); /*�����y����ֵ*/
   line(451,200,x2,y2);
   /*��������*/

   /*���ô�ѭ��,��ʱһ��*/
   while(t[0].ti_sec==s&&t[0].ti_min==m&&t[0].ti_hour==h)
   {  gettime(t);/*ȡ��ϵͳʱ��*/
      if(bioskey(1)!=0){
       k=bioskey(0);
       count=keyhandle(k,count);
      if(count==5) count=1;
      }
     }
   setcolor(15);
   digitclock(485,318,digitsec(s)+1);/*����ʱ�����ӣ���*/

   setcolor(12); /*����ɫ*/
   x2=98*sin(s/30*PI)+451;
   y2=200-98*cos(s/30*PI);
   line(451,200,x2,y2);
  /*��ԭ������ɫ��ԭ��λ�ô��ٻ������룬�Դﵽ�����ǰ�����Ŀ��*/

   /*���Ӵ���*/
  if(t[0].ti_min!=m){ /*�������б仯*/
         /*������ǰ����*/
         setcolor(15); /*��ɫ*/
         x1=80*sin(m/30*PI)+451;
         y1=200-80*cos(m/30*PI);
         line(451,200,x1,y1);
         /*�����µķ���*/
         m=t[0].ti_min;
         digitclock(446,318,digitmin(m)); /*������ʱ������ʾ�µķ���ֵ*/
         x1=80*sin(m/30*PI)+451;
         y1=200-80*cos(m/30*PI);
         line(451,200,x1,y1);
  }

  /*Сʱ����*/
  if((t[0].ti_hour*60+t[0].ti_min)!=(h*60+m)){  /*��Сʱ���б仯*/
         /*������ǰʱ��*/
          setcolor(15); /*��ɫ*/
          x=50*sin((h*60+m)/360*PI)+451;/*50:ʱ�ӵĳ��ȣ���λ�����أ���451:Բ�ĵ�x����ֵ*/
          y=200-50*cos((h*60+m)/360*PI);
          line(451,200,x,y);
          /*�����µ�ʱ��*/
          h=t[0].ti_hour;
          digitclock(408,318,digithour(h));
          x=50*sin((h*60+m)/360*PI)+451;
          y=200-50*cos((h*60+m)/360*PI);
          line(451,200,x,y);
     }
   }
 }


int keyhandle(int key,int count)   /*���̿��� */
{ switch(key)
   {case UP: timeupchange(count-1); /*��Ϊcount�ĳ�ʼֵΪ�������Դ˴�����*/
    break;
    case DOWN:timedownchange(count-1); /*��Ϊcount�ĳ�ʼֵΪ�������Դ˴�����*/
     break;
    case TAB:setcolor(15);
    clearcursor(count); /*���ԭ���Ĺ��*/
    drawcursor(count);  /*��ʾһ���µĹ��*/
    count++;
    break;
  }
  return count;
 }

int timeupchange(int count) /*���������Ƶİ���*/
{
     if(count==1){
        t[0].ti_hour++;
        if(t[0].ti_hour==24) t[0].ti_hour=0;
        settime(t); /*�����µ�ϵͳʱ��*/
        }

     if(count==2){
        t[0].ti_min++;
        if(t[0].ti_min==60) t[0].ti_min=0;
        settime(t); /*�����µ�ϵͳʱ��*/
        }

    if(count==3){
        t[0].ti_sec++;
        if(t[0].ti_sec==60) t[0].ti_sec=0;
        settime(t); /*�����µ�ϵͳʱ��*/
        }
 }

int timedownchange(int count) /*���������Ƶİ���*/
{
   if(count==1) {
        t[0].ti_hour--;
        if(t[0].ti_hour==0) t[0].ti_hour=23;
        settime(t);/*�����µ�ϵͳʱ��*/
        }
   if(count==2) {
        t[0].ti_min--;
        if(t[0].ti_min==0) t[0].ti_min=59;
        settime(t);/*�����µ�ϵͳʱ��*/
        }

  if(count==3) {
        t[0].ti_sec--;
        if(t[0].ti_sec==0) t[0].ti_sec=59;
        settime(t);/*�����µ�ϵͳʱ��*/
        }
 }


 int digithour(double h)/*��double�͵�Сʱ��ת����int��*/
{int i;
 for(i=0;i<=23;i++)
  {if(h==i) return i;}
 }

int digitmin(double m)/*��double�͵ķ�����ת����int��*/
{int i;
 for(i=0;i<=59;i++)
  {if(m==i) return i;}
}

int digitsec(double s) /*��double�͵�������ת����int��*/
{int i;
 for(i=0;i<=59;i++)
  {if(s==i) return i;}
}


void digitclock(int x,int y,int clock)/*��ָ��λ����ʾ����ʱ��:ʱ\��\��*/
{char buffer1[10];
 setfillstyle(0,2);
 bar(x,y,x+15,328);
 if(clock==60) clock=0;
 sprintf(buffer1,"%d",clock);
 outtextxy(x,y,buffer1);
 }

void drawcursor(int count)    /*����count��ֵ����һ�����*/
{switch(count)
 {
  case 1:line(424,315,424,325);break;
  case 2:line(465,315,465,325);break;
  case 3:line(505,315,505,325);break;
  }
 }

void clearcursor(int count)    /*����count��ֵ�����ǰһ�����*/
{switch(count)
 {
  case 2:line(424,315,424,325);break;
  case 3:line(465,315,465,325);break;
  case 1:line(505,315,505,325);break;
  }
 }

