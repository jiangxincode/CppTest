#include "stdio.h"    /* ��׼���������      */
#include "string.h"   /* �ַ�������������    */
#include "math.h"     /* ��ѧ������          */
#include "stdlib.h"   /* ��׼������          */
#include "graphics.h" /* ͼ�κ�����          */
#include "bios.h"     /* �����������ϵͳ������*/
#include "dos.h"      /* dos������           */

#define NUM0       0x5230    /* С�����������ּ�0  */
#define NUM1       0x4f31    /* С�����������ּ�1  */
#define NUM2       0x5032    /* С�����������ּ�2  */
#define NUM3       0x5133    /* С�����������ּ�3  */
#define NUM4       0x4b34    /* С�����������ּ�4  */
#define NUM5       0x4c35    /* С�����������ּ�5  */
#define NUM6       0x4d36    /* С�����������ּ�6  */
#define NUM7       0x4737    /* С�����������ּ�7  */
#define NUM8       0x4838    /* С�����������ּ�8  */
#define NUM9       0x4939    /* С�����������ּ�9  */
#define NUMPNT     0x532e    /* С�������� . ��    */
#define NUMADD     0x4e2b    /* С�������� + ��    */
#define NUMSUB     0x4a2d    /* С�������� - ��    */
#define NUMMUL     0x372a    /* С�������� * ��    */
#define NUMDIV     0x352f    /* С�������� / ��    */
#define NUMEQU     0x1c0d    /* С�������� = ��    */

#define KEY0       0xb30     /* �������������ּ�0  */
#define KEY1       0x231     /* �������������ּ�1  */
#define KEY2       0x332     /* �������������ּ�2  */
#define KEY3       0x433     /* �������������ּ�3  */
#define KEY4       0x534     /* �������������ּ�4  */
#define KEY5       0x635     /* �������������ּ�5  */
#define KEY6       0x736     /* �������������ּ�6  */
#define KEY7       0x837     /* �������������ּ�7  */
#define KEY8       0x938     /* �������������ּ�8  */
#define KEY9       0xa39     /* �������������ּ�9  */
#define KEYPNT     0x342e    /* ���������� . ��    */
#define KEYSUB     0xc2d     /* ���������� - ��    */
#define KEYMUL     0x92a     /* ���������� * ��    */
#define KEYEQU     0xd3d     /* ���������� = ��    */

#define SQR        0x340     /* @ ��,��ƽ���� */
#define KEYR       0x1372    /* r ��,ȡ���� */
#define PERCENT    0x625     /* % ��,��ٷ��� */
#define DEL        0x5300    /* DEL ��  */
#define ESC        0x11b     /* ESC ��  */
#define BACKSPACE  0xe08     /* �˸� ��  */
#define F9         0x4300    /* F9 �����������任  */
#define CTRL_L     0x260c    /* Ctrl ��+L��������������е���ֵ */
#define CTRL_R     0x1312    /* Ctrl ��+R������ȡ�������е���ֵ */
#define CTRL_M     0x320d    /* Ctrl ��+M��������ǰ��ֵд���������*/
#define CTRL_P     0x1910    /* Ctrl ��+P��������ǰ��ֵ�ͼ������б������ֵ���*/
#define ALT_X      0x2d00    /* Alt ��+X��  */

#define TRUE  1     /* Ϊʮ����1��ʾΪ�� true  */
#define FALSE 0     /* Ϊʮ����0��ʾΪ�� false */

/*����������ṹ��*/
struct Block
    {    int  left,top,width,height;        /* ��������,��,��          */
         char caption[50];                  /* ����                    */
         int  fontcolor,fontsize,status;    /* ������ɫ,�����С,״̬  */
    };

void Form(struct Block form);      /* �������ʾ������*/
void TextBox(struct Block txtbox); /* �������ʾ�ı������*/
void Label(struct Block label);    /* �������ʾ��ǩ�������书�ܿ�������ǩ���Ϊ��M*/

void CommandButton(struct Block cmdbutton); /*��ʾcmdbutton[i]���ť*/
void CommandButton_KeyboardDown(int i); /*���尴�±��Ϊi�ļ������еĲ������簴ť��״̬�ĸı�*/
void CommandButton_KeyboardUp(int i);   /*�����ɿ����Ϊi�İ��������еĲ������簴ť��״̬*/


