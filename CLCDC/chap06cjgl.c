#include "stdio.h"   /*标准输入输出函数库*/
#include "stdlib.h"  /*标准函数库*/
#include "string.h"  /*字符串函数库*/
#include "conio.h"    /*屏幕操作函数库*/
#define HEADER1 "      ----------------------------STUDENT----------------------------------  \n"
#define HEADER2 "     |    number     |      name     |Comp|Math|Eng |   sum  |  ave  |mici | \n"
#define HEADER3 "     |---------------|---------------|----|----|----|--------|-------|-----| "
#define FORMAT  "        |    %-10s |%-15s|%4d|%4d|%4d| %4d   | %.2f |%4d |\n"
#define DATA  p->data.num,p->data.name,p->data.egrade,p->data.mgrade,p->data.cgrade,p->data.total,p->data.ave,p->data.mingci
#define END     "       --------------------------------------------------------------------- \n"

int saveflag=0;  /*是否需要存盘的标志变量*/
/*定义与学生有关的数据结构*/
typedef struct student      /*标记为student*/
{
char num[10];   /*学号*/
char name[15];  /*姓名*/
int cgrade;     /*C语言成绩*/
int mgrade;     /*数学成绩*/
int egrade;     /*英语成绩*/
int total;      /*总分*/
float ave;      /*平均分*/
int mingci;     /*名次*/
};

/*定义每条记录或结点的数据结构，标记为：node*/
typedef struct node
{
struct student data;  /*数据域*/
struct node *next;    /*指针域*/
}Node,*Link;   /*Node为node类型的结构变量，*Link为node类型的指针变量*/


void menu()  /*主菜单*/
{
system("cls");   /*调用DOS命令，清屏.与clrscr()功能相同*/
textcolor(10);   /*在文本模式中选择新的字符颜色*/
gotoxy(10,5);     /*在文本窗口中设置光标*/
cprintf("                 The Students' Grade Management System \n");
gotoxy(10,8);
cprintf("     *************************Menu********************************\n");
gotoxy(10,9);
cprintf("     *  1 input   record             2 delete record             *\n");
gotoxy(10,10);
cprintf("     *  3 search  record             4 modify record             *\n");
gotoxy(10,11);
cprintf("     *  5 insert  record             6 count  record             *\n");
gotoxy(10,12);
cprintf("     *  7 sort    reord              8 save   record             *\n");
gotoxy(10,13);
cprintf("     *  9 display record             0 quit   system             *\n");
gotoxy(10,14);
cprintf("     *************************************************************\n");
/*cprintf()送格式化输出至文本窗口屏幕中*/
}
void printheader() /*格式化输出表头*/
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
void printdata(Node *pp) /*格式化输出表中数据*/
{
 Node* p;
 p=pp;
 printf(FORMAT,DATA);

}

void Wrong()  /*输出按键错误信息*/
{
printf("\n\n\n\n\n***********Error:input has wrong! press any key to continue**********\n");
getchar();
}

void Nofind()  /*输出未查找此学生的信息*/
{
printf("\n=====>Not find this student!\n");
}

void Disp(Link l)  /*显示单链表l中存储的学生记录，内容为student结构中定义的内容*/
{
Node *p;
p=l->next; /*l存储的是单链表中头结点的指针，该头结点没有存储学生信息，指针域指向的后继结点才有学生信息*/

if(!p)  /*p==NULL,NUll在stdlib中定义为0*/
{
  printf("\n=====>Not student record!\n");
  getchar();
  return;
}

printf("\n\n");
printheader(); /*输出表格头部*/

while(p)    /*逐条输出链表中存储的学生信息*/
{
  printdata(p);
  p=p->next;  /*移动直下一个结点*/
  printf(HEADER3);
}
getchar();
}

/*************************************************************
作用：用于定位链表中符合要求的节点，并返回指向该节点的指针
参数：findmess[]保存要查找的具体内容; nameornum[]保存按什么查找;
      在单链表l中查找;
**************************************************************/
Node* Locate(Link l,char findmess[],char nameornum[])
{
Node *r;
if(strcmp(nameornum,"num")==0) /*按学号查询*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.num,findmess)==0) /*若找到findmess值的学号*/
    return r;
   r=r->next;
  }
}
else if(strcmp(nameornum,"name")==0)  /*按姓名查询*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.name,findmess)==0)    /*若找到findmess值的学生姓名*/
    return r;
   r=r->next;
  }
}
return 0; /*若未找到，返回一个空指针*/
}


