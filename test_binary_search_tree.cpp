#include <iostream>
#include <iomanip>

#include "binary_search_tree.h"

using namespace std;

void print(binary_node *node)
{
    if(node != NULL)
    {
        cout << node->data << " ";
    }
}

int main002()
{
    binary_tree b_tree;
    //binary_node *p;
    //cout << "Input the root: ";
    //b_tree.create_binary_tree();
    //b_tree.create_binary_tree("34(56(36,),78(72(28,29),35))");
    b_tree.create_binary_tree("34(56(72,67),63(29,80))");
    cout << boolalpha << b_tree.is_complete() << endl;
    //b_tree.print_in_table();
    //cout << endl;
    //p = b_tree.find(35);
    //cout << p->data << endl;
    //p = b_tree.get_parent(p);
    //cout << p->data << endl;
    //p = b_tree.get_right_child(p);
    //cout << p->data << endl;
    //cout << b_tree.get_height() << endl;
    //cout << b_tree.get_size() << endl;
    //cout << b_tree.get_leaf_size() << endl;
    //binary_search_tree bs_tree;
    //bs_tree.create_binary_tree("53(17(09,45(23,)),78(65,87(81,94)))");
    //bs_tree.print_in_table();
    //cout << endl;
    //bs_tree.insert(23);
    //bs_tree.print_in_table();
    //cout << endl;
    //bs_tree.insert(104);
    //bs_tree.print_in_table();
    //cout << endl;
    //bs_tree.remove(23);
    //bs_tree.print_in_table();
    //cout << endl;
    //bs_tree.remove(23);
    //bs_tree.print_in_table();
    //cout << endl;
    //int min, max;
    //bs_tree.get_min_max(min,max);
    //cout << min << " " << max << " " << (max-min) << endl;
    //bs_tree.remove(max);
    //bs_tree.print_in_table();
    //cout << boolalpha << bs_tree.is_binary_search_tree() << endl;
    //b_tree.preorder(print);
    //cout << endl;
    //b_tree.inorder(print);
    //cout << endl;
    //b_tree.postorder(print);
    //cout << endl;
    b_tree.levelorder(print);
    //int min, max;
    //b_tree.get_min_max(min,max);
    //cout << min << " " << max << " " << (max-min) << endl;
    return 0;
}
