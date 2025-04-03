#include <gtest/gtest.h>

#include "../main.cpp"

TEST(LinkedListTest, EmptyList)
{
  LinkedList<int> list;
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PushFront)
{
  LinkedList<int> list;
  list.push_front(10);
  list.push_front(20);
  list.push_front(30);
  EXPECT_EQ(list.getSize(), 3);

  auto it = list.begin();
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);
}

TEST(LinkedListTest, PushBack)
{
  LinkedList<int> list;
  list.push_back(30);
  list.push_back(20);
  list.push_back(10);
  EXPECT_EQ(list.getSize(), 3);

  auto it = list.begin();
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);
}

TEST(LinkedListTest, PopFront)
{
  LinkedList<int> list;
  list.push_front(10);
  list.push_front(20);
  list.push_front(30);

  list.pop_front();
  EXPECT_EQ(list.getSize(), 2);

  auto it = list.begin();
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);

  list.pop_front();
  list.pop_front();
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PopBack)
{
  LinkedList<int> list;
  list.push_front(30);
  list.push_front(20);
  list.push_front(10);

  list.pop_back();
  EXPECT_EQ(list.getSize(), 2);

  auto it = list.begin();
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);

  list.pop_back();
  list.pop_back();
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());
}
