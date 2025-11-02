#pragma once
#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
class TQueue
{
protected:
  size_t capacity;
  size_t head;
  size_t tail;
  size_t count;
  T* memory;
public:
  TQueue();
  TQueue(size_t capacity_);
  TQueue(const TQueue& other);
  TQueue(TQueue&& other);
  ~TQueue();

  size_t GetCapacity() const;
  size_t GetFront() const;
  size_t GetRear() const;
  size_t GetCount() const;
  T* GetMemory() const;

  void SetCapacity(size_t capacity_);
  void SetFront(size_t head_);
  void SetRear(size_t tail_);
  void SetCount(size_t count_);
  void SetMemory(T* memory_);

  size_t Size() const;
  void enqueue(const T& element);
  T dequeue();

  bool operator==(const TQueue<T>& other) const;
  bool operator!=(const TQueue<T>& other) const;
  T operator[](size_t index) const;

  bool IsEmpty() const;
  bool IsFull() const;

  class TIterator
  {
  protected:
    TQueue<T>& p;
    size_t cur;
    size_t prev;
  public:
    TIterator(TQueue<T> &queue, size_t start, size_t cnt);
    T& operator*();
    TIterator& operator++();
    TIterator operator++(int);

    bool operator==(const TIterator& other) const;
    bool operator!=(const TIterator& other) const;
  };

  TIterator begin();
  TIterator end();

  template <class I>
  friend istream& operator>>(istream& is, TQueue<I>& queue);

  template <class O>
  friend ostream& operator<<(ostream& os, const TQueue<O>& queue);
};

template <class T>
inline TQueue<T>::TQueue() : capacity(0), head(0), tail(0), count(0), memory(new T[capacity]) {}

template <class T>
inline TQueue<T>::TQueue(size_t capacity_) : capacity(capacity_), head(0), tail(0), count(0), memory(new T[capacity]) {}

template <class T>
inline TQueue<T>::TQueue(const TQueue& other) : capacity(other.capacity), head(other.head), tail(other.tail), count(other.count), memory(new T[capacity])
{
  for (size_t i = 0; i < capacity; ++i)
    memory[i] = other.memory[i];
}

template <class T>
inline TQueue<T>::TQueue(TQueue&& other) : capacity(other.capacity), head(other.head), tail(other.tail), count(other.count), memory(other.memory)
{
  other.memory = nullptr;
  other.capacity = 0;
  other.head = 0;
  other.tail = 0;
  other.count = 0;
}

template <class T>
inline TQueue<T>::~TQueue()
{
  delete[] memory;
}

template <class T>
inline size_t TQueue<T>::GetCapacity() const
{
  return capacity;
}

template <class T>
inline size_t TQueue<T>::GetFront() const
{
  return head;
}

template <class T>
inline size_t TQueue<T>::GetRear() const
{
  return tail;
}

template <class T>
inline size_t TQueue<T>::GetCount() const
{
  return count;
}

template <class T>
inline T* TQueue<T>::GetMemory() const
{
  return memory;
}

template <class T>
inline void TQueue<T>::SetCapacity(size_t capacity_)
{
  if (capacity_ < count)
    throw("Wrong capacity");

  T* newMem = new T[capacity_];
  for (size_t i = 0; i < count; ++i)
    newMem[i] = memory[(head + i) % capacity];

  delete[] memory;
  memory = newMem;
  head = 0;
  tail = count;
  capacity = capacity_;
}

template <class T>
inline void TQueue<T>::SetFront(size_t head_)
{
  if (head_ >= capacity)
    throw("Wrong head");
  head = head_;
}

template <class T>
inline void TQueue<T>::SetRear(size_t tail_)
{
  if (tail_ >= capacity)
    throw("Wrong tail");
  tail = tail_;
}

template <class T>
inline void TQueue<T>::SetCount(size_t count_)
{
  if (count_ > capacity)
    throw("Wrong count");
  count = count_;
}