void InitApp(); /*��ʼ������*/
void Showme();  /*��ʾ����������*/
void Load();    /*��ʼ��Ĭ��ֵ*/

void CommandButton_Click(int key);  /*������ʱ�����Ĳ���*/
void DoubleRun(); /*��������:�Ӽ��˳�*/
void SingleRun(int operatoror); /*������*/
void Resetbuf(); /*���û�����*/
void StoreSet(int key); /*�������洢����*/
void Unload(); /*�˳�ϵͳʱ��һЩ�ָ�����*/


struct Block frmmain,txtscreen,lblstore,cmdbutton[28]; /*����������,�ı������,�����ǩ,28[0-27]����ť*/
int clickflag;  /*clickflag:������־��*/
int top,pointflag,digitkeyhit; /*top:���滺�����еĵ�ǰλ����pointflag:С�����ǣ�digitkeyhit:���ּ��������*/
int operatoror,runflag,ctnflag; /*operatoror:��������runflag:�����ǣ�ctnflag:��������*/
int errorflag; /*������*/
double num1,num2,store; /*num1:������1,num2��������2,store���������*/
char strbuf[33];  /*�ַ�������,���ڱ���һ��������*/


void main()
    {

         int key;  /*����˼������϶���İ������*/
         InitApp();/*��ʼ�����򣬽���ͼ��ģʽ*/
         Showme(); /*��ʾ����������*/
         Load();   /*��ʼ��Ĭ��ֵ*/
         while(1)
             {
                    if(bioskey(1)==0) continue; /*ֱ���м�����ʱ���ŷ��ط�0ֵ�����򷵻�0ֵ*/
                    key=bioskey(0); /*�����������İ���ֵ*/
                    switch(key)    /*������Ӧ�ļ��̰�����ƥ�䵽������������*/
                        {    case NUM0:case KEY0:          key=10;break;
                             case NUM1:case KEY1:          key=1;break;
                             case NUM2:case KEY2:          key=2;break;
                             case NUM3:case KEY3:          key=3;break;
                             case NUM4:case KEY4:          key=4;break;
                             case NUM5:case KEY5:          key=5;break;
                             case NUM6:case KEY6:          key=6;break;
                             case NUM7:case KEY7:          key=7;break;
                             case NUM8:case KEY8:          key=8;break;
                             case NUM9:case KEY9:          key=9;break;
                             case F9:                      key=11;break;
                             case NUMPNT:case KEYPNT:      key=12;break;
                             case NUMADD:                  key=13;break;
                             case NUMSUB:case KEYSUB:      key=14;break;
                             case NUMMUL:case KEYMUL:      key=15;break;
                             case NUMDIV:                  key=16;break;
                             case SQR:                     key=17;break;
                             case PERCENT:                 key=18;break;
                             case KEYR:                    key=19;break;
                             case NUMEQU:case KEYEQU:      key=20;break;
                             case CTRL_L:                  key=21;break;
                             case CTRL_R:                  key=22;break;
                             case CTRL_M:                  key=23;break;
                             case CTRL_P:                  key=24;break;
                             case BACKSPACE:               key=25;break;
                             case DEL:                     key=26;break;
                             case ESC:                     key=27;break;
                             case ALT_X:                   key=0; break;
                             default:                      key=-1;break;
                     }
             if(key<0) continue; /*����Ӧ�İ������ظ������򷵻ص�while(1)��ִ��*/
             CommandButton_KeyboardDown(key);/*Ϊ���ڼ���������ʾ����Ч�����ڴ˺����иı�һЩ��ť��״ֵ̬*/
             CommandButton_Click(key); /*����key��ֵ��������ز���*/
             delay(300000);    /*Ϊ��ͻ������Ч�����˴���ʱ300000����*/
             CommandButton_KeyboardUp(key); /*�ڴ�����˰�����Ҫ�ָ���ť��״ֵ̬*/
        }
    }

