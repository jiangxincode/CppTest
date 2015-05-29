#include "stdio.h"   /*标准输入输出函数库*/
#include "stdlib.h"  /*标准函数库*/
#include "string.h"  /*字符串函数库*/
#include "conio.h"   /*屏幕操作函数库*/
#define HEADER1 "    ---------------------------TELEPHONE BOOK---------------------------\n"
#define HEADER2 "   |    num       |    name    |  phonenumber    |      address        | \n"
#define HEADER3 "   |--------------|------------|-----------------|---------------------| \n"
#define FORMAT  "   |    %-10s|  %-10s| %-15s |%-20s | \n"
#define DATA         p->num,p->name,p->phonenum,p->address
#define END     "   ---------------------------------------------------------------------\n"
#define N 100
int saveflag=0;  /*是否需要存盘的标志变量*/
/*定义与电话簿有关的数据结构*/
typedef struct telebook      /*标记为telebook*/
{
char num[4];          /*编号*/
char name[10];        /*姓名*/
char phonenum[15];    /*电话号码*/
char address[20];     /*地址*/
}TELEBOOK;

void menu()  /*主菜单*/
{
system("cls");   /*调用DOS命令，清屏.与clrscr()功能相同*/
textcolor(13);   /*在文本模式中选择新的字符颜色*/
gotoxy(10,5);    /*在文本窗口中设置光标*/
cprintf("                 The telephone-book  Management System \n");
gotoxy(10,8);
cprintf("     *************************Menu********************************\n");
gotoxy(10,9);
cprintf("     *  1 input   record              2 display record             *\n");
gotoxy(10,10);
cprintf("     *  3 delete  record              4 search  record             *\n");
gotoxy(10,11);
cprintf("     *  5 modify  record              6 insert  record             *\n");
gotoxy(10,12);
cprintf("     *  7 sort    record              8 save    record             *\n");
gotoxy(10,13);
cprintf("     *  0 quit    system                                           *\n");
gotoxy(10,14);
cprintf("     *************************************************************\n");
/*cprintf()送格式化输出至文本窗口屏幕中*/
}
/*格式化输出表头*/
void printheader()
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
 /*格式化输出表中数据*/
void printdata(TELEBOOK pp)
{
 TELEBOOK* p;
 p=&pp;
 printf(FORMAT,DATA);

}

