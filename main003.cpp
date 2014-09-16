#include <iostream>
#include <string>
/*
����һ��query��һ��text������Сд��ĸ��ɡ�
Ҫ����text���ҳ���ͬ����˳������������query�е��������ĸ���еĳ��ȡ�
���磬 queryΪ��acbac����textΪ��acaccbabb����
��ôtext�еġ�cba��Ϊ�������������query�е���ĸ���У�
��ˣ����ؽ��Ӧ��Ϊ�䳤��3��
��ע�����Ч�ʡ�
2015 ����Ͱ� �����з�����ʦ ���߱���
*/
using namespace std;

int main0031()
{
    string text,query;
    cout << "Input text: " << endl;
    cin >> text;
    cout << "Input query: " << endl;
    cin >> query;
    string::size_type len = 0;
    for(string::size_type i=0; i<query.length(); i++)
    {
        for(string::size_type j=query.length()-1; j>i; j--)
        {
            string temp = query.substr(i,j);
            if(text.find(temp) != string::npos)
            {
                if((j-i)>len)
                {
                    len = j - i + 1; //i��jλ��֮�й���(j-i+1)��Ԫ��
                }
            }
        }
    }
    cout << len;
    return 0;
}


/*
�������ַ���������Ӵ�(LCS����)
(1)�㷨�Ļ���˼�룺���þ���Խ�ԭ����ʵ��
���ַ�ƥ���ʱ�򣬲��Ǽ򵥵ĸ���ӦԪ�ظ���1�����Ǹ��������Ͻ�Ԫ�ص�ֵ��һ��
������������Ǳ�������Ǿ�����ֵ����Ԫ�ص�λ�ã��ھ������ɵĹ��������ж�
��ǰ���ɵ�Ԫ�ص�ֵ�ǲ������ģ��ݴ����ı��Ǳ�����ֵ����ô��������ɵ�ʱ
���ƥ���Ӵ���λ�úͳ��Ⱦ��Ѿ������ˡ�
==========================================================================
����
�ַ���1��21232523311324
�ַ���2��312123223445
����c�ı仯���Ϊ��
 0 0 1 0 1 0 1 1 0 0 0 0
 0 1 0 2 0 0 0 0 0 0 0 0
 0 0 2 0 3 0 1 1 0 0 0 0
 1 0 0 0 0 4 0 0 2 0 0 0
 0 0 1 0 1 0 5 1 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 1
 0 0 1 0 1 0 1 1 0 0 0 0
 1 0 0 0 0 2 0 0 2 0 0 0
 1 0 0 0 0 1 0 0 1 0 0 0
 0 2 0 1 0 0 0 0 0 0 0 0
 0 1 0 1 0 0 0 0 0 0 0 0
 1 0 0 0 0 1 0 0 1 0 0 0
 0 0 1 0 1 0 2 1 0 0 0 0
 0 0 0 0 0 0 0 0 0 1 1 0
����14����1�ĳ��ȣ�����12����2�ĳ��ȣ�
��Ӵ�Ϊ:21232
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define M 100
char* LCS(char left[],char right[])
{
    int lenLeft = strlen(left),lenRight=strlen(right);
    char *c = (char *)malloc(lenRight), *p;//ע������Ҫд��char��,������int��,����������������ʱ���������      //����c��¼������ƥ�����
    int start,end,len; //start����������Ӵ�����ʼ�㣬end����������Ӵ�����ֹ��
    end=len=0;//len��ʾ������Ӵ��ĳ���

    for(int i=0; i<lenLeft; i++) //��1��ǰ���Ƚ�
    {
        for(int j=lenRight-1; j>=0; j--) //��2�Ӻ���ǰ�Ƚ�
        {
            if(left[i] == right[j])//Ԫ�����ʱ
            {
                if(i==0||j==0)
                    c[j]=1;
                else
                {
                    c[j]=c[j-1]+1;
                }
            }
            else
                c[j] = 0;

            if(c[j] > len)
            {
                len=c[j];
                end=j;
            }
        }
    }

    start=end-len+1;
    p =(char*)malloc(len+1);//����p��¼������Ӵ�

    for(int i=start; i<=end; i++)
    {
        p[i-start] = right[i];
    }

    p[len]='\0';
    return p;
}
void main0032()
{
    char str1[M],str2[M];
    printf("�������ַ���1:");
    gets(str1);
    printf("�������ַ���2:");
    gets(str2);
    printf("��Ӵ�Ϊ:");
    printf("%s\n",LCS(str1,str2));
}

void GetMaxCommStr(char *s1,char *s2,char *s3)//s1��s2 ΪҪ�Աȵ������ַ�����
{
    //s3�����洢���Ĺ����ַ���
    // char *s1=stra,  *s2=strb;
    char len1 = strlen(s1);
    char len2 = strlen(s2);
    char maxlen = 0;

    for(int i = 0; i < len1; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            if(s1[i] == s2[j])     //�ҵ��˵�һ����ȵ�
            {
                int as = i, bs = j, count = 1; //�����һ����ȵ��׵�ַ

                while((as+1<len1) && (bs+1<len2) && (s1[++as] == s2[++bs]))     //���������ȳ���
                    count++;

                if(count > maxlen)  //���������󳤶������
                {
                    maxlen = count;
                    //r1=i;             //�洢�������ַ�������ʼλ
                }
            }
        }
    }

    if(maxlen>0)  //�й������ַ���
    {
        for(int i=0; i<maxlen; i++)
        {
            *(s3+i)=*(s1+i);
        }

        printf("maxlen is %d\n",maxlen);
        printf("len1 is %d\n",len1);
        printf("len2 is %d\n",len2);
    }
}

int main0033()
{
    char strd[80]= {0};
    char stra[80]="iojhklgklskljklngvnkldg";
    char strb[80]="kldfjjsfgjlkjgldakfga;";
    GetMaxCommStr(stra,strb,strd);
    printf("stra is: %s\n",stra);
    printf("strb is: %s\n",strb);
    printf("strd is: %s\n",strd);
    return 0;
}

int main003()
{
    main0031();
    return 0;
}
