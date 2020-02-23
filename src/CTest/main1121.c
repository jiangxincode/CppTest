#include <stdio.h>
#include <math.h>

static int search(int x[],int low,int high,int key)
{
    while(low<=high)
    {
        int mid=(low+high)/2;

        if(x[mid]==key)
        {
            return mid;
        }
        else if(key<x[mid])
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }

    return -1;
}
int main(void)
{
    int xx[]= {5,23,28,34,43,45,56,60,67,90},i,key;
    printf("Input an int number:\n");
    scanf("%11d",&key);
    i=search(xx,0,9,key);

    if(i==-1)
    {
        printf("not found!\n");
    }
    else
    {
        printf("%d\n",i);
    }

    return 0;
}