/*显示数组temp[]中存储的电话簿记录，内容为telebook结构中定义的内容*/
void Disp(TELEBOOK temp[],int n)
{
int i;
if(n==0)  /*表示没有电话簿记录*/
{
  printf("\n=====>Not telephone record!\n");
  getchar();
  return;
}

printf("\n\n");
printheader(); /*输出表格头部*/
i=0;
while(i<n)    /*逐条输出数组中存储的电话簿记录*/
{
  printdata(temp[i]);
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

void Nofind()  /*输出未查找此记录的信息*/
{
printf("\n=====>Not find this telephone record!\n");
}

/*************************************************************
作用：用于定位数组中符合要求的记录，并返回保存该记录的数组元素下标值
参数：findmess[]保存要查找的具体内容; nameorphonenum[]保存按什么在数组中查找;
**************************************************************/
int Locate(TELEBOOK temp[],int n,char findmess[],char nameorphonenum[])
{
int i=0;
if(strcmp(nameorphonenum,"phonenum")==0) /*按电话号码查询*/
{
  while(i<n)
   {
   if(strcmp(temp[i].phonenum,findmess)==0) /*若找到findmess值的电话号码*/
    return i;
    i++;
    }
}
else if(strcmp(nameorphonenum,"name")==0)  /*按姓名查询*/
{
  while(i<n)
   {
   if(strcmp(temp[i].name,findmess)==0) /*若找到findmess值的姓名*/
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
      if(strlen(n)>lens) printf("\n exceed the required length! \n");
      /*进行长度校验，超过lens值重新输入*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/

}

 /*增加电话簿记录*/
int Add(TELEBOOK temp[],int n)
{
 char ch,num[10];
 int i,flag=0;
 system("cls");
 Disp(temp,n); /*先打印出已有的电话簿信息*/

 while(1) /*一次可输入多条记录，直至输入编号为0的记录才结束添加操作*/
 {
  while(1) /*输入记录编号，保证该编号没有被使用，若输入编号为0，则退出添加记录操作*/
  {
    stringinput(num,10,"input number(press '0'return menu):"); /*格式化输入编号并检验*/
    flag=0;
    if(strcmp(num,"0")==0) /*输入为0，则退出添加操作，返回主界面*/
      {return n;}
     i=0;
    while(i<n) /*查询该编号是否已经存在，若存在则要求重新输入一个未被占用的编号*/
    {
      if(strcmp(temp[i].num,num)==0)
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
  strcpy(temp[n].num,num); /*将字符串num拷贝到temp[n].num中*/
  stringinput(temp[n].name,15,"Name:");
  stringinput(temp[n].phonenum,15,"Telephone:");
  stringinput(temp[n].address,15,"Adress:");
  saveflag=1;
  n++;
  }
     return n;
}

/*按编号或姓名，查询电话簿记录*/
void Qur(TELEBOOK temp[],int n)
{
int select; /*1:按姓名查，2：按电话号码查，其他：返回主界面（菜单）*/
char searchinput[20]; /*保存用户输入的查询内容*/
int p=0;
if(n<=0) /*若数组为空*/
{
  system("cls");
  printf("\n=====>No telephone record!\n");
  getchar();
  return;
}
system("cls");
printf("\n     =====>1 Search by name  =====>2 Search by telephone number\n");
printf("      please choice[1,2]:");
scanf("%d",&select);
if(select==1)   /*按姓名查询*/
 {

  stringinput(searchinput,10,"input the existing name:");
  p=Locate(temp,n,searchinput,"name");
  /*在数组temp中查找编号为searchinput值的元素，并返回该数组元素的下标值*/
  if(p!=-1) /*若找到该记录*/
  {
   printheader();
   printdata(temp[p]);
   printf(END);
   printf("press any key to return");
   getchar();
  }
  else
   Nofind();
   getchar();
}
else if(select==2) /*按电话号码查询*/
{
  stringinput(searchinput,15,"input the existing telephone number:");
  p=Locate(temp,n,searchinput,"phonenum");
  if(p!=-1)
  {
   printheader();
   printdata(temp[p]);
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

/*删除电话簿记录：先找到保存该记录的数组元素的下标值，然后在数组中删除该数组元素*/
int Del(TELEBOOK temp[],int n)
{
int sel;
char findmess[20];
int p=0,i=0;
if(n<=0)
{ system("cls");
  printf("\n=====>No telephone record!\n");
  getchar();
  return n;
}
system("cls");
Disp(temp,n);
printf("\n    =====>1 Delete by name       =====>2 Delete by telephone number\n");
printf("    please choice[1,2]:");
scanf("%d",&sel);
if(sel==1)
{
  stringinput(findmess,10,"input the existing name:");
  p=Locate(temp,n,findmess,"name");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++) /*删除此记录，后面记录向前移*/
   { 
    strcpy(temp[i-1].num,temp[i].num);
    strcpy(temp[i-1].name,temp[i].name);
    strcpy(temp[i-1].phonenum,temp[i].phonenum);
    strcpy(temp[i-1].address,temp[i].address);

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
else if(sel==2) /*先按电话号码查询到该记录所在的数组元素的下标值*/
{
  stringinput(findmess,15,"input the existing telephone number:");
  p=Locate(temp,n,findmess,"phonenum");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++)   /*删除此记录，后面记录向前移*/
   { 
    strcpy(temp[i-1].num,temp[i].num);
    strcpy(temp[i-1].name,temp[i].name);
    strcpy(temp[i-1].phonenum,temp[i].phonenum);
    strcpy(temp[i-1].address,temp[i].address);
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

/*修改电话簿记录。先按输入的联系人姓名查询到该记录，
  然后提示用户修改该记录编号之外的值，编号不能修改*/
void Modify(TELEBOOK temp[],int n)
{
char findmess[20];
int p=0;
if(n<=0)
{ system("cls");
  printf("\n=====>No telephone number record!\n");
  getchar();
  return ;
}
system("cls");
printf("modify telephone book recorder");
Disp(temp,n);
stringinput(findmess,10,"input the existing name:"); /*输入并检验该姓名*/
p=Locate(temp,n,findmess,"name"); /*查询到该数组元素,并返回下标值*/
if(p!=-1) /*若p!=－1,表明已经找到该数组元素*/
{
   printf("Number:%s,\n",temp[p].num);
   printf("Name:%s,",temp[p].name);
   stringinput(temp[p].name,15,"input new name:");

   printf("Name:%s,",temp[p].phonenum);
   stringinput(temp[p].phonenum,15,"input new telephone:");

   printf("Name:%s,",temp[p].address);
   stringinput(temp[p].address,30,"input new address:");

   printf("\n=====>modify success!\n");
   getchar();
   Disp(temp,n);
   getchar();
   saveflag=1;
}
else
  {Nofind();
   getchar();
  }
return ;
}

/*插入记录:按编号查询到要插入的数组元素的位置，然后在该记录编号之后插入一个新数组元素。*/
int Insert(TELEBOOK temp[],int n)
{
   char ch,num[10],s[10];  /*s[]保存插入点位置之前的记录编号,num[]保存输入的新记录的编号*/
   TELEBOOK newinfo;
   int flag=0,i=0,kkk=0;
   system("cls");
   Disp(temp,n);
   while(1)
   { stringinput(s,10,"please input insert location  after the Number:");
     flag=0;i=0;
     while(i<n) /*查询该编号是否存在，flag=1表示该编号存在*/
     {
      if(strcmp(temp[i].num,s)==0)  {kkk=i;flag=1;break;}
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
  { stringinput(num,10,"input new Number:");
    i=0;flag=0;
    while(i<n) /*查询该编号是否存在，flag=1表示该编号存在*/
     {
      if(strcmp(temp[i].num,num)==0)  {flag=1;break;}
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
  stringinput(newinfo.phonenum,15,"Telephone:");
  stringinput(newinfo.address,15,"Adress:");

  saveflag=1; /*在main()有对该全局变量的判断，若为1,则进行存盘操作*/

 for(i=n-1;i>kkk;i--) /*从最后一个组织元素开始往向移一个元素位置*/
 {
   strcpy(temp[i+1].num,temp[i].num);
   strcpy(temp[i+1].name,temp[i].name);
   strcpy(temp[i+1].phonenum,temp[i].phonenum);
   strcpy(temp[i+1].address,temp[i].address);
 }
   strcpy(temp[kkk+1].num,newinfo.num);  /*在kkk的元素位置后插入新记录*/
   strcpy(temp[kkk+1].name,newinfo.name);
   strcpy(temp[kkk+1].phonenum,newinfo.phonenum);
   strcpy(temp[kkk+1].address,newinfo.address);
   n++;
   Disp(temp,n);
   printf("\n\n");
   getchar();
   return n;
}


/*利用选择排序法实现数组的按记录编号或姓名的升序排序*/
void SelectSort(TELEBOOK temp[],int n)
{
int i=0,j=0,flag=0,indexmin,select;
char charflag[10];
TELEBOOK newinfo;
if(n<=0)
{ system("cls");
  printf("\n=====>Not telephone record!\n");
  getchar();
  return ;
}
system("cls");
Disp(temp,n);  /*显示排序前的所有记录*/
printf("     ==>1 SORT BY NUMBER   ==>2 SORT BY NAME\n");
printf("      please choice[1,2]:");
scanf("%d",&select);
if(select==1)   /*按记录编号排序*/
{
 for(i=0;i<n-1;i++)
 {
  flag=32767;indexmin=0;
  for(j=i;j<n;j++)
    { if(atoi(temp[j].num)<flag)
      { flag=atoi(temp[j].num);
        indexmin=j;
       }
     }
     strcpy(newinfo.num,temp[i].num);  /*利用结构变量newinfo实现数组元素的交换*/
     strcpy(newinfo.name,temp[i].name);
     strcpy(newinfo.phonenum,temp[i].phonenum);
     strcpy(newinfo.address,temp[i].address);

     strcpy(temp[i].num,temp[indexmin].num);
     strcpy(temp[i].name,temp[indexmin].name);
     strcpy(temp[i].phonenum,temp[indexmin].phonenum);
     strcpy(temp[i].address,temp[indexmin].address);

     strcpy(temp[indexmin].num,newinfo.num);
    strcpy(temp[indexmin].name,newinfo.name);
    strcpy(temp[indexmin].phonenum,newinfo.phonenum);
    strcpy(temp[indexmin].address,newinfo.address);
  }
      Disp(temp,n);  /*显示排序后的所有记录*/
      saveflag=1;
      printf("\n    =====>sort complete!\n");
      getchar();
      return;
 }
 else if(select==2)
 {
  for(i=0;i<n-1;i++)
 {
  charflag[0]=255;indexmin=0;
  for(j=i;j<n;j++)
    { if(strcmp(temp[j].name,charflag)>0)
      { charflag[0]=temp[j].name;
        indexmin=j;
       }
     }
     strcpy(newinfo.num,temp[i].num);  /*利用结构变量newinfo实现数组元素的交换*/
     strcpy(newinfo.name,temp[i].name);
     strcpy(newinfo.phonenum,temp[i].phonenum);
     strcpy(newinfo.address,temp[i].address);

     strcpy(temp[i].num,temp[indexmin].num);
     strcpy(temp[i].name,temp[indexmin].name);
     strcpy(temp[i].phonenum,temp[indexmin].phonenum);
     strcpy(temp[i].address,temp[indexmin].address);

     strcpy(temp[indexmin].num,newinfo.num);
    strcpy(temp[indexmin].name,newinfo.name);
    strcpy(temp[indexmin].phonenum,newinfo.phonenum);
    strcpy(temp[indexmin].address,newinfo.address);
    }
      Disp(temp,n);  /*显示排序后的所有记录*/
      saveflag=1;
      printf("\n    =====>sort complete!\n");
      getchar();
      return;
  }
  else
  {Wrong();
   getchar();
   getchar();
   return;}

}




/*数据存盘,若用户没有专门进行此操作且对数据有修改，在退出系统时， 会提示用户存盘*/
void Save(TELEBOOK temp[],int n)
{
FILE* fp;
int i=0;
fp=fopen("c:\\telephon","w");/*以只写方式打开文本文件*/
if(fp==NULL) /*打开文件失败*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
for(i=0;i<n;i++)
{
  if(fwrite(&temp[i],sizeof(TELEBOOK),1,fp)==1)/*每次写一条记录或一个结构数组元素至文件*/
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
 printf("the current link is empty,no telephone record is saved!\n");
 getchar();
 }
fclose(fp); /*关闭此文件*/
}


void main()
{
  TELEBOOK tele[N];         /*定义TELEBOOK结构体*/
  FILE *fp;           /*文件指针*/
  int select;         /*保存选择结果变量*/
  char ch;            /*保存(y,Y,n,N)*/
  int count=0;        /*保存文件中的记录条数（或元素个数）*/
   
  fp=fopen("C:\\telephon","a+");
  /*以追加方式打开文本文件c:\telephon，可读可写，若此文件不存在，会创建此文件*/
  if(fp==NULL)
  {
    printf("\n=====>can not open file!\n");
    exit(0);
  }

while(!feof(fp))
{
   if(fread(&tele[count],sizeof(TELEBOOK),1,fp)==1) /*一次从文件中读取一条电话簿记录*/
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
   printf("\n              Please Enter your choice(0~8):");    /*显示提示信息*/
   scanf("%d",&select);

  if(select==0)
  {
   if(saveflag==1) /*若对数组的数据有修改且未进行存盘操作，则此标志为1*/
   { getchar();
     printf("\n==>Whether save the modified record to file?(y/n):");
     scanf("%c",&ch);
     if(ch=='y'||ch=='Y')
       Save(tele,count);
   }
   printf("\n===>thank you for useness!");
   getchar();
   break;
  }

  switch(select)
  {
  case 1:count=Add(tele,count);break;       /*增加电话簿记录*/
  case 2:system("cls");Disp(tele,count);break;   /*显示电话簿记录*/
  case 3:count=Del(tele,count);break;      /*删除电话簿记录*/
  case 4:Qur(tele,count);break;           /*查询电话簿记录*/
  case 5:Modify(tele,count);break;        /*修改电话簿记录*/
  case 6:count=Insert(tele,count);break;  /*插入电话簿记录*/
  case 7:SelectSort(tele,count);break;        /*排序电话簿记录*/
  case 8:Save(tele,count);break;        /*保存电话簿记录*/
  default: Wrong();getchar();break;        /*按键有误，必须为数值0-9*/
  }
 }
}
