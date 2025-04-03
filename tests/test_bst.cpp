#include <gtest/gtest.h>

#include "../main.cpp"

TEST(BSTTest, EmptyTree)
{
  BST<int> tree;
  EXPECT_EQ(tree.getSize(), 0);
  EXPECT_TRUE(tree.empty());
  EXPECT_FALSE(tree.search(10));
}

TEST(BSTTest, Insertion)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);

  EXPECT_EQ(tree.getSize(), 3);
  EXPECT_FALSE(tree.empty());
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(15));
  EXPECT_FALSE(tree.search(20));
}

TEST(BSTTest, MinMax)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  EXPECT_EQ(tree.getMinimum(), 3);
  EXPECT_EQ(tree.getMaximum(), 15);

  tree.insert(20);
  tree.insert(1);

  EXPECT_EQ(tree.getMinimum(), 1);
  EXPECT_EQ(tree.getMaximum(), 20);
}

TEST(BSTTest, Deletion)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  EXPECT_EQ(tree.getSize(), 5);

  // Delete leaf node
  tree.deleteNode(3);
  EXPECT_EQ(tree.getSize(), 4);
  EXPECT_FALSE(tree.search(3));

  // Delete node with one child
  tree.insert(20);
  tree.deleteNode(15);
  EXPECT_EQ(tree.getSize(), 4);
  EXPECT_FALSE(tree.search(15));
  EXPECT_TRUE(tree.search(20));

  // Delete node with two children
  tree.insert(3);
  tree.deleteNode(5);
  EXPECT_EQ(tree.getSize(), 4);
  EXPECT_FALSE(tree.search(5));
}

TEST(BSTTest, Iterator)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  std::vector<int> expected = {3, 5, 7, 10, 15};
  std::vector<int> actual;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(*it);
  }

  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}

TEST(BSTTest, EdgeCases)
{
  BST<int> tree;

  // Test empty tree exception
  EXPECT_THROW(tree.getMinimum(), std::out_of_range);
  EXPECT_THROW(tree.getMaximum(), std::out_of_range);

  // Test deleting non-existent node
  tree.insert(10);
  tree.deleteNode(20);  // Should not throw, just do nothing
  EXPECT_EQ(tree.getSize(), 1);

  // Test deleting root
  tree.deleteNode(10);
  EXPECT_EQ(tree.getSize(), 0);
  EXPECT_TRUE(tree.empty());
}
