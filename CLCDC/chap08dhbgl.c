#include "stdio.h"   /*��׼�������������*/
#include "stdlib.h"  /*��׼������*/
#include "string.h"  /*�ַ���������*/
#include "conio.h"   /*��Ļ����������*/
#define HEADER1 "    ---------------------------TELEPHONE BOOK---------------------------\n"
#define HEADER2 "   |    num       |    name    |  phonenumber    |      address        | \n"
#define HEADER3 "   |--------------|------------|-----------------|---------------------| \n"
#define FORMAT  "   |    %-10s|  %-10s| %-15s |%-20s | \n"
#define DATA         p->num,p->name,p->phonenum,p->address
#define END     "   ---------------------------------------------------------------------\n"
#define N 100
int saveflag=0;  /*�Ƿ���Ҫ���̵ı�־����*/
/*������绰���йص����ݽṹ*/
typedef struct telebook      /*���Ϊtelebook*/
{
char num[4];          /*���*/
char name[10];        /*����*/
char phonenum[15];    /*�绰����*/
char address[20];     /*��ַ*/
}TELEBOOK;

void menu()  /*���˵�*/
{
system("cls");   /*����DOS�������.��clrscr()������ͬ*/
textcolor(13);   /*���ı�ģʽ��ѡ���µ��ַ���ɫ*/
gotoxy(10,5);    /*���ı����������ù��*/
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
/*cprintf()�͸�ʽ��������ı�������Ļ��*/
}
/*��ʽ�������ͷ*/
void printheader()
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
 /*��ʽ�������������*/
void printdata(TELEBOOK pp)
{
 TELEBOOK* p;
 p=&pp;
 printf(FORMAT,DATA);

}

