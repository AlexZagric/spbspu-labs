#ifndef STACK_HPP
#define STACK_HPP

namespace zagrivnyy
{
  template< class T >
  class Stack
  {
  public:
    virtual ~Stack() { }

    virtual void push(const T &e) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
  };
}

#endif
