/**
 * 2015 ����Ͱ� �����з�����ʦ ���߱���
 * Longest Common String ������Ӵ�
 * ����һ��query��һ��text
 * Ҫ����text���ҳ���ͬ����˳������������query�е���������еĳ��ȡ�
 * ���磬 queryΪ��acbac����textΪ��acaccbabb����
 * ��ôtext�еġ�cba��Ϊ�������������query�е���ĸ���У�
 * ��ˣ����ؽ��Ӧ��Ϊ�䳤��3
 */

#include <iostream>
#include <string>

#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

int LCS1(const string& text, const string& query)
{
    string::size_type len = 0;

    for(string::size_type i=0; i<query.length(); i++)
    {
        for(string::size_type j=query.length()-1; j>i; j--)
        {
            string temp = query.substr(i,j-i+1);

            if(text.find(temp) != string::npos)
            {
                if((j-i)>len)
                {
                    len = j - i + 1; //i��jλ��֮�й���(j-i+1)��Ԫ��
                }
            }
        }
    }
    return len;
}


/**
 * �㷨�Ļ���˼�룺���þ���Խ�ԭ����ʵ��
 * ���ַ�ƥ���ʱ�򣬲��Ǽ򵥵ĸ���ӦԪ�ظ���1�����������Ͻ�Ԫ�ص�ֵ��1
 * ��������Ǳ�������Ǿ�����ֵ����Ԫ�ص�λ�ã��ھ������ɵĹ��������ж�
 * ��ǰ���ɵ�Ԫ�ص�ֵ�ǲ������ģ��ݴ����ı��Ǳ�����ֵ����ô��������ɵ�ʱ
 * ���ƥ���Ӵ���λ�úͳ��Ⱦ��Ѿ������ˡ�

 * ����
 * �ַ���1��21232523311324
 * �ַ���2��312123223445
 * ����c�ı仯���Ϊ��
 * 0 0 1 0 1 0 1 1 0 0 0 0
 * 0 1 0 2 0 0 0 0 0 0 0 0
 * 0 0 2 0 3 0 1 1 0 0 0 0
 * 1 0 0 0 0 4 0 0 2 0 0 0
 * 0 0 1 0 1 0 5 1 0 0 0 0
 * 0 0 0 0 0 0 0 0 0 0 0 1
 * 0 0 1 0 1 0 1 1 0 0 0 0
 * 1 0 0 0 0 2 0 0 2 0 0 0
 * 1 0 0 0 0 1 0 0 1 0 0 0
 * 0 2 0 1 0 0 0 0 0 0 0 0
 * 0 1 0 1 0 0 0 0 0 0 0 0
 * 1 0 0 0 0 1 0 0 1 0 0 0
 * 0 0 1 0 1 0 2 1 0 0 0 0
 * 0 0 0 0 0 0 0 0 0 1 1 0
 * ����14����1�ĳ��ȣ�����12����2�ĳ��ȣ�
 * ��Ӵ�Ϊ:21232
 */

int LCS2(const char left[],const char right[],int &pos)
{
    int arr[strlen(right)];
    int len = 0;

    for(size_t i=0; i<strlen(left); i++)
    {
        for(int j=strlen(right)-1; j>=0; j--) //�˴�����ʹ��size_t
        {
            if(left[i] == right[j])
            {
                if(i==0||j==0)
                    arr[j]=1;
                else
                {
                    arr[j]=arr[j-1]+1;
                }
            }
            else
                arr[j] = 0;

            if(arr[j] > len)
            {
                len=arr[j];
                pos = j;
            }
        }
    }

    pos = pos-len+1;
    return len;
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

int main05423()
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

int main0542()
{
    cout << LCS1("hello","llohghdfja") << endl;

    int pos;
    cout << LCS2("hello","llohghdfja",pos) << endl;
    cout << pos << endl;
    return 0;
}
