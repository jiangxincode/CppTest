#include <iostream>
#include <cstring>
#include <cstdlib>

#include "hash.h"

using namespace std;

int HashTable::Find_Ins(const char * id)
{
    int i = FindPos(id),  j = i; 						//i是计算出来的散列地址

    while(ht[j].info != Empty && strcmp(ht[j].Element, id) != 0)
    {
        //冲突
        j = (j + 1) % TableSize;						//当做循环表处理, 找下一个空桶

        if(j == i) return -TableSize;					//转一圈回到开始点, 表已满, 失败
    }

    if(ht[j].info != Active)
    {
        //插入
        if(j > i)
        {
            for(int k = j; k > i; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            strcpy(ht[i].Element,id);
            ht[i].info = Active;  			//插入
        }
        else
        {
            HashEntry temp;
            temp.Element = ht[TableSize-1].Element;
            temp.info = ht[TableSize-1].info;

            for(int k = TableSize-1; k > i; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            strcpy(ht[i].Element,id);
            ht[i].info = Active;  			//插入

            for(int k=j; k>0; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            ht[0].Element = temp.Element;
            ht[0].info = temp.info;
        }
    }

    return j;
}

void HashTable :: HashSort()
{
    int n, i;
    char str[BUFSIZ];
    cin >> n >> str;

    for(i = 0; i < n; i++)
    {
        if(Find_Ins(str) == - TableSize)
        {
            cout << "表已满" << endl;
            break;
        }

        cin >> str;
    }

    for(i = 0; i < TableSize; i++)
        if(ht[i].info == Active) cout << ht[i].Element << endl;
}
