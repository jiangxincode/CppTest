#include<stdio.h>
#include<math.h>

int f1104(int n,int count)
{
    if(count>5)
        return 1;
    else if(count<=5&&n%5!=1)
        return 0;
    else((count<=5) && (n%5==1));

    return f1104(4*n/5,count+1);
}
int main1104()
{
    int n,count=1;

    for(n=1;; n++)
    {
        if(f1104(n,count)==1)
        {
            printf("%d",n);
            break;
        }
    }

    return 0;
}



