#include "stdio.h"   /*��׼�������������*/
#include "stdlib.h"  /*��׼������*/
#include "string.h"  /*�ַ���������*/
#include "conio.h"   /*��Ļ����������*/
#define HEADER1 " -------------------------------ZGGZ---------------------------------------- \n"
#define HEADER2 "|  number|    name   |  jbgz  |   jj   |   kk   |   yfgz |   sk   |  sfgz  | \n"
#define HEADER3 "|--------|-----------|--------|--------|--------|--------|--------|--------| \n"
#define FORMAT  "|%-8s|%-10s |%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f| \n"
#define DATA      p->num,p->name,p->jbgz,p->jj,p->kk,p->yfgz,p->sk,p->sfgz
#define END     "---------------------------------------------------------------------------- \n"
#define N 60
int saveflag=0;  /*�Ƿ���Ҫ���̵ı�־����*/
/*������ְ���йص����ݽṹ*/
typedef struct employee      /*���Ϊemployee*/
{
char num[10];   /*ְ�����*/
char name[15];  /*ְ������*/
float jbgz;     /*��������*/
float jj;       /*����*/
float kk;       /*�ۿ�*/
float yfgz;     /*Ӧ������*/
float sk;       /*˰��*/
float sfgz;     /*ʵ������*/
}ZGGZ;

void menu()  /*���˵�*/
{
system("cls");   /*����DOS�������.��clrscr()������ͬ*/
textcolor(10);   /*���ı�ģʽ��ѡ���µ��ַ���ɫ*/
gotoxy(10,5);    /*���ı����������ù��*/
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
/*cprintf()�͸�ʽ��������ı�������Ļ��*/
}
void printheader() /*��ʽ�������ͷ*/
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
void printdata(ZGGZ pp) /*��ʽ�������������*/
{
 ZGGZ* p;
 p=&pp;
 printf(FORMAT,DATA);

}

void Disp(ZGGZ tp[],int n)  /*��ʾ����tp[]�д洢�ļ�¼������Ϊemployee�ṹ�ж��������*/
{
int i;
if(n==0)  /*��ʾû��ְ�����ʼ�¼*/
{
  printf("\n=====>Not employee record!\n");
  getchar();
  return;
}

printf("\n\n");
printheader(); /*������ͷ��*/
i=0;
while(i<n)    /*������������д洢��ְ����Ϣ*/
{
  printdata(tp[i]);
  i++;
  printf(HEADER3);
}
getchar();
}

void Wrong()  /*�������������Ϣ*/
{
printf("\n\n\n\n\n***********Error:input has wrong! press any key to continue**********\n");
getchar();
}

void Nofind()  /*���δ���Ҵ�ְ������Ϣ*/
{
printf("\n=====>Not find this employee record!\n");
}

/*************************************************************
���ã����ڶ�λ�����з���Ҫ��ļ�¼�������ر���ü�¼������Ԫ���±�ֵ
������findmess[]����Ҫ���ҵľ�������; nameornum[]���水ʲô�������в���;
**************************************************************/
int Locate(ZGGZ tp[],int n,char findmess[],char nameornum[])
{
int i=0;
if(strcmp(nameornum,"num")==0) /*��ְ����Ų�ѯ*/
{
  while(i<n)
   {
   if(strcmp(tp[i].num,findmess)==0) /*���ҵ�findmessֵ��ְ�����*/
    return i;
    i++;
    }
}
else if(strcmp(nameornum,"name")==0)  /*��ְ��������ѯ*/
{
  while(i<n)
   {
   if(strcmp(tp[i].name,findmess)==0) /*���ҵ�findmessֵ������*/
    return i;
    i++;
    }
}
return -1; /*��δ�ҵ�������һ������-1*/
}


