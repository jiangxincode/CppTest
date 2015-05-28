#ifndef _SOMETHING_H
#define _SOMETHING_H

#define STRU struct student
#define KEY age
//#define KEY name                                             /* 调用哈希函数需要的宏*/
#define NULLTag "\0"
#define DELTag "1\0"
#define HashSize 29
struct student                                               /* 定义存放学生信息的结构体*/
{
    int num;
    char name[8];
    char sex;
    int age;
};
typedef struct student ElemType;
typedef struct student* ElemTypeP;
typedef ElemType hashlist[HashSize];
typedef char KeyType[8];

int hashdel(hashlist HT,int m,ElemType a);
int hashins(hashlist HT,int m,ElemType a);
int hashsch(hashlist HT,int m,KeyType a);
int hashpos(char *str,int i,int m);
unsigned int hashk(char *str,int i);

#endif // _SOMETHING_H

