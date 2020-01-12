#include <stdio.h>
#include <string.h>

#define N 5

struct address
{
    int no;
    char name[10];
    char phone[15];
};
int delphone(char delname[ ], struct address list[])
{
    int i;

    for(i=0; i<N; i++)
        if(strcmp(list[i].name,delname)==0)
        {
            break;
        }

    if(i<N)
    {
        for(int j=i; j<N; j++)
        {
            list[j]=list[j+1];
        }

        return N-1;
    }

    return N;
}
int main(void)
{
    struct address list[N]= {{1,"zhang","2301"},{2,"zhao","2302"},{3,"liu","2303"},
        {4,"li","2304"}, {5,"sun", "2305"}
    };
    int k;
    char delname[10];
    printf("Please input the name of deleting:");
    fgets(delname,10,stdin);
    k=delphone(delname, list);

    if(k<N)
    {
        printf("The information after deleting:\n");

        for(int i=0; i<k; i++)
        {
            printf("%5d%15s%15s\n", list[i].no, list[i].name, list[i].phone);
        }
    }
    else
    {
        printf("Not found \n");
    }

    return 0;
}
