#include "tqueue.h"

#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length)
{
  ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
  ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_copy_queue)
{
  TQueue<int> s1(5);
  ASSERT_NO_THROW(TQueue<int> q2(s1));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
  TQueue<int> q1(5);
  q1.Put(1);
  q1.Put(2);
  q1.Put(3);
  TQueue<int> q2(q1);
  EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, copied_queue_is_different_object)
{
  TQueue<int> q1(5);
  for (int i = 0; i < 3; i++)
    q1.Put(i);
  TQueue<int> q2(q1);
  q2.Pop();
  q2.Put(12);
  EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, can_put_and_top_element)
{
  TQueue<int> q(5);
  q.Put(5);
  q.Put(6);
  EXPECT_EQ(5, q.Top());
}

TEST(TQueue, can_get_and_pop_element)
{
  TQueue<int> q(5);
  q.Put(5);
  q.Put(6);
  EXPECT_EQ(5, q.Pop());
  EXPECT_EQ(6, q.Pop());
}

TEST(TQueue, can_pop_element)
{
  TQueue<int> q(5);
  q.Put(5);
  q.Put(6);
  q.Pop();
  EXPECT_EQ(6, q.Top());
}

TEST(TQueue, can_check_for_emptyness)
{
  TQueue<int> q(5);
  EXPECT_EQ(true, q.IsEmpty());
  q.Put(11);
  EXPECT_EQ(false, q.IsEmpty());
  q.Pop();
  EXPECT_EQ(true, q.IsEmpty());
}

TEST(TQueue, can_check_for_fullness)
{
  TQueue<int> q(5);
  EXPECT_EQ(false, q.IsFull());
  q.Put(0);
  EXPECT_EQ(false, q.IsFull());
  for (int i = 1; i < 5; i++)
    q.Put(i);
  EXPECT_EQ(true, q.IsFull());
}

TEST(TQueue, cant_put_item_into_full_queue)
{
  TQueue<int> q(5);
  for (int i = 0; i < 5; i++)
    q.Put(i);
  ASSERT_ANY_THROW(q.Put(0));
}

TEST(TQueue, cant_pop_item_from_empty_queue)
{
  TQueue<int> q(5);
  q.Put(0);
  q.Pop();
  ASSERT_ANY_THROW(q.Pop());
}

TEST(TQueue, cant_get_top_item_from_empty_queue)
{
  TQueue<int> q(5);
  q.Put(0);
  q.Pop();
  ASSERT_ANY_THROW(q.Top());
}

TEST(TQueue, can_assign_queue_to_itself)
{
  TQueue<int> q(5);
  ASSERT_NO_THROW(q = q);
}

TEST(TQueue, compare_queue_with_itself_returns_true)
{
  TQueue<int> q(5);
  q.Put(0);
  EXPECT_EQ(true, q == q);
}

TEST(TQueue, compare_different_size_queues_returns_correct)
{
  TQueue<int> q1(5), q2(5);
  q1.Put(5);
  q1.Put(6);
  q2.Put(5);
  EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, compare_same_data_queues_returns_correct)
{
  TQueue<int> q1(5), q2(5);
  q1.Put(5);
  q1.Put(6);
  q2.Put(5);
  q2.Put(6);
  EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, test_queue_cercular_buffer)
{
  TQueue<int> q(4);
  q.Put(12);
  q.Put(13);
  q.Put(14);
  q.Put(15);
  EXPECT_EQ(true, q.IsFull());
  q.Pop();
  EXPECT_EQ(false, q.IsFull());
  ASSERT_NO_THROW(q.Put(16));
  q.Pop();
  ASSERT_NO_THROW(q.Put(17));
  EXPECT_EQ(14, q.Pop());
  EXPECT_EQ(15, q.Pop());
  EXPECT_EQ(16, q.Pop());
  EXPECT_EQ(17, q.Pop());
  EXPECT_EQ(true, q.IsEmpty());
}