/*
windows.h头文件包含了其他windows头文件，这些头文件
的某些头文件也包含了其他头文件，这些头文件中最重要
的有：
WINDEF.H	基本形态定义
WINNT.H		支持Unicode的形态定义
WINBASE.H	Kernel函数
WINUSER.H	使用者界面函数
WINGDI.H	图形装置界面函数
windows.h是为mysql.h服务端，必须位于其之前
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
	int n;	//存储用户输入的编号
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
	printf("\t ** \t 1-显示所有图书信息					\n");
	printf("\t ** \t 2-添加图书信息						\n");
	printf("\t ** \t 3-修改图书信息						\n");
	printf("\t ** \t 4-删除图书信息						\n");
	printf("\t ** \t 5-查询图书信息						\n");
	printf("\t ** \t 6-退出								\n");
	printf("\t **************************************** \n");
	printf("\t ENTER YOUR CHOICE(1-6):");
}

void ShowAll()
{
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","db_books",0,NULL,0))
	{
		printf("\n\t 不能连接数据库！\n");
	}
	else
	{
		if(mysql_query(&mysql,"select * from tb_book"))
		{
			printf("\n\t查询 tb_book 数据表失败！\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t **************************************** \n");
				printf("\t             显示所有图书信息             \n");
				printf("\t **************************************** \n");
				printf("\t 图书编号		图书名		作者		出版社\n");
				printf("\t **************************************** \n");
				while(row=mysql_fetch_row(result))
				{
					fprintf(stdout,"\t %s		%s		%s		%s	\n",row[0],row[1],row[2],row[3]);
				}
				printf("\t **************************************** \n");
			}
			else
			{
				printf("\n\t	没有记录信息！\n");
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	inquire();
}

void inquire()
{
	printf("\t 显示主菜单？(y/n):");
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
		printf("\t               添加图书信息               \n");
		printf("\t **************************************** \n");
		if(mysql_query(&mysql,"select * from tb_book"))
			printf("\n\t 查询 tb_book 数据失败！\n");
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
						printf("\t 记录存在，按任意键继续！");
						_getch();
						mysql_free_result(result);
						mysql_close(&mysql);
						return;
					}
				}while(row=mysql_fetch_row(result));
			}
			printf("\t 图书名：");
			scanf_s("%s",&bookname);
			sql="insert into tb_book(ID,bookname,author,bookconcern) values(";	
			strcat_s(dest,sql);
			strcat_s(dest,"'");
			strcat_s(dest,id);
			strcat_s(dest,"','");
			strcat_s(dest,bookname);
			printf("\t 作者：");
			scanf_s("%s",&author);
			strcat_s(dest,"','");
			strcat_s(dest,author);
			printf("\t 出版社：");
			scanf_s("%s",&bookconcern);
			strcat_s(dest,"','");
			strcat_s(dest,bookconcern);
			strcat_s(dest,"')");
			printf("\t%s\n",dest);
			if(mysql_query(&mysql,dest)!=0)
			{
				fprintf(stderr,"不能插入记录！",mysql_error(&mysql));
			}
			else
			{
				printf("\t 插入成功！\n");
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
		printf("\t 不能连接数据库!\n");
	}
	else
	{
		printf("\t 请输入您要修改的图书编号：");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t% s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t 查询tb_book 数据表失败!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t 发现记录信息。是否显示？(y/n):");
				scanf_s("%s",ch);
				if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
				{
					printf("\t **************************************** \n");
					printf("\t               显示图书信息               \n");
					printf("\t **************************************** \n");
					printf("\t 图书编号		图书名		作者		出版社\n");
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
						printf("\t 图书名：");
						scanf_s("%s",&bookname);
						sql="update tb_book set bookname='";	
						strcat_s(dest1,sql);
						strcat_s(dest1,bookname);
						printf("\t 作者：");
						scanf_s("%s",&author);
						strcat_s(dest1,"',author='");
						strcat_s(dest1,author);
						printf("\t 出版社：");
						scanf_s("%s",&bookconcern);
						strcat_s(dest1,"',bookconcern='");
						strcat_s(dest1,bookconcern);
						strcat_s(dest1,"'where id='");
						strcat_s(dest1,id);
						strcat_s(dest1,"'");
						printf("\t%s\n",dest1);
						if(mysql_query(&mysql,dest1)!=0)
						{
							fprintf(stderr,"\t 不能修改记录！\n",mysql_error(&mysql));
						}
						else
						{
							printf("\t 修改成功！\n");
						}
					}
				}
			}
			else
				printf("\t 没有要修改的信息！\n");
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
		printf("\t 不能连接数据库！\n");
	else
	{
		printf("\t 请输入您要删除的图书编号：");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t %s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t 查询tb_book 数据表失败!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				printf("\t 发现记录信息。是否显示？(y/n):");
				scanf_s("%s",ch);
				if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
				{
					printf("\t **************************************** \n");
					printf("\t               显示图书信息               \n");
					printf("\t **************************************** \n");
					printf("\t 图书编号		图书名		作者		出版社\n");
					printf("\t **************************************** \n");
					while(row=mysql_fetch_row(result))
					{
						fprintf(stdout,"\t %s		%s		%s		%s\n",row[0],row[1],row[2],row[3]);
					}
					printf("\t **************************************** \n");
					printf("\t 是否删除?(y/n):");
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
							fprintf(stderr,"\t 不能删除记录！\n",mysql_error(&mysql));
						}
						else
						{
							printf("\t 删除成功！\n");
						}
					}
				}
			}
			else
				printf("\t 没有发现要删除的信息！\n");
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
		printf("\t 不能连接数据库！\n");
	else
	{
		printf("\t 请输入您要查询的图书编号:");
		scanf_s("%s",id);
		sql="select * from tb_book where id='";
		strcat_s(dest,sql);
		strcat_s(dest,id);
		strcat_s(dest,"'");
		printf("\t%s\n",dest);
		if(mysql_query(&mysql,dest))
		{
			printf("\t 查询tb_book 数据表失败!\n");
		}
		else
		{
			result=mysql_store_result(&mysql);
			if(mysql_num_rows(result)!=NULL)
			{
				
				printf("\t **************************************** \n");
				printf("\t               显示图书信息               \n");
				printf("\t **************************************** \n");
				printf("\t 图书编号		图书名		作者		出版社\n");
				printf("\t **************************************** \n");
				while(row=mysql_fetch_row(result))
				{
					fprintf(stdout,"\t %s		%s		%s		%s\n",row[0],row[1],row[2],row[3]);
				}
				printf("\t **************************************** \n");
			}
			else
				printf("\t 没有发现要删除的信息！\n");
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}