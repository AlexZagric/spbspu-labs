#ifndef STACKARRAY_HPP
#define STACKARRAY_HPP
#include "Stack.hpp"
#include "StackOverflow.hpp"

namespace zagrivnyy
{
  template< class T >
  class StackArray: public Stack< T >
  {
  public:
    StackArray(const int size = 100);
    ~StackArray() override;

    void push(const T &e) override;
    T pop() override;
    bool isEmpty() override;

  private:
    T *array_ = nullptr;
    int top_ = 0;
    int size_ = 0;
  };

  template< class T >
  StackArray< T >::StackArray(const int size)
  {
    try
    {
      array_ = new T[size_ = size];
    }
    catch (...)
    {
      throw T;
    }
    top_ = 0;
  }

  template< class T >
  StackArray< T >::~StackArray()
  {
    delete[] array_;
  }

  template< class T >
  void StackArray< T >::push(const T &e)
  {
    if (top_ == size_)
    {
      throw StackOverflow();
    }

    array_[++top_] = e;
  }

  template< class T >
  T StackArray< T >::pop()
  {
    if (top_ == 0)
    {
      throw T;
    }

    return array_[top_--];
  }

  template< class T >
  bool StackArray< T >::isEmpty()
  {
    return top_ == 0;
  }
}
#endif
