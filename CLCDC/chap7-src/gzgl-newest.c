#include "stdio.h"   /*标准输入输出函数库*/
#include "stdlib.h"  /*标准函数库*/
#include "string.h"  /*字符串函数库*/
#include "conio.h"   /*屏幕操作函数库*/
#define HEADER1 " -------------------------------ZGGZ---------------------------------------- \n"
#define HEADER2 "|  number|    name   |  jbgz  |   jj   |   kk   |   yfgz |   sk   |  sfgz  | \n"
#define HEADER3 "|--------|-----------|--------|--------|--------|--------|--------|--------| \n"
#define FORMAT  "|%-8s|%-10s |%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f| \n"
#define DATA      p->num,p->name,p->jbgz,p->jj,p->kk,p->yfgz,p->sk,p->sfgz
#define END     "---------------------------------------------------------------------------- \n"
#define N 60
int saveflag=0;  /*是否需要存盘的标志变量*/
/*定义与职工有关的数据结构*/
typedef struct employee      /*标记为employee*/
{
char num[10];   /*职工编号*/
char name[15];  /*职工姓名*/
float jbgz;     /*基本工资*/
float jj;       /*奖金*/
float kk;       /*扣款*/
float yfgz;     /*应发工资*/
float sk;       /*税款*/
float sfgz;     /*实发工资*/
}ZGGZ;

