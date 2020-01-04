#include <iostream>

using namespace std;

template <class T>
struct SetNode
{
    T data;
    SetNode<T> *link;
    SetNode():link(NULL) {};
    SetNode(T x,SetNode<T> *next = NULL):data(x),link(next) {};
};

template <class T>
class LinkedSet
{
private:
    SetNode<T> *first,*last;
public:
    LinkedSet()
    {
        first = last = new SetNode<T>;
        first->link = last;
        last->link = first;
    }
    bool addMember(T& x);
    void display();
    SetNode<T>* getFirst();
    SetNode<T>* Search(SetNode<T> *head,SetNode<T> *& current,T key);
};

template <class T>
bool LinkedSet<T>::addMember(T& x)
{
    SetNode<T> *p=first->link, *pre=first;

    while(p!=first && p->data < x)
    {
        pre = p;
        p = p->link;
    }

    if(p!=first && p->data == x)
    {
        return false;
    }

    SetNode<T> *s = new SetNode<T>(x);
    s->link = p;
    pre->link = s;

    if(p == NULL)
    {
        last = s;
    }

    return true;
}
template<class T>
void LinkedSet<T>::display()
{
    SetNode<T> *p = first;
    cout << p->data << "\t";
    p = p->link;

    while(p!=first)
    {
        cout << p->data << "\t";
        p = p->link;
    }

    cout << endl;
}

template <class T>
SetNode<T>* LinkedSet<T>::getFirst()
{
    return first;
}
template <class T>
SetNode<T>* LinkedSet<T>::Search(SetNode<T> *head,SetNode<T> *& current,T key)
{
    SetNode<T> *p,*q;

    if(key<current->data)
    {
        p=first;
        q=current;
    }
    else
    {
        p=current;
        q=first;
    }

    while(p!=q && p->data<key)
        p=p->link;

    if(p->data == key)
    {
        current = p;
        return p;
    }
    else
    {
        current=first;
        return NULL;
    }
}
