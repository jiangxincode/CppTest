#include<stdio.h>
#include<string.h>
#include<ctype.h>

int count1148(char a[], char w[][10], int n,int b[])
{
    int i,j,k,p;

    for(p=0; p<n; p++)
        for(i=0; a[i]!='\0'; i++)
        {
            for(k=0,j=i; w[p][k]!='\0'&&w[p][k]==a[j]; k++,j++);

            if(k>0&&w[p][k]=='\0'&&!isalpha(a[i-1]))
            {
                b[p]++;
                i=i+strlen(w[p]);
            }
        }

    return 0;
}
int main1148()
{
    char a[50]= {"this is a book, that is an apple"};
    char w[][10]= {"is","that"};
    int i,b[20]= {0};
    count1148(a,w,2,b);

    for(i=0; i<2; i++)
    {
        puts(w[i]);
        printf("%d\n",b[i]);
    }

    return 0;
}