void InitApp()   /*��ʼ������*/
    {
         int driver=DETECT,mode; /* ��ʾ�豸����Ϊ�Զ������ʾ��ģʽ */
         initgraph(&driver,&mode,"");   /* ��ʼ��ͼ����ʾϵͳ  */
         if(driver!=VGA&&driver!=EGA)  /* ������ܳ�ʼ��  */
             {  printf("\n\nERROR!Can't initialize the graphics system!"); /* ��ʾ������Ϣ"���ܳ�ʼ��ͼ��ϵͳ"  */
                    closegraph();   /* �ر�ͼ�νӿ�*/
                    exit(0);       /* ֱ���˳�ϵͳ */
             }
         setbkcolor(9);     /* ���ñ�����ɫΪ��ɫ  */


         /*�����ڵ���������*/
         frmmain.left=200; frmmain.top=100; frmmain.width=230;  frmmain.height=235; frmmain.fontcolor=BLACK; frmmain.fontsize=1;   strcpy(frmmain.caption,"   << Calculator >>");frmmain.status=1;
         /*�ı������������*/
         txtscreen.left=10;txtscreen.top=25;txtscreen.width=210;txtscreen.height=30;txtscreen.fontcolor=BLACK;txtscreen.fontsize=1;strcpy(txtscreen.caption,"0.");           txtscreen.status=1;
         /*��ǩ����������*/
         lblstore.left=190; lblstore.top=62; lblstore.width=30;  lblstore.height=25; lblstore.fontcolor=YELLOW; lblstore.fontsize=1;strcpy(lblstore.caption,"");              lblstore.status=1;
         /*���ť����������*/
         cmdbutton[1].left=50-35;cmdbutton[1].top=165;cmdbutton[1].width=30;cmdbutton[1].height=25;cmdbutton[1].fontcolor=BLUE;cmdbutton[1].fontsize=1;strcpy(cmdbutton[1].caption,"1");cmdbutton[1].status=1;
         cmdbutton[2].left=85-35;cmdbutton[2].top=165;cmdbutton[2].width=30;cmdbutton[2].height=25;cmdbutton[2].fontcolor=BLUE;cmdbutton[2].fontsize=1;strcpy(cmdbutton[2].caption,"2");cmdbutton[2].status=1;
         cmdbutton[3].left=120-35;cmdbutton[3].top=165;cmdbutton[3].width=30;cmdbutton[3].height=25;cmdbutton[3].fontcolor=BLUE;cmdbutton[3].fontsize=1;strcpy(cmdbutton[3].caption,"3");cmdbutton[3].status=1;
         cmdbutton[4].left=50-35;cmdbutton[4].top=130;cmdbutton[4].width=30;cmdbutton[4].height=25;cmdbutton[4].fontcolor=BLUE;cmdbutton[4].fontsize=1;strcpy(cmdbutton[4].caption,"4");cmdbutton[4].status=1;
         cmdbutton[5].left=85-35;cmdbutton[5].top=130;cmdbutton[5].width=30;cmdbutton[5].height=25;cmdbutton[5].fontcolor=BLUE;cmdbutton[5].fontsize=1;strcpy(cmdbutton[5].caption,"5");cmdbutton[5].status=1;
         cmdbutton[6].left=120-35;cmdbutton[6].top=130;cmdbutton[6].width=30;cmdbutton[6].height=25;cmdbutton[6].fontcolor=BLUE;cmdbutton[6].fontsize=1;strcpy(cmdbutton[6].caption,"6");cmdbutton[6].status=1;
         cmdbutton[7].left=50-35;cmdbutton[7].top=95;cmdbutton[7].width=30;cmdbutton[7].height=25;cmdbutton[7].fontcolor=BLUE;cmdbutton[7].fontsize=1;strcpy(cmdbutton[7].caption,"7");cmdbutton[7].status=1;
         cmdbutton[8].left=85-35;cmdbutton[8].top=95;cmdbutton[8].width=30;cmdbutton[8].height=25;cmdbutton[8].fontcolor=BLUE;cmdbutton[8].fontsize=1;strcpy(cmdbutton[8].caption,"8");cmdbutton[8].status=1;
         cmdbutton[9].left=120-35;cmdbutton[9].top=95;cmdbutton[9].width=30;cmdbutton[9].height=25;cmdbutton[9].fontcolor=BLUE;cmdbutton[9].fontsize=1;strcpy(cmdbutton[9].caption,"9");cmdbutton[9].status=1;
         cmdbutton[10].left=50-35;cmdbutton[10].top=200;cmdbutton[10].width=30;cmdbutton[10].height=25;cmdbutton[10].fontcolor=BLUE;cmdbutton[10].fontsize=1;strcpy(cmdbutton[10].caption,"0");cmdbutton[10].status=1;
         cmdbutton[11].left=85-35;cmdbutton[11].top=200;cmdbutton[11].width=30;cmdbutton[11].height=25;cmdbutton[11].fontcolor=BLUE;cmdbutton[11].fontsize=1;strcpy(cmdbutton[11].caption,"+/-");cmdbutton[11].status=1;
         cmdbutton[12].left=120-35;cmdbutton[12].top=200;cmdbutton[12].width=30;cmdbutton[12].height=25;cmdbutton[12].fontcolor=BLUE;cmdbutton[12].fontsize=1;strcpy(cmdbutton[12].caption,".");cmdbutton[12].status=1;
         cmdbutton[13].left=155-35;cmdbutton[13].top=95;cmdbutton[13].width=30;cmdbutton[13].height=25;cmdbutton[13].fontcolor=RED;cmdbutton[13].fontsize=1;strcpy(cmdbutton[13].caption,"+");cmdbutton[13].status=1;
         cmdbutton[14].left=155-35;cmdbutton[14].top=130;cmdbutton[14].width=30;cmdbutton[14].height=25;cmdbutton[14].fontcolor=RED;cmdbutton[14].fontsize=1;strcpy(cmdbutton[14].caption,"-");cmdbutton[14].status=1;
         cmdbutton[15].left=155-35;cmdbutton[15].top=165;cmdbutton[15].width=30;cmdbutton[15].height=25;cmdbutton[15].fontcolor=RED;cmdbutton[15].fontsize=1;strcpy(cmdbutton[15].caption,"*");cmdbutton[15].status=1;
         cmdbutton[16].left=155-35;cmdbutton[16].top=200;cmdbutton[16].width=30;cmdbutton[16].height=25;cmdbutton[16].fontcolor=RED;cmdbutton[16].fontsize=1;strcpy(cmdbutton[16].caption,"/");cmdbutton[16].status=1;
         cmdbutton[17].left=190-35;cmdbutton[17].top=95;cmdbutton[17].width=30;cmdbutton[17].height=25;cmdbutton[17].fontcolor=BLUE;cmdbutton[17].fontsize=1;strcpy(cmdbutton[17].caption,"sqr");cmdbutton[17].status=1;
         cmdbutton[18].left=190-35;cmdbutton[18].top=130;cmdbutton[18].width=30;cmdbutton[18].height=25;cmdbutton[18].fontcolor=BLUE;cmdbutton[18].fontsize=1;strcpy(cmdbutton[18].caption,"%");cmdbutton[18].status=1;
         cmdbutton[19].left=190-35;cmdbutton[19].top=165;cmdbutton[19].width=30;cmdbutton[19].height=25;cmdbutton[19].fontcolor=BLUE;cmdbutton[19].fontsize=1;strcpy(cmdbutton[19].caption,"1/x");cmdbutton[19].status=1;
         cmdbutton[20].left=190-35;cmdbutton[20].top=200;cmdbutton[20].width=30;cmdbutton[20].height=25;cmdbutton[20].fontcolor=RED;cmdbutton[20].fontsize=1;strcpy(cmdbutton[20].caption,"=");cmdbutton[20].status=1;
         cmdbutton[21].left=190;cmdbutton[21].top=95;cmdbutton[21].width=30;cmdbutton[21].height=25;cmdbutton[21].fontcolor=RED;cmdbutton[21].fontsize=1;strcpy(cmdbutton[21].caption,"MC");cmdbutton[21].status=1;
         cmdbutton[22].left=190;cmdbutton[22].top=130;cmdbutton[22].width=30;cmdbutton[22].height=25;cmdbutton[22].fontcolor=RED;cmdbutton[22].fontsize=1;strcpy(cmdbutton[22].caption,"MR");cmdbutton[22].status=1;
         cmdbutton[23].left=190;cmdbutton[23].top=165;cmdbutton[23].width=30;cmdbutton[23].height=25;cmdbutton[23].fontcolor=RED;cmdbutton[23].fontsize=1;strcpy(cmdbutton[23].caption,"MS");cmdbutton[23].status=1;
         cmdbutton[24].left=190;cmdbutton[24].top=200;cmdbutton[24].width=30;cmdbutton[24].height=25;cmdbutton[24].fontcolor=RED;cmdbutton[24].fontsize=1;strcpy(cmdbutton[24].caption,"M+");cmdbutton[24].status=1;
         cmdbutton[25].left=50-35;cmdbutton[25].top=60;cmdbutton[25].width=53;cmdbutton[25].height=25;cmdbutton[25].fontcolor=RED;cmdbutton[25].fontsize=1;strcpy(cmdbutton[25].caption,"<-");cmdbutton[25].status=1;
         cmdbutton[26].left=108-35;cmdbutton[26].top=60;cmdbutton[26].width=53;cmdbutton[26].height=25;cmdbutton[26].fontcolor=RED;cmdbutton[26].fontsize=1;strcpy(cmdbutton[26].caption,"Del");cmdbutton[26].status=1;
         cmdbutton[27].left=166-35;cmdbutton[27].top=60;cmdbutton[27].width=53;cmdbutton[27].height=25;cmdbutton[27].fontcolor=RED;cmdbutton[27].fontsize=1;strcpy(cmdbutton[27].caption,"Esc");cmdbutton[27].status=1;
         /* ���ü��������� */
    }

