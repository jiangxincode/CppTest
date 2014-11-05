#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/** \cond */
int main0000()
{
    char*src="hello,world";
    char*dest=NULL;
    int len = strlen(src);
    dest = (char*)malloc(len);
    char* d = dest;
    char* s = &src[len-1];

    while(len-- != 0)
        *(d++) = *(s --);

    printf("%s",dest);
    return 0;
}
/** \endcond */
