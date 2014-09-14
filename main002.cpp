/*
参考main0526
*/

#include <iostream>
#include <stack>
#include <sstream>
#include <iomanip>

#include <cstdlib> //just for NULL
#include <climits> //just for INT_MAX and INT_MIN
#include <cctype> // just for isdigit

using namespace std;

struct binary_node
{
    int data;
    int count; //计数，插入相同元素，则递增
    binary_node *left_child, *right_child;
    binary_node():data(0),count(1),left_child(NULL),right_child(NULL) {}
    binary_node(int D, binary_node *L = NULL, binary_node *R = NULL):data(D),count(1),left_child(R),right_child(R) {}
};

class binary_tree
{


private:
    binary_node *root;
    int ref_val; //the mark for the ending of the binary tree
    void create_binary_tree(binary_node *&sub_tree);
    void create_binary_tree(binary_node *&sub_tree, string str);
    void destroy_binary_tree(binary_node *&sub_tree);
    void preorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void inorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void postorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void print_in_table(binary_node *sub_tree); //广义表形式输出
    void get_min_max(binary_node *node, int &min, int &max);
    binary_node* get_parent(binary_node *sub_tree, binary_node *current);
    binary_node* find(binary_node *sub_tree, int target);
    int get_height(binary_node *sub_tree);
    int get_size(binary_node *sub_tree);
    int get_leaf_size(binary_node *sub_tree);
    bool is_binary_search_tree(binary_node *sub_tree);


public:
    binary_tree():root(NULL),ref_val(-1) {}
    binary_tree(int ref_val):root(NULL),ref_val(ref_val) {}
    ~binary_tree()
    {
        destroy_binary_tree(root);
    }
    bool empty()
    {
        if(root == NULL) return true;
        else return false;
    }
    void create_binary_tree()
    {
        create_binary_tree(root);
    }
    void create_binary_tree(string str)
    {
        create_binary_tree(root,str);
    }

    void preorder(void (*visit)(binary_node *node))
    {
        preorder(root,visit);
    }
    void inorder(void (*visit)(binary_node *node))
    {
        inorder(root,visit);
    }
    void postorder(void (*visit)(binary_node *node))
    {
        postorder(root,visit);
    }
    void print_in_table()
    {
        print_in_table(root);
    }
    int get_root_data()
    {
        if(root != NULL)
        {
            return root->data;
        }
        else
            return -1;
    }
    void get_min_max(int &min, int &max)
    {
        min = INT_MAX;
        max = INT_MIN;
        get_min_max(root,min,max);
    }
    int get_min()
    {
        int min = INT_MAX;
        int max = INT_MAX; //减少最大值的操作
        get_min_max(root,min,max);
        return min;
    }
    int get_max()
    {
        int min = INT_MIN; //减少最小值的操作
        int max = INT_MIN;
        get_min_max(root,min,max);
        return max;
    }
    binary_node* get_parent(binary_node *current)
    {
        return get_parent(root,current);
    }
    binary_node* get_left_child(binary_node *current)
    {
        return ((current==NULL)?NULL:current->left_child);
    }
    binary_node* get_right_child(binary_node *current)
    {
        return ((current==NULL)?NULL:current->right_child);
    }
    binary_node* find(int target)
    {
        return find(root,target);
    }
    int get_height()
    {
        return get_height(root);
    }
    int get_size()
    {
        return get_size(root);
    }
    int get_leaf_size()
    {
        return get_leaf_size(root);
    }
    bool is_binary_search_tree()
    {
        return is_binary_search_tree(root);
    }
};

void binary_tree::create_binary_tree(binary_node *&sub_tree) //注意这里一定要传引用
{
    int input;
    cin >> input;
    if(input != ref_val)
    {
        sub_tree = new binary_node(input);
        cout << "Input the left child of the node " << input << ": ";
        create_binary_tree(sub_tree->left_child);
        cout << "Input the right child of the node " << input << ": ";
        create_binary_tree(sub_tree->right_child);
    }
    else
        sub_tree = NULL;
}

void binary_tree::create_binary_tree(binary_node *&sub_tree, string str)
{
    string::iterator it;
    stack<binary_node *> sta;
    binary_node *p, *t;
    int k;
    for(it=str.begin();it!=str.end();it++)
    {
        char c_temp = *it;
        string str_temp = "";
        switch(c_temp)
        {
            case '(': sta.push(p);k=1;break;
            case ')': t = sta.top();sta.pop();break;
            case ',': k = 2;break;
            default:
                do{
                    str_temp += c_temp;
                    if(it!=str.end()-1)
                    {
                        c_temp = *(++it);
                    }
                }while(isdigit(c_temp));
                it --;
                stringstream io(str_temp);
                int i_temp;
                io >> i_temp;
                p = new binary_node(i_temp);
                if(sub_tree == NULL)
                {
                    sub_tree = p;
                }
                else if(k == 1)
                {
                    t = sta.top();
                    t->left_child = p;
                }
                else
                {
                    t = sta.top();
                    t->right_child = p;
                }
        }
    }
}

void binary_tree::destroy_binary_tree(binary_node *&sub_tree)
{
    if(sub_tree == NULL)
    {
        return ;
    }
    else
    {
        destroy_binary_tree(sub_tree->left_child);
        destroy_binary_tree(sub_tree->right_child);
        delete sub_tree;
    }
}
void binary_tree::preorder(binary_node *sub_tree, void (*visit)(binary_node *node))
{
    if(sub_tree == NULL)
    {
        return ;
    }
    visit(sub_tree);
    preorder(sub_tree->left_child,visit);
    preorder(sub_tree->right_child,visit);
}

