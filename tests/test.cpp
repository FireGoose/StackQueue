#include <gtest.h>
#include "TStack.h"
#include "TQueue.h"


TEST(TStackTest, DefaultConstructor)
{
  TStack<int> stack;
  EXPECT_EQ(stack.Size(), 0);
  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_EQ(stack.GetCapacity(), 0);
}

TEST(TStackTest, ParameterizedConstructor)
{
  TStack<int> stack(5);
  EXPECT_EQ(stack.Size(), 0);
  EXPECT_EQ(stack.GetCapacity(), 5);
  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_FALSE(stack.IsFull());
}

TEST(TStackTest, CopyConstructor)
{
  TStack<int> stack1(3);
  stack1.push(1);
  stack1.push(2);

  TStack<int> stack2(stack1);
  EXPECT_EQ(stack2.Size(), 2);
  EXPECT_EQ(stack2.GetCapacity(), 3);
  EXPECT_EQ(stack2.pop(), 2);
  EXPECT_EQ(stack2.pop(), 1);
}

TEST(TStackTest, MoveConstructor)
{
  TStack<int> stack1(3);
  stack1.push(1);
  stack1.push(2);

  TStack<int> stack2(std::move(stack1));
  EXPECT_EQ(stack2.Size(), 2);
  EXPECT_EQ(stack2.GetCapacity(), 3);
  EXPECT_EQ(stack1.GetMemory(), nullptr);
  EXPECT_EQ(stack1.Size(), 0);
}

TEST(TStackTest, PushAndPop)
{
  TStack<int> stack(3);
  stack.push(10);
  stack.push(20);
  stack.push(30);

  EXPECT_EQ(stack.Size(), 3);
  EXPECT_TRUE(stack.IsFull());

  EXPECT_EQ(stack.pop(), 30);
  EXPECT_EQ(stack.pop(), 20);
  EXPECT_EQ(stack.pop(), 10);
  EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, PushWithResize)
{
  TStack<int> stack(2);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(stack.Size(), 3);
  EXPECT_GE(stack.GetCapacity(), 3);
  EXPECT_EQ(stack.pop(), 3);
  EXPECT_EQ(stack.pop(), 2);
  EXPECT_EQ(stack.pop(), 1);
}

TEST(TStackTest, PopEmptyStack)
{
  TStack<int> stack;
  EXPECT_THROW(stack.pop(), const char*);
}

TEST(TStackTest, EqualityOperator)
{
  TStack<int> stack1(3);
  stack1.push(1);
  stack1.push(2);

  TStack<int> stack2(3);
  stack2.push(1);
  stack2.push(2);

  TStack<int> stack3(3);
  stack3.push(3);
  stack3.push(4);

  EXPECT_TRUE(stack1 == stack2);
  EXPECT_FALSE(stack1 == stack3);
  EXPECT_TRUE(stack1 != stack3);
}

TEST(TStackTest, IndexOperator)
{
  TStack<int> stack(3);
  stack.push(10);
  stack.push(20);
  stack.push(30);

  EXPECT_EQ(stack[0], 10);
  EXPECT_EQ(stack[1], 20);
  EXPECT_EQ(stack[2], 30);
  EXPECT_THROW(stack[3], const char*);
}

TEST(TStackTest, SetCapacity)
{
  TStack<int> stack(2);
  stack.push(1);
  stack.push(2);

  stack.SetCapacity(5);
  EXPECT_EQ(stack.GetCapacity(), 5);
  EXPECT_EQ(stack.Size(), 2);
  EXPECT_EQ(stack.pop(), 2);
  EXPECT_EQ(stack.pop(), 1);
}

TEST(TStackTest, Iterator)
{
  TStack<int> stack(3);
  stack.push(1);
  stack.push(2);
  stack.push(3);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = stack.begin(); it != stack.end(); ++it)
    EXPECT_EQ(*it, expected[i++]);

  auto it = stack.begin();
  EXPECT_EQ(*it, 1);
  auto it2 = it++;
  EXPECT_EQ(*it2, 1);
  EXPECT_EQ(*it, 2);
}

