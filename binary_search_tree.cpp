#include <iostream>
#include "binary_search_tree.h"

using namespace std;

bool binary_search_tree::is_binary_search_tree(binary_node *sub_tree)
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

binary_node* binary_search_tree::insert(binary_node *& sub_tree,int data)
{
    if(sub_tree == NULL)
    {
        sub_tree = new binary_node(data);
        return sub_tree;
    }
    else if(data < sub_tree->data)
    {
        return insert(sub_tree->left_child,data);
    }
    else if(data > sub_tree->data)
    {
        return insert(sub_tree->right_child,data);
    }
    else
    {
        sub_tree->count ++;
        return NULL;
    }
}

void binary_search_tree::remove(binary_node *& sub_tree)
{
    binary_node *p = sub_tree;

    if(p == NULL)
    {
        return ;
    }
    else if(p->count > 1)
    {
        p->count --;
    }
    else if((p->left_child == NULL) && (p->right_child == NULL))
    {
        binary_node *parent = get_parent(p);
        (parent->left_child==p) ? (parent->left_child=NULL) : (parent->right_child=NULL);
        delete p;
    }
    else if(p->left_child != NULL)
    {
        binary_node *q = p;
        while(q->right_child != NULL)
        {
            q = q->right_child;
        }
        p->data = q->data;
        p->count = q->count;
        remove(q);
    }
    else
    {
        binary_node *q = p;
        while(p->left_child != NULL)
        {
            q = q->left_child;
        }
        p->data = q->data;
        p->count = q->count;
        remove(q);
    }
}

bool binary_search_tree::remove(binary_node *&sub_tree,int data)
{
    binary_node *t = sub_tree;

    while((t != NULL) && (t->data != data))
    {
        if(data < t->data)
        {
            t = t->left_child;
        }
        else
        {
            t = t->right_child;
        }
    }
    if(t == NULL)
    {
        return false; //Î´ÕÒµ½
    }
    else
    {
        remove(t);
    }
    return true;
}

void binary_search_tree::get_min_max(binary_node *sub_tree, int &min, int &max)
{
    binary_node *p = sub_tree;
    while(p->left_child != NULL)
    {
        p = p->left_child;
    }
    min = p->data;

    p = sub_tree;
    while(p->right_child != NULL)
    {
        p = p->right_child;
    }
    max = p->data;
}
