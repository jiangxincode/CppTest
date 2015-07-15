#include <iostream>
#include <iomanip>

#include "../src/binary_tree.h"
#include "../include/gtest/gtest.h"

using namespace std;

void static print(binary_node *node)
{
    if(node != NULL)
    {
        cout << node->data << " ";
    }
}

TEST(BinaryTreeTest, binary_tree_test01)
{
    binary_tree b_tree;
    b_tree.create_binary_tree("34(56(72,67),63(29,80))");
    ASSERT_TRUE(b_tree.is_complete());
    //b_tree.levelorder(print);
}
TEST(BinaryTreeTest, binary_tree_test02)
{
    binary_tree b_tree;
    binary_node *p;
    //cout << "Input the root: ";
    //b_tree.create_binary_tree();
    b_tree.create_binary_tree("34(56(36,),78(72(28,29),35))");
    //b_tree.print_in_table();
    //cout << endl;
    p = b_tree.find(35);
    ASSERT_EQ(35, p->data);
    p = b_tree.get_parent(p);
    ASSERT_EQ(78, p->data);
    p = b_tree.get_right_child(p);
    ASSERT_EQ(35, p->data);

    ASSERT_EQ(4, b_tree.get_height());
    ASSERT_EQ(8, b_tree.get_size());
    ASSERT_EQ(4, b_tree.get_leaf_size());

    ASSERT_EQ(28, b_tree.get_min());
    ASSERT_EQ(78, b_tree.get_max());


    //b_tree.preorder(print);
    //cout << endl;
    //b_tree.inorder(print);
    //cout << endl;
    //b_tree.postorder(print);
    //cout << endl;
    //b_tree.levelorder(print);
}

