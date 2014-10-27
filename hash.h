#define DefaultSize 1000
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
class HashTable
{
    //ɢ�б��ඨ��
public:
    enum KindOfEntry { Active, Empty, Deleted };			//������� (� / �� / ɾ)
    HashTable() : TableSize(DefaultSize)
    {
        ht = new HashEntry[TableSize];    //���캯��
    }
    ~HashTable()
    {
        delete [ ] ht;    //��������
    }
    int Find-Ins(const char * id);					//��ɢ�б���������ʶ��id
    void HashSort();
private:
    struct HashEntry
    {
        //�����
        Type Element;								//���������, ������Ĺؼ���
        KindOfEntry info;							//����״̬: Active, Empty, Deleted
        HashEntry() : info(Empty) { }					//����캯��, �ÿ�
    };
    HashEntry *ht;								//ɢ�б�洢����
    int TableSize;								//���Ͱ��
    int FindPos(string s) const
    {
        return atoi(*s) - 32;    //ɢ�к���
    }
}

int HashTable :: Find-Ins(const char * id)
{
    int i = FindPos(id),  j = i; 						//i�Ǽ��������ɢ�е�ַ

    while(ht[j].info != Empty && strcmp(ht[j].Element, id) != 0)
    {
        //��ͻ
        j = (j + 1) % TableSize;						//����ѭ������, ����һ����Ͱ

        if(j == i) return -TableSize;					//תһȦ�ص���ʼ��, ������, ʧ��
    }

    if(ht[j].info != Active)
    {
        //����
        if(j > i)
        {
            while(int k = j; k > i; k--)
            {
                ht[k].Element = ht[k-1].Element;
                ht[k].info = ht[k-1].info;
            }

            ht[i].Element = id;
            ht[i].info = Active;  			//����
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
            ht[i].info = Active;  			//����

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
                cout << "������" << endl;
                break;
            }

            cin >> str;
        }

        for(i = 0; i < TableSize; i++)
            if(ht[i].info == Active) cout << ht[i].Element << endl;
    }