TEST(TQueueTest, DefaultConstructor)
{
  TQueue<int> queue;
  EXPECT_EQ(queue.Size(), 0);
  EXPECT_TRUE(queue.IsEmpty());
  EXPECT_EQ(queue.GetCapacity(), 0);
}

TEST(TQueueTest, ParameterizedConstructor)
{
  TQueue<int> queue(5);
  EXPECT_EQ(queue.Size(), 0);
  EXPECT_EQ(queue.GetCapacity(), 5);
  EXPECT_TRUE(queue.IsEmpty());
  EXPECT_FALSE(queue.IsFull());
}

TEST(TQueueTest, CopyConstructor)
{
  TQueue<int> queue1(3);
  queue1.enqueue(1);
  queue1.enqueue(2);

  TQueue<int> queue2(queue1);
  EXPECT_EQ(queue2.Size(), 2);
  EXPECT_EQ(queue2.GetCapacity(), 3);
  EXPECT_EQ(queue2.dequeue(), 1);
  EXPECT_EQ(queue2.dequeue(), 2);
}

TEST(TQueueTest, MoveConstructor)
{
  TQueue<int> queue1(3);
  queue1.enqueue(1);
  queue1.enqueue(2);

  TQueue<int> queue2(std::move(queue1));
  EXPECT_EQ(queue2.Size(), 2);
  EXPECT_EQ(queue2.GetCapacity(), 3);
  EXPECT_EQ(queue1.GetMemory(), nullptr);
  EXPECT_EQ(queue1.Size(), 0);
}

TEST(TQueueTest, EnqueueAndDequeue)
{
  TQueue<int> queue(3);
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  EXPECT_EQ(queue.Size(), 3);
  EXPECT_TRUE(queue.IsFull());

  EXPECT_EQ(queue.dequeue(), 10);
  EXPECT_EQ(queue.dequeue(), 20);
  EXPECT_EQ(queue.dequeue(), 30);
  EXPECT_TRUE(queue.IsEmpty());
}

TEST(TQueueTest, EnqueueWithResize)
{
  TQueue<int> queue(2);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  EXPECT_EQ(queue.Size(), 3);
  EXPECT_GE(queue.GetCapacity(), 3);
  EXPECT_EQ(queue.dequeue(), 1);
  EXPECT_EQ(queue.dequeue(), 2);
  EXPECT_EQ(queue.dequeue(), 3);
}

TEST(TQueueTest, CircularBufferBehavior)
{
  TQueue<int> queue(3);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  EXPECT_EQ(queue.dequeue(), 1);
  queue.enqueue(4);

  EXPECT_EQ(queue.dequeue(), 2);
  EXPECT_EQ(queue.dequeue(), 3);
  EXPECT_EQ(queue.dequeue(), 4);
  EXPECT_TRUE(queue.IsEmpty());
}

TEST(TQueueTest, DequeueEmptyQueue)
{
  TQueue<int> queue;
  EXPECT_THROW(queue.dequeue(), const char*);
}

TEST(TQueueTest, EqualityOperator)
{
  TQueue<int> queue1(3);
  queue1.enqueue(1);
  queue1.enqueue(2);

  TQueue<int> queue2(3);
  queue2.enqueue(1);
  queue2.enqueue(2);

  TQueue<int> queue3(3);
  queue3.enqueue(3);
  queue3.enqueue(4);

  EXPECT_TRUE(queue1 == queue2);
  EXPECT_FALSE(queue1 == queue3);
  EXPECT_TRUE(queue1 != queue3);
}

TEST(TQueueTest, IndexOperator)
{
  TQueue<int> queue(3);
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  EXPECT_EQ(queue[0], 10);
  EXPECT_EQ(queue[1], 20);
  EXPECT_EQ(queue[2], 30);
  EXPECT_THROW(queue[3], const char*);
}