void Showme()   /*��ʾ����������*/
    {    int i;
         Form(frmmain); /*��ʾ�����ڣ�frmmainΪ�����ڵĽṹ������*/
         TextBox(txtscreen); /*��ʾ�ı���*/
         Label(lblstore); /*��ʾ��������״̬��ǩ*/
         for(i=1;i<28;i++) /*��ʾ27����ť�ڼ�������������*/
             CommandButton(cmdbutton[i]);
    }

void Load() /*��ʼ��Ĭ��ֵ*/
    {    num1=num2=0;
         Resetbuf();
         ctnflag=FALSE;
         operatoror=0;
         runflag=FALSE;
         errorflag=FALSE;
         store=0;
         clickflag=FALSE;

         strcpy(txtscreen.caption,"0.");
         TextBox(txtscreen);/*�ı����г�ʼ��ʾΪ0.���ַ�*/

         strcpy(lblstore.caption,"");
         Label(lblstore);
    }

void Unload() /*�˳�ϵͳ*/
    {
         cleardevice(); /*���ͼ����Ļ*/
         closegraph();  /*�ر�ͼ��ϵͳ*/
         exit(0);
    }

void Resetbuf()
    {    strbuf[0]=' ';
         strbuf[1]=0;
         top=1;
         digitkeyhit=FALSE;
         pointflag=FALSE;
    }


