#include <stdio.h>
#include <time.h>

// 该算法很容易理解，但是效率不算特别高，在我的机器上的测试结果为：The total time is: 28.566000
int is2Power1(long unsigned int num)
{
    long unsigned int i;
    for(i=1;i<=num;i*=2)
    {
        if(i == num)
        {
             return 1;
        }

    }
    return 0;
}

// 有人提出，其中的i*=2，可以用i<<=1来替换，
// 在我的机器上的测试结果为：The total time is: 27.821000，我们发现仅仅提高了不到一秒，基本可以忽略不计。
int is2Power2(long unsigned int num)
{
    long unsigned int i;
    for(i=1;i<=num;i<<=1)
    {
        if(i == num)
        {
             return 1;
        }

    }
    return 0;
}

// 我们可以采取另一种思路，让i从num开始每次除2来判断，如果余数不为0立即返回，这样能会快判断出那些不符合条件的值，这样便能加快判断速度。
// 这种算法在我的机器上的测试结果为：The total time is: 3.958000，可以看出效率提高了近8倍。
int is2Power3(long unsigned int num)
{
    long unsigned int i;
    for(i=num;i>=1;i/=2)
    {
        if(i==1)
            return 1;
        else if(i%2 != 0)
        {
             return 0;
        }
    }
    return 1;
}

// 由于2的n次方的数二进制表示是第1位为1，其余为0，而x-1（假如x为2的n次方）得到的数的二进制表示恰恰是第1位为0，其余为1，两者相与，得到的结果就为0，否则结果肯定不为0。
// 在我的机器上的测试结果为：The total time is: 1.484000
int is2Power4(long unsigned int num)
{
    return ((num & (num-1))==0)?1:0;
}

// 也有一个类似的算法，原理类似， 这种算法在我的机器上的测试结果为：The total time is: 1.503000
int is2Power5(long unsigned int num)
{
    return ((num & (~num+1))==num)?1:0;
}


// 判断某个数据是否为2的n次方（1,2,4,8,16...）。例如如果用户输入的不是2^n，则要求用户重新输入
int main()
{
    long unsigned int i;
    clock_t start,end;
    start = clock();
    for(i=1;i<100000000;i++)
    {
        if(is2Power5(i))
        {
            printf("%ld\n",i);
        }
    }
    end =clock();
    printf("The total time is: %lf",((double)(end-start))/CLOCKS_PER_SEC);
    return 0;
}