/*输入字符串，并进行长度验证(长度<lens)*/
void stringinput(char *t,int lens,char *notice)
{
   char n[255];
   do{
      printf(notice);  /*显示提示信息*/
      scanf("%s",n);  /*输入字符串*/
      if(strlen(n)>lens)printf("\n exceed the required length! \n"); /*进行长度校验，超过lens值重新输入*/
     }while(strlen(n)>lens);
   strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/
}

/*输入分数，0<＝分数<＝100)*/
int numberinput(char *notice)
{
  int t=0;
   do{
      printf(notice);  /*显示提示信息*/
      scanf("%d",&t);  /*输入分数*/
      if(t>100 || t<0) printf("\n score must in [0,100]! \n"); /*进行分数校验*/
   }while(t>100 || t<0);
   return t;
}


 /*增加学生记录*/
void Add(Link l)
{
Node *p,*r,*s;  /*实现添加操作的临时的结构体指针变量*/
char ch,flag=0,num[10];
r=l;
s=l->next;
system("cls");
Disp(l); /*先打印出已有的学生信息*/
while(r->next!=NULL)
  r=r->next; /*将指针移至于链表最末尾，准备添加记录*/
while(1) /*一次可输入多条记录，直至输入学号为0的记录结点添加操作*/
{
 while(1) /*输入学号，保证该学号没有被使用，若输入学号为0，则退出添加记录操作*/
{

  stringinput(num,10,"input number(press '0'return menu):"); /*格式化输入学号并检验*/
  flag=0;

  if(strcmp(num,"0")==0) /*输入为0，则退出添加操作，返回主界面*/
      {return;}
  s=l->next;
    while(s) /*查询该学号是否已经存在，若存在则要求重新输入一个未被占用的学号*/
    {
      if(strcmp(s->data.num,num)==0)
      {
       flag=1;
       break;
       }
     s=s->next;
    }

  if(flag==1) /*提示用户是否重新输入*/

     {  getchar();
        printf("=====>The number %s is not existing,try again?(y/n):",num);
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
         continue;
        else
          return;
      }
     else
      {break;}
  }
  
  p=(Node *)malloc(sizeof(Node)); /*申请内存空间*/
  if(!p)
   {
      printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
      return ;             /*返回主界面*/
   }
  strcpy(p->data.num,num); /*将字符串num拷贝到p->data.num中*/
  stringinput(p->data.name,15,"Name:");
  p->data.cgrade=numberinput("C language Score[0-100]:"); /*输入并检验分数，分数必须在0－100之间*/
  p->data.mgrade=numberinput("Math Score[0-100]:");   /*输入并检验分数，分数必须在0－100之间*/
  p->data.egrade=numberinput("English Score[0-100]:"); /*输入并检验分数，分数必须在0－100之间*/
  p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade; /*计算总分*/
  p->data.ave=(float)(p->data.total/3);  /*计算平均分*/
  p->data.mingci=0;
  p->next=NULL; /*表明这是链表的尾部结点*/
  r->next=p;  /*将新建的结点加入链表尾部中*/
  r=p;
  saveflag=1;

  }
     return ;
}

void Qur(Link l) /*按学号或姓名，查询学生记录*/
{
int select; /*1:按学号查，2：按姓名查，其他：返回主界面（菜单）*/
char searchinput[20]; /*保存用户输入的查询内容*/
Node *p;
if(!l->next) /*若链表为空*/
{
  system("cls");
  printf("\n=====>No student record!\n");
  getchar();
  return;

}
system("cls");
printf("\n     =====>1 Search by number  =====>2 Search by name\n");
printf("      please choice[1,2]:");
scanf("%d",&select);
if(select==1)   /*按学号查询*/
 {

  stringinput(searchinput,10,"input the existing student number:");
  p=Locate(l,searchinput,"num");/*在l中查找学号为searchinput值的节点，并返回节点的指针*/
  if(p) /*若p!=NULL*/
  {
   printheader();
   printdata(p);
   printf(END);
   printf("press any key to return");
   getchar();
  }
  else
   Nofind();
   getchar();
}
else if(select==2) /*按姓名查询*/
{
  stringinput(searchinput,15,"input the existing student name:");
  p=Locate(l,searchinput,"name");
  if(p)
  {
   printheader();
   printdata(p);
   printf(END);
   printf("press any key to return");
   getchar();
  }
  else
   Nofind();
   getchar();
}
else
  Wrong();
  getchar();
  
}

