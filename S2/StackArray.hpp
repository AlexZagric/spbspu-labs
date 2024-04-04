#ifndef STACKARRAY_HPP
#define STACKARRAY_HPP
#include "Stack.hpp"

namespace zagrivnyy
{
  template< class T >
  class StackArray: public Stack< T >
  {
  public:
    StackArray(int size = 100);
    ~Stack() override;
    void push() override;
    T pop() override;
    bool isEmpty() override;

  private:
    T *array_ = nullptr;
    int top_ = 0;
    int size_ = 0;
  };
}
#endif
