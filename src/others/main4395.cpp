/**
 * 字符转换Univesity
 * 简要描述
 * 字符替换，按照替换规则，将输入的字符串做转换;其它字符不作处理。
 * 详细描述：
 * 题目背景
 * 字母的替换规则，如下所示，A被E替换，B被C替换，依次类推。
 * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 * E C F A J K L B D G H I V W Z Y M N O P Q R S T U X
 * a b c d e f g h i j k l m n o p q r s t u v w x y z
 * e r w q t y g h b n u i o p s j k d l f a z x c v m
 *
 */
#include <stdlib.h>
#include <string.h>

#include "iostream"



char* CharReplace(char* pSourceChar)
{
    char *pEncryptUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *pEncryptLower = "abcdefghijklmnopqrstuvwxyz";
    char *pDecryptUpper = "ECFAJKLBDGHIVWZYMNOPQRSTUX";
    char *pDecryptLower = "erwqtyghbnuiopsjkdlfazxcvm";


    char* pResultChar = (char*)malloc(strlen(pSourceChar)+1);

    int index = 0;

    while(*(pSourceChar+index) != '\0')
    {
        if(strchr(pEncryptUpper, *(pSourceChar+index)) != NULL)
        {
            *(pResultChar+index) = *(pDecryptUpper + (*(pSourceChar+index) - 'A'));
        }
        else if(strchr(pEncryptLower, *(pSourceChar+index)) != NULL)
        {
            *(pResultChar+index) = *(pDecryptLower + (*(pSourceChar+index) - 'a'));
        }
        else
        {
            *(pResultChar+index) = *(pSourceChar+index);
        }
        index++;
    }

    *(pResultChar+index) = '\0';

    return pResultChar;
}

int main()
{
    char szSource[] = "Ilttabaje zaujljg#";
    char szResult[] = "Different meaning#";
    char* pResult = CharReplace(szSource);
    std::cout << (0 == strcmp(szResult, pResult)) << std::endl;
}