void Form(struct Block form)   /* �������ʾ������*/
    {    int x1=form.left; /*�������Ͻǵĺ�����ֵ*/
         int y1=form.top;  /*�������Ͻǵ�������ֵ*/
         int x2=form.width+x1-1;/*�������½ǵĺ�����ֵ*/
         int y2=form.height+y1-1; /*�������½ǵ�������ֵ*/

         setfillstyle(SOLID_FILL,LIGHTGRAY); /*�������ģʽ����ɫ  */
                bar(x1+1,y1+1,x2-1,y2-1);    /*��һ������ɫ����䴰�ڣ���Ϊ������,���˺����������߿�*/
         setcolor(WHITE);                    /*���õ�ǰ������ɫ*/
                line(x1,y1,x2,y1);
                line(x1,y1,x1,y2);    /*�ð��߻��߿���ߺ��ϱߵ��ߣ�����������*/
         setcolor(DARKGRAY);          /*�������ģʽ����ɫ  */
                line(x2,y1,x2,y2);
                line(x1,y2,x2,y2);    /*�����ɫ���߿��ұߺ��±ߵ��ߣ�����������*/
         setfillstyle(SOLID_FILL,RED);
                bar(x1+2,y1+2,x2-2,y1+15);    /*���ñ�������ɫΪ��ɫ*/
         settextjustify(LEFT_TEXT,CENTER_TEXT); /*�����ı��Ķ��뷽ʽΪ���ж���*/
         settextstyle(DEFAULT_FONT,0,form.fontsize); /*�����ı���ʾ����ΪĬ������,��СΪ�����������С*/
         setcolor(form.fontcolor);
                outtextxy(x1+3,y1+10,form.caption);  /*�����������ɫ��ʾ�����ڱ�����*/

         if(form.status&1)     /*�жϴ����Ƿ����,δʹ��ALT+X��,���Ͻǵģذ�ť*/
             {      cmdbutton[0].left=form.width-15;
                    cmdbutton[0].top=3;
                    cmdbutton[0].width=12;
                    cmdbutton[0].height=12;
                    cmdbutton[0].status=1;
                    cmdbutton[0].caption[0]=0;
                    CommandButton(cmdbutton[0]);
                    x1=cmdbutton[0].left+form.left;
                    y1=cmdbutton[0].top+form.top;
                    x2=cmdbutton[0].width+x1-1;
                    y2=cmdbutton[0].height+y1-1;
                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                         bar(x1+1,y1+1,x2-1,y2-1);
                    setcolor(DARKGRAY);
                         line(x1+2,y1+2,x2-2,y2-2);
                         line(x2-2,y1+2,x1+2,y2-2);
             }

    }