/*删除学生记录：先找到保存该学生记录的节点，然后删除该节点*/
void Del(Link l)
{
int sel;
Node *p,*r;
char findmess[20];
if(!l->next)
{ system("cls");
  printf("\n=====>No student record!\n");
  getchar();
  return;
}
system("cls");
Disp(l);
printf("\n        =====>1 Delete by number       =====>2 Delete by name\n");
printf("       please choice[1,2]:");
scanf("%d",&sel);
if(sel==1)
{

  stringinput(findmess,10,"input the existing student number:");
  p=Locate(l,findmess,"num");
  if(p)  /*p!=NULL*/
  {
   r=l;
   while(r->next!=p)
    r=r->next;
   r->next=p->next;/*将p所指节点从链表中去除*/
   free(p); /*释放内存空间*/
   printf("\n=====>delete success!\n");
   getchar();
   saveflag=1;
  }
  else
   Nofind();
   getchar();
}
else if(sel==2) /*先按姓名查询到该记录所在的节点*/
{
  stringinput(findmess,15,"input the existing student name");
  p=Locate(l,findmess,"name");
  if(p)
  {
   r=l;
   while(r->next!=p)
    r=r->next;
   r->next=p->next;
   free(p);
   printf("\n=====>delete success!\n");
   getchar();
   saveflag=1;
  }
  else
   Nofind();
   getchar();
}
else
  Wrong();
  getchar();
}

/*修改学生记录。先按输入的学号查询到该记录，然后提示用户修改学号之外的值，学号不能修改*/
void Modify(Link l)
{
Node *p;
char findmess[20];
if(!l->next)
{ system("cls");
  printf("\n=====>No student record!\n");
  getchar();
  return;
}
system("cls");
printf("modify student recorder");
Disp(l);


stringinput(findmess,10,"input the existing student number:"); /*输入并检验该学号*/
p=Locate(l,findmess,"num"); /*查询到该节点*/
if(p) /*若p!=NULL,表明已经找到该节点*/
{
  printf("Number:%s,\n",p->data.num);
  printf("Name:%s,",p->data.name);
  stringinput(p->data.name,15,"input new name:");

  printf("C language score:%d,",p->data.cgrade);
  p->data.cgrade=numberinput("C language Score[0-100]:");

  printf("Math score:%d,",p->data.mgrade);
  p->data.mgrade=numberinput("Math Score[0-100]:");


  printf("English score:%d,",p->data.egrade);
   p->data.egrade=numberinput("English Score[0-100]:");

  p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade;
  p->data.ave=(float)(p->data.total/3);
  p->data.mingci=0;
  printf("\n=====>modify success!\n");
  Disp(l);
  saveflag=1;
}
else
  Nofind();
  getchar();

}



/*插入记录:按学号查询到要插入的节点的位置，然后在该学号之后插入一个新节点。*/
void Insert(Link l)
{
   Link p,v,newinfo; /*p指向插入位置，newinfo指新插入记录*/
   char ch,num[10],s[10];  /*s[]保存插入点位置之前的学号,num[]保存输入的新记录的学号*/
   int flag=0;
   v=l->next;
   system("cls");
   Disp(l);
   while(1)
   { stringinput(s,10,"please input insert location  after the Number:");
     flag=0;v=l->next;
     while(v) /*查询该学号是否存在，flag=1表示该学号存在*/
     {
      if(strcmp(v->data.num,s)==0)  {flag=1;break;}
          v=v->next;
     }
      if(flag==1)
        break; /*若学号存在，则进行插入之前的新记录的输入操作*/
     else
     {  getchar();
        printf("\n=====>The number %s is not existing,try again?(y/n):",s);
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
         {continue;}
        else
          {return;}
      }
   }
  /*以下新记录的输入操作与Add()相同*/
  stringinput(num,10,"input new student Number:");
  v=l->next;
  while(v)
  {
   if(strcmp(v->data.num,num)==0)
   {
    printf("=====>Sorry,the new number:'%s' is existing !\n",num);
    printheader();
    printdata(v);
    printf("\n");
    getchar();
    return;
   }
   v=v->next;
  }
  

  newinfo=(Node *)malloc(sizeof(Node));
  if(!newinfo)
   {
      printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
      return ;             /*返回主界面*/
   }
  strcpy(newinfo->data.num,num);
  stringinput(newinfo->data.name,15,"Name:");
  newinfo->data.cgrade=numberinput("C language Score[0-100]:");
  newinfo->data.mgrade=numberinput("Math Score[0-100]:");
  newinfo->data.egrade=numberinput("English Score[0-100]:");
  newinfo->data.total=newinfo->data.egrade+newinfo->data.cgrade+newinfo->data.mgrade;
  newinfo->data.ave=(float)(newinfo->data.total/3);
  newinfo->data.mingci=0;
  newinfo->next=NULL;
  saveflag=1; /*在main()有对该全局变量的判断，若为1,则进行存盘操作*/
  /*将指针赋值给p,因为l中的头节点的下一个节点才实际保存着学生的记录*/
  p=l->next;
  while(1)
   {
     if(strcmp(p->data.num,s)==0) /*在链表中插入一个节点*/
      {
        newinfo->next=p->next;
        p->next=newinfo;
        break;
       }
      p=p->next;
    }

   Disp(l);
   printf("\n\n");
   getchar();

}

