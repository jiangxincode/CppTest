#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
void f_new(void);
void f_save(void);
void f_open(void);
typedef struct
{
	int type;
	char name[20];
	char sex[2];
	char phone[20];
}PERSON;
PERSON data[200];
long count=0,n=0;
char a[20];
int main1171()
{
	int m;
	printf("\n\n\n"
		   "\t*************************************************\n"
		   "\t********       通      讯      录      **********\n"
		   "\t*************                     ***************\n"
		   "\t*************************************************\n"
		   "\t*************************************************\n"
		   "\t*******     Weclome to notebook!!!     **********\n"
		   "\t*************************************************\n"
		   "\t*****             made by 蒋鑫 (111150034)  **** \n"
		   "\t*************************************************\n"
		   "\t****************         地科院基地班       *****\n"
		   "\t***  copyright @ JX   ***************************\n"
		   "\t*************************************************\n"
		   "\t*************************************************\n"
		   "\t*************************************************\n"
		   "\t*Please use VC,or you will lose some information*\n"
		   "\t*************************************************\n"
		   "\t*************************************************\n"
		   "\n\n\n");
	printf("Input e if you want exit.\nOtherwise you can input any letter or number and end up with Enter:\n");
	scanf("%s",a);
	if(strncmp(a,"e",1)==0)
	{
		printf("Are you really want to exit? if so,please input y.\nOtherwise you can input any letter or number and end up with Enter:\n:");
        scanf("%s",a);
	    if(strncmp(a,"y",1)==0)
			return 0;
	}
loop:do{
	printf("\n\n\n\n\n\n\n\n"
		"\t**********************************\n"
		"\t             1.新    建           \n"
		"\t             2.保    存           \n"
		"\t             3.打    开           \n"
		"\t             4.版权说明           \n"
		"\t             5.使用说明           \n"
		"\t             6.退    出           \n"
		"\t**********************************\n"
		"\t**********************************\n"
		"\t***********  made by JX  *********\n"
		"\t**********************************\n"
		"\tPlease choose the function:\n\n\n\n\n");
	scanf("%d",&m);
	while(m<1||m>6)
	{
		printf("Error!\n");
		printf("Please input again\n");
	    scanf("%d",&m);
	};
	switch(m){
	case 1: f_new();break;
	case 2: f_save();break;
	case 3: f_open();break;
	case 4: {
		printf("\n    本程序由南京大学地球科学与工程学院的蒋鑫制作。");
		printf("\n    如果你使用本程序即代表已经完全同意本约定，否则请勿使用。");
        printf("\n    请您不要未经允许擅自复制，修改，传播本程序。");
		printf("\n    本程序仅用于个人娱乐研究使用，同时本程序尚在调试之中，一次在使用过程中对你造成的损失概不负责。");
		printf("\n    具体损失包括但不限于：");
		printf("\n    资料丢失，电脑黑屏，蓝屏或死机。");
		printf("\n    本程序的一切解释权归蒋鑫所有");
		printf("\n    copyright  @  蒋鑫(JX)");
		printf("\n\n");
		printf("Continue?(y/n)\n");
	    scanf("%s",a);
	    if(strncmp("n",a,1)==0)
			return 0;
	    else
			goto loop;
			};
   case 5: {
		printf("\n    本程序可以新建，存储，打开联系人信息。");
		printf("\n    若是打开联系人信息则信息必须按照固定格式：关系  姓名  性别  手机号码。其中姓名最好是以中文存储的。");
        printf("\n    本程序中使用大量中文提示符，所以建议在vc等支持中文的编译器中使用，否则会导致乱码等错误。");
		printf("\n    在存储和打开联系人信息文件时需要指出文件名，此时要注意输入文件拓展名，否则会存储或打开失败。");
		printf("\n    使用时请严格按照提示语操作，否则会造成您的信息受损。");
		printf("\n    本程序尚在调试阶段，出现错误在所难免，请勿吐糟！！");
		printf("\n    若果你对本程序有任何建议请发送到1027980638@qq.com.");
		printf("\n\t\t\t\t   by 蒋鑫(JX)\n");
		printf("Continue?(y/n)\n");
	    scanf("%s",a);
	    if(strncmp("n",a,1)==0)
			return 0;
	    else
			goto loop;
			};
   case 6: break;
   default:goto loop;
	}
	}while(m!=6);
	return 0;
}
/*void f_new(void)
　　新建文件函数。功能：清空data数组中数据(例如：将全局变量count置为0表示数组中有效记录数量位0),提示用户进入建立新记录的输入状态，
给出每一输入项目的提示信息，接收用户输入的数据并保存到data数组中。data数组中每增加一条记录count变量自增1。
允许用户一次性输入多条记录，输入结束后返回上层函数。*/
void f_new(void)
{
	printf("You can input the data following the reference.\n");
	printf("How many pieces of your data?\n");
	scanf("%d",&n);
	for(count=1;count<=n;count++)
	{
		printf("\n\nNow you can input the data %ld\n",count);
		printf("Please input the type:\n");
		printf("When you input the type you can use:\n1 for 亲属\n2 for 朋友\n3 for 同事\n4 for 同学\n5 for 其它\nOthers for 无效记录\n");
		scanf("%d",&data[count].type);
		printf("Please input the name:\n(In Chinese!)\n");
		if(count==1)
			printf("If you don't understand why you should input in Chinese,please input why,otherwise input according reference:\n");
		scanf("%s",data[count].name);
		if(strncmp("why",data[count].name,3)==0)
		{
			printf("其实这是由于我自己的技术能力有限，如果你输入英文名字的话，在以后的保存和输出时很难实现对齐功能，因为对于普通的中国人来说");
			printf("名字只是两个或者三个字（少数民族同胞除外），这样利用制表符很容易实现对齐功能，而用英文名字字母数量不同，很难对齐。");
			printf("\n现在可以输入了吧。用中文！！\n");
			scanf("%s",data[count].name);
		}
		printf("Please input the sex:\n");
		printf("When you input the sex you can input\nm for 男\nf for 女\n");
		scanf("%s",data[count].sex);
		printf("Please input the phone:\n");
		scanf("%s",data[count].phone);
	}
}
/*void f_save(void)
保存文件函数。功能：将data数组中全部有效记录（记录数保存在count中）保存到磁盘数据文件中(文件名及保存位置在运行程序时由用户输入)。
保存完毕后显示报告信息，返回上层函数。*/
void f_save(void)
{
	FILE *fp;
	char TYPE[20],SEX[10];
    printf("Input name of the file you want to save this data in:\n");
	scanf("%s",a);
	fp=fopen(a,"w");
	for(count=1;count<=n;count++)
	{
		switch(data[count].type){
		case 1:strcpy(TYPE,"亲属");break;
		case 2:strcpy(TYPE,"朋友");break;
		case 3:strcpy(TYPE,"同事");break;
		case 4:strcpy(TYPE,"同学");break;
		case 5:strcpy(TYPE,"其他");break;
		default:strcpy(TYPE,"无效");break;
		}
		if(strncmp(data[count].sex,"m",1)==0)
			strcpy(SEX,"男");
		else if(strncmp(data[count].sex,"f",1)==0)
			strcpy(SEX,"女");
		else
			strcpy(SEX,"未知");
		fprintf(fp,"%s\t%s\t%s\t%s\n",TYPE,data[count].name,SEX,data[count].phone);
	}
	fclose(fp);
	printf("You have saved the data successfully!\n");
}
/*void f_open(void)
打开文件函数。
功能：清空data数组(count变量置为0)。从指定盘的数据文件((文件名及保存位置在运行程序时由用户输入)中读入全部数据保存到data数组。
data数组每存入一条新记录count变量自增1 。将新读入的data数组中全部数据显示在屏幕上（一行显示一条记录）。按任意键则返回上层函数。*/
void f_open(void)
{
	FILE *fp;
	char TYPE[20],SEX[10];
	int m;
loop1:printf("Input the name of the file you want open:\n");
	scanf("%s",a);
	if((fp=fopen(a,"r"))==NULL)
	{
		printf("Cannot open the file!\n");
loop3:  printf("\n\n\n\n\n\n\n\n"
		"\t**********************************\n"
		"\t             1.继续               \n"
		"\t             2.返回               \n"
		"\t             3.退出               \n"
		"\t**********************************\n"
		"\t**********************************\n"
		"\tPlease choose the function:\n\n\n\n\n");
		scanf("%d",&m);
		switch(m){
		case 1:goto loop1; break;
		case 2:goto loop2;break;
		case 3:exit(1);
		default:goto loop3;
		}
	}
	if(n==0)
	{
		printf("Hao many pieces of data you want to open?\n");
		scanf("%d",&n);
	}
	printf("关系\t名字\t性别\t手机\n");
	for(count=1;count<=n;count++)
	{
		switch(data[count].type){
		case 1:strcpy(TYPE,"亲属");break;
		case 2:strcpy(TYPE,"朋友");break;
		case 3:strcpy(TYPE,"同事");break;
		case 4:strcpy(TYPE,"同学");break;
		case 5:strcpy(TYPE,"其他");break;
		case 6:strcpy(TYPE,"无效");break;
		}
		if(strncmp(data[count].sex,"m",1)==0)
			strcpy(SEX,"男");
		else if(strncmp(data[count].sex,"f",1)==0)
			strcpy(SEX,"女");
		else
			strcpy(SEX,"未知");
		fscanf(fp,"%s%s%s%s",TYPE,data[count].name,SEX,data[count].phone);
		printf("%s\t%s\t%s\t%s\n",TYPE,data[count].name,SEX,data[count].phone);
	}
	fclose(fp);
	n=0;
	printf("Continue?(y/n)\n");
	scanf("%s",a);
	if(strncmp("y",a,1)==0)
		;
	else
		exit(1);
loop2:;

}
