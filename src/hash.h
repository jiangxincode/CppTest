#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class HashTable
{
    //散列表类定义
public:
    enum KindOfEntry { Active, Empty, Deleted };			//表项分类 (活动 / 空 / 删)
    HashTable() : TableSize(BUFSIZ)
    {
        ht = new HashEntry[TableSize];    //构造函数
    }
    ~HashTable()
    {
        delete [ ] ht;    //析构函数
    }
    int Find_Ins(const char * id);					//在散列表中搜索标识符id
    void HashSort();
private:
    struct HashEntry
    {
        //表项定义
        //Type Element;								//表项的数据, 即表项的关键码
        char *Element;
        KindOfEntry info;							//三种状态: Active, Empty, Deleted
        HashEntry() : info(Empty) { }					//表项构造函数, 置空
    };
    HashEntry *ht;								//散列表存储数组
    int TableSize;								//最大桶数
    int FindPos(const char* s) const
    {
        return atoi(s) - 32;    //散列函数
    }
};

