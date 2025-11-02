#include <iostream>
#include "TStack.h"
#include "TQueue.h"


int main()
{
  TStack<int> stack(5);
  stack.push(1);
  stack.push(2);
  stack.push(3);

  cout << stack << endl;

  TQueue<int> queue(5);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  cout << queue << endl; // [1, 2, 3]
  cout << queue.dequeue() << endl; // 1
  cout << queue << endl; // [2, 3]

  queue.enqueue(4);
  cout << queue << endl; // [2, 3, 4]
}