#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/** \brief 把一个字符串中的字符从小写转为大写
 *
 * \param des 目标字符串
 * \param src 源字符串
 * \return 正常情况下返回指向目标字符串的指针，否则返回NULL
 *
 */

char* strltou(char *des, const char *src)
{
    if((des==NULL) || (src==NULL))
    {
        return NULL;
    }
    char *p_des = des;
    const char *p_src = src;
    for(; *p_src!='\0'; p_src++,p_des++)
    {
        if((*p_src>='a') && (*p_src<='z'))
        {
            *p_des = *p_src-'a'+'A';
        }
        else
        {
            *p_des = *p_src;
        }
    }
    *p_des = '\0';
    return des;
}

/** \brief 把一个字符串中的字符从小写转为大写
 *
 * \param des 目标字符串
 * \param src 源字符串
 * \return 正常情况下返回指向目标字符串的指针，否则返回NULL
 *
 */

char* strutol(char *des, const char *src)
{
    if((des==NULL) || (src==NULL))
    {
        return NULL;
    }
    char *p_des = des;
    const char *p_src = src;
    for(; *p_src!='\0'; p_src++,p_des++)
    {
        if((*p_src>='A') && (*p_src<='Z'))
        {
            *p_des = *p_src-'A'+'a';
        }
        else
        {
            *p_des = *p_src;
        }
    }
    *p_des = '\0';
    return des;
}


/** \cond */
int main0015()
{
    char source[1024];
    printf("Please input a string:\n");
    scanf("%1023s",source);
    char *target = (char *)malloc(sizeof(source));
    //strltou(target,source);
    strutol(target,source);
    printf("The result is:\n%s\n",target);
    return 0;
}
/** \endcond */

