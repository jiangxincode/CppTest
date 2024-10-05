#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int DefaultSize = 100;
enum KindOfStatus {
    Active, Empty, Deleted
}; //表项分类 (活动 / 空 / 删)

template<class E, class K>
class HashTable {
public:
    HashTable(const int d, int sz = DefaultSize);

    ~HashTable() {
        delete[] ht;
        delete[] info;
    }

    HashTable<E, K> &operator=(const HashTable<E, K> &ht2);

    bool Search(const K k1, E &e1) const;

    bool Insert(const E &e1);

    bool Remove(const K k1, E &e1);

    void makeEmpty();

private:
    int divitor; // 散列函数的除数
    int CurrentSize, TableSize; // 当前桶数及最大桶数
    E *ht; // 散列表存储数组
    KindOfStatus *info; //状态数组

    int FindPos(const K k1) const; // 散列函数：计算初始桶号

    int operator==(E &e1) { // 重载函数：元素判等
        return *this == e1;
    }

    int operator!=(E &e1) { // 重载函数：元素判不等
        return *this != e1;
    }
};


template<class E, class K>
HashTable<E, K>::HashTable(int d, int sz) {
    divitor = d;
    TableSize = sz;
    CurrentSize = 0;
    ht = new E[TableSize];
    info = new KindOfStatus[TableSize];
    for (int i = 0; i < TableSize; i++) {
        info[i] = Empty;
    }
};

template<class E, class K>
int HashTable<E, K>::FindPos(const K k1) const {
    int i = k1 % divitor;
    int j = i;
    do {
        if (info[j] == Empty || info[j] == Active && ht[j] == k1) {
            return j;
        }
    } while (j != i);
    return j;
};

template<class E, class K>
bool HashTable<E, K>::Search(const K k1, E &e1) const {
    int i = FindPos(k1);
    if (info[i] != Active || ht[i] != k1) {
        return false;
    }
    1 = ht[i];
    return true;
};

template<class E, class K>
void HashTable<E, K>::makeEmpty() {
    for (int i = 0; i < TableSize; i++) {
        info[i] = Empty;
    }
    CurrentSize = 0;
};

template<class E, class K>
HashTable<E, K> &HashTable<E, K>::operator=(const HashTable<E, K> &ht2) {
    if (this != &ht2) {
        delete[] ht;
        delete[] info;
        TableSize = ht2.TableSize;
        ht = new E[TableSize];
        info = new KindOfStatus[TableSize];
        for (int i = 0; i < TableSize; i++) {
            ht[i] = ht2.ht[i];
            info[i] = ht2.info[i];
        }
        CurrentSize = ht2.CurrentSize;
    }
    return *this;
}

template<class E, class K>
bool HashTable<E, K>::Insert(const E &e1) {
    K k1 = e1;
    int i = FindPos(k1);
    if (info[i] != Active) {
        ht[i] = e1;
        info[i] = Active;
        CurrentSize++;
        return true;
    }
    if (info[i] == Active && ht[i] == e1) {
        cout << "exist" << endl;
        return false;
    }
    cout << "full" << endl;
    return false;
};

template<class E, class K>
bool HashTable<E, K>::Remove(const K k1, E &e1) {
    int i = FindPos(k1);
    if (info[i] == Active && ht[i] == k1) {
        info[i] == Deleted;
        CurrentSize--;
        return true;
    }
    return false;
};

int main() {
    HashTable<char, char>* ht = new HashTable<char, char>(3, 3);
    char tmp = '\0';
    cout << ht->Search('a', tmp) << endl;
    ht->Insert('a');
    cout << ht->Search('a', tmp) << endl;
    ht->Remove('a', tmp);
    cout << ht->Search('a', tmp) << endl;
}
