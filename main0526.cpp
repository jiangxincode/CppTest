#include <iostream>
#include <stack>

#include <cstdlib>
#include <cstdio>

using namespace std;

template <class T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *leftChild,*rightChild;
    BinTreeNode():leftChild(NULL),rightChild(NULL) {}
    BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T> *r=NULL):data(x),leftChild(l),rightChild(r) {}
};

template <class T>
class BinaryTree
{
public:
    BinaryTree():root(NULL) {}
    BinaryTree(T value):root(NULL),RefValue(value){}
    //BinaryTree(BinaryTree<T>& s);
    //~BinaryTree(){destroy(root);}
    bool IsEmpty()
    {
        return (root == NULL)?true:false;
    }
    BinTreeNode<T> *Parent(BinTreeNode<T> *current)
    {
        return (root == NULL || root == current)?NULL:Parent(root,current);
    }
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current)
    {
        return (current != NULL)?current->leftChild:NULL;
    }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current)
    {
        return (current != NULL)?current->rightChild:NULL;
    }
    int Height()
    {
        return Height(root);
    }
    int Size()
    {
        return Size(root);
    }
    BinTreeNode<T> *getRoot()const
    {
        return root;
    }
    void preOrder(void (*visit)(BinTreeNode<T> *p))
    {
        preOrder(root,visit);
    }
    void inOrder(void (*visit)(BinTreeNode<T> *p))
    {
        inOrder(root,visit);
    }
    void postOrder(void (*visit)(BinTreeNode<T> *p))
    {
        postOrder(root,visit);
    }
    //void leverOrder(void (*visit)(BinTreeNode<T> *p));
    int Insert(const T item);
    BinTreeNode<T> *Find(T item)const;
    int leaf(BinTreeNode<T> *ptr);
    void exchange(BinTreeNode<T> *ptr);
protected:
    BinTreeNode<T> *root;
    T RefValue;
    // create the tree from file
    void CreateBinTree(istream& in,BinTreeNode<T> *& subTree);
    bool Insert(BinTreeNode<T> *& subTree,const T& x);
    void destroy(BinTreeNode<T> *& subTree);
    //bool Find(BinTreeNode<T> *subTree,const T& x)const;
    //BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);
    int Height(BinTreeNode<T> *subTree)const;
    int Size(BinTreeNode<T> *subTree)const;
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree,BinTreeNode<T> *current);
    //BinTreeNode<T> *Find(BinTreeNode<T> *subTree,const T& x)const;
    void Traverse(BinTreeNode<T> *subTree,ostream& out);
    void preOrder(BinTreeNode<T>& subTree,void (*visit)(BinTreeNode<T> *p));
    void inOrder(BinTreeNode<T>& subTree,void (*visit)(BinTreeNode<T> *p));
    void postOrder(BinTreeNode<T>& subTree,void (*visit)(BinTreeNode<T> *p));
    void *visit(BinTreeNode<T> *temp);
    friend istream& operator>> (istream& in,BinaryTree<T>& Tree)
    {
        Tree.CreateBinTree(in,Tree.root);
        return in;
    }
    friend ostream& operator<< (ostream& out,BinaryTree<T>& Tree)
    {
        out << "二叉数的前序遍历\n";
        Tree.Traverse(Tree.root,out);
        out << endl;
        return out;
    }

};
template <class T>
bool BinaryTree<T>::Insert(BinTreeNode<T> *&subTree, const T&)
{
    return true;
}

/*
template <class T>
bool Find(BinTreeNode<T> *subTree,const T& x)const
{
	return true;
}
*/

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree)
{
    if(subTree != NULL)
    {
        destroy(subTree->leftChild);
        destroy(subTree->rigthChild);
        delete subTree;
    }
}

template <class T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T> *subTree,BinTreeNode<T> *current)
{
    if(subTree == NULL)
        return NULL;
    if(subTree->leftChild == current || subTree->rightChild == current)
        return subTree;
    BinTreeNode<T> *p;
    if(p = Parent(subTree->leftChild,current)!=NULL)
        return p;
    else
        return Parent(subTree->rightChild,current);
}

template <class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree,ostream& out)
{
    if(subTree != NULL)
    {
        out << subTree->data<<' ';
        Traverse(subTree->leftChild,out);
        Traverse(subTree->rightChild,out);
    }
}

template <class T>
void BinaryTree<T>::CreateBinTree(istream& in,BinTreeNode<T> *&BT)
{
    stack<BinTreeNode<char>*> s;
    BT = NULL;
    BinTreeNode<char> *p,*t;
    int k;
    char ch;
    in >> ch;
    while(ch != '#')
    {
        switch(ch)
        {
        case '(':
            s.push(p);
            k=1;
            break;
        case ')':
            t = s.top();
            s.pop();
            break;
        case ',':
            k = 2;
            break;
        default:
            p = new BinTreeNode<char>(ch);
            if(BT == NULL)
                BT = p;
            else if(k == 1)
            {
                t = s.top();
                t->leftChild = p;
            }
            else
            {
                t = s.top();
                t->rightChild = p;
            }
        }
        in >> ch;
    }
}

template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> &subTree,void(*vist)(BinTreeNode<T> *p))
{
    if(subTree != NULL)
    {
        inOrder(subTree -> leftChild,visit);
        visit(subTree);
        inOrder(subTree -> rightChild.visit);
    }
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> &subTree,void(*vist)(BinTreeNode<T> *p))
{
    if(subTree != NULL)
    {
        visit(subTree);
        preOrder(subTree -> leftChild,visit);
        preOrder(subTree -> rightChild.visit);
    }
}

template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T> &subTree,void(*vist)(BinTreeNode<T> *p))
{
    if(subTree != NULL)
    {
        postOrder(subTree -> leftChild,visit);
        postOrder(subTree -> rightChild.visit);
        visit(subTree);
    }
}

template <class T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree)const
{
    if(subTree == NULL)
        return 0;
    else
        return 1+Size(subTree->leftChild)+Size(subTree->rightChild);
}

template <class T>
int BinaryTree<T>::Height(BinTreeNode<T> *subTree)const
{
    if(subTree == NULL)
        return 0;
    else
    {
        int i = Height(subTree -> leftChild);
        int j = Height(subTree -> rightChild);
        return (i<j)?j+1:i+1;
    }
}

template <class T>
void* BinaryTree<T>::visit(BinTreeNode<T>* temp)
{
    return NULL;
}

template <class T>
int BinaryTree<T>::leaf(BinTreeNode<T> *ptr)
{
    if(ptr == NULL)
        return 0;
    else if(ptr->leftChild == NULL&&ptr->rightChild == NULL)
        return 1;
    else
        return leaf(ptr->leftChild)+leaf(ptr->rightChild);
}
template <class T>
void BinaryTree<T>::exchange(BinTreeNode<T> *ptr)
{
    BinTreeNode<T> *temp;
    if(ptr->leftChild!=NULL||ptr->rightChild!=NULL)
    {
        temp = ptr->leftChild;
        ptr->leftChild = ptr->rightChild;
        ptr->rightChild = temp;
        exchange(ptr->leftChild);
        exchange(ptr->rightChild);
    }
}

int main0526()
{
	cout << "Input the Tree:\n" << endl;
	BinaryTree<char> mytree('#');
	cin >> mytree;
	cout << mytree;
	return 0;
}
