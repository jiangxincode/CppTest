/*
�������ܡ�
 replaceword�����Ĺ����Ƕ�sָ����������洢��һ��Ӣ�ľ����е�ÿ�����������´���
 ��word_tab�����в��Ҹõ��ʣ���δ�ҵ��򱣳�ԭ���ʲ��䣻
 ���ҵ�����word_tab�����иõ��ʺ���ĵ�һ�������滻�����е�ԭ����
 ������õ�����word_tab�����е����һ���������õ�һ�������滻����
���������������н����
 �������ݣ�I accuse your mistakes.
 ��������I forgive your mistakes.
��Ҫ��
1��������ĿҪ�󼰳��������֮����߼���ϵ�Գ����еĴ�������޸ġ�
2���Ĵ�ʱ�������޸�����е�һ�������ݣ�����������
   �������������������Ԥ�����������������������䣬Ҳ����ɾȥ������䡣
*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
void replaceword(char s[])
{
    char word_tab[4][10]= {"sad","happy","accuse","forgive"};
    char t[10],tmp[80];
    int i,j,k,n;

    for(i=0; s[i]; i++)
    {
        for(j=i,k=0; isalpha(s[j]); k++,j++)
            t[k]=s[j];

        t[k]=0;

        if(k>0)
        {
            for(n=0; n<4; n++)
                if(strcmp(t,word_tab[n])==0)
                    break;

            if(n<4)
            {
                strcpy(tmp,s+i+strlen(t));
                strcpy(s+i,word_tab[(n+1)%4]);
                strcat(s,tmp);
                i=i+strlen(word_tab[(n+1)%4]);
            }
            else
                i=i+strlen(t);
        }
    }
}
int main1141()
{
    char line[80]="I accuse your mistakes.";
    replaceword(line);
    puts(line);
    return 0;
}