/*��ʾ����temp[]�д洢�ĵ绰����¼������Ϊtelebook�ṹ�ж��������*/
void Disp(TELEBOOK temp[],int n)
{
int i;
if(n==0)  /*��ʾû�е绰����¼*/
{
  printf("\n=====>Not telephone record!\n");
  getchar();
  return;
}

printf("\n\n");
printheader(); /*������ͷ��*/
i=0;
while(i<n)    /*������������д洢�ĵ绰����¼*/
{
  printdata(temp[i]);
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

void Nofind()  /*���δ���Ҵ˼�¼����Ϣ*/
{
printf("\n=====>Not find this telephone record!\n");
}

/*************************************************************
���ã����ڶ�λ�����з���Ҫ��ļ�¼�������ر���ü�¼������Ԫ���±�ֵ
������findmess[]����Ҫ���ҵľ�������; nameorphonenum[]���水ʲô�������в���;
**************************************************************/
int Locate(TELEBOOK temp[],int n,char findmess[],char nameorphonenum[])
{
int i=0;
if(strcmp(nameorphonenum,"phonenum")==0) /*���绰�����ѯ*/
{
  while(i<n)
   {
   if(strcmp(temp[i].phonenum,findmess)==0) /*���ҵ�findmessֵ�ĵ绰����*/
    return i;
    i++;
    }
}
else if(strcmp(nameorphonenum,"name")==0)  /*��������ѯ*/
{
  while(i<n)
   {
   if(strcmp(temp[i].name,findmess)==0) /*���ҵ�findmessֵ������*/
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
      if(strlen(n)>lens) printf("\n exceed the required length! \n");
      /*���г���У�飬����lensֵ��������*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*��������ַ����������ַ���t��*/

}

 /*���ӵ绰����¼*/
int Add(TELEBOOK temp[],int n)
{
 char ch,num[10];
 int i,flag=0;
 system("cls");
 Disp(temp,n); /*�ȴ�ӡ�����еĵ绰����Ϣ*/

 while(1) /*һ�ο����������¼��ֱ��������Ϊ0�ļ�¼�Ž�����Ӳ���*/
 {
  while(1) /*�����¼��ţ���֤�ñ��û�б�ʹ�ã���������Ϊ0�����˳���Ӽ�¼����*/
  {
    stringinput(num,10,"input number(press '0'return menu):"); /*��ʽ�������Ų�����*/
    flag=0;
    if(strcmp(num,"0")==0) /*����Ϊ0�����˳���Ӳ���������������*/
      {return n;}
     i=0;
    while(i<n) /*��ѯ�ñ���Ƿ��Ѿ����ڣ���������Ҫ����������һ��δ��ռ�õı��*/
    {
      if(strcmp(temp[i].num,num)==0)
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
  strcpy(temp[n].num,num); /*���ַ���num������temp[n].num��*/
  stringinput(temp[n].name,15,"Name:");
  stringinput(temp[n].phonenum,15,"Telephone:");
  stringinput(temp[n].address,15,"Adress:");
  saveflag=1;
  n++;
  }
     return n;
}

/*����Ż���������ѯ�绰����¼*/
void Qur(TELEBOOK temp[],int n)
{
int select; /*1:�������飬2�����绰����飬���������������棨�˵���*/
char searchinput[20]; /*�����û�����Ĳ�ѯ����*/
int p=0;
if(n<=0) /*������Ϊ��*/
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
if(select==1)   /*��������ѯ*/
 {

  stringinput(searchinput,10,"input the existing name:");
  p=Locate(temp,n,searchinput,"name");
  /*������temp�в��ұ��Ϊsearchinputֵ��Ԫ�أ������ظ�����Ԫ�ص��±�ֵ*/
  if(p!=-1) /*���ҵ��ü�¼*/
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
else if(select==2) /*���绰�����ѯ*/
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

/*ɾ���绰����¼�����ҵ�����ü�¼������Ԫ�ص��±�ֵ��Ȼ����������ɾ��������Ԫ��*/
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
   for(i=p+1;i<n;i++) /*ɾ���˼�¼�������¼��ǰ��*/
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
else if(sel==2) /*�Ȱ��绰�����ѯ���ü�¼���ڵ�����Ԫ�ص��±�ֵ*/
{
  stringinput(findmess,15,"input the existing telephone number:");
  p=Locate(temp,n,findmess,"phonenum");
  getchar();
  if(p!=-1)
  {
   for(i=p+1;i<n;i++)   /*ɾ���˼�¼�������¼��ǰ��*/
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

/*�޸ĵ绰����¼���Ȱ��������ϵ��������ѯ���ü�¼��
  Ȼ����ʾ�û��޸ĸü�¼���֮���ֵ����Ų����޸�*/
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
stringinput(findmess,10,"input the existing name:"); /*���벢���������*/
p=Locate(temp,n,findmess,"name"); /*��ѯ��������Ԫ��,�������±�ֵ*/
if(p!=-1) /*��p!=��1,�����Ѿ��ҵ�������Ԫ��*/
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

/*�����¼:����Ų�ѯ��Ҫ���������Ԫ�ص�λ�ã�Ȼ���ڸü�¼���֮�����һ��������Ԫ�ء�*/
int Insert(TELEBOOK temp[],int n)
{
   char ch,num[10],s[10];  /*s[]��������λ��֮ǰ�ļ�¼���,num[]����������¼�¼�ı��*/
   TELEBOOK newinfo;
   int flag=0,i=0,kkk=0;
   system("cls");
   Disp(temp,n);
   while(1)
   { stringinput(s,10,"please input insert location  after the Number:");
     flag=0;i=0;
     while(i<n) /*��ѯ�ñ���Ƿ���ڣ�flag=1��ʾ�ñ�Ŵ���*/
     {
      if(strcmp(temp[i].num,s)==0)  {kkk=i;flag=1;break;}
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
  { stringinput(num,10,"input new Number:");
    i=0;flag=0;
    while(i<n) /*��ѯ�ñ���Ƿ���ڣ�flag=1��ʾ�ñ�Ŵ���*/
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
  
  strcpy(newinfo.num,num); /*���ַ���num������newinfo.num��*/
  stringinput(newinfo.name,15,"Name:");
  stringinput(newinfo.phonenum,15,"Telephone:");
  stringinput(newinfo.address,15,"Adress:");

  saveflag=1; /*��main()�жԸ�ȫ�ֱ������жϣ���Ϊ1,����д��̲���*/

 for(i=n-1;i>kkk;i--) /*�����һ����֯Ԫ�ؿ�ʼ������һ��Ԫ��λ��*/
 {
   strcpy(temp[i+1].num,temp[i].num);
   strcpy(temp[i+1].name,temp[i].name);
   strcpy(temp[i+1].phonenum,temp[i].phonenum);
   strcpy(temp[i+1].address,temp[i].address);
 }
   strcpy(temp[kkk+1].num,newinfo.num);  /*��kkk��Ԫ��λ�ú�����¼�¼*/
   strcpy(temp[kkk+1].name,newinfo.name);
   strcpy(temp[kkk+1].phonenum,newinfo.phonenum);
   strcpy(temp[kkk+1].address,newinfo.address);
   n++;
   Disp(temp,n);
   printf("\n\n");
   getchar();
   return n;
}


/*����ѡ������ʵ������İ���¼��Ż���������������*/
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
Disp(temp,n);  /*��ʾ����ǰ�����м�¼*/
printf("     ==>1 SORT BY NUMBER   ==>2 SORT BY NAME\n");
printf("      please choice[1,2]:");
scanf("%d",&select);
if(select==1)   /*����¼�������*/
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
     strcpy(newinfo.num,temp[i].num);  /*���ýṹ����newinfoʵ������Ԫ�صĽ���*/
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
      Disp(temp,n);  /*��ʾ���������м�¼*/
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
     strcpy(newinfo.num,temp[i].num);  /*���ýṹ����newinfoʵ������Ԫ�صĽ���*/
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
      Disp(temp,n);  /*��ʾ���������м�¼*/
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




/*���ݴ���,���û�û��ר�Ž��д˲����Ҷ��������޸ģ����˳�ϵͳʱ�� ����ʾ�û�����*/
void Save(TELEBOOK temp[],int n)
{
FILE* fp;
int i=0;
fp=fopen("c:\\telephon","w");/*��ֻд��ʽ���ı��ļ�*/
if(fp==NULL) /*���ļ�ʧ��*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
for(i=0;i<n;i++)
{
  if(fwrite(&temp[i],sizeof(TELEBOOK),1,fp)==1)/*ÿ��дһ����¼��һ���ṹ����Ԫ�����ļ�*/
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
fclose(fp); /*�رմ��ļ�*/
}


void main()
{
  TELEBOOK tele[N];         /*����TELEBOOK�ṹ��*/
  FILE *fp;           /*�ļ�ָ��*/
  int select;         /*����ѡ��������*/
  char ch;            /*����(y,Y,n,N)*/
  int count=0;        /*�����ļ��еļ�¼��������Ԫ�ظ�����*/
   
  fp=fopen("C:\\telephon","a+");
  /*��׷�ӷ�ʽ���ı��ļ�c:\telephon���ɶ���д�������ļ������ڣ��ᴴ�����ļ�*/
  if(fp==NULL)
  {
    printf("\n=====>can not open file!\n");
    exit(0);
  }

while(!feof(fp))
{
   if(fread(&tele[count],sizeof(TELEBOOK),1,fp)==1) /*һ�δ��ļ��ж�ȡһ���绰����¼*/
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
   printf("\n              Please Enter your choice(0~8):");    /*��ʾ��ʾ��Ϣ*/
   scanf("%d",&select);

  if(select==0)
  {
   if(saveflag==1) /*����������������޸���δ���д��̲�������˱�־Ϊ1*/
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
  case 1:count=Add(tele,count);break;       /*���ӵ绰����¼*/
  case 2:system("cls");Disp(tele,count);break;   /*��ʾ�绰����¼*/
  case 3:count=Del(tele,count);break;      /*ɾ���绰����¼*/
  case 4:Qur(tele,count);break;           /*��ѯ�绰����¼*/
  case 5:Modify(tele,count);break;        /*�޸ĵ绰����¼*/
  case 6:count=Insert(tele,count);break;  /*����绰����¼*/
  case 7:SelectSort(tele,count);break;        /*����绰����¼*/
  case 8:Save(tele,count);break;        /*����绰����¼*/
  default: Wrong();getchar();break;        /*�������󣬱���Ϊ��ֵ0-9*/
  }
 }
}