template <class T>
inline void TQueue<T>::SetMemory(T* memory_)
{
  delete[] memory;
  memory = memory_;
}

template <class T>
inline size_t TQueue<T>::Size() const
{
  return count;
}

template <class T>
inline void TQueue<T>::enqueue(const T& element)
{
  if (IsFull())
  {
    if (capacity == 0)
    {
      capacity = 10;
      memory = new T[capacity];
    }
    else
    {
      size_t newCap = capacity * 2;
      T* newMem = new T[newCap];

      for (size_t i = 0; i < count; ++i)
        newMem[i] = memory[(head + i) % capacity];

      delete[] memory;
      memory = newMem;
      head = 0;
      tail = count;
      capacity = newCap;
    }
  }

  memory[tail] = element;
  tail = (tail + 1) % capacity;
  count++;
}

template <class T>
inline T TQueue<T>::dequeue()
{
  if (IsEmpty())
    throw("Empty queue");

  T element = memory[head];
  head = (head + 1) % capacity;
  count--;
  return element;
}

template <class T>
inline bool TQueue<T>::operator==(const TQueue<T>& other) const
{
  if (count != other.count)
    return false;

  for (size_t i = 0; i < count; ++i)
  {
    if (memory[(head + i) % capacity] != other.memory[(other.head + i) % other.capacity])
      return false;
  }
  return true;
}

template <class T>
inline bool TQueue<T>::operator!=(const TQueue<T>& other) const
{
  return !(*this == other);
}

template <class T>
inline T TQueue<T>::operator[](size_t index) const
{
  if (index >= count)
    throw("Index out of range");
  return memory[(head + index) % capacity];
}

template <class T>
inline bool TQueue<T>::IsEmpty() const
{
  return count == 0;
}

template <class T>
inline bool TQueue<T>::IsFull() const
{
  return count == capacity;
}

template <class T>
inline TQueue<T>::TIterator::TIterator(TQueue<T> &queue, size_t start, size_t cnt) : p(queue), cur(start), prev(cnt) {}

template <class T>
inline T& TQueue<T>::TIterator::operator*()
{
  return p.memory[cur];
}

template <class T>
inline typename TQueue<T>::TIterator& TQueue<T>::TIterator::operator++()
{
  cur = (cur + 1) % p.capacity;
  prev++;
  return *this;
}

template <class T>
inline typename TQueue<T>::TIterator TQueue<T>::TIterator::operator++(int)
{
  TIterator temp = *this;
  ++(*this);
  return temp;
}

template <class T>
inline bool TQueue<T>::TIterator::operator==(const TIterator& other) const
{
  return &p == &other.p && prev == other.prev;
}

template <class T>
inline bool TQueue<T>::TIterator::operator!=(const TIterator& other) const
{
  return !(*this == other);
}

template <class T>
inline typename TQueue<T>::TIterator TQueue<T>::begin()
{
  return TIterator(*this, head, 0);
}

template <class T>
inline typename TQueue<T>::TIterator TQueue<T>::end()
{
  return TIterator(*this, (head + count) % capacity, count);
}

template <class I>
inline istream& operator>>(istream& is, TQueue<I>& queue)
{
  queue.head = 0;
  queue.tail = 0;
  queue.count = 0;

  size_t n;
  is >> n;

  if (n > queue.capacity)
    queue.SetCapacity(n);

  for (size_t i = 0; i < n; ++i)
  {
    I element;
    is >> element;
    queue.enqueue(element);
  }

  return is;
}

template <class O>
inline ostream& operator<<(ostream& os, const TQueue<O>& queue)
{
  os << "[";
  for (size_t i = 0; i < queue.count; ++i)
  {
    os << queue.memory[(queue.head + i) % queue.capacity];
    if (i < queue.count - 1)
      os << ", ";
  }
  os << "]";
  return os;
}