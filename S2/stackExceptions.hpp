#ifndef STACKEXCEPTIONS_HPP
#define STACKEXCEPTIONS_HPP
#include <exception>

namespace zagrivnyy
{
  class StackOverflow: public std::exception
  {
  public:
    StackOverflow():
      reason("Stack Overflow")
    {
    }

    const char *what() const noexcept override
    {
      return reason;
    };

  private:
    const char *reason;
  };

  class StackUnderflow: public std::exception
  {
  public:
    StackUnderflow():
      reason("Stack Underflow")
    {
    }

    const char *what() const noexcept override
    {
      return reason;
    };

  private:
    const char *reason;
  };

  class WrongStackSize: public std::exception
  {
  public:
    WrongStackSize():
      reason("Wrong Stack Size")
    {
    }

    const char *what() const noexcept override
    {
      return reason;
    };

  private:
    const char *reason;
  };
}
#endif
