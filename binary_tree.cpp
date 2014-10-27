#include <iostream>
#include <stack>
#include <queue>
#include <sstream>

#include <cctype> // just for isdigit

#include "binary_tree.h"

using namespace std;

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

    for(it=str.begin(); it!=str.end(); ++it)
    {
        char c_temp = *it;
        string str_temp = "";

        switch(c_temp)
        {
        case '(':
            sta.push(p);
            k=1;
            break;

        case ')':
            t = sta.top();
            sta.pop();
            break;

        case ',':
            k = 2;
            break;

        default:
            do
            {
                str_temp += c_temp;

                if(it!=str.end()-1)
                {
                    c_temp = *(++it);
                }
            }
            while(isdigit(c_temp));

            --it;
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

void binary_tree::levelorder(binary_node *sub_tree, void (*visit)(binary_node *node))
{
    queue<binary_node *> node_queue;

    if(sub_tree == NULL)
    {
        return ;
    }

    node_queue.push(sub_tree);

    while(!node_queue.empty())
    {
        binary_node *temp = node_queue.front();
        visit(temp);
        node_queue.pop();

        if(temp->left_child)
        {
            node_queue.push(temp->left_child);
        }

        if(temp->right_child)
        {
            node_queue.push(temp->right_child);
        }
    }
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

/**
 *采用广度优先遍历，从根节点开始，入队列，如果队列不为空，循环。
 *遇到第一个没有左儿子或者右儿子的节点，设置标志位，
 *如果之后再遇到有左/右儿子的节点，那么这不是一颗完全二叉树。
 */
bool binary_tree::is_complete(binary_node *sub_tree)
{
    queue<binary_node *> node_queue;
    bool flag = false;

    if(sub_tree == NULL)
    {
        return true;
    }

    node_queue.push(sub_tree);

    while(!node_queue.empty())
    {
        binary_node *temp = node_queue.front();
        node_queue.pop();

        if(temp->left_child)
        {
            if(flag)
            {
                return false;
            }
            else
            {
                node_queue.push(temp->left_child);
            }
        }
        else
        {
            flag = true;
        }

        if(temp->right_child)
        {
            if(flag)
            {
                return false;
            }
            else
            {
                node_queue.push(temp->right_child);
            }
        }
        else
        {
            flag = true;
        }
    }

    return true;
}
