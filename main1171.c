#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

void f_new(void);
void f_save(void);
void f_open(void);

typedef struct
{
    int type;
    char name[20];
    char sex[2];
    char phone[20];
} PERSON;

PERSON data[200];
long count=0,n=0;
char a[20];
int main1171()
{
    puts("\n\n\n"
         "\t*************************************************\n"
         "\t*************************************************\n"
         "\t*******     Weclome to notebook     *************\n"
         "\t*************************************************\n"
         "\t*************************************************\n"
         "\t*******************  copyright @ jiangxin   *****\n"
         "\t*************************************************\n"
         "\t*************************************************\n"
         "\n\n\n");
    puts("Input e if you want exit, Otherwise ANY KEY:");
    scanf("%19s",a);

    if(!strncmp(a,"e",1))
    {
        return 0;
    }

    int m;

    do
    {
        puts("\n\n\n\n\n\n\n\n"
             "\t**********************************\n"
             "\t             1.��    ��           \n"
             "\t             2.��    ��           \n"
             "\t             3.��    ��           \n"
             "\t             4.��Ȩ˵��           \n"
             "\t             5.ʹ��˵��           \n"
             "\t             6.��    ��           \n"
             "\t**********************************\n"
             "\tPlease choose the function:\n\n\n\n\n");
        scanf("%11d",&m);

        while(m<1 || m>6)
        {
            printf("Error!\n");
            printf("Please input again\n");
            scanf("%11d",&m);
        };

        switch(m)
        {
        case 1:
            f_new();
            break;

        case 2:
            f_save();
            break;

        case 3:
            f_open();
            break;

        case 4:
        {
            puts("    ���������Ͼ���ѧ�����ѧ�빤��ѧԺ�Ľ���������");
            puts("    �����ʹ�ñ����򼴴����Ѿ���ȫͬ�ⱾԼ������������ʹ�á�");
            puts("    ������Ҫδ���������Ը��ƣ��޸ģ�����������");
            puts("    ����������ڸ��������о�ʹ�ã�ͬʱ���������ڵ���֮�У�һ����ʹ�ù����ж�����ɵ���ʧ�Ų�����");
            puts("    ������ʧ�����������ڣ�");
            puts("    ���϶�ʧ�����Ժ�����������������");
            puts("    �������һ�н���Ȩ�齯������");
            puts("    copyright  @  ����(JX)");
            puts("Continue?(y/n)");
            scanf("%19s",a);

            if(strncmp("n",a,1)==0)
                return 0;

            break;
        }

        case 5:
        {
            puts("    ����������½����洢������ϵ����Ϣ��");
            puts("    ���Ǵ���ϵ����Ϣ����Ϣ���밴�չ̶���ʽ����ϵ  ����  �Ա�  �ֻ����롣������������������Ĵ洢�ġ�");
            puts("    ��������ʹ�ô���������ʾ�������Խ�����vc��֧�����ĵı�������ʹ�ã�����ᵼ������ȴ���");
            puts("    �ڴ洢�ʹ���ϵ����Ϣ�ļ�ʱ��Ҫָ���ļ�������ʱҪע�������ļ���չ���������洢���ʧ�ܡ�");
            puts("    ʹ��ʱ���ϸ�����ʾ���������������������Ϣ����");
            puts("    ���������ڵ��Խ׶Σ����ִ����������⣬�������㣡��");
            puts("    ������Ա��������κν����뷢�͵�1027980638@qq.com.");
            puts("\t\t\t\t   by jiangxin");
            puts("Continue?(y/n)");
            scanf("%19s",a);

            if(strncmp("n",a,1)==0)
                return 0;

            break;
        };

        default:
            break;
        }
    }
    while(m != 6);

    return 0;
}
/**
�����½��ļ����������ܣ����data����������(���磺��ȫ�ֱ���count��Ϊ0��ʾ��������Ч��¼����λ0),��ʾ�û����뽨���¼�¼������״̬��
����ÿһ������Ŀ����ʾ��Ϣ�������û���������ݲ����浽data�����С�data������ÿ����һ����¼count��������1��
�����û�һ�������������¼����������󷵻��ϲ㺯����*/
void f_new(void)
{
    printf("You can input the data following the reference.\n");
    printf("How many pieces of your data?\n");
    scanf("%11ld",&n);

    for(count=1; count<=n; count++)
    {
        printf("\n\nNow you can input the data %ld\n",count);
        printf("Please input the type:\n");
        printf("1 for ����\n2 for ����\n3 for ͬ��\n4 for ͬѧ\n5 for ����\n");
        scanf("%11d",&data[count].type);
        printf("Please input the name:\n(In Chinese!)\n");

        if(count==1)
            printf("If you don't understand why you should input in Chinese,please input why,otherwise input according reference:\n");

        scanf("%19s",data[count].name);

        if(strncmp("why",data[count].name,3)==0)
        {
            printf("��ʵ�����������Լ��ļ����������ޣ����������Ӣ�����ֵĻ������Ժ�ı�������ʱ����ʵ�ֶ��빦�ܣ���Ϊ������ͨ���й�����˵");
            printf("����ֻ���������������֣���������ͬ�����⣩�����������Ʊ��������ʵ�ֶ��빦�ܣ�����Ӣ��������ĸ������ͬ�����Ѷ��롣");
            printf("\n���ڿ��������˰ɡ������ģ���\n");
            scanf("%19s",data[count].name);
        }

        printf("Please input the sex:\n");
        printf("m for ��\nf for Ů\n");
        scanf("%1s",data[count].sex);
        printf("Please input the phone:\n");
        scanf("%19s",data[count].phone);
    }
}
/**
�����ļ�����
���ܣ���data������ȫ����Ч��¼����¼��������count�У����浽���������ļ���(�ļ���������λ�������г���ʱ���û�����)��
������Ϻ���ʾ������Ϣ�������ϲ㺯����*/
void f_save(void)
{
    FILE *fp;
    char TYPE[20],SEX[10];
    printf("Input name of the file you want to save this data in:\n");
    scanf("%19s",a);
    fp=fopen(a,"w");

    for(count=1; count<=n; count++)
    {
        switch(data[count].type)
        {
        case 1:
            strcpy(TYPE,"����");
            break;

        case 2:
            strcpy(TYPE,"����");
            break;

        case 3:
            strcpy(TYPE,"ͬ��");
            break;

        case 4:
            strcpy(TYPE,"ͬѧ");
            break;

        default:
            strcpy(TYPE,"����");
            break;
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
/**
���ļ�������
���ܣ����data����(count������Ϊ0)����ָ���̵������ļ�((�ļ���������λ�������г���ʱ���û�����)�ж���ȫ�����ݱ��浽data���顣
data����ÿ����һ���¼�¼count��������1 �����¶����data������ȫ��������ʾ����Ļ�ϣ�һ����ʾһ����¼������������򷵻��ϲ㺯����*/
void f_open(void)
{
    FILE *fp;
    char TYPE[20],SEX[10];
    printf("Input the name of the file you want open:\n");
    scanf("%19s",a);

    if((fp=fopen(a,"r"))==NULL)
    {
        printf("Cannot open the file!\n");
    }

    printf("Hao many pieces of data you want to open?\n");
    scanf("%11ld",&n);
    printf("��ϵ\t����\t�Ա�\t�ֻ�\n");

    for(count=1; count<=n; count++)
    {
        switch(data[count].type)
        {
        case 1:
            strcpy(TYPE,"����");
            break;

        case 2:
            strcpy(TYPE,"����");
            break;

        case 3:
            strcpy(TYPE,"ͬ��");
            break;

        case 4:
            strcpy(TYPE,"ͬѧ");
            break;

        default:
            strcpy(TYPE,"����");
            break;
        }

        if(strncmp(data[count].sex,"m",1)==0)
            strcpy(SEX,"��");
        else if(strncmp(data[count].sex,"f",1)==0)
            strcpy(SEX,"Ů");
        else
            strcpy(SEX,"δ֪");

        fscanf(fp,"%19s%19s%1s%19s",TYPE,data[count].name,SEX,data[count].phone);
        printf("%s\t%s\t%s\t%s\n",TYPE,data[count].name,SEX,data[count].phone);
    }

    fclose(fp);
}
