#define DefaultSize 1000
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
class HashTable
{
    //散列表类定义
public:
    enum KindOfEntry { Active, Empty, Deleted };			//表项分类 (活动 / 空 / 删)
    HashTable() : TableSize(DefaultSize)
    {
        ht = new HashEntry[TableSize];    //构造函数
    }
    ~HashTable()
    {
        delete [ ] ht;    //析构函数
    }
    int Find-Ins(const char * id);					//在散列表中搜索标识符id
    void HashSort();
private:
    struct HashEntry
    {
        //表项定义
        Type Element;								//表项的数据, 即表项的关键码
        KindOfEntry info;							//三种状态: Active, Empty, Deleted
        HashEntry() : info(Empty) { }					//表项构造函数, 置空
    };
    HashEntry *ht;								//散列表存储数组
    int TableSize;								//最大桶数
    int FindPos(string s) const
    {
        return atoi(*s) - 32;    //散列函数
    }
}

int HashTable :: Find-Ins(const char * id)
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
            while(int k = j; k > i; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            ht[i].Element = id;
            ht[i].info = Active;  			//插入
        }
        else
        {
            HashEntry temp;
            temp.Element = ht[TableSize-1].Element;
            temp.info = ht[TableSize-1].info;

            while(int k = TableSize-1; k > i; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            ht[i].Element = id;
            ht[i].info = Active;  			//插入

            while(int k=j; k>0; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            ht[0].Element = temp.Element;
            ht[0].info = temp.info;
        }

        return j;
    }

    void HashTable :: HashSort()
    {
        int n, i;
        char * str;
        cin >> n >> str;

        for(i = 0; i < n; i++)
        {
            if(Find-Ins(str) == - Tablesize)
            {
                cout << "表已满" << endl;
                break;
            }

            cin >> str;
        }

        for(i = 0; i < TableSize; i++)
            if(ht[i].info == Active) cout << ht[i].Element << endl;
    }
