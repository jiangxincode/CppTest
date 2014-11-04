/***********************************************
ChineseWordSegmentation
中文分词使用整数进行判断
在目录下的word.txt是中文词的词典文件
程序对同一目录下的article.txt进行分割
程序实现:第一个中文字用hash表进行查找，之后进行森林的搜索
***********************************************/

#include <stdio.h>
#include <malloc.h>

#define MAXVALUE 65536
#define PATHLENGTH 50
#define MAXWORDLENGTH 60

void dic_init();
void free_hash();/*释放hash和后面的根*/
void file_split(const char *filename);

typedef struct Forest //the structure for forest
{
    long int value;
    struct Forest *child, *sibling; //子女节点和兄弟节点
    short int is_Chinese; //中文词的标记
} Forest;

Forest *HashTable[MAXVALUE] = {NULL}; //第一个字的根结点用数组存储

Forest *search_charactor(Forest *root, int value) //在此层进行文字的查找
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

        while(tmp && (tmp->value != value)) //沿兄弟节点遍历
        {
            root = tmp;
            tmp = tmp->sibling;
        }

        if(tmp)return tmp; //找到了相同字符
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
词典初始化：中文字第一层用hash查找并找到根，后面用森林进行查找
**/
void dic_init()
{
    FILE *fp;
    int i;
    unsigned char buffer[MAXWORDLENGTH] = {0};
    long int value;
    Forest *tmpcell;
    char p_dic_path[PATHLENGTH];
    puts("Input the directory of the dictionary");
    scanf("%49s", p_dic_path);
    fp = fopen(p_dic_path, "r");

    while(NULL == fp)
    {
        perror("Can't find the dictionary\n");
        scanf("%49s", p_dic_path);
        fp = fopen(p_dic_path, "r");
    }

    while(!feof(fp))
    {
        fscanf(fp, "%59s\n", buffer);

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

        Forest *root = HashTable[value];

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
void free_forest(Forest *root)/*递归释放森令各节点*/
{
    if(root == NULL) return ;
    else
    {
        Forest *tmp = root->sibling;
        free_forest(root->child);
        free(root);
        free_forest(tmp);
    }
}
void free_hash()/*释放hash和后面的根*/
{
    for(int i=0; i<MAXVALUE; i++)
    {
        free_forest(HashTable[i]);
    }
}
void file_split(const char *filename)
{
    int lasteof = 0; //记录最后一个匹配的词
    int str_pos = 0; //str的位置
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

        if(ch[0] < 128) //非中文字符直接输出,并将前面匹配的中文词输出
        {
            str[str_pos] = 0;
            printf("%s", str);
            str_pos = 0;
            putchar(ch[0]);
        }
        else //中文字符需要读两个字节
        {
            ch[1] = fgetc(fp);
            value = ch[0] * 256 + ch[1];

            if(str_pos == 0) //中文词的首字
            {
                root = HashTable[value];
                str[str_pos++] = ch[0];
                str[str_pos++] = ch[1];
                lasteof = 2;
            }
            else //中文词的非首字
            {
                root = search_charactor(root, value);

                if(root == NULL) //没有匹配该词
                {
                    str[lasteof] = 0;
                    printf("[%s]", str);

                    if(str_pos != 2) //如果不是中文词的第二个字
                    {
                        if(str_pos == lasteof) //如果该中文词仅含中文字符则仅回退一个中文字符
                            fseek(fp, -2, SEEK_CUR);
                        else //如果该中文词包含ASCII字符则仅回退末尾若干个英文字符
                            fseek(fp, -(str_pos - lasteof), SEEK_CUR);
                    }
                    else //如果是中文词的第二个字
                        fseek(fp, -2, SEEK_CUR);

                    str_pos = 0;
                }
                else //若匹配直接存储
                {
                    str[str_pos++] = ch[0];
                    str[str_pos++] = ch[1];

                    if(root->is_Chinese == 1) /*若是一个中文词，记录下最后的位置*/
                        lasteof = str_pos;
                }
            }
        }
    }

    fclose(fp);
    return ;
}
int main0019()
{
    const char *filename = "data/article.txt";
    dic_init();
    file_split(filename);
    free_hash();
    getchar();
    return 0;
}

