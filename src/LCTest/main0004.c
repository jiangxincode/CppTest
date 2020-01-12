#include <stdio.h>
#include <stdlib.h>

#define NUMBER 10

int main()
{
        int i,a[NUMBER];
        int *p=a;
        FILE *fp;
        if((fp=fopen("test","w"))==NULL)
        {
                printf("Open Error!!\n");
                exit(0);
        }
        printf("Please input 10 int numbers:\n");
        for(i=0; i<NUMBER; i++)
        {
                scanf("%d",&a[i]);
        }
        for(i=0; i<NUMBER; i++)
        {
                fprintf(fp,"%d\t",*(p+i));
                printf("%d\t",a[i]);
        }
        printf("\n");
        fclose(fp);
        return 0;
}
