#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "jiangxin.h"

int main0001()
{
    int i;
    /* Seed the random-number generator with current time so that
    * the numbers will be different every time we run.
    */
    srand((unsigned)time(NULL));

    /* Display 10 numbers. */
    for(i = 0; i < 10; i++)
        printf("%6d\n", rand());

    return 0;
}