void binary_tree::inorder(binary_node *sub_tree, void (*visit)(binary_node *node))
{
    if(sub_tree == NULL)
    {
        return ;
    }
    inorder(sub_tree->left_child,visit);
    visit(sub_tree);
    inorder(sub_tree->right_child,visit);
}

void binary_tree::postorder(binary_node *sub_tree, void (*visit)(binary_node *node))
{
    if(sub_tree == NULL)
    {
        return ;
    }
    postorder(sub_tree->left_child,visit);
    postorder(sub_tree->right_child,visit);
    visit(sub_tree);
}

void binary_tree::print_in_table(binary_node *sub_tree) //以广义表形式输出二叉树
{
    if(sub_tree != NULL)
    {
        cout << sub_tree->data << '[' << sub_tree -> count << ']';

        if(sub_tree->left_child!=NULL || sub_tree->right_child!=NULL)
        {
            cout<<'(';
            print_in_table(sub_tree->left_child);
            if(sub_tree->right_child!=NULL)
            {
                cout<<',';
            }
            print_in_table(sub_tree->right_child);
            cout<<')';
        }
    }
}
void binary_tree::get_min_max(binary_node *node, int &min, int &max)
{
    if(node == NULL)
    {
        return ;
    }
    if(node->data < min)
    {
        min = node->data;
    }
    else if(node->data > max)
    {
        max = node->data;
    }
    get_min_max(node->left_child,min,max);
    get_min_max(node->right_child,min,max);
}
void print(binary_node *node)
{
    if(node != NULL)
    {
        cout << node->data << " ";
    }
}

binary_node* binary_tree::get_parent(binary_node *sub_tree, binary_node *current)
{
    binary_node *p;
    if((sub_tree == NULL) || (sub_tree == current) || (sub_tree == NULL))
    {
        return NULL;
    }
    else if((sub_tree->left_child == current) || (sub_tree->right_child == current))
    {
        return sub_tree;
    }
    else if((p=get_parent(sub_tree->left_child,current)) != NULL)
    {
        return p;
    }
    else
    {
        return get_parent(sub_tree->right_child,current);
    }
}

binary_node* binary_tree::find(binary_node *sub_tree, int target)
{
    binary_node *p;
    if(sub_tree == NULL)
    {
        return NULL;
    }
    else if(sub_tree->data == target)
    {
        return sub_tree;
    }
    else if((p=find(sub_tree->left_child,target))!=NULL)
    {
        return p;
    }
    else if((p=find(sub_tree->right_child,target))!=NULL)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

int binary_tree::get_height(binary_node *sub_tree)
{
    if(sub_tree == NULL)
    {
        return 0;
    }
    else
    {
        int left_size, right_size;
        left_size = get_height(sub_tree->left_child);
        right_size = get_height(sub_tree->right_child);
        return (left_size>right_size)?(1+left_size):(1+right_size);
    }
}
int binary_tree::get_size(binary_node *sub_tree)
{
    if(sub_tree == NULL)
    {
        return 0;
    }
    else
    {
        return 1+get_size(sub_tree->left_child)+get_size(sub_tree->right_child);
    }
}

int binary_tree::get_leaf_size(binary_node *sub_tree)
{
    if(sub_tree == NULL)
    {
        return 0;
    }
    else if((sub_tree->left_child==NULL) && (sub_tree->right_child==NULL))
    {
        return 1;
    }
    else
    {
        return get_leaf_size(sub_tree->left_child) + get_leaf_size(sub_tree->right_child);
    }
}

bool binary_tree::is_binary_search_tree(binary_node *sub_tree)
{
    binary_node *p=sub_tree;
    if(p!=NULL)
    {
        if(p->left_child!=NULL)
        {
            if(p->left_child->data > p->data)
            {
                return false;
            }
        }
        if(p->right_child!=NULL)
        {
            if(p->right_child->data < p->data)
            {
                return false;
            }
        }
    }
    if((p->left_child!=NULL) && (!is_binary_search_tree(p->left_child)))
    {
        return false;
    }
    if((p->right_child!=NULL) && (!is_binary_search_tree(p->left_child)))
    {
        return false;
    }
    else
    {
        return true;
    }
}
int main002()
{
    binary_tree b_tree;
    //binary_node *p;
    //cout << "Input the root: ";
    //b_tree.create_binary_tree();
    b_tree.create_binary_tree("34(56(36,),78(72(28,29),35))");
    b_tree.print_in_table();
    cout << endl;
    //b_tree.create_binary_tree("53(17(09,45(23,)),78(65,87(81,94)))");
    //p = b_tree.find(35);
    //cout << p->data << endl;

    //p = b_tree.get_parent(p);
    //cout << p->data << endl;

    //p = b_tree.get_right_child(p);
    //cout << p->data << endl;

    cout << b_tree.get_height() << endl;
    cout << b_tree.get_size() << endl;
    cout << b_tree.get_leaf_size() << endl;

    cout << boolalpha << b_tree.is_binary_search_tree() << endl;

    b_tree.preorder(print);
    cout << endl;
    b_tree.inorder(print);
    cout << endl;
    b_tree.postorder(print);
    cout << endl;
    //int min, max;
    //b_tree.get_min_max(min,max);
    //cout << min << " " << max << " " << (max-min) << endl;
    return 0;
}
