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
		   "\t********       ͨ      Ѷ      ¼      **********\n"
		   "\t*************                     ***************\n"
		   "\t*************************************************\n"
		   "\t*************************************************\n"
		   "\t*******     Weclome to notebook!!!     **********\n"
		   "\t*************************************************\n"
		   "\t*****             made by ���� (111150034)  **** \n"
		   "\t*************************************************\n"
		   "\t****************         �ؿ�Ժ���ذ�       *****\n"
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
		"\t             1.��    ��           \n"
		"\t             2.��    ��           \n"
		"\t             3.��    ��           \n"
		"\t             4.��Ȩ˵��           \n"
		"\t             5.ʹ��˵��           \n"
		"\t             6.��    ��           \n"
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
		printf("\n    ���������Ͼ���ѧ�����ѧ�빤��ѧԺ�Ľ���������");
		printf("\n    �����ʹ�ñ����򼴴����Ѿ���ȫͬ�ⱾԼ������������ʹ�á�");
        printf("\n    ������Ҫδ���������Ը��ƣ��޸ģ�����������");
		printf("\n    ����������ڸ��������о�ʹ�ã�ͬʱ���������ڵ���֮�У�һ����ʹ�ù����ж�����ɵ���ʧ�Ų�����");
		printf("\n    ������ʧ�����������ڣ�");
		printf("\n    ���϶�ʧ�����Ժ�����������������");
		printf("\n    �������һ�н���Ȩ�齯������");
		printf("\n    copyright  @  ����(JX)");
		printf("\n\n");
		printf("Continue?(y/n)\n");
	    scanf("%s",a);
	    if(strncmp("n",a,1)==0)
			return 0;
	    else
			goto loop;
			};
   case 5: {
		printf("\n    ����������½����洢������ϵ����Ϣ��");
		printf("\n    ���Ǵ���ϵ����Ϣ����Ϣ���밴�չ̶���ʽ����ϵ  ����  �Ա�  �ֻ����롣������������������Ĵ洢�ġ�");
        printf("\n    ��������ʹ�ô���������ʾ�������Խ�����vc��֧�����ĵı�������ʹ�ã�����ᵼ������ȴ���");
		printf("\n    �ڴ洢�ʹ���ϵ����Ϣ�ļ�ʱ��Ҫָ���ļ�������ʱҪע�������ļ���չ���������洢���ʧ�ܡ�");
		printf("\n    ʹ��ʱ���ϸ�����ʾ���������������������Ϣ����");
		printf("\n    ���������ڵ��Խ׶Σ����ִ����������⣬�������㣡��");
		printf("\n    ������Ա��������κν����뷢�͵�1027980638@qq.com.");
		printf("\n\t\t\t\t   by ����(JX)\n");
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
�����½��ļ����������ܣ����data����������(���磺��ȫ�ֱ���count��Ϊ0��ʾ��������Ч��¼����λ0),��ʾ�û����뽨���¼�¼������״̬��
����ÿһ������Ŀ����ʾ��Ϣ�������û���������ݲ����浽data�����С�data������ÿ����һ����¼count��������1��
�����û�һ�������������¼����������󷵻��ϲ㺯����*/
void f_new(void)
{
	printf("You can input the data following the reference.\n");
	printf("How many pieces of your data?\n");
	scanf("%d",&n);
	for(count=1;count<=n;count++)
	{
		printf("\n\nNow you can input the data %ld\n",count);
		printf("Please input the type:\n");
		printf("When you input the type you can use:\n1 for ����\n2 for ����\n3 for ͬ��\n4 for ͬѧ\n5 for ����\nOthers for ��Ч��¼\n");
		scanf("%d",&data[count].type);
		printf("Please input the name:\n(In Chinese!)\n");
		if(count==1)
			printf("If you don't understand why you should input in Chinese,please input why,otherwise input according reference:\n");
		scanf("%s",data[count].name);
		if(strncmp("why",data[count].name,3)==0)
		{
			printf("��ʵ�����������Լ��ļ����������ޣ����������Ӣ�����ֵĻ������Ժ�ı�������ʱ����ʵ�ֶ��빦�ܣ���Ϊ������ͨ���й�����˵");
			printf("����ֻ���������������֣���������ͬ�����⣩�����������Ʊ��������ʵ�ֶ��빦�ܣ�����Ӣ��������ĸ������ͬ�����Ѷ��롣");
			printf("\n���ڿ��������˰ɡ������ģ���\n");
			scanf("%s",data[count].name);
		}
		printf("Please input the sex:\n");
		printf("When you input the sex you can input\nm for ��\nf for Ů\n");
		scanf("%s",data[count].sex);
		printf("Please input the phone:\n");
		scanf("%s",data[count].phone);
	}
}
/*void f_save(void)
�����ļ����������ܣ���data������ȫ����Ч��¼����¼��������count�У����浽���������ļ���(�ļ���������λ�������г���ʱ���û�����)��
������Ϻ���ʾ������Ϣ�������ϲ㺯����*/
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
		case 1:strcpy(TYPE,"����");break;
		case 2:strcpy(TYPE,"����");break;
		case 3:strcpy(TYPE,"ͬ��");break;
		case 4:strcpy(TYPE,"ͬѧ");break;
		case 5:strcpy(TYPE,"����");break;
		default:strcpy(TYPE,"��Ч");break;
		}
		if(strncmp(data[count].sex,"m",1)==0)
			strcpy(SEX,"��");
		else if(strncmp(data[count].sex,"f",1)==0)
			strcpy(SEX,"Ů");
		else
			strcpy(SEX,"δ֪");
		fprintf(fp,"%s\t%s\t%s\t%s\n",TYPE,data[count].name,SEX,data[count].phone);
	}
	fclose(fp);
	printf("You have saved the data successfully!\n");
}
/*void f_open(void)
���ļ�������
���ܣ����data����(count������Ϊ0)����ָ���̵������ļ�((�ļ���������λ�������г���ʱ���û�����)�ж���ȫ�����ݱ��浽data���顣
data����ÿ����һ���¼�¼count��������1 �����¶����data������ȫ��������ʾ����Ļ�ϣ�һ����ʾһ����¼������������򷵻��ϲ㺯����*/
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
		"\t             1.����               \n"
		"\t             2.����               \n"
		"\t             3.�˳�               \n"
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
	printf("��ϵ\t����\t�Ա�\t�ֻ�\n");
	for(count=1;count<=n;count++)
	{
		switch(data[count].type){
		case 1:strcpy(TYPE,"����");break;
		case 2:strcpy(TYPE,"����");break;
		case 3:strcpy(TYPE,"ͬ��");break;
		case 4:strcpy(TYPE,"ͬѧ");break;
		case 5:strcpy(TYPE,"����");break;
		case 6:strcpy(TYPE,"��Ч");break;
		}
		if(strncmp(data[count].sex,"m",1)==0)
			strcpy(SEX,"��");
		else if(strncmp(data[count].sex,"f",1)==0)
			strcpy(SEX,"Ů");
		else
			strcpy(SEX,"δ֪");
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
