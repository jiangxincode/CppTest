#include <iostream>
#include <cstring>

using namespace std;

/* trie�Ľڵ����� */
template <int Size> //SizeΪ�ַ���Ĵ�С
struct trie_node
{
    bool terminable; //��ǰ�ڵ��Ƿ������Ϊ�ַ����Ľ�β
    int node; //�ӽڵ�ĸ���
    trie_node *child[Size]; //ָ���ӽڵ�ָ��

    /* ���캯�� */
    trie_node() : terminable(false), node(0)
    {
        memset(child, 0, sizeof(child));
    }
};

/* trie */
template <int Size, typename Index> //SizeΪ�ַ���Ĵ�С��IndexΪ�ַ���Ĺ�ϣ����
class trie
{
public:
    /* �������ͱ��� */
    typedef trie_node<Size> node_type;
    typedef trie_node<Size>* link_type;

    /* ���캯�� */
    trie(Index i = Index()) : index(i) { }

    /* �������� */
    ~trie()
    {
        clear();
    }

    /* ��� */
    void clear()
    {
        clear_node(root);
        for (int i = 0; i < Size; ++i)
            root.child[i] = 0;
    }

    /* �����ַ��� */
    template <typename Iterator>
    void insert(Iterator begin, Iterator end)
    {
        link_type cur = &root; //��ǰ�ڵ�����Ϊ���ڵ�
        for (; begin != end; ++begin)
        {
            if (!cur->child[index[*begin]]) //����ǰ�ַ��Ҳ���ƥ�䣬���½��ڵ�
            {
                cur->child[index[*begin]] = new node_type;
                ++cur->node; //��ǰ�ڵ���ӽڵ�����һ
            }
            cur = cur->child[index[*begin]]; //����ǰ�ڵ�����Ϊ��ǰ�ַ���Ӧ���ӽڵ�
        }
        cur->terminable = true; //���ô�����һ���ַ��Ľڵ�Ŀ���ֹ��־Ϊ��
    }

    /* �����ַ��������C����ַ��������ذ汾 */
    void insert(const char *str)
    {
        insert(str, str + strlen(str));
    }

    /* �����ַ������㷨�Ͳ������� */
    template <typename Iterator>
    bool find(Iterator begin, Iterator end)
    {
        link_type cur = &root;
        for (; begin != end; ++begin)
        {
            if (!cur->child[index[*begin]])
                return false;
            cur = cur->child[index[*begin]];
        }
        return cur->terminable;
    }

    /* �����ַ��������C����ַ��������ذ汾 */
    bool find(const char *str)
    {
        return find(str, str + strlen(str));
    }

    /* ɾ���ַ��� */
    template <typename Iterator>
    bool erase(Iterator begin, Iterator end)
    {
        bool result; //���ڴ���������
        erase_node(begin, end, root, result);
        return result;
    }

    /* ɾ���ַ��������C����ַ��������ذ汾 */
    bool erase(char *str)
    {
        return erase(str, str + strlen(str));
    }

    /* ���ֵ������������ */
    template <typename Functor>
    void traverse(Functor &execute = Functor())
    {
        visit_node(root, execute);
    }

private:
    /* ����ĳ��㼰���ӽ�� */
    template <typename Functor>
    void visit_node(node_type cur, Functor &execute)
    {
        execute(cur);
        for (int i = 0; i < Size; ++i)
        {
            if (cur.child[i] == 0) continue;
            visit_node(*cur.child[i], execute);
        }
    }
    /* ���ĳ���ڵ�������ӽڵ� */
    void clear_node(node_type cur)
    {
        for (int i = 0; i < Size; ++i)
        {
            if (cur.child[i] == 0) continue;
            clear_node(*cur.child[i]);
            delete cur.child[i];
            cur.child[i] = 0;
            if (--cur.node == 0) break;
        }
    }

    /* ��������ɾ������ڵ㣬����ֵ�������丸�ڵ������Ƿ��ɾ���ýڵ� */
    template <typename Iterator>
    bool erase_node(Iterator begin, Iterator end, node_type &cur, bool &result)
    {
        if (begin == end) //�������ַ�����β���ݹ����ֹ����
        {
            result = cur.terminable; //�����ǰ�ڵ������Ϊ��ֹ�ַ�����ô���Ϊ��
            cur.terminable = false;  //���øýڵ�Ϊ������Ϊ��ֹ�ַ�����ɾ�����ַ���
            return cur.node == 0;    //���ýڵ�Ϊ��Ҷ����ô֪ͨ�丸�ڵ�ɾ����
        }
        //���޷�ƥ�䵱ǰ�ַ�ʱ���������Ϊ�ٲ����ؼ٣���֪ͨ�丸�ڵ㲻Ҫɾ����
        if (cur.child[index[*begin]] == 0) return result = false;
        //�ж��Ƿ�Ӧ��ɾ�����ӽڵ�
        else if (erase_node((++begin)--, end, *(cur.child[index[*begin]]), result))
        {
            delete cur.child[index[*begin]]; //ɾ�����ӽڵ�
            cur.child[index[*begin]] = 0; //�ӽڵ�����һ
            //����ǰ�ڵ�Ϊ��Ҷ����ô֪ͨ�丸�ڵ�ɾ����
            if (--cur.node == 0 && cur.terminable == false) return true;
        }
        return false; //������������ؼ�
    }

    /* ���ڵ� */
    node_type root;

    /* ���ַ�ת��Ϊ������ת����������� */
    Index index;
};

//index function object
class IndexClass
{
public:
    int operator[](const char key)
    {
        return key % 26;
    }
};

int test_trie()
{
    trie<26,IndexClass> t;
    t.insert("tree");
    t.insert("tea");
    t.insert("A");
    t.insert("ABC");

    if(t.find("tree"))
        cout<<"find tree"<<endl;
    else
        cout<<"not find tree"<<endl;

    if(t.find("tre"))
        cout<<"find tre"<<endl;
    else
        cout<<"not find tre"<<endl;

    if(t.erase("tree"))
        cout<<"delete tree"<<endl;
    else
        cout<<"not find tree"<<endl;

    if(t.find("tree"))
        cout<<"find tree"<<endl;
    else
        cout<<"not find tree"<<endl;

    return 0;
}

int main1800()
{
    return 0;
}