void TextBox(struct Block txtbox)     /* ���ú���ʾ�����*/
    {    /*(x1,y1),(x2,y2)Ϊ�������е��������*/
         int x1=txtbox.left+frmmain.left;
         int y1=txtbox.top+frmmain.top;
         int x2=txtbox.width+x1-1;
         int y2=txtbox.height+y1-1;

         setfillstyle(SOLID_FILL,WHITE);
                bar(x1+1,y1+1,x2-1,y2-1);
         /*��bar()�������߿����Խ����������������ı߿���*/
         setcolor(LIGHTGRAY);
                rectangle(x1+1,y1+1,x2-1,y2-1);
         setcolor(DARKGRAY);
                line(x1,y1,x2,y1);
                line(x1,y1,x1,y2);
                setcolor(WHITE);
                line(x2,y1,x2,y2);
                line(x1,y2,x2,y2);
         settextjustify(RIGHT_TEXT,CENTER_TEXT); /*Ϊͼ�κ��������ı��Ķ��뷽ʽ,��һ����Ϊˮƽ���뷽ʽ���ڶ�����Ϊ��ֱ���뷽ʽ*/
         settextstyle(DEFAULT_FONT,0,txtbox.fontsize); /*Ϊͼ��������õ�ǰ���ı�����:���壬���򣬴�С*/
         setcolor(txtbox.fontcolor); /*���÷������������ɫ*/
         outtextxy(x2-10,(y1+y2)/2,txtbox.caption);  /*��ָ��λ����ʾtxtbox.caption���ַ���ֵ*/

    }

void Label(struct Block label) /*���ú���ʾ���������书�ܵ�ʹ��״̬��Ĭ��Ϊ��*/
    {    int x1=label.left+frmmain.left;
         int y1=label.top+frmmain.top;
         int x2=label.width+x1-1;
         int y2=label.height+y1-1;

         setfillstyle(SOLID_FILL,LIGHTGRAY);
                bar(x1+1,y1+1,x2-1,y2-1);
         setcolor(DARKGRAY);
                line(x1,y1,x2,y1);
                line(x1,y1,x1,y2);
         setcolor(WHITE);
                line(x2,y1,x2,y2);
                line(x1,y2,x2,y2);
         settextjustify(CENTER_TEXT,CENTER_TEXT);
         settextstyle(DEFAULT_FONT,0,label.fontsize);
         setcolor(label.fontcolor);
                outtextxy((x1+x2)/2,(y1+y2)/2,label.caption);

    }

void CommandButton(struct Block cmdbutton)  /*���ú���ʾ������ť*/
    {     /*(x1,y1),(x2,y2)Ϊ�������е��������*/
         int x1=cmdbutton.left+frmmain.left;
         int y1=cmdbutton.top+frmmain.top;
         int x2=cmdbutton.width+x1-1;
         int y2=cmdbutton.height+y1-1;
         int c1,c2;
         /*��ť�ĳ�ʼ״̬Ϊ1,���м����º���״̬��Ϊ0,�����갴���������ָֻ�Ϊ״̬1*/
         if(cmdbutton.status) /*���ݰ�ť�ĵ�ǰ״ֵ̬�����ֱ��ò�ͬ����ɫ�߿����ػ�˰�ť*/
             {      c1=WHITE;  /*��ɫ*/
                    c2=DARKGRAY; /*���ɫ*/
             }
         else /*�����м�����*/
             {      c1=DARKGRAY;
                    c2=WHITE;
             }

         setcolor(c1);
                line(x1,y1,x2,y1);
                line(x1,y1,x1,y2);
         setcolor(c2);
                line(x2,y1,x2,y2);
                line(x1,y2,x2,y2);
         settextjustify(CENTER_TEXT,CENTER_TEXT);
         settextstyle(DEFAULT_FONT,0,cmdbutton.fontsize);
         outtextxy((x1+x2)/2,(y1+y2)/2,cmdbutton.caption);

    }

