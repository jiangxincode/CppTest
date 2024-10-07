/*
windows.hͷ�ļ�����������windowsͷ�ļ�����Щͷ�ļ�
��ĳЩͷ�ļ�Ҳ����������ͷ�ļ�����Щͷ�ļ�������Ҫ
���У�
WINDEF.H	������̬����
WINNT.H		֧��Unicode����̬����
WINBASE.H	Kernel����
WINUSER.H	ʹ���߽��溯��
WINGDI.H	ͼ��װ�ý��溯��
windows.h��Ϊmysql.h����ˣ�����λ����֮ǰ
*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <mysql/mysql.h>

#pragma comment(lib,"libmysql.lib")

MYSQL mysql;
MYSQL_RES *result;
MYSQL_ROW row;
char ch[2];

void ShowAll();
void AddBook();
void ModifyBook();
void DeleteBook();
void QueryBook();
void showmenu();
void inquire();

int main()
{
	int n;	//�洢�û�����ı��
	mysql_init(&mysql);
	showmenu();
	scanf_s("%d",&n);
	while(n)
	{
		switch(n)
		{
		case 1:ShowAll();
			break;
		case 2:AddBook();
			break;
		case 3:ModifyBook();
			break;
		case 4:DeleteBook();
			break;
		case 5:QueryBook();
			break;
		case 6:exit(0);
		default:break;
		}
		scanf_s("%d",&n);
	}
	return 0;
}

void showmenu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t **************************************** \n");
	printf("\t *     Welcome To Jiang Books System    * \n");
	printf("\t **************************************** \n");
	printf("\t ** \t 1-��ʾ����ͼ����Ϣ					\n");
	printf("\t ** \t 2-���ͼ����Ϣ						\n");
	printf("\t ** \t 3-�޸�ͼ����Ϣ						\n");
	printf("\t ** \t 4-ɾ��ͼ����Ϣ						\n");
	printf("\t ** \t 5-��ѯͼ����Ϣ						\n");
	printf("\t ** \t 6-�˳�								\n");
	printf("\t **************************************** \n");
	printf("\t ENTER YOUR CHOICE(1-6):");
}

void ShowAll()
{
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
	{
		printf("\n\t �����������ݿ⣡\n");
	}
	else
	{
		if(mysql_query(&mysql,"select * from tb_book"))
		{
			printf("\n\t��ѯ tb_book ���ݱ�ʧ�ܣ�\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t **************************************** \n");
				printf("\t             ��ʾ����ͼ����Ϣ             \n");
				printf("\t **************************************** \n");
				printf("\t ͼ����		ͼ����		����		������\n");
				printf("\t **************************************** \n");
				while(row=mysql_fetch_row(result))
				{
					fprintf(stdout,"\t %s		%s		%s		%s	\n",row[0],row[1],row[2],row[3]);
				}
				printf("\t **************************************** \n");
			}
			else
			{
				printf("\n\t	û�м�¼��Ϣ��\n");
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	inquire();
}

void inquire()
{
	printf("\t ��ʾ���˵���(y/n):");
	scanf_s("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	{
		showmenu();
	}
	else
	{
		exit(0);
	}
}
void AddBook()
{
	unsigned __int64 rowcount;
	char id[10];
	/*
	char *bookname;
	char *author;
	char *bookconcern;
	*/
	char *sql;

	char bookname[50];
	char author[50];
	char bookconcern[50];
	char dest[300]={" "};
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
		printf("\n\t Can not connect db_books!\n");
	else
	{
		printf("\t **************************************** \n");
		printf("\t               ���ͼ����Ϣ               \n");
		printf("\t **************************************** \n");
		if(mysql_query(&mysql,"select * from tb_book"))
			printf("\n\t ��ѯ tb_book ����ʧ�ܣ�\n");
		else
		{
			result=mysql_store_result(&mysql);
			rowcount=mysql_num_rows(result);
			row=mysql_fetch_row(result);
			printf("\t ID:");
			scanf_s("%s",id);
			if(mysql_num_rows(result)!=NULL)
			{
				do
				{
					if(!strcmp(id,row[0]))
					{
						printf("\t ��¼���ڣ��������������");
						_getch();
						mysql_free_result(result);
						mysql_close(&mysql);
						return;
					}
				}while(row=mysql_fetch_row(result));
			}
			printf("\t ͼ������");
			scanf_s("%s",&bookname);
			sql="insert into tb_book(ID,bookname,author,bookconcern) values(";	
			strcat_s(dest,sql);
			strcat_s(dest,"'");
			strcat_s(dest,id);
			strcat_s(dest,"','");
			strcat_s(dest,bookname);
			printf("\t ���ߣ�");
			scanf_s("%s",&author);
			strcat_s(dest,"','");
			strcat_s(dest,author);
			printf("\t �����磺");
			scanf_s("%s",&bookconcern);
			strcat_s(dest,"','");
			strcat_s(dest,bookconcern);
			strcat_s(dest,"')");
			printf("\t%s\n",dest);
			if(mysql_query(&mysql,dest)!=0)
			{
				fprintf(stderr,"���ܲ����¼��",mysql_error(&mysql));
			}
			else
			{
				printf("\t ����ɹ���\n");
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	inquire();
}
void ModifyBook()
{
	char id[10];
	char *sql;
	char dest[300]={" "};
	char dest1[300]={" "};
	/*
	char *bookname;
	char *author;
	char *bookconcern;
	*/
	char bookname[50];
	char author[50];
	char bookconcern[50];
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
	{
		printf("\t �����������ݿ�!\n");
	}
	else
	{
		printf("\t ��������Ҫ�޸ĵ�ͼ���ţ�");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t% s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t ��ѯtb_book ���ݱ�ʧ��!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t ���ּ�¼��Ϣ���Ƿ���ʾ��(y/n):");
				scanf_s("%s",ch);
				if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
				{
					printf("\t **************************************** \n");
					printf("\t               ��ʾͼ����Ϣ               \n");
					printf("\t **************************************** \n");
					printf("\t ͼ����		ͼ����		����		������\n");
					printf("\t **************************************** \n");
					while(row=mysql_fetch_row(result))
					{
						fprintf(stdout,"\t %s		%s		%s		%s\n",row[0],row[1],row[2],row[3]);
					}
					printf("\t **************************************** \n");
					printf("\t Modify?(y/n):");
					scanf_s("%s",ch);
					if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
					{
						printf("\t ͼ������");
						scanf_s("%s",&bookname);
						sql="update tb_book set bookname='";	
						strcat_s(dest1,sql);
						strcat_s(dest1,bookname);
						printf("\t ���ߣ�");
						scanf_s("%s",&author);
						strcat_s(dest1,"',author='");
						strcat_s(dest1,author);
						printf("\t �����磺");
						scanf_s("%s",&bookconcern);
						strcat_s(dest1,"',bookconcern='");
						strcat_s(dest1,bookconcern);
						strcat_s(dest1,"'where id='");
						strcat_s(dest1,id);
						strcat_s(dest1,"'");
						printf("\t%s\n",dest1);
						if(mysql_query(&mysql,dest1)!=0)
						{
							fprintf(stderr,"\t �����޸ļ�¼��\n",mysql_error(&mysql));
						}
						else
						{
							printf("\t �޸ĳɹ���\n");
						}
					}
				}
			}
			else
				printf("\t û��Ҫ�޸ĵ���Ϣ��\n");
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}
void DeleteBook()
{
	char id[10];
	char *sql;
	char dest[300]={" "};
	char dest1[300]={" "};
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
		printf("\t �����������ݿ⣡\n");
	else
	{
		printf("\t ��������Ҫɾ����ͼ���ţ�");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t %s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t ��ѯtb_book ���ݱ�ʧ��!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t ���ּ�¼��Ϣ���Ƿ���ʾ��(y/n):");
				scanf_s("%s",ch);
				if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
				{
					printf("\t **************************************** \n");
					printf("\t               ��ʾͼ����Ϣ               \n");
					printf("\t **************************************** \n");
					printf("\t ͼ����		ͼ����		����		������\n");
					printf("\t **************************************** \n");
					while(row=mysql_fetch_row(result))
					{
						fprintf(stdout,"\t %s		%s		%s		%s\n",row[0],row[1],row[2],row[3]);
					}
					printf("\t **************************************** \n");
					printf("\t �Ƿ�ɾ��?(y/n):");
					scanf_s("%s",ch);
					if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
					{
						sql="delete from tb_book where id='";	
						strcat_s(dest1,sql);
						strcat_s(dest1,id);
						strcat_s(dest1,"'");
						printf("\t%s\n",dest1);
						if(mysql_query(&mysql,dest1)!=0)
						{
							fprintf(stderr,"\t ����ɾ����¼��\n",mysql_error(&mysql));
						}
						else
						{
							printf("\t ɾ���ɹ���\n");
						}
					}
				}
			}
			else
				printf("\t û�з���Ҫɾ������Ϣ��\n");
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}
void QueryBook()
{
	char id[10];
	char *sql;
	char dest[300]={" "};
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
		printf("\t �����������ݿ⣡\n");
	else
	{
		printf("\t ��������Ҫ��ѯ��ͼ����:");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t%s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t ��ѯtb_book ���ݱ�ʧ��!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				
				printf("\t **************************************** \n");
				printf("\t               ��ʾͼ����Ϣ               \n");
				printf("\t **************************************** \n");
				printf("\t ͼ����		ͼ����		����		������\n");
				printf("\t **************************************** \n");
				while(row=mysql_fetch_row(result))
				{
					fprintf(stdout,"\t %s		%s		%s		%s\n",row[0],row[1],row[2],row[3]);
				}
				printf("\t **************************************** \n");
			}
			else
				printf("\t û�з���Ҫɾ������Ϣ��\n");
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}