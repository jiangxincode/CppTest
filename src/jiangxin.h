typedef enum TRANSFORM
{
    TOLOWER, //转成小写形式
    TOUPPER //转成大写形式
} TRANSFORM;

char jx_getchar(TRANSFORM option);
void jx_print_bye(void);
void jx_print_author_info(void);
void jx_swap_integer(int* i_num1,int* i_num2,short method);
int prime(int n);

