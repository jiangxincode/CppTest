
//静态链表的定义
const int maxSize = 100; //the size of static list

template <class T>
struct SLinkNode
{
    T data; //data of every node
    int link; //the pointer of node
};

template <class T>
class StaticList
{
    SLinkNode<T> elem[maxSize];
    int avil; //the head address that can be destributed currently
public:
    void InitList();
    int Length(); //calculate the length of the static list
    int Search(T x); //find the value x in the static list
    int Locate(int i); //find the node which sequence is i
    bool Append(T x); //add a new node on the last of staic list
    bool Insert(int i,T x); //insert a new node in the node which sequence is i
    bool Remove(int i); //remove the node which sequence is i
    bool IsEmpty(); //judge the static list is empty or not
};

template <class T>
void StaticList<T>::InitList()
{
    elem[0]=-1;
    avil = 1;

    for(int i=0; i<maxSize-1; i++)
    {
        elem[i].link=i+1;
    }

    elem[maxSize-1].link=-1;
}

template <class T>
int StaticList<T>::Length()
{
    int p=elem[0].link;
    int i=0;

    while(p!=-1)
    {
        p=elem[p].link;
        i++;
    }

    return i;
}

template <class T>
int StaticList<T>::Search(T x)
{
    int p=elem[0].link;

    while(p!=-1)
    {
        if(elem[p].data==1)
            break;
        else
            p=elem[p].link;
    }

    return p;
}

template <class T>
int StaticList<T>::Locate(int i)
{
    if(i<0) return -1;

    if(i==0) return 0;

    int j=1;
    int p=elem[0].link;

    while(p!=-1&&j<i)
    {
        p=elem[p].link;
        j++;
    }

    return p;
}

template <class T>
bool StaticList<T>::Insert(int i,T x)
{
    int p=Locate(i);

    if(p==-1)
    {
        return false;
    }

    int q=avil;
    avil=elem[avil].link;
    elem[q].data=x;
    elem[q].link=elem[p].link;
    elem[p].link=q;
    return true;
}

template <class T>
bool StaticList<T>::Remove(int i)
{
    int p=Locate(i);

    if(p == -1) return false;

    int q = elem[p].link;
    elem[p].link = elem[q].link;
    elem[q].link = avil;
    avil = q;
    return true;
}
