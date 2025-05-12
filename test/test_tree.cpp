#include"AVLtree.h"
#include<gtest.h>

TEST(AVLTreeTest, can_insert_and_search) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 5);
    tree.insert(tree.root, 15);

    EXPECT_TRUE(tree.search(tree.root, 10));
    EXPECT_TRUE(tree.search(tree.root, 20));
    EXPECT_TRUE(tree.search(tree.root, 5));
    EXPECT_TRUE(tree.search(tree.root, 15));
    EXPECT_FALSE(tree.search(tree.root, 25));
}

TEST(AVLTreeTest, insert_duplicates) {
    AVL_Tree<int> tree;
    EXPECT_TRUE(tree.insert(tree.root, 10));
    EXPECT_FALSE(tree.insert(tree.root, 10)); 
}

TEST(AVLTreeTest, _erase_leaf_node) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 5);

    tree.erase(tree.root, 5);
    EXPECT_FALSE(tree.search(tree.root, 5));
    EXPECT_TRUE(tree.search(tree.root, 10));
    EXPECT_TRUE(tree.search(tree.root, 20));
}

TEST(AVLTreeTest, erase_node_with_one_child) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 15);
    tree.insert(tree.root, 25);

    tree.erase(tree.root, 20);
    EXPECT_FALSE(tree.search(tree.root, 20));
    EXPECT_TRUE(tree.search(tree.root, 15));
    EXPECT_TRUE(tree.search(tree.root, 25));
}

TEST(AVLTreeTest, erase_node_with_two_children) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 5);
    tree.insert(tree.root, 15);
    tree.insert(tree.root, 25);
    tree.insert(tree.root, 12);
    tree.insert(tree.root, 17);

    tree.erase(tree.root, 20);
    EXPECT_FALSE(tree.search(tree.root, 20));
    EXPECT_TRUE(tree.search(tree.root, 15));
    EXPECT_TRUE(tree.search(tree.root, 25));
    EXPECT_TRUE(tree.search(tree.root, 12));
    EXPECT_TRUE(tree.search(tree.root, 17));
}

TEST(AVLTreeTest, balance_after_insert) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 30);

    EXPECT_EQ(tree.getHeight(tree.root), 1);
    EXPECT_EQ(tree.root->value, 20);
    EXPECT_EQ(tree.root->left->value, 10);
    EXPECT_EQ(tree.root->right->value, 30);
}

TEST(AVLTreeTest, balance_after_erase) {
    AVL_Tree<int> tree;
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 30);
    tree.insert(tree.root, 5);
    tree.insert(tree.root, 15);
    tree.insert(tree.root, 25);
    tree.insert(tree.root, 35);

    tree.erase(tree.root, 35);
    tree.erase(tree.root, 25);

    EXPECT_LE(abs(tree.getBalance(tree.root)), 1);
}
