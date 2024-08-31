/**
 * 字符串加解密
 * 题目描述
 * 1、对输入的字符串进行加解密，并输出。
 * 2加密方法为：
 * 当内容是英文字母时则用该英文字母的后一个字母替换，同时字母变换大小写,如字母a时则替换为B；字母Z时则替换为a；
 * 当内容是数字时则把该数字加1，如0替换1，1替换2，9替换0；
 * 其他字符不做变化。
 * 3、解密方法为加密的逆过程。
 *
 * 接口描述：
 *     实现接口，每个接口实现1个基本操作：
 * void Encrypt (char aucPassword[], char aucResult[])：在该函数中实现字符串加密并输出
 * 说明：
 * 1、字符串以\0结尾。
 * 2、字符串最长100个字符。
 *
 * int unEncrypt (char result[], char password[])：在该函数中实现字符串解密并输出
 * 说明：
 * 1、字符串以\0结尾。
 *     2、字符串最长100个字符。
 *
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream>

//1、对输入的字符串进行加解密，并输出。
//
//2加密方法为：
//当内容是英文字母时则用该英文字母的后一个字母替换，同时字母变换大小写,如字母a时则替换为B；字母Z时则替换为a；
//当内容是数字时则把该数字加1，如0替换1，1替换2，9替换0；
//其他字符不做变化。
//
//3、解密方法为加密的逆过程。


int Encrypt (char password[], char result[])
{
    /* 代码在这里实现 */
    for (int i=0;i<strlen(password);i++)
    {
        if (isdigit(password[i]))
        {
            result[i] = '0' + (password[i]-'0'+1) % 10;
        }
        else if (isupper(password[i]))
        {
            if (password[i] == 'Z')
            {
                result[i] = 'a';
            }
            else
            {
                result[i] = password[i] + 1 - 'A' + 'a';
            }
        }
        else if (islower(password[i]))
        {
            if(password[i] == 'z')
            {
                result[i] = 'A';
            }
            else
            {
                result[i] = password[i] + 1 - 'a' + 'A';
            }
        }
        else
        {
            result[i] = password[i];
        }
    }
    result[strlen(password)] = '\0';

    return 0;
}

int unEncrypt (char result[], char password[])
{
    /* 代码在这里实现 */
    for (int i=0;i<strlen(result);i++)
    {
        if (isdigit(result[i]))
        {
            password[i] = '0' + (result[i]-'0'-1+10) % 10;
        }
        else if (isupper(result[i]))
        {
            if (result[i] == 'A')
            {
                password[i] = 'z';
            }
            else
            {
                password[i] = result[i] - 1 - 'A' + 'a';
            }
        }
        else if (islower(result[i]))
        {
            if(result[i] == 'a')
            {
                password[i] = 'Z';
            }
            else
            {
                password[i] = result[i] - 1 - 'a' + 'A';
            }
        }
        else
        {
            password[i] = result[i];
        }
    }
    password[strlen(result)] = '\0';

    return 0;
}

int main()
{
    char password[] = "Huawei1234";
    char excepted[] = "iVBXFJ2345";
    char actual[101];

    Encrypt (password, actual);
    std::cout << (0 == strcmp(actual, excepted)) << std::endl;

    char UnEncryptPassword[101];

    unEncrypt (actual, UnEncryptPassword);
    std::cout << (0 == strcmp(UnEncryptPassword, password)) << std::endl;


    return 0;
}