TEST(TQueueTest, SetCapacity)
{
  TQueue<int> queue(2);
  queue.enqueue(1);
  queue.enqueue(2);

  queue.SetCapacity(5);
  EXPECT_EQ(queue.GetCapacity(), 5);
  EXPECT_EQ(queue.Size(), 2);
  EXPECT_EQ(queue.dequeue(), 1);
  EXPECT_EQ(queue.dequeue(), 2);
}

TEST(TQueueTest, Iterator)
{
  TQueue<int> queue(3);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = queue.begin(); it != queue.end(); ++it)
    EXPECT_EQ(*it, expected[i++]);

  queue.dequeue();
  queue.enqueue(4);

  int expected2[] = {2, 3, 4};
  i = 0;
  for (auto it = queue.begin(); it != queue.end(); ++it)
    EXPECT_EQ(*it, expected2[i++]);
}


TEST(IOStreamTest, StackOutput)
{
  TStack<int> stack(3);
  stack.push(1);
  stack.push(2);
  stack.push(3);

  std::stringstream ss;
  ss << stack;
  EXPECT_EQ(ss.str(), "[1, 2, 3]");
}

TEST(IOStreamTest, QueueOutput)
{
  TQueue<int> queue(3);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  std::stringstream ss;
  ss << queue;
  EXPECT_EQ(ss.str(), "[1, 2, 3]");
}

TEST(IOStreamTest, StackInput)
{
  TStack<int> stack(5);
  std::stringstream ss("3\n10 20 30");
  ss >> stack;

  EXPECT_EQ(stack.Size(), 3);
  EXPECT_EQ(stack.pop(), 30);
  EXPECT_EQ(stack.pop(), 20);
  EXPECT_EQ(stack.pop(), 10);
}

TEST(IOStreamTest, QueueInput)
{
  TQueue<int> queue(5);
  std::stringstream ss("3\n10 20 30");
  ss >> queue;

  EXPECT_EQ(queue.Size(), 3);
  EXPECT_EQ(queue.dequeue(), 10);
  EXPECT_EQ(queue.dequeue(), 20);
  EXPECT_EQ(queue.dequeue(), 30);
}


TEST(TemplateTest, StackWithDouble)
{
  TStack<double> stack(3);
  stack.push(1.5);
  stack.push(2.7);

  EXPECT_DOUBLE_EQ(stack.pop(), 2.7);
  EXPECT_DOUBLE_EQ(stack.pop(), 1.5);
}

TEST(TemplateTest, QueueWithString)
{
  TQueue<std::string> queue(3);
  queue.enqueue("hello");
  queue.enqueue("world");

  EXPECT_EQ(queue.dequeue(), "hello");
  EXPECT_EQ(queue.dequeue(), "world");
}


TEST(EdgeCaseTest, StackZeroCapacity)
{
  TStack<int> stack(0);
  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_TRUE(stack.IsFull());

  stack.push(1);
  EXPECT_FALSE(stack.IsEmpty());
  EXPECT_EQ(stack.pop(), 1);
}

TEST(EdgeCaseTest, QueueZeroCapacity)
{
  TQueue<int> queue(0);
  EXPECT_TRUE(queue.IsEmpty());
  EXPECT_TRUE(queue.IsFull());

  queue.enqueue(1);
  EXPECT_FALSE(queue.IsEmpty());
  EXPECT_EQ(queue.dequeue(), 1);
}

TEST(EdgeCaseTest, StackMultipleResize)
{
  TStack<int> stack(1);
  for (int i = 0; i < 100; ++i)
    stack.push(i);

  EXPECT_EQ(stack.Size(), 100);
  for (int i = 99; i >= 0; --i)
    EXPECT_EQ(stack.pop(), i);
}

TEST(EdgeCaseTest, QueueMultipleResize)
{
  TQueue<int> queue(1);
  for (int i = 0; i < 100; ++i)
    queue.enqueue(i);

  EXPECT_EQ(queue.Size(), 100);
  for (int i = 0; i < 100; ++i)
    EXPECT_EQ(queue.dequeue(), i);
}