/*�����ַ����������г�����֤(����<lens)*/
void stringinput(char *t,int lens,char *notice)
{
   char n[255];
   do{
      printf(notice);  /*��ʾ��ʾ��Ϣ*/
      scanf("%s",n);  /*�����ַ���*/
      if(strlen(n)>lens) printf("\n exceed the required length! \n"); /*���г���У�飬����lensֵ��������*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*��������ַ����������ַ���t��*/

}

/*������ֵ��0<����ֵ)*/
float numberinput(char *notice)
{
  float t=0.00;
   do{
      printf(notice);    /*��ʾ��ʾ��Ϣ*/
      scanf("%f",&t);  /*�����繤�ʵ���ֵ�͵�ֵ*/
      if(t<0) printf("\n score must >=0! \n"); /*������ֵУ��*/
   }while(t<0);
   return t;
}


 /*����ְ�����ʼ�¼*/
int Add(ZGGZ tp[],int n)
{
 char ch,num[10];
 int i,flag=0;
 system("cls");
 Disp(tp,n); /*�ȴ�ӡ�����е�ְ��������Ϣ*/

 while(1) /*һ�ο����������¼��ֱ������ְ�����Ϊ0�ļ�¼�Ž�����Ӳ���*/
 {
  while(1) /*����ְ����ţ���֤�ñ��û�б�ʹ�ã���������Ϊ0�����˳���Ӽ�¼����*/
  {
    stringinput(num,10,"input number(press '0'return menu):"); /*��ʽ�������Ų�����*/
    flag=0;
    if(strcmp(num,"0")==0) /*����Ϊ0�����˳���Ӳ���������������*/
      {return n;}
     i=0;
    while(i<n) /*��ѯ�ñ���Ƿ��Ѿ����ڣ���������Ҫ����������һ��δ��ռ�õı��*/
    {
      if(strcmp(tp[i].num,num)==0)
      {
       flag=1;
       break;
       }
      i++;
    }

  if(flag==1) /*��ʾ�û��Ƿ���������*/
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
  strcpy(tp[n].num,num); /*���ַ���num������tp[n].num��*/
  stringinput(tp[n].name,15,"Name:");
  tp[n].jbgz=numberinput("jbgz:"); /*���벢�����������*/
  tp[n].jj=numberinput("jiangjin:");         /*���벢���齱��*/
  tp[n].kk=numberinput("koukuan:");      /*���벢����ۿ�*/
  tp[n].yfgz=tp[n].jbgz+tp[n].jj-tp[n].kk;      /*����Ӧ������*/
  tp[n].sk=tp[n].yfgz*0.12;  /*����˰������ȡӦ�����ʵİٷ�֮һʮ��*/
  tp[n].sfgz=tp[n].yfgz-tp[n].sk; /*����ʵ������*/
  saveflag=1;
  n++;
  }
     return n;
}

/*��ְ����Ż���������ѯ��¼*/
void Qur(ZGGZ tp[],int n)
{
int select; /*1:����Ų飬2���������飬���������������棨�˵���*/
char searchinput[20]; /*�����û�����Ĳ�ѯ����*/
int p=0;
if(n<=0) /*������Ϊ��*/
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
if(select==1)   /*����Ų�ѯ*/
 {

  stringinput(searchinput,10,"input the existing employee number:");
  p=Locate(tp,n,searchinput,"num");/*������tp�в��ұ��Ϊsearchinputֵ��Ԫ�أ������ظ�����Ԫ�ص��±�ֵ*/
  if(p!=-1) /*���ҵ��ü�¼*/
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
else if(select==2) /*��������ѯ*/
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

/*ɾ����¼�����ҵ�����ü�¼������Ԫ�ص��±�ֵ��Ȼ����������ɾ��������Ԫ��*/
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
   for(i=p+1;i<n;i++) /*ɾ���˼�¼�������¼��ǰ��*/
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
else if(sel==2) /*�Ȱ�������ѯ���ü�¼���ڵ�����Ԫ�ص��±�ֵ*/
{
  stringinput(findmess,15,"input the existing employee name:");
  p=Locate(tp,n,findmess,"name");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++)   /*ɾ���˼�¼�������¼��ǰ��*/
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

/*�޸ļ�¼���Ȱ������ְ����Ų�ѯ���ü�¼��Ȼ����ʾ�û��޸ı��֮���ֵ����Ų����޸�*/
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
stringinput(findmess,10,"input the existing employee number:"); /*���벢����ñ��*/
p=Locate(tp,n,findmess,"num"); /*��ѯ��������Ԫ��,�������±�ֵ*/
if(p!=-1) /*��p!=��1,�����Ѿ��ҵ�������Ԫ��*/
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

/*�����¼:��ְ����Ų�ѯ��Ҫ���������Ԫ�ص�λ�ã�Ȼ���ڸñ��֮�����һ��������Ԫ�ء�*/
int Insert(ZGGZ tp[],int n)
{
   char ch,num[10],s[10];  /*s[]��������λ��֮ǰ�ı��,num[]����������¼�¼�ı��*/
   ZGGZ newinfo;
   int flag=0,i=0,kkk=0;
   system("cls");
   Disp(tp,n);
   while(1)
   { stringinput(s,10,"please input insert location  after the Number:");
     flag=0;i=0;
     while(i<n) /*��ѯ�ñ���Ƿ���ڣ�flag=1��ʾ�ñ�Ŵ���*/
     {
      if(strcmp(tp[i].num,s)==0)  {kkk=i;flag=1;break;}
      i++;
     }
      if(flag==1)
        break; /*����Ŵ��ڣ�����в���֮ǰ���¼�¼�������*/
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
  /*�����¼�¼�����������Add()��ͬ*/

  while(1)
  { stringinput(num,10,"input new employee Number:");
    i=0;flag=0;
    while(i<n) /*��ѯ�ñ���Ƿ���ڣ�flag=1��ʾ�ñ�Ŵ���*/
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
  
  strcpy(newinfo.num,num); /*���ַ���num������newinfo.num��*/
  stringinput(newinfo.name,15,"Name:");
  newinfo.jbgz=numberinput("jbgz:"); /*���벢����jbgz*/
  newinfo.jj=numberinput("jiangjin:");         /*���벢����jiangjin*/
  newinfo.kk=numberinput("koukuan:");      /*���벢����koukuan*/
  newinfo.yfgz=newinfo.jbgz+newinfo.jj-newinfo.kk;      /*����yfgz*/
  newinfo.sk=newinfo.yfgz*0.12;  /*����sk*/
  newinfo.sfgz=newinfo.yfgz-newinfo.sk;
  saveflag=1; /*��main()�жԸ�ȫ�ֱ������жϣ���Ϊ1,����д��̲���*/

 for(i=n-1;i>kkk;i--) /*�����һ����֯Ԫ�ؿ�ʼ������һ��Ԫ��λ��*/
 { strcpy(tp[i+1].num,tp[i].num);
   strcpy(tp[i+1].name,tp[i].name);
   tp[i+1].jbgz=tp[i].jbgz;
   tp[i+1].jj=tp[i].jj;
   tp[i+1].kk=tp[i].kk;
   tp[i+1].yfgz=tp[i].yfgz;
   tp[i+1].sk=tp[i].sk;
   tp[i+1].sfgz=tp[i].sfgz;
 }
   strcpy(tp[kkk+1].num,newinfo.num);  /*��kkk��Ԫ��λ�ú�����¼�¼*/
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

/*ͳ�ƹ�˾��Ա���Ĺ����ڸ��ȼ�������*/
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
  if(tp[i].sfgz>=10000) {count10000++;i=i+1;continue;}  /*ʵ������>10000*/
  if(tp[i].sfgz>=5000)  {count5000++;i=i+1;continue;}    /*5000<=ʵ������<10000*/
  if(tp[i].sfgz>=2000)  {count2000++;i=i+1;continue;}    /*2000<=ʵ������<5000*/
  if(tp[i].sfgz<2000)   {count0++;i=i+1;continue;}      /*ʵ������<2000*/

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

/*����ð������ʵ������İ�ʵ�������ֶεĽ������򣬴Ӹߵ���*/
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
Disp(tp,n);  /*��ʾ����ǰ�����м�¼*/
for(i=0;i<n;i++)
{
  flag=0;
  for(j=0;j<n-1;j++)
   if((tp[j].sfgz<tp[j+1].sfgz))
    { flag=1;
      strcpy(newinfo.num,tp[j].num);  /*���ýṹ����newinfoʵ������Ԫ�صĽ���*/
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
     if(flag==0) break;/*�����flag=0����ζ��û�н����ˣ������Ѿ����*/
    }
      Disp(tp,n);  /*��ʾ���������м�¼*/
      saveflag=1;
      printf("\n    =====>sort complete!\n");

}




/*���ݴ���,���û�û��ר�Ž��д˲����Ҷ��������޸ģ����˳�ϵͳʱ�� ����ʾ�û�����*/
void Save(ZGGZ tp[],int n)
{
FILE* fp;
int i=0;
fp=fopen("c:\\zggz","wb");/*��ֻд��ʽ�򿪶������ļ�*/
if(fp==NULL) /*���ļ�ʧ��*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
for(i=0;i<n;i++)
{
  if(fwrite(&tp[i],sizeof(ZGGZ),1,fp)==1)/*ÿ��дһ����¼��һ���ṹ����Ԫ�����ļ�*/
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
fclose(fp); /*�رմ��ļ�*/
}


void main()
{
  ZGGZ gz[N];         /*����ZGGZ�ṹ��*/
  FILE *fp;           /*�ļ�ָ��*/
  int select;         /*����ѡ��������*/
  char ch;            /*����(y,Y,n,N)*/
  int count=0;        /*�����ļ��еļ�¼��������Ԫ�ظ�����*/
   
  fp=fopen("C:\\zggz","ab+");
  /*��׷�ӷ�ʽ�򿪶������ļ�c:\zggz���ɶ���д�������ļ������ڣ��ᴴ�����ļ�*/
  if(fp==NULL)
  {
    printf("\n=====>can not open file!\n");
    exit(0);
  }

while(!feof(fp))
{
   if(fread(&gz[count],sizeof(ZGGZ),1,fp)==1) /*һ�δ��ļ��ж�ȡһ��ְ�����ʼ�¼*/
      count++;
}
fclose(fp); /*�ر��ļ�*/
printf("\n==>open file sucess,the total records number is : %d.\n",count);
getchar();
menu();
while(1)
{
   system("cls");
   menu();
   printf("\n              Please Enter your choice(0~9):");    /*��ʾ��ʾ��Ϣ*/
   scanf("%d",&select);

  if(select==0)
  {
   if(saveflag==1) /*����������������޸���δ���д��̲�������˱�־Ϊ1*/
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
  case 1:count=Add(gz,count);break;       /*����ְ�����ʼ�¼*/
  case 2:count=Del(gz,count);break;      /*ɾ��ְ�����ʼ�¼*/
  case 3:Qur(gz,count);break;           /*��ѯְ�����ʼ�¼*/
  case 4:Modify(gz,count);break;        /*�޸�ְ�����ʼ�¼*/
  case 5:count=Insert(gz,count);break;  /*����ְ�����ʼ�¼*/
  case 6:Tongji(gz,count);break;       /*ͳ��ְ�����ʼ�¼*/
  case 7:Sort(gz,count);break;        /*����ְ�����ʼ�¼*/
  case 8:Save(gz,count);break;        /*����ְ�����ʼ�¼*/
  case 9:system("cls");Disp(gz,count);break;         /*��ʾְ�����ʼ�¼*/
  default: Wrong();getchar();break;        /*�������󣬱���Ϊ��ֵ0-9*/
  }
 }
}
