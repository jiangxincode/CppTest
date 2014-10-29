#include <stdbool.h>

#define _windows_ // For Windows OS

#ifndef _windows_
#define _linux // For Linux OS
#endif // _windows_

char jx_getchar(short option);
void jx_print_bye(void);
void jx_print_author_info(void);
void jx_swap_integer(int* i_num1,int* i_num2,short method);
int prime(int n);