void CommandButton_KeyboardDown(int i) /*����ĳ��ʱ�����Ĳ���*/
    {    clickflag=TRUE;      /*���̵����־*/
         cmdbutton[i].status=0;
         CommandButton(cmdbutton[i]); /*�����ʼʱ��ͬ�ı߿���ɫɫ���ػ�����ť*/
    }



void CommandButton_KeyboardUp(int key) /*������������󣬻ָ���ť״̬���ػ�����ť*/
    {  clickflag=FALSE;
         cmdbutton[key].status=1;
         CommandButton(cmdbutton[key]);
    }



void CommandButton_Click(int key)      /*������Ӧ��������*/
    {
        if(errorflag==TRUE)  return;
         switch(key)
             {  case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:   /*1-9*/
                        if(top<15) /*����������С��15λ*/
                            {    strbuf[top++]='0'+key; /*'0'+key��ʾ���ַ�1,��û��'0'+��洢����Ascll��ΪkeyΪ�ַ�*/
                                 strbuf[top]=0; /*�洢����ASCLL��Ϊ0�ı�ʾ���ַ�Ctrl+@*/
                                 digitkeyhit=TRUE; /*��ʾ�������ּ�����*/
                                 strcpy(txtscreen.caption,strbuf); /*���ı�������ʾ��ǰ��*/
                            }
                        runflag=FALSE; /*������Ϊ��*/
                        if(ctnflag==FALSE) operatoror=0;
                        break;
                    case 10:     /* 0����*/
                        if(top<15&&top!=1)
                            {    strbuf[top++]='0';
                                 strbuf[top]=0;
                                 strcpy(txtscreen.caption,strbuf);
                            }
                        digitkeyhit=TRUE;
                        runflag=FALSE;
                        if(ctnflag==FALSE) operatoror=0;
                        break;
                    case 11:    /*��������*/
                        if(digitkeyhit==TRUE)
                            {    strbuf[0]=strbuf[0]==' '?'-':' ';
                                 strcpy(txtscreen.caption,strbuf);
                            }
                        else if(runflag==TRUE) /*��ʾû���µ����룬������֮ǰ�ļ�����������ת��*/
                            {    num1=-num2;
                                 sprintf(txtscreen.caption,"%G",num1);
                            }
                        else   /*ԭ������������*/
                            {    num1=-num1;
                                 sprintf(txtscreen.caption,"%G",num1);
                            }
                        runflag=FALSE;
                        if(ctnflag==FALSE) operatoror=0;
                        break;
                    case 12:   /*����һ��С����*/
                        if(top==1) /*��ʾ��û��������,����0.״̬*/
                            {  strbuf[top++]='0';
                                 strbuf[top++]='.';
                                 strbuf[top]=0;
                                 strcpy(txtscreen.caption,strbuf);
                                 digitkeyhit=TRUE;
                                 runflag=FALSE;
                                 pointflag=TRUE;
                                 if(ctnflag==FALSE) operatoror=0;
                            }
                        else if(top<15&&pointflag==FALSE)
                            {  strbuf[top++]='.';
                                 strbuf[top]=0;
                                 strcpy(txtscreen.caption,strbuf);
                                 digitkeyhit=TRUE;
                                 runflag=FALSE;
                                 pointflag=TRUE;
                                 if(ctnflag==FALSE) operatoror=0;
                            }
                        break;
                    case 13:case 14:case 15:case 16:   /* ��������Ӽ��˳������ */
                        if(digitkeyhit) /*���������֮ǰ�Ѿ�������һ����*/
                            num1=atof(strbuf);
                        if(ctnflag) /*֮ǰ�������У����������������*/
                            if(digitkeyhit==TRUE) /*��1+2+�����*/
                                 DoubleRun(); /*�ȼ����1+2*/
                            else
                                 ;
                        else /*֮ǰ�������У�û�������������,��:1+�����*/
                            if(operatoror==0)
                                 num2=num1;
                            else
                                 ;
                        Resetbuf();
                        operatoror=key;
                        ctnflag=TRUE;
                        runflag=TRUE;
                        break;
                    case 17:case 18:case 19:   /*������ ����,�ٷֱ�,����*/
                        if(digitkeyhit)
                            num1=atof(strbuf); /*num1���浱ǰ������*/

                        SingleRun(key);
                        Resetbuf();
                        ctnflag=FALSE;
                        operatoror=0;
                        runflag=FALSE;
                        break;
                    case 20:    /*��ȡ�����������ڲ���*/
                        if(digitkeyhit) num1=atof(strbuf);
                        if(operatoror)
                            DoubleRun(); /*��һ��������,������num2��*/
                        else
                            num2=num1;
                        Resetbuf();
                        ctnflag=FALSE;
                        runflag=TRUE;
                        break;
                    case 21:case 22:case 23:case 24: /*ֵ�ı����һЩ����*/
                        if(digitkeyhit) num1=atof(strbuf);
                        StoreSet(key);
                        Resetbuf();
                        break;
                    case 25:    /*ɾ�����ֵ��������ֵ����һλ��(BackSpace��)*/
                        if(top>1)
                            if(strbuf[--top]=='.')
                                {  if(strbuf[1]=='0'&&strbuf[2]=='.')
                                         strbuf[--top]=0;
                                     else
                                         strbuf[top]=0;
                                     pointflag=FALSE;
                                }
                            else
                                strbuf[top]=0;
                        operatoror=0;
                        ctnflag=FALSE;
                        runflag=FALSE;
                        strcpy(txtscreen.caption,strbuf);
                        break;
                    case 26:   /*�����ǰ��ʾ��ֵ(Del��)*/
                        Resetbuf();
                        num1=0;
                        strcpy(txtscreen.caption,strbuf);
                        TextBox(txtscreen);
                        break;
                    case 27:   /*������е�ֵ,�����洢��,�Ѿ������˵�(ESC����*/
                        Resetbuf();
                        num1=num2=0;
                        ctnflag=FALSE;
                        operatoror=0;
                        runflag=FALSE;
                        errorflag=FALSE;

                        strcpy(txtscreen.caption,"0.");
                        TextBox(txtscreen);

                        break;
                    case 0:
                        Unload();
                        break;
             }
         if(errorflag==FALSE)
             {  if(atof(txtscreen.caption)==0)
                        strcpy(txtscreen.caption,"0");
                    if(strchr(txtscreen.caption,'.')==NULL)
                        strcat(txtscreen.caption,".");
             }
         TextBox(txtscreen); /*��ʾtxtscreen�ṹ������ֵ*/
    }

