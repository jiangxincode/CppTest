/**
 * �ַ����������໥ת��
 */

#include <stdlib.h>
#include <stdio.h>

int main00021()
{
    char *str_num = "1234";
    int i_num = atoi(str_num);
    printf("string:%s,int:%d",str_num,i_num);

    return 0;
}

/**
 * �÷�����intת��char *�ǲ��Ƽ��ģ���isoȡ�������Ǵ󲿷�ϵͳ֧�֣�
 * ��Ҫ�ŵ��ǿ��Ըı����
 */
/*
int main00022()
{
    int i;
    char buffer [33];
    printf("Enter a number: ");
    scanf("%d",&i);
    itoa(i,buffer,10);
    printf("decimal: %s\n",buffer);
    itoa(i,buffer,16);
    printf("hexadecimal: %s\n",buffer);
    itoa(i,buffer,2);
    printf("binary: %s\n",buffer);
    return 0;
}
*/

/**
 * ��֪��0�㿪ʼ������(seconds) ��������ַ���"H:M:S",  ����H��Сʱ, M�����ӣ�S����
 */
int main00023()
{
    int H, M, S,seconds;
    char ctime[10];
    char *time_str;
    puts("Input the seconds");
    scanf("%d",&seconds);
    H=seconds/3600;
    M=(seconds%3600)/60;
    S=(seconds%3600)%60;
    sprintf(ctime, "%d:%d:%d", H, M, S); // ������ת�����ַ���
    time_str=ctime;
    puts(time_str);
    //��sprintf��Ӧ���� sscanf ����, ���Խ��ַ���ת��������.
    char str[] = "15.455";
    int i;
    float fp;
    sscanf(str, "%d", &i); // ���ַ���ת��������   i = 15
    sscanf(str, "%f", &fp); // ���ַ���ת���ɸ����� fp = 15.455000
    printf("Integer: = %d ", i+1);
    printf("Real: = %f ", fp+1);
    return 0;
}

int main0002()
{
    main00023();
    return 0;
}
