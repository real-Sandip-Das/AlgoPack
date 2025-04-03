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

TEST(BSTTest, LeftRotate)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(12);
  tree.insert(20);

  // Before rotation: 10 is root, 15 is its right child
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(15));

  // Rotate left at root (10)
  // After rotation: 15 should be the new root, 10 should be its left child
  bool rotationResult = tree.left_rotate(10);
  EXPECT_TRUE(rotationResult);

  // All elements should still be in the tree
  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(12));
  EXPECT_TRUE(tree.search(15));
  EXPECT_TRUE(tree.search(20));

  // Check in-order traversal is still correct (BST property maintained)
  std::vector<int> expected = {5, 10, 12, 15, 20};
  std::vector<int> actual;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(*it);
  }

  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]);
  }

  // Attempt to rotate at a node that doesn't exist or can't be rotated
  EXPECT_FALSE(tree.left_rotate(100));  // Node doesn't exist
  EXPECT_FALSE(tree.left_rotate(20));   // No right child
}

TEST(BSTTest, RightRotate)
{
  BST<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(30);
  tree.insert(5);
  tree.insert(15);

  // Before rotation: 20 is root, 10 is its left child
  EXPECT_TRUE(tree.search(20));
  EXPECT_TRUE(tree.search(10));

  // Rotate right at root (20)
  // After rotation: 10 should be the new root, 20 should be its right child
  bool rotationResult = tree.right_rotate(20);
  EXPECT_TRUE(rotationResult);

  // All elements should still be in the tree
  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(10));
  EXPECT_TRUE(tree.search(15));
  EXPECT_TRUE(tree.search(20));
  EXPECT_TRUE(tree.search(30));

  // Check in-order traversal is still correct (BST property maintained)
  std::vector<int> expected = {5, 10, 15, 20, 30};
  std::vector<int> actual;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(*it);
  }

  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]);
  }

  // Attempt to rotate at a node that doesn't exist or can't be rotated
  EXPECT_FALSE(tree.right_rotate(100));  // Node doesn't exist
  EXPECT_FALSE(tree.right_rotate(5));    // No left child
}

TEST(BSTTest, SequentialRotations)
{
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  // Perform a left rotation followed by right rotation
  tree.left_rotate(10);   // 15 becomes root
  tree.right_rotate(15);  // 10 becomes root again

  // Tree should maintain its BST property
  std::vector<int> expected = {3, 5, 7, 10, 12, 15, 20};
  std::vector<int> actual;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(*it);
  }

  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
