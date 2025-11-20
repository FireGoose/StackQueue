#pragma once
#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  size_t capacity;
  size_t top;
  T* memory;
public:
  TStack();
  TStack(size_t capacity_);
  TStack(const TStack& other);
  TStack(TStack&& other);
  ~TStack();

  size_t GetCapacity() const;
  size_t GetTop() const;
  T* GetMemory() const;

  void SetCapacity(size_t capacity_);
  void SetTop(size_t top_);
  void SetMemory(T* memory_);

  size_t Size() const;
  void push(const T& element);
  T pop();

  bool operator==(const TStack<T>& other) const;
  bool operator!=(const TStack<T>& other) const;
  T operator[](size_t index) const;

  bool IsEmpty() const;
  bool IsFull() const;

  class TIterator
  {
  protected:
    TStack<T>& p;
    size_t cur;
    size_t prev;
  public:
    TIterator(TStack<T> &stack, size_t start, size_t cnt);
    T& operator*();
    TIterator& operator++();
    TIterator operator++(int);

    bool operator==(const TIterator& other) const;
    bool operator!=(const TIterator& other) const;
  };

  TIterator begin();
  TIterator end();

  template <class I>
  friend istream& operator>>(istream& is, TStack<I>& stack);

  template <class O>
  friend ostream& operator<<(ostream& os, const TStack<O>& stack);
};

template <class T>
inline TStack<T>::TStack() : capacity(0), top(0), memory(new T[capacity]) {}

template <class T>
inline TStack<T>::TStack(size_t capacity_) : capacity(capacity_), top(0), memory(new T[capacity]) {}

template <class T>
inline TStack<T>::TStack(const TStack& other) : capacity(other.capacity), top(other.top), memory(new T[capacity])
{
  for (size_t i = 0; i < top; ++i)
    memory[i] = other.memory[i];
}

template <class T>
inline TStack<T>::TStack(TStack&& other) : capacity(other.capacity), top(other.top), memory(other.memory)
{
  other.memory = nullptr;
  other.capacity = 0;
  other.top = 0;
}

template <class T>
inline TStack<T>::~TStack()
{
  delete[] memory;
}

template <class T>
inline size_t TStack<T>::GetCapacity() const
{
  return capacity;
}

template <class T>
inline size_t TStack<T>::GetTop() const
{
  return top;
}

template <class T>
inline T* TStack<T>::GetMemory() const
{
  return memory;
}

template <class T>
inline void TStack<T>::SetCapacity(size_t capacity_)
{
  if (capacity_ < top)
    throw("Wrong capacity");

  T* newMem = new T[capacity_];
  for (size_t i = 0; i < top; ++i)
    newMem[i] = memory[i];

  delete[] memory;
  memory = newMem;
  capacity = capacity_;
}

template <class T>
inline void TStack<T>::SetTop(size_t top_)
{
  if (top_ > capacity)
    throw("Wrong top");
  top = top_;
}

template <class T>
inline void TStack<T>::SetMemory(T* memory_)
{
  delete[] memory;
  memory = memory_;
}

template <class T>
inline size_t TStack<T>::Size() const
{
  return top;
}

template <class T>
inline void TStack<T>::push(const T& element)
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

      for (size_t i = 0; i < top; ++i)
        newMem[i] = memory[i];

      delete[] memory;
      memory = newMem;
      capacity = newCap;
    }
  }
  memory[top] = element;
  top++;
}

template <class T>
inline T TStack<T>::pop()
{
  if (IsEmpty())
    throw("Empty stack");

  return memory[--top];
}

template <class T>
inline bool TStack<T>::operator==(const TStack<T>& other) const
{
  if (top != other.top)
    return false;

  for (size_t i = 0; i < top; ++i)
  {
    if (memory[i] != other.memory[i])
      return false;
  }
  return true;
}

template <class T>
inline bool TStack<T>::operator!=(const TStack<T>& other) const
{
  return !(*this == other);
}

template <class T>
inline T TStack<T>::operator[](size_t index) const
{
  if (index >= top)
    throw("Index out of range");
  return memory[index];
}

template <class T>
inline bool TStack<T>::IsEmpty() const
{
  return top == 0;
}

template <class T>
inline bool TStack<T>::IsFull() const
{
  return top == capacity;
}


template <class T>
inline TStack<T>::TIterator::TIterator(TStack<T> &stack, size_t start, size_t cnt) : p(stack), cur(start), prev(cnt) {}

template <class T>
inline T& TStack<T>::TIterator::operator*()
{
  return p.memory[cur];
}

template <class T>
inline typename TStack<T>::TIterator& TStack<T>::TIterator::operator++()
{
  cur++;
  prev++;
  return *this;
}

template <class T>
inline typename TStack<T>::TIterator TStack<T>::TIterator::operator++(int)
{
  TIterator temp = *this;
  ++(*this);
  return temp;
}

template <class T>
inline bool TStack<T>::TIterator::operator==(const TIterator& other) const
{
  return &p == &other.p && prev == other.prev;
}

template <class T>
inline bool TStack<T>::TIterator::operator!=(const TIterator& other) const
{
  return !(*this == other);
}

template <class T>
inline typename TStack<T>::TIterator TStack<T>::begin()
{
  return TIterator(*this, 0, 0);
}

template <class T>
inline typename TStack<T>::TIterator TStack<T>::end()
{
  return TIterator(*this, top, top);
}

template <class I>
inline istream& operator>>(istream& is, TStack<I>& stack)
{
  stack.top = 0;
  size_t n;
  is >> n;

  if (n > stack.capacity)
    stack.SetCapacity(n);

  for (size_t i = 0; i < n; ++i)
  {
    I element;
    is >> element;
    stack.push(element);
  }

  return is;
}

template <class O>
inline ostream& operator<<(ostream& os, const TStack<O>& stack)
{
  os << "[";
  for (size_t i = 0; i < stack.top; ++i) 
  {
    os << stack.memory[i];
    if (i < stack.top - 1)
      os << ", ";
  }
  os << "]";
  return os;
}