/*统计该班的总分第一名和单科第一,和各科不及格人数*/
void Tongji(Link l)
{
Node *pm,*pe,*pc,*pt; /*用于指向分数最高的节点*/
Node *r=l->next;
int countc=0,countm=0,counte=0; /*保存三门成绩中不及格的人数*/
if(!r)
{ system("cls");
  printf("\n=====>Not student record!\n");
  getchar();
  return ;
}
system("cls");
Disp(l);
pm=pe=pc=pt=r;
while(r)
{
  if(r->data.cgrade<60) countc++;
  if(r->data.mgrade<60) countm++;
  if(r->data.egrade<60) counte++;

  if(r->data.cgrade>=pc->data.cgrade)    pc=r;
  if(r->data.mgrade>=pm->data.mgrade)    pm=r;
  if(r->data.egrade>=pe->data.egrade)    pe=r;
  if(r->data.total>=pt->data.total)      pt=r;
  r=r->next;
}
printf("\n------------------------------the TongJi result--------------------------------\n");
printf("C Language<60:%d (ren)\n",countc);
printf("Math      <60:%d (ren)\n",countm);
printf("English   <60:%d (ren)\n",counte);
printf("-------------------------------------------------------------------------------\n");
printf("The highest student by total   scroe   name:%s totoal score:%d\n",pt->data.name,pt->data.total);
printf("The highest student by English score   name:%s totoal score:%d\n",pe->data.name,pe->data.egrade);
printf("The highest student by Math    score   name:%s totoal score:%d\n",pm->data.name,pm->data.mgrade);
printf("The highest student by C       score   name:%s totoal score:%d\n",pc->data.name,pc->data.cgrade);
printf("\n\npress any key to return");
getchar();
}
/*利用插入排序法实现单链表的按总分字段的降序排序，从高到低*/
void Sort(Link l)
{
Link ll;
Node *p,*rr,*s;
int i=0;
if(l->next==NULL)
{ system("cls");
  printf("\n=====>Not student record!\n");
  getchar();
  return ;
}

ll=(Node*)malloc(sizeof(Node)); /*用于创建新的节点*/
if(!ll)
   {
      printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
      return ;             /*返回主界面*/
   }
ll->next=NULL;
system("cls");
Disp(l);  /*显示排序前的所有学生记录*/
p=l->next;
while(p) /*p!=NULL*/
{
  s=(Node*)malloc(sizeof(Node)); /*新建节点用于保存从原链表中取出的节点信息*/
  if(!s) /*s==NULL*/
   {
      printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
      return ;             /*返回主界面*/
   }
  s->data=p->data; /*填数据域*/
  s->next=NULL;    /*指针域为空*/
  rr=ll;
  /*rr链表于存储插入单个节点后保持排序的链表，ll是这个链表的头指针,每次从头开始查找插入位置*/

  while(rr->next!=NULL && rr->next->data.total>=p->data.total)
   {rr=rr->next;} /*指针移至总分比p所指的节点的总分小的节点位置*/
  if(rr->next==NULL)/*若新链表ll中的所有节点的总分值都比p->data.total大时，就将p所指节点加入链表尾部*/
     rr->next=s;
  else /*否则将该节点插入至第一个总分字段比它小的节点的前面*/
  {
   s->next=rr->next;
   rr->next=s;
  }
   p=p->next; /*原链表中的指针下移一个节点*/
 }

   l->next=ll->next; /*ll中存储是的已排序的链表的头指针*/
   p=l->next;           /*已排好序的头指针赋给p，准备填写名次*/
   while(p!=NULL)  /*当p不为空时，进行下列操作*/
   {
      i++;       /*结点序号*/
      p->data.mingci=i;   /*将名次赋值*/
      p=p->next;   /*指针后移*/

   }
Disp(l);
saveflag=1;
printf("\n    =====>sort complete!\n");

}