void menu()  /*主菜单*/
{
system("cls");   /*调用DOS命令，清屏.与clrscr()功能相同*/
textcolor(10);   /*在文本模式中选择新的字符颜色*/
gotoxy(10,5);    /*在文本窗口中设置光标*/
cprintf("                 The Employee' Salary Management System \n");
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
void printdata(ZGGZ pp) /*格式化输出表中数据*/
{
 ZGGZ* p;
 p=&pp;
 printf(FORMAT,DATA);

}

void Disp(ZGGZ tp[],int n)  /*显示数组tp[]中存储的记录，内容为employee结构中定义的内容*/
{
int i;
if(n==0)  /*表示没有职工工资记录*/
{
  printf("\n=====>Not employee record!\n");
  getchar();
  return;
}

printf("\n\n");
printheader(); /*输出表格头部*/
i=0;
while(i<n)    /*逐条输出数组中存储的职工信息*/
{
  printdata(tp[i]);
  i++;
  printf(HEADER3);
}
getchar();
}

void Wrong()  /*输出按键错误信息*/
{
printf("\n\n\n\n\n***********Error:input has wrong! press any key to continue**********\n");
getchar();
}

void Nofind()  /*输出未查找此职工的信息*/
{
printf("\n=====>Not find this employee record!\n");
}

/*************************************************************
作用：用于定位数组中符合要求的记录，并返回保存该记录的数组元素下标值
参数：findmess[]保存要查找的具体内容; nameornum[]保存按什么在数组中查找;
**************************************************************/
int Locate(ZGGZ tp[],int n,char findmess[],char nameornum[])
{
int i=0;
if(strcmp(nameornum,"num")==0) /*按职工编号查询*/
{
  while(i<n)
   {
   if(strcmp(tp[i].num,findmess)==0) /*若找到findmess值的职工编号*/
    return i;
    i++;
    }
}
else if(strcmp(nameornum,"name")==0)  /*按职工姓名查询*/
{
  while(i<n)
   {
   if(strcmp(tp[i].name,findmess)==0) /*若找到findmess值的姓名*/
    return i;
    i++;
    }
}
return -1; /*若未找到，返回一个整数-1*/
}


/*输入字符串，并进行长度验证(长度<lens)*/
void stringinput(char *t,int lens,char *notice)
{
   char n[255];
   do{
      printf(notice);  /*显示提示信息*/
      scanf("%s",n);  /*输入字符串*/
      if(strlen(n)>lens) printf("\n exceed the required length! \n"); /*进行长度校验，超过lens值重新输入*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/

}

/*输入数值，0<＝数值)*/
float numberinput(char *notice)
{
  float t=0.00;
   do{
      printf(notice);    /*显示提示信息*/
      scanf("%f",&t);  /*输入如工资等数值型的值*/
      if(t<0) printf("\n score must >=0! \n"); /*进行数值校验*/
   }while(t<0);
   return t;
}


 /*增加职工工资记录*/
int Add(ZGGZ tp[],int n)
{
 char ch,num[10];
 int i,flag=0;
 system("cls");
 Disp(tp,n); /*先打印出已有的职工工资信息*/

 while(1) /*一次可输入多条记录，直至输入职工编号为0的记录才结束添加操作*/
 {
  while(1) /*输入职工编号，保证该编号没有被使用，若输入编号为0，则退出添加记录操作*/
  {
    stringinput(num,10,"input number(press '0'return menu):"); /*格式化输入编号并检验*/
    flag=0;
    if(strcmp(num,"0")==0) /*输入为0，则退出添加操作，返回主界面*/
      {return n;}
     i=0;
    while(i<n) /*查询该编号是否已经存在，若存在则要求重新输入一个未被占用的编号*/
    {
      if(strcmp(tp[i].num,num)==0)
      {
       flag=1;
       break;
       }
      i++;
    }

  if(flag==1) /*提示用户是否重新输入*/
     {  getchar();
        printf("==>The number %s is existing,try again?(y/n):",num);
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
         continue;
        else
          return n;
      }
  else
      {break;}
  }
  strcpy(tp[n].num,num); /*将字符串num拷贝到tp[n].num中*/
  stringinput(tp[n].name,15,"Name:");
  tp[n].jbgz=numberinput("jbgz:"); /*输入并检验基本工资*/
  tp[n].jj=numberinput("jiangjin:");         /*输入并检验奖金*/
  tp[n].kk=numberinput("koukuan:");      /*输入并检验扣款*/
  tp[n].yfgz=tp[n].jbgz+tp[n].jj-tp[n].kk;      /*计算应发工资*/
  tp[n].sk=tp[n].yfgz*0.12;  /*计算税金，这里取应发工资的百分之一十二*/
  tp[n].sfgz=tp[n].yfgz-tp[n].sk; /*计算实发工资*/
  saveflag=1;
  n++;
  }
     return n;
}

/*按职工编号或姓名，查询记录*/
void Qur(ZGGZ tp[],int n)
{
int select; /*1:按编号查，2：按姓名查，其他：返回主界面（菜单）*/
char searchinput[20]; /*保存用户输入的查询内容*/
int p=0;
if(n<=0) /*若数组为空*/
{
  system("cls");
  printf("\n=====>No employee record!\n");
  getchar();
  return;
}
system("cls");
printf("\n     =====>1 Search by number  =====>2 Search by name\n");
printf("      please choice[1,2]:");
scanf("%d",&select);
if(select==1)   /*按编号查询*/
 {

  stringinput(searchinput,10,"input the existing employee number:");
  p=Locate(tp,n,searchinput,"num");/*在数组tp中查找编号为searchinput值的元素，并返回该数组元素的下标值*/
  if(p!=-1) /*若找到该记录*/
  {
   printheader();
   printdata(tp[p]);
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
  stringinput(searchinput,15,"input the existing employee name:");
  p=Locate(tp,n,searchinput,"name");
  if(p!=-1)
  {
   printheader();
   printdata(tp[p]);
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

/*删除记录：先找到保存该记录的数组元素的下标值，然后在数组中删除该数组元素*/
int Del(ZGGZ tp[],int n)
{
int sel;
char findmess[20];
int p=0,i=0;
if(n<=0)
{ system("cls");
  printf("\n=====>No employee record!\n");
  getchar();
  return n;
}
system("cls");
Disp(tp,n);
printf("\n    =====>1 Delete by number       =====>2 Delete by name\n");
printf("    please choice[1,2]:");
scanf("%d",&sel);
if(sel==1)
{
  stringinput(findmess,10,"input the existing employee number:");
  p=Locate(tp,n,findmess,"num");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++) /*删除此记录，后面记录向前移*/
   { 
    strcpy(tp[i-1].num,tp[i].num);
    strcpy(tp[i-1].name,tp[i].name);
    tp[i-1].jbgz=tp[i].jbgz;
    tp[i-1].jj=tp[i].jj;
    tp[i-1].kk=tp[i].kk;
    tp[i-1].yfgz=tp[i].yfgz;
    tp[i-1].jbgz=tp[i].sk;
    tp[i-1].sfgz=tp[i].sfgz;
    }
    printf("\n==>delete success!\n");
    n--;
    getchar();
    saveflag=1;
   }
  else
   Nofind();
   getchar();
 }
else if(sel==2) /*先按姓名查询到该记录所在的数组元素的下标值*/
{
  stringinput(findmess,15,"input the existing employee name:");
  p=Locate(tp,n,findmess,"name");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++)   /*删除此记录，后面记录向前移*/
   { 
    strcpy(tp[i-1].num,tp[i].num);
    strcpy(tp[i-1].name,tp[i].name);
    tp[i-1].jbgz=tp[i].jbgz;
    tp[i-1].jj=tp[i].jj;
    tp[i-1].kk=tp[i].kk;
    tp[i-1].yfgz=tp[i].yfgz;
    tp[i-1].jbgz=tp[i].sk;
    tp[i-1].sfgz=tp[i].sfgz;
    }
    printf("\n=====>delete success!\n");
    n--;
    getchar();
    saveflag=1;
  }
  else
   Nofind();
   getchar();
}
 return n;
}

/*修改记录。先按输入的职工编号查询到该记录，然后提示用户修改编号之外的值，编号不能修改*/
void Modify(ZGGZ tp[],int n)
{
char findmess[20];
int p=0;
if(n<=0)
{ system("cls");
  printf("\n=====>No employee record!\n");
  getchar();
  return ;
}
system("cls");
printf("modify employee recorder");
Disp(tp,n);
stringinput(findmess,10,"input the existing employee number:"); /*输入并检验该编号*/
p=Locate(tp,n,findmess,"num"); /*查询到该数组元素,并返回下标值*/
if(p!=-1) /*若p!=－1,表明已经找到该数组元素*/
{
   printf("Number:%s,\n",tp[p].num);
   printf("Name:%s,",tp[p].name);
   stringinput(tp[p].name,15,"input new name:");

   printf("jbgz:%8.2f,",tp[p].jbgz);
   tp[p].jbgz=numberinput("jbgz:");

   printf("jiangjin:%8.2f,",tp[p].jj);
   tp[p].jj=numberinput("jiangjin:");

   printf("koukuan:%8.2f,",tp[p].kk);
   tp[p].kk=numberinput("koukuan:");

   tp[n].yfgz=tp[n].jbgz+tp[n].jj-tp[n].kk;
   tp[n].sk=tp[n].yfgz*0.12;
   tp[n].sfgz=tp[n].yfgz-tp[n].sk;
   printf("\n=====>modify success!\n");
   getchar();
   Disp(tp,n);
   getchar();
   saveflag=1;
}
else
  {Nofind();
   getchar();
  }
return ;
}

/*插入记录:按职工编号查询到要插入的数组元素的位置，然后在该编号之后插入一个新数组元素。*/
int Insert(ZGGZ tp[],int n)
{
   char ch,num[10],s[10];  /*s[]保存插入点位置之前的编号,num[]保存输入的新记录的编号*/
   ZGGZ newinfo;
   int flag=0,i=0,kkk=0;
   system("cls");
   Disp(tp,n);
   while(1)
   { stringinput(s,10,"please input insert location  after the Number:");
     flag=0;i=0;
     while(i<n) /*查询该编号是否存在，flag=1表示该编号存在*/
     {
      if(strcmp(tp[i].num,s)==0)  {kkk=i;flag=1;break;}
      i++;
     }
      if(flag==1)
        break; /*若编号存在，则进行插入之前的新记录输入操作*/
     else
     {  getchar();
        printf("\n=====>The number %s is not existing,try again?(y/n):",s);
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
         {continue;}
        else
          {return n;}
      }
   }
  /*以下新记录的输入操作与Add()相同*/

  while(1)
  { stringinput(num,10,"input new employee Number:");
    i=0;flag=0;
    while(i<n) /*查询该编号是否存在，flag=1表示该编号存在*/
     {
      if(strcmp(tp[i].num,num)==0)  {flag=1;break;}
      i++;
     }
       if(flag==1)
      {
       getchar();
       printf("\n=====>Sorry,The number %s is  existing,try again?(y/n):",num);
       scanf("%c",&ch);
       if(ch=='y'||ch=='Y')
       {continue;}
       else
       {return n;}
      }
      else
       break;
  }
  
  strcpy(newinfo.num,num); /*将字符串num拷贝到newinfo.num中*/
  stringinput(newinfo.name,15,"Name:");
  newinfo.jbgz=numberinput("jbgz:"); /*输入并检验jbgz*/
  newinfo.jj=numberinput("jiangjin:");         /*输入并检验jiangjin*/
  newinfo.kk=numberinput("koukuan:");      /*输入并检验koukuan*/
  newinfo.yfgz=newinfo.jbgz+newinfo.jj-newinfo.kk;      /*计算yfgz*/
  newinfo.sk=newinfo.yfgz*0.12;  /*计算sk*/
  newinfo.sfgz=newinfo.yfgz-newinfo.sk;
  saveflag=1; /*在main()有对该全局变量的判断，若为1,则进行存盘操作*/

 for(i=n-1;i>kkk;i--) /*从最后一个组织元素开始往向移一个元素位置*/
 { strcpy(tp[i+1].num,tp[i].num);
   strcpy(tp[i+1].name,tp[i].name);
   tp[i+1].jbgz=tp[i].jbgz;
   tp[i+1].jj=tp[i].jj;
   tp[i+1].kk=tp[i].kk;
   tp[i+1].yfgz=tp[i].yfgz;
   tp[i+1].sk=tp[i].sk;
   tp[i+1].sfgz=tp[i].sfgz;
 }
   strcpy(tp[kkk+1].num,newinfo.num);  /*在kkk的元素位置后插入新记录*/
   strcpy(tp[kkk+1].name,newinfo.name);
   tp[kkk+1].jbgz=newinfo.jbgz;
   tp[kkk+1].jj=newinfo.jj;
   tp[kkk+1].kk=newinfo.kk;
   tp[kkk+1].yfgz=newinfo.yfgz;
   tp[kkk+1].sk=newinfo.sk;
   tp[kkk+1].sfgz=newinfo.sfgz;
   n++;
   Disp(tp,n);
   printf("\n\n");
   getchar();
   return n;
}

/*统计公司的员工的工资在各等级的人数*/
void Tongji(ZGGZ tp[],int n)
{
int count10000=0,count5000=0,count2000=0,count0=0;
int i=0;
if(n<=0)
{ system("cls");
  printf("\n=====>Not employee record!\n");
  getchar();
  return ;
}
system("cls");
Disp(tp,n);
i=0;
while(i<n)
{
  if(tp[i].sfgz>=10000) {count10000++;i=i+1;continue;}  /*实发工资>10000*/
  if(tp[i].sfgz>=5000)  {count5000++;i=i+1;continue;}    /*5000<=实发工资<10000*/
  if(tp[i].sfgz>=2000)  {count2000++;i=i+1;continue;}    /*2000<=实发工资<5000*/
  if(tp[i].sfgz<2000)   {count0++;i=i+1;continue;}      /*实发工资<2000*/

}
printf("\n------------------------------the TongJi result--------------------------------\n");
printf("sfgz>=     10000:%d (ren)\n",count10000);
printf("5000<=sfgz<10000:%d (ren)\n",count5000);
printf("2000<=sfgz< 5000:%d (ren)\n",count2000);
printf("sfgz<       2000:%d (ren)\n",count0);
printf("-------------------------------------------------------------------------------\n");
printf("\n\npress any key to return");
getchar();
}

/*利用冒泡排序法实现数组的按实发工资字段的降序排序，从高到低*/
void Sort(ZGGZ tp[],int n)
{
int i=0,j=0,flag=0;
ZGGZ newinfo;
if(n<=0)
{ system("cls");
  printf("\n=====>Not employee record!\n");
  getchar();
  return ;
}
system("cls");
Disp(tp,n);  /*显示排序前的所有记录*/
for(i=0;i<n;i++)
{
  flag=0;
  for(j=0;j<n-1;j++)
   if((tp[j].sfgz<tp[j+1].sfgz))
    { flag=1;
      strcpy(newinfo.num,tp[j].num);  /*利用结构变量newinfo实现数组元素的交换*/
      strcpy(newinfo.name,tp[j].name);
      newinfo.jbgz=tp[j].jbgz;
      newinfo.jj=tp[j].jj;
      newinfo.kk=tp[j].kk;
      newinfo.yfgz=tp[j].yfgz;
      newinfo.sk=tp[j].sk;
      newinfo.sfgz=tp[j].sfgz;

      strcpy(tp[j].num,tp[j+1].num);
      strcpy(tp[j].name,tp[j+1].name);
      tp[j].jbgz=tp[j+1].jbgz;
      tp[j].jj=tp[j+1].jj;
      tp[j].kk=tp[j+1].kk;
      tp[j].yfgz=tp[j+1].yfgz;
      tp[j].sk=tp[j+1].sk;
      tp[j].sfgz=tp[j+1].sfgz;

      strcpy(tp[j+1].num,newinfo.num);
      strcpy(tp[j+1].name,newinfo.name);
      tp[j+1].jbgz=newinfo.jbgz;
      tp[j+1].jj=newinfo.jj;
      tp[j+1].kk=newinfo.kk;
      tp[j+1].yfgz=newinfo.yfgz;
      tp[j+1].sk=newinfo.sk;
      tp[j+1].sfgz=newinfo.sfgz;
     }
     if(flag==0) break;/*若标记flag=0，意味着没有交换了，排序已经完成*/
    }
      Disp(tp,n);  /*显示排序后的所有记录*/
      saveflag=1;
      printf("\n    =====>sort complete!\n");

}




/*数据存盘,若用户没有专门进行此操作且对数据有修改，在退出系统时， 会提示用户存盘*/
void Save(ZGGZ tp[],int n)
{
FILE* fp;
int i=0;
fp=fopen("c:\\zggz","wb");/*以只写方式打开二进制文件*/
if(fp==NULL) /*打开文件失败*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
for(i=0;i<n;i++)
{
  if(fwrite(&tp[i],sizeof(ZGGZ),1,fp)==1)/*每次写一条记录或一个结构数组元素至文件*/
  { 
   continue;
  }
  else
  {
   break;
  }
}
if(i>0)
{
  getchar();
  printf("\n\n=====>save file complete,total saved's record number is:%d\n",i);
  getchar();
  saveflag=0;
}
else
{system("cls");
 printf("the current link is empty,no employee record is saved!\n");
 getchar();
 }
fclose(fp); /*关闭此文件*/
}


void main()
{
  ZGGZ gz[N];         /*定义ZGGZ结构体*/
  FILE *fp;           /*文件指针*/
  int select;         /*保存选择结果变量*/
  char ch;            /*保存(y,Y,n,N)*/
  int count=0;        /*保存文件中的记录条数（或元素个数）*/
   
  fp=fopen("C:\\zggz","ab+");
  /*以追加方式打开二进制文件c:\zggz，可读可写，若此文件不存在，会创建此文件*/
  if(fp==NULL)
  {
    printf("\n=====>can not open file!\n");
    exit(0);
  }

while(!feof(fp))
{
   if(fread(&gz[count],sizeof(ZGGZ),1,fp)==1) /*一次从文件中读取一条职工工资记录*/
      count++;
}
fclose(fp); /*关闭文件*/
printf("\n==>open file sucess,the total records number is : %d.\n",count);
getchar();
menu();
while(1)
{
   system("cls");
   menu();
   printf("\n              Please Enter your choice(0~9):");    /*显示提示信息*/
   scanf("%d",&select);

  if(select==0)
  {
   if(saveflag==1) /*若对数组的数据有修改且未进行存盘操作，则此标志为1*/
   { getchar();
     printf("\n==>Whether save the modified record to file?(y/n):");
     scanf("%c",&ch);
     if(ch=='y'||ch=='Y')
       Save(gz,count);
   }
   printf("\n===>thank you for useness!");
   getchar();
   break;
  }

  switch(select)
  {
  case 1:count=Add(gz,count);break;       /*增加职工工资记录*/
  case 2:count=Del(gz,count);break;      /*删除职工工资记录*/
  case 3:Qur(gz,count);break;           /*查询职工工资记录*/
  case 4:Modify(gz,count);break;        /*修改职工工资记录*/
  case 5:count=Insert(gz,count);break;  /*插入职工工资记录*/
  case 6:Tongji(gz,count);break;       /*统计职工工资记录*/
  case 7:Sort(gz,count);break;        /*排序职工工资记录*/
  case 8:Save(gz,count);break;        /*保存职工工资记录*/
  case 9:system("cls");Disp(gz,count);break;         /*显示职工工资记录*/
  default: Wrong();getchar();break;        /*按键有误，必须为数值0-9*/
  }
 }
}