void DoubleRun() /*��������*/
    {  switch(operatoror)
             {      case 13: num2+=num1;break;  /*��*/
                    case 14: num2-=num1;break; /*��*/
                    case 15: num2*=num1;break; /*��*/
                    case 16: if(num1==0)     /*��*/
                                         errorflag=TRUE;
                                     else
                                         num2/=num1;
                                     break;
             }
         if(errorflag)
             strcpy(txtscreen.caption,"Can't divide by zero!");
         else
             sprintf(txtscreen.caption,"%G",num2);
    }

void SingleRun(int key) /*������*/
    {  switch(key)
             {  case 17:  /*�󿪷�*/
                        if(num1<0)
                             errorflag=TRUE;
                        else
                             num1=sqrt(num1);
                        break;
                    case 18:  /*��ٷֱ�*/
                             num1/=100;
                        break;
                    case 19: /*����*/
                        if(num1==0)
                             errorflag=TRUE;
                        else
                             num1=1/num1;
                        break;
                }
         if(errorflag==TRUE)
             if(num1<0)
                 strcpy(txtscreen.caption,"Can't blower than zero!");
             else
                 strcpy(txtscreen.caption,"Can't equal to zero!");
         else
             sprintf(txtscreen.caption,"%G",num1);
    }

void StoreSet(int key)  /*����洢����*/
   {  switch(key)
             {  case 21:   /*�������*/
                        store=0;
                        lblstore.caption[0]=0;
                        break;
                case 22:  /*ȡ�������ֵ*/
                        num1=store;
                        sprintf(txtscreen.caption,"%G",store);
                        runflag=FALSE;
                        if(ctnflag==FALSE) operatoror=0;
                        break;
                case 23:  /*���浱ǰ����*/
                        store=num1;
                        strcpy(lblstore.caption,"M");
                        break;
               case 24:  /*����ֵ�뵱ǰ�������*/
                        store+=num1;
                        strcpy(lblstore.caption,"M");
                        break;
            }
         Label(lblstore);
    }


