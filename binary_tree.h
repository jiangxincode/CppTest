#include <string>

#include <cstdlib> //just for NULL
#include <climits> //just for INT_MAX and INT_MIN

struct binary_node
{
    int data;
    int count; //计数，插入相同元素，则递增
    binary_node *left_child, *right_child;
    binary_node *parent;
    binary_node():data(0),count(1),left_child(NULL),right_child(NULL) {}
    binary_node(int D, binary_node *L = NULL, binary_node *R = NULL):data(D),count(1),left_child(R),right_child(R) {}
};

class binary_tree
{

protected:
    binary_node *root;
    int ref_val; //the mark for the ending of the binary tree

    void create_binary_tree(binary_node *&sub_tree);
    void create_binary_tree(binary_node *&sub_tree, std::string str);

    void destroy_binary_tree(binary_node *&sub_tree);

    void preorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void inorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void postorder(binary_node *sub_tree, void (*visit)(binary_node *node));
    void levelorder(binary_node *sub_tree, void (*visit)(binary_node *node));

    void print_in_table(binary_node *sub_tree); //广义表形式输出

    virtual void get_min_max(binary_node *node, int &min, int &max);

    binary_node* get_parent(binary_node *sub_tree, binary_node *current);

    binary_node* find(binary_node *sub_tree, int target);

    int get_height(binary_node *sub_tree);
    int get_size(binary_node *sub_tree);
    int get_leaf_size(binary_node *sub_tree);

    bool is_complete(binary_node *sub_tree);

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
    void create_binary_tree(std::string str)
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
    void levelorder(void (*visit)(binary_node *node))
    {
        levelorder(root,visit);
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
    virtual void get_min_max(int &min, int &max)
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
    bool is_complete() //A complete binary tree or not
    {
        return is_complete(root);
    }
};
