#include <iostream>
#include <iomanip>

#include "../src/binary_search_tree.h"
#include <gtest/gtest.h>

using namespace std;

TEST(BinarySearchTreeTest, binary_search_tree_test)
{
    binary_search_tree bs_tree;
    bs_tree.create_binary_tree("53(17(09,45(23,)),78(65,87(81,94)))");
    ASSERT_EQ(10, bs_tree.get_size());
    bs_tree.insert(23); //插入相同元素，数量不变，对应计数+1
    ASSERT_EQ(10, bs_tree.get_size());
    bs_tree.insert(104);
    ASSERT_EQ(11, bs_tree.get_size());
    bs_tree.remove(23);
    ASSERT_EQ(11, bs_tree.get_size());
    bs_tree.remove(23);
    ASSERT_EQ(10, bs_tree.get_size());
    ASSERT_EQ(104, bs_tree.get_max());
    ASSERT_EQ(9, bs_tree.get_min());
    bs_tree.remove(bs_tree.get_max());
    ASSERT_EQ(94, bs_tree.get_max());
    ASSERT_TRUE(bs_tree.is_binary_search_tree());
}
