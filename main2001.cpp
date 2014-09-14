/***********************************************
ChineseWordSegmentation
���ķִ�ʹ�����������ж�
��Ŀ¼�µ�word.txt�����ĴʵĴʵ��ļ�
�����ͬһĿ¼�µ�article.txt���зָ�
����ʵ��:��һ����������hash����в��ң�֮�����ɭ�ֵ�����
***********************************************/

#include <stdio.h>
#include <malloc.h>

#define MAXVALUE 65536
#define PATHLENGTH 50
#define MAXWORDLENGTH 60

void dic_init();
void free_hash();/*�ͷ�hash�ͺ���ĸ�*/
void file_split(const char *filename);

typedef struct Forest //the structure for forest
{
    long int value;
    struct Forest *child, *sibling; //��Ů�ڵ���ֵܽڵ�
    short int is_Chinese; //���Ĵʵı��
} Forest;

Forest *HashTable[MAXVALUE] = {NULL}; //��һ���ֵĸ����������洢

Forest *search_charactor(Forest *root, int value) //�ڴ˲�������ֵĲ���
{
    if(root == NULL)
        return root;
    else
    {
        root = root->child;
        while(root && (root->value != value))
            root = root->sibling;
        return root;
    }
}
Forest *insert_charactor(Forest *root, int value)
{
    Forest *tmpcell, *tmp;
    if(root->child == NULL)
    {
        tmpcell = (Forest *)malloc(sizeof(Forest));
        tmpcell->value = value;
        tmpcell->child = NULL;
        tmpcell->sibling = NULL;
        //tmpcell->eof=0;
        root->child = tmpcell;
        return tmpcell;
    }
    else
    {
        tmp = root->child;
        while(tmp && (tmp->value != value)) //���ֵܽڵ����
        {
            root = tmp;
            tmp = tmp->sibling;
        }
        if(tmp)return tmp; //�ҵ�����ͬ�ַ�
        else
        {
            tmpcell = (Forest *)malloc(sizeof(Forest));
            tmpcell->value = value;
            tmpcell->child = NULL;
            tmpcell->sibling = NULL;
            root->sibling = tmpcell;
            return tmpcell;
        }
    }
}
/**
�ʵ��ʼ���������ֵ�һ����hash���Ҳ��ҵ�����������ɭ�ֽ��в���
**/
void dic_init()
{
    FILE *fp;
    int i;
    unsigned char buffer[MAXWORDLENGTH] = {0};
    long int value;
    Forest *root, *tmpcell;

    char p_dic_path[PATHLENGTH];
    puts("Input the directory of the dictionary");
    scanf("%s", p_dic_path);
    fp = fopen(p_dic_path, "r");
    while(NULL == fp)
    {
        perror("Can't find the dictionary\n");
        scanf("%s", p_dic_path);
        fp = fopen(p_dic_path, "r");
    }

    while(!feof(fp))
    {
        fscanf(fp, "%s\n", buffer);
        //printf("%s\n",buffer);
        if(128 > buffer[0])
        {
            value = buffer[0]*256;
        }
        else
        {
            value = buffer[0]*256+buffer[1];
        }
        if(HashTable[value] == NULL)
        {

            tmpcell = (Forest *)malloc(sizeof(Forest));

            tmpcell->value = value;

            tmpcell->child = NULL;
            tmpcell->sibling = NULL;
            HashTable[value] = tmpcell;
        }
        if(128 > buffer[0])
        {
            tmpcell->is_Chinese = 0;
            i = 1;
        }
        else
        {
            tmpcell->is_Chinese = 1;
            i = 2;
        }
        root = HashTable[value];


        //printf("%d %d\n",buffer[i],buffer[i]);
        while(1)
        {
            if(0 == buffer[i]) //end of the data item
                break;
            else if(128 > buffer[i]) //a ASCII charactor
            {
                value = buffer[i] * 256;
                root = insert_charactor(root, value);
                root->is_Chinese = 0;
                i++;
            }
            else //a Chinese charactor
            {
                value = buffer[i] * 256 + buffer[i + 1];
                root = insert_charactor(root, value);
                root->is_Chinese = 1;
                i += 2;
            }
        }
    }
    fclose(fp);

}
void free_forest(Forest *root)/*�ݹ��ͷ�ɭ����ڵ�*/
{
    Forest *tmp;
    if(root == NULL) return ;
    else
    {
        tmp = root->sibling;
        free_forest(root->child);
        free(root);
        free_forest(tmp);
    }
}
void free_hash()/*�ͷ�hash�ͺ���ĸ�*/
{
    for(int i=0;i<MAXVALUE;i++)
    {
        free_forest(HashTable[i]);
    }
}
void file_split(const char *filename)
{
    int lasteof = 0; //��¼���һ��ƥ��Ĵ�
    int str_pos = 0; //str��λ��
    int value;
    unsigned char str[20] = {0}, ch[2] = {0};
    Forest *root;
    FILE *fp = fopen(filename, "r");
    printf("filename :%s\n", filename);
    if(fp == NULL)
    {
        printf("No file\n");
        return ;
    }
    while(!feof(fp))
    {
        ch[0] = fgetc(fp);
        if(ch[0] < 128) //�������ַ�ֱ�����,����ǰ��ƥ������Ĵ����
        {
            str[str_pos] = 0;
            printf("%s", str);
            str_pos = 0;
            putchar(ch[0]);
        }
        else //�����ַ���Ҫ�������ֽ�
        {
            ch[1] = fgetc(fp);
            value = ch[0] * 256 + ch[1];
            if(str_pos == 0) //���Ĵʵ�����
            {
                root = HashTable[value];
                str[str_pos++] = ch[0];
                str[str_pos++] = ch[1];
                lasteof = 2;
            }
            else //���Ĵʵķ�����
            {
                root = search_charactor(root, value);
                if(root == NULL) //û��ƥ��ô�
                {
                    str[lasteof] = 0;
                    printf("[%s]", str);
                    if(str_pos != 2) //����������Ĵʵĵڶ�����
                    {
                        if(str_pos == lasteof) //��������Ĵʽ��������ַ��������һ�������ַ�
                            fseek(fp, -2, SEEK_CUR);
                        else //��������Ĵʰ���ASCII�ַ��������ĩβ���ɸ�Ӣ���ַ�
                            fseek(fp, -(str_pos - lasteof), SEEK_CUR);
                    }
                    else //��������Ĵʵĵڶ�����
                        fseek(fp, -2, SEEK_CUR);
                    str_pos = 0;
                }
                else //��ƥ��ֱ�Ӵ洢
                {
                    str[str_pos++] = ch[0];
                    str[str_pos++] = ch[1];
                    if(root->is_Chinese == 1) /*����һ�����Ĵʣ���¼������λ��*/
                        lasteof = str_pos;
                }
            }
        }
    }
    fclose(fp);
    return ;
}
int main2001()
{
    const char *filename = "data/article.txt";
    dic_init();
    file_split(filename);
    free_hash();
    getchar();
    return 0;
}