/*数据存盘,若用户没有专门进行此操作且对数据有修改，在退出系统时， 会提示用户存盘*/
void Save(Link l)
{
FILE* fp;
Node *p;
int count=0;
fp=fopen("c:\\student","wb");/*以只写方式打开二进制文件*/
if(fp==NULL) /*打开文件失败*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
p=l->next;

while(p)
{
  if(fwrite(p,sizeof(Node),1,fp)==1)/*每次写一条记录或一个节点信息至文件*/
  { 
   p=p->next;
   count++;
  }
  else
  {
   break;
  }
}
if(count>0)
{
  getchar();
  printf("\n\n\n\n\n=====>save file complete,total saved's record number is:%d\n",count);
  getchar();
  saveflag=0;
}
else
{system("cls");
 printf("the current link is empty,no student record is saved!\n");
 getchar();
 }
fclose(fp); /*关闭此文件*/
}

void main()
{

  Link l;      /*定义链表*/
  FILE *fp;    /*文件指针*/
  int select;     /*保存选择结果变量*/
  char ch;     /*保存(y,Y,n,N)*/
  int count=0; /*保存文件中的记录条数（或结点个数）*/
  Node *p,*r;   /*定义记录指针变量*/


  l=(Node*)malloc(sizeof(Node));
  if(!l)
   {
      printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
      return ;             /*返回主界面*/
   }
  l->next=NULL;
  r=l;
  fp=fopen("C:\\student","ab+"); /*以追加方式打开一个二进制文件，可读可写，若此文件不存在，会创建此文件*/
  if(fp==NULL)
  {
    printf("\n=====>can not open file!\n");
    exit(0);
  }

while(!feof(fp))
{
  p=(Node*)malloc(sizeof(Node));
  if(!p)
   {
      printf(" memory malloc failure!\n");    /*没有申请成功*/
      exit(0);       /*退出*/
   }

  if(fread(p,sizeof(Node),1,fp)==1) /*一次从文件中读取一条学生成绩记录*/
  {
   p->next=NULL;
   r->next=p;
   r=p;                            /*r指针向后移一个位置*/
   count++;
   }
}

fclose(fp); /*关闭文件*/
printf("\n=====>open file sucess,the total records number is : %d.\n",count);
menu();
while(1)
{
   system("cls");
   menu();
   p=r;
   printf("\n              Please Enter your choice(0~9):");    /*显示提示信息*/
   scanf("%d",&select);

  if(select==0)
  {
   if(saveflag==1) /*若对链表的数据有修改且未进行存盘操作，则此标志为1*/
   { getchar();
     printf("\n=====>Whether save the modified record to file?(y/n):");
     scanf("%c",&ch);
     if(ch=='y'||ch=='Y')
       Save(l);
   }
   printf("=====>thank you for useness!");
   getchar();
   break;
  }

  switch(select)
  {
  case 1:Add(l);break;            /*增加学生记录*/
  case 2:Del(l);break;           /*删除学生记录*/
  case 3:Qur(l);break;           /*查询学生记录*/
  case 4:Modify(l);break;        /*修改学生记录*/
  case 5:Insert(l);break;        /*插入学生记录*/
  case 6:Tongji(l);break;       /*统计学生记录*/
  case 7:Sort(l);break;        /*排序学生记录*/
  case 8:Save(l);break;        /*保存学生记录*/
  case 9:system("cls");Disp(l);break;         /*显示学生记录*/
  default: Wrong();getchar();break;        /*按键有误，必须为数值0-9*/
  }
}
}
