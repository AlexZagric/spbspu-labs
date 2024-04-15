#ifndef STACKOVERFLOW_HPP
#define STACKOVERFLOW_HPP
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
}
#endif
