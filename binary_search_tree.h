#include "binary_tree.h"

class binary_search_tree : public binary_tree //question
{
private:
    bool is_binary_search_tree(binary_node *sub_tree);
    binary_node* insert(binary_node *&sub_tree, int data);
    void remove(binary_node *&sub_tree);
    bool remove(binary_node *&sub_tree, int data);
    void get_min_max(binary_node *sub_tree, int &min, int &max);


public:
    bool is_binary_search_tree()
    {
        return is_binary_search_tree(root);
    }
    binary_node* insert(int data)
    {
        return insert(root,data);
    }
    bool remove(int data)
    {
        return remove(root,data);
    }
    void get_min_max(int &min, int &max) override
    {
        get_min_max(root,min,max);
    }
};
